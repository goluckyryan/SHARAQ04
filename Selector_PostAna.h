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
#include <TMath.h>

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
   
   //==========================  STore in new ROOT file
   TFile * saveFile;
   TTree * newTree;
   
   TString saveFileName;
   
   Int_t totnumEntry;
   
   Int_t eventID;
	//  runNumber
	Int_t runNum;
   // coinReg
   Int_t coinRegNum; // 1abc, a = all other, b = beam, c = ppcoin, if 1001, only beam trigger, if 1011, both beam
	// gate
	Int_t gateNum;
   Int_t pidusGate;
   Int_t piddsGate[2];
	//// S0img
	//Double_t s0x, s0y, s0a, s0b;
	// get tof and charge upstream
	Double_t tofFH9, qFH9, tFH9;
	Double_t qF3, tF3;
   //Double_t tTplaLB,  tTplaLF;
   //Double_t tTplaRB,  tTplaRF;
	Double_t tofTplaL, qTplaL, tTplaL;
	Double_t tofTplaR, qTplaR, tTplaR;
   //// tof and Q from S0DPL v775
   Double_t tof_S0D, qS0D, tS0D;
   //Double_t qS0DU, qS0DD, tS0DU, tS0DD;
   
   Double_t tTgt;
	// tof from S0DPL to nyoki
	Double_t tofS1[14], qS1[14], tS1[14];
	//Double_t qS1c[14];
	// SMWDC X Y
//	Double_t x1, y1, a1, b1; // for smwdc-L
//	Double_t x2, y2, a2, b2; // for smwdc-R
//   Double_t s1x, s1y, s1a, s1b; // for smwdc-S1
//	// pid_ds
//	Double_t pidZ, pidAOQ;
//	//vertex
//	Double_t vertexZ;
//	// Phsyics
//	Double_t E1, E2;
//	Double_t theta1, theta2;
//	Double_t phi1, phi2;
//	Double_t Ex;// Sp2 - 13.26;
//	Double_t ExS;// Sp - 13.26;
//	Double_t kMomt; // redisual momentum
//	//carbon
//	Double_t theta1c, theta2c;
//	Double_t phi1c, phi2c;
//	Double_t Exc, kMomtc;

   //============================================= Declaration of leaf types
   art::TEventHeader *eventheader;
//   art::TEventHeader *eventheader_shvmism;
//   art::TEventHeader *eventheader_shvmif3;
   art::TCoinRegData *coinReg;
   art::TGateArray *gate;
//   TClonesArray    *plaV1190_F3;
//   TClonesArray    *plaV1190_FH9;
//   TClonesArray    *tof_US;
//   TClonesArray    *plaV775_L_cal;
//   TClonesArray    *plaV775_R_cal;
   TClonesArray    *plaV775;
//   TClonesArray    *tof_DS;
//   TClonesArray    *S0img;
//   TClonesArray    *smwdc_L;
//   TClonesArray    *smwdc_R;
   TClonesArray    *nyoki;
//   TClonesArray    *nyoki_t;
   TClonesArray    *tof_D1;
//   TClonesArray    *smwdc_S1;
//   art::sh04::TParticleIdentifier *pid_us;
//   art::sh04::TParticleIdentifier *pid_ds;
//   TClonesArray    *vertex;
   TClonesArray    *tofL;
   TClonesArray    *tofR;
   TClonesArray    *tofS0D;
//   art::sh04::TP2PKinematicsData *p2p;
//   art::sh04::TP2PKinematicsData *p2p_Lab;
//   art::sh04::TP2PKinematicsData *p2p_c;
//   art::sh04::TP2PKinematicsData *p2p_c_lab;

   //==================================================== List of branches
   TBranch        *b_eventheader;   //!
//   TBranch        *b_eventheader_shvmism;   //!
//   TBranch        *b_eventheader_shvmif3;   //!
   TBranch        *b_coinReg;   //!
   TBranch        *b_gate;   //!
//   TBranch        *b_plaV1190_F3;   //!
//   TBranch        *b_plaV1190_FH9;   //!
//   TBranch        *b_tof_US;   //!
//   TBranch        *b_plaV775_L_cal;   //!
//   TBranch        *b_plaV775_R_cal;   //!
   TBranch        *b_plaV775;   //!
//   TBranch        *b_tof_DS;   //!
//   TBranch        *b_S0img;   //!
//   TBranch        *b_smwdc_L;   //!
//   TBranch        *b_smwdc_R;   //!
   TBranch        *b_nyoki;   //!
//   TBranch        *b_nyoki_t;   //!
   TBranch        *b_tof_D1;   //!
//   TBranch        *b_smwdc_S1;   //!
//   TBranch        *b_pid_us;   //!
//   TBranch        *b_pid_ds;   //!
//   TBranch        *b_vertex;   //!
//   TBranch        *b_tofL;   //!
//   TBranch        *b_tofR;   //!
//   TBranch        *b_tofS0D;   //!
//   TBranch        *b_p2p;   //!
//   TBranch        *b_p2p_Lab;   //!
//   TBranch        *b_p2p_c;   //!
//   TBranch        *b_p2p_c_lab;   //!

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

   //======================================= Set object pointer
   eventheader = 0;
//   eventheader_shvmism = 0;
//   eventheader_shvmif3 = 0;
   coinReg = 0;
   gate = 0;
//   plaV1190_F3 = 0;
//   plaV1190_FH9 = 0;
//   tof_US = 0;
   plaV775 = 0;
//   plaV775_L_cal = 0;
//   plaV775_R_cal = 0;
//   tof_DS = 0;
//   S0img = 0;
//   smwdc_L = 0;
//   smwdc_R = 0;
   nyoki = 0;
//   nyoki_t = 0;
   tof_D1 = 0;
//   smwdc_S1 = 0;
//   pid_us = 0;
//   pid_ds = 0;
//   vertex = 0;
   tofL = 0;
   tofR = 0;
   tofS0D = 0;
//   p2p = 0;
//   p2p_Lab = 0;
//   p2p_c = 0;
//   p2p_c_lab = 0;
   //===================================== Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("eventheader", &eventheader, &b_eventheader);
//   fChain->SetBranchAddress("eventheader0", &eventheader, &b_eventheader);
//   fChain->SetBranchAddress("eventheader_shvmism", &eventheader_shvmism, &b_eventheader_shvmism);
//   fChain->SetBranchAddress("eventheader_shvmif3", &eventheader_shvmif3, &b_eventheader_shvmif3);
   fChain->SetBranchAddress("coinReg", &coinReg, &b_coinReg);
   fChain->SetBranchAddress("gate", &gate, &b_gate);
//   fChain->SetBranchAddress("plaV1190_F3", &plaV1190_F3, &b_plaV1190_F3);
//   fChain->SetBranchAddress("plaV1190_FH9", &plaV1190_FH9, &b_plaV1190_FH9);
//   fChain->SetBranchAddress("tof_US", &tof_US, &b_tof_US);
//   fChain->SetBranchAddress("plaV775_L_cal", &plaV775_L_cal, &b_plaV775_L_cal);
//   fChain->SetBranchAddress("plaV775_R_cal", &plaV775_R_cal, &b_plaV775_R_cal);
   fChain->SetBranchAddress("plaV775", &plaV775, &b_plaV775);
//   fChain->SetBranchAddress("tof_DS", &tof_DS, &b_tof_DS);
//   fChain->SetBranchAddress("S0img", &S0img, &b_S0img);
//   fChain->SetBranchAddress("smwdc_L", &smwdc_L, &b_smwdc_L);
//   fChain->SetBranchAddress("smwdc_R", &smwdc_R, &b_smwdc_R);
   fChain->SetBranchAddress("nyoki", &nyoki, &b_nyoki);
//   fChain->SetBranchAddress("nyoki_t", &nyoki_t, &b_nyoki_t);
   fChain->SetBranchAddress("tof_D1", &tof_D1, &b_tof_D1);
//   fChain->SetBranchAddress("smwdc_S1", &smwdc_S1, &b_smwdc_S1);
//   fChain->SetBranchAddress("pid_us", &pid_us, &b_pid_us);
//   fChain->SetBranchAddress("pid_ds", &pid_ds, &b_pid_ds);
//   fChain->SetBranchAddress("vertex", &vertex, &b_vertex);
//   fChain->SetBranchAddress("tofL", &tofL, &b_tofL);
//   fChain->SetBranchAddress("tofR", &tofR, &b_tofR);
//   fChain->SetBranchAddress("tofS0D", &tofS0D, &b_tofS0D);
//   fChain->SetBranchAddress("p2p", &p2p, &b_p2p);
//   fChain->SetBranchAddress("p2p_Lab", &p2p_Lab, &b_p2p_Lab);
//   fChain->SetBranchAddress("p2p_c", &p2p_c, &b_p2p_c);
//   fChain->SetBranchAddress("p2p_c_lab", &p2p_c_lab, &b_p2p_c_lab);
   
   //Store in New ROOT file
   saveFileName = fChain->GetDirectory()->GetName();
   saveFileName = "P_"+saveFileName;
   
   printf("Converting %s ------> %s \n", fChain->GetDirectory()->GetName(), saveFileName.Data());
   
   saveFile = new TFile( saveFileName,"recreate");
   newTree =  new TTree("tree","tree");
   
   
   eventID = -1;
	runNum = -1;
   coinRegNum= 1000;
	gateNum = -1;
   pidusGate = -10;
   piddsGate[0] = 0;
   piddsGate[1] = 0;
//	s0x = TMath::QuietNaN(); 
//	s0y = TMath::QuietNaN();
//	s0a = TMath::QuietNaN();
//	s0b = TMath::QuietNaN();
	tofFH9 = TMath::QuietNaN();  qFH9 = TMath::QuietNaN(); tFH9 = TMath::QuietNaN();
	qF3 = TMath::QuietNaN(); tF3 = TMath::QuietNaN();
   tTgt = TMath::QuietNaN();
	tofTplaL = TMath::QuietNaN();  qTplaL = TMath::QuietNaN(); tTplaL = TMath::QuietNaN();
//	tTplaLB = TMath::QuietNaN(); tTplaLF = TMath::QuietNaN();
	tofTplaR = TMath::QuietNaN();  qTplaR = TMath::QuietNaN(); tTplaR = TMath::QuietNaN();
//	tTplaRB = TMath::QuietNaN(); tTplaRF = TMath::QuietNaN();
   tof_S0D = TMath::QuietNaN(); qS0D = TMath::QuietNaN(); tS0D = TMath::QuietNaN();
//   qS0DU = TMath::QuietNaN(); tS0DU = TMath::QuietNaN();
//   qS0DD = TMath::QuietNaN(); tS0DD = TMath::QuietNaN();
   for( Int_t p = 0; p < 14; p++){
      tofS1[p] = TMath::QuietNaN();
      tS1[p] = TMath::QuietNaN();
      qS1[p] = TMath::QuietNaN();
      //qS1c[p] = TMath::QuietNaN();
   }
//	x1 = TMath::QuietNaN();
//	y1 = TMath::QuietNaN();
//	a1 = TMath::QuietNaN();
//	b1 = TMath::QuietNaN(); 
//	x2 = TMath::QuietNaN();
//	y2 = TMath::QuietNaN(); 
//	a2 = TMath::QuietNaN(); 
//	b2 = TMath::QuietNaN(); 
//   s1x = TMath::QuietNaN();
//   s1y = TMath::QuietNaN(); 
//   s1a = TMath::QuietNaN(); 
//   s1b = TMath::QuietNaN();
//   pidZ = TMath::QuietNaN();
//   pidAOQ = TMath::QuietNaN();
//	vertexZ = TMath::QuietNaN();
//	E1 = TMath::QuietNaN();
//	E2 = TMath::QuietNaN();
//	theta1 = TMath::QuietNaN();
//	theta2 = TMath::QuietNaN();
//	phi1 = TMath::QuietNaN(); 
//	phi2 = TMath::QuietNaN();
//	Ex = TMath::QuietNaN(); // Sp2 - 13.26;
//	ExS = TMath::QuietNaN(); // Sp - 13.26;
//	kMomt = TMath::QuietNaN(); // redisual momentum
//	
//	theta1c = TMath::QuietNaN();
//	theta2c = TMath::QuietNaN();
//	phi1c = TMath::QuietNaN(); 
//	phi2c = TMath::QuietNaN();
//	Exc = TMath::QuietNaN();
//	kMomtc = TMath::QuietNaN();

	newTree->Branch("eventID",&eventID,"eventID/I");   
	newTree->Branch("runNum", &runNum, "runNum/I");
	newTree->Branch("coinReg", &coinRegNum, "coinRegNum/I");
	newTree->Branch("gate",&gateNum,"gateNum/I");
	newTree->Branch("pidusGate", &pidusGate, "pidusGate/I");
//	newTree->Branch("piddsGate", piddsGate, "piddsGate[2]/I");
//	newTree->Branch("tofFH9",&tofFH9,"tofFH9/D");
//	newTree->Branch("qFH9",&qFH9,"qFH9/D");
//	newTree->Branch("tFH9",&tFH9,"tFH9/D");
//
//	newTree->Branch("qF3",&qF3,"qF3/D");
//	newTree->Branch("tF3",&tF3,"tF3/D");
//   
	newTree->Branch("tTgt",&tTgt,"tTgt/D");
//   
//	newTree->Branch("tTplaLB",&tTplaLB,"tTplaLB/D");
//	newTree->Branch("tTplaLF",&tTplaLF,"tTplaLF/D");
//	newTree->Branch("tTplaRB",&tTplaRB,"tTplaRB/D");
//	newTree->Branch("tTplaRF",&tTplaRF,"tTplaRF/D");
//
   newTree->Branch("tofTplaL",&tofTplaL,"tofTplaL/D");
   newTree->Branch("qTplaL",&qTplaL,"qTplaL/D");
   newTree->Branch("tTplaL",&tTplaL,"tTplaL/D");
   
   newTree->Branch("tofTplaR",&tofTplaR,"tofTplaR/D");
   newTree->Branch("qTplaR",&qTplaR,"qTplaR/D");
   newTree->Branch("tTplaR",&tTplaR,"tTplaR/D");

   newTree->Branch("tofS0D",&tof_S0D,"tof_S0D/D");
	newTree->Branch("qS0D",&qS0D,"qS0D/D");
	newTree->Branch("tS0D",&tS0D,"tS0D/D");
//
//	newTree->Branch("qS0DU",&qS0DU,"qS0DU/D");
//	newTree->Branch("tS0DU",&tS0DU,"tS0DU/D");
//
//	newTree->Branch("qS0DD",&qS0DD,"qS0DD/D");
//	newTree->Branch("tS0DD",&tS0DD,"tS0DD/D");
//   
//	newTree->Branch("s0x", &s0x, "s0x/D");
//	newTree->Branch("s0y", &s0y, "s0y/D");
//	newTree->Branch("s0a", &s0a, "s0a/D");
//	newTree->Branch("s0b", &s0b, "s0b/D");
//	
	newTree->Branch("tofS1", tofS1, "tofS1[14]/D");
	newTree->Branch("qS1", qS1, "qS1[14]/D");
//	newTree->Branch("qS1c", qS1c, "qS1c[14]/D");
	newTree->Branch("tS1", tS1, "tS1[14]/D");
	/*
	newTree->Branch("x1",&x1,"x1/D");
	newTree->Branch("a1",&a1,"a1/D");
	newTree->Branch("y1",&y1,"y1/D");
	newTree->Branch("b1",&b1,"b1/D");
	/*
	newTree->Branch("x2",&x2,"x2/D");
	newTree->Branch("a2",&a2,"a2/D");
	newTree->Branch("y2",&y2,"y2/D");
	newTree->Branch("b2",&b2,"b2/D");
	*/
//   newTree->Branch("s1x",&s1x,"s1x/D");
//   newTree->Branch("s1a",&s1a,"s1a/D");
//   newTree->Branch("s1y",&s1y,"s1y/D");
//   newTree->Branch("s1b",&s1b,"s1b/D");
//	
//	newTree->Branch("pidZ",&pidZ,"pidZ/D");
//	newTree->Branch("pidAOQ",&pidAOQ,"pidAOQ/D");
	/*
	newTree->Branch("vertexZ",&vertexZ,"vertexZ/D");
	
	newTree->Branch("E1",&E1,"E1/D");
	newTree->Branch("E2",&E2,"E2/D");
	newTree->Branch("theta1",&theta1,"theta1/D");
	newTree->Branch("theta2",&theta2,"theta2/D");
	newTree->Branch("phi1",&phi1,"phi1/D");
	newTree->Branch("phi2",&phi2,"phi2/D");
	newTree->Branch("Ex",&Ex,"Ex/D");
	newTree->Branch("ExS",&ExS,"ExS/D");
	newTree->Branch("kMomt",&kMomt,"kMomt/D");

	
	newTree->Branch("theta1c",&theta1c,"theta1c/D");
	newTree->Branch("theta2c",&theta2c,"theta2c/D");
	newTree->Branch("phi1c",&phi1c,"phi1c/D");
	newTree->Branch("phi2c",&phi2c,"phi2c/D");
	newTree->Branch("Exc",&Exc,"Exc/D");
	newTree->Branch("kMomtc",&kMomtc,"kMomtc/D");
   */
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
