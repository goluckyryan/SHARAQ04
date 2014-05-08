void MWDCplotValidPlane(){

   Double_t Qgate = 800;
   Int_t minTrackPlane = 5;
   TString filename = "ppDown.root";
   
   TFile *f0 = new TFile (filename);
   TTree *tree = (TTree*)f0->Get("tree");
   
   TCanvas * cMWDCeff = new TCanvas ("cMWDCeff","cMWDCeff", 1200,50,800,800);
   //cMWDCeff->Divide(2,2);
   
   const Int_t nBin = 7;
   TH2F * validPlane = new TH2F("validPlane", "Number of Valid Plane (No Gate)", nBin, 0, 7, nBin, 0, 7);
   
   TCut cut ="";
   
   tree->Draw("smwdc_R.fNPlaneValid:smwdc_L.fNPlaneValid>>validPlane",cut,"col");
   
   Int_t count[nBin][nBin];
   Int_t totCount = validPlane->GetEntries();
   TString hTitle;
   hTitle.Form("%s, Number of Valid Plane (tot:%d)",filename.Data(), totCount);
   validPlane->SetTitle(hTitle);
   validPlane->SetXTitle("MWDC-L");
   validPlane->SetYTitle("MWDC-R");
   validPlane->SetStats(0);
   validPlane->Draw("col");
   
   Int_t countOR[nBin];
   
   TString countText;
   TLatex text;
   text.SetTextSize(0.03);
   text.SetTextColor(0);
   
   
   printf("=========================\n");
   printf(" %3s |", "");
   for ( Int_t j = 0; j < nBin; j++){
      printf("%6d, ", j);
   }
   printf("\n");
   for ( Int_t i = 0; i < 9*nBin; i++) printf("-");
   printf("\n");
   for (Int_t i = 0; i < nBin; i++){
      printf(" %3d |", i);
      countOR[i] = 0;
      for (Int_t j = 0; j < nBin; j++){
         count[i][j] = validPlane->GetBinContent(i+1,j+1);
         countText.Form("%d",count[i][j]);
         text.DrawText(validPlane->GetBinLowEdge(i+1),validPlane->GetBinLowEdge(j+1), countText);
         
         for ( Int_t k = 0; k < nBin; k++){
            if ( i>=k && j >=k) {
               countOR[k] += count[i][j];
            }
         }
         printf("%6d, ", count[i][j]); 
      }
      printf("\n");
   }
   
   printf("====================\n");
   printf(" totCount:%d \n",totCount);
   text.SetTextColor(1);
   for (Int_t k = 0; k < nBin; k++){
      if ( k < nBin) {
         countOR[k] = countOR[k] - countOR[k+1];
      }
      printf(" Count[%d]:%7d [%4.1f%%]\n",k, countOR[k], countOR[k]*100./totCount);
      countText.Form("%4.1f%%", countOR[k]*100./totCount);
      text.DrawText( validPlane->GetBinCenter(k+1), validPlane->GetBinCenter(k+1), countText);
   }
   
 
}


