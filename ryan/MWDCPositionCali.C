
void MWDCPositionCali() {

//############################################################################  
//   const char* rootfile="PrimaryData/phys23F.root"; 
   const char* rootfile="ppAll_1105.root"; 
   
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=100000;

//############################################################################
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded.\n",rootfile);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totEntries = tree->GetEntries();
   if(allentry){
     firstEntry = 0;
     nEntries = totEntries;
   }
   Int_t endEntry = firstEntry + nEntries;
   printf("totEntries:%d, nEntries:%.d [%5.2f%%]\n", totEntries, nEntries, 100.*nEntries/totEntries);
   
//############################################################################  
   Int_t Div[2] = {2,2};
   TCanvas * cMWDC = new TCanvas("cMWDC", "MWDC Position Calibaration", 100, 50, 400*Div[0], 400*Div[1]);
   cMWDC->Divide(Div[0],Div[1]);

   gStyle->SetOptStat(0);
   
   TH2F* hXZ = new TH2F("hXZ", "Z and X", 50, -100, 100, 50, -1050, -950);
   hXZ->SetXTitle("X [mm]");
   hXZ->SetYTitle("Z [mm]");

	TH2F* hYZ = new TH2F("hYZ", "Z and Y", 50, -100, 100, 50, -1050, -950);
   hYZ->SetXTitle("Y [mm]");
   hYZ->SetYTitle("Z [mm]");
   
   TH1F* hSigma1 = new TH1F("hSigma1", "sigma 1 vs Z", 100, -1070,-1000);
   TH1F* hSigma2 = new TH1F("hSigma2", "sigma 2 vs Z", 100, -1070,-1000);

//############################################################################   
   TClonesArray  *hoge_L;
   tree->SetBranchAddress("smwdc_L",&hoge_L);
   
  	TRandom *ranZ_seed = new TRandom();
   
//############################################################################  
   for( Int_t eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID);
      
      // initialization
      Double_t x1, a1, y1, b1;

//---------Get SMWDC image, should be one 1 instance
      Int_t nHit = hoge_L->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         art::TMWDCTrackingResult * xy1 = (art::TMWDCTrackingResult*)hoge_L->At(p);
         //NValidPlane1 = xy1 -> GetNPlaneValid();
         Int_t TrackingID1  = xy1 -> GetTrackingID();
         //Double_t ex1 = xy1->GetSigma(0);
         //Double_t ea1 = xy1->GetSigma(1);
         art::TTrack * track1 = (art::TTrack*)xy1->GetTrack();
         x1 = track1->GetX();
         y1 = track1->GetY();
         a1 = track1->GetA();
         b1 = track1->GetB();
      }
      if (TrackingID1 != 1) continue;
      
      Double_t ranZ = ranZ_seed->Integer(300) -1200.;
      
      hXZ->Fill(x1+a1*ranZ, ranZ);
      hYZ->Fill(y1+b1*ranZ, ranZ);
      //printf(" Z, X = %.3f, %.3f \n", ranZ, x1-a1*ranZ);

	}

	cMWDC->cd(1);
	hXZ->Draw("colz");
	cMWDC->cd(2);
	hYZ->Draw("colz");
	
	
//############################################################################

	TF1* fit = new TF1("fit", "gaus(0)+gaus(3)", -45,20);
	fit->SetParLimits(2, 0, 30);
	fit->SetParLimits(5, 0, 30);
	
	Double_t para[6] ={4000, -20, 10, 6000, 0, 10};
	
	TCut ang = "TMath::Abs((p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()-86.5)<3";
	TH1F * temp = new TH1F("temp", "temp", 200, -100, 100);
	
	cMWDC->cd(4);
	for( Double_t zz = -1000; zz > -1060; zz -= 4){
		printf(" ---------- Z : %10.2f ", zz); 
		TString drawScript;
		drawScript.Form("smwdc_L.fTrack.fX+smwdc_L.fTrack.fA*%.1f>>temp", zz);
		tree->Draw(drawScript);
		fit->SetParameters(para);
		temp->Fit(fit, "RQ");
		fit->GetParameters(para);
		hSigma1->Fill(zz, para[5]);
		hSigma1->SetBinError(hSigma1->FindBin(zz),fit->GetParError(5));
		hSigma2->Fill(zz, para[3]);
		hSigma2->SetBinError(hSigma1->FindBin(zz),fit->GetParError(3));
		printf(" mean : %6.2f, sigma: %.2f | %6.1f, %.2f \n", para[4], para[5], para[1], para[2]);
	}
	
	cMWDC->cd(3);
	hSigma1->Draw();
	
	cMWDC->cd(4);
	//hSigma2->Draw();
	
      
}
