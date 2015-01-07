#include "ryan/constant.h"
#include "ryan/RelCalculator.h"
#include "ryan/Compress/TBeamData.h"
#include "ryan/Compress/TRecoilData.h"

void simpleAna() {
   gStyle->SetOptStat(0);
      
   const char* rootfile="23F_1228_nyoki_run23.root";
   
   TString plotName = "Multiplicity of nyoki";
   TString branch = "nyoki"; // branch anme
   TString branch_2 = "";
	TCut cut ="";
	Int_t nBin = 5;
	Double_t minX = 1;
	Double_t maxX = 6;
	
	//###########################
   TFile *f0 = new TFile (rootfile, "read"); 
   TTree *tree = (TTree*)f0->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
	printf("----------%s is loaded. totEntry = %d \n", rootfile, totnumEntry);
	
	//###########################
	if ( gROOT->FindObject("cSimple")){
		delete cSimple;
	}
	TCanvas* cSimple = new TCanvas("cSimple", "cSimple", 2300, 100, 800, 600);
	
	if( gROOT->FindObject("h1D")){
		delete h1D;
      delete h2D;
	}
	//Int_t NumEvent = tree->GetEntries();
	TString hTitle;
	hTitle.Form("%s.%s",branch_2.Data(),plotName.Data());
	
	TH1F * h1D = new TH1F("h1D", hTitle, nBin, minX, maxX);
	//h1D->SetLineColor(kRed);

	TH2F * h2D = new TH2F("h2D", hTitle, nBin, 0, 100, 100, 0, 100);
	
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
   TClonesArray *hoge;
   tree->SetBranchAddress(branch ,&hoge);
   
   for( Int_t eventID = 0; eventID < totnumEntry; eventID ++ ){
   	tree->GetEntry(eventID);
   	
   	h1D->Fill(hoge->GetEntriesFast());
   
   }
   
   //###################################
   
   h1D->Draw();
   	
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

