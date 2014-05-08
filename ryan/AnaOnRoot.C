#include "constant.h"
#include "TBeamData.h"
#include "TRecoilData.h"

void AnaOnRoot() {
   gStyle->SetOptStat(0);

   
   TFile *f0 = new TFile ("23FUp_ppcoin.root");
   TTree *tree = (TTree*)f0->Get("tree");
   TBeamData *beam = new TBeamData("23F");
   Bool_t allentry  = 0;
   Int_t firstEntry = 0;
   Int_t nEntries=1000000;

//##########################################################
   beam->Print();
   Double_t Principle_tof = tofByBrho(L_F3FH9,beam->fBrho, beam->fMass, beam->fZ);
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;
   
   TCanvas *cAnaOnRoot = new TCanvas("cScript", "cScript", 1200,50, 900,900);   
   cAnaOnRoot->Divide(3,3);
   
   TH1F* hCoinReg = new TH1F("hCoinReg", "CoinReg", 7, 0,7);
   TH2F* hPIDUSV1190 = new TH2F("hPIDUSV1190"  , "PID UpStream V1190", 300, -1470,-1420, 300, 3000, 6500);
   TH2F* hPIDUSV775  = new TH2F("hPIDUSV775"  , "PID UpStream V775", 300, 370, 420, 300, 3000, 6500);
   TH2F* hPIDDS   = new TH2F("hPIDDS"  , "PID DownStream", 300, -137,-127, 300, 1000, 3000);
   TH1F* hBeamZ   = new TH1F("hBeamZ"  , "BeamZ", 100, -100,200);
   TH1F* hOpenAng = new TH1F("hOpenAng", "OpenAng", 50, 60,110);
   TH1F* hSp      = new TH1F("hSp"     , "Sp",  150, -50, 100);
 
//##########################################################   
   art::TCoinRegData *hoge_coinReg;
   art::TEventHeader *hoge_run;
   art::sh04::TP2PKinematicsData *hoge_p2p;
   TLorentzVector *hoge_L, *hoge_R;
   TClonesArray *hoge_ppac, *hoge_S0img, *hoge_fh9, *hoge_us, *hoge_V775, *hoge_beamZ;
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("eventheader",1);
   tree->SetBranchStatus("coinReg",1);
   tree->SetBranchStatus("ppac",1);
   tree->SetBranchStatus("S0img",1);
   tree->SetBranchStatus("plaV1190_FH9",1); //get charge for PID
   tree->SetBranchStatus("tof_US",1);
   tree->SetBranchStatus("plaV775",1);    //get charge and time
   tree->SetBranchStatus("beamZ", 1);
   tree->SetBranchStatus("recoil_L",1);
   tree->SetBranchStatus("recoil_R",1);
   tree->SetBranchStatus("p2p",1);

   tree->SetBranchAddress("eventheader",&hoge_run);
   tree->SetBranchAddress("coinReg",&hoge_coinReg);
   tree->SetBranchAddress("ppac",&hoge_ppac);
   tree->SetBranchAddress("S0img",&hoge_S0img);
   tree->SetBranchAddress("plaV1190_FH9",&hoge_fh9);
   tree->SetBranchAddress("tof_US",&hoge_us);
   tree->SetBranchAddress("plaV775",&hoge_V775);
   tree->SetBranchAddress("beamZ",&hoge_beamZ);
   tree->SetBranchAddress("recoil_L",&hoge_L);
   tree->SetBranchAddress("recoil_R",&hoge_R);
   tree->SetBranchAddress("p2p",&hoge_p2p);

//############################################################################   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   
   art::TPPACData * ppacData;
   art::TTwoSidedPlasticData * V775Data;
   art::TTimeDifference * tofusdata;
   art::TTwoSidedPlasticData * Qusdata;
   art::TMWDCTrackingResult * xyS0;
   art::TTrack * trackS0;
   art::sh04::TBeamZ *beamZData;
   
//##############################################################################
   for( Int_t eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID);
      
//----------------Get Event Number
      Int_t runNum = hoge_run->GetRunNumber();
      
//--------------Get coinReg
      // 0 = F3, 1 = FH9, 2=ppcoin, 3 = ND coin, 4 = ppsingle, 5 = ND single, 6 = ND cosmic
      Bool_t CoinRegGate = 0;
      for (Int_t k = 0; k <7; k++){
         if ( hoge_coinReg->Test(k) == 1){
            if ( k == 2) {
               CoinRegGate = 1;
               hCoinReg->Fill(k);
            }
         }
      }
      if( !CoinRegGate ) continue;
      
//----------------Get tof and charge upstream V1190
      Int_t nHit = hoge_us -> GetEntriesFast();
      Bool_t PID = 0;
      Double_t tof_usV1190 = kInvalidD;
      Double_t Q_usG = kInvalidD;
      for( Int_t p = 0; p < nHit; p++){
         tofusdata = (art::TTimeDifference*)hoge_us->At(p) ;
         Int_t HitID        = tofusdata->GetHitID();
         Double_t tof_us    = tofusdata->GetTiming();
         Qusdata = (art::TTwoSidedPlasticData*) hoge_fh9->At(HitID-1);
         Double_t Q_us      = Qusdata->GetCharge();
         if ( tof_us < beam->fTofGate[0] || tof_us> beam->fTofGate[1]) continue; //PID gate
         if ( Q_us < beam->fQGate[0] || Q_us > beam->fQGate[1]) continue; // PID gate
         tof_usV1190 = tof_us;
         Q_usG   = Q_us;
         PID = 1;
      }
      if ( PID == 0 ) continue;
      hPIDUSV1190->Fill(tof_usV1190, Q_usG);
      
//---------------Get charge DS of Tpla and S0D
      Int_t TplaHit_check = 0;
      Double_t timeV775[5], Q_ds[5];
      Int_t nHit = hoge_V775->GetEntriesFast();
      for ( Int_t p = 0; p < nHit; p++){
         V775Data = (art::TTwoSidedPlasticData*)hoge_V775->At(p);
         Int_t DetID           = V775Data->GetDetID();
         Q_ds[DetID]     = V775Data->GetCharge(); 
         timeV775[DetID] = V775Data->GetTiming();
         if (DetID == 0 || DetID == 1) TplaHit_check++;

      }
      if ( TplaHit_check !=2 ) continue;           // both Tpla hit timing gate // Part of ppcoin
      if ( Q_ds[0] < 500 || Q_ds[1] < 500) continue;  // gamma gate 

//-------------------- Calculated TIme
      //Double_t tof1        = kInvalidD; Double_t Q1    = kInvalidD; 
      //Double_t tof2        = kInvalidD; Double_t Q2    = kInvalidD;
      Double_t tofS0D      = kInvalidD; Double_t QS0D  = kInvalidD;
      
      Double_t tof_usV775  = timeV775[3] - timeV775[2] - beam->fToffsetV775 + Principle_tof;
      Double_t tref_tgt = timeV775[3] + (tof_usV775)*LENGTH_RATIO_FH9_TGT;// tof from Fh9 to tgt
      
      //tof1   = timeV775[0] - tref_tgt + beam->fToffset1 ; Q1    = Q_ds[0];
      //tof2   = timeV775[1] - tref_tgt + beam->fToffset2 ; Q2    = Q_ds[1];
      tofS0D = timeV775[4] - tref_tgt ; QS0D = Q_ds[4];
      
      hPIDUSV775->Fill(tof_usV775, Q_usG);
      hPIDDS->Fill(tofS0D, QS0D);

//---------------------- PPAC;
/*      if (beam->fppacOn){
         nHit = hoge_ppac->GetEntriesFast();
         for (Int_t p = 0; p < nHit; p++){
            ppacData = (art::TPPACData*)hoge_ppac->At(p) ;
            ppacX = ppacData->GetX();
         }
         Brho = beam->fBrho * (1 - ppacX/7500.);
      }else{
         Brho = beam->fBrho;
      }      
      TKAppac = TKAByBrho(Brho, beam->fMass, beam->fA, beam->fZ);
*/      
      
//---------Get beamZ
      Int_t nHit = hoge_beamZ->GetEntriesFast();
      Double_t beamZ;
      for ( Int_t p = 0; p < nHit; p++){
         beamZData = (art::sh04::TBeamZ*)hoge_beamZ->At(p);
         beamZ = beamZData->GetAverage();
      }
      hBeamZ->Fill(beamZ);

//---------Get OpenAngle
      Double_t theta1 = hoge_L->Theta() * TMath::RadToDeg();
      Double_t theta2 = hoge_R->Theta() * TMath::RadToDeg();
      
      hOpenAng -> Fill(theta1+theta2);
      
//---------Get Sp
      hSp -> Fill(hoge_p2p->GetSp());

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
   
   cAnaOnRoot->cd(1);
   hCoinReg->Draw();
   
   cAnaOnRoot->cd(2);
   hPIDUSV1190->Draw("colz");

   cAnaOnRoot->cd(3);
   hPIDUSV775->Draw("colz");
   
   cAnaOnRoot->cd(4);
   hPIDDS->Draw("colz");
   
   cAnaOnRoot->cd(5);
   hBeamZ->Draw();
   
   cAnaOnRoot->cd(6);
   hOpenAng->Draw();
   
   cAnaOnRoot->cd(7);
   hSp->Draw();

   clock.Stop("timer");
   printf("============ finished|%10.3f sec \n",clock.GetRealTime("timer"));
   
/*   TLatex text;
   text.SetNDC();
   text.SetTextColor(1);
   text.DrawText(0.2, 0.3, "no Corr");
   text.SetTextColor(2);
   text.DrawText(0.2, 0.25, "Mag Corr");
   text.SetTextColor(4);
   text.DrawText(0.2, 0.2, "Mag + BeamZ=15 Corr");*/
   
   
}
