void MaxiLikelihood_Func_Norm(TH1F* h2, TF1* f1, TH1F* h1) {
   
   // find the likelihood of h2 to function f1, use h1 as normalization
   
   Int_t nBin = h2->GetNbinsX();
   Int_t nEvent = h2->GetEntries();
   Double_t wi  = h2->GetBinWidth(1)/2.;
   
   Double_t Max = 0;
   Double_t dMax = 0;
   Double_t area = f1->Integral(0,400)/(wi*2);
   for( Int_t i = 1; i <= nBin; i++){
            Double_t yi  = h2->GetBinContent(i);
            Double_t dyi = h2->GetBinError(i);
            
            Double_t bi  = h2->GetBinCenter(i);
            Double_t Gi  = f1->Eval(bi);
            //Double_t Gi  = f1->Integral(bi-wi, bi+wi)/area;

            //printf("%3d, bi:%10f, yi:%10f, Gi:%10.9f, Gi/area:%10.9f, %10f\n", i, bi, yi, Gi, Gi*area,  yi*TMath::Log(Gi/area));
            Max  += yi*TMath::Log(Gi/area);
            dMax += TMath::Power(dyi*TMath::Log(Gi/area),2); 
   }
   //Max = Max;
   dMax = TMath::Sqrt(dMax);
   
   
   //---------- normalization
   nBin = h1->GetNbinsX();
   wi  = h1->GetBinWidth(1)/2.;
   
   Double_t MaxN = 0;
   Double_t dMaxN = 0;
   area = f1->Integral(0,400)/(wi*2);
   for( Int_t i = 1; i <= nBin; i++){
            Double_t yi  = h1->GetBinContent(i);
            Double_t dyi = h1->GetBinError(i);
            
            Double_t bi  = h1->GetBinCenter(i);
            Double_t Gi  = f1->Eval(bi);
            //Double_t Gi  = f1->Integral(bi-wi, bi+wi)/area;

            //printf("%3d, bi:%10f, yi:%10f, Gi:%10.9f, Gi/area:%10.9f, %10f\n", i, bi, yi, Gi, Gi*area,  yi*TMath::Log(Gi/area));
            MaxN  += yi*TMath::Log(Gi/area);
            dMaxN += TMath::Power(dyi*TMath::Log(Gi/area),2); 
   }
   
   MaxN = MaxN * nEvent / area; // this is the reference Max-Likelihood;
   dMaxN = sqrt(dMaxN) * nEvent / area; // this is the error of the reference Max-Likelihood;
   
   printf(" sample: %f, norm:%f \n", Max, MaxN);
   Double_t MaxR = Max/MaxN;
   
   //printf(" %10f, %10f, %10f, %10f \n", dMax, Max, dMaxN, MaxN);
   
   //Double_t dMaxR = MaxR * sqrt(pow(dMax/Max,2) + pow(dMaxN/MaxN,2));
   Double_t dMaxR = dMax/MaxN;

   printf("nEvent:%d, area:%10.2f, Maximum Likelihood :%10.5f(%10.5f) = (%10.5f, %10.5f)\n", nEvent, area, MaxR, dMaxR, MaxR-dMaxR, MaxR+dMaxR);
   
   //TODO, need to calculate the value of perfect fit, then normalize.
   
   
   return ;
}
