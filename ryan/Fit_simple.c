void Fit(){
   Int_t nPara = 3;
   Double_t Xrange[2] = {-2,2};
   TF1 *fit = new TF1("fit", user_func, Xrange[0], Xrange[1], nPara); 
   fit->SetParameters(30000, 0, 0.27);
   h2->Fit("fit");
}

void user_func(Double_t *x, Double_t *para){
   Double_t arg = 0;
   if(para[2]) arg = (x[0]-para[1])/para[2];
   
   return para[0]*TMath::Exp(-0.5*arg*arg);
}
