{
  gROOT->Reset();
  gROOT->ProcessLine(".!date");
  gStyle->SetOptStat(0);
   
  TFile *f0 = new TFile ("23F_0920_pid_ppcoin_hist.root"); //TTree *tree1 = (TTree*)f0->Get("tree");  

   //TCut PIDds = "nyoki.fID==7 && TMath::Abs(nyoki.fCharge-2950)<450";
  // TCut PID23f = "TMath::Abs(plaV1190_FH9.fCharge-5913)<147 && TMath::Abs(tof_US.fTiming+1463)<2";
    
   //   TFile *f1 = new TFile ("23F_0914_all.root"); TTree *tree2 = (TTree*)f1->Get("tree");
//   TFile *f2 = new TFile ("Rphys23Fclean.root","read"); TTree *recoil = (TTree*)f2->Get("recoil");   

	// update.
//   TFile *f0 = new TFile ("23F_0912_all_1.root","update"); 
//   TFile *f1 = new TFile ("RppAll_0714_multiOffset.root","update"); TTree *recoil = (TTree*)f1->Get("recoil");   
//   f0->Close();

//  TBrowser B("test","test", 900,600); 
   
   
//============= Temp analysis   
/*
   TCanvas * cScript = new TCanvas("cScript", "cScript", 0,0 , 1200, 800);
   cScript->Divide(3,2);
   TCut common = "gate.Test(3) && gate.Test(4)";
   
   //cScript->cd(1);
   //tree->Draw("vertex.fZ:vertex.fX>>hv(100,-20,20,100,-100,200)","","colz");
//   tree->Draw("vertex.fZ>>hZ(50,-100,100)","gate.Test(3) && gate.Test(5)");
//	tree->Draw("plaV775.fCharge:tofS0D[0].fTiming>>hpid(100,-120,-110,100,0,3000)", "!TMath::IsNaN(tofS0D[0].fTiming) && plaV775.GetDetID()==4", "colz");
   
   
   TCut VertexZ = "TMath::Abs(vertex.fZ-12)<26";
   TCut VertexZ2 = "(TMath::Abs(vertex.fZ+38)<24 || TMath::Abs(vertex.fZ-66)<28)";
//   TCut VertexZ2 = "TMath::Abs(vertex.fZ-50)<25";
   TCut OpenAng = "TMath::Abs((p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()-80)<10";
   TCut SpGate  = "TMath::Abs(p2p.fSp2-30)<30";
  
  	TCut gate = common + VertexZ;
  	TCut side = common + VertexZ2;
  	
  	gate.Print();
  	side.Print();
  	
  	TH1F * hSp = new TH1F("hSp", "Sp", 50, -40, 110);
  	hSp->SetMinimum(0);
  	TH1F * hSpS = new TH1F("hSpS", "Sp", 50, -40, 110);
   hSpS->SetLineColor(2);
   TH1F * hSp2 = new TH1F("hSp2", "Sp2", 50, -40, 110);
  	//hSp2->SetMinimum(0);
  	
  	TH1F * hOpenAng = new TH1F("hOpenAng", "OpenAng", 60, 40, 100);
  	hOpenAng->SetMinimum(0);
  	TH1F * hOpenAngBG = new TH1F("hOpenAngBG", "OpenAng BG", 60, 40, 100);
   hOpenAngBG->SetLineColor(2);
   TH1F * hOpenAngSub = new TH1F("hOpenAngSub", "OpenAng Sub", 60, 40, 100);
  	
  	//hSp2->SetMinimum(0);
  	
   cScript->cd(1);
   tree->Draw("vertex.fZ>>hvZ(150,-100,200)", common);
   
   cScript->cd(2);
   tree->Draw("vertex.fZ>>hvZc(150,-100,200)",gate,"");   
   tree->Draw("vertex.fZ>>hvZs(150,-100,200)",side,"same");
   
   cScript->cd(3);
   tree->Draw("(p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()>>hOpenAng",gate);
   tree->Draw("(p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()>>hOpenAngBG",side,"same");
   
   cScript->cd(4);
   hOpenAngSub = HistSub(hOpenAng, hOpenAngBG);
   hOpenAngSub->Draw();
   
   cScript->cd(5);
   tree->Draw("p2p.fSp>>hSp",gate);
   tree->Draw("p2p.fSp>>hSpS",side, "same");
   
   
  	cScript->cd(6);
  	hSp2 = HistSub(hSp, hSpS);
  	hSp2->Draw("");
  	
	Double_t para[3*3];
	
	TF1 * g1 = new TF1("g1", "gaus", -10, 5);
	TF1 * g2 = new TF1("g2", "gaus",  5, 20);
	TF1 * g3 = new TF1("g3", "gaus", 20, 35);
	
	TF1 * total = new TF1("total", "gaus(0)+gaus(3)+gaus(6)", -20, 35);
	total->SetLineColor(2);
	total->SetParLimits(2,0,10);
	total->SetParLimits(5,0,10);
	total->SetParLimits(8,0,10);
	//total->FixParameter(1,-2);
	//total->FixParameter(4,13.26);
	//total->FixParameter(7,23.8);

	g1->FixParameter(1,0);
	g2->FixParameter(1,13.26);
	g3->FixParameter(1,23.8);
	
	hSp2->Fit(g1, "R0");
	hSp2->Fit(g2, "R0+");
	hSp2->Fit(g3, "R0+");
	
	g1->GetParameters(&para[0]);
	g2->GetParameters(&para[3]);
	g3->GetParameters(&para[6]);

	total->SetParameters(para);
	
	hSp2->Fit(total,"R+");

	TF1 * k1 = new TF1("k1", "gaus", -20, 60);
	TF1 * k2 = new TF1("k2", "gaus", -20, 60);
	TF1 * k3 = new TF1("k3", "gaus", -20, 60);
	
	total->GetParameters(para);
	
	k1->SetParameters(&para[0]);
	k2->SetParameters(&para[3]);
	k3->SetParameters(&para[6]);
	
	k1->SetLineColor(1);k1->Draw("same");
	k2->SetLineColor(2);k2->Draw("same");
	k3->SetLineColor(3);k3->Draw("same");
   
   
/*   
   cScript->cd(4);
   tree->Draw("vertex.fZ>>hZg(50,-100,100)","gate.Test(3) && gate.Test(5)" && OpenAng);
		
   cScript->cd(5);
   tree->Draw("(p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()>>hOpenAngg1(60,40,100)","gate.Test(3) && gate.Test(5)" && VertexZ);
   tree->Draw("(p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()>>hOpenAngg2(60,40,100)","gate.Test(3) && gate.Test(5)" && VertexZ2, "same");
   
   cScript->cd(6);
   tree->Draw("p2p.fSp2>>hSpg1(50,-120,280)","gate.Test(3) && gate.Test(5)" && VertexZ);
   tree->Draw("p2p.fSp2>>hSpg2(50,-120,280)","gate.Test(3) && gate.Test(5)" && VertexZ2, "same");
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
