#include "constant.h"
#include "RelCalculator.h"
#include "Compress/TBeamData.h"

void pidNyoki() {

//   const char* rootfile="23F_1201_nyoki_run23.root";
   const char* rootfile="23F_1204_nyoki_run2425.root";
   
   Int_t nyokiID[2] = {0,10};
   Bool_t useS0AB = 0;
   Int_t useToFQ = 2; // 0 = z-AoQ, 1 = Q-tof, 2 = z-tof
   Bool_t useSlew = 0;
   
   Bool_t allentry    = 0;
   Int_t firstEntry   = 0;
   Int_t nEntries     = 3000000;

	const Double_t Brho = 6.7288;  
	
	Int_t sampleRate = 1;
	
	Bool_t ppcoin = 1;
	Bool_t beam = 0;
	Bool_t NototherTrig = 0;
	Bool_t pid23F = 1;
	Bool_t pid22O = 0;
	Bool_t pid8Li = 0;
	
	Bool_t fitZ = 0;

//########################################################   

	Double_t LS0DNyoki = 6560.;
	Double_t tofOffSet = 46.4;
	Double_t b,g,h, Sa,Sk,SQ,St;

	b = 500;
	g = 16.5;//15.7;
	h = 0.007288;//0.0064;
	
	Sa = 28.0;
	Sk = 0.240;
	SQ = 500;
	St = 5;

   TString histTitle;
   histTitle.Form("PID Nyoki-%d~%d (%s)", nyokiID[0], nyokiID[1], rootfile);
   if( useS0AB) histTitle += " S0AB gate";
   if( ppcoin) histTitle += " ppcoin";
   if( beam) histTitle += " beam";
   if( pid23F) histTitle += " 23F";
   if( pid22O) histTitle += " 22O";
   if( pid8Li) histTitle += " 8Li";
   
   gStyle->SetOptStat(0);

   TCanvas* cPID = new TCanvas("cPid", "PID", 2000, 0, 1000, 500);
   cPID->Divide(2,1);
   
   TH2F* hPIDNyoki ;
   if( useToFQ==0){
		hPIDNyoki= new TH2F("PID_nyoki",histTitle,400, 1.9, 3.2, 300 , 0, 11);
		hPIDNyoki->SetXTitle("A/Q");
		hPIDNyoki->SetYTitle("Z");	
	}else if( useToFQ == 1){
		hPIDNyoki= new TH2F("PID_nyoki",histTitle,400, 25, 40, 400 , 500, 2000);
		hPIDNyoki->SetXTitle("ToF [ns]");
		hPIDNyoki->SetYTitle("Q");	
   }else if( useToFQ == 2){
		hPIDNyoki= new TH2F("PID_nyoki",histTitle, 100, 28, 45, 110 , 0, 11);
		hPIDNyoki->SetXTitle("ToF [ns]");
		hPIDNyoki->SetYTitle("Z");	
   }
  

//#####################################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;

   TClonesArray *hoge_nyoki, *hoge_tofD1, *hoge_S0img;
   art::TCoinRegData *hoge_coinReg;
	art::TGateArray * gate;

   TFile *f = new TFile(rootfile,"read");
   TTree *pid = (TTree*)f->Get("tree");
   
   Int_t totnumEntry = pid->GetEntries();
	pid->SetBranchStatus("gate",1);
   pid->SetBranchStatus("coinReg",1);
   pid->SetBranchStatus("nyoki",1);
   pid->SetBranchStatus("tof_D1",1);
   if ( useS0AB) pid->SetBranchStatus("S0img",1);


	tree->SetBranchAddress("gate",&gate); 
   pid->SetBranchAddress("coinReg",&hoge_coinReg);
   pid->SetBranchAddress("nyoki",&hoge_nyoki);
   pid->SetBranchAddress("tof_D1",&hoge_tofD1);
   if ( useS0AB) pid->SetBranchAddress("S0img", &hoge_S0img);
      
   if (allentry) {
      firstEntry = 0;
      nEntries = totnumEntry;
   }
   
   Int_t firstRun, lastRun, firstEvID, lastEvID;
   Bool_t firstcheck = 1;
   
   printf("File:%s ==== TotnumEntry:%d, 1stEntry:%d, nEntries:%d[%4.1f%%]\n"
                 , rootfile
                 , totnumEntry
                 , firstEntry
                 , nEntries
                 , nEntries*100./totnumEntry);
                 
  Int_t count = 0;
   
//#############################################################   
   for( Int_t eventID = firstEntry; eventID < TMath::Min(firstEntry+nEntries, totnumEntry); eventID+=sampleRate){
      pid->GetEntry(eventID); 
      
      if( ppcoin && !hoge_coinReg->Test(2) ) continue;
      if( beam && !hoge_coinReg->Test(1) ) continue;
      
      if( NototherTrig && (hoge_coinReg->Test(0) || hoge_coinReg->Test(3) || hoge_coinReg->Test(4) || hoge_coinReg->Test(5) || hoge_coinReg->Test(6)) ) continue;
      
      if( pid23F && gate->Test(0) != 1) continue;
      if( pid22O && gate->Test(1) != 1) continue;
      if( pid8Li && gate->Test(6) != 1) continue;
      
      Double_t tof = -50;
      Double_t QQ = -50;
      Double_t beta = 0;
      Bool_t tofPass = 0;
      Bool_t QQPass = 0;
      
      Double_t s0a = -500;
      Double_t s0b = -500;
      
      //Get Charge from nyoki
      Int_t nHit1 =hoge_nyoki->GetEntriesFast();
      for(Int_t p = 0; p < nHit1; p++){
         data1 = (art::TTwoSidedPlasticData*)hoge_nyoki->At(p) ;
         Int_t ID   = data1->GetID();
         //printf(", QQ ID: %d ", ID);
         if( ID >= nyokiID[0] && ID <= nyokiID[1]) {
         	QQ  = data1->GetCharge();
            QQPass = 1;
      	}else{	
            continue;
      	}
      }

      if( QQPass == 0 ) continue;
      
      //Get tof_D1
      Int_t nHit2 =hoge_tofD1->GetEntriesFast();
      for(Int_t p = 0; p < nHit2; p++){
         data2 = (art::TTimeDifference*)hoge_tofD1->At(p) ;
         Int_t ID = data2->GetID();
         //printf("tof ID: %d ", ID);
         if ( ID >= nyokiID[0] && ID <= nyokiID[1]) {
         	//Slew 
         	Double_t walk = Sa/TMath::Power(QQ-SQ,Sk) - St;
         	if( useSlew == 0) walk = 0;
         	tof = data2->GetTiming() + tofOffSet - walk;
         	//printf("%10.2f , %10.2f \n", tof, walk);
         	beta = LS0DNyoki/cVaccum/tof;
         	tofPass = 1;
      	}else{
      		continue;
      	}
      }
      
      if( tofPass == 0 ) continue;
      
      if( tof<27 || tof>46 ) continue;
      
      //Get S0img
      if( useS0AB ){
		   Int_t nHit = hoge_S0img->GetEntriesFast();
		   for( Int_t p = 0; p < nHit; p++){
		      art::TMWDCTrackingResult * xyS0 = (art::TMWDCTrackingResult*)hoge_S0img->At(p);
		      art::TTrack * trackS0 = (art::TTrack*)xyS0->GetTrack();
		      //s0x = trackS0->GetX();
		      //s0y = trackS0->GetY();
		      s0a = trackS0->GetA()*1000; // (mrad)
		      s0b = trackS0->GetB()*1000; // (mrad)
		   }      
		   if( TMath::Abs(s0a)>10 || TMath::Abs(s0b)>10 ) continue;  
		}
		
		count += 1;
		
		if( useToFQ == 1){
		   //printf("Q:%6.0f, tof:%6.2f \n", QQ, tof);
			hPIDNyoki->Fill(tof,QQ);
			
		}else{
		   Double_t gamma = 1./TMath::Sqrt(1-beta*beta);
		   //hPIDNyoki->Fill(tof[q],QAveFH9[p]);
		   Double_t AoQ = cVaccum*Brho/mu/gamma/beta;
		   //Double_t Zvalue = 0.0073*QAveFH9[p]-33.6; 
		   Double_t L = (QQ-b);
		   Double_t z = TMath::Sqrt(L/(g-L*h))*beta;
		   //hPIDNyoki->Fill(AQ,QAveFH9[p]);
		   
		   if( useToFQ==0) hPIDNyoki->Fill(AoQ,z);
		   if( useToFQ==2) hPIDNyoki->Fill(tof,z);
		}
		
  
//------------Clock      
      clock.Stop("timer");
      Double_t timer = clock.GetRealTime("timer");
      clock.Start("timer");
      
      if ( !shown ) {
         if (fmod(timer, 10) < 1 ){
            printf( "%10d[%2d%%] |%3d min %5.2f sec | expect:%5.1fmin\n", 
            eventID, 
            TMath::Nint((eventID+1-firstEntry)*100./nEntries),
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
   
   printf(" total count = %d\n", count);
   
   cPID->cd(1);
   hPIDNyoki->Draw("colz");
   
   cPID->cd(2);
   hPIDNyoki->ProjectionY("test")->Draw();
   
   if( fitZ ){
		TF1 * fit = new TF1("fit", "gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)+gaus(15)+gaus(18)+gaus(21)", 1.8, 11);
		Double_t par[24] = {1000, 2, 0.2, 1500, 3, 0.2, 800, 4, 0.2, 500, 5, 0.5, 400, 6, 0.5, 1000, 7, 0.5, 7000, 8, 0.5, 5500, 9, 0.5};
		fit->SetParameters(par);
		fit->SetParLimits(1,1.8, 2.2);
		fit->SetParLimits(4,2.7, 3.3);
		fit->SetParLimits(7,3.7, 4.3);
		fit->SetParLimits(10,4.7, 5.3);
		fit->SetParLimits(13,5.7, 6.3);
		fit->SetParLimits(16,6.7, 7.3);
		fit->SetParLimits(19,7.7, 8.5);
		fit->SetParLimits(22,8.7, 9.5);
		test->Fit("fit", "R");
	}
   return ;
}
