const Int_t nOrder = 2; // order of polynomial

void Fit_ppSumTheta(){
   gStyle->SetOptFit(1111);
   const Int_t nParaSumTheta = 3;
   const Int_t nPara = nParaSumTheta + 1 + nOrder+1; //6
   Double_t Xrange[2] = {80,92};
   Int_t Npx = 100;
   TF1 *fit = new TF1("fit", fitFunction, Xrange[0], Xrange[1], nPara); 
   fit->SetNpx(Npx);
   fit->SetParameters(2000, 0.4,  260, -0.2,  -55000, 1200, -7);
   fit->SetParLimits(0,10,10000);
   fit->SetParLimits(1,0.15,1);
   //fit->SetParLimits(3,-0.5,0.5);
   fit->FixParameter(2,260);
   fit->SetParLimits(3,-2,0.1);
   //fit->FixParameter(3,0);
   
   h2->Fit("fit");
   
   //get parameter
   Double_t pa[nPara];
   fit->GetParameters(pa);
   
   TF1 *gfit = new TF1("gfit", GausConSumTheta,Xrange[0], Xrange[1], nParaSumTheta);
   gfit->SetNpx(Npx);
   gfit->SetLineColor(4);
   gfit->SetParameters(pa);
   gfit->Draw("same");
   TF1 *gPoly = new TF1("gPloy", Poly,Xrange[0], Xrange[1], nOrder+1);
   gPoly->SetNpx(Npx);
   gPoly->SetLineColor(1);
   gPoly->SetParameters(&pa[nParaSumTheta+1]);
   gPoly->Draw("same");
}

Double_t fitFunction(const Double_t *x, const Double_t *para){
  //const Int_t nParaPloy = nOrder +1;
  //para[3] = shift of x;
  
  Double_t arg[1];
  arg[0] = x[0] +para[3];
  return GausConSumTheta(arg,para) + Poly(arg,&para[4]);
  
}

Double_t Poly(const Double_t *x, const Double_t *para){
   
   Double_t val = 0;
   
   for ( Int_t i = 0; i <= nOrder; i++){
      val += para[i]*TMath::Power(x[0],i);
   }
  
   return val;
}

Double_t Gauss(const Double_t *x, const Double_t *para){
   // magnitude, mean, sigma
   return para[0]*TMath::Gaus(x[0], para[1],para[2],0);
}

Double_t GausConSumTheta(Double_t *x, Double_t *para){
  //para[0] = Gaussian magnitude
  //para[1] = Gaussian sigma
  //Para[2] = KE
  Double_t np = 500.0;  // number of Convolution step
  Double_t sc = 5.0;    // convolution extends to +-sc Gaussuan sigma
  
  Double_t xx;

  const Double_t xlow  = x[0] - sc*para[1];
  const Double_t xhigh = x[0] + sc*para[1];
  const Double_t step = (xhigh-xlow)/np;

  Double_t sum = 0;
  for(Int_t i = 0; i <np; i++){
    xx = xlow + i*step;
    sum += SumTheta(&xx,&para[2])* TMath::Gaus(xx,x[0],para[1],0)*step;    
    
  }

  return para[0]*sum ;
}

Double_t SumTheta(Double_t*x , Double_t *para){
  //para[0] = KE
  //para[1] = CM theta limit // hard parameter
  const Double_t mp = 938.272;
  Double_t a  = para[0]/mp/2;
  Double_t temp0 = 4*(1+a)/a/a;
  Double_t arg   = x[0]*TMath::DegToRad(); // input x[0] is deg, arg is rad
  Double_t temp1 = TMath::Power(TMath::Sin(arg),2);
  Double_t temp2 = TMath::Power(TMath::Tan(arg),2);
  Double_t limit = TMath::ATan(TMath::Sqrt(temp0)/TMath::Sin(34*TMath::DegToRad()));

  //printf(" KE:%10.4f, a:%10.4f, Theta_min:%10.4f deg\n",para[0], a, TMath::ATan(TMath::Sqrt(temp0))*TMath::RadToDeg() );
  //printf(" x[0]:%10.4f\n", x[0]);

  if ( temp2 > temp0 && arg<=limit && arg>=0){
    if ( temp2 <= temp0 +1) {
      return 1/temp1;
    }
      return 1/temp1/TMath::Sqrt(temp2-temp0);
  }else{
    return 0;
  }
  
}
