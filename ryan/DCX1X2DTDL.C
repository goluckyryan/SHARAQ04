void DCX1X2DTDL(){
   
   TFile* f0 = new TFile ("phys14UpDCX1X2.root");
   TTree* phys14 = (TTree*)f0->Get("tree");
   
   TFile* f1 = new TFile ("phys22DCX1X2.root");
   TTree* phys22 = (TTree*)f1->Get("tree");
   
   TH1F* hRunNum1 = new TH1F("runNum1", "runNum phys22", 50, 0, 50);
   TH1F* hRunNum2 = new TH1F("runNum2", "runNum phys14", 50, 0, 50);
   hRunNum1->SetLineColor(4);
   hRunNum2->SetLineColor(2);
   
   TH1F* hdcx1Xa = new TH1F("dcx1Xa", "dcx1 X phys22", 50, 0, 5);
   TH1F* hdcx1Xb = new TH1F("dcx1Xb", "dcx1 X phys14", 50, 0, 5);
   hdcx1Xa->SetLineColor(4);
   hdcx1Xb->SetLineColor(2);
   
   TH1F* hdcx1Ua = new TH1F("dcx1Ua", "dcx1 U phys22", 50, 0, 5);
   TH1F* hdcx1Ub = new TH1F("dcx1Ub", "dcx1 U phys14", 50, 0, 5);
   hdcx1Ua->SetLineColor(4);
   hdcx1Ub->SetLineColor(2);
   
   TH1F* hdcx1Va = new TH1F("dcx1Va", "dcx1 V phys22", 50, 0, 5);
   TH1F* hdcx1Vb = new TH1F("dcx1Vb", "dcx1 V phys14", 50, 0, 5);
   hdcx1Va->SetLineColor(4);
   hdcx1Vb->SetLineColor(2);
   
   TH1F* hdcx2U1a = new TH1F("dcx2U1a", "dcx2 U1 phys22", 50, 0, 5);
   TH1F* hdcx2U1b = new TH1F("dcx2U1b", "dcx2 U1 phys14", 50, 0, 5);
   hdcx2U1a->SetLineColor(4);
   hdcx2U1b->SetLineColor(2);
   
   TH1F* hdcx2U2a = new TH1F("dcx2U2a", "dcx2 U2 phys22", 50, 0, 5);
   TH1F* hdcx2U2b = new TH1F("dcx2U2b", "dcx2 U2 phys14", 50, 0, 5);
   hdcx2U2a->SetLineColor(4);
   hdcx2U2b->SetLineColor(2);
   
   TH1F* hdcx2V1a = new TH1F("dcx2V1a", "dcx2 V1 phys22", 50, 0, 5);
   TH1F* hdcx2V1b = new TH1F("dcx2V1b", "dcx2 V1 phys14", 50, 0, 5);
   hdcx2V1a->SetLineColor(4);
   hdcx2V1b->SetLineColor(2);
   
   TH1F* hdcx2V2a = new TH1F("dcx2V2a", "dcx2 V2 phys22", 50, 0, 5);
   TH1F* hdcx2V2b = new TH1F("dcx2V2b", "dcx2 V2 phys14", 50, 0, 5);
   hdcx2V2a->SetLineColor(4);
   hdcx2V2b->SetLineColor(2);
   
//===============================================================
   TH1F* hdcx1Xta = new TH1F("dcx1Xta", "dcx1 X t phys22", 200, 5500, 5800);
   TH1F* hdcx1Xtb = new TH1F("dcx1Xtb", "dcx1 X t phys14", 200, 5500, 5800);
   hdcx1Xta->SetLineColor(4);
   hdcx1Xtb->SetLineColor(2);
   
   TH1F* hdcx1Uta = new TH1F("dcx1Uta", "dcx1 U t phys22", 200, 5500, 5800);
   TH1F* hdcx1Utb = new TH1F("dcx1Utb", "dcx1 U t phys14", 200, 5500, 5800);
   hdcx1Uta->SetLineColor(4);
   hdcx1Utb->SetLineColor(2);
   
   TH1F* hdcx1Vta = new TH1F("dcx1Vta", "dcx1 V t phys22", 200, 5500, 5800);
   TH1F* hdcx1Vtb = new TH1F("dcx1Vtb", "dcx1 V t phys14", 200, 5500, 5800);
   hdcx1Vta->SetLineColor(4);
   hdcx1Vtb->SetLineColor(2);
   
   TH1F* hdcx2U1ta = new TH1F("dcx2U1ta", "dcx2 U1 t phys22", 200, 5500, 5800);
   TH1F* hdcx2U1tb = new TH1F("dcx2U1tb", "dcx2 U1 t phys14", 200, 5500, 5800);
   hdcx2U1ta->SetLineColor(4);
   hdcx2U1tb->SetLineColor(2);
   
   TH1F* hdcx2U2ta = new TH1F("dcx2U2ta", "dcx2 U2 t phys22", 200, 5500, 5800);
   TH1F* hdcx2U2tb = new TH1F("dcx2U2tb", "dcx2 U2 t phys14", 200, 5500, 5800);
   hdcx2U2ta->SetLineColor(4);
   hdcx2U2tb->SetLineColor(2);
   
   TH1F* hdcx2V1ta = new TH1F("dcx2V1ta", "dcx2 V1 t phys22", 200, 5500, 5800);
   TH1F* hdcx2V1tb = new TH1F("dcx2V1tb", "dcx2 V1 t phys14", 200, 5500, 5800);
   hdcx2V1ta->SetLineColor(4);
   hdcx2V1tb->SetLineColor(2);
   
   TH1F* hdcx2V2ta = new TH1F("dcx2V2ta", "dcx2 V2 t phys22", 200, 5500, 5800);
   TH1F* hdcx2V2tb = new TH1F("dcx2V2tb", "dcx2 V2 t phys14", 200, 5500, 5800);
   hdcx2V2ta->SetLineColor(4);
   hdcx2V2tb->SetLineColor(2);
   
//===============================================================
   TCanvas* cDCX1X2 = new TCanvas("cDCX1X2", "DCX1 X2 DT-DL", 100,50, 1000,800);
   cDCX1X2->Divide(4,4);
   
   TCut cut = "coinReg.Test(1)==1";
   
   cDCX1X2->cd(4);
   phys22->Draw("eventheader.fRunNumber>>runNum1", cut);
   phys14->Draw("eventheader.fRunNumber>>runNum2", cut,"same");
   
   cDCX1X2->cd(1);
   phys22->Draw("dcx1_x.fDriftLength>>dcx1Xa", cut);
   phys14->Draw("dcx1_x.fDriftLength>>dcx1Xb", cut,"same");
   
   cDCX1X2->cd(2);
   phys22->Draw("dcx1_u.fDriftLength>>dcx1Ua", cut);
   phys14->Draw("dcx1_u.fDriftLength>>dcx1Ub", cut,"same");

   cDCX1X2->cd(3);
   phys22->Draw("dcx1_v.fDriftLength>>dcx1Va", cut);
   phys14->Draw("dcx1_v.fDriftLength>>dcx1Vb", cut,"same");
   
   cDCX1X2->cd(5);
   phys22->Draw("dcx2_u1.fDriftLength>>dcx2U1a", cut);
   phys14->Draw("dcx2_u1.fDriftLength>>dcx2U1b", cut,"same");
   
   cDCX1X2->cd(6);
   phys22->Draw("dcx2_u2.fDriftLength>>dcx2U2a", cut);
   phys14->Draw("dcx2_u2.fDriftLength>>dcx2U2b", cut,"same");
   
   cDCX1X2->cd(7);
   phys22->Draw("dcx2_v1.fDriftLength>>dcx2V1a", cut);
   phys14->Draw("dcx2_v1.fDriftLength>>dcx2V1b", cut,"same");
   
   cDCX1X2->cd(8);
   phys22->Draw("dcx2_v2.fDriftLength>>dcx2V2a", cut);
   phys14->Draw("dcx2_v2.fDriftLength>>dcx2V2b", cut,"same");
   
//==================================================================
   cDCX1X2->cd(9);
   phys22->Draw("dcx1_x.fTiming>>dcx1Xta", cut);
   phys14->Draw("dcx1_x.fTiming>>dcx1Xtb", cut,"same");
   
   cDCX1X2->cd(10);
   phys22->Draw("dcx1_u.fTiming>>dcx1Uta", cut);
   phys14->Draw("dcx1_u.fTiming>>dcx1Utb", cut,"same");

   cDCX1X2->cd(11);
   phys22->Draw("dcx1_v.fTiming>>dcx1Vta", cut);
   phys14->Draw("dcx1_v.fTiming>>dcx1Vtb", cut,"same");
   
   cDCX1X2->cd(13);
   phys22->Draw("dcx2_u1.fTiming>>dcx2U1ta", cut);
   phys14->Draw("dcx2_u1.fTiming>>dcx2U1tb", cut,"same");
   
   cDCX1X2->cd(14);
   phys22->Draw("dcx2_u2.fTiming>>dcx2U2ta", cut);
   phys14->Draw("dcx2_u2.fTiming>>dcx2U2tb", cut,"same");
   
   cDCX1X2->cd(15);
   phys22->Draw("dcx2_v1.fTiming>>dcx2V1ta", cut);
   phys14->Draw("dcx2_v1.fTiming>>dcx2V1tb", cut,"same");
   
   cDCX1X2->cd(16);
   phys22->Draw("dcx2_v2.fTiming>>dcx2V2ta", cut);
   phys14->Draw("dcx2_v2.fTiming>>dcx2V2tb", cut,"same");
   return ;
}
