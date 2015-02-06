TF1 * total;
const Int_t numGauss = 4;// number of gauss
const int NPAR = 3*numGauss;

Double_t fixSigma = 3.0; //3.0 is not fixed
Double_t para[3*numGauss] = {300, 32, 10};
//Double_t para[3*numGauss] = {50, 30, 5, 10, 40,7};
//Double_t para[3*numGauss] = {20, 13.3, 5 , 160, 30, 5, 120, 40, 5};
Double_t para[3*numGauss] = {20, 0, 5, 20, 10, 5 , 160, 20, 5, 120, 40, 5};
//Double_t para[3*numGauss] = {20, 13, fixSigma, 160, 28, fixSigma, 120, 40, fixSigma};
//Double_t para[3*numGauss] = {20, 13.3, fixSigma, 40, 23.3, fixSigma, 100, 36, fixSigma, 10, 40, fixSigma};
//Double_t para[3*numGauss] = {20,0,4, 50,10,4, 120,15,4, 80,25,4, 30,40,5, 20,60,4};


void Ana_carbon(){
   //gROOT->Reset();
   gROOT->ProcessLine(".!date");
   gStyle->SetOptStat(0);
 
   TFile *f1 = new TFile ("23F_0205_all.root"); TTree *tree = (TTree*)f1->Get("tree");
	//gROOT->ProcessLine("listg tree");

	Int_t Div[2] = {2,1};
   
   Int_t SpHistRange[2] = {-20,100};
   Int_t SpHistBin = 120;
   
   Int_t fitRange[2] = {-20, 100};
   
   Int_t vertexZHW = 20;
   
   Double_t factor = 1;

   
  
   //*****************************
   TString vertexZStr;
   vertexZStr.Form("TMath::Abs(vertex.fZ-15)<%d", vertexZHW);
   TCut VertexZ;
   VertexZ = vertexZStr;
   
   TCut OpenPhi = "TMath::Abs(TMath::Abs(p2p.fRecoilL.Phi()-p2p.fRecoilR.Phi())*TMath::RadToDeg()-150)<10";
  
	TCut ang = "TMath::Abs((p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()-75)<15";
	
	TCut basic = "gate.Test(9)";
	TCut tofD1 = "TMath::Abs(tof_D1.fTiming-35)<2 ";
	TCut basic2 = "gate.Test(11) && !gate.Test(9)";
	TCut carbon = "TMath::Abs(vertex.fZ-160)<60";
	
	TCut pidZ = "pid_ds.fZ>5";
	TCut s1xcut = "abs(smwdc_S1.fTrack.fX-50)<180";
  
  	TCut gate = tofD1 + pidZ + s1xcut + VertexZ ;// + ang ;//basic + + nyokiID + nyokiQ  + OpenPhi;
  	TCut side = tofD1 + !pidZ + s1xcut + VertexZ ;//+ ang ;//!basic ++ nyokiID + nyokiQ
  	
  	gate.Print();
  	side.Print();
  	
	TString textStr;
	TLatex text;
	text.SetNDC(1);
	text.SetTextSize(0.035);
  	
  	//***************************
  	Double_t binWidth = (SpHistRange[1] - SpHistRange[0])*1./SpHistBin;
  	printf("Sp Range: (%.1f, %.1f), SpBin: %.1f , bin width = %.2f\n",SpHistRange[0], SpHistRange[1], SpHistBin, binWidth);

   TCanvas * cAna = new TCanvas("cAna", "Ana", 2000,0 , 400*Div[0], 400*Div[1]);
   cAna->Divide(Div[0], Div[1]);
  	
  	TString hSpTitle;
   hSpTitle.Form("Excitation energy ");
  	TH1F * hSp = new TH1F("hSp", hSpTitle, SpHistBin, SpHistRange[0], SpHistRange[1]);
  	hSp->SetMinimum(0);
  	hSp->SetXTitle("Ex [MeV]");
  	TString hSpYTitle;
  	hSpYTitle.Form("count / %.2f MeV", binWidth);
  	hSp->SetYTitle(hSpYTitle);
  	TH1F * hSpCarbon = new TH1F("hSpCarbon", "Seperation energy Carbon", SpHistBin, SpHistRange[0], SpHistRange[1]);
  	hSpCarbon->SetLineColor(2);
  	
  	TH1F * hOpenAng = new TH1F("hOpenAng", "OpenAng", 60 , 40, 100);
  	hOpenAng->SetMinimum(0);
  	hOpenAng->SetXTitle("Openning angle [deg]");
  	hOpenAng->SetYTitle("count / 1 deg");
  	TH1F * hOpenAngCarbon = new TH1F("hOpenAngCarbon", "OpenAng Carbon", 60 , 40, 100);
  	hOpenAngCarbon->SetLineColor(2);
  	
  	TH1F* hvZc = new TH1F("hvZc", "vertex(Z)", 180, -100, 260);
  	hvZc->SetXTitle("vertex(Z) [mm]");
  	hvZc->SetYTitle("count / 2 mm");
  	hvZc->SetLineColor(1);
  	TH1F* hvZ = new TH1F("hvZ", "vertex(Z)", 180, -100, 260);
  	hvZ->SetXTitle("vertex(Z) [mm]");
  	hvZ->SetYTitle("count / 2 mm");
  	TH1F* hvZcar = new TH1F("hvZcar", "vertex(Z)", 180, -100, 260);
  	hvZcar->SetLineColor(2);
  	
  	//******************************************************
  	gROOT->ProcessLine(".!date"); 
   /*cAna->cd(1);
   tree->Draw("vertex.fZ>>hvZc", common);
   gROOT->ProcessLine(".!date"); printf("Draw(vertex.fZ, common) ... done \n");
   tree->Draw("vertex.fZ>>hvZ",gate,"same");   
   gROOT->ProcessLine(".!date"); printf("Draw(vertex.fZ, gate) ... done \n");
   tree->Draw("vertex.fZ>>hvZcar",side,"same");   
   gROOT->ProcessLine(".!date"); printf("Draw(vertex.fZ, carbon) ... done \n");
   /*
   cAna->cd(2);
   tree->Draw("(p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()>>hOpenAng",gate);
   gROOT->ProcessLine(".!date"); printf("Draw(openAngle, gate) ... done \n");
   tree->Draw("(p2p_c.fRecoilL.Theta()+p2p_c.fRecoilR.Theta())*TMath::RadToDeg()>>hOpenAngCarbon",side, "same");
   gROOT->ProcessLine(".!date"); printf("Draw(openAngle, carbon) ... done \n");
   
	cAna->cd(6);
	TH1F* testOpenAng = new TH1F(*hOpenAng);
	testOpenAng->Add(hOpenAngCarbon, -1);
	testOpenAng->Draw();
   
   cAna->cd(5);
   //tree->Draw("TMath::Abs(p2p.fRecoilL.Phi()-p2p.fRecoilR.Phi())*TMath::RadToDeg()>>h1(60,140,200)",gate);
   //tree->Draw("TMath::Abs(p2p.fRecoilL.Phi()-p2p.fRecoilR.Phi())*TMath::RadToDeg()>>h2(60,140,200)",side, "same");
  
   /**/
   cAna->cd(1);
   tree->Draw("p2p.fEx>>hSp",gate);
   gROOT->ProcessLine(".!date"); printf("Draw.(Sp, gate) ... done \n");
   tree->Draw("p2p.fEx>>hSpCarbon",side, "same");
   gROOT->ProcessLine(".!date"); printf("Draw.(Sp, Carbon) ... done \n");

   printf("entries in hSp - hSpBG : %d, sqrt() = %.1f \n", hSp->Integral(1,SpHistBin)-factor*hSpCarbon->Integral(1,SpHistBin), 
                                                      sqrt(hSp->Integral(1,SpHistBin)-factor*hSpCarbon->Integral(1,SpHistBin)));
	
	hSpCarbon->Scale(factor);
	
	textStr.Form("carbon BG x %.2f", factor);
	text.DrawLatex(0.6, 0.8, textStr.Data());
	
	/*textStr.Form("vertexZ gate");
	text.DrawLatex(0.60, 0.7, textStr.Data());
	textStr.Form("crystal gate");
	text.DrawLatex(0.6, 0.67, textStr.Data());
	textStr.Form("OpenAng gate");
	text.DrawLatex(0.6, 0.64, textStr.Data());
	textStr.Form("nyoki Q gate");
	text.DrawLatex(0.6, 0.61, textStr.Data());
	textStr.Form("ToF(S0D-nyoki) gate");
	text.DrawLatex(0.6, 0.58, textStr.Data());*/
	

	cAna->cd(2);
	TH1F* testSp = new TH1F( *hSp);
	printf(" carbon X factor %f\n", factor);
	//testSp->Sumw2();
	testSp->Add(hSpCarbon, -1); //#8 = -1.1, #7 = -1.4
	testSp->Draw();
	
	//****************************************
  	//cAna->cd(2);
	
	if( numGauss == 1){
		total = new TF1("total", "gaus(0)", fitRange[0], fitRange[1]);
	}else	if( numGauss == 2){
		total = new TF1("total", "gaus(0) + gaus(3)", fitRange[0], fitRange[1]);
	}else if( numGauss == 3){	
		total = new TF1("total", "gaus(0) + gaus(3) + gaus(6)", fitRange[0], fitRange[1]);
	}else if( numGauss == 4){
	   total = new TF1("total", "gaus(0) + gaus(3) + gaus(6) + gaus(9)", fitRange[0], fitRange[1]);
	}else if( numGauss == 5){
	   total = new TF1("total", "gaus(0) + gaus(3) + gaus(6) + gaus(9) + gaus(12)", fitRange[0], fitRange[1]);
	}else if( numGauss == 6){
	   total = new TF1("total", "gaus(0) + gaus(3) + gaus(6) + gaus(9) + gaus(12) + gaus(15)", fitRange[0], fitRange[1]);
	}
	
	total->SetLineColor(1);
	total->SetLineWidth(2);
	/*
	if( numGauss >=1){
		total->SetParLimits(0,10,400);
		total->SetParLimits(1,fitRange[0],40);
		total->SetParLimits(2,1,20);
		
		//total->FixParameter(1,13.3);
		
		if(fixSigma != 3.0) total->FixParameter(2,fixSigma);
	}
	if(numGauss >= 2){
		total->SetParLimits(3,4,250);
		total->SetParLimits(4,fitRange[0],60);
		total->SetParLimits(5,1,15);
		
		//total->FixParameter(4,23.3);
		
		if(fixSigma != 3.0) total->FixParameter(5,fixSigma);
	}
	if(numGauss >= 3){
		total->SetParLimits(6,5,400);
		total->SetParLimits(7,25,fitRange[1]);
		total->SetParLimits(8,1,50);
		
		if(fixSigma  != 3.0) total->FixParameter(8,fixSigma);
	}
	if(numGauss >= 4){
		total->SetParLimits(9, 20,250);
		total->SetParLimits(10,30,fitRange[1]);
		total->SetParLimits(11,1,15);
		
		if(fixSigma != 3.0) total->FixParameter(11,fixSigma);
	}
	*/

	total->SetParameters(para);	
	
	//fixSigma = 4;
	if( fixSigma != 3.0){ 
	total->FixParameter(2,fixSigma);
	total->FixParameter(5,fixSigma);
	total->FixParameter(8,fixSigma);
	total->FixParameter(11,fixSigma);
	total->FixParameter(14,fixSigma);
	total->FixParameter(17,fixSigma);
	}

	printf("***********fit total %d Guassians\n", numGauss);  
	testSp->Fit(total,"R");
	total->GetParameters(para);
		
	//testSp->Fit(total,"RL");
	//total->GetParameters(para);
	
	//*************************************************
	TVirtualFitter * fitter = TVirtualFitter::GetFitter();
	assert(fitter !=0);
	double * covMatrix = fitter->GetCovarianceMatrix();
	
	TF1 * derv_par0 = new TF1("dfdp0",df_dPar, fitRange[0], fitRange[1], 1);
	TF1 * derv_par1 = new TF1("dfdp1",df_dPar, fitRange[0], fitRange[1], 1);
	TF1 * derv_par2 = new TF1("dfdp2",df_dPar, fitRange[0], fitRange[1], 1);
	double c[3];
	double *epar = total->GetParErrors();
	
	TF1 * k1 = new TF1("k1", "gaus", fitRange[0], fitRange[1]);
	TF1 * k2;
	TF1 * k3;
	TF1 * k4;
	TF1 * k5;
	TF1 * k6;
	
	k1->SetParameters(&para[0]);
	k1->SetLineColor(2);k1->SetLineWidth(1);k1->SetLineStyle(1);//k1->Draw("same");
	
	if(numGauss >= 2){
		k2 = new TF1("k2", "gaus", fitRange[0], fitRange[1]);
		k2->SetParameters(&para[3]);
		k2->SetLineColor(4);k2->SetLineWidth(1);k2->SetLineStyle(1);//k2->Draw("same");
	}
			
	if(numGauss >= 3){
		k3 = new TF1("k3", "gaus", fitRange[0], fitRange[1]);
		k3->SetParameters(&para[6]);	
		k3->SetLineColor(6);k3->SetLineWidth(1);k3->SetLineStyle(1);//k3->Draw("same");
	}
	if(numGauss >=4 ){
		k4 = new TF1("k4", "gaus", fitRange[0], fitRange[1]);
		k4->SetParameters(&para[9]);
		k4->SetLineColor(7);k4->SetLineWidth(1);k4->SetLineStyle(1);//k4->Draw("same");
	}
	if(numGauss >=5 ){
		k5 = new TF1("k5", "gaus", fitRange[0], fitRange[1]);
		k5->SetParameters(&para[12]);
		k5->SetLineColor(8);k5->SetLineWidth(1);k5->SetLineStyle(1);
	}
	if(numGauss >=6 ){
		k6 = new TF1("k6", "gaus", fitRange[0], fitRange[1]);
		k6->SetParameters(&para[15]);
		k6->SetLineColor(9);k6->SetLineWidth(1);k6->SetLineStyle(1);
	}

	//*********************************
	printf("reduced chi-square: %3.1f/%d = %3.1f\n", total->GetChisquare(), total->GetNDF(), total->GetChisquare()/total->GetNDF());
	/*
	textStr.Form("#chi^{2}/NDF: %3.3f", total->GetChisquare()/total->GetNDF());
	text.DrawLatex(0.15, 0.86, textStr.Data());

	derv_par0->SetParameter(0, 0);
	derv_par1->SetParameter(0, 1);
	derv_par2->SetParameter(0, 2);
	c[0] = derv_par0->Integral(para[1]-3*para[2],para[1]+3*para[2]);	
	c[1] = derv_par1->Integral(para[1]-3*para[2],para[1]+3*para[2]);
	c[2] = derv_par2->Integral(para[1]-3*para[2],para[1]+3*para[2]);
	double sigma_integral = IntegralError(3, c, epar, covMatrix);
	if( TMath::IsNaN(sigma_integral) ) { printf("no covMarix\n"); sigma_integral = IntegralError(3, c, epar); }
	printf("c[0]... %.2f, %.2f, %.2f , sigma:%.2f\n", c[0], c[1], c[2], sigma_integral);
	
	textStr.Form("mean: %3.1f#pm%3.1f", para[1], total->GetParError(1));
	text.DrawLatex(0.5, 0.8, textStr.Data());
	textStr.Form("#sigma: %3.1f#pm%3.1f", para[2], total->GetParError(2));
	text.DrawLatex(0.5, 0.77, textStr.Data());
	textStr.Form("count: %.0f(%.0f)", k1->Integral(para[1]-3*para[2],para[1]+3*para[2])/binWidth, sigma_integral/binWidth);
	text.DrawLatex(0.5, 0.74, textStr.Data());
	
	if( numGauss>=2){
		derv_par0->SetParameter(0, 3);
		derv_par1->SetParameter(0, 4);
		derv_par2->SetParameter(0, 5);
		c[0] = derv_par0->Integral(para[4]-3*para[5],para[4]+3*para[5]);	
		c[1] = derv_par1->Integral(para[4]-3*para[5],para[4]+3*para[5]);
		c[2] = derv_par2->Integral(para[4]-3*para[5],para[4]+3*para[5]);
		double sigma_integral = IntegralError(3, c, epar, covMatrix);
		if( TMath::IsNaN(sigma_integral) ) { printf("no covMarix\n");sigma_integral = IntegralError(3, c, epar);}
	
		textStr.Form("mean: %3.1f#pm%3.1f", para[4], total->GetParError(4));
		text.DrawLatex(0.5, 0.64, textStr.Data());
		textStr.Form("#sigma: %3.1f#pm%3.1f", para[5], total->GetParError(5));
		text.DrawLatex(0.5, 0.61, textStr.Data());
		textStr.Form("count: %.0f(%.0f)", k2->Integral(para[4]-3*para[5],para[4]+3*para[5])/binWidth, sigma_integral/binWidth);
		text.DrawLatex(0.5, 0.58, textStr.Data());
	}
	if( numGauss>=3){
		derv_par0->SetParameter(0, 6);
		derv_par1->SetParameter(0, 7);
		derv_par2->SetParameter(0, 8);
		c[0] = derv_par0->Integral(para[7]-3*para[8],para[7]+3*para[8]);	
		c[1] = derv_par1->Integral(para[7]-3*para[8],para[7]+3*para[8]);
		c[2] = derv_par2->Integral(para[7]-3*para[8],para[7]+3*para[8]);
		double sigma_integral = IntegralError(3, c, epar, covMatrix);
		if( TMath::IsNaN(sigma_integral) ) { printf("no covMarix\n");sigma_integral = IntegralError(3, c, epar);}

		textStr.Form("mean: %3.1f#pm%3.1f", para[7], total->GetParError(7));
		text.DrawLatex(0.5, 0.48, textStr.Data());
		textStr.Form("#sigma: %3.1f#pm%3.1f", para[8], total->GetParError(8));
		text.DrawLatex(0.5, 0.45, textStr.Data());	
		textStr.Form("count: %.0f(%.0f)", k3->Integral(para[7]-3*para[8],para[7]+3*para[8])/binWidth,sigma_integral/binWidth);
		text.DrawLatex(0.5, 0.42, textStr.Data());
	}
	if( numGauss>=4){
		derv_par0->SetParameter(0, 9);
		derv_par1->SetParameter(0, 10);
		derv_par2->SetParameter(0, 11);
		c[0] = derv_par0->Integral(para[10]-3*para[11],para[10]+3*para[11]);	
		c[1] = derv_par1->Integral(para[10]-3*para[11],para[10]+3*para[11]);
		c[2] = derv_par2->Integral(para[10]-3*para[11],para[10]+3*para[11]);
		double sigma_integral = IntegralError(3, c, epar, covMatrix);
		if( TMath::IsNaN(sigma_integral) ) { printf("no covMarix\n");sigma_integral = IntegralError(3, c, epar);}
		
		textStr.Form("mean: %3.1f#pm%3.1f", para[10], total->GetParError(10));
		text.DrawLatex(0.75, 0.80, textStr.Data());
		textStr.Form("#sigma: %3.1f#pm%3.1f", para[11], total->GetParError(11));
		text.DrawLatex(0.75, 0.77, textStr.Data());	
		textStr.Form("count: %.0f(%.0f)", k4->Integral(para[10]-3*para[11],para[10]+3*para[11])/binWidth,sigma_integral/binWidth);
		text.DrawLatex(0.75, 0.74, textStr.Data());
	}
	if( numGauss>=5){
		derv_par0->SetParameter(0, 12);
		derv_par1->SetParameter(0, 13);
		derv_par2->SetParameter(0, 14);
		c[0] = derv_par0->Integral(para[13]-3*para[14],para[13]+3*para[14]);	
		c[1] = derv_par1->Integral(para[13]-3*para[14],para[13]+3*para[14]);
		c[2] = derv_par2->Integral(para[13]-3*para[14],para[13]+3*para[14]);
		double sigma_integral = IntegralError(3, c, epar, covMatrix);
		if( TMath::IsNaN(sigma_integral) ) { printf("no covMarix\n");sigma_integral = IntegralError(3, c, epar);}
		
		textStr.Form("mean: %3.1f#pm%3.1f", para[13], total->GetParError(13));
		text.DrawLatex(0.75, 0.64, textStr.Data());
		textStr.Form("#sigma: %3.1f#pm%3.1f", para[14], total->GetParError(14));
		text.DrawLatex(0.75, 0.61, textStr.Data());	
		textStr.Form("count: %.0f(%.0f)", k5->Integral(para[13]-3*para[14],para[13]+3*para[14])/binWidth,sigma_integral/binWidth);
		text.DrawLatex(0.75, 0.58, textStr.Data());
	}
	if( numGauss>=6){
		derv_par0->SetParameter(0, 15);
		derv_par1->SetParameter(0, 16);
		derv_par2->SetParameter(0, 17);
		c[0] = derv_par0->Integral(para[16]-3*para[17],para[16]+3*para[17]);	
		c[1] = derv_par1->Integral(para[16]-3*para[17],para[16]+3*para[17]);
		c[2] = derv_par2->Integral(para[16]-3*para[17],para[16]+3*para[17]);
		double sigma_integral = IntegralError(3, c, epar, covMatrix);
		if( TMath::IsNaN(sigma_integral) ) { printf("no covMarix\n");sigma_integral = IntegralError(3, c, epar);}
		
		textStr.Form("mean: %3.1f#pm%3.1f", para[16], total->GetParError(16));
		text.DrawLatex(0.75, 0.48, textStr.Data());
		textStr.Form("#sigma: %3.1f#pm%3.1f", para[17], total->GetParError(17));
		text.DrawLatex(0.75, 0.45, textStr.Data());	
		textStr.Form("count: %.0f(%.0f)", k6->Integral(para[16]-3*para[17],para[16]+3*para[17])/binWidth,sigma_integral/binWidth);
		text.DrawLatex(0.75, 0.42, textStr.Data());
	}
	*/
	k1->Draw("same");
	if(numGauss >= 2) k2->Draw("same");
	if(numGauss >= 3) k3->Draw("same");
	if(numGauss >= 4) k4->Draw("same");
	if(numGauss >= 5) k5->Draw("same");
	if(numGauss >= 6) k6->Draw("same");
	
   
   //*********************************
   /*cAna->cd(3);
   
   TH2F* hMomtZSp = new TH2F("hMomtZSp", "Momentum.Z vs Sp",  SpHistBin, fitRange[0], fitRange[1], 100,-200, 200);
   TH2F* hMomtZSp2 = new TH2F("hMomtZSp2", "Momentum.Z vs Sp carbon",  SpHistBin, fitRange[0], fitRange[1], 100, -200, 200);
   
   tree->Draw("p2p.fResidual.Pz():p2p.fSp>>hMomtZSp", gate, "colz");
   tree->Draw("p2p.fResidual.Pz():p2p.fSp>>hMomtZSp2", side, "colz");
   
	TH2F* testMomtZSp = new TH2F( *hMomtZSp);
	testMomtZSp->Add(hMomtZSp2, (-1)*factor); //#8 = -1.1, #7 = -1.4
	testMomtZSp->Draw("colz");
   
   */
   /*
   cAna->cd(3);
   
   Int_t momtbin = 30;
   Int_t momtRange[2] = {0, 300};
   Double_t momtbinWidth = (momtRange[1]-momtRange[0])/momtbin;
   TString YTitleStr;
   YTitleStr.Form("count / %.1f MeV/c", momtbinWidth);
   
   Double_t SpCutRange[2] = {-2, 2};
   TString SpCutStr1, SpCutStr2; 
   SpCutStr1.Form("TMath::Abs(p2p.fEx-%.1f)<%.1f", SpCutRange[0] , SpCutRange[1]);
   
   TCut SpCut1, SpCut2;
   SpCut1 = SpCutStr1;
   SpCutStr2.Form("TMath::Abs(p2p.fEx-%.1f)<%.1f", SpCutRange[0] , SpCutRange[1]);
   SpCut2 = SpCutStr2;
   
   TCut ana1 = gate + SpCut1;
   TCut ana2 = side + SpCut2;
   
   TString hMomtStr;
   hMomtStr.Form("Momt.Dis, |Ex-%.1f|<%.1f", SpCutRange[0] , SpCutRange[1]);
   
   TH1F* hMomt = new TH1F("hMomt", hMomtStr, momtbin,momtRange[0], momtRange[1]);
   TH1F* hMomt2 = new TH1F("hMomt2", "Momentum ", momtbin, momtRange[0], momtRange[1]);
   hMomt->SetXTitle("k [MeV/c]");
   hMomt->SetYTitle(YTitleStr);
   hMomt2->SetLineColor(2);
   
   tree->Draw("p2p.fResidual.P()>>hMomt", ana1, "");
   tree->Draw("p2p.fResidual.P()>>hMomt2", ana2, "same"); 
   hMomt2->Scale(factor);
   hMomt2->Draw("same");
   
   cAna->cd(4);
	TH1F* testMomt = new TH1F( *hMomt);
	//testMomt->Sumw2();
	testMomt->Add(hMomt2, -1); //#8 = -1.1, #7 = -1.4
	testMomt->Draw("same");
   testMomt->Fit("gaus");
   
   //***********************
   cAna->cd(7);
   
   Double_t SpCutRange[2] = {15.8, 4};
   SpCutStr1.Form("TMath::Abs(p2p.fEx-%.1f)<%.1f", SpCutRange[0] , SpCutRange[1]);
   SpCut1 = SpCutStr1;
   SpCutStr2.Form("TMath::Abs(p2p.fEx-%.1f)<%.1f", SpCutRange[0] , SpCutRange[1]);
   SpCut2 = SpCutStr2;
   
   ana1 = gate + SpCut1;
   ana2 = side + SpCut2;
   
   hMomtStr.Form("Momt.Dis, |Ex-%.1f|<%.1f", SpCutRange[0] , SpCutRange[1]);
   
   TH1F* hMomta = new TH1F("hMomta", hMomtStr, momtbin,momtRange[0], momtRange[1]);
   TH1F* hMomta2 = new TH1F("hMomta2", "Momentum ", momtbin, momtRange[0], momtRange[1]);
   hMomta->SetXTitle("k [MeV/c]");
   hMomta->SetXTitle(YTitleStr);
   hMomta2->SetLineColor(2);
   
   tree->Draw("p2p.fResidual.P()>>hMomta", ana1, "");
   tree->Draw("p2p.fResidual.P()>>hMomta2", ana2, "same");
   hMomta2->Scale(factor);
   hMomta2->Draw("same");
   
   cAna->cd(8);
	TH1F* testMomta = new TH1F( *hMomta);
	//testMomta->Sumw2();
	testMomta->Add(hMomta2, -1); //#8 = -1.1, #7 = -1.4
	testMomta->Draw("same");
	testMomta->Fit("gaus");
	
	cAna->cd(5);
	testMomta->Draw();
	testMomt->Draw("same");
	
   
   /*
   Double_t SpGateRange[2] = {29, 5.};
   
   TString SpGateStr1,SpGateStr2;
   TCut SpGate1, SpGate2;
   
   SpGateStr1.Form("TMath::Abs(p2p.fSp-%.1f)<%.1f", SpGateRange[0] , SpGateRange[1]);
   SpGate1 = SpGateStr1;
   SpGate1.Print();
   
   SpGateStr2.Form("TMath::Abs(p2p_c.fSp-%.1f)<%.1f", SpGateRange[0] , SpGateRange[1]);
   SpGate2 = SpGateStr2;
   SpGate2.Print();
   
   TCut ana1 = gate + SpGate1;   
   TCut ana2 = side + SpGate2;
   
   TString hMomtStr;
   hMomtStr.Form("Momentum Distribution, |Sp-%.1f|<%.1f", SpGateRange[0] , SpGateRange[1]);
   TH1F* hMomt1 = new TH1F("hMomt1", hMomtStr, 100, 0, 300);
   hMomt1->SetXTitle("k [MeV/c]");
   hMomt1->SetYTitle("count / 3 MeV/c");
   
   TH1F* hMomt2 = new TH1F("hMomt2", "Momentum Distribution", 100, 0, 300);
	hMomt2->SetLineColor(2);
   
//   tree->Draw("TMath::Power(TMath::Power(0.84746*(938.272+p2p.fIncident.E()-p2p.fRecoilL.E()-p2p.fRecoilR.E())-1.310797*(p2p.fResidual.Pz()),2)+TMath::Power(p2p.fResidual.Px(),2)+TMath::Power(p2p.fResidual.Py(),2),0.5)>>hkP1", anaP1);
//   tree->Draw("TMath::Power(TMath::Power(0.84746*(938.272+p2p.fIncident.E()-p2p.fRecoilL.E()-p2p.fRecoilR.E())-1.310797*(p2p.fResidual.Pz()),2)+TMath::Power(p2p.fResidual.Px(),2)+TMath::Power(p2p.fResidual.Py(),2),0.5)>>hkD5", anaD5,"same");
   
   tree->Draw("TMath::Power(TMath::Power(0.84746*(p2p.fResidual.E())-1.310797*(p2p.fResidual.Pz()),2)+TMath::Power(p2p.fResidual.Px(),2)+TMath::Power(p2p.fResidual.Py(),2),0.5)>>hMomt1", ana1);
   tree->Draw("TMath::Power(TMath::Power(0.84746*(p2p_c.fResidual.E())-1.310797*(p2p_c.fResidual.Pz()),2)+TMath::Power(p2p_c.fResidual.Px(),2)+TMath::Power(p2p_c.fResidual.Py(),2),0.5)>>hMomt2", ana2, "same");
   
	cAna->cd(3);
	TH1F* testMomt = new TH1F( *hMomt1);
	testMomt->Add(hMomt2, -1.4); //#8 = -1.1, #7 = -1.4
	testMomt->Draw();
/*
	*/
	
   
}  

//__________________________________________________________________
/*
double fitFunction(double * x, double * p) {
	
	return 

}*/

//____________________________________________________________________
double df_dPar(double * x, double * p) { 
   // derivative of the function w.r..t parameters
   // use calculated derivatives from TF1::GradientPar

   double grad[NPAR]; 
   // p is used to specify for which parameter the derivative is computed 
   int ipar = int(p[0] ); 
   //printf("p[0] : %f, ipar: %d \n",p[0], ipar);
   assert (ipar >=0 && ipar < NPAR );

   assert(total);
   total->GradientPar(x, grad);

   return grad[ipar]; 
}

//____________________________________________________________________
double IntegralError(int npar, double * c, double * errPar, 
   double * covMatrix = 0) {   
// calculate the error on the integral given the parameter error and 
// the integrals of the gradient functions c[] 

   double err2 = 0; 
   for (int i = 0; i < npar; ++i) { 
      if (covMatrix == 0) { // assume error are uncorrelated
         err2 += c[i] * c[i] * errPar[i] * errPar[i]; 
      } else {
         double s = 0; 
         for (int j = 0; j < npar; ++j) {
            s += covMatrix[i*npar + j] * c[j]; 
         }
         err2 += c[i] * s; 
      }
   }

   return TMath::Sqrt(err2);
}


