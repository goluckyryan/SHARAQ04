void tofusResol_ppac() {
   
   Int_t eventID;
   Long64_t totnumEntry;
   
   const char* rootfile="phys14_45_67.root";
   TString detector = "V775";
   Double_t Brho    = 4.2;
   Bool_t allentry  = 0;
   Int_t firstEntry = 0;
   Int_t nEntries=1000000;
   Int_t nBin = 220;
   Double_t Yrange[2] = {4.1, 4.3};
   Double_t slideBin[2] = {109,111};
   
   TString hTofPPACTitle;
   hTofPPACTitle.Form("tof_us(%s) vs PPAC(X)",detector.Data());  
   TH2F* hTofPPAC = new TH2F("hTofPPAC",hTofPPACTitle,300, 400, 408, nBin , Yrange[0], Yrange[1]);
   hTofPPAC->SetXTitle("Tof us[ns]");
   hTofPPAC->SetYTitle("Brho");

   TCanvas* ctofPPAC = new TCanvas("ctofPPAC", "tof upstream by PPAC", 0, 0, 800, 600);   
   ctofPPAC->Divide(1,2);

   TClonesArray *hoge_tof, *hoge_ppac;
   TFile *f = new TFile(rootfile,"read");
   TTree *pid = (TTree*)f->Get("tree");
   totnumEntry = pid->GetEntries();
   pid->SetBranchStatus("*",0);
   pid->SetBranchStatus("ppac",1);
   pid->SetBranchAddress("ppac",&hoge_ppac);
   
   if ( detector == "V1190"){
      pid->SetBranchStatus("tof_US",1);
      pid->SetBranchAddress("tof_US",&hoge_tof);
   }else{
      pid->SetBranchStatus("tof_DS",1);
      pid->SetBranchAddress("tof_DS",&hoge_tof);
   }
   
   if (allentry) nEntries = totnumEntry;
   
   printf("======%s================ nEntries:%d\n",detector.Data(),nEntries);
   
   for( eventID = firstEntry; eventID < firstEntry+nEntries; eventID++){
      pid->GetEntry(eventID); 
      
      //Get PPAC fX
      Int_t nHit1 =hoge_ppac->GetEntriesFast();
      Double_t * ppacX = new Double_t[nHit1];
      for(Int_t p = 0; p < nHit1; p++){
         art::TPPACData * ppacData = (art::TPPACData*)hoge_ppac->At(p);
         ppacX[p]   = ppacData->GetX();
      }
      
      //Get tof
      Int_t nHit2 =hoge_tof->GetEntriesFast();
      Double_t * tof = new Double_t[nHit2];
      Int_t    * detID = new Double_t[nHit2];
      for(Int_t p = 0; p < nHit2; p++){
         art::TTimeDifference *data2 = (art::TTimeDifference*)hoge_tof->At(p) ;
         detID[p]          = data2->GetDetID();
         tof[p]     = data2->GetTiming();
      }
      
      for (Int_t p = 0; p < nHit1; p++){
         for (Int_t q = 0; q< nHit2; q++){
            if (detector == "V1190"){
               hTofPPAC->Fill(tof[q]+1440.+404.3598,Brho*(1-ppacX[p]/7500));
            }else{
               if (detID[q] == 2){
                  hTofPPAC->Fill(tof[q]-302.22+404.3598,Brho*(1+ppacX[p]/7500));
               }
            }
         }
      }
     
   delete ppacX;
   delete tof;
   delete detID;

   }
   
   ctofPPAC->cd(1);
   hTofPPAC->Draw("colz");
   ctofPPAC->cd(2);
   hTofPPAC->ProjectionX("test",slideBin[0],slideBin[1]);
   TString testTitle;
   testTitle.Form("ProjectX, Brho = (%10.6f,%10.6f|%10.6f)",
                  Yrange[0]+(slideBin[0]-1)*(Yrange[1]-Yrange[0])/nBin,
                  Yrange[0]+(slideBin[1])*(Yrange[1]-Yrange[0])/nBin,
                  (slideBin[1]-slideBin[0]+1)*(Yrange[1]-Yrange[0])/nBin);
   test->SetTitle(testTitle);
   test->Draw();
   test->Fit("gaus");

   return ;
}
