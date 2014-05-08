#include "constant.h"

void ChargeCompareS0DNyoki() {
   
   const char* rootfile="Data/phys22_clean.root";
   Bool_t allentry  = 0;
   Int_t firstEntry = 0;
   Int_t nEntries=1000000;
  
   TCanvas* cQcompS0DNyoki = new TCanvas("cQcompS0DNyoki", "Charge comparision of S0D and Nyoki", 1200, 0, 800, 800);   
   cQcompS0DNyoki->Divide(2,2);
   
   TH2F* hPIDDS = new TH2F("hPIDDS","PID downstream", 100 , -80, -56,300, 0, 4000);
   hPIDDS->SetYTitle("Q of S0D");
   hPIDDS->SetXTitle("tof(FH9 - S0D)");
   
   TH2F* hQcomp = new TH2F("hQcomp","Q of S0D and Nyoki", 300 , 0, 9000,300, 0, 4000);
   hQcomp->SetYTitle("Q of S0D");
   hQcomp->SetXTitle("Q of Nyoki");
   
   TH2F* hS0DQnyokiID = new TH2F("hS0DQnyokiID", "S0D Q vs nyoki ID", 14, 0, 14, 300, 0, 4000);
   hS0DQnyokiID->SetYTitle("Q of S0D");
   hS0DQnyokiID->SetXTitle("Nyoki ID");
   
   TClonesArray *hoge_V775, *hoge_tofDS, *hoge_tofD1, *hoge_nyoki;
   TFile *f = new TFile(rootfile,"read");
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("plaV775",1);
   tree->SetBranchStatus("tof_DS",1);
   tree->SetBranchStatus("tof_D1",1);
   tree->SetBranchStatus("nyoki",1);
   
   tree->SetBranchAddress("plaV775",&hoge_V775);
   tree->SetBranchAddress("tof_DS",&hoge_tofDS);
   tree->SetBranchAddress("tof_D1",&hoge_tofD1);
   tree->SetBranchAddress("nyoki",&hoge_nyoki);
   
   if (allentry) nEntries = totnumEntry;
   
   printf("====================== nEntries:%d\n",nEntries);
   
   for( Int_t eventID = firstEntry; eventID < firstEntry+nEntries; eventID++){
      tree->GetEntry(eventID); 
      
      //Get Charge from S0D 
      Int_t nHit1 = hoge_V775->GetEntriesFast();
      Double_t QS0D = kInvalidD;
      for(Int_t p = 0; p < nHit1; p++){
         art::TTwoSidedPlasticData *data = (art::TTwoSidedPlasticData*)hoge_V775->At(p) ;
         Int_t detID   = data->GetDetID();
         if (detID == 4) { QS0D  = data->GetCharge();}
      }

      
      if ( !TMath::IsNaN(QS0D) ){
         Int_t nHit = hoge_tofDS->GetEntriesFast();
         for (Int_t p = 0; p < nHit; p++){
            art::TTimeDifference *data1 = (art::TTimeDifference*)hoge_tofDS->At(p) ;
            Int_t detID = data1->GetDetID();
            if ( detID == 4) {
               hPIDDS->Fill( data1->GetTiming(), QS0D);
            }
         }
         
         Int_t nHit = hoge_tofD1->GetEntriesFast();
         for(Int_t p = 0; p < nHit; p++){
            art::TTimingChargeData *data2 = (art::TTimingChargeData*)hoge_tofD1->At(p) ;
            if ( data2->GetTiming() > -100) {
               hQcomp->Fill(data2->GetCharge(), QS0D);
            }
         }
         
         Int_t nHit = hoge_nyoki->GetEntriesFast();
         for(Int_t p = 0; p < nHit; p++){
            art::TTimingChargeData *data3 = (art::TTimingChargeData*)hoge_nyoki->At(p) ;
            hS0DQnyokiID->Fill(data3->GetID(), QS0D);
         }
         
      }

   }
   

   cQcompS0DNyoki->cd(1);
   hPIDDS->Draw("colz");
   cQcompS0DNyoki->cd(2);
   hQcomp->Draw("colz");
   cQcompS0DNyoki->cd(3);
   hS0DQnyokiID->Draw("colz");

}
