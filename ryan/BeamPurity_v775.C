void BeamPurity_v775() {
//================ variable
   Int_t eventID;
   // runNumber
   Int_t runNum;
   // coinReg
   Int_t coinReg;
   // get tof and charge upstream
   Double_t tof_us, Q_us;
   
//############################################################################   
   //const char* rootfile="PrimaryData/phys22Optics.root";
   const char* rootfile="23F_run23_0603.root";
   TString beam = "23F";
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=600000;
   Int_t runRange[2] = {1, 3000};
   
            //for [23F,  318.0, 770.0, 323.0, 1000.0]
         //[22O,  302.0, 700.0, 306.0,  900.0]
         //[21O,  314.0, 750.0, 317.0,  890.0]
         //[19N,  306.3, 675.8, 310.0,  843.6]
         //[16C,  310.0, 645.0, 316.0,  745.0]
         //[13B,  318.0, 584.0, 320.0,  684.0]
         //[10Be, 326.0, 525.0, 331.0,  625.0]
         //[8Li,  312.2, 457.0, 316.0,  590.7]
         //[7Li,  341.0, 477.0, 347.0,  577.0]
         
        // [25F,  311, 762, 319, 1060] 
        // [24O,  292, 726, 301,  960]
        // [13B,  328, 577, 335,  685]
        // [14B,  311, 580, 315,  680]
        // [10Be, 336, 514, 343,  636]
        // [11Be, 315, 516, 322,  619]
        // [8Li,  321, 462, 330,  575]
        // [9Li,  294, 517, 302,  558]
        // [6He,  294, 465, 302,  517]
   
   Double_t tGate[2];
   Double_t qGate[2];
   
   if( beam == "23F") {tGate[0] = -323; tGate[1] = -318; qGate[0] = 770; qGate[1] = 1000;};
   if( beam == "22O") {tGate[0] = -306; tGate[1] = -302; qGate[0] = 700; qGate[1] =  900;};
   if( beam == "25F") {tGate[0] = -319; tGate[1] = -311; qGate[0] = 762; qGate[1] = 1060;};
   
//############################################################################
   gStyle->SetOptStat(0);
   
   TCanvas* cBeamRatio = new TCanvas("cBeamRatio", "BeamRatio", 300, 150, 800, 400);
   cBeamRatio->Divide(2,1);
   
   TH2F * hPIDUS     = new TH2F("PIDUS", beam + " - PID up stream", 300, -340, -280, 300, 400, 1200);
   hPIDUS->SetXTitle("tof(F3-FH9) [ns]");
   hPIDUS->SetYTitle("Charge(F3) [a.u.]");
   hPIDUS->GetYaxis()->SetTitleOffset(1.5);
   TH2F * hPIDUSbeam = new TH2F("PIDUSbeam", beam + " - PID up stream gated", 300, -340, -280, 300, 400, 1200);
   hPIDUSbeam->SetXTitle("tof(F3-FH9) [ns]");
   hPIDUSbeam->SetYTitle("Charge(F3) [a.u.]");
   hPIDUSbeam->GetYaxis()->SetTitleOffset(1.5);

//############################################################################
   art::TCoinRegData *hoge_coinReg;
   art::TEventHeader *hoge_run;
   TClonesArray  *hoge_V775, *hoge_ds;
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded. \n",rootfile);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("eventheader",1);
   tree->SetBranchStatus("coinReg",1);
   tree->SetBranchStatus("plaV775",1); //get charge for PID
   tree->SetBranchStatus("tof_DS",1);

   tree->SetBranchAddress("eventheader",&hoge_run);
   tree->SetBranchAddress("coinReg",&hoge_coinReg);
   tree->SetBranchAddress("plaV775",&hoge_V775);
   tree->SetBranchAddress("tof_DS",&hoge_ds);

//############################################################################   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);

   art::TTimeDifference * tofdsdata;
   
   gROOT->ProcessLine(".!date");
   Int_t count_USHit = 0, count_PIDgate=0;
   
//##############################################################
   for( eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID,0);
      
      // initialization
      coinReg = 0;
      tof_us = TMath::QuietNaN(); Q_us = TMath::QuietNaN();

//--------------Get coinReg
      if( hoge_coinReg->Test(1) != 1 ) continue;

//----------------Get Event Number
      runNum = hoge_run->GetRunNumber();
      if ( runNum < runRange[0]) continue; 
      if ( runNum > runRange[1]) break;
//----------------Get tof and charge upstream V1190
      //Double_t tof_us[40], Q_us[40];
      Bool_t PID = 0;
      Int_t nHit = hoge_ds -> GetEntriesFast();
      if (nHit == 0) continue;
      count_USHit++;
      
      for( Int_t p = 0; p < nHit; p++){
         Int_t detID = ((art::TTimeDifference*)hoge_ds->At(p))->GetID() ;
         if( detID != 2) continue;
         tof_us    = -((art::TTimeDifference*)hoge_ds->At(p))->GetTiming(); // minus sign
         Q_us = ((art::TTwoSidedPlasticData*) hoge_V775->At(p))->GetCharge();
         //printf("%d, %f, %f \n", eventID, tof_us, Q_us);
         hPIDUS->Fill(tof_us, Q_us);
         
         if ( tof_us < tGate[0] || tof_us > tGate[1]) continue; //PID gate
         if ( Q_us < qGate[0] || Q_us > qGate[1]) continue; // PID gate
         PID = 1;
      }
      if ( PID == 0 ) continue;
      hPIDUSbeam->Fill(tof_us, Q_us);
      
      count_PIDgate++;
      
   }
   
   cBeamRatio->cd(1);
   hPIDUS->Draw("colz");
   cBeamRatio->cd(2);
   hPIDUSbeam->Draw("colz");

   printf("============ finished.\n");
   printf("%15s:%10d \n", "nEntries",nEntries);
   printf("%15s:%10d [%4.1f%%] \n", "count coinReg", count_USHit, count_USHit*100./nEntries);
   printf("%10s%5s:%10d [%4.1f%%][%4.1f%%] \n", "count",beam.Data(), count_PIDgate, count_PIDgate*100./nEntries, count_PIDgate*100./count_USHit);
   
   TString testStr;
   TLatex text;
   text.SetNDC();
   text.SetTextColor(1);
   testStr.Form("beam trig.:%d", count_USHit);
   text.DrawText(0.2, 0.3, testStr);
   testStr.Form("%s:%d[%4.1f%%(%4.1f%%)]", beam.Data(), count_PIDgate,count_PIDgate*100./count_USHit, TMath::Sqrt(1./count_PIDgate+1./count_USHit)*100.*count_PIDgate/count_USHit);
   text.DrawText(0.2, 0.25, testStr);
   
   return ;
}
