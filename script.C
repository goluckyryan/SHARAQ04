
{
   gROOT->Reset();
   gROOT->ProcessLine(".!date");
   gStyle->SetOptStat(0);

   TFile *f0 = new TFile ("ppAll_0731.root"); TTree *tree = (TTree*)f0->Get("tree");   

//   TFile *f1 = new TFile ("14O_0802_timecheck.root"); TTree *ppNew = (TTree*)f1->Get("tree");   

//   TFile *f1 = new TFile ("ppAll_0724_multiOffset.root"); TTree *tree1 = (TTree*)f1->Get("tree");


	// update.
//   TFile *f2 = new TFile ("ppDown_0723.root","update"); TTree *down = (TTree*)f2->Get("tree");   
//   TFile *f1 = new TFile ("RppAll_0714_multiOffset.root","update"); TTree *recoil = (TTree*)f1->Get("recoil");   
//   f0->Close();

   //  TBrowser B("test","test", 900,600); 

   Int_t firstEntry = 0;
   Int_t nEntries=10000;

   //TH1F* hScript = new TH1F("hScript", "#Delta#theta_{XA}", 300, 0, 3000);
   //hScript->SetXTitle("#Delta#theta_{XA} [deg]");
   //hScript->SetYTitle("count / 0.2 [deg] ");
   //hScript->SetTitleOffset(1.5,"Y");
   //hScript->SetMinimum(0);
   TH1F * hChargeL  = new TH1F("hChargeL", "QL", 300, 0, 3000);
   
   //tree->Draw("(p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()>>hScript");
   //tree->Draw("beamZ.fAverage>>hScript","","", 1000, 0);
   tree->Draw("plaV775.fCharge>>hChargeL", "plaV775.GetDetID()==0", "", nEntries, firstEntry);
   //tree->Draw("120.+(atan(smwdc_L.fTrack.fA)-atan(smwdc_R.fTrack.fA))*TMath::RadToDeg()>>hScript", "TMath::Abs(TMath::Abs(p2p.fRecoilL.Phi()-p2p.fRecoilR.Phi())*TMath::RadToDeg()-180)<10");   
   //tree->Draw("120.+(atan(smwdc_L.fTrack.fA)-atan(smwdc_R.fTrack.fA))*TMath::RadToDeg()>>hScript", "TMath::Abs(beamZ)<10");   
  
   /*tree->Draw("(60.-(atan(smwdc_R.fTrack.fA))*TMath::RadToDeg()):(p2p.fRecoilR.Theta())*TMath::RadToDeg()>>h1(200,20,70,200,20,70)", "", "colz");   
	h1->SetXTitle("#theta_{X} [deg]");
	h1->SetYTitle("#theta_{A} [deg]");
	h1->Draw("colz");
   */
	
	
}   


//############################################# Template
   
/*   TLatex text;
   text.SetNDC();
   text.SetTextColor(1);
   text.DrawText(0.2, 0.3, "no Corr");
   text.SetTextColor(2);
   text.DrawText(0.2, 0.25, "Mag Corr");
   text.SetTextColor(4);
   text.DrawText(0.2, 0.2, "Mag + BeamZ=15 Corr");*/
   
   
/* ----------- get leave data

	Double_t data;
	tree->SetBranchAddress("branch", &data);
	tree->GetEntry(eventID);
	printf("%f \n", data);
	
	*/
