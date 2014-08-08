// Trim the root file, extract essentail data. For quicker analysis

void TrimForReduce() {
   
//############################################################################   
   const char* savefilename="R25F_0728.root";
   //const char* rootfile="Data/phys14_1_43.root";
   const char* rootfile="25F_0728.root";
   //const char* rootfile="Data/phys24Down.root";
   Bool_t allentry  = 0;
   Int_t firstEntry = 0;
   Int_t nEntries=1000;
   
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
   // gate
   Int_t gate;
   // ppac
   Double_t ppacX, Brho, TKAppac;
   // S0img
   Double_t s0x, s0y;
   // get tof and charge upstream
   Double_t tof_usV1190, Q_us;
   Double_t tof_usV775;
   //downstream V775
   Double_t tof1, Q1;
   Double_t tof2, Q2;
   Double_t tofS0D, QS0D;
   // SMWDC X Y
   Double_t x1, y1, a1, b1; // for smwdc-L
   Double_t x2, y2, a2, b2; // for smwdc-R
   
   // Phsyics
   Double_t TKAV775;
   Double_t E1, E2;
   Double_t theta1, theta2;
   Double_t phi1, phi2;
   Double_t beamZ1, beamZ2, wbeamZ;
   Double_t vertexX, vertexY, vertexZ;
   Double_t Sp;
   Double_t Sp2;

   TFile *savefile = new TFile(savefilename,"recreate");
   TTree *recoil; 
   recoil = new TTree("recoil","recoil");
   recoil->Branch("runNum", &runNum, "runNum/I");
   recoil->Branch("eventID",&eventID,"eventID/I");
   recoil->Branch("coinReg",&coinReg,"coinReg/I");
   recoil->Branch("tof_usV1190",&tof_usV1190,"tof_usV1190/D");
   recoil->Branch("tof_usV775",&tof_usV775,"tof_usV775/D");
   recoil->Branch("Q_us",&Q_us,"Q_us/D");
   recoil->Branch("s0x", &s0x, "s0x/D");
   recoil->Branch("s0y", &s0y, "s0y/D");
   recoil->Branch("ppacX", &ppacX, "ppacX/D");
   recoil->Branch("Brho",&Brho, "Brho/D");
   recoil->Branch("TKAppac",&TKAppac,"TKAppac/D");
   recoil->Branch("TKAV775",&TKAV775,"TKAV775/D");
   recoil->Branch("tofS0D", &tofS0D, "tofS0D/D");
   recoil->Branch("QS0D", &QS0D, "QS0D/D");
   recoil->Branch("tof1",&tof1,"tof1/D");
   recoil->Branch("tof2",&tof2,"tof2/D");
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
   recoil->Branch("E1",&E1,"E1/D");
   recoil->Branch("E2",&E2,"E2/D");
   recoil->Branch("theta1",&theta1,"theta1/D");
   recoil->Branch("theta2",&theta2,"theta2/D");
   recoil->Branch("phi1",&phi1,"phi1/D");
   recoil->Branch("phi2",&phi2,"phi2/D");
   recoil->Branch("beamZ1",&beamZ1,"beamZ1/D");
   recoil->Branch("beamZ2",&beamZ2,"beamZ2/D");
   recoil->Branch("wbeamZ", &wbeamZ,"wbeamZ/D");
   recoil->Branch("vertexX",&vertexX,"vertexX/D");
   recoil->Branch("vertexY",&vertexY,"vertexY/D");
   recoil->Branch("Sp",&Sp,"Sp/D");
   recoil->Branch("Sp2",&Sp2,"Sp2/D");

//############################################################################
   
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded. ----> %s\n",rootfile, savefilename);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("eventheader",1);
   tree->SetBranchStatus("coinReg",1);
   tree->SetBranchStatus("gate",1);
   tree->SetBranchStatus("ppac",1);
   tree->SetBranchStatus("S0img",1);
   tree->SetBranchStatus("plaV1190_FH9",1); //get charge for PID
   tree->SetBranchStatus("tof_US",1);
   tree->SetBranchStatus("plaV775",1);    //get charge and time
   tree->SetBranchStatus("smwdc_L",1);
   tree->SetBranchStatus("smwdc_R",1);
   tree->SetBranchStatus("beamZ",1);
   tree->SetBranchStatus("vertex",1);
   tree->SetBranchStatus("tofL",1);
   tree->SetBranchStatus("tofR",1);
   tree->SetBranchStatus("tofS0D",1);
   tree->SetBranchStatus("p2p",1);
   
   art::TCoinRegData *hoge_coinReg;
   art::TGateArray* hoge_gate;
   art::TEventHeader *hoge_run;
   TClonesArray *hoge_ppac, *hoge_S0img, *hoge_fh9, *hoge_us, *hoge_V775, *hoge_L, *hoge_R;
   TClonesArray *hoge_beamZ, *hoge_vertex, *hoge_tofL, *hoge_tofR, *hoge_tofS0D;
   art::sh04::TP2PKinematicsData *hoge_p2p;
   
   tree->SetBranchAddress("eventheader",&hoge_run);
   tree->SetBranchAddress("coinReg",&hoge_coinReg);
   tree->SetBranchAddress("gate",&hoge_gate);
   tree->SetBranchAddress("ppac",&hoge_ppac);
   tree->SetBranchAddress("S0img",&hoge_S0img);
   tree->SetBranchAddress("plaV1190_FH9",&hoge_fh9);
   tree->SetBranchAddress("tof_US",&hoge_us);
   tree->SetBranchAddress("plaV775",&hoge_V775);
   tree->SetBranchAddress("smwdc_L",&hoge_L);
   tree->SetBranchAddress("smwdc_R",&hoge_R);
   tree->SetBranchAddress("beamZ",&hoge_beamZ);
   tree->SetBranchAddress("vertex",&hoge_vertex);
   tree->SetBranchAddress("tofL",&hoge_tofL);
   tree->SetBranchAddress("tofR",&hoge_tofR);
   tree->SetBranchAddress("tofS0D",&hoge_tofS0D);
   tree->SetBranchAddress("p2p",&hoge_p2p);

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
   art::TTimeDifference * tofusdata, * tofL, * tofR, *tofS0D;
   art::TTwoSidedPlasticData * Qusdata;
   art::TMWDCTrackingResult * xyS0,* xy1,* xy2;
   art::TTrack * trackS0,* track1,* track2;
   
   gROOT->ProcessLine(".!date");
//##############################################################################
   for( eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID);
      
      // initialization
      coinReg = 0;
      tof_usV1190 = kInvalidD; Q_usG = kInvalidD;
      tof1  = kInvalidD; Q1 = kInvalidD; 
      tof2  = kInvalidD; Q2 = kInvalidD;
      //tdiff1 = kInvalidD; tdiff2 = kInvalidD;
      tofS0D= kInvalidD; QS0D = kInvalidD;
      
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
               count0++;
            }
         }else if ( k == 3){
            if ( hoge_coinReg->Test(3) == 1) coinReg += 40;
         }else{
            if ( hoge_coinReg->Test(k) == 1) coinReg += 1;
         }
      }
      //if( coinReg%10 != 0 ) continue;
      //count0++;
      
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
      count1 ++;
      
      if ( Q_ds[0] < 500 || Q_ds[1] < 500) continue;  // gamma gate 
      count2++;
      
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
      count3++;
//---------------------- PPAC;
      if (beam->fppacOn){
         nHit = hoge_ppac->GetEntriesFast();
         for (Int_t p = 0; p < nHit; p++){
            ppacData = (art::TPPACData*)hoge_ppac->At(p) ;
            ppacX = ppacData->GetX();
         }
         Brho = beam->fBrho * (1 - ppacX/7500.);
      }else{
         Brho = beam->fBrho;
      }      
      TKAppac = TKAByBrho(Brho, beam->fMass, beam->fA, beam->fZ);
      
//-------------------- Calculated TIme
      tof_usV1190 = tof_usV1190 - beam->fToffsetV1190 + Principle_tof;
      
      tof_usV775  = timeV775[3] - timeV775[2] - beam->fToffsetV775 + Principle_tof;
      //if (TMath::Abs(tof_usV775 - Principle_tof) > 20) continue;  // tof Gate
      
      TKAV775 = TKAByTof(L_F3FH9, tof_usV775, beam->fMass, beam->fA);
      printf("%f, %f, %f, %f, %f \n", TKAV775, tof_usV775, timeV775[3], timeV775[2], beam->fToffsetV775);
      
      if ( TMath::IsNaN(TKAV775) || TKAV775 < 0 ) continue;    // TKA gate
      
      Double_t tref_tgt = timeV775[3] + (tof_usV775)*LENGTH_RATIO_FH9_TGT;// tof from Fh9 to tgt
      
      //printf("%f, %f, %f, %f \n", timeV775[0],tref_tgt, beam->fToffset1);
      
      tof1   = timeV775[0] - tref_tgt + beam->fToffset1 ; Q1    = Q_ds[0];
      tof2   = timeV775[1] - tref_tgt + beam->fToffset2 ; Q2    = Q_ds[1];
      tofS0D = timeV775[4] - tref_tgt ; 
      
      if ( beam->fName == "14O" && runNum > 44){
         QS0D = 1.75*Q_ds[4]-403.5;
      }else{
         QS0D = Q_ds[4];
      }
      
      if ( TMath::IsNaN(tof1) || TMath::IsNaN(tof2) ) continue;         // tof gate
      //if ( tof1 < 0 || tof1 > 30 || tof2 < 0 || tof2>30) continue;      // 
      count4++;
      //printf("%10.2f, %10.2f \n", tof1, tof2);
      
//---------Get S0img image, should be one 1 instance
if (beam->fName != "proton") {
      nHit = hoge_S0img->GetEntriesFast();
      //Double_t s0a, s0b;
      for( Int_t p = 0; p < nHit; p++){
         xyS0 = (art::TMWDCTrackingResult*)hoge_S0img->At(p);
         trackS0 = (art::TTrack*)xyS0->GetTrack();
         s0x = trackS0->GetX();
         s0y = trackS0->GetY();
         //s0a = trackS0->GetA();
         //s0b = trackS0->GetB();
      }      
      beam->SetKinetic(Brho, 0, 0);
}
      
//---------Get SMWDC image, should be one 1 instance
      nHit = hoge_L->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         recoil1->TRecoilData();
         xy1 = (art::TMWDCTrackingResult*)hoge_L->At(p);
         //NValidPlane1 = xy1 -> GetNPlaneValid();
         Int_t TrackingID1  = xy1 -> GetTrackingID();
         Double_t ex1 = xy1->GetSigma(0);
         Double_t ea1 = xy1->GetSigma(1);
         track1 = (art::TTrack*)xy1->GetTrack();
         x1 = track1->GetX();
         y1 = track1->GetY();
         a1 = track1->GetA();
         b1 = track1->GetB();
         if ( TrackingID1 != 1) continue;
         recoil1->SetKinetic(1,tof1,x1,y1,a1,b1, s0x, s0y, 0.5, ex1, 0, ea1, 0);
      }
      nHit = hoge_R->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         recoil2->TRecoilData();
         xy2 = (art::TMWDCTrackingResult*)hoge_R->At(p);
         //NValidPlane2 = xy2 -> GetNPlaneValid();
         Int_t TrackingID2  = xy2 -> GetTrackingID();
         Double_t ex2 = xy2->GetSigma(0);
         Double_t ea2 = xy2->GetSigma(1);
         track2 = (art::TTrack*)xy2->GetTrack();
         x2 = track2->GetX();
         y2 = track2->GetY();
         a2 = track2->GetA();
         b2 = track2->GetB();
         if ( TrackingID2 != 1) continue;
         recoil2->SetKinetic(2, tof2,x2,y2,a2,b2, s0x, s0y, 0.5, ex2, 0,ea2, 0);
      }
      
      if (recoil1->fOK == 0 || recoil2->fOK == 0) continue;   // recoil gate
      count5++;
      
      E1 = recoil1->fTKA;
      E2 = recoil2->fTKA;
      
      if ( TMath::IsNaN(E1) || TMath::IsNaN(E2)  || E1 > 400 || E2 > 400) continue;   // energy gate
      count6++;         
      
      beamZ1 = recoil1->fBeamZ;
      beamZ2 = recoil2->fBeamZ;
      Double_t ebeamZ1 = recoil1->feBeamZ;
      Double_t ebeamZ2 = recoil2->feBeamZ;
      
      // calculated min
      wbeamZ = (beamZ1/ebeamZ1/ebeamZ1+beamZ2/ebeamZ2/ebeamZ2)/(1/ebeamZ1/ebeamZ1+1/ebeamZ2/ebeamZ2);  
      
      vertexX = recoil1->fBeamX;
      vertexY = recoil1->fBeamX;
      
      //if ( TMath::Abs(wbeamZ) > 1000 ) continue; // beamZ gate   
      count7++;  
      
      //fl1 = recoil1->fFlightLength;
      //fl2 = recoil2->fFlightLength;
      theta1 = recoil1->fTheta;
      theta2 = recoil2->fTheta;
      phi1 = recoil1->fPhi;
      phi2 = recoil2->fPhi;
      
      // beam 
      Double_t gamma = TKAppac/mp + 1;
      Double_t beta  = TMath::Sqrt(1-1/gamma/gamma);

      Sp = (1-gamma)*mp - gamma*(E1+E2)
	         + beta*gamma*(
                 (recoil1->fMomentum)*TMath::Cos(theta1) + 
                 (recoil2->fMomentum)*TMath::Cos(theta2));
                 
      //Sp2 = Mass(Res*) - (Mass(Target) - proton) 
      residual = beam->f4Vector + target.f4Vector - recoil1->f4Vector - recoil2->f4Vector;
      //printf(" resiudal mass %10.4f", residual.M());
      Sp2 = residual.M() - beam->fMass + mp;
/*      Double_t Sp2 ;
      Sp2  = TMath::Power(gamma*beam->fMass - E1 - E2 - mp,2);
      Sp2 -= TMath::Power(beta*gamma*beam->fMass - recoil1->fMomentum*TMath::Cos(theta1)-recoil2->fMomentum*TMath::Cos(theta2),2);
      Sp2 -= TMath::Power(recoil1->fMomentum*TMath::Sin(theta1)*TMath::Sin(phi1)-recoil2->fMomentum*TMath::Sin(theta2)*TMath::Sin(phi2),2);
      Sp2 -= TMath::Power(recoil1->fMomentum*TMath::Sin(theta1)*TMath::Cos(phi1)-recoil2->fMomentum*TMath::Sin(theta2)*TMath::Cos(phi2),2);
      Sp2  = TMath::Sqrt(Sp2) - beam->fMass + mp;
      printf(" Sp - Sp2: %10.2f, %10.2f, %10.2f, %10.2f \n", Sp,Sp2, Sp2 , Sp-Sp2);
*/

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
  
   savefile->cd();
   recoil->Write();
   savefile->Close();
   f->Close();

   clock.Stop("timer");
   printf("============ finished|%10.3f sec --> %s\n",clock.GetRealTime("timer"),savefilename);
   printf("             nEntries   :%10d \n", nEntries);
   printf(" count   coinReg        :%10d [%4.1f%%] \n",  count0, count0*100./nEntries);
   printf(" count both Tpla hit    :%10d [%4.1f%%] \n",  count1, count1*100./nEntries);
   printf(" count both gamma Q<500 :%10d [%4.1f%%] \n",  count2, count2*100./nEntries);
   printf(" count  PID_US          :%10d [%4.1f%%] \n",  count3, count3*100./nEntries);
   printf(" count both tof valid   :%10d [%4.1f%%] \n",  count4, count4*100./nEntries);
   printf(" count both recoil      :%10d [%4.1f%%] \n",  count5, count5*100./nEntries);
   printf(" count both E<400       :%10d [%4.1f%%] \n",  count6, count6*100./nEntries);
   printf(" count     wbeamZ       :%10d [%4.1f%%] \n",  count7, count7*100./nEntries);
   return ;
}
