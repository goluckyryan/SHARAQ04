void Hist_PeakEdge(const TH1F* htemp){
   Int_t nBin = htemp->GetNbinsX();
   Double_t maxi = htemp->GetMaximum();
   Int_t maxiBin = htemp->GetMaximumBin();
   Double_t maxiX = htemp->GetBinCenter(maxiBin);
   
   Double_t halfMax = maxi/2.;
   
   Double_t lowX, highX;
   Int_t lowBin, highBin;
   
   //_____________find low X and high X
   for( Int_t i = 1; i < nBin; i ++){
   	Int_t y1 = htemp->GetBinContent(i) - halfMax;
   	Int_t y2 = htemp->GetBinContent(i+1) - halfMax;
   	
   	Int_t findFlag = 0;
   	
   	//if (TMath::Sign(y1,y2) == -1 ) continue;
   	
   	if ( y1 <= 0 && y2 >= 0){
   		findFlag = 1;
   		Double_t x1 = htemp->GetBinCenter(i);
   		Double_t x2 = htemp->GetBinCenter(i+1);
   		
   		lowBin = i;
   		
   		lowX = (y2*x1-y1*x2)/(y2-y1);
   	}
   	
   	if ( y1 >= 0 && y2 <= 0){
   		findFlag = 2;
   		Double_t x1 = htemp->GetBinCenter(i);
   		Double_t x2 = htemp->GetBinCenter(i+1);
   		
   		highBin = i;
   		
   		highX = (y1*x2-y2*x1)/(y1-y2);
   	}
   	
   	if(findFlag == 2) break;
   
   }
   
   printf("maxi: %.2f @ x : %.2f | lowX : %.2f (%d), highX: %.2f(%d)\n", maxi, maxiX, lowX, lowBin, highX, highBin);
   
   htemp->Draw();
   TLine line;
   line.DrawLine(lowX, 0, lowX, maxi);
   line.DrawLine(lowX-10, halfMax, highX+10, halfMax); 
   line.DrawLine(highX, 0, highX, maxi);
   
}

