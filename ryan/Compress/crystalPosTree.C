#include <TBenchmark.h>
#include <TFile.h>
#include <TMath.h>
#include <math.h>
#include <TTree.h>
#include <TList.h>
#include <TClonesArray.h>
#include "constant.h"
#include "TBeamData.h"
#include "RelCalculator.h"

void crystalPosTree() {
   
//############################################################################   
   const char* rootfile="Data/phys24Up.root";
   TBeamData *beam = new TBeamData("25F");
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=1000000;
   
   beam->Print();
   Double_t Principle_tof = tofByBrho(L_F3FH9,beam->fBrho, beam->fMass, beam->fZ);
//############################################################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;
   
   Int_t runNum;
   Int_t eventID;
   Int_t coinReg;
   Double_t tofUS, QUS;
   Double_t tofS0D, QS0D;
   Double_t s0x, s0y;
  
   TFile *savefile = new TFile("CrystalPos.root","recreate");
   TTree *recoil; 
   recoil = new TTree("recoil","recoil");
   recoil->Branch("runNum" , &runNum , "runNum/I");
   recoil->Branch("eventID", &eventID, "eventID/I");
   recoil->Branch("coinReg", &coinReg, "coinReg/I");
   recoil->Branch("tofUS"  , &tofUS  , "tofUS/D");
   recoil->Branch("QUS"    , &QUS    , "QUS/D");
   recoil->Branch("tofS0D" , &tofS0D , "tofS0D/D");
   recoil->Branch("QS0D"   , &QS0D   , "QS0D/D");
   recoil->Branch("s0x"    , &s0x    , "s0x/D");
   recoil->Branch("s0y"    , &s0y    , "s0y/D");
   
//############################################################################
   art::TCoinRegData *hoge_coinReg;
   art::TEventHeader *hoge_run;
   TClonesArray *hoge_S0img, *hoge_fh9, *hoge_us, *hoge_V775;
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded.\n",rootfile);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("eventheader",1);
   tree->SetBranchStatus("coinReg",1);
   tree->SetBranchStatus("S0img",1);
   tree->SetBranchStatus("plaV1190_FH9",1); //get charge for PID
   tree->SetBranchStatus("tof_US",1);
   tree->SetBranchStatus("plaV775",1);    //get charge and time

   tree->SetBranchAddress("eventheader",&hoge_run);
   tree->SetBranchAddress("coinReg",&hoge_coinReg);
   tree->SetBranchAddress("S0img",&hoge_S0img);
   tree->SetBranchAddress("plaV1190_FH9",&hoge_fh9);
   tree->SetBranchAddress("tof_US",&hoge_us);
   tree->SetBranchAddress("plaV775",&hoge_V775);

//############################################################################   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   
   art::TTwoSidedPlasticData * V775Data;
   art::TTimeDifference * tofusdata;
   art::TTwoSidedPlasticData * Qusdata;
   art::TMWDCTrackingResult * xyS0;
   art::TTrack * trackS0;

//##############################################################################
   for( Int_t eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID);
      
//----------------Get Event Number
      runNum = hoge_run->GetRunNumber();

//----------------Get tof and charge upstream V1190
      tofUS = kInvalidD, QUS = kInvalidD;
      Int_t nHit = hoge_us -> GetEntriesFast();
      Bool_t PID = 0;
      for( Int_t p = 0; p < nHit; p++){
         tofusdata = (art::TTimeDifference*)hoge_us->At(p) ;
         Int_t HitID        = tofusdata->GetHitID();
         Double_t tof_us    = tofusdata->GetTiming();
         Qusdata = (art::TTwoSidedPlasticData*) hoge_fh9->At(HitID-1);
         Double_t Q_us      = Qusdata->GetCharge();
         if ( tof_us < beam->fTofGate[0] || tof_us> beam->fTofGate[1]) continue; //PID gate
         if ( Q_us < beam->fQGate[0] || Q_us > beam->fQGate[1]) continue; // PID gate
         tofUS = tof_us;
         QUS   = Q_us;
         PID = 1;
      }
      if ( PID == 0 ) continue;

//---------Get S0img image, should be one 1 instance
      nHit = hoge_S0img->GetEntriesFast();
      s0x = kInvalidD, s0y = kInvalidD;
      for( Int_t p = 0; p < nHit; p++){
         xyS0 = (art::TMWDCTrackingResult*)hoge_S0img->At(p);
         trackS0 = (art::TTrack*)xyS0->GetTrack();
         s0x = trackS0->GetX();
         s0y = trackS0->GetY();
      }
      
      if ( TMath::IsNaN(s0x) || TMath::IsNaN(s0y) ) continue;

//---------------Get charge DS of Tpla and S0D
      Double_t tFH9 = kInvalidD;
      Double_t tF3 = kInvalidD;
      tofS0D = kInvalidD; 
      QS0D = kInvalidD;
      Int_t nHit = hoge_V775->GetEntriesFast();
      for ( Int_t p = 0; p < nHit; p++){
         V775Data = (art::TTwoSidedPlasticData*)hoge_V775->At(p);
         Int_t DetID  = V775Data->GetDetID();
         if ( DetID == 2) {
            tF3    = V775Data->GetTiming();
         }
         if ( DetID == 3) {
            tFH9   = V775Data->GetTiming();
         }      
         if (DetID == 4) {
            QS0D   = V775Data->GetCharge(); 
            tofS0D = V775Data->GetTiming();
         }
      }
      if ( TMath::IsNaN(tFH9) || TMath::IsNaN(tofS0D) || TMath::IsNaN(tF3) ) continue;
      Double_t tof_usV775  = tFH9 - tF3 - beam->fToffsetV775 + Principle_tof;
      tofS0D = tofS0D - tFH9 - (tof_usV775)*LENGTH_RATIO_FH9_TGT;
      if (beam->fName == "14O" && runNum > 44) QS0D  = 1.75*QS0D[4]-403.5;

//--------------Get coinReg
      Int_t coinReg=0;
      for (Int_t k = 0; k <7; k++){
         if ( k == 1 ){
            if ( hoge_coinReg->Test(1) == 1 ) coinReg += 10;
         }else if ( k == 2){
            if ( hoge_coinReg->Test(2) == 1 ) coinReg += 20;
         }else if ( k == 3){
            if ( hoge_coinReg->Test(3) == 1) coinReg += 40;
         }else{
            if ( hoge_coinReg->Test(k) == 1) coinReg += 1;
         }
      }
      
      //printf(" tFH9:%10.2f, tofS0D:%10.2f, coinReg:%d\n", tFH9, tofS0D, coinReg);
      
//------------ Fill Tree
      savefile->cd(); //set focus on this file
      recoil->Fill(); 
     
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
   
   savefile->cd();
   recoil->Write();
   savefile->Close();
   f->Close();

   clock.Stop("timer");
   printf("============ finished|%10.3f sec\n",clock.GetRealTime("timer"));
   return ;
}

