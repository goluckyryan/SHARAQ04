//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Feb 10 15:42:42 2015 by ROOT version 5.34/10
// from TTree tree/tree
// found on file: 23F_0208.root
//////////////////////////////////////////////////////////

#ifndef test_Selector_h
#define test_Selector_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.
//#include "<TEventHeader.h>"
//#include "./share/src/cont/TCoinRegData.h"
//#include "/share/src/gate/TGateArray.h"
//#include <TClonesArray.h>
//#include "/share/src/sh04/TParticleIdentifier.h"
//#include "/share/src/sh04/TP2PKinematicsData.h"

// Fixed size dimensions of array or collections stored in the TTree if any.

class test_Selector : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   
   TH2F* hist, *hist2, *hist3, *hist4, *histvertexZ;
   
   Int_t totnumEntry;
   Double_t kInvalidD = TMath::QuietNaN();
   
   // Declaration of leaf types
   art::TEventHeader *eventheader0;
   art::TCoinRegData *coinReg;
   art::TGateArray *gate;
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
   TClonesArray    *tof_D1_t;
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
   TBranch        *b_coinReg;   //!
   TBranch        *b_gate;   //!
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
   TBranch        *b_tof_D1_t;   //!
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

   test_Selector(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~test_Selector() { }
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

   ClassDef(test_Selector,0);
};

#endif

#ifdef test_Selector_cxx
void test_Selector::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).
   
   hist  = new TH2F("PID",   "PID",        50,   2,   3, 50,    1,  10);
   hist2 = new TH2F("hist2", "s1x vs A/Q", 50,   2,   3, 50, -200, 200);
   hist3 = new TH2F("hist3", "s1x vs Sp",  50, -80, 100, 50, -200, 200);
   hist4 = new TH2F("hist4", "s1x vs Z",   50,   1,  10, 50, -200, 200);
   histvertexZ = new TH1F("histvertexZ", "vertexZ",  100, -100, 300);
   
   totnumEntry = tree->GetEntries();

   // Set object pointer
   eventheader0 = 0;
   coinReg = 0;
   gate = 0;
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
   tof_D1_t = 0;
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
   fChain->SetBranchAddress("coinReg", &coinReg, &b_coinReg);
   fChain->SetBranchAddress("gate", &gate, &b_gate);
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
   fChain->SetBranchAddress("tof_D1_t", &tof_D1_t, &b_tof_D1_t);
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
}

Bool_t test_Selector::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef test_Selector_cxx
