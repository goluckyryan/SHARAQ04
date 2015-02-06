//#include "HistSub.C"

void Ana(){
   gROOT->ProcessLine(".!date");
   gStyle->SetOptStat(0);
 
   TFile *f1 = new TFile ("23F_0204_all.root"); TTree *tree = (TTree*)f1->Get("tree");
	gROOT->ProcessLine("listg tree");

	Double_t bgRatio = 0.85; 

	Double_t pidZmin = 5;
	Double_t tofD1[2] = {35, 1}; //mid, half-width
	Double_t vertexZ[2] = {10, 60}; // mid, half-width
	Double_t openAng[2] = {80, 15}; // mid, hald-width


	//========================================================================
   Int_t Div[2] = {4,1};
   Int_t size[2] = {400,400};
   TCanvas * cAna = new TCanvas("cAna", "Ana", 0,0 , Div[0]*size[0], Div[1]*size[1]);
   cAna->Divide(Div[0],Div[1]);
   
   //========================================================================
   TString tofD1GateText ; tofD1GateText.Form("abs(tof_D1.fTiming-%2.0f)<%2.0f", tofD1[0], tofD1[1]);
   TString vertexZGateText; vertexZGateText.Form("TMath::Abs(vertex.fZ-%3.0f)<%3.0f", vertexZ[0], vertexZ[1]);
	TString openAngGateText; openAngGateText.Form("TMath::Abs((p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()-2.0f)<%2.0f", openAng[0], openAng[1]);
   TString pidZGateText; pidZGateText.Form("pid_ds.fZ>%1.0f", pidZmin);
   
   TCut nyoki = "nyoki.fCharge>1000 && nyoki.fCharge<2800";
   TCut nyokiID = "nyoki.fID == 9";
   TCut PID23fgate = "TMath::Abs(plaV1190_FH9.fCharge-5913)<147 && TMath::Abs(tof_US.fTiming+1463)<2";
   
   TCut tofD1Gate  = tofD1GateText;
   TCut vertexZGate = vertexZGateText;
   TCut tgtGate = "gate.Test(9)";
   TCut holderGate = "!gate.Test(9)"; //gate.Test(11) & 
   TCut OpenAngGate = openAngGateText;
   TCut s1xAGate = "smwdc_S1.fTrack.fX<0";
   TCut s1xBGate = "0<smwdc_S1.fTrack.fX && smwdc_S1.fTrack.fX<100";
   TCut pidZGate = pidZGateText;
   
   TCut commonGate = tofD1Gate + vertexZGate + pidZGate;// + s1xAGate;// + OpenAng;
  
   TCut VertexZ2Gate = "(TMath::Abs(vertex.fZ+44)<24 || TMath::Abs(vertex.fZ-80)<36)";
   
  	TCut signal = commonGate + tgtGate;
  	TCut background = commonGate + holderGate;
  	
  	signal.Print();
  	background.Print();
  	
  	TString tofD1text; tofD1text.Form("|tof_D1-%2.0f|<%2.0f",tofD1[0],tofD1[1]);
   TString vertexZtext; vertexZtext.Form("|vertex.Z-%3.0f|<%3.0f",  vertexZ[0], vertexZ[1]);
  	TString openAngtext; openAngtext.Form("|#Delta#theta-%2.0f|<%2.0f",openAng[0], openAng[1]);
  	TString pidZtext; pidZtext.Form("pid.Z>%1.0f",pidZmin);
  	TString s1xAtext;
  	TString tgttext = "target";
  	TString holdertext = "holder";
  	
  	//========================================================================
  	
  	TString countText;
   TLatex *text = new TLatex();
   text->SetNDC();
   text->SetTextSize(0.04);
  	//========================================================================
   cAna->cd(1);
	tree->Draw("smwdc_S1.fTrack.fX:p2p.fEx>>hs1xExA(80,-40,120, 50, -200, 200)", tofD1Gate + vertexZGate + pidZGate + tgtGate, "colz");

/*   text->DrawLatex(0.6, 0.80, tofD1text);
   text->DrawLatex(0.6, 0.75, pidZtext);
   text->DrawLatex(0.6, 0.70, vertexZtext);
   text->SetTextColor(2);text->DrawLatex(0.6, 0.6, tgttext);
   text->SetTextColor(4);text->DrawLatex(0.6, 0.5, holdertext);
/**/
   
   //tree->Draw("p2p.fRecoilL.Theta()*TMath::RadToDeg():p2p.fRecoilR.Theta()*TMath::RadToDeg()>>ha(55,15,70,55,15,70)",gate + "abs(pid_ds.fAOQ-2.55)<0.22", "colz");
   
   
   cAna->cd(2);
   tree->Draw("smwdc_S1.fTrack.fX:p2p.fEx>>hs1xExB(80,-40,120, 50, -200, 200)", tofD1Gate + vertexZGate + !pidZGate + tgtGate, "colz");
  	
   cAna->cd(3);
   tree->Draw("p2p.fEx>>hSpA( 50, -20, 80)",  tofD1Gate + vertexZGate + pidZGate + tgtGate, "colz");
   tree->Draw("p2p.fEx>>hSpB( 50, -20, 80)",  tofD1Gate + vertexZGate + !pidZGate + tgtGate, "same");
   
   cAna->cd(4);
   tree->Draw("p2p.fEx>>hSpAa( 50, -20, 80)",  tofD1Gate + !vertexZGate + pidZGate + tgtGate , "colz");
  	tree->Draw("p2p.fEx>>hSpAb( 50, -20, 80)",  tofD1Gate + !vertexZGate + !pidZGate + tgtGate , "same");

  	/**/
  	//========================================================================
  	/*
	Double_t para[3*3];
	Double_t paraError[3*3];
	
	TF1 * g1 = new TF1("g1", "gaus", -10, 5);
	TF1 * g2 = new TF1("g2", "gaus",  5, 20);
	TF1 * g3 = new TF1("g3", "gaus", 20, 30);
	
	TF1 * total = new TF1("total", "gaus(0)+gaus(3)+gaus(6)", -20, 30);
	total->SetLineColor(2);
	total->SetParLimits(2,0,10);
	total->SetParLimits(5,0,10);
	total->SetParLimits(8,0,10);
	//total->FixParameter(1,-2);
	//total->FixParameter(4,13.26);
	//total->FixParameter(7,23.8);

	g1->FixParameter(1,0);
	//g2->FixParameter(1,13.26);
	g3->FixParameter(1,23.8);
	
	hSpSub->Fit(g1, "R0");
	hSpSub->Fit(g2, "R0+");
	hSpSub->Fit(g3, "R0+");
	
	g1->GetParameters(&para[0]);
	g2->GetParameters(&para[3]);
	g3->GetParameters(&para[6]);
	
//	g1->GetParErrors(&paraError[0]);
//	g2->GetParErrors(&paraError[3]);
//	g3->GetParErrors(&paraError[6]);

	total->SetParameters(para);
	
	hSpSub->Fit(total,"R+");

	TF1 * k1 = new TF1("k1", "gaus", -20, 60);
	TF1 * k2 = new TF1("k2", "gaus", -20, 60);
	TF1 * k3 = new TF1("k3", "gaus", -20, 60);
	
	total->GetParameters(para);
	
	k1->SetParameters(&para[0]);
	k2->SetParameters(&para[3]);
	k3->SetParameters(&para[6]);
	
//	k1->SetParErrors(&paraError[0]);
//	k2->SetParErrors(&paraError[3]);
//	k3->SetParErrors(&paraError[6]);
	
	k1->SetLineColor(1);k1->Draw("same");
	k2->SetLineColor(2);k2->Draw("same");
	k3->SetLineColor(4);k3->Draw("same");
	
	printf("x-sec g1: %.0f(%.0f)\n", k1->Integral(para[1]-3*para[0],para[1]+3*para[0]), k1->IntegralError(para[1]-3*para[0],para[1]+3*para[0]));
	printf("x-sec g2: %.0f(%.0f)\n", k2->Integral(para[4]-3*para[3],para[4]+3*para[3]), k2->IntegralError(para[4]-3*para[3],para[4]+3*para[3]));
	printf("x-sec g3: %.0f(%.0f)\n", k3->Integral(para[7]-3*para[6],para[7]+3*para[6]), k3->IntegralError(para[7]-3*para[6],para[7]+3*para[6]));
   
   /*
   TCanvas * cAna2 = new TCanvas("cAna2", "Ana2", 1400,0 , 500, 500);
   cAna2->cd();
   
   TCut SpP1  = "TMath::Abs(p2p.fSp-24)<5.2";
   TCut SpD5  = "TMath::Abs(p2p.fSp-12)<5";
   
   TCut anaP1 = gate + SpP1;
   TCut anaD5 = gate + SpD5;
   
   TH1F* hkP1 = new TH1F("hkP1", "Momentum Distribution", 15, 0, 300);
   hkP1->SetXTitle("k [MeV/c]");
   hkP1->SetYTitle("count / 20 MeV/c");
   TH1F* hkD5 = new TH1F("hkD5", "Momentum Distribution", 15, 0, 300);
   hkD5->SetLineColor(2);
   
//   tree->Draw("TMath::Power(TMath::Power(0.84746*(938.272+p2p.fIncident.E()-p2p.fRecoilL.E()-p2p.fRecoilR.E())-1.310797*(p2p.fResidual.Pz()),2)+TMath::Power(p2p.fResidual.Px(),2)+TMath::Power(p2p.fResidual.Py(),2),0.5)>>hkP1", anaP1);
//   tree->Draw("TMath::Power(TMath::Power(0.84746*(938.272+p2p.fIncident.E()-p2p.fRecoilL.E()-p2p.fRecoilR.E())-1.310797*(p2p.fResidual.Pz()),2)+TMath::Power(p2p.fResidual.Px(),2)+TMath::Power(p2p.fResidual.Py(),2),0.5)>>hkD5", anaD5,"same");
   
   tree->Draw("TMath::Power(TMath::Power(0.84746*(p2p.fResidual.E())-1.310797*(p2p.fResidual.Pz()),2)+TMath::Power(p2p.fResidual.Px(),2)+TMath::Power(p2p.fResidual.Py(),2),0.5)>>hkP1", anaP1);
   tree->Draw("TMath::Power(TMath::Power(0.84746*(p2p.fResidual.E())-1.310797*(p2p.fResidual.Pz()),2)+TMath::Power(p2p.fResidual.Px(),2)+TMath::Power(p2p.fResidual.Py(),2),0.5)>>hkD5", anaD5,"same");
   
   
   */
}  

