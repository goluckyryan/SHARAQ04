void GetHistogramData(TH1F* h1) {
   
   Int_t nBin = h1->GetNbinsX();
   
   printf("{\n");
   for(Int_t i = 1; i <= nBin; i++){
      printf("{%10.3f, %10.3f, %10.3f},\n", h1->GetBinCenter(i), h1->GetBinContent(i), h1->GetBinError(i));
   }
   printf("}\n");
   
   return ;
}
