#include "HistSub.C"

void Ana(){
   gROOT->ProcessLine(".!date");
   gStyle->SetOptStat(0);
 
   TFile *f1 = new TFile ("23F_0914_all.root"); TTree *tree = (TTree*)f1->Get("tree");

   TCanvas * cAna = new TCanvas("cAna", "Ana", 0,0 , 1200, 800);
   cAna->Divide(3,2);
   
   
   TCut common = "gate.Test(3) && gate.Test(4)";
   TCut VertexZ = "TMath::Abs(vertex.fZ-12)<26";
   TCut VertexZ2 = "(TMath::Abs(vertex.fZ+38)<24 || TMath::Abs(vertex.fZ-70)<32)";
   //TCut OpenAng = "TMath::Abs((p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()-80)<10";
   
  
  	TCut gate = common + VertexZ;
  	TCut side = common + VertexZ2;
  	
  	gate.Print();
  	side.Print();
  	
  	TH1F * hSp = new TH1F("hSp", "Seperation energy", 50, -40, 110);
  	hSp->SetMinimum(0);
  	hSp->SetXTitle("Sp [MeV]");
  	hSp->SetYTitle("count / 3 MeV");
  	TH1F * hSpBG = new TH1F("hSpBG", "Sp", 50, -40, 110);
   hSpBG->SetLineColor(2);
   TH1F * hSpSub = new TH1F("hSpSub", "Sp2", 50, -40, 110);
  	hSpSub->SetXTitle("Sp [MeV]");
  	hSpSub->SetYTitle("count / 3 MeV");
  	//hSpSub->SetMinimum(0);
  	
  	TH1F * hOpenAng = new TH1F("hOpenAng", "OpenAng", 60, 40, 100);
  	hOpenAng->SetMinimum(0);
  	hOpenAng->SetXTitle("openning angle [deg]");
  	hOpenAng->SetYTitle("count / 1 deg");
  	TH1F * hOpenAngBG = new TH1F("hOpenAngBG", "OpenAng BG", 60, 40, 100);
   hOpenAngBG->SetLineColor(2);
   TH1F * hOpenAngSub = new TH1F("hOpenAngSub", "OpenAng Sub", 60, 40, 100);
  	//hSpSub->SetMinimum(0);
  	
  	TH1F* hvZ = new TH1F("hvZ", "vertex(Z)", 150, -100, 200);
  	hvZ->SetXTitle("vertex(Z) [mm]");
  	hvZ->SetYTitle("count / 2 mm");
  	TH1F* hvZBG = new TH1F("hvZBG", "vertex(Z)", 150, -100, 200);
  	hvZBG->SetLineColor(2);
  	
   cAna->cd(1);
   tree->Draw("vertex.fZ>>hvZc(150,-100,200)", common);
   printf("Draw(vertex.fZ, common) ... done \n");
   
   cAna->cd(2);
   tree->Draw("vertex.fZ>>hvZ",gate,"");   
   printf("Draw(vertex.fZ, gate) ... done \n");
   tree->Draw("vertex.fZ>>hvZBG",side,"same");
   printf("Draw(vertex.fZ, side) ... done \n");
   
   cAna->cd(3);
   tree->Draw("(p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()>>hOpenAng",gate);
   printf("Draw(openAngle, gate) ... done \n");
   tree->Draw("(p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()>>hOpenAngBG",side,"same");
   printf("Draw(openAngle, side) ... done \n");
   
   cAna->cd(4);
   hOpenAngSub = HistSub(hOpenAng, hOpenAngBG);
   hOpenAngSub->Draw();
   
   cAna->cd(5);
   tree->Draw("p2p.fSp>>hSp",gate);
   printf("Draw(Sp, gate) ... done \n");
   tree->Draw("p2p.fSp>>hSpBG",side, "same");
   printf("Draw(Sp, side) ... done \n");   
   
  	cAna->cd(6);
  	hSpSub = HistSub(hSp, hSpBG);
  	hSpSub->SetYTitle("count / 3 MeV");
  	hSpSub->Draw("");
  	
  	
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

