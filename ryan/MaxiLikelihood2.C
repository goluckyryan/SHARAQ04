void MaxiLikelihood2(TH1F* h1, TH1F* h2, TH1F* h3) {
   
   // find the ratio of h2 an h3 in h1
   
   Int_t nBin = h1->GetNbinsX();
   if( h2->GetNbinsX() != nBin ) return 0;
   if( h3->GetNbinsX() != nBin ) return 0;

   TH1F* htemp = new TH1F("htemp", "htemp", nBin, 0, 400);
   
   for(float a = 0; a < 1.05; a+=0.05){

      Double_t Max = 0;
      Double_t dMax = 0;
      Double_t Sum = 0;
      htemp->Clear();
      htemp->Add(h1, h2, a, 1-a);
      for( Int_t i = 1; i <= nBin; i++){
         Sum += htemp->GetBinContent(i);
      }
      for( Int_t i = 1; i <= nBin; i++){
         Double_t xi = htemp->GetBinContent(i);
         Double_t yi = h3->GetBinContent(i);
         Double_t dyi = h3->GetBinError(i);
         //   printf("%3d, xi:%10f, yi:%10f, %10f\n", i, xi, yi, yi*TMath::Log(xi/Sum));
         Max += yi*TMath::Log(xi/Sum);
         dMax += TMath::Power(dyi*TMath::Log(xi/Sum),2); 
      }
      dMax = TMath::Sqrt(dMax);
      printf("a=%5.3f, Maximum Likelihood :%10.2f(%10.2f)\n", a, Max, dMax); 
   }

   
   return ;
}
