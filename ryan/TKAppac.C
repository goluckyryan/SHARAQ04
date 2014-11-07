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

void TKAppac() {
   
//############################################################################   
   const char* rootfile="23F_0925_optics.root";
   //const char* rootfile="ppDown.root";
   //const char* rootfile="Data/phys2.root";
   TBeamData *beam  = new TBeamData("23F");
   Bool_t allentry  = 1;
   Int_t firstEntry =  0;
   Int_t nEntries   = 100000;
   
   beam->Print();
   Double_t Principle_tof = tofByBrho(L_F3FH9,beam->fBrho, beam->fMass, beam->fZ);
   Double_t Principle_TKA = TKAByBrho(beam->fBrho, beam->fMass, beam->fA, beam->fZ);
   printf("---- Principle Tof: %10.3f ns\n", Principle_tof);
   
//############################################################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;
   
   gStyle-> SetOptStat(0); 
   
   TCanvas* cTKAppac = new TCanvas("cTKAppac", "TKA check", 100, 50, 800,800);
   cTKAppac->Divide(2,2);
   
   TString hBrhoTitle;
   hBrhoTitle.Form("B_{#rho} (%s), %s", rootfile, beam->fName.Data());
   
   TH1F* hBrho = new TH1F("Brho", hBrhoTitle, 200, beam->fBrho-0.1, beam->fBrho+0.1);
//   TH1F* hBrho = new TH1F("Brho", hBrhoTitle, 100, 6, 7);
   TH1F* hTKAppac  = new TH1F("TKAppac" , "TKA by ppac", 240, beam->fTKA-6, beam->fTKA+6);
   hTKAppac->SetXTitle("TKA [MeV / nucleon]");
   hTKAppac->SetYTitle("count / 50 keV/nucleon");
   TH1F* hTKAV1190 = new TH1F("TKAV1190", "TKA by V1190", 240, beam->fTKA-6, beam->fTKA+6);
   TH1F* hTKAV775  = new TH1F("TKAV775" , "TKA by V775", 240, beam->fTKA-6, beam->fTKA+6);
   hTKAppac->SetLineColor(1);
   hTKAV1190->SetLineColor(2);
   hTKAV775->SetLineColor(4);
   
   TH2F* hBrhoTKAV775 = new TH2F("BrhoTKAV775", "Brho vs TKAV775",  100, beam->fTKA-10, beam->fTKA+10, 100, beam->fBrho-0.2, beam->fBrho+0.2);
   hBrhoTKAV775->SetXTitle("TKA by V775");
   hBrhoTKAV775->SetYTitle("Brho");
   TH2F* hTKAppacV775 = new TH2F("TKAppacV775", "TKAppac vs TKAV775",  100, beam->fTKA-10, beam->fTKA+10, 100, beam->fTKA-10, beam->fTKA+10);
   hBrhoTKAV775->SetXTitle("TKA by V775");
   hBrhoTKAV775->SetYTitle("TKA by ppac");
   
   TH1F* hTKADiff = new TH1F("TKADiff", "TKAppac - TKAV775", 100, -4, 4 );
   
//############################################################################
   art::TCoinRegData *hoge_coinReg;
   art::TEventHeader *hoge_run;
   TClonesArray *hoge_ppac,  *hoge_fh9, *hoge_us, *hoge_V775;
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded. \n",rootfile);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("eventheader",1);
   tree->SetBranchStatus("coinReg",1);
   //if (beam->fppacOn) 
   tree->SetBranchStatus("ppac",1);
   tree->SetBranchStatus("plaV1190_FH9",1); //get charge for PID
   tree->SetBranchStatus("tof_US",1);
   tree->SetBranchStatus("plaV775",1);    //get charge and time

   tree->SetBranchAddress("eventheader",&hoge_run);
   tree->SetBranchAddress("coinReg",&hoge_coinReg);
   //if (beam->fppacOn) 
   tree->SetBranchAddress("ppac",&hoge_ppac);
   tree->SetBranchAddress("plaV1190_FH9",&hoge_fh9);
   tree->SetBranchAddress("tof_US",&hoge_us);
   tree->SetBranchAddress("plaV775",&hoge_V775);

   art::TPPACData * ppacData;
   art::TTwoSidedPlasticData * V775Data;
   art::TTimeDifference * tofusdata;
   art::TTwoSidedPlasticData * Qusdata;
   
//############################################################################   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   
   gROOT->ProcessLine(".!date");
//##############################################################################
   for(Int_t eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID);
      
//----------------Get Event Number
      Int_t runNum = hoge_run->GetRunNumber();
      
//--------------Get coinReg
      // 0 = F3, 1 = FH9, 2=ppcoin, 3 = ND coin, 4 = ppsingle, 5 = ND single, 6 = ND cosmic
      if ( hoge_coinReg->Test(1) != 1 ) continue;
      
//---------------Get charge DS of Tpla and S0D
      Double_t timeV775[5];
      Int_t nHit = hoge_V775->GetEntriesFast();
      for ( Int_t p = 0; p < nHit; p++){
         V775Data = (art::TTwoSidedPlasticData*)hoge_V775->At(p);
         Int_t DetID     = V775Data->GetDetID();
         timeV775[DetID] = V775Data->GetTiming();
      }
      
//----------------Get tof and charge upstream V1190
      Double_t tof_usV1190 = kInvalidD;
      nHit = hoge_us -> GetEntriesFast();
      Bool_t PID = 0;
      for( Int_t p = 0; p < nHit; p++){
         tofusdata = (art::TTimeDifference*)hoge_us->At(p) ;
         Int_t HitID        = tofusdata->GetHitID();
         Double_t tof_us   = tofusdata->GetTiming();
         Qusdata = (art::TTwoSidedPlasticData*) hoge_fh9->At(HitID-1);
         Double_t Q_us      = Qusdata->GetCharge();
         if ( tof_us < beam->fTofGate[0] || tof_us> beam->fTofGate[1]) continue; //PID gate
         if ( Q_us < beam->fQGate[0] || Q_us > beam->fQGate[1]) continue; // PID gate
         tof_usV1190 = tof_us;
         PID = 1;
      }
      if ( PID == 0 ) continue;

//---------------------- PPAC;
      Double_t Brho = kInvalidD, ppacX = kInvalidD;
      //if (beam->fppacOn){
         nHit = hoge_ppac->GetEntriesFast();
         for (Int_t p = 0; p < nHit; p++){
            ppacData = (art::TPPACData*)hoge_ppac->At(p) ;
            ppacX = ppacData->GetX();
         }      
         if ( TMath::IsNaN(ppacX)) continue; 
         Brho = beam->fBrho * (1 - ppacX/7500.);
      //}else{
      //   Brho = beam->fBrho;
      //}      
      Double_t TKAppac = TKAByBrho(Brho, beam->fMass, beam->fA, beam->fZ);
      
      hBrho->Fill(Brho);
      hTKAppac->Fill(TKAppac);
      
//-------------------- Calculated TIme
      tof_usV1190 = tof_usV1190 - beam->fToffsetV1190 + Principle_tof;
      Double_t TKAV1190 = TKAByTof(L_F3FH9, tof_usV1190, beam->fMass, beam->fA);
      hTKAV1190->Fill(TKAV1190);
      
      
      Double_t tof_usV775  = timeV775[3] - timeV775[2] - beam->fToffsetV775 + Principle_tof;
      Double_t TKAV775 = TKAByTof(L_F3FH9, tof_usV775, beam->fMass, beam->fA);
      hTKAV775->Fill(TKAV775);
      
      hBrhoTKAV775->Fill(TKAV775,Brho);
      hTKAppacV775->Fill(TKAV775,TKAppac);
      hTKADiff->Fill(TKAppac - TKAV775);
      
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

   clock.Stop("timer");
   printf("============ finished|%10.3f sec\n",clock.GetRealTime("timer"));
   
   cTKAppac->cd(1);
   hBrho->Draw();
   
   TLine line;
   line.SetLineColor(2);
   line.DrawLine(beam->fBrho, 0, beam->fBrho, hBrho->GetMaximum());
   
   cTKAppac->cd(2);
   hBrhoTKAV775->Draw("colz"); 
   cTKAppac->cd(3);
   hTKAppacV775->Draw("colz"); 
   hTKADiff->Draw();
   
   cTKAppac->cd(4);
   hTKAppac->Draw("");
   hTKAV1190->Draw("same");
   hTKAV775->Draw("same");
   
   line.DrawLine(Principle_TKA, 0, Principle_TKA, hTKAppac->GetMaximum());
   
   TLatex text;
   text.SetNDC();
   text.SetTextColor(1);
   text.DrawText(0.2, 0.8, "ppac");
   text.SetTextColor(2);
   text.DrawText(0.2, 0.75, "V1190");
   text.SetTextColor(4);
   text.DrawText(0.2, 0.7, "V775");
   
   


   return ;
}
