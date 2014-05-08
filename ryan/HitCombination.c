void HitCombination(){
   TBenchmark watch;
   watch.Start("timer");

    const Int_t fNPlane = 3;
    Int_t * fWeight     = new Int_t[fNPlane];
    Int_t * fNValidHit  = new Int_t[fNPlane];

    fWeight[0] = 1;fNValidHit[0] = 1;
    fWeight[1] = 1;fNValidHit[1] = 2;
    fWeight[2] = 1;fNValidHit[2] = 3;
    //fWeight[3] = 1;fNValidHit[3] = 3;
    //fWeight[4] = 1;fNValidHit[4] = 3;
    //fWeight[5] = 1;fNValidHit[5] = 3;

// Find  nHitSum and fNValidPlane;
    Int_t nHitProduct = 1;
    Int_t fNHitSum     = 0;
    Int_t fNValidPlane = 0;
    for ( Int_t i = 0; i < fNPlane; i++){
        fNValidHit[i] = fNValidHit[i]*fWeight[i];
        if (fWeight[i] != 0){
            nHitProduct = nHitProduct*fNValidHit[i];     
            fNValidPlane ++;
        }
        fNHitSum += fNValidHit[i];
    }
    
// Initialize position as a Matrix

    printf("==============\n");
    printf(" %10s:", "weight");for (Int_t i = 0; i< fNPlane; i++) {printf(" %1d,",fWeight[i]);} printf("\n");
    printf(" %10s:", "nHit"  );for (Int_t i = 0; i< fNPlane; i++) {printf(" %1d,",fNValidHit[i]);} printf("\n");
    printf(" nValidPlane:%d, nHitSum : %d\n",fNValidPlane,nHitProduct);
    printf("==============\n");
    printf("%7s|","i \\ j ");for ( Int_t i = 0; i < fNPlane; i++){printf("   %1d,", i);}
    printf("\n -----------------------\n");
    
    
//------------Loop all Combination
      fPosition = new TMatrixD(nHitProduct,fNPlane);
      std::vector<Double_t>  mean(nHitProduct,0.);
      std::vector<Double_t>  FOM(nHitProduct,0.);
 
   //------------Loop all Combination
/*      for ( Int_t i = 0; i < nHitProduct; i++ ){
         Bool_t addedFlag = 0;
         for ( Int_t iPlane = 0; iPlane < fNPlane; ++iPlane){
            if (i == 0) {
               (*fPosition)[i][iPlane] = 0;
            }else{
               if ( !addedFlag){
                  if ( (*fPosition)[i-1][iPlane] < fNValidHit[iPlane]-1){
                     (*fPosition)[i][iPlane] = (*fPosition)[i-1][iPlane] + 1;
                     addedFlag = 1;
                  }else{
                     (*fPosition)[i][iPlane] = 0;
                  }
               }else{
                  (*fPosition)[i][iPlane] = (*fPosition)[i-1][iPlane];
               }
            }
         }
         for (Int_t iPlane = 0; iPlane < fNPlane; ++iPlane){
            mean[i] += (*fPosition)[i][iPlane]/fNPlane;
         }
         for (Int_t iPlane = 0; iPlane < fNPlane; ++iPlane){
            FOM[i] += pow((*fPosition)[i][iPlane] - mean[i],2);
         }
         FOM[i] = FOM[i]*mean[i]*fNPlane;
      }
      */
      
      Int_t index = 0;
      for ( Int_t iPlane = 0; iPlane < fNPlane; ++iPlane){
         for (Int_t iHit = 0; iHit < fNValidHit[iPlane]; ++iHit){
            (*fPosition)[index][iPlane] = iHit;
         }
         index ++;
         if (index >= nHitProduct) break;
      }
      
      for ( Int_t i = 0; i< nHitProduct; ++i){
         printf("%4d |", i);
         for (Int_t iPlane = 0; iPlane < fNPlane; ++iPlane){
            printf(" %3f,", (*fPosition)[i][iPlane]);
         }
         printf(" |\n");
      }
   
   //--------------Bubble Sorting
      Double_t temp;      
      for ( Int_t i = 1; i < nHitProduct; ++i ){
         for (Int_t j = 0; j < nHitProduct-1; ++j){
            if ( FOM[j+1] < FOM[j]){
               // Swap
               for (Int_t iPlane = 0; iPlane < fNPlane; ++iPlane){
                  temp = (*fPosition)[j][iPlane];
                  (*fPosition)[j][iPlane] = (*fPosition)[j+1][iPlane];
                  (*fPosition)[j+1][iPlane] = temp;   
               }
            
               temp = mean[j];
               mean[j] = mean[j+1];
               mean[j+1] = temp;
               
               temp = FOM[j];
               FOM[j] = FOM[j+1];
               FOM[j+1] = temp;      
            }
         }      
      }

   
   delete fPosition;
   
   watch.Stop("timer");
   printf(" time cost:%10.3f msec\n", watch.GetRealTime("timer")*1000);
    
}

Int_t Dec2Bin(Int_t dec){
   Int_t bin = 0;
   
   const Int_t NDigit = (Int_t)TMath::Log2(dec)+1;
   Int_t * residual = new Int_t[NDigit];
   Int_t * divident = new Int_t[NDigit];
   
   for (Int_t i = 0; i < NDigit; i++){
      Int_t posSum;
      if ( i == 0){
         posSum = dec;
      }else{
         posSum = divident[i-1];
      }
      divident[i] = posSum/2;
      residual[i] = posSum%2;
      bin = bin + residual[i]*pow(10,i);
   }

   return bin;
}

Int_t Bin2Dec(Int_t bin){
   Int_t dec = 0;
   
   const Int_t NDigit = (Int_t)TMath::Log10(bin)+1;
   Int_t *digit = new Int_t[NDigit];
   
   for (Int_t i = 0; i<NDigit; i++){
      Int_t posSum = pow(10,i);
      digit[i] = (bin/posSum)%2;
      dec = dec + digit[i]*pow(2,i);
      //printf("%d, base:%d,  digit:%d, dec:%d\n",i,posSum, digit[i], dec);
   }
   
   delete digit;
   return dec;
}

/*
FloatVec_t Dec2BinArray(Int_t dec, const Int_t NDigit){
   FloatVec_t residual(NDigit,0);
   Int_t divident[NDigit];
   
   for (Int_t i = 0; i < NDigit; i++){
      Int_t posSum;
      if ( i == 0){
         posSum = dec;
      }else{
         posSum = divident[i-1];
      }
      divident[i] = posSum/2;
      residual[i] = posSum%2;
   }

   return residual;
}
*/
