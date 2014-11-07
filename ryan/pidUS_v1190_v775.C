#include "constant.h"
#include "RelCalculator.h"
#include "Compress/TBeamData.h"

void pidUS_v1190_v775() {

   const char* rootfile="23F_0924_run08_46.root";
   TBeamData *beam = new TBeamData("23F");
   
   Bool_t BeamTrigger = 0;
   Bool_t ppcoin      = 0;
   Bool_t PIDUSGate   = 0;
   
   Bool_t allentry    = 0;
   Int_t firstEntry   = 0;
   Int_t nEntries     = 500000;
   Int_t runRange[2] = {1, 1};
  
   beam->Print();

//########################################################   
   Double_t Principle_tof = tofByBrho(L_F3FH9,beam->fBrho, beam->fMass, beam->fZ);
   
   TString histTitle;
   histTitle.Form("PID upstream (%s)", rootfile);
   if (BeamTrigger) histTitle += " Beam Trigger";
   if (ppcoin) histTitle+= " ppcoin";
   if (PIDUSGate) histTitle += " PIDUS" + beam->fName;
   
   //gStyle->SetOptStat(0);
   
   TH2F* hPID_US_v1190 = new TH2F("PID_US_v1190",histTitle,300, -1500, -1410, 300 , 4900, 6200);
   hPID_US_v1190->SetXTitle("tof v1190 [ns]");
   hPID_US_v1190->SetYTitle("Q(FH9)");	
   TH2F* hPID_US_v775 = new TH2F("hPID_US_v775","PID up stream v775",300, -340,-280, 300 , 0, 1500);
   hPID_US_v775->SetXTitle("tof v775 [ns]");
   hPID_US_v775->SetYTitle("Q(F3)");
   TH2F* hCharge = new TH2F("hCharge","Charge(FH9)v1190 vs Charge(F3)v775",300, 0, 1500, 300 ,4900, 6200);
   hCharge->SetXTitle("Q(FH9)v775");
   hCharge->SetYTitle("Q(F3)v1190");

   TH2F* hChargeD = new TH2F("hChargeD", "Charge Multi", 300, 0, 1500, 300, 4900, 6200);

   TCanvas* cPidAll = new TCanvas("cPidAll", "PID", 0, 0, 700, 700);
   cPidAll->Divide(2,2);

//#####################################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;

   TClonesArray *hoge_FH9, *hoge_tof, *hoge_V775;
   art::TCoinRegData *hoge_coinReg;
   art::TEventHeader *hoge_run;
   TFile *f = new TFile(rootfile,"read");
   TTree *pid = (TTree*)f->Get("tree");
   Int_t totnumEntry = pid->GetEntries();
   pid->SetBranchStatus("*",0);
   pid->SetBranchStatus("eventheader",1);
   //pid->SetBranchStatus("coinReg",1);
   pid->SetBranchStatus("plaV1190_FH9",1);
   pid->SetBranchStatus("tof_US",1);
   pid->SetBranchStatus("plaV775",1);
     
   pid->SetBranchAddress("eventheader",&hoge_run);  
   //pid->SetBranchAddress("coinReg",&hoge_coinReg);
   pid->SetBranchAddress("plaV1190_FH9",&hoge_FH9);
   pid->SetBranchAddress("tof_US",&hoge_tof);
   pid->SetBranchAddress("plaV775",&hoge_V775); 
   
   art::TTwoSidedPlasticData * data1, * data3;
   art::TTimeDifference *data2;
      
   if (allentry) {
      firstEntry = 0;
      nEntries = totnumEntry;
   }
   
   Int_t hitIDFH9[50], hitID[50];
   Double_t QAveFH9[50], tof[50];
   Double_t QAveV775[5];
   Double_t tAveV775[5];
   Int_t firstRun, lastRun, firstEvID, lastEvID;
   Bool_t firstcheck = 1;
   
   printf("File:%s ==== TotnumEntry:%d, 1stEntry:%d, nEntries:%d[%4.1f%%]\n"
                 , rootfile
                 , totnumEntry
                 , firstEntry
                 , nEntries
                 , nEntries*100./totnumEntry);
   if(BeamTrigger) printf(".. BeamTrigger.\n");
   if(PIDUSGate) printf(".. PID upstream gate.\n");

   Int_t countS, countM, countM_mismatch;

//#############################################################   
   for( Int_t eventID = firstEntry; eventID < TMath::Min(firstEntry+nEntries, totnumEntry); eventID++){
      pid->GetEntry(eventID); 
      
      Int_t runNum = hoge_run->GetRunNumber();
      
      if ( BeamTrigger && hoge_coinReg->Test(1) != 1 ) continue; 
      if ( ppcoin && hoge_coinReg->Test(2) != 1 ) continue; 
      
      for( Int_t p = 0; p <50; p++){
         hitIDFH9[p] = -1;
         hitID[p]    = -2;
         QAveFH9[p]  = TMath::QuietNaN();
         tof[p]      = TMath::QuietNaN();
      }
      
      for(Int_t p = 0; p < 5; p++){
         QAveV775[p] = -1e5;
         tAveV775[p] = -1e5;
      }
      
      
      //Get Charge from FH9  
      Int_t nHit1 =hoge_FH9->GetEntriesFast();
      for(Int_t p = 0; p < nHit1; p++){
         data1 = (art::TTwoSidedPlasticData*)hoge_FH9->At(p) ;
         hitIDFH9[p]   = data1->GetHitID();
         QAveFH9[p]    = data1->GetCharge();
      }
      
      //Get tof
      Int_t nHit2 =hoge_tof->GetEntriesFast();
      for(Int_t p = 0; p < nHit2; p++){
         data2 = (art::TTimeDifference*)hoge_tof->At(p) ;
         hitID[p]       = data2->GetHitID();
         tof[p]         = data2->GetTiming();
      }
      
      Bool_t PIDcheck = 0;
      for (Int_t p = 0; p < nHit1; p++){
         for (Int_t q = 0; q< nHit2; q++){
         	//printf(" %d, %d \n", hitIDFH9[p], hitID[q]);
            if (hitIDFH9[p] == hitID[q]){
               //printf("PID US : %f, %f \n", tof[q], QAveFH9[p]);
               //if ( PIDUSGate && (tof[q] < beam->fTofGate[0] || tof[q] > beam->fTofGate[1])) continue; //PID gate
               //if ( PIDUSGate && (QAveFH9[p] < beam->fQGate[0] || QAveFH9[p] > beam->fQGate[1])) continue; // PID gate
               //PIDcheck = 1;
               hPID_US_v1190->Fill(tof[q],QAveFH9[p]);
            }
         }
      }
      //if ( PIDUSGate && PIDcheck == 0 ) continue;
      
      //Get Charge from V775 
      Int_t nHit =hoge_V775->GetEntriesFast();
      for(Int_t p = 0; p < nHit; p++){
         data3 = (art::TTwoSidedPlasticData*)hoge_V775->At(p) ;
         Int_t detIDV775   = data3->GetDetID();
         QAveV775[detIDV775]    = data3->GetQAve();
         tAveV775[detIDV775]    = data3->GetTAve();
      }
      if ( tAveV775[3] == -1e5 ) continue;    
         
      Double_t tofF3FH9 = tAveV775[3] - tAveV775[2] - beam->fToffsetV775 + Principle_tof;
      Double_t tof1     = tAveV775[0] - tAveV775[3] - tofF3FH9 * LENGTH_RATIO_FH9_TGT ;
      Double_t tof2     = tAveV775[1] - tAveV775[3] - tofF3FH9 * LENGTH_RATIO_FH9_TGT ;
      Double_t tofS0D   = tAveV775[4] - tAveV775[3] - tofF3FH9 * LENGTH_RATIO_FH9_TGT ;
      
      hPID_US_v775->Fill(tAveV775[3]-tAveV775[2], QAveV775[2]);

      if ( nHit1 >= 2) {
        countM ++ ;
        Int_t matchFlag == 0;
        for(Int_t p = 0; p < nHit1; p++){
          //hCharge->Fill(QAveV775[2],QAveFH9[p]);
          if (matchFlag == 0){
            if (TMath::Abs(QAveFH9[p]-2.44*QAveV775[2]-3802)<200){
              matchFlag = 1;
            }   
          }else{
            break;
          }
        }
        if (matchFlag == 0) {
          countM_mismatch ++;
          hCharge->Fill(QAveV775[2], QAveFH9[p]);
        }
      }

      if (nHit1 == 1) {
        hChargeD->Fill(QAveV775[2], QAveFH9[0]);
        countS ++;
      }

//------------Clock      
      clock.Stop("timer");
      Double_t timer = clock.GetRealTime("timer");
      clock.Start("timer");
      
      if ( !shown ) {
         if (fmod(timer, 10) < 1 ){
            printf( "%10d[%2d%%](#%d) |%3d min %5.2f sec | expect:%5.1fmin\n", 
            eventID, 
            TMath::Nint((eventID+1-firstEntry)*100./nEntries),
            runNum,
            TMath::Floor(timer/60), timer - TMath::Floor(timer/60)*60,
            nEntries*timer/(eventID+1-firstEntry)/60.);
            shown = 1;
         }
      }else{
         if (fmod(timer, 10) > 9 ){
            shown = 0;
         }
      }

   }
   
   cPidAll->cd(1);
   hPID_US_v1190->Draw("colz");
   
   cPidAll->cd(2);
   hPID_US_v775->Draw("colz");

   cPidAll->cd(3);
   hCharge->Draw("colz");

   cPidAll->cd(4);
   hChargeD->Draw("colz");

   printf("%d, %d, %d \n", countS, countM, countM_mismatch);

   return ;
}
