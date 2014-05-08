void Fit_Lorentzian(){

   gStyle->SetOptFit(1111);
   Int_t nPara = 3;
   Double_t Xrange[2] = {-2,2};
   TF1 *fit = new TF1("fit", Lorentzian, Xrange[0], Xrange[1], nPara); 
   fit->SetParameters(2000, 0., 1.); 
   //fit->FixParameter(1,0);
   htemp->Fit("fit");
}

Double_t Lorentzian(Double_t *x, Double_t *para){
   // magnitude, offset, FUll-width 
   Double_t arg;
   if (para[2]) arg = (x[0]-para[1])/para[2];
   
   return para[0] / (1 + arg*arg);
}
