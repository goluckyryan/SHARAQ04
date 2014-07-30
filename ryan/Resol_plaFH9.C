#include "constant.h"

void Resol_plaFH9() {

   // there is only 3 planes for DC91. A and B is assumed to be 0
   
   const char* rootfile="PrimaryData/ppOptics.root";
   //const char* FH9_branch="plaV775"; Int_t plaID = 3;
   const char* FH9_branch="plaV1190_FH9"; Int_t plaID = 0; 
   Double_t plaBeta = 0.66;
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=4000000;
   Int_t nBin = 400;
   Double_t slideBin[2] = {nBin/2-1,nBin/2+1};
   
   Double_t tDiffRange[2] = {-4,6};
   Double_t FH9XRange[2] = {-60, 80};
   Double_t distance = 100;//mm

   //#############################################################
   TClonesArray *hoge_pla, *hoge_MWDC;
   TFile *f = new TFile(rootfile,"read");
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus(FH9_branch,1);
   tree->SetBranchAddress(FH9_branch,&hoge_pla);
   
   tree->SetBranchStatus("dc91",1);
   tree->SetBranchAddress("dc91",&hoge_MWDC);
   
   //*************************************************************
   gStyle->SetOptStat(0);
   TH2F* hTdiff = new TH2F("hTdiff","tdiff vs FH9(X by DC91)",200, tDiffRange[0], tDiffRange[1], nBin , FH9XRange[0], FH9XRange[1]);
   hTdiff->SetXTitle("Tdiff[ns]");
   hTdiff->SetYTitle("X [mm]");

   TCanvas* cFH9Resol = new TCanvas("cFH9Resol", "FH9 resolution by SMWDC", 0, 0, 800, 600);   
   cFH9Resol->Divide(1,2);
   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   
   //*************************************************************
   for( Int_t eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID); 
      
      // Get Tdiff
      Double_t tdiff = kInvalidD;
      Int_t nHitpla = hoge_pla->GetEntriesFast();
      for ( Int_t p = 0; p < nHitpla; p++){
         art::TTwoSidedPlasticData * plaData = (art::TTwoSidedPlasticData*)hoge_pla->At(p);
         if ( plaData->GetDetID() == plaID){
            tdiff= plaData->GetTDiff();
         }
      }
      
      // Get MWDC X and A then project to Tpla
      Double_t FH9X = kInvalidD;
      Int_t nHitSMWDC = hoge_MWDC->GetEntriesFast();
      for( Int_t p = 0; p < nHitSMWDC; p++){
         art::TMWDCTrackingResult * smwdc = (art::TMWDCTrackingResult*)hoge_MWDC->At(p);
         art::TTrack * track = (art::TTrack*)smwdc->GetTrack();
         Double_t x = track->GetX();
         //Double_t a = track->GetA();
         FH9X = x ;
      }
      
      //printf(" %d | nHitpla:%d, tdiff:%10.5f | nHitSMWDC:%d, FH9X:%10.3f \n", eventID, nHitpla, tdiff, nHitSMWDC, FH9X);      
      if (TMath::Finite(tdiff) && TMath::Finite(FH9X)){
         hTdiff->Fill(tdiff, FH9X);
      }

   }
   
   //#############################################################
   cFH9Resol->cd(1);
   hTdiff->Draw("colz");
   cFH9Resol->cd(2);
   hTdiff->ProjectionX("test",slideBin[0],slideBin[1]);
   Double_t TplaXWidth = (slideBin[1]-slideBin[0]+1)*(FH9XRange[1]-FH9XRange[0])/nBin;
   TString testTitle;
   testTitle.Form("ProjectX, FH9_X = (%10.3f mm,%10.3f mm| width:%10.3f mm)",
                  FH9XRange[0]+(slideBin[0]-1)*(FH9XRange[1]-FH9XRange[0])/nBin,
                  FH9XRange[0]+(slideBin[1])*(FH9XRange[1]-FH9XRange[0])/nBin,
                  TplaXWidth);
   test->SetTitle(testTitle);
   TF1 *fit = new TF1("fit", "gaus(0)", tDiffRange[0], tDiffRange[1]); 
   fit->SetParameters(500, (tDiffRange[0]+tDiffRange[1])/2 , 0.5);
   test->Fit("fit");
   Double_t para[3];
   fit->GetParameters(para);
   test->Draw();
   
   /*
   hTdiff->ProjectionX("test2",nBin/4-1,nBin/4+1);
   test2->Fit("gaus");
   test2->Draw("same");
   
   hTdiff->ProjectionX("test3",nBin*3/4-1,nBin*3/4+1);
   test3->Fit("gaus");
   test3->Draw("same");
   */
   
   TLatex text;
   text.SetNDC();
   text.SetTextColor(1);
   TString textStr;
   textStr.Form("Tpla Beta:%4.2f",plaBeta);
   text.DrawText(0.2, 0.7, textStr);
   textStr.Form("Tavg Resol:%6.1f ps",TMath::Sqrt(TMath::Power(para[2],2)-TMath::Power(2*TplaXWidth/plaBeta/cVaccum,2))*1000.);
   text.DrawText(0.2, 0.65, textStr);

   return ;
}
