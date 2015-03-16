#define Selector_Aux_cxx
// The class definition in Selector_Aux.h has been generated automatically
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
// Root > T->Process("Selector_Aux.C")
// Root > T->Process("Selector_Aux.C","some options")
// Root > T->Process("Selector_Aux.C+")
//

#include "Selector_Aux.h"
#include <TH2.h>
#include <TStyle.h>


void Selector_Aux::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void Selector_Aux::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t Selector_Aux::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either Selector_Aux::GetEntry() or TBranch::GetEntry()
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
   
   Double_t wireZ[6] = {-40, -24, -8, 8, 24, 40};
   Double_t center[6]={28.375, 28.625, 22.375, 22.625, 22.375, 22.625};
   Double_t cell = 20;
   Double_t angle[6] ={0, 0, -36.8699, -36.8699, 36.8699, 36.8699};
   
   Bool_t debug =0;
      
   /*
   //___________________get SMWDC
   b_smwdc_S1->GetEntry(entry);
   Int_t nHit = smwdc_S1->GetEntriesFast();
   if( nHit == 0 ) {return kTRUE;}
   
   Double_t wirePos[6] = {};
   Double_t trackPos[6] = {};
   Double_t DL[6] = {};
   
   Double_t s1x, s1a, s1y, s1b ;
   Double_t s1A, s1B;
   
   Bool_t isGood = 0;
   for(Int_t p = 0; p < nHit; p++){
      art::TMWDCTrackingResult* hoge = (art::TMWDCTrackingResult*)smwdc_S1->At(p);
      if( hoge->GetNPlaneValid() != 6) continue;
      isGood = hoge->IsGood();
      if( !isGood) continue;
      art::TTrack* trackResult =  (art::TTrack*)((art::TMWDCTrackingResult*)smwdc_S1->At(p))->GetTrack();
      s1x = trackResult->GetX();
      s1a = trackResult->GetA();
      s1y = trackResult->GetY();
      s1b = trackResult->GetB();
      s1A = s1a+s1b;
      s1B = s1a-s1b;

      //if( abs(s1a) > 1) continue;
      
      if(debug) printf("%d_______________________________\n", entry);
      
      for( Int_t i = 0; i < 6; i++){
         Int_t wireID = hoge->GetWireIDAdopted(i); 
         DL[i] = hoge->GetDriftLengthAdopted(i);
         wirePos[i] = (wireID-center[i])*cell;
         trackPos[i] = (s1x + wireZ[i]*s1a)*cos(angle[i]*TMath::DegToRad())+(s1y + wireZ[i]*s1b)*sin(angle[i]*TMath::DegToRad());
         
         if(debug)printf("%d: wireID:%d , wirePos:%5.1f - trackPos:%5.1f = %6.1f, DL:%5.1f, (x,a,y,b):(%5.3f,%5.3f,%5.3f,%5.3f)\n", 
            i, 
            wireID, 
            wirePos[i], 
            trackPos[i], 
            wirePos[i]-trackPos[i], 
            DL[i],
            s1x,
            s1a,
            s1y,
            s1b);
         
      }
   }
   if(!isGood) return kTRUE;
   
   if( wireID[0] == 29 || wireID[1]==29) return kTRUE;
   
   if( abs(s1A+0.2) < 0.2 && abs(s1B+0.2)<0.2){
      h1->Fill(DL[1], DL[0]);
      //h2->Fill(wireID[1],wireID[0]);
      h3->Fill(wirePos[0]-trackPos[0],wirePos[1]-trackPos[1]);
      /*h2->Fill(TMath::Abs(wirePos[1]-trackPos[1]), DL[1]);
      h3->Fill(TMath::Abs(wirePos[2]-trackPos[2]), DL[2]);
      h4->Fill(TMath::Abs(wirePos[3]-trackPos[3]), DL[3]);
      h5->Fill(TMath::Abs(wirePos[4]-trackPos[4]), DL[4]);
      h6->Fill(TMath::Abs(wirePos[5]-trackPos[5]), DL[5]);
   }else{
      h7->Fill(DL[1], DL[0]);
      //h8->Fill(wireID[1],wireID[0]);
      h9->Fill(wirePos[0]-trackPos[0],wirePos[1]-trackPos[1]);
      /*h8->Fill(TMath::Abs(wirePos[1]-trackPos[1]), DL[1]);
      h9->Fill(TMath::Abs(wirePos[2]-trackPos[2]), DL[2]);
      h10->Fill(TMath::Abs(wirePos[3]-trackPos[3]), DL[3]);
      h11->Fill(TMath::Abs(wirePos[4]-trackPos[4]), DL[4]);
      h12->Fill(TMath::Abs(wirePos[5]-trackPos[5]), DL[5]);
   }
   */
   
   //___________________get Raw DATA
   b_smwdc_S1_x1->GetEntry(entry);
   Int_t Count750 = 0;
   
   Int_t nHit = smwdc_S1_x1->GetEntriesFast();
   if( nHit == 0) return kTRUE;
   for(Int_t p = 0; p < nHit; p++){
      art::TMWDCHitData* data = (art::TMWDCHitData*)smwdc_S1_x1->At(p);
      if( data->GetCharge() > 750) Count750 ++;
      //X1wire[p] = data->GetID();
      //X1driftLength[p] = data->GetDriftLength();
      //X1charge[p]=data->GetCharge();
      h1->Fill(data->GetID(), data->GetCharge());
      //printf("%2.0f, %5.3f, %8.2f \n", data->GetID(), data->GetDriftLength(), data->GetCharge());
   }
   
   g1->Fill(Count750);
   g2->Fill(nHit);
   g3->Fill(nHit-Count750);

   return kTRUE;
}

void Selector_Aux::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void Selector_Aux::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
   TCanvas* Aux = new TCanvas("Aux", "Aux", 0,100, 600,300);
   Aux->Divide(3,1);
   
   Aux->cd(1); h1->Draw("colz");
   //Aux->cd(2); h2->Draw("colz");
   Aux->cd(2); g1->Draw("colz"); g2->Draw("same");
   Aux->cd(3); g3->Draw("colz");
   //Aux->cd(5); h5->Draw("colz");
   //Aux->cd(6); h6->Draw("colz");
   
   //Aux->cd(3); h7->Draw("colz");
   //Aux->cd(8); h8->Draw("colz");
   //Aux->cd(4); h9->Draw("colz");
   //Aux->cd(10); h10->Draw("colz");
   //Aux->cd(11); h11->Draw("colz");
   //Aux->cd(12); h12->Draw("colz");*/
   
}
