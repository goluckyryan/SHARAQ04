#include "TBeamData.h"
#include "../RelCalculator.h"

void Ana_23F_Simple() {
   const char* rootfile="Rphys23Fclean.root";
   TFile *f = new TFile(rootfile,"read");
   TTree *recoil = (TTree*)f->Get("recoil");
   TBeamData *beam = new TBeamData("23F");
   printf("=================================================\n");
   printf(" >>> %s <<< loaded. \n", rootfile);
   printf("====== totnumEntry:%d\n",recoil->GetEntries());
   
   Int_t Xdiv = 4, Ydiv = 3;
   Double_t padSize = 400;
   TCanvas* cAna = new TCanvas("cAna", "Analysis", 600, 500, padSize*Xdiv, padSize*Ydiv);
   cAna->Divide(Xdiv,Ydiv);
   
   Double_t center[2]={0, 1.9}; 
   Double_t radius = 8.;
   Double_t beamZRange[2]     = { -10, 40 }; // min, max , central gate
   Double_t beamZRangeSide[2] = { -50, 100 };
   Int_t EtotGateMin = 100;
   Double_t OpAngGateRange[2]={80,10}; // central, half-width
   
   Int_t SpnBin = 50;
   Double_t SpRange[2] = {-60, 140}; //MeV
   Int_t OpenAngBin = 30;
   Double_t OpenAngRange[2]={OpAngGateRange[0]-OpAngGateRange[1]-2,OpAngGateRange[0]+OpAngGateRange[1]+2};

//==========================================================
   Double_t resol = (SpRange[1]-SpRange[0])/SpnBin; //MeV
   Double_t Principle_tof = tofByBrho(L_F3FH9,beam->fBrho, beam->fMass, beam->fZ);
   
   gStyle->SetOptStat(0);
   
   TH2F* hPIDUS   = new TH2F("PIDUS"  , "PID UpStream", 100, Principle_tof*0.9 , Principle_tof*1.1, 100, beam->fQGate[0]*0.9, beam->fQGate[1]*1.1);
   TH1F* hcoinReg = new TH1F("coinReg", "coinReg, beam+=10, ppcoin+=20, NDcoin+=40, Other+=1", 80, 0, 80);
   TH2F* hS0img   = new TH2F("S0img"  , "S0 img"                           , 30, -15,  15, 30,  -15,  15);
   
   TH2F* hPID1    = new TH2F("PID1"   , "PID Tpla1" ,   200,  0, 50, 200, 600, 3000);  
   TH2F* hPID2    = new TH2F("PID2"   , "PID Tpla2" ,   200,  0, 50, 200, 600, 3000);
   
   TH2F* hBeamZEtot = new TH2F("BeamZEtot", "BeamZ vs Etot", 50, 0, 400, 100, -100, 200);
   
   TH1F* hEtot     = new TH1F("Etot"     , "E1+E2"  ,   50,  0, 400);
   TH1F* hEtotsg   = new TH1F("Etotsg"   , "E1+E2"  ,   50,  0, 400);
   TH1F* hEtotbg   = new TH1F("Etotbg"   , "E1+E2"  ,   50,  0, 400);
   hEtot->SetLineColor(3);
   hEtot->SetYTitle("count/8 MeV");
   hEtotsg->SetLineColor(4);
   hEtotbg->SetLineColor(2);

   TH1F* hOpenAngSGN  = new TH1F("OpenAngSGN"  , "Open Angle Res(O)"       , OpenAngBin, OpenAngRange[0], OpenAngRange[1]);
   TH1F* hOpenAngBGN  = new TH1F("OpenAngBGN"  , "Open Angle Res(O)"       , OpenAngBin, OpenAngRange[0], OpenAngRange[1]);
   TH1F* hOpenAngSubN = new TH1F("OpenAngSubN" , "Open ANgle sub Res(O)"   , OpenAngBin, OpenAngRange[0], OpenAngRange[1]);
   hOpenAngSGN->SetLineColor(4);
   TString hDthetaYTitle;
   hDthetaYTitle.Form("count/%3.1f deg", (OpenAngRange[1]-OpenAngRange[0])/OpenAngBin );
   hOpenAngSGN->SetYTitle(hDthetaYTitle.Data());
   hOpenAngBGN->SetLineColor(2);
   hOpenAngSubN->SetFillColor(4);
   
   TH1F* hwBeamZ    = new TH1F("wBeamZ"   , "weighted beamZ"  , 300, -100, 200);
   TH1F* hwBeamZsg  = new TH1F("wBeamZsg" , "weighted beamZ g:p2p"  , 300, -100, 200);
   TH1F* hwBeamZbg  = new TH1F("wBeamZbg" , "weighted beamZ g:BG"  , 300, -100, 200);
   hwBeamZ->SetLineColor(3);
   hwBeamZsg->SetLineColor(4);
   hwBeamZbg->SetLineColor(2);
   
   TH2F * hSpEtot  = new TH2F("SpEtot", "Sp vs Etot g:p2p x Res(O)", 50, 0 , 400, SpnBin, SpRange[0], SpRange[1]);
   hSpEtot->SetXTitle("Etot");
   hSpEtot->SetYTitle("Sp");
   TH2F * hOpenAngSp = new TH2F("OpenAngSp", "OpenAng vs Sp", SpnBin, SpRange[0], SpRange[1], OpenAngBin, OpenAngRange[0], OpenAngRange[1]);
   hOpenAngSp->SetXTitle("Sp");
   hOpenAngSp->SetYTitle("Open Ang");
   
   TH2F * hPIDDS   = new TH2F("PIDDS" , "PIDDS g:p2p"         , 300, -130,  -125, 300 ,  500, 2700);
   TH2F * hPIDDS3  = new TH2F("PIDDS3", "PIDDS g:p2p x Res(O)", 300, -130,  -125, 300 ,  500, 2700);   
   
   TH1F* hSp3   = new TH1F("Sp3","Sp g:p2p x Res(O)"   ,SpnBin, SpRange[0], SpRange[1]);
   TH1F* hSp3bg = new TH1F("Sp3bg","Sp g:BG x Res(O)"  ,SpnBin, SpRange[0], SpRange[1]);
   hSp3->SetMinimum(0);
   hSp3bg->SetLineColor(2);
   TString SpYTitleStr;
   SpYTitleStr.Form("count / %3.1f MeV",resol);
   hSp3->SetYTitle(SpYTitleStr.Data());
   
   TH1F* hSp3sub   = new TH1F("Sp3sub","Sp sub Res(O)"   ,SpnBin, SpRange[0], SpRange[1]);
   hSp3sub->SetFillColor(4);

//=========== Cut   
   TCut ppcoin = "(coinReg >=20 && coinReg <40) || coinReg>=60";
   TString crystalTitle;
   crystalTitle.Form("TMath::Power(s0x-%4.2f,2) + TMath::Power(s0y-%4.2f,2) < %7.2f", center[0], center[1], radius*radius);
   TCut crystal = crystalTitle;
   
   TCutG *ResO23F = new TCutG("ResO23F",6);
   ResO23F->SetVarX("tofS0D");
   ResO23F->SetVarY("QS0D");
   ResO23F->SetPoint(0,-129.1,1872.3);
   ResO23F->SetPoint(1,-126.1,2072.9);
   ResO23F->SetPoint(2,-125.7,1957.0);
   ResO23F->SetPoint(3,-127.7,1676.2);
   ResO23F->SetPoint(4,-128.2,1200.0);
   ResO23F->SetPoint(5,-129.1,1444.4);
   ResO23F->SetPoint(6,-129.1,1872.3);
   
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
   TCut common = PIDUS + crystal ;
   TCut SignalGate = common + Ext1 + "ResO23F";
   TCut BGGate = common + Ext2 + "ResO23F";
   
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
   //recoil->Draw("Q1:tof1>>PID1",SignalGate,"colz");
   recoil->Draw("wbeamZ:E1+E2>>BeamZEtot", common, "colz");

   cAna->cd(4);
   recoil->Draw("Q2:tof2>>PID2",SignalGate,"colz");
   
   cAna->cd(5);
   //recoil->Draw("E1+E2>>Etot",common + "ResO23F","");
   recoil->Draw("E1+E2>>Etotsg",SignalGate ,"");
   recoil->Draw("E1+E2>>Etotbg",BGGate ,"same");
   textStr.Form("E1+E2>%d",EtotGateMin);
   text.DrawText(0.2, 0.8, textStr);
   cAna->cd(6);
   recoil->Draw("wbeamZ>>wBeamZ",common + "ResO23F","");
   recoil->Draw("wbeamZ>>wBeamZsg",SignalGate,"same");
   recoil->Draw("wbeamZ>>wBeamZbg",BGGate,"same");
   textStr.Form("%4.1f<wbeamZ<%4.1f",beamZRange[0], beamZRange[1]);
   text.DrawText(0.2, 0.8, textStr);
   textStr.Form("(%4.1f<.<%4.1f) || (%4.1f<.<%4.1f)",beamZRangeSide[0],beamZRange[0], beamZRange[1],beamZRangeSide[1]); 
   text.DrawText(0.2, 0.7, textStr);
   
   cAna->cd(7);
   recoil->Draw("QS0D:tofS0D>>PIDDS3", common + "ResO23F","colz same");
   ResO23F->Draw("same");
   
   cAna->cd(8);
   //recoil->Draw("Sp:(E1+E2)>>SpEtot", SignalGate, "colz");
   recoil->Draw("(theta1+theta2)*TMath::RadToDeg():Sp>>OpenAngSp",SignalGate,"colz");
   
   cAna->cd(9);
   recoil->Draw("(theta1+theta2)*TMath::RadToDeg()>>OpenAngSGN",SignalGate,"colz");
   recoil->Draw("(theta1+theta2)*TMath::RadToDeg()>>OpenAngBGN",BGGate,"same");
   textStr.Form("%4.1f<OpAng<%4.1f",OpAngGateRange[0]- OpAngGateRange[1],OpAngGateRange[0]+OpAngGateRange[1]);
   text.DrawText(0.2, 0.8, textStr);
   hOpenAngSubN->Add(hOpenAngSGN, hOpenAngBGN, 1, -1);
   cAna->cd(10);
   hOpenAngSubN->Draw("");
  
   
   cAna->cd(11);
   recoil->Draw("Sp2>>Sp3",SignalGate ,"");
   recoil->Draw("Sp2>>Sp3bg",BGGate ,"same");
   line.SetLineColor(6);
   line.DrawLine(beam->fSp, 0, beam->fSp, hSp3->GetMaximum()); //23F Sp(proton)
   line.DrawLine(beam->fSp + 23.26, 0, beam->fSp + 23.26, hSp3->GetMaximum()); // 22O Sp(proton)
   line.SetLineColor(7);
   line.DrawLine(beam->fSp + 6.85, 0, beam->fSp + 6.85, hSp3->GetMaximum()); // 22O Sp(neutron)
   
   cAna->cd(12);
   hSp3sub->Add(hSp3,hSp3bg, 1, -1);
   hSp3sub->Draw();
   line.SetLineColor(6);
   line.DrawLine(beam->fSp, 0, beam->fSp, hSp3sub->GetMaximum());
   

   gROOT->ProcessLine(".!date");
   return ;
}




