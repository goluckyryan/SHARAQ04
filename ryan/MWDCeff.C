
void MWDCeff() {

//############################################################################  
   //const char* rootfile="ppDown.root"; 
   const char* rootfile="PrimaryData/ppAll_0613.root";
   //const char* rootfile="/media/ResearchData/sharaq04/ppUp.root";
   //const char* rootfile="phys14_45_67.root";
   Bool_t ValidorTracked = 0; // 0 = Valid, 1 = tracked
   Bool_t allentry  = 0;
   Int_t firstEntry = 0;
   Int_t nEntries=100000;
   Double_t Qgate = 800;
   Double_t Xgate[2] = {-600, -400};
   Bool_t histonoff = 1; // 0 = off 
   
//############################################################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;

   if ( histonoff ){
      TCanvas * cMWDC = new TCanvas("cMWDC", "Charge of Tpla", 100, 50, 800, 800);
      cMWDC->Divide(2,2);
   }
   TH1F * hQ1  = new TH1F("Q1", "Q1", 100, 0, 3000);
   TH1F * hQ2  = new TH1F("Q2", "Q2", 100, 0, 3000);
   hQ1->SetLineColor(4);
   hQ2->SetLineColor(2);
   TH1F * htdiff1  = new TH1F("tdiff1", "Tdiff1", 100, -15, 15);
   TH1F * htdiff2  = new TH1F("tdiff2", "Tdiff2", 100, -15, 15);
   htdiff1->SetLineColor(4);
   htdiff2->SetLineColor(2);
   
   TH2F * hQ1Plane = new TH2F("Q1Plane", "Q1 vs NValidPlane1", 7, 0, 7, 200, 0, 3000);
   TH2F * hQ2Plane = new TH2F("Q2Plane", "Q2 vs NValidPlane2", 7, 0, 7, 200, 0, 3000);
   
   TH1F * hNVPlane1 = new TH1F("NVPlane1", "NValidPlane 1", 7,0,7);
   TH1F * hNVPlane2 = new TH1F("NVPlane2", "NValidPlane 2", 7,0,7);
   
 
//############################################################################
   art::TEventHeader *hoge_run;
   TClonesArray *hoge_V775, *hoge_L, *hoge_R;
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded.\n",rootfile);
   TTree *tree = (TTree*)f->Get("tree");
   //tree->Scan("plaV775.fID:plaV775.fQAve:smwdc_L.GetTrackingID():smwdc_L.fNPlaneValid:smwdc_L.fWireIDAdopted:smwdc_R.GetTrackingID():smwdc_R.fNPlaneValid:smwdc_R.fWireIDAdopted","","",nEntries+1,firstEntry);
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
   
   Int_t countN6[3]; // 6 plane fired
   Int_t countN5comp[3]; 
   Int_t countN5[3][6];
   Int_t countQ[3];
   Int_t countN4[3];
   Int_t countN3[3];
   Int_t countN2[3];
   Int_t countN1[3];
   Int_t countN0[3];
   
   for ( Int_t i = 0; i < 3; ++i ) {
      countN6[i] = 0;
      countN5comp[i] = 0;
      countQ[i] = 0;
      countN4[i] = 0;
      countN3[i] = 0;
      countN2[i] = 0;
      countN1[i] = 0;
      countN0[i] = 0;
      for (Int_t j = 0; j < 6; ++j ) {
         countN5[i][j] = 0;
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
      Int_t mwdcBoth = 0;
      if ( QTpla[0] > Qgate ){
         Int_t nHit = hoge_L->GetEntriesFast();
         for( Int_t p = 0; p < nHit; p++){
            xy1 = (art::TMWDCTrackingResult*)hoge_L->At(p);
            if ( ValidorTracked == 1 && xy1 -> GetTrackingID() != 1) continue;
         
            Int_t NValidPlane = xy1 -> GetNPlaneValid();
            //track1 = (art::TTrack *)xy1->GetTrack();
            
            //if ( track1->GetX() < Xgate[0] || track1->GetX() > Xgate[1] ) continue; 
            
            if (NValidPlane > 0 ) countQ[0]++;
            
            if ( NValidPlane >= 5 ) mwdcBoth ++;
            if ( NValidPlane == 6 ) countN6[0] ++ ; // count for validPlane == 6
            if ( NValidPlane == 5 ) {  // count number of each plane for validPlane == 5
               countN5comp[0]++;
               for ( Int_t i = 0; i<6 ; i++){
                  if (xy1->GetWireIDAdopted(i) == -1) countN5[0][i] ++; //missing
               }
            }
            if ( NValidPlane == 4 ) countN4[0] ++;
            if ( NValidPlane == 3 ) countN3[0] ++;
            if ( NValidPlane == 2 ) countN2[0] ++;
            if ( NValidPlane == 1 ) countN1[0] ++;
            if ( NValidPlane == 0 ) countN0[0] ++;
         }
         hQ1->Fill(QTpla[0]);
         htdiff1->Fill(tdiff[0]+5);
         hQ1Plane->Fill(NValidPlane, QTpla[0]);
         hNVPlane1->Fill(NValidPlane);
      }
      
      if ( QTpla[1] > Qgate ){
         if ( QTpla[0] > Qgate) countQ[2] ++; 
         Int_t nHit = hoge_R->GetEntriesFast();
         for( Int_t p = 0; p < nHit; p++){
            xy2 = (art::TMWDCTrackingResult*)hoge_R->At(p);
            if ( ValidorTracked == 1 && xy2 -> GetTrackingID() !=1 ) continue;
            
            Int_t NValidPlane = xy2 -> GetNPlaneValid();
            //track2 = (art::TTrack *)xy2->GetTrack();
            
            //if ( track2->GetX() < Xgate[0] || track2->GetX() > Xgate[1] ) continue;
            
            if (NValidPlane > 0 ) countQ[1]++;
            
            if ( NValidPlane >= 5 ) mwdcBoth ++;
            if ( NValidPlane == 6 ) countN6[1] ++ ; // count for validPlane == 6
            if ( NValidPlane == 5 ) {  // count number of each plane for validPlane == 5
               countN5comp[1]++;
               for ( Int_t i = 0; i<6 ; i++){
                  if (xy2->GetWireIDAdopted(i) == -1) countN5[1][i] ++; // missing 
               }
            }
            if ( NValidPlane == 4 ) countN4[1] ++;
            if ( NValidPlane == 3 ) countN3[1] ++;
            if ( NValidPlane == 2 ) countN2[1] ++;
            if ( NValidPlane == 1 ) countN1[1] ++;
            if ( NValidPlane == 0 ) countN0[1] ++;
         }
         hQ2->Fill(QTpla[1]);
         htdiff2->Fill(tdiff[1]);
         hQ2Plane->Fill(NValidPlane, QTpla[1]);
         hNVPlane2->Fill(NValidPlane);
      }
      
      if (mwdcBoth == 2) countN6[2] ++;
      
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
      cMWDC->cd(1);
      hQ1Plane->Draw("colz");
      //hQ1->Draw();
      //hQ2->Draw("same");
      cMWDC->cd(2);
      hQ2Plane->Draw("colz");
      //htdiff1->Draw();
      //htdiff2->Draw("same");
      cMWDC->cd(3);
      hNVPlane1->Draw();
      cMWDC->cd(4);
      hNVPlane2->Draw();
   }
   
   //##############  calculation efficiency
   Double_t eff[2][6];
   Double_t eff0[2] = {1,1};
   Double_t eff6[2] = {1,1};
   Double_t eff5[2][6];
   Double_t eff5tot[2] = {0,0};
   Int_t countN5tot[2]={0,0};
   Int_t totcount[2] = {0,0};
   for ( Int_t i = 0; i < 2; i++){ // L and R
      for ( Int_t j = 0; j < 6; j++){ // plane
         eff[i][j] = countN6[i]*100./(countN6[i]+countN5[i][j]); // in %
         eff6[i] = eff6[i]*eff[i][j]/100.; 
         eff0[i] = eff0[i]*(1.-eff[i][j]/100.); 
         countN5tot[i] += countN5[i][j];
         eff5[i][j] = 1;
      }
      eff6[i] = eff6[i]*100.;
      eff0[i] = eff0[i]*100.;
      for ( Int_t j = 0; j < 6; j++){ // plane
         for ( Int_t k = 0 ; k < 6; k ++){
            if ( j == k) {
               eff5[i][j] = eff5[i][j]*(1.-eff[i][k]/100.);
            }else{
               eff5[i][j] = eff5[i][j]*eff[i][k]/100.;
            }
         }
         eff5[i][j] = eff5[i][j]*100.; // in %
         eff5tot[i] += eff5[i][j]; // in %
      }
      totcount[i] = countN6[i]*100./eff6[i];
   }
  
   clock.Stop("timer");
   printf("============ finished|%10.3f sec = %10.3f min\n",clock.GetRealTime("timer"), clock.GetRealTime("timer")/60.);
   if ( ValidorTracked == 0){
      printf("------------- Qgate:%f, Fired Efficiency \n", Qgate);
   }else{
      printf("------------- Qgate:%f, Tracked Efficency \n", Qgate);   
   }
   printf("------------- Xgate:(%5.0f,%5.0f)\n", Xgate[0], Xgate[1]);
   printf("countQ>%4d:%10d \t\t\t%10d \t\t\t%10d\n", TMath::Nint(Qgate),  countQ[0], countQ[1], countQ[2]);
   printf("count>=5   :%10d[%4.1f%%] \t\t%10d[%4.1f%%] \t\t%10d[%4.1f%%] \n"
                              ,countN6[0]+countN5tot[0],(countN6[0]+countN5tot[0])*100./countQ[0]
                              ,countN6[1]+countN5tot[1],(countN6[1]+countN5tot[1])*100./countQ[0]
                              ,countN6[2], countN6[2]*100./countQ[2]);
   printf("countN6    :%10d[%4.1f%%] \t\t%10d[%4.1f%%] \n",  countN6[0],countN6[0]*100./countQ[0], countN6[1],countN6[1]*100./countQ[1]);
   //printf("countN5comp:%10d \t\t\t%10d \n",  countN5comp[0], countN5comp[1]);
   printf("countN5tot :%10d \t\t\t%10d \n",  countN5tot[0], countN5tot[1]);
   for ( Int_t i = 0; i < 6; i++){
      printf("countN5[%1d] :%10d[%4.1f%%](%4.1f%%) \t%10d[%4.1f%%](%4.1f%%) \n", i,countN5[0][i], eff[0][i], eff5[0][i],countN5[1][i], eff[1][i] , eff5[1][i]);
   }
   printf("eff6       :%10.2f%% \t\t%10.2f%% \t\t%10.2f%%\n",  eff6[0], eff6[1], eff6[0]*eff6[1]/100.);
   printf("eff5tot    :%10.2f%% \t\t%10.2f%% \n",  eff5tot[0], eff5tot[1]);
   printf("eff65      :%10.2f%% \t\t%10.2f%% \n",  eff6[0]+eff5tot[0], eff6[1]+eff5tot[1]);
   printf("eff0       :%10.2f%% \t\t%10.2f%% \n",  eff0[0], eff0[1]);
   printf("countQ[exp]:%10d[%4.1f%%] \t\t%10d[%4.1f%%] \n", totcount[0] ,totcount[0]*100./countQ[0] ,totcount[1] ,totcount[1]*100./countQ[1]);
   printf("countN4    :%10d \t\t\t%10d \n",  countN4[0], countN4[1]);
   printf("countN3    :%10d \t\t\t%10d \n",  countN3[0], countN3[1]);
   printf("countN2    :%10d \t\t\t%10d \n",  countN2[0], countN2[1]);
   printf("countN1    :%10d \t\t\t%10d \n",  countN1[0], countN1[1]);
   printf("countN0    :%10d \t\t\t%10d \n",  countN0[0], countN0[1]);

   return ;
}
