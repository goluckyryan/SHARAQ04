#include "RelCalculator.h"
Double_t TKA = 260;

void PPFit_BeamZ_direct(Int_t angle1 = 40, Int_t angle2 = 60, Int_t LR = 1, Int_t OPCM = 1){

   TFile *f0 = new TFile ("ppDown_0723.root");
   TTree *tree = (TTree*)f0->Get("tree");
   
   Double_t OpenAngGateRange[2] = {84, 89};
   Double_t sideGateExtL = 0;
   Double_t sideGateExtR = 0;
   
   //================ calculate theta 
   if (OPCM ==1 ){
      Int_t    cmThetaRange[2] = {angle1, angle2};
      Double_t thetaOpRange[2] ={CMtoLabTheta(TKA,cmThetaRange[0]), CMtoLabTheta(TKA,cmThetaRange[1])};
      //Int_t    cmThetaRange2[2] = {180 - angle2, 180 - angle1};
      //Double_t thetaOpRange2[2] ={CMtoLabTheta(TKA,cmThetaRange2[0]), CMtoLabTheta(TKA,cmThetaRange2[1])};
      printf(" using CM Frame Theta1 (%4.1f,%4.1f) = Lab1(%5.2f, %5.2f)\n",cmThetaRange[0],cmThetaRange[1], thetaOpRange[0], thetaOpRange[1]);
      //printf(" using CM Frame Theta2 (%4.1f,%4.1f) = Lab2(%5.2f, %5.2f)\n",cmThetaRange2[0],cmThetaRange2[1], thetaOpRange2[0], thetaOpRange2[1]);
   }else{
      Int_t    cmThetaRange[2] = {angle1, angle2};
      Double_t thetaOpRange[2] = {cmThetaRange[0], cmThetaRange[1]};
      printf(" using Lab Frame Theta (%4.1f,%4.1f)\n",thetaOpRange[0], thetaOpRange[1]);
   }
   //===================Setting histogram
   gStyle->SetOptStat(0);
   TCanvas * cBeamZ = new TCanvas ("cBeamZ","cBeamZ", 1200,50,800,800);
   cBeamZ->Divide(2,2);
   Double_t OpenAngGateRange_width = OpenAngGateRange[1] - OpenAngGateRange[0];
   TString h1Title, h2Title;
   h1Title.Form("%4.1f < OpenAngGateRange < %4.1f", OpenAngGateRange[0], OpenAngGateRange[1]);
   h2Title.Form("OpenAngGateRange = (%4.1f, %4.1f) or (%4.1f, %4.1f)", OpenAngGateRange[0]-OpenAngGateRange_width/2, OpenAngGateRange[1]+OpenAngGateRange_width/2);
   
   Double_t DisplayRangeH[2] = {-100,200};
   Int_t nBinH = TMath::Nint((DisplayRangeH[1]-DisplayRangeH[0])/3.);
   TH1F * h1 = new TH1F("h1",h1Title, nBinH, DisplayRangeH[0], DisplayRangeH[1]);
   h1->SetMinimum(0);
   h1->SetXTitle("weigthed beamZ");
   h1->SetStats(1);
   TH1F * h2 = new TH1F("h2",h2Title, nBinH, DisplayRangeH[0], DisplayRangeH[1]);
   h2->SetMinimum(0);
   h2->SetLineColor(2);
   h2->SetStats(0);
   TH1F * h3 = new TH1F("h3","h1-h2", nBinH, DisplayRangeH[0], DisplayRangeH[1]);
   
   Double_t DisplayRangeG[2] = {80,96};
   Int_t nBinG = (DisplayRangeG[1]-DisplayRangeG[0])*8;
   TH1F * h1g = new TH1F("h1g","gate", nBinG, DisplayRangeG[0], DisplayRangeG[1]);
   h1g->SetXTitle("theta1+theta2");
   h1g->SetStats(0);
   TH1F * h2g = new TH1F("h2g","gate2", nBinG, DisplayRangeG[0], DisplayRangeG[1]);
   h2g->SetLineColor(2);
   h2g->SetStats(1);
   
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
   
   
   //=============Set Gate
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
   //TCut thetaGate2;
   //thetaGate2 += thetaGateTitle2;
   
   TString centralGateTitle, sideGateTitle;
   centralGateTitle.Form("TMath::Abs((p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()-%5.2f)<%5.2f", OpenAngGateRange[0]+OpenAngGateRange_width/2, OpenAngGateRange_width/2);
   sideGateTitle.Form("TMath::Abs((p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()-%5.2f)<%5.2f || TMath::Abs((p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()-%5.2f)<%5.2f",
              OpenAngGateRange[0]-OpenAngGateRange_width/4 - sideGateExtL, OpenAngGateRange_width/4 + sideGateExtL, 
              OpenAngGateRange[1]+OpenAngGateRange_width/4 + sideGateExtR, OpenAngGateRange_width/4 + sideGateExtR);
   TCut CentralGate, SideGate;
   CentralGate += centralGateTitle;
   SideGate += sideGateTitle;
   
   CentralGate.Print();
   SideGate.Print();
   thetaGate.Print();
   
   
   //==============Calculate
   cBeamZ->cd(1);
   tree->Draw("beamZ.fAverage>>h1",CentralGate && thetaGate );
   tree->Draw("beamZ.fAverage>>h2",SideGate && thetaGate  , "same");
   
   /*cBeamZ->cd(3);
   tree->Draw("E2:E1>>hTAngL", CentralGate && thetaGate && thetaGate2 , "colz");
   
   cBeamZ->cd(6);
   tree->Draw("E2:theta2*TMath::RadToDeg()>>hTAngR", CentralGate && thetaGate && thetaGate2 , "colz");
   */ 
   cBeamZ->cd(3);
   tree->Draw("(p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()>>h1g",CentralGate && thetaGate );
   tree->Draw("(p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()>>h2g",SideGate && thetaGate , "same");
   
   Int_t CountTotal=h1g->GetEntries();
   Int_t CountBG = h2g->GetEntries();
   
   Int_t CountSignal = CountTotal - CountBG;
   Double_t ErrorSignal = sqrt((Double_t)CountTotal + (Double_t)CountBG);
   TString countText;
   TLatex *text = new TLatex();
   text->SetNDC();
   countText.Form("%5s%5d","Tot:", CountTotal);
   text->DrawLatex(0.6, 0.85, countText);
   countText.Form("%5s%5d", "BG:",CountBG);
   text->DrawLatex(0.6, 0.8, countText);
   countText.Form("%5s%5d[%3d]","Sig:", CountSignal, TMath::Nint(ErrorSignal));
   text->DrawLatex(0.6, 0.75, countText);
   
   printf("====== Central:%d, Side:%d => Signal:%d [%5.1f] \n",  CountTotal, CountBG, CountSignal, ErrorSignal);
   
   cBeamZ->cd(2);
   h3 = HistSub(h1, h2);
   
   cBeamZ->cd(4);
   if (LR == 1){
      tree->Draw("p2p.fRecoilL.Theta()*TMath::RadToDeg()>>hL", CentralGate && thetaGate );
      tree->Draw("p2p.fRecoilR.Theta()*TMath::RadToDeg()>>hR", CentralGate && thetaGate , "same");
   }else{
      tree->Draw("p2p.fRecoilR.Theta()*TMath::RadToDeg()>>hR", CentralGate && thetaGate );
      tree->Draw("p2p.fRecoilL.Theta()*TMath::RadToDeg()>>hL", CentralGate && thetaGate , "same");
   }
   
   //================== Save as png
   /*TImage *img = TImage::Create();
   
   img->FromPad(cBeamZ);
   
   TString imgName;
   if (LR == 1){
   	imgName.Form("L_");
	}else{
		imgName.Form("");
	}
   img->WriteImage();
   
   delete img;
   
   */
   //delete cBeamZ;
   
}

//#####################################################################
TH1F* HistSub(TH1F *hist1, TH1F *hist2){
   Int_t nBin = hist1-> GetNbinsX();
   Double_t Xmin = hist1->GetBinLowEdge(1);
   Double_t Xmax = hist1->GetBinLowEdge(nBin)+hist1->GetBinWidth(nBin);
   if ( nBin != hist2->GetNbinsX()) return 0;
   Double_t xx;
   Double_t countS = 0, countTot = 0, countBG = 0;
   // Count Range
   Double_t countRangeSet[2] = {11, 18};//center, width
   Double_t countRange[2] = {countRangeSet[0]-countRangeSet[1]*2, countRangeSet[0]+countRangeSet[1]*2};
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
   
   TF1 * fit = new TF1("fit","gaus", Xmin, Xmax);
   hout->Fit(fit);
   
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
   
   TString countResult;
   countResult.Form("%d[%d],%d[%d]",
         TMath::Nint(countS),
         TMath::Nint(TMath::Sqrt(countTot+countBG)),
         TMath::Nint((fit->Integral(countRange[0]-50,countRange[1]+50))/(hist1->GetBinWidth(nBin))),
         TMath::Nint((fit->IntegralError(countRange[0]-50,countRange[1]+50))/(hist1->GetBinWidth(nBin))) );
   TLatex *resultText = new TLatex();
   resultText->SetNDC();
   resultText->DrawLatex(0.15, 0.85, countResult); 
   
   return hout;


} 
