
{
   gROOT->Reset();
   gROOT->ProcessLine(".!date");
   gStyle->SetOptStat(0);

//   TFile *f1 = new TFile ("PrimaryData/phys14Up.root"); TTree *tree = (TTree*)f1->Get("tree");
   
   TFile *f2 = new TFile ("test.root"); TTree *recoil = (TTree*)f2->Get("recoil");
   
//   TFile *f3 = new TFile ("RppAll.root"); TTree *ppold2 = (TTree*)f3->Get("recoil");
   
   TBrowser B("test","test", 900,600); 

/*	TCanvas * cScript = new TCanvas ("cScript", "Tpla Decay constant", 10, 30, 800, 800);   
   
   TH2F * hQ
   
   Double_t tof, Q1, Q2, x1, a1;
   
   
   */
   
}


//############################################# Template
   
/*   TLatex text;
   text.SetNDC();
   text.SetTextColor(1);
   text.DrawText(0.2, 0.3, "no Corr");
   text.SetTextColor(2);
   text.DrawText(0.2, 0.25, "Mag Corr");
   text.SetTextColor(4);
   text.DrawText(0.2, 0.2, "Mag + BeamZ=15 Corr");*/
   
   
/* ----------- get leave data

	Double_t data;
	tree->SetBranchAddress("branch", &data);
	tree->GetEntry(eventID);
	printf("%f \n", data);
	
	*/
