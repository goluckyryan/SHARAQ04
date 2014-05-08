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

// should be around 7,000 event per sec.

void PPElastics() {
  
   const char* savefilename="test.root";
   const char* rootfile="Data/ppDown.root";
   TBeamData* beam = new TBeamData("proton");
   Bool_t allentry  = 0;
   Int_t firstEntry = 0;
   Int_t nEntries=100000;
   // Both Tpla,  gamma, tof_us,  0<tof<30, recoil,  E<400, |wbeamZ|<1000
   Bool_t Gate[7] = {1, 1, 1, 1, 1, 0, 0};
   
   beam->Print();
   Double_t Principle_tof = tofByBrho(L_F3FH9,beam->fBrho, beam->fMass, beam->fZ);
   printf("---- Principle Tof: %10.3f ns\n", Principle_tof);
   TBeamData target("proton");
   target.SetKinetic(0, 0, 0);
   //target.Print();
   //target.f4Vector->Print();
   TLorentzVector residual;
//############################################################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;
   
//================ Tree branch
   Int_t eventID;
   // runNumber
   Int_t runNum;
   // get tof and charge upstream
   Double_t tof_usV1190, Q_usG;
   Double_t tof_usV775;
   //downstream V775
   Double_t tof1, Q1;
   Double_t tof2, Q2;
   Double_t tdiff1, tdiff2;
   Double_t tofS0D, QS0D;
   // SMWDC X Y
   Int_t NValidPlane1,NValidPlane2;
   Double_t x1, y1, a1, b1; // for smwdc-L
   Double_t x2, y2, a2, b2; // for smwdc-R
   
   TRecoilData * recoil1 = new TRecoilData();
   TRecoilData * recoil2 = new TRecoilData();
   
   // Phsyics
   Double_t TKAV775;
   Double_t E1, E2;
   //Double_t fl1, fl2;
   Double_t theta1, theta2;
   Double_t phi1, phi2;
   Double_t beamZ1, beamZ2;
   Double_t Sp, Sp2;
   Double_t wbeamZ;

   TFile *savefile = new TFile(savefilename,"recreate");
   TTree *recoil; 
   recoil = new TTree("recoil","recoil");
   recoil->Branch("runNum", &runNum, "runNum/I");
   recoil->Branch("eventID",&eventID,"eventID/I");
   recoil->Branch("tof_usV1190",&tof_usV1190,"tof_usV1190/D");
   recoil->Branch("tof_usV775",&tof_usV775,"tof_usV775/D");
   recoil->Branch("Q_us",&Q_usG,"Q_usG/D");
   recoil->Branch("NValidPlane1",&NValidPlane1,"NValidPlane1/I");
   recoil->Branch("NValidPlane2",&NValidPlane2,"NValidPlane2/I");
   recoil->Branch("TKAV775",&TKAV775,"TKAV775/D");
   recoil->Branch("tofS0D", &tofS0D, "tofS0D/D");
   recoil->Branch("QS0D", &QS0D, "QS0D/D");
   recoil->Branch("tof1",&tof1,"tof1/D");
   recoil->Branch("tof2",&tof2,"tof2/D");
   //recoil->Branch("fl1",&fl1,"fl1/D");
   //recoil->Branch("fl2",&fl2,"fl2/D");
   recoil->Branch("tdiff1",&tdiff1,"tdiff1/D");
   recoil->Branch("tdiff2",&tdiff2,"tdiff2/D");
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
   recoil->Branch("x1",&x1,"x1/D");
   recoil->Branch("E1",&E1,"E1/D");
   recoil->Branch("E2",&E2,"E2/D");
   recoil->Branch("theta1",&theta1,"theta1/D");
   recoil->Branch("theta2",&theta2,"theta2/D");
   recoil->Branch("phi1",&phi1,"phi1/D");
   recoil->Branch("phi2",&phi2,"phi2/D");
   recoil->Branch("beamZ1",&beamZ1,"beamZ1/D");
   recoil->Branch("beamZ2",&beamZ2,"beamZ2/D");
   recoil->Branch("wbeamZ", &wbeamZ,"wbeamZ/D");
   recoil->Branch("Sp",&Sp,"Sp/D");
   recoil->Branch("Sp2",&Sp2,"Sp2/D");

//############################################################################
   art::TEventHeader *hoge_run;
   TClonesArray  *hoge_fh9, *hoge_us, *hoge_V775, *hoge_ds, *hoge_L, *hoge_R;
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded. ----> %s\n",rootfile, savefilename);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("eventheader",1);
   tree->SetBranchStatus("plaV1190_FH9",1); //get charge
   tree->SetBranchStatus("tof_US",1);
   tree->SetBranchStatus("plaV775",1);    //get charge
   tree->SetBranchStatus("tof_DS",1);
   tree->SetBranchStatus("smwdc_L",1);
   tree->SetBranchStatus("smwdc_R",1);

   tree->SetBranchAddress("eventheader",&hoge_run);
   tree->SetBranchAddress("plaV1190_FH9",&hoge_fh9);
   tree->SetBranchAddress("tof_US",&hoge_us);
   tree->SetBranchAddress("plaV775",&hoge_V775);
   tree->SetBranchAddress("tof_DS",&hoge_ds);
   tree->SetBranchAddress("smwdc_L",&hoge_L);
   tree->SetBranchAddress("smwdc_R",&hoge_R);

//############################################################################   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   
   printf("====== totnumEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry, nEntries,nEntries*100./totnumEntry);
   
   art::TPPACData * ppacData;
   art::TTimeDifference * tofdsdata;
   art::TTwoSidedPlasticData * V775Data;
   art::TTimeDifference *tofusdata;
   art::TTwoSidedPlasticData *Qusdata;
   art::TMWDCTrackingResult* xy1, *xy2;
   art::TTrack* track1, *track2;
   
   Int_t count1=0, count2=0, count3=0, count4=0, count5=0, count6=0, count7=0, count8=0;
   for( Int_t i = firstEntry; i < endEntry; i++){
      eventID = i;
      tree->GetEntry(eventID);
      
      // initialization
      tof_usV1190 = kInvalidD; Q_usG = kInvalidD;
      tof1  = kInvalidD; Q1 = kInvalidD; tdiff1 = kInvalidD;
      tof2  = kInvalidD; Q2 = kInvalidD; tdiff2 = kInvalidD;
      tofS0D= kInvalidD; QS0D = kInvalidD;

//---------------Get tof downstream V775
      Int_t TplaHit_check = 0;
      Int_t DetID;
      Double_t tof_ds[5];
      Int_t nHit = hoge_ds -> GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         tofdsdata = (art::TTimeDifference*)hoge_ds->At(p);
         DetID     = tofdsdata->GetDetID();
         tof_ds[DetID] = tofdsdata->GetTiming();
         if (DetID == 0 || DetID == 1) TplaHit_check++;
      }
      if (Gate[0] && TplaHit_check !=2 ) continue;           // both Tpla hit timing gate
      count1 ++;
//---------------Get charge DS of Tpla and S0D
      Int_t nHit = hoge_V775->GetEntriesFast();
      Int_t DetID ;
      Double_t timeV775[5], Q_ds[5], tdiff[5];
      for ( Int_t p = 0; p < nHit; p++){
         V775Data = (art::TTwoSidedPlasticData*)hoge_V775->At(p);
         DetID           = V775Data->GetDetID();
         Q_ds[DetID]     = V775Data->GetCharge(); 
         timeV775[DetID] = V775Data->GetTiming();
         tdiff[DetID]    = V775Data->GetTDiff();
         if (DetID == 0 || DetID == 1) TplaHit_check++; 
         if (DetID == 0) tdiff1 = tdiff[0];
         if (DetID == 1) tdiff2 = tdiff[1];
      }
      
      if ( Gate[1] && (Q_ds[0] < 700 || Q_ds[1] < 700)) continue;  // gamma gate 
      count2++;
      
//----------------Get Event Number
      runNum = hoge_run->GetRunNumber();
      
//----------------Get tof and charge upstream V1190
      Int_t HitID;
      Int_t nHit = hoge_us -> GetEntriesFast();
      Double_t tof_us[40], Q_us[40];
      for( Int_t p = 0; p < nHit; p++){
         tofusdata = (art::TTimeDifference*)hoge_us->At(p) ;
         HitID        = tofusdata->GetHitID();
         tof_us[p]    = tofusdata->GetTiming();
         Qusdata = (art::TTwoSidedPlasticData*) hoge_fh9->At(HitID-1);
         Q_us[p]      = Qusdata->GetCharge();
         if ( tof_us[p] < beam->fTofGate[0] || tof_us[p] > beam->fTofGate[1]) continue; //PID gate
         if ( Q_us[p] < beam->fQGate[0] || Q_us[p] > beam->fQGate[1]) continue; // PID gate
         tof_usV1190 = tof_us[p];
         Q_usG   = Q_us[p];
      }
      
//-------------------- Calculated TIme
      tof_usV1190 = tof_usV1190 - beam->fToffsetV1190 + Principle_tof;
      
      tof_usV775  = timeV775[3] - timeV775[2] - beam->fToffsetV775 + Principle_tof;
      if ( Gate[2] && TMath::Abs(tof_usV775 - Principle_tof) > 20) continue;  // tof Gate
      count3++;
      
      TKAV775 = TKAByTof(L_F3FH9, tof_usV775, beam->fMass, beam->fA);
      if ( Gate[3] && (TMath::IsNaN(TKAV775) || TKAV775 < 0 )) continue;    // TKA gate
      
      Double_t tref_tgt = timeV775[3] + (tof_usV775)*LENGTH_RATIO_FH9_TGT;// tof from Fh9 to tgt
      
      tof1   = timeV775[0] - tref_tgt + beam->fToffset1 ; Q1    = Q_ds[0];
      tof2   = timeV775[1] - tref_tgt + beam->fToffset2 ; Q2    = Q_ds[1];
      tofS0D  = tof_ds[4]                ; QS0D  = Q_ds[4];
      if (Gate[3] && (TMath::IsNaN(tof1) || TMath::IsNaN(tof2) )) continue;         // tof gate
      if (Gate[3] && (tof1 < 0 || tof1 > 30 || tof2 < 0 || tof2>30)) continue;      // 
      count4++;
      
//---------Get SMWDC image, should be one 1 instance
      Int_t nHit = hoge_L->GetEntriesFast();
      Double_t ex1, ea1;
      for( Int_t p = 0; p < nHit; p++){
         recoil1->TRecoilData();
         xy1 = (art::TMWDCTrackingResult*)hoge_L->At(p);
         NValidPlane1 = xy1 -> GetNPlaneValid();
         Int_t TrackingID1  = xy1 -> GetTrackingID();
         ex1 = xy1->GetSigma(0);
         ea1 = xy1->GetSigma(1);
         track1 = (art::TTrack*)xy1->GetTrack();
         x1 = track1->GetX();
         y1 = track1->GetY();
         a1 = track1->GetA();
         b1 = track1->GetB();
         if ( TrackingID1 != 1) continue;
         recoil1->SetKinetic(1,tof1,x1,y1,a1,b1, 0.5, ex1, 0, ea1, 0);
      }
      Int_t nHit = hoge_R->GetEntriesFast();
      Double_t ex2, ea2;    
      for( Int_t p = 0; p < nHit; p++){
         recoil2->TRecoilData();
         xy2 = (art::TMWDCTrackingResult*)hoge_R->At(p);
         NValidPlane2 = xy2 -> GetNPlaneValid();
         Int_t TrackingID2  = xy2 -> GetTrackingID();
         ex2 = xy2->GetSigma(0);
         ea2 = xy2->GetSigma(1);
         track2 = (art::TTrack*)xy2->GetTrack();
         x2 = track2->GetX();
         y2 = track2->GetY();
         a2 = track2->GetA();
         b2 = track2->GetB();
         if ( TrackingID2 != 1) continue;
         recoil2->SetKinetic(2, tof2,x2,y2,a2,b2, 0.5, ex2, 0,ea2, 0);
      }
      
      if (Gate[4] && (recoil1->fOK == 0 || recoil2->fOK == 0)) continue;   // recoil gate
      count5++;
      
      E1 = recoil1->fTKA;
      E2 = recoil2->fTKA;
      
      if ( Gate[5] && (TMath::IsNaN(E1) || TMath::IsNaN(E2) )) continue;   // energy gate
      if ( Gate[5] && ( E1 > 400 || E2 > 400)) continue;   
      count6++;     
      
      beamZ1 = recoil1->fBeamZ;
      beamZ2 = recoil2->fBeamZ;
      Double_t ebeamZ1 = recoil1->feBeamZ;
      Double_t ebeamZ2 = recoil2->feBeamZ;
      
      // calculated min
      wbeamZ = (beamZ1/ebeamZ1/ebeamZ1+beamZ2/ebeamZ2/ebeamZ2)/(1/ebeamZ1/ebeamZ1+1/ebeamZ2/ebeamZ2);  
      if ( Gate[6] && TMath::Abs(wbeamZ) > 1000 ) continue; // beamZ gate   
      count7++;     

      //fl1 = recoil1->fFlightLength;
      //fl2 = recoil2->fFlightLength;
      theta1 = recoil1->fTheta;
      theta2 = recoil2->fTheta;
      phi1 = recoil1->fPhi;
      phi2 = recoil2->fPhi;

      // beam 
      Double_t gamma = TKAV775/mp + 1;
      Double_t beta  = TMath::Sqrt(1-1/gamma/gamma);
      Sp = (1-gamma)*mp - gamma*(E1+E2)
	         + beta*gamma*(
                 (recoil1->fMomentum)*TMath::Cos(theta1) + 
                 (recoil2->fMomentum)*TMath::Cos(theta2));
                 
      //beam->SetKinetic(BrhoByTKA(TKAV775,beam->fMass, beam->fA, beam->fZ), 0, 0);
      beam->SetKinetic(beam->fBrho,0,0);
      residual = beam->f4Vector + target.f4Vector - recoil1->f4Vector - recoil2->f4Vector;
      Sp2 = residual.M2();
              
      savefile->cd(); //set focus on this file
      recoil->Fill();  
      count8++;
      
      clock.Stop("timer");
      Double_t time = clock.GetRealTime("timer");
      clock.Start("timer");
      
      if ( !shown ) {
         if (fmod(time, 10) < 1 ){
            printf( " %6d[%2d%%] | %3d min %6.3f sec | expect:%5.1fmin\n", eventID, TMath::Nint((eventID+1)*100./(endEntry+1)),
            TMath::Floor(time/60), time - TMath::Floor(time/60)*60,
            (endEntry+1)/(eventID+1)*time/60.);
            shown = 1;
         }
      }else{
         if (fmod(time, 10) > 1 ){
            shown = 0;
         }
      }
   }
  
   savefile->cd();
   recoil->Write();
   savefile->Close();
   f->Close();
   
   printf("============ finished|%10.3f sec\n",clock.GetRealTime("timer"));
   printf("nEntries:%d \n", nEntries);
   printf("%1d count both   T   :%7d [%4.1f%%] \n", Gate[0], count1, count1*100./nEntries);
   printf("%1d count both gamma :%7d [%4.1f%%] \n", Gate[1], count2, count2*100./nEntries);
   printf("%1d count  tof_us    :%7d [%4.1f%%] \n", Gate[2], count3, count3*100./nEntries);
   printf("%1d count both tof<30:%7d [%4.1f%%] \n", Gate[3], count4, count4*100./nEntries);
   printf("%1d count both recoil:%7d [%4.1f%%] \n", Gate[4], count5, count5*100./nEntries);
   printf("%1d count both E<400 :%7d [%4.1f%%] \n", Gate[5], count6, count6*100./nEntries);
   printf("%1d count     wbeamZ :%7d [%4.1f%%] \n", Gate[6], count7, count7*100./nEntries);
   printf("  count     Fill   :%7d [%4.1f%%] \n", count8, count8*100./nEntries);

   return ;
}


