
void crystalPos() {
   
//############################################################################   
   const char* rootfile="CrystalPos.root"; // require simple tree
   TFile *f = new TFile(rootfile,"read");
   TTree *recoil = (TTree*)f->Get("recoil");
   
   Double_t tRange[2] = {-135, -125};
   Double_t QRange[2] = {1500, 3500};
   
//############################################################################   
   Int_t Xdiv = 5, Ydiv = 2;
   Double_t padSize = 300;
   TCanvas* cCryPos = new TCanvas("cCryPos", "Crystal Position", 100, 50, padSize*Xdiv, padSize*Ydiv);
   cCryPos->Divide(Xdiv,Ydiv);
   
   TH2F* hPIDUS   = new TH2F("PIDUS","PID US g:PID x S0D fired"   ,300, -1500, -1410, 300 , 5000, 6500);
   
   TH1F* hcoinRegBeam = new TH1F("coinRegBeam", "coinReg g:PID x beamTrigger x Res(F)", 80, 0, 80);
   TH1F* hcoinReg     = new TH1F("coinReg"    , "coinReg g:PID x ppcoin x Res(O)", 80, 0, 80);
   
   TH2F* hPIDDSBeam  = new TH2F("PIDDSBeam" ,"PID DS g:PID x beamTrig x Res(F)"    ,300, tRange[0], tRange[1], 300 , QRange[0], QRange[1]);  
   TH2F* hPIDDS      = new TH2F("PIDDS"     ,"PID DS g:PID x NNcoin x Res(O)" ,300, tRange[0], tRange[1], 300 , QRange[0], QRange[1]);
   
   Double_t s0range = 15;
   Int_t s0bin = 30;
   TH2F* hS0imgBeam   = new TH2F("S0imgBeam"   ,"S0img g:PID x beamTrig  x Res(F)",s0bin, -s0range, s0range, s0bin , -s0range, s0range);
   TH2F* hS0img       = new TH2F("S0img"       ,"S0img g:PID x ppcoin x Res(O)",s0bin, -s0range, s0range, s0bin , -s0range, s0range);
   TH2F* hS0imgRatio  = new TH2F("S0imgRatio"  ,"S0img ratio"       ,s0bin, -s0range, s0range, s0bin , -s0range, s0range);

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
   
   TCut ppcoin = " ((coinReg>=20 && coinReg<40)|| coinReg>=60)&& ResO";
   TCut beamTrig = "coinReg>=10 && coinReg<20 && ResF";
   
//#########################################################
   
   cCryPos->cd(1);
   recoil->Draw("QUS:tofUS>>PIDUS","", "colz");
   cCryPos->cd(2);
   recoil->Draw("coinReg>>coinRegBeam", beamTrig, "");
   cCryPos->cd(3);
   recoil->Draw("QS0D:tofS0D>>PIDDSBeam", beamTrig, "colz");
   cCryPos->cd(4);
   recoil->Draw("s0y:s0x>>S0imgBeam", beamTrig, "colz");
   
   cCryPos->cd(7);
   recoil->Draw("coinReg>>coinReg", ppcoin, "");
   cCryPos->cd(8);
   recoil->Draw("QS0D:tofS0D>>PIDDS", ppcoin, "colz");
   cCryPos->cd(9);
   recoil->Draw("s0y:s0x>>S0img", ppcoin, "colz");
   
   hS0imgRatio = DivideHist(hS0img, hS0imgBeam);
   cCryPos->cd(5);
   hS0imgRatio->Draw("colz");
   
   TLine line;
   Int_t nPt = 20;
   Double_t radius = 7;
   Double_t center[2] = {0, 1.9};
   for ( Int_t i = 0; i < nPt; i++){
      line.DrawLine(center[0] + radius*TMath::Cos(2*TMath::Pi()*i/nPt),
                    center[1] + radius*TMath::Sin(2*TMath::Pi()*i/nPt),
                    center[0] + radius*TMath::Cos(2*TMath::Pi()*(i+1)/nPt),
                    center[1] + radius*TMath::Sin(2*TMath::Pi()*(i+1)/nPt));
   }
   
   TLatex text;
   text.SetNDC();
   text.SetTextColor(1);
   TString textStr;
   textStr.Form("(%4.2f,%4.2f|%4.2f",center[0],center[1],radius);
   text.DrawText(0.2, 0.2, textStr);
   
   hS0imgRatio->ProjectionY("test",s0bin/2-1,s0bin/2+1);
   TString testTitle;
   testTitle.Form("CrystalPos ProjectY X=(%4.2f,%4.2f)",-s0range*2/s0bin, s0range*2/s0bin);
   test->SetTitle(testTitle);
   cCryPos->cd(10);
   test->Draw();
   return ;
}

TH2F * DivideHist(TH2F* hist1, TH2F* hist2){
   Int_t nBinX = hist1->GetNbinsX();
   Int_t nBinY = hist1->GetNbinsY();
   
   if ( nBinX != hist2->GetNbinsX() || nBinY != hist2->GetNbinsY() ) return 0;
   
   Double_t Xrange[2] = {hist1->GetXaxis()->GetXmin(), hist1->GetXaxis()->GetXmax()};
   Double_t Yrange[2] = {hist1->GetYaxis()->GetXmin(), hist1->GetYaxis()->GetXmax()};
   
   TString hName, hTitle;
   hName.Form("hR");
   hTitle.Form("%s/%s",hist1->GetName(),hist2->GetName()); 
   
   TH2F * hout = new TH2F(hName,hTitle, nBinX, Xrange[0],Xrange[1], nBinY, Yrange[0], Yrange[1]);
   
   Double_t x, y;
   for( Int_t i = 1; i <= nBinX ; i++){
      for (Int_t j = 1; j <= nBinY ; j++){
         x = hist1->GetBinCenter(i);
         y = hist1->GetBinCenter(j);
         if ( hist2->GetBinContent(i,j) == 0 ) continue;
         Double_t h1 = hist1->GetBinContent(i,j);
         Double_t h2 = hist2->GetBinContent(i,j);
         hout -> Fill(x,y, h1/h2);
      }  
   }

   return hout;

}
