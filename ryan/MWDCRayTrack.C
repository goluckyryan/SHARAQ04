
void MWDCRayTrack() {

//############################################################################  
//   const char* rootfile="PrimaryData/phys23F.root"; 
//   const char* rootfile="ppAll_1105.root";
   const char* rootfile="23F_1212_nyoki_run23.root"; 
   
   TString mwdcName = "smwdc_S1";
   
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=1000;
   
   Double_t zRange[2] = {-200,300};
   
   Double_t ang = 13.65*TMath::DegToRad();
   

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
   Int_t Div[2] = {2,1};
   Int_t size = 600;
   TCanvas * cMWDC = new TCanvas("cMWDC", "MWDC Position Calibaration", 100, 50, size*Div[0], size*Div[1]);
   cMWDC->Divide(Div[0],Div[1]);

   gStyle->SetOptStat(0);
   
   TH2F* hXZ = new TH2F("hXZ", "Z and X", 200, -200, 500, zRange[1]- zRange[0], zRange[0], zRange[1]);
   hXZ->SetXTitle("X [mm]");
   hXZ->SetYTitle("Z [mm]");

	TH2F* hYZ = new TH2F("hYZ", "Z and Y", 200, -200, 200, zRange[1]- zRange[0], zRange[0], zRange[1]);
   hYZ->SetXTitle("Y [mm]");
   hYZ->SetYTitle("Z [mm]");
  

//############################################################################   
   TClonesArray  *hoge_MWDC;
   art::TGateArray * gate;
   tree->SetBranchAddress(mwdcName,&hoge_MWDC);
	tree->SetBranchAddress("gate",&gate);
   
  	TRandom *ranZ_seed = new TRandom();
   
//############################################################################  
   for( Int_t eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID);
      
      // initialization
      Double_t xx, aa, yy, bb;
      
//---------- Gate
		if( !gate->Test(5)) continue;
		
//---------Get SMWDC image, should be one 1 instance
      Int_t nHit = hoge_MWDC->GetEntriesFast();
      for( Int_t p = 0; p < nHit; p++){
         art::TMWDCTrackingResult * xyy = (art::TMWDCTrackingResult*)hoge_MWDC->At(p);
         //NValidPlane1 = xyy -> GetNPlaneValid();
         Int_t TrackingID1  = xyy -> GetTrackingID();
         //Double_t exx = xyy->GetSigma(0);
         //Double_t eaa = xyy->GetSigma(1);
         art::TTrack * track1 = (art::TTrack*)xyy->GetTrack();
         xx = track1->GetX();
         yy = track1->GetY();
         aa = track1->GetA();
         bb = track1->GetB();
      }
      if (TrackingID1 != 1) continue;
      
      Double_t ranZ = ranZ_seed->Integer(int(zRange[1]- zRange[0])) + zRange[0];
      
      hXZ->Fill(xx+aa*ranZ, ranZ);
	   hYZ->Fill(yy+bb*ranZ, ranZ);
	   //printf(" Z, X = %10.3f, %10.3f | x, a  = %10.3f, %10.3f \n", ranZ, xx-aa*ranZ, xx, aa);
	   
	}

	cMWDC->cd(1);
	hXZ->Draw("colz");
	
	TLine line;
	line.SetLineWidth(1);
	line.SetLineColor(2);
	line.DrawLine(-zRange[0]*TMath::Tan(ang), zRange[0], -zRange[1]*TMath::Tan(ang), zRange[1]);
	
	cMWDC->cd(2);
	hYZ->Draw("colz");
	
	
}
