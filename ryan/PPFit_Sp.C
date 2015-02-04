#include "RelCalculator.h"
Double_t TKA = 258.5062;

void PPFit_Sp(Int_t angle1 = 0, Int_t angle2 = 180, Int_t LR = 1, Int_t OPCM = 1){

//   const char* rootfile="ppAll_1118_OpenCorr.root";
   const char* rootfile="proton.root";
   TFile *f0 = new TFile (rootfile); TTree *tree = (TTree*)f0->Get("tree");
   
   Double_t OpenAngGateRange[2] = {84, 90};
   Bool_t CentralEqSide = 1;
   Bool_t AuxGateSwitch[2] = {1,1}; // beamZ, OpenPhi
   Double_t OpenPhiGate = 7.5;
   Double_t beamZGate[2] = {10,60}; //mid, half-width
   Double_t sideGateExtL = 0; //deg
   Double_t sideGateExtR = 0;
   
   printf("================> %s opened.\n", rootfile);
   
   //==================================================================================== calculate theta 
   if (OPCM ==1 ){
      Int_t    cmThetaRange[2] = {angle1, angle2};
      Double_t thetaOpRange[2] ={CMtoLabTheta(TKA,cmThetaRange[0]), CMtoLabTheta(TKA,cmThetaRange[1])};
      printf(" using CM Frame Theta1 (%4.1f,%4.1f) = Lab1(%5.2f, %5.2f)\n",cmThetaRange[0],cmThetaRange[1], thetaOpRange[0], thetaOpRange[1]);
   }else{
      Int_t    cmThetaRange[2] = {angle1, angle2};
      Double_t thetaOpRange[2] = {cmThetaRange[0], cmThetaRange[1]};
      printf(" using Lab Frame Theta (%4.1f,%4.1f)\n",thetaOpRange[0], thetaOpRange[1]);
   }
   Double_t OpenAngGateRange_width = OpenAngGateRange[1] - OpenAngGateRange[0];
      
   //==================================================================================== Set Gates
   TString thetaGateTitle;
   //TString thetaGateTitle2;
   if ( LR == 1) {
      thetaGateTitle.Form("p2p.fRecoilL.Theta()*TMath::RadToDeg() > %5.2f && p2p.fRecoilL.Theta()*TMath::RadToDeg() < %5.2f", thetaOpRange[0], thetaOpRange[1]);
      //thetaGateTitle2.Form("theta2*TMath::RadToDeg() > %5.2f && theta2*TMath::RadToDeg() < %5.2f", thetaOpRange2[0], thetaOpRange2[1]);
   }else{
      thetaGateTitle.Form("p2p.fRecoilR.Theta()*TMath::RadToDeg() > %5.2f && p2p.fRecoilR.Theta()*TMath::RadToDeg() < %5.2f", thetaOpRange[0], thetaOpRange[1]);
      //thetaGateTitle2.Form("theta1*TMath::RadToDeg() > %5.2f && theta1*TMath::RadToDeg() < %5.2f", thetaOpRange2[0], thetaOpRange2[1]);
   }
   TCut thetaGate;
   thetaGate += thetaGateTitle;
   
   TString centralGateTitle, sideGateTitle;
   centralGateTitle.Form("TMath::Abs((p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()-%5.2f)<%5.2f", OpenAngGateRange[0]+OpenAngGateRange_width/2, OpenAngGateRange_width/2);
   sideGateTitle.Form("TMath::Abs((p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()-%5.2f)<%5.2f || TMath::Abs((p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()-%5.2f)<%5.2f",
              OpenAngGateRange[0]-OpenAngGateRange_width/4 - sideGateExtL, OpenAngGateRange_width/4 + sideGateExtL, 
              OpenAngGateRange[1]+OpenAngGateRange_width/4 + sideGateExtR, OpenAngGateRange_width/4 + sideGateExtR);
   TCut CentralGate, SideGate;
   CentralGate += centralGateTitle;
   SideGate += sideGateTitle;
   
   TString AuxGateTitle;
   AuxGateTitle.Form("abs(beamZ.fAverage-%2.0f)<%2.0f", beamZGate[0], beamZGate[1]);
   TString AuxGate2Title;
   AuxGate2Title.Form("abs(abs(p2p.fRecoilL.Phi()-p2p.fRecoilR.Phi())*TMath::RadToDeg()-180)<%3.1f", OpenPhiGate);
   TCut AuxGate, AuxGate2;
   
   if ( AuxGateSwitch[0] ) {
   	AuxGate = AuxGateTitle;
	}
	
	if ( AuxGateSwitch[1] ) {
   	AuxGate2 = AuxGate2Title;
   }
   if ( CentralEqSide ){
   	SideGate = CentralGate;
   }
   
   CentralGate.Print();
   SideGate.Print();
   thetaGate.Print();
   AuxGate.Print();
   AuxGate2.Print();
   
   //-------------------------------- Gate text
   TString thetaGateText;
   if( LR ==1 ){
   	thetaGateText.Form("%4.1f<#theta_L<%4.1f", thetaOpRange[0], thetaOpRange[1]);
   }else{
   	thetaGateText.Form("%4.1f<#theta_R<%4.1f", thetaOpRange[0], thetaOpRange[1]);
   }
   
   TString CentralGateText;
   CentralGateText.Form("|#Delta#theta-%4.1f|<%4.1f",  OpenAngGateRange[0]+OpenAngGateRange_width/2, OpenAngGateRange_width/2);
   
   TString SideGate1Text, SideGate2Text;;
   SideGate1Text.Form("#Delta#theta#in(%4.1f,%4.1f)", OpenAngGateRange[0]-OpenAngGateRange_width/2 - sideGateExtL, OpenAngGateRange[0]);
   SideGate2Text.Form("#Delta#theta#in(%4.1f,%4.1f)", OpenAngGateRange[1], OpenAngGateRange[1] + OpenAngGateRange_width/2 + sideGateExtR);
   
   if ( CentralEqSide ){
   	SideGate1Text = "";
   	SideGate2Text = "";
   }
   
   TString AuxGateText;
   AuxGateText.Form("|BeamZ-%2.0f|<%2.0f", beamZGate[0], beamZGate[1]);
   TString AuxGate2Text;
   AuxGate2Text.Form("|#Delta#Phi|<%3.1f", OpenPhiGate);
   
   
   //================================================================================== Setting histograms
   gStyle->SetOptStat(0);
   TCanvas * cSp = new TCanvas ("cSp","cSp", 200,50,2000,800);
   cSp->Divide(5,2);
   TString h1Title;
   h1Title.Form("%s", rootfile);
   
   Double_t DisplayRangeH[2] = {-30,30};
   Int_t nBinH = TMath::Nint((DisplayRangeH[1]-DisplayRangeH[0])/1.);
   TH1F * h1 = new TH1F("h1",h1Title, nBinH, DisplayRangeH[0], DisplayRangeH[1]);
   h1->SetMinimum(0);
   h1->SetXTitle("Sp [MeV]");
   h1->SetYTitle("Count / 1 MeV");
   h1->SetStats(1);
   TH1F * h2 = new TH1F("h2",h1Title, nBinH, DisplayRangeH[0], DisplayRangeH[1]);
   h2->SetMinimum(0);
   h2->SetLineColor(2);
   h2->SetStats(0);
   TH1F * h3 = new TH1F("h3","h1-h2", nBinH, DisplayRangeH[0], DisplayRangeH[1]);
   
   Double_t DisplayRangeG[2] = {82,94};
   Int_t nBinG = (DisplayRangeG[1]-DisplayRangeG[0])*8;
   TString h1gTitle;
   h1gTitle.Form("OpenTheta");

   TH1F * h1g = new TH1F("h1g",h1gTitle, nBinG, DisplayRangeG[0], DisplayRangeG[1]);
   h1g->SetXTitle("theta1+theta2 [deg]");
   h1g->SetYTitle("Count / 0.125 deg");
   h1g->SetStats(0);
   h1g->SetMinimum(0);
   TH1F * h2g = new TH1F("h2g","gate2", nBinG, DisplayRangeG[0], DisplayRangeG[1]);
   h2g->SetLineColor(2);
   h2g->SetStats(1);
   TH1F * h3g = new TH1F("h3g","", nBinG, DisplayRangeG[0], DisplayRangeG[1]);
   
   Int_t ThetaRange[2] = { 10, 80};
   Int_t ThetaBin = (ThetaRange[1]-ThetaRange[0])*4;
   TString hLTitle, hRTitle;
   if ( LR ==1 ){
      hLTitle.Form("%6.2f <theta1<%6.2f",thetaOpRange[0], thetaOpRange[1]);
      hRTitle.Form("theta2");
   }else{
      hRTitle.Form("%6.2f <theta2<%6.2f",thetaOpRange[0], thetaOpRange[1]);
      hLTitle.Form("theta1");   
   }
   TH1F * hL = new TH1F("hL", hLTitle,  ThetaBin, ThetaRange[0], ThetaRange[1]);
   TH1F * hR = new TH1F("hR", hRTitle,  ThetaBin, ThetaRange[0], ThetaRange[1]);
   hL->SetMinimum(0);
   hR->SetMinimum(0);
   hR->SetLineColor(2);
   
   TH2F * hTAngL = new TH2F("hTAngL", "T1 vs theta1", 100,  0, 250, 100, 0, 250);
   TH2F * hTAngR = new TH2F("hTAngR", "T2 vs theta2", 140, 10,  80, 100, 0, 250);
   
   TH1F * hPhi = new TH1F("hPhi", "Open(Phi)", 120, -30, 30);
   hPhi->SetMinimum(0);
   hPhi->SetXTitle("phi1+phi2 [deg]");
   hPhi->SetYTitle("Count / 0.5 deg");
   TH1F * hPhibg = new TH1F("hPhibg", "Open(Phi)", 120, -30, 30); 
   hPhibg->SetMinimum(0);
   hPhibg->SetLineColor(2);
   
   TH1F * hbeamZ = new TH1F("hbeamZ", "beamZ", 100,-100,200);
   hbeamZ->SetMinimum(0);
   hbeamZ->SetXTitle("BeamZ [mm]");
   hbeamZ->SetYTitle("Count / 3 mm");
   TH1F * hbeamZbg = new TH1F("hbeamZbg", "beamZ", 100,-100,200); 
   hbeamZbg->SetMinimum(0);
   hbeamZbg->SetLineColor(2);
   TH1F * hbeamSub= new TH1F("hbeamSub","hbeamZ-hbeamZbg", 100, -100, 200);
   
   TH1F * hEsum = new TH1F("hEsum", "E1+E2", 100,100,350);
   hEsum->SetMinimum(0);
   hEsum->SetXTitle("E1+E1 [MeV]");
   hEsum->SetYTitle("count / 2.5 MeV");
   TH1F * hEsumBG = new TH1F("hEsumBG", "E1+E2", 100,100,350); 
   hEsumBG->SetMinimum(0);
   hEsumBG->SetLineColor(2);
   TH1F * hEsumSub= new TH1F("hEsumSub","hEsum-hEsumBG", 100, 150, 350);
  
   
   //=========================================================================================== Calculate
  	TString countText;
   TLatex *text = new TLatex();
   text->SetNDC();
   text->SetTextSize(0.04);
   
  	//--------------------------------------------
   cSp->cd(1);
   tree->Draw("p2p.fSp>>h1",CentralGate && thetaGate && AuxGate2 && AuxGate);
   tree->Draw("p2p.fSp>>h2",SideGate && thetaGate && !AuxGate2  && AuxGate, "same");
   
   text->DrawLatex(0.6,0.80,thetaGateText);
   text->DrawLatex(0.6,0.75,AuxGateText);
   
   text->SetTextColor(4);if( CentralEqSide ) text->SetTextColor(1);text->DrawLatex(0.6,0.70,CentralGateText);
   text->SetTextColor(4);text->DrawLatex(0.6,0.65,AuxGate2Text);
   text->SetTextColor(2);text->DrawLatex(0.6,0.60, "!" + AuxGate2Text);
   text->SetTextColor(2);text->DrawLatex(0.6,0.55,SideGate1Text);
   text->SetTextColor(2);text->DrawLatex(0.6,0.50,SideGate2Text);
   text->SetTextColor(1);
   
   cSp->cd(6);
   //h3 = HistSub(h1, h2, 0, 10);
   TH1F* h3= new TH1F(*h1);
  	h3->Sumw2();
  	h3->Add(h2,-1);
  	h3->Draw();
  	
  	TF1 * fitSp = new TF1("fitSp", "gaus", -20, 20);
  	fitSp->SetParameters(200, 0, 3);
  	h3->Fit("fitSp");
  	
  	countText.Form("Sp:%.2f#pm%.2f", fitSp->GetParameter(1), fitSp->GetParError(1));
   text->DrawLatex(0.6, 0.85, countText);
   countText.Form("#sigma:%.2f#pm%.2f",fitSp->GetParameter(2), fitSp->GetParError(2));
   text->DrawLatex(0.6, 0.8, countText);
   countText.Form("#chi^{2}:%.2f",fitSp->GetChisquare()/fitSp->GetNDF());
   text->DrawLatex(0.6, 0.75, countText);
   
   /*
   countText.Form("%5s%5d","Tot:", CountTotal);
   text->DrawLatex(0.6, 0.85, countText);
   countText.Form("%5s%5d", "BG:",CountBG);
   text->DrawLatex(0.6, 0.8, countText);
   countText.Form("%5s%5d[%3d]","Sig:", CountSignal, TMath::Nint(ErrorSignal));
   text->DrawLatex(0.6, 0.75, countText);*/
  	
  	//--------------------------------------------
   cSp->cd(2);
   tree->Draw("(p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()>>h1g",CentralGate && thetaGate && AuxGate2  && AuxGate);
   tree->Draw("(p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()>>h2g",SideGate && thetaGate && !AuxGate2  && AuxGate, "same");
   
   text->DrawLatex(0.6,0.80,thetaGateText);
   text->DrawLatex(0.6,0.75,AuxGateText);
   text->SetTextColor(4);if( CentralEqSide ) text->SetTextColor(1);text->DrawLatex(0.6,0.70,CentralGateText);
   text->SetTextColor(4);text->DrawLatex(0.6,0.65,AuxGate2Text);
   text->SetTextColor(2);text->DrawLatex(0.6,0.60, "!" + AuxGate2Text);
   text->SetTextColor(2);text->DrawLatex(0.6,0.55,SideGate1Text);
   text->SetTextColor(2);text->DrawLatex(0.6,0.50,SideGate2Text);
   text->SetTextColor(1);
   
   
   //h3g = HistSub(h1g, h2g, 86,1);
   
   Int_t CountTotal=h1g->GetEntries();
   Int_t CountBG = h2g->GetEntries();
   
   Int_t CountSignal = CountTotal - CountBG;
   Double_t ErrorSignal = sqrt((Double_t)CountTotal + (Double_t)CountBG);
   
   printf("====== Central:%d, Side:%d => Signal:%d [%5.1f] \n",  CountTotal, CountBG, CountSignal, ErrorSignal);

   cSp->cd(7);
   TH1F* h4= new TH1F(*h1g);
  	h4->Sumw2();
  	h4->Add(h2g,-1);
  	h4->Draw();
  	
  	TF1 * fit = new TF1("fit", "gaus", 80, 92);
  	fit->SetParameters(200, 86.5, 1);
  	h4->Fit("fit");
  	
   countText.Form("#Delta#theta:%.2f#pm%.2f", fit->GetParameter(1), fit->GetParError(1));
   text->DrawLatex(0.6, 0.85, countText);
   countText.Form("#sigma:%.2f#pm%.2f",fit->GetParameter(2), fit->GetParError(2));
   text->DrawLatex(0.6, 0.8, countText);
   countText.Form("#chi^{2}:%.2f",fit->GetChisquare()/fit->GetNDF());
   text->DrawLatex(0.6, 0.75, countText);
   
  	//--------------------------------------------
   cSp->cd(3);  
   //tree->Draw("abs(p2p.fRecoilL.Phi()-p2p.fRecoilR.Phi())*TMath::RadToDeg()-180>>hPhi", CentralGate, "");   
   tree->Draw("abs(p2p.fRecoilL.Phi()-p2p.fRecoilR.Phi())*TMath::RadToDeg()-180>>hPhi", CentralGate && thetaGate && AuxGate && "abs(p2p.fSp)<13", "");
   tree->Draw("abs(p2p.fRecoilL.Phi()-p2p.fRecoilR.Phi())*TMath::RadToDeg()-180>>hPhibg", SideGate && thetaGate && AuxGate && "abs(p2p.fSp)>13", "same");
  	
   text->DrawLatex(0.6,0.80,thetaGateText);
   text->DrawLatex(0.6,0.75,AuxGateText);
   text->SetTextColor(4);if( CentralEqSide ) text->SetTextColor(1);text->DrawLatex(0.6,0.70,CentralGateText);
   text->SetTextColor(4);text->DrawLatex(0.6,0.65,"|Sp|<13");
   text->SetTextColor(2);text->DrawLatex(0.6,0.60,"|Sp>13|");
   text->SetTextColor(2);text->DrawLatex(0.6,0.55,SideGate1Text);
   text->SetTextColor(2);text->DrawLatex(0.6,0.50,SideGate2Text);
   text->SetTextColor(1);
  	
  	cSp->cd(8);
  	TH1F * htest = new TH1F(*hPhi);
  	htest->Sumw2();
  	htest->Add(hPhibg,-1);
  	htest->Draw();
  	//htest->Fit("gaus", "", "", -20, 20);
  	
  	TF1 * fitPhi = new TF1("fitPhi", "gaus", 80, 92);
  	fitPhi->SetParameters(200, 86.5, 1);
  	htest->Fit("fitPhi");
   
  	countText.Form("#Delta#phi:%.2f#pm%.2f", fitPhi->GetParameter(1), fitPhi->GetParError(1));
   text->DrawLatex(0.6, 0.85, countText);
   countText.Form("#sigma:%.2f#pm%.2f",fitPhi->GetParameter(2), fitPhi->GetParError(2));
   text->DrawLatex(0.6, 0.8, countText);
   countText.Form("#chi^{2}:%.2f",fitPhi->GetChisquare()/fitPhi->GetNDF());
   text->DrawLatex(0.6, 0.75, countText);
  	
  	
  	//--------------------------------------------
  	cSp->cd(4);
   tree->Draw("beamZ.fAverage>>hbeamZ",CentralGate && thetaGate && AuxGate2 , "");
   tree->Draw("beamZ.fAverage>>hbeamZbg",SideGate && thetaGate && !AuxGate2 , "same");
  	
   text->DrawLatex(0.6,0.80,thetaGateText);
   text->SetTextColor(4);if( CentralEqSide ) text->SetTextColor(1);text->DrawLatex(0.6,0.70,CentralGateText);
   text->SetTextColor(4);text->DrawLatex(0.6,0.65,AuxGate2Text);
   text->SetTextColor(2);text->DrawLatex(0.6,0.60, "!" + AuxGate2Text);
   text->SetTextColor(2);text->DrawLatex(0.6,0.55,SideGate1Text);
   text->SetTextColor(2);text->DrawLatex(0.6,0.50,SideGate2Text);
   text->SetTextColor(1);
     	
  	cSp->cd(9);
  	TH1F * hbeamZ3 = new TH1F(*hbeamZ);
  	hbeamZ3->Sumw2();
  	hbeamZ3->Add(hbeamZbg,-1);
  	hbeamZ3->Draw();
  	//htest->Fit("gaus", "", "", -20, 20);
  	
  	TF1 * fitbeamZ = new TF1("fitbeamZ", "gaus", -50, 120);
  	fitbeamZ->SetParameters(200, 10, 50);
  	hbeamZ3->Fit("fitbeamZ");
   
  	countText.Form("BeamZ:%.2f#pm%.2f", fitbeamZ->GetParameter(1), fitbeamZ->GetParError(1));
   text->DrawLatex(0.5, 0.85, countText);
   countText.Form("#sigma:%.2f#pm%.2f",fitbeamZ->GetParameter(2), fitbeamZ->GetParError(2));
   text->DrawLatex(0.6, 0.8, countText);
   countText.Form("#chi^{2}:%.2f",fitbeamZ->GetChisquare()/fitbeamZ->GetNDF());
   text->DrawLatex(0.6, 0.75, countText);
  	
  	
  	cSp->cd(5);
   //tree->Draw("p2p.fSp:(p2p.fRecoilL.E()+p2p.fRecoilR.E()-2*938.272)>>htest(100,0,350,100,-30,30)",CentralGate && thetaGate && AuxGate && AuxGate2, "colz");
   tree->Draw("(p2p.fRecoilL.E()+p2p.fRecoilR.E()-2*938.272)>>hEsum"  ,CentralGate && thetaGate && AuxGate && AuxGate2, "");
   tree->Draw("(p2p.fRecoilL.E()+p2p.fRecoilR.E()-2*938.272)>>hEsumBG",SideGate && thetaGate && AuxGate && !AuxGate2, "same");
   
   text->DrawLatex(0.6,0.80,thetaGateText);
   text->DrawLatex(0.6,0.75,AuxGateText);
   text->SetTextColor(4);if( CentralEqSide ) text->SetTextColor(1);text->DrawLatex(0.6,0.70,CentralGateText);
   text->SetTextColor(4);text->DrawLatex(0.6,0.65,AuxGate2Text);
   text->SetTextColor(2);text->DrawLatex(0.6,0.60,"!" + AuxGate2Text);
   text->SetTextColor(2);text->DrawLatex(0.6,0.55,SideGate1Text);
   text->SetTextColor(2);text->DrawLatex(0.6,0.50,SideGate2Text);
   text->SetTextColor(1);   
   
   cSp->cd(10);
  	//hEsumSub = HistSub(hEsum, hEsumBG, 260, 60);
  	TH1F * hEsumSub = new TH1F(*hEsum);
  	hEsumSub->Sumw2();
  	hEsumSub->Add(hEsumBG,-1);
  	hEsumSub->Draw();
  	//htest->Fit("gaus", "", "", -20, 20);
  	
  	TF1 * fitEsum = new TF1("fitEsum", "gaus", 0, 300);
  	fitEsum->SetParameters(200, 250, 100);
  	hEsumSub->Fit("fitEsum");
   
  	countText.Form("#SigmaE:%.2f#pm%.2f", fitEsum->GetParameter(1), fitEsum->GetParError(1));
   text->DrawLatex(0.6, 0.85, countText);
   countText.Form("#sigma:%.2f#pm%.2f",fitEsum->GetParameter(2), fitEsum->GetParError(2));
   text->DrawLatex(0.6, 0.8, countText);
   countText.Form("#chi^{2}:%.2f",fitEsum->GetChisquare()/fitEsum->GetNDF());
   text->DrawLatex(0.6, 0.75, countText);
  	

   /*if (LR == 1){
      tree->Draw("p2p.fRecoilL.Theta()*TMath::RadToDeg()>>hL", CentralGate && thetaGate && AuxGate);
      tree->Draw("p2p.fRecoilR.Theta()*TMath::RadToDeg()>>hR", CentralGate && thetaGate && AuxGate, "same");
   }else{
      tree->Draw("p2p.fRecoilR.Theta()*TMath::RadToDeg()>>hR", CentralGate && thetaGate && AuxGate);
      tree->Draw("p2p.fRecoilL.Theta()*TMath::RadToDeg()>>hL", CentralGate && thetaGate && AuxGate, "same");
   }*/
   
   //hbeamSub = HistSub(hbeamZ, hbeamZbg, 11, 30);
}

//#####################################################################
TH1F* HistSub(TH1F *hist1, TH1F *hist2, Double_t min, Double_t max){
   Int_t nBin = hist1-> GetNbinsX();
   Double_t Xmin = hist1->GetBinLowEdge(1);
   Double_t Xmax = hist1->GetBinLowEdge(nBin)+hist1->GetBinWidth(nBin);
   if ( nBin != hist2->GetNbinsX()) return 0;
   Double_t xx;
   Double_t countS = 0, countTot = 0, countBG = 0;
   // Count Range
   Double_t countRangeSet[2] = {min, max};//center, half-width
   Double_t countRange[2] = {countRangeSet[0]-countRangeSet[1], countRangeSet[0]+countRangeSet[1]};
   TString histName, histTitle;
   histName.Form("%s - %s",hist1->GetName(), hist2->GetName());
   histTitle.Form("countRange(%5.1f-%5.1f)",countRange[0],countRange[1]);
   TH1F * hout = new TH1F( histName, histTitle, nBin, Xmin, Xmax);
   TString XaxisTitle;
   XaxisTitle.Form("%s", hist1->GetXaxis()->GetTitle());
   hout->SetXTitle(XaxisTitle);

   for ( Int_t i = 1; i <=nBin; i++){
      xx = hist1->GetBinCenter(i);
      hout->Fill(xx,hist1->GetBinContent(i) - hist2->GetBinContent(i));
      hout->SetBinError(i, TMath::Sqrt( hist1->GetBinContent(i) + hist2->GetBinContent(i)));
      if ( xx > countRange[0] && xx < countRange[1]){
         countBG  += hist2->GetBinContent(i);
         countTot += hist1->GetBinContent(i);
         countS += hist1->GetBinContent(i) - hist2->GetBinContent(i);
      }
   }
   
   //TF1 * fit = new TF1("fit","gaus", -10, 10);
   TF1 * fit = new TF1("fit","gaus(0) + gaus(3)", -15, 10);
   Double_t para[6] = {400, -10, 4, 800, 0, 4};
   fit->SetParameters(para);
   hout->Fit(fit, "R");
  	fit->GetParameters(para);
   
   hout->Draw("E1");
   printf("Count(%4.1f, %4.1f): Signal:%5d [%6.1f] | Total:%d, BG:%d \n",countRange[0], countRange[1], countS, TMath::Sqrt(countTot+countBG), countTot, countBG);

   TLine *line1 = new TLine(countRange[0], hout->GetMinimum(), countRange[0], hout->GetMaximum());
   TLine *line2 = new TLine(countRange[1], hout->GetMinimum(), countRange[1], hout->GetMaximum());
   line1->SetLineColor(3);
   line2->SetLineColor(3);
   line1->SetLineWidth(2);
   line2->SetLineWidth(2);
   line1->Draw("same");
   line2->Draw("same");   
   
   //Gauss1->Draw("same");
   //Gauss2->Draw("same");
   
   TString countResult;
   countResult.Form("%d[%d],%d[%d]",
         TMath::Nint(countS),
         TMath::Nint(TMath::Sqrt(countTot+countBG)),
         TMath::Nint((fit->Integral(countRange[0]-50,countRange[1]+50))/(hist1->GetBinWidth(nBin))),
         TMath::Nint((fit->IntegralError(countRange[0]-50,countRange[1]+50))/(hist1->GetBinWidth(nBin))) );
   TLatex *resultText = new TLatex();
   resultText->SetNDC();
   resultText->DrawLatex(0.15, 0.85, countResult); 
   
   TF1 * k1 = new TF1("k1", "gaus", -15, 15);
   k1->SetParameters(&para[0]);
   k1->SetLineColor(4);
   k1->SetLineWidth(1);
   k1->Draw("same");
   
   TF1 * k2 = new TF1("k2", "gaus", -15, 15);
   k2->SetParameters(&para[3]);
   k2->SetLineColor(7);
   k2->SetLineWidth(1);
   k2->Draw("same");
   
	printf("reduced chi-square: %3.1f/%d = %.3f\n", fit->GetChisquare(), fit->GetNDF(), fit->GetChisquare()/fit->GetNDF());
   
   return hout;


} 
