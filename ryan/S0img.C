void S0img() {
   Double_t tof, charge, S0x, S0y;
   Int_t nHit1, nHit2, nHit3;
   Int_t coinReg;
   Int_t detID;
   Int_t eventID;
   Long64_t i,j, p,q, k, n, nEntries, totnumEntry;
   Bool_t flag;
   TStopwatch time;
   time.Reset();
   
   const char* savefilename="Gated.root";
   const char* rootfile="~/sharaq04/optics4027.root";
   Bool_t debugInfo = 0; //0 - false
   Bool_t allentry  = 1;
   nEntries = 10000;
   
   TH2F* h3 = new TH2F("pid","pid Upstream",200, -1470, -1400, 100 , 5000, 6200);
   TH2F* h4 = new TH2F("pid","pid Upstream w/ coinReg",200, -1470, -1400, 100 , 5000, 6200);
   TH2F* h5 = new TH2F("S0img1","S0img ",100, -30, 30, 100 , -30, 30);
   TH2F* h6 = new TH2F("S0img2","S0img w/ coinReg",100, -30, 30, 100 , -30, 30);
   TH2F* h7 = new TH2F("S0img3","S0img w/ coinReg + pid",100, -30, 30, 100 , -30, 30);
   TCanvas* ctest = new TCanvas("ctest", "PID", 50, 50, 600, 600);
   ctest->Divide(3,2);   
  
   TClonesArray *hoge1, *hoge2, *hoge3, *hoge4, *hoge5;
   TFile *f = new TFile(rootfile,"read");
   TTree *tree = (TTree*)f->Get("tree");
   totnumEntry = tree->GetEntries();
   printf("===============================================================\n");
   printf(" total number event: %10d\n",totnumEntry);
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("coinReg",1);
   tree->SetBranchStatus("tof_US",1);
   tree->SetBranchStatus("S0img",1);
   //tree->SetBranchStatus("ppac",1);
   tree->SetBranchStatus("plaV775",1);
   
   //tree->Scan("plaV1190_FH9.fTAve:plaV1190_F3.fTAve","","",10);

   tree->SetBranchAddress("coinReg",&hoge1);
   tree->SetBranchAddress("tof_US",&hoge2);
   tree->SetBranchAddress("S0img",&hoge3);
   //tree->SetBranchAddress("ppac",&hoge4);
   tree->SetBranchAddress("plaV775",&hoge5);
   
   if (allentry) nEntries = totnumEntry;
   
   if (debugInfo) printf("======================================\n");
   
   for( i = 0; i < nEntries; i++){
   
      tree->GetEntry(i);   
      eventID = i;  
      
      nHit1 = hoge1->GetEntriesFast();      
      if (debugInfo)  printf("--------------------- %4d, %4d \n", i, nHit1);
      for( p = 0; p < nHit1; p++){
         art::TRawDataSimple<UShort_t>* CoinData = (art::TRawDataSimple<UShort_t>*)hoge1->At(p) ;
         coinReg  = CoinData->Get();
         
         //if (coinReg != 2) continue;
         
         nHit2 = hoge2->GetEntriesFast();
         for ( q = 0; q < nHit2; q++){
            art::TTimingChargeData* pidData = (art::TTimingChargeData*)hoge2->At(q) ;
            tof = pidData->GetTiming();
            charge = pidData->GetCharge();
            if ( p == 0) {
               h3->Fill(tof,charge);
            }
            if ( coinReg == 2){
               h4->Fill(tof,charge);
            }
            
            if( tof > - 1446 && tof < -1436 && charge > 5646 && charge < 5930){
               nHit3 = hoge3->GetEntriesFast();
               for ( k = 0; k< nHit3; k++){
                  art::TMWDCTrackingResult* xy = (art::TMWDCTrackingResult*)hoge3->At(k);
                  art::TTrack* track = (art::TTrack*)xy->GetTrack();
                  S0x = track->GetX();
                  S0y = track->GetY();
                  h6->Fill(S0x,S0y);
                  if( coinReg == 2) h7->Fill(S0x,S0y);
               }
            }  
         }
      }
      
      nHit3 = hoge3->GetEntriesFast();
      for ( k = 0; k< nHit3; k++){
         xy = (art::TMWDCTrackingResult*)hoge3->At(k);
         art::TTrack* track = (art::TTrack*)xy->GetTrack();
         S0x = track->GetX();
         S0y = track->GetY();
         h5->Fill(S0x,S0y);
      }

      
      if( i%10000 ==0) printf(" event:%10d, %5.2f%% \n",i,(Double_t)i/totnumEntry*100);

   }
   
   
   ctest->cd(1);
//   h1->Draw("colz");
//   ctest->cd(2);
//   h1->Draw("same");
//   h2->Draw("same");
   h3->Draw("colz");
   ctest->cd(2);
   h4->Draw("colz");
   ctest->cd(4);
   h5->Draw("colz");
   ctest->cd(5);
   h6->Draw("colz");
   ctest->cd(6);
   h7->Draw("colz");

   printf("End of Run. endEvent:%10d(%5.2f%%) time:%10.2f sec \n",i, (Double_t)i*100/totnumEntry, time.RealTime());
   

}
