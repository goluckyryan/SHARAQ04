void eventShiftCheck() {
   
   TStopwatch time;
   time.Reset();

   Long64_t  shiftSM = -1;
   Int_t    nShiftSM = 2;
   Long64_t *shiftEntrySM = new Long64_t[nShiftSM];
   
   shiftEntrySM[0] = 184600;
   shiftEntrySM[1] = 370400;
/*   shiftEntrySM[2] = 3138700;
/*   shiftEntrySM[3] = 4871600;
/*   shiftEntrySM[4] = 4573900;
/*   shiftEntrySM[5] = 5622900;
/*   shiftEntrySM[6] = 2578400;
*/   
   Long64_t  shiftF3 = -1;
   Int_t    nShiftF3 = 3;
   Long64_t *shiftEntryF3 = new Long64_t[nShiftF3];
   
   shiftEntryF3[0] =   86200;
//   shiftEntryF3[1] =  184600;
   shiftEntryF3[1] =  370400;
   shiftEntryF3[2] =  451900;

   
   int flag = 51; //chance of fail test, in case for accidental
   
   const char* savefilename="phys22_es.root";
   const char* rootfile="23F_es_norm_0002.root";
   Bool_t debugInfo = 0;
   Bool_t plantTree = 0;
   Bool_t plothist  = 1;
   Bool_t breakAtFail = 1;
   Bool_t endofdata   = 1; // if 0 , use endEntry, 1 use totnumEntry
   Int_t  firstEntry  = 0;
   Int_t    endEntry  = firstEntry+  800000;
   Int_t  RunRange[2] = {2,2};
   
   Double_t SMGate[2] = {-125, -100};
   Double_t F3Gate[2] = {-1465, -1458};
   
   Int_t SMThershold = 40;
   Int_t F3Thershold = 20;
   
//##################################################################   
   Int_t runNum;
   Double_t tFH9V1190[50];
   Double_t tFH9V775;
   Double_t tF3V1190[50];
   Double_t tDiffF3[50], tDiffSM[50];
   Int_t nHitFH9V1190, nHitF3V1190;
   Int_t eventID;
   Int_t nCom;
   Int_t count_F3 = 0, count_SM = 0;

   TFile savefile(savefilename,"recreate");
   TTree *t1 = new TTree("es_corr","ToF");
   if (plantTree ){
      t1->Branch("runNum", &runNum, "runNum/I");
      t1->Branch("eventID",&eventID,"eventID/I");
      t1->Branch("nHitFH9V1190",&nHitFH9V1190,"nHitFH9V1190/I");
      t1->Branch("tFH9V1190",tFH9V1190,"tFH9V1190[nHitFH9V1190]/D");
      t1->Branch("tFH9V775",&tFH9V775,"tFH9V775/D");
      t1->Branch("nHitF3V1190",&nHitF3V1190,"nHitF3V1190/I");
      t1->Branch("tF3V1190",tF3V1190,"tF3V1190[nHitF3V1190]/D");
      t1->Branch("tDiffSM",tDiffSM,"tDiffSM[nHitFH9V1190]/D");
      t1->Branch("nCom",&nCom,"nCom/I");
      t1->Branch("tDiffF3",tDiffF3,"tDiffF3[nCom]/D");      
   }

   art::TEventHeader *hogeRun;
   TClonesArray *hogeFH9V1190, *hogeV775, *hogeF3V1190;
   TFile *f = new TFile(rootfile,"read");
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   printf("===============================================================\n");
   printf(" total number event: %10d\n",totnumEntry);
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("eventheader",1);
   tree->SetBranchStatus("plaV1190_FH9",1);
   tree->SetBranchStatus("plaV1190_F3",1);
   tree->SetBranchStatus("plaV775",1);

   tree->SetBranchAddress("eventheader",&hogeRun);
   tree->SetBranchAddress("plaV1190_FH9",&hogeFH9V1190);
   tree->SetBranchAddress("plaV775",&hogeV775);
   tree->SetBranchAddress("plaV1190_F3",&hogeF3V1190);
   
   if (endofdata) endEntry = totnumEntry;
   
   if (plothist){
      TString h4_title, h5_title;
      h4_title.Form("V1190(FH9) vs V1190(F3) %6d -%6d",firstEntry,endEntry);
      h5_title.Form("tdiff(FH9-F3) V1190 %6d -%6d",firstEntry,endEntry);
   
      TH2F* h1 = new TH2F("es","event Shift FH9 V1190 vs V775", 200, -500, -300, 200, -400,-100);
      h1->SetXTitle("V1190");
      h1->SetYTitle("V775");
      TH1F* h3 = new TH1F("tdiffFH9","FH9 t(V1190)-t(V775)", 200, -140,-90);
      
      TH2F* h4 = new TH2F("es39",h4_title, 200, -440, -340, 200, 1000,1100);
      h4->SetXTitle("V1190(FH9)");
      h4->SetYTitle("V1190(F3)");
      TH1F* h5 = new TH1F("tdiffF3FH9",h5_title, 100, -1470, -1440);
      TH1F* h6 = new TH1F("count_SM","count_SM",100, 0, 100);
      TH1F* h7 = new TH1F("count_F3","count_F3",100, 0, 100);
      
      TCanvas* c1 = new TCanvas("c1", "check", 50, 50, 900, 600);
      c1->Divide(3,2);  
      c1->SetGridx(1); c1->SetGridy(1);
   }
   
   time.Start();
//##################################################################################   
   for( eventID = firstEntry; eventID < endEntry; eventID++){
      time.Continue();
      tree->GetEntry(eventID);  
      
      if ( hogeRun->GetRunNumber() < RunRange[0] ) continue;
      if ( hogeRun->GetRunNumber() > RunRange[1] ) break;

      for (Int_t p = 0; p < 50; p++){
         tFH9V1190[p] = TMath::QuietNaN();
         tF3V1190[p]  = TMath::QuietNaN();
         tDiffSM[p]   = TMath::QuietNaN();
         tDiffF3[p]   = TMath::QuietNaN();
      }
      tFH9V775 = TMath::QuietNaN();
      
      //Get runNum
      runNum = hogeRun->GetRunNumber();
      
      //Get V1190 FH9 timing
      nHitFH9V1190 =hogeFH9V1190->GetEntriesFast();     
      for( Int_t p = 0; p < nHitFH9V1190; p++){
         art::TTwoSidedPlasticData *data1 = (art::TTwoSidedPlasticData*)hogeFH9V1190->At(p) ;
         tFH9V1190[p] = data1->GetT1();
      }

//================================================================================
//====================== FH9 V1190 and V775 compare
      // shifting eventID
      for (Int_t j =0 ; j < nShiftSM; j++) {
         if ( eventID >= shiftEntrySM[j] && shiftSM != 0) then){
            tree->GetEntry(eventID+shiftSM*(j+1));
            if (firstEntry > shiftEntrySM[j] && eventID == firstEntry) printf("....SM Shifted @ %8d by %3d \n",shiftEntrySM[j],shiftSM*(j+1));
            if(eventID == shiftEntrySM[j])  printf(" ......SM Shifted. %8d -> %8d\n",eventID,eventID+shiftSM*(j+1)) ;
         }
      }
      
      // Get V775 timing
      Int_t nHitV775 =hogeV775->GetEntriesFast();   
      for(Int_t  q = 0; q < nHitV775; q++){
         art::TTwoSidedPlasticData *data2 = (art::TTwoSidedPlasticData*)hogeV775->At(q) ;
         Int_t detID   = data2->GetDetID();
         if (detID == 4) tFH9V775  = data2->GetT1();
      }
      for(Int_t p = 0; p < nHitFH9V1190; p++){ 
         if (TMath::Finite(tFH9V775)) {
            if (debugInfo ) printf(" Filled  tFH9V1190:%10.4f  tFH9V775:%10.4f \n",tFH9V1190[p],tFH9V775);
            if (plothist){
               h1->Fill(tFH9V1190[p],tFH9V775);
               h3->Fill(tFH9V1190[p]-tFH9V775);
            }
            tDiffSM[p] = tFH9V1190[p]-tFH9V775;
            if(tDiffSM[p]> SMGate[0] && tDiffSM[p] < SMGate[1]) count_SM = count_SM + 1;
         }
      }
//================================================================================ 
//===============   F3 V1190 and FH9 V1190 tDiffF3 compare
      tree->GetEntry(eventID); //reset the pointer to eventID-th enetry
      
      for (Int_t j =0 ; j < nShiftF3; j++) {
         if (eventID >= shiftEntryF3[j] && shiftF3 != 0) then){
            tree->GetEntry(eventID+shiftF3*(j+1));
            if (firstEntry > shiftEntryF3[j] && eventID == firstEntry) printf("....F3 Shifted @ %8d by %3d \n",shiftEntryF3[j],shiftF3*(j+1));
            if(eventID == shiftEntryF3[j])  printf(" ......F3 Shifted. %8d -> %8d\n",eventID,eventID+shiftF3*(j+1)) ;
         }
      }
      
      //Get F3 V1190 Timing
      nHitF3V1190 =hogeF3V1190->GetEntriesFast(); 
      for(Int_t k = 0; k < nHitF3V1190; k++){
         art::TTwoSidedPlasticData *data3 = (art::TTwoSidedPlasticData*)hogeF3V1190->At(k) ;
         tF3V1190[k]  = data3->GetT1();
      }
      
      nCom=0;
      for (Int_t p = 0; p < nHitFH9V1190; p++){
         for(Int_t k = 0; k < nHitF3V1190; k++){
            if (debugInfo ) printf(" Filled  tFH9V1190:%10.4f  tF3V1190:%10.4f \n",tFH9V1190[p],tF3V1190[k]);
            if (plothist){
               h4->Fill(tFH9V1190[p],tF3V1190[k]);
               h5->Fill(tFH9V1190[p]-tF3V1190[k]);
            }
            tDiffF3[nCom] = tFH9V1190[p]-tF3V1190[k];
            if( tDiffF3[nCom] > F3Gate[0] && tDiffF3[nCom] < F3Gate[1]) count_F3 = count_F3 + 1;
            nCom = nCom +1 ;
         }
      }
///================================================================================
      if (plantTree){
         savefile.cd(); //set focus on this file
         t1->Fill();
      }
      
      if( eventID%10000 ==0) printf(" event:%10d(#%2d), %5.2f%% time:%10.2f sec |count_F3:%2d,count_SM:%2d\n"
                        ,eventID
                        ,runNum
                        ,eventID*100./totnumEntry
                        ,time.RealTime()
                        ,count_F3
                        ,count_SM);
      
      if( eventID%100 == 0 && eventID != firstEntry){
         if ((count_F3 <= F3Thershold || count_SM <= SMThershold )&& flag > 0 ) {
            printf("============count_F3:%3d,count_SM:%3d @ %10d flag:%1d\n",count_F3,count_SM,eventID-100,flag); 
            flag = flag - 1;
            if (breakAtFail && flag == 0) break;
         }
         h6->Fill(count_SM);
         h7->Fill(count_F3);
         count_F3  = 0;
         count_SM = 0;
      }
      
   }
///================================================================================
   printf("End of Run. endEvent:%10d(%5.2f%%) time:%10.2f sec \n",eventID, (Double_t)eventID*100/totnumEntry, time.RealTime());
   
   if (plothist){
      c1->cd(1); 
      h1->Draw("colz");
      c1->cd(2);
      h3->Draw();
      TLine *line1 = new TLine(SMGate[0],0, SMGate[0], h3->GetMaximum());
      TLine *line2 = new TLine(SMGate[1],0, SMGate[1], h3->GetMaximum());
      line1->SetLineColor(3);
      line2->SetLineColor(3);
      line1->SetLineWidth(2);
      line2->SetLineWidth(2);
      line1->Draw("same");
      line2->Draw("same");   
      c1->cd(3);  
      h6->Draw();
      TLine * lineSM = new TLine(SMThershold,0, SMThershold, h6->GetMaximum());
      lineSM->SetLineColor(3);
      lineSM->SetLineWidth(2);
      lineSM->Draw("same");  
      c1->cd(4);
      h4->Draw("colz"); 
      c1->cd(5);
      h5->Draw();
      TLine * line3 = new TLine(F3Gate[0],0, F3Gate[0], h5->GetMaximum());
      TLine * line4 = new TLine(F3Gate[1],0, F3Gate[1], h5->GetMaximum());
      line3->SetLineColor(3);
      line4->SetLineColor(3);
      line3->SetLineWidth(2);
      line4->SetLineWidth(2);
      line3->Draw("same");
      line4->Draw("same");
      c1->cd(6);
      h7->Draw();
      TLine * lineF3 = new TLine(F3Thershold,0, F3Thershold, h7->GetMaximum());
      lineF3->SetLineColor(3);
      lineF3->SetLineWidth(2);
      lineF3->Draw("same");
   }
   
   if (plantTree){
      savefile.cd();
      t1->Write();
      savefile.Close();
   } 
   
}
