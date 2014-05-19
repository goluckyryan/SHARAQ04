{
   gROOT->Reset();
   gROOT->ProcessLine(".!date");
//   gStyle->SetOptStat(0);

   TFile *f1 = new TFile ("PrimaryData/ppAll.root");
   TTree *ppnew = (TTree*)f1->Get("tree");
  
   
//   TFile *f2 = new TFile ("PrimaryData/ppOptics.root");
//   TTree *ppold = (TTree*)f2->Get("tree");
   
//   TFile *f3 = new TFile ("RppAll.root");
//   TTree *ppold2 = (TTree*)f3->Get("recoil");
   
   
/*   Int_t Xrange[2] = {80,92};
   Int_t nBin = (Xrange[1]-Xrange[0])*4;
   
   TH1F *h0 = new TH1F("h0", "Opening Angle", nBin, Xrange[0],Xrange[1]);
   TH1F *h1 = new TH1F("h1", "Mag Corr", nBin, Xrange[0],Xrange[1]);
   TH1F *h2 = new TH1F("h2", "Mag beamZ Corr", nBin, Xrange[0],Xrange[1]);
   
   //TCanvas *cScript = new TCanvas("cScript", "cScript", 1200,50, 600,400);
*/
   
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
