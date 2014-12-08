
void NyokiQCali() {

//############################################################################  
//   const char* rootfile="PrimaryData/phys23F.root"; 
   const char* rootfile="23F_1106.root"; 
   
   Bool_t allentry  = 0;
   Int_t firstEntry = 0;
   Int_t nEntries=2000000;

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
   Int_t Div[2] = {3,1};
   TCanvas * cNyokiQ = new TCanvas("cNyokiQ", "Nyoki Q Calibaration", 2000, 50, 400*Div[0], 400*Div[1]);
   cNyokiQ->Divide(Div[0],Div[1]);

   gStyle->SetOptStat(0);
   /*
   TH2F* hQ01 = new TH2F("hQ01", "Nyoki Q,  0  1", 100, -500, 2000, 100, -500, 2000);
   TH2F* hQ12 = new TH2F("hQ12", "Nyoki Q,  1  2", 100, -500, 3500, 100, -500, 3500);
   TH2F* hQ23 = new TH2F("hQ23", "Nyoki Q,  2  3", 100, -500, 3500, 100, -500, 3500);
   TH2F* hQ34 = new TH2F("hQ34", "Nyoki Q,  3  4", 100, -500, 3500, 100, -500, 3500);
   TH2F* hQ45 = new TH2F("hQ45", "Nyoki Q,  4  5", 100, -500, 3500, 100,    0, 3500);
   TH2F* hQ56 = new TH2F("hQ56", "Nyoki Q,  5  6", 100,  100, 3500, 100,  100, 3500);
   TH2F* hQ67 = new TH2F("hQ67", "Nyoki Q,  6  7", 100,  100, 3500, 100,  100, 3500);
   */
   TH2F* hQ78 = new TH2F("hQ78", "Nyoki Q,  7  8", 100,  200, 4500, 100,  200, 4000);
   /*
   TH2F* hQ89 = new TH2F("hQ89", "Nyoki Q,  8  9", 100,  100, 3500, 100,  100, 3500);
   TH2F* hQ9a = new TH2F("hQ9a", "Nyoki Q,  9 10", 100,    0, 3500, 100,    0, 3500);
   TH2F* hQab = new TH2F("hQab", "Nyoki Q, 10 11", 100, -500, 3500, 100, -500, 3500);
   TH2F* hQbc = new TH2F("hQbc", "Nyoki Q, 11 12", 100, -500, 3500, 100, -500, 3500);
   TH2F* hQcd = new TH2F("hQcd", "Nyoki Q, 12 13", 100, -500, 3500, 100, -500, 3500);
   */
   
//############################################################################   
   TClonesArray  *hoge_nyoki;
   tree->SetBranchAddress("nyoki",&hoge_nyoki);
	//art::TTimingChargeData * data;

   Double_t charge[14];
   
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;
   
//############################################################################  
   for( Int_t eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID);
      
		//--------- initialization
   	for( Int_t i = 0; i < 14; i++){
   		charge[i] = TMath::QuietNaN();
   	}
		//--------- Get nyoki Q
      Int_t nHit = hoge_nyoki->GetEntriesFast();
      if( nHit < 2) continue;
      
      //printf(" nHit : %d \n", nHit);
      
      for( Int_t p = 0; p < nHit; p++){
         data = (art::TTimingChargeData*)hoge_nyoki->At(p);
         Int_t ID = data->GetID();
         charge[ID] = data->GetCharge();
      }
      
      //--------- Fill Hist
      /*
      if( !TMath::IsNaN(charge[0]) && !TMath::IsNaN(charge[1]) ){	hQ01->Fill(charge[0], charge[1]);}
      if( !TMath::IsNaN(charge[1]) && !TMath::IsNaN(charge[2]) ){	hQ12->Fill(charge[1], charge[2]);}
      if( !TMath::IsNaN(charge[2]) && !TMath::IsNaN(charge[3]) ){	hQ23->Fill(charge[2], charge[3]);}
      if( !TMath::IsNaN(charge[3]) && !TMath::IsNaN(charge[4]) ){	hQ34->Fill(charge[3], charge[4]);}
      if( !TMath::IsNaN(charge[4]) && !TMath::IsNaN(charge[5]) ){	hQ45->Fill(charge[4], charge[5]);}
      if( !TMath::IsNaN(charge[5]) && !TMath::IsNaN(charge[6]) ){	hQ56->Fill(charge[5], charge[6]);}
      if( !TMath::IsNaN(charge[6]) && !TMath::IsNaN(charge[7]) ){	hQ67->Fill(charge[6], charge[7]);}
      */
      if( !TMath::IsNaN(charge[7]) && !TMath::IsNaN(charge[8]) ){	
      	if( TMath::Abs(charge[7] - charge[8]) < 500 ){ 
      		hQ78->Fill(charge[7], 0.963*charge[8]+51.);
      	}
		}
      /*
      if( !TMath::IsNaN(charge[8]) && !TMath::IsNaN(charge[9]) ){	hQ89->Fill(charge[8], charge[9]);}
      if( !TMath::IsNaN(charge[9]) && !TMath::IsNaN(charge[10]) ){	hQ9a->Fill(charge[9], charge[10]);}
      if( !TMath::IsNaN(charge[10]) && !TMath::IsNaN(charge[11]) ){	hQab->Fill(charge[10], charge[11]);}
      if( !TMath::IsNaN(charge[11]) && !TMath::IsNaN(charge[12]) ){	hQbc->Fill(charge[11], charge[12]);}
      if( !TMath::IsNaN(charge[12]) && !TMath::IsNaN(charge[13]) ){	hQcd->Fill(charge[12], charge[13]);}	
      */
      
      	//printf(" nyoki-7, nyoki-8 = %.3f, %.3f \n", charge[7], charge[8]);

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
	
	/*
	cNyokiQ->cd(1); hQ01->Draw("colz");
	cNyokiQ->cd(2); hQ12->Draw("colz");
	cNyokiQ->cd(3); hQ23->Draw("colz");
	cNyokiQ->cd(4); hQ34->Draw("colz");
	cNyokiQ->cd(5); hQ45->Draw("colz");
	cNyokiQ->cd(6); hQ56->Draw("colz");
	cNyokiQ->cd(7); hQ67->Draw("colz");
	cNyokiQ->cd(8); hQ78->Draw("colz");
	cNyokiQ->cd(9); hQ89->Draw("colz");
	cNyokiQ->cd(10); hQ9a->Draw("colz");
	cNyokiQ->cd(11); hQab->Draw("colz");
	cNyokiQ->cd(12); hQbc->Draw("colz");
	cNyokiQ->cd(13); hQcd->Draw("colz");
	*/
	
	cNyokiQ->cd(1);
	hQ78->Draw("colz");
	cNyokiQ->cd(2);
	hQ78->ProfileY("_pfy")->Draw();
	hQ78_pfy->Fit("pol1", "", "", 500, 3500);
	cNyokiQ->cd(3);
	hQ78->ProfileX("_pfx")->Draw();
	hQ78_pfx->Fit("pol1", "", "", 500, 3500);
	
	
//############################################################################
	
      
}
