#define PostSelector_cxx
// The class definition in PostSelector.h has been generated automatically
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
// Root > T->Process("PostSelector.C")
// Root > T->Process("PostSelector.C","some options")
// Root > T->Process("PostSelector.C+")
//

#include "PostSelector.h"
#include <TH2.h>
#include <TStyle.h>


void PostSelector::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void PostSelector::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t PostSelector::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either PostSelector::GetEntry() or TBranch::GetEntry()
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
   
   
   //fChain->GetEntry(entry); <-- eat RAM fast
   
   //______________________________________________________________ eventID
   eventID = entry;
   
   //______________________________________________________________ run number
   runNum = eventheader0->GetRunNumber();
   
   //______________________________________________________________ gate Num
   if( gate->Test(9) == 1) {gateNum = 1;}
   if( gate->Test(11) == 1 && !gate->Test(9)) {gateNum = 2;}
   
   //______________________________________________________________ FH9
   /*b_plaV1190_FH9->GetEntry(entry);
   b_tof_US->GetEntry(entry);
	for( Int_t p = 0; p < plaV1190_FH9 -> GetEntriesFast(); p++){
		Int_t HitID  = ((art::TTimeDifference*)plaV1190_FH9->At(p))->GetHitID();
		tofFH9  = ((art::TTimeDifference*)plaV1190_FH9->At(p))->GetTiming();
		QFH9 = ((art::TTwoSidedPlasticData*) tof_US->At(HitID-1))->GetCharge();
		if( TMath::Abs(tofFH9+1463)<3 ) break;
	}
   */
   //______________________________________________________________ tofS1
   b_tof_D1_t->GetEntry(entry);
   for( Int_t p = 0; p < tof_D1_t->GetEntriesFast(); p++){
		tofS1 = ((art::TTimeDifference*)tof_D1_t->At(p))->GetTiming() ;
	}
	//if( TMath::Abs(tofS1-35) > 15 ) {return kTRUE;}
	
	//______________________________________________________________ NyokiQ_t = QS1
   b_nyoki_t->GetEntry(entry);
   for( Int_t p = 0; p < nyoki_t->GetEntriesFast(); p++){
		QS1 = ((art::TTimingChargeData*)nyoki_t->At(p))->GetCharge() ;
	}
	
	//______________________________________________________________ S0img
	b_S0img->GetEntry(entry);
   for( Int_t p = 0; p < S0img->GetEntriesFast(); p++){
		s0x = ((art::TTrack*)((art::TMWDCTrackingResult*)S0img->At(p))->GetTrack())->GetX();
		//s1a = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_S1->At(p))->GetTrack())->GetA();
		s0y = ((art::TTrack*)((art::TMWDCTrackingResult*)S0img->At(p))->GetTrack())->GetY();
		//s1b = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_S1->At(p))->GetTrack())->GetB();
	}   
	
   //______________________________________________________________ vertex Z
   b_vertex->GetEntry(entry);
   for( Int_t p = 0; p < vertex->GetEntriesFast(); p++){
		vertexZ = ((art::TTrack*)vertex->At(p))->GetZ();
	}
   //if( TMath::Abs(vertexZ-10)>40 ) {return kTRUE;}

   //______________________________________________________________ MWDC-S1
	b_smwdc_S1->GetEntry(entry);
   for( Int_t p = 0; p < smwdc_S1->GetEntriesFast(); p++){
		s1x = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_S1->At(p))->GetTrack())->GetX();
		s1a = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_S1->At(p))->GetTrack())->GetA();
		s1y = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_S1->At(p))->GetTrack())->GetY();
		s1b = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_S1->At(p))->GetTrack())->GetB();
	}   
	//if( TMath::IsNaN(s1x) ) {return kTRUE;}
	//if( s1x> 3 ) {return kTRUE;}
	
   //______________________________________________________________ PID downstream
   b_pid_ds->GetEntry(entry);
   pidAOQ = pid_ds->GetAOQ(); 
   pidZ = pid_ds->GetZ(); 
   //if( TMath::IsNaN(pidAOQ) ) {return kTRUE;}
   //if( pidZ<5 ) {return kTRUE;}
   
	//______________________________________________________________ p2p
	b_p2p->GetEntry(entry);
	E1 = p2p->GetRecoilL()->E()-938.272;
	E2 = p2p->GetRecoilR()->E()-938.272;
	
	if( E1 > 400 || E2 > 400 ) {return kTRUE;}
	
	
	kMomt = p2p->GetResidual()->P();
	if( kMomt > 2000 )  {return kTRUE;}
	
	theta1 = p2p->GetRecoilL()->Theta()*TMath::RadToDeg();
	phi1 = p2p->GetRecoilL()->Phi()*TMath::RadToDeg();
	
	theta2 = p2p->GetRecoilR()->Theta()*TMath::RadToDeg();
	phi2 = p2p->GetRecoilR()->Phi()*TMath::RadToDeg();
	
	Ex = p2p->GetSp2()-13.26;	
   //if( TMath::IsNaN(Ex) ) {return kTRUE;}
   //printf("%f, %f \n", s1x, Ex);
   
   //______________________________________________________________ p2p_c
	b_p2p_c->GetEntry(entry);
	
	theta1c = p2p_c->GetRecoilL()->Theta()*TMath::RadToDeg();
	phi1c = p2p_c->GetRecoilL()->Phi()*TMath::RadToDeg();
	
	theta2c = p2p_c->GetRecoilR()->Theta()*TMath::RadToDeg();
	phi2c = p2p_c->GetRecoilR()->Phi()*TMath::RadToDeg();
	
	Exc = p2p_c->GetSp2()-13.26;
	kMomtc = p2p_c->GetResidual()->P();
   
   //______________________________________________________________   
   saveFile->cd(); //set focus on this file
   newTree->Fill();  
   
   if( entry%1000000  == 0) printf(" readed entris : %10d [%2.0f%%] \n", entry, entry*100./totnumEntry);

   return kTRUE;
}

void PostSelector::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void PostSelector::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
	
	saveFile->cd(); //set focus on this file
   newTree->Write(); 
   saveFile->Close();
}
