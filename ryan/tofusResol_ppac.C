#include "constant.h"
#include "RelCalculator.h"
#include "TBeamData.h"

//TODO make the Brho be X-axis. 
//TODO make the different from tof and calculated tof. 

void tofusResol_ppac() {
   
   Int_t eventID;
   Long64_t totnumEntry;
   
   const char* rootfile="phys22Optics.root";
   TString detector = "V775"; // either V1190 or V775
   TBeamData *beam = new TBeamData("23F");
   Double_t PathLength = L_F3FH9+000;
   
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=1000000;
   Int_t nBin = 220;
   Double_t slideBin[2] = {109,111};

//============================================
   Double_t Yrange[2] = {beam->fBrho-0.1, beam->fBrho+0.1};
   Double_t principle_tof = tofByBrho(PathLength, beam->fBrho, beam->fMass,beam->fZ);
   Double_t lineBrho = Yrange[0]+(slideBin[0]+slideBin[1])*(Yrange[1]-Yrange[0])/nBin/2;
   Double_t lineTof = tofByBrho(PathLength, lineBrho, beam->fMass, beam->fZ);
   
   TString hTofPPACTitle;
   hTofPPACTitle.Form("tof_us(%s) vs PPAC(X)",detector.Data());  
   TH2F* hTofPPAC = new TH2F("hTofPPAC",hTofPPACTitle,300, principle_tof-5, principle_tof+5, nBin , Yrange[0], Yrange[1]);
   hTofPPAC->SetXTitle("Tof us[ns]");
   hTofPPAC->SetYTitle("beam->fBrho");

   TCanvas* ctofPPAC = new TCanvas("ctofPPAC", "tof upstream by PPAC", 1000, 0, 800, 600);   
   ctofPPAC->Divide(1,2);
//============================================
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
         detID[p]   = data2->GetDetID();
         tof[p]     = data2->GetTiming();
      }
      
      for (Int_t p = 0; p < nHit1; p++){
         for (Int_t q = 0; q< nHit2; q++){
            if (detector == "V1190"){
               hTofPPAC->Fill(tof[q]- beam->fToffsetV1190 +principle_tof,beam->fBrho*(1+ppacX[p]/7500));
            }else{
               if (detID[q] == 2){
                  hTofPPAC->Fill(tof[q]+ beam->fToffsetV775 +principle_tof,beam->fBrho*(1-ppacX[p]/7500));
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

   TF1 *func = new TF1("func", BrhoBytof, principle_tof-5, principle_tof+5, 4); 
   func->SetParameters( PathLength, beam->fMass, beam->fZ); 
   func->SetLineColor(5);  
   func->Draw("same"); 

   TF1 *func1 = new TF1("func1", BrhoBytof, principle_tof-5, principle_tof+5, 4); 
   func1->SetParameters( PathLength+100, beam->fMass, beam->fZ); 
   func1->SetLineColor(6);  
   func1->Draw("same"); 

   TF1 *func2 = new TF1("func2", BrhoBytof, principle_tof-5, principle_tof+5, 4); 
   func2->SetParameters( PathLength-100, beam->fMass, beam->fZ); 
   func2->SetLineColor(6);  
   func2->Draw("same"); 
   
   TLine lineA;
   lineA.SetLineColor(1);
   lineA.DrawLine(principle_tof-5, Yrange[0]+(slideBin[0]-1)*(Yrange[1]-Yrange[0])/nBin, 
                  principle_tof+5, Yrange[0]+(slideBin[0]-1)*(Yrange[1]-Yrange[0])/nBin);
   TLine lineB;
   lineB.SetLineColor(1);
   lineB.DrawLine( principle_tof-5, Yrange[0]+(slideBin[1])*(Yrange[1]-Yrange[0])/nBin,
                   principle_tof+5, Yrange[0]+(slideBin[1])*(Yrange[1]-Yrange[0])/nBin);

   ctofPPAC->cd(2);
   hTofPPAC->ProjectionX("test",slideBin[0],slideBin[1]);
   TString testTitle;
   testTitle.Form("ProjectX, beam->fBrho = (%10.6f,%10.6f|%10.6f)",
                  Yrange[0]+(slideBin[0]-1)*(Yrange[1]-Yrange[0])/nBin,
                  Yrange[0]+(slideBin[1])*(Yrange[1]-Yrange[0])/nBin,
                  (slideBin[1]-slideBin[0]+1)*(Yrange[1]-Yrange[0])/nBin);
   test->SetTitle(testTitle);
   test->Draw();
   test->Fit("gaus");
   
   TLine line1;
   line1.SetLineColor(2);
   printf("Brho = %f, tof = %f \n", lineBrho, lineTof);
   line1.DrawLine(lineTof,  0, lineTof,  140); 

   return ;
}

Double_t BrhoBytof(Double_t *x, Double_t *para){

   //Double_t Length, Double_t beam->fMass,Int_t beam->fZ

   Double_t arg = TMath::Sqrt(x[0]*x[0]*cVaccum*cVaccum - para[0]*para[0]);
   return para[1]*para[0]/para[2]/cVaccum/arg;

}

Double_t tofByBrho(Double_t *x, Double_t *para){

  //Double_t Length, Double_t mass, , Int_t Z

  Double_t arg ;

}


