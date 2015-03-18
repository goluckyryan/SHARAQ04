#include "ryan/constant.h"

void NyokiQCaliS0D() {
  gStyle->SetOptStat(0);

  //const char* rootfile="23F_ppcoin_0314.root";
  const char* rootfile="test_run23.root";

  TString plotName = "Multiplicity of nyoki";
  TString branch = "nyoki"; // branch anme
  TString branch_2 = "";
  TCut cut ="";
  Int_t nBin = 5;
  Double_t minX = 1;
  Double_t maxX = 6;
  
  Double_t timeGate[2] = {-270,-210};
  
  Int_t S0DQRange[2] = {800, 2200};
  Int_t nyokiQRange[2] = {800, 2200};

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

  Int_t Div[2] = {5, 2};
  TCanvas* cSimple = new TCanvas("cSimple", "cSimple", 100, 100, Div[0]*300, Div[1]*300);
  cSimple->Divide(Div[0],Div[1]);

  //Int_t NumEvent = tree->GetEntries();
  TString hTitle;
  hTitle.Form("%s.%s {%s}",branch_2.Data(),plotName.Data(), rootfile);

  TH1F * h1D = new TH1F("h1D", hTitle, nBin, minX, maxX);
  //h1D->SetLineColor(kRed);

  TH2F * hn03 = new TH2F("hn03", "Nyoki-03 Calibrated" , 100, S0DQRange[0], S0DQRange[1], 100, S0DQRange[0], S0DQRange[1]); hn03->SetXTitle("nyoki [ch]"); hn03->SetYTitle("S0DPL [ch]");
  TH2F * hn04 = new TH2F("hn04", "Nyoki-04 Calibrated" , 100, S0DQRange[0], S0DQRange[1], 100, S0DQRange[0], S0DQRange[1]); hn04->SetXTitle("nyoki [ch]"); hn04->SetYTitle("S0DPL [ch]");
  TH2F * hn05 = new TH2F("hn05", "Nyoki-05 Calibrated" , 100, S0DQRange[0], S0DQRange[1], 100, S0DQRange[0], S0DQRange[1]); hn05->SetXTitle("nyoki [ch]"); hn05->SetYTitle("S0DPL [ch]");
  TH2F * hn06 = new TH2F("hn06", "Nyoki-06 Calibrated" , 100, S0DQRange[0], S0DQRange[1], 100, S0DQRange[0], S0DQRange[1]); hn06->SetXTitle("nyoki [ch]"); hn06->SetYTitle("S0DPL [ch]");
  TH2F * hn07 = new TH2F("hn07", "Nyoki-07 Calibrated" , 100, S0DQRange[0], S0DQRange[1], 100, S0DQRange[0], S0DQRange[1]); hn07->SetXTitle("nyoki [ch]"); hn07->SetYTitle("S0DPL [ch]");
  TH2F * hn08 = new TH2F("hn08", "Nyoki-08 Calibrated" , 100, S0DQRange[0], S0DQRange[1], 100, S0DQRange[0], S0DQRange[1]); hn08->SetXTitle("nyoki [ch]"); hn08->SetYTitle("S0DPL [ch]");
  TH2F * hn09 = new TH2F("hn09", "Nyoki-09 Calibrated" , 100, S0DQRange[0], S0DQRange[1], 100, S0DQRange[0], S0DQRange[1]); hn09->SetXTitle("nyoki [ch]"); hn09->SetYTitle("S0DPL [ch]");
  TH2F * hn10 = new TH2F("hn10", "Nyoki-10 Calibrated" , 100, S0DQRange[0], S0DQRange[1], 100, S0DQRange[0], S0DQRange[1]); hn10->SetXTitle("nyoki [ch]"); hn10->SetYTitle("S0DPL [ch]");

  TH2F * hn = new TH2F("hn", "Nyoki Q Calibrated" , 8, 3, 11, 100, S0DQRange[0], S0DQRange[1]);	
  hn->SetXTitle("nyoki ID");
  hn->SetYTitle("nyoki Q [ch]");

//###################################
  tree->SetBranchStatus("*",0);
  tree->SetBranchStatus("plaV775",1);
  tree->SetBranchStatus("nyoki",1);

  TClonesArray *hoge_v775 = 0;
  TClonesArray *hoge_nyoki = 0;
  tree->SetBranchAddress("plaV775",&hoge_v775);
  tree->SetBranchAddress("nyoki",&hoge_nyoki);
  
  Double_t s0DQ = kInvalidD;
  Double_t nQ[14];

  for( Int_t eventID = 0; eventID < totnumEntry; eventID ++ ){
    tree->GetEntry(eventID,0);
    
    h1D->Fill(hoge_nyoki->GetEntriesFast());
    
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
    for( Int_t p = 0; p < 14; p++){ nQ[p] = kInvalidD;}
    Int_t nHit = hoge_nyoki -> GetEntriesFast();
    for( Int_t p = 0; p < nHit; p++){
        Int_t id = (art::TTimingChargeData*) hoge_nyoki->At(p))->GetID(); 
        nQ[id] = ((art::TTimingChargeData*) hoge_nyoki->At(p))->GetCharge();
        
        hn->Fill(id, nQ[id]);
        
        if( id == 3) hn03->Fill(nQ[id], s0DQ);
        if( id == 4) hn04->Fill(nQ[id], s0DQ);
        if( id == 5) hn05->Fill(nQ[id], s0DQ);
        if( id == 6) hn06->Fill(nQ[id], s0DQ);
        if( id == 7) hn07->Fill(nQ[id], s0DQ);
        if( id == 8) hn08->Fill(nQ[id], s0DQ);
        if( id == 9) hn09->Fill(nQ[id], s0DQ);
        if( id ==10) hn10->Fill(nQ[id], s0DQ);
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

  cSimple->cd(10); h1D->Draw();
  
  TLine line;
  
  cSimple->cd(1); hn03->Draw("colz"); line.DrawLine(S0DQRange[0], S0DQRange[0], S0DQRange[1], S0DQRange[1]);
  cSimple->cd(2); hn04->Draw("colz"); line.DrawLine(S0DQRange[0], S0DQRange[0], S0DQRange[1], S0DQRange[1]);
  cSimple->cd(3); hn05->Draw("colz"); line.DrawLine(S0DQRange[0], S0DQRange[0], S0DQRange[1], S0DQRange[1]);
  cSimple->cd(4); hn06->Draw("colz"); line.DrawLine(S0DQRange[0], S0DQRange[0], S0DQRange[1], S0DQRange[1]);
  cSimple->cd(5); hn07->Draw("colz"); line.DrawLine(S0DQRange[0], S0DQRange[0], S0DQRange[1], S0DQRange[1]);
  cSimple->cd(6); hn08->Draw("colz"); line.DrawLine(S0DQRange[0], S0DQRange[0], S0DQRange[1], S0DQRange[1]);
  cSimple->cd(7); hn09->Draw("colz"); line.DrawLine(S0DQRange[0], S0DQRange[0], S0DQRange[1], S0DQRange[1]);
  cSimple->cd(8); hn10->Draw("colz"); line.DrawLine(S0DQRange[0], S0DQRange[0], S0DQRange[1], S0DQRange[1]);
  cSimple->cd(9); hn->Draw("colz");
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

