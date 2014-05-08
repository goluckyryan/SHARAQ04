#include "constant.h"
#include "RelCalculator.h"
#include "TBeamData.h"

void tplaAna() {
   
   const char* rootfile="Data/phys14Down.root";
   TString detector = "Tpla-L"; //Tpla-L
   TBeamData *beam = new TBeamData("14O");
   Bool_t allentry  = 0;
   Int_t firstEntry = 0;
   Int_t nEntries=500000;
   Double_t TplaBeta = 1/1.5;
   Double_t Qth = 100.;
   Double_t QGate[2] = {1000,1050};
   
//#######################################################   
   Double_t Principle_tof = tofByBrho(L_F3FH9,beam->fBrho, beam->fMass, beam->fZ);
   Int_t detectorID;
   Double_t TdiffRange[2];
   Double_t TplaXRange[2];
   Double_t TplaPMTPos[2];
   Double_t TplaMidPt;
   Double_t Qoffset[2], QGain[2];
   Int_t Sign;
   Double_t sigma[2], Woffset[2];
   Double_t tofoffset;
   Double_t slewOffset;
   
   TClonesArray *hoge_V775, *hoge_MWDC;
   TFile *f = new TFile(rootfile,"read");
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("plaV775",1);
   tree->SetBranchAddress("plaV775",&hoge_V775);
   
   if ( detector == "Tpla-L"){
      tree->SetBranchStatus("smwdc_L",1);
      tree->SetBranchAddress("smwdc_L",&hoge_MWDC);
      detectorID = 0;
      TdiffRange[0] = -15;
      TdiffRange[1] = 5;
      TplaXRange[0] = -1300;
      TplaXRange[1] = 200;
      TplaPMTPos[0] = 200;
      TplaPMTPos[1] = -1300;
      TplaMidPt = -950; 
      Qoffset[0] = -544; Qoffset[1] = -522;
      QGain[0]   = 1.15 ; QGain[1] = 1;
      Sign = -1;
      sigma[0] = 270; sigma[1] = 270;
      Woffset[0] = 0; Woffset[1] = 0;
      tofoffset = beam->fToffset1;
      slewOffset = 10;
   }else{
      tree->SetBranchStatus("smwdc_R",1);
      tree->SetBranchAddress("smwdc_R",&hoge_MWDC);
      detectorID = 1;
      TdiffRange[0] = -9;
      TdiffRange[1] = 11;
      TplaXRange[0] = -200;
      TplaXRange[1] = 1300;
      TplaPMTPos[0] = -200;
      TplaPMTPos[1] = 1300;
      TplaMidPt = 380;
      Qoffset[0] = -552; Qoffset[1] = -472;
      QGain[0]   = 2 ; QGain[1] = 0.86;
      Sign = 1;
      sigma[0] = 250; sigma[1] = 250;
      Woffset[0] = 0; Woffset[1] = 0;
      tofoffset = beam->fToffset2;
      slewOffset = 10;
   }
   
   TH1F* ht1    = new TH1F("ht1", detector + " t1", 200, -240, -180);
   TH1F* ht2    = new TH1F("ht2", detector + " t2", 200, -240, -180);
   ht1->SetLineColor(4);
   ht2->SetLineColor(2);
   TH1F* hQ1    = new TH1F("hQ1", "Q1", 200, 0, 4000);
   TH1F* hQ2    = new TH1F("hQ2", "Q2", 200, 0, 4000);
   hQ1->SetLineColor(4);
   hQ2->SetLineColor(2);
   
   TH1F* ht1new    = new TH1F("ht1new", "t1new = t1 - t1", 200, -10, 20);
   TH1F* ht2new    = new TH1F("ht2new", "t2new = t2 - t1", 200, -10, 20);
   ht1new->SetLineColor(4);
   ht2new->SetLineColor(2);
   
   TH2F* hQTplaX     = new TH2F("hQTplaX"    , "Q1/Q2 vs TplaX"   , 400, TplaXRange[0], TplaXRange[1], 200, 0., 2.5);
   TH2F* hTDiffTplaX = new TH2F("hTDiffTplaX", "tdiff vs TplaX", 400, TplaXRange[0], TplaXRange[1], 200, TdiffRange[0], TdiffRange[1]);
   TH2F* hTDiffNewTplaX = new TH2F("hTDiffNewTplaX", "tdiffNew vs TplaX", 400, TplaXRange[0], TplaXRange[1], 200, TdiffRange[0], TdiffRange[1]);

   TH2F* hDWalkTplaX    = new TH2F("hDWalkTplaX", "DWalk vs TplaX", 400, TplaXRange[0], TplaXRange[1], 200, -5, 5);
   TH2F* hDWalkNewTplaX = new TH2F("hDWalkNewTplaX", "DWalkNew vs TplaX", 400, TplaXRange[0], TplaXRange[1], 200, -5, 5);
   TH2F* hDWalkCal      = new TH2F("hDWalkCal"  , "DWalk vs DWalkCal", 200, -5, 5, 200, -5, 5);

   TString hDWalkFixTitle;
   hDWalkFixTitle.Form("(%5.0f,%5.0f)",QGate[0],QGate[1]);
   TH2F* hDWalkFixQ2 = new TH2F("hDWalkFixQ2", "DWalk vs Q1 | Q2"+hDWalkFixTitle, 200, 0, 3000, 200, -5, 5);
   TH2F* hDWalkFixQ1 = new TH2F("hDWalkFixQ1", "DWalk vs Q2 | Q1"+hDWalkFixTitle, 200, 0, 3000, 200, -5, 5);
   
   TH2F* hDWalkCal1  = new TH2F("hDWalkCal1" , "DWalkCal1 vs Q1", 200, 0, 3000, 200, -5, 5);
   TH2F* hDWalkCal2  = new TH2F("hDWalkCal2" , "DWalkCal2 vs Q2", 200, 0, 3000, 200, -5, 5);
   
   TH1F* htof      = new TH1F("htof"     , detector + " tof(tgt-Tpla)", 200,  5, 30); 
   TH1F* htofnew   = new TH1F("htofnew"  , detector + " tof(tgt-Tpla) w/ Slew Correction", 200, 5, 30); 
   htof->SetLineColor(4);
   htofnew->SetLineColor(2);
   
   TH2F* htofComp  = new TH2F("htofComp", "tof vs tofnew", 200, 5, 30, 200, 5, 30);
   
   TH1F* hW1 = new TH1F("hW1", "W1", 200, 0,20);
   TH1F* hW2 = new TH1F("hW2", "W2", 200, 0,20);
   hW1->SetLineColor(4);
   hW2->SetLineColor(2);
   TH1F* hWavg = new TH1F("hWavg", "(W1+W2)/2", 200, 0, 20);
   TH2F* hW1W2 = new TH2F("hW1W2", "W1 vs W2", 200, 0, 20, 200, 0, 20);
   TH2F* hWavgTof = new TH2F("hWavgTof", "Wavg vs Tof", 200, 5, 30, 200, 1, 20);
   
   TH2F* hW1Q1 = new TH2F("hW1Q1", "W1 vs Q1", 200, 0, 2500, 200, 0, 20);
   TH2F* hW2Q2 = new TH2F("hW2Q2", "W2 vs Q2", 200, 0, 2500, 200, 0, 20);
   

   Int_t Xdiv = 6, Ydiv = 3;
   TCanvas* cTplaAna = new TCanvas("cTplaAna", "Tpla Decay constant", 1200, 100, 300*Xdiv, 300*Ydiv);   
   cTplaAna->Divide(Xdiv, Ydiv);
   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   
//##########################################################################   
   for( Int_t eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID); 
      
      // Get Time and charge
      Double_t Q1 = kInvalidD, Q2 = kInvalidD;
      Double_t t1 = kInvalidD, t2 = kInvalidD;
      Double_t tFH9 = kInvalidD;
      Double_t tF3  = kInvalidD;
      Int_t nHitV775 = hoge_V775->GetEntriesFast();
      for ( Int_t p = 0; p < nHitV775; p++){
         art::TTwoSidedPlasticData * V775Data = (art::TTwoSidedPlasticData*)hoge_V775->At(p);
         Int_t DetID = V775Data->GetDetID();
         if (  DetID == detectorID){
            t1   = V775Data->GetT1();
            t2   = V775Data->GetT2();
            Q1   = (V775Data->GetQ1()+Qoffset[0])*QGain[0]+Qth;
            Q2   = (V775Data->GetQ2()+Qoffset[1])*QGain[1]+Qth;         
         }
         if ( DetID == 2 ) tF3  = V775Data->GetTAve();
         if ( DetID == 3 ) tFH9 = V775Data->GetTAve();
      }
      if ( TMath::IsNaN(tF3) || TMath::IsNaN(tFH9)) continue;
      if ( TMath::IsNaN(t1) || TMath::IsNaN(t2)) continue;
      if ( TMath::IsNaN(Q1) || TMath::IsNaN(Q2)) continue;
      if ( Q2 > 6000 || Q1 > 6000) continue;
      
      // Get MWDC X and A then project to Tpla
      Double_t TplaX = kInvalidD;
      Int_t nHitSMWDC = hoge_MWDC->GetEntriesFast();
      for( Int_t p = 0; p < nHitSMWDC; p++){
         art::TMWDCTrackingResult * smwdc = (art::TMWDCTrackingResult*)hoge_MWDC->At(p);
         art::TTrack * track = (art::TTrack*)smwdc->GetTrack();
         Double_t x = track->GetX();
         Double_t a = track->GetA();
         if ( TMath::Abs(a - x/z0)> 0.1 ) continue;
         TplaX = x + (z0Tpla-z0)*a;
      }
      if ( TMath::IsNaN(TplaX)) continue;
       
      ht1->Fill(t1);
      ht2->Fill(t2);
      hQ1->Fill(Q1);
      hQ2->Fill(Q2);
      
      ht1new->Fill(t1-t1);
      ht2new->Fill(t2-t1);
      Double_t Q0 = TMath::Sqrt(Q1*Q2)*1.445;
      Double_t DWalk = t1-t2 - Sign*2/TplaBeta/cVaccum*(TplaX - TplaMidPt);
      Double_t W1 = WalkFunction(Q1, Q0, sigma[0], Qth)+Woffset[0];
      Double_t W2 = WalkFunction(Q2, Q0, sigma[1], Qth)+Woffset[1];
      hW1->Fill(W1);
      hW2->Fill(W2);
      hW1W2->Fill(W1,W2);
      hWavg->Fill((W1+W2)/2);
      hW1Q1->Fill(Q1,W1);
      hW2Q2->Fill(Q2,W2);
      hQTplaX->Fill(TplaX,Q1/Q2);
      hTDiffTplaX->Fill(TplaX, t1-t2);
      hDWalkTplaX->Fill(TplaX, DWalk);
      hDWalkCal->Fill(W1-W2, DWalk);
      hDWalkNewTplaX->Fill(TplaX, DWalk - (W1-W2));
      hTDiffNewTplaX->Fill(TplaX, t1-t2 - (W1-W2));
      //if ( Q1/Q2> 2.4 ) printf("Q1:%7.2f, Q2:%7.2f, Q0:%7.2f, X%7.2f\n",Q1,Q2,Q0, TplaX);
      if ( Q2 > QGate[0] && Q2 < QGate[1] ) {
         hDWalkFixQ2->Fill(Q1,DWalk);
         hDWalkCal1->Fill(Q1,W1-W2);
      }
      if ( Q1 > QGate[0] && Q1 < QGate[1] ) {
         hDWalkFixQ1->Fill(Q2,DWalk);
         hDWalkCal2->Fill(Q2,W1-W2);
      }
      Double_t tofF3FH9 = tFH9 - tF3 - beam->fToffsetV775 + Principle_tof;
      Double_t tof    = (t1+t2)/2 - tFH9 - tofF3FH9*LENGTH_RATIO_FH9_TGT + tofoffset;
      Double_t tofnew = (t1+t2)/2 - tFH9 - tofF3FH9*LENGTH_RATIO_FH9_TGT + tofoffset - (W1+W2)/2 + slewOffset; 
      
      if ( tof > 0 && tof < 30) {
         htof->Fill(tof);
         htofnew->Fill(tofnew);
      }
      htofComp->Fill(tof,tofnew);
      hWavgTof->Fill(tof, (W1+W2)/2);
   }
   TLatex text;
   text.SetNDC();
   text.SetTextSize(0.04);
   TString textStr;
   
/*   cTplaAna->cd(1);
   ht2->Draw();
   ht1->Draw("same"); 
   cTplaAna->cd(3);
   ht2new->Draw();
   ht1new->Draw("same");
   
*/
   cTplaAna->cd(1);
   hTDiffTplaX->Draw("colz");
   cTplaAna->cd(2);
   hQ1->Draw();
   hQ2->Draw("same");

   text.SetTextColor(4);
   textStr.Form("Q1 offset:%7.2f, gain:%5.2f",Qoffset[0],QGain[0]);
   text.DrawText(0.3, 0.8, textStr);
   text.SetTextColor(2);
   textStr.Form("Q2 offset:%7.2f, gain:%5.2f",Qoffset[1],QGain[1]);
   text.DrawText(0.3, 0.7, textStr);

   cTplaAna->cd(3);
   hDWalkFixQ2->Draw("colz");
   hDWalkCal1->Draw("same");
   
   cTplaAna->cd(4);
   hTDiffNewTplaX->Draw("colz");
   

   cTplaAna->cd(7);
   hDWalkTplaX->Draw("colz");
   cTplaAna->cd(8);
//   hDWalkCal->Draw("colz");
   hQTplaX->Draw("colz");
   
   
   cTplaAna->cd(9);
   hDWalkFixQ1->Draw("colz");
   hDWalkCal2->Draw("same");
   
   cTplaAna->cd(10);
   hDWalkNewTplaX->Draw("colz");
   
   cTplaAna->cd(5);
   hTDiffNewTplaX->ProfileY("test");
   TF1 *fit = new TF1("fit", "pol1(0)", -10, 0); 
   fit->SetParameters(-800,-80);
   test->Fit("fit");
   Double_t para[2];
   fit->GetParameters(para);
   test->Draw("");
   
   Double_t TplaBetaNew = TMath::Abs(2*para[1]/cVaccum);
   text.SetTextColor(1);
   textStr.Form("Tpla Beta:%4.2f",TplaBetaNew);
   text.DrawText(0.2, 0.2, textStr);
   
   cTplaAna->cd(11);
   hTDiffNewTplaX->ProjectionY("resol", 199, 201);
   Double_t TplaXWidth = 3*(TplaXRange[1]-TplaXRange[0])/400;
   TF1 *fitResol = new TF1("fitResol", "gaus(0)", -10, 0); 
   fitResol->SetParameters(100, -6 , 0.5);
   resol->Fit("fitResol");
   Double_t paraRes[3];
   fitResol->GetParameters(paraRes);
   resol->Draw();
   
   textStr.Form("Tavg Resol:%6.0f ps",TMath::Sqrt(TMath::Power(paraRes[2],2)-TMath::Power(2*TplaXWidth/TplaBetaNew/cVaccum,2))*1000.);
   text.DrawText(0.3, 0.65, textStr);
   
   cTplaAna->cd(6);
   htofComp->Draw("colz");
   cTplaAna->cd(12);
   htof->Draw("");
   htofnew->Draw("same");
   
   cTplaAna->cd(13);
   hW1->Draw();
   hW2->Draw("same");
   cTplaAna->cd(14);
   hW1W2->Draw("colz");
   cTplaAna->cd(15);
   hWavg->Draw();
   cTplaAna->cd(16);
   hWavgTof->Draw("colz");
   
   cTplaAna->cd(17);
   hW1Q1->Draw("colz");
   cTplaAna->cd(18);
   hW2Q2->Draw("colz");

   
  
   return ;
}

Double_t WalkFunction(Double_t Q, Double_t Q0, Double_t sigma, Double_t Qth){
   //return sigma*(-TMath::Sqrt(2*TMath::Log(Q/Qth)) + TMath::Sqrt(2*TMath::Log(Q0/Qth)));
   return sigma/TMath::Power(Q,0.5) ;
}


