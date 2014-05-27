#include "ryan/constant.h"
#include "ryan/RelCalculator.h"
#include "ryan/TBeamData.h"
#include "ryan/TRecoilData.h"

void Tpla_Q_T_E_analysis() {
//############################################################################   
   const char* savefilename="test.root";
   const char* rootfile="PrimaryData/phys14Up.root";
   TBeamData *beam = new TBeamData("14O");
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
   Double_t tof1, tof2;
   Double_t ts;
   Double_t t1B, Q1B, t1F, Q1F;
   Double_t t2B, Q2B, t2F, Q2F;
   // SMWDC X Y
   Double_t x1, y1, a1, b1; // for smwdc-L
   Double_t x2, y2, a2, b2; // for smwdc-L
   
   TRecoilData * recoildata1 = new TRecoilData();
   TRecoilData * recoildata2 = new TRecoilData();
   
   // Phsyics
   Double_t E1, E2;

   TFile *savefile = new TFile(savefilename,"recreate");
   TTree *recoil; 
   recoil = new TTree("recoil","recoil");
   recoil->Branch("runNum", &runNum, "runNum/I");
   recoil->Branch("eventID",&eventID,"eventID/I");
   recoil->Branch("ts",&ts,"ts/D");
   
   recoil->Branch("tof1",&tof1,"tof1/D");
   recoil->Branch("t1B",&t1B,"t1B/D");
   recoil->Branch("t1F",&t1B,"t1F/D");
   recoil->Branch("Q1B",&Q1B,"Q1B/D");
   recoil->Branch("Q1F",&Q1B,"Q1F/D");
   recoil->Branch("x1",&x1,"x1/D");
   recoil->Branch("a1",&a1,"a1/D");
   recoil->Branch("E1",&E1,"E1/D");
   
   recoil->Branch("tof2",&tof2,"tof2/D");
   recoil->Branch("t2B",&t2B,"t2B/D");
   recoil->Branch("t2F",&t2B,"t2F/D");
   recoil->Branch("Q2B",&Q2B,"Q2B/D");
   recoil->Branch("Q2F",&Q2B,"Q2F/D");
   recoil->Branch("x2",&x2,"x2/D");
   recoil->Branch("a2",&a2,"a2/D");
   recoil->Branch("E2",&E2,"E2/D");

//############################################################################
   art::TEventHeader *hoge_run;
   TClonesArray *hoge_V775, *hoge_L, *hoge_R;
   TFile *f1 = new TFile (rootfile); 
   TTree *tree = (TTree*)f1->Get("tree");
   printf(">> %s <<< is loaded. ----> %s\n",rootfile, savefilename);
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("plaV775",1);    //get charge and time

   tree->SetBranchAddress("eventheader",&hoge_run);
   tree->SetBranchAddress("plaV775",&hoge_V775);
	
   tree->SetBranchStatus("smwdc_L",1);
   tree->SetBranchAddress("smwdc_L",&hoge_L);

   tree->SetBranchStatus("smwdc_R",1);
   tree->SetBranchAddress("smwdc_R",&hoge_R);

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
   art::TTrack * track;
   
//##############################################################################
   for( eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID);
      
      // initialization
      tof1   = kInvalidD;
      tof2   = kInvalidD;
      t1B  = kInvalidD; Q1B = kInvalidD; t1F  = kInvalidD; Q1F = kInvalidD;
      t2B  = kInvalidD; Q2B = kInvalidD; t2F  = kInvalidD; Q2F = kInvalidD;
     
//---------------Get charge DS of Tpla and S0D
		Int_t TplaCheck1 = 0;
		Int_t TplaCheck2 = 0;
      Double_t timeV775[5], tB[5], tF[5], QB[5], QF[5];
      Int_t nHit = hoge_V775->GetEntriesFast();
      for ( Int_t p = 0; p < nHit; p++){
         V775Data = (art::TTwoSidedPlasticData*)hoge_V775->At(p);
         Int_t DetID     = V775Data->GetDetID();
         timeV775[DetID] = V775Data->GetTiming();
         tB[DetID]       = V775Data->GetT1();
         tF[DetID]       = V775Data->GetT2();
         QB[DetID]       = V775Data->GetQ1();
         QF[DetID]       = V775Data->GetQ2();
        	if( DetID == 0 || DetID == 2 || DetID == 3) TplaCheck1 ++;
        	if( DetID == 1 || DetID == 2 || DetID == 3) TplaCheck2 ++;
      }
      if ( TplaCheck1 !=3  || TplaCheck2 !=3) continue;  
      
      Double_t tof_usV775  = timeV775[3] - timeV775[2] - beam->fToffsetV775 + Principle_tof;
      if ( TMath::IsNaN(tof_usV775) ) continue;
      
      ts = timeV775[3] + (tof_usV775)*LENGTH_RATIO_FH9_TGT;// tof from Fh9 to tgt
      
//---------Get SMWDC image, should be one 1 instance
      if ( TplaCheck1 == 3){
      	tof1  = timeV775[0] - ts + beam->fToffset1 + 0.3;
      	t1B = tB[0]; Q1B = QB[0]; t1F = tF[0]; Q1F = QF[0];
      	
      	nHit = hoge_L->GetEntriesFast();
      	for( Int_t p = 0; p < nHit; p++){
         	recoildata1->TRecoilData();
         	xy = (art::TMWDCTrackingResult*)hoge_L->At(p);
         	if ( xy -> GetTrackingID() != 1) continue;
         
         	track = (art::TTrack*)xy->GetTrack();
         
         	x1 = track->GetX();
         	y1 = track->GetY();
         	a1 = track->GetA();
         	b1 = track->GetB();
         
         	recoildata1->SetKinetic(1,tof1,x1,y1,a1,b1,0, 0, 0,0, 0, 0, 0);
      	}
      	
      	E1 = recoildata1->fTKA;
      
      }
      
      if ( TplaCheck2 == 3){
      	tof2  = timeV775[1] - ts + beam->fToffset2; 
      	t2B = tB[1]; Q2B = QB[1]; t2F = tF[1]; Q2F = QF[1];
      	
      	nHit = hoge_R->GetEntriesFast();
      	for( Int_t p = 0; p < nHit; p++){
         	recoildata2->TRecoilData();
         	xy = (art::TMWDCTrackingResult*)hoge_R->At(p);
         	if ( xy -> GetTrackingID() != 1) continue;
         
         	track = (art::TTrack*)xy->GetTrack();
         
         	x2 = track->GetX();
         	y2 = track->GetY();
         	a2 = track->GetA();
         	b2 = track->GetB();

         	recoildata2->SetKinetic(2,tof2,x2,y2,a2,b2,0, 0, 0, 0, 0, 0, 0);
      	}  
      	
      	E2 = recoildata2->fTKA;
      }

      if ( TMath::IsNaN(tof1) && TMath::IsNaN(tof2)  ) continue;         // tof gate
      
      if (recoildata1->fOK == 0 && recoildata2->fOK == 0) continue;   // recoil gate
      
      if ( TMath::IsNaN(E1) && TMath::IsNaN(E2) ) continue;   // energy gate    

//----------- Fill        
      savefile->cd(); //set focus on this file
      recoil->Fill();  
      
//------------Clock      
      clock.Stop("timer");
      Double_t time = clock.GetRealTime("timer");
      clock.Start("timer");
      
      if ( !shown ) {
         if (fmod(time, 20) < 1 ){
            printf( "%10d[%2d%%] |%3d min %5.2f sec | expect:%5.1fmin\n", 
            eventID, 
            TMath::Nint((eventID+1-firstEntry)*100./nEntries),
            TMath::Floor(time/60), time - TMath::Floor(time/60)*60,
            nEntries*time/(eventID+1-firstEntry)/60.);
            shown = 1;
         }
      }else{
         if (fmod(time, 20) > 9 ){
            shown = 0;
         }
      }
      
   }
  
   //savefile->cd();
   //recoil->Write();
   //savefile->Close();
   //f1->Close();
   
   clock.Stop("timer");
   printf("============ finished|%10.3f sec --> %s\n",clock.GetRealTime("timer"),savefilename);
   
   gROOT->ProcessLine(".q");
}

