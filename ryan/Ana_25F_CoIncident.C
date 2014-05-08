#include "TBeamData.h"
#include "RelCalculator.h"

void Ana_25F_CoIncident() {
   const char* rootfile="Rphys25FAll_test.root";
   TFile *f = new TFile(rootfile,"read");
   TTree *recoil = (TTree*)f->Get("recoil");
   TBeamData *beam = new TBeamData("25F");
   printf("=================================================\n");
   printf(" >>> %s <<< loaded. \n", rootfile);
   printf("====== totnumEntry:%d\n",recoil->GetEntries());
   
   Int_t Xdiv = 4, Ydiv = 4;
   Double_t padSize = 400;
   TCanvas* cCoin = new TCanvas("cCoin", "Analysis", 100, 100, padSize*Xdiv, padSize*Ydiv);
   cCoin->Divide(Xdiv,Ydiv);
   
   Double_t center[2]={0, 1.9}; 
   Double_t radiusA = 0., radiusB = 7. ;
   Double_t beamZRange[2]     = { -10, 40 }; // min, max , central gate
   Int_t EtotGateMin = 100;
   Double_t OpAngGateRange[2]={80,6}; // central, half-width
   
   Int_t SpnBin = 50;
   Double_t SpRange[2] = {-10, 40}; //MeV
   Int_t hDthetaBin = (OpAngGateRange[1]*2+4)*2;
   Double_t hDthetaRange[2]={OpAngGateRange[0]-OpAngGateRange[1]-2,OpAngGateRange[0]+OpAngGateRange[1]+2};

//==========================================================
   Double_t resol = (SpRange[1]-SpRange[0])/SpnBin; //MeV
   Double_t Principle_tof = tofByBrho(L_F3FH9,beam->fBrho, beam->fMass, beam->fZ);
   
   gStyle->SetOptStat(0);
   
   TH2F* hPIDUS   = new TH2F("PIDUS"  , "PID UpStream", 100, Principle_tof*0.9 , Principle_tof*1.1, 100, beam->fQGate[0]*0.9, beam->fQGate[1]*1.1);
   TH1F* hcoinReg = new TH1F("coinReg", "coinReg, beam+=10, ppcoin+=20, NDcoin+=40, Other+=1", 80, 0, 80);
   TH2F* hS0img   = new TH2F("S0img"  , "S0 img"                           , 30, -15,  15, 30,  -15,  15);
   TH2F* hPID1    = new TH2F("PID1"   , "PID Tpla1" ,   200,  0, 50, 200, 300, 3000);  
   TH2F* hPID2    = new TH2F("PID2"   , "PID Tpla2" ,   200,  0, 50, 200, 300, 3000);
   TH2F* hPIDDS   = new TH2F("PIDDS"  , "PIDDS "         , 300, -134,  -125, 300 ,  1500, 3500); 
   
   TH1F* hEtot     = new TH1F("Etot"     , "E1+E2"  ,   50,  0, 400);
   hEtot->SetYTitle("count/8 MeV");

   TH1F* hDtheta  = new TH1F("Dtheta"  , "Open Angle"       , hDthetaBin, hDthetaRange[0], hDthetaRange[1]);
   TString hDthetaYTitle;
   hDthetaYTitle.Form("count/%3.1f deg", (hDthetaRange[1]-hDthetaRange[0])/hDthetaBin );
   hDtheta->SetYTitle(hDthetaYTitle);
   
   TH1F* hwBeamZ    = new TH1F("wBeamZ"   , "weighted beamZ"  , 300, -100, 200);
   hwBeamZ->SetYTitle("count/1 mm");
   
   TH1F* hSp   = new TH1F("Sp","Sp"   ,SpnBin, SpRange[0], SpRange[1]);
   hSp->SetMinimum(0);
   TString SpYTitle;
   SpYTitle.Form("count/%3.1f MeV",resol);
   hSp->SetYTitle(SpYTitle);
   
   TH2F* hOpenAngEtot = new TH2F("OpenAngEtot", "OpenAng vs Etot", 50, 0, 400, hDthetaBin, hDthetaRange[0], hDthetaRange[1]);
   hOpenAngEtot->SetXTitle("Etot");
   hOpenAngEtot->SetYTitle("OpenAng");

   TH2F* hOpenAngBeamZ = new TH2F("OpenAngBeamZ", "OpenAng vs BeamZ", 200, -100,200, hDthetaBin, hDthetaRange[0], hDthetaRange[1]);
   hOpenAngBeamZ->SetXTitle("BeamZ");
   hOpenAngBeamZ->SetYTitle("OpenAng");
   
   TH2F* hOpenAngSp  = new TH2F("OpenAngSp", "OpenAng vs Sp", SpnBin, SpRange[0], SpRange[1], hDthetaBin, hDthetaRange[0], hDthetaRange[1]);
   hOpenAngSp->SetXTitle("Sp");
   hOpenAngSp->SetYTitle("OpenAng");
   
   TH2F* hSpEtot  = new TH2F("SpEtot", "Sp vs Etot", 50, 0 , 400, SpnBin, SpRange[0], SpRange[1]);
   hSpEtot->SetXTitle("Etot");
   hSpEtot->SetYTitle("Sp");
   
   TH2F* hSpBeamZ  = new TH2F("SpBeamZ", "Sp vs BeamZ", 300, -100 , 200, SpnBin, SpRange[0], SpRange[1]);
   hSpBeamZ->SetXTitle("BeamZ");
   hSpBeamZ->SetYTitle("Sp");
   
   TH2F* hEtotBeamZ  = new TH2F("EtotBeamZ", "Etot vs BeamZ", 300, -100, 200, 50, 0 , 400);
   hEtotBeamZ->SetXTitle("beamZ");
   hEtotBeamZ->SetYTitle("Etot");
   
//=========== Cut   
   TCut ppcoin = "(coinReg >=20 && coinReg <40) || coinReg>=60";
   TString crystalTitle;
   crystalTitle.Form("TMath::Power(s0x-%4.2f,2) + TMath::Power(s0y-%4.2f,2) <= %7.2f", center[0], center[1], radiusB*radiusB);
   TCut crystal = crystalTitle;
   TString AcrystalTitle;
   AcrystalTitle.Form("TMath::Power(s0x-%4.2f,2) + TMath::Power(s0y-%4.2f,2) >= %7.2f", center[0], center[1], radiusA*radiusA);
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
   
   TString OpAngGateTitle;
   OpAngGateTitle.Form("TMath::Abs((theta1+theta2)*TMath::RadToDeg()-%4.1f)<%4.1f",OpAngGateRange[0],OpAngGateRange[1]);
   TCut OpenAngGate = OpAngGateTitle;
   TString EtotGateTitle;
   EtotGateTitle.Form("E1+E2>%4d",EtotGateMin);
   TCut EtotGate   = EtotGateTitle;
   
   TString beamZGate1Title;
   beamZGate1Title.Form("wbeamZ>%7.2f && wbeamZ<%7.2f", beamZRange[0], beamZRange[1]);
   TCut Ext1 = beamZGate1Title;
   
   //TCut common = ppcoin + crystal + EtotGate + OpenAngGate + Ext1 + "TplaPID1 && TplaPID2 && ResO25F";
   //TCut common = ppcoin + crystal + EtotGate + OpenAngGate + "TplaPID1 && TplaPID2 && ResO25F";
   //TCut common = ppcoin + crystal + EtotGate +  "TplaPID1 && TplaPID2";
   //TCut common = crystal + Ext1 + "TplaPID1 && TplaPID2 && ResO25F";
   TCut common = ppcoin + crystal + Acrystal + Ext1  + "TplaPID1 && TplaPID2 && ResO25F";
   //TCut common = ppcoin + crystal +  "TplaPID1 && TplaPID2 && ResO25F";
   //TCut common = ppcoin + "TplaPID1 && TplaPID2 && ResO25F";
   //TCut common = "TplaPID1 && TplaPID2 && ResO25F";
   //TCut common = "TplaPID1 && TplaPID2";
   //TCut common = "";
   
   common.Print();
   
   TLatex text;
   text.SetNDC();
   text.SetTextColor(1);
   TString textStr;
//=====================================
   cCoin->cd(1);
   recoil->Draw("Q_us:tof_usV1190>>PIDUS",common,"colz");
   textStr.Form("%s",rootfile);
   text.DrawText(0.2, 0.2, textStr);
   
   cCoin->cd(2);
   recoil->Draw("coinReg>>coinReg",common);
   
   cCoin->cd(3);
   recoil->Draw("s0y:s0x>>S0img",common,"colz");
   textStr.Form("(%4.2f,%4.2f|%4.2f)",center[0],center[1],radiusB);
   text.DrawText(0.2, 0.2, textStr);
   TLine line;
   Int_t nPt = 20;
   for ( Int_t i = 0; i < nPt; i++){
      line.DrawLine(center[0] + radiusB*TMath::Cos(2*TMath::Pi()*i/nPt),
                    center[1] + radiusB*TMath::Sin(2*TMath::Pi()*i/nPt),
                    center[0] + radiusB*TMath::Cos(2*TMath::Pi()*(i+1)/nPt),
                    center[1] + radiusB*TMath::Sin(2*TMath::Pi()*(i+1)/nPt));
   }
   cCoin->cd(4);
   recoil->Draw("Q1:tof1>>PID1",common,"colz");
   TplaPID1->Draw("same");
   
   cCoin->cd(5);
   recoil->Draw("Q2:tof2>>PID2",common,"colz");
   TplaPID2->Draw("same");
   
   cCoin->cd(6);
   recoil->Draw("QS0D:tofS0D>>PIDDS",common,"colz");
   ResF25F->Draw("same");
   ResO25F->Draw("same");
   
   cCoin->cd(7);
   recoil->Draw("E1+E2>>Etot",common ,"");
   
   cCoin->cd(8);
   recoil->Draw("wbeamZ>>wBeamZ",common ,"");
   
   cCoin->cd(9);
   recoil->Draw("Sp>>Sp", common, "colz");
   
   cCoin->cd(10);
   recoil->Draw("(theta1+theta2)*TMath::RadToDeg()>>Dtheta",common,"colz");
    
   cCoin->cd(11);
   recoil->Draw("(theta1+theta2)*TMath::RadToDeg():E1+E2>>OpenAngEtot",common,"colz");
   
   cCoin->cd(12);
   recoil->Draw("(theta1+theta2)*TMath::RadToDeg():wbeamZ>>OpenAngBeamZ",common,"colz");
   
   cCoin->cd(13);
   recoil->Draw("(theta1+theta2)*TMath::RadToDeg():Sp>>OpenAngSp",common,"colz");
   
   cCoin->cd(14);
   recoil->Draw("Sp:E1+E2>>SpEtot",common,"colz");
   
   cCoin->cd(15);
   recoil->Draw("Sp:wbeamZ>>SpBeamZ",common,"colz");
   
   cCoin->cd(16);
   recoil->Draw("E1+E2:wbeamZ>>EtotBeamZ", common, "colz");

   return ;
}




