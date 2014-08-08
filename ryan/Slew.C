#include "constant.h"
#include "RelCalculator.h"

void Slew() {
   const char* rootfile="ppAll_0731.root";
   //const char* rootfile="25F_0728.root";
   TString detector = "Tpla-L"; //Tpla-L, Tpla-R
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
   if ( detector == "Tpla-L"){
      PlaDetID = 0;
      plaBranch = "plaV775";
      mwdcBranch = "smwdc_L";
      TDiffRange[0] = -15;
      TDiffRange[1] = 5;
      PlaXRange[0] = -1300;
      PlaXRange[1] = 200;
      PMTPos[0] = 200;
      PMTPos[1] = -1300;
      //Qoffset[0] = -544; Qoffset[1] = -522;
      //QGain[0]   = 1.15 ; QGain[1] = 1;

      Qoffset[0] = 0; Qoffset[1] = 0;
      QGain[0]   = 1 ; QGain[1] = 1;
      Sign = -1;
      sigma[0] = 270; sigma[1] = 270;
      Woffset[0] = 0; Woffset[1] = 0;
   }else if (detector == "Tpla-R"){
      PlaDetID = 1;
      plaBranch = "plaV775";
      mwdcBranch = "smwdc_R";
      TDiffRange[0] = -9;
      TDiffRange[1] = 11;
      PlaXRange[0] = -200;
      PlaXRange[1] = 1300;
      PMTPos[0] = -200;
      PMTPos[1] = 1300;
      Qoffset[0] = -850; Qoffset[1] = 0;
      QGain[0]   = 2.33 ; QGain[1] = 1;
      
      /*Qoffset[0] = 0; Qoffset[1] = 0;
      QGain[0]   = 1 ; QGain[1] = 1;
      */
      Sign = 1;
      sigma[0] = 250; sigma[1] = 250;
      Woffset[0] = 0; Woffset[1] = 0;
   }
   
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;

   TClonesArray *hoge_pla, *hoge_mwdc;
   art::sh04::TP2PKinematicsData* hoge_p2p;
   TFile *f = new TFile(rootfile,"read");
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus(plaBranch,1);
   tree->SetBranchAddress(plaBranch,&hoge_pla);
   tree->SetBranchStatus(mwdcBranch,1);
   tree->SetBranchAddress(mwdcBranch,&hoge_mwdc);
   tree->SetBranchStatus("p2p",1);
   tree->SetBranchAddress("p2p",&hoge_p2p);

//========================================================    

   gStyle->SetOptStat(0);
   TH1F* hQ1    = new TH1F("hQ1", "Q1", 200, 0, 4000);
   TH1F* hQ2    = new TH1F("hQ2", "Q2", 200, 0, 4000);
   hQ1->SetLineColor(4);
   hQ2->SetLineColor(2);

	Double_t QRange[2] = {500,2500};
   TH2F* hQ1Q2 = new TH2F("hQ1Q2", "Q2 vs Q1 ", 100, QRange[0], QRange[1], 100, QRange[0], QRange[1]);
   TH1F* hLogQ = new TH1F("hLogQ", "Log(Q2/Q1)", 100, -1, 1); 
   TH2F* hLogQPlaX = new TH2F("hLogQPlaX", "Log(Q2/Q1) vs TDiff", 100, PlaXRange[0], PlaXRange[1], 100, -1,1 );

   TH2F* hQ1E1 = new TH2F("hQ1E1", "Q1 vs E1", 100, -50, 250, 100, QRange[0], QRange[1]);
   TH2F* hQ2E2 = new TH2F("hQ2E2", "Q2 vs E2", 100, -50, 250, 100, QRange[0], QRange[1]);

   TH1F* hPlaX  = new TH1F("hPlaX" , "PlaX"  , 100, PlaXRange[0], PlaXRange[1]);
   
   TH1F* hDecay = new TH1F("hDecay", "Decay constant [mm]", 100, 1000, 5000);
   
   Double_t Range[2] = {-10, 10};
   TH2F* hQ1t1 = new TH2F("hQ1t1", "Q1 vs T1 " , 100, Range[0], Range[1], 100, QRange[0], QRange[1]);
   TH2F* hQ2t2 = new TH2F("hQ2t2", "Q2 vs T2 " , 100, Range[0], Range[1], 100, QRange[0], QRange[1]);

   TH2F* hSlew1 = new TH2F("hSlew1", "Q vs |Slew|", 100, QRange[0], QRange[1], 100, 0, 10);
   TH2F* hSlew2 = new TH2F("hSlew2", "Q vs |Slew|", 100, QRange[0], QRange[1], 100, 0, 10);
   
   TH2F* hQ1t1Slew = new TH2F("hQ1t1Slew", "Q1 vs tavg | Slew", 100, Range[0], Range[1], 100, QRange[0], QRange[1]);
   TH2F* hQ2t2Slew = new TH2F("hQ2t2Slew", "Q2 vs tavg | Slew", 100, Range[0], Range[1], 100, QRange[0], QRange[1]);

   TH1F* hOpenAng = new TH1F("hOpenAng", "OpenAng", 100, 80, 92);
   TH1F* hOpenAng2 = new TH1F("hOpenAng2", "OpenAng2", 100, 80, 92);
   
   TH2F* hPlaXt1 = new TH2F("hPlaXt1", "PlaX vs t1", 100, Range[0], Range[1], 100, PlaXRange[0], PlaXRange[1]);
   TH2F* hPlaXQ1 = new TH2F("hPlaXQ1", "PlaX vs Q1", 100, QRange[0], QRange[1], 100 , PlaXRange[0], PlaXRange[1]);

	TH2F* hPlaXt2 = new TH2F("hPlaXt2", "PlaX vs t2", 100, Range[0], Range[1], 100, PlaXRange[0], PlaXRange[1]);
   TH2F* hPlaXQ2 = new TH2F("hPlaXQ2", "PlaX vs Q2", 100, QRange[0], QRange[1], 100 , PlaXRange[0], PlaXRange[1]);

   Int_t Xdiv = 5, Ydiv = 3;
   //if( gROOT->FindObject("cSlew")) delete cSlew;
   TCanvas* cSlew = new TCanvas("cSlew", "Slew Correction", 2000, 0, 300*Xdiv, 300*Ydiv);   
   cSlew->Divide(Xdiv, Ydiv);
   

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

      //********************* Get MWDC X and A then project to Tpla
      Double_t PlaX = kInvalidD;
      Double_t x1, a1;
      Int_t nHitSMWDC = hoge_mwdc->GetEntriesFast();
      for( Int_t p = 0; p < nHitSMWDC; p++){
         art::TMWDCTrackingResult * smwdc = (art::TMWDCTrackingResult*)hoge_mwdc->At(p);
         art::TTrack * track = (art::TTrack*)smwdc->GetTrack();
         x1 = track->GetX();
         a1 = track->GetA();
         if ( TMath::Abs(a1 - x1/z0)> 0.1 ) continue;
         PlaX = x1 + (z0Tpla-z0)*a1;
      }
      //printf("%f \n",PlaX);
      if ( TMath::IsNaN(PlaX) ) continue;
      
      //********************* Get Time and charge
      Double_t Q1 = kInvalidD, Q2 = kInvalidD;
      Double_t t1 = kInvalidD, t2 = kInvalidD;
      Double_t tFH9 = kInvalidD;
      Double_t tF3  = kInvalidD;
      Int_t nHitV775 = hoge_pla->GetEntriesFast();
      for ( Int_t p = 0; p < nHitV775; p++){
         art::TTwoSidedPlasticData * V775Data = (art::TTwoSidedPlasticData*)hoge_pla->At(p);
         Int_t DetID = V775Data->GetDetID();
         if (  DetID == PlaDetID){
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

      //*********************** Get theta from p2p
      Double_t theta1 = hoge_p2p->GetRecoilL()->Theta()*TMath::RadToDeg();
      Double_t theta2 = hoge_p2p->GetRecoilR()->Theta()*TMath::RadToDeg();
      Double_t Sp = hoge_p2p->GetSp();
      Double_t phi1 = hoge_p2p->GetRecoilL()->Phi()*TMath::RadToDeg();
      Double_t phi2 = hoge_p2p->GetRecoilR()->Phi()*TMath::RadToDeg();
      Double_t E;
      if ( detector == "Tpla-L"){ 
      	E = hoge_p2p->GetRecoilL()->E()-mp;
     	}else{
     		E = hoge_p2p->GetRecoilR()->E()-mp;
     	}
      //Double_t beta = hoge_p2p->GetRecoilR()->Beta();


      //printf("%f, %f = %f \n", phi1, phi2, TMath::Abs(phi1-phi2));
      if( TMath::IsNaN(theta1+theta2) || TMath::Abs(theta1+theta2-87)>3 ) continue;
      if( TMath::Abs(Sp)>10 ) continue;

      hOpenAng->Fill(theta1+theta2);
      if( TMath::Abs(TMath::Abs(phi1-phi2)-180)>2) {
        hOpenAng2->Fill(theta1+theta2);
        continue;
      }
      hOpenAng2->SetLineColor(kRed);
      
      //*********************** Calculate theritical tof, from (theta, phi, E)
      Double_t theta, phi;
      if ( detector == "Tpla-L"){ 
      	theta = theta1;
      	phi = phi1;
      	//printf("theta_XA:%.2f, theta:%.2f\n", atan(a1)*TMath::RadToDeg()+60., theta);
      	//if (TMath::Abs(60. + atan(a1)*TMath::RadToDeg() - theta) > 5 ) continue; 
     	}else{
     		theta = theta2;
      	phi = phi2;
      	//if (TMath::Abs(60. - atan(a1)*TMath::RadToDeg() - theta) > 5 ) continue; 
     	}
      Double_t length = 2.*z0Tpla/(cos(theta/TMath::RadToDeg())-Sign*sqrt(3.)*cos(phi/TMath::RadToDeg())*sin(theta/TMath::RadToDeg()));
      Double_t T0 = 258.506;
      Double_t T = T0/((2*mp+T0)*TMath::Power(tan(theta/TMath::RadToDeg()),2)/2/mp+1);
      Double_t beta = TMath::Sqrt(1 - TMath::Power(mp/(mp+T),2));
      Double_t tof = length/cVaccum/beta;
      
      //printf("%d | ang(%.2f, %.2f), L:%.2f, beta:%.2f, tof:%.2f \n", eventID, theta2, phi2, length, beta, tof);
      
      
      //*********************** Adjust time reference to tTgt
      Double_t tofF3FH9    = tFH9 - tF3 + 306.92 +  Principle_tof; // common stop
      const Double_t tTgt  =  tFH9 + tofF3FH9*LENGTH_RATIO_FH9_TGT; 
         
      
      //printf("---- %.2f(%.2f), %.2f(%.2f), %.2f, %.2f, %.2f, %.2f\n", t1, Q1, t2, Q2, tF3, tFH9, tofF3FH9, tTgt);   
      t1  = t1 - tTgt + 62 - tof - Sign*PlaX/PlaBeta/cVaccum;  // L = 62, R = 60
      t2  = t2 - tTgt + 51 - tof + Sign*PlaX/PlaBeta/cVaccum ; // L = 51, R = 55
      tFH9 = tFH9 - tTgt;
      tF3  = tF3 - tTgt;
      //printf("               %.2f, %.2f \n", t1, t2);
      
      Double_t a = (2*(PlaX-PMTPos[0])-(PMTPos[1]-PMTPos[0]))/TMath::Log(Q2/Q1);

      // Fill Histogram
      hQ1->Fill(Q1);
      hQ2->Fill(Q2);
      hLogQPlaX->Fill(PlaX, TMath::Log(Q2/Q1));
      hPlaX->Fill(PlaX);
      
      hQ1E1->Fill(E,Q1);
      hQ2E2->Fill(E,Q2);
      hDecay->Fill(a);
 
      Double_t tavg = (t1+t2)/2;
      
      // Slew correction
      Double_t Cslew1 = 500;
	   Double_t Pslew1 = 0.9;
	   Double_t Kslew1 = 300;
      Double_t Cslew2 = 500;
	   Double_t Pslew2 = 0.9;
	   Double_t Kslew2 = 300;
      Double_t slew1 = Cslew1/TMath::Power(Q1-Kslew1,Pslew1) ;
      Double_t slew2 = Cslew2/TMath::Power(Q2-Kslew2,Pslew2) ;
      Double_t t1Slew = t1 - slew1;
      Double_t t2Slew = t2 - slew2;
      Double_t tavgSlew = (t1Slew+t2Slew)/2;

      hSlew1->Fill(Q1, TMath::Abs(slew1));
      hSlew2->Fill(Q2, TMath::Abs(slew2));
      //printf("%d | tTgt:%.2f, t1(slew):%.2f(%.2f), t2(slew):%.2f(%.2f) \n", eventID, tTgt, t1, t1Slew, t2, t2Slew);

      hQ1Q2->Fill(Q1,Q2);

      hQ1t1Slew->Fill(t1Slew, Q1);
      hQ2t2Slew->Fill(t2Slew, Q2);
      
      hPlaXt1->Fill(t1, PlaX);
      hPlaXQ1->Fill(Q1, PlaX);
      
      hPlaXt2->Fill(t2, PlaX);
      hPlaXQ2->Fill(Q2, PlaX);

      hQ1t1->Fill(t1, Q1);
      hQ2t2->Fill(t2, Q2);


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
   cSlew->cd(1);
   hQ1->Draw();
   hQ2->Draw("same");

   text.SetTextColor(4);
   textStr.Form("Q1 offset:%7.2f, gain:%5.2f",Qoffset[0],QGain[0]);
   text.DrawText(0.3, 0.8, textStr);
   text.SetTextColor(2);
   textStr.Form("Q2 offset:%7.2f, gain:%5.2f",Qoffset[1],QGain[1]);
   text.DrawText(0.3, 0.7, textStr);
   
   
   cSlew->cd(6);
   hPlaX->Draw(""); 
   
   cSlew->cd(11);
   //hQ1Q2->Draw("colz");
   hSlew1->Draw("colz");
   hSlew2->Draw("colz same");
   //hSlewDiff->Draw();
   //hLogQPlaX->Draw("colz");
   //hQ1E1->Draw("colz");
   
   //******* COl 2
   cSlew->cd(2);
   hPlaXt1->Draw("colz");
   
   cSlew->cd(7);
   hPlaXQ1->Draw("colz");
   
   cSlew->cd(12);
   hLogQPlaX->Draw("colz");

	
	//******* COl 3
   cSlew->cd(3);
   hQ1t1->Draw("colz");
   
   TString walkfun1;
   walkfun1.Form("TMath::Power(%.2f/(x+1), 1./%.2f)+%.2f",Cslew1, Pslew1, Kslew1);
   TF1* walk1 = new TF1("walk1", walkfun1, -1, 15);
   walk1->Draw("same");
   
   cSlew->cd(8);
   hQ1t1Slew->Draw("colz");
   
   text.SetTextColor(2);
   text.SetTextSize(0.08);
   textStr.Form("W = #frac{%.0f}{{}^{%.1f}#sqrt{Q-%.0f}}",Cslew1,Pslew1, Kslew1);
   text.DrawLatex(0.15, 0.7, textStr);
   
   
   cSlew->cd(13);
   hQ1t1->ProjectionX("hQ1t1_proX");
   hQ1t1Slew->ProjectionX("hQ1t1Slew_proX");
   hQ1t1Slew_proX->SetLineColor(kRed);
   hQ1t1Slew_proX->Draw("");
   hQ1t1_proX->Draw("same");
   //hQ1t1Slew_proX->Fit("gaus");
   
   //******* COl 4
   cSlew->cd(4);
   hPlaXt2->Draw("colz");
   
   cSlew->cd(9);
   hPlaXQ2->Draw("colz");

   
   //******* COl 5
   cSlew->cd(5);
   hQ2t2->Draw("colz");
   
   TString walkfun2;
   walkfun2.Form("TMath::Power(%.2f/(x-6), 1./%.2f)+%.2f",Cslew2, Pslew2, Kslew2);
   TF1* walk2 = new TF1("walk2", walkfun2, -10, 2);
   walk2->Draw("same");

   
   cSlew->cd(10);
   hQ2t2Slew->Draw("colz");
   text.SetTextColor(2);
   textStr.Form("W = #frac{%.0f}{{}^{%.1f}#sqrt{Q-%.0f}}",Cslew2,Pslew2, Kslew2);
   text.DrawLatex(0.15, 0.7, textStr);

  
   cSlew->cd(15);
   hQ2t2->ProjectionX("hQ2t2_proX");
   hQ2t2Slew->ProjectionX("hQ2t2Slew_proX");
   hQ2t2Slew_proX->SetLineColor(kRed);
   hQ2t2Slew_proX->Draw("");
   hQ2t2_proX->Draw("same");
   
   return ;
}

