// Trim the root file, extract essentail data. For quicker analysis
#include "constant.h"
//#include "RelCalculator.h"

void PostTree() {
   
//############################################################################   
   const char* savefilename="P_23F_0205_all.root";
   //const char* rootfile="Data/phys14_1_43.root";
   const char* rootfile="23F_0205_all.root";
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
   Double_t s0x, s0y;
   // get tof and charge upstream
   Double_t tof_usV1190, Q_us;
   //Double_t tof_usV775;
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

   // Phsyics
   Double_t E1, E2;
   Double_t theta1, theta2;
   Double_t phi1, phi2;
   //Double_t beamZ1, beamZ2, wbeamZ;
   Double_t vertexZ;
   Double_t Ex;
   Double_t Ex2; // Sp2 - 13.26;
   Double_t k; // redisual momentum


   TFile *savefile = new TFile(savefilename,"recreate");
   TTree *recoil; 
   recoil = new TTree("recoil","recoil");
   recoil->Branch("runNum", &runNum, "runNum/I");
   recoil->Branch("eventID",&eventID,"eventID/I");
   recoil->Branch("gate",&gate,"gate/I");
//   recoil->Branch("coinReg",&coinReg,"coinReg/I");
   recoil->Branch("tof_usV1190",&tof_usV1190,"tof_usV1190/D");
   //recoil->Branch("tof_usV775",&tof_usV775,"tof_usV775/D");
   recoil->Branch("Q_us",&Q_us,"Q_us/D");
   recoil->Branch("s0x", &s0x, "s0x/D");
   recoil->Branch("s0y", &s0y, "s0y/D");
//   recoil->Branch("ppacX", &ppacX, "ppacX/D");
//   recoil->Branch("Brho",&Brho, "Brho/D");
//   recoil->Branch("TKAppac",&TKAppac,"TKAppac/D");
//   recoil->Branch("TKAV775",&TKAV775,"TKAV775/D");
//   recoil->Branch("tofS0D", &tofS0D, "tofS0D/D");
//   recoil->Branch("QS0D", &QS0D, "QS0D/D");
//   recoil->Branch("tof1",&tof1,"tof1/D");
//   recoil->Branch("tof2",&tof2,"tof2/D");
//   recoil->Branch("Q1",&Q1,"Q1/D");
//   recoil->Branch("Q2",&Q2,"Q2/D");
   recoil->Branch("tofS1",&tofS1,"tofS1/D");
//   recoil->Branch("QS1",&QS1,"QS1/D");
   recoil->Branch("x1",&x1,"x1/D");
   recoil->Branch("a1",&a1,"a1/D");
   recoil->Branch("y1",&y1,"y1/D");
   recoil->Branch("b1",&b1,"b1/D");
   recoil->Branch("x2",&x2,"x2/D");
   recoil->Branch("a2",&a2,"a2/D");
   recoil->Branch("y2",&y2,"y2/D");
   recoil->Branch("b2",&b2,"b2/D");
   recoil->Branch("s1x",&s1x,"s1x/D");
   recoil->Branch("s1a",&s1a,"s1a/D");
   recoil->Branch("s1y",&s1y,"s1y/D");
   recoil->Branch("s1b",&s1b,"s1b/D");
   recoil->Branch("pidZ",&pidZ,"pidZ/D");
   recoil->Branch("pidAoQ",&pidAoQ,"pidAoQ/D");
   recoil->Branch("E1",&E1,"E1/D");
   recoil->Branch("E2",&E2,"E2/D");
   recoil->Branch("theta1",&theta1,"theta1/D");
   recoil->Branch("theta2",&theta2,"theta2/D");
   recoil->Branch("phi1",&phi1,"phi1/D");
   recoil->Branch("phi2",&phi2,"phi2/D");
   recoil->Branch("vertexZ",&vertexZ,"vertexZ/D");
   recoil->Branch("Ex",&Ex,"Ex/D");
   recoil->Branch("Ex2",&Ex2,"Ex2/D");
   recoil->Branch("k",&k,"k/D");
   


//############################################################################
   
   TFile *f = new TFile(rootfile,"read");
   if( f == 0){
   	printf(" cannot load file . \n");
   	return;
   }
   printf(">> %s <<< is loaded. ----> %s\n",rootfile, savefilename);
   TTree* tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree.GetEntries();
   
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("eventheader0",1);
//   tree->SetBranchStatus("coinReg",1);
   tree->SetBranchStatus("gate",1);
   //tree->SetBranchStatus("ppac",1);
   tree->SetBranchStatus("S0img",1);
   tree->SetBranchStatus("plaV1190_FH9",1); //get charge for PID
   tree->SetBranchStatus("tof_US",1);
   //tree->SetBranchStatus("tof_D1",1);
   //tree->SetBranchStatus("plaV775",1);    //get charge and time
   tree->SetBranchStatus("smwdc_L",1);
   tree->SetBranchStatus("smwdc_R",1);
   tree->SetBranchStatus("smwdc_S1",1);
   tree->SetBranchStatus("vertex",1);
   //tree->SetBranchStatus("tofL",1);
   //tree->SetBranchStatus("tofR",1);
   //tree->SetBranchStatus("tofS0D",1);   
   tree->SetBranchStatus("tof_D1_t",1);
   tree->SetBranchStatus("pid_ds",1);
   tree->SetBranchStatus("p2p",1);
   
//   art::TCoinRegData *hoge_coinReg;
   art::TGateArray* hoge_gate = 0;
   art::TEventHeader *hoge_run = 0;
   //TClonesArray *hoge_ppac;
   TClonesArray *hoge_S0img = 0;
   TClonesArray *hoge_fh9 = 0, *hoge_us = 0 , *hoge_L = 0, *hoge_R = 0, *hoge_S1 = 0 ; //*hoge_V775,
   TClonesArray *hoge_vertex = 0, *hoge_tofD1 = 0;//, *hoge_tofL, *hoge_tofR, *hoge_tofS0D, *hoge_nyoki;
   art::sh04::TParticleIdentifier *hoge_pid = 0;
   art::sh04::TP2PKinematicsData *hoge_p2p = 0;
   
   tree->SetBranchAddress("eventheader0",&hoge_run);
//   tree->SetBranchAddress("coinReg",&hoge_coinReg);
   tree->SetBranchAddress("gate",&hoge_gate);
   //tree->SetBranchAddress("ppac",&hoge_ppac);
   tree->SetBranchAddress("S0img",&hoge_S0img);
   tree->SetBranchAddress("plaV1190_FH9",&hoge_fh9);
   tree->SetBranchAddress("tof_US",&hoge_us);
   //tree->SetBranchAddress("plaV775",&hoge_V775);
   tree->SetBranchAddress("smwdc_L",&hoge_L);
   tree->SetBranchAddress("smwdc_R",&hoge_R);
   tree->SetBranchAddress("smwdc_S1",&hoge_S1);
   //tree->SetBranchAddress("beamZ",&hoge_beamZ);
   tree->SetBranchAddress("vertex",&hoge_vertex);
   //tree->SetBranchAddress("tofL",&hoge_tofL);
   //tree->SetBranchAddress("tofR",&hoge_tofR);
   //tree->SetBranchAddress("tofS0D",&hoge_tofS0D);
   tree->SetBranchAddress("tof_D1_t",&hoge_tofD1);
   //tree->SetBranchAddress("nyoki",&hoge_nyoki);
   tree->SetBranchAddress("pid_ds",&hoge_pid);
   tree->SetBranchAddress("p2p",&hoge_p2p);
   
  /* TBranch *branch = tree->GetBranch("smwdc_L");
   branch->SetAddress(&hoge_L);
   branch->SetAutoDelete(kTRUE);*/
   

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
   
   art::TTrack * track;
   
//##############################################################################
   for( eventID = firstEntry; eventID < endEntry; eventID ++){
      // clear memory
      /*delete hoge_run; hoge_run = 0;
      delete hoge_gate; hoge_gate = 0;
      delete hoge_S0img; hoge_S0img = 0;
      delete hoge_fh9; hoge_fh9 = 0;
      delete hoge_us; hoge_us = 0;
      delete hoge_L; hoge_L = 0;
      delete hoge_R; hoge_R = 0;
      delete hoge_S1; hoge_S1 = 0;
      delete hoge_vertex; hoge_vertex = 0;
      delete hoge_pid; hoge_pid = 0;
      delete hoge_p2p; hoge_p2p = 0;*/
      tree->GetEntry(eventID,0);
      
      // initialization
      //coinReg = 0;
      tof_usV1190 = kInvalidD; Q_us = kInvalidD;
      //tof1  = kInvalidD; Q1 = kInvalidD; 
      //tof2  = kInvalidD; Q2 = kInvalidD;
      //tdiff1 = kInvalidD; tdiff2 = kInvalidD;
      //tofS0D= kInvalidD; QS0D = kInvalidD;
      
//----------------Get Event Number
      runNum = -100;
      runNum = hoge_run->GetRunNumber();

//--------------- Get gate

/*	  Int_t Ngate = hoge_gate->GetSize();
	  gate = 0;
      for ( Int_t i = 0; i < Ngate; i++){
      	if( hoge_gate->Test(i)) gate += TMath::Power(2,i);
      }
      */
      
      gate = 0;
      if( hoge_gate->Test(9)) gate = 1;
      if( hoge_gate->Test(11)) gate = 2;
      
      
//--------------Get coinReg, CoinGate is a 8 bit data, xxxxdcba, a = F3 frigger, b = beam trigger, c = ppcoin 
     // 0 = F3, 1 = FH9, 2=ppcoin, 3 = ND coin, 4 = ppsingle, 5 = ND single, 6 = ND cosmic
      //coinReg = hoge_coinReg->GetQuality() & 7;    
      //if( coinReg != 4 ) continue;
      
//----------------Get tof and charge upstream V1190
		tof_usV1190 = kInvalidD; Q_us = kInvalidD;      
      Int_t nHit = hoge_us -> GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         //tofusdata = (art::TTimeDifference*)hoge_us->At(p) ;
         Int_t HitID  = ((art::TTimeDifference*)hoge_us->At(p))->GetHitID();
         tof_usV1190  = ((art::TTimeDifference*)hoge_us->At(p))->GetTiming();
         Q_us = ((art::TTwoSidedPlasticData*) hoge_fh9->At(HitID-1))->GetCharge();
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


	  nHit = hoge_tofS0D->GetEntriesFast();
      for (Int_t p = 0; p < nHit; p++){
         tofS0D = ((art::TTimeDifference*)hoge_tofS0D->At(p))->GetTiming() ;
      }
    
*/  
    	nHit = hoge_tofD1->GetEntriesFast();
      for (Int_t p = 0; p < nHit; p++){
         tofS1 = ((art::TTimeDifference*)hoge_tofD1->At(p))->GetTiming() ;
      }
    
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


      
      k = hoge_p2p->GetResidual()->P();

//----------- Fill        
      savefile->cd(); //set focus on this file
      recoil->Fill();  
      
//------------Clock      
      clock.Stop("timer");
      Double_t time = clock.GetRealTime("timer");
      clock.Start("timer");
      
      if ( !shown ) {
         if (fmod(time, 10) < 1 ){
            savefile->cd();
			   recoil->Write();
            printf( "%10d[%2d%%](#%2d) |%3d min %5.2f sec | expect:%6.1fmin , recoil:%10d, %6.2f MB\n", 
            eventID, 
            TMath::Nint((eventID+1-firstEntry)*100./nEntries),
            runNum,
            TMath::Floor(time/60), time - TMath::Floor(time/60)*60,
            nEntries*time/(eventID+1-firstEntry)/60.,
            recoil->GetEntries(),
            recoil->GetZipBytes()/1024./1024.);
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
   delete savefile;
   f->Close();
   delete f;
   
   clock.Stop("timer");
   printf("============ finished|%10.3f sec --> %s\n",clock.GetRealTime("timer"),savefilename);

	gROOT->Reset();
   return ;
}
