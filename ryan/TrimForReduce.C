// Trim the root file, extract essentail data. For quicker analysis
#include "constant.h"
#include "RelCalculator.h"

void TrimForReduce() {
   
//############################################################################   
   const char* savefilename="R25F_0808_a.root";
   //const char* rootfile="Data/phys14_1_43.root";
   const char* rootfile="25F_0808.root";
   //const char* rootfile="Data/phys24Down.root";
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=100000;
   
//############################################################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;

//================ Tree branch
   Int_t eventID;
   // runNumber
   Int_t runNum;
   // coinReg
//   Int_t coinReg;
   // gate
   Int_t gate;
   // ppac
//   Double_t ppacX, Brho, TKAppac;
   // S0img
//   Double_t s0x, s0y;
   // get tof and charge upstream
   Double_t tof_usV1190, Q_us;
   Double_t tof_usV775;
   //downstream V775
   Double_t tof1, Q1;
   Double_t tof2, Q2;
   Double_t tofS0D, QS0D;
   // SMWDC X Y
/*   Double_t x1, y1, a1, b1; // for smwdc-L
   Double_t x2, y2, a2, b2; // for smwdc-R*/
   
   // Phsyics
//   Double_t TKAV775;
   Double_t E1, E2;
   Double_t theta1, theta2;
   Double_t phi1, phi2;
   //Double_t beamZ1, beamZ2, wbeamZ;
   Double_t vertexX, vertexY, vertexZ;
   Double_t Sp;
   Double_t Sp2;

   TFile *savefile = new TFile(savefilename,"recreate");
   TTree *recoil; 
   recoil = new TTree("recoil","recoil");
   recoil->Branch("runNum", &runNum, "runNum/I");
   recoil->Branch("eventID",&eventID,"eventID/I");
   recoil->Branch("gate",&gate,"gate/I");
//   recoil->Branch("coinReg",&coinReg,"coinReg/I");
   recoil->Branch("tof_usV1190",&tof_usV1190,"tof_usV1190/D");
   recoil->Branch("tof_usV775",&tof_usV775,"tof_usV775/D");
   recoil->Branch("Q_us",&Q_us,"Q_us/D");
//   recoil->Branch("s0x", &s0x, "s0x/D");
//   recoil->Branch("s0y", &s0y, "s0y/D");
//   recoil->Branch("ppacX", &ppacX, "ppacX/D");
//   recoil->Branch("Brho",&Brho, "Brho/D");
//   recoil->Branch("TKAppac",&TKAppac,"TKAppac/D");
//   recoil->Branch("TKAV775",&TKAV775,"TKAV775/D");
   recoil->Branch("tofS0D", &tofS0D, "tofS0D/D");
   recoil->Branch("QS0D", &QS0D, "QS0D/D");
   recoil->Branch("tof1",&tof1,"tof1/D");
   recoil->Branch("tof2",&tof2,"tof2/D");
   recoil->Branch("Q1",&Q1,"Q1/D");
   recoil->Branch("Q2",&Q2,"Q2/D");
/*   recoil->Branch("x1",&x1,"x1/D");
   recoil->Branch("a1",&a1,"a1/D");
   recoil->Branch("y1",&y1,"y1/D");
   recoil->Branch("b1",&b1,"b1/D");
   recoil->Branch("x2",&x2,"x2/D");
   recoil->Branch("a2",&a2,"a2/D");
   recoil->Branch("y2",&y2,"y2/D");
   recoil->Branch("b2",&b2,"b2/D");*/
   recoil->Branch("E1",&E1,"E1/D");
   recoil->Branch("E2",&E2,"E2/D");
   recoil->Branch("theta1",&theta1,"theta1/D");
   recoil->Branch("theta2",&theta2,"theta2/D");
   recoil->Branch("phi1",&phi1,"phi1/D");
   recoil->Branch("phi2",&phi2,"phi2/D");
   //recoil->Branch("beamZ1",&beamZ1,"beamZ1/D");
   //recoil->Branch("beamZ2",&beamZ2,"beamZ2/D");
   //recoil->Branch("wbeamZ", &wbeamZ,"wbeamZ/D");
   recoil->Branch("vertexX",&vertexX,"vertexX/D");
   recoil->Branch("vertexY",&vertexY,"vertexY/D");
   recoil->Branch("vertexZ",&vertexZ,"vertexZ/D");
   recoil->Branch("Sp",&Sp,"Sp/D");
   recoil->Branch("Sp2",&Sp2,"Sp2/D");

//############################################################################
   
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded. ----> %s\n",rootfile, savefilename);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("eventheader",1);
//   tree->SetBranchStatus("coinReg",1);
   tree->SetBranchStatus("gate",1);
   //tree->SetBranchStatus("ppac",1);
//   tree->SetBranchStatus("S0img",1);
   tree->SetBranchStatus("plaV1190_FH9",1); //get charge for PID
   tree->SetBranchStatus("tof_US",1);
   tree->SetBranchStatus("plaV775",1);    //get charge and time
//   tree->SetBranchStatus("smwdc_L",1);
//   tree->SetBranchStatus("smwdc_R",1);
   //tree->SetBranchStatus("beamZ",1);
   tree->SetBranchStatus("vertex",1);
   tree->SetBranchStatus("tofL",1);
   tree->SetBranchStatus("tofR",1);
   tree->SetBranchStatus("tofS0D",1);
   tree->SetBranchStatus("p2p",1);
   
   //art::TCoinRegData *hoge_coinReg;
   art::TGateArray* hoge_gate;
   art::TEventHeader *hoge_run;
   //TClonesArray *hoge_ppac, *hoge_S0img;
   TClonesArray *hoge_fh9, *hoge_us, *hoge_V775;
   // *hoge_L, *hoge_R;
   TClonesArray *hoge_beamZ, *hoge_vertex, *hoge_tofL, *hoge_tofR, *hoge_tofS0D;
   art::sh04::TP2PKinematicsData *hoge_p2p;
   
   tree->SetBranchAddress("eventheader",&hoge_run);
//   tree->SetBranchAddress("coinReg",&hoge_coinReg);
   tree->SetBranchAddress("gate",&hoge_gate);
   //tree->SetBranchAddress("ppac",&hoge_ppac);
//   tree->SetBranchAddress("S0img",&hoge_S0img);
   tree->SetBranchAddress("plaV1190_FH9",&hoge_fh9);
   tree->SetBranchAddress("tof_US",&hoge_us);
   tree->SetBranchAddress("plaV775",&hoge_V775);
//   tree->SetBranchAddress("smwdc_L",&hoge_L);
//   tree->SetBranchAddress("smwdc_R",&hoge_R);
   //tree->SetBranchAddress("beamZ",&hoge_beamZ);
   tree->SetBranchAddress("vertex",&hoge_vertex);
   tree->SetBranchAddress("tofL",&hoge_tofL);
   tree->SetBranchAddress("tofR",&hoge_tofR);
   tree->SetBranchAddress("tofS0D",&hoge_tofS0D);
   tree->SetBranchAddress("p2p",&hoge_p2p);

//############################################################################   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   
   Int_t count0 = 0 , count1 = 0;
   
   gROOT->ProcessLine(".!date");
//##############################################################################
   for( eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID);
      
      // initialization
      coinReg = 0;
      tof_usV1190 = kInvalidD; Q_us = kInvalidD;
      tof1  = kInvalidD; Q1 = kInvalidD; 
      tof2  = kInvalidD; Q2 = kInvalidD;
      //tdiff1 = kInvalidD; tdiff2 = kInvalidD;
      tofS0D= kInvalidD; QS0D = kInvalidD;
      
//----------------Get Event Number
      runNum = hoge_run->GetRunNumber();

//--------------- Get gate
	  Int_t Ngate = hoge_gate->GetSize();
	  gate = 0;
      for ( Int_t i = 0; i < Ngate; i++){
      	if( hoge_gate->Test(i)) gate += TMath::Power(2,i);
      }
//--------------Get coinReg
 /*     // 0 = F3, 1 = FH9, 2=ppcoin, 3 = ND coin, 4 = ppsingle, 5 = ND single, 6 = ND cosmic
      for (Int_t k = 0; k <7; k++){
         if ( k == 1 ){
            if ( hoge_coinReg->Test(1) == 1 ) coinReg += 10;
         }else if ( k == 2){
            if ( hoge_coinReg->Test(2) == 1 ) {
               coinReg += 20;
            }
         }else if ( k == 3){
            if ( hoge_coinReg->Test(3) == 1) coinReg += 40;
         }else{
            if ( hoge_coinReg->Test(k) == 1) coinReg += 1;
         }
      }
      //if( coinReg%10 != 0 ) continue;

      */
//---------------Get charge DS of Tpla and S0D
      Int_t TplaHit_check = 0;
      Double_t timeV775[5], Q_ds[5];
      Int_t nHit = hoge_V775->GetEntriesFast();
      for ( Int_t p = 0; p < nHit; p++){
        art:: TTwoSidedPlasticData* V775Data = (art::TTwoSidedPlasticData*)hoge_V775->At(p);
         Int_t DetID           = V775Data->GetDetID();
         Q_ds[DetID]     = V775Data->GetCharge(); 
         timeV775[DetID] = V775Data->GetTiming();
         if (DetID == 0 || DetID == 1) TplaHit_check++;

      }
      if ( TplaHit_check !=2 ) continue;           // both Tpla hit timing gate // Part of ppcoin
      count0 ++;
      QS0D = Q_ds[4];
      Q1   = Q_ds[0];
      Q2   = Q_ds[1];
      
//----------------Get tof and charge upstream V1190
      nHit = hoge_us -> GetEntriesFast();
      Bool_t PID = 0;
      for( Int_t p = 0; p < nHit; p++){
        art:: TTimeDifference* tofusdata = (art::TTimeDifference*)hoge_us->At(p) ;
         Int_t HitID        = tofusdata->GetHitID();
         Double_t tof_usV1190   = tofusdata->GetTiming();
         art::TTwoSidedPlasticData* Qusdata = (art::TTwoSidedPlasticData*) hoge_fh9->At(HitID-1);
         Double_t Q_us      = Qusdata->GetCharge();
      }
//---------------------- PPAC;
/*      nHit = hoge_ppac->GetEntriesFast();
      for (Int_t p = 0; p < nHit; p++){
        art::TPPACData * ppacData = (art::TPPACData*)hoge_ppac->At(p) ;
         ppacX = ppacData->GetX();
      }
      Brho = 7.1315 * (1 - ppacX/7500.);
 
      TKAppac = TKAByBrho(Brho, mp, 1, 1);
      */
//-------------------- get tof
	  nHit = hoge_tofL->GetEntriesFast();
      for (Int_t p = 0; p < nHit; p++){
         art:: TTimeDifference* tofL = (art::TTimeDifference*)hoge_tofL->At(p) ;
         tof1 = tofL->GetTiming();
      }


	  nHit = hoge_tofR->GetEntriesFast();
      for (Int_t p = 0; p < nHit; p++){
         art:: TTimeDifference* tofR = (art::TTimeDifference*)hoge_tofR->At(p) ;
         tof2 = tofR->GetTiming();
      }


	  nHit = hoge_tofS0D->GetEntriesFast();
      for (Int_t p = 0; p < nHit; p++){
         art:: TTimeDifference* tof_S0D = (art::TTimeDifference*)hoge_tofS0D->At(p) ;
         tofS0D = tof_S0D->GetTiming();
      }
      
      //if ( TMath::IsNaN(tof1) || TMath::IsNaN(tof2) ) continue;         // tof gate

      
//---------Get S0img image, should be one 1 instance
 /*     nHit = hoge_S0img->GetEntriesFast();
      //Double_t s0a, s0b;
      for( Int_t p = 0; p < nHit; p++){
         art::TMWDCTrackingResult * xyS0 = (art::TMWDCTrackingResult*)hoge_S0img->At(p);
         art::TTrack * trackS0 = (art::TTrack*)xyS0->GetTrack();
         s0x = trackS0->GetX();
         s0y = trackS0->GetY();
         //s0a = trackS0->GetA();
         //s0b = trackS0->GetB();
      }      

      if( TMath::IsNaN(s0x)) continue;
      
//---------Get SMWDC image, should be one 1 instance
      nHit = hoge_L->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         art::TMWDCTrackingResult * xy1 = (art::TMWDCTrackingResult*)hoge_L->At(p);
         //NValidPlane1 = xy1 -> GetNPlaneValid();
         Int_t TrackingID1  = xy1 -> GetTrackingID();
         //Double_t ex1 = xy1->GetSigma(0);
         //Double_t ea1 = xy1->GetSigma(1);
         art::TTrack * track1 = (art::TTrack*)xy1->GetTrack();
/*         x1 = track1->GetX();
         y1 = track1->GetY();
         a1 = track1->GetA();
         b1 = track1->GetB();
      }
      if (TrackingID1 != 1) continue;

      nHit = hoge_R->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         art::TMWDCTrackingResult * xy2 = (art::TMWDCTrackingResult*)hoge_R->At(p);
         //NValidPlane2 = xy2 -> GetNPlaneValid();
         Int_t TrackingID2  = xy2 -> GetTrackingID();
         //Double_t ex2 = xy2->GetSigma(0);
         //Double_t ea2 = xy2->GetSigma(1);
         art::TTrack * track2 = (art::TTrack*)xy2->GetTrack();
  /*       x2 = track2->GetX();
         y2 = track2->GetY();
         a2 = track2->GetA();
         b2 = track2->GetB();
      }
      
      if ( TrackingID2 != 1) continue;
      count1 ++;*/
      
//--------------- Get vertex , beamZ
      nHit = hoge_vertex->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
        art::TTrack * ver = (art::TTrack*)hoge_vertex->At(p);
        vertexX = ver->GetX();
        vertexY = ver->GetY();
        vertexZ = ver->GetZ();
      }

/*
      nHit = hoge_beamZ->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
        art::sh04::TBeamZ * beamZ = (art::sh04::TBeamZ*)hoge_beamZ->At(p);
        beamZ1 = beamZ->GetL();
        beamZ2 = beamZ->GetR();
        wbeamZ = beamZ->GetAverage();
      }
*/
//--------------- Get p2p

      E1 = hoge_p2p->GetRecoilL()->E();
      E2 = hoge_p2p->GetRecoilR()->E();      

      theta1 = hoge_p2p->GetRecoilL()->Theta()*TMath::RadToDeg();
      theta2 = hoge_p2p->GetRecoilR()->Theta()*TMath::RadToDeg();

      phi1 = hoge_p2p->GetRecoilL()->Phi()*TMath::RadToDeg();
      phi1 = hoge_p2p->GetRecoilR()->Phi()*TMath::RadToDeg();

      Sp = hoge_p2p->GetSp();
      Sp2 = hoge_p2p->GetSp2();

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
   printf(" Both Tpla fired gate   : %d \n", count0);
   printf(" S0, MWDC-L/R Track gate: %d \n", count1);

   return ;
}
