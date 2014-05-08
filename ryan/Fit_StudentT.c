void Fit_StudentT(){

   gStyle->SetOptFit(1111);
   Int_t nPara = 4;
   Double_t Xrange[2] = {-2,2};
   TF1 *fit = new TF1("fit", StudentT, Xrange[0], Xrange[1], nPara); 
   fit->SetParameters(3,2000, 0., 1.); 
   fit->FixParameter(0,3);
   htemp->Fit("fit");
}

Double_t StudentT(Double_t *x, Double_t *para){
   // DF, magnitude, offset, sigma 
   Int_t DF = para[0];
   Double_t arg;
   if (para[3]) arg = (x[0]-para[2])/para[3];
   
   return para[1]*TMath::Student(arg, DF);
}
