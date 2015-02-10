// Trim the root file, extract essentail data. For quicker analysis
#include "constant.h"
//#include "RelCalculator.h"

void PostTree() {
   
//############################################################################   
	const char* savefilename="P_23F_0208.root";
	const char* rootfile="23F_0208.root";
	
	Bool_t allentry  = 0;
	Int_t firstEntry = 0;
	Int_t nEntries=100000;

	Bool_t gate23F = 1;
   
   Bool_t getrunNum   = 1;
   Bool_t getcoinReg  = 0;
   Bool_t getgate     = 1;
   Bool_t getPPAC     = 0;
   Bool_t getS0img    = 0;
   Bool_t getFH9      = 1;
   Bool_t getTplaL    = 0;
   Bool_t getTplaR    = 0;
   Bool_t getS0D      = 1;
   Bool_t getMWDCL    = 1;
   Bool_t getMWDCR    = 1;
   Bool_t getMWDCS1   = 1;
   Bool_t getvertex   = 1;
   Bool_t getpidDS    = 1;
   Bool_t getp2p      = 1;
   
//############################################################################
	TBenchmark clock;
	clock.Reset();
	clock.Start("timer");
	Bool_t shown = 0;

//================ Tree branch
	Int_t eventID;
	//  runNumber
	Int_t runNum;
	// coinReg
	Int_t coinReg;
	// gate
	Int_t gate;
	// ppac
	Double_t ppacX, Brho, TKAppac;
	// S0img
	Double_t s0x, s0y;
	// get tof and charge upstream
	Double_t tofFH9, QFH9;
	Double_t tofFH9v775;
	//downstream V775
	Double_t tof1, Q1;
	Double_t tof2, Q2;
	Double_t tofS0D, QS0D;
	Double_t tofS1, QS1;
	// SMWDC X Y
	Double_t x1, y1, a1, b1; // for smwdc-L
	Double_t x2, y2, a2, b2; // for smwdc-R
	Double_t s1x, s1y, s1a, s1b; // for smwdc-S1
	// pid_ds
	Double_t pidZ, pidAoQ;
	//vertex
	Double_t vertexZ;
	// Phsyics
	Double_t E1, E2;
	Double_t theta1, theta2;
	Double_t phi1, phi2;
	Double_t Ex;
	Double_t Ex2; // Sp2 - 13.26;
	Double_t kMomt; // redisual momentum


	TFile *savefile = new TFile(savefilename,"recreate");
	TTree *tree = new TTree("tree","tree");

	tree->Branch("eventID",&eventID,"eventID/I");   
	if (getrunNum) tree->Branch("runNum", &runNum, "runNum/I");
	if (getcoinReg) tree->Branch("coinReg",&coinReg,"coinReg/I");
	if (getgate ) tree->Branch("gate",&gate,"gate/I");
	if (getPPAC) {
		tree->Branch("ppacX", &ppacX, "ppacX/D");
		tree->Branch("Brho",&Brho, "Brho/D");
		tree->Branch("TKAppac",&TKAppac,"TKAppac/D");
	}
	if ( getFH9){
		tree->Branch("tofFH9",&tofFH9,"tofFH9/D");
		tree->Branch("tofFH9v775",&tofFH9v775,"tofFH9v775/D");
		tree->Branch("QFH9",&QFH9,"QFH9/D");
	}
	if (getS0img){
		tree->Branch("s0x", &s0x, "s0x/D");
		tree->Branch("s0y", &s0y, "s0y/D");
	}
	if (getS0D){
		tree->Branch("tofS0D", &tofS0D, "tofS0D/D");
		tree->Branch("QS0D", &QS0D, "QS0D/D");
	}
	if (getTplaL){	
		tree->Branch("tof1",&tof1,"tof1/D");
		tree->Branch("Q1",&Q1,"Q1/D");
	}
	if (getTplaR){
		tree->Branch("tof2",&tof2,"tof2/D");
		tree->Branch("Q2",&Q2,"Q2/D");
	}
	
//   tree->Branch("tofS1",&tofS1,"tofS1/D");
//   tree->Branch("QS1",&QS1,"QS1/D");

	if( getMWDCL){
		tree->Branch("x1",&x1,"x1/D");
		tree->Branch("a1",&a1,"a1/D");
		tree->Branch("y1",&y1,"y1/D");
		tree->Branch("b1",&b1,"b1/D");
	}
	if( (getMWDCR){
		tree->Branch("x2",&x2,"x2/D");
		tree->Branch("a2",&a2,"a2/D");
		tree->Branch("y2",&y2,"y2/D");
		tree->Branch("b2",&b2,"b2/D");
	}
	if( getMWDCS1){
		tree->Branch("s1x",&s1x,"s1x/D");
		tree->Branch("s1a",&s1a,"s1a/D");
		tree->Branch("s1y",&s1y,"s1y/D");
		tree->Branch("s1b",&s1b,"s1b/D");
	}
	if( getpidDS){
		tree->Branch("pidZ",&pidZ,"pidZ/D");
		tree->Branch("pidAoQ",&pidAoQ,"pidAoQ/D");
	}
	if (getvertex) tree->Branch("vertexZ",&vertexZ,"vertexZ/D");
	if( getp2p){
		tree->Branch("E1",&E1,"E1/D");
		tree->Branch("E2",&E2,"E2/D");
		tree->Branch("theta1",&theta1,"theta1/D");
		tree->Branch("theta2",&theta2,"theta2/D");
		tree->Branch("phi1",&phi1,"phi1/D");
		tree->Branch("phi2",&phi2,"phi2/D");
		tree->Branch("Ex",&Ex,"Ex/D");
		tree->Branch("Ex2",&Ex2,"Ex2/D");
		tree->Branch("kMomt",&kMomt,"kMomt/D");
   }


//############################################################################
   
   TFile *f = new TFile(rootfile,"read");
   if( f == 0){
   	printf(" cannot load file . \n");
   	return;
   }
   printf(">> %s <<< is loaded. ----> %s\n",rootfile, savefilename);
   TTree* oldtree = (TTree*)f->Get("tree");
   Int_t totnumEntry = oldtree->GetEntries();
   
   oldtree->SetBranchStatus("*",0);
   
   if (getrunNum) {
   	oldtree->SetBranchStatus("eventheader0",1);   art::TEventHeader *hoge_run = 0; oldtree->SetBranchAddress("eventheader0",&hoge_run);
	}
	if (getcoinReg){
	   oldtree->SetBranchStatus("coinReg",1); art::TCoinRegData *hoge_coinReg;   oldtree->SetBranchAddress("coinReg",&hoge_coinReg);
   }
   if( getgate){
   	oldtree->SetBranchStatus("gate",1); art::TGateArray* hoge_gate = 0; oldtree->SetBranchAddress("gate",&hoge_gate);
	}
	if( getPPAC){
	   oldtree->SetBranchStatus("ppac",1); TClonesArray *hoge_ppac = 0; oldtree->SetBranchAddress("ppac",&hoge_ppac);
	}
	if( getS0img) {
		oldtree->SetBranchStatus("S0img",1); TClonesArray *hoge_S0img = 0; oldtree->SetBranchAddress("S0img",&hoge_S0img);
	}	
   if( getFH9){
   	oldtree->SetBranchStatus("plaV1190_FH9",1); TClonesArray *hoge_fh9 = 0; oldtree->SetBranchAddress("plaV1190_FH9",&hoge_fh9);
   	oldtree->SetBranchStatus("tof_US",1); TClonesArray *hoge_us = 0; oldtree->SetBranchAddress("tof_US",&hoge_us);
   }
   if( getFH9 || getTplaL || getTPlaR || getS0D){
   	oldtree->SetBranchStatus("plaV775",1); TClonesArray *hoge_V775 = 0; oldtree->SetBranchAddress("plaV775",&hoge_V775);
   	oldtree->SetBranchStatus("tof_DS",1); TClonesArray *hoge_ds = 0; oldtree->SetBranchAddress("tof_DS",&hoge_ds);
   }
   if( getMWDCL){
	   oldtree->SetBranchStatus("smwdc_L",1); TClonesArray *hoge_L = 0; oldtree->SetBranchAddress("smwdc_L",&hoge_L);
   }
   if( getMWDCR){
	   oldtree->SetBranchStatus("smwdc_R",1); TClonesArray *hoge_R = 0; oldtree->SetBranchAddress("smwdc_R",&hoge_R);
   }
   if( getMWDCS1){
   	oldtree->SetBranchStatus("smwdc_S1",1); TClonesArray *hoge_S1 = 0; oldtree->SetBranchAddress("smwdc_S1",&hoge_S1);
   }
   if( getvertex){
   	oldtree->SetBranchStatus("vertex",1); TClonesArray *hoge_vertex = 0; oldtree->SetBranchAddress("smwdc_S1",&hoge_vertex);
   }
   if( getTplaL){
		oldtree->SetBranchStatus("tofL",1); TClonesArray *hoge_tofL = 0; oldtree->SetBranchAddress("tofL",&hoge_tofL);
	}
	if( getTplaR){
		oldtree->SetBranchStatus("tofR",1); TClonesArray *hoge_tofR = 0; oldtree->SetBranchAddress("tofR",&hoge_tofR);
	}
	if( getS0D) {
		oldtree->SetBranchStatus("tofS0D",1); TClonesArray *hoge_tofS0D = 0; oldtree->SetBranchAddress("tofS0D",&hoge_tofS0D);   
	}
//   oldtree->SetBranchStatus("tof_D1_t",1); TClonesArray *hoge_d1 = 0; oldtree->SetBranchAddress("tof_D1_t",&hoge_d1);
	if (getpidDS){
	   oldtree->SetBranchStatus("pid_ds",1); art::sh04::TParticleIdentifier *hoge_pid = 0; oldtree->SetBranchAddress("pid_ds",&hoge_pid);
   }
   if( getp2p){
	   oldtree->SetBranchStatus("p2p",1); art::sh04::TP2PKinematicsData *hoge_p2p = 0; oldtree->SetBranchAddress("p2p",&hoge_p2p);
   }
//   TBranch *branch = oldtree->GetBranch("smwdc_L"); TClonesArray *hoge_L = 0; branch->SetAddress(&hoge_L); branch->SetAutoDelete(kTRUE);
  
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
   for( eventID = firstEntry; eventID < endEntry; eventID ++){
      // clear memory
      if (getrunNum) { delete hoge_run; hoge_run = 0; }
      if (getgate) { delete hoge_gate; hoge_gate = 0; }
      if (getS0img) { delete hoge_S0img; hoge_S0img = 0; }
      if (getFH9) { 
      	delete hoge_fh9; hoge_fh9 = 0;
      	delete hoge_us; hoge_us = 0; 
   	}
      if (getTplaL || getTplaR || getS0D) { delete hoge_V775; hoge_V775 = 0; }
      if (getMWDCL) { delete hoge_L; hoge_L = 0; } 
      if (getMWDCR) { delete hoge_R; hoge_R = 0; }
      if (getMWDCS1) { delete hoge_S1; hoge_S1 = 0; }
      if (getvertex) { delete hoge_vertex; hoge_vertex = 0; }
      if (getTplaL) { delete hoge_tofL; hoge_tofL = 0; }
      if (getTplaR) { delete hoge_tofR; hoge_tofR = 0; }
      if (getS0D) { delete hoge_tofS0D; hoge_tofS0D = 0; }
      if (getpidDS) { delete hoge_pid; hoge_pid = 0; }
      if (getp2p) { delete hoge_p2p; hoge_p2p = 0; }
      oldtree->GetEntry(eventID,0);
      
//----------------Get Event Number
		if( getrunNum){
     		runNum = -100;
      	runNum = hoge_run->GetRunNumber();
		}
//--------------- Get gate
      if( gate23F && !hoge_gate->Test(0)) continue;
      
      if( getgate){
      	gate = 0;
      	if( hoge_gate->Test(9)) gate = 1;
      	if( hoge_gate->Test(11)) gate = 2;
      }
//--------------Get coinReg, CoinGate is a 8 bit data, xxxxdcba, a = F3 frigger, b = beam trigger, c = ppcoin 
     // 0 = F3, 1 = FH9, 2=ppcoin, 3 = ND coin, 4 = ppsingle, 5 = ND single, 6 = ND cosmic
      //coinReg = hoge_coinReg->GetQuality() & 7;    
      //if( coinReg != 4 ) continue;
      
//----------------Get tof and charge upstream V1190
      if( getFH9){
			tofFH9 = kInvalidD; 
			QFH9 = kInvalidD;      
		   Int_t nHit = hoge_us -> GetEntriesFast();
		   for( Int_t p = 0; p < nHit; p++){
		      //tofusdata = (art::TTimeDifference*)hoge_us->At(p) ;
		      Int_t HitID  = ((art::TTimeDifference*)hoge_us->At(p))->GetHitID();
		      tofFH9  = ((art::TTimeDifference*)hoge_us->At(p))->GetTiming();
		      QFH9 = ((art::TTwoSidedPlasticData*) hoge_fh9->At(HitID-1))->GetCharge();
		   }
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
/*
	  nHit = hoge_tofL->GetEntriesFast();
      for (Int_t p = 0; p < nHit; p++){
         tof1 = ((art::TTimeDifference*)hoge_tofL->At(p))->GetTiming() ;
         //tof1 = tofL->GetTiming();
      }


	  nHit = hoge_tofR->GetEntriesFast();
      for (Int_t p = 0; p < nHit; p++){
         tof2 = ((art::TTimeDifference*)hoge_tofR->At(p))->GetTiming() ;
      }
*/

		if( getTplaL || getTplaR || getS0D){
			Q1 = kInvalidD;
			Q2 = kInvalidD;
			QS0D = kInvalidD;
		   nHit = hoge_V775->GetEntriesFast();
		   for (Int_t p = 0; p < nHit; p++){
		   	Int_t id = ((art::TTimeDifference*)hoge_V775->At(p))->GetID() ;
		      if( id == 0) Q1 = ((art::TTimeDifference*)hoge_V775->At(p))->GetCharge() ;
		      if( id == 0) Q1 = ((art::TTimeDifference*)hoge_V775->At(p))->GetCharge() ;
		   }
		}
		
		
	   tofS0D = kInvalidD;
		nHit = hoge_tofS0D->GetEntriesFast();
		for (Int_t p = 0; p < nHit; p++){
         tofS0D = ((art::TTimeDifference*)hoge_tofS0D->At(p))->GetTiming() ;
      }
    
/*    	nHit = hoge_tofD1->GetEntriesFast();
      for (Int_t p = 0; p < nHit; p++){
         tofS1 = ((art::TTimeDifference*)hoge_tofD1->At(p))->GetTiming() ;
      }
    
*/    
//---------Get S0img image, should be one 1 instance
		s0x = kInvalidD;
		s0y = kInvalidD;
      nHit = hoge_S0img->GetEntriesFast();
      //Double_t s0a, s0b;
      for( Int_t p = 0; p < nHit; p++){
         //xy = (art::TMWDCTrackingResult*)hoge_S0img->At(p);
         //track = (art::TTrack*)xy->GetTrack();
         track = (art::TTrack*) ((art::TMWDCTrackingResult*)hoge_S0img->At(p))->GetTrack();
         s0x = track->GetX();
         s0y = track->GetY();
         //s0a = trackS0->GetA();
         //s0b = trackS0->GetB();
      }      

      if( TMath::IsNaN(s0x)) continue;
      
//---------Get SMWDC image, should be one 1 instance
      x1 = kInvalidD;
		y1 = kInvalidD;
		a1 = kInvalidD;
		b1 = kInvalidD;
      nHit = hoge_L->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         //xy = (art::TMWDCTrackingResult*)hoge_L->At(p);
         //NValidPlane1 = xy1 -> GetNPlaneValid();
         //Int_t TrackingID1  = ((art::TMWDCTrackingResult*)hoge_L->At(p))-> GetTrackingID();
         track = (art::TTrack*)((art::TMWDCTrackingResult*)hoge_L->At(p))->GetTrack();
         x1 = track->GetX();
         y1 = track->GetY();
         a1 = track->GetA();
         b1 = track->GetB();
      }
      if (TMath::IsNaN(x1)) continue;

      x2 = kInvalidD;
		y2 = kInvalidD;
		a2 = kInvalidD;
		b2 = kInvalidD;
      nHit = hoge_R->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         //art::TMWDCTrackingResult * xy2 = (art::TMWDCTrackingResult*)hoge_R->At(p);
         //NValidPlane2 = xy2 -> GetNPlaneValid();
         //Int_t TrackingID2  = xy2 -> GetTrackingID();
         //Double_t ex2 = xy2->GetSigma(0);
         //Double_t ea2 = xy2->GetSigma(1);
         //art::TTrack * track2 = (art::TTrack*)xy2->GetTrack();
         //Int_t TrackingID2  = ((art::TMWDCTrackingResult*)hoge_R->At(p))-> GetTrackingID();
         track = (art::TTrack*)((art::TMWDCTrackingResult*)hoge_R->At(p))->GetTrack();
         
         x2 = track->GetX();
         y2 = track->GetY();
         a2 = track->GetA();
         b2 = track->GetB();
      }
      
      if (TMath::IsNaN(x2)) continue;
      
      s1x = kInvalidD;
		s1y = kInvalidD;
		s1a = kInvalidD;
		s1b = kInvalidD;
      nHit = hoge_S1->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         Int_t TrackingIDS1  = ((art::TMWDCTrackingResult*)hoge_S1->At(p))-> GetTrackingID();
         track = (art::TTrack*)((art::TMWDCTrackingResult*)hoge_S1->At(p))->GetTrack();
         s1x = track->GetX();
         s1y = track->GetY();
         s1a = track->GetA();
         s1b = track->GetB();
      }
      
      if (TMath::IsNaN(s1x)) continue;
      
//--------------- Get vertex , beamZ
      vertexZ = kInvalidD;
      nHit = hoge_vertex->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
        //art::TTrack * ver = (art::TTrack*)hoge_vertex->At(p);
        //vertexX = ver->GetX();
        //vertexY = ver->GetY();
        vertexZ = ((art::TTrack*)hoge_vertex->At(p))->GetZ();
      }
      
      if( abs(vertexZ)>500) continue;

/*
      nHit = hoge_beamZ->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
        art::sh04::TBeamZ * beamZ = (art::sh04::TBeamZ*)hoge_beamZ->At(p);
        beamZ1 = beamZ->GetL();
        beamZ2 = beamZ->GetR();
        wbeamZ = beamZ->GetAverage();
      }
*/

//--------------- Get pid_ds
		pidZ = hoge_pid->GetZ();
		pidAoQ = hoge_pid->GetAOQ();
		
		if( abs(pidZ-10)>10 ) continue;
		if( abs(pidAoQ-2.5)>3 ) continue;

//--------------- Get p2p
      Ex = hoge_p2p->GetSp() -13.26;
      Ex2 = hoge_p2p->GetSp2()-13.26;
      
      if( abs(Ex)>200 ) continue;

      E1 = hoge_p2p->GetRecoilL()->E()-938.272;
      E2 = hoge_p2p->GetRecoilR()->E()-938.272;      
      
      if( E1 > 1000 || E2 > 1000) continue;

      theta1 = hoge_p2p->GetRecoilL()->Theta()*TMath::RadToDeg();
      theta2 = hoge_p2p->GetRecoilR()->Theta()*TMath::RadToDeg();

      phi1 = hoge_p2p->GetRecoilL()->Phi()*TMath::RadToDeg();
      phi2 = hoge_p2p->GetRecoilR()->Phi()*TMath::RadToDeg();


      
      kMomt = hoge_p2p->GetResidual()->P();

//----------- Fill        
      savefile->cd(); //set focus on this file
      tree->Fill();  
      
//------------Clock      
      clock.Stop("timer");
      Double_t time = clock.GetRealTime("timer");
      clock.Start("timer");
      
      if ( !shown ) {
         if (fmod(time, 10) < 1 ){
            savefile->cd();
			   tree->Write();
            printf( "%10d[%2d%%](#%2d) |%3d min %5.2f sec | expect:%6.1fmin , tree:%10d, %6.2f MB\n", 
            eventID, 
            TMath::Nint((eventID+1-firstEntry)*100./nEntries),
            runNum,
            TMath::Floor(time/60), time - TMath::Floor(time/60)*60,
            nEntries*time/(eventID+1-firstEntry)/60.,
            tree->GetEntries(),
            tree->GetZipBytes()/1024./1024.);
            shown = 1;
            
            

         }
      }else{
         if (fmod(time, 10) > 9 ){
            shown = 0;
         }
      }
      
      
   }
  
   savefile->cd();
   tree->Write();
   savefile->Close();
   delete savefile;
   f->Close();
   delete f;
   
   clock.Stop("timer");
   printf("============ finished|%10.3f sec --> %s\n",clock.GetRealTime("timer"),savefilename);

	gROOT->Reset();
   return ;
}
