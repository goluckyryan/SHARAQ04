#include "TBeamData.h"
#include "RelCalculator.h"

void Ana_25F_Simple() {
   const char* rootfile="Rphys25FAll.root";
   TFile *f = new TFile(rootfile,"read");
   TTree *recoil = (TTree*)f->Get("recoil");
   TBeamData *beam = new TBeamData("25F");
   printf("=================================================\n");
   printf(" >>> %s <<< loaded. \n", rootfile);
   printf("====== totnumEntry:%d\n",recoil->GetEntries());
   
   Int_t Xdiv = 4, Ydiv = 3;
   Double_t padSize = 400;
   TCanvas* cAna = new TCanvas("cAna", "Analysis", 200, 300, padSize*Xdiv, padSize*Ydiv);
   cAna->Divide(Xdiv,Ydiv);
   
   Double_t center[2]={0, 0}; 
   Double_t Aradius = 0., radius = 8.;
   Double_t beamZRange[2]     = { -60, 120 }; // min, max , central gate
   Double_t beamZRangeSide[2] = { -60, 120 };
   Int_t EtotGateMin = 100;
   Double_t OpAngGateRange[2]={83,10}; // central, half-width
   
   Int_t SpnBin = 50;
   Double_t SpRange[2] = {-50,100}; //MeV
   Int_t hDthetaBin = (OpAngGateRange[1]*2+4)*2;
   Double_t hDthetaRange[2]={OpAngGateRange[0]-OpAngGateRange[1]-2,OpAngGateRange[0]+OpAngGateRange[1]+2};

//==========================================================
   Double_t resol = (SpRange[1]-SpRange[0])/SpnBin; //MeV
   Double_t Principle_tof = tofByBrho(L_F3FH9,beam->fBrho, beam->fMass, beam->fZ);
   
   gStyle->SetOptStat(0);
   
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

   TH1F* hDthetasgO  = new TH1F("DthetasgO"  , "Open Angle Res(O)"       , hDthetaBin, hDthetaRange[0], hDthetaRange[1]);
   TH1F* hDthetabgO  = new TH1F("DthetabgO"  , "Open Angle Res(O)"       , hDthetaBin, hDthetaRange[0], hDthetaRange[1]);
   TH1F* hDthetasubO = new TH1F("DthetasubO" , "Open Angle sub Res(O)"   , hDthetaBin, hDthetaRange[0], hDthetaRange[1]);
   hDthetasgO->SetLineColor(4);
   hDthetasgO->SetMinimum(0);
   TString hDthetaYTitle;
   hDthetaYTitle.Form("count/%3.1f deg", (hDthetaRange[1]-hDthetaRange[0])/hDthetaBin );
   hDthetasgO->SetYTitle(hDthetaYTitle.Data());
   hDthetabgO->SetLineColor(2);
   hDthetasubO->SetFillColor(4);
   
   TH1F* hwBeamZ    = new TH1F("wBeamZ"   , "weighted beamZ"  , 300, -100, 200);
   TH1F* hwBeamZsg  = new TH1F("wBeamZsg" , "weighted beamZ g:p2p"  , 300, -100, 200);
   TH1F* hwBeamZbg  = new TH1F("wBeamZbg" , "weighted beamZ g:BG"  , 300, -100, 200);
   hwBeamZ->SetLineColor(3);
   hwBeamZsg->SetLineColor(4);
   hwBeamZbg->SetLineColor(2);
   
   TH2F * hSpEtot  = new TH2F("SpEtot", "Sp vs Etot g:p2p x Res(O)", 50, 0 , 400, SpnBin, SpRange[0], SpRange[1]);
   hSpEtot->SetXTitle("Etot");
   hSpEtot->SetYTitle("Sp");
   
   TH2F* hOpenAngSp  = new TH2F("OpenAngSp", "OpenAng vs Sp", SpnBin, SpRange[0], SpRange[1], hDthetaBin, hDthetaRange[0], hDthetaRange[1]);
   hOpenAngSp->SetXTitle("Sp");
   hOpenAngSp->SetYTitle("OpenAng");
   
   TH2F * hPIDDS   = new TH2F("PIDDS" , "PIDDS g:p2p"         , 300, -136,  -125, 300 ,  1500, 3500);
   TH2F * hPIDDS3  = new TH2F("PIDDS3", "PIDDS g:p2p x Res(O)", 300, -136,  -125, 300 ,  1500, 3500);   
   
   TH1F* hSp   = new TH1F("Sp","Sp g:p2p x Res(O)"   ,SpnBin, SpRange[0], SpRange[1]);
   TH1F* hSpbg = new TH1F("Spbg","Sp g:BG x Res(O)"  ,SpnBin, SpRange[0], SpRange[1]);
   //hSp->SetMinimum(0);
   hSpbg->SetLineColor(2);
   TString SpYTitleStr;
   SpYTitleStr.Form("count / %3.1f MeV",resol);
   hSp->SetYTitle(SpYTitleStr.Data());
   
   TH1F* hSpsub   = new TH1F("Spsub","Sp sub Res(O)"   ,SpnBin, SpRange[0], SpRange[1]);
   hSpsub->SetFillColor(4);


//=========== Cut   
   TCut ppcoin = "(coinReg >=20 && coinReg <40) || coinReg>=60";
   TString crystalTitle;
   crystalTitle.Form("TMath::Power(s0x-%4.2f,2) + TMath::Power(s0y-%4.2f,2) < %7.2f", center[0], center[1], radius*radius);
   TCut crystal = crystalTitle;
   TString AcrystalTitle;
   AcrystalTitle.Form("TMath::Power(s0x-%4.2f,2) + TMath::Power(s0y-%4.2f,2) > %7.2f", center[0], center[1], Aradius*Aradius);
   TCut Acrystal = AcrystalTitle;
   
   TCutG *ResF25F = new TCutG("ResF25F",4);
   ResF25F->SetVarX("tofS0D");
   ResF25F->SetVarY("QS0D");
   ResF25F->SetPoint(0,-133.08,2521.8);
   ResF25F->SetPoint(1,-132.72,2310.2);
   ResF25F->SetPoint(2,-126.73,3230.0);
   ResF25F->SetPoint(3,-127.61,3459.8);
   ResF25F->SetPoint(4,-133.08,2521.8);
   
   TCutG *ResO25F = new TCutG("ResO25F",4);
   ResO25F->SetVarX("tofS0D");
   ResO25F->SetVarY("QS0D");
   ResO25F->SetPoint(0,-132.72,2310.2);
   ResO25F->SetPoint(1,-132.38,2178.5);
   ResO25F->SetPoint(2,-126.38,3000.0);
   ResO25F->SetPoint(3,-126.73,3230.0);
   ResO25F->SetPoint(4,-132.72,2310.2);
   
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

   //TCut common = ppcoin + Acrystal + crystal + EtotGate + OpenAngGate + "TplaPID1 && TplaPID2 && ResO25F";
   //TCut common = ppcoin + Acrystal + crystal + EtotGate + "TplaPID1 && TplaPID2 && ResO25F";
   //TCut common = PIDUS + ppcoin + crystal + EtotGate +  "TplaPID1 && TplaPID2";
   //TCut common = PIDUS + ppcoin + crystal +  "TplaPID1 && TplaPID2";
   //TCut common = PIDUS + ppcoin + "TplaPID1 && TplaPID2";
   TCut common = crystal + "ResO25F";
   TCut SignalGate = Ext1 +  common ;
   TCut BGGate = Ext2 + common ;
   
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
   textStr.Form("(%4.2f,%4.2f|%4.2f, %4.2f)",center[0],center[1],Aradius, radius);
   text.DrawText(0.2, 0.2, textStr);
   TLine line;
   Int_t nPt = 20;
   for ( Int_t i = 0; i < nPt; i++){
      line.DrawLine(center[0] + Aradius*TMath::Cos(2*TMath::Pi()*i/nPt),
                    center[1] + Aradius*TMath::Sin(2*TMath::Pi()*i/nPt),
                    center[0] + Aradius*TMath::Cos(2*TMath::Pi()*(i+1)/nPt),
                    center[1] + Aradius*TMath::Sin(2*TMath::Pi()*(i+1)/nPt));
   }
   for ( Int_t i = 0; i < nPt; i++){
      line.DrawLine(center[0] + radius*TMath::Cos(2*TMath::Pi()*i/nPt),
                    center[1] + radius*TMath::Sin(2*TMath::Pi()*i/nPt),
                    center[0] + radius*TMath::Cos(2*TMath::Pi()*(i+1)/nPt),
                    center[1] + radius*TMath::Sin(2*TMath::Pi()*(i+1)/nPt));
   }
   cAna->cd(3);
   recoil->Draw("Q1:tof1>>PID1",SignalGate,"colz");
   TplaPID1->Draw("same");
   cAna->cd(4);
   recoil->Draw("Q2:tof2>>PID2",SignalGate,"colz");
   TplaPID2->Draw("same");
   
   cAna->cd(5);
   //recoil->Draw("E1+E2>>Etot",common ,"");
   recoil->Draw("E1+E2>>Etotsg",SignalGate ,"");
   recoil->Draw("E1+E2>>Etotbg",BGGate ,"same");
   textStr.Form("E1+E2>%d",EtotGateMin);
   text.DrawText(0.2, 0.8, textStr);
   cAna->cd(6);
   recoil->Draw("wbeamZ>>wBeamZ",common ,"");
   recoil->Draw("wbeamZ>>wBeamZsg",SignalGate,"same");
   recoil->Draw("wbeamZ>>wBeamZbg",BGGate,"same");
   textStr.Form("%4.1f<wbeamZ<%4.1f",beamZRange[0], beamZRange[1]);
   text.DrawText(0.2, 0.8, textStr);
   textStr.Form("(%4.1f<.<%4.1f) || (%4.1f<.<%4.1f)",beamZRangeSide[0],beamZRange[0], beamZRange[1],beamZRangeSide[1]); 
   text.DrawText(0.2, 0.7, textStr);
   
   cAna->cd(7);
   recoil->Draw("QS0D:tofS0D>>PIDDS", "","colz");
   //recoil->Draw("QS0D:tofS0D>>PIDDS3", common ,"colz same");
   ResF25F->Draw("same");
   ResO25F->Draw("same");
   
   cAna->cd(8);
   //recoil->Draw("Sp:(E1+E2)>>SpEtot", SignalGate, "colz");
   recoil->Draw("(theta1+theta2)*TMath::RadToDeg():Sp>>OpenAngSp",SignalGate,"colz");
   
   cAna->cd(9);
   recoil->Draw("(theta1+theta2)*TMath::RadToDeg()>>DthetasgO",SignalGate,"colz");
   recoil->Draw("(theta1+theta2)*TMath::RadToDeg()>>DthetabgO",BGGate,"same");
   textStr.Form("%4.1f<OpAng<%4.1f",OpAngGateRange[0]- OpAngGateRange[1],OpAngGateRange[0]+OpAngGateRange[1]);
   text.DrawText(0.2, 0.8, textStr);
   hDthetasubO->Add(hDthetasgO, hDthetabgO, 1, -1);
   cAna->cd(10);
   hDthetasubO->Draw("");
  
   
   cAna->cd(11);
   recoil->Draw("Sp>>Sp",SignalGate ,"");
   recoil->Draw("Sp>>Spbg",BGGate ,"same");
   line.SetLineColor(6);
   line.DrawLine(beam->fSp, 0, beam->fSp, hSp->GetMaximum());
   line.DrawLine(beam->fSp + 27.1, 0, beam->fSp + 27.1, hSp->GetMaximum());
   line.SetLineColor(7);
   line.DrawLine(beam->fSp + 4.19, 0, beam->fSp + 4.19, hSp->GetMaximum());
   
   cAna->cd(12);
   hSpsub->Add(hSp,hSpbg, 1, -1);
   hSpsub->Draw();
   line.SetLineColor(6);
   line.DrawLine(beam->fSp, 0, beam->fSp, hSpsub->GetMaximum());

   return ;
}




