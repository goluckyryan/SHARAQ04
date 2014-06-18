#include "constant.h"

void MWDC_TimeGateAnalysis() {

//############################################################################  
   //const char* rootfile="ppDown.root"; 
   const char* rootfile="ppAll_0617_mwdctime.root";
   //const char* rootfile="/media/ResearchData/sharaq04/ppUp.root";
   //const char* rootfile="phys14_45_67.root";
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=500;
   Bool_t histonoff = 1; // 0 = off 
   
//############################################################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;

   if ( histonoff ){
      TCanvas * cMWDC = new TCanvas("cMWDC_TimeGate", "cMWDC_TimeGate", 100, 50, 800, 800);
      cMWDC_TimeGate->Divide(2,2);
      
      TH1F** hTL = new TH1F*[4];
      TH1F** hTrackID = new TH1F*[4];
      TH1F** hSSR = new TH1F*[4];
      for (Int_t i = 0; i < 4; i++){
      	TString hTitle;
      	hTitle.Form("TL%1d",i);
      	hTL[i] = new TH1F(hTitle, hTitle, 200, -200, 200);
      	hTL[i] -> SetLineColor(i+1);
      	hTitle.Form("TrackID-%d",i);
      	hTrackID[i] = new TH1F(hTitle, hTitle, 2, 0, 2);
      	hTrackID[i] -> SetLineColor(i+1);
      	hTitle.Form("SSR-%d",i);
      	hSSR[i] = new TH1F(hTitle, hTitle, 100, 0, 0.4);
      	hSSR[i] -> SetLineColor(i+1);
      }
      
   }
 
//############################################################################
   art::TEventHeader *hoge_run;
   TClonesArray *hoge_DT, *hoge1, *hoge2, *hoge3, *hoge4;
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded.\n",rootfile);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("eventheader",1);
   tree->SetBranchStatus("smwdc_L_DT",1);
   tree->SetBranchStatus("smwdc_L",1);
   tree->SetBranchStatus("smwdc_L_TLgated",1);
   tree->SetBranchStatus("smwdc_L_TWgated",1);
   tree->SetBranchStatus("smwdc_L_TLTWgated",1);

   tree->SetBranchAddress("eventheader",&hoge_run);
   tree->SetBranchAddress("smwdc_L_DT",&hoge_DT);
   tree->SetBranchAddress("smwdc_L",&hoge1);
   tree->SetBranchAddress("smwdc_L_TLgated",&hoge2);
   tree->SetBranchAddress("smwdc_L_TWgated",&hoge3);
   tree->SetBranchAddress("smwdc_L_TLTWgated",&hoge4);

	TClonesArray * * hoge_L = new TClonesArray*[4];
	hoge_L[0] = hoge1;
	hoge_L[1] = hoge2;
	hoge_L[2] = hoge3;
	hoge_L[3] = hoge4;

//############################################################################   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   
   //ToGet ClassName
   //hoge->At(0)->ClassName()
	art::TMWDCTrackingResult * * xy = new art::TMWDCTrackingResult[4];
	art::TTimingChargeData * DT;
	
   float ** AdoptedTL = new float*[4];
   float ** AdoptedTW = new float*[4];
   for ( int i = 0 ; i < 4; i ++){
   	AdoptedTL[i] = new float[6];
   	AdoptedTW[i] = new float[6]; 
   	for ( int j = 0 ; j < 6; j ++){ 
   		AdoptedTL[i][j] = kInvalidD;
   		AdoptedTW[i][j] = kInvalidD;
   	}
   }
	
//###############################################################################
   for( Int_t eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID);
      //printf(" %6d --------------------------- \n", eventID);
      
		//----------------Get Event Number
      Int_t runNum = hoge_run->GetRunNumber();
      
		//----------------Get SMWDC data
		int AdoptedWireID[4][6];
   	int trackID[4] = {-1,-1,-1,-1};
   	float SSR[4] = {kInvalidD,kInvalidD,kInvalidD,kInvalidD};
		for( Int_t i = 0; i < 4; i++){
      	Int_t nHit = hoge_L[i]->GetEntriesFast();
      	for( Int_t p = 0; p < nHit; p++){
         	xy[i] = (art::TMWDCTrackingResult*)hoge_L[i]->At(p);
         	trackID[i] = xy[i]->IsGood();
         	SSR[i] = xy[i]->GetSSR();
         	//printf(" gate:%1d, GoodTrack:%3d, SSR:%10.7f | ", i, xy[i]->IsGood(), xy[i]->GetSSR());
         	//printf("Adopted WireID:: ");
         	for(Int_t k = 0; k < 6; k++){
         		AdoptedWireID[i][k] = xy[i]->GetWireIDAdopted(k);
         		//printf("%2d, ", AdoptedWireID[i][k]); 
      		}
      		//printf("\n");
      	}
      	hTrackID[i] -> Fill(trackID[i]);
      	hSSR[i] -> Fill(SSR[i]);
      }
      

      for ( int i = 0 ; i < 4; i ++){
      	for ( int j = 0 ; j < 6; j ++){ 
      		AdoptedTL[i][j] = kInvalidD;
      		AdoptedTW[i][j] = kInvalidD;
      	}
      }
      
		//----------------Get DT data
		Int_t nHitDT = hoge_DT->GetEntriesFast();
		float TL = new float[nHitDT];
		float TW = new float[nHitDT];
		int   planeID = new int[nHitDT];
		int   wireID  = new int[nHitDT];
		for (Int_t p = 0; p < nHitDT; p++){
			DT = (art::TTimingChargeData*) hoge_DT->At(p);
			TL[p] = DT->GetTiming();
			TW[p] = DT->GetCharge();
			Int_t detID = DT->GetDetID() + 1;
			if (detID < 57) {planeID[p] = 1; wireID[p] = detID;}
			if (detID >=  57 && detID < 113) {planeID[p] = 2; wireID[p] = detID -  56;}
			if (detID >= 113 && detID < 157) {planeID[p] = 3; wireID[p] = detID - 112;}
			if (detID >= 157 && detID < 201) {planeID[p] = 4; wireID[p] = detID - 156;}
			if (detID >= 201 && detID < 245) {planeID[p] = 5; wireID[p] = detID - 200;}
			if (detID >= 245 ) {planeID[p] = 6; wireID[p] = detID - 244;} 
			//printf(" %2d, plane:%2d, wireID:%2d, TL:%7.2f, TW:%7.2f", p, planeID[p], wireID[p], TL[p], TW[p]);			
			
			for( Int_t k = 0 ; k < 6; k++){
				bool matched = 0;
				for ( int i = 0; i < 4; i++){
					if ( planeID[p] == k+1 && wireID[p] == AdoptedWireID[i][k]){
		   			AdoptedTL[i][k] = TL[p];
		   			AdoptedTW[i][k] = TW[p];
		   			//printf("   matched (%1d)", i);
		   			matched = 1;
					}	
					if ( matched ) hTL[i] -> Fill(AdoptedTL[i][k]);
				}
			}
			//printf("\n");
		} 
         

		//------------Clock      
      clock.Stop("timer");
      Double_t time = clock.GetRealTime("timer");
      clock.Start("timer");
      
      if ( !shown ) {
         if (fmod(time, 10) < 1 ){
            printf( "%10d[%2d%%](#%2d) |%3d min %5.2f sec | expect:%5.1fmin\n", 
            eventID, 
            TMath::Nint((eventID+1-firstEntry)*100./nEntries),
            runNum,
            TMath::Floor(time/60), time - TMath::Floor(time/60)*60,
            nEntries*time/(eventID+1-firstEntry)/60.);
            shown = 1;
         }
      }else{
         if (fmod(time, 10) > 9 ){
            shown = 0;
         }
      }
      
   }
   
   
   if ( histonoff ){
      cMWDC_TimeGate->cd(1);
      for( Int_t i = 0; i < 4; i++){
      	hTL[i]->Draw("same");
      }
      
      cMWDC_TimeGate->cd(2);
      for( Int_t i = 0; i < 4; i++){
      	hTrackID[i]->SetMaximum(totnumEntry);
      	hTrackID[i]->Draw("same");
      }
      
      cMWDC_TimeGate->cd(3);
      for( Int_t i = 0; i < 4; i++){
         hSSR[i]->SetMaximum(30000);
      	hSSR[i]->Draw("same");
      }
   }
   
//##############################################################################   
   clock.Stop("timer");
   printf("============ finished|%10.3f sec = %10.3f min\n",clock.GetRealTime("timer"), clock.GetRealTime("timer")/60.);
	
   return ;
}
