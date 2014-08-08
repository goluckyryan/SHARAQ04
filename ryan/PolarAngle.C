#include "constant.h"
#include "RelCalculator.h"

void PolarAngle() {
   const char* rootfile="ppAll_0731.root";
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=1000;

   Double_t PlaBeta = 1/1.5;

   
   printf("\n >>>>> file: %s \n", rootfile); 

//#######################################################   
   Double_t Principle_tof = tofByBrho(L_F3FH9,2.4781, mp, 1);
   Int_t PlaDetID;
   Double_t TDiffRange[2];
   Double_t PlaXRange[2];
   Double_t PMTPos[2];
   Double_t Qoffset[2], QGain[2];
   Int_t Sign;
   Double_t sigma[2], Woffset[2];
   char* plaBranch;
   char* mwdcBranch;
   
//========================================================   
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;

   TClonesArray *hoge_mwdcL, *hoge_mwdcR;
   art::sh04::TP2PKinematicsData* hoge_p2p;
   TFile *f = new TFile(rootfile,"read");
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("smwdc_R",1);
   tree->SetBranchAddress("smwdc_R",&hoge_mwdcR);
   tree->SetBranchStatus("smwdc_L",1);
   tree->SetBranchAddress("smwdc_L",&hoge_mwdcL);
   tree->SetBranchStatus("p2p",1);
   tree->SetBranchAddress("p2p",&hoge_p2p);

//========================================================    

   gStyle->SetOptStat(0);

   Int_t Xdiv = 3, Ydiv = 3;
   TCanvas* cPolarAngle = new TCanvas("cPolarAngle", "Slew Correction", 2000, 0, 300*Xdiv, 300*Ydiv);   
   cPolarAngle->Divide(Xdiv, Ydiv);
   
   TH2F* hThetaL = new TH2F("hThetaL", "#theta^{L}_{XY} vs #theta^{L}_{AB}", 200, 20, 70, 200, 20, 70);
   TH2F* hPhiL = new TH2F("hPhiL", "#phi^{L}_{XY} vs #phi^{L}_{AB}", 200, -50, 50, 200, -50, 50);
   
   TH2F* hThetaR = new TH2F("hThetaR", "#theta^{R}_{XY} vs #theta^{R}_{AB}", 200, 20, 70, 200, 20, 70);
   TH2F* hPhiR = new TH2F("hPhiR", "#phi^{R}_{XY} vs #phi^{R}_{AB}", 200, 130, 230, 200, 130, 230);
   
   TH2F* hOpenTheta = new TH2F("hOpenTheta", "#Delta#theta_{XY} vs #Delta#theta_{AB}", 150, 70, 100, 150, 70, 100);
   TH2F* hOpenPhi = new TH2F("hOpenPhi", "#Delta#phi_{XY} vs #Delta#phi_{AB}", 200, -50, 50, 200, -50, 50);

   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   
   const Double_t cos = cos(60.*TMath::DegToRad());
   const Double_t sin = sin(60.*TMath::DegToRad());
   const Double_t B = 0.065; // T
   const Double_t rho  = 0.11; // m
   
//##########################################################################   
   for( Int_t eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID); 

      //********************* Get MWDC X and A then project to Tpla
      Double_t x1, a1, y1, b1;
      Double_t x2, a2, y2, b2;
      Int_t nHitSMWDCL = hoge_mwdcL->GetEntriesFast();
      if ( nHitSMWDCL == 0 ) continue;
      for( Int_t p = 0; p < nHitSMWDCL; p++){
         art::TMWDCTrackingResult * smwdc_L = (art::TMWDCTrackingResult*)hoge_mwdcL->At(p);
         art::TTrack * track = (art::TTrack*)smwdc_L->GetTrack();
         x1 = track->GetX();
         a1 = track->GetA();
         y1 = track->GetY();
         b1 = track->GetB();
      }
      
      Int_t nHitSMWDCR = hoge_mwdcR->GetEntriesFast();
      if ( nHitSMWDCR == 0 ) continue;
      for( Int_t p = 0; p < nHitSMWDCR; p++){
         art::TMWDCTrackingResult * smwdc_R = (art::TMWDCTrackingResult*)hoge_mwdcR->At(p);
         art::TTrack * track = (art::TTrack*)smwdc_R->GetTrack();
         x2 = track->GetX();
         a2 = track->GetA();
         y2 = track->GetY();
         b2 = track->GetB();
      }

      //*********************** Get theta from p2p
      Double_t theta1 = hoge_p2p->GetRecoilL()->Theta()*TMath::RadToDeg();
      Double_t theta2 = hoge_p2p->GetRecoilR()->Theta()*TMath::RadToDeg();
      Double_t Sp = hoge_p2p->GetSp();
      Double_t phi1 = hoge_p2p->GetRecoilL()->Phi()*TMath::RadToDeg();
      Double_t phi2 = hoge_p2p->GetRecoilR()->Phi()*TMath::RadToDeg();
      Double_t momt1 = hoge_p2p->GetRecoilL()->P();
      Double_t momt2 = hoge_p2p->GetRecoilR()->P();
      
      //printf("%.2f \n", momt1);
      
      if ( phi2 < 0 ) phi2 += 360.;

      //*********************** Calculate polar angle from AB
      Double_t theta1_AB = acos((cos - sin*a1)/sqrt(a1*a1+b1*b1+1))*TMath::RadToDeg();
      Double_t phi1_AB   = atan2(b1,(sin + cos*a1))*TMath::RadToDeg();
      Double_t theta2_AB = acos((cos + sin*a2)/sqrt(a2*a2+b2*b2+1))*TMath::RadToDeg();
      Double_t phi2_AB   = atan2(b2,(-sin + cos*a2))*TMath::RadToDeg();
      
      if ( phi2_AB < 0 ) phi2_AB += 360.;
      
      //----------------- magnetic filed correction
      theta1_AB -= rho*B*cVaccum/momt1;
      theta2_AB -= rho*B*cVaccum/momt2;
      
      //printf("L: theta:(%.2f,%.2f) , theta_AB:(%.2f,%.2f) \n", theta1, phi1, theta1_AB, phi1_AB);
      //printf("R: theta:(%.2f,%.2f) , theta_AB:(%.2f,%.2f) \n", theta2, phi2, theta2_AB, phi2_AB);
		
		//************* Cut
		//if ( abs(theta1 - theta1_AB)>2 || abs(theta2 - theta2_AB)>2 ) continue;
		//if ( abs(phi1 - phi1_AB)>5 || abs(phi2 - phi2_AB)>7 ) continue;
		
		//************************ Fill histogram
		hThetaL->Fill(theta1, theta1_AB);
		hThetaR->Fill(theta2, theta2_AB);
		
		hPhiL->Fill(phi1, phi1_AB);
		hPhiR->Fill(phi2, phi2_AB);
		
		hOpenTheta->Fill(theta1+theta2, theta1_AB+theta2_AB);
		hOpenPhi->Fill(TMath::Abs(phi1-phi2)-180, TMath::Abs(phi1_AB-phi2_AB)-180);

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

	//***** COl 1
   cPolarAngle->cd(1);
	hThetaL->Draw("colz");
	
	cPolarAngle->cd(4);
	hPhiL->Draw("colz");
	
	cPolarAngle->cd(7);
	hOpenTheta->Draw("colz");

   
   //******* COl 2
   cPolarAngle->cd(2);
   hThetaR->Draw("colz");
	
	cPolarAngle->cd(5);
	hPhiR->Draw("colz");
	
	cPolarAngle->cd(8);
	hOpenPhi->Draw("colz");
	
	
   //******* COl 3
   cPolarAngle->cd(3);
	
	cPolarAngle->cd(6);
	hOpenTheta->ProjectionX("hOpenTheta_XY");
	hOpenTheta->ProjectionY("hOpenTheta_AB");
	hOpenTheta_AB->SetLineColor(kRed);
	hOpenTheta_AB->SetMinimum(0);
	hOpenTheta_AB->Draw();
	hOpenTheta_XY->Draw("same");
	
	cPolarAngle->cd(9);
	hOpenPhi->ProjectionX("hOpenPhi_XY");
	hOpenPhi->ProjectionY("hOpenPhi_AB");
	hOpenPhi_AB->SetLineColor(kRed);
	hOpenPhi_XY->Draw();
	hOpenPhi_AB->Draw("same");


   return ;
}

