void Fit_Binomial(const TH1F* htemp){
   gStyle->SetOptFit(1111);
   Int_t nPara = 2;
   Double_t Xrange[2] = {1,6};
   TF1 *fit = new TF1("fit", Binomial_dist, Xrange[0], Xrange[1], nPara); 
   fit->SetParameters(200000, 0.94);
   htemp->Fit("fit","Q");
   
}

Double_t Binomial_dist(Double_t *x, Double_t *para){
   Int_t N = 6;
   Int_t arg;
   if( para[1]) arg = TMath::Floor(x[0]); 
   return para[0]* TMath::Binomial(N,arg) * TMath::Power(para[1],arg) * TMath::Power((1-para[1]), N-arg);
}
