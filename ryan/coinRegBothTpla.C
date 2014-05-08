#include "constant.h"
#include "RelCalculator.h"
#include "TBeamData.h"

void coinRegBothTpla() {
   
//############################################################################   
   const char* rootfile="Data/phys22_clean.root";
   TBeamData *beam = new TBeamData("23F");
   Bool_t PIDUSGate   = 0;
   Bool_t allentry  = 1;
   Int_t firstEntry = 3000000;
   Int_t nEntries=1000000;
   
   beam->Print();
   
//############################################################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;
   
   TString hCheckTitle;
   hCheckTitle = rootfile;
   if (PIDUSGate) hCheckTitle += ", PIDUS="+beam->fName;
   TH1F* hCheck = new TH1F("check", hCheckTitle, 9, 1, 10);
   
   TCanvas * cCheck = new TCanvas("check", "check", 100, 100, 600, 400);

//############################################################################
   art::TCoinRegData *hoge_coinReg;
   art::TEventHeader *hoge_run;
   TClonesArray *hoge_V775, *hoge_L, *hoge_R;
   TClonesArray *hoge_FH9, *hoge_tof;
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded. \n",rootfile);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("eventheader",1);
   tree->SetBranchStatus("coinReg",1);
   tree->SetBranchStatus("plaV1190_FH9",1);
   tree->SetBranchStatus("tof_US",1);
   tree->SetBranchStatus("plaV775",1);   
   tree->SetBranchStatus("smwdc_L",1);
   tree->SetBranchStatus("smwdc_R",1);

   tree->SetBranchAddress("eventheader",&hoge_run);
   tree->SetBranchAddress("coinReg",&hoge_coinReg);
   tree->SetBranchAddress("plaV1190_FH9",&hoge_FH9);
   tree->SetBranchAddress("tof_US",&hoge_tof);
   tree->SetBranchAddress("plaV775",&hoge_V775);
   tree->SetBranchAddress("smwdc_L",&hoge_L);
   tree->SetBranchAddress("smwdc_R",&hoge_R);

//############################################################################   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   if (PIDUSGate) printf(" ... PIDUS Gate.\n");
   
   art::TTwoSidedPlasticData * V775Data;
   art::TMWDCTrackingResult * xy1,* xy2;
   
   Int_t hitIDFH9[50], hitID[50];
   Double_t QAveFH9[50], tof[50];
   
//##############################################################################
   for( Int_t eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID);
      
//---------------- PID US
      for( Int_t p = 0; p <50; p++){
         hitIDFH9[p] = -1;
         hitID[p]    = -2;
         QAveFH9[p]  = TMath::QuietNaN();
         tof[p]      = TMath::QuietNaN();
      }
      //Get Charge from FH9  
      Int_t nHit1 =hoge_FH9->GetEntriesFast();
      for(Int_t p = 0; p < nHit1; p++){
         data1 = (art::TTwoSidedPlasticData*)hoge_FH9->At(p) ;
         hitIDFH9[p]   = data1->GetHitID();
         QAveFH9[p]    = data1->GetCharge();
      }
      
      //Get tof
      Int_t nHit2 =hoge_tof->GetEntriesFast();
      for(Int_t p = 0; p < nHit2; p++){
         data2 = (art::TTimeDifference*)hoge_tof->At(p) ;
         hitID[p]       = data2->GetHitID();
         tof[p]         = data2->GetTiming();
      }

      Bool_t PIDcheck = 0;
      for (Int_t p = 0; p < nHit1; p++){
         for (Int_t q = 0; q< nHit2; q++){
            if (hitIDFH9[p] == hitID[q]){
               if ( PIDUSGate && (tof[q] < beam->fTofGate[0] || tof[q] > beam->fTofGate[1])) continue; //PID gate
               if ( PIDUSGate && (QAveFH9[p] < beam->fQGate[0] || QAveFH9[p] > beam->fQGate[1])) continue; // PID gate
               PIDcheck = 1;
            }
         }
      }
      if ( PIDUSGate && PIDcheck == 0 ) continue;
      
      // initialization
      Int_t check = 0 ; // 1 = only ppcoin, 2 = only Both Tpla, 4 = only Both MWDC tracked
      
//----------------Get Event Number
      Int_t runNum = hoge_run->GetRunNumber();
      
//--------------Get coinReg
      // 0 = F3, 1 = FH9, 2=ppcoin, 3 = ND coin, 4 = ppsingle, 5 = ND single, 6 = ND cosmic
      if ( hoge_coinReg->Test(2) == 1 ) check = check + 1;
      
//---------------Get charge DS of Tpla and S0D
      Int_t TplaHit_check = 0;
      Int_t nHit = hoge_V775->GetEntriesFast();
      for ( Int_t p = 0; p < nHit; p++){
         V775Data = (art::TTwoSidedPlasticData*)hoge_V775->At(p);
         Int_t DetID     = V775Data->GetDetID();
         if ( DetID > 1) continue;
         if ( TMath::IsNaN(V775Data->GetTiming()) ) continue;
         //if ( V775Data->GetQAve() < 800 ) continue;
         //printf("%d(%6.1f, %6.1f) \n", DetID, V775Data->GetTiming(), V775Data->GetQAve());
         TplaHit_check++;
      }
      if ( TplaHit_check == 2 ) check = check + 2;
      
//---------Get SMWDC image, should be one 1 instance
      Int_t MWDCTracked_check = 0;
      nHit = hoge_L->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         xy1 = (art::TMWDCTrackingResult*)hoge_L->At(p);
         if (xy1 -> GetTrackingID() == 1) MWDCTracked_check ++;
      }
      nHit = hoge_R->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         xy2 = (art::TMWDCTrackingResult*)hoge_R->At(p);
         if (xy2 -> GetTrackingID() == 1) MWDCTracked_check ++;
      }
      
      if ( MWDCTracked_check == 2) check = check + 4;
      hCheck->Fill(check);     
      
//------------Clock      
      clock.Stop("timer");
      Double_t time = clock.GetRealTime("timer");
      clock.Start("timer");
      
      if ( !shown ) {
         if (fmod(time, 10) < 1 ){
            printf( "%10d[%2d%%](#%2d) |%3d min %5.2f sec | expect:%5.1fmin\n", 
            eventID, 
            TMath::Nint((eventID+1-firstEntry)*100./nEntries),
            runNum,
            TMath::Floor(time/60), time - TMath::Floor(time/60)*60,
            nEntries*time/(eventID+1-firstEntry)/60.);
            shown = 1;
         }
      }else{
         if (fmod(time, 10) > 9 ){
            shown = 0;
         }
      }
      
   }
  
   hCheck->Draw();
   TLatex text;
   text.SetTextColor(1);
   text.SetTextAngle(90);
   text.SetTextSize(0.04);
   text.DrawText(1.5, 0.5, "PPCoin");
   text.DrawText(2.5, 0.5, "BothTpla");
   text.DrawText(3.5, 0.5, "PPCoin + BothTpla");
   text.DrawText(4.5, 0.5, "BothMWDCTracked");
   text.DrawText(5.5, 0.5, "PPcoin + BothMWDCTracked");
   text.DrawText(6.5, 0.5, "BothTpla + BothMWDCTracked");
   text.DrawText(7.5, 0.5, "PPcoin + BothTpla + BothMWDCTracked");

   clock.Stop("timer");
   printf("============ finished|%10.3f sec \n",clock.GetRealTime("timer"));
   
   return ;
}
