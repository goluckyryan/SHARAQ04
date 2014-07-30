void Ana_14O_complete() {
   gROOT->ProcessLine(".!date");
   const char* rootfile="Rphys14All.root";
   TFile *f = new TFile(rootfile,"read");
   TTree *recoil = (TTree*)f->Get("recoil");
   printf("====== totnumEntry:%d\n",recoil->GetEntries());
   
   Int_t Xdiv = 5, Ydiv = 5;
   Double_t padSize = 400;
   TCanvas* cAna = new TCanvas("cAna", "Analysis", 200, 150, padSize*Xdiv, padSize*Ydiv);
   cAna->Divide(Xdiv,Ydiv);
   
   Double_t range[2] = {-10, 60}; //MeV
   Int_t nBin = 35;
   Double_t center[2]={0, 3.35}; //{0,3.35}
   Double_t radius = 7.;
   Double_t beamZRange[2] = { -8, 40 };

//==========================================================
   Double_t resol = (range[1]-range[0])/nBin; //MeV
   
   printf(" %s opened. Sp Resol= %4.2f \n", rootfile, resol);
   
   TH1F* hrunNum  = new TH1F("runNUm" , "run Number"                       , 65, 1, 66);
   TH1F* hcoinReg = new TH1F("coinReg", "beam+=10, ppcoin+=20, NDcoin+=40" , 80,0,80);
   TH2F* hPIDUS   = new TH2F("PIDUS"  , "PID US"                           , 200, 390, 410, 200, 5500, 6000);
   TH1F* hBrho    = new TH1F("Brho"   , "Brho"                             , 200, 3.5,  4.5);
   TH1F* hTKAppac = new TH1F("TKAppac", "TKA by PPAC"                      , 200, 235, 260);
   TH1F* hTKAtime = new TH1F("TKAtime", "TKA by tof"                       , 200, 235, 260);
   hTKAppac->SetLineColor(4);
   hTKAtime->SetLineColor(2);
   TH2F* hTKAcomp = new TH2F("TKAcomp", "TKA ppac vs tof"                  , 200, 235, 260, 200, 235, 260);
   TH2F* hS0img   = new TH2F("S0img"  , "S0 img"                           , 200, -30,  30, 200,  -30,  30);
   TH1F* htof1    = new TH1F("tof1"   , "Tof (tgt - tpla1)"                , 200,   0,  50);
   TH1F* htof2    = new TH1F("tof2"   , "Tof (tgt - tpla2)"                , 200,   0,  50);
   htof1->SetLineColor(4);
   htof2->SetLineColor(2);
   TH2F* htofcomp = new TH2F("tofcomp", "Tof1 vs Tof2"                     , 200, 0, 50, 200, 0, 50);
   TH1F* hQ1      = new TH1F("Q1"     , "Q1",    200,  500, 2000);
   TH1F* hQ2      = new TH1F("Q2"     , "Q2",    200,  500, 2000);
   hQ1->SetLineColor(4);
   hQ2->SetLineColor(2);
   TH2F* hQcomp   = new TH2F("Qcomp"  , "Q1 vs Q2",    200, 500, 2000, 200, 500, 2000);
   TH1F* hE1      = new TH1F("E1"     , "E1"     ,   200,  0, 400);
   TH1F* hE2      = new TH1F("E2"     , "E2"     ,   200,  0, 400);
   TH1F* hEtot    = new TH1F("Etot"   , "E1+E2"  ,   200,  0, 400);
   hE1->SetLineColor(4);
   hE2->SetLineColor(2);
   hEtot->SetLineColor(3);
   TH2F* hPID1    = new TH2F("PID1"   , "PID Tpla1" ,   200,  0, 50, 200, 600, 3000);  
   TH2F* hPID2    = new TH2F("PID2"   , "PID Tpla2" ,   200,  0, 50, 200, 600, 3000);
   TH1F* hDtheta  = new TH1F("Dtheta" , "theta1+theta2", 200,  35, 130);
   TH1F* hDthetasg  = new TH1F("Dthetasg" , "theta1+theta2", 200,  35, 130);
   TH1F* hDthetabg  = new TH1F("Dthetabg" , "theta1+theta2", 200,  35, 130);
   hDtheta->SetLineColor(3);
   hDthetasg->SetLineColor(4);
   hDthetabg->SetLineColor(2);
      
   TH2F* htheta   = new TH2F("theta"  , "theta1 vs theta2", 200, 15, 70, 200, 15, 70);
   TH1F* hDphi    = new TH1F("Dphi"   , "phi2-phi1"       , 200, 150, 210);
   TH1F* hDphisg    = new TH1F("Dphisg"   , "phi2-phi1"       , 200, 150, 210);
   TH1F* hDphibg    = new TH1F("Dphibg"   , "phi2-phi1"       , 200, 150, 210);
   hDphi->SetLineColor(3);
   hDphisg->SetLineColor(4);
   hDphibg->SetLineColor(2);
   
   TH2F* hphi     = new TH2F("phi"    , "phi1 vs phi2"    , 200, -30, 30, 200, 150, 210);
   TH2F* hOpenAng = new TH2F("OpenAng", "Dtheta vs Dphi"  , 200,  40, 140, 200, 150, 210);
   TH1F* hwBeamZ  = new TH1F("wBeamZ" , "weighted beamZ g:common"  , 300, -100, 200);
   TH1F* hwBeamZsg  = new TH1F("wBeamZsg" , "weighted beamZ g:p2p"  , 300, -100, 200);
   TH1F* hwBeamZbg  = new TH1F("wBeamZbg" , "weighted beamZ g:BG"  , 300, -100, 200);
   hwBeamZ->SetLineColor(3);
   hwBeamZsg->SetLineColor(4);
   hwBeamZbg->SetLineColor(2);
   
   TH2F * hPIDD        = new TH2F("PIDDS", "PIDDS g:p2p", 300, -70,  -60, 300 ,   0, 2500);
   TH2F * hPIDDS1      = new TH2F("PIDDS1", "PIDDS g:p2p x Res(H)", 300, -70,  -60, 300 ,   0, 2500);
   TH2F * hPIDDS2      = new TH2F("PIDDS2", "PIDDS g:p2p x Res(O)", 300, -70,  -60, 300 ,   0, 2500);
   TH2F * hPIDDS3      = new TH2F("PIDDS3", "PIDDS g:p2p x Res(N)", 300, -70,  -60, 300 ,   0, 2500);
   TH2F * hPIDDS4      = new TH2F("PIDDS4", "PIDDS g:p2p x Res(C)", 300, -70,  -60, 300 ,   0, 2500);      
   
   TH1F* hSp1   = new TH1F("Sp1","Sp g:common = PID x ppcoin x crystal x TplaPID"   ,nBin, range[0], range[1]);
   TH1F* hSp2   = new TH1F("Sp2","Sp g:p2p = common x wbeamZ"   ,nBin, range[0], range[1]);
   TH1F* hSp3   = new TH1F("Sp3","Sp g:p2p x Res(N)"   ,nBin, range[0], range[1]);
   TH1F* hSp4   = new TH1F("Sp4","Sp g:p2p x Res(C)"   ,nBin, range[0], range[1]);
   TH1F* hSp2bg   = new TH1F("Sp2bg","Sp g:BG = common x wbeamZ"   ,nBin, range[0], range[1]);
   TH1F* hSp3bg   = new TH1F("Sp3bg","Sp g:BG x Res(N)"   ,nBin, range[0], range[1]);
   TH1F* hSp4bg   = new TH1F("Sp4bg","Sp g:BG x Res(C)"   ,nBin, range[0], range[1]);
   hSp2bg->SetLineColor(2);
   hSp3bg->SetLineColor(2);
   hSp4bg->SetLineColor(2);

//=========== Cut   
   TCut ppcoin = "(coinReg==20 || coinReg==30 || coinReg==60 || coinReg==70)";
   TString crystalTitle;
   crystalTitle.Form("TMath::Power(s0x-%4.2f,2) + TMath::Power(s0y-%4.2f,2) < %7.2f", center[0], center[1], radius*radius);
   TCut crystal = crystalTitle;
   
   TCut validY = "TMath::Finite(QS0D)";
   TCut validX = "TMath::Finite(tofS0D)";
   
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
   TplaPID2->SetPoint(1,13.,1600.);
   TplaPID2->SetPoint(2, 2., 600.);
   TplaPID2->SetPoint(3,50., 600.);
   TplaPID2->SetPoint(4,35.,2400.);
   TplaPID2->SetPoint(5,19.,3000.);

   TString beamZGate1Title;
   TString beamZGate2Title;
   beamZGate1Title.Form("wbeamZ>%10.2f && wbeamZ<%10.2f", beamZRange[0], beamZRange[1]);
   beamZGate2Title.Form("((wbeamZ>%10.2f && wbeamZ<%10.2f) || (wbeamZ>%10.2f && wbeamZ<%10.2f))", -32., beamZRange[0], beamZRange[1], 100.);
   TCut Ext1 = beamZGate1Title;
   TCut Ext2 = beamZGate2Title;
   TCut common = ppcoin + "TplaPID1" + "TplaPID2";//+crystal;
   TCut SignalGate = common + Ext1;
   TCut BGGate = common + Ext2;
   
   SignalGate.Print();
   BGGate.Print();
   
//=====================================
   cAna->cd(1);
   recoil->Draw("runNum>>runNUm",SignalGate,"colz");
   cAna->cd(2);
   recoil->Draw("coinReg>>coinReg",SignalGate,"colz");
   cAna->cd(3);
   recoil->Draw("Q_us:tof_usV1190>>PIDUS",SignalGate,"colz");
   cAna->cd(4);
   recoil->Draw("TKAppac>>TKAppac",SignalGate,"");
   recoil->Draw("TKAV775>>TKAtime",SignalGate,"same");
   cAna->cd(5);
   recoil->Draw("TKAppac:TKAtime>>TKAcomp",SignalGate,"colz");
   
   cAna->cd(6);
   recoil->Draw("s0y:s0x>>S0img",SignalGate,"colz");
   cAna->cd(7);
   recoil->Draw("tof1>>tof1",SignalGate,"");
   recoil->Draw("tof2>>tof2",SignalGate,"same");
   cAna->cd(8);
   recoil->Draw("tof1:tof2>>tofcomp",SignalGate,"colz");
   cAna->cd(9);
   recoil->Draw("Q2>>Q2",SignalGate,"");
   recoil->Draw("Q1>>Q1",SignalGate,"same");
   cAna->cd(10);
   recoil->Draw("Q2:Q1>>Qcomp",SignalGate,"colz");
   
   cAna->cd(11);
   recoil->Draw("E1>>E1",SignalGate,"");
   recoil->Draw("E2>>E2",SignalGate,"same");
   recoil->Draw("E1+E2>>Etot",SignalGate,"same");
   cAna->cd(12);
   recoil->Draw("Q1:tof1>>PID1",SignalGate,"colz");
   cAna->cd(13);
   recoil->Draw("Q2:tof2>>PID2",SignalGate,"colz");
   cAna->cd(14);
   recoil->Draw("(theta1+theta2)*TMath::RadToDeg()>>Dtheta",SignalGate,"colz");
   recoil->Draw("(theta1+theta2)*TMath::RadToDeg()>>Dthetasg",SignalGate && "ResN","colz");
   recoil->Draw("(theta1+theta2)*TMath::RadToDeg()>>Dthetabg",BGGate && "ResN","same");
   cAna->cd(15);
   recoil->Draw("theta2*TMath::RadToDeg():theta1*TMath::RadToDeg()>>theta",SignalGate,"colz");
   
   cAna->cd(16);
   recoil->Draw("(phi2-phi1)*TMath::RadToDeg()>>Dphi",SignalGate,"colz");
   recoil->Draw("(phi2-phi1)*TMath::RadToDeg()>>Dphisg",SignalGate && "ResN","colz");
   recoil->Draw("(phi2-phi1)*TMath::RadToDeg()>>Dphibg",BGGate && "ResN","same");
   cAna->cd(17);
   recoil->Draw("phi2*TMath::RadToDeg():phi1*TMath::RadToDeg()>>phi",SignalGate,"colz");
   cAna->cd(18);
   recoil->Draw("(phi2-phi1)*TMath::RadToDeg():(theta1+theta2)*TMath::RadToDeg()>>OpenAng",SignalGate,"colz");
   cAna->cd(19);
   recoil->Draw("wbeamZ>>wBeamZ",common,"");
   recoil->Draw("wbeamZ>>wBeamZsg",SignalGate,"same");
   recoil->Draw("wbeamZ>>wBeamZbg",BGGate,"same");
   cAna->cd(20);
   recoil->Draw("QS0D:tofS0D>>PIDDS",SignalGate,"colz");
   cAna->cd(25);
   recoil->Draw("QS0D:tofS0D>>PIDDS1",SignalGate && "ResH","colz");
   recoil->Draw("QS0D:tofS0D>>PIDDS2",SignalGate && "ResO","colz same");
   recoil->Draw("QS0D:tofS0D>>PIDDS3",SignalGate && "ResN","colz same");
   recoil->Draw("QS0D:tofS0D>>PIDDS4",SignalGate && "ResC","colz same");
   
   cAna->cd(21);
   recoil->Draw("Sp2>>Sp1",common ,"");
   cAna->cd(22);
   recoil->Draw("Sp2>>Sp2",SignalGate ,"");
   recoil->Draw("Sp2>>Sp2bg",BGGate ,"same");
   cAna->cd(23);
   recoil->Draw("Sp2>>Sp3",SignalGate && "ResN","");
   recoil->Draw("Sp2>>Sp3bg",BGGate && "ResN","same");
   cAna->cd(24);
   recoil->Draw("Sp2>>Sp4",SignalGate && "ResC","");
   recoil->Draw("Sp2>>Sp4bg",BGGate && "ResC","same");
   
/*   
   TCanvas* cAux = new TCanvas("cAux", "PID DS SignalGate", 100, 50, 600, 600);
   cAux->cd();
   recoil->Draw("QS0D:tofS0D>>PIDDS1","ResH","colz");
   recoil->Draw("QS0D:tofS0D>>PIDDS2","ResO","colz same");
   recoil->Draw("QS0D:tofS0D>>PIDDS3","ResN","colz same");
   recoil->Draw("QS0D:tofS0D>>PIDDS4","ResC","colz same");
*/   
   gROOT->ProcessLine(".!date");
   return ;
}


