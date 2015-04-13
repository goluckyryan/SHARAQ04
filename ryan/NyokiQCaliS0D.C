#include "ryan/constant.h"

void NyokiQCaliS0D() {
  gStyle->SetOptStat(0);

  //const char* rootfile="23F_ppcoin_0314.root";
  //const char* rootfile="test_run23_nyokiQ_ppcoin_Q_calib.root";
  const char* rootfile="test.root";

  TString branch = "nyoki"; // branch anme
  TString branch_2 = "";
  TCut cut ="";
  Int_t nBin = 5;
  Double_t minX = 1;
  Double_t maxX = 6;
  
  Double_t timeGate[2] = {-270,-210};
  
  Int_t S0DQRange[2]   = {800, 2200};
  Int_t nyokiQRange[2] = {800, 4000};

//###########################  load tree
  TFile *f0 = new TFile (rootfile, "read"); 
  TTree *tree = (TTree*)f0->Get("tree");
  Int_t totnumEntry = tree->GetEntries();
  printf("----------%s is loaded. totEntry = %d \n", rootfile, totnumEntry);

  TBenchmark clock;
  clock.Reset();
  clock.Start("timer");
  Bool_t shown = 0;
//###########################  Canvas and histogram
  if ( gROOT->FindObject("cSimple")){
    delete cSimple;
  }

  Int_t Div[2] = {3, 1};
  TCanvas* cSimple = new TCanvas("cSimple", "cSimple", 2000, 100, Div[0]*400, Div[1]*400);
  cSimple->Divide(Div[0],Div[1]);

  TH2F * hn06 = new TH2F("hn06", "Nyoki-06 Calibrated" , 100, nyokiQRange[0], nyokiQRange[1], 100, S0DQRange[0], S0DQRange[1]); hn06->SetXTitle("nyoki [ch]"); hn06->SetYTitle("S0DPL [ch]");
  TH2F * hn07 = new TH2F("hn07", "Nyoki-07 Calibrated" , 100, nyokiQRange[0], nyokiQRange[1], 100, S0DQRange[0], S0DQRange[1]); hn07->SetXTitle("nyoki [ch]"); hn07->SetYTitle("S0DPL [ch]");
  TH2F * hn08 = new TH2F("hn08", "Nyoki-08 Calibrated" , 100, nyokiQRange[0], nyokiQRange[1], 100, S0DQRange[0], S0DQRange[1]); hn08->SetXTitle("nyoki [ch]"); hn08->SetYTitle("S0DPL [ch]");

//###################################
  tree->SetBranchStatus("*",0);
  tree->SetBranchStatus("plaV775",1);
  tree->SetBranchStatus("nyoki",1);
  tree->SetBranchStatus("gate",1);

  TClonesArray *hoge_v775 = 0;
  TClonesArray *hoge_nyoki = 0;
  art::TGateArray *hoge_gate;
  tree->SetBranchAddress("plaV775",&hoge_v775);
  tree->SetBranchAddress("nyoki",&hoge_nyoki);
  tree->SetBranchAddress("gate",&hoge_gate);
  
  Double_t s0DQ = kInvalidD;
  Double_t nQ[14], nT[14];

  for( Int_t eventID = 0; eventID < totnumEntry; eventID ++ ){
    tree->GetEntry(eventID,0);
    
    if( !hoge_gate->Test(12) )continue;
    //if( !hoge_gate->Test(3) )continue;
    
    //____________________ get S0DPL Q
    s0DQ = kInvalidD;
    Bool_t hitFlag = 0;
    Int_t nHit = hoge_v775 -> GetEntriesFast();
    //printf(" ----------- nHit: %d \n", nHit);
    for( Int_t p = 0; p < nHit; p++){
//      Int_t hitID = ((art::TTwoSidedPlasticData*) hoge_v775->At(p))->GetID();
      Int_t hitID = ((art::TTimingChargeData*) hoge_v775->At(p))->GetID();
      if ( hitID != 4 ) continue;
//      s0DQ = ((art::TTwoSidedPlasticData*) hoge_v775->At(p))->GetCharge();
      s0DQ = ((art::TTimingChargeData*) hoge_v775->At(p))->GetCharge();
      hitFlag = 1;
      //printf("S0DPL: %f \n", s0DQ);
    }       
    if( hitFlag == 0 ) continue; 
      
    //____________________ get nyoki Q 
    for( Int_t p = 0; p < 14; p++){ 
      nQ[p] = kInvalidD;
      nT[p] = kInvalidD;
    }
    Int_t nHit = hoge_nyoki -> GetEntriesFast();
    for( Int_t p = 0; p < nHit; p++){
        Int_t id = (art::TTimingChargeData*) hoge_nyoki->At(p))->GetID(); 
        nQ[id] = ((art::TTimingChargeData*) hoge_nyoki->At(p))->GetCharge();
        nT[id] = ((art::TTimingChargeData*) hoge_nyoki->At(p))->GetTiming();
        
        if( nT[id] < timeGate[0] || nT[id] > timeGate[1]) continue;
        
        if( id == 6) hn06->Fill(nQ[id], s0DQ);
        if( id == 7) hn07->Fill(nQ[id], s0DQ);
        if( id == 8) hn08->Fill(nQ[id], s0DQ);
        //printf("%d, %7.2f, %7.2f \n", id, nQ[id], s0DQ);
    }
    
    clock.Stop("timer");
    Double_t time = clock.GetRealTime("timer");
    clock.Start("timer");
    
    if ( !shown ) {
      if (fmod(time, 10) < 1 ){
        printf( "%10d[%2d%%] |%3d min %5.2f sec | expect:%6.1fmin\n", 
        eventID, 
        TMath::Nint((eventID+1)*100./totnumEntry),
        TMath::Floor(time/60), time - TMath::Floor(time/60)*60,
        totnumEntry*time/(eventID+1)/60.);
        shown = 1;
      }
    }else{
      if (fmod(time, 10) > 9 ){
        shown = 0;
      }
    }
    

  }

//###################################
  
  TLine line;
  
  cSimple->cd(1); hn06->Draw("colz"); line.DrawLine(S0DQRange[0], S0DQRange[0], S0DQRange[1], S0DQRange[1]);
  cSimple->cd(2); hn07->Draw("colz"); line.DrawLine(S0DQRange[0], S0DQRange[0], S0DQRange[1], S0DQRange[1]);
  cSimple->cd(3); hn08->Draw("colz"); line.DrawLine(S0DQRange[0], S0DQRange[0], S0DQRange[1], S0DQRange[1]);
//###################################	
  /*
  TLatex text;
  text.SetNDC();
  text.SetTextColor(kRed);
  text.DrawText(0.2, 0.8, "TL & TW");
  text.SetTextColor(kBlue);
  text.DrawText(0.2, 0.75, "TL");
  text.SetTextColor(kGreen);
  text.DrawText(0.2, 0.7, "TW");
  text.SetTextColor(kBlack);
  text.DrawText(0.2, 0.65, cut.GetTitle());
  */
}

