EnergyStraggling(){
   
   gROOT->Reset();
   gROOT->ProcessLine(".!date");
   gStyle->SetOptStat(0);

//========================================================

   char * rootfile = "23F_0217_run23.root";
   /* FL = 6903 <=> offset = 0  */

   Double_t FL = 6290;
   Double_t offset = -3.26;   
   TString Isotope = "22O";
   

   TString cut = "&& gate.Test(12) && TMath::Abs(S0img.fTrack.fA)<0.005 && TMath::Abs(S0img.fTrack.fB)<0.005 && nyoki.fID==7";
   //TString cut = "gate.Test(0) && gate.Test(12) && nyoki.fID==7";

//========================================================
   TFile *f0 = new TFile (rootfile, "read"); 
   if( f0==0){
      printf("cannot load file: %s \n", rootfile);
      return;
   }
        
   TTree *tree = (TTree*)f0->Get("tree");
   gROOT->ProcessLine("listg tree");
   printf("=====> /// %s //// is loaded. Total #Entry: %d \n", rootfile,  tree->GetEntries());

   TLatex text;
   text.SetNDC();
   text.SetTextColor(1);
   text.SetTextColor(0.04); 
//======================================================== Canvas

   Int_t Div[2] = {3,2};  //x,y
   Int_t size[2] = {400,400}; //x,y
   TCanvas * cScript = new TCanvas("cScript", "cScript", 2000,0 , size[0]*Div[0], size[1]*Div[1]);
   cScript->Divide(Div[0],Div[1]);
   
   Double_t mass = 0;
   Int_t A = 0;   
   Int_t tofF3FH9[2] ={ 375, 390};
   Int_t engRange[2] ={ 260, 300};
   Int_t tofS0DHodo[2] ={ 30, 35};
   TString PIDcut = "";
   
   if( Isotope == "23F") {
      mass = 21423.1; 
      A = 23.0;
      PIDcut="gate.Test(0)";
   }
   if( Isotope == "22O") {
      mass = 20498.1; 
      A = 22.0;
      PIDcut="gate.Test(1)";
      tofF3FH9[0] = 390;
      tofF3FH9[1] = 410;
      engRange[0] = 230;
      engRange[1] = 260;
      tofS0DHodo[0] = 32;
      tofS0DHodo[1] = 37;
   }
   
   printf("............. %s : %7.1f MeV, %d \n", Isotope.Data(), mass, A);
   
   
   TH1F* h1 = new TH1F("h1", "tof(F3-FH9) | L = 74075 mm | tgt + " + Isotope, 200, tofF3FH9[0], tofF3FH9[1]);
   h1->SetXTitle("tof(F3-FH9) [ns]");

   TH1F* h2 = new TH1F("h2", "Kinetic Energy per nucleon | tgt + "+ Isotope, 200, engRange[0], engRange[1]);
   h2->SetXTitle("TKE [A MeV]");

   TString hTitle;
   hTitle.Form("tof(S0DPL-Hodo-7) | L = %4.0f mm | tgt + %s", FL, Isotope.Data());
   TH1F* h4 = new TH1F("h4", hTitle, 200, tofS0DHodo[0], tofS0DHodo[1]);
   h4->SetLineColor(2);
   h4->SetXTitle("tof(S0DPL-Hodo) [ns]");

   TH1F* h5 = new TH1F("h5", "Kinetic Energy per nucleon | tgt + "+ Isotope, 200, engRange[0], engRange[1]);
   h5->SetXTitle("TKE [A MeV]");
   h5->SetLineColor(2);
   
   TH1F* h3 = new TH1F("h3", "Energy Loss", 200, -20, 40);
   h3->SetXTitle("Energy Loss [A MeV]");
//======================================================== 
   TString plotF3FH9eng;
   plotF3FH9eng.Form("%f/%d*(1/TMath::Sqrt(1-TMath::Power(74075/299.792458/(tof_US.fTiming+1463+382.18),2))-1)>>h2", mass, A );
   
   TString plotS0DHodoTime;
   plotS0DHodoTime.Form("tof_D1.fTiming+%f>>h4", offset);

   TString plotS0DHodoeng;
   plotS0DHodoeng.Form("%f/%d*(1/TMath::Sqrt(1-TMath::Power(%f/299.792458/(tof_D1.fTiming+%f),2))-1)>>h5", mass, A, FL, offset);

   TString energyLoss;
   energyLoss.Form("%f/%d*((1/TMath::Sqrt(1-TMath::Power(74075/299.792458/(tof_US.fTiming+1463+382.18),2))-1)-(1/TMath::Sqrt(1-TMath::Power(%f/299.792458/(tof_D1.fTiming+%f),2))-1))>>h3", mass, A, FL, offset);

//========================================================
   TF1 * fit = new TF1("fit", "gaus(0)", 380, 386);
//========================================================

   cScript->cd(1);
   tree->Draw("(tof_US.fTiming+1463+382.18)>>h1", PIDcut + cut, "colz");
   //fit->SetRange(tofF3FH9[0], tofF3FH9[1]);
   //fit->SetParameter(1, 382);
   //h1->Fit("fit", "RN");
   

   cScript->cd(2);
   tree->Draw(plotF3FH9eng, PIDcut + cut, "colz");

   cScript->cd(4);
   tree->Draw(plotS0DHodoTime, PIDcut + cut , "colz");

   cScript->cd(5);
   tree->Draw(plotS0DHodoeng, PIDcut + cut , "colz");


   cScript->cd(3);
   tree->Draw(energyLoss, PIDcut + cut, "colz");

   cScript->cd(6);
   h2->Draw();
   h5->Draw("same");

}
