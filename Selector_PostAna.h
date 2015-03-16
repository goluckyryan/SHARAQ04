//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Feb 10 18:14:28 2015 by ROOT version 5.34/10
// from TTree tree/tree
// found on file: 23F_0208.root
//////////////////////////////////////////////////////////

#ifndef Selector_PostAna_h
#define Selector_PostAna_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.
//#include "./TEventHeader.h"
//#include "./cont/TCoinRegData.h"
//#include "./gate/TGateArray.h"
//#include <TClonesArray.h>
//#include "./sh04/TParticleIdentifier.h"
//#include "./sh04/TP2PKinematicsData.h"

// Fixed size dimensions of array or collections stored in the TTree if any.

class Selector_PostAna : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   
   //  STore in new ROOT file
   TFile * saveFile;
   TTree * newTree;
   
   TString saveFileName;
   
   Int_t totnumEntry;
   Double_t kInvalidD = TMath::QuietNaN();
   
   Int_t eventID;
	//  runNumber
	Int_t runNum;
	// gate
	Int_t gateNum;
	// S0img
	Double_t s0x, s0y;
	// get tof and charge upstream
	Double_t tofFH9, QFH9;
	// tof from S0DPL to nyoki
	Double_t tofS1, QS1;
	// SMWDC X Y
	Double_t x1, y1, a1, b1; // for smwdc-L
	Double_t x2, y2, a2, b2; // for smwdc-R
	Double_t s1x, s1y, s1a, s1b; // for smwdc-S1
	// pid_ds
	Double_t pidZ, pidAOQ;
	//vertex
	Double_t vertexZ;
	// Phsyics
	Double_t E1, E2;
	Double_t theta1, theta2;
	Double_t phi1, phi2;
	Double_t Ex;// Sp2 - 13.26;
	Double_t kMomt; // redisual momentum
	//carbon
	Double_t theta1c, theta2c;
	Double_t phi1c, phi2c;
	Double_t Exc, kMomtc;

   // Declaration of leaf types
   art::TEventHeader *eventheader0;
   art::TEventHeader *eventheader_shvmism;
   art::TEventHeader *eventheader_shvmif3;
   art::TCoinRegData *coinReg;
   art::TGateArray *gate;
   TClonesArray    *plaV1190_F3;
   TClonesArray    *plaV1190_FH9;
   TClonesArray    *tof_US;
   TClonesArray    *plaV775;
   TClonesArray    *tof_DS;
   TClonesArray    *S0img;
   TClonesArray    *smwdc_L;
   TClonesArray    *smwdc_R;
   TClonesArray    *nyoki;
   TClonesArray    *nyoki_t;
   TClonesArray    *tof_D1;
   TClonesArray    *smwdc_S1;
   art::sh04::TParticleIdentifier *pid_us;
   art::sh04::TParticleIdentifier *pid_ds;
   TClonesArray    *vertex;
   TClonesArray    *tofL;
   TClonesArray    *tofR;
   TClonesArray    *tofS0D;
   art::sh04::TP2PKinematicsData *p2p;
   art::sh04::TP2PKinematicsData *p2p_Lab;
   art::sh04::TP2PKinematicsData *p2p_c;
   art::sh04::TP2PKinematicsData *p2p_c_lab;

   // List of branches
   TBranch        *b_eventheader0;   //!
   TBranch        *b_eventheader_shvmism;   //!
   TBranch        *b_eventheader_shvmif3;   //!
   TBranch        *b_coinReg;   //!
   TBranch        *b_gate;   //!
   TBranch        *b_plaV1190_F3;   //!
   TBranch        *b_plaV1190_FH9;   //!
   TBranch        *b_tof_US;   //!
   TBranch        *b_plaV775;   //!
   TBranch        *b_tof_DS;   //!
   TBranch        *b_S0img;   //!
   TBranch        *b_smwdc_L;   //!
   TBranch        *b_smwdc_R;   //!
   TBranch        *b_nyoki;   //!
   TBranch        *b_nyoki_t;   //!
   TBranch        *b_tof_D1;   //!
   TBranch        *b_smwdc_S1;   //!
   TBranch        *b_pid_us;   //!
   TBranch        *b_pid_ds;   //!
   TBranch        *b_vertex;   //!
   TBranch        *b_tofL;   //!
   TBranch        *b_tofR;   //!
   TBranch        *b_tofS0D;   //!
   TBranch        *b_p2p;   //!
   TBranch        *b_p2p_Lab;   //!
   TBranch        *b_p2p_c;   //!
   TBranch        *b_p2p_c_lab;   //!

   Selector_PostAna(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~Selector_PostAna() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(Selector_PostAna,0);
};

#endif

#ifdef Selector_PostAna_cxx
void Selector_PostAna::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).
   
   totnumEntry = tree->GetEntries();

   // Set object pointer
   eventheader0 = 0;
   eventheader_shvmism = 0;
   eventheader_shvmif3 = 0;
   coinReg = 0;
   gate = 0;
   plaV1190_F3 = 0;
   plaV1190_FH9 = 0;
   tof_US = 0;
   plaV775 = 0;
   tof_DS = 0;
   S0img = 0;
   smwdc_L = 0;
   smwdc_R = 0;
   nyoki = 0;
   nyoki_t = 0;
   tof_D1 = 0;
   smwdc_S1 = 0;
   pid_us = 0;
   pid_ds = 0;
   vertex = 0;
   tofL = 0;
   tofR = 0;
   tofS0D = 0;
   p2p = 0;
   p2p_Lab = 0;
   p2p_c = 0;
   p2p_c_lab = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("eventheader0", &eventheader0, &b_eventheader0);
   fChain->SetBranchAddress("eventheader_shvmism", &eventheader_shvmism, &b_eventheader_shvmism);
   fChain->SetBranchAddress("eventheader_shvmif3", &eventheader_shvmif3, &b_eventheader_shvmif3);
   fChain->SetBranchAddress("coinReg", &coinReg, &b_coinReg);
   fChain->SetBranchAddress("gate", &gate, &b_gate);
   fChain->SetBranchAddress("plaV1190_F3", &plaV1190_F3, &b_plaV1190_F3);
   fChain->SetBranchAddress("plaV1190_FH9", &plaV1190_FH9, &b_plaV1190_FH9);
   fChain->SetBranchAddress("tof_US", &tof_US, &b_tof_US);
   fChain->SetBranchAddress("plaV775", &plaV775, &b_plaV775);
   fChain->SetBranchAddress("tof_DS", &tof_DS, &b_tof_DS);
   fChain->SetBranchAddress("S0img", &S0img, &b_S0img);
   fChain->SetBranchAddress("smwdc_L", &smwdc_L, &b_smwdc_L);
   fChain->SetBranchAddress("smwdc_R", &smwdc_R, &b_smwdc_R);
   fChain->SetBranchAddress("nyoki", &nyoki, &b_nyoki);
   fChain->SetBranchAddress("nyoki_t", &nyoki_t, &b_nyoki_t);
   fChain->SetBranchAddress("tof_D1", &tof_D1, &b_tof_D1);
   fChain->SetBranchAddress("smwdc_S1", &smwdc_S1, &b_smwdc_S1);
   fChain->SetBranchAddress("pid_us", &pid_us, &b_pid_us);
   fChain->SetBranchAddress("pid_ds", &pid_ds, &b_pid_ds);
   fChain->SetBranchAddress("vertex", &vertex, &b_vertex);
   fChain->SetBranchAddress("tofL", &tofL, &b_tofL);
   fChain->SetBranchAddress("tofR", &tofR, &b_tofR);
   fChain->SetBranchAddress("tofS0D", &tofS0D, &b_tofS0D);
   fChain->SetBranchAddress("p2p", &p2p, &b_p2p);
   fChain->SetBranchAddress("p2p_Lab", &p2p_Lab, &b_p2p_Lab);
   fChain->SetBranchAddress("p2p_c", &p2p_c, &b_p2p_c);
   fChain->SetBranchAddress("p2p_c_lab", &p2p_c_lab, &b_p2p_c_lab);
   
   //Store in New ROOT file
   saveFileName = fChain->GetDirectory()->GetName();
   saveFileName = "P_"+saveFileName;
   
   printf("Converting %s ------> %s \n", fChain->GetDirectory()->GetName(), saveFileName.Data());
   
   saveFile = new TFile( saveFileName,"recreate");
   newTree =  new TTree("tree","tree");
   
   eventID = -1;
	runNum = -1;
	gateNum = -1;
	s0x = kInvalidD; 
	s0y = kInvalidD;
	tofFH9 = kInvalidD; 
	QFH9 = kInvalidD;
	tofS1 = kInvalidD;
	QS1 = kInvalidD;
	x1 = kInvalidD;
	y1 = kInvalidD;
	a1 = kInvalidD;
	b1 = kInvalidD; 
	x2 = kInvalidD;
	y2 = kInvalidD; 
	a2 = kInvalidD; 
	b2 = kInvalidD; 
	s1x = kInvalidD;
	s1y = kInvalidD; 
	s1a = kInvalidD; 
	s1b = kInvalidD;
	pidZ = kInvalidD;
	pidAOQ = kInvalidD;
	vertexZ = kInvalidD;
	E1 = kInvalidD;
	E2 = kInvalidD;
	theta1 = kInvalidD;
	theta2 = kInvalidD;
	phi1 = kInvalidD; 
	phi2 = kInvalidD;
	Ex = kInvalidD; // Sp2 - 13.26;
	kMomt = kInvalidD; // redisual momentum
	
	theta1c = kInvalidD;
	theta2c = kInvalidD;
	phi1c = kInvalidD; 
	phi2c = kInvalidD;
	Exc = kInvalidD;
	kMomtc = kInvalidD;

	newTree->Branch("eventID",&eventID,"eventID/I");   
	newTree->Branch("runNum", &runNum, "runNum/I");
	newTree->Branch("gateNum",&gateNum,"gateNum/I");
	
	newTree->Branch("tofFH9",&tofFH9,"tofFH9/D");
	newTree->Branch("QFH9",&QFH9,"QFH9/D");
	
	newTree->Branch("s0x", &s0x, "s0x/D");
	newTree->Branch("s0y", &s0y, "s0y/D");
	
	newTree->Branch("tofS1", &tofS1, "tofS1/D");
	newTree->Branch("QS1", &QS1, "QS1/D");
	/*
	newTree->Branch("x1",&x1,"x1/D");
	newTree->Branch("a1",&a1,"a1/D");
	newTree->Branch("y1",&y1,"y1/D");
	newTree->Branch("b1",&b1,"b1/D");
	
	newTree->Branch("x2",&x2,"x2/D");
	newTree->Branch("a2",&a2,"a2/D");
	newTree->Branch("y2",&y2,"y2/D");
	newTree->Branch("b2",&b2,"b2/D");
	*/
	newTree->Branch("s1x",&s1x,"s1x/D");
	newTree->Branch("s1a",&s1a,"s1a/D");
	newTree->Branch("s1y",&s1y,"s1y/D");
	newTree->Branch("s1b",&s1b,"s1b/D");
	
	newTree->Branch("pidZ",&pidZ,"pidZ/D");
	newTree->Branch("pidAOQ",&pidAOQ,"pidAOQ/D");
	
	newTree->Branch("vertexZ",&vertexZ,"vertexZ/D");
	
	newTree->Branch("E1",&E1,"E1/D");
	newTree->Branch("E2",&E2,"E2/D");
	newTree->Branch("theta1",&theta1,"theta1/D");
	newTree->Branch("theta2",&theta2,"theta2/D");
	newTree->Branch("phi1",&phi1,"phi1/D");
	newTree->Branch("phi2",&phi2,"phi2/D");
	newTree->Branch("Ex",&Ex,"Ex/D");
	newTree->Branch("kMomt",&kMomt,"kMomt/D");

	
	newTree->Branch("theta1c",&theta1c,"theta1c/D");
	newTree->Branch("theta2c",&theta2c,"theta2c/D");
	newTree->Branch("phi1c",&phi1c,"phi1c/D");
	newTree->Branch("phi2c",&phi2c,"phi2c/D");
	newTree->Branch("Exc",&Exc,"Exc/D");
	newTree->Branch("kMomtc",&kMomtc,"kMomtc/D");
   
}

Bool_t Selector_PostAna::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef Selector_PostAna_cxx
