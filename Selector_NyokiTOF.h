//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Apr  1 13:53:40 2015 by ROOT version 5.34/10
// from TTree tree/tree
// found on file: 23F_0330_run23.root
//////////////////////////////////////////////////////////

#ifndef Selector_NyokiTOF_h
#define Selector_NyokiTOF_h

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

class Selector_NyokiTOF : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   
   TH2F * h1, *h2, *h3, *h4, *h5, *h6;
   
   TH1F * g1, *g2, *g3, *g4, *g5, *g6;

   // Declaration of leaf types
   art::TEventHeader *eventheader;
   art::TCoinRegData *coinReg;
   art::TGateArray *gate;
   TClonesArray    *plaV1190_F3;
   TClonesArray    *plaV1190_FH9;
   TClonesArray    *tof_US;
   TClonesArray    *ppac;
   TClonesArray    *plaV775;
   TClonesArray    *tof_DS;
   TClonesArray    *S0img;
   TClonesArray    *tofL;
   TClonesArray    *tofR;
   TClonesArray    *tofS0D;
   TClonesArray    *nyoki;
   TClonesArray    *nyoki_t;
   TClonesArray    *tof_D1;
   TClonesArray    *smwdc_S1;

   // List of branches
   TBranch        *b_eventheader;   //!
   TBranch        *b_coinReg;   //!
   TBranch        *b_gate;   //!
   TBranch        *b_plaV1190_F3;   //!
   TBranch        *b_plaV1190_FH9;   //!
   TBranch        *b_tof_US;   //!
   TBranch        *b_ppac;   //!
   TBranch        *b_plaV775;   //!
   TBranch        *b_tof_DS;   //!
   TBranch        *b_S0img;   //!
   TBranch        *b_tofL;   //!
   TBranch        *b_tofR;   //!
   TBranch        *b_tofS0D;   //!
   TBranch        *b_nyoki;   //!
   TBranch        *b_nyoki_t;   //!
   TBranch        *b_tof_D1;   //!
   TBranch        *b_smwdc_S1;   //!

   Selector_NyokiTOF(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~Selector_NyokiTOF() { }
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

   ClassDef(Selector_NyokiTOF,0);
};

#endif

#ifdef Selector_NyokiTOF_cxx
void Selector_NyokiTOF::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).
   
   h1 = new TH2F("h1", "all",  500, 30, 38, 500, 30, 42);
   h2 = new TH2F("h2", "23F",  500, 30, 38, 500, 30, 42);
   h3 = new TH2F("h3", "22O",  500, 30, 38, 500, 30, 42);
   h4 = new TH2F("h4", "21O",  500, 30, 38, 500, 30, 42);
   h5 = new TH2F("h5", "10Be", 500, 30, 38, 500, 30, 42);
   h6 = new TH2F("h6", "8Li",  500, 30, 38, 500, 30, 42);
   
   g1 = new TH1F("g1", "all",  100,  -3, 0);
   g2 = new TH1F("g2", "23F",  100,  -3, 0);
   g3 = new TH1F("g3", "220",  100,  -3, 0);
   g4 = new TH1F("g4", "210",  100,  -3, 0);
   g5 = new TH1F("g5", "10Be", 100,  -3, 0);
   g6 = new TH1F("g6", "8Li",  100,  -3, 0);

   // Set object pointer
   eventheader = 0;
   coinReg = 0;
   gate = 0;
   plaV1190_F3 = 0;
   plaV1190_FH9 = 0;
   tof_US = 0;
   ppac = 0;
   plaV775 = 0;
   tof_DS = 0;
   S0img = 0;
   tofL = 0;
   tofR = 0;
   tofS0D = 0;
   nyoki = 0;
   nyoki_t = 0;
   tof_D1 = 0;
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
   fChain->SetBranchAddress("ppac", &ppac, &b_ppac);
   fChain->SetBranchAddress("plaV775", &plaV775, &b_plaV775);
   fChain->SetBranchAddress("tof_DS", &tof_DS, &b_tof_DS);
   fChain->SetBranchAddress("S0img", &S0img, &b_S0img);
   fChain->SetBranchAddress("tofL", &tofL, &b_tofL);
   fChain->SetBranchAddress("tofR", &tofR, &b_tofR);
   fChain->SetBranchAddress("tofS0D", &tofS0D, &b_tofS0D);
   fChain->SetBranchAddress("nyoki", &nyoki, &b_nyoki);
   fChain->SetBranchAddress("nyoki_t", &nyoki_t, &b_nyoki_t);
   fChain->SetBranchAddress("tof_D1", &tof_D1, &b_tof_D1);
   fChain->SetBranchAddress("smwdc_S1", &smwdc_S1, &b_smwdc_S1);
}

Bool_t Selector_NyokiTOF::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef Selector_NyokiTOF_cxx
