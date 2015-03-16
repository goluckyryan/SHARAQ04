#define Selector_Nyoki_cxx
// The class definition in Selector_Nyoki.h has been generated automatically
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
// Root > T->Process("Selector_Nyoki.C")
// Root > T->Process("Selector_Nyoki.C","some options")
// Root > T->Process("Selector_Nyoki.C+")
//

#include "Selector_Nyoki.h"
#include <TH2.h>
#include <TStyle.h>


void Selector_Nyoki::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void Selector_Nyoki::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t Selector_Nyoki::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either Selector_Nyoki::GetEntry() or TBranch::GetEntry()
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

	b_nyoki->GetEntry(entry);
	
	Int_t nHit = nyoki->GetEntriesFast();
	h1->Fill(nHit);
	for( Int_t p = 0; p < nHit; p++){
		ID[p] = ((art::TTimingChargeData *) nyoki->At(p))->GetID();
	}
	
	Int_t CoinCount = 0;
	for( Int_t p = 0; p < nHit-1; p++){
		for (Int_t q = 1; q < nHit; q ++){
			//printf("%d, %d , %d %d\n", ID[p], ID[q], ID[p] == ID[q] + 1,  ID[p] == ID[q] - 1 );
			if( ID[p] == ID[q] + 1 ) {
				hMulti->Fill(nHit, ID[p]);
				CoinCount = 1;
			}
			if( ID[p] == ID[q] - 1 ) {
				hMulti->Fill(nHit, ID[q]);
				CoinCount = 1;
			}
		}
	}
	
	if( nHit >= 2){
		h2->Fill(CoinCount);
	}

   return kTRUE;
}

void Selector_Nyoki::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void Selector_Nyoki::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
   
   TCanvas * test = new TCanvas("test", "test", 100, 100, 1200, 400);
   test->Divide(3,1);
   
   test->cd(1);
   h1->Draw("");
   printf("total event: %d \n", h1->GetEntries());
   printf("hit event: %d \n", h1->GetEntries() - h1->GetBinContent(1));
   printf("single event: %d \n", h1->GetBinContent(2));
   printf("Multi-hit event: %d \n", h1->GetEntries()- h1->GetBinContent(1)- h1->GetBinContent(2));

   test->cd(2);
   h2->Draw("colz");
   printf("Multi-hit event: %d \n", h2->GetEntries());
   printf("True Multi event: %d \n", h2->GetBinContent(2));
   printf("Adjacent event: %d \n", h2->GetBinContent(3));
   
   test->cd(3);
   hMulti->Draw("colz");


}
