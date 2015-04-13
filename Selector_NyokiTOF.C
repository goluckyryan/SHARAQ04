#define Selector_NyokiTOF_cxx
// The class definition in Selector_NyokiTOF.h has been generated automatically
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
// Root > T->Process("Selector_NyokiTOF.C")
// Root > T->Process("Selector_NyokiTOF.C","some options")
// Root > T->Process("Selector_NyokiTOF.C+")
//

#include "Selector_NyokiTOF.h"
#include <TH2.h>
#include <TStyle.h>


void Selector_NyokiTOF::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void Selector_NyokiTOF::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t Selector_NyokiTOF::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either Selector_NyokiTOF::GetEntry() or TBranch::GetEntry()
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
   
   //_______________________ gate
   b_gate->GetEntry(entry);
   if( !gate->Test(12)) return kTRUE; 
   
   //______________________________________________________________ S0img
   b_S0img->GetEntry(entry);
   Double_t s0x = TMath::QuietNaN();
   Double_t s0a = TMath::QuietNaN();
   Double_t s0y = TMath::QuietNaN();
   Double_t s0b = TMath::QuietNaN();
   for( Int_t p = 0; p < S0img->GetEntriesFast(); p++){
      s0x = ((art::TTrack*)((art::TMWDCTrackingResult*)S0img->At(p))->GetTrack())->GetX();
      s0a = ((art::TTrack*)((art::TMWDCTrackingResult*)S0img->At(p))->GetTrack())->GetA();
      s0y = ((art::TTrack*)((art::TMWDCTrackingResult*)S0img->At(p))->GetTrack())->GetY();
      s0b = ((art::TTrack*)((art::TMWDCTrackingResult*)S0img->At(p))->GetTrack())->GetB();
   }   
   
   if( TMath::Abs(s0a*1000)>10 ) return kTRUE;
   if( TMath::Abs(s0b*1000)>10 ) return kTRUE;
   
   //_______________________Get TOF(F3-FH9)
   b_tof_DS->GetEntry(entry);
   Double_t tofus= TMath::QuietNaN();
   for( Int_t p = 0; p < tof_DS->GetEntriesFast(); p++){
      Int_t ID = ((art::TTimingChargeData*)tof_DS->At(p))->GetID() ;
      if( ID == 2){
         tofus = ((art::TTimingChargeData*)tof_DS->At(p))->GetTiming() ;
      }
   }
   
   if( TMath::IsNaN(tofus)) return kTRUE;
   tofus = -tofus + 321.15 + 0.354 + 382.18;
   
   //_______________________Get Nyoki TOF(S0D-n7)
   b_tof_D1->GetEntry(entry);
   Double_t tofn7= TMath::QuietNaN();
   for( Int_t p = 0; p < tof_D1->GetEntriesFast(); p++){
      Int_t ID = ((art::TTimingChargeData*)tof_D1->At(p))->GetID() ;
      if( ID == 7){
         tofn7 = ((art::TTimingChargeData*)tof_D1->At(p))->GetTiming() ;
      }
   }
   
   const Double_t timeoffset = -2.06; 
   tofn7 = tofn7 + timeoffset;
   
   if( TMath::IsNaN(tofn7)) return kTRUE;
   
   const Double_t L_F3FH9 = 74075.0; 
   const Double_t L_S0DN =   6276.2; 
   
   
   h1->Fill(tofus*L_S0DN/L_F3FH9, tofn7);
   //g1->Fill(tofus*L_S0DN/L_F3FH9 - tofn7);
   //g1->Fill(tofn7);
   //g1->Fill(tofus*L_S0DN/L_F3FH9/tofn7);
   
   //_______________________
   b_gate->GetEntry(entry);
   
   if( gate->Test(0) ) {         
      h2->Fill(tofus*L_S0DN/L_F3FH9, tofn7);
      g2->Fill(tofus*L_S0DN/L_F3FH9 - tofn7);
      //g2->Fill(tofn7);
      //g2->Fill(tofus*L_S0DN/L_F3FH9);
      //g2->Fill(tofus*L_S0DN/L_F3FH9/tofn7);
   } 
   
   
   if( gate->Test(1)) {
      h3->Fill(tofus*L_S0DN/L_F3FH9, tofn7);
      g3->Fill(tofus*L_S0DN/L_F3FH9 - tofn7);
      //g3->Fill(tofn7);
      //g3->Fill(tofus*L_S0DN/L_F3FH9);
      //g3->Fill(tofus*L_S0DN/L_F3FH9/tofn7);
   } 

   if( gate->Test(2)) {
      h4->Fill(tofus*L_S0DN/L_F3FH9, tofn7);
      g4->Fill(tofus*L_S0DN/L_F3FH9 - tofn7);
      //g4->Fill(tofn7);
      //g4->Fill(tofus*L_S0DN/L_F3FH9);
      //g4->Fill(tofus*L_S0DN/L_F3FH9/tofn7);
   } 
   
   if( gate->Test(6)) {
      h5->Fill(tofus*L_S0DN/L_F3FH9, tofn7);
      g5->Fill(tofus*L_S0DN/L_F3FH9 - tofn7);
      //g5->Fill(tofn7);
      //g5->Fill(tofus*L_S0DN/L_F3FH9);
      //g5->Fill(tofus*L_S0DN/L_F3FH9/tofn7);
   } 

   if( gate->Test(7)) {
      h6->Fill(tofus*L_S0DN/L_F3FH9, tofn7);
      g6->Fill(tofus*L_S0DN/L_F3FH9 - tofn7);
      //g6->Fill(tofn7);
      //g6->Fill(tofus*L_S0DN/L_F3FH9);
      //g6->Fill(tofus*L_S0DN/L_F3FH9/tofn7);
   } 
   
   return kTRUE;
}

void Selector_NyokiTOF::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void Selector_NyokiTOF::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
   
   Int_t size = 600;
   Int_t div[2] = {1,1};
   TCanvas * haha = new TCanvas("haha", "haha", 0, 0, div[0]*size, div[1]*size);
   haha->Divide(div[0], div[1]);
   
   /*
   haha->cd(1); h1->Draw("colz");
   haha->cd(div[0]+1); g1->Draw("colz");

   haha->cd(2); h2->Draw("colz");
   haha->cd(div[0]+2); g2->Draw("colz");

   haha->cd(3); h3->Draw("colz");
   haha->cd(div[0]+3); g3->Draw("colz");

   haha->cd(4); h4->Draw("colz");
   haha->cd(div[0]+4); g4->Draw("colz");

   haha->cd(5); h5->Draw("colz");
   haha->cd(div[0]+5); g5->Draw("colz");

   haha->cd(6); h6->Draw("colz");
   haha->cd(div[0]+6); g6->Draw("colz");
   * */
   
   haha->cd(1);
   g2->Draw();
   g3->SetLineColor(2);g3->Draw("same");
   g4->SetLineColor(3);g4->Draw("same");
   g5->SetLineColor(6);g5->Draw("same");
   g6->SetLineColor(7);g6->Draw("same");
   

}
