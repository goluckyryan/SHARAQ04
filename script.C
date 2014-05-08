{
   gROOT->Reset();
   gROOT->ProcessLine(".!date");
   gStyle->SetOptStat(0);

//   TFile *f1 = new TFile ("test.root");
//   TTree *test = (TTree*)f1->Get("recoil");
   
//   TFile *f2 = new TFile ("phys24_down_1.root");
//   TTree *recoil = (TTree*)f2->Get("tree");
   
//   TFile *f0 = new TFile ("25F_new.root");
//   TTree *tree = (TTree*)f0->Get("tree");
   
   TFile *f1 = new TFile ("PrimaryData/phys14Up.root");
   TTree *test = (TTree*)f1->Get("tree");
   
/*   TFile *f1 = new TFile ("phys22DCX1X2.root");
   TTree *phys22 = (TTree*)f1->Get("tree");
   
   TFile *f0 = new TFile ("TimeCheck25F.root");
   TTree *recoil1 = (TTree*)f0->Get("recoil");
   
/*   TFile *f1 = new TFile ("CompareTKAphy14.root");
   TTree *recoil2 = (TTree*)f1->Get("recoil");
   
   TFile *f2 = new TFile ("CompareTKAproton.root");
   TTree *recoil3 = (TTree*)f2->Get("recoil");
   
   
/*   Int_t Xrange[2] = {80,92};
   Int_t nBin = (Xrange[1]-Xrange[0])*4;
   
   TH1F *h0 = new TH1F("h0", "Opening Angle", nBin, Xrange[0],Xrange[1]);
   TH1F *h1 = new TH1F("h1", "Mag Corr", nBin, Xrange[0],Xrange[1]);
   TH1F *h2 = new TH1F("h2", "Mag beamZ Corr", nBin, Xrange[0],Xrange[1]);
   
   //TCanvas *cScript = new TCanvas("cScript", "cScript", 1200,50, 600,400);
*/
//   gROOT->ProcessLine("TBrowser B");
   
   TBrowser B("test","test", 900,600);
   
/*   TLatex text;
   text.SetNDC();
   text.SetTextColor(1);
   text.DrawText(0.2, 0.3, "no Corr");
   text.SetTextColor(2);
   text.DrawText(0.2, 0.25, "Mag Corr");
   text.SetTextColor(4);
   text.DrawText(0.2, 0.2, "Mag + BeamZ=15 Corr");*/
   
   
}
