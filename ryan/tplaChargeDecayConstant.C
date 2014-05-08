#include "constant.h"

void tplaChargeDecayConstant() {
   
   const char* rootfile="phys14_45_67.root";
   TString detector = "Tpla-R"; //Tpla-L
   Bool_t allentry  = 0;
   Int_t firstEntry = 0;
   Int_t nEntries=4000000;
   
//#######################################################   
   Int_t detectorID;
   Double_t TdiffRange[2];
   Double_t TplaPMTPos[2];
   Double_t TplaMidPt;
   Double_t Qoffset[2], QGain[2];
   Int_t Sign;
   
   TClonesArray *hoge_V775, *hoge_MWDC;
   TFile *f = new TFile(rootfile,"read");
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("plaV775",1);
   tree->SetBranchAddress("plaV775",&hoge_V775);
   
   if ( detector == "Tpla-L"){
      tree->SetBranchStatus("smwdc_L",1);
      tree->SetBranchAddress("smwdc_L",&hoge_MWDC);
      detectorID = 0;
      TdiffRange[0] = -15;
      TdiffRange[1] = 5;
      TplaPMTPos[0] = 200;
      TplaPMTPos[1] = -1300;
      TplaMidPt = -1000; 
      Qoffset[0] = -544; Qoffset[1] = -522;
      QGain[0]   = 1.15 ; QGain[1] = 1;
      Sign = -1;
   }else{
      tree->SetBranchStatus("smwdc_R",1);
      tree->SetBranchAddress("smwdc_R",&hoge_MWDC);
      detectorID = 1;
      TdiffRange[0] = -9;
      TdiffRange[1] = 11;
      TplaPMTPos[0] = -200;
      TplaPMTPos[1] = 1300;
      TplaMidPt = 500;
      Qoffset[0] = -552; Qoffset[1] = -472;
      QGain[0]   = 2 ; QGain[1] = 0.86;
      Sign = 1;
   }
   
   //Qoffset[0] = 0; Qoffset[1] = 0;
   //QGain[0]   = 1 ; QGain[1] = 1;
   
   TH1F * hDecay = new TH1F("hDecay", "Charge Decay Constant", 200,0, 4000);
   TH1F * hQ1    = new TH1F("hQ1", "Charge 1=B", 200, 0, 8000);
   TH1F * hQ2    = new TH1F("hQ2", "Charge 2=F", 200, 0, 8000);
   hQ1->SetLineColor(4);
   hQ2->SetLineColor(2);
   TH2F * hQTplaX = new TH2F("hQTplaX","Q0 vs TplaX", 400, TplaPMTPos[0], TplaPMTPos[1], 200, 0., 2.5);
   TH2F * htdiffTplaX = new TH2F("htdiffTplaX", "tdiff vs TplaX", 400, TplaPMTPos[0], TplaPMTPos[1], 200, TdiffRange[0], TdiffRange[1]);

   TCanvas* cTplaDecay = new TCanvas("cTplaDecay", "Tpla Decay constant", 0, 200, 800, 400);   
   cTplaDecay->Divide(2,2);
   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   
//##########################################################################   
   for( Int_t eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID); 
      
      // Get Time and charge
      Double_t Q1 = kInvalidD, Q2 = kInvalidD;
      Double_t t1 = kInvalidD, t2 = kInvalidD;
      Int_t nHitV775 = hoge_V775->GetEntriesFast();
      for ( Int_t p = 0; p < nHitV775; p++){
         art::TTwoSidedPlasticData * V775Data = (art::TTwoSidedPlasticData*)hoge_V775->At(p);
         if ( V775Data->GetDetID() == detectorID){
            t1   = V775Data->GetT1();
            t2   = V775Data->GetT2();
            Q1   = (V775Data->GetQ1()+Qoffset[0])*QGain[0];
            Q2   = (V775Data->GetQ2()+Qoffset[1])*QGain[1];         
         }
      }
      if ( TMath::IsNaN(t1) || TMath::IsNaN(t2)) continue;
      if ( TMath::IsNaN(Q1) || TMath::IsNaN(Q2)) continue;
      if ( Q2 > 6000 || Q1 > 6000) continue;
      
      // Get MWDC X and A then project to Tpla
      Double_t TplaX = kInvalidD;
      Int_t nHitSMWDC = hoge_MWDC->GetEntriesFast();
      for( Int_t p = 0; p < nHitSMWDC; p++){
         art::TMWDCTrackingResult * smwdc = (art::TMWDCTrackingResult*)hoge_MWDC->At(p);
         art::TTrack * track = (art::TTrack*)smwdc->GetTrack();
         Double_t x = track->GetX();
         Double_t a = track->GetA();
         if ( TMath::Abs(a - x/z0)> 0.1 ) continue;
         TplaX = x + (z0Tpla-z0)*a;
      }
      
  
      if ( TMath::IsNaN(TplaX)) continue;
       
      hDecay->Fill(Sign*(TplaPMTPos[0]+TplaPMTPos[1]-2*TplaX)/TMath::Log(Q1/Q2));
      hQ1->Fill(Q1);
      hQ2->Fill(Q2);
      Double_t Q0 = TMath::Sqrt(Q1*Q2)*1.445;
      hQTplaX->Fill(TplaX,Q1/Q2);
      htdiffTplaX->Fill(TplaX, t1-t2);
      //if ( Q1/Q2> 2.4 ) printf("Q1:%7.2f, Q2:%7.2f, Q0:%7.2f, X%7.2f\n",Q1,Q2,Q0, TplaX);
      //printf("%d|Q1:%7.2f, Q2:%7.2f, TplaX:%7.2f, a:%f\n",eventID, Q1, Q2, TplaX, (TplaPMTPos[0]+TplaPMTPos[1]-2*TplaX)/TMath::Log(Q1-500/Q2-500));
      

   }
   
     
   cTplaDecay->cd(1);
   //hDecay->Draw("");
   hQTplaX->Draw("colz");
   cTplaDecay->cd(2);
   hQ1->Draw();
   hQ2->Draw("same");
   
   TLatex text;
   text.SetNDC();
   text.SetTextSize(0.04);
   TString textStr;
   
   text.SetTextColor(4);
   textStr.Form("Q1 offset:%7.2f, gain:%5.2f",Qoffset[0],QGain[0]);
   text.DrawText(0.3, 0.8, textStr);
   
   text.SetTextColor(2);
   textStr.Form("Q2 offset:%7.2f, gain:%5.2f",Qoffset[1],QGain[1]);
   text.DrawText(0.3, 0.7, textStr);
   cTplaDecay->cd(3);
   htdiffTplaX->Draw("colz");
  
   return ;
}
