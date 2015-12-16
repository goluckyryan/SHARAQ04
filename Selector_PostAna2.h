//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jul 24 15:48:54 2015 by ROOT version 5.34/10
// from TTree tree/tree
// found on file: X_25F_ppcoin_r14_core.root
//////////////////////////////////////////////////////////

#ifndef Selector_PostAna2_h
#define Selector_PostAna2_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class Selector_PostAna2 : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain

TBenchmark clock;
   Bool_t shown;
   
   Int_t count;

   Double_t mp;
   
   Double_t Sp0;
   Double_t mass, massA, massZ;
   Double_t Brho0, BrhoDS;
   
   Double_t beamZ;

   //==========================  STore in new ROOT file
   TFile * saveFile;
   TTree * newTree;
   
   TString saveFileName;
   Int_t totnumEntry;
   
   //-----------get tof and charge upstream
   Double_t tofF3FH9;
   Double_t tofTplaL;
   Double_t tofTplaR;
   Double_t tofS0S0D;
   Double_t tofS0DS1; 
   //-----------pid_ds
   Double_t pidZ, pidAOQ;
   Double_t tofc, s1xc;
   Double_t pidAOQ_p;
   Double_t FL, beta;
   //-----------Phsyics
   Double_t E1, E2;
   Double_t theta1, theta2;
   Double_t phi1, phi2;
   Double_t Ex;// Sp2 - 13.26;
   Double_t kMomt; // redisual momentum
   
   
   // Declaration of leaf types
   Int_t           eventID;
   Int_t           runNum;
   Double_t        tF3;
   Double_t        tFH9;
   Double_t        s0x;
   Double_t        s0y;
   Double_t        s0a;
   Double_t        s0b;
   Double_t        s0dx;
   Double_t        s0dy;
   Double_t        ppacX;
   Double_t        qTplaL;
   Double_t        tTplaL;
   Double_t        qTplaR;
   Double_t        tTplaR;
   Double_t        tS0;
   Double_t        qS0D;
   Double_t        tS0D;
   Double_t        qS1;
   Double_t        tS1;
   Int_t           nyokiID;
   Double_t        x1;
   Double_t        a1;
   Double_t        y1;
   Double_t        b1;
   Double_t        x2;
   Double_t        a2;
   Double_t        y2;
   Double_t        b2;
   Double_t        s1x;
   Double_t        s1a;
   Double_t        s1y;
   Double_t        s1b;
   Double_t        vertexZ;
   Double_t        vertexX;
   Double_t        vertexY;

   // List of branches
   TBranch        *b_eventID;   //!
   TBranch        *b_runNum;   //!
   TBranch        *b_tF3;   //!
   TBranch        *b_tFH9;   //!
   TBranch        *b_s0x;   //!
   TBranch        *b_s0y;   //!
   TBranch        *b_s0a;   //!
   TBranch        *b_s0b;   //!
   TBranch        *b_s0dx;   //!
   TBranch        *b_s0dy;   //!
   TBranch        *b_ppacX;   //!
   TBranch        *b_qTplaL;   //!
   TBranch        *b_tTplaL;   //!
   TBranch        *b_qTplaR;   //!
   TBranch        *b_tTplaR;   //!
   TBranch        *b_tS0;   //!
   TBranch        *b_qS0D;   //!
   TBranch        *b_tS0D;   //!
   TBranch        *b_qS1;   //!
   TBranch        *b_tS1;   //!
   TBranch        *b_nyokiID;   //!
   TBranch        *b_x1;   //!
   TBranch        *b_a1;   //!
   TBranch        *b_y1;   //!
   TBranch        *b_b1;   //!
   TBranch        *b_x2;   //!
   TBranch        *b_a2;   //!
   TBranch        *b_y2;   //!
   TBranch        *b_b2;   //!
   TBranch        *b_s1x;   //!
   TBranch        *b_s1a;   //!
   TBranch        *b_s1y;   //!
   TBranch        *b_s1b;   //!
   TBranch        *b_vertexZ;   //!
   TBranch        *b_vertexX;   //!
   TBranch        *b_vertexY;   //!

   Selector_PostAna2(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~Selector_PostAna2() { }
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

   ClassDef(Selector_PostAna2,0);
};

#endif

#ifdef Selector_PostAna2_cxx
void Selector_PostAna2::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).
   
   totnumEntry = tree->GetEntries();

   count = 0;
   
   mp = 938.272;


   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("eventID", &eventID, &b_eventID);
   fChain->SetBranchAddress("runNum", &runNum, &b_runNum);
   fChain->SetBranchAddress("tF3", &tF3, &b_tF3);
   fChain->SetBranchAddress("tFH9", &tFH9, &b_tFH9);
   fChain->SetBranchAddress("s0x", &s0x, &b_s0x);
   fChain->SetBranchAddress("s0y", &s0y, &b_s0y);
   fChain->SetBranchAddress("s0a", &s0a, &b_s0a);
   fChain->SetBranchAddress("s0b", &s0b, &b_s0b);
   fChain->SetBranchAddress("s0dx", &s0dx, &b_s0dx);
   fChain->SetBranchAddress("s0dy", &s0dy, &b_s0dy);
   fChain->SetBranchAddress("ppacX", &ppacX, &b_ppacX);
   fChain->SetBranchAddress("qTplaL", &qTplaL, &b_qTplaL);
   fChain->SetBranchAddress("tTplaL", &tTplaL, &b_tTplaL);
   fChain->SetBranchAddress("qTplaR", &qTplaR, &b_qTplaR);
   fChain->SetBranchAddress("tTplaR", &tTplaR, &b_tTplaR);
   fChain->SetBranchAddress("tS0", &tS0, &b_tS0);
   fChain->SetBranchAddress("qS0D", &qS0D, &b_qS0D);
   fChain->SetBranchAddress("tS0D", &tS0D, &b_tS0D);
   fChain->SetBranchAddress("qS1", &qS1, &b_qS1);
   fChain->SetBranchAddress("tS1", &tS1, &b_tS1);
   fChain->SetBranchAddress("nyokiID", &nyokiID, &b_nyokiID);
   fChain->SetBranchAddress("x1", &x1, &b_x1);
   fChain->SetBranchAddress("a1", &a1, &b_a1);
   fChain->SetBranchAddress("y1", &y1, &b_y1);
   fChain->SetBranchAddress("b1", &b1, &b_b1);
   fChain->SetBranchAddress("x2", &x2, &b_x2);
   fChain->SetBranchAddress("a2", &a2, &b_a2);
   fChain->SetBranchAddress("y2", &y2, &b_y2);
   fChain->SetBranchAddress("b2", &b2, &b_b2);
   fChain->SetBranchAddress("s1x", &s1x, &b_s1x);
   fChain->SetBranchAddress("s1a", &s1a, &b_s1a);
   fChain->SetBranchAddress("s1y", &s1y, &b_s1y);
   fChain->SetBranchAddress("s1b", &s1b, &b_s1b);
   fChain->SetBranchAddress("vertexZ", &vertexZ, &b_vertexZ);
   fChain->SetBranchAddress("vertexX", &vertexX, &b_vertexX);
   fChain->SetBranchAddress("vertexY", &vertexY, &b_vertexY);
   
   if( !b_ppacX ) printf(" no ppacX \n");

   //================================Store in New ROOT file
   saveFileName = fChain->GetDirectory()->GetName();
   saveFileName = "Z_"+saveFileName;
   
   printf("Converting %s ------> %s , total Entry : %d \n", fChain->GetDirectory()->GetName(), saveFileName.Data(), totnumEntry);
   
   saveFile = new TFile( saveFileName,"recreate");
   newTree =  new TTree("tree","tree");
   
   clock.Reset();
   clock.Start("timer");
   shown = 0;
   
   //________________________________________________ Branch
   newTree->Branch("s0x",&s0x,"s0x/D");
   newTree->Branch("s0y",&s0y,"s0y/D");
   newTree->Branch("s0dx",&s0dx,"s0dx/D");
   newTree->Branch("vertexZ",&vertexZ,"vertexZ/D");
   
   newTree->Branch("tofTplaL",&tofTplaL,"tofTplaL/D");
   newTree->Branch("tofTplaR",&tofTplaR,"tofTplaR/D");   
   newTree->Branch("tofS0S0D",&tofS0S0D,"tofS0S0D/D");
   newTree->Branch("tofS0DS1", &tofS0DS1, "tofS0DS1/D");

   newTree->Branch("pidZ",&pidZ,"pidZ/D");
   newTree->Branch("pidAOQ",&pidAOQ,"pidAOQ/D");
   newTree->Branch("tofc",&tofc,"tofc/D");
   newTree->Branch("s1xc",&s1xc,"s1xc/D");
   newTree->Branch("pidAOQ_p",&pidAOQ_p,"pidAOQ_p/D");
   newTree->Branch("FL",&FL,"FL/D");
   newTree->Branch("beta",&beta,"beta/D");

   newTree->Branch("E1",&E1,"E1/D");
   newTree->Branch("E2",&E2,"E2/D");
   newTree->Branch("theta1",&theta1,"theta1/D");
   newTree->Branch("theta2",&theta2,"theta2/D");
   newTree->Branch("phi1",&phi1,"phi1/D");
   newTree->Branch("phi2",&phi2,"phi2/D");
   newTree->Branch("Ex",&Ex,"Ex/D");
   newTree->Branch("kMomt",&kMomt,"kMomt/D");


}

Bool_t Selector_PostAna2::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef Selector_PostAna2_cxx
