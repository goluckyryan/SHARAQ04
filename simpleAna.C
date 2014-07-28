#include "ryan/constant.h"
#include "ryan/RelCalculator.h"
#include "ryan/TBeamData.h"
#include "ryan/TRecoilData.h"

void simpleAna() {
   gStyle->SetOptStat(0);
   
   TString name = "GetTrackingID()";
   TString side = "L";
	Int_t nBin = 3;
	Double_t minX = -1;
	Double_t maxX = 2;
	
	//###########################
	if( gROOT->FindObject("h")){
		delete h;
		delete hTL;
		delete hTW;
	}
	//Int_t NumEvent = tree->GetEntries();
	TString hTitle;
	hTitle.Form("%s.%s",side.Data(),name.Data());
	TH1F * h = new TH1F("h", hTitle, nBin, minX, maxX);
	h->SetLineColor(kRed);
	TH1F * hTL = new TH1F("hTL", "hTL", nBin, minX, maxX);
	TH1F * hTW = new TH1F("hTW", "hTW", nBin, minX, maxX);
	hTW->SetLineColor(kGreen); 
	
	TString branch, name1, name2, name3;
	branch = "smwdc_"; // branch
	name1 = branch + side + "." + name + ">>h";
	name2 = branch + side + "_TLgated." + name + ">>hTL";
	name3 = branch + side + "_TWgated." + name + ">>hTW";
	
	printf("%s\n", name1.Data());
	printf("%s\n", name2.Data());
	printf("%s\n", name3.Data());
	
	TCut cut = "";//"coinReg.Test(2)";
	
	tree->Draw(name1,cut,"");
	tree->Draw(name2,cut,"same");
	tree->Draw(name3,cut,"same");
	
	TLatex text;
   text.SetNDC();
   text.SetTextColor(kRed);
   text.DrawText(0.2, 0.8, "TL & TW");
   text.SetTextColor(kBlue);
   text.DrawText(0.2, 0.75, "TL");
   text.SetTextColor(kGreen);
   text.DrawText(0.2, 0.7, "TW");
   
}

