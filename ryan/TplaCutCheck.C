
void TplaCutCheck() {
   
//############################################################################   
   const char* rootfile="Rphys25FUp_test.root"; 
   TFile *f = new TFile(rootfile,"read");
   TTree *recoil = (TTree*)f->Get("recoil");
   
   Double_t tRange[2] = {0, 50};
   Double_t QRange[2] = {0, 3500};
   
//############################################################################   
   Int_t Xdiv = 2, Ydiv = 1;
   Double_t padSize = 450;
   TCanvas* cTplaCutCheck = new TCanvas("cTplaCutCheck", "Check of Tpla PID Cut", 10, 50, padSize*Xdiv, padSize*Ydiv);
   cTplaCutCheck->Divide(Xdiv,Ydiv);
   
   gStyle->SetOptStat(0);
   
   TH2F* hTplaL = new TH2F("TplaL","Tpla-L PID" ,300, tRange[0], tRange[1], 300 , QRange[0], QRange[1]);
   TH2F* hTplaR = new TH2F("TplaR","Tpla-R PID" ,300, tRange[0], tRange[1], 300 , QRange[0], QRange[1]);

//############################################################################

   TCutG *TplaPID1 = new TCutG("TplaPID1",5);
   TplaPID1->SetVarX("tof1");
   TplaPID1->SetVarY("Q1");
   TplaPID1->SetPoint(0,19.,3000.);
   TplaPID1->SetPoint(1,13.,1600.);
   TplaPID1->SetPoint(2, 2., 600.);
   TplaPID1->SetPoint(3,50., 600.);
   TplaPID1->SetPoint(4,35.,2400.);
   TplaPID1->SetPoint(5,19.,3000.);

   TCutG *TplaPID2 = new TCutG("TplaPID2",5);
   TplaPID2->SetVarX("tof2");
   TplaPID2->SetVarY("Q2");
   TplaPID2->SetPoint(0,19.,3000.);
   TplaPID2->SetPoint(1,14.,1600.);
   TplaPID2->SetPoint(2, 3., 600.);
   TplaPID2->SetPoint(3,50., 600.);
   TplaPID2->SetPoint(4,35.,2400.);
   TplaPID2->SetPoint(5,19.,3000.);

   
//#########################################################
   
   cTplaCutCheck->cd(1);
   recoil->Draw("Q1:tof1>>TplaL","", "colz");
   TplaPID1->Draw("same");
   cTplaCutCheck->cd(2);
   recoil->Draw("Q2:tof2>>TplaR","", "colz");
   TplaPID2->Draw("same");
   
 
   return ;
}
