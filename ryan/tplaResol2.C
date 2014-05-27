#include "constant.h"

void tplaResol2() {
   
   const char* rootfile="PrimaryData/phys14Down.root";
   TString detector = "Tpla-L"; //Tpla-L
   Double_t TplaBeta = 0.55;
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=1000000;
   Int_t nBin = 500;
   Int_t relBinWidth = 2;
   
   printf("\n >>>>> file: %s \n", rootfile); 

//######################################
   TClonesArray *hoge_V775, *hoge_MWDC;
   TFile *f = new TFile(rootfile,"read");
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("plaV775",1);
   tree->SetBranchAddress("plaV775",&hoge_V775);
   
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;
   
   Int_t detectorID;
   Double_t Xrange[2];
   Double_t Yrange[2];
   if ( detector == "Tpla-L"){
      tree->SetBranchStatus("smwdc_L",1);
      tree->SetBranchAddress("smwdc_L",&hoge_MWDC);
      detectorID = 0;
      Xrange[0] = -15;
      Xrange[1] = 5;
      Yrange[0] = -1300;
      Yrange[1] = 200;
   }else{
      tree->SetBranchStatus("smwdc_R",1);
      tree->SetBranchAddress("smwdc_R",&hoge_MWDC);
      detectorID = 1;
      Xrange[0] = -9;
      Xrange[1] = 11;
      Yrange[0] = -200;
      Yrange[1] = 1300;
   }
   
   gStyle->SetOptStat(0);
   TString hTdiffTitle;
   hTdiffTitle.Form("%s | tdiff vs Tpla(X by mwdc)",detector.Data());  
   TH2F* hTdiff = new TH2F("hTdiff",hTdiffTitle, nBin , Yrange[0], Yrange[1], 200, Xrange[0], Xrange[1]);
   hTdiff->SetXTitle("Tpla(X)[mm]");
   hTdiff->SetYTitle("Tdiff[ns]");
   
	TString hResolTitle;
	hResolTitle.Form("Tavg Resolution vs TplaX. binWidth:%2d (%4.1f mm)", relBinWidth, (relBinWidth)*(Yrange[1]-Yrange[0])/nBin);
	TH1F* hResol = new TH1F("hResol", hResolTitle, nBin, Yrange[0], Yrange[1]); 
	hResol->SetXTitle("TplaX[mm]");
   hResol->SetYTitle("Tavg Resol [ps]");

   TCanvas* cTplaResol = new TCanvas("cTplaResol", "Tpla resolution by SMWDC", 0, 0, 800, 600);   
   cTplaResol->Divide(1,2);
   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   
   
   for( Int_t eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID); 
      
      // Get Tdiff
      Double_t tdiff = kInvalidD;
      Int_t nHitV775 = hoge_V775->GetEntriesFast();
      for ( Int_t p = 0; p < nHitV775; p++){
         art::TTwoSidedPlasticData * V775Data = (art::TTwoSidedPlasticData*)hoge_V775->At(p);
         if ( V775Data->GetDetID() == detectorID){
            tdiff= V775Data->GetTDiff();
         }
      }
      if(!TMath::Finite(tdiff)) continue;
      
      // Get MWDC X and A then project to Tpla
      Double_t TplaX = kInvalidD;
      Int_t nHitSMWDC = hoge_MWDC->GetEntriesFast();
      for( Int_t p = 0; p < nHitSMWDC; p++){
         art::TMWDCTrackingResult * smwdc = (art::TMWDCTrackingResult*)hoge_MWDC->At(p);
         art::TTrack * track = (art::TTrack*)smwdc->GetTrack();
         Double_t x = track->GetX();
         Double_t a = track->GetA();
         if ( TMath::Abs(a - x/z0)> 0.1 ) continue;
         TplaX = x + (z0Tpla-z0)*a;
      }
      if (!TMath::Finite(TplaX)) continue;     
      //printf(" %d | nHitV775:%d, tdiff:%10.5f | nHitSMWDC:%d, TplaX:%10.3f \n", eventID, nHitV775, tdiff, nHitSMWDC, TplaX);
      
      hTdiff->Fill(TplaX,tdiff);
      
//------------Clock      
      clock.Stop("timer");
      Double_t time = clock.GetRealTime("timer");
      clock.Start("timer");
      
      if ( !shown ) {
         if (fmod(time, 10) < 1 ){
            printf( "%10d[%2d%%] |%3d min %5.2f sec | expect:%5.1fmin\n", 
            eventID, 
            TMath::Nint((eventID+1-firstEntry)*100./nEntries),
            TMath::Floor(time/60), time - TMath::Floor(time/60)*60,
            nEntries*time/(eventID+1-firstEntry)/60.);
            shown = 1;
         }
      }else{
         if (fmod(time, 10) > 9 ){
            shown = 0;
         }
      }

   }

	TLatex text;
   text.SetNDC();
   text.SetTextColor(1);
   TString textStr;
   
   cTplaResol->cd(1);
   hTdiff->Draw("colz");

   cTplaResol->cd(2);

	TF1 *fit = new TF1("fit", "gaus(0)", Xrange[0], Xrange[1]);
	Double_t para[3];

   for ( Int_t relBinID = 1; relBinID <= nBin; relBinID += relBinWidth){
   	hTdiff->ProjectionY("test",relBinID,relBinID+relBinWidth);
   	Double_t TplaXPos   = Yrange[0] + (relBinID+relBinWidth/2.)*(Yrange[1]-Yrange[0])/nBin;
   	Double_t TplaXWidth = (relBinWidth)*(Yrange[1]-Yrange[0])/nBin;
   	Int_t peakBin=test->GetMaximumBin();
   	fit->SetParameters(500, test->GetBinCenter(peakBin) , 0.5);
   	test->Fit("fit", "Q");
   	fit->GetParameters(para);
   	Double_t resolution = TMath::Abs(TMath::Sqrt(TMath::Power(para[2],2)-TMath::Power(2*TplaXWidth/TplaBeta/cVaccum,2)))*1000.;
   	
   	if (TMath::Finite(resolution) && resolution < 800. && para[2] != 0.5) {
   		printf(" bin:(%3d,%3d) TplaX: %7.1f, mean: %4.1f, sigma: %4.2f(%f), resol: %6.2f ps \n", relBinID, relBinID+relBinWidth, TplaXPos, para[1], para[2], fit->GetParError(2), resolution);
   		hResol->Fill(TplaXPos,resolution);
   		//hResol->SetBinError(relBinID*relBinWidth, fit->GetParError(2)*1000);
   	}
   }
  
   hResol->Draw("E");
   
   textStr.Form("Tpla Beta:%4.2f",TplaBeta);
   text.DrawText(0.3, 0.7, textStr);

   return ;
}
