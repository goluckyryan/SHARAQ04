void SimpleTreeToRecoil() {   
   
   const char* savefilename="Rphys14Down.root";
   //const char* rootfile="Data/phys14_1_43.root";
   //const char* rootfile="ppDown.root";
   const char* rootfile="Data/phys14_45_67.root";
   TBeamData *beam = new TBeamData("O14");
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=1000000;
   
   beam->Print();
   Double_t Principle_tof = tofByBrho(L_F3FH9,beam->fBrho, beam->fMass, beam->fZ);
   printf("---- Principle Tof: %10.3f ns\n", Principle_tof);
   TBeamData target("proton");
   target.SetKinetic(0, 0, 0);
   TLorentzVector residual;
//################################################################
   Double_t tof_usV1190;
   Int_t  runNum, eventID, conReg;
   TFile *f = new TFile(rootfile,"read");
   TTree *simTree = (TTree*)f->Get("recoil");   
   Int_t totnumEntry = recoil->GetEntries();
   simTree->SetBranchAddress("runNum",&runNum);
   simTree->SetBranchAddress("eventID",&eventID);
   simTree->SetBranchAddress("coinReg",&coinReg);
   simTree->SetBranchAddress("tof_usV1190",&tof_usV1190);
   simTree->SetBranchAddress("tFH9",&tFH9);
   
//#################################################################
   TFile *savefile = new TFile(savefilename,"recreate");
   TTree *recoil; 
   recoil = new TTree("recoil","recoil");
   recoil->Branch("runNum", &runNum, "runNum/I");
   recoil->Branch("eventID",&eventID,"eventID/I");
   recoil->Branch("coinReg",&coinReg,"coinReg/I");
   recoil->Branch("tof_usV1190",&tof_usV1190,"tof_usV1190/D");
   recoil->Branch("tof_usV775",&tof_usV775,"tof_usV775/D");
   recoil->Branch("QFH9",&QFH9,"QFH9/D");
   recoil->Branch("s0x", &s0x, "s0x/D");
   recoil->Branch("s0y", &s0y, "s0y/D");
   recoil->Branch("TKAppac",&TKAppac, "TKAppac/D");
   recoil->Branch("tofS0D", &tofS0D, "tofS0D/D");
   recoil->Branch("QS0D", &QS0D, "QS0D/D");
   recoil->Branch("tof1",&tof1,"tof1/D");
   recoil->Branch("tof2",&tof2,"tof2/D");
   recoil->Branch("Q1",&Q1,"Q1/D");
   recoil->Branch("Q2",&Q2,"Q2/D");
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
  
//#################################################################   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   
   
   for ( Int_t i = firstEntry; i < endEntry ; i++){

   }

   
   return ;
}
