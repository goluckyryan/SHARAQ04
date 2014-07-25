void Fit_2Gauss(TH1F* hFit, Double_t minX, Double_t maxX, Double_t mag1, Double_t x1, Double_t sigma1, Double_t mag2, Double_t x2, Double_t sigma2){
   gStyle->SetOptFit(1111);
   const Int_t nPara = 6;
   TF1 *fit = new TF1("fit", fitFunction,  minX, maxX, nPara); 
   fit->SetParameters(mag1,  x1, sigma1,
                      mag2,  x2, sigma2);
   fit->SetParLimits(1, -5,5); // x1
   fit->SetParLimits(2, 0,10);   // sigma1
   fit->SetParLimits(4, -15,0); // x2
   fit->SetParLimits(5, 0,10);   // sigma2
   //fit->FixParameter(1,0);
   //fit->FixParameter(4,0);
   hFit->Fit("fit");
   //Get para
   Double_t para[nPara];
   fit->GetParameters(para);
   
   //seperate function
   TF1 *Gauss1 = new TF1("Gauss1", Gauss, minX, maxX, 3);
   Gauss1->SetLineColor(kBlue);
   TF1 *Gauss2 = new TF1("Gauss2", Gauss, minX, maxX, 3);
   Gauss2->SetLineColor(7);
   
   Gauss1->SetParameters(para);
   Gauss1->Draw("same");
   Double_t para2[3]={para[3],para[4],para[5]}; 
   Gauss2->SetParameters(para2);
   Gauss2->Draw("same");
   
   printf("========= Count: Gauss1(%d), Gauss2(%d) \n",Gauss1->Integral(para[1]-3*para[2],para[1]+3*para[2]), Gauss2->Integral(para[4]-3*para[5],para[4]+3*para[5]));
   
}

Double_t fitFunction(Double_t *x, Double_t *para){
   const Int_t nParaGauss = 3;
   const Double_t para2[3] = {para[nParaGauss],para[nParaGauss+1], para[nParaGauss+2]};
   return Gauss(x,para) + Gauss(x,para2);
}

Double_t Gauss(Double_t *x, Double_t *para){
   // magnitude, offset, sigma
   Double_t arg;
   if(para[2]) arg = (x[0] - para[1])/para[2];
   
   return para[0]*TMath::Gaus(arg,0,1,0);
}
