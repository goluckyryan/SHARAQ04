#define Selector_PostAna2_cxx
// The class definition in Selector_PostAna2.h has been generated automatically
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
// Root > T->Process("Selector_PostAna2.C")
// Root > T->Process("Selector_PostAna2.C","some options")
// Root > T->Process("Selector_PostAna2.C+")
//

#include "Selector_PostAna2.h"
#include <TH2.h>
#include <TStyle.h>


void Selector_PostAna2::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void Selector_PostAna2::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t Selector_PostAna2::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either Selector_PostAna2::GetEntry() or TBranch::GetEntry()
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

   //____________________________________________________________ some parameter;
   const Double_t angleOffset = 0.00524;
   const Double_t L_FH9S0 = 10865.;
   const Double_t L_F3FH9 = 74075.;
   const Double_t toffset_F3FH9 = 703.68;
   const Double_t toffset_L = 58.7+0.2;
   const Double_t toffset_R = 59.5+0.2;
   
   const Bool_t vertexCorr = 1; 
   const Bool_t IncAngleCorr = 1; 
   const Bool_t PolMagCorr = 1; 
   
   /*
   Sp0 = 13.26; //23F
   mass = 21423.077578;
   massA = 23;
   massZ = 8;
   Brho0 = 6.7288;
   /**/
   
   
   Sp0 = 14.43; //25F
   mass = 23294.116162;
   massA = 25;
   massZ = 9;
   Brho0 = 7.1315;
   BrhoDS = 7.12;
   /**/
   
   beamZ = 10.; // for TOF

   //#################################################################### Phsyics
   ppacX = 0;
   if ( b_ppacX) {
      b_ppacX->GetEntry(entry,0);
   }
   
   b_tFH9->GetEntry(entry,0);
   b_tF3->GetEntry(entry,0);
   b_tTplaL->GetEntry(entry,0);
   b_tTplaR->GetEntry(entry,0);
   b_tS1->GetEntry(entry,0);
   b_tS0D->GetEntry(entry,0);
   b_vertexZ->GetEntry(entry,0);
   b_vertexX->GetEntry(entry,0);
   b_vertexY->GetEntry(entry,0);
   b_x1->GetEntry(entry,0);
   b_y1->GetEntry(entry,0);
   b_x2->GetEntry(entry,0);
   b_y2->GetEntry(entry,0);
   b_s0x->GetEntry(entry,0);
   b_s0y->GetEntry(entry,0);
   b_s1x->GetEntry(entry,0);
   b_s0dx->GetEntry(entry,0);
   b_s0a->GetEntry(entry,0);
   b_s0b->GetEntry(entry,0);
   b_qS1->GetEntry(entry,0);
   
   //__________________________________ TOF

   tofF3FH9 = tFH9 - tF3 + toffset_F3FH9;

   tS0 = tFH9 + tofF3FH9*(L_FH9S0 + vertexZ)/L_F3FH9;
   
   tofTplaL = tTplaL - tS0 + toffset_L;
   tofTplaR = tTplaR - tS0 + toffset_R;
   tofS0S0D = tS0D - tS0;
   tofS0DS1 = tS1 - tS0D;
   
   //printf("tS1:%f, tS0D:%f, tofS0DS1:%f \n", tS1, tS0D, tofS0DS1);
   
   if ( tofS0DS1 < 32 || tofS0DS1 > 39 ) return kTRUE;
   
   if( !b_ppacX ) ppacX = 0; 
   
   //____________________________________________________________ 
   TVector3 p1(x1,y1,1022.37), p2(x2,y2,1022.37), pV(vertexX,vertexY,vertexZ); // vector of P1, P2, P_vertex

   // rotate to Lab frame
   p1.RotateY(60*TMath::DegToRad());
   //set the length to Tpla;
   p1.SetMag(p1.Mag()*1400/1022.37);
   // Reaction Vectex Correction
   if( vertexCorr ) p1 = p1 - pV;
   // Incident Angle Correction
   if( IncAngleCorr ) {
      p1.RotateY(-s0a);
      p1.RotateX(s0b);
   }
   // Calculation momentum
   Double_t FL1 = p1.Mag();
   Double_t beta1 = FL1/tofTplaL/299.792458;
   p1.SetMag(mp*beta1/TMath::Sqrt(1-beta1*beta1));
   
   // rotate to Lab frame
   p2.RotateY(-60*TMath::DegToRad());
   //set the length to Tpla;
   p2.SetMag(p2.Mag()*1400/1022.37);
   // Reaction Vectex Correction
   if( vertexCorr) p2 = p2 - pV;
   // Incident Angle Correction
   if( IncAngleCorr){
      p2.RotateY(-s0a);
      p2.RotateX(s0b);   
   }
   // Calculation momentum
   Double_t FL2 = p2.Mag();
   Double_t beta2 = FL2/tofTplaR/299.792458;
   p2.SetMag(mp*beta2/TMath::Sqrt(1-beta2*beta2));
   
   //______________________________________________________________________ 4-vector
   TLorentzVector Pf; Pf.SetVectM(TVector3(0,0,299.792458*massZ*Brho0*(1+ppacX/7500)), mass);
   TLorentzVector Pt; Pt.SetVectM(TVector3(0,0,0), mp);
   TLorentzVector P1; P1.SetVectM(p1,mp); 
   TLorentzVector P2; P2.SetVectM(p2,mp);
   
   //full incidnet angle correction
   if( vertexCorr ){
      Pf.RotateY(-s0a);
      Pf.RotateX(s0b);
   }
   // Polarization Magnet correction
   if( PolMagCorr ){
      Double_t pBrho =  mp * P1.Beta() * P1.Gamma() / 299.972458;
      Double_t dTheta = 0.064 * 0.11 / pBrho;
      P1.RotateY(dTheta);
      pBrho =  mp * P2.Beta() * P2.Gamma() / 299.972458;
      dTheta = 0.064 * 0.11 / pBrho;
      P2.RotateY(dTheta);
      // artifical correction
      P1.RotateY(angleOffset);
      P2.RotateY(-angleOffset);
   }
   
   // Residual 
   TLorentzVector Pr = Pf + Pt- P1 - P2;

   E1 = P1.E()-P1.M();
   E2 = P2.E()-P2.M();
   theta1 = P1.Theta()*TMath::RadToDeg();
   theta2 = P2.Theta()*TMath::RadToDeg();
   phi1 = P1.Phi()*TMath::RadToDeg();
   phi2 = P2.Phi()*TMath::RadToDeg();
   Double_t Sp = Pr.M()- mass + mp;
   Ex = Sp - Sp0;
   
   //Set Residual to nuclus rest frame;
   TLorentzVector Prc = Pr;
   TVector3 b;
   b = Pf.BoostVector();
   Prc.Boost(-b);
   
   kMomt = Prc.P();
   
   //#################################################################### Downsteam analsysi
   pidZ = qS1;
   
   tofc = tofS0DS1;
   s1xc = (s1x + (-0.004874) * (-26.6) * s0dx) / (1 + (-0.004874) * s0dx);
   
   //===== 23F
   if( Sp0 == 13.26 ){
      pidAOQ = 0.05327*tofc +(-0.0021946)*s1xc +(1.64e-6)*s1xc*s1xc + 0.75409;
   }//const Double_t aoq = aoq_pre;
   
   //===== 25F
   if( Sp0 == 14.43){
      //pidAOQ_p = 0.05327*tofc +(-0.0021946)*s1xc +(1.64e-6)*s1xc*s1xc + 0.75409;
      //pidAOQ = 1.37253 - 0.0402106*tofc + 1.05522*pidAOQ_p;
      
      pidAOQ_p = -0.595295 + 0.0854414*tofc +(-0.00209171)*s1xc +(9.523e-7)*s1xc*s1xc;
      pidAOQ = 2.41191 - 0.0676409*tofc + 1.06027*pidAOQ_p;
   }
   
   //===== 22O
   if( Sp0 == 23.26){
      tofc = tofS0DS1 -0.004*s0dx;
      s1xc = (s1x +(-0.004874)*(-26.6)*s0dx)/(1+(-0.004874)*s0dx); 
      pidAOQ = (5.275e-2)*tofc + (-2.198e-3)*s1xc + 0.89;
      pidZ = qS1*(1 - (tofc - 33.3)*0.002*qS1);
   }
   
   count++;
   /**///============== testing
   //FL = 6575.6-0.452*s1x+0.000302*s1x*s1x;
   //beta = FL/tofS0DS1/299.792458;
   //Double_t gamma = 1/TMath::Sqrt(1-beta*beta);
   //
   //pidAOQ = 299.792458/931.5*BrhoDS*(1 + s1x/(-1200))/gamma/beta;
   
   /**/
   
   //printf("=========================================================================== %d (%d), %7.2f, %7.2f\n", entry, count, Brho0, ppacX);
   //printf("%7s, %7s, %7s, %7s, %7s, %7s, %7s, %7s\n", "tF3", "tFH9", "tS0", "tTplaL", "tTplaR", "tS0D", "nyokiID", "tS1"); 
   //printf("%7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7d, %7.2f\n", tF3, tFH9, tS0, tTplaL, tTplaR, tS0D,nyokiID, tS1); 
   //printf("-------------- TOF \n");
   //printf("%7s, %7s, %7s, %7s, %7s\n", "F3FH9", "S0S0D", "S0TplaL", "S0TplaR", "S0DS1"); 
   //printf("%7.2f, %7.2f, %7.2f, %7.2f, %7.2f\n", tofF3FH9, tofS0S0D, tofTplaL, tofTplaR, tofS0DS1); 
   //printf("-------------- S0img \n");
   //printf("%7s, %7s, %7s, %7s\n", "X", "A", "Y", "B"); 
   //printf("%7.2f, %7.2f, %7.2f, %7.2f\n", s0x, s0a*1000, s0y, s0b*1000); 
   //printf("-------------- DCS0D \n");
   //printf("%7s, %7s, %7s, %7s, %7s\n", "X", "Y", "vertexX", "vertexY", "vertexZ"); 
   //printf("%7.2f, %7.2f, %7.2f, %7.2f, %7.2f\n", s0dx, s0dy, vertexX, vertexY, vertexZ); 
   //printf("----------------------\n");
   //printf("%7s  %7s, %7s, %7s, %7s\n", "", "X", "A", "Y", "B"); 
   //printf("%7s, %7.2f, %7.2f, %7.2f, %7.2f\n", "MWDC-L", x1, a1*1000, y1, b1*1000); 
   //printf("%7s, %7.2f, %7.2f, %7.2f, %7.2f\n", "MWDC-R", x2, a2*1000, y2, b2*1000); 
   //printf("%7s, %7.2f, %7.2f, %7.2f, %7.2f\n", "MWDC-S1", s1x, s1a*1000, s1y, s1b*1000); 
   //printf("------------------------------ Recoil \n");
   //printf("L :%7.2f, %7.2f, %7.2f| %7.2f, %7.2f, %7.2f, %7.2f, %7.2f \n", p1.X(), p1.Y(), p1.Z(), p1.Mag(), p1.Theta()*TMath::RadToDeg(), p1.Phi()*TMath::RadToDeg(), FL1, beta1);
   //printf("R :%7.2f, %7.2f, %7.2f| %7.2f, %7.2f, %7.2f, %7.2f, %7.2f \n", p2.X(), p2.Y(), p2.Z(), p2.Mag(), p2.Theta()*TMath::RadToDeg(), p2.Phi()*TMath::RadToDeg(), FL2, beta2);
   //printf("----------------------\n");
   //printf("%4s: %10.2f, %10.2f, %10.2f, %10.2f | %10.2f, %10.2f, %10.2f \n", "Pf", Pf.X(), Pf.Y(), Pf.Z(), Pf.E(), Pf.M(), (Pf.E()-Pf.M())/massA, Pf.P());
   //printf("%4s: %10.2f, %10.2f, %10.2f, %10.2f | %10.2f, %10.2f, %10.2f \n", "Pt", Pt.X(), Pt.Y(), Pt.Z(), Pt.E(), Pt.M(), (Pt.E()-Pt.M())/massA, Pt.P());
   //printf("%4s: %10.2f, %10.2f, %10.2f, %10.2f | %10.2f, %10.2f, %10.2f \n", "P1", P1.X(), P1.Y(), P1.Z(), P1.E(), P1.M(), (P1.E()-P1.M())/massA, P1.P());
   //printf("%4s: %10.2f, %10.2f, %10.2f, %10.2f | %10.2f, %10.2f, %10.2f \n", "P2", P2.X(), P2.Y(), P2.Z(), P2.E(), P2.M(), (P2.E()-P2.M())/massA, P2.P());
   //printf("%4s: %10.2f, %10.2f, %10.2f, %10.2f | %10.2f, %10.2f, %10.2f \n", "Pr", Pr.X(), Pr.Y(), Pr.Z(), Pr.E(), Pr.M(), (Pr.E()-Pr.M())/massA, Pr.P());
   //printf(" ========== Sp: %f\n", Sp);
   //printf("%4s: %10.2f, %10.2f, %10.2f, %10.2f | %10.2f, %10.2f, %10.2f \n", "Prc", Prc.X(), Prc.Y(), Prc.Z(), Prc.E(), Prc.M(), (Prc.E()-Prc.M())/massA, Prc.P());
   
   //#################################################################### Timer  
   saveFile->cd(); //set focus on this file
   newTree->Fill();  

   clock.Stop("timer");
   Double_t time = clock.GetRealTime("timer");
   clock.Start("timer");

   if ( !shown ) {
      if (fmod(time, 10) < 1 ){
         printf( "%10d[%2d%%]|%3d min %5.2f sec | expect:%5.1fmin %10d\n", 
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

void Selector_PostAna2::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.
   
   saveFile->cd(); //set focus on this file
   newTree->Write(); 
   saveFile->Close();

   printf("-------------- done. %s, %d\n", saveFileName.Data(), count);

}

void Selector_PostAna2::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
