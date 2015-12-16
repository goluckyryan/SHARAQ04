void MaxiLikelihood(TH1F* h1, TH1F* h2) {
   
   Int_t nBin = h1->GetNbinsX();
   if( h2->GetNbinsX() != nBin ) return 0;

   Double_t Max = 0;
   Double_t dMax = 0;
   Double_t Sum = 0;
   for( Int_t i = 1; i <= 20; i++){
            Sum += h1->GetBinContent(i);
   }
   for( Int_t i = 1; i <= 20; i++){
            Double_t xi = h1->GetBinContent(i);
            Double_t yi = h2->GetBinContent(i);
            Double_t dyi = h2->GetBinError(i);
         //   printf("%3d, xi:%10f, yi:%10f, %10f\n", i, xi, yi, yi*TMath::Log(xi/Sum));
            Max += yi*TMath::Log(xi/Sum);
            dMax += TMath::Power(dyi*TMath::Log(xi/Sum),2); 
   }
   dMax = TMath::Sqrt(dMax);
   printf("Sum:%10.2f, Maximum Likelihood :%10.2f(%10.2f) = (%10.2f, %10.2f)\n", Sum, Max, dMax, Max-dMax, Max+dMax);
   
   return ;
}
