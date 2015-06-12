//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Jun  5 20:20:46 2015 by ROOT version 5.34/10
// from TTree tree/tree
// found on file: pp_0605.root
//////////////////////////////////////////////////////////

#ifndef Selector_offsetPP_h
#define Selector_offsetPP_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>

// Header file for the classes stored in the TTree if any.
//#include "./TEventHeader.h"
//#include "./cont/TCoinRegData.h"
//#include <TClonesArray.h>
//#include "./sh04/TP2PKinematicsData.h"

// Fixed size dimensions of array or collections stored in the TTree if any.

class Selector_offsetPP : public TSelector {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   
   TBenchmark clock;
   Bool_t shown;
   Int_t count;

   //====================
   TFile * saveFile;
   TTree * newTree;
   
   TString saveFileName;
   
   Int_t totnumEntry;
   
   Double_t Exm5[11];
   Double_t Exm4[11];
   Double_t Exm3[11];
   Double_t Exm2[11];
   Double_t Exm1[11];
   Double_t Ex00[11];
   Double_t Exp1[11];
   Double_t Exp2[11];
   Double_t Exp3[11];
   Double_t Exp4[11];
   Double_t Exp5[11];
   
   
   Double_t theta1, theta2, Dtheta;
   Double_t phi1, phi2, Dphi;
   Double_t vertexZ;


   // Declaration of leaf types
   art::TEventHeader *eventheader;
   art::TCoinRegData *coinReg;
   TClonesArray    *plaV1190_F3;
   TClonesArray    *plaV1190_FH9;
   TClonesArray    *tof_US;
   TClonesArray    *plaV775;
   TClonesArray    *tof_DS;
   TClonesArray    *smwdc_L;
   TClonesArray    *smwdc_R;
   TClonesArray    *beamZ;
   //TClonesArray    *tofL_p5;
   //TClonesArray    *tofR_p5;
   //TClonesArray    *tofS0D_p5;
   //TClonesArray    *tofL_p4;
   //TClonesArray    *tofR_p4;
   //TClonesArray    *tofS0D_p4;
   //TClonesArray    *tofL_p3;
   //TClonesArray    *tofR_p3;
   //TClonesArray    *tofS0D_p3;
   //TClonesArray    *tofL_p2;
   //TClonesArray    *tofR_p2;
   //TClonesArray    *tofS0D_p2;
   //TClonesArray    *tofL_p1;
   //TClonesArray    *tofR_p1;
   //TClonesArray    *tofS0D_p1;
   //TClonesArray    *tofL;
   //TClonesArray    *tofR;
   //TClonesArray    *tofS0D;
   //TClonesArray    *tofL_m1;
   //TClonesArray    *tofR_m1;
   //TClonesArray    *tofS0D_m1;
   //TClonesArray    *tofL_m2;
   //TClonesArray    *tofR_m2;
   //TClonesArray    *tofS0D_m2;
   //TClonesArray    *tofL_m3;
   //TClonesArray    *tofR_m3;
   //TClonesArray    *tofS0D_m3;
   //TClonesArray    *tofL_m4;
   //TClonesArray    *tofR_m4;
   //TClonesArray    *tofS0D_m4;
   //TClonesArray    *tofL_m5;
   //TClonesArray    *tofR_m5;
   //TClonesArray    *tofS0D_m5;
   art::sh04::TP2PKinematicsData *p2p_p500_p500;
   art::sh04::TP2PKinematicsData *p2p_p500_p400;
   art::sh04::TP2PKinematicsData *p2p_p500_p300;
   art::sh04::TP2PKinematicsData *p2p_p500_p200;
   art::sh04::TP2PKinematicsData *p2p_p500_p100;
   art::sh04::TP2PKinematicsData *p2p_p500_0000;
   art::sh04::TP2PKinematicsData *p2p_p500_m100;
   art::sh04::TP2PKinematicsData *p2p_p500_m200;
   art::sh04::TP2PKinematicsData *p2p_p500_m300;
   art::sh04::TP2PKinematicsData *p2p_p500_m400;
   art::sh04::TP2PKinematicsData *p2p_p500_m500;
   art::sh04::TP2PKinematicsData *p2p_p400_p500;
   art::sh04::TP2PKinematicsData *p2p_p400_p400;
   art::sh04::TP2PKinematicsData *p2p_p400_p300;
   art::sh04::TP2PKinematicsData *p2p_p400_p200;
   art::sh04::TP2PKinematicsData *p2p_p400_p100;
   art::sh04::TP2PKinematicsData *p2p_p400_0000;
   art::sh04::TP2PKinematicsData *p2p_p400_m100;
   art::sh04::TP2PKinematicsData *p2p_p400_m200;
   art::sh04::TP2PKinematicsData *p2p_p400_m300;
   art::sh04::TP2PKinematicsData *p2p_p400_m400;
   art::sh04::TP2PKinematicsData *p2p_p400_m500;
   art::sh04::TP2PKinematicsData *p2p_p300_p500;
   art::sh04::TP2PKinematicsData *p2p_p300_p400;
   art::sh04::TP2PKinematicsData *p2p_p300_p300;
   art::sh04::TP2PKinematicsData *p2p_p300_p200;
   art::sh04::TP2PKinematicsData *p2p_p300_p100;
   art::sh04::TP2PKinematicsData *p2p_p300_0000;
   art::sh04::TP2PKinematicsData *p2p_p300_m100;
   art::sh04::TP2PKinematicsData *p2p_p300_m200;
   art::sh04::TP2PKinematicsData *p2p_p300_m300;
   art::sh04::TP2PKinematicsData *p2p_p300_m400;
   art::sh04::TP2PKinematicsData *p2p_p300_m500;
   art::sh04::TP2PKinematicsData *p2p_p200_p500;
   art::sh04::TP2PKinematicsData *p2p_p200_p400;
   art::sh04::TP2PKinematicsData *p2p_p200_p300;
   art::sh04::TP2PKinematicsData *p2p_p200_p200;
   art::sh04::TP2PKinematicsData *p2p_p200_p100;
   art::sh04::TP2PKinematicsData *p2p_p200_0000;
   art::sh04::TP2PKinematicsData *p2p_p200_m100;
   art::sh04::TP2PKinematicsData *p2p_p200_m200;
   art::sh04::TP2PKinematicsData *p2p_p200_m300;
   art::sh04::TP2PKinematicsData *p2p_p200_m400;
   art::sh04::TP2PKinematicsData *p2p_p200_m500;
   art::sh04::TP2PKinematicsData *p2p_p100_p500;
   art::sh04::TP2PKinematicsData *p2p_p100_p400;
   art::sh04::TP2PKinematicsData *p2p_p100_p300;
   art::sh04::TP2PKinematicsData *p2p_p100_p200;
   art::sh04::TP2PKinematicsData *p2p_p100_p100;
   art::sh04::TP2PKinematicsData *p2p_p100_0000;
   art::sh04::TP2PKinematicsData *p2p_p100_m100;
   art::sh04::TP2PKinematicsData *p2p_p100_m200;
   art::sh04::TP2PKinematicsData *p2p_p100_m300;
   art::sh04::TP2PKinematicsData *p2p_p100_m400;
   art::sh04::TP2PKinematicsData *p2p_p100_m500;
   art::sh04::TP2PKinematicsData *p2p_0000_p500;
   art::sh04::TP2PKinematicsData *p2p_0000_p400;
   art::sh04::TP2PKinematicsData *p2p_0000_p300;
   art::sh04::TP2PKinematicsData *p2p_0000_p200;
   art::sh04::TP2PKinematicsData *p2p_0000_p100;
   art::sh04::TP2PKinematicsData *p2p_0000_0000;
   art::sh04::TP2PKinematicsData *p2p_0000_m100;
   art::sh04::TP2PKinematicsData *p2p_0000_m200;
   art::sh04::TP2PKinematicsData *p2p_0000_m300;
   art::sh04::TP2PKinematicsData *p2p_0000_m400;
   art::sh04::TP2PKinematicsData *p2p_0000_m500;
   art::sh04::TP2PKinematicsData *p2p_m100_p500;
   art::sh04::TP2PKinematicsData *p2p_m100_p400;
   art::sh04::TP2PKinematicsData *p2p_m100_p300;
   art::sh04::TP2PKinematicsData *p2p_m100_p200;
   art::sh04::TP2PKinematicsData *p2p_m100_p100;
   art::sh04::TP2PKinematicsData *p2p_m100_0000;
   art::sh04::TP2PKinematicsData *p2p_m100_m100;
   art::sh04::TP2PKinematicsData *p2p_m100_m200;
   art::sh04::TP2PKinematicsData *p2p_m100_m300;
   art::sh04::TP2PKinematicsData *p2p_m100_m400;
   art::sh04::TP2PKinematicsData *p2p_m100_m500;
   art::sh04::TP2PKinematicsData *p2p_m200_p500;
   art::sh04::TP2PKinematicsData *p2p_m200_p400;
   art::sh04::TP2PKinematicsData *p2p_m200_p300;
   art::sh04::TP2PKinematicsData *p2p_m200_p200;
   art::sh04::TP2PKinematicsData *p2p_m200_p100;
   art::sh04::TP2PKinematicsData *p2p_m200_0000;
   art::sh04::TP2PKinematicsData *p2p_m200_m100;
   art::sh04::TP2PKinematicsData *p2p_m200_m200;
   art::sh04::TP2PKinematicsData *p2p_m200_m300;
   art::sh04::TP2PKinematicsData *p2p_m200_m400;
   art::sh04::TP2PKinematicsData *p2p_m200_m500;
   art::sh04::TP2PKinematicsData *p2p_m300_p500;
   art::sh04::TP2PKinematicsData *p2p_m300_p400;
   art::sh04::TP2PKinematicsData *p2p_m300_p300;
   art::sh04::TP2PKinematicsData *p2p_m300_p200;
   art::sh04::TP2PKinematicsData *p2p_m300_p100;
   art::sh04::TP2PKinematicsData *p2p_m300_0000;
   art::sh04::TP2PKinematicsData *p2p_m300_m100;
   art::sh04::TP2PKinematicsData *p2p_m300_m200;
   art::sh04::TP2PKinematicsData *p2p_m300_m300;
   art::sh04::TP2PKinematicsData *p2p_m300_m400;
   art::sh04::TP2PKinematicsData *p2p_m300_m500;
   art::sh04::TP2PKinematicsData *p2p_m400_p500;
   art::sh04::TP2PKinematicsData *p2p_m400_p400;
   art::sh04::TP2PKinematicsData *p2p_m400_p300;
   art::sh04::TP2PKinematicsData *p2p_m400_p200;
   art::sh04::TP2PKinematicsData *p2p_m400_p100;
   art::sh04::TP2PKinematicsData *p2p_m400_0000;
   art::sh04::TP2PKinematicsData *p2p_m400_m100;
   art::sh04::TP2PKinematicsData *p2p_m400_m200;
   art::sh04::TP2PKinematicsData *p2p_m400_m300;
   art::sh04::TP2PKinematicsData *p2p_m400_m400;
   art::sh04::TP2PKinematicsData *p2p_m400_m500;
   art::sh04::TP2PKinematicsData *p2p_m500_p500;
   art::sh04::TP2PKinematicsData *p2p_m500_p400;
   art::sh04::TP2PKinematicsData *p2p_m500_p300;
   art::sh04::TP2PKinematicsData *p2p_m500_p200;
   art::sh04::TP2PKinematicsData *p2p_m500_p100;
   art::sh04::TP2PKinematicsData *p2p_m500_0000;
   art::sh04::TP2PKinematicsData *p2p_m500_m100;
   art::sh04::TP2PKinematicsData *p2p_m500_m200;
   art::sh04::TP2PKinematicsData *p2p_m500_m300;
   art::sh04::TP2PKinematicsData *p2p_m500_m400;
   art::sh04::TP2PKinematicsData *p2p_m500_m500;

   // List of branches
   TBranch        *b_eventheader;   //!
   TBranch        *b_coinReg;   //!
   TBranch        *b_plaV1190_F3;   //!
   TBranch        *b_plaV1190_FH9;   //!
   TBranch        *b_tof_US;   //!
   TBranch        *b_plaV775;   //!
   TBranch        *b_tof_DS;   //!
   TBranch        *b_smwdc_L;   //!
   TBranch        *b_smwdc_R;   //!
   TBranch        *b_beamZ;   //!
   //TBranch        *b_tofL_p5;   //!
   //TBranch        *b_tofR_p5;   //!
   //TBranch        *b_tofS0D_p5;   //!
   //TBranch        *b_tofL_p4;   //!
   //TBranch        *b_tofR_p4;   //!
   //TBranch        *b_tofS0D_p4;   //!
   //TBranch        *b_tofL_p3;   //!
   //TBranch        *b_tofR_p3;   //!
   //TBranch        *b_tofS0D_p3;   //!
   //TBranch        *b_tofL_p2;   //!
   //TBranch        *b_tofR_p2;   //!
   //TBranch        *b_tofS0D_p2;   //!
   //TBranch        *b_tofL_p1;   //!
   //TBranch        *b_tofR_p1;   //!
   //TBranch        *b_tofS0D_p1;   //!
   //TBranch        *b_tofL;   //!
   //TBranch        *b_tofR;   //!
   //TBranch        *b_tofS0D;   //!
   //TBranch        *b_tofL_m1;   //!
   //TBranch        *b_tofR_m1;   //!
   //TBranch        *b_tofS0D_m1;   //!
   //TBranch        *b_tofL_m2;   //!
   //TBranch        *b_tofR_m2;   //!
   //TBranch        *b_tofS0D_m2;   //!
   //TBranch        *b_tofL_m3;   //!
   //TBranch        *b_tofR_m3;   //!
   //TBranch        *b_tofS0D_m3;   //!
   //TBranch        *b_tofL_m4;   //!
   //TBranch        *b_tofR_m4;   //!
   //TBranch        *b_tofS0D_m4;   //!
   //TBranch        *b_tofL_m5;   //!
   //TBranch        *b_tofR_m5;   //!
   //TBranch        *b_tofS0D_m5;   //!
   TBranch        *b_p2p_p500_p500;   //!
   TBranch        *b_p2p_p500_p400;   //!
   TBranch        *b_p2p_p500_p300;   //!
   TBranch        *b_p2p_p500_p200;   //!
   TBranch        *b_p2p_p500_p100;   //!
   TBranch        *b_p2p_p500_0000;   //!
   TBranch        *b_p2p_p500_m100;   //!
   TBranch        *b_p2p_p500_m200;   //!
   TBranch        *b_p2p_p500_m300;   //!
   TBranch        *b_p2p_p500_m400;   //!
   TBranch        *b_p2p_p500_m500;   //!
   TBranch        *b_p2p_p400_p500;   //!
   TBranch        *b_p2p_p400_p400;   //!
   TBranch        *b_p2p_p400_p300;   //!
   TBranch        *b_p2p_p400_p200;   //!
   TBranch        *b_p2p_p400_p100;   //!
   TBranch        *b_p2p_p400_0000;   //!
   TBranch        *b_p2p_p400_m100;   //!
   TBranch        *b_p2p_p400_m200;   //!
   TBranch        *b_p2p_p400_m300;   //!
   TBranch        *b_p2p_p400_m400;   //!
   TBranch        *b_p2p_p400_m500;   //!
   TBranch        *b_p2p_p300_p500;   //!
   TBranch        *b_p2p_p300_p400;   //!
   TBranch        *b_p2p_p300_p300;   //!
   TBranch        *b_p2p_p300_p200;   //!
   TBranch        *b_p2p_p300_p100;   //!
   TBranch        *b_p2p_p300_0000;   //!
   TBranch        *b_p2p_p300_m100;   //!
   TBranch        *b_p2p_p300_m200;   //!
   TBranch        *b_p2p_p300_m300;   //!
   TBranch        *b_p2p_p300_m400;   //!
   TBranch        *b_p2p_p300_m500;   //!
   TBranch        *b_p2p_p200_p500;   //!
   TBranch        *b_p2p_p200_p400;   //!
   TBranch        *b_p2p_p200_p300;   //!
   TBranch        *b_p2p_p200_p200;   //!
   TBranch        *b_p2p_p200_p100;   //!
   TBranch        *b_p2p_p200_0000;   //!
   TBranch        *b_p2p_p200_m100;   //!
   TBranch        *b_p2p_p200_m200;   //!
   TBranch        *b_p2p_p200_m300;   //!
   TBranch        *b_p2p_p200_m400;   //!
   TBranch        *b_p2p_p200_m500;   //!
   TBranch        *b_p2p_p100_p500;   //!
   TBranch        *b_p2p_p100_p400;   //!
   TBranch        *b_p2p_p100_p300;   //!
   TBranch        *b_p2p_p100_p200;   //!
   TBranch        *b_p2p_p100_p100;   //!
   TBranch        *b_p2p_p100_0000;   //!
   TBranch        *b_p2p_p100_m100;   //!
   TBranch        *b_p2p_p100_m200;   //!
   TBranch        *b_p2p_p100_m300;   //!
   TBranch        *b_p2p_p100_m400;   //!
   TBranch        *b_p2p_p100_m500;   //!
   TBranch        *b_p2p_0000_p500;   //!
   TBranch        *b_p2p_0000_p400;   //!
   TBranch        *b_p2p_0000_p300;   //!
   TBranch        *b_p2p_0000_p200;   //!
   TBranch        *b_p2p_0000_p100;   //!
   TBranch        *b_p2p_0000_0000;   //!
   TBranch        *b_p2p_0000_m100;   //!
   TBranch        *b_p2p_0000_m200;   //!
   TBranch        *b_p2p_0000_m300;   //!
   TBranch        *b_p2p_0000_m400;   //!
   TBranch        *b_p2p_0000_m500;   //!
   TBranch        *b_p2p_m100_p500;   //!
   TBranch        *b_p2p_m100_p400;   //!
   TBranch        *b_p2p_m100_p300;   //!
   TBranch        *b_p2p_m100_p200;   //!
   TBranch        *b_p2p_m100_p100;   //!
   TBranch        *b_p2p_m100_0000;   //!
   TBranch        *b_p2p_m100_m100;   //!
   TBranch        *b_p2p_m100_m200;   //!
   TBranch        *b_p2p_m100_m300;   //!
   TBranch        *b_p2p_m100_m400;   //!
   TBranch        *b_p2p_m100_m500;   //!
   TBranch        *b_p2p_m200_p500;   //!
   TBranch        *b_p2p_m200_p400;   //!
   TBranch        *b_p2p_m200_p300;   //!
   TBranch        *b_p2p_m200_p200;   //!
   TBranch        *b_p2p_m200_p100;   //!
   TBranch        *b_p2p_m200_0000;   //!
   TBranch        *b_p2p_m200_m100;   //!
   TBranch        *b_p2p_m200_m200;   //!
   TBranch        *b_p2p_m200_m300;   //!
   TBranch        *b_p2p_m200_m400;   //!
   TBranch        *b_p2p_m200_m500;   //!
   TBranch        *b_p2p_m300_p500;   //!
   TBranch        *b_p2p_m300_p400;   //!
   TBranch        *b_p2p_m300_p300;   //!
   TBranch        *b_p2p_m300_p200;   //!
   TBranch        *b_p2p_m300_p100;   //!
   TBranch        *b_p2p_m300_0000;   //!
   TBranch        *b_p2p_m300_m100;   //!
   TBranch        *b_p2p_m300_m200;   //!
   TBranch        *b_p2p_m300_m300;   //!
   TBranch        *b_p2p_m300_m400;   //!
   TBranch        *b_p2p_m300_m500;   //!
   TBranch        *b_p2p_m400_p500;   //!
   TBranch        *b_p2p_m400_p400;   //!
   TBranch        *b_p2p_m400_p300;   //!
   TBranch        *b_p2p_m400_p200;   //!
   TBranch        *b_p2p_m400_p100;   //!
   TBranch        *b_p2p_m400_0000;   //!
   TBranch        *b_p2p_m400_m100;   //!
   TBranch        *b_p2p_m400_m200;   //!
   TBranch        *b_p2p_m400_m300;   //!
   TBranch        *b_p2p_m400_m400;   //!
   TBranch        *b_p2p_m400_m500;   //!
   TBranch        *b_p2p_m500_p500;   //!
   TBranch        *b_p2p_m500_p400;   //!
   TBranch        *b_p2p_m500_p300;   //!
   TBranch        *b_p2p_m500_p200;   //!
   TBranch        *b_p2p_m500_p100;   //!
   TBranch        *b_p2p_m500_0000;   //!
   TBranch        *b_p2p_m500_m100;   //!
   TBranch        *b_p2p_m500_m200;   //!
   TBranch        *b_p2p_m500_m300;   //!
   TBranch        *b_p2p_m500_m400;   //!
   TBranch        *b_p2p_m500_m500;   //!

   Selector_offsetPP(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~Selector_offsetPP() { }
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

   ClassDef(Selector_offsetPP,0);
};

#endif

#ifdef Selector_offsetPP_cxx
void Selector_offsetPP::Init(TTree *tree)
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


   // Set object pointer
   eventheader = 0;
   coinReg = 0;
   plaV1190_F3 = 0;
   plaV1190_FH9 = 0;
   tof_US = 0;
   plaV775 = 0;
   tof_DS = 0;
   smwdc_L = 0;
   smwdc_R = 0;
   beamZ = 0;
   //tofL_p5 = 0;
   //tofR_p5 = 0;
   //tofS0D_p5 = 0;
   //tofL_p4 = 0;
   //tofR_p4 = 0;
   //tofS0D_p4 = 0;
   //tofL_p3 = 0;
   //tofR_p3 = 0;
   //tofS0D_p3 = 0;
   //tofL_p2 = 0;
   //tofR_p2 = 0;
   //tofS0D_p2 = 0;
   //tofL_p1 = 0;
   //tofR_p1 = 0;
   //tofS0D_p1 = 0;
   //tofL = 0;
   //tofR = 0;
   //tofS0D = 0;
   //tofL_m1 = 0;
   //tofR_m1 = 0;
   //tofS0D_m1 = 0;
   //tofL_m2 = 0;
   //tofR_m2 = 0;
   //tofS0D_m2 = 0;
   //tofL_m3 = 0;
   //tofR_m3 = 0;
   //tofS0D_m3 = 0;
   //tofL_m4 = 0;
   //tofR_m4 = 0;
   //tofS0D_m4 = 0;
   //tofL_m5 = 0;
   //tofR_m5 = 0;
   //tofS0D_m5 = 0;
   p2p_p500_p500 = 0;
   p2p_p500_p400 = 0;
   p2p_p500_p300 = 0;
   p2p_p500_p200 = 0;
   p2p_p500_p100 = 0;
   p2p_p500_0000 = 0;
   p2p_p500_m100 = 0;
   p2p_p500_m200 = 0;
   p2p_p500_m300 = 0;
   p2p_p500_m400 = 0;
   p2p_p500_m500 = 0;
   p2p_p400_p500 = 0;
   p2p_p400_p400 = 0;
   p2p_p400_p300 = 0;
   p2p_p400_p200 = 0;
   p2p_p400_p100 = 0;
   p2p_p400_0000 = 0;
   p2p_p400_m100 = 0;
   p2p_p400_m200 = 0;
   p2p_p400_m300 = 0;
   p2p_p400_m400 = 0;
   p2p_p400_m500 = 0;
   p2p_p300_p500 = 0;
   p2p_p300_p400 = 0;
   p2p_p300_p300 = 0;
   p2p_p300_p200 = 0;
   p2p_p300_p100 = 0;
   p2p_p300_0000 = 0;
   p2p_p300_m100 = 0;
   p2p_p300_m200 = 0;
   p2p_p300_m300 = 0;
   p2p_p300_m400 = 0;
   p2p_p300_m500 = 0;
   p2p_p200_p500 = 0;
   p2p_p200_p400 = 0;
   p2p_p200_p300 = 0;
   p2p_p200_p200 = 0;
   p2p_p200_p100 = 0;
   p2p_p200_0000 = 0;
   p2p_p200_m100 = 0;
   p2p_p200_m200 = 0;
   p2p_p200_m300 = 0;
   p2p_p200_m400 = 0;
   p2p_p200_m500 = 0;
   p2p_p100_p500 = 0;
   p2p_p100_p400 = 0;
   p2p_p100_p300 = 0;
   p2p_p100_p200 = 0;
   p2p_p100_p100 = 0;
   p2p_p100_0000 = 0;
   p2p_p100_m100 = 0;
   p2p_p100_m200 = 0;
   p2p_p100_m300 = 0;
   p2p_p100_m400 = 0;
   p2p_p100_m500 = 0;
   p2p_0000_p500 = 0;
   p2p_0000_p400 = 0;
   p2p_0000_p300 = 0;
   p2p_0000_p200 = 0;
   p2p_0000_p100 = 0;
   p2p_0000_0000 = 0;
   p2p_0000_m100 = 0;
   p2p_0000_m200 = 0;
   p2p_0000_m300 = 0;
   p2p_0000_m400 = 0;
   p2p_0000_m500 = 0;
   p2p_m100_p500 = 0;
   p2p_m100_p400 = 0;
   p2p_m100_p300 = 0;
   p2p_m100_p200 = 0;
   p2p_m100_p100 = 0;
   p2p_m100_0000 = 0;
   p2p_m100_m100 = 0;
   p2p_m100_m200 = 0;
   p2p_m100_m300 = 0;
   p2p_m100_m400 = 0;
   p2p_m100_m500 = 0;
   p2p_m200_p500 = 0;
   p2p_m200_p400 = 0;
   p2p_m200_p300 = 0;
   p2p_m200_p200 = 0;
   p2p_m200_p100 = 0;
   p2p_m200_0000 = 0;
   p2p_m200_m100 = 0;
   p2p_m200_m200 = 0;
   p2p_m200_m300 = 0;
   p2p_m200_m400 = 0;
   p2p_m200_m500 = 0;
   p2p_m300_p500 = 0;
   p2p_m300_p400 = 0;
   p2p_m300_p300 = 0;
   p2p_m300_p200 = 0;
   p2p_m300_p100 = 0;
   p2p_m300_0000 = 0;
   p2p_m300_m100 = 0;
   p2p_m300_m200 = 0;
   p2p_m300_m300 = 0;
   p2p_m300_m400 = 0;
   p2p_m300_m500 = 0;
   p2p_m400_p500 = 0;
   p2p_m400_p400 = 0;
   p2p_m400_p300 = 0;
   p2p_m400_p200 = 0;
   p2p_m400_p100 = 0;
   p2p_m400_0000 = 0;
   p2p_m400_m100 = 0;
   p2p_m400_m200 = 0;
   p2p_m400_m300 = 0;
   p2p_m400_m400 = 0;
   p2p_m400_m500 = 0;
   p2p_m500_p500 = 0;
   p2p_m500_p400 = 0;
   p2p_m500_p300 = 0;
   p2p_m500_p200 = 0;
   p2p_m500_p100 = 0;
   p2p_m500_0000 = 0;
   p2p_m500_m100 = 0;
   p2p_m500_m200 = 0;
   p2p_m500_m300 = 0;
   p2p_m500_m400 = 0;
   p2p_m500_m500 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   //fChain->SetBranchAddress("eventheader", &eventheader, &b_eventheader);
   //fChain->SetBranchAddress("coinReg", &coinReg, &b_coinReg);
   //fChain->SetBranchAddress("plaV1190_F3", &plaV1190_F3, &b_plaV1190_F3);
   //fChain->SetBranchAddress("plaV1190_FH9", &plaV1190_FH9, &b_plaV1190_FH9);
   //fChain->SetBranchAddress("tof_US", &tof_US, &b_tof_US);
   //fChain->SetBranchAddress("plaV775", &plaV775, &b_plaV775);
   //fChain->SetBranchAddress("tof_DS", &tof_DS, &b_tof_DS);
   //fChain->SetBranchAddress("smwdc_L", &smwdc_L, &b_smwdc_L);
   //fChain->SetBranchAddress("smwdc_R", &smwdc_R, &b_smwdc_R);
   fChain->SetBranchAddress("beamZ", &beamZ, &b_beamZ);
   //fChain->SetBranchAddress("tofL_p5", &tofL_p5, &b_tofL_p5);
   //fChain->SetBranchAddress("tofR_p5", &tofR_p5, &b_tofR_p5);
   //fChain->SetBranchAddress("tofS0D_p5", &tofS0D_p5, &b_tofS0D_p5);
   //fChain->SetBranchAddress("tofL_p4", &tofL_p4, &b_tofL_p4);
   //fChain->SetBranchAddress("tofR_p4", &tofR_p4, &b_tofR_p4);
   //fChain->SetBranchAddress("tofS0D_p4", &tofS0D_p4, &b_tofS0D_p4);
   //fChain->SetBranchAddress("tofL_p3", &tofL_p3, &b_tofL_p3);
   //fChain->SetBranchAddress("tofR_p3", &tofR_p3, &b_tofR_p3);
   //fChain->SetBranchAddress("tofS0D_p3", &tofS0D_p3, &b_tofS0D_p3);
   //fChain->SetBranchAddress("tofL_p2", &tofL_p2, &b_tofL_p2);
   //fChain->SetBranchAddress("tofR_p2", &tofR_p2, &b_tofR_p2);
   //fChain->SetBranchAddress("tofS0D_p2", &tofS0D_p2, &b_tofS0D_p2);
   //fChain->SetBranchAddress("tofL_p1", &tofL_p1, &b_tofL_p1);
   //fChain->SetBranchAddress("tofR_p1", &tofR_p1, &b_tofR_p1);
   //fChain->SetBranchAddress("tofS0D_p1", &tofS0D_p1, &b_tofS0D_p1);
   //fChain->SetBranchAddress("tofL", &tofL, &b_tofL);
   //fChain->SetBranchAddress("tofR", &tofR, &b_tofR);
   //fChain->SetBranchAddress("tofS0D", &tofS0D, &b_tofS0D);
   //fChain->SetBranchAddress("tofL_m1", &tofL_m1, &b_tofL_m1);
   //fChain->SetBranchAddress("tofR_m1", &tofR_m1, &b_tofR_m1);
   //fChain->SetBranchAddress("tofS0D_m1", &tofS0D_m1, &b_tofS0D_m1);
   //fChain->SetBranchAddress("tofL_m2", &tofL_m2, &b_tofL_m2);
   //fChain->SetBranchAddress("tofR_m2", &tofR_m2, &b_tofR_m2);
   //fChain->SetBranchAddress("tofS0D_m2", &tofS0D_m2, &b_tofS0D_m2);
   //fChain->SetBranchAddress("tofL_m3", &tofL_m3, &b_tofL_m3);
   //fChain->SetBranchAddress("tofR_m3", &tofR_m3, &b_tofR_m3);
   //fChain->SetBranchAddress("tofS0D_m3", &tofS0D_m3, &b_tofS0D_m3);
   //fChain->SetBranchAddress("tofL_m4", &tofL_m4, &b_tofL_m4);
   //fChain->SetBranchAddress("tofR_m4", &tofR_m4, &b_tofR_m4);
   //fChain->SetBranchAddress("tofS0D_m4", &tofS0D_m4, &b_tofS0D_m4);
   //fChain->SetBranchAddress("tofL_m5", &tofL_m5, &b_tofL_m5);
   //fChain->SetBranchAddress("tofR_m5", &tofR_m5, &b_tofR_m5);
   //fChain->SetBranchAddress("tofS0D_m5", &tofS0D_m5, &b_tofS0D_m5);
   fChain->SetBranchAddress("p2p_p500_p500", &p2p_p500_p500, &b_p2p_p500_p500);
   fChain->SetBranchAddress("p2p_p500_p400", &p2p_p500_p400, &b_p2p_p500_p400);
   fChain->SetBranchAddress("p2p_p500_p300", &p2p_p500_p300, &b_p2p_p500_p300);
   fChain->SetBranchAddress("p2p_p500_p200", &p2p_p500_p200, &b_p2p_p500_p200);
   fChain->SetBranchAddress("p2p_p500_p100", &p2p_p500_p100, &b_p2p_p500_p100);
   fChain->SetBranchAddress("p2p_p500_0000", &p2p_p500_0000, &b_p2p_p500_0000);
   fChain->SetBranchAddress("p2p_p500_m100", &p2p_p500_m100, &b_p2p_p500_m100);
   fChain->SetBranchAddress("p2p_p500_m200", &p2p_p500_m200, &b_p2p_p500_m200);
   fChain->SetBranchAddress("p2p_p500_m300", &p2p_p500_m300, &b_p2p_p500_m300);
   fChain->SetBranchAddress("p2p_p500_m400", &p2p_p500_m400, &b_p2p_p500_m400);
   fChain->SetBranchAddress("p2p_p500_m500", &p2p_p500_m500, &b_p2p_p500_m500);
   fChain->SetBranchAddress("p2p_p400_p500", &p2p_p400_p500, &b_p2p_p400_p500);
   fChain->SetBranchAddress("p2p_p400_p400", &p2p_p400_p400, &b_p2p_p400_p400);
   fChain->SetBranchAddress("p2p_p400_p300", &p2p_p400_p300, &b_p2p_p400_p300);
   fChain->SetBranchAddress("p2p_p400_p200", &p2p_p400_p200, &b_p2p_p400_p200);
   fChain->SetBranchAddress("p2p_p400_p100", &p2p_p400_p100, &b_p2p_p400_p100);
   fChain->SetBranchAddress("p2p_p400_0000", &p2p_p400_0000, &b_p2p_p400_0000);
   fChain->SetBranchAddress("p2p_p400_m100", &p2p_p400_m100, &b_p2p_p400_m100);
   fChain->SetBranchAddress("p2p_p400_m200", &p2p_p400_m200, &b_p2p_p400_m200);
   fChain->SetBranchAddress("p2p_p400_m300", &p2p_p400_m300, &b_p2p_p400_m300);
   fChain->SetBranchAddress("p2p_p400_m400", &p2p_p400_m400, &b_p2p_p400_m400);
   fChain->SetBranchAddress("p2p_p400_m500", &p2p_p400_m500, &b_p2p_p400_m500);
   fChain->SetBranchAddress("p2p_p300_p500", &p2p_p300_p500, &b_p2p_p300_p500);
   fChain->SetBranchAddress("p2p_p300_p400", &p2p_p300_p400, &b_p2p_p300_p400);
   fChain->SetBranchAddress("p2p_p300_p300", &p2p_p300_p300, &b_p2p_p300_p300);
   fChain->SetBranchAddress("p2p_p300_p200", &p2p_p300_p200, &b_p2p_p300_p200);
   fChain->SetBranchAddress("p2p_p300_p100", &p2p_p300_p100, &b_p2p_p300_p100);
   fChain->SetBranchAddress("p2p_p300_0000", &p2p_p300_0000, &b_p2p_p300_0000);
   fChain->SetBranchAddress("p2p_p300_m100", &p2p_p300_m100, &b_p2p_p300_m100);
   fChain->SetBranchAddress("p2p_p300_m200", &p2p_p300_m200, &b_p2p_p300_m200);
   fChain->SetBranchAddress("p2p_p300_m300", &p2p_p300_m300, &b_p2p_p300_m300);
   fChain->SetBranchAddress("p2p_p300_m400", &p2p_p300_m400, &b_p2p_p300_m400);
   fChain->SetBranchAddress("p2p_p300_m500", &p2p_p300_m500, &b_p2p_p300_m500);
   fChain->SetBranchAddress("p2p_p200_p500", &p2p_p200_p500, &b_p2p_p200_p500);
   fChain->SetBranchAddress("p2p_p200_p400", &p2p_p200_p400, &b_p2p_p200_p400);
   fChain->SetBranchAddress("p2p_p200_p300", &p2p_p200_p300, &b_p2p_p200_p300);
   fChain->SetBranchAddress("p2p_p200_p200", &p2p_p200_p200, &b_p2p_p200_p200);
   fChain->SetBranchAddress("p2p_p200_p100", &p2p_p200_p100, &b_p2p_p200_p100);
   fChain->SetBranchAddress("p2p_p200_0000", &p2p_p200_0000, &b_p2p_p200_0000);
   fChain->SetBranchAddress("p2p_p200_m100", &p2p_p200_m100, &b_p2p_p200_m100);
   fChain->SetBranchAddress("p2p_p200_m200", &p2p_p200_m200, &b_p2p_p200_m200);
   fChain->SetBranchAddress("p2p_p200_m300", &p2p_p200_m300, &b_p2p_p200_m300);
   fChain->SetBranchAddress("p2p_p200_m400", &p2p_p200_m400, &b_p2p_p200_m400);
   fChain->SetBranchAddress("p2p_p200_m500", &p2p_p200_m500, &b_p2p_p200_m500);
   fChain->SetBranchAddress("p2p_p100_p500", &p2p_p100_p500, &b_p2p_p100_p500);
   fChain->SetBranchAddress("p2p_p100_p400", &p2p_p100_p400, &b_p2p_p100_p400);
   fChain->SetBranchAddress("p2p_p100_p300", &p2p_p100_p300, &b_p2p_p100_p300);
   fChain->SetBranchAddress("p2p_p100_p200", &p2p_p100_p200, &b_p2p_p100_p200);
   fChain->SetBranchAddress("p2p_p100_p100", &p2p_p100_p100, &b_p2p_p100_p100);
   fChain->SetBranchAddress("p2p_p100_0000", &p2p_p100_0000, &b_p2p_p100_0000);
   fChain->SetBranchAddress("p2p_p100_m100", &p2p_p100_m100, &b_p2p_p100_m100);
   fChain->SetBranchAddress("p2p_p100_m200", &p2p_p100_m200, &b_p2p_p100_m200);
   fChain->SetBranchAddress("p2p_p100_m300", &p2p_p100_m300, &b_p2p_p100_m300);
   fChain->SetBranchAddress("p2p_p100_m400", &p2p_p100_m400, &b_p2p_p100_m400);
   fChain->SetBranchAddress("p2p_p100_m500", &p2p_p100_m500, &b_p2p_p100_m500);
   fChain->SetBranchAddress("p2p_0000_p500", &p2p_0000_p500, &b_p2p_0000_p500);
   fChain->SetBranchAddress("p2p_0000_p400", &p2p_0000_p400, &b_p2p_0000_p400);
   fChain->SetBranchAddress("p2p_0000_p300", &p2p_0000_p300, &b_p2p_0000_p300);
   fChain->SetBranchAddress("p2p_0000_p200", &p2p_0000_p200, &b_p2p_0000_p200);
   fChain->SetBranchAddress("p2p_0000_p100", &p2p_0000_p100, &b_p2p_0000_p100);
   fChain->SetBranchAddress("p2p_0000_0000", &p2p_0000_0000, &b_p2p_0000_0000);
   fChain->SetBranchAddress("p2p_0000_m100", &p2p_0000_m100, &b_p2p_0000_m100);
   fChain->SetBranchAddress("p2p_0000_m200", &p2p_0000_m200, &b_p2p_0000_m200);
   fChain->SetBranchAddress("p2p_0000_m300", &p2p_0000_m300, &b_p2p_0000_m300);
   fChain->SetBranchAddress("p2p_0000_m400", &p2p_0000_m400, &b_p2p_0000_m400);
   fChain->SetBranchAddress("p2p_0000_m500", &p2p_0000_m500, &b_p2p_0000_m500);
   fChain->SetBranchAddress("p2p_m100_p500", &p2p_m100_p500, &b_p2p_m100_p500);
   fChain->SetBranchAddress("p2p_m100_p400", &p2p_m100_p400, &b_p2p_m100_p400);
   fChain->SetBranchAddress("p2p_m100_p300", &p2p_m100_p300, &b_p2p_m100_p300);
   fChain->SetBranchAddress("p2p_m100_p200", &p2p_m100_p200, &b_p2p_m100_p200);
   fChain->SetBranchAddress("p2p_m100_p100", &p2p_m100_p100, &b_p2p_m100_p100);
   fChain->SetBranchAddress("p2p_m100_0000", &p2p_m100_0000, &b_p2p_m100_0000);
   fChain->SetBranchAddress("p2p_m100_m100", &p2p_m100_m100, &b_p2p_m100_m100);
   fChain->SetBranchAddress("p2p_m100_m200", &p2p_m100_m200, &b_p2p_m100_m200);
   fChain->SetBranchAddress("p2p_m100_m300", &p2p_m100_m300, &b_p2p_m100_m300);
   fChain->SetBranchAddress("p2p_m100_m400", &p2p_m100_m400, &b_p2p_m100_m400);
   fChain->SetBranchAddress("p2p_m100_m500", &p2p_m100_m500, &b_p2p_m100_m500);
   fChain->SetBranchAddress("p2p_m200_p500", &p2p_m200_p500, &b_p2p_m200_p500);
   fChain->SetBranchAddress("p2p_m200_p400", &p2p_m200_p400, &b_p2p_m200_p400);
   fChain->SetBranchAddress("p2p_m200_p300", &p2p_m200_p300, &b_p2p_m200_p300);
   fChain->SetBranchAddress("p2p_m200_p200", &p2p_m200_p200, &b_p2p_m200_p200);
   fChain->SetBranchAddress("p2p_m200_p100", &p2p_m200_p100, &b_p2p_m200_p100);
   fChain->SetBranchAddress("p2p_m200_0000", &p2p_m200_0000, &b_p2p_m200_0000);
   fChain->SetBranchAddress("p2p_m200_m100", &p2p_m200_m100, &b_p2p_m200_m100);
   fChain->SetBranchAddress("p2p_m200_m200", &p2p_m200_m200, &b_p2p_m200_m200);
   fChain->SetBranchAddress("p2p_m200_m300", &p2p_m200_m300, &b_p2p_m200_m300);
   fChain->SetBranchAddress("p2p_m200_m400", &p2p_m200_m400, &b_p2p_m200_m400);
   fChain->SetBranchAddress("p2p_m200_m500", &p2p_m200_m500, &b_p2p_m200_m500);
   fChain->SetBranchAddress("p2p_m300_p500", &p2p_m300_p500, &b_p2p_m300_p500);
   fChain->SetBranchAddress("p2p_m300_p400", &p2p_m300_p400, &b_p2p_m300_p400);
   fChain->SetBranchAddress("p2p_m300_p300", &p2p_m300_p300, &b_p2p_m300_p300);
   fChain->SetBranchAddress("p2p_m300_p200", &p2p_m300_p200, &b_p2p_m300_p200);
   fChain->SetBranchAddress("p2p_m300_p100", &p2p_m300_p100, &b_p2p_m300_p100);
   fChain->SetBranchAddress("p2p_m300_0000", &p2p_m300_0000, &b_p2p_m300_0000);
   fChain->SetBranchAddress("p2p_m300_m100", &p2p_m300_m100, &b_p2p_m300_m100);
   fChain->SetBranchAddress("p2p_m300_m200", &p2p_m300_m200, &b_p2p_m300_m200);
   fChain->SetBranchAddress("p2p_m300_m300", &p2p_m300_m300, &b_p2p_m300_m300);
   fChain->SetBranchAddress("p2p_m300_m400", &p2p_m300_m400, &b_p2p_m300_m400);
   fChain->SetBranchAddress("p2p_m300_m500", &p2p_m300_m500, &b_p2p_m300_m500);
   fChain->SetBranchAddress("p2p_m400_p500", &p2p_m400_p500, &b_p2p_m400_p500);
   fChain->SetBranchAddress("p2p_m400_p400", &p2p_m400_p400, &b_p2p_m400_p400);
   fChain->SetBranchAddress("p2p_m400_p300", &p2p_m400_p300, &b_p2p_m400_p300);
   fChain->SetBranchAddress("p2p_m400_p200", &p2p_m400_p200, &b_p2p_m400_p200);
   fChain->SetBranchAddress("p2p_m400_p100", &p2p_m400_p100, &b_p2p_m400_p100);
   fChain->SetBranchAddress("p2p_m400_0000", &p2p_m400_0000, &b_p2p_m400_0000);
   fChain->SetBranchAddress("p2p_m400_m100", &p2p_m400_m100, &b_p2p_m400_m100);
   fChain->SetBranchAddress("p2p_m400_m200", &p2p_m400_m200, &b_p2p_m400_m200);
   fChain->SetBranchAddress("p2p_m400_m300", &p2p_m400_m300, &b_p2p_m400_m300);
   fChain->SetBranchAddress("p2p_m400_m400", &p2p_m400_m400, &b_p2p_m400_m400);
   fChain->SetBranchAddress("p2p_m400_m500", &p2p_m400_m500, &b_p2p_m400_m500);
   fChain->SetBranchAddress("p2p_m500_p500", &p2p_m500_p500, &b_p2p_m500_p500);
   fChain->SetBranchAddress("p2p_m500_p400", &p2p_m500_p400, &b_p2p_m500_p400);
   fChain->SetBranchAddress("p2p_m500_p300", &p2p_m500_p300, &b_p2p_m500_p300);
   fChain->SetBranchAddress("p2p_m500_p200", &p2p_m500_p200, &b_p2p_m500_p200);
   fChain->SetBranchAddress("p2p_m500_p100", &p2p_m500_p100, &b_p2p_m500_p100);
   fChain->SetBranchAddress("p2p_m500_0000", &p2p_m500_0000, &b_p2p_m500_0000);
   fChain->SetBranchAddress("p2p_m500_m100", &p2p_m500_m100, &b_p2p_m500_m100);
   fChain->SetBranchAddress("p2p_m500_m200", &p2p_m500_m200, &b_p2p_m500_m200);
   fChain->SetBranchAddress("p2p_m500_m300", &p2p_m500_m300, &b_p2p_m500_m300);
   fChain->SetBranchAddress("p2p_m500_m400", &p2p_m500_m400, &b_p2p_m500_m400);
   fChain->SetBranchAddress("p2p_m500_m500", &p2p_m500_m500, &b_p2p_m500_m500);
   
      //======================
   saveFileName = fChain->GetDirectory()->GetName();
   saveFileName = "O_"+saveFileName;
   
   printf("Converting %s---> %s, total Entry: %d\n", fChain->GetDirectory()->GetName(), saveFileName.Data(), totnumEntry);
   
   saveFile = new TFile(saveFileName, "recreate");
   newTree = new TTree("tree", "tree");
   
   clock.Reset();
   clock.Start("timer");
   shown = 0;
   
   
   theta1 = TMath::QuietNaN();
   theta2 = TMath::QuietNaN();
   Dtheta = TMath::QuietNaN();
   phi1 = TMath::QuietNaN();
   phi2 = TMath::QuietNaN();
   Dphi = TMath::QuietNaN();
   vertexZ = TMath::QuietNaN();
   
   for( Int_t i = 0; i < 11; i++){
      Exm5[i] = TMath::QuietNaN();
      Exm4[i] = TMath::QuietNaN();
      Exm3[i] = TMath::QuietNaN();
      Exm2[i] = TMath::QuietNaN();
      Exm1[i] = TMath::QuietNaN();
      Ex00[i] = TMath::QuietNaN();
      Exp1[i] = TMath::QuietNaN();
      Exp2[i] = TMath::QuietNaN();
      Exp3[i] = TMath::QuietNaN();
      Exp4[i] = TMath::QuietNaN();
      Exp5[i] = TMath::QuietNaN();
   }
   
   newTree->Branch("Dtheta", &Dtheta, "Dtheta/D");
   newTree->Branch("theta1", &theta1, "Dtheta1/D");
   newTree->Branch("theta2", &theta2, "Dtheta2/D");
   newTree->Branch("Dphi", &Dphi, "Dphi/D");
   newTree->Branch("phi1", &phi1, "phi1/D");
   newTree->Branch("phi2", &phi2, "phi2/D");
   newTree->Branch("vertexZ", &vertexZ, "vertexZ/D");
   
   newTree->Branch("Exm5", Exm5, "Exm5[11]/D");
   newTree->Branch("Exm4", Exm4, "Exm4[11]/D");
   newTree->Branch("Exm3", Exm3, "Exm3[11]/D");
   newTree->Branch("Exm2", Exm2, "Exm2[11]/D");
   newTree->Branch("Exm1", Exm1, "Exm1[11]/D");
   newTree->Branch("Ex00", Ex00, "Ex00[11]/D");
   newTree->Branch("Exp1", Exp1, "Exp1[11]/D");
   newTree->Branch("Exp2", Exp2, "Exp2[11]/D");
   newTree->Branch("Exp3", Exp3, "Exp3[11]/D");
   newTree->Branch("Exp4", Exp4, "Exp4[11]/D");
   newTree->Branch("Exp5", Exp5, "Exp5[11]/D");


}

Bool_t Selector_offsetPP::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef Selector_offsetPP_cxx
