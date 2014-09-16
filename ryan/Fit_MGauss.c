void Fit_MGauss(TH1D* hFit){
	Double_t para[7*3];
	
	TF1 * g1 = new TF1("g1", "gaus", 14100, 14400);
	TF1 * g2 = new TF1("g2", "gaus", 14400, 14700);
	TF1 * g3 = new TF1("g3", "gaus", 14700, 15000);
//	TF1 * g4 = new TF1("g4", "gaus", 15000, 15250);
//	TF1 * g5 = new TF1("g5", "gaus", 15250, 15400); 
//	TF1 * g6 = new TF1("g6", "gaus", 15400, 15700);
	//TF1 * g7 = new TF1("g7", "gaus", 2400, 2700);

	TF1 * total = new TF1("total", "gaus(0)+gaus(3)+gaus(6)", 14100, 15700);
	total->SetLineColor(2);
	//total->SetParLimits(14,0,140);
	//total->SetParLimits(17,0,140);

	g1->Fixparameter(1,-2);
	g2->Fixparameter(1,13.26);
	g3->Fixparameter(1,23.8);
	
	hFit->Fit(g1, "R0");
	hFit->Fit(g2, "R0+");
	hFit->Fit(g3, "R0+");
//	hFit->Fit(g4, "R0+");
//	hFit->Fit(g5, "R0+");
//	hFit->Fit(g6, "R0+");
//	hFit->Fit(g7, "R0+");
	
	g1->GetParameters(&para[0]);
	g2->GetParameters(&para[3]);
	g3->GetParameters(&para[6]);
//	g4->GetParameters(&para[9]);
//	g5->GetParameters(&para[12]);
//	g6->GetParameters(&para[15]);
//	g7->GetParameters(&para[18]);

	total->SetParameters(para);
	
	hFit->Fit(total,"R+");


	TF1 * k1 = new TF1("k1", "gaus", 14000, 16500);
	TF1 * k2 = new TF1("k2", "gaus", 14000, 16500);
	TF1 * k3 = new TF1("k3", "gaus", 14000, 16500);
//	TF1 * k4 = new TF1("k4", "gaus", 14000, 16500);
//	TF1 * k5 = new TF1("k5", "gaus", 14000, 16500);
//	TF1 * k6 = new TF1("k6", "gaus", 14000, 16500);
	//TF1 * k7 = new TF1("k7", "gaus", 14000, 16500);
	
	total->GetParameters(para);
	
	k1->SetParameters(&para[0]);
	k2->SetParameters(&para[3]);
	k3->SetParameters(&para[6]);
	k4->SetParameters(&para[9]);
	k5->SetParameters(&para[12]);
	k6->SetParameters(&para[15]);
	//k7->SetParameters(&para[18]);
	
	k1->SetLineColor(1);k1->Draw("same");
	k2->SetLineColor(2);k2->Draw("same");
	k3->SetLineColor(3);k3->Draw("same");
	k4->SetLineColor(4);k4->Draw("same");
	k5->SetLineColor(5);k5->Draw("same");
	k6->SetLineColor(6);k6->Draw("same");
	//k1->SetLineColor(7);k7->Draw("same");

}


/*
	Double_t minX[M], maxX[M]; 
   gStyle->SetOptFit(1111);
   const Int_t nPara = 3*M;
   Double_t para[nPara]; 
   TF1 **fit = new TF1[M];
   
   TString TotalFit;
   for ( Int_t i = 0; i < M; i++){
   	TString fitName;
   	fitName.Form("fit[%d]",i);
   	TF1 *fit[i] = new TF1(fitName, "gaus",  minX[i], maxX[i]);
   	fit->SetParameter(0, mag[i]);
   	fit->SetParameter(1, x[i]);
   	fit->SetParameter(2, sigma[i]);
   	fit->SetParLimits(0, 5000);
   	fit->SetParLimits(1, 0,3000);
   	fit->SetParLimits(2, 0,1000);
	   //fit->FixParameter(1,0);
   	//fit->FixParameter(4,0);
   	hFit->Fit(fitname, "R+");
   	TString TotalFitName;
   	TotalFitName.Form("gaus(%d)",i);
   	TotalFit += TotalFitName;
   } 
   
   TF1 * total = new TF1("total", TotalFit, minX[0], maxX[M-1]);
   hFit->Fit(total, "R+");
   
 /*  //Get para
   Double_t para[nPara];
   fit->GetParameters(para);
   
   //seperate function
  /* TF1 **GaussFit = new TF1[M];
   for ( Int_t i = 0; i < M; i++){
   	TString funcName;
   	funcName.Form("GaussFit[%d]",i);
   	TF1 *GaussFit[i] = new TH1F(funcName, Gauss, minX, maxX, 3);
   	GaussFit[i]->SetLineColor(i);
   	Double_t paraM[3] = {para[i], para[i+1], para[i+2]};
   	GaussFit[i]->SetParameters(paraM);
   	GaussFit[i]->Draw("same");	
		
	   printf("== Gauss[%d]:%d \n",GaussFit[i]->Integral(paraM[1]-3*paraM[2],paraM[1]+3*paraM[2]));
      	
   }
   
}*/
