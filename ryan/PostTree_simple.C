// Trim the root file, extract essentail data. For quicker analysis
#include "constant.h"
//#include "RelCalculator.h"

void PostTree_simple() {
   
//############################################################################   
   const char* savefilename="P_23F_run23_nyokiQ.root";
   //const char* rootfile="Data/phys14_1_43.root";
   const char* rootfile="23F_run23_nyokiQ.root";
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
   Double_t tofS0D, QS0D;
   Double_t tofS1, QS1;
   Double_t tofS1_n, QS1_n;



   TFile *savefile = new TFile(savefilename,"recreate");
   TTree *recoil; 
   recoil = new TTree("recoil","recoil");
   recoil->Branch("eventID",&eventID,"eventID/I");
   recoil->Branch("tofS0D", &tofS0D, "tofS0D/D");
   recoil->Branch("QS0D", &QS0D, "QS0D/D");
   recoil->Branch("tofS1",&tofS1,"tofS1/D");
   recoil->Branch("QS1",&QS1,"QS1/D");
   recoil->Branch("tofS1_n",&tofS1_n,"tofS1_n/D");
   recoil->Branch("QS1_n",&QS1_N,"QS1_n/D");


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
   tree->SetBranchStatus("eventheader",1);
   tree->SetBranchStatus("plaV775",1);    //get charge and time
   tree->SetBranchStatus("tof_DS",1);
   tree->SetBranchStatus("nyoki",1);
   tree->SetBranchStatus("nyoki_n",1);
   tree->SetBranchStatus("tof_D1",1);   
   tree->SetBranchStatus("tof_D1_n",1);
   

   art::TEventHeader *hoge_run = 0;
   TClonesArray *hoge_V775 = 0, *hoge_ds = 0;
   TClonesArray *hoge_nyoki = 0, *hoge_nyoki_n;
   TClonesArray *hoge_tofD1 = 0, *hoge_tofD1_n;
   
   
   tree->SetBranchAddress("eventheader",&hoge_run);
   tree->SetBranchAddress("plaV775",&hoge_V775);
   tree->SetBranchAddress("tof_DS",&hoge_ds);
   tree->SetBranchAddress("nyoki",&hoge_tofL);
   tree->SetBranchAddress("tofR",&hoge_tofR);
   tree->SetBranchAddress("tof_D1_t",&hoge_tofD1);
   tree->SetBranchAddress("tof_D1_t",&hoge_tofD1);


   
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
      tree->GetEntry(eventID,0);
      
//----------------Get Event Number
      runNum = -100;
      runNum = hoge_run->GetRunNumber();

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
