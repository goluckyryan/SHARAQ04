#include <TBenchmark.h>
#include <TFile.h>
#include <TMath.h>
#include <math.h>
#include <TTree.h>
#include <TList.h>
#include <TClonesArray.h>
#include "constant.h"
#include "RelCalculator.h"
#include "TBeamData.h"
#include "TRecoilData.h"
#include "TLorentzVector.h" //(px, py, pz, E)
/*****************************************************
adjust tof L and R seperatly, and using Sp (gated by beamZ, opening angle, etc )

******************************************************/
Double_t * AngleLen(int id, Double_t x, Double_t a, Double_t y, Double_t b, Double_t ex, Double_t ea);
Double_t KE(Double_t tof, Double_t len);


void TofAdjust() {
   
//############################################################################   
   const char* savefilename="RppAll_0714_multiOffset.root";
   //const char* rootfile="Data/phys14_1_43.root";
   const char* rootfile="PrimaryData/ppAll_0714_multiOffset.root";
   //const char* rootfile="Data/phys24Down.root";
   TBeamData *beam = new TBeamData("proton");
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=10000;
   
   beam->Print();
   Double_t Principle_tof = tofByBrho(L_F3FH9,beam->fBrho, beam->fMass, beam->fZ);
   printf("---- Principle Tof: %10.3f ns\n", Principle_tof);
//############################################################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;

//================ Tree branch
   Int_t eventID;
   // runNumber
   Int_t runNum;
   // coinReg
   Int_t coinReg;
   // S0img
   Double_t s0x, s0y;
   // get tof and charge upstream
   Double_t tof_usV1190, Q_usG;
   Double_t tof_usV775;
   //downstream V775
   Double_t tof1[9], Q1;
   Double_t tof2[9], Q2;
   // SMWDC X Y
   Double_t x1, y1, a1, b1; // for smwdc-L
   Double_t x2, y2, a2, b2; // for smwdc-R
   Double_t len1, len2; // length
   
   //Nyoki
   
   // Phsyics
   Double_t TKAV775;
   Double_t E1[9], E2[9];
   Double_t theta1, theta2;
   Double_t phi1, phi2;
   Double_t beamZ1, beamZ2;
   Double_t wbeamZ;
   Double_t beamX1, beamX2;
   
   Double_t Sp[81];

   TFile *savefile = new TFile(savefilename,"recreate");
   TTree *recoil; 
   recoil = new TTree("recoil","recoil");
   recoil->Branch("runNum", &runNum, "runNum/I");
   recoil->Branch("eventID",&eventID,"eventID/I");
   recoil->Branch("coinReg",&coinReg,"coinReg/I");
   recoil->Branch("tof_usV1190",&tof_usV1190,"tof_usV1190/D");
   recoil->Branch("tof_usV775",&tof_usV775,"tof_usV775/D");
   recoil->Branch("Q_us",&Q_usG,"Q_usG/D");
   recoil->Branch("TKAV775",&TKAV775,"TKAV775/D");
   recoil->Branch("tof1",tof1,"tof1[9]/D");
   recoil->Branch("tof2",tof2,"tof2[9]/D");
   recoil->Branch("Q1",&Q1,"Q1/D");
   recoil->Branch("Q2",&Q2,"Q2/D");
   recoil->Branch("x1",&x1,"x1/D");
   recoil->Branch("a1",&a1,"a1/D");
   recoil->Branch("y1",&y1,"y1/D");
   recoil->Branch("b1",&b1,"b1/D");
   recoil->Branch("x2",&x2,"x2/D");
   recoil->Branch("a2",&a2,"a2/D");
   recoil->Branch("y2",&y2,"y2/D");
   recoil->Branch("b2",&b2,"b2/D");
   recoil->Branch("len1",&len1,"len1/D");
   recoil->Branch("len2",&len2,"len2/D");
   recoil->Branch("E1",E1,"E1[9]/D");
   recoil->Branch("E2",E2,"E2[9]/D");
   recoil->Branch("theta1",&theta1,"theta1/D");
   recoil->Branch("theta2",&theta2,"theta2/D");
   recoil->Branch("phi1",&phi1,"phi1/D");
   recoil->Branch("phi2",&phi2,"phi2/D");
   recoil->Branch("beamZ1",&beamZ1,"beamZ1/D");
   recoil->Branch("beamZ2",&beamZ2,"beamZ2/D");
   recoil->Branch("wbeamZ", &wbeamZ,"wbeamZ/D");
   recoil->Branch("beamX1",&beamX1,"beamX1/D");
   recoil->Branch("beamX2",&beamX2,"beamX2/D");
   recoil->Branch("Sp",Sp,"Sp[81]/D");

//############################################################################
   art::TCoinRegData *hoge_coinReg;
   art::TEventHeader *hoge_run;
   TClonesArray *hoge_ppac, *hoge_S0img, *hoge_fh9, *hoge_us, *hoge_V775, *hoge_L, *hoge_R;
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded. ----> %s\n",rootfile, savefilename);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("eventheader",1);
   tree->SetBranchStatus("coinReg",1);
   tree->SetBranchStatus("plaV1190_FH9",1); //get charge for PID
   tree->SetBranchStatus("tof_US",1);
   tree->SetBranchStatus("plaV775",1);    //get charge and time
   tree->SetBranchStatus("smwdc_L",1);
   tree->SetBranchStatus("smwdc_R",1);

   tree->SetBranchAddress("eventheader",&hoge_run);
   tree->SetBranchAddress("coinReg",&hoge_coinReg);
   tree->SetBranchAddress("plaV1190_FH9",&hoge_fh9);
   tree->SetBranchAddress("tof_US",&hoge_us);
   tree->SetBranchAddress("plaV775",&hoge_V775);
   tree->SetBranchAddress("smwdc_L",&hoge_L);
   tree->SetBranchAddress("smwdc_R",&hoge_R);

//############################################################################   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   
   art::TPPACData * ppacData;
   art::TTwoSidedPlasticData * V775Data;
   art::TTimeDifference * tofusdata;
   art::TTwoSidedPlasticData * Qusdata;
   art::TMWDCTrackingResult * xy1,* xy2;
   art::TTrack * track1,* track2;
   
   Double_t* output1L = new Double_t[7];
   Double_t* output1R = new Double_t[7];
   
   gROOT->ProcessLine(".!date");
//##############################################################################
   for( eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID);
      
      // initialization
      coinReg = 0;
      tof_usV1190 = kInvalidD; Q_usG = kInvalidD;
      Q1 = kInvalidD; 
      Q2 = kInvalidD;
      
//----------------Get Event Number
      runNum = hoge_run->GetRunNumber();
      
//--------------Get coinReg
      // 0 = F3, 1 = FH9, 2=ppcoin, 3 = ND coin, 4 = ppsingle, 5 = ND single, 6 = ND cosmic
      for (Int_t k = 0; k <7; k++){
         if ( k == 1 ){
            if ( hoge_coinReg->Test(1) == 1 ) coinReg += 10;
         }else if ( k == 2){
            if ( hoge_coinReg->Test(2) == 1 ) {
               coinReg += 20;
            }
         }else if ( k == 3){
            if ( hoge_coinReg->Test(3) == 1) coinReg += 40;
         }else{
            if ( hoge_coinReg->Test(k) == 1) coinReg += 1;
         }
      }
      
//---------------Get charge DS of Tpla and S0D
      Int_t TplaHit_check = 0;
      Double_t timeV775[5], Q_ds[5];
      Int_t nHit = hoge_V775->GetEntriesFast();
      for ( Int_t p = 0; p < nHit; p++){
         V775Data = (art::TTwoSidedPlasticData*)hoge_V775->At(p);
         Int_t DetID           = V775Data->GetDetID();
         Q_ds[DetID]     = V775Data->GetCharge(); 
         timeV775[DetID] = V775Data->GetTiming();
         if (DetID == 0 || DetID == 1) TplaHit_check++;

      }
      if ( TplaHit_check !=2 ) continue;           // both Tpla hit timing gate // Part of ppcoin
      if ( TMath::IsNaN(timeV775[0]) || TMath::IsNaN(timeV775[1]) || TMath::IsNaN(timeV775[2]) || TMath::IsNaN(timeV775[3]) ) continue;
      if ( Q_ds[0] < 500 || Q_ds[1] < 500) continue;  // gamma gate 
      
//----------------Get tof and charge upstream V1190
      nHit = hoge_us -> GetEntriesFast();
      Bool_t PID = 0;
      for( Int_t p = 0; p < nHit; p++){
         tofusdata = (art::TTimeDifference*)hoge_us->At(p) ;
         Int_t HitID        = tofusdata->GetHitID();
         Double_t tof_us   = tofusdata->GetTiming();
         Qusdata = (art::TTwoSidedPlasticData*) hoge_fh9->At(HitID-1);
         Double_t Q_us      = Qusdata->GetCharge();
         if ( tof_us < beam->fTofGate[0] || tof_us> beam->fTofGate[1]) continue; //PID gate
         if ( Q_us < beam->fQGate[0] || Q_us > beam->fQGate[1]) continue; // PID gate
         tof_usV1190 = tof_us;
         Q_usG   = Q_us;
         PID = 1;
      }
      if ( PID == 0 ) continue;
      
//---------Get SMWDC image, should be one 1 instance
		Double_t ex1, ea1, ex2, ea2;
      nHit = hoge_L->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         xy1 = (art::TMWDCTrackingResult*)hoge_L->At(p);
         Int_t TrackingID1  = xy1 -> GetTrackingID();
         if ( TrackingID1 != 1) continue;
         ex1 = xy1->GetSigma(0);
         ea1 = xy1->GetSigma(1);
         track1 = (art::TTrack*)xy1->GetTrack();
         x1 = track1->GetX();
         y1 = track1->GetY();
         a1 = track1->GetA();
         b1 = track1->GetB();
      }
      
      nHit = hoge_R->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         xy2 = (art::TMWDCTrackingResult*)hoge_R->At(p);
         Int_t TrackingID2  = xy2 -> GetTrackingID();
         if ( TrackingID2 != 1) continue;
         ex2 = xy2->GetSigma(0);
         ea2 = xy2->GetSigma(1);
         track2 = (art::TTrack*)xy2->GetTrack();
         x2 = track2->GetX();
         y2 = track2->GetY();
         a2 = track2->GetA();
         b2 = track2->GetB();
      }
      
//-------------------- Calculate Theta, Phi, beamZ, beamX

		output1L = AngleLen(1, x1, a1, y1, b1, ex1, ea1);
		if( TMath::IsNaN(output1L[0]) ) continue;
		output1R = AngleLen(2, x2, a2, y2, b2, ex2, ea2);
		if( TMath::IsNaN(output1R[0]) ) continue;

		theta1 = output1L[0]*rad2deg;
		phi1   = output1L[1]*rad2deg;
		len1   = output1L[2];
		
		theta2 = output1R[0]*rad2deg;
		phi2   = output1R[1]*rad2deg;
		len2   = output1R[2];
		
		beamZ1 = output1L[3];
      beamZ2 = output1R[3];
      Double_t ebeamZ1 = output1L[4];
      Double_t ebeamZ2 = output1R[4];
      // calculated weighted average
      wbeamZ = (beamZ1/ebeamZ1/ebeamZ1+beamZ2/ebeamZ2/ebeamZ2)/(1/ebeamZ1/ebeamZ1+1/ebeamZ2/ebeamZ2);  
      
      beamX1 = output1L[5];
      beamX2 = output1R[5];
      
//-------------------- Calculated Time
      tof_usV1190 = tof_usV1190 - beam->fToffsetV1190 + Principle_tof;
      
      tof_usV775  = timeV775[3] - timeV775[2] - beam->fToffsetV775 + Principle_tof;
      //if (TMath::Abs(tof_usV775 - Principle_tof) > 20) continue;  // tof Gate
      
      TKAV775 = TKAByTof(L_F3FH9, tof_usV775, beam->fMass, beam->fA);
     // printf("%f, %f, %f, %f, %f \n", TKAV775, tof_usV775, timeV775[3], timeV775[2], beam->fToffsetV775);
      
      if ( TMath::IsNaN(TKAV775) || TKAV775 < 0 ) continue;    // TKA gate
      
      Double_t tref_tgt = timeV775[3] + (tof_usV775)*LENGTH_RATIO_FH9_TGT;// tof from Fh9 to tgt
      
      Q1    = Q_ds[0]; Q2    = Q_ds[1];
      
      for( Int_t i = 0; i <9; i++){
	      tof1[i]   = timeV775[0] - tref_tgt + beam->fToffset1 + (i-4)*0.2; 
   	   tof2[i]   = timeV775[1] - tref_tgt + beam->fToffset2 + (i-4)*0.2;
   	   E1[i] = KE(tof1[i], len1);
   	   E2[i] = KE(tof2[i], len2); 
   	}     
      
//------------------- Sp 
      Double_t gamma = TKAV775/mp + 1;
      Double_t beta  = TMath::Sqrt(1-1/gamma/gamma);

		for( Int_t i = 0; i<9; i++){
			for( Int_t j = 0; j<9; j++){
			
      		Sp[9*i+j] = (1-gamma)*mp - gamma*(E1[i]+E2[j])
	   		      + beta*gamma*(
      		           sqrt(2*mp*E1[i]+E1[i]*E1[i])*TMath::Cos(theta1*deg2rad) + 
      		           sqrt(2*mp*E2[j]+E2[j]*E2[j])*TMath::Cos(theta2*deg2rad)
      		        );
      		//if (i==0 && j ==0 ) printf("===================== %d", eventID);      
      		//printf("(%d,%d) tof1:%6.2f E1:%6.1f tof2:%6.2f E2:%6.1f Sp:%6.1f \n", i, j,  tof1[i], E1[i], tof2[j], E2[j], Sp[9*i+j]);
      	}
      }

//----------- Fill        
      savefile->cd(); //set focus on this file
      recoil->Fill();  
      
//------------Clock      
      clock.Stop("timer");
      Double_t time = clock.GetRealTime("timer");
      clock.Start("timer");
      
      if ( !shown ) {
         if (fmod(time, 10) < 1 ){
            printf( "%10d[%2d%%](#%2d) |%3d min %5.2f sec | expect:%5.1fmin\n", 
            eventID, 
            TMath::Nint((eventID+1-firstEntry)*100./nEntries),
            runNum,
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
  
   delete output1L;
   delete output1R;
   
   savefile->cd();
   recoil->Write();
   savefile->Close();
   f->Close();

   clock.Stop("timer");
   printf("============ finished|%10.3f sec --> %s\n",clock.GetRealTime("timer"),savefilename);
   return ;
}

//#######################################################################################

Double_t * AngleLen(int id, Double_t x, Double_t a, Double_t y, Double_t b, Double_t ex, Double_t ea){

	Double_t * output = new Double_t[7];
	output[0] = kInvalidD; // Theta
	output[1] = kInvalidD; // Phi
	output[2] = kInvalidD; // Length
	output[3] = kInvalidD; // BeamZ
	output[4] = kInvalidD; // eBeamZ
	output[5] = kInvalidD; // BeamX
	output[6] = kInvalidD; // eBeamX
	
	Double_t PlaneAngle;
   Double_t Xpos, Ypos, Zpos;   // lab frame coordiante
   Double_t Zmwdc, Xmwdc, Ymwdc; // lab frame coordiante
   
   if (id ==1) { // SMWDC-L
      PlaneAngle = mwdcAngleL;
      Zmwdc = z0+ z0L;//-DbeamZ*cos(PlaneAngle*deg2rad);
      Xmwdc = x + x0L;//+DbeamZ*sin(PlaneAngle*deg2rad);
      Ymwdc = y + y0L;
   }else if(id = 2){
      PlaneAngle = mwdcAngleR;
      Zmwdc = z0+ z0R;//-DbeamZ*cos(PlaneAngle*deg2rad);
      Xmwdc = x + x0R;//-DbeamZ*sin(PlaneAngle*deg2rad);
      Ymwdc = y + y0R;
   }else{
      return output;
   }
   
   PlaneAngle = PlaneAngle*deg2rad;
   const Double_t cos = TMath::Cos(PlaneAngle);
   const Double_t sin = TMath::Sin(PlaneAngle);
   
   if ( TMath::Abs(x) <10000 && TMath::Abs(y)<200){
      Xpos = sin*Zmwdc + cos*Xmwdc;
      Ypos = Ymwdc;
      Zpos = cos*Zmwdc - sin*Xmwdc - DbeamZ;
   }else{
   	return output;
   }

	Double_t fFlightLength, fTheta, fPhi;
   fFlightLength = TMath::Sqrt(Xpos*Xpos+Ypos*Ypos+Zpos*Zpos);
   fFlightLength = fFlightLength*z0Tpla/Zmwdc;
	
	output[2] = fFlightLength;

   fTheta = TMath::ATan2(TMath::Sqrt(Xpos*Xpos+Ypos*Ypos), Zpos);
   // range -90 ~ 270
   fPhi   = TMath::ATan2(Ypos,Xpos);
   if (fPhi < -TMath::PiOver2()){
      fPhi = fPhi + TMath::Pi()*2;
   }else if (fPhi > 3*TMath::PiOver2()){
      fPhi = fPhi - TMath::Pi()*2;
   }
   
   output[0] = fTheta;
   output[1] = fPhi;
   

	Double_t BeamZ, eBeamZ, BeamX, eBeamX;   
   BeamZ = (a *Zmwdc - Xmwdc)/(a * cos + sin);
   eBeamZ = TMath::Sqrt(TMath::Power((Xmwdc*cos + Zmwdc*sin)/(a * cos + sin)*ea,2) + ex*ex)/(a * cos + sin);
   eBeamZ = TMath::Abs(eBeamZ);

   BeamX = (a *Zmwdc - Xmwdc)/(a * sin - cos);
   eBeamX = TMath::Sqrt(TMath::Power((Xmwdc*sin - Zmwdc*cos)/(a * sin - cos)*ea,2) + ex*ex)/(a * sin - cos);
   eBeamX = TMath::Abs(eBeamX);   
   
	output[3] = BeamZ ;
	output[4] = eBeamZ ;
	output[5] = BeamX ;
	output[6] = eBeamX ;

	return output;

}

Double_t KE(Double_t tof, Double_t len){

	if ( tof < z0Tpla / cVaccum ) return kInvalidD;

	Double_t fBeta, fGamma, fTKA;
	
   fBeta  = len/cVaccum/tof;
   fGamma = 1/sqrt(1-fBeta*fBeta);
   fTKA   = (fGamma-1)*mp;

	return fTKA;
}
