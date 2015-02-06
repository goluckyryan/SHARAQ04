void Ana_2(){
   gROOT->ProcessLine(".!date");
   gStyle->SetOptStat(0);
 
   TFile *f1 = new TFile ("23F_1002.root"); TTree *tree = (TTree*)f1->Get("tree");
	gROOT->ProcessLine("listg tree");

   TCanvas * cAna = new TCanvas("cAna", "Ana", 2000,0 , 400, 400);
   //cAna->Divide(4,2);
   
   
   Int_t SpHistRange[2] = {-40,120};
   Int_t SpHistBin = 80;
   
   Int_t nyokiIDnum = 5;
   Int_t nyokiQRange[2] = { 2000, 10000};
   Int_t vertexZHW = 60;
   
   if (nyokiIDnum == 7){
     nyokiQRange[1] = 3300;
     SpHistBin = 160;
   }else if (nyokiIDnum == 8){
     nyokiQRange[1] = 3000;
     SpHistBin = 160;
   }
   
   TString nyokiIDStr, nyokiQStr, vertexZStr;
   nyokiIDStr.Form("nyoki.fID == %d", nyokiIDnum);
   nyokiQStr.Form("nyoki.fCharge>%d && nyoki.fCharge<%d", nyokiQRange[0],nyokiQRange[1]);
   vertexZStr.Form("TMath::Abs(vertex.fZ)<%d", vertexZHW);
   TCut nyokiID,nyokiQ, VertexZ;
   nyokiID = nyokiIDStr;
   nyokiQ = nyokiQStr;
   VertexZ = vertexZStr;
   
   TCut OpenAng = "TMath::Abs((p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()-80)<10";
   TCut OpenPhi = "TMath::Abs(TMath::Abs(p2p.fRecoilL.Phi()-p2p.fRecoilR.Phi())*TMath::RadToDeg()-150)<10";
   
   //TCut PID23f = "TMath::Abs(plaV1190_FH9.fCharge-5913)<147 && TMath::Abs(tof_US.fTiming+1463)<2";
   TCut common = "gate.Test(9)" + nyokiQ + nyokiID;
  
  	TCut gate = common + VertexZ;// + OpenPhi;
  	TCut side = common ;//+ VertexZ2;
  	
  	gate.Print();
  	side.Print();
  	
  	//************************************************
  	Int_t binWidth = (SpHistRange[1] - SpHistRange[0])*1./SpHistBin;
  	TString hSpTitle;
  	hSpTitle.Form("Seperation energy | Nyoki-%d", nyokiIDnum);
  	TH1F * hSp = new TH1F("hSp", hSpTitle, SpHistBin, SpHistRange[0], SpHistRange[1]);
  	hSp->SetMinimum(0);
  	hSp->SetXTitle("Sp [MeV]");
  	TString hSpYTitle;
  	hSpYTitle.Form("count / %d MeV", binWidth);
  	hSp->SetYTitle(hSpYTitle);
  	
  	TString hSpNyokiTitle;
  	hSpNyokiTitle.Form("Sp vs Nyoki_%0d", nyokiIDnum); 
  	TH2F * hSpNyoki = new TH2F("hSpNyoki", hSpNyokiTitle, SpHistBin, SpHistRange[0], SpHistRange[1], 35, 500, 4000);
  	hSpNyoki->SetXTitle("Sp [MeV]");
  	hSpNyoki->SetYTitle("Nyoki Q [a.u.]");
  	
  	TH1F * hOpenAng = new TH1F("hOpenAng", "OpenAng", 60 , 40, 100);
  	hOpenAng->SetMinimum(0);
  	hOpenAng->SetXTitle("Openning angle [deg]");
  	hOpenAng->SetYTitle("count / 1 deg");
  	TString hOpenAngNyokiTitle;
  	hOpenAngNyokiTitle.Form("OpenAngle vs Nyoki_%0d", nyokiIDnum); 
  	TH2F * hOpenAngNyoki = new TH2F("hOpenAngNyoki", hOpenAngNyokiTitle, SpHistRange[1], 40, 100, 35, 500, 4000);
  	hOpenAngNyoki->SetXTitle("Openning Angle [1 deg]");
  	hOpenAngNyoki->SetYTitle("Nyoki Q [a.u.]");
  	
  	TH1F* hvZc = new TH1F("hvZc", "vertex(Z)", 180, -100, 260);
  	hvZc->SetXTitle("vertex(Z) [mm]");
  	hvZc->SetYTitle("count / 2 mm");
  	TH1F* hvZ = new TH1F("hvZ", "vertex(Z)", 180, -100, 260);
  	hvZ->SetXTitle("vertex(Z) [mm]");
  	hvZ->SetYTitle("count / 2 mm");
  	hvZ->SetLineColor(2);
  	
  	
  	//******************************************************
   /*cAna->cd(1);
   tree->Draw("vertex.fZ>>hvZc", common);
   gROOT->ProcessLine(".!date"); printf("Draw(vertex.fZ, common) ... done \n");
   tree->Draw("vertex.fZ>>hvZ",gate,"same");   
   gROOT->ProcessLine(".!date"); printf("Draw(vertex.fZ, gate) ... done \n");
   
   cAna->cd(2);
   tree->Draw("(p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()>>hOpenAng",gate);
   gROOT->ProcessLine(".!date"); printf("Draw(openAngle, gate) ... done \n");
   
   cAna->cd(5);
   tree->Draw("TMath::Abs(p2p.fRecoilL.Phi()-p2p.fRecoilR.Phi())*TMath::RadToDeg()>>h1(60,140,200)",gate);
   
   cAna->cd(6);
   tree->Draw("nyoki.fCharge:(p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()>>hOpenAngNyoki",gate , "colz");

   
  	cAna->cd(7);
  	tree->Draw("nyoki.fCharge:p2p.fSp>>hSpNyoki", gate, "colz");
   */

   cAna->cd(1);
   tree->Draw("p2p.fSp>>hSp",gate);
   gROOT->ProcessLine(".!date"); printf("Draw.(Sp, gate) ... done \n");
   
   /*
	//****************************************
  	cAna->cd(3);
  	
  	const Int_t fitType = 2; // 1 = poly2, 2 = poly2 + gaus, 3 = poly2 + 2 x guas ...
  	
	TF1 * g1 = new TF1("g1", "pol2", SpHistRange[0], SpHistRange[1]);
	TF1 * g2 = new TF1("g2", "gaus",  10, 40);
	TF1 * g3 = new TF1("g3", "gaus", 55, 70);
	TF1 * g4 = new TF1("g4", "gaus",  35, 45);
	
	TF1 * total;
	
	if( fitType == 2){
		total = new TF1("total", "pol2(0) + gaus(3)", SpHistRange[0], SpHistRange[1]);
	}else if( fitType == 3){	
		total = new TF1("total", "pol2(0) + gaus(3) + gaus(6)", SpHistRange[0], SpHistRange[1]);
	}else if( fitType == 4){
	   total = new TF1("total", "pol2(0) + gaus(3) + gaus(6) + gaus(9)", SpHistRange[0], SpHistRange[1]);
	}
	total->SetLineColor(2);
	total->SetLineWidth(1);
	
	//total->SetParLimits(3,50,150);
	//total->SetParLimits(4,20,30);
	total->SetParLimits(5,1,10);
	
	if(fitType >= 3){
		//total->SetParLimits(6,0,100);
		total->SetParLimits(7,57,70);
		total->SetParLimits(8,5,20);
	}
	
	if(fitType >= 4){
		total->SetParLimits(9,50,150);
		total->SetParLimits(10,25,40);
		total->SetParLimits(11,1,10);
	}
	
	printf("***********fit poly2\n");	hSp->Fit(g1, "R0");
	printf("***********fit guas 1\n");  hSp->Fit(g2, "R0+");
	
	Double_t para[3*fitType];
	
	g1->GetParameters(&para[0]);
	g2->GetParameters(&para[3]);
	
	if(fitType >= 3){
		printf("***********fit guas 2\n");  hSp->Fit(g3, "R0+");
		g3->GetParameters(&para[6]);
	}
	if(fitType >=4 ){
		printf("***********fit guas 3\n");  hSp->Fit(g4, "R0+");
		g4->GetParameters(&para[9]);
	}
	
	total->SetParameters(para);
	
	printf("***********fit total\n");  hSp->Fit(total,"");
	total->GetParameters(para);
	
	TF1 * k1 = new TF1("k1", "pol2", SpHistRange[0], SpHistRange[1]);
	TF1 * k2 = new TF1("k2", "gaus", SpHistRange[0], SpHistRange[1]);
	TF1 * k3;
	TF1 * k4;
	
	k1->SetParameters(&para[0]);
	k2->SetParameters(&para[3]);

	k1->SetLineColor(1);k1->SetLineWidth(1);k1->SetLineStyle(1);k1->Draw("same");
	k2->SetLineColor(4);k2->SetLineWidth(1);k2->SetLineStyle(1);//k2->Draw("same");
			
	if(fitType >= 3){
		k3 = new TF1("k3", "gaus", SpHistRange[0], SpHistRange[1]);
		k3->SetParameters(&para[6]);	
		k3->SetLineColor(6);k3->SetLineWidth(1);k3->SetLineStyle(1);//k3->Draw("same");
	}
	if(fitType >=3 ){
		k4 = new TF1("k4", "gaus", SpHistRange[0], SpHistRange[1]);
		k4->SetParameters(&para[9]);
		k4->SetLineColor(7);k4->SetLineWidth(1);k4->SetLineStyle(1);//k4->Draw("same");
	}

	//*********************************
	Double_t minX = para[4]-3*para[5];
	Double_t maxX = para[4]+3*para[5];
	Double_t CountFit = k2->Integral(minX,maxX)/binWidth; 
	printf("x-sec fit: %.0f\n", CountFit);
	printf("reduced chi-square: %3.1f/%d = %3.1f\n", total->GetChisquare(), total->GetNDF(), total->GetChisquare()/total->GetNDF());
	
	
	TString textStr;
	TLatex text;
	text.SetNDC(1);
	text.SetTextSize(0.04);
	textStr.Form("#chi^{2}/NDF: %3.1f", total->GetChisquare()/total->GetNDF());
	text.DrawLatex(0.15, 0.8, textStr.Data());
	
	textStr.Form("mean: %3.1f#pm%3.1f", para[4], total->GetParError(4));
	text.DrawLatex(0.6, 0.7, textStr.Data());
	textStr.Form("#sigma: %3.1f#pm%3.1f", para[5], total->GetParError(5));
	text.DrawLatex(0.6, 0.65, textStr.Data());
	if( fitType>=3){
		textStr.Form("mean: %3.1f#pm%3.1f", para[7], total->GetParError(7));
		text.DrawLatex(0.6, 0.2, textStr.Data());
		textStr.Form("#sigma: %3.1f#pm%3.1f", para[8], total->GetParError(8));
		text.DrawLatex(0.6, 0.15, textStr.Data());	
	}
	
	TH1F* hSignal = new TH1F(*hSp);
	hSignal->Sumw2();
	hSignal->Add(k1, -1);
	
	cAna->cd(4);
	hSignal->Draw();
	k2->Draw("same");
	if(fitType >= 3) k3->Draw("same");
	if(fitType >=3 ) k4->Draw("same");
	
	Double_t Count = hSignal->Integral(hSp->FindBin(minX), hSp->FindBin(maxX));
	printf("x-sec count[%d,%d]: %.0f\n", hSp->FindBin(minX), hSp->FindBin(maxX), Count);
	textStr.Form("Count: %.0f[%.0f]", Count, CountFit);
	text.DrawLatex(0.5, 0.7, textStr.Data());
	
	if( fitType >= 3){
		textStr.Form("Count: [%.0f]", k3->Integral(para[7]-3*para[8],para[7]+3*para[8])/binWidth );
		text.DrawLatex(0.5, 0.65, textStr.Data());	
	}
	
	
	
	TLine line;
	line.SetLineColor(3);
	line.SetLineWidth(1);
	line.DrawLine(minX, 0, minX, 30);
	line.DrawLine(maxX, 0, maxX,30);
   
   //*********************************
   //TCanvas * cAna2 = new TCanvas("cAna2", "Ana2", 1400,0 , 500, 500);
   cAna->cd(8);
   
   TString SpGateStr1,SpGateStr2;
   TCut SpGate1, SpGate2;
   
   SpGateStr1.Form("TMath::Abs(p2p.fSp-%.1f)<%.1f", para[4], 3*para[5]);
   SpGate1 = SpGateStr1;
   SpGate1.Print();
   if( fitType >=3){
	   SpGateStr2.Form("TMath::Abs(p2p.fSp-%.1f)<%.1f", para[7], para[8]);   
	   SpGate2 = SpGateStr2;
   	SpGate2.Print();
   }
   
   
   TCut ana1 = gate + SpGate1;
   TCut ana2 = gate + SpGate2;   
   
   TH1F* hMomt1 = new TH1F("hMomt1", "Momentum Distribution", 30, 0, 300);
   hMomt1->SetXTitle("k [MeV/c]");
   hMomt1->SetYTitle("count / 10 MeV/c");
   
   TH1F* hMomt2;
   if ( fitType >=3 ){
   	hMomt2 = new TH1F("hMomt2", "Momentum Distribution", 30, 0, 300);
   	hMomt2->SetLineColor(2);
   }
   
//   tree->Draw("TMath::Power(TMath::Power(0.84746*(938.272+p2p.fIncident.E()-p2p.fRecoilL.E()-p2p.fRecoilR.E())-1.310797*(p2p.fResidual.Pz()),2)+TMath::Power(p2p.fResidual.Px(),2)+TMath::Power(p2p.fResidual.Py(),2),0.5)>>hkP1", anaP1);
//   tree->Draw("TMath::Power(TMath::Power(0.84746*(938.272+p2p.fIncident.E()-p2p.fRecoilL.E()-p2p.fRecoilR.E())-1.310797*(p2p.fResidual.Pz()),2)+TMath::Power(p2p.fResidual.Px(),2)+TMath::Power(p2p.fResidual.Py(),2),0.5)>>hkD5", anaD5,"same");
   
   tree->Draw("TMath::Power(TMath::Power(0.84746*(p2p.fResidual.E())-1.310797*(p2p.fResidual.Pz()),2)+TMath::Power(p2p.fResidual.Px(),2)+TMath::Power(p2p.fResidual.Py(),2),0.5)>>hMomt1", ana1);
	if( fitType>=3){
		tree->Draw("TMath::Power(TMath::Power(0.84746*(p2p.fResidual.E())-1.310797*(p2p.fResidual.Pz()),2)+TMath::Power(p2p.fResidual.Px(),2)+TMath::Power(p2p.fResidual.Py(),2),0.5)>>hMomt2", ana2, "same");
	}
   */
}  

