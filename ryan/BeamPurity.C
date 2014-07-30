#include <TBenchmark.h>
#include <TFile.h>
#include <TMath.h>
#include <math.h>
#include <TTree.h>
#include <TList.h>
#include <TClonesArray.h>
#include "constant.h"
#include "RelCalculator.h"
#include "Compress/TBeamData.h"

void BeamPurity() {
//================ Tree branch
   Int_t eventID;
   // runNumber
   Int_t runNum;
   // coinReg
   Int_t coinReg;
   // get tof and charge upstream
   Double_t tof_usV1190, Q_usG;
   
//############################################################################   
   const char* rootfile="Data/phys22Optics.root";
   TBeamData *beam = new TBeamData("23F");
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=600000;
   
   beam->Print();
   Double_t Principle_tof = tofByBrho(L_F3FH9,beam->fBrho, beam->fMass, beam->fZ);
   printf("---- Principle Tof: %10.3f ns\n", Principle_tof);
//############################################################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;

   gStyle->SetOptStat(0);
   
   TCanvas* cBeamRatio = new TCanvas("cBeamRatio", "BeamRatio", 300, 150, 800, 400);
   cBeamRatio->Divide(2,1);
   
   TH2F * hPIDUS     = new TH2F("PIDUS", "PID up stream", 300, -1500, -1400, 300, 5000, 6500);
   TH2F * hPIDUSbeam = new TH2F("PIDUSbeam", "PID up stream gated", 300, -1500, -1400, 300, 5000, 6500);

//############################################################################
   art::TCoinRegData *hoge_coinReg;
   art::TEventHeader *hoge_run;
   TClonesArray  *hoge_fh9, *hoge_us;
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded. \n",rootfile);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("eventheader",1);
   tree->SetBranchStatus("coinReg",1);
   tree->SetBranchStatus("plaV1190_FH9",1); //get charge for PID
   tree->SetBranchStatus("tof_US",1);

   tree->SetBranchAddress("eventheader",&hoge_run);
   tree->SetBranchAddress("coinReg",&hoge_coinReg);
   tree->SetBranchAddress("plaV1190_FH9",&hoge_fh9);
   tree->SetBranchAddress("tof_US",&hoge_us);

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
   
   gROOT->ProcessLine(".!date");
   Int_t count_USHit = 0, count_PIDgate=0;
   
//##############################################################
   for( eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID);
      
      // initialization
      coinReg = 0;
      tof_usV1190 = kInvalidD; Q_usG = kInvalidD;

//--------------Get coinReg
      // 0 = F3, 1 = FH9, 2=ppcoin, 3 = ND coin, 4 = ppsingle, 5 = ND single, 6 = ND cosmic
      /*for (Int_t k = 0; k <7; k++){
         if ( k == 1 ){
            if ( hoge_coinReg->Test(1) == 1 ) coinReg += 10;
         }else if ( k == 2){
            if ( hoge_coinReg->Test(2) == 1 ) coinReg += 20;
         }else if ( k == 3){
            if ( hoge_coinReg->Test(3) == 1) coinReg += 40;
         }else{
            if ( hoge_coinReg->Test(k) == 1) coinReg += 1;
         }
      }*/
      if( hoge_coinReg->Test(1) != 1 ) continue;

//----------------Get Event Number
      runNum = hoge_run->GetRunNumber();
//----------------Get tof and charge upstream V1190
      //Double_t tof_us[40], Q_us[40];
      Bool_t PID = 0;
      Int_t nHit = hoge_us -> GetEntriesFast();
      if (nHit == 0) continue;
      count_USHit++;
      
      for( Int_t p = 0; p < nHit; p++){
         tofusdata = (art::TTimeDifference*)hoge_us->At(p) ;
         Int_t HitID        = tofusdata->GetHitID();
         Double_t tof_us    = tofusdata->GetTiming();
         Qusdata = (art::TTwoSidedPlasticData*) hoge_fh9->At(HitID-1);
         Double_t Q_us      = Qusdata->GetCharge();
         hPIDUS->Fill(tof_us, Q_us);
         if ( tof_us < beam->fTofGate[0] || tof_us> beam->fTofGate[1]) continue; //PID gate
         if ( Q_us < beam->fQGate[0] || Q_us > beam->fQGate[1]) continue; // PID gate
         tof_usV1190 = tof_us;
         Q_usG   = Q_us;
         PID = 1;
      }
      if ( PID == 0 ) continue;
      hPIDUSbeam->Fill(tof_usV1190, Q_usG);
      count_PIDgate++;
      
//------------Clock      
/*      clock.Stop("timer");
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
*/      
   }
   
   cBeamRatio->cd(1);
   hPIDUS->Draw("colz");
   cBeamRatio->cd(2);
   hPIDUSbeam->Draw("colz");

   clock.Stop("timer");
   printf("============ finished|%10.3f sec\n",clock.GetRealTime("timer"));
   printf("             nEntries:%10d \n", nEntries);
   printf(" count   coinReg  :%10d [%4.1f%%] \n",  count_USHit, count_USHit*100./nEntries);
   printf(" count     PID    :%10d [%4.1f%%][%4.1f%%] \n",  count_PIDgate, count_PIDgate*100./nEntries, count_PIDgate*100./count_USHit);
   
   TString testStr;
   TLatex text;
   text.SetNDC();
   text.SetTextColor(1);
   testStr.Form("coinReg:%d", count_USHit);
   text.DrawText(0.2, 0.3, testStr);
   testStr.Form("PID:%d[%4.1f%%(%4.1f%%)]", count_PIDgate,count_PIDgate*100./count_USHit, TMath::Sqrt(1./count_PIDgate+1./count_USHit)*100.*count_PIDgate/count_USHit);
   text.DrawText(0.2, 0.25, testStr);
   
   return ;
}
