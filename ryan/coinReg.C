
void coinReg() {
   
//############################################################################   
   const char* rootfile="23F_1128_nyoki.root";
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=1000000;
   
//############################################################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;
   
   gStyle->SetOptStat(0);
   TCanvas * cCheck = new TCanvas("check", "check", 2000, 100, 800, 400);
   cCheck->Divide(2,1);

   TString hCheckTitle;
   hCheckTitle = rootfile;
   TH1F* hCheck = new TH1F("check", hCheckTitle, 4, 0, 4);
   
   TH2F* hCheck2 = new TH2F("check2", "coinReg vs runNum", 4, 21, 25, 4, 0, 4);
//############################################################################
   art::TCoinRegData *hoge_coinReg;
   art::TEventHeader *hoge_run;
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded. \n",rootfile);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("eventheader",1);
   tree->SetBranchStatus("coinReg",1);

   tree->SetBranchAddress("eventheader",&hoge_run);
   tree->SetBranchAddress("coinReg",&hoge_coinReg);

//############################################################################   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   
//##############################################################################
   for( Int_t eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID);
      
//----------------Get Event Number
      Int_t runNum = hoge_run->GetRunNumber();
      
//--------------Get coinReg
		Int_t check = 0; 
      // 0 = F3, 1 = FH9, 2=ppcoin, 3 = ND coin, 4 = ppsingle, 5 = ND single, 6 = ND cosmic
      if ( hoge_coinReg->Test(1) == 1 ) check += 1;
      if ( hoge_coinReg->Test(2) == 1 ) check += 2;
      
      hCheck->Fill(check);
      hCheck2->Fill(runNum, check);
      

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
  
   cCheck->cd(1);
   hCheck->Draw();
   Int_t max = hCheck->GetMaximum();
   TLatex text;
   text.SetTextColor(1);
   text.SetTextAngle(90);
   text.SetTextSize(0.04);
   text.DrawText(0.5, max/4, "others");
   text.DrawText(1.5, max/4, "only Beam");
   text.DrawText(2.5, max/4, "only ppcoin");
   text.DrawText(3.5, max/4, "Beam + ppcoin");
   
   
   cCheck->cd(2);
   hCheck2->Draw("colz");
   
   clock.Stop("timer");
   printf("============ finished|%10.3f sec \n",clock.GetRealTime("timer"));
   
   return ;
}
