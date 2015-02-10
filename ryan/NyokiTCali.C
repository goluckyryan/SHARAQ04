//The value at plot2 are the offset require


void NyokiTCali(Int_t nyokiIDa = 7, Int_t nyokiIDb = 8, Double_t a_adj=0, Double_t b_adj=1) {

//############################################################################  
//   const char* rootfile="PrimaryData/phys23F.root"; 
   const char* rootfile="23F_run24_nyokiCali.root"; 
   
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=2000000;
   
   Int_t nyokiID[2] = {nyokiIDa, nyokiIDb};
   
   Int_t nBin = 100;
   Double_t diffRange[2] = {-3,3};
   Double_t nyokiRange[2] = {-260, -230};

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
	if ( gROOT->FindObject("cNyokiQ")){
		delete cNyokiQ;
	}
	
	if( gROOT->FindObject("hTab")){
		delete hTab;
		delete hTdiff;
	}
 
   Int_t Div[2] = {2,1};
   TCanvas * cNyokiQ = new TCanvas("cNyokiQ", "Nyoki Q Calibaration", 2000, 50, 400*Div[0], 400*Div[1]);
   cNyokiQ->Divide(Div[0],Div[1]);

   gStyle->SetOptStat(0);
   TString hTitle;
   hTitle.Form("Hodo time, %d vs %d {%s}", nyokiID[0], nyokiID[1], rootfile);
   TH2F* hTab = new TH2F("hTab", hTitle, 100, nyokiRange[0], nyokiRange[1], 100, nyokiRange[0], nyokiRange[1]);
   TString xTitle, yTitle;
   xTitle.Form("Hodo %d [ns]", nyokiID[0]);
   yTitle.Form("Hodo %d [ns]", nyokiID[1]);
	hTab->SetXTitle(xTitle);
	hTab->SetYTitle(yTitle);
	
	hTitle.Form("Hodo Time (%d - %d)", nyokiID[1], nyokiID[0]);
	TH1F* hTdiff = new TH1F("hTdiff", hTitle, nBin, diffRange[0], diffRange[1]);
	hTdiff->SetXTitle(" [ns]");
	
   
//############################################################################   
   tree->SetBranchStatus("*",0);
   //tree->SetBranchStatus("plaV775",1);
   tree->SetBranchStatus("nyoki",1);

   TClonesArray  *hoge_nyoki, *hoge_v775 = 0;
   tree->SetBranchAddress("nyoki",&hoge_nyoki);
   //tree->SetBranchAddress("plaV775",&hoge_v775);

	//art::TTimingChargeData * data;

   Double_t timing[14];
   Double_t S0Dt; 
   
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;
   
//############################################################################  
   for( Int_t eventID = firstEntry; eventID < endEntry; eventID ++){
      delete hoge_v775; hoge_v775=0;
      
      tree->GetEntry(eventID,0);
      
   	//--------- Get S0D timing
		/*S0Dt = TMath::QuietNaN();
		Bool_t hitFlag = 0;
   	Int_t nHit = hoge_v775 -> GetEntriesFast();
   	//printf(" ----------- nHit: %d \n", nHit);
      for( Int_t p = 0; p < nHit; p++){
         Int_t hitID = ((art::TTwoSidedPlasticData*) hoge_v775->At(p))->GetID();
         if ( hitID != 4 ) continue;
         S0Dt = ((art::TTwoSidedPlasticData*) hoge_v775->At(p))->GetTiming();
         hitFlag = 1;
         //printf("S0DPL: %f \n", s0DQ);
      }       
      if( hitFlag == 0 ) continue; 
      /**/
      
   
		//--------- Get nyoki T
      Int_t nHit = hoge_nyoki->GetEntriesFast();
      if( nHit < 2) continue;
      
      //printf(" nHit : %d \n", nHit);
      for( Int_t i = 0; i < 14; i++){
   		timing[i] = TMath::QuietNaN();
   	}
      for( Int_t p = 0; p < nHit; p++){
         Int_t ID = ((art::TTimingChargeData*)hoge_nyoki->At(p))->GetID();
         timing[ID] = ((art::TTimingChargeData*)hoge_nyoki->At(p))->GetTiming();
      }
      if( TMath::IsNaN(timing[nyokiID[0]]) || TMath::IsNaN(timing[nyokiID[1]]) ) continue;
      
      //__________ Check tof;
      //printf(" %f - %f = %f\n", timing[nyokiID[0]],  S0Dt, timing[nyokiID[0]] - S0Dt);
      //if( abs(timing[nyokiID[0]] - S0Dt - 35)>10) continue;
      if( abs(timing[nyokiID[0]] - (nyokiRange[0] + nyokiRange[1])/2)>(nyokiRange[1] - nyokiRange[0])/2) continue;
      if( abs(timing[nyokiID[1]] - (nyokiRange[0] + nyokiRange[1])/2)>(nyokiRange[1] - nyokiRange[0])/2) continue;
      //--------- Fill Hist      	
		hTab->Fill(b_adj*timing[nyokiID[0]]+a_adj, timing[nyokiID[1]]);
		hTdiff->Fill(timing[nyokiID[1]] - (b_adj*timing[nyokiID[0]]+a_adj) );
   	
      	//printf(" nyoki-7, nyoki-8 = %.3f, %.3f \n", timing[7], timing[8]);

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
	
	//==================================================
	TString textStr;
	TLatex text;
	text.SetNDC(1);
	text.SetTextSize(0.035);
	
	TF1* fit = new TF1("fit", "[0]+[1]*x", nyokiRange[0], nyokiRange[1]);
	
	cNyokiQ->cd(1);
	hTab->Draw("colz");
	TLine line;
	line.DrawLine(nyokiRange[0], nyokiRange[0], nyokiRange[1], nyokiRange[1]);
	
	
	cNyokiQ->cd(2);
	hTdiff->Draw();
	
	/*
	hTab->ProfileY("_pfy")->Draw();
	hTab_pfy->SetTitle("ProfileY");
	hTab_pfy->SetMinimum(nyokiRange[0]);
	hTab_pfy->SetMaximum(nyokiRange[1]);
	
	hTab_pfy->Fit(fit, "R" );
	Double_t a = fit->GetParameter(0);
	Double_t b = fit->GetParameter(1);
	
	Double_t err_a = fit->GetParError(0);
	Double_t err_b = fit->GetParError(1);
	
	textStr.Form("inte.: %5.3f (%5.3f)", a, err_a); text.DrawLatex(0.5,0.40, textStr);	
	textStr.Form("slope: %5.3f (%5.3f)", b, err_b); text.DrawLatex(0.5,0.35, textStr);
	
	/*
	cNyokiQ->cd(3);
	hTab->ProfileX("_pfx")->Draw();
	hTab_pfx->SetTitle("ProfileX");
	hTab_pfx->SetMinimum(nyokiRange[0]);
	hTab_pfx->SetMaximum(nyokiRange[1]);
	
	hTab_pfx->Fit(fit, "R" );
	Double_t a = fit->GetParameter(0);
	Double_t b = fit->GetParameter(1);
	
	Double_t err_a = fit->GetParError(0);
	Double_t err_b = fit->GetParError(1);
	
	textStr.Form("inte.: %5.3f (%5.3f)", a, err_a); text.DrawLatex(0.5,0.40, textStr);	
	textStr.Form("slope: %5.3f (%5.3f)", b, err_b); text.DrawLatex(0.5,0.35, textStr);
	*/
	
//############################################################################
	
      
}
