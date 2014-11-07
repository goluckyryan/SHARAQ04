
void Temp() {
   
//############################################################################   
   const char* rootfile="23F_1002.root";
   //const char* rootfile="Data/phys24Down.root";
   Bool_t allentry  = 0;
   Int_t firstEntry = 0;
   Int_t nEntries=100000;
   
//############################################################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;
   
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded. \n",rootfile);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("nyoki",1);
   tree->SetBranchStatus("p2p",1);
   
   TClonesArray *hoge_nyoki;
   art::sh04::TP2PKinematicsData *hoge_p2p;
   
   tree->SetBranchAddress("nyoki",&hoge_nyoki);
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
      
      Bool_t nyokiPass = 0;
      
//----------------Get nyoki ID and charge
      nHit = hoge_us -> GetEntriesFast();
      Bool_t PID = 0;
      for( Int_t p = 0; p < nHit; p++){
        art:: TTimeDifference* tofusdata = (art::TTimeDifference*)hoge_us->At(p) ;
         Int_t HitID        = tofusdata->GetHitID();
         Double_t tof_usV1190   = tofusdata->GetTiming();
         art::TTwoSidedPlasticData* Qusdata = (art::TTwoSidedPlasticData*) hoge_fh9->At(HitID-1);
         Double_t Q_us      = Qusdata->GetCharge();
      }

//--------------- Get p2p

      Sp = hoge_p2p->GetSp();
      
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

   return ;
}
