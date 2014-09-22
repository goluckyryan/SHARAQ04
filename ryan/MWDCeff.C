
void MWDCeff() {

//############################################################################  
//   const char* rootfile="PrimaryData/phys23F.root"; 
   const char* rootfile="23F_0916_all.root"; 
   
   Bool_t allentry  = 0;
   Int_t firstEntry = 0;
   Int_t nEntries=100000;

   Int_t threshold = 700;
   Bool_t TplaGate = 0;

//############################################################################
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded.\n",rootfile);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totEntries = tree->GetEntries();
   if(allentry){
     firstEntry = 0;
     nEntries = totEntries;
   }
   printf("totEntries:%d, nEntries:%.d [%5.2f%%]\n", totEntries, nEntries, 100.*nEntries/totEntries);
   
//############################################################################  
   TCanvas * cMWDC = new TCanvas("cMWDC", "MWDC efficiency", 100, 50, 1600, 600);
   cMWDC->Divide(4,2);

   gStyle->SetOptStat(0);
   TString hQLTitle;
   hQLTitle.Form("%s | TDiff Gate:%d | QL", rootfile, TplaGate);
   TH1F * hQL  = new TH1F("hQL", hQLTitle, 300, 0, 3000);
   TH1F * hQR  = new TH1F("hQR", "QR", 300, 0, 3000);
 
   TH1F * hQLg  = new TH1F("hQLg", "QL gate:ValidPlane==0", 300, 0, 3000);
   TH1F * hQRg  = new TH1F("hQRg", "QR gate:ValidPlane==0", 300, 0, 3000);
   hQLg->SetLineColor(2);
   hQRg->SetLineColor(2);

   TH1F * hVPL = new TH1F("hVPL", "Valid Plane L", 6,  1, 7);
   TH1F * hVPR = new TH1F("hVPR", "Valid Plane R", 6,  1, 7);

   TH1F * hGoodL = new TH1F("hGoodL", "IsGood() L", 2, 0, 2); 
   TH1F * hGoodR = new TH1F("hGoodR", "IsGood() R", 2, 0, 2);
   hGoodL->SetMinimum(0);
   hGoodR->SetMinimum(0);

   TH2F * hGood = new TH2F("hGood", "IsGood() L and R", 2, 0, 2, 2, 0, 2);
   
   TCut aux = "gate.Test(0)";
   TCut cutL = "";
   TCut cutR = "";
   TCut cutLR = "";
   if(TplaGate){
     cutL = "TMath::Abs(plaV775.fTDiff+4)<2";
     cutR = "TMath::Abs(plaV775.fTDiff-2)<2";
     cutLR = "TMath::Abs(plaV775[2].fTDiff+4)<2 && TMath::Abs(plaV775[3].fTDiff-2)<2";
   }

   cutL.Print();
   cutR.Print();
   cutLR.Print();

//############################################################################   
   
   cMWDC->cd(1);
   tree->Draw("plaV775.fCharge>>hQL", "plaV775.GetDetID()==0 && smwdc_L[0].fNPlaneValid" && cutL && aux, "", nEntries, firstEntry);
   tree->Draw("plaV775.fCharge>>hQLg", "plaV775.GetDetID()==0 && smwdc_L[0].fNPlaneValid==0" && cutL && aux, "same", nEntries, firstEntry);

   cMWDC->cd(2);
   tree->Draw("smwdc_L[0].fNPlaneValid>>hVPL", "plaV775.GetDetID()==0 && smwdc_L[0].fNPlaneValid" && cutL && aux, "", nEntries, firstEntry);

   cMWDC->cd(3);
   tree->Draw("smwdc_L[0].IsGood()>>hGoodL", "plaV775.GetDetID()==0 && smwdc_L[0].fNPlaneValid" && cutL && aux,"", nEntries, firstEntry); 

   cMWDC->cd(5);
   tree->Draw("plaV775.fCharge>>hQRg", "plaV775.GetDetID()==1 && smwdc_R[0].fNPlaneValid==0" && cutR && aux, "",  nEntries, firstEntry);
   tree->Draw("plaV775.fCharge>>hQR", "plaV775.GetDetID()==1 && smwdc_R[0].fNPlaneValid" && cutR && aux, "same", nEntries, firstEntry);

   cMWDC->cd(6);
   tree->Draw("smwdc_R[0].fNPlaneValid>>hVPR", "plaV775.GetDetID()==1 && smwdc_R[0].fNPlaneValid" && cutR && aux, "", nEntries, firstEntry);

   cMWDC->cd(7);
   tree->Draw("smwdc_R[0].IsGood()>>hGoodR", "plaV775.GetDetID()==1 && smwdc_R[0].fNPlaneValid" && cutR && aux, "",nEntries, firstEntry); 

   cMWDC->cd(4);
   // incorrect cout. a event may be count twice or count once.
   tree->Draw("smwdc_R[0].IsGood():smwdc_L[0].IsGood()>>hGood", "plaV775.GetDetID()<=1 && smwdc_L[0].fNPlaneValid && smwdc_R[0].fNPlaneValid" && cutLR && aux, "colz", nEntries, firstEntry);

//###############################################################################   
   TLatex text;
   text.SetNDC();
   TString textStr;
   TLine line;
   line.SetLineColor(kGreen);
   line.SetLineWidth(1);

   Int_t countPlaL800, countPlaL;
   Int_t countPlaR800, countPlaR;
   
   countPlaL800 = hQLg->GetEntries() - hQLg->Integral(1, threshold/10);
   countPlaL    = hQL->GetEntries();

   countPlaR800 = hQRg->GetEntries() - hQRg->Integral(1, threshold/10);
   countPlaR    = hQR->GetEntries();

   cMWDC->cd(1);
   text.SetTextColor(kBlue);
   textStr.Form("mwdc fired:%d",countPlaL);text.DrawText(0.5,0.7, textStr);
   text.SetTextColor(kRed);
   textStr.Form("Q>%d:%d",threshold,countPlaL800);text.DrawText(0.5,0.6, textStr);
   line.DrawLine(threshold,0,threshold,hQL->GetMaximum()/2);

   cMWDC->cd(5);
   text.SetTextColor(kBlue);
   textStr.Form("mwdc fired:%d",countPlaR);text.DrawText(0.5,0.7, textStr);
   text.SetTextColor(kRed);
   textStr.Form("Q>%d:%d",threshold,countPlaR800);text.DrawText(0.5,0.6, textStr);
   line.DrawLine(threshold,0,threshold,hQR->GetMaximum()/2);



   cMWDC->cd(2);
   TF1 *fitL = new TF1("fitL", Binomial_dist, 1, 6, 2); 
   fitL->SetParameters(hVPL->GetEntries(), 0.94);
   hVPL->Fit("fitL","Q");
   text.SetTextColor(kBlue);
   textStr.Form("Eff_{fire}:%5.2f%%(%5.2f%%)",100.*fitL->GetParameter(1),100.*fitL->GetParError(1));text.DrawLatex(0.2,0.7, textStr);
   textStr.Form("N_{0}(exp):%.0f",hVPL->GetEntries());text.DrawLatex(0.2,0.6, textStr);
   textStr.Form("N_{0}(fit):%.0f(%.0f)",fitL->GetParameter(0),fitL->GetParError(0));text.DrawLatex(0.2,0.55, textStr);   
   
   cMWDC->cd(6);
   TF1 *fitR = new TF1("fitR", Binomial_dist, 1, 6, 2); 
   fitR->SetParameters(hVPR->GetEntries(), 0.94);
   hVPR->Fit("fitR","Q");
   textStr.Form("Eff_{fire}:%5.2f%%(%5.2f%%)",100.*fitR->GetParameter(1),100.*fitR->GetParError(1));text.DrawLatex(0.2,0.7, textStr);
   textStr.Form("N_{0}(exp):%.0f",hVPR->GetEntries());text.DrawLatex(0.2,0.6, textStr);
   textStr.Form("N_{0}(fit):%.0f(%.0f)",fitR->GetParameter(0), fitR->GetParError(0));text.DrawLatex(0.2,0.55, textStr);

   Int_t countGoodL, countGoodR;
   countGoodL=hGoodL->GetBinContent(2);
   countGoodR=hGoodR->GetBinContent(2);

   cMWDC->cd(3);
   textStr.Form("%d",countGoodL);text.DrawLatex(0.7,0.7, textStr);
   textStr.Form("%.0f",hGoodL->GetBinContent(1));text.DrawLatex(0.2,0.7, textStr);
   textStr.Form("Track_{eff}:%5.2f%%",100*hGoodL->GetBinContent(2)/hGoodL->GetEntries());text.DrawLatex(0.55,0.6, textStr);
   
   cMWDC->cd(7);
   textStr.Form("%d",countGoodR);text.DrawLatex(0.7,0.7, textStr);
   textStr.Form("%.0f",hGoodR->GetBinContent(1));text.DrawLatex(0.2,0.7, textStr);
   textStr.Form("Track_{eff}:%5.2f%%",100*hGoodR->GetBinContent(2)/hGoodR->GetEntries());text.DrawLatex(0.55,0.6, textStr);
   
   
   Int_t countGood, countGoodLR;
   countGood = hGood->GetBinContent(2,2); // L:not
   countGoodLR = hGood->GetEntries();  

   cMWDC->cd(4);
   text.SetNDC(0);
   text.SetTextColor(kBlack);
   textStr.Form("%.0f",hGood->GetBinContent(1,1));text.DrawLatex(0.5,0.5, textStr);
   textStr.Form("%.0f",hGood->GetBinContent(1,2));text.DrawLatex(0.5,1.5, textStr);
   textStr.Form("%.0f",hGood->GetBinContent(2,1));text.DrawLatex(1.5,0.5, textStr);
   textStr.Form("%.0f",hGood->GetBinContent(2,2));text.DrawLatex(1.5,1.5, textStr);
   


   Double_t fireEffPlaL = 1.*countPlaL/(countPlaL+countPlaL800), fireEffPlaR = 1.*countPlaR/(countPlaR+countPlaR800);
   Int_t N0expL = hVPL->GetEntries(), N0expR = hVPR->GetEntries();
   Int_t N0fitL = fitL->GetParameter(0), N0fitR = fitR->GetParameter(0);
   Double_t fireEffL = 1-TMath::Power(1-fitL->GetParameter(1),6), fireEffR = 1-TMath::Power(1-fitR->GetParameter(1),6);
   Double_t trackEffL = 1.*countGoodL/hGoodL->GetEntries(), trackEffR = 1.*countGoodR/hGoodR->GetEntries();
   Double_t DetEffL = fireEffL*trackEffL, DetEffR = fireEffR*trackEffR;
   
   printf("fire eff (pla) :%5.2f%%, %5.2f%%\n", fireEffPlaL*100., fireEffPlaR*100.);
   printf("fire eff (mwdc):%5.2f%%, %5.2f%%\n", fireEffL*100., fireEffR*100.);
   printf("tracking eff   :%5.2f%%, %5.2f%%, %5.2f%%, %5.2f%%\n", 100.*trackEffL, 100.*trackEffR, 100.*trackEffL*trackEffR, 100.*countGood/countGoodLR );
   printf("Detect eff     :%5.2f%%, %5.2f%%, %5.2f%%\n", 100.*DetEffL, 100.*DetEffR, 100.*DetEffL*DetEffR);

   printf("N0exp/N0fit    :%5.2f%%, %5.2f%%\n", 100.*N0expL/N0fitL, 100.*N0expR/N0fitR);

   return ;
}


Double_t Binomial_dist(Double_t *x, Double_t *para){
   Int_t N = 6;
   Int_t arg;
   if( para[1]) arg = TMath::Floor(x[0]); 
   return para[0]* TMath::Binomial(N,arg) * TMath::Power(para[1],arg) * TMath::Power((1-para[1]), N-arg);
}
