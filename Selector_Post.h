//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sun May  3 12:55:32 2015 by ROOT version 5.34/10
// from TTree tree/tree
// found on file: 23F_ppcoin_0502.root
//////////////////////////////////////////////////////////

#ifndef Selector_Post_h
#define Selector_Post_h

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

class Selector_Post : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   
   TBenchmark clock;
   Bool_t shown;
   
   Int_t count;

   //==========================  STore in new ROOT file
   TFile * saveFile;
   TTree * newTree;
   
   TString saveFileName;
   
   Int_t totnumEntry;
   
   Int_t eventID;
	//-----------runNumber
	Int_t runNum;
   //-----------coinReg
   Int_t coinRegNum; // 1abc, a = all other, b = beam, c = ppcoin, if 1001, only beam trigger, if 1011, both beam
	//-----------gate
	Int_t s0imgGate;
   Int_t pidusGate;
	//-----------S0img
   Double_t s0x, s0y, s0a, s0b;
   Double_t s0dx, s0dy;
	//-----------get tof and charge upstream
	Double_t tofFH9, qFH9, tFH9;
	Double_t qF3, tF3;
   //Double_t tTplaLB,  tTplaLF;
   //Double_t tTplaRB,  tTplaRF;
	Double_t tofTplaL, qTplaL, tTplaL;
	Double_t tofTplaR, qTplaR, tTplaR;
   //-----------tof and Q from S0DPL v775
   Double_t tof_S0D, qS0D, tS0D;
   //Double_t qS0DU, qS0DD, tS0DU, tS0DD;
   Double_t tTgt;
	//-----------tof from S0DPL to nyoki
	Double_t tofS1, qS1[14], tS1[14];
	Double_t tofTgtS1, tofS0DS1;
   Int_t nyokiM;
	//Double_t qS1c[14];
	//-----------SMWDC X Y
   Double_t x1, y1, a1, b1; // for smwdc-L
   Double_t x2, y2, a2, b2; // for smwdc-R
   Double_t s1x, s1y, s1a, s1b; // for smwdc-S1
   Double_t s1xr, s1ar; // for smwdc-S1 -- rotated
	//-----------pid_ds
	Double_t pidZ, pidAOQ;
   Double_t brho, FL, beta;
   Int_t nyokiID;
	//-----------pid_ds_corr
	Double_t pidZc, pidAOQc;
   Double_t brhoc, FLc, betac;
   //-----------vertex
	Double_t vertexZ;
   //-----------correction
   Double_t s1xc, tofc;
   //-----------Phsyics
	Double_t E1, E2;
	Double_t theta1, theta2;
	Double_t phi1, phi2;
	Double_t Ex;// Sp2 - 13.26;
	Double_t ExS;// Sp - 13.26;
	Double_t kMomt; // redisual momentum
   Double_t thetaR, phiR;
   //carbon
	Double_t theta1c, theta2c;
	Double_t phi1c, phi2c;
	Double_t Exc, kMomtc;

   //============================================= Declaration of leaf types


   // Declaration of leaf types
   art::TEventHeader *eventheader;
   art::TCoinRegData *coinReg;
   art::TGateArray *gate;
   TClonesArray    *plaV1190_F3;
   TClonesArray    *plaV1190_FH9;
   TClonesArray    *tof_US;
   TClonesArray    *plaV775;
   TClonesArray    *tof_DS;
   TClonesArray    *S0img;
   TClonesArray    *dcs0d;
   TClonesArray    *smwdc_L;
   TClonesArray    *smwdc_R;
   TClonesArray    *nyoki;
   TClonesArray    *tof_s1;
   TClonesArray    *smwdc_S1;
   TClonesArray    *nyoki_c;
   TClonesArray    *nyoki_z;
   TClonesArray    *nyoki_t;
   art::sh04::TParticleIdentifier *pid_s1;
   art::TTimingData *tof_c;
   art::TTrack     *s1_c;
   TClonesArray    *beamZ;
   TClonesArray    *vertex;
   TClonesArray    *tofL;
   TClonesArray    *tofR;
   TClonesArray    *tofS0D;
   art::sh04::TP2PKinematicsData *p2p;
   art::sh04::TP2PKinematicsData *p2p_Lab;
   art::sh04::TP2PKinematicsData *p2p_c;
   art::sh04::TP2PKinematicsData *p2p_c_Lab;

   //==================================================== List of branches
   TBranch        *b_eventheader;   //!
   TBranch        *b_coinReg;   //!
   TBranch        *b_gate;   //!
   TBranch        *b_plaV1190_F3;   //!
   TBranch        *b_plaV1190_FH9;   //!
   TBranch        *b_tof_US;   //!
   TBranch        *b_plaV775;   //!
   TBranch        *b_tof_DS;   //!
   TBranch        *b_S0img;   //!
   TBranch        *b_dcs0d;   //!
   TBranch        *b_smwdc_L;   //!
   TBranch        *b_smwdc_R;   //!
   TBranch        *b_nyoki;   //!
   TBranch        *b_tof_s1;   //!
   TBranch        *b_smwdc_S1;   //!
   TBranch        *b_nyoki_c;   //!
   TBranch        *b_nyoki_z;   //!
   TBranch        *b_nyoki_t;   //!
   TBranch        *b_pid_s1;   //!
   TBranch        *b_tof_c;   //!
   TBranch        *b_s1_c;   //!
   TBranch        *b_beamZ;   //!
   TBranch        *b_vertex;   //!
   TBranch        *b_tofL;   //!
   TBranch        *b_tofR;   //!
   TBranch        *b_tofS0D;   //!
   TBranch        *b_p2p;   //!
   TBranch        *b_p2p_Lab;   //!
   TBranch        *b_p2p_c;   //!
   TBranch        *b_p2p_c_Lab;   //!

   Selector_Post(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~Selector_Post() { }
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

   ClassDef(Selector_Post,0);
};

#endif

#ifdef Selector_Post_cxx
void Selector_Post::Init(TTree *tree)
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
   //======================================= Set object pointer
   eventheader = 0;
   coinReg = 0;
   gate = 0;
   plaV1190_F3 = 0;
   plaV1190_FH9 = 0;
   tof_US = 0;
   plaV775 = 0;
   tof_DS = 0;
   S0img = 0;
   dcs0d = 0;
   smwdc_L = 0;
   smwdc_R = 0;
   nyoki = 0;
   tof_s1 = 0;
   smwdc_S1 = 0;
   nyoki_c = 0;
   nyoki_z = 0;
   nyoki_t = 0;
   pid_s1 = 0;
   tof_c = 0;
   s1_c = 0;
   beamZ = 0;
   vertex = 0;
   tofL = 0;
   tofR = 0;
   tofS0D = 0;
   p2p = 0;
   p2p_Lab = 0;
   p2p_c = 0;
   p2p_c_Lab = 0;
   
   //===================================== Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   //fChain->SetBranchAddress("eventheader0", &eventheader, &b_eventheader);
   fChain->SetBranchAddress("eventheader", &eventheader, &b_eventheader);
   //fChain->SetBranchAddress("coinReg", &coinReg, &b_coinReg);
   //fChain->SetBranchAddress("gate", &gate, &b_gate);
   //fChain->SetBranchAddress("plaV1190_F3", &plaV1190_F3, &b_plaV1190_F3);
   //fChain->SetBranchAddress("plaV1190_FH9", &plaV1190_FH9, &b_plaV1190_FH9);
   //fChain->SetBranchAddress("tof_US", &tof_US, &b_tof_US);
   //fChain->SetBranchAddress("plaV775", &plaV775, &b_plaV775);
   //fChain->SetBranchAddress("tof_DS", &tof_DS, &b_tof_DS);
   fChain->SetBranchAddress("S0img", &S0img, &b_S0img);
   fChain->SetBranchAddress("dcs0d", &dcs0d, &b_dcs0d);
   //fChain->SetBranchAddress("smwdc_L", &smwdc_L, &b_smwdc_L);
   //fChain->SetBranchAddress("smwdc_R", &smwdc_R, &b_smwdc_R);
   //fChain->SetBranchAddress("nyoki", &nyoki, &b_nyoki);
   fChain->SetBranchAddress("tof_s1", &tof_s1, &b_tof_s1);
   fChain->SetBranchAddress("smwdc_S1", &smwdc_S1, &b_smwdc_S1);
   //fChain->SetBranchAddress("nyoki_c", &nyoki_c, &b_nyoki_c);
   fChain->SetBranchAddress("nyoki_z", &nyoki_z, &b_nyoki_z);
   fChain->SetBranchAddress("nyoki_t", &nyoki_t, &b_nyoki_t);
   fChain->SetBranchAddress("pid_s1", &pid_s1, &b_pid_s1);
   fChain->SetBranchAddress("tof_c", &tof_c, &b_tof_c);
   fChain->SetBranchAddress("s1_c", &s1_c, &b_s1_c);
   //fChain->SetBranchAddress("beamZ", &beamZ, &b_beamZ);
   fChain->SetBranchAddress("vertex", &vertex, &b_vertex);
   fChain->SetBranchAddress("tofL", &tofL, &b_tofL);
   fChain->SetBranchAddress("tofR", &tofR, &b_tofR);
   fChain->SetBranchAddress("tofS0D", &tofS0D, &b_tofS0D);
   fChain->SetBranchAddress("p2p", &p2p, &b_p2p);
   //fChain->SetBranchAddress("p2p_Lab", &p2p_Lab, &b_p2p_Lab);
   //fChain->SetBranchAddress("p2p_c", &p2p_c, &b_p2p_c);
   //fChain->SetBranchAddress("p2p_c_Lab", &p2p_c_Lab, &b_p2p_c_Lab);
   
   if (b_coinReg       ) printf("%10s....on\n", "coinReg");
   if (b_gate          ) printf("%10s....on\n", "gate");
   if (b_plaV1190_FH9  ) printf("%10s....on\n", "plaV1190_FH9");
   if (b_tof_US        ) printf("%10s....on\n", "tof_US");
   if (b_plaV775       ) printf("%10s....on\n", "plaV775");
   if (b_tof_DS        ) printf("%10s....on\n", "tof_DS");
   if (b_S0img         ) printf("%10s....on\n", "S0img");
   if (b_dcs0d         ) printf("%10s....on\n", "DCS0D");
   if (b_smwdc_L       ) printf("%10s....on\n", "smwdc-L");
   if (b_smwdc_R       ) printf("%10s....on\n", "smwdc_R");
   if (b_nyoki         ) printf("%10s....on\n", "nyoki");
   if (b_tof_s1        ) printf("%10s....on\n", "tof_s1");
   if (b_smwdc_S1      ) printf("%10s....on\n", "smwdc_S1");
   if (b_nyoki_c       ) printf("%10s....on\n", "nyoki_c");
   if (b_nyoki_z       ) printf("%10s....on\n", "nyoki_z");
   if (b_nyoki_t       ) printf("%10s....on\n", "nyoki_t");
   if (b_pid_s1        ) printf("%10s....on\n", "pid_s1");
   if (b_tof_c         ) printf("%10s....on\n", "tof_c");
   if (b_s1_c          ) printf("%10s....on\n", "s1_c");
   if (b_beamZ         ) printf("%10s....on\n", "beamZ");
   if (b_vertex        ) printf("%10s....on\n", "vertex");
   if (b_tofL          ) printf("%10s....on\n", "tofL");
   if (b_tofR          ) printf("%10s....on\n", "tofR");
   if (b_tofS0D        ) printf("%10s....on\n", "tofS0D");
   if (b_p2p           ) printf("%10s....on\n", "p2p");
   if (b_p2p_Lab       ) printf("%10s....on\n", "p2p_Lab");
   if (b_p2p_c         ) printf("%10s....on\n", "p2p_c");
   if (b_p2p_c_Lab     ) printf("%10s....on\n", "p2p_c_Lab");
   
   
   //================================Store in New ROOT file
   saveFileName = fChain->GetDirectory()->GetName();
   saveFileName = "P_"+saveFileName;
   
   printf("Converting %s ------> %s , total Entry : %d \n", fChain->GetDirectory()->GetName(), saveFileName.Data(), totnumEntry);
   
   saveFile = new TFile( saveFileName,"recreate");
   newTree =  new TTree("tree","tree");
   
   clock.Reset();
   clock.Start("timer");
   shown = 0;
   
   eventID = -1;
	runNum = -1;
   coinRegNum= 1000;
	s0imgGate = -1;
   pidusGate = -10;
	s0x = TMath::QuietNaN(); s0y = TMath::QuietNaN(); s0a = TMath::QuietNaN(); s0b = TMath::QuietNaN();
	s0dx = TMath::QuietNaN(); s0dy = TMath::QuietNaN(); 
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
      tS1[p] = TMath::QuietNaN();
      qS1[p] = TMath::QuietNaN();
   }
   nyokiM = 0;
   
   tofS1 = TMath::QuietNaN();
   tofS0DS1 = TMath::QuietNaN();
	
   x1 = TMath::QuietNaN(); y1 = TMath::QuietNaN(); a1 = TMath::QuietNaN(); b1 = TMath::QuietNaN(); 
	x2 = TMath::QuietNaN(); y2 = TMath::QuietNaN(); a2 = TMath::QuietNaN(); b2 = TMath::QuietNaN(); 
   s1x = TMath::QuietNaN(); s1y = TMath::QuietNaN(); s1a = TMath::QuietNaN(); s1b = TMath::QuietNaN();
   s1xr = TMath::QuietNaN(); s1ar = TMath::QuietNaN();
   
   pidZ = TMath::QuietNaN();
   nyokiID = -1;
   pidAOQ = TMath::QuietNaN();
   brho = TMath::QuietNaN();
   FL = TMath::QuietNaN();
   beta = TMath::QuietNaN();
   
   pidZc = TMath::QuietNaN();
   pidAOQc = TMath::QuietNaN();
   brhoc = TMath::QuietNaN();
   FLc = TMath::QuietNaN();
   betac = TMath::QuietNaN();
   
	vertexZ = TMath::QuietNaN();
	E1 = TMath::QuietNaN();
	E2 = TMath::QuietNaN();
	theta1 = TMath::QuietNaN();
	theta2 = TMath::QuietNaN();
	phi1 = TMath::QuietNaN(); 
	phi2 = TMath::QuietNaN();
	Ex = TMath::QuietNaN(); // Sp2 - 13.26;
	ExS = TMath::QuietNaN(); // Sp - 13.26;
	kMomt = TMath::QuietNaN(); // redisual momentum
   
   s1xc = TMath::QuietNaN();
   tofc = TMath::QuietNaN();
   
   if( b_p2p_c ){
      theta1c = TMath::QuietNaN();
      theta2c = TMath::QuietNaN();
      phi1c = TMath::QuietNaN(); 
      phi2c = TMath::QuietNaN();
      Exc = TMath::QuietNaN();
      kMomtc = TMath::QuietNaN();
      thetaR = TMath::QuietNaN();
      phiR = TMath::QuietNaN();
      
   }
   
   //________________________________________________ Branch

	newTree->Branch("eventID",&eventID,"eventID/I");   
	newTree->Branch("runNum", &runNum, "runNum/I");
	if( b_coinReg) {
      newTree->Branch("coinReg", &coinRegNum, "coinRegNum/I");
   }
   if( b_gate){
      newTree->Branch("s0imgGate",&s0imgGate,"s0imgGate/I");
      newTree->Branch("pidusGate", &pidusGate, "pidusGate/I");
   }
   if( b_plaV1190_FH9){
      newTree->Branch("tofFH9",&tofFH9,"tofFH9/D");
      newTree->Branch("qFH9",&qFH9,"qFH9/D");
      newTree->Branch("tFH9",&tFH9,"tFH9/D");
   }
   
   if( b_plaV1190_F3){
      newTree->Branch("qF3",&qF3,"qF3/D");
      newTree->Branch("tF3",&tF3,"tF3/D");
   }
   
   newTree->Branch("tofTplaL",&tofTplaL,"tofTplaL/D");
   newTree->Branch("tofTplaR",&tofTplaR,"tofTplaR/D");
   newTree->Branch("tofS0D",&tof_S0D,"tof_S0D/D");
   
   if( b_plaV775){
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
   }
   
   if( b_S0img){
      newTree->Branch("s0x", &s0x, "s0x/D");
      newTree->Branch("s0y", &s0y, "s0y/D");
      newTree->Branch("s0a", &s0a, "s0a/D");
      newTree->Branch("s0b", &s0b, "s0b/D");
   }
   
   if( b_dcs0d){
      newTree->Branch("s0dx", &s0dx, "s0dx/D");
      newTree->Branch("s0dy", &s0dy, "s0dy/D");
   }
   
   if( b_tof_s1){
      newTree->Branch("tofS1", &tofS1, "tofS1/D");
   }
   
   if( b_nyoki_z){
      newTree->Branch("qS1", qS1, "qS1[14]/D");
      newTree->Branch("tS1", tS1, "tS1[14]/D");
      newTree->Branch("nyokiM", &nyokiM, "nyokiM/I");
   }
   
   if( b_smwdc_L){
      newTree->Branch("x1",&x1,"x1/D");
      newTree->Branch("a1",&a1,"a1/D");
      newTree->Branch("y1",&y1,"y1/D");
      newTree->Branch("b1",&b1,"b1/D");
   }
   
   if( b_smwdc_R){
      newTree->Branch("x2",&x2,"x2/D");
      newTree->Branch("a2",&a2,"a2/D");
      newTree->Branch("y2",&y2,"y2/D");
      newTree->Branch("b2",&b2,"b2/D");
   }
   
   if( b_smwdc_S1){
      newTree->Branch("s1x",&s1x,"s1x/D");
      newTree->Branch("s1a",&s1a,"s1a/D");
      newTree->Branch("s1y",&s1y,"s1y/D");
      newTree->Branch("s1b",&s1b,"s1b/D");
      newTree->Branch("s1xr",&s1xr,"s1xr/D");
      newTree->Branch("s1ar",&s1ar,"s1ar/D");
   }
   
   if( b_plaV775 && b_nyoki_zt) {
      newTree->Branch("tofTgtS1",&tofTgtS1,"tofTgtS1/D");
   }

   if( b_nyoki_t){
      //newTree->Branch("pidZc",&pidZc,"pidZc/D");
      newTree->Branch("nyokiID",&nyokiID,"nyokiID/I");
   }
   
   if( b_pid_s1){
      newTree->Branch("pidZ",&pidZ,"pidZ/D");
      newTree->Branch("pidAOQ",&pidAOQ,"pidAOQ/D");
      newTree->Branch("brho",&brho,"brho/D");
      newTree->Branch("FL",&FL,"FL/D");
      newTree->Branch("beta",&beta,"beta/D");
	
      newTree->Branch("pidAOQc",&pidAOQc,"pidAOQc/D");
      newTree->Branch("brhoc",&brhoc,"brhoc/D");
      newTree->Branch("FLc",&FLc,"FLc/D");
      newTree->Branch("betac",&betac,"betac/D");
   }
   
   if( b_vertex){
      newTree->Branch("vertexZ",&vertexZ,"vertexZ/D");
   }
   
   if( b_p2p){
      newTree->Branch("E1",&E1,"E1/D");
      newTree->Branch("E2",&E2,"E2/D");
      newTree->Branch("theta1",&theta1,"theta1/D");
      newTree->Branch("theta2",&theta2,"theta2/D");
      newTree->Branch("phi1",&phi1,"phi1/D");
      newTree->Branch("phi2",&phi2,"phi2/D");
      newTree->Branch("Ex",&Ex,"Ex/D");
      newTree->Branch("ExS",&ExS,"ExS/D");
      newTree->Branch("kMomt",&kMomt,"kMomt/D");
      newTree->Branch("thetaR",&thetaR,"thetaR/D");
      newTree->Branch("phiR",&phiR,"phiR/D");
   }
   
   if( b_s1_c ){
      newTree->Branch("s1xc",&s1xc,"s1xc/D");
   }
   
   if( b_tof_c){
      newTree->Branch("tofc",&tofc,"tofc/D");
   }

   
   if( b_p2p_c){
      printf("......................\n");
      newTree->Branch("theta1c",&theta1c,"theta1c/D");
      newTree->Branch("theta2c",&theta2c,"theta2c/D");
      newTree->Branch("phi1c",&phi1c,"phi1c/D");
      newTree->Branch("phi2c",&phi2c,"phi2c/D");
      newTree->Branch("Exc",&Exc,"Exc/D");
      newTree->Branch("kMomtc",&kMomtc,"kMomtc/D");
   }
   
}

Bool_t Selector_Post::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef Selector_Post_cxx
