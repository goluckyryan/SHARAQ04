#include "constant.h"

void pidNyoki() {

   const char* rootfile="23F_0217_run23.root";
   
   Int_t nyokiID[2] = {2,10};
   Bool_t useS0AB = 0;
   Int_t useToFQ = 0 ;// 0 = z-AoQ, 1 = Q-tof, 2 = z-tof, 3 = z - s1x
   Bool_t useSlew = 0;
   Bool_t useMWDC = 1;
   Bool_t forceCal = 1;
   
   Double_t newO[2] = {0,0}; //{x,z} mm
   Double_t ang = 0; //deg, left hand rotation about y axis
   
	Int_t Div[2] = {1,1};
	Int_t size = 400;
   
   Bool_t allentry    = 1;
   Int_t firstEntry   = 0;
   Int_t nEntries     = 100000;
	
	Int_t sampleRate = 1;
	
	Bool_t ppcoin = 0;
	Bool_t beam = 0;
	Bool_t pid23F = 0;
	Bool_t pid22O = 0;
	Bool_t pid8Li = 0;
	
	Bool_t fitZ = 0;

//########################################################  
	const Double_t Brho0 = 6.5269;//6.7288;//*22/8*9/23;  
	const Double_t LS0DNyoki = 6862.1; //6575.60525; // mm
	const Double_t para1 = -0.451752;
	const Double_t para2 = 0.0003021347;
	const Double_t att  = 99999999;//3000.; // mm
	const Double_t r0 = 4.4; // m
	const Double_t xdp = -1427; //-1156; // mm / 100%
	const Double_t B0 = Brho0/r0; // T
	Double_t tofOffSet = 0.1;
	Double_t b,g,h, Sa,Sk,SQ,St;
	
	Double_t nyokiY[2] = {50, 0}; //start, end
	
	ang = ang * TMath::DegToRad();
	
	//____
	b = 500; // ch
	//g = 16.5;//
	g =18.4;
	//h = 0.007288;//
	h = -0.0089834;
	
	//____Slew
	Sa = 28.0;
	Sk = 0.240;
	SQ = 500;
	St = 5;

   TString histTitle;
   histTitle.Form("PID Nyoki-%d~%d (%s)", nyokiID[0], nyokiID[1], rootfile);
   if( useS0AB) histTitle += " S0AB gate";
   if( ppcoin) histTitle += " ppcoin";
   if( beam) histTitle += " beam";
   if( pid23F) histTitle += " 23F";
   if( pid22O) histTitle += " 22O";
   if( pid8Li) histTitle += " 8Li";
   
   gStyle->SetOptStat(0);
   TString canvasName = "PID Nyoki : ";
   canvasName += rootfile;
   TCanvas* cPID = new TCanvas("cPid", canvasName, 2000, 0, Div[0]*size,Div[1]*size);
   cPID->Divide(Div[0],Div[1]);
   
   TH2F* hPIDNyoki ;
   if( useToFQ==0){
		hPIDNyoki= new TH2F("PID_nyoki",histTitle,400, 1.8, 3.5, 220 , 0, 11);
		hPIDNyoki->SetXTitle("A/Q");
		hPIDNyoki->SetYTitle("Z");	
	}else if( useToFQ == 1){
		hPIDNyoki= new TH2F("PID_nyoki",histTitle,400, 25, 40, 400 , 500, 2000);
		hPIDNyoki->SetXTitle("ToF [ns]");
		hPIDNyoki->SetYTitle("Q");	
   }else if( useToFQ == 2){
		hPIDNyoki= new TH2F("PID_nyoki",histTitle, 200, 28, 45, 220 , 0, 11);
		hPIDNyoki->SetXTitle("ToF [ns]");
		hPIDNyoki->SetYTitle("Z");	
   }else if ( useToFQ == 3) {
   	hPIDNyoki= new TH2F("PID_nyoki",histTitle, 200, -200, 500, 220 , 0, 11);
		hPIDNyoki->SetXTitle("s1x [mm]");
		hPIDNyoki->SetYTitle("Z");		
		useMWDC = 1;
   }
   
   TH2F* hAux = new TH2F("hAux", "Z0 vs (A/Q)0", 400, 1.8, 3.5, 220, 0, 11);
	hAux->SetXTitle("(A/Q)0");
	hAux->SetYTitle("Z0");	

   TH2F* hAux2 = new TH2F("hAux2", "", 100, 1.8, 3.5, 220, 4.0, 8.0);
	hAux2->SetXTitle("A/Q");
	hAux2->SetYTitle("Brho");
	
	TH2F* hAux3 = new TH2F("hAux3", "", 200, 30, 40, 200, 0, 1700);
	hAux3->SetXTitle("tof");
	hAux3->SetYTitle("L");

	TH2F* hAux4 = new TH2F("hAux4", "", 400, -100, 100, 200, 1, 10);
	hAux4->SetXTitle("s1x");
	hAux4->SetYTitle("Z");

	TH1F* hAux5 = new TH1F("hAux5", "from A/Q", 100, 20, 25);
	hAux5->SetXTitle("A");
	hAux5->SetLineColor(2);
	
	TH1F* hAux6 = new TH1F("hAux6", "", 100, 20, 25);
	hAux6->SetXTitle("A");

	TH1F* hDiffz = new TH1F("hDiffz", "", 100, -0.2, 0.2);
	hDiffz->SetXTitle("z - z0");
	TH1F* hDiffAoQ = new TH1F("hDiffAoQ", "", 100, -0.2, 0.2);
	hDiffAoQ->SetXTitle("A/Q - A/Q0");

//#####################################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;

   TClonesArray *hoge_nyoki, *hoge_tofD1, *hoge_S0img, *hoge_mwdc, *hoge_vertex;
   art::TCoinRegData *hoge_coinReg;
	art::TGateArray * gate;

   TFile *f = new TFile(rootfile,"read");
   TTree *pid = (TTree*)f->Get("tree");
   
   Int_t totnumEntry = pid->GetEntries();
	pid->SetBranchStatus("*",0);
	pid->SetBranchStatus("gate",1);
   pid->SetBranchStatus("coinReg",1);
   pid->SetBranchStatus("nyoki",1);
   pid->SetBranchStatus("tof_D1",1);
   //pid->SetBranchStatus("vertex",1);
   if ( useMWDC) pid->SetBranchStatus("smwdc_S1",1);
   if ( useS0AB) pid->SetBranchStatus("S0img",1);


	tree->SetBranchAddress("gate",&gate); 
   pid->SetBranchAddress("coinReg",&hoge_coinReg);
   pid->SetBranchAddress("nyoki",&hoge_nyoki);
   pid->SetBranchAddress("tof_D1",&hoge_tofD1);
   //pid->SetBranchAddress("vertex",&hoge_vertex);
   if ( useS0AB) pid->SetBranchAddress("S0img", &hoge_S0img);
   if ( useMWDC) pid->SetBranchAddress("smwdc_S1",&hoge_mwdc);
   
   
   if( nEntries > totnumEntry) allentry = 1;
      
   if (allentry) {
      firstEntry = 0;
      nEntries = totnumEntry;
   }
   
   printf("File:%s ==== TotnumEntry:%d, 1stEntry:%d, nEntries:%d[%4.1f%%]\n"
                 , rootfile
                 , totnumEntry
                 , firstEntry
                 , nEntries
                 , nEntries*100./totnumEntry);
                 
  Int_t count = 0;
   
//#############################################################   
   for( Int_t eventID = firstEntry; eventID < TMath::Min(firstEntry+nEntries, totnumEntry); eventID+=sampleRate){
      pid->GetEntry(eventID,0); 
      
      if( ppcoin && !hoge_coinReg->Test(2) ) continue;
      if( beam && !hoge_coinReg->Test(1) ) continue;
          
      if( pid23F && gate->Test(0) != 1) continue;
      if( pid22O && gate->Test(1) != 1) continue;
      if( pid8Li && gate->Test(6) != 1) continue;
      
      //if( gate->Test(9) !=1) continue;
      
      Double_t tof = -50;
      Double_t QQ = -50;
      Bool_t tofPass = 0;
      Bool_t QQPass = 0;
      
      Double_t s0x = -500;
      Double_t s0y = -500;
      Double_t s0a = -500;
      Double_t s0b = -500;
      
      Double_t s1x = -50000;
      Double_t s1a = -500;
      Double_t s1y = -50000;
      
      Double_t s1yO = -50000;
      Double_t s1xO = -50000;
      Double_t s1aO = -500; 
      
      
      Double_t FL = LS0DNyoki;
      
      //___________________________________________________________Get S0img
   if( useS0AB ){
      Int_t nHit = hoge_S0img->GetEntriesFast();
      Bool_t S0Pass = 0;
      for( Int_t p = 0; p < nHit; p++){
         art::TMWDCTrackingResult * xyS0 = (art::TMWDCTrackingResult*)hoge_S0img->At(p);
         S0Pass = xyS0->IsGood();
         art::TTrack * trackS0 = (art::TTrack*)xyS0->GetTrack();
         s0x = trackS0->GetX();
         s0y = trackS0->GetY();
         s0a = trackS0->GetA()*1000; // (mrad)
         s0b = trackS0->GetB()*1000; // (mrad)
      }      

      if( S0Pass == 0 ) continue;
      //if( TMath::Abs(s0a)>10 || TMath::Abs(s0b)>10 ) continue;
      if( TMath::Abs(s0x)>4 ) continue;  
   }
   //___________________________________________________________Get Vertex
   //Int_t nHit = hoge_vertex->GetEntriesFast();
   //for( Int_t p = 0; p < nHit; p++){

   //}

   //___________________________________________________________Get SMWDC-S1
   if ( useMWDC) {
      Int_t nHit = hoge_mwdc->GetEntriesFast();
      Bool_t mwdcPass = 0;
      if(nHit == 0 ) continue;
      for( Int_t p = 0; p < nHit; p++){
         art::TMWDCTrackingResult * xyS1 = (art::TMWDCTrackingResult*)hoge_mwdc->At(p);
         mwdcPass = xyS1->IsGood();
         art::TTrack * trackS1 = (art::TTrack*)xyS1->GetTrack();
         s1xO = trackS1->GetX(); // (mm)
         s1aO = trackS1->GetA(); // (rad)
         s1yO = trackS1->GetY(); // (mm)
      }      
      if( mwdcPass == 0 ) continue;

      //printf("%.3f, %.3f ", s1xO,s1aO);

      s1x = (s1xO - newO[0] + s1aO*newO[1])/(cos(ang) - s1aO*sin(ang));
      s1a = (s1aO + tan(ang))/(1 - s1aO*tan(ang));
      s1y = s1yO;

      //printf("| %.3f, %.3f //\n", s1x,s1a);

      FL = LS0DNyoki +para1*s1x + para2*s1x*s1x;
   }

   //___________________________________________________________Get Charge from nyoki
   Int_t nHit1 =hoge_nyoki->GetEntriesFast();
   if( nHit1 >= 2) continue;

   for(Int_t p = 0; p < nHit1; p++){
      data1 = (art::TTwoSidedPlasticData*)hoge_nyoki->At(p) ;
      Int_t ID   = data1->GetID();
      //printf(", QQ ID: %d ", ID);
      if( ID >= nyokiID[0] && ID <= nyokiID[1]) {
         QQ  = data1->GetCharge();
         QQPass = 1;
      }else{	
         continue;
      }
   }
   if( QQPass == 0 ) continue;

   //___________________________________________________________Get tof_D1
   Int_t nHit2 =hoge_tofD1->GetEntriesFast();
   for(Int_t p = 0; p < nHit2; p++){
      data2 = (art::TTimeDifference*)hoge_tofD1->At(p) ;
      Int_t ID = data2->GetID();
      //printf("tof ID: %d ", ID);
      if ( ID >= nyokiID[0] && ID <= nyokiID[1]) {
         //Slew 
         Double_t walk = Sa/TMath::Power(QQ-SQ,Sk) - St;
         if( useSlew == 0) walk = 0;
         
         tof = data2->GetTiming() + tofOffSet - walk;
         //printf("%10.2f , %10.2f \n", tof, walk);
         tofPass = 1;
      }else{
         continue;
      }
   }
   if( tofPass == 0 ) continue;
   if( tof<27 || tof>46 ) continue;
         
   count += 1;


   //___________________________________________________________Calculate z and AoQ and fill histogram		
   if( useToFQ == 1){
      //printf("Q:%6.0f, tof:%6.2f \n", QQ, tof);
      hPIDNyoki->Fill(tof,QQ);			
   }
   if( useToFQ != 1 || forceCal ) {
      Double_t beta0 = LS0DNyoki/cVaccum/tof;
      Double_t gamma0 = 1./TMath::Sqrt(1.-beta0*beta0);
      Double_t AoQ0 = cVaccum*Brho0/mu/gamma0/beta0;
      
      Double_t beta = FL/cVaccum/tof;
      Double_t gamma = 1./TMath::Sqrt(1.-beta*beta);
   //		   Double_t Brho = ( 2018.03 - 0.985391*s1x - 0.00018424*s1x*s1x ) / cVaccum;	
      Double_t Brho = Brho0* (1 + s1x/xdp);//- s1x*s1x/1.13195E7 );
      Double_t AoQ = cVaccum*Brho/mu/gamma/beta;
      
      Double_t L0 = (QQ-b);
      Double_t z0 = TMath::Sqrt(L0/(g+L0*h))*beta0;
      
      Double_t L;
      //if( nyokiY[0] < s1y && s1y < nyokiY[1] ) {
      //	L = (QQ-b)*TMath::Exp((nyokiY[0]-s1y)/att);
      //}else{
         L = L0;
      //}
      Double_t z = TMath::Sqrt(L/(g+L*h))*beta;
      
      hAux->Fill(AoQ0, z0);
      //hAux2->Fill(z, s1y);
      hAux2->Fill(AoQ, Brho);
      hAux3->Fill(tof,L0);
      hAux4->Fill(s1x,z); //-4069.4
      //hAux5->Fill(s1x);
      if( TMath::Abs(z-8.)<0.1) {
         //printf(" %f* %f = %f \n", z0, AoQ0, AoQ0*8); 
         hAux5->Fill(AoQ*8.);
      }
      if( TMath::Abs(z0-9.)<0.1 ) {
         hAux6->Fill(AoQ*9.);
      }
      
      
      hDiffz->Fill( z - z0);
      hDiffAoQ->Fill( AoQ - AoQ0);
      
      if( useToFQ==0) hPIDNyoki->Fill(AoQ,z);
      if( useToFQ==2) hPIDNyoki->Fill(tof,z);
      if( useToFQ==3) hPIDNyoki->Fill(s1x,z);
   }


   //------------Clock      
   clock.Stop("timer");
   Double_t timer = clock.GetRealTime("timer");
   clock.Start("timer");

   if ( !shown ) {
      if (fmod(timer, 10) < 1 ){
         printf( "%10d[%2d%%] |%3d min %5.2f sec | expect:%5.1fmin\n", 
         eventID, 
         TMath::Nint((eventID+1-firstEntry)*100./nEntries),
         TMath::Floor(timer/60), timer - TMath::Floor(timer/60)*60,
         nEntries*timer/(eventID+1-firstEntry)/60.);
         shown = 1;
      }
   }else{
      if (fmod(timer, 10) > 9 ){
         shown = 0;
      }
   }

   }

   printf(" total count = %d\n", count);

   cPID->cd(1);
   hPIDNyoki->Draw("colz");
   hAux4->Draw("colz");
   //hPIDNyoki->ProjectionX()->Draw("colz");
   //hAux3->Draw("colz");
   /*
   cPID->cd(4);
   hAux->Draw("colz");
   //hPIDNyoki->ProjectionY("test")->Draw();
   //hDiffz->Draw();

   cPID->cd(2);
   //hPIDNyoki->ProjectionY("test")->Draw();
   hAux->ProjectionY("testAux")->Draw("same");
   //testAux->SetLineColor(2);
   //testAux->Draw("same");
   //hAux2->ProfileY()->Draw();
   //hDiffAoQ->Draw();


   //hAux3->Draw("colz");	
   //hAux3->ProjectionX()->Draw();
   //TF1 * func = new TF1 ("func", "8.54677*x/TMath::Sqrt(1-x*x)", 0.5, 0.8);
   //func->Draw("same");

   cPID->cd(5);
   //hAux5->Draw();
   /*hAux4->Draw("colz");
   TF1 * func2 = new TF1 ("func2", "x/299.792458/0.61859", 6400, 6800);
   func2->Draw("same");
   //hAux2->Draw("colz");
   //hAux2->ProjectionX()->Draw();
   */
   //hAux3->ProjectionY()->Draw("");
   //hPIDNyoki->ProjectionY("testPID")->Draw("");
   /**/
   /*
   cPID->cd(6);
   //tree->Draw("coinReg.fQuality & 255");
   hAux6->Draw();
   //hAux2->Draw("colz");
   hAux5->Draw("same");
   //hAux->ProjectionX("aux_Z=9", 170, 190)->Draw("");
   //hAux->ProjectionX("aux_Z=8", 150, 170)->Draw("same");

   cPID->cd(3);
   hAux4->Draw("colz");
   //hPIDNyoki->ProjectionX("pid_Z=9", 170, 190)->Draw("");
   //hPIDNyoki->ProjectionX("pid_Z=8", 150, 170)->Draw("same");


   /**/

   if( fitZ ){
   cPID->cd(2);
   TF1 * fit = new TF1("fit", "gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)+gaus(15)+gaus(18)", 2.5, 11);
   Double_t par[21] = { 1500, 3, 0.2, 800, 4, 0.2, 500, 5, 0.5, 400, 6, 0.5, 1000, 7, 0.5, 7000, 8, 0.5, 5500, 9, 0.5};
   fit->SetParameters(par);
   fit->SetParLimits(1,2.7, 3.3);
   fit->SetParLimits(2,0, 2);
   fit->SetParLimits(4,3.7, 4.3);
   fit->SetParLimits(5,0, 2);
   fit->SetParLimits(7,4.7, 5.3);
   fit->SetParLimits(8,0, 2);
   fit->SetParLimits(10,5.7, 6.3);
   fit->SetParLimits(11,0, 2);
   fit->SetParLimits(13,6.7, 7.3);
   fit->SetParLimits(14,0, 2);
   fit->SetParLimits(16,7.7, 8.5);
   fit->SetParLimits(17,0, 2);
   fit->SetParLimits(29,8.7, 9.5);
   fit->SetParLimits(20,0, 2);
   testAux->Fit("fit", "R");
   fit->GetParameters(par);

   TF1* k2 = new TF1("k2", "gaus", 2.5, 11); k2->SetParameters(&par[0]); k2->SetLineColor(1);k2->SetLineWidth(1);k2->Draw("same");
   TF1* k3 = new TF1("k3", "gaus", 2.5, 11); k3->SetParameters(&par[3]); k3->SetLineColor(2);k3->SetLineWidth(1);k3->Draw("same");
   TF1* k4 = new TF1("k4", "gaus", 2.5, 11); k4->SetParameters(&par[6]); k4->SetLineColor(3);k4->SetLineWidth(1);k4->Draw("same");
   TF1* k5 = new TF1("k5", "gaus", 2.5, 11); k5->SetParameters(&par[9]); k5->SetLineColor(4);k5->SetLineWidth(1);k5->Draw("same");
   TF1* k6 = new TF1("k6", "gaus", 2.5, 11); k6->SetParameters(&par[12]);k6->SetLineColor(5);k6->SetLineWidth(1);k6->Draw("same");
   TF1* k7 = new TF1("k7", "gaus", 2.5, 11); k7->SetParameters(&par[15]);k7->SetLineColor(6);k7->SetLineWidth(1);k7->Draw("same");
   TF1* k8 = new TF1("k8", "gaus", 2.5, 11); k8->SetParameters(&par[18]);k8->SetLineColor(7);k8->SetLineWidth(1);k8->Draw("same");
   //TF1* k9 = new TF1("k9", "gaus", 1.8, 11); k9->SetParameters(&par[21]);k9->SetLineColor(8);k9->SetLineWidth(1);k9->Draw("same");



   //testPID->Fit("fit", "R");

   }
   return ;
}
