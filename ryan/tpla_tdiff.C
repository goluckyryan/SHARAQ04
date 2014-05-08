#include "constant.h"

void tpla_tdiff() {
   Double_t tdiff,tdiff1, tdiff2;
   Int_t nHit;
   Int_t detID;
   Int_t eventID;
   Long64_t i,j, p,q, k, n, nEntries, totnumEntry;
   TStopwatch time;
   time.Reset();
   
//   const char* savefilename="tdiff_tpla.root";
   const char* rootfile="~/sharaq04/all.root";
   Bool_t debugInfo = 0; //0 - false
   Bool_t allentry  = 1;
   nEntries=100000;
   
   TH2F* h2 = new TH2F("TDiff","TDiff of Tpla-L and R",200, -15,  10, 100 , -10, 15);
   TCanvas* c1 = new TCanvas("c1", "PID", 50, 50, 600, 600);
//   c1->Divide(2,1);   
 
   TClonesArray *hoge;
   TFile *f = new TFile(rootfile,"read");
   TTree *tree = (TTree*)f->Get("tree");
   totnumEntry = tree->GetEntries();
   printf("===============================================================\n");
   printf(" total number event: %10d\n",totnumEntry);
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("plaV775",1);
   
   //tree->Scan("plaV1190_FH9.fTAve:plaV1190_F3.fTAve","","",10);

   tree->SetBranchAddress("plaV775",&hoge);
   
   if (allentry) nEntries = totnumEntry;
   
   if (debugInfo ==1) printf("======================================\n");
   
   for( i = 0; i < nEntries; i++){
      tdiff1 = kInvalid;
      tdiff2 = kInvalid;
      tree->GetEntry(i);   
      nHit =hoge->GetEntriesFast();
      eventID = i;        
      if (debugInfo ==1)  printf("--------------------- %4d, %4d \n", i, nHit);
      for( p = 0; p < nHit; p++){
         art::TTwoSidedPlasticData *data = (art::TTwoSidedPlasticData*)hoge->At(p) ;
         detID   = data->GetDetID();
         tdiff = data->GetTDiff();
         if (detID ==0) tdiff1 = tdiff;
         if (detID ==1) tdiff2 = tdiff;
         if (debugInfo ==1) printf("detID:%1d T:%10.4f,  T1:%10.4f , T2:%10.4f  \n",detID, tdiff, tdiff1, tdiff2);         
      }
      if(tdiff1 !=kInvalid && tdiff2 !=kInvalid){
         if (debugInfo ==1) printf(".....T1:%10.4f T2:%10.4f  \n", tdiff1, tdiff2);
         h2->Fill(tdiff1,tdiff2);
      }
      
      if( i%10000 ==0) printf(" event:%10d, %5.2f%% \n",i,(Double_t)i/totnumEntry*100);
     
 /*     if(plantTree){
         savefile.cd(); //set focus on this file
         t1->Fill();
      }*/
   }
   
   
   c1->cd(1);
//   h1->Draw("colz");
//   c1->cd(2);
   h2->Draw("colz");

   printf("End of Run. endEvent:%10d(%5.2f%%) time:%10.2f sec \n",i, (Double_t)i*100/totnumEntry, time.RealTime());
   
  /* if(plantTree){
      savefile.cd();
      t1->Write();
      savefile.Close();
   } */

}
