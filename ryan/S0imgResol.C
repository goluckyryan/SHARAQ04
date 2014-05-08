//Find the resolution of X A Y B by residual

void S0imgResol() {

   const char* rootfile="Data/phys14Up.root";
   Bool_t allentry  = 0;
   Int_t firstEntry = 3000000;
   Int_t nEntries   = 1000000;
   
//############################################################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;
   
   //====== explaination
   Double_t SSR;
   Double_t var; // =SSR/(7-4);
   Double_t CoVar[4];
   Double_t varBeta[4]; // =CoVar[4]*var
   Double_t sigma[4];
   
   CoVar[0] = 6.567639144; 
   CoVar[1] = 0.0000122454356; 
   CoVar[2] = 18.73226659; 
   CoVar[3] = 0.00003454508459;
   
   //========= Histogram
   TCanvas* cS0Resol = new TCanvas("cS0Resol", "S0img Resol.", 100, 100, 600,600);
   cS0Resol->Divide(2,2);
   
   TH1F* hsigmaX = new TH1F("sigmaX", "sigma(X) [mm]", 100, 0, 5);
   TH1F* hsigmaY = new TH1F("sigmaY", "sigma(Y) [mm]", 100, 0, 5);
   TH1F* hsigmaA = new TH1F("sigmaA", "sigma(A) [mrad]", 100, 0, 20);
   TH1F* hsigmaB = new TH1F("sigmaB", "sigma(B) [mrad]", 100, 0, 20);

//############################################################################
   art::TEventHeader *hoge_run;
   TClonesArray *hoge_S0img;
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded.\n",rootfile);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("eventheader",1);
   tree->SetBranchStatus("S0img",1);

   tree->SetBranchAddress("eventheader",&hoge_run);
   tree->SetBranchAddress("S0img",&hoge_S0img);

//############################################################################   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   

   art::TMWDCTrackingResult * xyS0;

//##############################################################################
   for( Int_t eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID);
     
      
//----------------Get Event Number
      Int_t runNum = hoge_run->GetRunNumber();

      Int_t nHit = hoge_S0img->GetEntriesFast();
      //Double_t s0a, s0b;
      for( Int_t p = 0; p < nHit; p++){
         xyS0 = (art::TMWDCTrackingResult*)hoge_S0img->At(p);
         SSR = xyS0->GetSSR();
         var = SSR/(7.-4.);
      }     
      
      for ( Int_t i = 0; i < 4; i++){
         varBeta[i] = CoVar[i]*var;
         sigma[i] = TMath::Sqrt(varBeta[i]);
      } 
      
      hsigmaX->Fill(sigma[0]);
      hsigmaA->Fill(sigma[1]*1000.);
      hsigmaY->Fill(sigma[2]);
      hsigmaB->Fill(sigma[3]*1000.);
      
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
   
   cS0Resol->cd(1);
   hsigmaX->Draw();
   
   cS0Resol->cd(2);
   hsigmaA->Draw();
   
   cS0Resol->cd(3);
   hsigmaY->Draw();
   
   cS0Resol->cd(4);
   hsigmaB->Draw();


   clock.Stop("timer");
   printf("============ finished|%10.3f sec\n",clock.GetRealTime("timer"));
   return ;
}
