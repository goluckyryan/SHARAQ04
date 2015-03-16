#define Selector_test_cxx
// The class definition in Selector_test.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("Selector_test.C")
// Root > T->Process("Selector_test.C","some options")
// Root > T->Process("Selector_test.C+")
//

#include "Selector_test.h"
#include <TH2.h>
#include <TStyle.h>


void Selector_test::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void Selector_test::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t Selector_test::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either Selector_test::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.

   const Double_t timeGate[2] = {-50,170};
   const Double_t ChargeGate[2] = {350, 99999};
   
   Bool_t debug = 1;
   
   //_________________________________________________ nyoki
   
   if( debug ) printf("%10d=======================\n", entry);
   //_________________________________________________X1
   b_smwdc_S1_x1->GetEntry(entry);
   Int_t nHit = smwdc_S1_x1->GetEntriesFast();
   Int_t wireTemp =0 ;
   Double_t t1 = -500;
   if( debug ) printf(" X1----------------- %d \n", nHit);
   for(Int_t p = 0; p < nHit; p++){
      art::TMWDCHitData* data = (art::TMWDCHitData*)smwdc_S1_x1->At(p);      //X1wire[p] = data->GetID();
      
      if( data->GetCharge() < ChargeGate[0]) continue;
      if( data->GetTiming() < timeGate[0] || data->GetTiming() > timeGate[1]) continue;
      if( debug ) printf("%2.0f, %8.3f, %8.3f, %8.2f \n", data->GetID(), data->GetTiming(), data->GetDriftLength(), data->GetCharge());
      
      //printf("wireTemp:%d, wireID:%d \n", wireTemp, data->GetID());
      if( p > 0 && data->GetID() == wireTemp) {
         g1->Fill(data->GetTiming()-t1, data->GetCharge()); 
      }else{
         wireTemp = data->GetID();
         t1 = data->GetTiming();
      }
      
   }//_________________________________________________X2
   b_smwdc_S1_x2->GetEntry(entry);
   Int_t nHit = smwdc_S1_x2->GetEntriesFast();
   if( debug ) printf(" X2----------------- %d \n", nHit);
   for(Int_t p = 0; p < nHit; p++){
      art::TMWDCHitData* data = (art::TMWDCHitData*)smwdc_S1_x2->At(p); 
      if( data->GetCharge() < ChargeGate[0]) continue;
      if( data->GetTiming() < timeGate[0] || data->GetTiming() > timeGate[1]) continue;
      if( debug ) printf("%2.0f, %8.3f, %8.3f, %8.2f \n", data->GetID(), data->GetTiming(), data->GetDriftLength(), data->GetCharge());
      
      if( p > 0 && data->GetID() == wireTemp) {
         g1->Fill(data->GetTiming()-t1, data->GetCharge()); 
      }else{
         wireTemp = data->GetID();
         t1 = data->GetTiming();
      }
   }
   
   //_________________________________________________U1
   b_smwdc_S1_u1->GetEntry(entry);
   Int_t nHit = smwdc_S1_u1->GetEntriesFast();
   if( debug ) printf(" U1----------------- %d \n", nHit);
   for(Int_t p = 0; p < nHit; p++){
      art::TMWDCHitData* data = (art::TMWDCHitData*)smwdc_S1_u1->At(p);      //X1wire[p] = data->GetID();
      if( data->GetCharge() < ChargeGate[0]) continue;
      if( data->GetTiming() < timeGate[0] || data->GetTiming() > timeGate[1]) continue;
      if( debug ) printf("%2.0f, %8.3f, %8.3f, %8.2f \n", data->GetID(), data->GetTiming(), data->GetDriftLength(), data->GetCharge());
      
      if( p > 0 && data->GetID() == wireTemp) {
         g1->Fill(data->GetTiming()-t1, data->GetCharge()); 
      }else{
         wireTemp = data->GetID();
         t1 = data->GetTiming();
      }
   }

   //_________________________________________________U2
   b_smwdc_S1_u2->GetEntry(entry);
   Int_t nHit = smwdc_S1_u2->GetEntriesFast();
   if( debug ) printf(" U2----------------- %d \n", nHit);
   for(Int_t p = 0; p < nHit; p++){
      art::TMWDCHitData* data = (art::TMWDCHitData*)smwdc_S1_u2->At(p);      //X1wire[p] = data->GetID();
      if( data->GetCharge() < ChargeGate[0]) continue;
      if( data->GetTiming() < timeGate[0] || data->GetTiming() > timeGate[1]) continue;
      if( debug ) printf("%2.0f, %8.3f, %8.3f, %8.2f \n", data->GetID(), data->GetTiming(), data->GetDriftLength(), data->GetCharge());
      
      if( p > 0 && data->GetID() == wireTemp) {
         g1->Fill(data->GetTiming()-t1, data->GetCharge()); 
      }else{
         wireTemp = data->GetID();
         t1 = data->GetTiming();
      }
   }
   
   //_________________________________________________V1
   b_smwdc_S1_v1->GetEntry(entry);
   Int_t nHit = smwdc_S1_v1->GetEntriesFast();
   if( debug ) printf(" V1----------------- %d \n", nHit);
   for(Int_t p = 0; p < nHit; p++){
      art::TMWDCHitData* data = (art::TMWDCHitData*)smwdc_S1_v1->At(p);      //X1wire[p] = data->GetID();
      if( data->GetCharge() < ChargeGate[0]) continue;
      if( data->GetTiming() < timeGate[0] || data->GetTiming() > timeGate[1]) continue;
      if( debug ) printf("%2.0f, %8.3f, %8.3f, %8.2f \n", data->GetID(), data->GetTiming(), data->GetDriftLength(), data->GetCharge());
      
      if( p > 0 && data->GetID() == wireTemp) {
         g1->Fill(data->GetTiming()-t1, data->GetCharge()); 
      }else{
         wireTemp = data->GetID();
         t1 = data->GetTiming();
      }
   }
   
   //_________________________________________________V2
   b_smwdc_S1_v2->GetEntry(entry);
   Int_t nHit = smwdc_S1_v2->GetEntriesFast();
   if( debug ) printf(" V2----------------- %d \n", nHit);
   for(Int_t p = 0; p < nHit; p++){
      art::TMWDCHitData* data = (art::TMWDCHitData*)smwdc_S1_v2->At(p);      //X1wire[p] = data->GetID();
      if( data->GetCharge() < ChargeGate[0]) continue;
      if( data->GetTiming() < timeGate[0] || data->GetTiming() > timeGate[1]) continue;
      if( debug ) printf("%2.0f, %8.3f, %8.3f, %8.2f \n", data->GetID(), data->GetTiming(), data->GetDriftLength(), data->GetCharge());
      
      if( p > 0 && data->GetID() == wireTemp) {
         
         g1->Fill(data->GetTiming()-t1, data->GetCharge()); 
         
         //printf("%7.3f, %7.3f \n", );
      }else{
         wireTemp = data->GetID();
         t1 = data->GetTiming();
      }
   }
   
   //_______________________________________________ SMWDc_S1
   b_smwdc_S1->GetEntry(entry);
   Int_t nHit = smwdc_S1->GetEntriesFast();
   Int_t wireID[6] = {0,0,0,0,0,0};
   Int_t LR[6] = {0,0,0,0,0,0};
   Double_t DL[6] = {20,20,20,20,20,20};
   Double_t res[6] = {20,20,20,20,20,20};
   Double_t CI[4] = {-1,-1,-1,-1};
   if( debug ) printf("__________ Tracking \n");
   for(Int_t p = 0; p < nHit; p++){
      art::TMWDCTrackingResult* hoge = (art::TMWDCTrackingResult*)smwdc_S1->At(p);
      art::TTrack* trackResult =  (art::TTrack*)((art::TMWDCTrackingResult*)smwdc_S1->At(p))->GetTrack();
      Double_t s1x = trackResult->GetX();
      Double_t s1a = trackResult->GetA();
      Double_t s1y = trackResult->GetY();
      Double_t s1b = trackResult->GetB();
      
      if( debug ) printf(" SSR: %7.3f, x:%6.3f, a:%6.3f, y:%6.3f, b:%6.3f\n", hoge->GetSSR(), s1x, s1a, s1y, s1b);
      if( debug ) printf("    CI         x:%6.3f, a:%6.3f, y:%6.3f, b:%6.3f\n", hoge->GetCI(0), hoge->GetCI(1), hoge->GetCI(2), hoge->GetCI(3));
      
      for(Int_t q = 0; q < 6; q++){
         wireID[q] = hoge->GetWireIDAdopted(q);
         //LR[q] = hoge->GetLRAdopted(q);
         DL[q] = hoge->GetDriftLengthAdopted(q);
         res[q] = hoge->GetResidual(q);
      }
      
      for(Int_t q = 0; q < 4; q++){
         CI[q] = hoge->GetCI(q);
      }
      
   }
   
   if( debug ) {
      for(Int_t q = 0; q < 6; q++){printf("%7d, ", wireID[q]);} printf("\n");
      for(Int_t q = 0; q < 6; q++){printf("%7.2f, ", DL[q]);}printf("\n");
   //for(Int_t q = 0; q < 6; q++){printf("%7d, ", LR[q]);}printf("\n");
      for(Int_t q = 0; q < 6; q++){printf("%7.4f, ", res[q]);}printf("\n");
      for(Int_t q = 0; q < 4; q++){printf("%6.3f, ", CI[q]);}printf("\n");
   }
   return kTRUE;
}

void Selector_test::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void Selector_test::Terminate()
{
   
   //TCanvas* haha = new TCanvas("haha", "haha", 2000, 0, 400, 400);
   //g1->Draw("colz");
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
