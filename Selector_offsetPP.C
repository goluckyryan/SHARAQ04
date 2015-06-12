#define Selector_offsetPP_cxx
// The class definition in Selector_offsetPP.h has been generated automatically
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
// Root > T->Process("Selector_offsetPP.C")
// Root > T->Process("Selector_offsetPP.C","some options")
// Root > T->Process("Selector_offsetPP.C+")
//

#include "Selector_offsetPP.h"
#include <TH2.h>
#include <TStyle.h>


void Selector_offsetPP::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void Selector_offsetPP::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t Selector_offsetPP::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either Selector_offsetPP::GetEntry() or TBranch::GetEntry()
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
   
   //-------------------------------
   b_p2p_0000_0000->GetEntry(entry);
   Ex00[5] = p2p_0000_0000->GetSp();
   if( TMath::IsNaN(Ex00[5])) return kTRUE;

   theta1 = p2p_0000_0000->GetRecoilL()->Theta()*TMath::RadToDeg();
   theta2 = p2p_0000_0000->GetRecoilR()->Theta()*TMath::RadToDeg();

   Dtheta = theta1 + theta2;

   phi1 = p2p_0000_0000->GetRecoilL()->Phi()*TMath::RadToDeg();
   phi2 = p2p_0000_0000->GetRecoilR()->Phi()*TMath::RadToDeg();
   
   //printf("b4: %f ", phi2);
   if( phi2 > 90 ) phi2 = phi2 - 180;
   if( phi2 < -90 ) phi2 = phi2 + 180;
   
   //printf("  , %f \n", phi2);
   
   Dphi = phi1-phi2;
   
   //-----------------------------
   b_beamZ->GetEntry(entry);
   vertexZ = TMath::QuietNaN();
   for( Int_t p = 0; p < beamZ->GetEntriesFast(); p++){
      vertexZ = ((art::sh04::TBeamZ*) beamZ->At(p))->GetAverage();
   }
   //if( TMath::Abs(vertexZ-10)>50 || TMath::IsNaN(vertexZ) ) return kTRUE;

   //-------------------------------
   //printf("Ex[5][5] = %4.1f, r_Cry = %d, tofS1 = %4.1f, dcs0d=%d, vZ=%4.1f, Z=%4.1f, A/Q=%4.1f \n", Ex[5][5], gate->Test(11), tofS1, track, vZ, pidZ, pidAOQ );
   count ++;
   
   b_p2p_m500_m500->GetEntry(entry); Exm5[0]  = p2p_m500_m500->GetSp();
   b_p2p_m500_m400->GetEntry(entry); Exm5[1]  = p2p_m500_m400->GetSp();
   b_p2p_m500_m300->GetEntry(entry); Exm5[2]  = p2p_m500_m300->GetSp();
   b_p2p_m500_m200->GetEntry(entry); Exm5[3]  = p2p_m500_m200->GetSp();
   b_p2p_m500_m100->GetEntry(entry); Exm5[4]  = p2p_m500_m100->GetSp();
   b_p2p_m500_0000->GetEntry(entry); Exm5[5]  = p2p_m500_0000->GetSp();
   b_p2p_m500_p100->GetEntry(entry); Exm5[6]  = p2p_m500_p100->GetSp();
   b_p2p_m500_p200->GetEntry(entry); Exm5[7]  = p2p_m500_p200->GetSp();
   b_p2p_m500_p300->GetEntry(entry); Exm5[8]  = p2p_m500_p300->GetSp();
   b_p2p_m500_p400->GetEntry(entry); Exm5[9]  = p2p_m500_p400->GetSp();
   b_p2p_m500_p500->GetEntry(entry); Exm5[10] = p2p_m500_p500->GetSp();
   
   b_p2p_m400_m500->GetEntry(entry); Exm4[0]  = p2p_m400_m500->GetSp();
   b_p2p_m400_m400->GetEntry(entry); Exm4[1]  = p2p_m400_m400->GetSp();
   b_p2p_m400_m300->GetEntry(entry); Exm4[2]  = p2p_m400_m300->GetSp();
   b_p2p_m400_m200->GetEntry(entry); Exm4[3]  = p2p_m400_m200->GetSp();
   b_p2p_m400_m100->GetEntry(entry); Exm4[4]  = p2p_m400_m100->GetSp();
   b_p2p_m400_0000->GetEntry(entry); Exm4[5]  = p2p_m400_0000->GetSp();
   b_p2p_m400_p100->GetEntry(entry); Exm4[6]  = p2p_m400_p100->GetSp();
   b_p2p_m400_p200->GetEntry(entry); Exm4[7]  = p2p_m400_p200->GetSp();
   b_p2p_m400_p300->GetEntry(entry); Exm4[8]  = p2p_m400_p300->GetSp();
   b_p2p_m400_p400->GetEntry(entry); Exm4[9]  = p2p_m400_p400->GetSp();
   b_p2p_m400_p500->GetEntry(entry); Exm4[10] = p2p_m400_p500->GetSp();

   b_p2p_m300_m500->GetEntry(entry); Exm3[0]  = p2p_m300_m500->GetSp();
   b_p2p_m300_m400->GetEntry(entry); Exm3[1]  = p2p_m300_m400->GetSp();
   b_p2p_m300_m300->GetEntry(entry); Exm3[2]  = p2p_m300_m300->GetSp();
   b_p2p_m300_m200->GetEntry(entry); Exm3[3]  = p2p_m300_m200->GetSp();
   b_p2p_m300_m100->GetEntry(entry); Exm3[4]  = p2p_m300_m100->GetSp();
   b_p2p_m300_0000->GetEntry(entry); Exm3[5]  = p2p_m300_0000->GetSp();
   b_p2p_m300_p100->GetEntry(entry); Exm3[6]  = p2p_m300_p100->GetSp();
   b_p2p_m300_p200->GetEntry(entry); Exm3[7]  = p2p_m300_p200->GetSp();
   b_p2p_m300_p300->GetEntry(entry); Exm3[8]  = p2p_m300_p300->GetSp();
   b_p2p_m300_p400->GetEntry(entry); Exm3[9]  = p2p_m300_p400->GetSp();
   b_p2p_m300_p500->GetEntry(entry); Exm3[10] = p2p_m300_p500->GetSp();
   
   b_p2p_m200_m500->GetEntry(entry); Exm2[0]  = p2p_m200_m500->GetSp();
   b_p2p_m200_m400->GetEntry(entry); Exm2[1]  = p2p_m200_m400->GetSp();
   b_p2p_m200_m300->GetEntry(entry); Exm2[2]  = p2p_m200_m300->GetSp();
   b_p2p_m200_m200->GetEntry(entry); Exm2[3]  = p2p_m200_m200->GetSp();
   b_p2p_m200_m100->GetEntry(entry); Exm2[4]  = p2p_m200_m100->GetSp();
   b_p2p_m200_0000->GetEntry(entry); Exm2[5]  = p2p_m200_0000->GetSp();
   b_p2p_m200_p100->GetEntry(entry); Exm2[6]  = p2p_m200_p100->GetSp();
   b_p2p_m200_p200->GetEntry(entry); Exm2[7]  = p2p_m200_p200->GetSp();
   b_p2p_m200_p300->GetEntry(entry); Exm2[8]  = p2p_m200_p300->GetSp();
   b_p2p_m200_p400->GetEntry(entry); Exm2[9]  = p2p_m200_p400->GetSp();
   b_p2p_m200_p500->GetEntry(entry); Exm2[10] = p2p_m200_p500->GetSp();
   
   b_p2p_m100_m500->GetEntry(entry); Exm1[0]  = p2p_m100_m500->GetSp();
   b_p2p_m100_m400->GetEntry(entry); Exm1[1]  = p2p_m100_m400->GetSp();
   b_p2p_m100_m300->GetEntry(entry); Exm1[2]  = p2p_m100_m300->GetSp();
   b_p2p_m100_m200->GetEntry(entry); Exm1[3]  = p2p_m100_m200->GetSp();
   b_p2p_m100_m100->GetEntry(entry); Exm1[4]  = p2p_m100_m100->GetSp();
   b_p2p_m100_0000->GetEntry(entry); Exm1[5]  = p2p_m100_0000->GetSp();
   b_p2p_m100_p100->GetEntry(entry); Exm1[6]  = p2p_m100_p100->GetSp();
   b_p2p_m100_p200->GetEntry(entry); Exm1[7]  = p2p_m100_p200->GetSp();
   b_p2p_m100_p300->GetEntry(entry); Exm1[8]  = p2p_m100_p300->GetSp();
   b_p2p_m100_p400->GetEntry(entry); Exm1[9]  = p2p_m100_p400->GetSp();
   b_p2p_m100_p500->GetEntry(entry); Exm1[10] = p2p_m100_p500->GetSp();
   
   b_p2p_0000_m500->GetEntry(entry); Ex00[0]  = p2p_0000_m500->GetSp();
   b_p2p_0000_m400->GetEntry(entry); Ex00[1]  = p2p_0000_m400->GetSp();
   b_p2p_0000_m300->GetEntry(entry); Ex00[2]  = p2p_0000_m300->GetSp();
   b_p2p_0000_m200->GetEntry(entry); Ex00[3]  = p2p_0000_m200->GetSp();
   b_p2p_0000_m100->GetEntry(entry); Ex00[4]  = p2p_0000_m100->GetSp();
   b_p2p_0000_p100->GetEntry(entry); Ex00[6]  = p2p_0000_p100->GetSp();
   b_p2p_0000_p200->GetEntry(entry); Ex00[7]  = p2p_0000_p200->GetSp();
   b_p2p_0000_p300->GetEntry(entry); Ex00[8]  = p2p_0000_p300->GetSp();
   b_p2p_0000_p400->GetEntry(entry); Ex00[9]  = p2p_0000_p400->GetSp();
   b_p2p_0000_p500->GetEntry(entry); Ex00[10] = p2p_0000_p500->GetSp();
   
   b_p2p_p100_m500->GetEntry(entry); Exp1[0]  = p2p_p100_m500->GetSp();
   b_p2p_p100_m400->GetEntry(entry); Exp1[1]  = p2p_p100_m400->GetSp();
   b_p2p_p100_m300->GetEntry(entry); Exp1[2]  = p2p_p100_m300->GetSp();
   b_p2p_p100_m200->GetEntry(entry); Exp1[3]  = p2p_p100_m200->GetSp();
   b_p2p_p100_m100->GetEntry(entry); Exp1[4]  = p2p_p100_m100->GetSp();
   b_p2p_p100_0000->GetEntry(entry); Exp1[5]  = p2p_p100_0000->GetSp();
   b_p2p_p100_p100->GetEntry(entry); Exp1[6]  = p2p_p100_p100->GetSp();
   b_p2p_p100_p200->GetEntry(entry); Exp1[7]  = p2p_p100_p200->GetSp();
   b_p2p_p100_p300->GetEntry(entry); Exp1[8]  = p2p_p100_p300->GetSp();
   b_p2p_p100_p400->GetEntry(entry); Exp1[9]  = p2p_p100_p400->GetSp();
   b_p2p_p100_p500->GetEntry(entry); Exp1[10] = p2p_p100_p500->GetSp();
   
   b_p2p_p200_m500->GetEntry(entry); Exp2[0]  = p2p_p200_m500->GetSp();
   b_p2p_p200_m400->GetEntry(entry); Exp2[1]  = p2p_p200_m400->GetSp();
   b_p2p_p200_m300->GetEntry(entry); Exp2[2]  = p2p_p200_m300->GetSp();
   b_p2p_p200_m200->GetEntry(entry); Exp2[3]  = p2p_p200_m200->GetSp();
   b_p2p_p200_m100->GetEntry(entry); Exp2[4]  = p2p_p200_m100->GetSp();
   b_p2p_p200_0000->GetEntry(entry); Exp2[5]  = p2p_p200_0000->GetSp();
   b_p2p_p200_p100->GetEntry(entry); Exp2[6]  = p2p_p200_p100->GetSp();
   b_p2p_p200_p200->GetEntry(entry); Exp2[7]  = p2p_p200_p200->GetSp();
   b_p2p_p200_p300->GetEntry(entry); Exp2[8]  = p2p_p200_p300->GetSp();
   b_p2p_p200_p400->GetEntry(entry); Exp2[9]  = p2p_p200_p400->GetSp();
   b_p2p_p200_p500->GetEntry(entry); Exp2[10] = p2p_p200_p500->GetSp();
   
   b_p2p_p300_m500->GetEntry(entry); Exp3[0]  = p2p_p300_m500->GetSp();
   b_p2p_p300_m400->GetEntry(entry); Exp3[1]  = p2p_p300_m400->GetSp();
   b_p2p_p300_m300->GetEntry(entry); Exp3[2]  = p2p_p300_m300->GetSp();
   b_p2p_p300_m200->GetEntry(entry); Exp3[3]  = p2p_p300_m200->GetSp();
   b_p2p_p300_m100->GetEntry(entry); Exp3[4]  = p2p_p300_m100->GetSp();
   b_p2p_p300_0000->GetEntry(entry); Exp3[5]  = p2p_p300_0000->GetSp();
   b_p2p_p300_p100->GetEntry(entry); Exp3[6]  = p2p_p300_p100->GetSp();
   b_p2p_p300_p200->GetEntry(entry); Exp3[7]  = p2p_p300_p200->GetSp();
   b_p2p_p300_p300->GetEntry(entry); Exp3[8]  = p2p_p300_p300->GetSp();
   b_p2p_p300_p400->GetEntry(entry); Exp3[9]  = p2p_p300_p400->GetSp();
   b_p2p_p300_p500->GetEntry(entry); Exp3[10] = p2p_p300_p500->GetSp();
   
   b_p2p_p400_m500->GetEntry(entry); Exp4[0]  = p2p_p400_m500->GetSp();
   b_p2p_p400_m400->GetEntry(entry); Exp4[1]  = p2p_p400_m400->GetSp();
   b_p2p_p400_m300->GetEntry(entry); Exp4[2]  = p2p_p400_m300->GetSp();
   b_p2p_p400_m200->GetEntry(entry); Exp4[3]  = p2p_p400_m200->GetSp();
   b_p2p_p400_m100->GetEntry(entry); Exp4[4]  = p2p_p400_m100->GetSp();
   b_p2p_p400_0000->GetEntry(entry); Exp4[5]  = p2p_p400_0000->GetSp();
   b_p2p_p400_p100->GetEntry(entry); Exp4[6]  = p2p_p400_p100->GetSp();
   b_p2p_p400_p200->GetEntry(entry); Exp4[7]  = p2p_p400_p200->GetSp();
   b_p2p_p400_p300->GetEntry(entry); Exp4[8]  = p2p_p400_p300->GetSp();
   b_p2p_p400_p400->GetEntry(entry); Exp4[9]  = p2p_p400_p400->GetSp();
   b_p2p_p400_p500->GetEntry(entry); Exp4[10] = p2p_p400_p500->GetSp();
   
   b_p2p_p500_m500->GetEntry(entry); Exp5[0]  = p2p_p500_m500->GetSp();
   b_p2p_p500_m400->GetEntry(entry); Exp5[1]  = p2p_p500_m400->GetSp();
   b_p2p_p500_m300->GetEntry(entry); Exp5[2]  = p2p_p500_m300->GetSp();
   b_p2p_p500_m200->GetEntry(entry); Exp5[3]  = p2p_p500_m200->GetSp();
   b_p2p_p500_m100->GetEntry(entry); Exp5[4]  = p2p_p500_m100->GetSp();
   b_p2p_p500_0000->GetEntry(entry); Exp5[5]  = p2p_p500_0000->GetSp();
   b_p2p_p500_p100->GetEntry(entry); Exp5[6]  = p2p_p500_p100->GetSp();
   b_p2p_p500_p200->GetEntry(entry); Exp5[7]  = p2p_p500_p200->GetSp();
   b_p2p_p500_p300->GetEntry(entry); Exp5[8]  = p2p_p500_p300->GetSp();
   b_p2p_p500_p400->GetEntry(entry); Exp5[9]  = p2p_p500_p400->GetSp();
   b_p2p_p500_p500->GetEntry(entry); Exp5[10] = p2p_p500_p500->GetSp();
   
   //______________________________________________________________   
   saveFile->cd(); //set focus on this file
   newTree->Fill();  

   clock.Stop("timer");
   Double_t time = clock.GetRealTime("timer");
   clock.Start("timer");
   if ( !shown ) {
      if (fmod(time, 10) < 1 ){
         printf( "%10d[%2d%%] |%3d min %5.2f sec | expect:%5.1fmin %10d\n", 
               entry, 
               TMath::Nint((entry+1)*100./totnumEntry),
               TMath::Floor(time/60), time - TMath::Floor(time/60)*60,
               totnumEntry*time/(entry+1)/60.,
               count);
               shown = 1;
      }
   }else{
      if (fmod(time, 10) > 9 ){
         shown = 0;
      }
   }
   


   return kTRUE;
}

void Selector_offsetPP::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void Selector_offsetPP::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
   saveFile->cd(); //set focus on this file
   newTree->Write(); 
   saveFile->Close();

   printf("-------------- done. %s, %d\n", saveFileName.Data(), count);
}
