
void NyokiQCali(Int_t nyokiIDa = 7, Int_t nyokiIDb = 8, Double_t a_adj=0, Double_t b_adj=1) {

//############################################################################  
//   const char* rootfile="PrimaryData/phys23F.root"; 
   const char* rootfile="test.root"; 
   
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=2000000;
   
   Int_t nyokiID[2] = {nyokiIDa, nyokiIDb};
   
   Double_t nyokiRange[2] = {700, 2200};

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
	
	if( gROOT->FindObject("hQab")){
		delete hQab;
		delete hDiff;
		delete hRatio;
	}
 
   Int_t Div[2] = {3,2};
   TCanvas * cNyokiQ = new TCanvas("cNyokiQ", "Nyoki Q Calibaration", 2000, 50, 400*Div[0], 400*Div[1]);
   cNyokiQ->Divide(Div[0],Div[1]);

   //gStyle->SetOptStat(0);
   TString hTitle;
   hTitle.Form("Nyoki Q, %d vs %d {%s}", nyokiID[0], nyokiID[1], rootfile);
   TH2F* hQab = new TH2F("hQab", hTitle, 100, nyokiRange[0], nyokiRange[1], 100, nyokiRange[0], nyokiRange[1]);
   TString xTitle, yTitle;
   xTitle.Form("nyoki %d", nyokiID[0]);
   yTitle.Form("nyoki %d", nyokiID[1]);
	hQab->SetXTitle(xTitle);
	hQab->SetYTitle(yTitle);
	
	hTitle.Form("Nyoki Q diff, %d - %d", nyokiID[1], nyokiID[0]);
	TH1F* hDiff = new TH1F("hDiff", hTitle, 100,  -250, 250);
   
   hTitle.Form("Nyoki Q ratio, %d / %d", nyokiID[1], nyokiID[0]);
	TH1F* hRatio = new TH1F("hRatio", hTitle, 100,  0, 2);
	
//############################################################################   
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("nyoki",1);

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
      tree->GetEntry(eventID,0);
      
		//--------- initialization
   	for( Int_t i = 0; i < 14; i++){
   		charge[i] = TMath::QuietNaN();
   	}
		//--------- Get nyoki Q
      Int_t nHit = hoge_nyoki->GetEntriesFast();
      if( nHit < 2) continue;
      
      //printf(" nHit : %d \n", nHit);
      
      //__________________
      for( Int_t p = 0; p < nHit; p++){
         Int_t ID = ((art::TTimingChargeData*)hoge_nyoki->At(p))->GetID();
         charge[ID] = ((art::TTimingChargeData*)hoge_nyoki->At(p))->GetCharge();
      }  
      
      //--------- Fill Hist
      if( TMath::IsNaN(charge[nyokiID[0]]) || TMath::IsNaN(charge[nyokiID[1]]) ) continue;
      
      if( charge[nyokiID[0]]<nyokiRange[0] || charge[nyokiID[0]]>nyokiRange[1] ) continue;
      
      if( charge[nyokiID[1]]<nyokiRange[0] || charge[nyokiID[1]]>nyokiRange[1] ) continue;
      	
   	if( TMath::Abs(charge[nyokiID[0]] - charge[nyokiID[1]]) > 300 ) continue;
   	 
		hQab->Fill(b_adj*charge[nyokiID[0]]+a_adj, charge[nyokiID[1]]);

      //printf(" nyoki-7, nyoki-8 = %.3f, %.3f \n", charge[7], charge[8]);
      	
      hDiff->Fill(charge[nyokiID[1]] - (b_adj*charge[nyokiID[0]]+a_adj) );
		
      hRatio->Fill(charge[nyokiID[1]] /( b_adj*charge[nyokiID[0]]+a_adj ));

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
	hQab->Draw("colz");
	TLine line;
	line.DrawLine(nyokiRange[0], nyokiRange[0], nyokiRange[1], nyokiRange[1]);
	
	cNyokiQ->cd(2);
	hQab->ProfileY("_pfy")->Draw();
	hQab_pfy->SetTitle("ProfileY");
	
	hQab_pfy->Fit(fit, "R" );
	Double_t a = fit->GetParameter(0);
	Double_t b = fit->GetParameter(1);
	
	Double_t err_a = fit->GetParError(0);
	Double_t err_b = fit->GetParError(1);
	
	textStr.Form("inte.: %5.3f (%5.3f)", a, err_a); text.DrawLatex(0.5,0.40, textStr);	
	textStr.Form("slope: %5.3f (%5.3f)", b, err_b); text.DrawLatex(0.5,0.35, textStr);
	
	cNyokiQ->cd(3);
	hQab->ProfileX("_pfx")->Draw();
	hQab_pfx->SetTitle("ProfileX");
	
	hQab_pfx->Fit(fit, "R" );
	Double_t a = fit->GetParameter(0);
	Double_t b = fit->GetParameter(1);
	
	Double_t err_a = fit->GetParError(0);
	Double_t err_b = fit->GetParError(1);
	
	textStr.Form("inte.: %5.3f (%5.3f)", a, err_a); text.DrawLatex(0.5,0.40, textStr);	
	textStr.Form("slope: %5.3f (%5.3f)", b, err_b); text.DrawLatex(0.5,0.35, textStr);
	
	cNyokiQ->cd(4);
	hDiff->Draw();
	
	cNyokiQ->cd(5);
	hRatio->Draw();
	
//############################################################################
	
      
}
