//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Feb 18 19:46:27 2015 by ROOT version 5.34/10
// from TTree tree/tree
// found on file: 23F_0217_run23.root
//////////////////////////////////////////////////////////

//ifndef Selector_Aux_h
//define Selector_Aux_h

//include <TROOT.h>
//include <TChain.h>
//include <TFile.h>
//include <TSelector.h>

// Header file for the classes stored in the TTree if any.
/*
//include "./TEventHeader.h"
//include "./cont/TCoinRegData.h"
//include "./gate/TGateArray.h"
//include <TClonesArray.h>
//include "./sh04/TParticleIdentifier.h"
*/
// Fixed size dimensions of array or collections stored in the TTree if any.

class Selector_Aux : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   
   TH2F *h1, *h2, *h3, *h4, *h5, *h6, *h7, *h8, *h9, *h10, *h11, *h12;
   
   TH1F *g1, *g2, *g3;
   
   Double_t *X1wire, *X1driftLength, *X1charge;
   Double_t *X2wire, *X2driftLength, *X2charge;
   Double_t *X3wire, *X3driftLength, *X3charge;
   Double_t *X4wire, *X4driftLength, *X4charge;
   Double_t *X5wire, *X5driftLength, *X5charge;
   Double_t *X6wire, *X6driftLength, *X6charge;
   

   // Declaration of leaf types
   art::TEventHeader *eventheader;
   art::TCoinRegData *coinReg;
   art::TGateArray *gate;
   TClonesArray    *plaV1190_F3;
   TClonesArray    *plaV1190_FH9;
   TClonesArray    *tof_US;
   TClonesArray    *plaV775;
   TClonesArray    *tof_DS;
//   TClonesArray    *S0img;
//   TClonesArray    *dcs0d_DT;
//   TClonesArray    *dcs0d_x1;
//   TClonesArray    *dcs0d_x2;
//   TClonesArray    *dcs0d_y1;
//   TClonesArray    *dcs0d_y2;
//   TClonesArray    *dcs0d;
   TClonesArray    *nyoki;
   TClonesArray    *nyoki_t;
   TClonesArray    *tof_D1;
   TClonesArray    *smwdc_S1_x1;
   TClonesArray    *smwdc_S1_x2;
   TClonesArray    *smwdc_S1_u1;
   TClonesArray    *smwdc_S1_u2;
   TClonesArray    *smwdc_S1_v1;
   TClonesArray    *smwdc_S1_v2;
//   TClonesArray    *smwdc_S1;
//   art::sh04::TParticleIdentifier *pid_ds;
//   TClonesArray    *tofL;
//   TClonesArray    *tofR;
//   TClonesArray    *tofS0D;

   // List of branches
   TBranch        *b_eventheader;   //!
   TBranch        *b_coinReg;   //!
   TBranch        *b_gate;   //!
   TBranch        *b_plaV1190_F3;   //!
   TBranch        *b_plaV1190_FH9;   //!
   TBranch        *b_tof_US;   //!
   TBranch        *b_plaV775;   //!
   TBranch        *b_tof_DS;   //!
//   TBranch        *b_S0img;   //!
//   TBranch        *b_dcs0d_DT;   //!
//   TBranch        *b_dcs0d_x1;   //!
//   TBranch        *b_dcs0d_x2;   //!
//   TBranch        *b_dcs0d_y1;   //!
//   TBranch        *b_dcs0d_y2;   //!
//   TBranch        *b_dcs0d;   //!
   TBranch        *b_nyoki;   //!
   TBranch        *b_nyoki_t;   //!
   TBranch        *b_tof_D1;   //!
   TBranch        *b_smwdc_S1_x1;   //!
   TBranch        *b_smwdc_S1_x2;   //!
   TBranch        *b_smwdc_S1_u1;   //!
   TBranch        *b_smwdc_S1_u2;   //!
   TBranch        *b_smwdc_S1_v1;   //!
   TBranch        *b_smwdc_S1_v2;   //!
//   TBranch        *b_smwdc_S1;   //!
//   TBranch        *b_pid_ds;   //!
//   TBranch        *b_tofL;   //!
//   TBranch        *b_tofR;   //!
//   TBranch        *b_tofS0D;   //!

   Selector_Aux(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~Selector_Aux() { }
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

   ClassDef(Selector_Aux,0);
};

//endif

//ifdef Selector_Aux_cxx
void Selector_Aux::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).
   
   h1 = new TH2F("h1", "X1 , Charge vs wireID",  56, 1,57, 200, 0, 1500);
   h2 = new TH2F("h2", "h2",  56, 1,57,  56, 1, 57);
   h3 = new TH2F("h3", "h3", 100, 0,10, 100, 0, 10);
   h4 = new TH2F("h4", "h4", 100, 0,10, 100, 0, 10);
   h5 = new TH2F("h5", "h5", 100, 0,10, 100, 0, 10);
   h6 = new TH2F("h6", "h6", 100, 0,10, 100, 0, 10);
   h7 = new TH2F("h7", "h7", 100, 0,10, 100, 0, 10);
   h8 = new TH2F("h8", "h8",  56, 1,57,  56, 1, 57);
   h9 = new TH2F("h9", "h9", 100, 0,10, 100, 0, 10);
   h10 = new TH2F("h10", "h10", 100, 0,10, 100, 0, 10);
   h11 = new TH2F("h11", "h11", 100, 0,10, 100, 0, 10);
   h12 = new TH2F("h12", "h12", 100, 0,10, 100, 0, 10);
   
   g1 = new TH1F("g1", "X1 Multiplicity Q > 750", 10, 0, 10); g1->SetLineColor(2);
   g2 = new TH1F("g2", "X1 Multiplicity Q > 0", 10, 0, 10);
   g3 = new TH1F("g3", "X1 Multiplicity (Q>0) - (Q>700)", 10, 0, 10);
   
   
   X1wire = new Double_t[]; X1driftLength= new Double_t[]; X1charge= new Double_t [];
   X2wire = new Double_t[]; X2driftLength= new Double_t[]; X2charge= new Double_t [];
   X3wire = new Double_t[]; X3driftLength= new Double_t[]; X3charge= new Double_t [];
   X4wire = new Double_t[]; X4driftLength= new Double_t[]; X4charge= new Double_t [];
   X5wire = new Double_t[]; X5driftLength= new Double_t[]; X5charge= new Double_t [];
   X6wire = new Double_t[]; X6driftLength= new Double_t[]; X6charge= new Double_t [];

   // Set object pointer
   eventheader = 0;
   coinReg = 0;
   gate = 0;
   plaV1190_F3 = 0;
   plaV1190_FH9 = 0;
   tof_US = 0;
   plaV775 = 0;
   tof_DS = 0;
//   S0img = 0;
//   dcs0d_DT = 0;
//   dcs0d_x1 = 0;
//   dcs0d_x2 = 0;
//   dcs0d_y1 = 0;
//   dcs0d_y2 = 0;
//   dcs0d = 0;
   nyoki = 0;
   nyoki_t = 0;
   tof_D1 = 0;
   smwdc_S1_x1 = 0;
   smwdc_S1_x2 = 0;
   smwdc_S1_u1 = 0;
   smwdc_S1_u2 = 0;
   smwdc_S1_v1 = 0;
   smwdc_S1_v2 = 0;
//   smwdc_S1 = 0;
//   pid_ds = 0;
//   tofL = 0;
//   tofR = 0;
//   tofS0D = 0;
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
//   fChain->SetBranchAddress("S0img", &S0img, &b_S0img);
//   fChain->SetBranchAddress("dcs0d_DT", &dcs0d_DT, &b_dcs0d_DT);
//   fChain->SetBranchAddress("dcs0d_x1", &dcs0d_x1, &b_dcs0d_x1);
//   fChain->SetBranchAddress("dcs0d_x2", &dcs0d_x2, &b_dcs0d_x2);
//   fChain->SetBranchAddress("dcs0d_y1", &dcs0d_y1, &b_dcs0d_y1);
//   fChain->SetBranchAddress("dcs0d_y2", &dcs0d_y2, &b_dcs0d_y2);
//   fChain->SetBranchAddress("dcs0d", &dcs0d, &b_dcs0d);
   fChain->SetBranchAddress("nyoki", &nyoki, &b_nyoki);
   fChain->SetBranchAddress("nyoki_t", &nyoki_t, &b_nyoki_t);
   fChain->SetBranchAddress("tof_D1", &tof_D1, &b_tof_D1);
   fChain->SetBranchAddress("smwdc_S1_x1", &smwdc_S1_x1, &b_smwdc_S1_x1);
   fChain->SetBranchAddress("smwdc_S1_x2", &smwdc_S1_x2, &b_smwdc_S1_x2);
   fChain->SetBranchAddress("smwdc_S1_u1", &smwdc_S1_u1, &b_smwdc_S1_u1);
   fChain->SetBranchAddress("smwdc_S1_u2", &smwdc_S1_u2, &b_smwdc_S1_u2);
   fChain->SetBranchAddress("smwdc_S1_v1", &smwdc_S1_v1, &b_smwdc_S1_v1);
   fChain->SetBranchAddress("smwdc_S1_v2", &smwdc_S1_v2, &b_smwdc_S1_v2);
//   fChain->SetBranchAddress("smwdc_S1", &smwdc_S1, &b_smwdc_S1);
//   fChain->SetBranchAddress("pid_ds", &pid_ds, &b_pid_ds);
//   fChain->SetBranchAddress("tofL", &tofL, &b_tofL);
//   fChain->SetBranchAddress("tofR", &tofR, &b_tofR);
//   fChain->SetBranchAddress("tofS0D", &tofS0D, &b_tofS0D);
}

Bool_t Selector_Aux::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

//endif // //ifdef Selector_Aux_cxx
