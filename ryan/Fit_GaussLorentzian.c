void Fit_GaussLorentzian(){
   gStyle->SetOptFit(1111);
   const Int_t nPara = 6;
   Double_t Xrange[2] = {-2,2};
   TF1 *fit = new TF1("fit", fitFunction, Xrange[0], Xrange[1], nPara); 
   fit->SetParameters(14000, 0., 0.2, 1000, 0, 0.5);
   //fit->SetParLimits(0,800,3000);
   fit->FixParameter(1,0);
   fit->FixParameter(4,0);
   hq->Fit("fit");
   //Get para
   Double_t para[nPara];
   fit->GetParameters(para);
   
   //seperate function
   TF1 *Gauss = new TF1("Gauss", Gauss, Xrange[0], Xrange[1], 3);
   Gauss->SetLineColor(kBlue);
   TF1 *Lorentzian = new TF1("Lorentzian", Lorentzian, Xrange[0], Xrange[1], 3);
   Lorentzian->SetLineColor(kGreen);
   
   Gauss->SetParameters(para);
   Gauss->Draw("same");
   Lorentzian->SetParameters(&para[3]);
   Lorentzian->Draw("same");
}

Double_t fitFunction(Double_t *x, Double_t *para){
   const Int_t nParaGuass = 3;
   const Int_t nParaLorent = 3;
   return Gauss(x,para) + Lorentzian(x,&para[nParaGuass]);
}

Double_t Lorentzian(Double_t *x, Double_t *para){
   // magnitude, offset, FUll-width 
   Double_t arg;
   if (para[2]) arg = (x[0]-para[1])/para[2];
   
   return para[0] / (1 + arg*arg);
}

Double_t Gauss(Double_t *x, Double_t *para){
   // magnitude, offset, sigma
   Double_t arg;
   if(para[2]) arg = (x[0] - para[1])/para[2];
   
   return para[0]*TMath::Gaus(arg,0,1,0);
}
