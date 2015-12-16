#define Selector_offset_cxx
// The class definition in Selector_offset.h has been generated automatically
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
// Root > T->Process("Selector_offset.C")
// Root > T->Process("Selector_offset.C","some options")
// Root > T->Process("Selector_offset.C+")
//

#include "Selector_offset.h"
#include <TH2.h>
#include <TStyle.h>


void Selector_offset::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void Selector_offset::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t Selector_offset::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either Selector_offset::GetEntry() or TBranch::GetEntry()
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
   
   //Double_t Sp = 13.26; //23F
   Double_t Sp = 14.43; //25F
   
   //-------------------------------
   b_p2p->GetEntry(entry);
   Ex00[5] = p2p->GetSp2()-Sp;
   if( TMath::IsNaN(Ex00[5])) return kTRUE;
   
   //-----------------------------
   b_gate->GetEntry(entry);
   if( !gate->Test(11) ) return kTRUE;
   
   //------------------------------
   b_tof_s1->GetEntry(entry);
   tofS1 = TMath::QuietNaN();
   for( Int_t p = 0; p < tof_s1->GetEntriesFast(); p++){
      tofS1 = ((art::TTimingData*)tof_s1->At(p))->GetTiming();
   }
   //if( tofS1< 32 || tofS1 > 35 || TMath::IsNaN(tofS1)) return kTRUE; //23F
   if( tofS1< 35 || tofS1 > 39 || TMath::IsNaN(tofS1)) return kTRUE; //25F
   
   //------------------------------
   b_dcs0d->GetEntry(entry);
   Int_t track = 0;
   for( Int_t p = 0; p< dcs0d->GetEntriesFast(); p++){
      track = ((art::TMWDCTrackingResult*) dcs0d->At(p))->IsGood();
   }
   //printf("track:%d \n", track);
   if( track == 0 ) return kTRUE;
   
   //-----------------------------
   b_vertex->GetEntry(entry);
   vertexZ = TMath::QuietNaN();
   for( Int_t p = 0; p < vertex->GetEntriesFast(); p++){
      vertexZ = ((art::TTrack*) vertex->At(p))->GetZ();
   }
   //printf("vZ:%6.1f \n", vZ);
   //if( TMath::Abs(vZ-10)>30 || TMath::IsNaN(vZ) ) return kTRUE;
   
   //-----------------------------
   //b_nyoki_zt->GetEntry(entry);
   //Double_t pidZ = TMath::QuietNaN();
   //for( Int_t p = 0; p < nyoki_zt->GetEntriesFast(); p++){
   //   pidZ = ((art::TTimingChargeData*) nyoki_zt->At(p))->GetCharge();
   //}
   ////printf("pidZ:%6.1f \n", pidZ);
   //if( TMath::Abs(pidZ-8.0)>0.6 || TMath::IsNaN(pidZ)) return kTRUE;
   
   //-----------------------------
   b_pid_s1->GetEntry(entry);
   pidAOQ = TMath::QuietNaN();
   pidAOQ = pid_s1->GetAOQ();
   
   pidAOQ = 1.05522*pidAOQ-0.0402106*tofS1+1.37253; //25F
   //if( TMath::Abs(pidAOQ*8-22)<0.5 || TMath::IsNaN(pidAOQ) ) return kTRUE;
   pidZ = TMath::QuietNaN();
   pidZ = pid_s1->GetZ();
   //if( TMath::Abs(pidZ-8.0)>0.6 || TMath::IsNaN(pidZ)) return kTRUE;
   if( TMath::Abs(pidZ-8.0)>4.0 || TMath::IsNaN(pidZ)) return kTRUE;
   
   
   //-------------------------------
   //printf("Ex[5][5] = %4.1f, r_Cry = %d, tofS1 = %4.1f, dcs0d=%d, vZ=%4.1f, Z=%4.1f, A/Q=%4.1f \n", Ex[5][5], gate->Test(11), tofS1, track, vZ, pidZ, pidAOQ );
   count ++;
   
   b_p2p_m500_m500->GetEntry(entry); Exm5[0]  = p2p_m500_m500->GetSp2()-Sp;
   b_p2p_m500_m400->GetEntry(entry); Exm5[1]  = p2p_m500_m400->GetSp2()-Sp;
   b_p2p_m500_m300->GetEntry(entry); Exm5[2]  = p2p_m500_m300->GetSp2()-Sp;
   b_p2p_m500_m200->GetEntry(entry); Exm5[3]  = p2p_m500_m200->GetSp2()-Sp;
   b_p2p_m500_m100->GetEntry(entry); Exm5[4]  = p2p_m500_m100->GetSp2()-Sp;
   b_p2p_m500_0000->GetEntry(entry); Exm5[5]  = p2p_m500_0000->GetSp2()-Sp;
   b_p2p_m500_p100->GetEntry(entry); Exm5[6]  = p2p_m500_p100->GetSp2()-Sp;
   b_p2p_m500_p200->GetEntry(entry); Exm5[7]  = p2p_m500_p200->GetSp2()-Sp;
   b_p2p_m500_p300->GetEntry(entry); Exm5[8]  = p2p_m500_p300->GetSp2()-Sp;
   b_p2p_m500_p400->GetEntry(entry); Exm5[9]  = p2p_m500_p400->GetSp2()-Sp;
   b_p2p_m500_p500->GetEntry(entry); Exm5[10] = p2p_m500_p500->GetSp2()-Sp;
   
   b_p2p_m400_m500->GetEntry(entry); Exm4[0]  = p2p_m400_m500->GetSp2()-Sp;
   b_p2p_m400_m400->GetEntry(entry); Exm4[1]  = p2p_m400_m400->GetSp2()-Sp;
   b_p2p_m400_m300->GetEntry(entry); Exm4[2]  = p2p_m400_m300->GetSp2()-Sp;
   b_p2p_m400_m200->GetEntry(entry); Exm4[3]  = p2p_m400_m200->GetSp2()-Sp;
   b_p2p_m400_m100->GetEntry(entry); Exm4[4]  = p2p_m400_m100->GetSp2()-Sp;
   b_p2p_m400_0000->GetEntry(entry); Exm4[5]  = p2p_m400_0000->GetSp2()-Sp;
   b_p2p_m400_p100->GetEntry(entry); Exm4[6]  = p2p_m400_p100->GetSp2()-Sp;
   b_p2p_m400_p200->GetEntry(entry); Exm4[7]  = p2p_m400_p200->GetSp2()-Sp;
   b_p2p_m400_p300->GetEntry(entry); Exm4[8]  = p2p_m400_p300->GetSp2()-Sp;
   b_p2p_m400_p400->GetEntry(entry); Exm4[9]  = p2p_m400_p400->GetSp2()-Sp;
   b_p2p_m400_p500->GetEntry(entry); Exm4[10] = p2p_m400_p500->GetSp2()-Sp;

   b_p2p_m300_m500->GetEntry(entry); Exm3[0]  = p2p_m300_m500->GetSp2()-Sp;
   b_p2p_m300_m400->GetEntry(entry); Exm3[1]  = p2p_m300_m400->GetSp2()-Sp;
   b_p2p_m300_m300->GetEntry(entry); Exm3[2]  = p2p_m300_m300->GetSp2()-Sp;
   b_p2p_m300_m200->GetEntry(entry); Exm3[3]  = p2p_m300_m200->GetSp2()-Sp;
   b_p2p_m300_m100->GetEntry(entry); Exm3[4]  = p2p_m300_m100->GetSp2()-Sp;
   b_p2p_m300_0000->GetEntry(entry); Exm3[5]  = p2p_m300_0000->GetSp2()-Sp;
   b_p2p_m300_p100->GetEntry(entry); Exm3[6]  = p2p_m300_p100->GetSp2()-Sp;
   b_p2p_m300_p200->GetEntry(entry); Exm3[7]  = p2p_m300_p200->GetSp2()-Sp;
   b_p2p_m300_p300->GetEntry(entry); Exm3[8]  = p2p_m300_p300->GetSp2()-Sp;
   b_p2p_m300_p400->GetEntry(entry); Exm3[9]  = p2p_m300_p400->GetSp2()-Sp;
   b_p2p_m300_p500->GetEntry(entry); Exm3[10] = p2p_m300_p500->GetSp2()-Sp;
   
   b_p2p_m200_m500->GetEntry(entry); Exm2[0]  = p2p_m200_m500->GetSp2()-Sp;
   b_p2p_m200_m400->GetEntry(entry); Exm2[1]  = p2p_m200_m400->GetSp2()-Sp;
   b_p2p_m200_m300->GetEntry(entry); Exm2[2]  = p2p_m200_m300->GetSp2()-Sp;
   b_p2p_m200_m200->GetEntry(entry); Exm2[3]  = p2p_m200_m200->GetSp2()-Sp;
   b_p2p_m200_m100->GetEntry(entry); Exm2[4]  = p2p_m200_m100->GetSp2()-Sp;
   b_p2p_m200_0000->GetEntry(entry); Exm2[5]  = p2p_m200_0000->GetSp2()-Sp;
   b_p2p_m200_p100->GetEntry(entry); Exm2[6]  = p2p_m200_p100->GetSp2()-Sp;
   b_p2p_m200_p200->GetEntry(entry); Exm2[7]  = p2p_m200_p200->GetSp2()-Sp;
   b_p2p_m200_p300->GetEntry(entry); Exm2[8]  = p2p_m200_p300->GetSp2()-Sp;
   b_p2p_m200_p400->GetEntry(entry); Exm2[9]  = p2p_m200_p400->GetSp2()-Sp;
   b_p2p_m200_p500->GetEntry(entry); Exm2[10] = p2p_m200_p500->GetSp2()-Sp;
   
   b_p2p_m100_m500->GetEntry(entry); Exm1[0]  = p2p_m100_m500->GetSp2()-Sp;
   b_p2p_m100_m400->GetEntry(entry); Exm1[1]  = p2p_m100_m400->GetSp2()-Sp;
   b_p2p_m100_m300->GetEntry(entry); Exm1[2]  = p2p_m100_m300->GetSp2()-Sp;
   b_p2p_m100_m200->GetEntry(entry); Exm1[3]  = p2p_m100_m200->GetSp2()-Sp;
   b_p2p_m100_m100->GetEntry(entry); Exm1[4]  = p2p_m100_m100->GetSp2()-Sp;
   b_p2p_m100_0000->GetEntry(entry); Exm1[5]  = p2p_m100_0000->GetSp2()-Sp;
   b_p2p_m100_p100->GetEntry(entry); Exm1[6]  = p2p_m100_p100->GetSp2()-Sp;
   b_p2p_m100_p200->GetEntry(entry); Exm1[7]  = p2p_m100_p200->GetSp2()-Sp;
   b_p2p_m100_p300->GetEntry(entry); Exm1[8]  = p2p_m100_p300->GetSp2()-Sp;
   b_p2p_m100_p400->GetEntry(entry); Exm1[9]  = p2p_m100_p400->GetSp2()-Sp;
   b_p2p_m100_p500->GetEntry(entry); Exm1[10] = p2p_m100_p500->GetSp2()-Sp;
   
   b_p2p_0000_m500->GetEntry(entry); Ex00[0]  = p2p_0000_m500->GetSp2()-Sp;
   b_p2p_0000_m400->GetEntry(entry); Ex00[1]  = p2p_0000_m400->GetSp2()-Sp;
   b_p2p_0000_m300->GetEntry(entry); Ex00[2]  = p2p_0000_m300->GetSp2()-Sp;
   b_p2p_0000_m200->GetEntry(entry); Ex00[3]  = p2p_0000_m200->GetSp2()-Sp;
   b_p2p_0000_m100->GetEntry(entry); Ex00[4]  = p2p_0000_m100->GetSp2()-Sp;
   b_p2p_0000_p100->GetEntry(entry); Ex00[6]  = p2p_0000_p100->GetSp2()-Sp;
   b_p2p_0000_p200->GetEntry(entry); Ex00[7]  = p2p_0000_p200->GetSp2()-Sp;
   b_p2p_0000_p300->GetEntry(entry); Ex00[8]  = p2p_0000_p300->GetSp2()-Sp;
   b_p2p_0000_p400->GetEntry(entry); Ex00[9]  = p2p_0000_p400->GetSp2()-Sp;
   b_p2p_0000_p500->GetEntry(entry); Ex00[10] = p2p_0000_p500->GetSp2()-Sp;
   
   b_p2p_p100_m500->GetEntry(entry); Exp1[0]  = p2p_p100_m500->GetSp2()-Sp;
   b_p2p_p100_m400->GetEntry(entry); Exp1[1]  = p2p_p100_m400->GetSp2()-Sp;
   b_p2p_p100_m300->GetEntry(entry); Exp1[2]  = p2p_p100_m300->GetSp2()-Sp;
   b_p2p_p100_m200->GetEntry(entry); Exp1[3]  = p2p_p100_m200->GetSp2()-Sp;
   b_p2p_p100_m100->GetEntry(entry); Exp1[4]  = p2p_p100_m100->GetSp2()-Sp;
   b_p2p_p100_0000->GetEntry(entry); Exp1[5]  = p2p_p100_0000->GetSp2()-Sp;
   b_p2p_p100_p100->GetEntry(entry); Exp1[6]  = p2p_p100_p100->GetSp2()-Sp;
   b_p2p_p100_p200->GetEntry(entry); Exp1[7]  = p2p_p100_p200->GetSp2()-Sp;
   b_p2p_p100_p300->GetEntry(entry); Exp1[8]  = p2p_p100_p300->GetSp2()-Sp;
   b_p2p_p100_p400->GetEntry(entry); Exp1[9]  = p2p_p100_p400->GetSp2()-Sp;
   b_p2p_p100_p500->GetEntry(entry); Exp1[10] = p2p_p100_p500->GetSp2()-Sp;
   
   b_p2p_p200_m500->GetEntry(entry); Exp2[0]  = p2p_p200_m500->GetSp2()-Sp;
   b_p2p_p200_m400->GetEntry(entry); Exp2[1]  = p2p_p200_m400->GetSp2()-Sp;
   b_p2p_p200_m300->GetEntry(entry); Exp2[2]  = p2p_p200_m300->GetSp2()-Sp;
   b_p2p_p200_m200->GetEntry(entry); Exp2[3]  = p2p_p200_m200->GetSp2()-Sp;
   b_p2p_p200_m100->GetEntry(entry); Exp2[4]  = p2p_p200_m100->GetSp2()-Sp;
   b_p2p_p200_0000->GetEntry(entry); Exp2[5]  = p2p_p200_0000->GetSp2()-Sp;
   b_p2p_p200_p100->GetEntry(entry); Exp2[6]  = p2p_p200_p100->GetSp2()-Sp;
   b_p2p_p200_p200->GetEntry(entry); Exp2[7]  = p2p_p200_p200->GetSp2()-Sp;
   b_p2p_p200_p300->GetEntry(entry); Exp2[8]  = p2p_p200_p300->GetSp2()-Sp;
   b_p2p_p200_p400->GetEntry(entry); Exp2[9]  = p2p_p200_p400->GetSp2()-Sp;
   b_p2p_p200_p500->GetEntry(entry); Exp2[10] = p2p_p200_p500->GetSp2()-Sp;
   
   b_p2p_p300_m500->GetEntry(entry); Exp3[0]  = p2p_p300_m500->GetSp2()-Sp;
   b_p2p_p300_m400->GetEntry(entry); Exp3[1]  = p2p_p300_m400->GetSp2()-Sp;
   b_p2p_p300_m300->GetEntry(entry); Exp3[2]  = p2p_p300_m300->GetSp2()-Sp;
   b_p2p_p300_m200->GetEntry(entry); Exp3[3]  = p2p_p300_m200->GetSp2()-Sp;
   b_p2p_p300_m100->GetEntry(entry); Exp3[4]  = p2p_p300_m100->GetSp2()-Sp;
   b_p2p_p300_0000->GetEntry(entry); Exp3[5]  = p2p_p300_0000->GetSp2()-Sp;
   b_p2p_p300_p100->GetEntry(entry); Exp3[6]  = p2p_p300_p100->GetSp2()-Sp;
   b_p2p_p300_p200->GetEntry(entry); Exp3[7]  = p2p_p300_p200->GetSp2()-Sp;
   b_p2p_p300_p300->GetEntry(entry); Exp3[8]  = p2p_p300_p300->GetSp2()-Sp;
   b_p2p_p300_p400->GetEntry(entry); Exp3[9]  = p2p_p300_p400->GetSp2()-Sp;
   b_p2p_p300_p500->GetEntry(entry); Exp3[10] = p2p_p300_p500->GetSp2()-Sp;
   
   b_p2p_p400_m500->GetEntry(entry); Exp4[0]  = p2p_p400_m500->GetSp2()-Sp;
   b_p2p_p400_m400->GetEntry(entry); Exp4[1]  = p2p_p400_m400->GetSp2()-Sp;
   b_p2p_p400_m300->GetEntry(entry); Exp4[2]  = p2p_p400_m300->GetSp2()-Sp;
   b_p2p_p400_m200->GetEntry(entry); Exp4[3]  = p2p_p400_m200->GetSp2()-Sp;
   b_p2p_p400_m100->GetEntry(entry); Exp4[4]  = p2p_p400_m100->GetSp2()-Sp;
   b_p2p_p400_0000->GetEntry(entry); Exp4[5]  = p2p_p400_0000->GetSp2()-Sp;
   b_p2p_p400_p100->GetEntry(entry); Exp4[6]  = p2p_p400_p100->GetSp2()-Sp;
   b_p2p_p400_p200->GetEntry(entry); Exp4[7]  = p2p_p400_p200->GetSp2()-Sp;
   b_p2p_p400_p300->GetEntry(entry); Exp4[8]  = p2p_p400_p300->GetSp2()-Sp;
   b_p2p_p400_p400->GetEntry(entry); Exp4[9]  = p2p_p400_p400->GetSp2()-Sp;
   b_p2p_p400_p500->GetEntry(entry); Exp4[10] = p2p_p400_p500->GetSp2()-Sp;
   
   b_p2p_p500_m500->GetEntry(entry); Exp5[0]  = p2p_p500_m500->GetSp2()-Sp;
   b_p2p_p500_m400->GetEntry(entry); Exp5[1]  = p2p_p500_m400->GetSp2()-Sp;
   b_p2p_p500_m300->GetEntry(entry); Exp5[2]  = p2p_p500_m300->GetSp2()-Sp;
   b_p2p_p500_m200->GetEntry(entry); Exp5[3]  = p2p_p500_m200->GetSp2()-Sp;
   b_p2p_p500_m100->GetEntry(entry); Exp5[4]  = p2p_p500_m100->GetSp2()-Sp;
   b_p2p_p500_0000->GetEntry(entry); Exp5[5]  = p2p_p500_0000->GetSp2()-Sp;
   b_p2p_p500_p100->GetEntry(entry); Exp5[6]  = p2p_p500_p100->GetSp2()-Sp;
   b_p2p_p500_p200->GetEntry(entry); Exp5[7]  = p2p_p500_p200->GetSp2()-Sp;
   b_p2p_p500_p300->GetEntry(entry); Exp5[8]  = p2p_p500_p300->GetSp2()-Sp;
   b_p2p_p500_p400->GetEntry(entry); Exp5[9]  = p2p_p500_p400->GetSp2()-Sp;
   b_p2p_p500_p500->GetEntry(entry); Exp5[10] = p2p_p500_p500->GetSp2()-Sp;
   
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

void Selector_offset::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void Selector_offset::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
   saveFile->cd(); //set focus on this file
   newTree->Write(); 
   saveFile->Close();

   printf("-------------- done. %s, %d\n", saveFileName.Data(), count);
}
