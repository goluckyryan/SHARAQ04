
void NyokiQCali_test(Int_t nyokiID = 7, Double_t intercept_adj=0, Double_t slope_adj=1) {

//############################################################################  
  //   const char* rootfile="PrimaryData/phys23F.root"; 
  //const char* rootfile="23F_ppcoin_0314.root"; 
  const char* rootfile="test_run23.root"; 

  Bool_t allentry  = 1;
  Int_t firstEntry = 0;
  Int_t nEntries=2000000;

  Double_t nyokiPlotRange[2] = {700, 2200};
  Double_t timeGate[2] = {-270,-210};

//############################################################################
  TFile *f = new TFile(rootfile,"read");
  printf(">> %s <<< is loaded.\n",rootfile);
  TTree *tree = (TTree*)f->Get("tree");
  Int_t totEntries = tree->GetEntries();
  if(allentry){
    firstEntry = 0;
    nEntries = totEntries;
  }
  Int_t endEntry = firstEntry + nEntries;
  printf("totEntries:%d, nEntries:%.d [%5.2f%%]\n", totEntries, nEntries, 100.*nEntries/totEntries);

//############################################################################ 
  if ( gROOT->FindObject("cNyokiQ")){
    delete cNyokiQ;
  }

  if( gROOT->FindObject("hQab")){
    delete hQab;
    delete hDiff;
    delete hRatio;
  }

  Int_t Div[2] = {3,2};
  Int_t size = 400;
  TCanvas * cNyokiQ = new TCanvas("cNyokiQ", "Nyoki Q Calibaration", 2000, 50, size*Div[0], size*Div[1]);
  cNyokiQ->Divide(Div[0],Div[1]);

  //gStyle->SetOptStat(0);
  TString hTitle;
  hTitle.Form("Nyoki Q, %d vs %d {%s}", nyokiID[0], nyokiID[1], rootfile);
  TH2F* hQab = new TH2F("hQab", hTitle, 100, nyokiPlotRange[0], nyokiPlotRange[1], 100, nyokiPlotRange[0], nyokiPlotRange[1]);
  TString xTitle, yTitle;
  xTitle.Form("nyoki %d", nyokiID[0]);
  yTitle.Form("nyoki %d", nyokiID[1]);
  hQab->SetXTitle(xTitle);
  hQab->SetYTitle(yTitle);

  hTitle.Form("Nyoki Q diff, %d - %d", nyokiID[1], nyokiID[0]);
  TH1F* hDiff = new TH1F("hDiff", hTitle, 100,  -100, 100);

  hTitle.Form("Nyoki Q ratio, %d / %d", nyokiID[1], nyokiID[0]);
  TH1F* hRatio = new TH1F("hRatio", hTitle, 100,  0.8, 1.2);

//############################################################################   
  tree->SetBranchStatus("*",0);
  tree->SetBranchStatus("nyoki",1);
  tree->SetBranchStatus("plaV775",1);

  TClonesArray  *hoge_nyoki;
  TClonesArray  *hoge_v775;
  tree->SetBranchAddress("nyoki",&hoge_nyoki);
  tree->SetBranchAddress("plaV775",&hoge_v775);

  Double_t charge[14];
  Double_t timing[14];
  Double_t s0dQ;

  TBenchmark clock;
  clock.Reset();
  clock.Start("timer");
  Bool_t shown = 0;
  
  Int_t count = 0;

//############################################################################  
  for( Int_t eventID = firstEntry; eventID < endEntry; eventID ++){
  tree->GetEntry(eventID,0);

    //--------- initialization
    for( Int_t i = 0; i < 14; i++){
      charge[i] = TMath::QuietNaN();
      timing[i] = TMath::QuietNaN();
    }
    //--------- Get nyoki Q
    Int_t nHit = hoge_nyoki->GetEntriesFast();
    if( nHit < 2) continue;

    //printf(" nHit : %d \n", nHit);

    //__________________
    for( Int_t p = 0; p < nHit; p++){
    Int_t ID = ((art::TTimingChargeData*)hoge_nyoki->At(p))->GetID();
      charge[ID] = ((art::TTimingChargeData*)hoge_nyoki->At(p))->GetCharge();
      timing[ID] = ((art::TTimingChargeData*)hoge_nyoki->At(p))->GetTiming();
    }  

    //--------- Fill Hist
    if( timing[nyokiID] < timeGate[0] || timing[nyokiID] > timeGate[1] ) continue;
    if( TMath::IsNaN(charge[nyokiID]) || TMath::IsNaN(charge[nyokiID]) ) continue;

    if( charge[nyokiID]<nyokiPlotRange[0] || charge[nyokiID]>nyokiPlotRange[1] ) continue;
    if( charge[nyokiID]<nyokiPlotRange[0] || charge[nyokiID]>nyokiPlotRange[1] ) continue;

 //   if( TMath::Abs(charge[nyokiID[0]] - charge[nyokiID[1]]) > 300 ) continue;
    
    
    //________________________________ Get S0D charge
    s0dQ = TMath::QuietNaN();
    Int_t nHit = hoge_v775->GetEntriesFast();
    for( Int_t p = 0; p < nHit; p++){
      Int_t ID = ((art::TTimingChargeData*)hoge_v775->At(p))->GetID();
      if (ID != 4) continue;
      s0dQ = ((art::TTimingChargeData*)hoge_v775->At(p))->GetCharge();
    }
    if(TMath::IsNaN(s0dQ)) continue;

    hQab->Fill(slope_adj*charge[nyokiID]+intercept_adj, s0dQ);

    //printf(" nyoki-7, nyoki-8 = %.3f, %.3f \n", charge[7], charge[8]);

    hDiff->Fill(s0dQ - (slope_adj*charge[nyokiID]+intercept_adj) );

    hRatio->Fill(s0dQ /( slope_adj*charge[nyokiID]+intercept_adj ));
    
    count ++;

    //------------------
    clock.Stop("timer");
    Double_t time = clock.GetRealTime("timer");
    clock.Start("timer");

    if ( !shown ) {
      if (fmod(time, 10) < 1 ){
        printf( "%10d[%2d%%] |%3d min %5.2f sec | expect:%5.1fmin\n", 
        eventID, 
        TMath::Nint((eventID+1-firstEntry)*100./nEntries),
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

  //==================================================
  TString textStr;
  TLatex text;
  text.SetNDC(1);
  text.SetTextSize(0.035);

  TF1* fit = new TF1("fit", "[0]+[1]*x", nyokiPlotRange[0], nyokiPlotRange[1]);

  cNyokiQ->cd(1);
  hQab->Draw("colz");
  TLine line;
  line.DrawLine(nyokiPlotRange[0], nyokiPlotRange[0], nyokiPlotRange[1], nyokiPlotRange[1]);


  cNyokiQ->cd(2);
  hQab->ProfileY("_pfy")->Draw();
  hQab_pfy->SetTitle("ProfileY");

  hQab_pfy->Fit(fit, "R" );
  Double_t a = fit->GetParameter(0);
  Double_t b = fit->GetParameter(1);

  Double_t err_a = fit->GetParError(0);
  Double_t err_b = fit->GetParError(1);

  textStr.Form("inte.: %5.3f (%5.3f)", a, err_a); text.DrawLatex(0.5,0.40, textStr);	
  textStr.Form("slope: %5.3f (%5.3f)", b, err_b); text.DrawLatex(0.5,0.35, textStr);

  cNyokiQ->cd(3);
  hQab->ProfileX("_pfx")->Draw();
  hQab_pfx->SetTitle("ProfileX");

  hQab_pfx->Fit(fit, "R" );
  Double_t a = fit->GetParameter(0);
  Double_t b = fit->GetParameter(1);

  Double_t err_a = fit->GetParError(0);
  Double_t err_b = fit->GetParError(1);

  textStr.Form("inte.: %5.3f (%5.3f)", a, err_a); text.DrawLatex(0.5,0.40, textStr);	
  textStr.Form("slope: %5.3f (%5.3f)", b, err_b); text.DrawLatex(0.5,0.35, textStr);


  cNyokiQ->cd(4);
  hDiff->Draw();

  cNyokiQ->cd(5);
  hRatio->Draw();

//############################################################################

  printf("effective count:%d \n", count);

}
