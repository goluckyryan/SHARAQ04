#include "constant.h"
#include "RelCalculator.h"
#include "Compress/TBeamData.h"

void tplaSlew() {
   
   const char* rootfile="ppAll_0731.root";
   TString detector = "Tpla-R"; //Tpla-L
   TBeamData *beam = new TBeamData("proton");
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=5000000;
   Double_t TplaBeta = 1/1.5;
   Double_t Qth = 100.;
   Double_t XGate[2] = { -600,   2000}; //central, half-width
   Double_t QGate[2] = {   00, 9900};
   
   printf("\n >>>>> file: %s \n", rootfile); 

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
   
//========================================================   
   TClonesArray *hoge_V775, *hoge_L, *hoge_R;
   TFile *f = new TFile(rootfile,"read");
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("plaV775",1);
   tree->SetBranchAddress("plaV775",&hoge_V775);
   tree->SetBranchStatus("smwdc_L",1);
   tree->SetBranchAddress("smwdc_L",&hoge_L);
   tree->SetBranchStatus("smwdc_R",1);
   tree->SetBranchAddress("smwdc_R",&hoge_R);
   
   if ( detector == "Tpla-L"){
      detectorID = 0;
      TdiffRange[0] = -15;
      TdiffRange[1] = 5;
      TplaXRange[0] = -1300;
      TplaXRange[1] = 200;
      TplaPMTPos[0] = 200;
      TplaPMTPos[1] = -1300;
      TplaMidPt = -950; 
      //Qoffset[0] = -544; Qoffset[1] = -522;
      //QGain[0]   = 1.15 ; QGain[1] = 1;

      Qoffset[0] = 0; Qoffset[1] = 0;
      QGain[0]   = 1 ; QGain[1] = 1;
      Sign = -1;
      sigma[0] = 270; sigma[1] = 270;
      Woffset[0] = 0; Woffset[1] = 0;
      tofoffset = beam->fToffset1;
      slewOffset = 10;
   }else{
      
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
   
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;

//========================================================    

   //gStyle->SetOptStat(0);
   TH1F* ht1    = new TH1F("ht1", detector + " t1", 200, -240, -180);
   TH1F* ht2    = new TH1F("ht2", detector + " t2", 200, -240, -180);
   ht1->SetLineColor(4);
   ht2->SetLineColor(2);
   TH1F* hQ1    = new TH1F("hQ1", "Q1", 200, 0, 4000);
   TH1F* hQ2    = new TH1F("hQ2", "Q2", 200, 0, 4000);
   hQ1->SetLineColor(4);
   hQ2->SetLineColor(2);

   TH2F* hQ1Q2 = new TH2F("hQ1Q2", "Q2 vs Q1 g:TplaX", 200, 0, 4000, 200, 0, 4000);
   
   TString hTplaXgTitle;
   hTplaXgTitle.Form("(%7.1f, %7.1f)", XGate[0]-XGate[1], XGate[0]+XGate[1]);
   TH1F* hTplaX  = new TH1F("hTplaX" , "TplaX"+hTplaXgTitle        , 400, TplaXRange[0],TplaXRange[1]);
   TH1F* hTplaXg = new TH1F("hTplaXg", "TplaX g:TplaX"+hTplaXgTitle, 400, TplaXRange[0],TplaXRange[1]);
   hTplaXg->SetLineColor(2);
   
   TH2F* hQ1tof1 = new TH2F("hQ1tof1", "Q1 vs (tavg - t1)", 100, -4, 8, 200, 0, 3500);
   TH2F* hQ2tof2 = new TH2F("hQ2tof2", "Q2 vs (t2 - tavg)", 100, -4, 8, 200, 0, 3500);
   
   TString hQtofTitle;
   hQtofTitle.Form("(%7.1f,%7.1f)", QGate[0], QGate[1]);
   TH2F* hQ1tof1g = new TH2F("hQ1tof1g", "Q1 vs (tavg - t1) g:TplaX Q2"+hQtofTitle, 200, -4,  8, 200, 0, 3500);
   TH2F* hQ2tof2g = new TH2F("hQ2tof2g", "Q2 vs (t2 - tavg) g:TplaX Q1"+hQtofTitle, 200, -4,  8, 200, 0, 3500);

   TH2F* hSlew = new TH2F("hSlew", "Q1 vs Slew", 200, 0, 3500, 100, 0, 10);

   TH2F* hQ1tof1gSlew = new TH2F("hQ1tof1gSlew", "Q1 vs (tavg - t1) g:TplaX Slew", 200,  -4, 8, 200, 0, 3500);
   TH2F* hQ2tof2gSlew = new TH2F("hQ2tof2gSlew", "Q2 vs (t2 - tavg) g:TplaX Slew", 200,  -4, 8, 200, 0, 3500);
   
   Int_t Xdiv = 3, Ydiv = 2;
   TCanvas* cTplaSlew = new TCanvas("cTplaSlew", "Tpla Slew", 10, 30, 400*Xdiv, 400*Ydiv);   
   cTplaSlew->Divide(Xdiv, Ydiv);

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

      // Get MWDC X and A then project to Tpla
      Double_t TplaX1 = kInvalidD;
//      Double_t TplaX2 = kInvalidD;
      Double_t x1, x2, a1, a2;
      Int_t nHitSMWDC = hoge_L->GetEntriesFast();
      for( Int_t p = 0; p < nHitSMWDC; p++){
         art::TMWDCTrackingResult * smwdc = (art::TMWDCTrackingResult*)hoge_L->At(p);
         art::TTrack * track = (art::TTrack*)smwdc->GetTrack();
         x1 = track->GetX();
         a1 = track->GetA();
         if ( TMath::Abs(a1 - x1/z0)> 0.1 ) continue;
         TplaX1 = x1 + (z0Tpla-z0)*a1;
      }
      if ( TMath::IsNaN(TplaX1) ) continue;
      if ( TMath::Abs(TplaX1 - XGate[0])> XGate[1] ) continue;
      
/*      Int_t nHitSMWDC = hoge_R->GetEntriesFast();
      for( Int_t p = 0; p < nHitSMWDC; p++){
         art::TMWDCTrackingResult * smwdc = (art::TMWDCTrackingResult*)hoge_R->At(p);
         art::TTrack * track = (art::TTrack*)smwdc->GetTrack();
         x2 = track->GetX();
         a2 = track->GetA();
         if ( TMath::Abs(a2 - x2/z0)> 0.1 ) continue;
         TplaX2 = x2 + (z0Tpla-z0)*a2;
      }
      if (TMath::IsNaN(TplaX2) ) continue;*/
      
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
            Q1   = V775Data->GetQ1()*QGain[0]+Qoffset[0];
            Q2   = V775Data->GetQ2()*QGain[1]+Qoffset[1];         
         }
         if ( DetID == 2 ) tF3  = V775Data->GetTAve();
         if ( DetID == 3 ) tFH9 = V775Data->GetTAve();
      }
      if ( TMath::IsNaN(tF3) || TMath::IsNaN(tFH9)) continue;
      if ( TMath::IsNaN(t1) || TMath::IsNaN(t2)) continue;
      if ( TMath::IsNaN(Q1) || TMath::IsNaN(Q2)) continue;
      if ( Q2 > 6000 || Q1 > 6000) continue;
      
       
      ht1->Fill(t1);
      ht2->Fill(t2);
      hQ1->Fill(Q1);
      hQ2->Fill(Q2);
      hTplaX->Fill(TplaX1);
 
      Double_t tofF3FH9 = tFH9 - tF3 - beam->fToffsetV775 + Principle_tof;
      Double_t tof    = (t1+t2)/2 - tFH9 - tofF3FH9*LENGTH_RATIO_FH9_TGT; 
      Double_t tavg   = (t1+t2)/2;     
      
      Double_t tof1 = tavg - t1;
      Double_t tof2 = t2 - tavg;
      hQ1tof1->Fill(tof1, Q1);
      hQ2tof2->Fill(tof2, Q2);

      // Slew correction
      Double_t Cslew = 4000;
      Double_t Pslew = 1;
      Double_t slew1 = Cslew/TMath::Power(Q1,Pslew) ;
      Double_t slew2 = Cslew/TMath::Power(Q2,Pslew) ;
      Double_t t1Slew = t1 + slew1;
      Double_t t2Slew = t2 + slew2;
      Double_t tavgSlew = (t1Slew+t2Slew)/2;
      Double_t tof1Slew = tavgSlew - t1Slew;
      Double_t tof2Slew = t2Slew - tavgSlew;

      hSlew->Fill(Q1, slew1);
      
      if ( TMath::Abs(TplaX1 - XGate[0])< XGate[1] ) {

         hTplaXg->Fill(TplaX1);   

         hQ1Q2->Fill(Q1,Q2);

         hQ1tof1gSlew->Fill(tof1Slew, Q1);
         hQ2tof2gSlew->Fill(tof2Slew, Q2);

         if ( Q2 > QGate[0] &&  Q2 < QGate[1]) hQ1tof1g->Fill(tof1, Q1);
         if ( Q1 > QGate[0] &&  Q1 < QGate[1]) hQ2tof2g->Fill(tof2, Q2);
                  
      }

      //------------Clock      
      clock.Stop("timer");
      Double_t time = clock.GetRealTime("timer");
      clock.Start("timer");
      
      if ( !shown ) {
         if (fmod(time, 10) < 1 ){
            printf( "%10d[%2d%%] |%3d min %5.2f sec | expect:%5.1fmin\n", 
            eventID, 
            TMath::Nint((eventID+1-firstEntry)*100./nEntries),
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

   TLatex text;
   text.SetNDC();
   text.SetTextSize(0.04);
   TString textStr;

/*   cTplaSlew->cd(1);
   hQ1->Draw();
   hQ2->Draw("same");

   text.SetTextColor(4);
   textStr.Form("Q1 offset:%7.2f, gain:%5.2f",Qoffset[0],QGain[0]);
   text.DrawText(0.3, 0.8, textStr);
   text.SetTextColor(2);
   textStr.Form("Q2 offset:%7.2f, gain:%5.2f",Qoffset[1],QGain[1]);
   text.DrawText(0.3, 0.7, textStr);
   
   cTplaSlew->cd(2);
   hQ1tof1->Draw("colz");
   
   cTplaSlew->cd(3);
   hQ2tof2->Draw("colz");*/
   
   cTplaSlew->cd(1);
   hTplaX->Draw("");
   hTplaXg->Draw("same");

   cTplaSlew->cd(2);
   hQ1tof1g->Draw("colz");
   
   cTplaSlew->cd(3);
   hQ2tof2g->Draw("colz");
   
   cTplaSlew->cd(4);
   //hQ1Q2->Draw("colz");
   hSlew->Draw("colz");
   
   cTplaSlew->cd(5);
   hQ1tof1gSlew->Draw("colz");
   
   cTplaSlew->cd(6);
   hQ2tof2gSlew->Draw("colz");
     
  
   return ;
}

