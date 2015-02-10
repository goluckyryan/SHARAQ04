#include "ryan/constant.h"

void nyokiQCali_new() {
   gStyle->SetOptStat(0);
      
   const char* rootfile="23F_run24_nyokiQ.root";
   
   TString plotName = "Multiplicity of nyoki";
   TString branch = "nyoki"; // branch anme
   TString branch_2 = "";
	TCut cut ="";
	Int_t nBin = 5;
	Double_t minX = 1;
	Double_t maxX = 6;
	
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
	
	Int_t Div[2] = {10, 2};
	TCanvas* cSimple = new TCanvas("cSimple", "cSimple", 100, 100, Div[0]*300, Div[1]*300);
	cSimple->Divide(Div[0],Div[1]);
	
	/*if( gROOT->FindObject("h1D")){
		delete h1D;
      delete h2D;
	}*/
	
	//Int_t NumEvent = tree->GetEntries();
	TString hTitle;
	hTitle.Form("%s.%s {%s}",branch_2.Data(),plotName.Data(), rootfile);
	
	TH1F * h1D = new TH1F("h1D", hTitle, nBin, minX, maxX);
	//h1D->SetLineColor(kRed);

	Int_t S0DQRange[2] = {800, 2200};
	Int_t nyokiQRange[2] = {800, 4500};

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
	
	TH2F * hn03n = new TH2F("hn03n", "Nyoki-03 " , 100, nyokiQRange[0], nyokiQRange[1], 100, S0DQRange[0], S0DQRange[1]); hn03->SetXTitle("nyoki [ch]"); hn03->SetYTitle("S0DPL [ch]");
	TH2F * hn04n = new TH2F("hn04n", "Nyoki-04 " , 100, nyokiQRange[0], nyokiQRange[1], 100, S0DQRange[0], S0DQRange[1]); hn04->SetXTitle("nyoki [ch]"); hn04->SetYTitle("S0DPL [ch]");
	TH2F * hn05n = new TH2F("hn05n", "Nyoki-05 " , 100, nyokiQRange[0], nyokiQRange[1], 100, S0DQRange[0], S0DQRange[1]); hn05->SetXTitle("nyoki [ch]"); hn05->SetYTitle("S0DPL [ch]");
	TH2F * hn06n = new TH2F("hn06n", "Nyoki-06 " , 100, nyokiQRange[0], nyokiQRange[1], 100, S0DQRange[0], S0DQRange[1]); hn06->SetXTitle("nyoki [ch]"); hn06->SetYTitle("S0DPL [ch]");
	TH2F * hn07n = new TH2F("hn07n", "Nyoki-07 " , 100, nyokiQRange[0], nyokiQRange[1], 100, S0DQRange[0], S0DQRange[1]); hn07->SetXTitle("nyoki [ch]"); hn07->SetYTitle("S0DPL [ch]");
	TH2F * hn08n = new TH2F("hn08n", "Nyoki-08 " , 100, nyokiQRange[0], nyokiQRange[1], 100, S0DQRange[0], S0DQRange[1]); hn08->SetXTitle("nyoki [ch]"); hn08->SetYTitle("S0DPL [ch]");
	TH2F * hn09n = new TH2F("hn09n", "Nyoki-09 " , 100, nyokiQRange[0], nyokiQRange[1], 100, S0DQRange[0], S0DQRange[1]); hn09->SetXTitle("nyoki [ch]"); hn09->SetYTitle("S0DPL [ch]");
	TH2F * hn10n = new TH2F("hn10n", "Nyoki-10 " , 100, nyokiQRange[0], nyokiQRange[1], 100, S0DQRange[0], S0DQRange[1]); hn10->SetXTitle("nyoki [ch]"); hn10->SetYTitle("S0DPL [ch]");
	
	TH2F * hnn = new TH2F("hnn", "Nyoki Q" , 8, 3, 11, 100, nyokiQRange[0], nyokiQRange[1]);	
	hnn->SetXTitle("nyoki ID");
	hnn->SetYTitle("nyoki Q [ch]");
	
	//#####################################
	/*
	TString name1, name2, name3;
	name1 = branch + branch_2 + "." + plotName + ">>h1D";
	
	printf("%s\n", name1.Data());
	printf("%s\n", name2.Data());
	printf("%s\n", name3.Data());
	
	tree->Draw(name1,cut,"");
	tree->Draw(name2,cut,"same");
	tree->Draw(name3,cut,"same");
	
	*/
   //###################################
   tree->SetBranchStatus("*",0);
   
   tree->SetBranchStatus("plaV775",1);
   tree->SetBranchStatus("nyoki",1);
   tree->SetBranchStatus("nyoki_n",1);

   TClonesArray *hoge_v775 = 0;
   TClonesArray *hoge_nyoki = 0;
   TClonesArray *hoge_nyoki_n = 0;  
   tree->SetBranchAddress("plaV775",&hoge_v775);
   tree->SetBranchAddress("nyoki",&hoge_nyoki);
   tree->SetBranchAddress("nyoki_n",&hoge_nyoki_n);
   
   for( Int_t eventID = 0; eventID < totnumEntry; eventID ++ ){
   	tree->GetEntry(eventID,0);
   	
   	h1D->Fill(hoge_nyoki->GetEntriesFast());
   	
   	//____________________ get S0DPL Q
   	Double_t s0DQ = kInvalidD;
   	Bool_t hitFlag = 0;
   	Int_t nHit = hoge_v775 -> GetEntriesFast();
   	//printf(" ----------- nHit: %d \n", nHit);
      for( Int_t p = 0; p < nHit; p++){
         Int_t hitID = ((art::TTwoSidedPlasticData*) hoge_v775->At(p))->GetID();
         if ( hitID != 4 ) continue;
         s0DQ = ((art::TTwoSidedPlasticData*) hoge_v775->At(p))->GetCharge();
         hitFlag = 1;
         //printf("S0DPL: %f \n", s0DQ);
      }       
      if( hitFlag == 0 ) continue; 
      
      //____________________ get nyoki Q 
   	Double_t nQ[14];
   	for( Int_t p = 0; p < 14; p++){ nQ[p] = kInvalidD;}
   	Int_t nHit = hoge_nyoki -> GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
      	Int_t id = (art::TTimingChargeData*) hoge_nyoki->At(p))->GetID(); 
         nQ[id] = ((art::TTimingChargeData*) hoge_nyoki->At(p))->GetCharge();
         hn->Fill(id, nQ[id]);
      }
      
      //____________________ get nyoki_n Q 
   	Double_t nQn[14];
   	for( Int_t p = 0; p < 14; p++){ nQn[p] = kInvalidD;}
   	Int_t nHit = hoge_nyoki_n -> GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         Int_t idn = (art::TTimingChargeData*) hoge_nyoki_n->At(p))->GetID(); 
         nQn[idn] = ((art::TTimingChargeData*) hoge_nyoki_n->At(p))->GetCharge();
         hnn->Fill(idn, nQn[idn]);
         //printf(" %d, %f , %f\n", id, nQ[id], nQn[id]);
      }
      
      hn03->Fill(nQ[3], s0DQ);
      hn04->Fill(nQ[4], s0DQ);
      hn05->Fill(nQ[5], s0DQ);
      hn06->Fill(nQ[6], s0DQ);
      hn07->Fill(nQ[7], s0DQ);
      hn08->Fill(nQ[8], s0DQ);
      hn09->Fill(nQ[9], s0DQ);
      hn10->Fill(nQ[10], s0DQ);
      
      hn03n->Fill(nQn[3], s0DQ);
      hn04n->Fill(nQn[4], s0DQ);
      hn05n->Fill(nQn[5], s0DQ);
      hn06n->Fill(nQn[6], s0DQ);
      hn07n->Fill(nQn[7], s0DQ);
      hn08n->Fill(nQn[8], s0DQ);
      hn09n->Fill(nQn[9], s0DQ);
      hn10n->Fill(nQn[10], s0DQ);
      
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
   
   
   cSimple->cd(11); hn03n->Draw("colz"); 
   cSimple->cd(12); hn04n->Draw("colz");
   cSimple->cd(13); hn05n->Draw("colz"); 
   cSimple->cd(14); hn06n->Draw("colz");
   cSimple->cd(15); hn07n->Draw("colz"); 
   cSimple->cd(16); hn08n->Draw("colz"); 
   cSimple->cd(17); hn09n->Draw("colz");
   cSimple->cd(18); hn10n->Draw("colz");
   cSimple->cd(19); hnn->Draw("colz");	
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

