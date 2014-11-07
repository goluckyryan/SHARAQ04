{
  gROOT->Reset();
  gROOT->ProcessLine(".!date");
  gStyle->SetOptStat(0);
   
//   TFile *f0 = new TFile ("hist_mwdc.root");

//   TFile *f0 = new TFile ("23F_1027.root"); TTree *tree = (TTree*)f0->Get("tree");    
//   TFile *f1 = new TFile ("ppAll_1106_OpenCorr.root"); TTree *tree2 = (TTree*)f1->Get("tree");  

//   TFile *f1 = new TFile ("23F_0914_all.root"); TTree *tree2 = (TTree*)f1->Get("tree");
//   TFile *f2 = new TFile ("Rphys23Fclean.root","read"); TTree *recoil = (TTree*)f2->Get("recoil");  


//   TFile *f0 = new TFile ("23F_1106_nyoki_runs23_noCali.root"); TTree *tree = (TTree*)f0->Get("tree");
   TFile *f1 = new TFile ("23F_1106.root"); TTree *tree = (TTree*)f1->Get("tree");

//================ update.
//   TFile *f0 = new TFile ("23F_0912_all_1.root","update"); 
//   TFile *f1 = new TFile ("RppAll_0714_multiOffset.root","update"); TTree *recoil = (TTree*)f1->Get("recoil");   
//   f0->Close();
//========================================================

	//gROOT->ProcessLine("listg tree");
   TBrowser B("test","test", 900,600); 
   
	TCut pid23F = "TMath::Abs(tof_DS[0].fTiming-321.2)<3 && TMath::Abs(plaV775[0].fCharge-875)<75";
	TCut pid22o = "TMath::Abs(tof_DS[0].fTiming-304)<3 && TMath::Abs(plaV775[0].fCharge-800)<100";
	TCut pid8Li = "TMath::Abs(tof_DS[0].fTiming-314)<3 && TMath::Abs(plaV775[0].fCharge-530)<50";

/*
	TCut ang = "TMath::Abs((p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()-86)<3";
//	TCut basic = "gate.Test(4) ";
//	TCut tofD1 = "TMath::Abs(tof_D1.fTiming+15)<5";
//	TCut nyoki = "TMath::Abs(nyoki.fID-8)<=1 && nyoki.fCharge>1800";
//	TCut basic2 = "gate.Test(5) && !gate.Test(4)";
	TCut poltgt = "TMath::Abs(beamZ.fAverage-10)<60";
	TCut carbon = "TMath::Abs(beamZ.fAverage-10)<120";
	TCut Sp = "TMath::Abs(p2p.fSp)<60";
	
	//tree->Draw("(p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()>>g1(100,80,90)","","");
	//tree2->Draw("(p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()>>g2(100,80,90)","","same");
	
	
	
//================================================ Temp analysis   
/*
	Int_t Div[2] = {2,1}; 
	Int_t size = 400;
   TCanvas * cScript = new TCanvas("cScript", "cScript", 2000,0 , size*Div[0], size*Div[1]);
   cScript->Divide(Div[0],Div[1]);
   
   cScript->cd(1);
	tree->Draw("p2p.fRecoilL.Theta()*TMath::RadToDeg():p2p.fRecoilR.Theta()*TMath::RadToDeg()>>g1(100, 20,70, 100, 20, 70)","","colz");
	
	cScript->cd(2);
	tree2->Draw("p2p.fRecoilL.Theta()*TMath::RadToDeg():p2p.fRecoilR.Theta()*TMath::RadToDeg()>>g2(100, 20,70, 100, 20, 70)","","colz");

/*
	cScript->cd(1);
	//tree->Draw("p2p.fEx>>g1(60,-20,100)", basic + tofD1+ nyoki + poltgt +ang );
	//tree->Draw("p2p.fEx>>g2(60,-20,100)", !basic + !tofD1+ nyoki + poltgt +ang , "same");
	
	//tree->Draw("(p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()>>g1(60,60,90)", basic + tofD1+ nyoki + poltgt + Sp);
	//tree->Draw("(p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()>>g2(60,60,90)", !basic + !tofD1+ nyoki + poltgt + Sp , "same");
	
	//Sp = "TMath::Abs(p2p.fEx-(-2))<2";
	
	tree->Draw("p2p.fResidual.P()>>g1(40,0,300)", basic + tofD1+ nyoki + poltgt + "TMath::Abs(p2p.fEx)<5");
	tree->Draw("p2p.fResidual.P()>>g2(40,0,300)", !basic + !tofD1+ nyoki + poltgt + "TMath::Abs(p2p.fEx)<5" , "same");
	
	g2->Scale(0.21);
	g2->SetLineColor(2);
	g2->Draw("same");

	cScript->cd(2);
	TH1F * g3 = new TH1F(*g1 - *g2);
	g3->Draw();
	
	cScript->cd(3);
	tree->Draw("p2p.fResidual.P()>>h1(100,0,300)", basic + tofD1+ nyoki + poltgt + "TMath::Abs(p2p.fEx-16)<10");
	tree->Draw("p2p.fResidual.P()>>h2(100,0,300)", !basic + !tofD1+ nyoki + poltgt + "TMath::Abs(p2p.fEx-16)<10" , "same");
	
	h2->Scale(0.21);
	h2->SetLineColor(2);
	h2->Draw("same");

	cScript->cd(4);
	TH1F * h3 = new TH1F(*h1 - *h2);
	h3->Scale(1/h3->Integral(0,100));
	h3->Draw();
	
	cScript->cd(5);
	tree->Draw("p2p.fResidual.P()>>k1(40,0,300)", basic + tofD1+ nyoki + poltgt + "TMath::Abs(p2p.fEx-40)<10");
	tree->Draw("p2p.fResidual.P()>>k2(40,0,300)", !basic + !tofD1+ nyoki + poltgt + "TMath::Abs(p2p.fEx-40)<10" , "same");
	
	k2->Scale(0.21);
	k2->SetLineColor(2);
	k2->Draw("same");

	cScript->cd(6);
	TH1F * k3 = new TH1F(*k1 - *k2);
	k3->Scale(1/k3->Integral(0,100));
	k3->Draw();
	
	
	cScript->cd(7);
	tree->Draw("p2p.fResidual.P()>>q1(40, 0,300)", basic + tofD1+ nyoki + poltgt + "TMath::Abs(p2p.fEx-60)<10");
	tree->Draw("p2p.fResidual.P()>>q2(40, 0,300)", !basic + !tofD1+ nyoki + poltgt + "TMath::Abs(p2p.fEx-60)<10" , "same");
	
	q2->Scale(0.21);
	q2->SetLineColor(2);
	q2->Draw("same");

	cScript->cd(8);
	TH1F * q3 = new TH1F(*q1 - *q2);
	q3->Scale(1/q3->Integral(0,100));
	q3->Draw();
	/*
	Double_t para[18] = {20,0,4, 50,10,4, 120,15,4, 80,25,4, 30,40,5, 20,60,4}  ;
	TF1 * total = new TF1("total", "gaus(0) + gaus(3) + gaus(6) + gaus(9) + gaus(12) + gaus(15)", -10, 100);
	total->SetParameters(para);
	
	g3->Fit("total","R");
	
	total->GetParameters(para);

	Double_t fitRange[2] = {-10,100};
	TF1 * k1 = new TF1("k1", "gaus", fitRange[0], fitRange[1]);
	TF1 * k2 = new TF1("k2", "gaus", fitRange[0], fitRange[1]);
	TF1 * k3 = new TF1("k3", "gaus", fitRange[0], fitRange[1]);
	TF1 * k4 = new TF1("k4", "gaus", fitRange[0], fitRange[1]);
	TF1 * k5 = new TF1("k5", "gaus", fitRange[0], fitRange[1]);
	TF1 * k6 = new TF1("k6", "gaus", fitRange[0], fitRange[1]);
	
	
	k1->SetParameters(&para[0]);
	k1->SetLineColor(2);k1->SetLineWidth(1);k1->SetLineStyle(1);k1->Draw("same");
	k2->SetParameters(&para[3]);
	k2->SetLineColor(4);k2->SetLineWidth(1);k2->SetLineStyle(1);k2->Draw("same");
	k3->SetParameters(&para[6]);	
	k3->SetLineColor(6);k3->SetLineWidth(1);k3->SetLineStyle(1);k3->Draw("same");
	k4->SetParameters(&para[9]);
	k4->SetLineColor(7);k4->SetLineWidth(1);k4->SetLineStyle(1);k4->Draw("same");
	k5->SetParameters(&para[12]);
	k5->SetLineColor(8);k4->SetLineWidth(1);k4->SetLineStyle(1);k5->Draw("same");
	k6->SetParameters(&para[15]);
	k6->SetLineColor(9);k4->SetLineWidth(1);k4->SetLineStyle(1);k6->Draw("same");

	printf("reduced chi-square: %3.1f/%d = %3.1f\n", total->GetChisquare(), total->GetNDF(), total->GetChisquare()/total->GetNDF());



/*	
  	TCut nyokiS = "((nyoki.fID==7 && TMath::Abs(nyoki.fCharge-2650)<650) || (nyoki.fID==8 && TMath::Abs(nyoki.fCharge-2500)<500))";  
  	
  	TCut nyokiA = "((nyoki.fID==7 || nyoki.fID==8) && TMath::Abs(nyoki.fCharge-2650)<650)";
  	TCut nyoki7 = "(nyoki.fID==7 && TMath::Abs(nyoki.fCharge-2650)<650)";
  	TCut nyoki8 = "(nyoki.fID==8 && TMath::Abs(nyoki.fCharge-2500)<500)";
  	   
   TH1F* h1 = new TH1F("h1", "nyoki 7 ~ 8", 60, -20, 100);
   h1->SetMinimum(0);
   TH1F* h2 = new TH1F("h2", "nyoki 7", 50, 0, 1);
   TH1F* h3 = new TH1F("h3", "nyoki 8", 50, 0, 1);
   h2->SetMinimum(0);
   h3->SetLineColor(2);
   
   cScript->cd(1);
   //tree->Draw("p2p_c.fSp>>h1", "gate.Test(4) & TMath::Abs(vertex.fZ-170)<60" && nyokiS);
   
   tree->Draw("p2p.fResidual.Theta()*TMath::RadToDeg()>>h2", "gate.Test(4) & TMath::Abs(vertex.fZ-170)<60" && nyoki7);
   h2->Scale(1./h2->Integral(1,50));
   //cScript->cd(2);
   
   tree->Draw("p2p.fResidual.Theta()*TMath::RadToDeg()>>h3", "gate.Test(4) & TMath::Abs(vertex.fZ-170)<60" && nyoki8, "same");
   h3->Scale(1./h3->Integral(1,50));
   
   /*
   cScript->cd(3);
   TH1F * twoPthree = new TH1F(*h2);
   twoPthree->Add(h3,1);
   twoPthree->SetTitle("nyoki 7 + nyoki 8");
   twoPthree->SetMinimum(0);
   twoPthree->Draw();
   
   cScript->cd(4);
   TH1F* overlap = new TH1F(*twoPthree);
   overlap->SetTitle("nyoki 7 + nyoki 8 - (nyoki 7 & nyoki 8)");
   overlap->Sumw2();
   overlap->Add(h1, -1);
   overlap->Draw();
   
/*   
   TCut common = "gate.Test(4) && nyoki.fCharge>2000 && TMath::Abs(vertex.fZ)<60";
   TCut carbon = "gate.Test(4) && nyoki.fCharge>2000 && TMath::Abs(vertex.fZ-160)<60";
   
  	TH1F * hSp = new TH1F("hSp", "Sp", 160, -40, 120);
  	hSp->SetMinimum(0);
  	TH1F* hMomt1 = new TH1F("hMomt1", "Momt", 100, 0, 300);
   
   cScript->cd(1);
   tree->Draw("p2p.fSp>>hSp", common);
   tree->Draw("p2p_c.fSp>>hSpc(160,-40,120)", carbon, "same");
   
   cScript->cd(2);
   tree->Draw("TMath::Power(TMath::Power(0.84746*(p2p.fResidual.E())-1.310797*(p2p.fResidual.Pz()),2)+TMath::Power(p2p.fResidual.Px(),2)+TMath::Power(p2p.fResidual.Py(),2),0.5)>>hMomt1", common);
   tree->Draw("TMath::Power(TMath::Power(0.84746*(p2p.fResidual.E())-1.310797*(p2p.fResidual.Pz()),2)+TMath::Power(p2p.fResidual.Px(),2)+TMath::Power(p2p.fResidual.Py(),2),0.5)>>hMomtc(100,0,300)", carbon, "same");
   
   cScript->cd(3);
   tree->Draw("TMath::Power(TMath::Power(0.84746*(p2p.fResidual.E())-1.310797*(p2p.fResidual.Pz()),2)+TMath::Power(p2p.fResidual.Px(),2)+TMath::Power(p2p.fResidual.Py(),2),0.5):p2p.fSp>>h1(80,-40,120,60,0,300)", common, "colz");
   
   cScript->cd(4);
   tree->Draw("TMath::Power(TMath::Power(0.84746*(p2p_c.fResidual.E())-1.310797*(p2p_c.fResidual.Pz()),2)+TMath::Power(p2p_c.fResidual.Px(),2)+TMath::Power(p2p_c.fResidual.Py(),2),0.5):p2p_c.fSp>>h2(80,-40,120,60,0,300)", carbon, "colz");
      
 /*  cScript->cd(1);
   tree->Draw("nyoki.fCharge:p2p.fSp>>hSpn(160, -40, 120, 40, 500, 4500)", common, "colz");
   
   cScript->cd(5);
   tree->Draw("nyoki.fCharge:(p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()>>hOpen(60, 60, 90, 40, 500, 4500)", common, "colz");
   
   cScript->cd(2);
   */
/*   cScript->cd(1);
   tree->Draw("plaV775_R_raw.fTiming>>h1(2000,0,2000)",     "plaV775_R_raw.fID==1");
   cScript->cd(2);
   tree->Draw("plaV775_R_raw.fTiming>>h1a(200, 200,300)",   "plaV775_R_raw.fID==1");
   cScript->cd(3);
   tree->Draw("plaV775_R_raw.fTiming>>h1b(200, 1750,1850)", "plaV775_R_raw.fID==1");
*/

/*
   TCut common = "gate.Test(0) && gate.Test(6) && TMath::Abs(vertex.fZ)<100";
   
   cScript->cd(1);
   gROOT->ProcessLine(".!date"); printf(" nyoki 6 \n");
   tree->Draw("p2p.fSp>>h6(40,-40,120)", common && "nyoki.fID==6 && nyoki.fCharge>1500", "colz");
   
   cScript->cd(6);
   gROOT->ProcessLine(".!date"); printf(" nyoki 6 2D\n");
   tree->Draw("nyoki.fCharge:p2p.fSp>>h6n(40,-40,120,50,0, 4500)", common && "nyoki.fID==6", "colz");
   
   cScript->cd(2);
   gROOT->ProcessLine(".!date"); printf(" nyoki 7 \n");
   tree->Draw("p2p.fSp>>h7(80,-40,120)", common && "nyoki.fID==7 && nyoki.fCharge>2000", "colz");
   
   cScript->cd(7);
   gROOT->ProcessLine(".!date"); printf(" nyoki 7 2D \n");
   tree->Draw("nyoki.fCharge:p2p.fSp>>h7n(40,-40,120,40,500, 4500)", common && "nyoki.fID==7", "colz");
   
   cScript->cd(3);
   gROOT->ProcessLine(".!date"); printf(" nyoki 8 \n");
   tree->Draw("p2p.fSp>>h8(80,-40,120)", common && "nyoki.fID==8 && nyoki.fCharge>2000", "colz");
   
   cScript->cd(8);
   gROOT->ProcessLine(".!date"); printf(" nyoki 8 2D \n");
   tree->Draw("nyoki.fCharge:p2p.fSp>>h8n(40,-40,120,45,500, 4500)", common && "nyoki.fID==8", "colz");
   
   cScript->cd(4);
   gROOT->ProcessLine(".!date"); printf(" nyoki 9 \n");
   tree->Draw("p2p.fSp>>h9(40,-40,120)", common && "nyoki.fID==9 && nyoki.fCharge>2000", "colz");
   
   cScript->cd(9);
   gROOT->ProcessLine(".!date"); printf(" nyoki 9 2D \n");
   tree->Draw("nyoki.fCharge:p2p.fSp>>h9n(40,-40,120,45,500, 4500)", common && "nyoki.fID==9", "colz");
   
   cScript->cd(5);
   gROOT->ProcessLine(".!date"); printf(" nyoki all \n");
   tree->Draw("p2p.fSp>>hall(80,-40,120)", common && "nyoki.fCharge>2000", "colz");
   
   cScript->cd(10);
   gROOT->ProcessLine(".!date"); printf(" nyoki all 2D \n");
   tree->Draw("nyoki.fCharge:p2p.fSp>>halln(40,-40,120,45,500, 4500)", common, "colz");
   
   /*cScript->cd(4);
   //gROOT->ProcessLine(".!date"); printf(" nyoki all 2D \n");
   //tree->Draw("nyoki.fCharge:p2p.fSp>>hn(40,-40,120,40,500, 4500)", common , "colz");
   
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
