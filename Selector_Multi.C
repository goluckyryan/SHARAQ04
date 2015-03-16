#define Selector_haha_cxx
// The class definition in Selector_haha.h has been generated automatically
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
// Root > T->Process("Selector_haha.C")
// Root > T->Process("Selector_haha.C","some options")
// Root > T->Process("Selector_haha.C+")
//

#include "Selector_haha.h"
#include <TH2.h>
#include <TStyle.h>


void Selector_haha::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void Selector_haha::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t Selector_haha::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either Selector_haha::GetEntry() or TBranch::GetEntry()
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
   
      //____________________________Get mwdc time charge and length  
   
   
   //_________________________________________________X1
   b_smwdc_S1_x1->GetEntry(entry);
   Int_t nHit = smwdc_S1_x1->GetEntriesFast();
   //printf("%d----------------------------------X1: \n", entry);
   Int_t Count350 = 0;
   Int_t Count600 = 0;
   for(Int_t p = 0; p < nHit; p++){
      art::TMWDCHitData* data = (art::TMWDCHitData*)smwdc_S1_x1->At(p);
      if( data->GetCharge() > 350 ) Count350 ++ ;
      if( data->GetCharge() > 600 ) Count600 ++ ;
      
      //X1wire[p] = data->GetID();
      //X1driftLength[p] = data->GetDriftLength();
      //X1charge[p]=data->GetCharge();
      //printf("%2.0f(%5.3f)[]%8.2f], ", data->GetID(), data->GetDriftLength(), data->GetCharge());
      //printf("%f, %d, %d \n", data->GetCharge(), Count350X1, Count600X1);
   }
   if ( nHit != 0){
      hx1a->Fill(Count350);
      hx1b->Fill(Count600);
   }  
   
   
   //_________________________________________________X2
   b_smwdc_S1_x2->GetEntry(entry);
   Int_t nHit = smwdc_S1_x2->GetEntriesFast();
   Int_t Count350 = 0;
   Int_t Count600 = 0;
   for(Int_t p = 0; p < nHit; p++){
      art::TMWDCHitData* data = (art::TMWDCHitData*)smwdc_S1_x2->At(p);
      if( data->GetCharge() > 350 ) Count350 ++ ;
      if( data->GetCharge() > 600 ) Count600 ++ ;
   }
   if ( nHit != 0){
      hx2a->Fill(Count350);
      hx2b->Fill(Count600);
   }  

   //_________________________________________________U1
   b_smwdc_S1_u1->GetEntry(entry);
   Int_t nHit = smwdc_S1_u1->GetEntriesFast();
   Int_t Count350 = 0;
   Int_t Count600 = 0;
   for(Int_t p = 0; p < nHit; p++){
      art::TMWDCHitData* data = (art::TMWDCHitData*)smwdc_S1_u1->At(p);
      if( data->GetCharge() > 350 ) Count350 ++ ;
      if( data->GetCharge() > 600 ) Count600 ++ ;
   }
   if ( nHit != 0){
      hu1a->Fill(Count350);
      hu1b->Fill(Count600);
   }  
   

   //_________________________________________________U2
   b_smwdc_S1_u2->GetEntry(entry);
   Int_t nHit = smwdc_S1_u2->GetEntriesFast();
   Int_t Count350 = 0;
   Int_t Count600 = 0;
   for(Int_t p = 0; p < nHit; p++){
      art::TMWDCHitData* data = (art::TMWDCHitData*)smwdc_S1_u2->At(p);
      if( data->GetCharge() > 350 ) Count350 ++ ;
      if( data->GetCharge() > 600 ) Count600 ++ ;
   }
   if ( nHit != 0){
      hu2a->Fill(Count350);
      hu2b->Fill(Count600);
   }  
   
   //_________________________________________________V1
   b_smwdc_S1_v1->GetEntry(entry);
   Int_t nHit = smwdc_S1_v1->GetEntriesFast();
   Int_t Count350 = 0;
   Int_t Count600 = 0;
   for(Int_t p = 0; p < nHit; p++){
      art::TMWDCHitData* data = (art::TMWDCHitData*)smwdc_S1_v1->At(p);
      if( data->GetCharge() > 350 ) Count350 ++ ;
      if( data->GetCharge() > 600 ) Count600 ++ ;
   }
   if ( nHit != 0){
      hv1a->Fill(Count350);
      hv1b->Fill(Count600);
   }  

   //_________________________________________________V2
   b_smwdc_S1_v2->GetEntry(entry);
   Int_t nHit = smwdc_S1_v2->GetEntriesFast();
   Int_t Count350 = 0;
   Int_t Count600 = 0;
   for(Int_t p = 0; p < nHit; p++){
      art::TMWDCHitData* data = (art::TMWDCHitData*)smwdc_S1_v2->At(p);
      if( data->GetCharge() > 350 ) Count350 ++ ;
      if( data->GetCharge() > 600 ) Count600 ++ ;
   }
   if ( nHit != 0){
      hv2a->Fill(Count350);
      hv2b->Fill(Count600);
   }  
   /**/
   /*
   //___________________________________ smwdc
   b_smwdc_S1->GetEntry(entry);
   Int_t nHit = smwdc_S1->GetEntriesFast();
   if( nHit == 0 ) {return kTRUE;}
   
   Double_t wire[6] = {};   
   Double_t s1x, s1a, s1y, s1b ;
   
   Bool_t isGood = 0;
   for(Int_t p = 0; p < nHit; p++){
      art::TMWDCTrackingResult* hoge = (art::TMWDCTrackingResult*)smwdc_S1->At(p);
      isGood = hoge->IsGood();
      if( !isGood) continue;
      art::TTrack* trackResult =  (art::TTrack*)((art::TMWDCTrackingResult*)smwdc_S1->At(p))->GetTrack();
      s1x = trackResult->GetX();
      s1a = trackResult->GetA();
      s1y = trackResult->GetY();
      s1b = trackResult->GetB();

      for( Int_t i = 0; i < 6; i++){
         wire[i] = hoge->GetWireIDAdopted(i); 
      }
   }
   
   if( wire[1] == 0) return kTRUE;
   
   Bool_t Diff = 0;
   
   //___________________________________ smwdc_0
   b_smwdc_S1_0->GetEntry(entry);
   Int_t nHit = smwdc_S1_0->GetEntriesFast();
   if( nHit == 0 ) {return kTRUE;}
   
   Double_t wire_0[6] = {};   
   Double_t s1x_0, s1a_0, s1y_0, s1b_0 ;
   
   Bool_t isGood = 0;
   for(Int_t p = 0; p < nHit; p++){
      art::TMWDCTrackingResult* hoge = (art::TMWDCTrackingResult*)smwdc_S1_0->At(p);
      isGood = hoge->IsGood();
      if( !isGood) continue;
      art::TTrack* trackResult =  (art::TTrack*)((art::TMWDCTrackingResult*)smwdc_S1_0->At(p))->GetTrack();
      s1x_0 = trackResult->GetX();
      s1a_0 = trackResult->GetA();
      s1y_0 = trackResult->GetY();
      s1b_0 = trackResult->GetB();

      for( Int_t i = 0; i < 6; i++){
         wire_0[i] = hoge->GetWireIDAdopted(i); 
         if( wire_0[i] != wire[i]) Diff = 1;
      }
   }
   
   if( Diff == 0) return kTRUE;
   
   //printf("%d_______________________%f, %f\n", entry, s1a_0, s1a);
   
   //for( Int_t i = 0; i < 6; i++){
   //   printf("%d : %d, %d\n", i, wire_0[i], wire[0]);
   //}
   
   
   
   hAux->Fill(s1a_0, s1a);
   */
   
   return kTRUE;
}

void Selector_haha::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void Selector_haha::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
   
   TCanvas* haha = new TCanvas("haha", "haha", 1600, 0, 600, 600);
   haha->Divide(2,3);
   
   haha->cd(1);
   //hAux->Draw("colz");
   hx1b->Draw("");
   hx1a->Draw("same");

   haha->cd(2);
   hx2b->Draw("");
   hx2a->Draw("same");

   haha->cd(3);
   hu1b->Draw("");
   hu1a->Draw("same");

   haha->cd(4);
   hu2b->Draw("");
   hu2a->Draw("same");

   haha->cd(5);
   hv1b->Draw("");
   hv1a->Draw("same");

   haha->cd(6);
   hv2b->Draw("");
   hv2a->Draw("same");/**/


}
