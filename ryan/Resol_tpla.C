#include "constant.h"

void tplaResol() {
   
   const char* rootfile="PrimaryData/phys14Down.root";
   TString detector = "Tpla-L"; //Tpla-L
   Double_t TplaBeta = 0.55;
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=4000000;
   Int_t nBin = 400;
   Double_t slideBin[2] = {nBin/2-1,nBin/2+1};
   
   Int_t detectorID;
   Double_t Xrange[2];
   Double_t Yrange[2];

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
      Xrange[0] = -15;
      Xrange[1] = 5;
      Yrange[0] = -1300;
      Yrange[1] = 200;
   }else{
      tree->SetBranchStatus("smwdc_R",1);
      tree->SetBranchAddress("smwdc_R",&hoge_MWDC);
      detectorID = 1;
      Xrange[0] = -9;
      Xrange[1] = 11;
      Yrange[0] = -200;
      Yrange[1] = 1300;
   }
   
   TString hTdiffTitle;
   hTdiffTitle.Form("%s | tdiff vs Tpla(X by mwdc)",detector.Data());  
   TH2F* hTdiff = new TH2F("hTdiff",hTdiffTitle,200, Xrange[0], Xrange[1], nBin , Yrange[0], Yrange[1]);
   hTdiff->SetXTitle("Tdiff[ns]");
   hTdiff->SetYTitle("Tpla(X)");

   TCanvas* cTplaResol = new TCanvas("cTplaResol", "Tpla resolution by SMWDC", 0, 0, 800, 600);   
   cTplaResol->Divide(1,2);
   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   
   
   for( Int_t eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID); 
      
      // Get Tdiff
      Double_t tdiff = kInvalidD;
      Int_t nHitV775 = hoge_V775->GetEntriesFast();
      for ( Int_t p = 0; p < nHitV775; p++){
         art::TTwoSidedPlasticData * V775Data = (art::TTwoSidedPlasticData*)hoge_V775->At(p);
         if ( V775Data->GetDetID() == detectorID){
            tdiff= V775Data->GetTDiff();
         }
      }
      
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
      
      //printf(" %d | nHitV775:%d, tdiff:%10.5f | nHitSMWDC:%d, TplaX:%10.3f \n", eventID, nHitV775, tdiff, nHitSMWDC, TplaX);
      
      
      if (TMath::Finite(tdiff) && TMath::Finite(TplaX)){
         hTdiff->Fill(tdiff, TplaX);
      }

   }
   
   cTplaResol->cd(1);
   hTdiff->Draw("colz");
   cTplaResol->cd(2);
   hTdiff->ProjectionX("test",slideBin[0],slideBin[1]);
   Double_t TplaXWidth = (slideBin[1]-slideBin[0]+1)*(Yrange[1]-Yrange[0])/nBin;
   TString testTitle;
   testTitle.Form("ProjectX, TplaX = (%10.3f,%10.3f|%10.3f)",
                  Yrange[0]+(slideBin[0]-1)*(Yrange[1]-Yrange[0])/nBin,
                  Yrange[0]+(slideBin[1])*(Yrange[1]-Yrange[0])/nBin,
                  TplaXWidth);
   test->SetTitle(testTitle);
   TF1 *fit = new TF1("fit", "gaus(0)", Xrange[0], Xrange[1]); 
   fit->SetParameters(500, (Xrange[0]+Xrange[1])/2 , 0.5);
   test->Fit("fit");
   Double_t para[3];
   fit->GetParameters(para);
   hTdiff->ProjectionX("test2",nBin/4-1,nBin/4+1);
   test2->Fit("gaus");
   hTdiff->ProjectionX("test3",nBin*3/4-1,nBin*3/4+1);
   test3->Fit("gaus");
   test->Draw();
   test2->Draw("same");
   test3->Draw("same");
   
   TLatex text;
   text.SetNDC();
   text.SetTextColor(1);
   TString textStr;
   textStr.Form("Tpla Beta:%4.2f",TplaBeta);
   text.DrawText(0.3, 0.7, textStr);
   textStr.Form("Tavg Resol:%6.1f ps",TMath::Sqrt(TMath::Power(para[2],2)-TMath::Power(2*TplaXWidth/TplaBeta/cVaccum,2))*1000.);
   text.DrawText(0.3, 0.65, textStr);

   return ;
}
