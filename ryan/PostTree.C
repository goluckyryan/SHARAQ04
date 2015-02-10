// Trim the root file, extract essentail data. For quicker analysis
#include "constant.h"
//#include "RelCalculator.h"

void PostTree() {
   
//############################################################################   
	const char* savefilename="P_23F_0208.root";
	const char* rootfile="23F_0208.root";
	
	Bool_t allentry  = 1;
	Int_t firstEntry = 0;
	Int_t nEntries=500000;

	Bool_t gate23F = 1;

   
//############################################################################
	TBenchmark clock;
	clock.Reset();
	clock.Start("timer");
	Bool_t shown = 0;

//================ Tree branch
	Int_t eventID;
	//  runNumber
	Int_t runNum;
	// gate
	Int_t gate;
	// S0img
	Double_t s0x, s0y;
	// get tof and charge upstream
	Double_t tofFH9, QFH9;
	//downstream V775
	Double_t tofS0D, QS0D;
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
	//carbon
	Double_t Exc, Ex2c,kMomtc;


	TFile *savefile = new TFile(savefilename,"recreate");
	TTree *tree = new TTree("tree","tree");

	tree->Branch("eventID",&eventID,"eventID/I");   
	tree->Branch("runNum", &runNum, "runNum/I");
	tree->Branch("gate",&gate,"gate/I");
	
	tree->Branch("tofFH9",&tofFH9,"tofFH9/D");
	tree->Branch("QFH9",&QFH9,"QFH9/D");
	
	tree->Branch("s0x", &s0x, "s0x/D");
	tree->Branch("s0y", &s0y, "s0y/D");
	
	tree->Branch("tofS0D", &tofS0D, "tofS0D/D");
	tree->Branch("QS0D", &QS0D, "QS0D/D");
	/*
	tree->Branch("x1",&x1,"x1/D");
	tree->Branch("a1",&a1,"a1/D");
	tree->Branch("y1",&y1,"y1/D");
	tree->Branch("b1",&b1,"b1/D");
	
	tree->Branch("x2",&x2,"x2/D");
	tree->Branch("a2",&a2,"a2/D");
	tree->Branch("y2",&y2,"y2/D");
	tree->Branch("b2",&b2,"b2/D");
	*/
	tree->Branch("s1x",&s1x,"s1x/D");
	tree->Branch("s1a",&s1a,"s1a/D");
	tree->Branch("s1y",&s1y,"s1y/D");
	tree->Branch("s1b",&s1b,"s1b/D");
	
	tree->Branch("pidZ",&pidZ,"pidZ/D");
	tree->Branch("pidAoQ",&pidAoQ,"pidAoQ/D");
	
	tree->Branch("vertexZ",&vertexZ,"vertexZ/D");
	
	tree->Branch("E1",&E1,"E1/D");
	tree->Branch("E2",&E2,"E2/D");
	tree->Branch("theta1",&theta1,"theta1/D");
	tree->Branch("theta2",&theta2,"theta2/D");
	tree->Branch("phi1",&phi1,"phi1/D");
	tree->Branch("phi2",&phi2,"phi2/D");
	tree->Branch("Ex",&Ex,"Ex/D");
	tree->Branch("Ex2",&Ex2,"Ex2/D");
	tree->Branch("kMomt",&kMomt,"kMomt/D");

	tree->Branch("Exc",&Exc,"Exc/D");
	tree->Branch("Ex2c",&Ex2c,"Ex2c/D");
	tree->Branch("kMomtc",&kMomtc,"kMomtc/D");


//############################################################################
   
   TFile *fff = new TFile(rootfile,"read");
   if( fff == 0){
   	printf(" cannot load file . \n");
   	return;
   }
   printf(">> %s <<< is loaded. ----> %s\n",rootfile, savefilename);
   TTree* oldtree = 0;
   fff->GetObject("tree", oldtree);
   
   //TTree* oldtree = (TTree*)fff->Get("tree");
   Int_t totnumEntry = oldtree->GetEntries();
   
   oldtree->SetBranchStatus("*",0);
   
	oldtree->SetBranchStatus("eventheader0",1);   art::TEventHeader *hoge_run = 0; oldtree->SetBranchAddress("eventheader0",&hoge_run);
	oldtree->SetBranchStatus("gate",1); art::TGateArray* hoge_gate = 0; oldtree->SetBranchAddress("gate",&hoge_gate);
	oldtree->SetBranchStatus("S0img",1); TClonesArray *hoge_S0img = 0; oldtree->SetBranchAddress("S0img",&hoge_S0img);
	oldtree->SetBranchStatus("plaV1190_FH9",1); TClonesArray *hoge_fh9 = 0; oldtree->SetBranchAddress("plaV1190_FH9",&hoge_fh9);
	oldtree->SetBranchStatus("tof_US",1); TClonesArray *hoge_us = 0; oldtree->SetBranchAddress("tof_US",&hoge_us);
	oldtree->SetBranchStatus("plaV775",1); TClonesArray *hoge_V775 = 0; oldtree->SetBranchAddress("plaV775",&hoge_V775);
   oldtree->SetBranchStatus("tofS0D",1); TClonesArray *hoge_tofS0D = 0; oldtree->SetBranchAddress("tofS0D",&hoge_tofS0D);   
   //oldtree->SetBranchStatus("smwdc_L",1); TClonesArray *hoge_L = 0; oldtree->SetBranchAddress("smwdc_L",&hoge_L);
   //oldtree->SetBranchStatus("smwdc_R",1); TClonesArray *hoge_R = 0; oldtree->SetBranchAddress("smwdc_R",&hoge_R);
	oldtree->SetBranchStatus("smwdc_S1",1); TClonesArray *hoge_S1 = 0; oldtree->SetBranchAddress("smwdc_S1",&hoge_S1);
	oldtree->SetBranchStatus("vertex",1); TClonesArray *hoge_vertex = 0; oldtree->SetBranchAddress("vertex",&hoge_vertex);
	oldtree->SetBranchStatus("pid_ds",1); art::sh04::TParticleIdentifier *hoge_pid = 0; oldtree->SetBranchAddress("pid_ds",&hoge_pid);
   oldtree->SetBranchStatus("p2p",1); art::sh04::TP2PKinematicsData *hoge_p2p = 0; oldtree->SetBranchAddress("p2p",&hoge_p2p);
   oldtree->SetBranchStatus("p2p_c",1); art::sh04::TP2PKinematicsData *hoge_p2pc = 0; oldtree->SetBranchAddress("p2p_c",&hoge_p2pc);

   //TBranch *branch = oldtree->GetBranch("smwdc_L"); TClonesArray *hoge_L = 0; branch->SetAddress(&hoge_L); branch->SetAutoDelete(kTRUE);
  
//############################################################################   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   gROOT->ProcessLine(".!date");

	//oldtree->SetAutoFlush(1);   
	//oldtree->SetCacheSize(30*1024);
   //printf(" set oldTree Auto Flush %d \n", oldtree->GetAutoFlush()); 
   //printf(" set oldTree Cache size %d \n", oldtree->GetCacheSize()); 
   
   printf(" file cache dir %s \n", fff->GetCacheFileDir()); 
   
   
   
//##############################################################################
	art::TTrack* track = 0;

   for( eventID = firstEntry; eventID < endEntry; eventID ++){
		//delete hoge_run; 		hoge_run = 0; 
   	//delete hoge_gate; hoge_gate = 0; 
      //delete hoge_S0img;       hoge_S0img = 0;      
		//delete hoge_fh9; hoge_fh9 = 0;
		//delete hoge_us; hoge_us = 0; 
		//delete hoge_V775; 		hoge_V775 = 0; 
		//delete hoge_tofS0D; hoge_tofS0D = 0; 
		//delete hoge_L; hoge_L = 0; 
      //delete hoge_R; hoge_R = 0;
      //delete hoge_S1; hoge_S1 = 0;
		//delete hoge_pid; hoge_pid = 0;
		//delete hoge_p2p; hoge_p2p = 0; 
      oldtree->GetEntry(eventID,0);
      
//----------------Get Event Number
		runNum = -100;
		runNum = hoge_run->GetRunNumber();

//--------------- Get gate
      if( gate23F && !hoge_gate->Test(0)) continue;      
   	gate = 0;
   	if( hoge_gate->Test(9)) gate = 1;
   	if( hoge_gate->Test(11)) gate = 2;
   	//delete hoge_gate; hoge_gate = 0; 
   	
//---------Get S0img image, should be one 1 instance
		s0x = kInvalidD;
		s0y = kInvalidD;
      Int_t nHit = hoge_S0img->GetEntriesFast();
      //Double_t s0a, s0b;
      for( Int_t p = 0; p < nHit; p++){
         track = (art::TTrack*) ((art::TMWDCTrackingResult*)hoge_S0img->At(p))->GetTrack();
         s0x = track->GetX();
         s0y = track->GetY();
         //s0a = trackS0->GetA();
         //s0b = trackS0->GetB();
      }
      track = 0;
      if( TMath::IsNaN(s0x)) continue;     
      
//----------------Get tof and charge upstream V1190

		tofFH9 = kInvalidD; 
		QFH9 = kInvalidD;      
		Int_t nHit = hoge_us -> GetEntriesFast();
		for( Int_t p = 0; p < nHit; p++){
			//tofusdata = (art::TTimeDifference*)hoge_us->At(p) ;
			Int_t HitID  = ((art::TTimeDifference*)hoge_us->At(p))->GetHitID();
			tofFH9  = ((art::TTimeDifference*)hoge_us->At(p))->GetTiming();
			QFH9 = ((art::TTwoSidedPlasticData*) hoge_fh9->At(HitID-1))->GetCharge();
		}

//-------------------- get S0D
		QS0D = kInvalidD;
		nHit = hoge_V775->GetEntriesFast();
		for (Int_t p = 0; p < nHit; p++){
			Int_t id = ((art::TTwoSidedPlasticData*)hoge_V775->At(p))->GetID() ;
			if( id != 4 ) continue; 
			tofS0D = ((art::TTwoSidedPlasticData*)hoge_V775->At(p))->GetCharge() ;
		}

		tofS0D = kInvalidD;
		nHit = hoge_tofS0D->GetEntriesFast();
		for (Int_t p = 0; p < nHit; p++){
			tofS0D = ((art::TTimeDifference*)hoge_tofS0D->At(p))->GetTiming() ;
		}		
      
//---------Get SMWDC image, should be one 1 instance
/*
      x1 = kInvalidD;
		y1 = kInvalidD;
		a1 = kInvalidD;
		b1 = kInvalidD;
      nHit = hoge_L->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         track = (art::TTrack*)((art::TMWDCTrackingResult*)hoge_L->At(p))->GetTrack();
         x1 = track->GetX();
         y1 = track->GetY();
         a1 = track->GetA();
         b1 = track->GetB();
      }
      //track = 0;
      if (TMath::IsNaN(x1)) continue;

      x2 = kInvalidD;
		y2 = kInvalidD;
		a2 = kInvalidD;
		b2 = kInvalidD;
      nHit = hoge_R->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         track = (art::TTrack*)((art::TMWDCTrackingResult*)hoge_R->At(p))->GetTrack();
         x2 = track->GetX();
         y2 = track->GetY();
         a2 = track->GetA();
         b2 = track->GetB();
      }
      //track = 0;
      if (TMath::IsNaN(x2)) continue;
*/      
      s1x = kInvalidD;
		s1y = kInvalidD;
		s1a = kInvalidD;
		s1b = kInvalidD;
      Int_t nHit = hoge_S1->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         //Int_t TrackingIDS1  = ((art::TMWDCTrackingResult*)hoge_S1->At(p))-> GetTrackingID();
         track = (art::TTrack*)((art::TMWDCTrackingResult*)hoge_S1->At(p))->GetTrack();
         s1x = track->GetX();
         s1y = track->GetY();
         s1a = track->GetA();
         s1b = track->GetB();
      }
      //track = 0;
      
      //printf("%d pass %fff\n", eventID, s1x); 
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
      //delete hoge_vertex; hoge_vertex = 0;  
      if( abs(vertexZ)>500) continue;


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
      
      Exc = hoge_p2pc->GetSp() -13.26;
      Ex2c = hoge_p2pc->GetSp2()-13.26;
      kMomtc = hoge_p2pc->GetResidual()->P();

//----------- Fill        
      savefile->cd(); //set focus on this file
      tree->Fill();  
      
//------------Clock      
      clock.Stop("timer");
      Double_t time = clock.GetRealTime("timer");
      clock.Start("timer");
      
      if ( !shown ) {
         if (fmod(time, 10) < 1 ){
            printf( "%10d[%2d%%](#%2d) |%3d min %5.2f sec | expect:%6.1fmin , tree:%10d, %6.2f MB\n", 
            eventID, 
            TMath::Nint((eventID+1-firstEntry)*100./nEntries),
            runNum,
            TMath::Floor(time/60), time - TMath::Floor(time/60)*60,
            nEntries*time/(eventID+1-firstEntry)/60.,
            tree->GetEntries(),
            tree->GetZipBytes()/1024./1024.);
            shown = 1;
            
				printf(" %d , %d MB\n", fff->GetCacheRead(), fff->GetFileBytesRead()/1024/1024 );
				fff->Flush();
				//oldtree->PrintCacheStats();
				//tree->PrintCacheStats();
				
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
   fff->Close();
   delete fff;
   
   
   clock.Stop("timer");
   printf("============ finished|%10.3f sec --> %s\n",clock.GetRealTime("timer"),savefilename);

	gROOT->Reset();
   return ;
}
