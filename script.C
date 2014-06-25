
{
   gROOT->Reset();
   gROOT->ProcessLine(".!date");
   gStyle->SetOptStat(0);

//      TFile *f0 = new TFile ("ppAll_0617_mwdctime.root"); TTree *tree = (TTree*)f0->Get("tree");   

//   TFile *f1 = new TFile ("PrimaryData/ppOptics.root"); TTree *ppNew = (TTree*)f1->Get("tree");   

//   TFile *f1 = new TFile ("PrimaryData/ppAll_0613.root"); TTree *ppNew = (TTree*)f1->Get("tree");

//   TFile *f1 = new TFile ("PrimaryData/phys25F_multiOffset.root","update"); TTree *tree = (TTree*)f1->Get("tree");
   
//   TFile *f1 = new TFile ("test.root","update"); TTree *tree = (TTree*)f1->Get("tree");   
//   f1->Close();
    
   TFile *f2 = new TFile ("test.root"); TTree *recoil = (TTree*)f2->Get("recoil");
   
//   TFile *f3 = new TFile ("RppAll.root"); TTree *ppold2 = (TTree*)f3->Get("recoil");
   
   TBrowser B("test","test", 900,600); 
}

/*
	TString cScriptTitle;
	cScriptTitle.Form("test");
	TCanvas * cScript = new TCanvas ("cScript", cScriptTitle, 10, 30, 1500, 1000);  
   cScript->Divide(4,3); 
  
   
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

//   tree->Draw("p2p.fEx>>p2p", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-9)<30", "colz");
//	tree->Draw("p2p.fEx>>p2pbg", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-48)<30", "colz same");  
   
   cScript->cd(1);
	tree->Draw("p2p_m500.fEx>>h1(20,-60,140)", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-9)<30", "colz");
	tree->Draw("p2p_m500.fEx>>h1b(20,-60,140)", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-48)<30", "colz same");

	cScript->cd(2);
	tree->Draw("p2p_m400.fEx>>h2(20,-60,140)", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-9)<30", "colz");
	tree->Draw("p2p_m400.fEx>>h2b(20,-60,140)", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-48)<30", "colz same");

   cScript->cd(3);
	tree->Draw("p2p_m300.fEx>>h3(20,-60,140)", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-9)<30", "colz");
	tree->Draw("p2p_m300.fEx>>h3b(20,-60,140)", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-48)<30", "colz same");

	cScript->cd(4);
	tree->Draw("p2p_m200.fEx>>h4(20,-60,140)", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-9)<30", "colz");
	tree->Draw("p2p_m200.fEx>>h4b(20,-60,140)", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-48)<30", "colz same");
	
   cScript->cd(5);
	tree->Draw("p2p_m100.fEx>>h5(20,-60,140)", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-9)<30", "colz");
	tree->Draw("p2p_m100.fEx>>h5b(20,-60,140)", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-48)<30", "colz same");

	cScript->cd(6);
	tree->Draw("p2p.fEx>>h6(20,-60,140)", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-9)<30", "colz");
	tree->Draw("p2p.fEx>>h6b(20,-60,140)", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-48)<30", "colz same");
    
   cScript->cd(7);
	tree->Draw("p2p_p100.fEx>>h7(20,-60,140)", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-9)<30", "colz");
	tree->Draw("p2p_p100.fEx>>h7b(20,-60,140)", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-48)<30", "colz same");
	
	cScript->cd(8);
	tree->Draw("p2p_p200.fEx>>h8(20,-60,140)", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-9)<30", "colz");
	tree->Draw("p2p_p200.fEx>>h8b(20,-60,140)", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-48)<30", "colz same");
   
   cScript->cd(9);
	tree->Draw("p2p_p300.fEx>>h9(20,-60,140)", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-9)<30", "colz");
	tree->Draw("p2p_p300.fEx>>h9b(20,-60,140)", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-48)<30", "colz same");
	
	cScript->cd(10);
	tree->Draw("p2p_p400.fEx>>h10(20,-60,140)", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-9)<30", "colz");
	tree->Draw("p2p_p400.fEx>>h10b(20,-60,140)", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-48)<30", "colz same");
	
	cScript->cd(11);
	tree->Draw("p2p_p500.fEx>>h11(20,-60,140)", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-9)<30", "colz");
	tree->Draw("p2p_p500.fEx>>h11b(20,-60,140)", "gate.Test(3) && gate.Test(4) && abs(vertex.fZ-48)<30", "colz same");
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
