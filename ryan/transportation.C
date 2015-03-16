void transportation(){

//========================================================

   char * rootfile = "23F_ppcoin_0314.root";
   Int_t nEvent = 100000;
   
   TString hTitle;
   hTitle.Form("Gate: ppcoin + 23F + crystal, nEvent:%d", nEvent);
   TCut gate = "gate.Test(12)";//"gate.Test(0) && gate.Test(12)";
        

//========================================================


   TFile *f0 = new TFile (rootfile, "read"); 
   if( f0==0){
      printf("cannot load file: %s \n", rootfile);
      return;
   }
        
   TTree *tree = (TTree*)f0->Get("tree");
   //gROOT->ProcessLine("listg tree");
   printf("=====> /// %15s //// is loaded. Total #Entry: %10d \n", rootfile,  tree->GetEntries());


/****************  transportation  *****************************/ 
   gStyle->SetOptStat(0);

        TCanvas *haha = new TCanvas("haha", "haha", 2000, 0, 800,800);
        
        TH1F* g1 = new TH1F("g1", "g1", 16, -2, 14);
        g1->SetTitle(hTitle);
        
        tree->Draw("plaV775.fID>>g1", gate, "", nEvent);
        tree->Draw("coinReg.Test(2)-2>>gb", "coinReg.Test(2)" + gate, "same", nEvent);
        tree->Draw("S0img.IsGood()+ 4>>ga", "S0img.IsGood()" + gate, "same", nEvent);
        tree->Draw("(TMath::Abs(tof_D1.fTiming-36)<5) + 5 >>g2", "TMath::Abs(tof_D1.fTiming-36)< 5" + gate, "same", nEvent);
        tree->Draw("nyoki_t.fID + 7 >> g3", gate, "same", nEvent);
        tree->Draw("(smwdc_S1.fNPlaneValid>=1) + 7 >>g4", "smwdc_S1.fNPlaneValid" + gate, "same", nEvent);
        tree->Draw("smwdc_S1.IsGood() + 8 >> g5", "smwdc_S1.IsGood()" + gate, "same", nEvent);
        tree->Draw("smwdc_L.IsGood() + 9 >> g6", "smwdc_L.IsGood()" + gate, "same", nEvent);
        tree->Draw("smwdc_R.IsGood() + 10 >> g7", "smwdc_R.IsGood()" + gate, "same", nEvent);
        tree->Draw("TMath::IsNaN(p2p.fSp) + 12 >> g8", "!TMath::IsNaN(p2p.fSp)" + gate, "same", nEvent);
        
        TLatex text;
        text.SetTextSize(0.03);
        text.SetTextAngle(90);
        TString textStr;
        textStr.Form("%6.0f, ppcoin", gb->GetEntries());
        text.DrawLatex(-0.5, 50, textStr);
        
        textStr.Form("%6.0f, Tpla_L", g1->GetBinContent(3));
        text.DrawLatex(0.5, 50, textStr);
        textStr.Form("%6.0f, Tpla-R", g1->GetBinContent(4));
        text.DrawLatex(1.5, 50, textStr);
        textStr.Form("%6.0f, F3PL", g1->GetBinContent(5));
        text.DrawLatex(2.5, 50, textStr);
        textStr.Form("%6.0f, FH9PL", g1->GetBinContent(6));
        text.DrawLatex(3.5, 50, textStr);
        textStr.Form("%6.0f, S0PL", g1->GetBinContent(7));
        text.DrawLatex(4.5, 50, textStr);
        textStr.Form("%6.0f, S0img IsGood", ga->GetEntries());
        text.DrawLatex(5.5, 50, textStr);
        textStr.Form("%6.0f, |TOF(S0D-Nyoki)-36|<5", g2->GetEntries());
        text.DrawLatex(6.5, 50, textStr);
        textStr.Form("%6.0f, nyoki_t", g3->GetEntries());
        text.DrawLatex(7.5, 50, textStr);
        textStr.Form("%6.0f, MWDC-S1 fried", g4->GetEntries());
        text.DrawLatex(8.5, 50, textStr);
        textStr.Form("%6.0f, MWDC-S1 IsGood", g5->GetEntries());
        text.DrawLatex(9.5, 50, textStr);
        textStr.Form("%6.0f, MWDC-L IsGood", g6->GetEntries());
        text.DrawLatex(10.5, 50, textStr);
        textStr.Form("%6.0f, MWDC-R IsGood", g7->GetEntries());
        text.DrawLatex(11.5, 50, textStr);
        textStr.Form("%6.0f, Sp isValid", g8->GetEntries());
        text.DrawLatex(12.5, 50, textStr);
        
        printf("............\n");

}
