#define Selector_PostAna_cxx
// The class definition in Selector_PostAna.h has been generated automatically
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
// Root > T->Process("Selector_PostAna.C")
// Root > T->Process("Selector_PostAna.C","some options")
// Root > T->Process("Selector_PostAna.C+")
//

#include "Selector_PostAna.h"
#include <TH2.h>
#include <TStyle.h>


void Selector_PostAna::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void Selector_PostAna::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t Selector_PostAna::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either Selector_PostAna::GetEntry() or TBranch::GetEntry()
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
   const Double_t toffset_L = 58.7;
   const Double_t toffset_R = 59.5;
   
   const Double_t CryRadius = 8;
   
   const Bool_t vertexCorr = 1; 
   const Bool_t IncAngleCorr = 1; 
   const Bool_t PolMagCorr = 1; 

   /*
   Sp0 = 23.26; //22O
   mass = 20498.064784;
   massA = 22;
   massZ = 8;
   Brho0 = 6.7288;
   /**/
   
   
   //Sp0 = 13.26; //23F
   //mass = 21423.077578;
   //massA = 23;
   //massZ = 9;
   //Brho0 = 6.7288;
   
   
   Sp0 = 14.43; //25F
   mass = 23294.116162;
   massA = 25;
   massZ = 9;
   Brho0 = 7.1315;
   
   beamZ = 10.; // for TOF
   
   //____________________________________________________________ eventnumber
   eventID = entry;
   b_eventheader->GetEntry(entry,0);
   runNum = eventheader->GetRunNumber();
   //if( eventID > 5000) {
   //   TSelector::Abort();
   //}
   
   //____________________________________________________________ conReg 
   b_coinReg->GetEntry(entry,0);
   coinRegNum = 0; 
   //if( !coinReg->Test(2) ) return kTRUE; // ppcoin 
   //if( coinReg->Test(0) ) {coinRegNum += 0;} // F3 
   //if( coinReg->Test(1) ) {coinRegNum += 2;}  // FH9 downscale 
   //if( coinReg->Test(2) ) {coinRegNum += 4;}   // ppcoin
   //
   //if( coinReg->Test(3) ) {coinRegNum += 8;} // ND coin
   //if( coinReg->Test(4) ) {coinRegNum += 16;} // ppsingle
   //if( coinReg->Test(5) ) {coinRegNum += 32;} // NDsingle
   //if( coinReg->Test(6) ) {coinRegNum += 64;} // ND cosmic
   
   //____________________________________________________________ ppac
   ppacX = 0;
   if ( b_ppac) {
      b_ppac->GetEntry(entry,0);
      for( Int_t p = 0; p < ppac->GetEntriesFast(); p++){
         ppacX = ((art::TPPACData*) ppac->At(p))->GetX();
      }
   }
   
   //____________________________________________________________ plaV775
   tofF3FH9 = TMath::QuietNaN(); qFH9 = TMath::QuietNaN(); tFH9 = TMath::QuietNaN();
	qF3 = TMath::QuietNaN(); tF3 = TMath::QuietNaN();
	tofTplaL = TMath::QuietNaN(); qTplaL = TMath::QuietNaN(); tTplaL = TMath::QuietNaN();
	tofTplaR = TMath::QuietNaN(); qTplaR = TMath::QuietNaN(); tTplaR = TMath::QuietNaN();
   tS0 = TMath::QuietNaN();
	tofS0S0D = TMath::QuietNaN(); qS0D = TMath::QuietNaN(); tS0D = TMath::QuietNaN();
   
   b_plaV775->GetEntry(entry,0);
   for( Int_t p = 0; p < plaV775->GetEntriesFast(); p++){
      Int_t DetID = ((art::TTimingChargeData*) plaV775->At(p))->GetID();
      Double_t timing = ((art::TTimingChargeData*)plaV775->At(p))->GetTiming(); 
      Double_t charge = ((art::TTimingChargeData*)plaV775->At(p))->GetCharge();
      //printf("    %d, ID:%d, %7.2f %7.2f \n", p, DetID, timing, charge);
      if ( DetID == 0 ) {
         tTplaL = timing;
         qTplaL = charge;
      }
      if ( DetID == 1 ) {
         tTplaR = timing;
         qTplaR = charge;
      }
      if ( DetID == 2 ) {
         tF3 = timing;
         qF3 = charge;
      }
      if ( DetID == 3 ) {
         tFH9 = timing;
      }
      if ( DetID == 4 ) {
         tS0D = timing;
         qS0D = charge;
      }
      
   }

   if( TMath::IsNaN(tFH9)) return kTRUE;
   if( TMath::IsNaN(tF3)) return kTRUE;
   if( TMath::IsNaN(tTplaL)) return kTRUE;
   if( TMath::IsNaN(tTplaR)) return kTRUE;
   if( TMath::IsNaN(qTplaL)) return kTRUE;
   if( TMath::IsNaN(qTplaR)) return kTRUE;
   //____________________________________________________________ nyoki_t
   tofS0DS1 = TMath::QuietNaN(); qS1 = TMath::QuietNaN(); tS1 = TMath::QuietNaN();
   b_nyoki_t->GetEntry(entry,0);
   nyokiID = -1;
   for( Int_t p = 0; p < nyoki_t->GetEntriesFast(); p++){
      nyokiID = ((art::TTimingChargeData*)nyoki_t->At(p))->GetAuxID() ;
      //nyokiID = ((art::TTimingChargeData*)nyoki_t->At(p))->GetID() ;
      tS1 = ((art::TTimingChargeData*)nyoki_t->At(p))->GetTiming() ;
      qS1 = ((art::TTimingChargeData*)nyoki_t->At(p))->GetCharge() ;
   }
   
   //printf("%d,  %d, %f \n", nyoki_t->GetEntriesFast(), nyokiID, tS1);
   
   if( nyokiID == -1 || nyokiID < 5) return kTRUE;
   if( TMath::IsNaN(tS1) ) return kTRUE;
   
   //____________________________________________________________ S0img
   b_S0img->GetEntry(entry);
   s0x = TMath::QuietNaN();
   s0y = TMath::QuietNaN();
   s0a = TMath::QuietNaN();
   s0b = TMath::QuietNaN();
   for( Int_t p = 0; p < S0img->GetEntriesFast(); p++){
      s0x = ((art::TTrack*)((art::TMWDCTrackingResult*)S0img->At(p))->GetTrack())->GetX();
      s0a = ((art::TTrack*)((art::TMWDCTrackingResult*)S0img->At(p))->GetTrack())->GetA();
      s0y = ((art::TTrack*)((art::TMWDCTrackingResult*)S0img->At(p))->GetTrack())->GetY();
      s0b = ((art::TTrack*)((art::TMWDCTrackingResult*)S0img->At(p))->GetTrack())->GetB();
   }   

   //printf("%d, s0x: %f \n", entry, s0x);

   if( TMath::IsNaN(s0x)) return kTRUE;
   
   if( s0x*s0x + TMath::Power(s0y-1.8,2) > CryRadius*CryRadius ) return kTRUE;
   
   //____________________________________________________________ dcs0d
   b_dcs0d->GetEntry(entry);
   s0dx = TMath::QuietNaN();
   s0dy = TMath::QuietNaN();
   for( Int_t p = 0; p < dcs0d->GetEntriesFast(); p++){
      s0dx = - ((art::TTrack*)((art::TMWDCTrackingResult*)dcs0d->At(p))->GetTrack())->GetX();
      s0dy = ((art::TTrack*)((art::TMWDCTrackingResult*)dcs0d->At(p))->GetTrack())->GetY();
   }   

   if( TMath::IsNaN(s0dx)) return kTRUE;

   //____________________________________________________________ smwdc_L
   b_smwdc_L->GetEntry(entry);
   x1 = TMath::QuietNaN();
   y1 = TMath::QuietNaN();
   a1 = TMath::QuietNaN();
   b1 = TMath::QuietNaN();
   Double_t dx1 = TMath::QuietNaN();
   Double_t dy1 = TMath::QuietNaN();
   for( Int_t p = 0; p < smwdc_L->GetEntriesFast(); p++){
      x1 = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_L->At(p))->GetTrack())->GetX();
      dx1 = ((art::TMWDCTrackingResult*)smwdc_L->At(p))->GetSigma(0);
      //a1 = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_L->At(p))->GetTrack())->GetA();
      y1 = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_L->At(p))->GetTrack())->GetY();
      dy1 = ((art::TMWDCTrackingResult*)smwdc_L->At(p))->GetSigma(2);
      //b1 = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_L->At(p))->GetTrack())->GetB();
   }
   if( TMath::IsNaN(x1)) return kTRUE;
   
   //____________________________________________________________ smwdc_R
   b_smwdc_R->GetEntry(entry);
   x2 = TMath::QuietNaN();
   y2 = TMath::QuietNaN();
   a2 = TMath::QuietNaN();
   b2 = TMath::QuietNaN();
   Double_t dx2 = TMath::QuietNaN();
   Double_t dy2 = TMath::QuietNaN();
   for( Int_t p = 0; p < smwdc_R->GetEntriesFast(); p++){
      x2 = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_R->At(p))->GetTrack())->GetX();
      dx2 = ((art::TMWDCTrackingResult*)smwdc_R->At(p))->GetSigma(0);
      //a2 = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_R->At(p))->GetTrack())->GetA();
      y2 = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_R->At(p))->GetTrack())->GetY();
      dy2 = ((art::TMWDCTrackingResult*)smwdc_R->At(p))->GetSigma(2);
      //b2 = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_R->At(p))->GetTrack())->GetB();
   }
   if( TMath::IsNaN(x2)) return kTRUE;

   //____________________________________________________________ smwdc_S1
   b_smwdc_S1->GetEntry(entry);
   s1x = TMath::QuietNaN();
   s1y = TMath::QuietNaN();
   s1a = TMath::QuietNaN();
   s1b = TMath::QuietNaN();
   for( Int_t p = 0; p < smwdc_S1->GetEntriesFast(); p++){
      s1x = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_S1->At(p))->GetTrack())->GetX();
      s1a = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_S1->At(p))->GetTrack())->GetA();
      s1y = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_S1->At(p))->GetTrack())->GetY();
      s1b = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_S1->At(p))->GetTrack())->GetB();
   }  
   if( TMath::IsNaN(s1x)) return kTRUE;
   
   //____________________________________________________________ vertex
   b_vertex->GetEntry(entry);
   vertexZ = TMath::QuietNaN();
   Double_t vertexX = TMath::QuietNaN();
   Double_t vertexY = TMath::QuietNaN();
   for( Int_t p = 0; p < vertex->GetEntriesFast(); p++){
      vertexZ = ((art::TTrack*)vertex->At(p))->GetZ();
      vertexX = ((art::TTrack*)vertex->At(p))->GetX();
      vertexY = ((art::TTrack*)vertex->At(p))->GetY();
   }

   if( vertexZ < -100 || vertexZ > 300 ) return kTRUE;
   
   //____________________________________________________________ display
   count ++;

   //#################################################################### Phsyics
   //__________________________________ TOF

   tofF3FH9 = tFH9 - tF3 + toffset_F3FH9;

   tS0 = tFH9 + tofF3FH9*(L_FH9S0 + vertexZ)/L_F3FH9;
   
   tofTplaL = tTplaL - tS0 + toffset_L;
   tofTplaR = tTplaR - tS0 + toffset_R;
   tofS0S0D = tS0D - tS0;
   tofS0DS1 = tS1 - tS0D;
   
   if ( tofS0DS1 < 32 || tofS0DS1 > 39 ) return kTRUE;
   
   //____________________________________________________________ 
   TVector3 p1(x1,y1,1022.37), p2(x2,y2,1022.37), pV(vertexX,vertexY,vertexZ); // vector of P1, P2, P_vertex
   
   TVector3 dp1(x1+dx1,y1+dy1,1022.37), dp2(x2+dx2,y2+dy2,1022.37);

   // rotate to Lab frame
   p1.RotateY(60*TMath::DegToRad());
   dp1.RotateY(60*TMath::DegToRad());
   //set the length to Tpla;
   p1.SetMag(p1.Mag()*1400/1022.37);
   dp1.SetMag(p1.Mag()*1400/1022.37);
   // Reaction Vectex Correction
   if( vertexCorr ) {
      p1 = p1 - pV;
      dp1 = dp1 - pV;
   }
   // Incident Angle Correction
   if( IncAngleCorr ) {
      p1.RotateY(-s0a);
      dp1.RotateY(-s0a);
      p1.RotateX(s0b);
      dp1.RotateX(s0b);
   }
   // Calculation momentum
   Double_t FL1 = p1.Mag();
   Double_t beta1 = FL1/tofTplaL/299.792458;
   p1.SetMag(mp*beta1/TMath::Sqrt(1-beta1*beta1));
   
   Double_t dFL1 = dp1.Mag();
   Double_t dbeta1 = dFL1/tofTplaL/299.792458;
   dp1.SetMag(mp*dbeta1/TMath::Sqrt(1-dbeta1*dbeta1));
   
   // rotate to Lab frame
   p2.RotateY(-60*TMath::DegToRad());
   dp2.RotateY(-60*TMath::DegToRad());
   //set the length to Tpla;
   p2.SetMag(p2.Mag()*1400/1022.37);
   dp2.SetMag(p2.Mag()*1400/1022.37);
   // Reaction Vectex Correction
   if( vertexCorr) {
      p2 = p2 - pV;
      dp2 = p2 - pV;
   }
   // Incident Angle Correction
   if( IncAngleCorr){
      p2.RotateY(-s0a);
      dp2.RotateY(-s0a);
      p2.RotateX(s0b);   
      dp2.RotateX(s0b);   
   }
   // Calculation momentum
   Double_t FL2 = p2.Mag();
   Double_t beta2 = FL2/tofTplaR/299.792458;
   p2.SetMag(mp*beta2/TMath::Sqrt(1-beta2*beta2));
   
   Double_t dFL2 = dp2.Mag();
   Double_t dbeta2 = dFL2/tofTplaR/299.792458;
   dp2.SetMag(mp*dbeta2/TMath::Sqrt(1-dbeta2*dbeta2));
   
   //______________________________________________________________________ 4-vector
   TLorentzVector Pf; Pf.SetVectM(TVector3(0,0,299.792458*massZ*Brho0*(1+ppacX/7500)), mass);
   TLorentzVector Pt; Pt.SetVectM(TVector3(0,0,0), mp);
   TLorentzVector P1; P1.SetVectM(p1,mp); 
   TLorentzVector P2; P2.SetVectM(p2,mp);
   
   TLorentzVector dP1; dP1.SetVectM(dp1,mp); 
   TLorentzVector dP2; dP2.SetVectM(dp2,mp);
   
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
      dP1.RotateY(dTheta);
      
      pBrho =  mp * P2.Beta() * P2.Gamma() / 299.972458;
      dTheta = 0.064 * 0.11 / pBrho;
      P2.RotateY(dTheta);
      dP2.RotateY(dTheta);
      // artifical correction
      P1.RotateY(angleOffset);
      P2.RotateY(-angleOffset);
      dP1.RotateY(angleOffset);
      dP2.RotateY(-angleOffset);
   }
   
   // Residual 
   TLorentzVector Pr = Pf + Pt- P1 - P2;
   TLorentzVector dPr = Pf + Pt- dP1 - dP2;

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
   TLorentzVector dPrc = dPr;
   TVector3 b;
   b = Pf.BoostVector();
   Prc.Boost(-b);
   dPrc.Boost(-b);
   
   kMomt = Prc.P();
   dkMomt = Prc.P()-dPrc.P();
   
   //if(-40<Ex && Ex<60) printf("kMomt:%10.3f, dkMomt:%10.3f\n", kMomt, dkMomt); 
   
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
      //pidAOQ = 1.37253 - 0.0402106*tofc + 1.05522*pidAOQ_p -1./8.;
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
   
   /*
   printf("=========================================================================== %d (%d), %7.2f, %7.2f\n", entry, count, Brho0, ppacX);
   printf("%7s, %7s, %7s, %7s, %7s, %7s, %7s, %7s\n", "tF3", "tFH9", "tS0", "tTplaL", "tTplaR", "tS0D", "nyokiID", "tS1"); 
   printf("%7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7.2f, %7d, %7.2f\n", tF3, tFH9, tS0, tTplaL, tTplaR, tS0D,nyokiID, tS1); 
   printf("-------------- TOF \n");
   printf("%7s, %7s, %7s, %7s, %7s\n", "F3FH9", "S0S0D", "S0TplaL", "S0TplaR", "S0DS1"); 
   printf("%7.2f, %7.2f, %7.2f, %7.2f, %7.2f\n", tofF3FH9, tofS0S0D, tofTplaL, tofTplaR, tofS0DS1); 
   printf("-------------- S0img \n");
   printf("%7s, %7s, %7s, %7s\n", "X", "A", "Y", "B"); 
   printf("%7.2f, %7.2f, %7.2f, %7.2f\n", s0x, s0a*1000, s0y, s0b*1000); 
   printf("-------------- DCS0D \n");
   printf("%7s, %7s, %7s, %7s, %7s\n", "X", "Y", "vertexX", "vertexY", "vertexZ"); 
   printf("%7.2f, %7.2f, %7.2f, %7.2f, %7.2f\n", s0dx, s0dy, vertexX, vertexY, vertexZ); 
   printf("----------------------\n");
   printf("%7s  %7s, %7s, %7s, %7s\n", "", "X", "A", "Y", "B"); 
   printf("%7s, %7.2f, %7.2f, %7.2f, %7.2f\n", "MWDC-L", x1, a1*1000, y1, b1*1000); 
   printf("%7s, %7.2f, %7.2f, %7.2f, %7.2f\n", "MWDC-R", x2, a2*1000, y2, b2*1000); 
   printf("%7s, %7.2f, %7.2f, %7.2f, %7.2f\n", "MWDC-S1", s1x, s1a*1000, s1y, s1b*1000); 
   printf("------------------------------ Recoil \n");
   printf("L :%7.2f, %7.2f, %7.2f| %7.2f, %7.2f, %7.2f, %7.2f, %7.2f \n", p1.X(), p1.Y(), p1.Z(), p1.Mag(), p1.Theta()*TMath::RadToDeg(), p1.Phi()*TMath::RadToDeg(), FL1, beta1);
   printf("R :%7.2f, %7.2f, %7.2f| %7.2f, %7.2f, %7.2f, %7.2f, %7.2f \n", p2.X(), p2.Y(), p2.Z(), p2.Mag(), p2.Theta()*TMath::RadToDeg(), p2.Phi()*TMath::RadToDeg(), FL2, beta2);
   printf("----------------------\n");
   printf("%4s: %10.2f, %10.2f, %10.2f, %10.2f | %10.2f, %10.2f, %10.2f \n", "Pf", Pf.X(), Pf.Y(), Pf.Z(), Pf.E(), Pf.M(), (Pf.E()-Pf.M())/massA, Pf.P());
   printf("%4s: %10.2f, %10.2f, %10.2f, %10.2f | %10.2f, %10.2f, %10.2f \n", "Pt", Pt.X(), Pt.Y(), Pt.Z(), Pt.E(), Pt.M(), (Pt.E()-Pt.M())/massA, Pt.P());
   printf("%4s: %10.2f, %10.2f, %10.2f, %10.2f | %10.2f, %10.2f, %10.2f \n", "P1", P1.X(), P1.Y(), P1.Z(), P1.E(), P1.M(), (P1.E()-P1.M())/massA, P1.P());
   printf("%4s: %10.2f, %10.2f, %10.2f, %10.2f | %10.2f, %10.2f, %10.2f \n", "P2", P2.X(), P2.Y(), P2.Z(), P2.E(), P2.M(), (P2.E()-P2.M())/massA, P2.P());
   printf("%4s: %10.2f, %10.2f, %10.2f, %10.2f | %10.2f, %10.2f, %10.2f \n", "Pr", Pr.X(), Pr.Y(), Pr.Z(), Pr.E(), Pr.M(), (Pr.E()-Pr.M())/massA, Pr.P());
   printf(" ========== Sp: %f\n", Sp);
   printf("%4s: %10.2f, %10.2f, %10.2f, %10.2f | %10.2f, %10.2f, %10.2f \n", "Prc", Prc.X(), Prc.Y(), Prc.Z(), Prc.E(), Prc.M(), (Prc.E()-Prc.M())/massA, Prc.P());
   /**/
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



void Selector_PostAna::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void Selector_PostAna::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

   saveFile->cd(); //set focus on this file
   newTree->Write(); 
   saveFile->Close();

   printf("-------------- done. %s, %d\n", saveFileName.Data(), count);


}
