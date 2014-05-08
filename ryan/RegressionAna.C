#include <TBenchmark.h>
#include <TFile.h>
#include <TMath.h>
#include <TTree.h>
#include <TClonesArray.h>
#include "constant.h"
#include "TBeamData.h"


void RegressionAna() {
  
   // Get SMWDC X Y
   Int_t NValidPlane1;
   Double_t x1, y1, a1, b1; // for smwdc-L
   Double_t wireID[6], DL[6];
   Double_t MSRi[6], MSR;
   Double_t Res[6];
   Int_t TrackID;
   
//############################################################################   
   const char* savefilename="RegAna.root";
   const char* rootfile="~/sharaq04/smwdc_l.root";
   Bool_t debugInfo = 0;
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=100;

//############################################################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   
   TFile savefile(savefilename,"recreate");
   TTree *regAna; 
   regAna = new TTree("regAna","regAna");
   regAna->Branch("eventID",&eventID,"eventID/I");
   regAna->Branch("NValidPlane1",&NValidPlane1,"NValidPlane1/I");
   regAna->Branch("wireID1",wireID  ,"wireID/D");
   regAna->Branch("wireID2",wireID+1,"(wireID+1)/D");
   regAna->Branch("wireID3",wireID+2,"(wireID+2)/D");
   regAna->Branch("wireID4",wireID+3,"(wireID+3)/D");
   regAna->Branch("wireID5",wireID+4,"(wireID+4)/D");
   regAna->Branch("wireID6",wireID+5,"(wireID+5)/D");
   regAna->Branch("TrackID",&TrackID,"TrackID/I");
   regAna->Branch("MSR",&MSR,"MSR/D");
   regAna->Branch("MSRi1",MSRi  ,"MSRi/D");
   regAna->Branch("MSRi2",MSRi+1,"(MSRi+1)/D");
   regAna->Branch("MSRi3",MSRi+2,"(MSRi+2)/D");
   regAna->Branch("MSRi4",MSRi+3,"(MSRi+3)/D");
   regAna->Branch("MSRi5",MSRi+4,"(MSRi+4)/D");
   regAna->Branch("MSRi6",MSRi+5,"(MSRi+5)/D");
   regAna->Branch("Res1",Res,"Res/D");
   regAna->Branch("Res2",Res+1,"(Res+1)/D");
   regAna->Branch("Res3",Res+2,"(Res+2)/D");
   regAna->Branch("Res4",Res+3,"(Res+3)/D");
   regAna->Branch("Res5",Res+4,"(Res+4)/D");
   regAna->Branch("Res6",Res+5,"(Res+5)/D");
   regAna->Branch("x1",&x1,"x1/D");
   regAna->Branch("a1",&a1,"a1/D");
   regAna->Branch("y1",&y1,"y1/D");
   regAna->Branch("b1",&b1,"b1/D");

//############################################################################
   //TCanvas *cRegAna = new TCanvas ("cRegAna","cRegAna", 50 , 50 , 600, 600);
   //TH2F * h2D  = new TH2F("h2d","h2d", 100, -1, 0.2, 100, -20,10);

   TClonesArray *hoge_L;
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded.\n",rootfile);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   printf("====== totnumEntry:%d\n", totnumEntry);
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("smwdc_L",1);

   tree->SetBranchAddress("smwdc_L",&hoge_L);

//############################################################################   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) endEntry = totnumEntry;
   
   if (debugInfo) printf("======================================\n");
   
   for( Int_t eventID = firstEntry; eventID < endEntry; eventID++){
      tree->GetEntry(eventID);

     //Get SMWDC image, should be one 1 instance
      Int_t smwdcHit1 = hoge_L->GetEntriesFast();
      for( Int_t p = 0; p < smwdcHit1; p++){
         art::TMWDCTrackingResult* SMWDC = (art::TMWDCTrackingResult*)hoge_L->At(p);
         if (SMWDC->GetTrackingID() == 0) continue;
         NValidPlane1 = SMWDC -> GetNValidPlane();
         MSR          = SMWDC -> GetMSR();
         
	      Bool_t flag = 0;
         for ( Int_t k = 0; k < 6; k++){
	         Res[k]  = SMWDC -> GetResidual(k);
	         MSRi[k] = SMWDC -> GetMSRi(k);// require ProjMatrix
            if ( flag ) continue;
            if ( MSRi[k] / (MSR*2/6*5) < 1e-4 ){
               TrackID = k+1;
               flag = 1;
            }else{
               TrackID = 0;
            }
         }               
         art::TTrack* track = (art::TTrack*)SMWDC->GetTrack();
         x1 = track->GetX();
         y1 = track->GetY();
         a1 = track->GetA();
         b1 = track->GetB();
         if (debugInfo ==1) {
	         printf(" eventID:%5d, X1:%8.2f A1:%7.2f | MSR:%8.5f (",eventID, x1, a1, MSR);
            for (Int_t k=0 ; k < 6; k++){
	            printf(" %f,",MSRi[k]);
	         }
	         printf("), %d\n", TrackID);
	      }
      }


      savefile.cd(); //set focus on this file
      regAna->Fill();
      
     
      if ( eventID%100000 ==0 && eventID != firstEntry){ 
         clock.Stop("timer");
         //printf(" missing Ratio(every 10k):%d/%d =%10.3f \n",count, countCoinRegGate, (Double_t)count/countCoinRegGate*100);
         printf(" eventID:%6d |%10.3fsec\n", eventID, clock.GetRealTime("timer"));
         clock.Start("timer");
      }
      
   }
   
   savefile.cd();
   regAna->Write();
   
   clock.Stop("timer");
   printf("============ finished|%10.3fsec\n",clock.GetRealTime("timer"));
   return ;
}


