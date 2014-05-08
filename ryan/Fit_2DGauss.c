void Fit_2DGauss(){
   gStyle->SetOptFit(1111);
   const Int_t nPara = 5;
   Double_t Xrange[2] = {-30.,30.};
   Double_t Yrange[2] = {-30.,30.};

   TF2 *fit = new TF2("fit", Gauss2D, Xrange[0], Xrange[1], Yrange[0], Yrange[1], nPara); 
   fit->SetParameters(100,  0., 5.,  0., 5.);
   fit->SetParLimits(1, -10,10);
   fit->SetParLimits(2, 0,10);
   fit->SetParLimits(3, -10,10);
   fit->SetParLimits(4, 0,10);
   //fit->FixParameter(1,0);
   //fit->FixParameter(4,0);
   h1->Fit("fit");

   //Get para
   //Double_t para[nPara];
   //fit->GetParameters(para);
   
   //Draw function
   fit->Draw("cont1 same");
}

Double_t Gauss2D(Double_t *x, Double_t *para){
   // magnitude, offset_X, sigma_X, offset_Y, sigma_Y
  Double_t arg1, arg2;
  if(para[4]) {
    arg1 = (x[0] - para[1])/para[2];
    arg2 = (x[1] - para[3])/para[4];
  }
   
  return para[0]*TMath::Exp(-0.5*(arg1*arg1+arg2*arg2));
}
