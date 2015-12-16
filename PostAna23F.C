{
        gROOT->Reset();
        gROOT->ProcessLine(".!date");
        gStyle->SetOptStat(0);

        //========================================================

        //char * rootfile = "Z_X_23F_ppcoin_r7_0619.root";
        char * rootfile = "P_23F_timeoffset_58.9_59.7.root"; // using for spectrum
        //char * rootfile = "P_23F_ppcoin_0603.root"; // all r
        //char * rootfile = "P_23F_r14_0824.root"; // all r
        //char * rootfile = "X_23F_r14_0824.root"; // all r
        //char * rootfile = "P_23F_r14_0820.root"; // all r

        TFile *f0 = new TFile (rootfile, "read"); 
        TTree *tree = (TTree*)f0->Get("tree");
        
        //-------------- THREEDEE
        TFile *f00 = new TFile ("THREEDEE/23F_Sp13.3_Tc030_ang010_phi00.root", "read"); TTree *Ex00 = (TTree*)f00->Get("tree");
        TFile *f10 = new TFile ("THREEDEE/23F_Sp23.3_Tc030_ang010_phi00.root", "read"); TTree *Ex10 = (TTree*)f10->Get("tree");
        TFile *f20 = new TFile ("THREEDEE/23F_Sp33.3_Tc030_ang010_phi00.root", "read"); TTree *Ex20 = (TTree*)f20->Get("tree");
        
        printf("=====> /// %15s //// is loaded. Total #Entry: %10d \n", rootfile,  tree->GetEntries());
/**///======================================================== Browser or Canvas
        Int_t Div[2] = {1,1};  //x,y
        Int_t size[2] = {600,400}; //x,y
        TCanvas * cPostAna = new TCanvas("cPostAna", "cPostAna", 2000, 0 , size[0]*Div[0], size[1]*Div[1]);
        cPostAna->Divide(Div[0],Div[1]);
        cPostAna->cd(1);

        /**///======================================================== Cut 
        //TCut gateCry = "";
        TCut gateCry = "s0x*s0x+TMath::Power(s0y-1.8,2)<49";
        //TCut gateCry = "s0x*s0x+TMath::Power(s0y-1.8,2)>49 && s0x*s0x+TMath::Power(s0y-1.8,2)<14.0*14.0";
        TCut gateCryc = "s0x*s0x+TMath::Power(s0y-1.8,2)>49 && s0x*s0x+TMath::Power(s0y-1.8,2)<196";
        TCut gateCryc2 = "s0x*s0x+TMath::Power(s0y-1.8,2)>49";
        //TCut gateTofS1 = "32<tofS1 && tofS1<35";
        TCut gateTofS1 = "32<tofS0DS1 && tofS0DS1<35";
        TCut gateS0D = "TMath::Finite(s0dx)";
        TCut gateVertexZ = "TMath::Abs(vertexZ-10)<60";
        TCut gateVertexZs = "TMath::Abs(vertexZ-10)>60 && TMath::Abs(vertexZ-10)<100";
        TCut gateVertexZc = "TMath::Abs(vertexZ-160)<60";
        TCut gateBeamZ = "TMath::Abs(beamZ-10)<30";
        TCut gateBeamZc = "TMath::Abs(beamZ-160)<30";
        //TCut gateOpenAng = "90>theta1+theta2 && theta1+theta2>70";
        //TCut gateOpenAng = "theta1>30 || theta2>30";
        TCut gateOpenAng = "";
        TCut gateZ = "8.9>pidZ && pidZ>7.2";
        TCut gateZn = "7.3>pidZ && pidZ>6.4";
        TCut gateNID = "nyokiID > 6";
        TCut gateAOQ = "23.5>pidAOQ*8 && pidAOQ*8>18.5";
        
        

        TCut gate0  = gateCry + gateTofS1 + gateVertexZ  + gateOpenAng + gateNID /*+ gateS0D*/;
        TCut gate0c = gateCry + gateTofS1 + gateVertexZc + gateOpenAng + gateNID /*+ gateS0D*/;
        TCut gatec  = gateCry + gateTofS1 + gateVertexZc + gateOpenAng + gateNID /*+ gateS0D*/ + gateZ + gateAOQ; 
        TCut gate   = gateCry + gateTofS1 + gateVertexZ  + gateOpenAng + gateNID /*+ gateS0D*/ + gateZ + gateAOQ;
        TCut gatec2 = gateCryc2 + gateTofS1 + gateVertexZ  + gateOpenAng + gateNID /*+ gateS0D*/ + gateZ + gateAOQ;
        

        TString gate0Str = "";//"r_Crystal<7 X 32<tofS1<35 X |vertexZ-10|<30 X Finite(S0D)";
        TString gatecStr = "";//"r_Crystal<7 X 32<tofS1<35 X |vertexZ-160|<30 X Finite(S0D) X 8.6>pidZ>7.4";
        TString gateStr  = "";//"r_Crystal<7 X 32<tofS1<35 X |vertexZ-10|<30 X Finite(S0D) X 8.6>pidZ>7.4";

        Double_t BGscale = 1.0;
/*        
        TCut cut23o = "TMath::Abs(pidAOQ*8-23)<0.5";
        TCut cut22o = "TMath::Abs(pidAOQ*8-22)<0.5";
        TCut cut21o = "TMath::Abs(pidAOQ*8-21)<0.5";
        TCut cut20o = "TMath::Abs(pidAOQ*8-20)<0.5";
        TCut cut19o = "TMath::Abs(pidAOQ*8-19)<0.5";
        TCut cut18o = "TMath::Abs(pidAOQ*8-18)<0.5";

/**/
        TCutG * gate22o = new TCutG("cut22o", 6);
        gate22o->SetVarX("pidAOQ");
        gate22o->SetVarY("pidZ");
        gate22o->SetPoint(0, 2.68, 8.44);
        gate22o->SetPoint(1, 2.68, 7.48);
        gate22o->SetPoint(2, 2.73, 7.20);
        gate22o->SetPoint(3, 2.80, 7.59);
        gate22o->SetPoint(4, 2.80, 8.46);
        gate22o->SetPoint(5, 2.73, 9.01);
        gate22o->SetPoint(6, 2.68, 8.44);

        TCutG * gate21o = new TCutG("cut21o", 6);
        gate21o->SetVarX("pidAOQ");
        gate21o->SetVarY("pidZ");
        gate21o->SetPoint(0, 2.56, 8.24);
        gate21o->SetPoint(1, 2.56, 7.53);
        gate21o->SetPoint(2, 2.63, 7.23);
        gate21o->SetPoint(3, 2.68, 7.54);
        gate21o->SetPoint(4, 2.68, 8.44);
        gate21o->SetPoint(5, 2.63, 8.75);
        gate21o->SetPoint(6, 2.56, 8.24);

        TCutG * gate20o = new TCutG("cut20o", 6);
        gate20o->SetVarX("pidAOQ");
        gate20o->SetVarY("pidZ");
        gate20o->SetPoint(0, 2.42, 8.27);
        gate20o->SetPoint(1, 2.42, 7.65);
        gate20o->SetPoint(2, 2.50, 7.20);
        gate20o->SetPoint(3, 2.56, 7.53);
        gate20o->SetPoint(4, 2.56, 8.24);
        gate20o->SetPoint(5, 2.49, 8.71);
        gate20o->SetPoint(6, 2.42, 8.27);

        TCutG * gate19o = new TCutG("cut19o", 6);
        gate19o->SetVarX("pidAOQ");
        gate19o->SetVarY("pidZ");
        gate19o->SetPoint(0, 2.31, 8.33);
        gate19o->SetPoint(1, 2.31, 7.62);
        gate19o->SetPoint(2, 2.37, 7.31);
        gate19o->SetPoint(3, 2.42, 7.65);
        gate19o->SetPoint(4, 2.42, 8.27);
        gate19o->SetPoint(5, 2.37, 8.64);
        gate19o->SetPoint(6, 2.31, 8.33);

        TCutG * gate18o = new TCutG("cut18o", 6);
        gate18o->SetVarX("pidAOQ");
        gate18o->SetVarY("pidZ");
        gate18o->SetPoint(0, 2.19, 8.35);
        gate18o->SetPoint(1, 2.19, 7.62);
        gate18o->SetPoint(2, 2.27, 7.36);
        gate18o->SetPoint(3, 2.31, 7.64);
        gate18o->SetPoint(4, 2.31, 8.33);
        gate18o->SetPoint(5, 2.26, 8.71);
        gate18o->SetPoint(6, 2.19, 8.35);

        //*///======================================================== analysis
        //tree->Draw("


/*++++++++++++++++++++++++++++++++++++++++++++++ Sp*/

        tree->Draw("Ex>>oAll( 50, -140, 180)", gate )  ; oAll->SetTitle(gateStr);
        tree->Draw("Ex>>oAllc(50, -140, 180)", gatec ) ; oAllc->SetTitle(gatecStr); oAllc->SetLineColor(2);
        tree->Draw("Ex>>o22(  50, -40, 60)", gate  + "cut22o") ; //o22->SetTitle(gateStr + " X 22O");
        tree->Draw("Ex>>o21(  50, -40, 60)", gate  + "cut21o") ; //o21->SetTitle(gateStr + " X 21O");
        tree->Draw("Ex>>o20(  50, -40, 60)", gate  + "cut20o") ; //o20->SetTitle(gateStr + " X 20O");
        tree->Draw("Ex>>o19(  50, -40, 60)", gate  + "cut19o") ; //o19->SetTitle(gateStr + " X 19O");
        tree->Draw("Ex>>o18(  50, -40, 60)", gate  + "cut18o") ; //o18->SetTitle(gateStr + " X 18O");
        tree->Draw("Ex>>o22c( 50, -40, 60)", gatec + "cut22o") ; //o22c->SetTitle(gateStr + " X 22O");
        tree->Draw("Ex>>o21c( 50, -40, 60)", gatec + "cut21o") ; //o21c->SetTitle(gateStr + " X 21O");
        tree->Draw("Ex>>o20c( 50, -40, 60)", gatec + "cut20o") ; //o20c->SetTitle(gateStr + " X 20O");
        tree->Draw("Ex>>o19c( 50, -40, 60)", gatec + "cut19o") ; //o19c->SetTitle(gateStr + " X 19O");
        tree->Draw("Ex>>o18c( 50, -40, 60)", gatec + "cut18o") ; //o18c->SetTitle(gateStr + " X 18O");
        tree->Draw("Ex>>o22c2(50, -40, 60)", gatec2 + "cut22o") ; //o22c->SetTitle(gateStr + " X 22O");
        tree->Draw("Ex>>o21c2(50, -40, 60)", gatec2 + "cut21o") ; //o21c->SetTitle(gateStr + " X 21O");
        tree->Draw("Ex>>o20c2(50, -40, 60)", gatec2 + "cut20o") ; //o20c->SetTitle(gateStr + " X 20O");
        
        oAllc->Scale(BGscale); TH1F* mAll = new TH1F(*oAll - *oAllc); mAll->SetName("mAll");mAll->SetTitle("23F(p,2p)22O*"); mAll->SetLineColor(1); mAll->SetLineWidth(2);

        o22c->Scale(BGscale); TH1F* m22 = new TH1F(*o22 - *o22c); m22->SetLineColor(2); m22->SetName("m22"); m22->SetTitle("23F(p,2p)22Ogs");
        o21c->Scale(BGscale); TH1F* m21 = new TH1F(*o21 - *o21c); m21->SetLineColor(3); m21->SetName("m21"); m21->SetTitle("23F(p,2p)22O*->21O*+n, 6.86");
        o20c->Scale(BGscale); TH1F* m20 = new TH1F(*o20 - *o20c); m20->SetLineColor(4); m20->SetName("m20"); m20->SetTitle("23F(p,2p)22O*->20O*+2n, 10.65");
        o19c->Scale(BGscale); TH1F* m19 = new TH1F(*o19 - *o19c); m19->SetLineColor(6); m19->SetName("m19"); m19->SetTitle("23F(p,2p)22O*->19O*+3n, 18.28");
        o18c->Scale(BGscale); TH1F* m18 = new TH1F(*o18 - *o18c); m18->SetLineColor(9); m18->SetName("m18"); m18->SetTitle("23F(p,2p)22O*->18O*+4n, 22.22");
        
        m21->SetXTitle("Ex [MeV]"); m21->SetYTitle("count / 2 MeV");

        THStack *mS = new THStack("mS", "Stack of Ex for 22O - 18O");
        mS->Add(m22);
        mS->Add(m21);
        mS->Add(m20);
        //mS->Add(m19);
        //mS->Add(m18);
        
        //tree->Draw("Ex:pidAOQ*8>>hq(100,19,24, 100, -40, 60)", gate, "colz");
        //tree->Draw("Ex:pidAOQ*8>>hqc(100,19,24, 100, -40, 60)", gatec, "colz");
        //TH2F* mhq = new TH2F(*hq);
        //mhq->Add(hqc,-BGscale);

        
        TF1* fit22o = new TF1("fit22o", "gaus(0)", -40, 60);
        Double_t para22[3]={10, 0, 8};
        fit22o->SetParameters(para22);
        fit22o->FixParameter(1, 0);
        fit22o->SetLineColor(2);
        fit22o->SetLineStyle(1);
        fit22o->SetLineWidth(2);
        m22->Fit("fit22o", "R");
        printf("reduced chi-squared = %f \n", fit22o->GetChisquare()/fit22o->GetNDF());

        //TF1* fit21o = new TF1("fit21o", "gaus(0)+gaus(3)", -20, 60);
        //Double_t para21[6]={30, 8, 8, 10, 35, 10};
        TF1* fit21o = new TF1("fit21o", "gaus(0)", -40, 60);
        Double_t para21[3]={40, 10, 8};
        fit21o->SetParameters(para21);
        //fit21o->SetParLimits(4, 30, 40);
        fit21o->SetLineColor(3);
        fit21o->SetLineStyle(7);
        m21->Fit("fit21o", "R");
        printf("reduced chi-squared = %f \n", fit21o->GetChisquare()/fit21o->GetNDF());

        //TF1* fit20o = new TF1("fit20o", "gaus(0)+gaus(3)", -20, 60);
        //Double_t para20[6]={30, 14, 8, 10, 35, 10};
        TF1* fit20o = new TF1("fit20o", "gaus(0)", -40, 60);
        Double_t para20[6]={40, 18, 9};
        fit20o->SetParameters(para20);
        //fit20o->SetParLimits(4, 30, 40);
        fit20o->SetLineColor(4);
        fit20o->SetLineStyle(2);
        m20->Fit("fit20o", "R");
        
                
        m21->Draw();m22->Draw("same");m20->Draw("same");
        
        leg = new TLegend(0.1,0.6,0.3,0.9);
        //leg->SetHeader("");
        leg->SetTextSize(0.05);
        leg->AddEntry(fit22o, "(^{23}F,^{22}O)", "l");
        leg->AddEntry(fit21o, "(^{23}F,^{21}O)", "l");
        leg->AddEntry(fit20o, "(^{23}F,^{20}O)", "l");
        leg->Draw();
        
/*++++++++++++++++++++++++++++++++++++++++++++++ openAngle*/
/*
        tree->Draw("theta1+theta2>>aAll( 50, 40, 90)", gate )  ; aAll->SetTitle(gateStr);
        tree->Draw("theta1+theta2>>aAllc(50, 40, 90)", gatec ) ; aAllc->SetTitle(gatecStr); aAllc->SetLineColor(2);
        tree->Draw("theta1+theta2>>a22(  50, 40, 90)", gate  + "cut22o") ; //o22->SetTitle(gateStr + " X 22O");
        tree->Draw("theta1+theta2>>a21(  50, 40, 90)", gate  + "cut21o") ; //o21->SetTitle(gateStr + " X 21O");
        tree->Draw("theta1+theta2>>a20(  50, 40, 90)", gate  + "cut20o") ; //o20->SetTitle(gateStr + " X 20O");
        tree->Draw("theta1+theta2>>a22c( 50, 40, 90)", gatec + "cut22o") ; //o22c->SetTitle(gateStr + " X 22O");
        tree->Draw("theta1+theta2>>a21c( 50, 40, 90)", gatec + "cut21o") ; //o21c->SetTitle(gateStr + " X 21O");
        tree->Draw("theta1+theta2>>a20c( 50, 40, 90)", gatec + "cut20o") ; //o20c->SetTitle(gateStr + " X 20O");

        
        aAllc->Scale(BGscale); TH1F* bAll= new TH1F(*aAll- *aAllc);bAll->SetName("bAll");bAll->SetTitle("23F(p,2p)22O*"); bAll->SetLineColor(1); bAll->SetLineWidth(2);
        a22c->Scale(BGscale) ; TH1F* b22 = new TH1F(*a22 - *a22c); b22->SetLineColor(2); b22->SetName("m22"); b22->SetTitle("23F(p,2p)22Ogs");
        a21c->Scale(BGscale) ; TH1F* b21 = new TH1F(*a21 - *a21c); b21->SetLineColor(3); b21->SetName("m21"); b21->SetTitle("23F(p,2p)22O*->21O*+n, 6.86");
        a20c->Scale(BGscale) ; TH1F* b20 = new TH1F(*a20 - *a20c); b20->SetLineColor(4); b20->SetName("m20"); b20->SetTitle("23F(p,2p)22O*->20O*+2n, 10.65");

        b21->Draw();b22->Draw("same");b20->Draw("same");

/*++++++++++++++++++++++++++++++++++++++++++++++ Coplanar Angle*/
/*
        tree->Draw("phi2-phi1>>uAll( 50, -50, 50)", gate )  ; uAll->SetTitle(gateStr);
        tree->Draw("phi2-phi1>>uAllc(50, -50, 50)", gatec ) ; uAllc->SetTitle(gatecStr); uAllc->SetLineColor(2);
        tree->Draw("phi2-phi1>>u22(  50, -50, 50)", gate  + "cut22o") ; //o22->SetTitle(gateStr + " X 22O");
        tree->Draw("phi2-phi1>>u21(  50, -50, 50)", gate  + "cut21o") ; //o21->SetTitle(gateStr + " X 21O");
        tree->Draw("phi2-phi1>>u20(  50, -50, 50)", gate  + "cut20o") ; //o20->SetTitle(gateStr + " X 20O");
        tree->Draw("phi2-phi1>>u22c( 50, -50, 50)", gatec + "cut22o") ; //o22c->SetTitle(gateStr + " X 22O");
        tree->Draw("phi2-phi1>>u21c( 50, -50, 50)", gatec + "cut21o") ; //o21c->SetTitle(gateStr + " X 21O");
        tree->Draw("phi2-phi1>>u20c( 50, -50, 50)", gatec + "cut20o") ; //o20c->SetTitle(gateStr + " X 20O");

        
        uAllc->Scale(BGscale); TH1F* vAll= new TH1F(*uAll- *uAllc);vAll->SetName("bAll");vAll->SetTitle("23F(p,2p)22O*"); vAll->SetLineColor(1); vAll->SetLineWidth(2);
        u22c->Scale(BGscale) ; TH1F* v22 = new TH1F(*u22 - *u22c); v22->SetLineColor(2); v22->SetName("m22"); v22->SetTitle("23F(p,2p)22Ogs");
        u21c->Scale(BGscale) ; TH1F* v21 = new TH1F(*u21 - *u21c); v21->SetLineColor(3); v21->SetName("m21"); v21->SetTitle("23F(p,2p)22O*->21O*+n, 6.86");
        u20c->Scale(BGscale) ; TH1F* v20 = new TH1F(*u20 - *u20c); v20->SetLineColor(4); v20->SetName("m20"); v20->SetTitle("23F(p,2p)22O*->20O*+2n, 10.65");

        v21->Draw();v22->Draw("same");v20->Draw("same");

/*++++++++++++++++++++++++++++++++++++++++++++++ PID*/
/*
        tree->Draw("pidZ:pidAOQc>>hPID(100,2,3, 100, 4, 10)", gate0, "colz"); hPID->SetTitle(gate0Str);
        tree->Draw("pidAOQ*8>>hA(100,19, 24)", gate, "colz"); hA->SetTitle(gateStr);
        tree->Draw("pidAOQ*8>>hAc(100,19, 24)", gatec, "colz"); hAc->SetTitle(gateStr);
        tree->Draw("pidAOQ*8>>hAg(100,19, 24)", gate + "60>Ex && Ex>-40", "colz"); hAg->SetTitle(gateStr + " X 60>Ex>-40");
        tree->Draw("pidAOQ*8>>hAgc(100,19, 24)", gatec + "60>Ex && Ex>-40", "colz"); hAgc->SetTitle(gatecStr + " X 60>Ex>-40");

        hAc->Scale(BGscale); TH1F* hAs = new TH1F(*hA - *hAc); hAs->SetTitle("");
        
        printf("------------ 23F, tofS0DS1, pidZ\n");
        Double_t stemp = hA->Integral(51,70); Double_t btemp = hAc->Integral(51,70); printf("22O:%4.0f, %4.0f| %4.0f(%3.0f)\n", stemp, btemp,stemp-btemp, TMath::Sqrt(stemp+btemp));
        Double_t stemp = hA->Integral(31,50); Double_t btemp = hAc->Integral(31,50); printf("21O:%4.0f, %4.0f| %4.0f(%3.0f)\n", stemp, btemp,stemp-btemp, TMath::Sqrt(stemp+btemp));
        Double_t stemp = hA->Integral(11,30); Double_t btemp = hAc->Integral(11,30); printf("20O:%4.0f, %4.0f| %4.0f(%3.0f)\n", stemp, btemp,stemp-btemp, TMath::Sqrt(stemp+btemp));
        
        hAgc->Scale(BGscale); TH1F* hAgs = new TH1F(*hAg - *hAgc); hAgs->SetTitle("");
        
        printf("------------ 23F, tofS0DS1, pidZ, 60>Ex>-40\n");
        Double_t stemp = hAg->Integral(51,70); Double_t btemp = hAgc->Integral(51,70); printf("22O:%4.0f, %4.0f| %4.0f(%3.0f)\n",stemp,btemp, stemp-btemp, TMath::Sqrt(stemp+btemp));
        Double_t stemp = hAg->Integral(31,50); Double_t btemp = hAgc->Integral(31,50); printf("21O:%4.0f, %4.0f| %4.0f(%3.0f)\n",stemp,btemp, stemp-btemp, TMath::Sqrt(stemp+btemp));
        Double_t stemp = hAg->Integral(11,30); Double_t btemp = hAgc->Integral(11,30); printf("20O:%4.0f, %4.0f| %4.0f(%3.0f)\n",stemp,btemp, stemp-btemp, TMath::Sqrt(stemp+btemp));
        
        printf("------------ 23F, tofS0DS1, pidZ, r < 7\n");
        tree->Draw("pidAOQ*8>>hAg2(100,19, 24)",  gate  + gateCry, "colz");   hAg2->SetTitle(gateStr + " X 35>Ex>-40");
        tree->Draw("pidAOQ*8>>hAg2c(100,19, 24)", gatec + gateCry, "colz"); hAg2c->SetTitle(gatecStr + " X 35>Ex>-40");        
        Double_t stemp = hAg2->Integral(51,70); Double_t btemp = hAg2c->Integral(51,70); printf("22O:%4.0f, %4.0f| %4.0f(%3.0f)\n",stemp,btemp, stemp-btemp, TMath::Sqrt(stemp+btemp));
        Double_t stemp = hAg2->Integral(31,50); Double_t btemp = hAg2c->Integral(31,50); printf("21O:%4.0f, %4.0f| %4.0f(%3.0f)\n",stemp,btemp, stemp-btemp, TMath::Sqrt(stemp+btemp));
        Double_t stemp = hAg2->Integral(11,30); Double_t btemp = hAg2c->Integral(11,30); printf("20O:%4.0f, %4.0f| %4.0f(%3.0f)\n",stemp,btemp, stemp-btemp, TMath::Sqrt(stemp+btemp));

        printf("------------ 23F, tofS0DS1, pidZ, 60>Ex>-40, r > 7 \n");
        tree->Draw("pidAOQ*8>>hAg3(100,19, 24)", gate + gateCry   + "60>Ex && Ex>-40", "colz");   hAg3->SetTitle(gateStr + " X 35>Ex>-40");
        tree->Draw("pidAOQ*8>>hAg3c(100,19, 24)", gatec + gateCry + "60>Ex && Ex>-40", "colz"); hAg3c->SetTitle(gatecStr + " X 35>Ex>-40");
        Double_t stemp = hAg3->Integral(51,70); Double_t btemp = hAg3c->Integral(51,70); printf("22O:%4.0f, %4.0f| %4.0f(%3.0f)\n",stemp,btemp, stemp-btemp, TMath::Sqrt(stemp+btemp));
        Double_t stemp = hAg3->Integral(31,50); Double_t btemp = hAg3c->Integral(31,50); printf("21O:%4.0f, %4.0f| %4.0f(%3.0f)\n",stemp,btemp, stemp-btemp, TMath::Sqrt(stemp+btemp));
        Double_t stemp = hAg3->Integral(11,30); Double_t btemp = hAg3c->Integral(11,30); printf("20O:%4.0f, %4.0f| %4.0f(%3.0f)\n",stemp,btemp, stemp-btemp, TMath::Sqrt(stemp+btemp));

        printf("------------ 23F, tofS0DS1, pidZ,  60>Ex>-40, 14 > r > 7\n");
        tree->Draw("pidAOQ*8>>hAg4(100,19, 24)", gate +   gateCryc + "60>Ex && Ex>-40", "colz");   hAg4->SetTitle(gateStr + " X 35>Ex>-40");
        tree->Draw("pidAOQ*8>>hAg4c(100,19, 24)", gatec + gateCryc + "60>Ex && Ex>-40", "colz"); hAg4c->SetTitle(gatecStr + " X 35>Ex>-40");
        Double_t stemp = hAg4->Integral(51,70); Double_t btemp = hAg4c->Integral(51,70); printf("22O:%4.0f, %4.0f| %4.0f(%3.0f)\n",stemp,btemp, stemp-btemp, TMath::Sqrt(stemp+btemp));
        Double_t stemp = hAg4->Integral(31,50); Double_t btemp = hAg4c->Integral(31,50); printf("21O:%4.0f, %4.0f| %4.0f(%3.0f)\n",stemp,btemp, stemp-btemp, TMath::Sqrt(stemp+btemp));
        Double_t stemp = hAg4->Integral(11,30); Double_t btemp = hAg4c->Integral(11,30); printf("20O:%4.0f, %4.0f| %4.0f(%3.0f)\n",stemp,btemp, stemp-btemp, TMath::Sqrt(stemp+btemp));

        printf("------------ 23F, tofS0DS1, pidZ,  60>Ex>-40, r > 14\n");
        tree->Draw("pidAOQ*8>>hAg5(100,19, 24)", gate +   gateCryc2 + "60>Ex && Ex>-40", "colz"); hAg5->SetTitle(gateStr + " X 35>Ex>-40");
        tree->Draw("pidAOQ*8>>hAg5c(100,19, 24)", gatec + gateCryc2 + "60>Ex && Ex>-40", "colz"); hAg5c->SetTitle(gatecStr + " X 35>Ex>-40");
        Double_t stemp = hAg5->Integral(51,70); Double_t btemp = hAg5c->Integral(51,70); printf("22O:%4.0f, %4.0f| %4.0f(%3.0f)\n",stemp,btemp, stemp-btemp, TMath::Sqrt(stemp+btemp));
        Double_t stemp = hAg5->Integral(31,50); Double_t btemp = hAg5c->Integral(31,50); printf("21O:%4.0f, %4.0f| %4.0f(%3.0f)\n",stemp,btemp, stemp-btemp, TMath::Sqrt(stemp+btemp));
        Double_t stemp = hAg5->Integral(11,30); Double_t btemp = hAg5c->Integral(11,30); printf("20O:%4.0f, %4.0f| %4.0f(%3.0f)\n",stemp,btemp, stemp-btemp, TMath::Sqrt(stemp+btemp));


        //TF1* fit = new TF1("fit", "gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)+gaus(15)", 16, 24);
        //Double_t para[18]={40, 17, 0.5, 80, 18, 0.5, 100, 19, 0.4, 210, 20, 0.3, 170, 21, 0.3, 40, 22, 0.3};
        //Double_t para[18]={10, 17, 0.5, 20, 18, 0.5, 40, 19, 0.4, 90, 20, 0.3, 80, 21, 0.3, 20, 22, 0.3};

        //TF1* fit = new TF1("fit", "gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)", 16, 24);
        //Double_t para[18]={40, 17, 0.5, 80, 18, 0.5, 100, 19, 0.4, 210, 20, 0.3, 170, 21, 0.3, 40, 22, 0.3};
        //Double_t para[15]={20, 18, 0.5, 40, 19, 0.4, 90, 20, 0.3, 80, 21, 0.3, 20, 22, 0.3};
/*
        TF1* fit = new TF1("fit", "gaus(0)+gaus(3)+gaus(6)", 19.5, 24);
        Double_t para[15]={80, 20, 0.3, 50, 21, 0.3, 10, 22, 0.3};

        fit->SetParameters(para);
        fit->SetLineColor(1);
        //fit->FixParameter(7,22);
        hAgs->Fit("fit","R");
        printf("reduced chi-squared = %f \n", fit->GetChisquare()/fit->GetNDF());        

        fit->GetParameters(para);
        TF1* g1 = new TF1("g1", "gaus(0)", 16, 24); g1->SetParameters(&para[0]); g1->SetLineColor(4); g1->Draw("same");
        TF1* g2 = new TF1("g2", "gaus(0)", 16, 24); g2->SetParameters(&para[3]); g2->SetLineColor(3); g2->Draw("same");
        TF1* g3 = new TF1("g3", "gaus(0)", 16, 24); g3->SetParameters(&para[6]); g3->SetLineColor(2); g3->Draw("same");
        //TF1* g4 = new TF1("g4", "gaus(0)", 16, 24); g4->SetParameters(&para[9]); g4->SetLineColor(3); g4->Draw("same");
        //TF1* g5 = new TF1("g5", "gaus(0)", 16, 24); g5->SetParameters(&para[12]); g5->SetLineColor(2); g5->Draw("same");
        //TF1* g6 = new TF1("g6", "gaus(0)", 16, 24); g6->SetParameters(&para[15]); g6->SetLineColor(2); g6->Draw("same");


        //tree->Draw("nyokiM:pidAOQ*8>>hAgM(80,16, 24, 5, 0, 5)", gate + "60>Ex && Ex>-40", "colz");
        //tree->Draw("pidZ>>hZ(60,4,10)", gate0 + "60>Ex && Ex>-40", "colz");   hZ->SetTitle(gateStr + " X 60>Ex>-40");
        //tree->Draw("pidZ>>hZc(60,4,10)", gate0c + "60>Ex && Ex>-40", "colz"); hZc->SetTitle(gatecStr + " X 60>Ex>-40"); hZc->SetLineColor(2);
        //
        //hZc->Scale(BGscale); TH1F* hZs = new TH1F(*hZ - *hZc); hZs->SetTitle("");
        /*
        hPID->ProjectionY("hZ");
        
        TF1* fitZ = new TF1("fitZ", "gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)", 4, 10);
        Double_t paraZ[15]={30, 5, 0.3, 100, 6, 0.2, 110, 7, 0.3, 270, 8, 0.3, 20, 9, 0.5};

        //TF1* fitZ = new TF1("fitZ", "gaus(0)+gaus(3)+gaus(6)+gaus(9)", 4, 10);
        //Double_t paraZ[15]={30, 5, 0.3, 100, 6, 0.2, 110, 7, 0.3, 270, 8, 0.3};

        fitZ->SetParameters(paraZ);
        fitZ->SetLineColor(1);
        hZ->Fit("fitZ");
        printf("reduced chi-squared = %f \n", fitZ->GetChisquare()/fitZ->GetNDF());        

        fitZ->GetParameters(paraZ);
        TF1* j1 = new TF1("j1", "gaus(0)", 4, 10); j1->SetParameters(&paraZ[0]);  j1->SetLineColor(9); j1->Draw("same");
        TF1* j2 = new TF1("j2", "gaus(0)", 4, 10); j2->SetParameters(&paraZ[3]);  j2->SetLineColor(6); j2->Draw("same");
        TF1* j3 = new TF1("j3", "gaus(0)", 4, 10); j3->SetParameters(&paraZ[6]);  j3->SetLineColor(4); j3->Draw("same");
        TF1* j4 = new TF1("j4", "gaus(0)", 4, 10); j4->SetParameters(&paraZ[9]);  j4->SetLineColor(3); j4->Draw("same");
        TF1* j5 = new TF1("j5", "gaus(0)", 4, 10); j5->SetParameters(&paraZ[12]); j5->SetLineColor(2); j5->Draw("same");
        
        //hZc->Draw("same");


/*++++++++++++++++++++++++++++++++++++++++++++++ Momentum*/
/*
        //tree->Draw("(0.002*kE + kp)/sqrt(1-0.002*0.002)>>p22(  9, -300, 300)", gate  + cut22o +"TMath::Abs(Ex)<20") ; //o22->SetTitle(gateStr + " X 22O");
        //tree->Draw("(0.002*kE + kp)/sqrt(1-0.002*0.002)>>p21(  18, -300, 300)", gate  + cut21o +"TMath::Abs(Ex-8)<20") ; //o21->SetTitle(gateStr + " X 21O");
        //tree->Draw("(0.002*kE + kp)/sqrt(1-0.002*0.002)>>p20(  18, -300, 300)", gate  + cut20o +"TMath::Abs(Ex-15)<20") ; //o20->SetTitle(gateStr + " X 20O");
        //tree->Draw("(0.002*kE + kp)/sqrt(1-0.002*0.002)>>p22c( 9, -300, 300)", gatec + cut22o +"TMath::Abs(Ex)<20") ; //o22c->SetTitle(gateStr + " X 22O");
        //tree->Draw("(0.002*kE + kp)/sqrt(1-0.002*0.002)>>p21c( 18, -300, 300)", gatec + cut21o +"TMath::Abs(Ex-8)<20") ; //o21c->SetTitle(gateStr + " X 21O");
        //tree->Draw("(0.002*kE + kp)/sqrt(1-0.002*0.002)>>p20c( 18, -300, 300)", gatec + cut20o +"TMath::Abs(Ex-15)<20") ; //o20c->SetTitle(gateStr + " X 20O");

        tree->Draw("kMomt>>p22(  40, 0, 400)", gate  + "cut22o" +"TMath::Abs(Ex)<20") ; //o22->SetTitle(gateStr + " X 22O");
        tree->Draw("kMomt>>p21(  40, 0, 400)", gate  + "cut21o" +"TMath::Abs(Ex-10)<10") ; //o21->SetTitle(gateStr + " X 21O");
        tree->Draw("kMomt>>p20(  40, 0, 400)", gate  + "cut20o" +"TMath::Abs(Ex-20)<20") ; //o20->SetTitle(gateStr + " X 20O");
        tree->Draw("kMomt>>p22c( 40, 0, 400)", gatec + "cut22o" +"TMath::Abs(Ex)<20") ; //o22c->SetTitle(gateStr + " X 22O");
        tree->Draw("kMomt>>p21c( 40, 0, 400)", gatec + "cut21o" +"TMath::Abs(Ex-10)<10") ; //o21c->SetTitle(gateStr + " X 21O");
        tree->Draw("kMomt>>p20c( 40, 0, 400)", gatec + "cut20o" +"TMath::Abs(Ex-20)<20") ; //o20c->SetTitle(gateStr + " X 20O");

        p22c->Scale(BGscale); TH1F* q22 = new TH1F(*p22 - *p22c); q22->SetLineColor(1); q22->SetName("q22"); q22->SetTitle("23F(p,2p)22Ogs");
        p21c->Scale(BGscale); TH1F* q21 = new TH1F(*p21 - *p21c); q21->SetLineColor(1); q21->SetName("q21"); q21->SetTitle("23F(p,2p)22O*->21O*+n, 6.86");
        p20c->Scale(BGscale); TH1F* q20 = new TH1F(*p20 - *p20c); q20->SetLineColor(1); q20->SetName("q20"); q20->SetTitle("23F(p,2p)22O*->20O*+2n, 10.65");

        q22->SetXTitle("k [MeV/c]"); q22->SetYTitle("count / 10 MeV"); q22->SetTitle("Ex = 0 MeV");
        q21->SetXTitle("k [MeV/c]"); q21->SetYTitle("count / 10 MeV"); q21->SetTitle("Ex = 10 MeV,");
        q20->SetXTitle("k [MeV/c]"); q20->SetYTitle("count / 10 MeV"); q20->SetTitle("Ex = 20 MeV");
        
        Ex00->Draw("k>>hk0a(40, 0, 400)", "xsec1d5", "E"); hk0a->SetLineColor(2); 
        Ex00->Draw("k>>hk0b(40, 0, 400)", "xsec1p1", "E"); hk0b->SetLineColor(3); 
        Ex00->Draw("k>>hk0c(40, 0, 400)", "xsec1p3", "E"); hk0c->SetLineColor(4); 
        Ex00->Draw("k>>hk0d(40, 0, 400)", "xsec2s1", "E"); hk0d->SetLineColor(6);
        Ex10->Draw("k>>hk1a(40, 0, 400)", "xsec1d5", "E"); hk1a->SetLineColor(2); 
        Ex10->Draw("k>>hk1b(40, 0, 400)", "xsec1p1", "E"); hk1b->SetLineColor(3); 
        Ex10->Draw("k>>hk1c(40, 0, 400)", "xsec1p3", "E"); hk1c->SetLineColor(4); 
        Ex10->Draw("k>>hk1d(40, 0, 400)", "xsec2s1", "E"); hk1d->SetLineColor(6); 
        Ex20->Draw("k>>hk2a(40, 0, 400)", "xsec1d5", "E"); hk2a->SetLineColor(2); 
        Ex20->Draw("k>>hk2b(40, 0, 400)", "xsec1p1", "E"); hk2b->SetLineColor(3); 
        Ex20->Draw("k>>hk2c(40, 0, 400)", "xsec1p3", "E"); hk2c->SetLineColor(4); 
        Ex20->Draw("k>>hk2d(40, 0, 400)", "xsec2s1", "E"); hk2d->SetLineColor(6); 
        
        Double_t temp = hk0a->GetMaximum(); 
        hk0a->Scale(q22->GetMaximum()/temp);
        hk0b->Scale(q22->GetMaximum()/temp);
        hk0c->Scale(q22->GetMaximum()/temp);
        hk0d->Scale(q22->GetMaximum()/temp);
        Double_t temp = hk1b->GetMaximum(); 
        hk1a->Scale(q21->GetMaximum()/temp);
        hk1b->Scale(q21->GetMaximum()/temp);
        hk1c->Scale(q21->GetMaximum()/temp);
        hk1d->Scale(q21->GetMaximum()/temp);
        Double_t temp = hk2c->GetMaximum(); 
        hk2a->Scale(q20->GetMaximum()/temp);  
        hk2b->Scale(q20->GetMaximum()/temp);  
        hk2c->Scale(q20->GetMaximum()/temp);
        hk2d->Scale(q20->GetMaximum()/temp);
        
        q22->SetMaximum(hk0a->GetMaximum()*1.1);
        q21->SetMaximum(hk1a->GetMaximum()*1.1);
        q20->SetMaximum(hk2a->GetMaximum()*1.1);
        
        
        q22->Draw();hk0a->Draw("same");hk0b->Draw("same");hk0c->Draw("same"); hk0d->Draw("same");
//        q21->Draw();hk1a->Draw("same");hk1b->Draw("same");hk1c->Draw("same"); hk1d->Draw("same");

/*++++++++++++++++++++++++++++++++++++++++++++++ Asymmetry*//*
        TCutG* cutAsy = gate20o;
        TString plotTitle = "(23F,20O)"; 
        TCut energy = "abs(Ex-18)<10";
                
        cutAsy->SetName("cutAsy");

        tree->Draw("theta1>>h2aL(5,20,70)", gate + "cutAsy" + energy + "runNum<=36", "colz");
        tree->Draw("theta2>>h2aR(5,20,70)", gate + "cutAsy" + energy + "runNum<=36", "colz");
        
        tree->Draw("theta1>>h2aLg(5,20,70)", gatec + "cutAsy" + energy + "runNum<=36", "colz");
        tree->Draw("theta2>>h2aRg(5,20,70)", gatec + "cutAsy" + energy + "runNum<=36", "colz");
        
        TH1F* h2aLs = new TH1F(*h2aL - *h2aLg); h2aLs->SetName("h2aLs"); h2aLs->SetLineColor(4);
        TH1F* h2aRs = new TH1F(*h2aR - *h2aRg); h2aRs->SetName("h2aRs"); h2aRs->SetLineColor(2);
        
        h2aLs->SetXTitle("theta [deg]"); h2aLs->SetYTitle("count / 10 deg"); h2aLs->SetTitle(plotTitle + "Spin up");
        h2aRs->SetXTitle("theta [deg]"); h2aRs->SetYTitle("count / 10 deg"); h2aRs->SetTitle(plotTitle + "Spin up");
        
        cPostAna->cd(1);
        h2aRs->Draw("");
        h2aLs->Draw("same");
        
        
        tree->Draw("theta1>>h2bL(5,20,70)", gate + "cutAsy" + energy + "runNum>36", "colz");
        tree->Draw("theta2>>h2bR(5,20,70)", gate + "cutAsy" + energy + "runNum>36", "colz");
        
        tree->Draw("theta1>>h2bLg(5,20,70)", gatec + "cutAsy" + energy + "runNum>36", "colz");
        tree->Draw("theta2>>h2bRg(5,20,70)", gatec + "cutAsy" + energy + "runNum>36", "colz");
        
        TH1F* h2bLs = new TH1F(*h2bL - *h2bLg); h2bLs->SetName("h2bLs"); h2bLs->SetLineColor(4);
        TH1F* h2bRs = new TH1F(*h2bR - *h2bRg); h2bRs->SetName("h2bRs"); h2bRs->SetLineColor(2);
        
        h2bLs->SetXTitle("theta [deg]"); h2bLs->SetYTitle("count / 10 deg"); h2bLs->SetTitle(plotTitle + "Spin down");
        h2bRs->SetXTitle("theta [deg]"); h2bRs->SetYTitle("count / 10 deg"); h2bRs->SetTitle(plotTitle + "Spin down");
        
        Ex10->Draw("theta1>>g1(5,20,70)", "xsec1p1*(1+asym1p1)","");
        Ex10->Draw("theta2>>g2(5,20,70)", "xsec1p1*(1+asym1p1)","");
        
        cPostAna->cd(2);
        h2bLs->Draw("E"); h2bLs->Draw("same");
        h2bRs->Draw("E same"); h2bRs->Draw("same");
        
        cPostAna->cd(1);
        h2aLs->Draw("E"); h2aLs->Draw("same");
        h2aRs->Draw("E same"); h2aRs->Draw("same");
        
        //--------------------calculate AyP
        Int_t nBin = h2aLs->GetNbinsX();
        
        Double_t yLu[nBin], yRu[nBin], yLd[nBin], yRd[nBin];
        Double_t xBin[nBin], AyP[nBin];
        
        for ( Int_t l = 1; l <= nBin; l++){
                Int_t i = l-1;
                xBin[i] = h2aLs->GetBinCenter(l);
                yLu[i]=h2aLs->GetBinContent(l);
                yRu[i]=h2aRs->GetBinContent(l);
                yLd[i]=h2bLs->GetBinContent(l);
                yRd[i]=h2bRs->GetBinContent(l);
                
                Double_t tYL = g1->GetBinContent(l);
                Double_t tYR = g2->GetBinContent(l);
                
                Double_t tAy = (tYL-tYR)/(tYL+tYR);
                
                Double_t YL = TMath::Sqrt(yLu[i]*yRd[i]);
                Double_t YR = TMath::Sqrt(yRu[i]*yLd[i]);
                
                Double_t dYL = TMath::Sqrt(yLu[i] + yRd[i])/2;
                Double_t dYR = TMath::Sqrt(yLd[i] + yRu[i])/2;
                
                AyP[i] = (YL - YR)/(YL + YR);
                
                Double_t dAyP = TMath::Sqrt(YL*YL*dYR*dYR + YR*YR*dYL*dYL)/TMath::Power(YL + YR,2);
                
                Double_t Ay = AyP[i]/0.3;
                Double_t dAy = Ay * TMath::Sqrt( TMath::Power(dAyP/AyP[i],2) + TMath::Power(dAyP/AyP[i],2));
                
                printf("x:%4.0f, yLu:%4.0f, yRu:%4.0f, yLd:%4.0f, yRd:%4.0f, AyP:%6.4f, dAyp:%10.6f, Ay:%10.6f, dAy:%10.6f, tAy:%10.6f\n", xBin[i], yLu[i], yRu[i], yLd[i], yRd[i], AyP[i], dAyP, Ay, dAy, tAy); 
        }
        
                
        

        
/***********/
}
