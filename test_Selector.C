#define test_Selector_cxx
// The class definition in test_Selector.h has been generated automatically
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
// Root > T->Process("test_Selector.C")
// Root > T->Process("test_Selector.C","some options")
// Root > T->Process("test_Selector.C+")
//

#include "test_Selector.h"
#include <TH2.h>
#include <TH1.h>
#include <TStyle.h>


void test_Selector::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void test_Selector::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t test_Selector::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either test_Selector::GetEntry() or TBranch::GetEntry()
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
   
   //eventID = entry;
   
   //runNum = eventheader0->GetRunNumber();
   
   //fChain->GetEntry(entry); <-- eat RAM fast
   
   //______________________________________________________________
   //Int_t nHit = tof_D1_t->GetEntriesFast();
   b_tof_D1_t->GetEntry(entry);
   
   Double_t tofD1 = kInvalidD;
   for( Int_t p = 0; p < tof_D1_t->GetEntriesFast(); p++){
		tofD1 = ((art::TTimeDifference*)tof_D1_t->At(p))->GetTiming() ;
	}
	if( TMath::Abs(tofD1-35)>2 ) { return kTRUE;}
	
   //______________________________________________________________
   b_vertex->GetEntry(entry);
   Double_t vertexZ = kInvalidD;
   Int_t nHit = vertex->GetEntriesFast();
   for( Int_t p = 0; p < nHit; p++){
		vertexZ = ((art::TTrack*)vertex->At(p))->GetZ();
	}
   if( TMath::Abs(vertexZ-10)>40 ) {return kTRUE;}

   //______________________________________________________________
	b_smwdc_S1->GetEntry(entry);
	Double_t s1x = kInvalidD;
	Int_t nHit = smwdc_S1->GetEntriesFast();
   for( Int_t p = 0; p < nHit; p++){
		s1x = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_S1->At(p))->GetTrack())->GetX();
	}   
	if( TMath::IsNaN(s1x) ) {return kTRUE;}
	if( s1x> 3 ) {return kTRUE;}
   
	//______________________________________________________________
	b_p2p->GetEntry(entry);
	Double_t Ex = p2p->GetSp2()-13.26;	
   if( TMath::IsNaN(Ex) ) {return kTRUE;}
   //printf("%f, %f \n", s1x, Ex);
   
   //______________________________________________________________   
   b_pid_ds->GetEntry(entry);
   Double_t AOQ = pid_ds->GetAOQ(); 
   Double_t pidZ = pid_ds->GetZ(); 
   if( TMath::IsNaN(AOQ) ) {return kTRUE;}
   //if( pidZ<5 ) {return kTRUE;}
   
   
   //______________________________________________________________   
   hist->Fill(AOQ,pidZ);
	hist2->Fill(AOQ, s1x);
	hist3->Fill(Ex, s1x);
	hist4->Fill(pidZ, s1x);
	histvertexZ->Fill(vertexZ);
	
	//if( entry%10000  == 0) printf(" readed entris : %10d [%2.0f%%] \n", entry, entry*100./totnumEntry);
   
   return kTRUE;
}

void test_Selector::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.
   

}

void test_Selector::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
   
   Int_t Div[2] = {3,2};
   Int_t size[2] = {300,300};
	TCanvas * test = new TCanvas("test", "test", 100,0 , size[0]*Div[0], size[1]*Div[1]);
   test->Divide(Div[0],Div[1]);
   
   test->cd(1);
   hist->Draw("colz");
   
   test->cd(2);
   hist2->Draw("colz");
   
   test->cd(3);
   hist3->Draw("colz");
   
   test->cd(6);
   hist3->ProjectionX()->Draw();

	test->cd(4);
   hist4->Draw("colz");

	test->cd(5);
   histvertexZ->Draw("colz");

}
