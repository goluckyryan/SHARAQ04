#include "constant.h"
#include "RelCalculator.h"
#include "Compress/TBeamData.h"

void pidS0D() {

   const char* rootfile="23F_1117_nyoki.root";
   TBeamData *beam = new TBeamData("23F");
   
   Bool_t BeamTrigger = 0;
   Bool_t ppcoin      = 0;
   Bool_t PIDUSGate   = 1;
   
   Bool_t allentry    = 1;
   Int_t firstEntry   = 0;
   Int_t nEntries     = 100000;
   Int_t runRange[2] = {0, 46};
  
   beam->Print();

//########################################################   
   Double_t Principle_tof = tofByBrho(L_F3FH9,beam->fBrho, beam->fMass, beam->fZ);
   
   TString histTitle;
   histTitle.Form("PID upstream (%s)", rootfile);
   if (BeamTrigger) histTitle += " Beam Trigger";
   if (ppcoin) histTitle+= " ppcoin";
   if (PIDUSGate) histTitle += " PIDUS" + beam->fName;
   
   gStyle->SetOptStat(0);
   
   TH2F* hPIDUS = new TH2F("PID_US",histTitle,300, -1500, -1410, 300 , 4900, 6200);
   hPIDUS->SetXTitle("tof before offset [ns]");
   hPIDUS->SetYTitle("Q(FH9)");	
   TH1F* hCoinReg = new TH1F("hCoinReg", "Coin Reg", 3, 0, 3);
   hCoinReg->SetXTitle("0 = others, 1 = Beam, 2 = ppcoin");
   
   TH2F* hPIDDS_S0D = new TH2F("hPIDDS_S0D","PID down stream",300, -127,-120, 300 , 1200, 2500);
   hPIDDS_S0D->SetXTitle("tof before offset [ns]");
   hPIDDS_S0D->SetYTitle("Q");
   TH2F* hPIDDS_S0Dppcoin = new TH2F("hPIDDS_S0Dppcoin","PID DS ppcoin",300, -130, -125, 300 ,1200, 2500);
   hPIDDS_S0Dppcoin->SetXTitle("tof before offset [ns]");
   hPIDDS_S0Dppcoin->SetYTitle("Q");
   
   TCanvas* cPidS0D = new TCanvas("cPidS0D", "PID", 0, 0, 800, 800);
   cPidS0D->Divide(2,2);

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
   pid->SetBranchStatus("coinReg",1);
   pid->SetBranchStatus("plaV1190_FH9",1);
   pid->SetBranchStatus("tof_US",1);
   pid->SetBranchStatus("plaV775",1);
     
   pid->SetBranchAddress("eventheader",&hoge_run);  
   pid->SetBranchAddress("coinReg",&hoge_coinReg);
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
   
//#############################################################   
   for( Int_t eventID = firstEntry; eventID < TMath::Min(firstEntry+nEntries, totnumEntry); eventID++){
      pid->GetEntry(eventID); 
      
      Int_t runNum = hoge_run->GetRunNumber();
      if ( runNum < runRange[0]) continue; 
      //if ( runNum == 19 ) continue; 
      if ( runNum > runRange[1]) break;
      if ( firstcheck) {
         firstRun = runNum;
         firstEvID = eventID;
         firstcheck = 0;
      }
      lastRun = runNum;
      lastEvID = eventID;
      
//      if ( BeamTrigger && hoge_coinReg->Test(1) != 1 ) continue; 
//      if ( ppcoin && hoge_coinReg->Test(2) != 1 ) continue; 
  	    
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
               if ( PIDUSGate && (tof[q] < beam->fTofGate[0] || tof[q] > beam->fTofGate[1])) continue; //PID gate
               if ( PIDUSGate && (QAveFH9[p] < beam->fQGate[0] || QAveFH9[p] > beam->fQGate[1])) continue; // PID gate
               PIDcheck = 1;
               hPIDUS->Fill(tof[q],QAveFH9[p]);
            }
         }
      }
      if ( PIDUSGate && PIDcheck == 0 ) continue;
      
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
      Double_t tofS0D   = tAveV775[4] - tAveV775[3] - tofF3FH9 * LENGTH_RATIO_FH9_TGT ;
      
      if (hoge_coinReg->Test(2) == 1 ){
      	hPIDDS_S0Dppcoin->Fill(tofS0D,QAveV775[4]);
      } 
      hPIDDS_S0D->Fill(tofS0D,QAveV775[4]);
      
      // coinReg
      if( hoge_coinReg->Test(1) == 1){
      	hCoinReg->Fill(1);
   	}else if (hoge_coinReg->Test(2) == 1){
   		hCoinReg->Fill(2);
		}else{
			hCoinReg->Fill(0);
		}
	
		//printf("PID DS : %d, %f \n", tofS0D, QAveV775[4]);
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
   
   cPidS0D->cd(1);
   hPIDUS->Draw("colz");
   
   TLatex text;
   text.SetNDC();
   text.SetTextColor(1);
   TString textStr;
   textStr.Form("event:(%d[#%d],%d[#%d])",firstEvID, firstRun, lastEvID, lastRun) ;
   text.DrawText(0.15, 0.2, textStr);
   
   cPidS0D->cd(2);
   hCoinReg->Draw();
   
   cPidS0D->cd(3);
   hPIDDS_S0D->Draw("colz");
   cPidS0D->cd(4);
   hPIDDS_S0Dppcoin->Draw("colz");

   return ;
}
