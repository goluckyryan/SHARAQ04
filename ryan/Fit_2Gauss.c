void Fit_2Gauss(){
   gStyle->SetOptFit(1111);
   const Int_t nPara = 5;
   Double_t Xrange[2] = {-50,150};
   TF1 *fit = new TF1("fit", fitFunction, Xrange[0], Xrange[1], nPara); 
   fit->SetParameters(500,  20., 20,
                      400, 100.);
   fit->SetParLimits(1, -50,50);
   fit->SetParLimits(2, 0,50);
   fit->SetParLimits(4, 80,110);
   //fit->FixParameter(1,0);
   //fit->FixParameter(4,0);
   h1->Fit("fit");
   //Get para
   Double_t para[nPara];
   fit->GetParameters(para);
   
   //seperate function
   TF1 *Gauss1 = new TF1("Gauss1", Gauss, Xrange[0], Xrange[1], 3);
   Gauss1->SetLineColor(kBlue);
   TF1 *Gauss2 = new TF1("Gauss2", Gauss, Xrange[0], Xrange[1], 3);
   Gauss2->SetLineColor(kGreen);
   
   Gauss1->SetParameters(para);
   Gauss1->Draw("same");
   Double_t para2[3]={para[3],para[4],para[1]}; 
   Gauss2->SetParameters(para2);
   Gauss2->Draw("same");
}

Double_t fitFunction(Double_t *x, Double_t *para){
   const Int_t nParaGauss = 3;
   const Double_t para2[3] = {para[nParaGauss],para[nParaGauss+1], para[1]};
   return Gauss(x,para) + Gauss(x,para2);
}

Double_t Gauss(Double_t *x, Double_t *para){
   // magnitude, offset, sigma
   Double_t arg;
   if(para[2]) arg = (x[0] - para[1])/para[2];
   
   return para[0]*TMath::Gaus(arg,0,1,0);
}
