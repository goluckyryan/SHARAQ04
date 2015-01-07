#include "constant.h"

void MWDC_check() {

   const char* rootfile="23F_1226_nyoki_run23_nogate.root";
   //const char* rootfile="23F_1225_nyoki_run23.root";
//   const char* rootfile="23F_1204_nyoki_run2425.root";

	Int_t nyokiIDGate[2] = {0,10};

//#####################################################

   TClonesArray *hoge_nyoki, *hoge_mwdc;

   TClonesArray *hoge_x1,*hoge_x2,*hoge_u1,*hoge_u2,*hoge_v1,*hoge_v2;

   TFile *f = new TFile(rootfile,"read");
   TTree *pid = (TTree*)f->Get("tree");
   
   Int_t totnumEntry = pid->GetEntries();
   pid->SetBranchStatus("nyoki",1);
   pid->SetBranchStatus("smwdc_S1",1);
   pid->SetBranchStatus("smwdc_S1_x1",1);
   pid->SetBranchStatus("smwdc_S1_x2",1);
   pid->SetBranchStatus("smwdc_S1_u1",1);
   pid->SetBranchStatus("smwdc_S1_u2",1);
   pid->SetBranchStatus("smwdc_S1_v1",1);
   pid->SetBranchStatus("smwdc_S1_v2",1);
   

   pid->SetBranchAddress("nyoki",&hoge_nyoki);
   pid->SetBranchAddress("smwdc_S1",&hoge_mwdc);
   pid->SetBranchAddress("smwdc_S1_x1",&hoge_x1);
   pid->SetBranchAddress("smwdc_S1_x2",&hoge_x2);
   pid->SetBranchAddress("smwdc_S1_u1",&hoge_u1);
   pid->SetBranchAddress("smwdc_S1_u2",&hoge_u2);
   pid->SetBranchAddress("smwdc_S1_v1",&hoge_v1);
   pid->SetBranchAddress("smwdc_S1_v2",&hoge_v2);
   
   printf("File:%s ==== TotnumEntry:%d\n" , rootfile , totnumEntry);
   
//#####################################################

   TCanvas* cPID = new TCanvas("cPid", "PID", 2000, 0, 500,500);
   
   TH2F* h1 = new TH2F("h1", "mean multiplicity vs s1x", 400, 500, 2200, 400 , 0, 1500); 
   
//#############################################################   
   for( Int_t eventID = 0; eventID < totnumEntry; eventID+=1){
      pid->GetEntry(eventID); 
      
      
      Double_t s1x = -50000;
      Double_t s1a = -500;
      Double_t s1y = -50000;
      Double_t s1b = -500;
      
      Double_t s1xe = -1;
      Double_t s1ae = -1;
      Double_t s1ye = -1;
      Double_t s1be = -1;
      
      Double_t SSR = -1;
      
      Int_t wire[6];
      Double_t DL[6];
      Double_t Res[6];
      Double_t QQ[6];
      for( Int_t i = 0; i < 6; i++){
      	wire[i] = -1;
      	DL[i] = -1;
      	Res[i] = -1;
      	QQ[i] = -1;
      }
      
      
      //____________Get from nyoki
      Int_t nHit1 =hoge_nyoki->GetEntriesFast();
      if( nHit1 >=2 ) continue;
      Bool_t nyokiPass = 0;
      Int_t* nyokiID = new Int_t[nHit1];
      Int_t* nyokiQQ = new Int_t[nHit1];
      for(Int_t p = 0; p < nHit1; p++){
         data1 = (art::TTwoSidedPlasticData*)hoge_nyoki->At(p) ;
         nyokiID[p]  = data1->GetID();
         nyokiQQ[p]  = data1->GetCharge();
         if( nyokiIDGate[0] <=nyokiID[p] && nyokiID[p] <= nyokiIDGate[1] ) nyokiPass= 1; 
      }
      
      if( !nyokiPass ) continue;
      
		//_____________Get SMWDC-S1
		Int_t nHit = hoge_mwdc->GetEntriesFast();
		Bool_t mwdcPass = 0;
		if(nHit == 0 ) continue;
		for( Int_t p = 0; p < nHit; p++){
		   art::TMWDCTrackingResult * xyS1 = (art::TMWDCTrackingResult*)hoge_mwdc->At(p);
		   mwdcPass = xyS1->IsGood();
		   art::TTrack * trackS1 = (art::TTrack*)xyS1->GetTrack();
		   s1x = trackS1->GetX(); // (mm)
		   s1a = trackS1->GetA(); // (rad)
		   s1y = trackS1->GetY(); // (mm)
		   s1b = trackS1->GetB(); // (rad)
			s1xe = xyS1->GetSigma(0);
			s1ae = xyS1->GetSigma(1);
			s1ye = xyS1->GetSigma(2);
			s1be = xyS1->GetSigma(3);
			SSR = xyS1->GetSSR();
		   for (Int_t i = 0; i < 6; i++){
		   	wire[i] = xyS1->GetWireIDAdopted(i);
		   	DL[i] = xyS1->GetDriftLengthOriginal(i);
		   	Res[i] = xyS1->GetResidual(i);
		   	QQ[i] = xyS1->GetChargeAdopted(i);
	   	}
		}      
		if( mwdcPass == 0 ) continue;
		
	   //if( !(20 < s1y && s1y < 30) ) continue;
	   //if( !(-0.03 < s1b && s1b < 0.03) ) continue;
	   //if( (-50 < s1x && s1x < 50) ) continue;
		
		//____________Get x1
		Int_t nHitx1 = hoge_x1->GetEntriesFast();
		Int_t*  x1Wire = new Int_t[nHitx1];
		Double_t*  x1DL = new Double_t[nHitx1];
		Double_t*  x1Q = new Double_t[nHitx1];
		for( Int_t p = 0; p < nHitx1; p++){
			art::TMWDCHitData* hit = (art::TMWDCHitData*) hoge_x1->At(p);
			x1Q[p] = hit->GetCharge();	
			x1Wire[p] = hit->GetID();
			x1DL[p] = hit->GetDriftLength();			
		}
		
		//____________Get x2
		Int_t nHitx2 = hoge_x2->GetEntriesFast();
		Int_t*  x2Wire = new Int_t[nHitx2];
		Double_t*  x2DL = new Double_t[nHitx2];
		Double_t*  x2Q = new Double_t[nHitx2];
		for( Int_t p = 0; p < nHitx2; p++){
			art::TMWDCHitData* hit = (art::TMWDCHitData*) hoge_x2->At(p);
			x2Wire[p] = hit->GetID();
			x2DL[p] = hit->GetDriftLength();
			x2Q[p] = hit->GetCharge();	
		}	
		
		//____________Get u1
		Int_t nHitu1 = hoge_u1->GetEntriesFast();
		Int_t*  u1Wire = new Int_t[nHitu1];
		Double_t*  u1DL = new Double_t[nHitu1];
		Double_t*  u1Q = new Double_t[nHitu1];
		for( Int_t p = 0; p < nHitu1; p++){
			art::TMWDCHitData* hit = (art::TMWDCHitData*) hoge_u1->At(p);
			u1Wire[p] = hit->GetID();
			u1DL[p] = hit->GetDriftLength();
			u1Q[p] = hit->GetCharge();	
		}
		
		//____________Get u2
		Int_t nHitu2 = hoge_u2->GetEntriesFast();
		Int_t*  u2Wire = new Int_t[nHitu2];
		Double_t*  u2DL = new Double_t[nHitu2];
		Double_t*  u2Q = new Double_t[nHitu2];
		for( Int_t p = 0; p < nHitu2; p++){
			art::TMWDCHitData* hit = (art::TMWDCHitData*) hoge_u2->At(p);
			u2Wire[p] = hit->GetID();
			u2DL[p] = hit->GetDriftLength();
			u2Q[p] = hit->GetCharge();	
		}

		//____________Get v1
		Int_t nHitv1 = hoge_v1->GetEntriesFast();
		Int_t*  v1Wire = new Int_t[nHitv1];
		Double_t*  v1DL = new Double_t[nHitv1];
		Double_t*  v1Q = new Double_t[nHitv1];
		for( Int_t p = 0; p < nHitv1; p++){
			art::TMWDCHitData* hit = (art::TMWDCHitData*) hoge_v1->At(p);
			v1Wire[p] = hit->GetID();
			v1DL[p] = hit->GetDriftLength();
			v1Q[p] = hit->GetCharge();	
		}
		
		//____________Get v2
		Int_t nHitv2 = hoge_v2->GetEntriesFast();
		Int_t*  v2Wire = new Int_t[nHitv2];
		Double_t*  v2DL = new Double_t[nHitv2];
		Double_t*  v2Q = new Double_t[nHitv2];
		for( Int_t p = 0; p < nHitv2; p++){
			art::TMWDCHitData* hit = (art::TMWDCHitData*) hoge_v2->At(p);
			v2Wire[p] = hit->GetID();
			v2DL[p] = hit->GetDriftLength();
			v2Q[p] = hit->GetCharge();	
		}
		
		
		
		//h1->Fill(s1x, (nHitx1+nHitx2+nHitu1+nHitu2+nHitv1+nHitv2)/6);
		//h1->Fill(nyokiQQ[0],TMath::RMS(6, QQ));
		h1->Fill(nyokiQQ[0],TMath::Mean(6, QQ));
		//h1->Fill(s1x,nyokiID[0]);	

/*      
      printf("=================================================== %d \n", eventID);
      for( Int_t i = 0; i < nHit1; i ++){printf(" %d", nyokiID[i]);} printf("\n");
      printf(" x:%8.2f(%6.2f) mm, a:%8.2f(%6.2f) mrad, y:%8.2f(%6.2f) mm, b:%8.2f(%6.2f) mrad \n",  s1x, s1xe, s1a*1000, s1ae*1000, s1y, s1ye, s1b*1000, s1be*1000);
      
      printf("SSR: %.3f \n", SSR);
      
      for( Int_t i = 0; i < 6; i++){
      	printf(" %d: wire ID:%d, DL:%4.1f, Res:%4.1f, Q:%5.1f\n", i,  wire[i], DL[i], Res[i], QQ[i]); 
      }
      
      printf("---------------------------\n");
      printf(" x1: "); for( Int_t i = 0; i < nHitx1; i++) {if(x1Q[i] >350 ) printf(" %3d[%4.1f]", x1Wire[i], x1DL[i]);} printf("\n");
      printf(" x2: "); for( Int_t i = 0; i < nHitx2; i++) {if(x2Q[i] >350 ) printf(" %3d[%4.1f]", x2Wire[i], x2DL[i]);} printf("\n");
      
      printf(" u1: "); for( Int_t i = 0; i < nHitu1; i++) {if(u1Q[i] >350 ) printf(" %3d[%4.1f]", u1Wire[i], u1DL[i]);} printf("\n");
      printf(" u2: "); for( Int_t i = 0; i < nHitu2; i++) {if(u2Q[i] >350 ) printf(" %3d[%4.1f]", u2Wire[i], u2DL[i]);} printf("\n");
      
      printf(" v1: "); for( Int_t i = 0; i < nHitv1; i++) {if(v1Q[i] >350 ) printf(" %3d[%4.1f]", v1Wire[i], v1DL[i]);} printf("\n");
      printf(" v2: "); for( Int_t i = 0; i < nHitv2; i++) {if(v2Q[i] >350 ) printf(" %3d[%4.1f]", v2Wire[i], v2DL[i]);} printf("\n");
      
		std::cout << "";
		std::cin.get();
		
		/**/
		  
		delete nyokiID;  
		delete x1Wire;
		delete x1DL;
		delete x1Q;
		delete x2Wire;
		delete x2DL;
		delete x2Q;
		
		delete u1Wire;
		delete u1DL;
		delete u1Q;
		delete u2Wire;
		delete u2DL;
		delete u2Q;

		delete v1Wire;
		delete v1DL;
		delete v1Q;
		delete v2Wire;
		delete v2DL;
		delete v2Q;
   }
   
   h1->Draw("colz");
   
   return ;
}


