Double_t Integration(TH1F * hist = htemp){
   Int_t maxBin = hist -> GetNbinsX();
   Int_t binID[2] = {0,maxBin-1};
   Int_t Floor = 0; //1 = using Bin start, 0 = using Bin center;

   Double_t integrated = 0;
   for (Int_t i = 0; i < maxBin; ++i){
      Double_t binCenter = hist->GetBinCenter(i);
      Double_t binWidth  = hist->GetBinWidth(i);
      integrated += (htemp->GetBinContent(i))*(binCenter - Floor*binWidth/2);
   }
   
   printf(" %s: Integration: (%d:%d) = %f \n",hist->GetName(),binID[0],binID[1],integrated);
   
   return integrated;
   
}
