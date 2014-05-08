void Fit_Chisq(){
   Int_t nPara = 3;
   Double_t Xrange[2] = {0,2};
   TF1 *fit = new TF1("fit", ChiSq_dist, Xrange[0], Xrange[1], nPara); 
   fit->SetParameters(2,6000, 1);
   fit->FixParameter(0,2);
   h1->Fit("fit");
}

void ChiSq_dist(Double_t *x, Double_t *para){
   //DF, magnitude, sigma^2
   Int_t DF = para[0];
   Double_t arg;
   if(para[2]) arg = x[0]/para[2];
   
   return para[1]* (TMath::Power(arg, DF/2-1) * TMath::Exp(-arg) )/ (para[2] *TMath::Power(2,DF) * TMath::Gamma(DF/2));
}
