void Fit_Chi(){
   gStyle->SetOptFit(1111);
   Int_t nPara = 3;
   Double_t Xrange[2] = {0, 5};
   TF1 *fit = new TF1("fit", Chi_dist, Xrange[0], Xrange[1], nPara); 
   fit->SetParameters(3 ,20000, 1);
   fit->FixParamter(0,3);
   hsigmaX->Fit("fit");
}

void Chi_dist(Double_t *x, Double_t *para){
   // DF, magnitude , sigma
   Int_t DF = para[0];
   Double_t arg;
   if(para[2]) arg = x[0]/para[2];
   
   return para[1]* (TMath::Power(2,1-DF/2) * TMath::Power(arg, DF-1) * TMath::Exp(-arg*arg/2) )/ (para[2]  * TMath::Gamma(DF/2));
}
