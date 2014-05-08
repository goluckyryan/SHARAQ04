#include <TBenchmark.h>
#include <TFile.h>
#include <TMath.h>
#include <math.h>
#include <TTree.h>
#include <TList.h>
#include <TClonesArray.h>

void detectorOnOffCheck() {
//================ Tree branch
   Int_t eventID;
   // runNumber
   Int_t runNum;
   // coinReg
   Int_t coinReg;
   // detectorID
   Int_t PPAC        = 1;
   Int_t F3plaV1190  = 2;
   Int_t FH9plaV1190 = 3;
   Int_t F3plaV775   = 4;
   Int_t FH9plaV775  = 5;
   Int_t S0Dpla      = 6;
   Int_t TplaL       = 7;
   Int_t TplaR       = 8;
   Int_t S0imgT      = 9;
   Int_t smwdcLT     = 10;
   Int_t smwdcRT     = 11;
   Int_t NyokiAny    = 12;
   Int_t smwdcS1T    = 13;
   const Int_t nDet = 11;
   Int_t * detID = new Int_t[nDet+1];
   // combined 
   Int_t F3FH9V1190  = 1; // 2+3
   Int_t F3FH9V775   = 2; // 4+5
   Int_t TplaLR      = 3; // 7+8
   Int_t smwdcLR     = 4; // 10+11
   Int_t TplaSMWDC   = 5; // [4]+[5]
   Int_t F3FH9S0D    = 6; //V775 [2]+9
   Int_t Pla         = 7; //V775
   Int_t PlaPPAC     = 8; //V775
   Int_t PlaPPACS0img= 9; //V775
   Int_t All         = 10;//V775
   Int_t F3FH9S0D2    = 16; //V1190 
   Int_t Pla2         = 17; //V1190
   Int_t PlaPPAC2     = 18; //V1190
   Int_t PlaPPACS0img2= 19; //V1190
   Int_t All2         = 20;//V1190
   
   Int_t combID[21], nComb = 20; // remember to change the branch
  
   // mwdc channel 
   // DCX1           = 
   //Int_t mwdcCh;

//############################################################################   
   const char* savefilename="Dphys22_clean.root";
   const char* rootfile="Data/phys22_clean.root";
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=1000000;
   
//############################################################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;

   TFile *savefile = new TFile(savefilename,"recreate");
   TTree *recoil; 
   recoil = new TTree("recoil","recoil");
   recoil->Branch("runNum" , &runNum  , "runNum/I");
   recoil->Branch("eventID", &eventID , "eventID/I");
   recoil->Branch("coinReg", &coinReg , "coinReg/I");
   recoil->Branch("detID"  , detID    , "detID[12]/I");
   recoil->Branch("combID" , combID   , "combID[21]/I");

//############################################################################
   art::TCoinRegData *hoge_coinReg;
   art::TEventHeader *hoge_run;
   TClonesArray *hoge_ppac, *hoge_f3, *hoge_fh9, *hoge_V775, *hoge_nyoki, *hoge_S0img, *hoge_L, *hoge_R;
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded. ----> %s\n",rootfile, savefilename);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("eventheader",1);
   tree->SetBranchStatus("coinReg",1);
   tree->SetBranchStatus("ppac",1);
   tree->SetBranchStatus("plaV1190_F3",1);
   tree->SetBranchStatus("plaV1190_FH9",1); //get charge for PID
   tree->SetBranchStatus("plaV775",1);    //get charge and time
   tree->SetBranchStatus("S0img",1);
   //tree->SetBranchStatus("nyoki",1);
   tree->SetBranchStatus("smwdc_L",1);
   tree->SetBranchStatus("smwdc_R",1);

   tree->SetBranchAddress("eventheader",&hoge_run);
   tree->SetBranchAddress("coinReg",&hoge_coinReg);
   tree->SetBranchAddress("ppac",&hoge_ppac);
   tree->SetBranchAddress("plaV1190_F3",&hoge_f3);
   tree->SetBranchAddress("plaV1190_FH9",&hoge_fh9);
   tree->SetBranchAddress("plaV775",&hoge_V775);
   tree->SetBranchAddress("S0img",&hoge_S0img);
   //tree->SetBranchAddress("nyoki",&hoge_nyoki);
   tree->SetBranchAddress("smwdc_L",&hoge_L);
   tree->SetBranchAddress("smwdc_R",&hoge_R);

//############################################################################   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);

   art::TTwoSidedPlasticData * V775Data;
   art::TMWDCTrackingResult * xyS0,* xy1,* xy2;
   
//#############################################################################
   for( eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID);
      
      for ( Int_t p = 0; p < nDet+1; p++){
         detID[p] = -1;
      }
      for ( Int_t p = 0; p < nComb+1; p++){
         combID[p] = -1;
      }

//----------------Get Event Number
      runNum = hoge_run->GetRunNumber();
      
//--------------Get coinReg
      // 0 = F3, 1 = FH9, 2=ppcoin, 3 = ND coin, 4 = ppsingle, 5 = ND single, 6 = ND cosmic
      coinReg = 0;
      for (Int_t k = 0; k <7; k++){
         if ( k == 1 ){
            if ( hoge_coinReg->Test(1) == 1 ) coinReg += 10;
         }else if ( k == 2){
            if ( hoge_coinReg->Test(2) == 1 ) coinReg += 20;
         }else if ( k == 3){
            if ( hoge_coinReg->Test(3) == 1) coinReg += 40;
         }else{
            if ( hoge_coinReg->Test(k) == 1) coinReg += 1;
         }
      }

//---------------------- PPAC;
      Int_t nHit = hoge_ppac->GetEntriesFast();
      if (nHit > 0 ) {
         detID[PPAC] = PPAC;
      }
      
//----------------Get  V1190
      Int_t nHit = hoge_f3 -> GetEntriesFast();
      if ( nHit > 0 ) {
         detID[F3plaV1190] = F3plaV1190;
      }
      
      Int_t nHit = hoge_fh9 -> GetEntriesFast();
      if ( nHit > 0 ) {
         detID[FH9plaV1190] = FH9plaV1190;
      }
      
//---------------Get V775
      Int_t nHit = hoge_V775->GetEntriesFast();
      for ( Int_t p = 0; p < nHit; p++){
         V775Data = (art::TTwoSidedPlasticData*)hoge_V775->At(p);
         Int_t DetID  = V775Data->GetDetID();
         if (DetID == 0) {
            detID[TplaL] = TplaL;
         }
         if (DetID == 1) {
            detID[TplaR] = TplaR;
         }
         if (DetID == 2) {
            detID[F3plaV775] = F3plaV775;
         }
         if (DetID == 3) {
            detID[FH9plaV775] = FH9plaV775;
         }
         if (DetID == 4) {
            detID[S0Dpla] = S0Dpla;
         }
      }
//--------------- Nyoki
//      Int_t nHit = hoge_nyoki->GetEntriesFast();
//      if (nHit > 0) 
     
//---------Get S0img image, should be one 1 instance
      nHit = hoge_S0img->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         xyS0 = (art::TMWDCTrackingResult*)hoge_S0img->At(p);
         if ( xyS0 -> GetTrackingID() == 1 ) { 
            detID[S0imgT] = S0imgT;
         }
      }
      
//---------Get SMWDC image, should be one 1 instance
      nHit = hoge_L->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         xy1 = (art::TMWDCTrackingResult*)hoge_L->At(p);
         if ( xy1 -> GetTrackingID() == 1) {
            detID[smwdcLT] = smwdcLT;
         }
      }
      
      nHit = hoge_R->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         xy2 = (art::TMWDCTrackingResult*)hoge_R->At(p);
         if ( xy2 -> GetTrackingID() == 1) {
            detID[smwdcRT] = smwdcRT;
         }
      }
      
//------------- COmbination
      if ( detID[F3plaV1190] > 0 && detID[FH9plaV1190] > 0) combID[F3FH9V1190] = F3FH9V1190;
      if ( detID[F3plaV775] > 0 && detID[FH9plaV775] > 0) combID[F3FH9V775] = F3FH9V775;
      if ( detID[TplaL] > 0 && detID[TplaR] > 0) combID[TplaLR] = TplaLR;
      if ( detID[smwdcLT] > 0 && detID[smwdcRT] > 0) combID[smwdcLR] = smwdcLR;
      if ( combID[TplaLR] > 0 && combID[smwdcLR] > 0) combID[TplaSMWDC] = TplaSMWDC;
      if ( combID[F3FH9V775] > 0 && detID[S0Dpla] > 0) combID[F3FH9S0D] = F3FH9S0D;
      if ( combID[F3FH9S0D] > 0 && combID[TplaLR] > 0) combID[Pla] = Pla;
      if ( combID[Pla] > 0 && detID[PPAC] > 0) combID[PlaPPAC] = PlaPPAC;
      if ( combID[PlaPPAC] > 0 && detID[S0imgT] > 0) combID[PlaPPACS0img] = PlaPPACS0img;
      if ( combID[PlaPPACS0img] > 0 && combID[smwdcLR] > 0) combID[All] = All;
      
      if ( combID[F3FH9V1190] > 0 && detID[S0Dpla] > 0) combID[F3FH9S0D2] = F3FH9S0D2;
      if ( combID[F3FH9S0D2] > 0 && combID[TplaLR] > 0) combID[Pla2] = Pla2;
      if ( combID[Pla2] > 0 && detID[PPAC] > 0) combID[PlaPPAC2] = PlaPPAC2;
      if ( combID[PlaPPAC2] > 0 && detID[S0imgT] > 0) combID[PlaPPACS0img2] = PlaPPACS0img2;
      if ( combID[PlaPPACS0img2] > 0 && combID[smwdcLR] > 0) combID[All2] = All2;
      
//----------- Print
/*      printf(" %10d |", eventID);
      for ( Int_t p = 1; p < nDet+1; p++){
         printf("%3d, ", detID[p]);
      }
      printf("\n");
      printf(" %10s |", "comb");
      for ( Int_t p = 1; p < nComb+1; p++){
         printf("%3d, ", combID[p]);
      }
      printf("\n");
*/
//----------- Fill        
      savefile->cd(); //set focus on this file
      recoil->Fill();  
      
//------------Clock      
      clock.Stop("timer");
      Double_t time = clock.GetRealTime("timer");
      clock.Start("timer");
      
      if ( !shown ) {
         if (fmod(time, 10) < 1 ){
            printf( "%10d[%2d%%](#%2d) |%3d min %5.2f sec | expect:%5.1fmin\n", 
            eventID, 
            TMath::Nint((eventID+1-firstEntry)*100./nEntries),
            runNum,
            TMath::Floor(time/60), time - TMath::Floor(time/60)*60,
            nEntries*time/(eventID+1-firstEntry)/60.);
            shown = 1;
         }
      }else{
         if (fmod(time, 10) > 9 ){
            shown = 0;
         }
      }
      
   }
  
   savefile->cd();
   recoil->Write();
   savefile->Close();
   f->Close();

   clock.Stop("timer");
   printf("============ finished|%10.3f sec --> %s\n",clock.GetRealTime("timer"),savefilename);
   delete detID;
   return ;
}
