
void NyokiQCali_single() {

//############################################################################  
//   const char* rootfile="PrimaryData/phys23F.root"; 
   const char* rootfile="23F_1117_nyoki.root"; 
   
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=    1000000;
   
   Int_t nyokiID[2] = {9,10}; // {x-axis, y-axis} 
   Int_t range[2] = {-500, 4500};
   Double_t fitRange[2] = {-500, 4500};
   Double_t gainA[2] = {1., 0}; // {slope, intercept} of x-axis
   Double_t gainB[2] = {1., 0}; // {slope, intercept} of y-axis
   Int_t Qdiff = 5000;

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
   printf("========= compare nyoki - %d, %d \n", nyokiID[0], nyokiID[1]);
//############################################################################  
   Int_t Div[2] = {3,1};
   TCanvas * cNyokiQ = new TCanvas("cNyokiQ", "Nyoki Q Calibaration", 2000, 50, 400*Div[0], 400*Div[1]);
   cNyokiQ->Divide(Div[0],Div[1]);

   gStyle->SetOptStat(0);

	TString hQabTitle;
	hQabTitle.Form("Nyoki Q, %d %d", nyokiID[0], nyokiID[1]);
   TH2F* hQab = new TH2F("hQ78", hQabTitle, 100, range[0], range[1], 100, range[0], range[1]);
	TString hQabX, hQabY;
	hQabX.Form("Nyoki-%d", nyokiID[0]);
	hQabY.Form("Nyoki-%d", nyokiID[1]);
   hQab->SetXTitle(hQabX);
   hQab->SetYTitle(hQabY);
//############################################################################   
   TClonesArray  *hoge_nyoki;
   tree->SetBranchAddress("nyoki",&hoge_nyoki);
	//art::TTimingChargeData * data;
   
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;
   
//############################################################################  
   for( Int_t eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID);
      
		//--------- initialization
   	Double_t Qa = TMath::QuietNaN();
   	Double_t Qb = TMath::QuietNaN();
   	Int_t Pass = 0;
   	
		//--------- Get nyoki Q
      Int_t nHit = hoge_nyoki->GetEntriesFast();
      if( nHit < 2) continue;
      
      //printf(" nHit : %d \n", nHit);
      
      for( Int_t p = 0; p < nHit; p++){
         data = (art::TTimingChargeData*)hoge_nyoki->At(p);
         Int_t ID = data->GetID();
         if ( ID == nyokiID[0] ) {
         	Qa = gainA[0]*data->GetCharge()+gainA[1];
         	Pass ++ ;
      	}
         if ( ID == nyokiID[1] ) {
         	Qb = gainB[0]*data->GetCharge()+gainB[1];
         	Pass ++ ;
      	}
      }
      
      //--------- Fill Hist
      if( Pass == 2 && TMath::Abs(Qa - Qb) < Qdiff ){ 
      		hQab->Fill(Qa, Qb);
		}else{
			continue;
		}

		//------------------
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
	
	
	cNyokiQ->cd(1);
	hQab->Draw("colz");
	cNyokiQ->cd(2);
	hQab->ProfileY("hQab_pfy")->Draw();
	hQab_pfy->Fit("pol1", "", "", fitRange[0], fitRange[1]);
	cNyokiQ->cd(3);
	hQab->ProfileX("hQab_pfx")->Draw();
	hQab_pfx->Fit("pol1", "", "", fitRange[0], fitRange[1]);
	
	
//############################################################################
	
      
}
