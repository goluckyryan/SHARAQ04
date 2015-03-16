//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Feb 25 18:46:01 2015 by ROOT version 5.34/10
// from TTree tree/tree
// found on file: test_2_run23.root
//////////////////////////////////////////////////////////

#ifndef Selector_haha_h
#define Selector_haha_h

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

class Selector_haha : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   
   TH1F* hx1a, *hx1b;
   TH1F* hx2a, *hx2b;
   TH1F* hu1a, *hu1b;
   TH1F* hu2a, *hu2b;
   TH1F* hv1a, *hv1b;
   TH1F* hv2a, *hv2b;
   
   TH2F* hAux;

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

   Selector_haha(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~Selector_haha() { }
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

   ClassDef(Selector_haha,0);
};

#endif

#ifdef Selector_haha_cxx
void Selector_haha::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).
   
   hx1a = new TH1F("hx1a", "Multiplicity x1", 20, 0, 20); hx1a->SetLineColor(2);
   hx1b = new TH1F("hx1b", "Multiplicity x1", 20, 0, 20); hx1b->SetLineColor(4);
   hx2a = new TH1F("hx2a", "Multiplicity x2", 20, 0, 20); hx2a->SetLineColor(2);
   hx2b = new TH1F("hx2b", "Multiplicity x2", 20, 0, 20); hx2b->SetLineColor(4);
   hu1a = new TH1F("hu1a", "Multiplicity u1", 20, 0, 20); hu1a->SetLineColor(2);
   hu1b = new TH1F("hu1b", "Multiplicity u1", 20, 0, 20); hu1b->SetLineColor(4);
   hu2a = new TH1F("hu2a", "Multiplicity u2", 20, 0, 20); hu2a->SetLineColor(2);
   hu2b = new TH1F("hu2b", "Multiplicity u2", 20, 0, 20); hu2b->SetLineColor(4);
   hv1a = new TH1F("hv1a", "Multiplicity v1", 20, 0, 20); hv1a->SetLineColor(2);
   hv1b = new TH1F("hv1b", "Multiplicity v1", 20, 0, 20); hv1b->SetLineColor(4);
   hv2a = new TH1F("hv2a", "Multiplicity v2", 20, 0, 20); hv2a->SetLineColor(2);
   hv2b = new TH1F("hv2b", "Multiplicity v2", 20, 0, 20); hv2b->SetLineColor(4);
   
   hAux = new TH2F("hAux", "hAux", 100, -2, 2, 100, -2, 2);
   
   

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

Bool_t Selector_haha::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef Selector_haha_cxx
