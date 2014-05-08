#include <TBenchmark.h>
#include <TFile.h>
#include <TMath.h>
#include <math.h>
#include <TTree.h>
#include <TList.h>
#include <TClonesArray.h>
#include "constant.h"
#include "RelCalculator.h"
#include "TBeamData.h"


void TimeCheck() {
//================ Tree branch
   Int_t eventID;
   // runNumber
   Int_t runNum;
   // coinReg
   Int_t coinReg;
   // ppac
   Double_t ppacX, Brho, TKAppac;
   // get tof and charge upstream
   Double_t tdiffV1190, tdiffV775, tdiff1, tdiff2;
   //
   Double_t tof_usV1190;
   Double_t tof_usV775;
   //
   Double_t tofp1, tofp2;
   //
   Double_t tof1, tof2;
   // Phsyics
   Double_t TKAV1190, TKAV775;
   
//############################################################################   
   const char* savefilename="TimeCheck25F.root";
   //const char* rootfile="phys14_45_67.root";
   const char* rootfile="Data/phys24Optics.root";
   TBeamData *beam = new TBeamData("F25");
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=1000000;
   
//############################################################################   
   beam->Print();
   Double_t Principle_tof = tofByBrho(L_F3FH9,beam->fBrho, beam->fMass, beam->fZ);
   printf("---- Principle Tof: %10.3f ns\n", Principle_tof);

   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;

   TFile *savefile = new TFile(savefilename,"recreate");
   TTree *recoil; 
   recoil = new TTree("recoil","recoil");
   recoil->Branch("runNum", &runNum, "runNum/I");
   recoil->Branch("eventID",&eventID,"eventID/I");
   recoil->Branch("coinReg",&coinReg,"coinReg/I");
   recoil->Branch("tdiffV1190",&tdiffV1190,"tdiffV1190/D");
   recoil->Branch("tdiffV775",&tdiffV775,"tdiffV775/D");
   recoil->Branch("tdiff1",&tdiff1,"tdiff1/D");
   recoil->Branch("tdiff2",&tdiff2,"tdiff2/D");
   recoil->Branch("tof_usV1190",&tof_usV1190,"tof_usV1190/D");
   recoil->Branch("tof_usV775",&tof_usV775,"tof_usV775/D");
   recoil->Branch("tofp1",&tofp1,"tofp1/D");
   recoil->Branch("tofp2",&tofp2,"tofp2/D");
   recoil->Branch("tof1",&tof1,"tof1/D");
   recoil->Branch("tof2",&tof2,"tof2/D");
   recoil->Branch("ppacX", &ppacX, "ppacX/D");
   recoil->Branch("Brho",&Brho, "Brho/D");
   recoil->Branch("TKAppac",&TKAppac,"TKAppac/D");
   recoil->Branch("TKAV1190",&TKAV1190,"TKAV1190/D");
   recoil->Branch("TKAV775",&TKAV775,"TKAV775/D");


//############################################################################
   art::TCoinRegData *hoge_coinReg;
   art::TEventHeader *hoge_run;
   TClonesArray *hoge_ppac, *hoge_fh9, *hoge_us, *hoge_V775;
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded. ----> %s\n",rootfile, savefilename);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("eventheader",1);
   tree->SetBranchStatus("coinReg",1);
   if (beam->fppacOn) tree->SetBranchStatus("ppac",1);
   tree->SetBranchStatus("plaV1190_FH9",1); //get charge for PID
   tree->SetBranchStatus("tof_US",1);
   tree->SetBranchStatus("plaV775",1);    //get charge and time

   tree->SetBranchAddress("eventheader",&hoge_run);
   tree->SetBranchAddress("coinReg",&hoge_coinReg);
   if (beam->fppacOn) tree->SetBranchAddress("ppac",&hoge_ppac);
   tree->SetBranchAddress("plaV1190_FH9",&hoge_fh9);
   tree->SetBranchAddress("tof_US",&hoge_us);
   tree->SetBranchAddress("plaV775",&hoge_V775);


//############################################################################   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   
   art::TPPACData * ppacData;
   art::TTimeDifference * tofdsdata;
   art::TTwoSidedPlasticData * V775Data;
   art::TTimeDifference * tofusdata;
   art::TTwoSidedPlasticData * Qusdata;
   
   gROOT->ProcessLine(".!date");
   for( eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID);
      
      // initialization
      coinReg = 0;
      tof_usV1190 = kInvalidD;
      
//----------------Get Event Number
      runNum = hoge_run->GetRunNumber();
      
//--------------Get coinReg
      // 0 = F3, 1 = FH9, 2=ppcoin, 3 = ND coin, 4 = ppsingle, 5 = ND single, 6 = ND cosmic
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
      
//---------------Get charge DS of plaV775
      Double_t timeV775[5];
      Int_t nHit = hoge_V775->GetEntriesFast();
      for ( Int_t p = 0; p < nHit; p++){
         V775Data = (art::TTwoSidedPlasticData*)hoge_V775->At(p);
         Int_t DetID           = V775Data->GetDetID();
         timeV775[DetID] = V775Data->GetTiming();
      }
      
//----------------Get tof and charge upstream V1190
      nHit = hoge_us -> GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         tofusdata = (art::TTimeDifference*)hoge_us->At(p) ;
         Int_t HitID        = tofusdata->GetHitID();
         Double_t tof_us   = tofusdata->GetTiming();
         Qusdata = (art::TTwoSidedPlasticData*) hoge_fh9->At(HitID-1);
         Double_t Q_us      = Qusdata->GetCharge();
         if ( tof_us < beam->fTofGate[0] || tof_us> beam->fTofGate[1]) continue; //PID gate
         if ( Q_us < beam->fQGate[0] || Q_us > beam->fQGate[1]) continue; // PID gate
         tof_usV1190 = tof_us;
      }
      if( TMath::IsNaN(tof_usV1190)) continue;
//---------------------- PPAC;
   if (beam->fppacOn) {
      nHit = hoge_ppac->GetEntriesFast();
      for (Int_t p = 0; p < nHit; p++){
         ppacData = (art::TPPACData*)hoge_ppac->At(p) ;
         ppacX = ppacData->GetX();
      }
      if (!TMath::Finite(ppacX)) continue;
      Brho = beam->fBrho * (1 - ppacX/7500.);      
      TKAppac = TKAByBrho(Brho, beam->fMass, beam->fA, beam->fZ);
   }
//-------------------- Calculated TIme
      tdiffV1190 = tof_usV1190;
      tof_usV1190 = tof_usV1190 - beam->fToffsetV1190 + Principle_tof;
      if ( !TMath::Finite(tof_usV1190) ) continue;
      TKAV1190 = TKAByTof(L_F3FH9, tof_usV1190, beam->fMass, beam->fA);

      tdiffV775   = timeV775[3] - timeV775[2];
      tof_usV775  = timeV775[3] - timeV775[2] - beam->fToffsetV775 + Principle_tof;
      
      tdiff1 = timeV775[0] - timeV775[3];
      tdiff2 = timeV775[1] - timeV775[3];
      
      tofp1 = tdiff1 - (tof_usV775)*LENGTH_RATIO_FH9_TGT;
      tofp2 = tdiff2 - (tof_usV775)*LENGTH_RATIO_FH9_TGT;
      
      tof1 = tofp1 + beam->fToffset1 ;
      tof2 = tofp2 + beam->fToffset2 ;
      
      if ( !TMath::Finite(tof_usV775) ) continue;
      TKAV775 = TKAByTof(L_F3FH9, tof_usV775, beam->fMass, beam->fA);
      
//----------- Fill        
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
   printf("============ finished|%10.3f sec --> %s\n",clock.GetRealTime("timer"),savefilename);
   return ;
}
