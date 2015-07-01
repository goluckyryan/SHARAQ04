
void BeamFraction_v775() {
   const char* rootfile="25F_optics.root";
   TString beam = "25F";
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries   =5000000;
   
   Double_t Zchm = -111.; // -111 = cooling chamber entrance, -222 is beam pipe, +55 NMR coil
   Double_t center[2]={0.4, 1.8};
   Double_t radius = 7.;
   
   Double_t tGate[2];
   Double_t qGate[2];
   
   if( beam == "23F") {tGate[0] = -323; tGate[1] = -318; qGate[0] = 770; qGate[1] = 1000;};
   if( beam == "22O") {tGate[0] = -306; tGate[1] = -302; qGate[0] = 700; qGate[1] =  900;};
   if( beam == "25F") {tGate[0] = -319; tGate[1] = -311; qGate[0] = 762; qGate[1] = 1060;};
   
//#########################################################   
   TCanvas *cBeamFract = new TCanvas ("cBeamFract", "Beam Fraction", 1300, 50, 800, 800); 
   cBeamFract->Divide(2,2);
   Int_t nBin = 180;
   
   gStyle->SetOptStat(0);
   
   TH1F * hPIDUS      = new TH1F("PIDUS"    , "PID upstream", 100, tGate[0]-3,tGate[1]+3);
   hPIDUS->SetXTitle("ToF(F3-FH9) [ns]");
   hPIDUS->SetYTitle("Count");
   TH2F * hS0img      = new TH2F("S0img"    , "S0img X Y"                , nBin, -30, 30, nBin, -30, 30);
   hS0img->SetXTitle("X [mm]");
   hS0img->SetYTitle("Y [mm]");
   TString hS0imgCrysTitle;
   hS0imgCrysTitle.Form("S0img Crystal (%4.2f,%4.2f)%5.2f", center[0],center[1],radius);
   TH2F * hS0imgCrys  = new TH2F("S0imgCrys", hS0imgCrysTitle        , nBin, -30, 30, nBin, -30, 30);
   hS0imgCrys->SetXTitle("X [mm]");
   hS0imgCrys->SetYTitle("Y [mm]");
   TH2F * hS0AB       = new TH2F("S0AB"     , "S0img A B"            , nBin, -100,  100, nBin, -100, 100);
   hS0AB->SetXTitle("A [mrad]");
   hS0AB->SetYTitle("B [mrad]");
//###########################################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;

   art::TCoinRegData *hoge_coinReg;
   TClonesArray *hoge_S0img, *hoge_v775, *hoge_ds;
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded.\n",rootfile);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("coinReg",1);
   tree->SetBranchStatus("S0img",1);
   tree->SetBranchStatus("plaV775",1); //get charge for PID
   tree->SetBranchStatus("tof_DS",1);

   tree->SetBranchAddress("coinReg",&hoge_coinReg);
   tree->SetBranchAddress("S0img",&hoge_S0img);
   tree->SetBranchAddress("plaV775",&hoge_v775);
   tree->SetBranchAddress("tof_DS",&hoge_ds);

//############################################################################   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   
   art::TMWDCTrackingResult * xyS0;
   art::TTrack * trackS0;
   
   Int_t countPID = 0, countS0img = 0, countCrystal = 0;
   
//#############################################################################   
   for( Int_t eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID);
   
//--------------coin Reg Gate 1 = FH9 trigger
      if ( hoge_coinReg->Test(1) != 1 ) continue;
      
//----------------Get tof and charge upstream V1190
      Int_t nHit = hoge_ds -> GetEntriesFast();
      Double_t tof_us = 0 , Q_us = 0;
      Bool_t PID = 0;
      for( Int_t p = 0; p < nHit; p++){
         Int_t detID = ((art::TTimeDifference*)hoge_ds->At(p))->GetID() ;
         if( detID != 2) continue;
         tof_us    = -((art::TTimeDifference*)hoge_ds->At(p))->GetTiming(); // minus sign
         Q_us = ((art::TTwoSidedPlasticData*) hoge_v775->At(p))->GetCharge();
         //printf("%d, %f, %f \n", eventID, tof_us, Q_us);
         if ( tof_us < tGate[0] || tof_us > tGate[1]) continue; //PID gate
         if ( Q_us < qGate[0] || Q_us > qGate[1]) continue; // PID gate
         PID = 1;
      }
      if ( PID == 0 ) continue;
      countPID++;
      hPIDUS->Fill(tof_us);
      
//---------Get S0img image, should be one 1 instance
      nHit = hoge_S0img->GetEntriesFast();
      Double_t s0x, s0y, s0a, s0b;
      Int_t trackID;
      for( Int_t p = 0; p < nHit; p++){
         xyS0 = (art::TMWDCTrackingResult*)hoge_S0img->At(p);
         trackID = xyS0->GetTrackingID();
         trackS0 = (art::TTrack*)xyS0->GetTrack();
         s0x = trackS0->GetX();
         s0y = trackS0->GetY();
         s0a = trackS0->GetA();
         s0b = trackS0->GetB();
      }
      if (trackID != 1) continue;
      countS0img++;
      hS0img->Fill(s0x,s0y);
      hS0AB ->Fill(s0a*1000,s0b*1000);
      
      Double_t s0chmX = s0x + s0a*Zchm;
      Double_t s0chmY = s0y + s0b*Zchm;
      
      if ( (s0chmX-center[0])*(s0chmX-center[0]) + (s0chmY-center[1])*(s0chmY-center[1]) > 15.*15.) continue;
      
      if ( (s0x-center[0])*(s0x-center[0]) + (s0y-center[1])*(s0y-center[1]) < radius*radius){
         countCrystal ++ ;
         hS0imgCrys->Fill(s0x,s0y);
         //hS0AB ->Fill(s0a*1000,s0b*1000);
      
      }
      
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
    
   TString countText;
   TLatex text;
   text.SetNDC();
   text.SetTextColor(1);
   
   cBeamFract->cd(1);
   hS0img->Draw("colz");
   countText.Form("count:%d",countS0img);
   text.DrawText(0.15, 0.8, countText); 
   //   text.DrawText(0.15, 0.85, rootfile); 
   
   TLine line;
   Int_t nPt = 20;
   for ( Int_t i = 0; i < nPt; i++){
      line.DrawLine(center[0] + radius*TMath::Cos(2*TMath::Pi()*i/nPt),
                    center[1] + radius*TMath::Sin(2*TMath::Pi()*i/nPt),
                    center[0] + radius*TMath::Cos(2*TMath::Pi()*(i+1)/nPt),
                    center[1] + radius*TMath::Sin(2*TMath::Pi()*(i+1)/nPt));
   }
   
   cBeamFract->cd(2);
   hS0AB->Draw("colz");
   
   cBeamFract->cd(3);
   hS0imgCrys->Draw("colz");
//   countText.Form("count:%d[%4.1f%%]", countCrystal, countCrystal*100./countPID);
   countText.Form("count:%d [%4.1f%%]", countCrystal, countCrystal*100./countS0img);
   text.DrawText(0.15, 0.8, countText);

   cBeamFract->cd(4);
   hPIDUS->Draw("colz");
   countText.Form("count:%d",countPID);
   text.DrawText(0.15, 0.8, countText);
}
