
{
   gROOT->Reset();
   gROOT->ProcessLine(".!date");
   gStyle->SetOptStat(0);

   TFile *f1 = new TFile ("PrimaryData/phys23F_m500ps.root"); TTree *tree = (TTree*)f1->Get("tree");
   
//   TFile *f2 = new TFile ("test.root"); TTree *recoil = (TTree*)f2->Get("recoil");
   
//   TFile *f3 = new TFile ("RppAll.root"); TTree *ppold2 = (TTree*)f3->Get("recoil");
   
   TBrowser B("test","test", 900,600); 

/*	TCanvas * cScript = new TCanvas ("cScript", "Tpla Decay constant", 10, 30, 800, 800);   
   
   TH2F * hQ
   
   Double_t tof, Q1, Q2, x1, a1; 
   */
   
   TH1F * hp2p = new TH1F("p2p", "Ex", 50, -60, 140);
   hp2p->SetXTitle("Ex");
   hp2p->SetYTitle("Count / 4 MeV");
   hp2p->SetMinimum(0);
   hp2p->SetLineColor(2);
	hp2p->SetFillColor(2);
	hp2p->SetFillStyle(3004);
	
	TH1F * hp2pbg = new TH1F("p2pbg", "Ex", 50, -60, 140);
   hp2pbg->SetXTitle("Ex");
   hp2pbg->SetYTitle("Count / 4 MeV");
   hp2pbg->SetLineColor(4);
	hp2pbg->SetFillColor(4);
	hp2pbg->SetFillStyle(3005);
   
	tree->Draw("p2p.fEx>>p2p", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-9)<30", "colz");
	tree->Draw("p2p.fEx>>p2pbg", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-48)<30", "colz same");

		

   
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
