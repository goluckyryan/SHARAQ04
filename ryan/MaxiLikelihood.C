void MaxiLikelihood(TH1F* h2, TH1F* h1) {
   
   // find the likelihood of h2 from h1, h1 is the model
   
   Int_t nBin = h2->GetNbinsX();
   if( h1->GetNbinsX() != nBin ) return 0;

   Double_t Max = 0;
   Double_t dMax = 0;
   Double_t Sum = 0;
   for( Int_t i = 1; i <= nBin; i++){
            Sum += h1->GetBinContent(i);
   }
   for( Int_t i = 1; i <= nBin; i++){
            Double_t xi  = h1->GetBinContent(i);
            Double_t yi  = h2->GetBinContent(i);
            Double_t dyi = h2->GetBinError(i);

            //printf("%3d, xi:%10f, yi:%10f, xi/Sum:%10.9f, %10f\n", i, xi, yi, xi/Sum, yi*TMath::Log(xi/Sum));
            Max += yi*TMath::Log(xi/Sum);
            dMax += TMath::Power(dyi*TMath::Log(xi/Sum),2); 
   }
   dMax = TMath::Sqrt(dMax);
   printf("Sum:%10.2f, Maximum Likelihood :%10.2f(%10.2f) = (%10.2f, %10.2f)\n", Sum, Max, dMax, Max-dMax, Max+dMax);
   
   return ;
}
