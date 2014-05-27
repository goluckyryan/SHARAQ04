#include "ryan/constant.h"
#include "ryan/RelCalculator.h"
#include "ryan/TBeamData.h"
#include "ryan/TRecoilData.h"

void simpleAna() {
//############################################################################   
   const char* savefilename="test_R.root";
   const char* rootfile="PrimaryData/phys14Up.root";
   TBeamData *beam = new TBeamData("14O");
   Int_t detectorID = 2; // 1=L , 2=R
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=10000000;
   
   beam->Print();
   Double_t Principle_tof = tofByBrho(L_F3FH9,beam->fBrho, beam->fMass, beam->fZ);
   printf("---- Principle Tof: %10.3f ns\n", Principle_tof);
//############################################################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;

//================ Tree branch
   Int_t eventID;
   // runNumber
   Int_t runNum;
   //downstream V775
   Double_t tof;
   Double_t ts;
   Double_t t1, Q1;
   Double_t t2, Q2;
   // SMWDC X Y
   Double_t x1, y1, a1, b1; // for smwdc-L
   
   TRecoilData * recoildata = new TRecoilData();
   
   // Phsyics
   Double_t E1;

   TFile *savefile = new TFile(savefilename,"recreate");
   TTree *recoil; 
   recoil = new TTree("recoil","recoil");
   recoil->Branch("runNum", &runNum, "runNum/I");
   recoil->Branch("eventID",&eventID,"eventID/I");
   recoil->Branch("tof",&tof,"tof/D");
   recoil->Branch("ts",&ts,"ts/D");
   recoil->Branch("t1",&t1,"t1/D");
   recoil->Branch("t2",&t2,"t2/D");
   recoil->Branch("Q1",&Q1,"Q1/D");
   recoil->Branch("Q2",&Q2,"Q2/D");
   recoil->Branch("x1",&x1,"x1/D");
   recoil->Branch("a1",&a1,"a1/D");
   recoil->Branch("y1",&y1,"y1/D");
   recoil->Branch("b1",&b1,"b1/D");
   recoil->Branch("E1",&E1,"E1/D");

//############################################################################
   art::TEventHeader *hoge_run;
   TClonesArray *hoge_V775, *hoge_smwdc;
   TFile *f1 = new TFile (rootfile); 
   TTree *tree = (TTree*)f1->Get("tree");
   printf(">> %s <<< is loaded. ----> %s\n",rootfile, savefilename);
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("eventheader",1);
   tree->SetBranchStatus("plaV775",1);    //get charge and time

   tree->SetBranchAddress("eventheader",&hoge_run);
   tree->SetBranchAddress("plaV775",&hoge_V775);
	
	Double_t tofOffset;
	if ( detectorID == 1) {
	   tree->SetBranchStatus("smwdc_L",1);
	   tree->SetBranchAddress("smwdc_L",&hoge_smwdc);
	   tofOffset = beam->fToffset1 ;
	}else{
	   tree->SetBranchStatus("smwdc_R",1);
	   tree->SetBranchAddress("smwdc_R",&hoge_smwdc);
	   tofOffset = beam->fToffset2 ;
	}


//############################################################################   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   
   art::TTwoSidedPlasticData * V775Data;
   art::TMWDCTrackingResult * xy;
   art::TTrack * track1;
   
//##############################################################################
   for( eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID);
      
      // initialization
      tof   = kInvalidD;
      t1  = kInvalidD; Q1 = kInvalidD; 
      t2  = kInvalidD; Q2 = kInvalidD;
      x1  = kInvalidD;
      a1  = kInvalidD;
      y1  = kInvalidD;
      b1  = kInvalidD;
      
//----------------Get Event Number
      runNum = hoge_run->GetRunNumber();
      
//---------------Get charge DS of Tpla and S0D
		Int_t TplaCheck = 0;
      Double_t timeV775[5];
      Int_t nHit = hoge_V775->GetEntriesFast();
      for ( Int_t p = 0; p < nHit; p++){
         V775Data = (art::TTwoSidedPlasticData*)hoge_V775->At(p);
         Int_t DetID     = V775Data->GetDetID();
         timeV775[DetID] = V775Data->GetTiming();
         if (DetID == detectorID - 1){
         	t1  = V775Data->GetT1();
         	Q1  = V775Data->GetQ1();
        		t2  = V775Data->GetT2();
         	Q2  = V775Data->GetQ2();
        	}
        	if( DetID == detectorID - 1 || DetID == 2 || DetID == 3) TplaCheck ++;
      }
      if ( TplaCheck != 3 ) continue;  
      
//-------------------- Calculated TIme
      
      Double_t tof_usV775  = timeV775[3] - timeV775[2] - beam->fToffsetV775 + Principle_tof;
      
      ts = timeV775[3] + (tof_usV775)*LENGTH_RATIO_FH9_TGT;// tof from Fh9 to tgt

      tof   = timeV775[detectorID - 1] - ts + tofOffset; 

      if ( TMath::IsNaN(tof)  ) continue;         // tof gate
      
//---------Get SMWDC image, should be one 1 instance
      nHit = hoge_smwdc->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         recoildata->TRecoilData();
         xy = (art::TMWDCTrackingResult*)hoge_smwdc->At(p);
         Int_t TrackingID1  = xy -> GetTrackingID();
         Double_t ex1 = xy->GetSigma(0);
         Double_t ea1 = xy->GetSigma(1);
         track1 = (art::TTrack*)xy->GetTrack();
         x1 = track1->GetX();
         y1 = track1->GetY();
         a1 = track1->GetA();
         b1 = track1->GetB();
         if ( TrackingID1 != 1) continue;
         recoildata->SetKinetic(detectorID,tof,x1,y1,a1,b1,0, 0, 0.5, ex1, 0, ea1, 0);
      }
      
//--------------------------------
      if (recoildata->fOK == 0 ) continue;   // recoil gate
      
      E1 = recoildata->fTKA;
      
      if ( TMath::IsNaN(E1)  ) continue;   // energy gate    

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
   f1->Close();
   
   clock.Stop("timer");
   printf("============ finished|%10.3f sec --> %s\n",clock.GetRealTime("timer"),savefilename);
   
   
}

