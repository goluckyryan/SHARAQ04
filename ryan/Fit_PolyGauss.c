const Int_t nOrder = 2; // order of polynomial

void Fit_PolyGauss(){
   gStyle->SetOptFit(1111);
   const Int_t nParaGauss = 3;
   const Int_t nPara = nParaGauss+nOrder+1;
   Double_t Xrange[2] = {80,90};
   
   
   TF1 *fit = new TF1("fit", fitFunction, Xrange[0], Xrange[1], nPara); 
   fit->SetParameters(400, 86., 0.2, 1000, 0);
   fit->SetParLimits(1,84,88);
   //fit->FixParameter(1,0);
   h1->Fit("fit");
   //Get para
   Double_t para[nPara];
   fit->GetParameters(para);
   
   //seperate function
   TF1 *Gauss = new TF1("Gauss", Gauss, Xrange[0], Xrange[1], 3);
   Gauss->SetLineColor(kBlue);
   TF1 *Poly = new TF1("Poly", Poly, Xrange[0], Xrange[1], nOrder+1);
   Poly->SetLineColor(kGreen);
   
   Gauss->SetParameters(para);
   Gauss->Draw("same");
   Poly->SetParameters(&para[nParaGauss]);
   Poly->Draw("same");
}

Double_t fitFunction(Double_t *x, Double_t *para){
   const Int_t nParaGuass = 3;
   const Int_t nParaPoly = nOrder+1;
   return Gauss(x,para) + Poly(x,&para[nParaGuass]);
}

Double_t Poly(Double_t *x, Double_t *para){
   
   Double_t val = 0;
   
   for ( Int_t i = 0; i <= nOrder; i++){
      val += para[i]*TMath::Power(x[0],i);
   }
  
   return val;
}

Double_t Gauss(Double_t *x, Double_t *para){
   // magnitude, offset, sigma
   Double_t arg;
   if(para[2]) arg = (x[0] - para[1])/para[2];
   
   return para[0]*TMath::Gaus(arg,0,1,0);
}
