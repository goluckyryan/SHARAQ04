#include <TBenchmark.h>
#include <TFile.h>
#include <TMath.h>
#include <math.h>
#include <TTree.h>
#include <TList.h>
#include <TClonesArray.h>
#include "constant.h"

void RunNumCoinReg() {
   
//############################################################################   
   //const char* rootfile="Data/phys24Up.root";
   const char* rootfile="Data/phys14Up.root";
   //const char* rootfile="Data/phys22_clean.root";
   Bool_t allentry  = 1;
   Int_t firstEntry = 3000000;
   Int_t nEntries=10000;
   
   Int_t runRange[2] = {0, 50};
  
//############################################################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;
   
   gStyle->SetOptStat(0);
   
   TString RunNumTitle;
   RunNumTitle.Form("RunNum (%s)", rootfile);
   
   TH1F* hRunNum  = new TH1F("hRunNum" , RunNumTitle, runRange[1]-runRange[0], runRange[0], runRange[1] );
   TH1F* hCoinReg = new TH1F("hCoinReg", "CoinReg| beam+=10, PPcoin+=20, NPcoin+=40, other+=1", 80, 0, 80 );
   
   TH2F* hCoinRun = new TH2F("hCoinRun", "CoinReg vs RunNum",runRange[1]-runRange[0], runRange[0], runRange[1], 80, 0, 80);
   // 0 = F3, 1 = FH9, 2=ppcoin, 3 = ND coin, 4 = ppsingle, 5 = ND single, 6 = ND cosmic
   TH1F* hCoinRegOrg = new TH1F("hCoinRegOrg", "CoinReg (inclusive)", 7, 0, 7); 
   
   TCanvas* cRunNum = new TCanvas("cRunNum", "RunNum & CoinReg", 100, 50, 800, 800);
   cRunNum->Divide(2,2);

//############################################################################
   art::TCoinRegData *hoge_coinReg;
   art::TEventHeader *hoge_run;
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded. \n",rootfile);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("eventheader",1);
   tree->SetBranchStatus("coinReg",1);

   tree->SetBranchAddress("eventheader",&hoge_run);
   tree->SetBranchAddress("coinReg",&hoge_coinReg);

//############################################################################   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   
   Int_t ppcoin = 0;
//##############################################################################
   for( Int_t eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID);
      
//----------------Get Event Number
      Int_t runNum = hoge_run->GetRunNumber();
      
      hRunNum->Fill(runNum);
      
//--------------Get coinReg
      // 0 = F3, 1 = FH9, 2=ppcoin, 3 = ND coin, 4 = ppsingle, 5 = ND single, 6 = ND cosmic
      Int_t coinReg = 0;
      for (Int_t k = 0; k <7; k++){
         if ( k == 1 ){
            if ( hoge_coinReg->Test(1) == 1 ) {
               coinReg += 10;
               hCoinRegOrg->Fill(1);
            }
         }else if ( k == 2){
            if ( hoge_coinReg->Test(2) == 1 ) {
               coinReg += 20;
               ppcoin += 1;
               hCoinRegOrg->Fill(2);
            }
         }else if ( k == 3){
            if ( hoge_coinReg->Test(3) == 1) {
               coinReg += 40;
               hCoinRegOrg->Fill(3);
            }
         }else{
            if ( hoge_coinReg->Test(k) == 1) {
               coinReg += 1;
               hCoinRegOrg->Fill(k);
            }
         }
      }
      hCoinReg->Fill(coinReg);
      
      hCoinRun->Fill(runNum, coinReg);
      
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
   
   cRunNum->cd(1);
   hRunNum->Draw();
   cRunNum->cd(2);
   hCoinReg->Draw();
   
   TLatex text;
   text.SetNDC();
   text.SetTextColor(1);
   TString textStr;
   textStr.Form("ppcoin:%d",ppcoin);
   text.DrawText(0.2, 0.8, textStr);
   textStr.Form("#event:%d",eventID);
   text.DrawText(0.2, 0.75, textStr);
   textStr.Form("ratio:%4.1f%%",ppcoin*100./eventID);
   text.DrawText(0.2, 0.7, textStr);
   
   cRunNum->cd(3);
   hCoinRun->Draw("colz");
   
   cRunNum->cd(4);
   hCoinRegOrg->Draw();
   // 0 = F3, 1 = FH9, 2=ppcoin, 3 = ND coin, 4 = ppsingle, 5 = ND single, 6 = ND cosmic
   text.SetTextAngle(90);
   text.SetNDC(0);
   text.SetTextSize(0.04);
   text.DrawText(0.5,0., "F3");
   text.DrawText(1.5,0., "beam");
   text.DrawText(2.5,0., "PPcoin");
   text.DrawText(3.5,0., "NPcoin");
   text.DrawText(4.5,0., "PPsingle");
   text.DrawText(5.5,0., "NDsingle");
   text.DrawText(6.5,0., "NDcosmic");
   
   Int_t maxBinHeight = hCoinRegOrg->GetMaximum();
   for( Int_t i = 1; i<8; i++){
      Int_t binCount = hCoinRegOrg->GetBinContent(i);
      textStr.Form("%7d",binCount);
      text.DrawText(i-0.5, maxBinHeight/2, textStr);
   }

   clock.Stop("timer");
   printf("============ finished|%10.3f sec\n",clock.GetRealTime("timer"));
   return ;
}
