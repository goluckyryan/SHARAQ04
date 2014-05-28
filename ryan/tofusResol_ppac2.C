#include "constant.h"
#include "RelCalculator.h"
#include "TBeamData.h"

void tofusResol_ppac2() {
   
   Int_t eventID;
   Long64_t totnumEntry;
   
   const char* rootfile="PrimaryData/phys14Up.root";
   TString detector = "V775"; // either V1190 or V775
   TBeamData *beam = new TBeamData("14O");
   Double_t PathLength = L_F3FH9+000;
   
   Bool_t S0Gate = 1;
   Double_t AGate = 0.005;
   Double_t BGate = 0.005;
   
   Bool_t allentry  = 0;
   Int_t firstEntry = 0;
   Int_t nEntries=5000000;
   Int_t nBin = 200;
   Int_t BinWidth = 3; // should be odd number

//============================================
   gStyle->SetOptStat(0);
   Double_t Xrange[2] = {beam->fBrho-0.07, beam->fBrho+0.07};
   Double_t principle_tof = tofByBrho(PathLength, beam->fBrho, beam->fMass,beam->fZ);
   
   TString hTofPPACTitle;
   hTofPPACTitle.Form("%s | tof_us(%s) vs PPAC(X)",rootfile, detector.Data());  
   TH2F* hTofPPAC = new TH2F("hTofPPAC",hTofPPACTitle, nBin , Xrange[0], Xrange[1], 300, principle_tof-5, principle_tof+5);
   hTofPPAC->SetYTitle("Tof us[ns]");
   hTofPPAC->SetXTitle("Brho [mT]");
   
   TString hTdiffBrhoTitle;
   hTdiffBrhoTitle.Form("Tof(Brho) - Tof(mean) | binWidth:%1d = BrhoWidth:%7.5f", BinWidth, hTofPPAC->GetBinWidth(1)*BinWidth);
   TH1F* hTdiffBrho = new TH1F("hTdiffBrho", hTdiffBrhoTitle, nBin , Xrange[0], Xrange[1]);
   hTofPPAC->SetXTitle("Brho [mT]");

   TCanvas* ctofPPAC = new TCanvas("ctofPPAC", "tof upstream by PPAC", 1000, 0, 800, 800);   
   ctofPPAC->Divide(1,2);
//============================================
   TClonesArray *hoge_tof, *hoge_ppac, *hoge_S0img;
   TFile *f = new TFile(rootfile,"read");
   TTree *pid = (TTree*)f->Get("tree");
   totnumEntry = pid->GetEntries();
   pid->SetBranchStatus("*",0);
   pid->SetBranchStatus("ppac",1);
   pid->SetBranchAddress("ppac",&hoge_ppac);
   
   if ( S0Gate){
      printf("S0 AB gate on. \n");
   	pid->SetBranchStatus("S0img",1);
   	pid->SetBranchAddress("S0img", &hoge_S0img); 
   }
   
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
      
      // Get S0img
      if (S0Gate){
      	Int_t nHit0 = hoge_S0img->GetEntriesFast();
      	Double_t S0A, S0B;
      	Int_t tracked = 0; 
      	for (Int_t p = 0; p < nHit0; p++){
         	art::TMWDCTrackingResult * xyS0 = (art::TMWDCTrackingResult*)hoge_S0img->At(p);
         	tracked = xyS0->GetTrackingID();
         	if (tracked != 1) continue;
         	art::TTrack * trackS0 = (art::TTrack*)xyS0->GetTrack();
         	S0A = trackS0->GetA();
         	S0B = trackS0->GetB(); 
      	}
      	if (tracked != 1) continue;
      	if (TMath::Abs(S0A) > AGate || TMath::Abs(S0B) > BGate ) continue;
      }
      
      //Get PPAC fX
      Int_t nHit1 =hoge_ppac->GetEntriesFast();
      if (nHit1 < 1) continue;
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
               hTofPPAC->Fill(beam->fBrho*(1+ppacX[p]/7500),tof[q]- beam->fToffsetV1190 +principle_tof);
            }else{
               if (detID[q] == 2){
                  hTofPPAC->Fill(beam->fBrho*(1+ppacX[p]/7500),tof[q]+ beam->fToffsetV775 +principle_tof);
               }
            }
         }
      }
     
      delete ppacX;
      delete tof;
      delete detID;

   }
   
   TLatex text;
   text.SetTextColor(1);
   text.SetNDC();
   TString strText;
   
   ctofPPAC->cd(1);
   hTofPPAC->Draw("colz");
   
   strText.Form("S0AB Gated. |A|<%5.3f , |B|<%5.3f", AGate, BGate);
   if( S0Gate) text.DrawText(0.2, 0.2, strText);

   TF1 *func = new TF1("func", testFunc, Xrange[0], Xrange[1], 3); 
   func->SetParameters( PathLength, beam->fMass, beam->fZ); 
   func->SetLineColor(4);  
   func->SetLineWidth(1);
   func->Draw("same"); 

   TF1 *func1 = new TF1("func1", testFunc, Xrange[0], Xrange[1], 3); 
   func1->SetParameters( PathLength+100, beam->fMass, beam->fZ); 
   func1->SetLineColor(6);  
   func1->Draw("same"); 

   TF1 *func2 = new TF1("func2", testFunc, Xrange[0], Xrange[1], 3); 
   func2->SetParameters( PathLength-100, beam->fMass, beam->fZ); 
   func2->SetLineColor(6);  
   func2->Draw("same"); 
   
   TLine lineA;
   lineA.SetLineColor(1);
   lineA.DrawLine( hTofPPAC->GetBinLowEdge(nBin/2), principle_tof-5,
                   hTofPPAC->GetBinLowEdge(nBin/2), principle_tof+5);
   TLine lineB;
   lineB.SetLineColor(1);
   lineB.DrawLine( hTofPPAC->GetBinLowEdge(nBin/2+BinWidth), principle_tof-5,
                   hTofPPAC->GetBinLowEdge(nBin/2+BinWidth), principle_tof+5);

   ctofPPAC->cd(2);
   
   for( Int_t binID = 1; binID <= nBin ; binID += BinWidth){
   	hTofPPAC->ProjectionY("test",binID,binID+BinWidth);
   	if(test->GetEntries() < 100 ) continue;
   	test->Fit("gaus","Q");
   	
   	Double_t testBrho = (hTofPPAC->GetBinLowEdge(binID) + hTofPPAC->GetBinLowEdge(binID + BinWidth))/2;
   	Double_t testTof = tofByBrho(PathLength, testBrho, beam->fMass, beam->fZ);
   
   	Double_t mean = test->GetFunction("gaus")->GetParameter(1);
   	Double_t sigma = test->GetFunction("gaus")->GetParameter(2);
   	
   	if(sigma > 0.5) continue;
   	
   	//printf("Bin:(%d[%5.3f],%d[%5.3f]) D:%7.5f, testBrho:%5.3f \n", binID, hTofPPAC->GetBinLowEdge(binID), binID + BinWidth, hTofPPAC->GetBinLowEdge(binID + BinWidth) , hTofPPAC->GetBinWidth(1), testBrho);
   	
   	hTdiffBrho->Fill(testBrho, mean-testTof);
   	hTdiffBrho->SetBinError(binID+BinWidth/2, sigma);
   }
   
   hTdiffBrho->Draw("E");
   

   return ;
}

Double_t BrhoBytof(Double_t *x, Double_t *para){

   //para[0] = Length
   //para[1] = Mass
   //para[2] = Z
	
  Double_t beta = para[0]/cVaccum/x[0];
  Double_t gamma = 1/TMath::Sqrt(1-beta*beta);
  return gamma*beta*para[1]/para[2]/cVaccum;

}

Double_t testFunc(Double_t *x, Double_t *para){

  //para[0] = Length
  //para[1] = Mass
  //para[2] = Z

  Double_t alpha = para[2]*x[0]*cVaccum/para[1]; // alpha = gamma*beta
  Double_t beta = alpha/TMath::Sqrt(1+alpha*alpha);
  
  return para[0]/cVaccum/beta;

}


