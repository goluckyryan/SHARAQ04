//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jul 21 18:26:44 2015 by ROOT version 5.34/10
// from TTree tree/tree
// found on file: 25F_ppcoin_r14_0720_noCorr.root
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
//#include "./cont/TTimingData.h"
//#include "./cont/TTrack.h"
//#include "./sh04/TP2PKinematicsData.h"

// Fixed size dimensions of array or collections stored in the TTree if any.

class Selector_PostAna : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   
   TBenchmark clock;
   Bool_t shown;
   
   Int_t count;

   Double_t mp;
   
   Double_t Sp0;
   Double_t mass, massA, massZ;
   Double_t Brho0;
   
   Double_t beamZ;

   //==========================  STore in new ROOT file
   TFile * saveFile;
   TTree * newTree;
   
   TString saveFileName;
   Int_t totnumEntry;
   
   Int_t eventID;
   //-----------runNumber
   Int_t runNum;
   Int_t coinRegNum;
   //-----------S0img
   Double_t s0x, s0y, s0a, s0b;
   //---------- DCS0D
   Double_t s0dx, s0dy;
   //----------pppac
   Double_t ppacX;
   //-----------get tof and charge upstream
   Double_t tofF3FH9, qFH9, tFH9;
   Double_t qF3, tF3;
   Double_t tofTplaL, qTplaL, tTplaL;
   Double_t tofTplaR, qTplaR, tTplaR;
   Double_t tofS0S0D, qS0D, tS0D;
   Double_t tS0;
   Double_t tofS0DS1, qS1, tS1; 
   Int_t nyokiID;
   //-----------SMWDC X Y
   Double_t x1, y1, a1, b1; // for smwdc-L
   Double_t x2, y2, a2, b2; // for smwdc-R
   Double_t s1x, s1y, s1a, s1b; // for smwdc-S1
   //-----------vertex
   Double_t vertexZ;
   Double_t vertexX;
   Double_t vertexY;
   //-----------pid_ds
   Double_t pidZ, pidAOQ;
   Double_t tofc, s1xc;
   Double_t pidAOQ_p;
   //-----------Phsyics
   Double_t E1, E2;
   Double_t theta1, theta2;
   Double_t phi1, phi2;
   Double_t Ex;// Sp2 - 13.26;
   Double_t kMomt; // redisual momentum
   Double_t dkMomt; // redisual momentum

   //============================================= Declaration of leaf types
   art::TEventHeader *eventheader;
   art::TCoinRegData *coinReg;
   //art::TGateArray *gate;
   //TClonesArray    *plaV1190_F3;
   //TClonesArray    *plaV1190_FH9;
   //TClonesArray    *tof_US;
   TClonesArray    *ppac;
   TClonesArray    *plaV775;
   //TClonesArray    *tof_DS;
   TClonesArray    *S0img;
   TClonesArray    *dcs0d;
   TClonesArray    *smwdc_L;
   TClonesArray    *smwdc_R;
   //TClonesArray    *nyoki;
   //TClonesArray    *nyoki_c;
   //TClonesArray    *nyoki_z;
   TClonesArray    *nyoki_t;
   //TClonesArray    *tof_s1;
   TClonesArray    *smwdc_S1;
   //art::sh04::TParticleIdentifier *pid_s1;
   //art::TTimingData *tof_c;
   //art::TTrack     *s1_c;
   TClonesArray    *vertex;
   //TClonesArray    *tofL;
   //TClonesArray    *tofR;
   //TClonesArray    *tofS0D;
   //art::sh04::TP2PKinematicsData *p2p;
   //art::sh04::TP2PKinematicsData *p2p_Lab;

   // List of branches
   TBranch        *b_eventheader;   //!
   TBranch        *b_coinReg;   //!
   TBranch        *b_gate;   //!
   //TBranch        *b_plaV1190_F3;   //!
   //TBranch        *b_plaV1190_FH9;   //!
   //TBranch        *b_tof_US;   //!
   TBranch        *b_ppac;   //!
   TBranch        *b_plaV775;   //!
   //TBranch        *b_tof_DS;   //!
   TBranch        *b_S0img;   //!
   TBranch        *b_dcs0d;   //!
   TBranch        *b_smwdc_L;   //!
   TBranch        *b_smwdc_R;   //!
   //TBranch        *b_nyoki;   //!
   //TBranch        *b_nyoki_c;   //!
   //TBranch        *b_nyoki_z;   //!
   TBranch        *b_nyoki_t;   //!
   //TBranch        *b_tof_s1;   //!
   TBranch        *b_smwdc_S1;   //!
   //TBranch        *b_pid_s1;   //!
   //TBranch        *b_tof_c;   //!
   //TBranch        *b_s1_c;   //!
   TBranch        *b_vertex;   //!
   //TBranch        *b_tofL;   //!
   //TBranch        *b_tofR;   //!
   //TBranch        *b_tofS0D;   //!
   //TBranch        *b_p2p;   //!
   //TBranch        *b_p2p_Lab;   //!

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

//########################################################################################################

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

   count = 0;
   
   mp = 938.272;

   //====================================== Set object pointer
   eventheader = 0;
   coinReg = 0;
   //gate = 0;
   //plaV1190_F3 = 0;
   //plaV1190_FH9 = 0;
   //tof_US = 0;
   ppac = 0;
   plaV775 = 0;
   //tof_DS = 0;
   S0img = 0;
   dcs0d = 0;
   smwdc_L = 0;
   smwdc_R = 0;
   //nyoki = 0;
   //nyoki_c = 0;
   //nyoki_z = 0;
   nyoki_t = 0;
   //tof_s1 = 0;
   smwdc_S1 = 0;
   //pid_s1 = 0;
   //tof_c = 0;
   //s1_c = 0;
   vertex = 0;
   //tofL = 0;
   //tofR = 0;
   //tofS0D = 0;
   //p2p = 0;
   //p2p_Lab = 0;
   
   
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   //fChain->SetBranchAddress("eventheader0", &eventheader, &b_eventheader);
   fChain->SetBranchAddress("eventheader", &eventheader, &b_eventheader);
   fChain->SetBranchAddress("coinReg", &coinReg, &b_coinReg);
   //fChain->SetBranchAddress("gate", &gate, &b_gate);
   //fChain->SetBranchAddress("plaV1190_F3", &plaV1190_F3, &b_plaV1190_F3);
   //fChain->SetBranchAddress("plaV1190_FH9", &plaV1190_FH9, &b_plaV1190_FH9);
   //fChain->SetBranchAddress("tof_US", &tof_US, &b_tof_US);
   //fChain->SetBranchAddress("ppac", &ppac, &b_ppac);
   fChain->SetBranchAddress("plaV775", &plaV775, &b_plaV775);
   //fChain->SetBranchAddress("tof_DS", &tof_DS, &b_tof_DS);
   fChain->SetBranchAddress("S0img", &S0img, &b_S0img);
   fChain->SetBranchAddress("dcs0d", &dcs0d, &b_dcs0d);
   fChain->SetBranchAddress("smwdc_L", &smwdc_L, &b_smwdc_L);
   fChain->SetBranchAddress("smwdc_R", &smwdc_R, &b_smwdc_R);
   //fChain->SetBranchAddress("nyoki", &nyoki, &b_nyoki);
   //fChain->SetBranchAddress("nyoki_c", &nyoki_c, &b_nyoki_c);
   //fChain->SetBranchAddress("nyoki_z", &nyoki_z, &b_nyoki_z);
   fChain->SetBranchAddress("nyoki_t", &nyoki_t, &b_nyoki_t);
   //fChain->SetBranchAddress("tof_s1", &tof_s1, &b_tof_s1);
   fChain->SetBranchAddress("smwdc_S1", &smwdc_S1, &b_smwdc_S1);
   //fChain->SetBranchAddress("pid_s1", &pid_s1, &b_pid_s1);
   //fChain->SetBranchAddress("tof_c", &tof_c, &b_tof_c);
   //fChain->SetBranchAddress("s1_c", &s1_c, &b_s1_c);
   fChain->SetBranchAddress("vertex", &vertex, &b_vertex);
   //fChain->SetBranchAddress("tofL", &tofL, &b_tofL);
   //fChain->SetBranchAddress("tofR", &tofR, &b_tofR);
   //fChain->SetBranchAddress("tofS0D", &tofS0D, &b_tofS0D);
   //fChain->SetBranchAddress("p2p", &p2p, &b_p2p);
   //fChain->SetBranchAddress("p2p_Lab", &p2p_Lab, &b_p2p_Lab);
   
   if( !b_ppac ) printf(" not ppac \n");
   
   //================================Store in New ROOT file
   saveFileName = fChain->GetDirectory()->GetName();
   saveFileName = "X2_"+saveFileName;
   
   printf("Converting %s ------> %s , total Entry : %d \n", fChain->GetDirectory()->GetName(), saveFileName.Data(), totnumEntry);
   
   saveFile = new TFile( saveFileName,"recreate");
   newTree =  new TTree("tree","tree");
   
   clock.Reset();
   clock.Start("timer");
   shown = 0;
   
   //________________________________________________ Branch

	newTree->Branch("eventID",&eventID,"eventID/I");   
	newTree->Branch("runNum", &runNum, "runNum/I");
   
	newTree->Branch("coinReg", &coinRegNum, "coinRegNum/I");
   
   newTree->Branch("tF3", &tF3, "tF3/D");
   newTree->Branch("tFH9", &tFH9, "tFH9/D");

   newTree->Branch("s0x", &s0x, "s0x/D");
   newTree->Branch("s0y", &s0y, "s0y/D");
   newTree->Branch("s0a", &s0a, "s0a/D");
   newTree->Branch("s0b", &s0b, "s0b/D");
   
   newTree->Branch("s0dx", &s0dx, "s0dx/D");
   newTree->Branch("s0dy", &s0dy, "s0dy/D");
   
   newTree->Branch("ppacX", &ppacX, "ppacX/D");
   
   newTree->Branch("tofTplaL",&tofTplaL,"tofTplaL/D");
   newTree->Branch("qTplaL",&qTplaL,"qTplaL/D");
   newTree->Branch("tTplaL",&tTplaL,"tTplaL/D");
   
   newTree->Branch("tofTplaR",&tofTplaR,"tofTplaR/D");   
   newTree->Branch("qTplaR",&qTplaR,"qTplaR/D");
   newTree->Branch("tTplaR",&tTplaR,"tTplaR/D");

   newTree->Branch("tS0",&tS0,"tS0/D");

   newTree->Branch("tofS0S0D",&tofS0S0D,"tofS0S0D/D");
   newTree->Branch("qS0D",&qS0D,"qS0D/D");
   newTree->Branch("tS0D",&tS0D,"tS0D/D");

   newTree->Branch("tofS0DS1", &tofS0DS1, "tofS0DS1/D");
   newTree->Branch("qS1",&qS1,"qS1/D");
   newTree->Branch("tS1",&tS1,"tS1/D");
   newTree->Branch("nyokiID",&nyokiID,"nyokiID/I");

   newTree->Branch("x1",&x1,"x1/D");
   newTree->Branch("a1",&a1,"a1/D");
   newTree->Branch("y1",&y1,"y1/D");
   newTree->Branch("b1",&b1,"b1/D");
   
   newTree->Branch("x2",&x2,"x2/D");
   newTree->Branch("a2",&a2,"a2/D");
   newTree->Branch("y2",&y2,"y2/D");
   newTree->Branch("b2",&b2,"b2/D");

   newTree->Branch("s1x",&s1x,"s1x/D");
   newTree->Branch("s1a",&s1a,"s1a/D");
   newTree->Branch("s1y",&s1y,"s1y/D");
   newTree->Branch("s1b",&s1b,"s1b/D");

   newTree->Branch("pidZ",&pidZ,"pidZ/D");
   newTree->Branch("pidAOQ",&pidAOQ,"pidAOQ/D");
   newTree->Branch("tofc",&tofc,"tofc/D");
   newTree->Branch("s1xc",&s1xc,"s1xc/D");
   newTree->Branch("pidAOQ_p",&pidAOQ_p,"pidAOQ_p/D");

   newTree->Branch("vertexZ",&vertexZ,"vertexZ/D");
   newTree->Branch("vertexX",&vertexX,"vertexX/D");
   newTree->Branch("vertexY",&vertexY,"vertexY/D");

   newTree->Branch("E1",&E1,"E1/D");
   newTree->Branch("E2",&E2,"E2/D");
   newTree->Branch("theta1",&theta1,"theta1/D");
   newTree->Branch("theta2",&theta2,"theta2/D");
   newTree->Branch("phi1",&phi1,"phi1/D");
   newTree->Branch("phi2",&phi2,"phi2/D");
   newTree->Branch("Ex",&Ex,"Ex/D");
   newTree->Branch("kMomt",&kMomt,"kMomt/D");
   newTree->Branch("dkMomt",&dkMomt,"dkMomt/D");

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
