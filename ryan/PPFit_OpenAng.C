#include "RelCalculator.h"
Double_t TKA = 260;
void PPFit_OpenAng(Int_t angle1 = 0, Int_t angle2 = 180, Int_t LR = 1, Int_t OPCM = 1){

   TFile *f0 = new TFile ("test.root");
   TTree *recoil = (TTree*)f0->Get("recoil");
   
   TCanvas * cThetaOp = new TCanvas ("cThetaOp","cThetaOp", 1200,50,800,800);
   cThetaOp->Divide(2,2);
   
   //================= Calculate angle range
   if (OPCM ==1 ){
      Int_t    cmThetaRange[2] = {angle1, angle2};
      Double_t thetaOpRange[2] ={CMtoLabTheta(TKA,cmThetaRange[0]), CMtoLabTheta(TKA,cmThetaRange[1])};
      printf(" using CM Frame Theta (%4.1f,%4.1f) = Lab(%5.2f, %5.2f)\n",cmThetaRange[0],cmThetaRange[1], thetaOpRange[0], thetaOpRange[1]);
   }else{
      Int_t    cmThetaRange[2] = {angle1, angle2};
      Double_t thetaOpRange[2] = {cmThetaRange[0], cmThetaRange[1]};
      printf(" using Lab Frame Theta (%4.1f,%4.1f)\n",thetaOpRange[0], thetaOpRange[1]);
   }
   
   Int_t beamZGate[2] = {-8, 40};
   Int_t sideGateExtL = 100;
   Int_t sideGateExtR = 10;   
   //================== Setting histogram
   Double_t beamZGate_width = beamZGate[1] - beamZGate[0];
   TString h1Title, h2Title;
   h1Title.Form("%d < beamZGate < %d", beamZGate[0], beamZGate[1]);
   h2Title.Form("beamZGate = (%4.1f, %4.1f) or (%4.1f, %4.1f)", beamZGate[0]-beamZGate_width/2, beamZGate[1]+beamZGate_width/2);
   
   Double_t DisplayRangeh1[2] = {76, 96};
   Int_t nBinh1 = (DisplayRangeh1[1]-DisplayRangeh1[0])*4;
   TH1F * h1 = new TH1F("h1",h1Title, nBinh1, DisplayRangeh1[0], DisplayRangeh1[1]);
   h1->SetMinimum(0);
   h1->SetXTitle("theta1+theta2");
   TH1F * h2 = new TH1F("h2",h2Title, nBinh1, DisplayRangeh1[0], DisplayRangeh1[1]);
   h2->SetMinimum(0);
   h2->SetLineColor(2);
   TH1F * h3 = new TH1F("h3","h1-h2", nBinh1, DisplayRangeh1[0], DisplayRangeh1[1]);
   
   Double_t DisplayRangeG[2] = {-100, 100};
   Int_t nBinG = (DisplayRangeG[1]-DisplayRangeG[0]);
   TH1F * h1g = new TH1F("h1g","gate", nBinG, DisplayRangeG[0], DisplayRangeG[1]);
   h1g->SetXTitle("weighted beamZGate");
   TH1F * h2g = new TH1F("h2g","gate2", nBinG, DisplayRangeG[0], DisplayRangeG[1]);
   h2g->SetLineColor(2);
   
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
   
   
   //=============== Gate Setting
   TString thetaOpGateTitle;
   if ( LR == 1) {
      thetaOpGateTitle.Form("theta1*TMath::RadToDeg() > %5.2f && theta1*TMath::RadToDeg() < %5.2f", thetaOpRange[0], thetaOpRange[1]);
   }else{
      thetaOpGateTitle.Form("theta2*TMath::RadToDeg() > %5.2f && theta2*TMath::RadToDeg() < %5.2f", thetaOpRange[0], thetaOpRange[1]);
   }
   TCut thetaOpGate;
   thetaOpGate += thetaOpGateTitle;
   
   TString centralGateTitle, sideGateTitle;
   centralGateTitle.Form("TMath::Abs(wbeamZ-%4.1f)<%4.1f", beamZGate[0]+beamZGate_width/2, beamZGate_width/2);
   sideGateTitle.Form("TMath::Abs(wbeamZ-%4.1f)<%4.2f || TMath::Abs(wbeamZ-%4.1f)<%4.2f",
              beamZGate[0]-beamZGate_width/4-sideGateExtL, beamZGate_width/4+sideGateExtL, 
              beamZGate[1]+beamZGate_width/4+sideGateExtR, beamZGate_width/4+sideGateExtR);
   TCut CentralGate, SideGate;
   CentralGate += centralGateTitle;
   SideGate += sideGateTitle;
   
   CentralGate.Print();
   SideGate.Print();
   thetaOpGate.Print();
   
   //=================== Draw and Result
   cThetaOp->cd(1);
   recoil->Draw("(theta1+theta2)*TMath::RadToDeg()>>h1",CentralGate && thetaOpGate);
   recoil->Draw("(theta1+theta2)*TMath::RadToDeg()>>h2",SideGate && thetaOpGate, "same");
    
   cThetaOp->cd(3);
   recoil->Draw("wbeamZ>>h1g",CentralGate && thetaOpGate);
   recoil->Draw("wbeamZ>>h2g",SideGate && thetaOpGate, "same");
   
   cThetaOp->cd(2);
   h3 = HistSubThetaOP(h1, h2);
   
   cThetaOp->cd(4);
   if (LR == 1){
      recoil->Draw("theta1*TMath::RadToDeg()>>hL", thetaOpGate );
      recoil->Draw("theta2*TMath::RadToDeg()>>hR", thetaOpGate , "same");
   }else{
      recoil->Draw("theta2*TMath::RadToDeg()>>hR", thetaOpGate );
      recoil->Draw("theta1*TMath::RadToDeg()>>hL", thetaOpGate , "same");
   }
}

TH1F* HistSubThetaOP(TH1F *hist1, TH1F *hist2){
   Int_t nBin = hist1-> GetNbinsX();
   Double_t Xmin = hist1->GetBinLowEdge(1);
   Double_t Xmax = hist1->GetBinLowEdge(nBin)+hist1->GetBinWidth(nBin);
   if ( nBin != hist2->GetNbinsX()) return 0;
   Double_t xx;
   Double_t countS = 0, countTot = 0, countBG = 0;
   Double_t countRange[2] = {84.2, 87.5};
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
   printf("Count(%4.1f, %4.1f): %5d [%6.1f] |%d, %d \n",countRange[0], countRange[1], countS, TMath::Sqrt(countTot+countBG), countTot, countBG);

   TLine *line1 = new TLine(countRange[0], hout->GetMinimum(), countRange[0], hout->GetMaximum());
   TLine *line2 = new TLine(countRange[1], hout->GetMinimum(), countRange[1], hout->GetMaximum());
   line1->SetLineColor(3);
   line2->SetLineColor(3);
   line1->SetLineWidth(2);
   line2->SetLineWidth(2);
   line1->Draw("same");
   line2->Draw("same");   
   
   TString countResult;
   countResult.Form("%d[%d]/%d[%d]",
         TMath::Nint(countS),
         TMath::Nint(TMath::Sqrt(countTot+countBG)),
         TMath::Nint((fit->Integral(countRange[0],countRange[1]))/(hist1->GetBinWidth(nBin))),
         TMath::Nint((fit->IntegralError(countRange[0],countRange[1]))/(hist1->GetBinWidth(nBin))) );
   TLatex *resultText = new TLatex();
   resultText->SetNDC();
   resultText->DrawLatex(0.15, 0.85, countResult); 
   
   return hout;


} 
