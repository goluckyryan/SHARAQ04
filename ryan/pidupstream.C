#include "TBeamData.h"

void pidupstream() {
   
   const char* rootfile="Data/phys22Optics.root";
   //const char* rootfile="Data/phys22_clean.root";
   TBeamData *beam = new TBeamData("23F");
   Bool_t allentry  = 1;
   Bool_t BeamTrigger = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=100;
   
   Double_t F3tGate[2]  = {1000, 1130};
   Double_t FH9tGate[2] = {-500, -300};
   Double_t AccShift = 34;
   
//########################################################################   
   TString histTitle;
   histTitle.Form("PID upstream (%s)", rootfile);
   
   if (BeamTrigger) histTitle += " Beam Trigger";
   
   gStyle->SetOptStat(1111);
   
   TH2F* hPIDUS = new TH2F("PID_US",histTitle,300, -1500, -1410, 300 , 4900, 6200);
   hPIDUS->SetStats(0);
   
   TH1F* hF3Timing = new TH1F("F3Timing", "F3 pla Tavg", 200, -1000, 2500);
   TH1F* hFH9Timing = new TH1F("FH9Timing", "FH9 pla Tavg", 200, -6000, 1000);
   
   TH1F* hF3Multi  = new TH1F("F3Multi", "F3 pla Multi", 10, 0, 10);
   TH1F* hFH9Multi = new TH1F("FH9Multi", "FH9 pla Multi", 10, 0, 10);
   TH1F* hTofMulti = new TH1F("TofMulti", "ToF Multi", 10, 0, 10);
   
   TH2F* hPIDUSg1 = new TH2F("PIDUSg1", "PIDcount", 300, -1500, -1410, 300 , 4900, 6200);
   TH2F* hPIDUSg2 = new TH2F("PIDUSg2", "AccCount", 300, -1500, -1410, 300 , 4900, 6200);
   hPIDUSg1->SetStats(0);
   hPIDUSg2->SetStats(0);
   
   TCanvas* cPidUS = new TCanvas("cPidUS", "PID", 0, 0, 1200, 600);   
   cPidUS->Divide(4,2);

//#####################################################

   TClonesArray *hoge_F3, *hoge_FH9, *hoge_tof;
   art::TCoinRegData *hoge_coinReg;
   TFile *f = new TFile(rootfile,"read");
   TTree *pid = (TTree*)f->Get("tree");
   Int_t totnumEntry = pid->GetEntries();
   pid->SetBranchStatus("*",0);
   pid->SetBranchStatus("coinReg",1);
   pid->SetBranchStatus("plaV1190_F3",1);
   pid->SetBranchStatus("plaV1190_FH9",1);
   pid->SetBranchStatus("tof_US",1);
   
   pid->SetBranchAddress("coinReg",&hoge_coinReg);
   pid->SetBranchAddress("plaV1190_F3",&hoge_F3);
   pid->SetBranchAddress("plaV1190_FH9",&hoge_FH9);
   pid->SetBranchAddress("tof_US",&hoge_tof);
   
   if (allentry) {
      firstEntry = 0;
      nEntries = totnumEntry;
   }
   
   if ( nEntries + firstEntry > totnumEntry) nEntries = totnumEntry - firstEntry;
   
   Int_t hitID[50], hitID0[50];
   Double_t QAveFH9[50], tof[50];
   Double_t TAveF3[50], TAveFH9[50];
   
   Int_t PIDcount = 0;
   Int_t AccCount = 0;
   Int_t totCount = 0;
   
   printf("File:%s ==== TotnumEntry:%d, 1stEntry:%d, nEntries:%d[%4.1f%%]\n"
                 , rootfile
                 , totnumEntry
                 , firstEntry
                 , nEntries
                 , nEntries*100./totnumEntry);
   if(BeamTrigger) printf(".. BeamTrigger.\n");
   
//##############################################################   
   for( Int_t eventID = firstEntry; eventID < firstEntry+nEntries; eventID++){
      pid->GetEntry(eventID); 
      
      if ( BeamTrigger && hoge_coinReg->Test(1) != 1 ) continue; 
      
     
      for( Int_t p = 0; p <50; p++){
         hitID[p]    = -2;
         hitID0[p]   = -3;
         QAveFH9[p]  = TMath::QuietNaN();
         TAveFH9[p]  = TMath::QuietNaN();
         TAveF3[p]   = TMath::QuietNaN();
         tof[p]      = TMath::QuietNaN();
      }
      
      //Get F3 Mulit-Hit
      Int_t F3Multi = 0;
      Int_t nHit = hoge_F3->GetEntriesFast();
      for(Int_t p = 0; p < nHit; p++){
         art::TTwoSidedPlasticData *data = (art::TTwoSidedPlasticData*)hoge_F3->At(p) ;
         TAveF3[p]    = data->GetTiming();
         if ( TMath::Finite(TAveF3[p]) ) {
            if ( TAveF3[p] > F3tGate[0] && TAveF3[p] < F3tGate[1]){
               F3Multi ++;
               hF3Timing->Fill(TAveF3[p]);
            }
         }  
      }
      hF3Multi->Fill(F3Multi);
      
      //Get Charge from FH9  
      Int_t FH9Multi = 0;
      Int_t nHit1 =hoge_FH9->GetEntriesFast();
      for(Int_t p = 0; p < nHit1; p++){
         art::TTwoSidedPlasticData *data1 = (art::TTwoSidedPlasticData*)hoge_FH9->At(p) ;
         QAveFH9[p]    = data1->GetCharge();
         TAveFH9[p]    = data1->GetTiming();
         if ( TMath::Finite(TAveFH9[p]) ) {
            if ( TAveFH9[p] > FH9tGate[0] && TAveFH9[p] < FH9tGate[1]){
               FH9Multi ++;
               hFH9Timing->Fill(TAveFH9[p]);
            }
         }  
      }
      hFH9Multi->Fill(FH9Multi);
      
      //Get tof
      Int_t nHit2 =hoge_tof->GetEntriesFast();
      if ( nHit2 >=1 ) totCount ++;
      for(Int_t p = 0; p < nHit2; p++){
         art::TTimeDifference *data2 = (art::TTimeDifference*)hoge_tof->At(p) ;
         hitID[p]       = data2->GetHitID();  // FH9 hit ID
         hitID0[p]      = data2->GetHitID0(); // F3 hit ID
         tof[p]         = data2->GetTiming();
         
         //TODO Get F3 and Dh9 timing and charge in here
      }
      
      Int_t tofMulti = 0;
      Int_t PIDcheck = 0;
      Int_t AccCheck = 0;
      for (Int_t p = 0; p < nHit1; p++){
         for (Int_t q = 0; q< nHit2; q++){
            if (p != hitID[q]-1) continue;
            if ( !TMath::Finite(tof[q]) || !TMath::Finite(QAveFH9[p]) ) continue;
            //find out the corresponding F3 and FH9 timing
            //printf("%6.2f- %6.2f = %6.2f \n", TAveFH9[hitID[q]-1], TAveF3[hitID0[q]-1], tof[q]);
            if ( TAveF3[hitID0[q]-1] < F3tGate[0] || TAveF3[hitID0[q]-1] > F3tGate[1]) continue;
            if ( TAveFH9[hitID[q]-1] < FH9tGate[0] || TAveFH9[hitID[q]-1] > FH9tGate[1]) continue;
             
            hPIDUS->Fill(tof[q],QAveFH9[p]);
            tofMulti ++;
            
            if ( QAveFH9[p] > beam->fQGate[0] && QAveFH9[p] < beam->fQGate[1] ){
               
               if ( tof[q] > beam->fTofGate[0] && tof[q] < beam->fTofGate[1] ){
                  PIDcheck ++;  
                  hPIDUSg1->Fill(tof[q],QAveFH9[p]);
               }
               if ( tof[q] > beam->fTofGate[0] - AccShift && tof[q] < beam->fTofGate[1] -AccShift ){
                  AccCheck ++;  
                  hPIDUSg2->Fill(tof[q],QAveFH9[p]);
               }
               
               /*printf("%6.2f, (%6.2f, %6.2f), (%6.2f, %6.2f)  == %d | %d\n", 
                         tof[q],
                         beam->fTofGate[0],  beam->fTofGate[1],
                         beam->fTofGate[0]-AccShift,  beam->fTofGate[1]-AccShift,
                         PIDcount, AccCount);*/
            }
            
         }
         
         if (PIDcheck >= 1) PIDcount ++;
         if (AccCheck >= 1) AccCount ++;
         
      }
      hTofMulti->Fill(tofMulti);

   }
   
   TLine line;
   
   cPidUS->cd(1);
   hF3Timing->Draw();
   line.DrawLine(F3tGate[0], 0, F3tGate[0], hF3Timing->GetMaximum());
   line.DrawLine(F3tGate[1], 0, F3tGate[1], hF3Timing->GetMaximum());
   
   cPidUS->cd(2);
   hFH9Timing->Draw();
   line.DrawLine(FH9tGate[0], 0, FH9tGate[0], hFH9Timing->GetMaximum());
   line.DrawLine(FH9tGate[1], 0, FH9tGate[1], hFH9Timing->GetMaximum());
   
   cPidUS->cd(3);
   hPIDUS->Draw("colz");
   
   
   line.DrawLine(beam->fTofGate[0], beam->fQGate[0], beam->fTofGate[0], beam->fQGate[1]);
   line.DrawLine(beam->fTofGate[0], beam->fQGate[1], beam->fTofGate[1], beam->fQGate[1]);
   line.DrawLine(beam->fTofGate[1], beam->fQGate[1], beam->fTofGate[1], beam->fQGate[0]);
   line.DrawLine(beam->fTofGate[1], beam->fQGate[0], beam->fTofGate[0], beam->fQGate[0]);
   
   line.DrawLine(beam->fTofGate[0]-AccShift, beam->fQGate[0], beam->fTofGate[0]-AccShift, beam->fQGate[1]);
   line.DrawLine(beam->fTofGate[0]-AccShift, beam->fQGate[1], beam->fTofGate[1]-AccShift, beam->fQGate[1]);
   line.DrawLine(beam->fTofGate[1]-AccShift, beam->fQGate[1], beam->fTofGate[1]-AccShift, beam->fQGate[0]);
   line.DrawLine(beam->fTofGate[1]-AccShift, beam->fQGate[0], beam->fTofGate[0]-AccShift, beam->fQGate[0]); 
   
   cPidUS->cd(4);
   hPIDUSg1->Draw("colz");
   hPIDUSg2->Draw("colz same");
   
   TLatex text;
   text.SetNDC();
   text.SetTextColor(1);
   
   TString textStr;
   textStr.Form("count PID:%d", PIDcount);
   text.DrawText(0.2, 0.3, textStr);
   textStr.Form("count Acc:%d",AccCount);
   text.DrawText(0.2, 0.25, textStr);
   textStr.Form("count tot:%d", totCount);
   text.DrawText(0.2, 0.2, textStr);
   textStr.Form("Purity:%4.1f%%",PIDcount*100./totCount);
   text.DrawText(0.2, 0.15, textStr);
   
   cPidUS->cd(5);
   hF3Multi->Draw();
   
   cPidUS->cd(6);
   hFH9Multi->Draw();
   
   cPidUS->cd(7);
   hTofMulti->Draw();
   
   cPidUS->cd(8);
   text.DrawText(0.2,0.3, rootfile);
   
   


   return ;
}
