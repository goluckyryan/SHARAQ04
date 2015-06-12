
//void MWDCeff_fine() 
{

//############################################################################  
   const char* rootfile="23F_run24_0603.root"; 
   
//############################################################################
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded.\n",rootfile);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totEntries = tree->GetEntries();
   printf("totEntries:%d\n", totEntries);
   
//############################################################################  
   TCanvas * cMWDC = new TCanvas("cMWDC", "MWDC efficiency", 100, 50, 900, 600);
   cMWDC->Divide(3,2);

   gStyle->SetOptStat(0);
   
   TH2F* hTDiffXL = new TH2F("hTDiffXL", "TDiff vs X(L)", 300, -1000,  200, 300, -20, 10);
   TH2F* hTDiffXR = new TH2F("hTDiffXR", "TDiff vs X(R)", 300,  -200, 1000, 300, -15, 15);

   TH2F* hTDiffGoodL = new TH2F("hTDiffGoodL", "TDiff vs IsGood(L)", 4, -1, 3, 300, -20, 10);
   TH2F* hTDiffGoodR = new TH2F("hTDiffGoodR", "TDiff vs IsGood(R)", 4, -1, 3, 300, -15, 15);
   
   TH1F* hEffXL = new TH1F("hEffXL", "Eff vs X(L)", 300, -1000,  200); 
   TH1F* hEffXR = new TH1F("hEffXR", "Eff vs X(R)", 300,  -200, 1000); 

//############################################################################   
   TCut gate23F = "gate.Test(0)";
   TCut TplaL = "plaV775.fID == 0";
   TCut TplaR = "plaV775.fID == 1";
   TCut Qgate = "1000<plaV775.fCharge && plaV775.fCharge<4000";
   
   cMWDC->cd(1); tree->Draw("plaV775.fTDiff:smwdc_L[0].fX>>hTDiffXL", gate23F + TplaL + Qgate, "colz");
   cMWDC->cd(4); tree->Draw("plaV775.fTDiff:smwdc_R[0].fX>>hTDiffXR", gate23F + TplaR + Qgate, "colz");

   cMWDC->cd(2); tree->Draw("plaV775.fTDiff:smwdc_L[0].IsGood()>>hTDiffGoodL", gate23F + TplaL + Qgate + "smwdc_L[0].fNPlaneValid", "colz");
   cMWDC->cd(5); tree->Draw("plaV775.fTDiff:smwdc_R[0].IsGood()>>hTDiffGoodR", gate23F + TplaR + Qgate + "smwdc_R[0].fNPlaneValid", "colz");

   cMWDC->cd(3); 

   //--------- sector
   Int_t sBin = 10;
   for( Int_t i = 1; i <= 300/sBin; i ++){
      hTDiffXL->ProjectionX("htemp", (i-1)*sBin+1, i*sBin);
      htemp->RebinX(3);
      if( htemp->GetEntries() > 600) {
         Int_t mBin = htemp->GetMaximumBin();
         Double_t xMean = htemp->GetBinCenter(mBin);
         hTDiffGoodL->ProjectionX("hproj", (i-1)*sBin+1, i*sBin);
         Double_t eff = hproj->GetBinContent(3)/hproj->GetEntries();
         printf("L: %3d, (%4d, %4d), %5d, %3d, %7.2f, %6.4f   |", i,  (i-1)*sBin+1, i*sBin, htemp->GetEntries(), mBin, xMean, eff);
         hEffXL->Fill(xMean, eff);
         hEffXL->SetBinError(hEffXL->FindBin(xMean),0.01);
      }

      hTDiffXR->ProjectionX("htemp", (i-1)*sBin+1, i*sBin);
      htemp->RebinX(3);
      if( htemp->GetEntries() > 600){
         Int_t mBin = htemp->GetMaximumBin();
         Double_t xMean = htemp->GetBinCenter(mBin);
         hTDiffGoodR->ProjectionX("hproj", (i-1)*sBin+1, i*sBin);
         Double_t eff = hproj->GetBinContent(3)/hproj->GetEntries();
         printf("R: %3d, (%4d, %4d), %5d, %3d, %7.2f, %6.4f \n", i,  (i-1)*sBin+1, i*sBin, htemp->GetEntries(), mBin, xMean, eff);
         hEffXR->Fill(xMean, eff);
         hEffXR->SetBinError(hEffXR->FindBin(xMean),0.01);
      }else{
         printf("\n");
      }
   } 
   
   hEffXL->SetMaximum(1);
   hEffXL->SetMinimum(0);
   hEffXL->Draw("E");

   cMWDC->cd(6);
   hEffXR->SetMaximum(1);
   hEffXR->SetMinimum(0);
   hEffXR->Draw("E");
   return;
}
/*
   art::TGateArray *hoge_gate;
   TClonesArray  *hoge_V775, *hoge_L, *hoge_R;
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded. \n",rootfile);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("plaV775",1);
   tree->SetBranchStatus("smwdc_L",1); //get charge for PID
   tree->SetBranchStatus("smwdc_R",1);

   tree->SetBranchAddress("plaV775",&hoge_V775);
   tree->SetBranchAddress("smwdc_L",&hoge_L);
   tree->SetBranchAddress("smwdc_R",&hoge_R);

//############################################################################   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   
   gROOT->ProcessLine(".!date");
   
//##############################################################
   for( eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID,0);
      
      Double_t tdiffL = TMath::QuietNaN();
      Double_t tdiffR = TMath::QuietNaN();
      Double_t qL = TMath::QuietNaN();
      Double_t qR = TMath::QuietNaN();
      Double_t xL = TMath::QuietNaN();
      Double_t xR = TMath::QuietNaN();

//--------------Get gate on 23F
      if( hoge_gate->Test(0) != 1 ) continue;

//----------------Get charge and tdiff of Tpla
      Int_t nHit = hoge_V775-> GetEntriesFast();
      if (nHit == 0) continue;
      for( Int_t p = 0; p < nHit; p++){
         Int_t DetID = ((art::TTwoSidedPlasticData*) hoge_V775->At(p))->GetID();
         if( DetID == 0 ){
            tdiffL = ((art::TTwoSidedPlasticData*) hoge_V775->At(p))->GetTDiff();
            qL = ((art::TTwoSidedPlasticData*) hoge_V775->At(p))->GetCharge();
            if ( qL < qGate[0] || qL > qGate[1] ) qL = TMath::QuietNaN();
         }
         if( DetID == 1 ){
            tdiffR = ((art::TTwoSidedPlasticData*) hoge_V775->At(p))->GetTDiff();
            qR = ((art::TTwoSidedPlasticData*) hoge_V775->At(p))->GetCharge();
            if ( qR < qGate[0] || qR > qGate[1] ) qR = TMath::QuietNaN();
         }
      }
      
      nHit = smwdc_L->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         (art::TMWDCTrackingResult*) mL = (art::TMWDCTrackingResult*)hoge_L->At(p);
         trackID = mL->GetTrackingID();
         track = (art::TTrack*)xyS0->GetTrack();
         s0x = trackS0->GetX();
         s0y = trackS0->GetY();
         s0a = trackS0->GetA();
         s0b = trackS0->GetB();
      }

      
   }


   return ;
}

