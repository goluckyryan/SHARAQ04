//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri May 29 13:39:09 2015 by ROOT version 5.34/10
// from TTree tree/tree
// found on file: 23F_ppcoin_0528_Tplaoffset.root
//////////////////////////////////////////////////////////

#ifndef Selector_offset_h
#define Selector_offset_h

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

class Selector_offset : public TSelector {
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
   
   
   Double_t pidAOQ;
   Double_t vertexZ;

   // Declaration of leaf types
   art::TEventHeader *eventheader0;
   art::TEventHeader *eventheader_shvmism;
   art::TEventHeader *eventheader_shvmif3;
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
   TClonesArray    *tofL_m500;
   TClonesArray    *tofR_m500;
   TClonesArray    *tofS0D_m500;
   TClonesArray    *tofL_m400;
   TClonesArray    *tofR_m400;
   TClonesArray    *tofS0D_m400;
   TClonesArray    *tofL_m300;
   TClonesArray    *tofR_m300;
   TClonesArray    *tofS0D_m300;
   TClonesArray    *tofL_m200;
   TClonesArray    *tofR_m200;
   TClonesArray    *tofS0D_m200;
   TClonesArray    *tofL_m100;
   TClonesArray    *tofR_m100;
   TClonesArray    *tofS0D_m100;
   TClonesArray    *tofL_p100;
   TClonesArray    *tofR_p100;
   TClonesArray    *tofS0D_p100;
   TClonesArray    *tofL_p200;
   TClonesArray    *tofR_p200;
   TClonesArray    *tofS0D_p200;
   TClonesArray    *tofL_p300;
   TClonesArray    *tofR_p300;
   TClonesArray    *tofS0D_p300;
   TClonesArray    *tofL_p400;
   TClonesArray    *tofR_p400;
   TClonesArray    *tofS0D_p400;
   TClonesArray    *tofL_p500;
   TClonesArray    *tofR_p500;
   TClonesArray    *tofS0D_p500;
   art::sh04::TP2PKinematicsData *p2p_m500_m500;
   art::sh04::TP2PKinematicsData *p2p_m500_m400;
   art::sh04::TP2PKinematicsData *p2p_m500_m300;
   art::sh04::TP2PKinematicsData *p2p_m500_m200;
   art::sh04::TP2PKinematicsData *p2p_m500_m100;
   art::sh04::TP2PKinematicsData *p2p_m500_0000;
   art::sh04::TP2PKinematicsData *p2p_m500_p100;
   art::sh04::TP2PKinematicsData *p2p_m500_p200;
   art::sh04::TP2PKinematicsData *p2p_m500_p300;
   art::sh04::TP2PKinematicsData *p2p_m500_p400;
   art::sh04::TP2PKinematicsData *p2p_m500_p500;
   art::sh04::TP2PKinematicsData *p2p_m400_m500;
   art::sh04::TP2PKinematicsData *p2p_m400_m400;
   art::sh04::TP2PKinematicsData *p2p_m400_m300;
   art::sh04::TP2PKinematicsData *p2p_m400_m200;
   art::sh04::TP2PKinematicsData *p2p_m400_m100;
   art::sh04::TP2PKinematicsData *p2p_m400_0000;
   art::sh04::TP2PKinematicsData *p2p_m400_p100;
   art::sh04::TP2PKinematicsData *p2p_m400_p200;
   art::sh04::TP2PKinematicsData *p2p_m400_p300;
   art::sh04::TP2PKinematicsData *p2p_m400_p400;
   art::sh04::TP2PKinematicsData *p2p_m400_p500;
   art::sh04::TP2PKinematicsData *p2p_m300_m500;
   art::sh04::TP2PKinematicsData *p2p_m300_m400;
   art::sh04::TP2PKinematicsData *p2p_m300_m300;
   art::sh04::TP2PKinematicsData *p2p_m300_m200;
   art::sh04::TP2PKinematicsData *p2p_m300_m100;
   art::sh04::TP2PKinematicsData *p2p_m300_0000;
   art::sh04::TP2PKinematicsData *p2p_m300_p100;
   art::sh04::TP2PKinematicsData *p2p_m300_p200;
   art::sh04::TP2PKinematicsData *p2p_m300_p300;
   art::sh04::TP2PKinematicsData *p2p_m300_p400;
   art::sh04::TP2PKinematicsData *p2p_m300_p500;
   art::sh04::TP2PKinematicsData *p2p_m200_m500;
   art::sh04::TP2PKinematicsData *p2p_m200_m400;
   art::sh04::TP2PKinematicsData *p2p_m200_m300;
   art::sh04::TP2PKinematicsData *p2p_m200_m200;
   art::sh04::TP2PKinematicsData *p2p_m200_m100;
   art::sh04::TP2PKinematicsData *p2p_m200_0000;
   art::sh04::TP2PKinematicsData *p2p_m200_p100;
   art::sh04::TP2PKinematicsData *p2p_m200_p200;
   art::sh04::TP2PKinematicsData *p2p_m200_p300;
   art::sh04::TP2PKinematicsData *p2p_m200_p400;
   art::sh04::TP2PKinematicsData *p2p_m200_p500;
   art::sh04::TP2PKinematicsData *p2p_m100_m500;
   art::sh04::TP2PKinematicsData *p2p_m100_m400;
   art::sh04::TP2PKinematicsData *p2p_m100_m300;
   art::sh04::TP2PKinematicsData *p2p_m100_m200;
   art::sh04::TP2PKinematicsData *p2p_m100_m100;
   art::sh04::TP2PKinematicsData *p2p_m100_0000;
   art::sh04::TP2PKinematicsData *p2p_m100_p100;
   art::sh04::TP2PKinematicsData *p2p_m100_p200;
   art::sh04::TP2PKinematicsData *p2p_m100_p300;
   art::sh04::TP2PKinematicsData *p2p_m100_p400;
   art::sh04::TP2PKinematicsData *p2p_m100_p500;
   art::sh04::TP2PKinematicsData *p2p_0000_m500;
   art::sh04::TP2PKinematicsData *p2p_0000_m400;
   art::sh04::TP2PKinematicsData *p2p_0000_m300;
   art::sh04::TP2PKinematicsData *p2p_0000_m200;
   art::sh04::TP2PKinematicsData *p2p_0000_m100;
   art::sh04::TP2PKinematicsData *p2p_0000_p100;
   art::sh04::TP2PKinematicsData *p2p_0000_p200;
   art::sh04::TP2PKinematicsData *p2p_0000_p300;
   art::sh04::TP2PKinematicsData *p2p_0000_p400;
   art::sh04::TP2PKinematicsData *p2p_0000_p500;
   art::sh04::TP2PKinematicsData *p2p_p100_m500;
   art::sh04::TP2PKinematicsData *p2p_p100_m400;
   art::sh04::TP2PKinematicsData *p2p_p100_m300;
   art::sh04::TP2PKinematicsData *p2p_p100_m200;
   art::sh04::TP2PKinematicsData *p2p_p100_m100;
   art::sh04::TP2PKinematicsData *p2p_p100_0000;
   art::sh04::TP2PKinematicsData *p2p_p100_p100;
   art::sh04::TP2PKinematicsData *p2p_p100_p200;
   art::sh04::TP2PKinematicsData *p2p_p100_p300;
   art::sh04::TP2PKinematicsData *p2p_p100_p400;
   art::sh04::TP2PKinematicsData *p2p_p100_p500;
   art::sh04::TP2PKinematicsData *p2p_p200_m500;
   art::sh04::TP2PKinematicsData *p2p_p200_m400;
   art::sh04::TP2PKinematicsData *p2p_p200_m300;
   art::sh04::TP2PKinematicsData *p2p_p200_m200;
   art::sh04::TP2PKinematicsData *p2p_p200_m100;
   art::sh04::TP2PKinematicsData *p2p_p200_0000;
   art::sh04::TP2PKinematicsData *p2p_p200_p100;
   art::sh04::TP2PKinematicsData *p2p_p200_p200;
   art::sh04::TP2PKinematicsData *p2p_p200_p300;
   art::sh04::TP2PKinematicsData *p2p_p200_p400;
   art::sh04::TP2PKinematicsData *p2p_p200_p500;
   art::sh04::TP2PKinematicsData *p2p_p300_m500;
   art::sh04::TP2PKinematicsData *p2p_p300_m400;
   art::sh04::TP2PKinematicsData *p2p_p300_m300;
   art::sh04::TP2PKinematicsData *p2p_p300_m200;
   art::sh04::TP2PKinematicsData *p2p_p300_m100;
   art::sh04::TP2PKinematicsData *p2p_p300_0000;
   art::sh04::TP2PKinematicsData *p2p_p300_p100;
   art::sh04::TP2PKinematicsData *p2p_p300_p200;
   art::sh04::TP2PKinematicsData *p2p_p300_p300;
   art::sh04::TP2PKinematicsData *p2p_p300_p400;
   art::sh04::TP2PKinematicsData *p2p_p300_p500;
   art::sh04::TP2PKinematicsData *p2p_p400_m500;
   art::sh04::TP2PKinematicsData *p2p_p400_m400;
   art::sh04::TP2PKinematicsData *p2p_p400_m300;
   art::sh04::TP2PKinematicsData *p2p_p400_m200;
   art::sh04::TP2PKinematicsData *p2p_p400_m100;
   art::sh04::TP2PKinematicsData *p2p_p400_0000;
   art::sh04::TP2PKinematicsData *p2p_p400_p100;
   art::sh04::TP2PKinematicsData *p2p_p400_p200;
   art::sh04::TP2PKinematicsData *p2p_p400_p300;
   art::sh04::TP2PKinematicsData *p2p_p400_p400;
   art::sh04::TP2PKinematicsData *p2p_p400_p500;
   art::sh04::TP2PKinematicsData *p2p_p500_m500;
   art::sh04::TP2PKinematicsData *p2p_p500_m400;
   art::sh04::TP2PKinematicsData *p2p_p500_m300;
   art::sh04::TP2PKinematicsData *p2p_p500_m200;
   art::sh04::TP2PKinematicsData *p2p_p500_m100;
   art::sh04::TP2PKinematicsData *p2p_p500_0000;
   art::sh04::TP2PKinematicsData *p2p_p500_p100;
   art::sh04::TP2PKinematicsData *p2p_p500_p200;
   art::sh04::TP2PKinematicsData *p2p_p500_p300;
   art::sh04::TP2PKinematicsData *p2p_p500_p400;
   art::sh04::TP2PKinematicsData *p2p_p500_p500;

   // List of branches
   TBranch        *b_eventheader0;   //!
   TBranch        *b_eventheader_shvmism;   //!
   TBranch        *b_eventheader_shvmif3;   //!
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
   TBranch        *b_tofL_m500;   //!
   TBranch        *b_tofR_m500;   //!
   TBranch        *b_tofS0D_m500;   //!
   TBranch        *b_tofL_m400;   //!
   TBranch        *b_tofR_m400;   //!
   TBranch        *b_tofS0D_m400;   //!
   TBranch        *b_tofL_m300;   //!
   TBranch        *b_tofR_m300;   //!
   TBranch        *b_tofS0D_m300;   //!
   TBranch        *b_tofL_m200;   //!
   TBranch        *b_tofR_m200;   //!
   TBranch        *b_tofS0D_m200;   //!
   TBranch        *b_tofL_m100;   //!
   TBranch        *b_tofR_m100;   //!
   TBranch        *b_tofS0D_m100;   //!
   TBranch        *b_tofL_p100;   //!
   TBranch        *b_tofR_p100;   //!
   TBranch        *b_tofS0D_p100;   //!
   TBranch        *b_tofL_p200;   //!
   TBranch        *b_tofR_p200;   //!
   TBranch        *b_tofS0D_p200;   //!
   TBranch        *b_tofL_p300;   //!
   TBranch        *b_tofR_p300;   //!
   TBranch        *b_tofS0D_p300;   //!
   TBranch        *b_tofL_p400;   //!
   TBranch        *b_tofR_p400;   //!
   TBranch        *b_tofS0D_p400;   //!
   TBranch        *b_tofL_p500;   //!
   TBranch        *b_tofR_p500;   //!
   TBranch        *b_tofS0D_p500;   //!
   TBranch        *b_p2p_m500_m500;   //!
   TBranch        *b_p2p_m500_m400;   //!
   TBranch        *b_p2p_m500_m300;   //!
   TBranch        *b_p2p_m500_m200;   //!
   TBranch        *b_p2p_m500_m100;   //!
   TBranch        *b_p2p_m500_0000;   //!
   TBranch        *b_p2p_m500_p100;   //!
   TBranch        *b_p2p_m500_p200;   //!
   TBranch        *b_p2p_m500_p300;   //!
   TBranch        *b_p2p_m500_p400;   //!
   TBranch        *b_p2p_m500_p500;   //!
   TBranch        *b_p2p_m400_m500;   //!
   TBranch        *b_p2p_m400_m400;   //!
   TBranch        *b_p2p_m400_m300;   //!
   TBranch        *b_p2p_m400_m200;   //!
   TBranch        *b_p2p_m400_m100;   //!
   TBranch        *b_p2p_m400_0000;   //!
   TBranch        *b_p2p_m400_p100;   //!
   TBranch        *b_p2p_m400_p200;   //!
   TBranch        *b_p2p_m400_p300;   //!
   TBranch        *b_p2p_m400_p400;   //!
   TBranch        *b_p2p_m400_p500;   //!
   TBranch        *b_p2p_m300_m500;   //!
   TBranch        *b_p2p_m300_m400;   //!
   TBranch        *b_p2p_m300_m300;   //!
   TBranch        *b_p2p_m300_m200;   //!
   TBranch        *b_p2p_m300_m100;   //!
   TBranch        *b_p2p_m300_0000;   //!
   TBranch        *b_p2p_m300_p100;   //!
   TBranch        *b_p2p_m300_p200;   //!
   TBranch        *b_p2p_m300_p300;   //!
   TBranch        *b_p2p_m300_p400;   //!
   TBranch        *b_p2p_m300_p500;   //!
   TBranch        *b_p2p_m200_m500;   //!
   TBranch        *b_p2p_m200_m400;   //!
   TBranch        *b_p2p_m200_m300;   //!
   TBranch        *b_p2p_m200_m200;   //!
   TBranch        *b_p2p_m200_m100;   //!
   TBranch        *b_p2p_m200_0000;   //!
   TBranch        *b_p2p_m200_p100;   //!
   TBranch        *b_p2p_m200_p200;   //!
   TBranch        *b_p2p_m200_p300;   //!
   TBranch        *b_p2p_m200_p400;   //!
   TBranch        *b_p2p_m200_p500;   //!
   TBranch        *b_p2p_m100_m500;   //!
   TBranch        *b_p2p_m100_m400;   //!
   TBranch        *b_p2p_m100_m300;   //!
   TBranch        *b_p2p_m100_m200;   //!
   TBranch        *b_p2p_m100_m100;   //!
   TBranch        *b_p2p_m100_0000;   //!
   TBranch        *b_p2p_m100_p100;   //!
   TBranch        *b_p2p_m100_p200;   //!
   TBranch        *b_p2p_m100_p300;   //!
   TBranch        *b_p2p_m100_p400;   //!
   TBranch        *b_p2p_m100_p500;   //!
   TBranch        *b_p2p_0000_m500;   //!
   TBranch        *b_p2p_0000_m400;   //!
   TBranch        *b_p2p_0000_m300;   //!
   TBranch        *b_p2p_0000_m200;   //!
   TBranch        *b_p2p_0000_m100;   //!
   TBranch        *b_p2p_0000_p100;   //!
   TBranch        *b_p2p_0000_p200;   //!
   TBranch        *b_p2p_0000_p300;   //!
   TBranch        *b_p2p_0000_p400;   //!
   TBranch        *b_p2p_0000_p500;   //!
   TBranch        *b_p2p_p100_m500;   //!
   TBranch        *b_p2p_p100_m400;   //!
   TBranch        *b_p2p_p100_m300;   //!
   TBranch        *b_p2p_p100_m200;   //!
   TBranch        *b_p2p_p100_m100;   //!
   TBranch        *b_p2p_p100_0000;   //!
   TBranch        *b_p2p_p100_p100;   //!
   TBranch        *b_p2p_p100_p200;   //!
   TBranch        *b_p2p_p100_p300;   //!
   TBranch        *b_p2p_p100_p400;   //!
   TBranch        *b_p2p_p100_p500;   //!
   TBranch        *b_p2p_p200_m500;   //!
   TBranch        *b_p2p_p200_m400;   //!
   TBranch        *b_p2p_p200_m300;   //!
   TBranch        *b_p2p_p200_m200;   //!
   TBranch        *b_p2p_p200_m100;   //!
   TBranch        *b_p2p_p200_0000;   //!
   TBranch        *b_p2p_p200_p100;   //!
   TBranch        *b_p2p_p200_p200;   //!
   TBranch        *b_p2p_p200_p300;   //!
   TBranch        *b_p2p_p200_p400;   //!
   TBranch        *b_p2p_p200_p500;   //!
   TBranch        *b_p2p_p300_m500;   //!
   TBranch        *b_p2p_p300_m400;   //!
   TBranch        *b_p2p_p300_m300;   //!
   TBranch        *b_p2p_p300_m200;   //!
   TBranch        *b_p2p_p300_m100;   //!
   TBranch        *b_p2p_p300_0000;   //!
   TBranch        *b_p2p_p300_p100;   //!
   TBranch        *b_p2p_p300_p200;   //!
   TBranch        *b_p2p_p300_p300;   //!
   TBranch        *b_p2p_p300_p400;   //!
   TBranch        *b_p2p_p300_p500;   //!
   TBranch        *b_p2p_p400_m500;   //!
   TBranch        *b_p2p_p400_m400;   //!
   TBranch        *b_p2p_p400_m300;   //!
   TBranch        *b_p2p_p400_m200;   //!
   TBranch        *b_p2p_p400_m100;   //!
   TBranch        *b_p2p_p400_0000;   //!
   TBranch        *b_p2p_p400_p100;   //!
   TBranch        *b_p2p_p400_p200;   //!
   TBranch        *b_p2p_p400_p300;   //!
   TBranch        *b_p2p_p400_p400;   //!
   TBranch        *b_p2p_p400_p500;   //!
   TBranch        *b_p2p_p500_m500;   //!
   TBranch        *b_p2p_p500_m400;   //!
   TBranch        *b_p2p_p500_m300;   //!
   TBranch        *b_p2p_p500_m200;   //!
   TBranch        *b_p2p_p500_m100;   //!
   TBranch        *b_p2p_p500_0000;   //!
   TBranch        *b_p2p_p500_p100;   //!
   TBranch        *b_p2p_p500_p200;   //!
   TBranch        *b_p2p_p500_p300;   //!
   TBranch        *b_p2p_p500_p400;   //!
   TBranch        *b_p2p_p500_p500;   //!

   Selector_offset(TTree * /*tree*/ =0) : fChain(0) { }
   virtual ~Selector_offset() { }
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

   ClassDef(Selector_offset,0);
};

#endif

#ifdef Selector_offset_cxx
void Selector_offset::Init(TTree *tree)
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
   eventheader0 = 0;
   eventheader_shvmism = 0;
   eventheader_shvmif3 = 0;
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
   tofL_m500 = 0;
   tofR_m500 = 0;
   tofS0D_m500 = 0;
   tofL_m400 = 0;
   tofR_m400 = 0;
   tofS0D_m400 = 0;
   tofL_m300 = 0;
   tofR_m300 = 0;
   tofS0D_m300 = 0;
   tofL_m200 = 0;
   tofR_m200 = 0;
   tofS0D_m200 = 0;
   tofL_m100 = 0;
   tofR_m100 = 0;
   tofS0D_m100 = 0;
   tofL_p100 = 0;
   tofR_p100 = 0;
   tofS0D_p100 = 0;
   tofL_p200 = 0;
   tofR_p200 = 0;
   tofS0D_p200 = 0;
   tofL_p300 = 0;
   tofR_p300 = 0;
   tofS0D_p300 = 0;
   tofL_p400 = 0;
   tofR_p400 = 0;
   tofS0D_p400 = 0;
   tofL_p500 = 0;
   tofR_p500 = 0;
   tofS0D_p500 = 0;
   p2p_m500_m500 = 0;
   p2p_m500_m400 = 0;
   p2p_m500_m300 = 0;
   p2p_m500_m200 = 0;
   p2p_m500_m100 = 0;
   p2p_m500_0000 = 0;
   p2p_m500_p100 = 0;
   p2p_m500_p200 = 0;
   p2p_m500_p300 = 0;
   p2p_m500_p400 = 0;
   p2p_m500_p500 = 0;
   p2p_m400_m500 = 0;
   p2p_m400_m400 = 0;
   p2p_m400_m300 = 0;
   p2p_m400_m200 = 0;
   p2p_m400_m100 = 0;
   p2p_m400_0000 = 0;
   p2p_m400_p100 = 0;
   p2p_m400_p200 = 0;
   p2p_m400_p300 = 0;
   p2p_m400_p400 = 0;
   p2p_m400_p500 = 0;
   p2p_m300_m500 = 0;
   p2p_m300_m400 = 0;
   p2p_m300_m300 = 0;
   p2p_m300_m200 = 0;
   p2p_m300_m100 = 0;
   p2p_m300_0000 = 0;
   p2p_m300_p100 = 0;
   p2p_m300_p200 = 0;
   p2p_m300_p300 = 0;
   p2p_m300_p400 = 0;
   p2p_m300_p500 = 0;
   p2p_m200_m500 = 0;
   p2p_m200_m400 = 0;
   p2p_m200_m300 = 0;
   p2p_m200_m200 = 0;
   p2p_m200_m100 = 0;
   p2p_m200_0000 = 0;
   p2p_m200_p100 = 0;
   p2p_m200_p200 = 0;
   p2p_m200_p300 = 0;
   p2p_m200_p400 = 0;
   p2p_m200_p500 = 0;
   p2p_m100_m500 = 0;
   p2p_m100_m400 = 0;
   p2p_m100_m300 = 0;
   p2p_m100_m200 = 0;
   p2p_m100_m100 = 0;
   p2p_m100_0000 = 0;
   p2p_m100_p100 = 0;
   p2p_m100_p200 = 0;
   p2p_m100_p300 = 0;
   p2p_m100_p400 = 0;
   p2p_m100_p500 = 0;
   p2p_0000_m500 = 0;
   p2p_0000_m400 = 0;
   p2p_0000_m300 = 0;
   p2p_0000_m200 = 0;
   p2p_0000_m100 = 0;
   p2p_0000_p100 = 0;
   p2p_0000_p200 = 0;
   p2p_0000_p300 = 0;
   p2p_0000_p400 = 0;
   p2p_0000_p500 = 0;
   p2p_p100_m500 = 0;
   p2p_p100_m400 = 0;
   p2p_p100_m300 = 0;
   p2p_p100_m200 = 0;
   p2p_p100_m100 = 0;
   p2p_p100_0000 = 0;
   p2p_p100_p100 = 0;
   p2p_p100_p200 = 0;
   p2p_p100_p300 = 0;
   p2p_p100_p400 = 0;
   p2p_p100_p500 = 0;
   p2p_p200_m500 = 0;
   p2p_p200_m400 = 0;
   p2p_p200_m300 = 0;
   p2p_p200_m200 = 0;
   p2p_p200_m100 = 0;
   p2p_p200_0000 = 0;
   p2p_p200_p100 = 0;
   p2p_p200_p200 = 0;
   p2p_p200_p300 = 0;
   p2p_p200_p400 = 0;
   p2p_p200_p500 = 0;
   p2p_p300_m500 = 0;
   p2p_p300_m400 = 0;
   p2p_p300_m300 = 0;
   p2p_p300_m200 = 0;
   p2p_p300_m100 = 0;
   p2p_p300_0000 = 0;
   p2p_p300_p100 = 0;
   p2p_p300_p200 = 0;
   p2p_p300_p300 = 0;
   p2p_p300_p400 = 0;
   p2p_p300_p500 = 0;
   p2p_p400_m500 = 0;
   p2p_p400_m400 = 0;
   p2p_p400_m300 = 0;
   p2p_p400_m200 = 0;
   p2p_p400_m100 = 0;
   p2p_p400_0000 = 0;
   p2p_p400_p100 = 0;
   p2p_p400_p200 = 0;
   p2p_p400_p300 = 0;
   p2p_p400_p400 = 0;
   p2p_p400_p500 = 0;
   p2p_p500_m500 = 0;
   p2p_p500_m400 = 0;
   p2p_p500_m300 = 0;
   p2p_p500_m200 = 0;
   p2p_p500_m100 = 0;
   p2p_p500_0000 = 0;
   p2p_p500_p100 = 0;
   p2p_p500_p200 = 0;
   p2p_p500_p300 = 0;
   p2p_p500_p400 = 0;
   p2p_p500_p500 = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fChain->SetMakeClass(1);

   //fChain->SetBranchAddress("eventheader0", &eventheader0, &b_eventheader0);
   //fChain->SetBranchAddress("eventheader_shvmism", &eventheader_shvmism, &b_eventheader_shvmism);
   //fChain->SetBranchAddress("eventheader_shvmif3", &eventheader_shvmif3, &b_eventheader_shvmif3);
   //fChain->SetBranchAddress("coinReg", &coinReg, &b_coinReg);
   fChain->SetBranchAddress("gate", &gate, &b_gate);
   //fChain->SetBranchAddress("plaV1190_F3", &plaV1190_F3, &b_plaV1190_F3);
   fChain->SetBranchAddress("plaV1190_FH9", &plaV1190_FH9, &b_plaV1190_FH9);
   //fChain->SetBranchAddress("tof_US", &tof_US, &b_tof_US);
   //fChain->SetBranchAddress("plaV775", &plaV775, &b_plaV775);
   //fChain->SetBranchAddress("tof_DS", &tof_DS, &b_tof_DS);
   //fChain->SetBranchAddress("S0img", &S0img, &b_S0img);
   fChain->SetBranchAddress("dcs0d", &dcs0d, &b_dcs0d);
   //fChain->SetBranchAddress("smwdc_L", &smwdc_L, &b_smwdc_L);
   //fChain->SetBranchAddress("smwdc_R", &smwdc_R, &b_smwdc_R);
   //fChain->SetBranchAddress("nyoki", &nyoki, &b_nyoki);
   fChain->SetBranchAddress("tof_s1", &tof_s1, &b_tof_s1);
   //fChain->SetBranchAddress("smwdc_S1", &smwdc_S1, &b_smwdc_S1);
   //fChain->SetBranchAddress("nyoki_c", &nyoki_c, &b_nyoki_c);
   //fChain->SetBranchAddress("nyoki_z", &nyoki_z, &b_nyoki_z);
   fChain->SetBranchAddress("pid_s1", &pid_s1, &b_pid_s1);
   //fChain->SetBranchAddress("tof_c", &tof_c, &b_tof_c);
   //fChain->SetBranchAddress("s1_c", &s1_c, &b_s1_c);
   //fChain->SetBranchAddress("beamZ", &beamZ, &b_beamZ);
   fChain->SetBranchAddress("vertex", &vertex, &b_vertex);
   //fChain->SetBranchAddress("tofL", &tofL, &b_tofL);
   //fChain->SetBranchAddress("tofR", &tofR, &b_tofR);
   //fChain->SetBranchAddress("tofS0D", &tofS0D, &b_tofS0D);
   fChain->SetBranchAddress("p2p", &p2p, &b_p2p);
   //fChain->SetBranchAddress("p2p_Lab", &p2p_Lab, &b_p2p_Lab);
   //fChain->SetBranchAddress("tofL_m500", &tofL_m500, &b_tofL_m500);
   //fChain->SetBranchAddress("tofR_m500", &tofR_m500, &b_tofR_m500);
   //fChain->SetBranchAddress("tofS0D_m500", &tofS0D_m500, &b_tofS0D_m500);
   //fChain->SetBranchAddress("tofL_m400", &tofL_m400, &b_tofL_m400);
   //fChain->SetBranchAddress("tofR_m400", &tofR_m400, &b_tofR_m400);
   //fChain->SetBranchAddress("tofS0D_m400", &tofS0D_m400, &b_tofS0D_m400);
   //fChain->SetBranchAddress("tofL_m300", &tofL_m300, &b_tofL_m300);
   //fChain->SetBranchAddress("tofR_m300", &tofR_m300, &b_tofR_m300);
   //fChain->SetBranchAddress("tofS0D_m300", &tofS0D_m300, &b_tofS0D_m300);
   //fChain->SetBranchAddress("tofL_m200", &tofL_m200, &b_tofL_m200);
   //fChain->SetBranchAddress("tofR_m200", &tofR_m200, &b_tofR_m200);
   //fChain->SetBranchAddress("tofS0D_m200", &tofS0D_m200, &b_tofS0D_m200);
   //fChain->SetBranchAddress("tofL_m100", &tofL_m100, &b_tofL_m100);
   //fChain->SetBranchAddress("tofR_m100", &tofR_m100, &b_tofR_m100);
   //fChain->SetBranchAddress("tofS0D_m100", &tofS0D_m100, &b_tofS0D_m100);
   //fChain->SetBranchAddress("tofL_p100", &tofL_p100, &b_tofL_p100);
   //fChain->SetBranchAddress("tofR_p100", &tofR_p100, &b_tofR_p100);
   //fChain->SetBranchAddress("tofS0D_p100", &tofS0D_p100, &b_tofS0D_p100);
   //fChain->SetBranchAddress("tofL_p200", &tofL_p200, &b_tofL_p200);
   //fChain->SetBranchAddress("tofR_p200", &tofR_p200, &b_tofR_p200);
   //fChain->SetBranchAddress("tofS0D_p200", &tofS0D_p200, &b_tofS0D_p200);
   //fChain->SetBranchAddress("tofL_p300", &tofL_p300, &b_tofL_p300);
   //fChain->SetBranchAddress("tofR_p300", &tofR_p300, &b_tofR_p300);
   //fChain->SetBranchAddress("tofS0D_p300", &tofS0D_p300, &b_tofS0D_p300);
   //fChain->SetBranchAddress("tofL_p400", &tofL_p400, &b_tofL_p400);
   //fChain->SetBranchAddress("tofR_p400", &tofR_p400, &b_tofR_p400);
   //fChain->SetBranchAddress("tofS0D_p400", &tofS0D_p400, &b_tofS0D_p400);
   //fChain->SetBranchAddress("tofL_p500", &tofL_p500, &b_tofL_p500);
   //fChain->SetBranchAddress("tofR_p500", &tofR_p500, &b_tofR_p500);
   //fChain->SetBranchAddress("tofS0D_p500", &tofS0D_p500, &b_tofS0D_p500);
   fChain->SetBranchAddress("p2p_m500_m500", &p2p_m500_m500, &b_p2p_m500_m500);
   fChain->SetBranchAddress("p2p_m500_m400", &p2p_m500_m400, &b_p2p_m500_m400);
   fChain->SetBranchAddress("p2p_m500_m300", &p2p_m500_m300, &b_p2p_m500_m300);
   fChain->SetBranchAddress("p2p_m500_m200", &p2p_m500_m200, &b_p2p_m500_m200);
   fChain->SetBranchAddress("p2p_m500_m100", &p2p_m500_m100, &b_p2p_m500_m100);
   fChain->SetBranchAddress("p2p_m500_0000", &p2p_m500_0000, &b_p2p_m500_0000);
   fChain->SetBranchAddress("p2p_m500_p100", &p2p_m500_p100, &b_p2p_m500_p100);
   fChain->SetBranchAddress("p2p_m500_p200", &p2p_m500_p200, &b_p2p_m500_p200);
   fChain->SetBranchAddress("p2p_m500_p300", &p2p_m500_p300, &b_p2p_m500_p300);
   fChain->SetBranchAddress("p2p_m500_p400", &p2p_m500_p400, &b_p2p_m500_p400);
   fChain->SetBranchAddress("p2p_m500_p500", &p2p_m500_p500, &b_p2p_m500_p500);
   fChain->SetBranchAddress("p2p_m400_m500", &p2p_m400_m500, &b_p2p_m400_m500);
   fChain->SetBranchAddress("p2p_m400_m400", &p2p_m400_m400, &b_p2p_m400_m400);
   fChain->SetBranchAddress("p2p_m400_m300", &p2p_m400_m300, &b_p2p_m400_m300);
   fChain->SetBranchAddress("p2p_m400_m200", &p2p_m400_m200, &b_p2p_m400_m200);
   fChain->SetBranchAddress("p2p_m400_m100", &p2p_m400_m100, &b_p2p_m400_m100);
   fChain->SetBranchAddress("p2p_m400_0000", &p2p_m400_0000, &b_p2p_m400_0000);
   fChain->SetBranchAddress("p2p_m400_p100", &p2p_m400_p100, &b_p2p_m400_p100);
   fChain->SetBranchAddress("p2p_m400_p200", &p2p_m400_p200, &b_p2p_m400_p200);
   fChain->SetBranchAddress("p2p_m400_p300", &p2p_m400_p300, &b_p2p_m400_p300);
   fChain->SetBranchAddress("p2p_m400_p400", &p2p_m400_p400, &b_p2p_m400_p400);
   fChain->SetBranchAddress("p2p_m400_p500", &p2p_m400_p500, &b_p2p_m400_p500);
   fChain->SetBranchAddress("p2p_m300_m500", &p2p_m300_m500, &b_p2p_m300_m500);
   fChain->SetBranchAddress("p2p_m300_m400", &p2p_m300_m400, &b_p2p_m300_m400);
   fChain->SetBranchAddress("p2p_m300_m300", &p2p_m300_m300, &b_p2p_m300_m300);
   fChain->SetBranchAddress("p2p_m300_m200", &p2p_m300_m200, &b_p2p_m300_m200);
   fChain->SetBranchAddress("p2p_m300_m100", &p2p_m300_m100, &b_p2p_m300_m100);
   fChain->SetBranchAddress("p2p_m300_0000", &p2p_m300_0000, &b_p2p_m300_0000);
   fChain->SetBranchAddress("p2p_m300_p100", &p2p_m300_p100, &b_p2p_m300_p100);
   fChain->SetBranchAddress("p2p_m300_p200", &p2p_m300_p200, &b_p2p_m300_p200);
   fChain->SetBranchAddress("p2p_m300_p300", &p2p_m300_p300, &b_p2p_m300_p300);
   fChain->SetBranchAddress("p2p_m300_p400", &p2p_m300_p400, &b_p2p_m300_p400);
   fChain->SetBranchAddress("p2p_m300_p500", &p2p_m300_p500, &b_p2p_m300_p500);
   fChain->SetBranchAddress("p2p_m200_m500", &p2p_m200_m500, &b_p2p_m200_m500);
   fChain->SetBranchAddress("p2p_m200_m400", &p2p_m200_m400, &b_p2p_m200_m400);
   fChain->SetBranchAddress("p2p_m200_m300", &p2p_m200_m300, &b_p2p_m200_m300);
   fChain->SetBranchAddress("p2p_m200_m200", &p2p_m200_m200, &b_p2p_m200_m200);
   fChain->SetBranchAddress("p2p_m200_m100", &p2p_m200_m100, &b_p2p_m200_m100);
   fChain->SetBranchAddress("p2p_m200_0000", &p2p_m200_0000, &b_p2p_m200_0000);
   fChain->SetBranchAddress("p2p_m200_p100", &p2p_m200_p100, &b_p2p_m200_p100);
   fChain->SetBranchAddress("p2p_m200_p200", &p2p_m200_p200, &b_p2p_m200_p200);
   fChain->SetBranchAddress("p2p_m200_p300", &p2p_m200_p300, &b_p2p_m200_p300);
   fChain->SetBranchAddress("p2p_m200_p400", &p2p_m200_p400, &b_p2p_m200_p400);
   fChain->SetBranchAddress("p2p_m200_p500", &p2p_m200_p500, &b_p2p_m200_p500);
   fChain->SetBranchAddress("p2p_m100_m500", &p2p_m100_m500, &b_p2p_m100_m500);
   fChain->SetBranchAddress("p2p_m100_m400", &p2p_m100_m400, &b_p2p_m100_m400);
   fChain->SetBranchAddress("p2p_m100_m300", &p2p_m100_m300, &b_p2p_m100_m300);
   fChain->SetBranchAddress("p2p_m100_m200", &p2p_m100_m200, &b_p2p_m100_m200);
   fChain->SetBranchAddress("p2p_m100_m100", &p2p_m100_m100, &b_p2p_m100_m100);
   fChain->SetBranchAddress("p2p_m100_0000", &p2p_m100_0000, &b_p2p_m100_0000);
   fChain->SetBranchAddress("p2p_m100_p100", &p2p_m100_p100, &b_p2p_m100_p100);
   fChain->SetBranchAddress("p2p_m100_p200", &p2p_m100_p200, &b_p2p_m100_p200);
   fChain->SetBranchAddress("p2p_m100_p300", &p2p_m100_p300, &b_p2p_m100_p300);
   fChain->SetBranchAddress("p2p_m100_p400", &p2p_m100_p400, &b_p2p_m100_p400);
   fChain->SetBranchAddress("p2p_m100_p500", &p2p_m100_p500, &b_p2p_m100_p500);
   fChain->SetBranchAddress("p2p_0000_m500", &p2p_0000_m500, &b_p2p_0000_m500);
   fChain->SetBranchAddress("p2p_0000_m400", &p2p_0000_m400, &b_p2p_0000_m400);
   fChain->SetBranchAddress("p2p_0000_m300", &p2p_0000_m300, &b_p2p_0000_m300);
   fChain->SetBranchAddress("p2p_0000_m200", &p2p_0000_m200, &b_p2p_0000_m200);
   fChain->SetBranchAddress("p2p_0000_m100", &p2p_0000_m100, &b_p2p_0000_m100);
   fChain->SetBranchAddress("p2p_0000_p100", &p2p_0000_p100, &b_p2p_0000_p100);
   fChain->SetBranchAddress("p2p_0000_p200", &p2p_0000_p200, &b_p2p_0000_p200);
   fChain->SetBranchAddress("p2p_0000_p300", &p2p_0000_p300, &b_p2p_0000_p300);
   fChain->SetBranchAddress("p2p_0000_p400", &p2p_0000_p400, &b_p2p_0000_p400);
   fChain->SetBranchAddress("p2p_0000_p500", &p2p_0000_p500, &b_p2p_0000_p500);
   fChain->SetBranchAddress("p2p_p100_m500", &p2p_p100_m500, &b_p2p_p100_m500);
   fChain->SetBranchAddress("p2p_p100_m400", &p2p_p100_m400, &b_p2p_p100_m400);
   fChain->SetBranchAddress("p2p_p100_m300", &p2p_p100_m300, &b_p2p_p100_m300);
   fChain->SetBranchAddress("p2p_p100_m200", &p2p_p100_m200, &b_p2p_p100_m200);
   fChain->SetBranchAddress("p2p_p100_m100", &p2p_p100_m100, &b_p2p_p100_m100);
   fChain->SetBranchAddress("p2p_p100_0000", &p2p_p100_0000, &b_p2p_p100_0000);
   fChain->SetBranchAddress("p2p_p100_p100", &p2p_p100_p100, &b_p2p_p100_p100);
   fChain->SetBranchAddress("p2p_p100_p200", &p2p_p100_p200, &b_p2p_p100_p200);
   fChain->SetBranchAddress("p2p_p100_p300", &p2p_p100_p300, &b_p2p_p100_p300);
   fChain->SetBranchAddress("p2p_p100_p400", &p2p_p100_p400, &b_p2p_p100_p400);
   fChain->SetBranchAddress("p2p_p100_p500", &p2p_p100_p500, &b_p2p_p100_p500);
   fChain->SetBranchAddress("p2p_p200_m500", &p2p_p200_m500, &b_p2p_p200_m500);
   fChain->SetBranchAddress("p2p_p200_m400", &p2p_p200_m400, &b_p2p_p200_m400);
   fChain->SetBranchAddress("p2p_p200_m300", &p2p_p200_m300, &b_p2p_p200_m300);
   fChain->SetBranchAddress("p2p_p200_m200", &p2p_p200_m200, &b_p2p_p200_m200);
   fChain->SetBranchAddress("p2p_p200_m100", &p2p_p200_m100, &b_p2p_p200_m100);
   fChain->SetBranchAddress("p2p_p200_0000", &p2p_p200_0000, &b_p2p_p200_0000);
   fChain->SetBranchAddress("p2p_p200_p100", &p2p_p200_p100, &b_p2p_p200_p100);
   fChain->SetBranchAddress("p2p_p200_p200", &p2p_p200_p200, &b_p2p_p200_p200);
   fChain->SetBranchAddress("p2p_p200_p300", &p2p_p200_p300, &b_p2p_p200_p300);
   fChain->SetBranchAddress("p2p_p200_p400", &p2p_p200_p400, &b_p2p_p200_p400);
   fChain->SetBranchAddress("p2p_p200_p500", &p2p_p200_p500, &b_p2p_p200_p500);
   fChain->SetBranchAddress("p2p_p300_m500", &p2p_p300_m500, &b_p2p_p300_m500);
   fChain->SetBranchAddress("p2p_p300_m400", &p2p_p300_m400, &b_p2p_p300_m400);
   fChain->SetBranchAddress("p2p_p300_m300", &p2p_p300_m300, &b_p2p_p300_m300);
   fChain->SetBranchAddress("p2p_p300_m200", &p2p_p300_m200, &b_p2p_p300_m200);
   fChain->SetBranchAddress("p2p_p300_m100", &p2p_p300_m100, &b_p2p_p300_m100);
   fChain->SetBranchAddress("p2p_p300_0000", &p2p_p300_0000, &b_p2p_p300_0000);
   fChain->SetBranchAddress("p2p_p300_p100", &p2p_p300_p100, &b_p2p_p300_p100);
   fChain->SetBranchAddress("p2p_p300_p200", &p2p_p300_p200, &b_p2p_p300_p200);
   fChain->SetBranchAddress("p2p_p300_p300", &p2p_p300_p300, &b_p2p_p300_p300);
   fChain->SetBranchAddress("p2p_p300_p400", &p2p_p300_p400, &b_p2p_p300_p400);
   fChain->SetBranchAddress("p2p_p300_p500", &p2p_p300_p500, &b_p2p_p300_p500);
   fChain->SetBranchAddress("p2p_p400_m500", &p2p_p400_m500, &b_p2p_p400_m500);
   fChain->SetBranchAddress("p2p_p400_m400", &p2p_p400_m400, &b_p2p_p400_m400);
   fChain->SetBranchAddress("p2p_p400_m300", &p2p_p400_m300, &b_p2p_p400_m300);
   fChain->SetBranchAddress("p2p_p400_m200", &p2p_p400_m200, &b_p2p_p400_m200);
   fChain->SetBranchAddress("p2p_p400_m100", &p2p_p400_m100, &b_p2p_p400_m100);
   fChain->SetBranchAddress("p2p_p400_0000", &p2p_p400_0000, &b_p2p_p400_0000);
   fChain->SetBranchAddress("p2p_p400_p100", &p2p_p400_p100, &b_p2p_p400_p100);
   fChain->SetBranchAddress("p2p_p400_p200", &p2p_p400_p200, &b_p2p_p400_p200);
   fChain->SetBranchAddress("p2p_p400_p300", &p2p_p400_p300, &b_p2p_p400_p300);
   fChain->SetBranchAddress("p2p_p400_p400", &p2p_p400_p400, &b_p2p_p400_p400);
   fChain->SetBranchAddress("p2p_p400_p500", &p2p_p400_p500, &b_p2p_p400_p500);
   fChain->SetBranchAddress("p2p_p500_m500", &p2p_p500_m500, &b_p2p_p500_m500);
   fChain->SetBranchAddress("p2p_p500_m400", &p2p_p500_m400, &b_p2p_p500_m400);
   fChain->SetBranchAddress("p2p_p500_m300", &p2p_p500_m300, &b_p2p_p500_m300);
   fChain->SetBranchAddress("p2p_p500_m200", &p2p_p500_m200, &b_p2p_p500_m200);
   fChain->SetBranchAddress("p2p_p500_m100", &p2p_p500_m100, &b_p2p_p500_m100);
   fChain->SetBranchAddress("p2p_p500_0000", &p2p_p500_0000, &b_p2p_p500_0000);
   fChain->SetBranchAddress("p2p_p500_p100", &p2p_p500_p100, &b_p2p_p500_p100);
   fChain->SetBranchAddress("p2p_p500_p200", &p2p_p500_p200, &b_p2p_p500_p200);
   fChain->SetBranchAddress("p2p_p500_p300", &p2p_p500_p300, &b_p2p_p500_p300);
   fChain->SetBranchAddress("p2p_p500_p400", &p2p_p500_p400, &b_p2p_p500_p400);
   fChain->SetBranchAddress("p2p_p500_p500", &p2p_p500_p500, &b_p2p_p500_p500);
   
   //======================
   saveFileName = fChain->GetDirectory()->GetName();
   saveFileName = "O_"+saveFileName;
   
   printf("Converting %s---> %s, total Entry: %d\n", fChain->GetDirectory()->GetName(), saveFileName.Data(), totnumEntry);
   
   saveFile = new TFile(saveFileName, "recreate");
   newTree = new TTree("tree", "tree");
   
   clock.Reset();
   clock.Start("timer");
   shown = 0;
   
   
   pidAOQ = TMath::QuietNaN();
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
   
   newTree->Branch("pidAOQ", &pidAOQ, "pidAOQ/D");
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

Bool_t Selector_offset::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

#endif // #ifdef Selector_offset_cxx
