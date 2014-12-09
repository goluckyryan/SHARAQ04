{

	gROOT->Reset();
	gROOT->ProcessLine(".!date");
	gStyle->SetOptStat(0);

	//TFile *f1 = new TFile ("23F_1201_nyoki_run23.root"); 
	TFile *f1 = new TFile ("23F_1204_nyoki_run2425.root"); 

	Int_t nyokiID = 7;

	Double_t Qgain=1, Qoffset=0;

	switch(nyokiID){
		case 0:  Qgain = 0.17; Qoffset = 522; break;
		case 1:  Qgain = 0.48; Qoffset = 319; break;
		case 2:  Qgain = 0.33; Qoffset = 429; break;
		case 3:  Qgain = 0.36; Qoffset = 443; break;
		case 4:  Qgain = 0.34; Qoffset = 441; break;
		case 5:  Qgain = 0.34; Qoffset = 566; break;
		case 6:  Qgain = 0.36; Qoffset = 486; break;
		case 7:  Qgain = 0.38; Qoffset = 581; break;
		case 8:  Qgain = 0.36; Qoffset = 439; break;
		case 9:  Qgain = 0.35; Qoffset = 577; break;
		case 10: Qgain = 0.22; Qoffset = 585; break;
	}
	
	printf("Qgain:%4.2f, Qoffset:%6.0f \n", Qgain, Qoffset);

	//=================================
	TClonesArray *hoge_FH9, *hoge_V775, *hoge_nyoki, *hoge_tofD1;
	art::TGateArray * gate;
   art::TCoinRegData *coinReg;
	TTree *tree = (TTree*)f1->Get("tree");
	Int_t totnumEntry = tree->GetEntries();
	
	printf(" --------------------- total entry = %d \n", totnumEntry);
	tree->SetBranchStatus("gate",1);
	tree->SetBranchStatus("coinReg",1);
	tree->SetBranchStatus("plaV775",1);
	tree->SetBranchStatus("plaV1190_FH9",1);
	tree->SetBranchStatus("nyoki",1);
	tree->SetBranchStatus("tof_D1",1);
	 
	tree->SetBranchAddress("coinReg",&coinReg); 
	tree->SetBranchAddress("gate",&gate); 
	tree->SetBranchAddress("plaV775",&hoge_V775);
	tree->SetBranchAddress("plaV1190_FH9",&hoge_FH9); 
	tree->SetBranchAddress("nyoki",&hoge_nyoki); 
	tree->SetBranchAddress("tof_D1",&hoge_tofD1); 
	
	//=====================================
	Int_t Div[2] ={4,1};
	Int_t size = 400;
	TCanvas * cScript= new TCanvas("cScript", "cScript", 2000, 100,Div[0]*size,Div[1]*size);
	cScript->Divide(Div[0],Div[1]);

	TString hTitle;	
	TH2F* hFH9S0DQ = new TH2F("hFH9S0DQ", "Q(FH9) vs Q(S0D)", 200, 0, 4000, 200, 5000, 6200); 
	hFH9S0DQ->SetXTitle("Q(S0D)");
	hFH9S0DQ->SetYTitle("Q(FH9)");
	
	hTitle.Form("Q(Nyoki-%d) vs Q(S0D)", nyokiID);
	Int_t Qmax = 2200;
	//if( Qgain !=1 ) Qmax = 2500;
	TH2F* hS0DNyokiQ = new TH2F("hS0DNyokiQ", hTitle, 200, 0, 4000, 200, 500, Qmax); 
	hS0DNyokiQ->SetXTitle("Q(S0D)");
	hS0DNyokiQ->SetYTitle("Q(Nyoki)");
	
	hTitle.Form("PID(Nyoki-%d)",nyokiID);
	TH2F* hNyokiPID = new TH2F("hNyokiPID", hTitle, 200, 30, 40, 200, 500, 2200); 
	hNyokiPID->SetXTitle("tof(S0D-Nyoki)");
	hNyokiPID->SetYTitle("Q(Nyoki)");
	
	TH2F* hFH9NyokiQ = new TH2F("hFH9NyokiQ", "Q(FH9) vs Q(Nyoki)", 200, 5000, 6200, 200, 500, 2200);
	hFH9NyokiQ->SetXTitle("Q(FH9)");
	hFH9NyokiQ->SetYTitle("Q(nyoki)");
	
	TH2F* hFH9SlewV775 = new TH2F("hFH9SlewV775", "Q(FH9) vs T(FH9,v775)", 200, -206, -198, 200, 4900, 6200);
	
	TH2F* hS0DSlew = new TH2F("hS0DSlew", "Q(S0D) vs T(S0D,v775)", 200, -276, -260, 200, 0, 4000);
	
	TH2F* hS0DPID = new TH2F("hS0DPID", "Q(S0D) vs ToF(FH9-S0D,v775)", 200, -76, -60, 200, 600, 2300);
	
	TH2F* hFH9PID = new TH2F("hFH9PID", "Q(FH9) vs ToF(F3-FH9,v775)", 200, -350, -270, 200, 4900, 6200);
	
	//======================================
	for( Int_t eventID = 0; eventID< 1000000; eventID ++){
		tree->GetEntry(eventID); 
		
		//if( coinReg->Test(1) != 1) continue;
		//if ( gate->Test(6) != 1) continue; 
		//if ( gate->Test(8) == 1) continue; 
		//if ( gate->Test(0) != 1) continue; 
		//if ( gate->Test(15) != 1) continue;
		
		Double_t QS0D = -10000;
		Double_t tFH9 = -10000;
		Double_t tS0D = -10000;
		Double_t tF3 = -10000;
		
		Int_t nHit = hoge_V775->GetEntriesFast();
		for(Int_t p = 0; p < nHit; p++){
			art::TTwoSidedPlasticData* data1 = (art::TTwoSidedPlasticData*)hoge_V775->At(p) ;
			Int_t ID = data1->GetID() ;
			if( ID == 4 ) {
				QS0D    = data1->GetCharge();
				tS0D    = data1->GetTiming();
				hS0DSlew->Fill(tS0D, QS0D);
			}else if(ID == 3){
				tFH9    = data1->GetTiming();
			}else if(ID == 2){
				tF3 = data1->GetTiming();
			}else{
				continue;
			}
		}
		if( tFH9 == -10000) continue;
		
		hS0DPID->Fill(tS0D-tFH9,QS0D);
		
		Double_t nyokiQ;
		
		Int_t nHit = hoge_nyoki->GetEntriesFast();
		Int_t nHit2 = hoge_tofD1->GetEntriesFast();
		//if ( nHit == 0 ) continue;
		for(Int_t p = 0; p < nHit; p++){
			art::TTwoSidedPlasticData* data1 = (art::TTwoSidedPlasticData*)hoge_nyoki->At(p) ;
			if( data1->GetID() != nyokiID ) continue ;
			nyokiQ = data1->GetCharge();
			hS0DNyokiQ->Fill(QS0D, nyokiQ);//*Qgain + Qoffset);
			if( nHit == nHit2) {
				art::TTimeDifference* data2 = (art::TTimeDifference *)hoge_tofD1->At(p) ;
				hNyokiPID->Fill(data2->GetTiming(), nyokiQ); 
			}
		}
				
		
		Int_t nHit = hoge_FH9->GetEntriesFast();
		if ( nHit >=2) continue;
		for(Int_t p = 0; p < nHit; p++){
			art::TTwoSidedPlasticData* data1 = (art::TTwoSidedPlasticData*)hoge_FH9->At(p) ;
			Double_t QFH9 = data1->GetCharge();
			hFH9S0DQ->Fill( QS0D, QFH9);
			//printf("nyokiQ:%4.0f, FH9 Q:%4.0f\n", nyokiQ, data1->GetCharge());		
			hFH9NyokiQ->Fill(QFH9,  nyokiQ);
			hFH9SlewV775->Fill(tFH9, QFH9);
			hFH9PID->Fill(tFH9-tF3, QFH9);
		}
		

	}
	
	cScript->cd(1);
	//hFH9PID->Draw("colz");
	//hFH9SlewV775->Draw("colz");
	//hFH9S0DQ->Draw("colz");
	
	//cScript->cd(2);
	//hS0DSlew->Draw("colz");
	hS0DNyokiQ->Draw("colz");
	TLine line;
	line.DrawLine( 0, 0, Qmax, Qmax);
	
	//cScript->cd(2);
	//hS0DPID->Draw("colz");
	
	cScript->cd(2);
	hNyokiPID->Draw("colz");
	
	
	cScript->cd(3);
	hS0DPID->Draw("colz");
	/*hS0DNyokiQ->Draw("colz");
	
	TLine line;
	line.DrawLine( Qoffset, 0, Qmax*Qgain+Qoffset , Qmax);
	/**/
	cScript->cd(4);
	hFH9PID->Draw("colz");
  
	/**/
}
