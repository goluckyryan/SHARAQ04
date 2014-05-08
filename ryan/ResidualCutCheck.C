
void ResidualCutCheck() {
   
//############################################################################   
   const char* rootfile="CrystalPos.root"; // require simple tree
   TFile *f = new TFile(rootfile,"read");
   TTree *recoil = (TTree*)f->Get("recoil");
   
   Double_t tRange[2] = {-134, -125};
   Double_t QRange[2] = {2000, 3500};
   
//############################################################################   
   Int_t Xdiv = 2, Ydiv = 1;
   Double_t padSize = 450;
   TCanvas* cCryPos = new TCanvas("cCryPos", "Crystal Position", 10, 50, padSize*Xdiv, padSize*Ydiv);
   cCryPos->Divide(Xdiv,Ydiv);
   
   gStyle->SetOptStat(0);
   TH2F* hPIDUS = new TH2F("PIDUS","PID US g:PID" ,300, -1500, -1410, 300 , 5000, 6500);
   
   TH2F* hPIDDS = new TH2F("PIDDS","PID DS g:PID" ,300, tRange[0], tRange[1], 300 , QRange[0], QRange[1]);

//############################################################################

//============================= 14O
/*   
   TCutG *ResO = new TCutG("ResO",4);
   ResO->SetVarX("tofS0D");
   ResO->SetVarY("QS0D");
   ResO->SetPoint(0,-69.4,2059.1);
   ResO->SetPoint(1,-69.2,1821.6);
   ResO->SetPoint(2,-64.3,2465.7);
   ResO->SetPoint(3,-66.7,2450.7);
   ResO->SetPoint(4,-69.4,2059.1);
   
   TCutG *ResN = new TCutG("ResN",5);
   ResN->SetVarX("tofS0D");
   ResN->SetVarY("QS0D");
   ResN->SetPoint(0,-69.2,1821.6);
   ResN->SetPoint(1,-69.0,1648.8);
   ResN->SetPoint(2,-66.4,1956.2);
   ResN->SetPoint(3,-62.9,2389.4);
   ResN->SetPoint(4,-64.3,2465.7);
   ResN->SetPoint(5,-69.2,1821.6);
   
   TCutG *ResC = new TCutG("ResC",6);
   ResC->SetVarX("tofS0D");
   ResC->SetVarY("QS0D");
   ResC->SetPoint(0,-69.0,1648.8);
   ResC->SetPoint(1,-68.8,1423.0);
   ResC->SetPoint(2,-66.4,1635.3);
   ResC->SetPoint(3,-61.8,2257.3);
   ResC->SetPoint(4,-62.9,2389.4);
   ResC->SetPoint(5,-66.4,1956.2);
   ResC->SetPoint(6,-69.0,1648.8);

   TCut ppcoin = " ((coinReg>=20 && coinReg<40)|| coinReg>=60)&& (ResN || ResC)";
   TCut beamTrig = "coinReg>=10 && coinReg<20 && ResO";
*/

//================================= 25F
   
   TCutG *ResF = new TCutG("ResF",4);
   ResF->SetVarX("tofS0D");
   ResF->SetVarY("QS0D");
   ResF->SetPoint(0,-133.08,2521.8);
   ResF->SetPoint(1,-132.72,2310.2);
   ResF->SetPoint(2,-126.73,3230.0);
   ResF->SetPoint(3,-127.61,3459.8);
   ResF->SetPoint(4,-133.08,2521.8);
   
   TCutG *ResO = new TCutG("ResO",4);
   ResO->SetVarX("tofS0D");
   ResO->SetVarY("QS0D");
   ResO->SetPoint(0,-132.72,2310.2);
   ResO->SetPoint(1,-132.38,2178.5);
   ResO->SetPoint(2,-126.38,3000.0);
   ResO->SetPoint(3,-126.73,3230.0);
   ResO->SetPoint(4,-132.72,2310.2);
   
   TCut ppcoin = "(coinReg>=20 && coinReg<40)|| coinReg>=60";
   TCut beamTrig = "coinReg>=10 && coinReg<20";

   
//#########################################################
   
   cCryPos->cd(1);
   recoil->Draw("QUS:tofUS>>PIDUS","", "colz");
   cCryPos->cd(2);
   recoil->Draw("QS0D:tofS0D>>PIDDS",ppcoin, "colz");
   ResF->Draw("same");
   ResO->Draw("same");
   
 
   return ;
}
