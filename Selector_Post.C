#define Selector_Post_cxx
// The class definition in Selector_Post.h has been generated automatically
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
// Root > T->Process("Selector_Post.C")
// Root > T->Process("Selector_Post.C","some options")
// Root > T->Process("Selector_Post.C+")
//

#include "Selector_Post.h"
#include <TH2.h>
#include <TStyle.h>


void Selector_Post::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

void Selector_Post::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();

}

Bool_t Selector_Post::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either Selector_Post::GetEntry() or TBranch::GetEntry()
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
   

         //______________________________________________________________ entry
        
         if( count > 500000) {
            Terminate();
            return kTRUE;
         }/**/
         //______________________________________________________________ p2p
         if( b_p2p ) {
            b_p2p->GetEntry(entry);
            E1 = p2p->GetRecoilL()->E()-938.272;
            E2 = p2p->GetRecoilR()->E()-938.272;

            //if( E1 > 400 || E2 > 400 ) {return kTRUE;}


            kMomt = p2p->GetResidual()->P();
            //if( kMomt > 2000 )  {return kTRUE;}

            theta1 = p2p->GetRecoilL()->Theta()*TMath::RadToDeg();
            phi1 = p2p->GetRecoilL()->Phi()*TMath::RadToDeg();

            theta2 = p2p->GetRecoilR()->Theta()*TMath::RadToDeg();
            phi2 = p2p->GetRecoilR()->Phi()*TMath::RadToDeg();
            //correct phi2 to be in range (-90,90);
            //if(phi1 < 0) phi1 = phi1 + 360;
            if(phi2 < 0) {
               phi2 = phi2 + 180;
            }else{
               phi2 = phi2 -180;
            }


            Ex = p2p->GetSp2()-13.26;
            ExS = p2p->GetSp()-13.26;
            if( TMath::IsNaN(ExS) && TMath::IsNaN(Ex) ) {return kTRUE;}
            //printf("%f, %f \n", s1x, Ex);
         }
         
         count ++;
         
/*        //______________________________________________________________ p2p_c
         b_p2p_c->GetEntry(entry);

         theta1c = p2p_c->GetRecoilL()->Theta()*TMath::RadToDeg();
         phi1c = p2p_c->GetRecoilL()->Phi()*TMath::RadToDeg();

         theta2c = p2p_c->GetRecoilR()->Theta()*TMath::RadToDeg();
         phi2c = p2p_c->GetRecoilR()->Phi()*TMath::RadToDeg();

         Exc = p2p_c->GetSp2()-13.26;
         kMomtc = p2p_c->GetResidual()->P();

*/
        
        //______________________________________________________________ run number
        b_eventheader->GetEntry(entry);
        runNum = eventheader->GetRunNumber();
        //runNum = eventheader0->GetRunNumber();
        //if( runNum == 29 ) return kTRUE;
        
        //______________________________________________________________ conReg
        if( b_coinReg){
           b_coinReg->GetEntry(entry);
           coinRegNum = 0; 
           if( coinReg->Test(0) ) {coinRegNum += 0;} // F3 
           if( coinReg->Test(1) ) {coinRegNum += 2;}  // FH9 downscale 
           if( coinReg->Test(2) ) {coinRegNum += 4;}   // ppcoin
           
           if( coinReg->Test(3) ) {coinRegNum += 8;} // ND coin
           if( coinReg->Test(4) ) {coinRegNum += 16;} // ppsingle
           if( coinReg->Test(5) ) {coinRegNum += 32;} // NDsingle
           if( coinReg->Test(6) ) {coinRegNum += 64;} // ND cosmic
           
           //if( coinRegNum == 64) return kTRUE;
           
           //printf(" %d, %d, %d, %d \n", coinReg->Test(1), coinRegNum[0], coinReg->Test(2), coinRegNum[1]); 
        }
        //______________________________________________________________ gate Num
        b_gate->GetEntry(entry);
        s0imgGate = 6;
        if( gate->Test(10) ) {s0imgGate = 1;} //radius <= 2
        if( gate->Test(11) && !gate->Test(10)) {s0imgGate = 2;} //radius <= 5
        if( gate->Test(12) && !gate->Test(11)) {s0imgGate = 3;} //radius <= 7
        if( gate->Test(13) && !gate->Test(12)) {s0imgGate = 4;} //radius <= 10
        if( gate->Test(14) && !gate->Test(13)) {s0imgGate = 5;} //radius <= 14
        
        pidusGate = -10;
        for( Int_t p = 0; p < 9; p++){
                if( gate->Test(p) ) {
                        pidusGate = p;
                }
        }
        
/*         //______________________________________________________________ FH9
         if( b_plaV1190_FH9){
            tofFH9 = TMath::QuietNaN();
            qFH9 = TMath::QuietNaN();
            b_plaV1190_FH9->GetEntry(entry);
            b_tof_US->GetEntry(entry);
            for( Int_t p = 0; p < plaV1190_FH9 -> GetEntriesFast(); p++){
                  Int_t HitID  = ((art::TTimeDifference*)plaV1190_FH9->At(p))->GetHitID();
                  tofFH9  = ((art::TTimeDifference*)plaV1190_FH9->At(p))->GetTiming();
                  qFH9 = ((art::TTwoSidedPlasticData*) tof_US->At(HitID-1))->GetCharge();
                  //if( TMath::Abs(tofFH9+1463)<3 ) break;
            }
         }
        
/*        //______________________________________________________________ plaV775_cal
        tTplaLB = TMath::QuietNaN();
        tTplaRF = TMath::QuietNaN();
        b_plaV775_L_cal->GetEntry(entry,0);
        for( Int_t p = 0; p < plaV775_L_cal -> GetEntriesFast(); p++){
                Int_t DetID = ((art::TTimingChargeData*)plaV775_L_cal->At(p))->GetID();
                Double_t timing = ((art::TTimingChargeData*)plaV775_L_cal->At(p))->GetTiming(); 
                if ( DetID == 0 ) {
                        tTplaLB = timing;
                }
                if ( DetID == 1 ) {
                        tTplaRF = timing;
                }
                if ( DetID == 4 ) {
                        tS0DU = timing;
                        qS0DU = ((art::TTimingChargeData*)plaV775_L_cal->At(p))->GetCharge();
                }
        }
        
        tTplaLF = TMath::QuietNaN();
        tTplaRB = TMath::QuietNaN();
        b_plaV775_R_cal->GetEntry(entry,0);
        for( Int_t p = 0; p < plaV775_R_cal -> GetEntriesFast(); p++){
                Int_t DetID = ((art::TTimingChargeData*)plaV775_R_cal->At(p))->GetID();
                Double_t timing = ((art::TTimingChargeData*)plaV775_R_cal->At(p))->GetTiming(); 
                if ( DetID == 0 ) {
                        tTplaLF = timing;
                }
                if ( DetID == 1 ) {
                        tTplaRB = timing;
                }
                if ( DetID == 4 ) {
                        tS0DD = timing;
                        qS0DD = ((art::TTimingChargeData*)plaV775_R_cal->At(p))->GetCharge();
                }
        }

        if(tTplaLB == 0) tTplaLB = TMath::QuietNaN();
        if(tTplaRF == 0) tTplaRF = TMath::QuietNaN();
        if(tTplaLF == 0) tTplaLF = TMath::QuietNaN();
        if(tTplaRB == 0) tTplaRB = TMath::QuietNaN();        
*/        
        //______________________________________________________________ time, charge and TOF
        if ( b_plaV775){        
           b_plaV775->GetEntry(entry,0);
           tS0D = TMath::QuietNaN();
           qS0D = TMath::QuietNaN();
           tTplaL = TMath::QuietNaN();
           qTplaL = TMath::QuietNaN();
           tTplaR = TMath::QuietNaN();
           qTplaR = TMath::QuietNaN();
           tF3 = TMath::QuietNaN();
           qF3 = TMath::QuietNaN();
           tFH9 = TMath::QuietNaN();
           tTgt = TMath::QuietNaN();
           tof_S0D = TMath::QuietNaN();
           tofTplaL = TMath::QuietNaN();
           tofTplaR = TMath::QuietNaN();
           for( Int_t p = 0; p < plaV775 -> GetEntriesFast(); p++){
                   Int_t DetID = ((art::TTimingChargeData*)plaV775->At(p))->GetID();
                   Double_t timing = ((art::TTimingChargeData*)plaV775->At(p))->GetTiming(); 
                   Double_t charge = ((art::TTimingChargeData*)plaV775->At(p))->GetCharge();
                   if ( DetID == 0 ) {
                           tTplaL = timing;
                           qTplaL = charge;
                           //tTplaLB = ((art::TTwoSidedPlasticData*)plaV775->At(p))->GetT1();
                           //tTplaLF = ((art::TTwoSidedPlasticData*)plaV775->At(p))->GetT2();
                   }
                   if ( DetID == 1 ) {
                           tTplaR = timing;
                           qTplaR = charge;
                           //tTplaRB = ((art::TTwoSidedPlasticData*)plaV775->At(p))->GetT1();
                           //tTplaRF = ((art::TTwoSidedPlasticData*)plaV775->At(p))->GetT2();
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
           
           if( tFH9 == 0 ) tFH9 = TMath::QuietNaN();
           if( tF3 == 0 ) tF3 = TMath::QuietNaN();
           if( tTplaL == 0 ) tTplaL = TMath::QuietNaN();
           if( tTplaR == 0 ) tTplaR = TMath::QuietNaN();
           if( qTplaL == 0 ) qTplaL = TMath::QuietNaN();
           if( qTplaR == 0 ) qTplaR = TMath::QuietNaN();
           
           tTgt = tFH9 + (tFH9-tF3)*10865./74075.;
           
           tof_S0D = tS0D - tTgt;
           tofTplaL = tTplaL - tTgt;
           tofTplaR = tTplaR - tTgt;
         }
         
         
        /*
        tof_S0D = TMath::QuietNaN();
        b_tofS0D->GetEntry(entry);
        for( Int_t p = 0; p < tofS0D -> GetEntriesFast(); p++){
                tof_S0D = ((art::TTimingData*)tofS0D->At(p))->GetTiming();
        }
        
        tofTplaL = TMath::QuietNaN();
        b_tofL->GetEntry(entry);
        for( Int_t p = 0; p < tofL -> GetEntriesFast(); p++){
                tofTplaL = ((art::TTimingData*)tofL->At(p))->GetTiming();
        }
        
        
        tofTplaR = TMath::QuietNaN();
        b_tofR->GetEntry(entry);
        for( Int_t p = 0; p < tofR -> GetEntriesFast(); p++){
                tofTplaR = ((art::TTimingData*)tofR->At(p))->GetTiming();
        }
        
*/        
        //______________________________________________________________ nyoki
        if ( b_nyoki_z){
            b_nyoki_z->GetEntry(entry);
            for( Int_t p = 0; p < 14; p++){
                     tS1[p] = TMath::QuietNaN();
                     qS1[p] = TMath::QuietNaN();
            }
            for( Int_t p = 0; p < nyoki_z->GetEntriesFast(); p++){
                     Int_t nS1 = ((art::TTimingChargeData*)nyoki_z->At(p))->GetID() ;
                     tS1[nS1] = ((art::TTimingChargeData*)nyoki_z->At(p))->GetTiming() ;
                     if( tS1[nS1] == 0) tS1[nS1] == TMath::QuietNaN();
                     qS1[nS1] = ((art::TTimingChargeData*)nyoki_z->At(p))->GetCharge() ;
                     if( qS1[nS1] == 0) {
                              qS1[nS1] == TMath::QuietNaN();
                     }
            }
         }
        
        

        //______________________________________________________________ tofS1
        b_tof_s1->GetEntry(entry);
        for( Int_t p = 0; p < 14; p++){
                tofS1[p] = TMath::QuietNaN();
        }
        for( Int_t p = 0; p < tof_s1->GetEntriesFast(); p++){
                Int_t nS1 = ((art::TTimingChargeData*)tof_s1->At(p))->GetID() ;
                tofS1[nS1] = ((art::TTimingChargeData*)tof_s1->At(p))->GetTiming() ;
                if( TMath::Abs(tS1[nS1]+240)>30) {
                        tofS1[nS1] = TMath::QuietNaN();
                        continue;
                }
        }
        //if( TMath::Abs(tofS1-35) > 15 ) {return kTRUE;}

        //______________________________________________________________ S0img
         if ( b_S0img){
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
         }

         //______________________________________________________________ DC-S0D
         if ( b_dcs0d){
            b_dcs0d->GetEntry(entry);
            s0dx = TMath::QuietNaN();
            s0dy = TMath::QuietNaN();
            for( Int_t p = 0; p < dcs0d->GetEntriesFast(); p++){
                     s0dx = ((art::TTrack*)((art::TMWDCTrackingResult*)dcs0d->At(p))->GetTrack())->GetX();
                     s0dy = ((art::TTrack*)((art::TMWDCTrackingResult*)dcs0d->At(p))->GetTrack())->GetY();
            }   
         }

        //______________________________________________________________ vertex Z
        
         if ( b_vertex){
            b_vertex->GetEntry(entry);
            vertexZ = TMath::QuietNaN();
            for( Int_t p = 0; p < vertex->GetEntriesFast(); p++){
               vertexZ = ((art::TTrack*)vertex->At(p))->GetZ();
            }
         }
        //if( TMath::Abs(vertexZ-10)>40 ) {return kTRUE;}

/*        //______________________________________________________________ MWDC-L
        b_smwdc_L->GetEntry(entry);
         x1 = TMath::QuietNaN();
         y1 = TMath::QuietNaN();
         a1 = TMath::QuietNaN();
         b1 = TMath::QuietNaN();
        for( Int_t p = 0; p < smwdc_S1->GetEntriesFast(); p++){
                x1 = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_L->At(p))->GetTrack())->GetX();
                a1 = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_L->At(p))->GetTrack())->GetA();
                y1 = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_L->At(p))->GetTrack())->GetY();
                b1 = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_L->At(p))->GetTrack())->GetB();
        }
        
        //______________________________________________________________ MWDC-R
        b_smwdc_R->GetEntry(entry);
         x2 = TMath::QuietNaN();
         y2 = TMath::QuietNaN();
         a2 = TMath::QuietNaN();
         b2 = TMath::QuietNaN();
        for( Int_t p = 0; p < smwdc_S1->GetEntriesFast(); p++){
                x2 = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_R->At(p))->GetTrack())->GetX();
                a2 = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_R->At(p))->GetTrack())->GetA();
                y2 = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_R->At(p))->GetTrack())->GetY();
                b2 = ((art::TTrack*)((art::TMWDCTrackingResult*)smwdc_R->At(p))->GetTrack())->GetB();
        }
*/        
        //______________________________________________________________ MWDC-S1
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
        
        Double_t COS = TMath::Cos(13.5*TMath::DegToRad());
        Double_t SIN = TMath::Sin(13.5*TMath::DegToRad());
        Double_t TAN = TMath::Tan(13.5*TMath::DegToRad());
        
        s1xr = s1x / (COS - s1a* SIN);
        s1ar = (s1a + TAN)/(1- s1a*TAN);
        
        //if( TMath::IsNaN(s1x) ) {return kTRUE;}
        //if( s1x> 3 ) {return kTRUE;}
        
        
/*        //_____________________________________________ custom PID caluclation 
        //____find the largest charge in nyoki
        pidZ = 0;
        Int_t hitID = -1;
        for( Int_t p = 0; p < 14; p++){
                if ( qS1[p] > pidZ ) {
                        pidZ = qS1[p];
                        hitID = p;
                }
        }
        if( hitID > -1){ 
                Double_t tofPID = tofS1[hitID];
                // flight length (mm) 
                Double_t fl = 6290.4 -0.451752 * s1x + 0.0003021347 * s1x * s1x ;  
                
                Double_t beta = fl / 299.792458 / tofPID;
                Double_t gamma = 1. / TMath::Sqrt(1 - beta * beta);
                
                // proton number
                pidZ = beta * pidZ;
                
                // brho (Tm) 25F = 7.1315
                Double_t brho = 6.5269 * (1. + s1x / (-1134.8254));
                
                // A/Q 
                pidAOQ = 299.792458 * brho / 931.5 / gamma / beta;
                
                //printf("%d, %f, %f, %f, %f, %f\n",hitID, tofPID, fl, beta, brho, pidAOQ);
        }
*/   

        //______________________________________________________________ PID downstream
        b_pid_s1->GetEntry(entry);
        pidAOQc = pid_s1->GetAOQ(); 
        brhoc   = pid_s1->GetBrho();
        
        Double_t alpha = 299.792458/931.5* brhoc/ pidAOQc;
        
        betac = alpha / TMath::Sqrt(1 + alpha*alpha);
        
        //pidZ = pid_s1->GetZ(); 
        
        
        Double_t nyokiT = TMath::QuietNaN();
        b_nyoki_zt->GetEntry(entry);
        for( Int_t p = 0; p < nyoki_zt->GetEntriesFast(); p++){
                pidZc = ((art::TTimingChargeData*)nyoki_zt->At(p))->GetCharge() ;
                nyokiID = ((art::TTimingChargeData*)nyoki_zt->At(p))->GetAuxID() ;
                nyokiT = ((art::TTimingChargeData*)nyoki_zt->At(p))->GetTiming() ;
                //if ( nyokiT < -270 || nyokiT > -210) nyokiT = TMath::QuietNaN();
        }
        
        tofTgtS1 = nyokiT - tTgt + 28.5;
      
        
        //if( TMath::IsNaN(pidAOQ) ) {return kTRUE;}
        //if( pidZ<5 ) {return kTRUE;}

        //______________________________________________________________ correction
/*         b_s1_c->GetEntry(entry);
         s1xc = TMath::QuietNaN();
         s1xc = s1_c->GetX();
        
        b_tof_c->GetEntry(entry);
         tofc = TMath::QuietNaN();
         tofc = tof_c->GetTiming();
         
         FLc = 299.792458 * betac * tofc;
         
         
/*         FL = 6290.4 + (-0.45172) * s1x + 3.021347e-4*s1x*s1x;
         beta = FL / 299.792458 / tofS1[0];
         Double_t gamma = 1/TMath::Sqrt(1 - beta*beta);
         brho = 6.5269 * (1. + s1x / (-1200));
         pidZ = pidZc;
         pidAOQ = 299.792458/ 931.5 * brho / beta / gamma; */

// FL from tgt to S1 = 7452.26 mm
// FL from tgt to nyoki = 7745.36 mm
// FL from S0D to S1 = 5997.26 mm

         FL = 7745.36 + (-0.00299) * s1xr + (-4.356e-7)*s1xr*s1xr + (1.15187e-10)*s1xr*s1xr*s1xr;
         beta = FL / 299.792458 / (tofTgtS1);
         Double_t gamma = 1/TMath::Sqrt(1 - beta*beta);
         brho = 6.5269 * (1. +(-0.000936409)*s1xr +(7.6898e-7)*s1xr*s1xr +(-3.024e-10)*s1xr*s1xr*s1xr);
         //brho = 6.5269 * (1. - s1xr/1500.);
         pidZ = pidZc;
         pidAOQ = 299.792458/ 931.5 * brho / beta / gamma;
         
         //printf("%f, %f, %f, %f\n", s1xr, FL, tofTgtS1, beta);



        //______________________________________________________________   
        saveFile->cd(); //set focus on this file
        newTree->Fill();  
        
        clock.Stop("timer");
        Double_t time = clock.GetRealTime("timer");
        clock.Start("timer");
      
         if ( !shown ) {
            if (fmod(time, 10) < 1 ){
               printf( "%10d[%2d%%](#%2d) |%3d min %5.2f sec | expect:%5.1fmin %10d\n", 
               entry, 
               TMath::Nint((entry+1)*100./totnumEntry),
               runNum,
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

        //if( entry%1000000  == 0) printf(" readed entris : %10d [%2.0f%%] \n", entry, entry*100./totnumEntry);

        return kTRUE;

   return kTRUE;
}

void Selector_Post::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void Selector_Post::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
        saveFile->cd(); //set focus on this file
        newTree->Write(); 
        saveFile->Close();
        
        printf("-------------- done. %s, %d\n", saveFileName.Data(), count);
}
