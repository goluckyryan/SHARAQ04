
void coinReg() {
   
//############################################################################   
   const char* rootfile="23F_1204_nyoki_run2425.root";
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=1000000;
   Int_t run[2] = {24, 25};
   
   Bool_t eventShift = 0;
   
   Int_t sampleRate = 10;
   
//############################################################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;
   
   gStyle->SetOptStat(0);
   TCanvas * cCheck = new TCanvas("check", "check", 2000, 100, 800, 400);
   cCheck->Divide(2,1);

   TString hCheckTitle;
   hCheckTitle.Form("%s, sample rate=%d", rootfile, sampleRate);
   TH1F* hCheck = new TH1F("check", hCheckTitle, 7, 1, 8);
   
   TH2F* hCheck2 = new TH2F("check2", "coinReg vs runNum", run[1] + 1 - run[0], run[0], run[1]+1, 6, 1, 8);
//############################################################################
   art::TCoinRegData *hoge_coinReg;
   art::TEventHeader *hoge_run;
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded. \n",rootfile);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   char* eventBranch = "eventheader";
   if( eventShift ) eventBranch = "eventheader0";
   
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus(eventBranch,1);
   tree->SetBranchStatus("coinReg",1);

   tree->SetBranchAddress(eventBranch,&hoge_run);
   tree->SetBranchAddress("coinReg",&hoge_coinReg);

//############################################################################   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   
   Int_t count = 0;
   
         TLorentzVector *const residual = fKinematics->GetResidual();
      *residual =  *incident;
      *residual -= *l;
      *residual -= *r;
      residual->SetE(residual->E()+P_MASS);
      residual->Boost(0,0,-0.6465);
      /* calculate seperation energy by mass difference or Q value */
      const Double_t sp2   = residual->M() - fM + P_MASS;
      fKinematics->SetSp2(sp2);
   
//##############################################################################
   for( Int_t eventID = firstEntry; eventID < endEntry; eventID += sampleRate){
      tree->GetEntry(eventID,0);
      
//----------------Get Event Number
      Int_t runNum = hoge_run->GetRunNumber();
      if( runNum < run[0] ) continue;
      if( runNum > run[1] ) break;
      
//--------------Get coinReg
		Int_t check = 0; 
      // 0 = F3, 1 = FH9, 2=ppcoin, 3 = ND coin, 4 = ppsingle, 5 = ND single, 6 = ND cosmic
      if ( hoge_coinReg->Test(1) == 1 ) check += 1;
      if ( hoge_coinReg->Test(2) == 1 ) check += 2;
      if ( hoge_coinReg->Test(0) || hoge_coinReg->Test(3) || hoge_coinReg->Test(4) || hoge_coinReg->Test(5) || hoge_coinReg->Test(6) ) check += 4; 
      
      hCheck->Fill(check);
      hCheck2->Fill(runNum, check);
      
      count ++;
      

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
   
   printf("count %d, totentries %d, ratio %.3f \n", count, nEntries, count/nEntries*100.);
  
   cCheck->cd(1);
   hCheck->Draw();
   Int_t max = hCheck->GetMaximum();
   TLatex text;
   text.SetTextColor(1);
   text.SetTextAngle(90);
   text.SetTextSize(0.04);
   TString textstr;
   textstr.Form("only Beam %.0f(%.2f%%)", hCheck->GetBinContent(1), hCheck->GetBinContent(1)/count*100.);
   text.DrawText(1.5, max/5, textstr);
   textstr.Form("only ppcoin %.0f(%.2f%%)", hCheck->GetBinContent(2), hCheck->GetBinContent(2)/count*100.);
   text.DrawText(2.5, max/5, textstr);
   textstr.Form("Beam x ppcoin %.0f(%.2f%%)", hCheck->GetBinContent(3), hCheck->GetBinContent(3)/count*100.);
   text.DrawText(3.5, max/5, textstr);
   textstr.Form("other %.0f(%.2f%%)", hCheck->GetBinContent(4), hCheck->GetBinContent(4)/count*100.);
   text.DrawText(4.5, max/5, textstr);
   textstr.Form("Beam x other %.0f(%.2f%%)", hCheck->GetBinContent(5), hCheck->GetBinContent(5)/count*100.);
   text.DrawText(5.5, max/5, textstr);
   textstr.Form("ppcoin x other %.0f(%.2f%%)", hCheck->GetBinContent(6), hCheck->GetBinContent(6)/count*100.);
   text.DrawText(6.5, max/5, textstr);
   textstr.Form("all %.0f(%.2f%%)", hCheck->GetBinContent(7), hCheck->GetBinContent(7)/count*100.);
   text.DrawText(7.5, max/5, textstr);
   
   
   cCheck->cd(2);
   hCheck2->Draw("colz");
   
   clock.Stop("timer");
   printf("============ finished|%10.3f sec \n",clock.GetRealTime("timer"));
   
   return ;
}
