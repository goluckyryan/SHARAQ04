
{
   gROOT->Reset();
   gROOT->ProcessLine(".!date");
   gStyle->SetOptStat(0);

//   TFile *f0 = new TFile ("PrimaryData/phys25F.root"); TTree *tree = (TTree*)f0->Get("tree");   

//   TFile *f1 = new TFile ("PrimaryData/ppOptics.root"); TTree *ppNew = (TTree*)f1->Get("tree");   

   TFile *f1 = new TFile ("ppUp_0723.root"); TTree *tree = (TTree*)f1->Get("tree");

   TFile *f1 = new TFile ("PrimaryData/ppUp.root","update"); TTree *old = (TTree*)f1->Get("tree");
   
//   TFile *f1 = new TFile ("RppAll_0714_multiOffset.root","update"); TTree *recoil = (TTree*)f1->Get("recoil");   
//   f1->Close();
    
//   TFile *f2 = new TFile ("ppAll_0716_multiOffset.root"); TTree *recoil = (TTree*)f2->Get("tree");
   
//   TFile *f3 = new TFile ("RppUp_0613.root"); TTree *ppold = (TTree*)f3->Get("recoil");
   
   TBrowser B("test","test", 900,600); 
   
//   ppNew->Draw("p2p.fSp>>h01(100,-50,50)","abs(beamZ.fAverage)<40 && abs((p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()-87.5)<2.5", "");


}
   
//   ppold->Draw("Sp>>hSP(100,-50,50)", "abs(wbeamZ)<50 && abs((theta1+theta2)*TMath::RadToDeg()-87.5)<2.5");
/*   
   Int_t nBin = 150;
   Int_t binMin = -50;
   Int_t binMax = 100;
   Int_t histMin = 0;
   Int_t histMax = 200;
   
   TH1F* h00 = new TH1F("hist00", "wBeamZ (-0.5,-0.5)", nBin,binMin,binMax); h00->SetLineColor(1); h00->SetMaximum(histMax); h00->SetMinimum(histMin);
   TH1F* h01 = new TH1F("hist01", "wBeamZ (-0.5, 0.0)", nBin,binMin,binMax); h01->SetLineColor(2); h01->SetMaximum(histMax); h01->SetMinimum(histMin);
   TH1F* h02 = new TH1F("hist02", "wBeamZ (-0.5, 0.5)", nBin,binMin,binMax); h02->SetLineColor(3); h02->SetMaximum(histMax); h02->SetMinimum(histMin);
   TH1F* h03 = new TH1F("hist03", "wBeamZ (-0.5, 1.5)", nBin,binMin,binMax); h03->SetLineColor(4); h03->SetMaximum(histMax); h03->SetMinimum(histMin);
   
   TH1F* h10 = new TH1F("hist10", "wBeamZ ( 0.0,-0.5)", nBin,binMin,binMax); h10->SetLineColor(1); h10->SetMaximum(histMax); h10->SetMinimum(histMin);
   TH1F* h11 = new TH1F("hist11", "wBeamZ ( 0.0, 0.0)", nBin,binMin,binMax); h11->SetLineColor(2); h11->SetMaximum(histMax); h11->SetMinimum(histMin);
   TH1F* h12 = new TH1F("hist12", "wBeamZ ( 0.0, 0.5)", nBin,binMin,binMax); h12->SetLineColor(3); h12->SetMaximum(histMax); h12->SetMinimum(histMin);
   TH1F* h13 = new TH1F("hist13", "wBeamZ ( 0.0, 1.5)", nBin,binMin,binMax); h13->SetLineColor(4); h13->SetMaximum(histMax); h13->SetMinimum(histMin);
   
   TH1F* h20 = new TH1F("hist20", "wBeamZ ( 0.5,-0.5)", nBin,binMin,binMax); h20->SetLineColor(1); h20->SetMaximum(histMax); h20->SetMinimum(histMin);
   TH1F* h21 = new TH1F("hist21", "wBeamZ ( 0.5, 0.0)", nBin,binMin,binMax); h21->SetLineColor(2); h21->SetMaximum(histMax); h21->SetMinimum(histMin);
   TH1F* h22 = new TH1F("hist22", "wBeamZ ( 0.5, 0.5)", nBin,binMin,binMax); h22->SetLineColor(3); h22->SetMaximum(histMax); h22->SetMinimum(histMin);
   TH1F* h23 = new TH1F("hist23", "wBeamZ ( 0.5, 1.5)", nBin,binMin,binMax); h23->SetLineColor(4); h23->SetMaximum(histMax); h23->SetMinimum(histMin);
   
   TH1F* h30 = new TH1F("hist30", "wBeamZ ( 1.0,-0.5)", nBin,binMin,binMax); h30->SetLineColor(1); h30->SetMaximum(histMax); h30->SetMinimum(histMin);
   TH1F* h31 = new TH1F("hist31", "wBeamZ ( 1.0, 0.0)", nBin,binMin,binMax); h31->SetLineColor(2); h31->SetMaximum(histMax); h31->SetMinimum(histMin);
   TH1F* h32 = new TH1F("hist32", "wBeamZ ( 1.0, 0.5)", nBin,binMin,binMax); h32->SetLineColor(3); h32->SetMaximum(histMax); h32->SetMinimum(histMin);
   TH1F* h33 = new TH1F("hist33", "wBeamZ ( 1.0, 1.5)", nBin,binMin,binMax); h33->SetLineColor(4); h33->SetMaximum(histMax); h33->SetMinimum(histMin);
   
   TH1F* h40 = new TH1F("hist40", "wBeamZ ( 1.5,-0.5)", nBin,binMin,binMax); h40->SetLineColor(1); h40->SetMaximum(histMax); h40->SetMinimum(histMin);
   TH1F* h41 = new TH1F("hist41", "wBeamZ ( 1.5, 0.0)", nBin,binMin,binMax); h41->SetLineColor(2); h41->SetMaximum(histMax); h41->SetMinimum(histMin);
   TH1F* h42 = new TH1F("hist42", "wBeamZ ( 1.5, 0.5)", nBin,binMin,binMax); h42->SetLineColor(3); h42->SetMaximum(histMax); h42->SetMinimum(histMin);
   TH1F* h43 = new TH1F("hist43", "wBeamZ ( 1.5, 1.5)", nBin,binMin,binMax); h43->SetLineColor(4); h43->SetMaximum(histMax); h43->SetMinimum(histMin);
  
  	TCanvas* cScript = new TCanvas("cScript", "cScript", 2000, 100, 900,600);
  	cScript->Divide(3,2);
  	
  	TCut gate1 = "abs(beamZ.fL-beamZ.fR)<50";
  	TCut gate2 = "abs((p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()-87)<3";
  	TCut gateA = "abs((p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()-83.25)<1.25";
  	TCut gateB = "abs((p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()-90.72)<1.25";
  	
  	cScript->cd(1);
   tree->Draw("beamZ.fL>>hist00", gate1 && gate2 && "abs(p2p_m500m500.fSp)<10", "same");
   tree->Draw("beamZ.fL>>hist01", gate1 && gate2 && "abs(p2p_m500zero.fSp)<10", "same");
   tree->Draw("beamZ.fL>>hist02", gate1 && gate2 && "abs(p2p_m500p500.fSp)<10", "same");
   tree->Draw("beamZ.fL>>hist03", gate1 && gate2 && "abs(p2p_m500p1500.fSp)<10", "same");
   tree->Draw("beamZ.fL>>hist0bg(150,-50,100)", gate1 && (gateA || gateB) && "abs(p2p_m500zero.fSp)<10", "same");
   
   cScript->cd(2);
   tree->Draw("beamZ.fL>>hist10" , gate1 && gate2 && "abs(p2p_zerom500.fSp)<10", "same");
   tree->Draw("beamZ.fL>>hist11" , gate1 && gate2 && "abs(p2p.fSp)<10", "same");
   tree->Draw("beamZ.fL>>hist12" , gate1 && gate2 && "abs(p2p_zerop1000.fSp)<10", "same");
   tree->Draw("beamZ.fL>>hist13" , gate1 && gate2 && "abs(p2p_zerop1500.fSp)<10", "same");
   tree->Draw("beamZ.fL>>hist1bg(150,-50,100)", gate1 && (gateA || gateB) && "abs(p2p.fSp)<10", "same");
   
   cScript->cd(3);
   tree->Draw("beamZ.fL>>hist20" , gate1 && gate2 && "abs(p2p_p500m500.fSp)<10", "same");
   tree->Draw("beamZ.fL>>hist21" , gate1 && gate2 && "abs(p2p_p500zero.fSp)<10", "same");
   tree->Draw("beamZ.fL>>hist22" , gate1 && gate2 && "abs(p2p_p500p1000.fSp)<10", "same");
   tree->Draw("beamZ.fL>>hist23" , gate1 && gate2 && "abs(p2p_p500p1500.fSp)<10", "same");
   tree->Draw("beamZ.fL>>hist2bg(150,-50,100)", gate1 && (gateA || gateB) && "abs(p2p_p500zero.fSp)<10", "same");

	cScript->cd(4);
   tree->Draw("beamZ.fL>>hist30" , gate1 && gate2 && "abs(p2p_p1000m500.fSp)<10", "same");
   tree->Draw("beamZ.fL>>hist31" , gate1 && gate2 && "abs(p2p_p1000zero.fSp)<10", "same");
   tree->Draw("beamZ.fL>>hist32" , gate1 && gate2 && "abs(p2p_p1000p1000.fSp)<10", "same");
   tree->Draw("beamZ.fL>>hist33" , gate1 && gate2 && "abs(p2p_p1000p1500.fSp)<10", "same");
   tree->Draw("beamZ.fL>>hist3bg(150,-50,100)", gate1 && (gateA || gateB) && "abs(p2p_p1000zero.fSp)<10", "same");
   
   cScript->cd(5);
   tree->Draw("beamZ.fL>>hist40" , gate1 && gate2 && "abs(p2p_p1500m500.fSp)<10", "same");
   tree->Draw("beamZ.fL>>hist41" , gate1 && gate2 && "abs(p2p_p1500zero.fSp)<10", "same");
   tree->Draw("beamZ.fL>>hist42" , gate1 && gate2 && "abs(p2p_p1500p1000.fSp)<10", "same");
   tree->Draw("beamZ.fL>>hist43" , gate1 && gate2 && "abs(p2p_p1500p1500.fSp)<10", "same");
	tree->Draw("beamZ.fL>>hist4bg(150,-50,100)", gate1 && (gateA || gateB) && "abs(p2p_p1500zero.fSp)<10", "same");
/*   
   TH1F ** hist = new TH1F[81];
   for (Int_t i = 0; i<4; i++){
   	for (Int_t j = 0; j <4; j++){
   		TString histTitle;
   		histTitle.Form("Sp | tof1:%4.1f, tof2:%4.1f",(i-1)*0.5, (j-4)*0.5);
   		TString histName;
   		histName.Form("hist%1d%1d", i,j);
   		hist[9*i+j] = new TH1F(histName, histTitle, 100, -50,50);	
   		hist[9*i+j]->SetLineColor(9*i+j);
   		hist[9*i+j]->SetMinimum(0);
   		hist[9*i+j]->SetMaximum(600);
   		
   		TString plot;
   		plot.Form("Sp[%2d]>>hist%1d%1d",9*i+j,i,j);
   		recoil->Draw(plot,"abs(wbeamZ)<50 && abs(theta1+theta2-87.5)<2.5","same");
   	}
	}
   */
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
