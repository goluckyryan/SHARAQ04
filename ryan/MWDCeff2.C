
void MWDCeff2() {

//############################################################################  
   //const char* rootfile="ppDown.root"; 
   const char* rootfile="PrimaryData/ppAll_0613.root";
   //const char* rootfile="/media/ResearchData/sharaq04/ppUp.root";
   //const char* rootfile="phys14_45_67.root";
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=10000;
   Double_t DTgate1[2] = {-5, -3};
   Double_t DTgate2[2] = {1, 3};
   
   Bool_t histonoff = 1; // 0 = off 
   
//############################################################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;

   if ( histonoff ){
   	gStyle->SetOptStat(0);
      TCanvas * cMWDC = new TCanvas("cMWDC", "Charge of Tpla", 100, 50, 800, 800);
      cMWDC->Divide(2,3);
   	
		TH2F * hDTX1 = new TH2F("hDTX1", "DT1 vs X1", 400, -1000,  200, 200, -17,  7);
		TH2F * hDTX2 = new TH2F("hDTX2", "DT2 vs X2", 400,  -200, 1000, 200,  -9, 12);
		
		TH1F * hNVPlane1 = new TH1F("NVPlane1", "NValidPlane 1", 7,0,7);
		TH1F * hNVPlane2 = new TH1F("NVPlane2", "NValidPlane 2", 7,0,7);
		
		TH1F * hGood1 = new TH1F("hGood1", "IsGood 1", 2, 0, 2);
		hGood1->SetMinimum(0);
		TH1F * hGood2 = new TH1F("hGood2", "IsGood 2", 2, 0, 2);
		hGood2->SetMinimum(0);
	}
 
//############################################################################
   art::TEventHeader *hoge_run;
   TClonesArray *hoge_V775, *hoge_L, *hoge_R;
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded.\n",rootfile);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("eventheader",1);
   tree->SetBranchStatus("plaV775",1);    //get charge and time
   tree->SetBranchStatus("smwdc_L",1);
   tree->SetBranchStatus("smwdc_R",1);

   tree->SetBranchAddress("eventheader",&hoge_run);
   tree->SetBranchAddress("plaV775",&hoge_V775);
   tree->SetBranchAddress("smwdc_L",&hoge_L);
   tree->SetBranchAddress("smwdc_R",&hoge_R);

//############################################################################   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   
   art::TTwoSidedPlasticData * V775Data;
   art::TMWDCTrackingResult * xy1,* xy2;
   art::TTrack * track1, * track2;
   
   Int_t countN6[2] = {0,0}; // 6 plane fired
   Int_t countN5[2] = {0,0};
   Int_t countN4[2] = {0,0};
   Int_t countN3[2] = {0,0};
   Int_t countN2[2] = {0,0};
   Int_t countN1[2] = {0,0}; 
   Int_t countN5comp[2][6]; // N5[i], i is missing plane
   Int_t countQ[2] = {0,0}; // total hit from Tpla
   Int_t countGood[2] = {0,0};
   Int_t countBad[2] = {0,0};
   
   for ( Int_t i = 0; i < 2; ++i ) {
      for (Int_t j = 0; j < 6; ++j ) {
         countN5comp[i][j] = 0;
      }
   } 

//###############################################################################
   for( Int_t eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID);
      
//----------------Get Event Number
      Int_t runNum = hoge_run->GetRunNumber();
      
//---------------Get charge DS of Tpla and S0D
      Double_t QTpla[2] = {-10,-10};
      Double_t tdiff[2] = {-1e3,-1e3};
      Int_t nHit = hoge_V775->GetEntriesFast();
      if ( nHit == 0 ) continue;
      for ( Int_t p = 0; p < nHit; p++){
         V775Data = (art::TTwoSidedPlasticData*)hoge_V775->At(p);
         Int_t DetID     = V775Data->GetDetID();
         if ( DetID >= 2 ) continue;
         QTpla[DetID]    = V775Data->GetCharge(); 
         tdiff[DetID]    = V775Data->GetTDiff();
      }

//---------Get SMWDC image, should be one 1 instance  
      if ( tdiff[0] > DTgate1[0] && tdiff[0] < DTgate1[1] ){
      	
         Int_t nHit = hoge_L->GetEntriesFast();
         Int_t NValidPlane = 0;
         for( Int_t p = 0; p < nHit; p++){
         
            xy1 = (art::TMWDCTrackingResult*)hoge_L->At(p);      
            NValidPlane = xy1 -> GetNPlaneValid();
            if ( NValidPlane == 0) continue;
            
            track1 = (art::TTrack *)xy1->GetTrack();
            
            if ( xy1->IsGood()) {
            	countGood[0] ++;
            }else{
            	countBad[0] ++;
         	}
         	
            if (NValidPlane > 0 ) countQ[0]++;
            if ( NValidPlane == 6 ) countN6[0] ++ ; // count for validPlane == 6
            if ( NValidPlane == 5 ) {  // count number of each plane for validPlane == 5
               countN5[0]++;
               for ( Int_t i = 0; i<6 ; i++){
                  if (xy1->GetWireIDAdopted(i) == -1) countN5comp[0][i] ++; //missing
               }
            }
            if ( NValidPlane == 4 ) countN4[0] ++;
            if ( NValidPlane == 3 ) countN3[0] ++;
            if ( NValidPlane == 2 ) countN2[0] ++;
            if ( NValidPlane == 1 ) countN1[0] ++;
            
         }
         if ( histonoff && NValidPlane > 0) {
         	hDTX1->Fill(track1->GetX(), tdiff[0]);
         	hNVPlane1->Fill(NValidPlane);
         	hGood1->Fill(xy1->IsGood());
         }
      }
      
      if ( tdiff[1] > DTgate2[0] && tdiff[1] < DTgate2[1] ){	
      
         Int_t nHit = hoge_R->GetEntriesFast();
         Int_t NValidPlane = 0;
         for( Int_t p = 0; p < nHit; p++){
         
            xy2 = (art::TMWDCTrackingResult*)hoge_R->At(p);      
            NValidPlane = xy2 -> GetNPlaneValid();
            if ( NValidPlane == 0) continue;
            
            track2 = (art::TTrack *)xy2->GetTrack();
            
            if ( xy2->IsGood()) {
            	countGood[1] ++;
            }else{
            	countBad[1] ++;
         	}
            
            if (NValidPlane > 0 ) countQ[1]++;
            if ( NValidPlane == 6 ) countN6[1] ++ ; // count for validPlane == 6
            if ( NValidPlane == 5 ) {  // count number of each plane for validPlane == 5
               countN5[1]++;
               for ( Int_t i = 0; i<6 ; i++){
                  if (xy2->GetWireIDAdopted(i) == -1) countN5comp[1][i] ++; //missing
               }
            }
            if ( NValidPlane == 4 ) countN4[1] ++;
            if ( NValidPlane == 3 ) countN3[1] ++;
            if ( NValidPlane == 2 ) countN2[1] ++;
            if ( NValidPlane == 1 ) countN1[1] ++;
            
         }
         if ( histonoff && NValidPlane > 0) {
         	hDTX2->Fill(track2->GetX(), tdiff[1]);
         	hNVPlane2->Fill(NValidPlane);
         	hGood2->Fill(xy2->IsGood());
         }
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
   
   //########### Draw Histogram
   if ( histonoff ){
   	TLatex text;
   	TString textstr;
   	
      cMWDC->cd(1);
      hDTX1->Draw("colz");
      textstr.Form("%4.1f<DT<%4.1f, countQ:%6d", DTgate1[0],DTgate1[1], countQ[0]);
      text.DrawText(-800,-15,textstr);
      
      cMWDC->cd(2);
      hDTX2->Draw("colz");
      textstr.Form("%4.1f<DT<%4.1f, countQ:%6d", DTgate2[0],DTgate2[1], countQ[0]);
      text.DrawText(0,-6,textstr);
      
      cMWDC->cd(3);
      hNVPlane1->Draw();
      text.SetTextAngle(90);
//		text.SetTextSize(0.04);
		text.DrawText(0.5,2,"gate out");
		textstr.Form("%6d",countN1[0]); text.DrawText(1.5,countN6[0]/2,textstr);
   	textstr.Form("%6d",countN2[0]); text.DrawText(2.5,countN6[0]/2,textstr);
   	textstr.Form("%6d",countN3[0]); text.DrawText(3.5,countN6[0]/2,textstr);
   	textstr.Form("%6d",countN4[0]); text.DrawText(4.5,countN6[0]/2,textstr);
   	textstr.Form("%6d",countN5[0]); text.DrawText(5.5,countN6[0]/2,textstr);
   	textstr.Form("%6d",countN6[0]); text.DrawText(6.5,countN6[0]/2,textstr);
      
      cMWDC->cd(4);
      hNVPlane2->Draw();
		text.DrawText(0.5,2,"gate out");
		textstr.Form("%6d",countN1[1]); text.DrawText(1.5,countN6[1]/2,textstr);
   	textstr.Form("%6d",countN2[1]); text.DrawText(2.5,countN6[1]/2,textstr);
   	textstr.Form("%6d",countN3[1]); text.DrawText(3.5,countN6[1]/2,textstr);
   	textstr.Form("%6d",countN4[1]); text.DrawText(4.5,countN6[1]/2,textstr);
   	textstr.Form("%6d",countN5[1]); text.DrawText(5.5,countN6[1]/2,textstr);
   	textstr.Form("%6d",countN6[1]); text.DrawText(6.5,countN6[1]/2,textstr);
   	
      cMWDC->cd(5);
      hGood1->Draw();
   	textstr.Form("%8d",countBad[0]) ; text.DrawText(0.5,countGood[0]/2, textstr);
   	textstr.Form("%8d",countGood[0]); text.DrawText(1.5,countGood[0]/2, textstr);
   	
      cMWDC->cd(6);
      hGood2->Draw();
   	textstr.Form("%8d",countBad[1]) ; text.DrawText(0.5,countGood[1]/2, textstr);
   	textstr.Form("%8d",countGood[1]); text.DrawText(1.5,countGood[1]/2, textstr);   
	}
   
   //##############  calculation efficiency
   Double_t eff[2][6]; // efficiency of each plane e1, e2, e3, e4, e5, e6 
   Double_t effgm[2] = {1,1}; // Geometric mean of efficiency = Power(e1 e2 e3 e4 e5 e6, 1/6);
   Double_t effavg[2] = {0,0}; // average efficiency = 6*N6/(6*N6+N5)
   Int_t N0[2] = {0,0}; // deduced N0, number of particle pass through ~ countQ;
   
   for ( Int_t i = 0; i < 2; i++){ // L and R
      for ( Int_t j = 0; j < 6; j++){ // plane
         eff[i][j] = (double)countN6[i]/(countN6[i]+countN5comp[i][j]); // in decimal
         effgm[i] = effgm[i]*eff[i][j]; 
         printf("countN6[%1d]=%5d, countN5comp[%1d][%1d]=%5d, eff = %4.1f \n", i, countN6[i], i,j, countN5comp[i][j], eff[i][j]*100.);
      }
      effavg[i] = (double)6*countN6[i]/(6*countN6[i] + countN5[i]);
      N0[i] = countN6[i]/effgm[i];
   }
  
   clock.Stop("timer");
   printf("============ finished|%10.3f sec = %10.3f min\n",clock.GetRealTime("timer"), clock.GetRealTime("timer")/60.);
   printf("countQ     :%10d\t\t\t%10d \n", countQ[0], countQ[1]);
   
   printf("countN6    :%10d \t\t\t%10d \n",  countN6[0], countN6[1]);
   printf("countN5    :%10d \t\t\t%10d \n",  countN5[0], countN5[1]);
   for ( Int_t i = 0; i < 6; i++){
      printf("countN5[%1d] :%10d[%4.1f%%] \t%10d[%4.1f%%] \n", i,countN5comp[0][i], eff[0][i]*100.,countN5comp[1][i], eff[1][i]*100. );
   }
   printf("effgm      :%10.2f%% \t\t%10.2f%% \t\t%10.2f%%\n",  effgm[0]*100, effgm[1]*100, effgm[0]*effgm[1]*100);
   printf("effavg     :%10.2f%% \t\t%10.2f%% \n",  effavg[0]*100, effavg[1]*100);
   printf("countNtot  :%10d[%4.1f%%] \t\t%10d[%4.1f%%] \n", N0[0] ,N0[0]*100./countQ[0] ,N0[1] ,N0[1]*100./countQ[1]);
   //printf("countN4    :%10d \t\t\t%10d \n",  countN4[0], countN4[1]);
   //printf("countN3    :%10d \t\t\t%10d \n",  countN3[0], countN3[1]);
   //printf("countN2    :%10d \t\t\t%10d \n",  countN2[0], countN2[1]);
   //printf("countN1    :%10d \t\t\t%10d \n",  countN1[0], countN1[1]);

   return ;
}
