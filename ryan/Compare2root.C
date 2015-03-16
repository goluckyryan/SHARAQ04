void Compare2root(){

//############################################################################
   const char* rootfile1="23F_0208.root";
   const char* rootfile2="23F_0208.root";
   
//############################################################################
   TFile *f0 = new TFile (rootfile1, "read"); 
   if( f0==0){
      printf("cannot load file: %s \n", rootfile1);
      return;
   }
   TTree *tree1 = (TTree*)f0->Get("tree");
   Int_t nEntries1 = tree1->GetEntries();
   printf("=====> /// %15s //// is loaded. Total #Entry: %10d \n", rootfile1,  nEntries1);



   TFile *f1 = new TFile (rootfile2, "read"); 
   if( f1==0){
      printf("cannot load file: %s \n", rootfile2);
      return;
   }
   Int_t nEntries2 = tree2->GetEntries();
   TTree *tree1 = (TTree*)f1->Get("tree");
   printf("=====> /// %15s //// is loaded. Total #Entry: %10d \n", rootfile2,  nEntries2);
   
   Int_t nEntries = TMath::Max(nEntries1,nEntries2);

//############################################################################
   TCanvas* Comp = new TCanvas("Comp", "Comp", 0, 0, 500, 500);
   
   TH2F * h1 = new TH2F("h1", "", 100, 0, 10, 100, 0, 10);


//############################################################################

   tree1->SetBranchStatus("*",0);
   tree1->SetBranchStatus("smwdc_S1",1); TClonesArray *hoge_a = 0; tree1->SetBranchAddress("smwdc_S1",&hoge_a);
      
   tree2->SetBranchStatus("*",0);
   tree2->SetBranchStatus("smwdc_S1",1); TClonesArray *hoge_b = 0; tree2->SetBranchAddress("smwdc_S1",&hoge_b);

//############################################################################
   for( Int_t eventID = 0; eventID < nEntries; eventID ++){
      tree1->GetEntries(eventID,0);
      
      Int_t TrackingIDS1;
      Double_t s1x, s1y, s1a, s1b;
      
      Int_t nHit = hoge_a->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         TrackingIDS1  = ((art::TMWDCTrackingResult*)hoge_a->At(p))-> GetTrackingID();
         
         if(TrackingIDS1 != 1) continue;
         
         art::Track* track = (art::TTrack*)((art::TMWDCTrackingResult*)hoge_a->At(p))->GetTrack();
         s1x = track->GetX();
         s1y = track->GetY();
         s1a = track->GetA();
         s1b = track->GetB();
      }
      
      if(TrackingIDS1 != 1) continue;
      
      //_________________________________________________________
      
      tree2->GetEntries(eventID,0);
      
      Int_t TrackingIDS2;
      Double_t s2x, s2y, s2a, s2b;
   
      Int_t nHit = hoge_b->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         TrackingIDS2  = ((art::TMWDCTrackingResult*)hoge_b->At(p))-> GetTrackingID();
         
         if(TrackingIDS2 != 1) continue;
         
         art::Track* track = (art::TTrack*)((art::TMWDCTrackingResult*)hoge_b->At(p))->GetTrack();
         s2x = track->GetX();
         s2y = track->GetY();
         s2a = track->GetA();
         s2b = track->GetB();
      }
      
      if(TrackingIDS2 != 1) continue;
      
      h1->Fill(s1a, s2a);
      
      
   }
   
   Comp->cd();
   h1->Draw("colz");

}
