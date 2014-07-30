#include "TBeamData.h"
#include "RelCalculator.h"

void Ana_14O_Simple() {
   const char* rootfile="Rphys14All.root";
   TFile *f = new TFile(rootfile,"read");
   TTree *recoil = (TTree*)f->Get("recoil");
   TBeamData *beam = new TBeamData("14O");
   printf("=================================================\n");
   printf(" >>> %s <<< loaded. \n", rootfile);
   printf("====== totnumEntry:%d\n",recoil->GetEntries());
   
   Int_t Xdiv = 4, Ydiv = 4;
   Double_t padSize = 400;
   TCanvas* cAna = new TCanvas("cAna", "Analysis", 600, 500, padSize*Xdiv, padSize*Ydiv);
   cAna->Divide(Xdiv,Ydiv);
   
   Double_t center[2]={0, 0}; 
   Double_t radius = 7.;
   Double_t beamZRange[2]     = { -8, 40 }; // min, max , central gate
   Double_t beamZRangeSide[2] = { -50, 100 };
   Int_t EtotGateMin = 10;
   Double_t OpAngGateRange[2]={85,10}; // central, half-width
   
   Int_t SpnBin = 150;
   Double_t SpRange[2] = {-50, 100}; //MeV
   Int_t hDthetaBin = 30;
   Double_t hDthetaRange[2]={70,100};

//==========================================================
   Double_t resol = (SpRange[1]-SpRange[0])/SpnBin; //MeV
   Double_t Principle_tof = tofByBrho(L_F3FH9,beam->fBrho, beam->fMass, beam->fZ);
   
   TH2F* hPIDUS   = new TH2F("PIDUS"  , "PID UpStream", 100, Principle_tof*0.9 , Principle_tof*1.1, 100, beam->fQGate[0]*0.9, beam->fQGate[1]*1.1);
   TH1F* hcoinReg = new TH1F("coinReg", "coinReg, beam+=10, ppcoin+=20, NDcoin+=40, Other+=1", 80, 0, 80);
   TH2F* hS0img   = new TH2F("S0img"  , "S0 img"                           , 30, -15,  15, 30,  -15,  15);
   
   TH2F* hPID1    = new TH2F("PID1"   , "PID Tpla1" ,   200,  0, 50, 200, 600, 3000);  
   TH2F* hPID2    = new TH2F("PID2"   , "PID Tpla2" ,   200,  0, 50, 200, 600, 3000);
   
   TH1F* hEtot     = new TH1F("Etot"     , "E1+E2"  ,   50,  0, 400);
   TH1F* hEtotsg   = new TH1F("Etotsg"   , "E1+E2"  ,   50,  0, 400);
   TH1F* hEtotbg   = new TH1F("Etotbg"   , "E1+E2"  ,   50,  0, 400);
   hEtot->SetLineColor(3);
   hEtot->SetYTitle("count/8 MeV");
   hEtotsg->SetLineColor(4);
   hEtotbg->SetLineColor(2);

   TH1F* hDthetasgN  = new TH1F("DthetasgN"  , "Open Angle Res(N)"       , hDthetaBin, hDthetaRange[0], hDthetaRange[1]);
   TH1F* hDthetabgN  = new TH1F("DthetabgN"  , "Open Angle Res(N)"       , hDthetaBin, hDthetaRange[0], hDthetaRange[1]);
   TH1F* hDthetasubN = new TH1F("DthetasubN" , "Open ANgle sub Res(N)"   , hDthetaBin, hDthetaRange[0], hDthetaRange[1]);
   hDthetasgN->SetLineColor(4);
   TString hDthetaYTitle;
   hDthetaYTitle.Form("count/%3.1f deg", (hDthetaRange[1]-hDthetaRange[0])/hDthetaBin );
   hDthetasgN->SetYTitle(hDthetaYTitle.Data());
   hDthetabgN->SetLineColor(2);
   hDthetasubN->SetFillColor(4);
   
   TH1F* hDthetasgC  = new TH1F("DthetasgC"  , "Open Angle Res(C)"       , hDthetaBin, hDthetaRange[0], hDthetaRange[1]);
   TH1F* hDthetabgC  = new TH1F("DthetabgC"  , "Open Angle Res(C)"       , hDthetaBin, hDthetaRange[0], hDthetaRange[1]);
   TH1F* hDthetasubC = new TH1F("DthetasubC" , "Open ANgle sub Res(C)"   , hDthetaBin, hDthetaRange[0], hDthetaRange[1]);
   hDthetasgC->SetLineColor(4);
   TString hDthetaYTitle;
   hDthetaYTitle.Form("count/%3.1f deg", (hDthetaRange[1]-hDthetaRange[0])/hDthetaBin );
   hDthetasgC->SetYTitle(hDthetaYTitle.Data());
   hDthetabgC->SetLineColor(2);
   hDthetasubC->SetFillColor(4);
   
   TH1F* hwBeamZ    = new TH1F("wBeamZ"   , "weighted beamZ"  , 300, -100, 200);
   TH1F* hwBeamZsg  = new TH1F("wBeamZsg" , "weighted beamZ g:p2p"  , 300, -100, 200);
   TH1F* hwBeamZbg  = new TH1F("wBeamZbg" , "weighted beamZ g:BG"  , 300, -100, 200);
   hwBeamZ->SetLineColor(3);
   hwBeamZsg->SetLineColor(4);
   hwBeamZbg->SetLineColor(2);
   
   TH2F * hSpEtot  = new TH2F("SpEtot", "Sp vs Etot g:p2p x Res(N)", 50, 0 , 400, SpnBin, SpRange[0], SpRange[1]);
   hSpEtot->SetXTitle("Etot");
   hSpEtot->SetYTitle("Sp");
   
   TH2F * hPIDDS       = new TH2F("PIDDS", "PIDDS g:p2p", 300, -70,  -60, 300 ,  500, 2700);
   TH2F * hPIDDS1      = new TH2F("PIDDS1", "PIDDS g:p2p x Res(H)", 300, -70,  -60, 300 ,   500, 2700);
   TH2F * hPIDDS2      = new TH2F("PIDDS2", "PIDDS g:p2p x Res(O)", 300, -70,  -60, 300 ,   500, 2700);
   TH2F * hPIDDS3      = new TH2F("PIDDS3", "PIDDS g:p2p x Res(N)", 300, -70,  -60, 300 ,   500, 2700);
   TH2F * hPIDDS4      = new TH2F("PIDDS4", "PIDDS g:p2p x Res(C)", 300, -70,  -60, 300 ,   500, 2700);      
   
   TH1F* hSp3   = new TH1F("Sp3","Sp g:p2p x Res(N)"   ,SpnBin, SpRange[0], SpRange[1]);
   TH1F* hSp4   = new TH1F("Sp4","Sp g:p2p x Res(C)"   ,SpnBin, SpRange[0], SpRange[1]);
   TH1F* hSp3bg   = new TH1F("Sp3bg","Sp g:BG x Res(N)"   ,SpnBin, SpRange[0], SpRange[1]);
   TH1F* hSp4bg   = new TH1F("Sp4bg","Sp g:BG x Res(C)"   ,SpnBin, SpRange[0], SpRange[1]);
   hSp3->SetMinimum(0);
   hSp4->SetMinimum(0);
   hSp3bg->SetLineColor(2);
   hSp4bg->SetLineColor(2);
   TString SpYTitleStr;
   SpYTitleStr.Form("count / %3.1f MeV",resol);
   hSp3->SetYTitle(SpYTitleStr.Data());
   hSp4->SetYTitle(SpYTitleStr.Data());
   
   TH1F* hSp3sub   = new TH1F("Sp3sub","Sp sub Res(N)"   ,SpnBin, SpRange[0], SpRange[1]);
   TH1F* hSp4sub   = new TH1F("Sp4sub","Sp sub Res(C)"   ,SpnBin, SpRange[0], SpRange[1]);
   hSp3sub->SetFillColor(4);
   hSp4sub->SetFillColor(4);

//=========== Cut   
   TCut ppcoin = "(coinReg >=20 && coinReg <40) || coinReg>=60";
   TString crystalTitle;
   crystalTitle.Form("TMath::Power(s0x-%4.2f,2) + TMath::Power(s0y-%4.2f,2) < %7.2f", center[0], center[1], radius*radius);
   TCut crystal = crystalTitle;
   
   TCutG *ResH = new TCutG("ResH",4);
   ResH->SetVarX("tofS0D");
   ResH->SetVarY("QS0D");
   ResH->SetPoint(0,-65.6,600.);
   ResH->SetPoint(1,-64. ,528.);
   ResH->SetPoint(2,-60. ,640.);
   ResH->SetPoint(3,-63. ,660.);
   ResH->SetPoint(4,-65.6,600.);
   
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

   TString beamZGate1Title;
   TString beamZGate2Title;
   beamZGate1Title.Form("wbeamZ>%7.2f && wbeamZ<%7.2f", beamZRange[0], beamZRange[1]);
   beamZGate2Title.Form("(wbeamZ>%7.2f && wbeamZ<%7.2f) || (wbeamZ>%7.2f && wbeamZ<%7.2f)", 
              beamZRangeSide[0], 
              beamZRange[0], 
              beamZRange[1],
              beamZRangeSide[1]);
   TCut Ext1 = beamZGate1Title;
   TCut Ext2 = beamZGate2Title;
   
   TString OpAngGateTitle;
   OpAngGateTitle.Form("TMath::Abs((theta1+theta2)*TMath::RadToDeg()-%4.1f)<%4.1f",OpAngGateRange[0],OpAngGateRange[1]);
   TCut OpenAngGate = OpAngGateTitle;
   TString EtotGateTitle;
   EtotGateTitle.Form("E1+E2>%4d",EtotGateMin);
   TCut EtotGate   = EtotGateTitle;
   TCut PIDUS      = "TMath::Finite(tof_usV1190)";
   
   //TCut common = ppcoin + crystal + EtotGate + OpenAngGate + "TplaPID1 && TplaPID2";
   //TCut common = PIDUS + ppcoin + crystal + EtotGate +  "TplaPID1 && TplaPID2";
   //TCut common = PIDUS + ppcoin + crystal +  "TplaPID1 && TplaPID2";
   //TCut common = PIDUS + ppcoin + "TplaPID1 && TplaPID2";
   //TCut common = PIDUS + ppcoin + crystal;
   TCut common = PIDUS + crystal;
   TCut SignalGate = common + Ext1 + "ResN";
   TCut BGGate = common + Ext2 + "ResN";
   
   common.Print();
   SignalGate.Print();
   BGGate.Print();
   
   TLatex text;
   text.SetNDC();
   text.SetTextColor(1);
   TString textStr;
//=====================================
   cAna->cd(1);
   recoil->Draw("Q_us:tof_usV1190>>PIDUS",SignalGate,"colz");
   //recoil->Draw("coinReg>>coinReg");
   textStr.Form("%s",rootfile);
   text.DrawText(0.2, 0.2, textStr);
   cAna->cd(2);
   recoil->Draw("s0y:s0x>>S0img",SignalGate,"colz");
   textStr.Form("(%4.2f,%4.2f|%4.2f)",center[0],center[1],radius);
   text.DrawText(0.2, 0.2, textStr);
   TLine line;
   Int_t nPt = 20;
   for ( Int_t i = 0; i < nPt; i++){
      line.DrawLine(center[0] + radius*TMath::Cos(2*TMath::Pi()*i/nPt),
                    center[1] + radius*TMath::Sin(2*TMath::Pi()*i/nPt),
                    center[0] + radius*TMath::Cos(2*TMath::Pi()*(i+1)/nPt),
                    center[1] + radius*TMath::Sin(2*TMath::Pi()*(i+1)/nPt));
   }
   cAna->cd(3);
   recoil->Draw("Q1:tof1>>PID1",SignalGate,"colz");
   cAna->cd(4);
   recoil->Draw("Q2:tof2>>PID2",SignalGate,"colz");
   
   cAna->cd(5);
   recoil->Draw("E1+E2>>Etot",common + "ResN","");
   recoil->Draw("E1+E2>>Etotsg",SignalGate ,"same");
   recoil->Draw("E1+E2>>Etotbg",BGGate ,"same");
   textStr.Form("E1+E2>%d",EtotGateMin);
   text.DrawText(0.2, 0.8, textStr);
   cAna->cd(6);
   recoil->Draw("wbeamZ>>wBeamZ",common + "ResN","");
   recoil->Draw("wbeamZ>>wBeamZsg",SignalGate,"same");
   recoil->Draw("wbeamZ>>wBeamZbg",BGGate,"same");
   textStr.Form("%4.1f<wbeamZ<%4.1f",beamZRange[0], beamZRange[1]);
   text.DrawText(0.2, 0.8, textStr);
   textStr.Form("(%4.1f<.<%4.1f) || (%4.1f<.<%4.1f)",beamZRangeSide[0],beamZRange[0], beamZRange[1],beamZRangeSide[1]); 
   text.DrawText(0.2, 0.7, textStr);
   
   cAna->cd(7);
   recoil->Draw("QS0D:tofS0D>>PIDDS1", common + "ResH","colz");
   recoil->Draw("QS0D:tofS0D>>PIDDS2", common + "ResO","colz same");
   recoil->Draw("QS0D:tofS0D>>PIDDS3", common + "ResN","colz same");
   recoil->Draw("QS0D:tofS0D>>PIDDS4", common + "ResC","colz same");
   
   cAna->cd(8);
   recoil->Draw("Sp:(E1+E2)>>SpEtot", SignalGate, "colz");
   
   cAna->cd(9);
   recoil->Draw("(theta1+theta2)*TMath::RadToDeg()>>DthetasgN",SignalGate,"colz");
   recoil->Draw("(theta1+theta2)*TMath::RadToDeg()>>DthetabgN",BGGate,"same");
   textStr.Form("%4.1f<OpAng<%4.1f",OpAngGateRange[0]- OpAngGateRange[1],OpAngGateRange[0]+OpAngGateRange[1]);
   text.DrawText(0.2, 0.8, textStr);
   hDthetasubN->Add(hDthetasgN, hDthetabgN, 1, -1);
   cAna->cd(10);
   hDthetasubN->Draw("");
   
   cAna->cd(11);
   recoil->Draw("(theta1+theta2)*TMath::RadToDeg()>>DthetasgC",common + Ext1 + "ResC","colz");
   recoil->Draw("(theta1+theta2)*TMath::RadToDeg()>>DthetabgC",common + Ext2 + "ResC","same");
   textStr.Form("%4.1f<OpAng<%4.1f",OpAngGateRange[0]- OpAngGateRange[1],OpAngGateRange[0]+OpAngGateRange[1]);
   text.DrawText(0.2, 0.8, textStr);
   hDthetasubC->Add(hDthetasgC, hDthetabgC, 1, -1);
   cAna->cd(12);
   hDthetasubC->Draw("");
  
   
   cAna->cd(13);
   recoil->Draw("Sp2>>Sp3",SignalGate ,"");
   recoil->Draw("Sp2>>Sp3bg",BGGate ,"same");
   cAna->cd(14);
   hSp3sub->Add(hSp3,hSp3bg, 1, -1);
   hSp3sub->Draw();
   cAna->cd(15);
   recoil->Draw("Sp2>>Sp4"  , common + Ext1 + "ResC","");
   recoil->Draw("Sp2>>Sp4bg", common + Ext2 + "ResC","same");
   cAna->cd(16);
   hSp4sub->Add(hSp4,hSp4bg, 1, -1);
   hSp4sub->Draw();

   gROOT->ProcessLine(".!date");
   return ;
}




