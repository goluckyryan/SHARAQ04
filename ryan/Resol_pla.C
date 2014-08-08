#include "constant.h"

void Resol_pla() {
   
   const char* rootfile="ppAll_0731.root";
   const char* plaBranch= "plaV775"; Int_t plaDetID = 0;
   const char* mwdcBranch = "smwdc_L";

   Double_t PlaBeta = 0.66;
   
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=1000000;
   
   Int_t nBin = 500;
   Int_t relBinWidth = 5;
   Double_t MeanRange[2] = {-1000,-200};
   
   Double_t maxResol = 1000; // ps
   
   printf("\n >>>>> file: %s \n", rootfile); 

	//######################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;
   
   //**************************************
   TClonesArray *hoge_pla, *hoge_MWDC;
   TFile *f = new TFile(rootfile,"read");
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus(plaBranch,1);
   tree->SetBranchAddress(plaBranch,&hoge_pla);
      
   Double_t TDiffRange[2];
   Double_t XRange[2];
   Double_t mwdc_z0, dis_mwdc_pla;
   TString plaName;
   if ( mwdcBranch == "smwdc_L"){
      tree->SetBranchStatus("smwdc_L",1);
      tree->SetBranchAddress("smwdc_L",&hoge_MWDC);
      mwdc_z0 = z0;
      dis_mwdc_pla = z0Tpla;
      TDiffRange[0] = -15;
      TDiffRange[1] = 5;
      XRange[0] = -1300;
      XRange[1] = 200;
      plaName = "Tpla-L";
   }else if (mwdcBranch == "smwdc_R"){
      tree->SetBranchStatus("smwdc_R",1);
      tree->SetBranchAddress("smwdc_R",&hoge_MWDC);
      mwdc_z0 = z0;
      dis_mwdc_pla = z0Tpla;
      TDiffRange[0] = -9;
      TDiffRange[1] = 11;
      XRange[0] = -200;
      XRange[1] = 1300;
      plaName = "Tpla-R";
   }else if (mwdcBranch == "dc91"){
   	tree->SetBranchStatus(mwdcBranch,1);
      tree->SetBranchAddress(mwdcBranch,&hoge_MWDC);
      mwdc_z0 = 0;
      dis_mwdc_pla = 150;
      XRange[0] = -60;
      XRange[1] = 80;
      if (plaBranch == "plaV1190_FH9"){
   		TDiffRange[0] = -4;
      	TDiffRange[1] = 6;
      	plaName = "Pla-FH9";
   	}else{
   		TDiffRange[0] = -4;
      	TDiffRange[1] = 6;
      	plaName = "Pla-F3";
   	}
   }
   //**************************************
   printf("====== Pla: %s, DetID:%d \n", plaBranch, plaDetID);
   printf("====== mwdc: %s \n", mwdcBranch);
   
   //**************************************
   gStyle->SetOptStat(0);
   TString hTdiffTitle;
   hTdiffTitle.Form("%s(tdiff) vs %s(X by %s)", plaName.Data(), plaName.Data(), mwdcBranch);  
   TH2F* hTdiff = new TH2F("hTdiff",hTdiffTitle, nBin , XRange[0], XRange[1], 200, TDiffRange[0], TDiffRange[1]);
   hTdiff->SetXTitle("pla(X)[mm]");
   hTdiff->SetYTitle("Tdiff[ns]");
   
	TString hResolTitle;
	hResolTitle.Form("Tavg Resolution vs %s(X). binWidth:%2d (%4.1f mm), Pla beta:%4.2f", plaName.Data(), relBinWidth, (relBinWidth)*(XRange[1]-XRange[0])/nBin, PlaBeta);
	TH1F* hResol = new TH1F("hResol", hResolTitle, nBin, XRange[0], XRange[1]); 
	hResol->SetXTitle("pla(X)[mm]");
   hResol->SetYTitle("Tavg Resol [ps]");

   TCanvas* cPlaResol = new TCanvas("cPlaResol", "Pla resolution by MWDC", 2000, 0, 800, 600);   
   cPlaResol->Divide(1,2);
   
   //**************************************
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
      Double_t Q1 = kInvalidD;
      Int_t nHitpla = hoge_pla->GetEntriesFast();
      for ( Int_t p = 0; p < nHitpla; p++){
         art::TTwoSidedPlasticData * plaData = (art::TTwoSidedPlasticData*)hoge_pla->At(p);
         if ( plaData->GetDetID() == plaDetID){
				Q1   = plaData->GetQ1();//*2.33-850;
				Q2   = plaData->GetQ2();
            tdiff= plaData->GetTDiff()-1000./TMath::Power(Q1-450,1) + 1000./TMath::Power(Q2-450,1);
         }
      }
      if(!TMath::Finite(tdiff)) continue;
      
      // Get MWDC X and A then project to Tpla
      Double_t PlaX = kInvalidD;
      Int_t nHitMWDC = hoge_MWDC->GetEntriesFast();
      for( Int_t p = 0; p < nHitMWDC; p++){
         art::TMWDCTrackingResult * mwdcData = (art::TMWDCTrackingResult*)hoge_MWDC->At(p);
         art::TTrack * track = (art::TTrack*)mwdcData->GetTrack();
         Double_t x = track->GetX();
         Double_t a = track->GetA();
         PlaX = x + (dis_mwdc_pla - mwdc_z0)*a;
      }
      if (!TMath::Finite(PlaX)) continue;     
      //printf(" %d | nHitpla:%d, tdiff:%10.5f | nHitMWDC:%d, PlaX:%10.3f \n", eventID, nHitpla, tdiff, nHitMWDC, PlaX);
      
      hTdiff->Fill(PlaX,tdiff);
      
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

	//**************************************
	TLatex text;
   text.SetNDC();
   text.SetTextColor(1);
   TString textStr;
   
   cPlaResol->cd(1);
   hTdiff->Draw("colz");

   cPlaResol->cd(2);

	TF1 *fit = new TF1("fit", "gaus(0)", TDiffRange[0], TDiffRange[1]);
	Double_t para[3];

	Double_t mean = 0;
	Double_t meanErr = 0;
	Int_t count = 0;
   for ( Int_t relBinID = 1; relBinID <= nBin; relBinID += relBinWidth){
   	hTdiff->ProjectionY("test",relBinID,relBinID+relBinWidth);
   	Double_t PlaXPos   = XRange[0] + (relBinID+relBinWidth/2.)*(XRange[1]-XRange[0])/nBin;
   	Double_t PlaXWidth = (relBinWidth)*(XRange[1]-XRange[0])/nBin;
   	Int_t peakBin=test->GetMaximumBin();
   	fit->SetParameters(500, test->GetBinCenter(peakBin) , 0.5);
   	test->Fit("fit", "Q");
   	fit->GetParameters(para);
   	// resol = Sqrt( sigma^2 - (2*DeltaX/beta/c)^2 )
   	Double_t resolution = TMath::Abs(TMath::Sqrt(TMath::Power(para[2],2)-TMath::Power(2*PlaXWidth/PlaBeta/cVaccum,2)))*1000.; //ps
   	Double_t err_resol = TMath::Abs(fit->GetParError(2)*para[2]/(resolution/1000.))*1000.; // ps
   	
   	if (TMath::Finite(resolution) && resolution < maxResol && para[2] != 0.5 && err_resol < resolution/2.) {
   		hResol->Fill(PlaXPos,resolution);
   		hResol->SetBinError(hResol->FindBin(PlaXPos),err_resol);
   		if ( PlaXPos > MeanRange[0] && PlaXPos < MeanRange[1] ){
	   		count ++;
   			mean +=resolution;
   			meanErr += err_resol*err_resol;
   		}
   		//printf(" bin:(%3d,%3d) PlaX: %7.1f, mean: %4.1f, sigma: %5.2f(%f), resol: %6.2f(%5.2f) ps \n", relBinID, relBinID+relBinWidth, PlaXPos, para[1], para[2], fit->GetParError(2), resolution, err_resol);
   		
   	}
   }
  
   hResol->Draw("E");
   
   TString textStr;
   textStr.Form("Mean (%.0f mm, %.0f mm) Tavg Resol.:%.2f(%.2f) ps", MeanRange[0], MeanRange[1], mean/count, TMath::Sqrt(meanErr)/count);
   text.DrawText(0.2, 0.2, textStr);

   return ;
}
