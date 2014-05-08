#include "constant.h"
#include "RelCalculator.h"
#include "TBeamData.h"

void pidTpla() {
   
   const char* rootfile="Data/phys22_clean.root";
   TBeamData *beam = new TBeamData("23F");
   Bool_t allentry  = 0;
   Int_t firstEntry = 0;
   Int_t nEntries=10000000;
   
//########################################################   
   Double_t Principle_tof = tofByBrho(L_F3FH9,beam->fBrho, beam->fMass, beam->fZ);
   
   gStyle->SetOptStat(0);
   
   TString hPIDDSTitle;
   hPIDDSTitle.Form("PID Tpla-L (%s)", rootfile);
   TH2F* hPIDTplaL = new TH2F("hPIDTplaL",hPIDDSTitle,100, -60, -20, 300 ,500, 2500);
   hPIDTplaL->SetXTitle("tof(tgt-TplaL)");
   hPIDTplaL->SetYTitle("Q");
   hPIDTplaL->SetStats(0);
   TH2F* hPIDTplaR = new TH2F("hPIDTplaR","PID Tpla-R",100, -60, -20, 300 ,500, 2500);
   hPIDTplaR->SetXTitle("tof(tgt-TplaR)");
   hPIDTplaR->SetYTitle("Q");
   hPIDTplaR->SetStats(0);
   
   TCanvas* cPIDDS = new TCanvas("cPIDDS", "PID", 0, 0, 1000, 500);   
   cPIDDS->Divide(2,1);
   
   TClonesArray *hoge_V775;
   TFile *f = new TFile(rootfile,"read");
   TTree *pid = (TTree*)f->Get("tree");
   Int_t totnumEntry = pid->GetEntries();
   pid->SetBranchStatus("*",0);
   pid->SetBranchStatus("plaV775",1);
   
   pid->SetBranchAddress("plaV775",&hoge_V775);
   
   art::TTwoSidedPlasticData *data1;
   
   if (allentry) {
      firstEntry = 0;
      nEntries = totnumEntry;
   }
   
   if ( nEntries + firstEntry > totnumEntry) nEntries = totnumEntry - firstEntry;
   
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;
   
   Double_t QAveV775[5];
   Double_t tAveV775[5];
   
   printf("File:%s ==== TotnumEntry:%d, 1stEntry:%d, nEntries:%d[%4.1f%%]\n",rootfile, totnumEntry, firstEntry, nEntries, nEntries*100./totnumEntry);
   
   for(Int_t eventID = firstEntry; eventID < firstEntry+nEntries; eventID++){
      pid->GetEntry(eventID); 
      
      for(Int_t p = 0; p < 5; p++){
         QAveV775[p] = -1e5;
         tAveV775[p] = -1e5;
      }
      
      //Get Charge from V775 
      Int_t nHit =hoge_V775->GetEntriesFast();
      for(Int_t p = 0; p < nHit; p++){
         data1 = (art::TTwoSidedPlasticData*)hoge_V775->At(p) ;
         Int_t detIDV775   = data1->GetDetID();
         QAveV775[detIDV775]    = data1->GetQAve();
         tAveV775[detIDV775]    = data1->GetTAve();
      }
      if ( tAveV775[3] == -1e5 ) continue;    
         
      Double_t tofF3FH9 = tAveV775[3] - tAveV775[2] - beam->fToffsetV775 + Principle_tof;
      Double_t tof1     = tAveV775[0] - tAveV775[3] - tofF3FH9 * LENGTH_RATIO_FH9_TGT ;
      Double_t tof2     = tAveV775[1] - tAveV775[3] - tofF3FH9 * LENGTH_RATIO_FH9_TGT ;
      
      //if( TMath::Finite(tof1) ) 
      hPIDTplaL->Fill(tof1,QAveV775[0]);
      //if( TMath::Finite(tof2) ) 
      hPIDTplaR->Fill(tof2,QAveV775[1]);

//------------Clock      
      clock.Stop("timer");
      Double_t timer = clock.GetRealTime("timer");
      clock.Start("timer");
      
      if ( !shown ) {
         if (fmod(timer, 10) < 1 ){
            printf( "%10d[%2d%%] |%3d min %5.2f sec | expect:%5.1fmin\n", 
            eventID, 
            TMath::Nint((eventID+1-firstEntry)*100./nEntries),
            TMath::Floor(timer/60), timer - TMath::Floor(timer/60)*60,
            nEntries*timer/(eventID+1-firstEntry)/60.);
            shown = 1;
         }
      }else{
         if (fmod(timer, 10) > 9 ){
            shown = 0;
         }
      }

   }
   
   cPIDDS->cd(1);
   hPIDTplaL->Draw("colz");
   cPIDDS->cd(2);
   hPIDTplaR->Draw("colz");
   
}
