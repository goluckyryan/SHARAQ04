void Fit_two2DGauss(){
   gStyle->SetOptFit(1111);
   const Int_t nPara = 10;
   Double_t Xrange[2] = {-100.,100.};
   Double_t Yrange[2] = {-100.,100.};

   TF2 *fit = new TF2("fit", fitFunction, Xrange[0], Xrange[1], Yrange[0], Yrange[1], nPara); 
   fit->SetParameters(1400,  0., 20.,  0., 20.,
                      1400, 50., 20., 50., 20.);
   fit->SetParLimits(2, 0,50);
   fit->SetParLimits(4, 0,50);
   fit->SetParLimits(7, 0,50);
   fit->SetParLimits(9, 0,50);
   //fit->FixParameter(1,0);
   //fit->FixParameter(4,0);
   h1->Fit("fit");

   //Get para
   //Double_t para[nPara];
   //fit->GetParameters(para);
   
   //Draw function
   fit->Draw("cont1 same");
}

Double_t fitFunction(Double_t *x, Double_t *para){
  //const Int_t nPeak = 2;
  const Int_t nPara = 5;
  Double_t *p1 = &para[0];
  Double_t *p2 = &para[nPara];
  
  return Gauss2D(x,p1)+Gauss2D(x,p2);
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
