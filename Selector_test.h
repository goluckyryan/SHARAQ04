//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Mar 11 10:35:31 2015 by ROOT version 5.34/10
// from TTree tree/tree
// found on file: test_run24_ref.root
//////////////////////////////////////////////////////////

#ifndef Selector_test_h
#define Selector_test_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.
//#include "./TEventHeader.h"
//#include "./cont/TCoinRegData.h"
//#include "./gate/TGateArray.h"
//#include <TClonesArray.h>

// Fixed size dimensions of array or collections stored in the TTree if any.

class Selector_test : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

   TH2F * g1;

   // Declaration of leaf types
   art::TEventHeader *eventheader;
   art::TCoinRegData *coinReg;
   art::TGateArray *gate;
   TClonesArray    *plaV1190_F3;
   TClonesArray    *plaV1190_FH9;
   TClonesArray    *tof_US;
   TClonesArray    *plaV775;
   TClonesArray    *tof_DS;
   TClonesArray    *nyoki;
   TClonesArray    *nyoki_t;
   TClonesArray    *tof_D1;
   TClonesArray    *smwdc_S1_x1;
   TClonesArray    *smwdc_S1_x2;
   TClonesArray    *smwdc_S1_u1;
   TClonesArray    *smwdc_S1_u2;
   TClonesArray    *smwdc_S1_v1;
   TClonesArray    *smwdc_S1_v2;
   TClonesArray    *smwdc_S1;

   // List of branches
   TBranch        *b_eventheader;   //!
   TBranch        *b_coinReg;   //!
   TBranch        *b_gate;   //!
   TBranch        *b_plaV1190_F3;   //!
   TBranch        *b_plaV1190_FH9;   //!
   TBranch        *b_tof_US;   //!
   TBranch        *b_plaV775;   //!
   TBranch        *b_tof_DS;   //!
   TBranch        *b_nyoki;   //!
   TBranch        *b_nyoki_t;   //!
   TBranch        *b_tof_D1;   //!
   TBranch        *b_smwdc_S1_x1;   //!
   TBranch        *b_smwdc_S1_x2;   //!
   TBranch        *b_smwdc_S1_u1;   //!
   TBranch        *b_smwdc_S1_u2;   //!
   TBranch        *b_smwdc_S1_v1;   //!
   TBranch        *b_smwdc_S1_v2;   //!
   TBranch        *b_smwdc_S1;   //!

   Selector_test(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~Selector_test() { }
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

   ClassDef(Selector_test,0);
};

#endif

#ifdef Selector_test_cxx
void Selector_test::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).
   
   g1 = new TH2F("g1", "g1", 200, -200, 200, 200, 0, 1100);

   // Set object pointer
   eventheader = 0;
   coinReg = 0;
   gate = 0;
   plaV1190_F3 = 0;
   plaV1190_FH9 = 0;
   tof_US = 0;
   plaV775 = 0;
   tof_DS = 0;
   nyoki = 0;
   nyoki_t = 0;
   tof_D1 = 0;
   smwdc_S1_x1 = 0;
   smwdc_S1_x2 = 0;
   smwdc_S1_u1 = 0;
   smwdc_S1_u2 = 0;
   smwdc_S1_v1 = 0;
   smwdc_S1_v2 = 0;
   smwdc_S1 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("eventheader", &eventheader, &b_eventheader);
   fChain->SetBranchAddress("coinReg", &coinReg, &b_coinReg);
   fChain->SetBranchAddress("gate", &gate, &b_gate);
   fChain->SetBranchAddress("plaV1190_F3", &plaV1190_F3, &b_plaV1190_F3);
   fChain->SetBranchAddress("plaV1190_FH9", &plaV1190_FH9, &b_plaV1190_FH9);
   fChain->SetBranchAddress("tof_US", &tof_US, &b_tof_US);
   fChain->SetBranchAddress("plaV775", &plaV775, &b_plaV775);
   fChain->SetBranchAddress("tof_DS", &tof_DS, &b_tof_DS);
   fChain->SetBranchAddress("nyoki", &nyoki, &b_nyoki);
   fChain->SetBranchAddress("nyoki_t", &nyoki_t, &b_nyoki_t);
   fChain->SetBranchAddress("tof_D1", &tof_D1, &b_tof_D1);
   fChain->SetBranchAddress("smwdc_S1_x1", &smwdc_S1_x1, &b_smwdc_S1_x1);
   fChain->SetBranchAddress("smwdc_S1_x2", &smwdc_S1_x2, &b_smwdc_S1_x2);
   fChain->SetBranchAddress("smwdc_S1_u1", &smwdc_S1_u1, &b_smwdc_S1_u1);
   fChain->SetBranchAddress("smwdc_S1_u2", &smwdc_S1_u2, &b_smwdc_S1_u2);
   fChain->SetBranchAddress("smwdc_S1_v1", &smwdc_S1_v1, &b_smwdc_S1_v1);
   fChain->SetBranchAddress("smwdc_S1_v2", &smwdc_S1_v2, &b_smwdc_S1_v2);
   fChain->SetBranchAddress("smwdc_S1", &smwdc_S1, &b_smwdc_S1);
}

Bool_t Selector_test::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef Selector_test_cxx
