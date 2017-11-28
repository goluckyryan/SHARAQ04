{
        gROOT->Reset();
        gROOT->ProcessLine(".!date");
        gStyle->SetOptStat(0);

//========================================================

        //char * rootfile = "P_25F_timeoffset_58.9_59.7.root";
        //char * rootfile = "O_25F_timeoffset_58.9_59.7.root";
        //char * rootfile = "P_25F_ppcoin_r14_0715.root";
        //char * rootfile = "X2_25F_ppcoin_r14_0715.root"; // using correct momt calculation
        //char * rootfile = "X_25F_ppcoin_r14_0720_noCorr.root"; 
        char * rootfile = "Z_X_25F_ppcoin_r14_0720_noCorr.root"; // using for spectrum, tTpla offset + 0.2 from X_25*.root
        //char * rootfile = "X2_25F_ppcoin_r14_0720_noCorr.root"; // using correct momt calculation
        //char * rootfile = "X3_25F_ppcoin_r14_0720_noCorr.root"; // using s0dx-s0x as angle for downstream PID
        //char * rootfile = "X4_25F_ppcoin_r14_0720_noCorr.root"; // 20160512 dsPID
        //char * rootfile = "P_25F_ppcoin_r14_0715.root"; // 
        
        TFile *f0 = new TFile (rootfile, "read"); TTree *tree = (TTree*)f0->Get("tree");
        printf("=====> /// %15s //// is loaded. Total #Entry: %10d \n", rootfile,  tree->GetEntries());
        
        
        //char * rootfile1 = "X3_25F_ppcoin_r14_0720_noCorr.root"; // using s0dx-s0x as angle for downstream PID
        //TFile *f1 = new TFile (rootfile1, "read"); TTree *tree1 = (TTree*)f1->Get("tree");
        //printf("=====> /// %15s //// is loaded. Total #Entry: %10d \n", rootfile1,  tree1->GetEntries());
        
        
        //-------------- THREEDEE
        TFile *f00 = new TFile ("THREEDEE/25F_Sp14.4_Tc010_ang003_phi002_DiracYesPerey.root", "read"); TTree *Ex00 = (TTree*)f00->Get("tree");
        TFile *f10 = new TFile ("THREEDEE/25F_Sp19.4_Tc010_ang003_phi002_DiracYesPerey.root", "read"); TTree *Ex05 = (TTree*)f10->Get("tree");
        TFile *f20 = new TFile ("THREEDEE/25F_Sp24.4_Tc010_ang003_phi002_DiracYesPerey.root", "read"); TTree *Ex13 = (TTree*)f20->Get("tree");
        TFile *f30 = new TFile ("THREEDEE/25F_Sp34.4_Tc010_ang003_phi002_DiracYesPerey.root", "read"); TTree *Ex20 = (TTree*)f30->Get("tree");
        
/**///======================================================== Browser or Canvas
        Int_t Div[2] = {2,1};  //x,y
        Int_t size[2] = {300,200}; //x,y
        TCanvas * cPostAna = new TCanvas("cPostAna", "cPostAna", 50, 0 , size[0]*Div[0], size[1]*Div[1]);
        cPostAna->Divide(Div[0],Div[1]);
        cPostAna->cd(1);

/**///======================================================== Cut 
        TCut gateCry = "s0x*s0x+TMath::Power(s0y-1.8,2)<49";
        TCut gateCryc = "s0x*s0x+TMath::Power(s0y-1.8,2)>49 && s0x*s0x+TMath::Power(s0y-1.8,2)<196";
        //TCut gateTofS1 = "35<tofS1 && tofS1<39";
        TCut gateTofS1 = "35<tofS0DS1 && tofS0DS1<39";
        TCut gateS0D = "TMath::Finite(s0dx)";
        TCut gateVertexZ = "TMath::Abs(vertexZ-10)<30";
        TCut gateVertexZc = "TMath::Abs(vertexZ-165)<50";
        //TCut gateOpenAng = "90>theta1+theta2 && theta1+theta2>60";
        //TCut gateOpenAng = "theta1>30 || theta2>30";
        TCut gateOpenAng = "";
        TCut gateZ = "8.6>pidZ && pidZ>7.4";
        //TCut gateZ = "pidZ>7.4";
        TCut gateNID = "";// "nyokiID>5";//"nyokiID > 3 && nyokiID <11";
        
        TCut gate0 = gateCry + gateTofS1 + gateVertexZ  + gateOpenAng + gateNID + gateS0D;
        TCut gatec = gateCry + gateTofS1 + gateVertexZc + gateOpenAng + gateNID + gateS0D + gateZ; 
        TCut gate =  gateCry + gateTofS1 + gateVertexZ  + gateOpenAng + gateNID + gateS0D + gateZ;
        
        TString gate0Str = "r_Crystal<7 X 32<tofS1<35 X |vertexZ-10|<30 X Finite(S0D)";
        TString gatecStr  = "r_Crystal<7 X 32<tofS1<35 X |vertexZ-160|<30 X Finite(S0D) X 8.6>pidZ>7.4";
        TString gateStr = "r_Crystal<7 X 32<tofS1<35 X |vertexZ-10|<30 X Finite(S0D) X 8.6>pidZ>7.4";
        
        //TCut cut22o = "TMath::Abs(pidAOQ*8-22)<0.5";
        //TCut cut23o = "TMath::Abs(pidAOQ*8-23)<0.5";
        //TCut cut23o = "22.5<pidAOQ*8 && pidAOQ*8 < 23.5";
        //TCut cut24o = "TMath::Abs(pidAOQ*8-24)<0.5";
        //TCut cut24o = "23.5<pidAOQ*8 && pidAOQ*8 < 28";

        Double_t BGscale = 1.;
        
        TCutG * gate21o = new TCutG("cut21o", 6);
        gate21o->SetVarX("pidAOQ");
        gate21o->SetVarY("pidZ");
        gate21o->SetPoint(0, 2.69-0.125, 8.58);
        gate21o->SetPoint(1, 2.68-0.125, 7.43);
        gate21o->SetPoint(2, 2.73-0.125, 7.30);
        gate21o->SetPoint(3, 2.79-0.125, 7.54);
        gate21o->SetPoint(4, 2.81-0.125, 8.63);
        gate21o->SetPoint(5, 2.75-0.125, 8.75);
        gate21o->SetPoint(6, 2.69-0.125, 8.58);
        
        TCutG * gate22o = new TCutG("cut22o", 6);
        gate22o->SetVarX("pidAOQ");
        gate22o->SetVarY("pidZ");
        gate22o->SetPoint(0, 2.81-0.125, 8.63);
        gate22o->SetPoint(1, 2.79-0.125, 7.54);
        gate22o->SetPoint(2, 2.84-0.125, 7.32);
        gate22o->SetPoint(3, 2.93-0.125, 7.43);
        gate22o->SetPoint(4, 2.95-0.125, 8.58);
        gate22o->SetPoint(5, 2.89-0.125, 8.76);
        gate22o->SetPoint(6, 2.81-0.125, 8.63);
        
        TCutG * gate23o = new TCutG("cut23o", 6);
        gate23o->SetVarX("pidAOQ");
        gate23o->SetVarY("pidZ");
        //gate23o->SetPoint(0, 2.95-0.125, 8.58);
        //gate23o->SetPoint(1, 2.93-0.125, 7.43);
        //gate23o->SetPoint(2, 2.85, 7.38);
        //gate23o->SetPoint(3, 2.93, 7.43);
        //gate23o->SetPoint(4, 2.95, 8.58);
        //gate23o->SetPoint(5, 2.89, 8.75);
        //gate23o->SetPoint(6, 2.95-0.125, 8.58);
        
        gate23o->SetPoint(0, 2.95-0.125, 8.58);
        gate23o->SetPoint(1, 2.93-0.125, 7.43);
        gate23o->SetPoint(2, 2.85, 7.38);
        gate23o->SetPoint(3, 2.92, 7.43);
        gate23o->SetPoint(4, 2.91, 8.72);
        gate23o->SetPoint(5, 2.89, 8.75);
        gate23o->SetPoint(6, 2.95-0.125, 8.58);
        
        TCutG * gate24o = new TCutG("cut24o", 6);
        gate24o->SetVarX("pidAOQ");
        gate24o->SetVarY("pidZ");
        gate24o->SetPoint(0, 2.91, 8.72);
        gate24o->SetPoint(1, 2.92, 7.43);
        gate24o->SetPoint(2, 3.04, 7.38);
        gate24o->SetPoint(3, 3.57, 7.72);
        gate24o->SetPoint(4, 3.56, 8.50);
        gate24o->SetPoint(5, 3.05, 9.00);
        gate24o->SetPoint(6, 2.91, 8.72);

//*///======================================================== analysis

/*++++++++++++++++++++++++++++++++++++++++++++++ E - theta */
/*
         tree->Draw("E1:theta1>>h1(50,10,80,50, 0, 400)", gate0 + gateZ + "-40<Ex && Ex<60", "colz" );
         h1->SetXTitle("theta1 [degree]");
         h1->SetYTitle("T1 [MeV]");
         h1->SetTitle("25F(p,2p)O, -40<Ex<60 MeV");

/*++++++++++++++++++++++++++++++++++++++++++++++ Spectrum*/
/*
        tree->Draw("Ex>>oAll( 150, -200, 100)", gate )  ; oAll->SetTitle(gateStr);
        tree->Draw("Ex>>oAllc(150, -200, 100)", gatec ) ; oAllc->SetTitle(gatecStr); oAllc->SetLineColor(2);
        tree->Draw("Ex>>o24(  25, -40, 60)", gate  + "cut24o") ; //o24->SetTitle(gateStr + " X 24O");
        tree->Draw("Ex>>o23(  25, -40, 60)", gate  + "cut23o") ; //o23->SetTitle(gateStr + " X 23O");
        tree->Draw("Ex>>o22(  25, -40, 60)", gate  + "cut22o") ; //o22->SetTitle(gateStr + " X 22O");
        tree->Draw("Ex>>o21(  25, -40, 60)", gate  + "cut21o") ; //o21->SetTitle(gateStr + " X 21O");
        tree->Draw("Ex>>o24c( 25, -40, 60)", gatec + "cut24o") ; //o24c->SetTitle(gateStr + " X 24O");
        tree->Draw("Ex>>o23c( 25, -40, 60)", gatec + "cut23o") ; //o23c->SetTitle(gateStr + " X 23O");
        tree->Draw("Ex>>o22c( 25, -40, 60)", gatec + "cut22o") ; //o22c->SetTitle(gateStr + " X 22O");
        tree->Draw("Ex>>o21c( 25, -40, 60)", gatec + "cut21o") ; //o21c->SetTitle(gateStr + " X 21O");
        
        oAllc->Scale(BGscale); TH1F* mAll = new TH1F(*oAll - *oAllc); mAll->SetName("mAll"); mAll->SetTitle("25F(p,2p)24O*");
        
        o24c->Scale(BGscale); TH1F* m24 = new TH1F(*o24 - *o24c); m24->SetName("m24"); m24->SetLineColor(2); m24->SetTitle("25F(p,2p)24Ogs (0, 4.19)");
        o23c->Scale(BGscale); TH1F* m23 = new TH1F(*o23 - *o23c); m23->SetName("m23"); m23->SetLineColor(3); m23->SetTitle("25F(p,2p)24O*->23O*+n,  (4.19, 6.93)");
        o22c->Scale(BGscale); TH1F* m22 = new TH1F(*o22 - *o22c); m22->SetName("m22"); m22->SetLineColor(4); m22->SetTitle("25F(p,2p)24O*->22O*+2n, (6.93, 13.8)");
        o21c->Scale(BGscale); TH1F* m21 = new TH1F(*o21 - *o21c); m21->SetName("m22"); m21->SetLineColor(6); m21->SetTitle("25F(p,2p)24O*->21O*+3n, (13.8, 17.6)");

        m22->SetXTitle("Ex [MeV]"); m22->SetYTitle("count / 4 MeV");
        m24->SetLineWidth(2);
        
        THStack *mS = new THStack("mS", "Stack of Ex for 22O - 18O");
        mS->Add(m24);
        mS->Add(m23);
        mS->Add(m22);
        mS->Add(m21);

        //tree->Draw("thetaR>>p24(  50, 0, 180)", gate  + "cut24o") ; //o22->SetTitle(gateStr + " X 22O");
        //tree->Draw("thetaR>>p23(  50, 0, 180)", gate  + "cut23o") ; //o21->SetTitle(gateStr + " X 21O");
        //tree->Draw("thetaR>>p22(  50, 0, 180)", gate  + "cut22o") ; //o20->SetTitle(gateStr + " X 20O");
        //
        //tree->Draw("thetaR>>p24c( 50, 0, 180)", gatec + "cut24o") ; //o22c->SetTitle(gateStr + " X 22O");
        //tree->Draw("thetaR>>p23c( 50, 0, 180)", gatec + "cut23o") ; //o21c->SetTitle(gateStr + " X 21O");
        //tree->Draw("thetaR>>p22c( 50, 0, 180)", gatec + "cut22o") ; //o20c->SetTitle(gateStr + " X 20O");
        //
        //p24c->Scale(BGscale); TH1F* q24 = new TH1F(*p24 - *p24c); q24->SetLineColor(2); q24->SetTitle("25F(p,2p)24Ogs");
        //p23c->Scale(BGscale); TH1F* q23 = new TH1F(*p23 - *p23c); q23->SetLineColor(3); q23->SetTitle("25F(p,2p)24O*->23O*+n, 4.18");
        //p22c->Scale(BGscale); TH1F* q22 = new TH1F(*p22 - *p22c); q22->SetLineColor(4); q22->SetTitle("25F(p,2p)24O*->22O*+2n, 6.93");

        TF1* fit24o = new TF1("fit24o", "gaus(0)", -40, 60);
        Double_t para24[3]={8, 0, 4};
        fit24o->SetParameters(para24);
        //fit24o->FixParameter(1, 0);
        fit24o->SetLineColor(2);
        fit24o->SetLineStyle(1);
        m24->Fit("fit24o", "R");
        printf("reduced chi-squared = %f \n", fit24o->GetChisquare()/fit24o->GetNDF());
        
        TF1* fit23o = new TF1("fit23o", "gaus(0)", -40, 60);
        Double_t para23[6]={12, 6, 6};
        fit23o->SetParameters(para23);
        //fit23o->SetParLimits(4, 30, 40);
        fit23o->SetLineColor(3);
        //fit23o->SetLineStyle(7);
        fit23o->SetLineStyle(1);
        m23->Fit("fit23o", "R");
        printf("reduced chi-squared = %f \n", fit23o->GetChisquare()/fit23o->GetNDF());
        
        TF1* fit22o = new TF1("fit22o", "gaus(0)", -40, 60);
        Double_t para22[6]={40, 13, 8};
        fit22o->SetParameters(para22);
        //fit22o->SetParLimits(4, 30, 40);
        fit22o->SetLineColor(4);
        //fit22o->SetLineStyle(2);
        fit22o->SetLineStyle(1);
        m22->Fit("fit22o", "R");
        printf("reduced chi-squared = %f \n", fit22o->GetChisquare()/fit22o->GetNDF());

        TF1* fit21o = new TF1("fit21o", "gaus(0)", -40, 60);
        Double_t para21[6]={15, 22, 8};
        fit21o->SetParameters(para21);
        //fit21o->SetParLimits(4, 30, 40);
        fit21o->SetLineColor(6);
        //fit21o->SetLineStyle(4);
        fit21o->SetLineStyle(1);
        m21->Fit("fit21o", "R");
        printf("reduced chi-squared = %f \n", fit21o->GetChisquare()/fit21o->GetNDF());
        
        
        //-------- count 
        Int_t sn24 = o24->Integral(7.,14.); Int_t n24 = o24c->Integral(7.,14.);
        Int_t sn23 = o23->Integral(8.,17.); Int_t n23 = o23c->Integral(8.,17.);
        Int_t sn22 = o22->Integral(8.,19.); Int_t n22 = o22c->Integral(8.,19.);
        Int_t sn21 = o21->Integral(12.,20.); Int_t n21 = o21c->Integral(12.,20.);
        
        printf(" 24O| SN:%4d, N:%4d, S:%4d(%3.0f) \n", sn24, n24, sn24-n24, sqrt(sn24+n24));
        printf(" 24O| SN:%4d, N:%4d, S:%4d(%3.0f) \n", sn23, n23, sn23-n23, sqrt(sn23+n23));
        printf(" 24O| SN:%4d, N:%4d, S:%4d(%3.0f) \n", sn22, n22, sn22-n22, sqrt(sn22+n22));
        printf(" 24O| SN:%4d, N:%4d, S:%4d(%3.0f) \n", sn21, n21, sn21-n21, sqrt(sn21+n21));
        
        
        m22->Draw();m24->Draw("same");m23->Draw("same");m21->Draw("same");
        /*
        leg = new TLegend(0.1,0.5,0.3,0.9);
        //leg->SetHeader("");
        leg->SetTextSize(0.05);
        leg->AddEntry(fit24o, "(^{25}F,^{24}O)", "l");
        leg->AddEntry(fit23o, "(^{25}F,^{23}O)", "l");
        leg->AddEntry(fit22o, "(^{25}F,^{22}O)", "l");
        leg->AddEntry(fit21o, "(^{25}F,^{21}O)", "l");
        leg->Draw();

/*++++++++++++++++++++++++++++++++++++++++++++++ downstream PID */
       /*
         // in P_xx has to subtract 1/8
         
        tree->Draw("Ex:pidAOQ*8>>hAEx(20,20,25, 20, -40, 60)", gate , "colz");
        tree->Draw("pidZ:pidAOQ>>hPID(40,2.5,3.2, 40, 4, 10)", gate0 + "60>Ex && Ex>-40", "colz");      hPID->SetTitle(gate0Str);
        tree->Draw("(pidAOQ)*8>>hA(60,20, 26)", gate, "colz");                        hA->SetTitle(gateStr);
        tree->Draw("(pidAOQ)*8>>hAg(60,20, 26)", gate   + "60>Ex && Ex>-40", "colz"); hAg->SetTitle(gateStr + " X 60>Ex>-40");
        tree->Draw("(pidAOQ)*8>>hAgc(60,20, 26)", gatec + "60>Ex && Ex>-40", "colz"); hAgc->SetTitle(gatecStr + " X 60>Ex>-40");
        
        hAgc->Scale(BGscale); TH1F* hAgs = new TH1F(*hAg - *hAgc); hAgs->SetTitle("");
        
        //tree->Draw("pidZ:pidAOQ>>hPID(100,2.2,3.2, 100, 4, 10)", "", "colz"); 
        tree->Draw("pidZ>>hZ(100,4,10)", gate0 + "pidAOQ>2.4", ""); 
        //tree->Draw("(pidAOQ)*8>>hA(60,20, 26)", "7.3<pidZ && pidZ<8.7", "colz"); 
        
        hZ->SetXTitle("Z"); hZ->SetYTitle("count / 0.06"); hZ->SetTitle("");
        hA->SetXTitle("A"); hA->SetYTitle("count / 0.1");  hA->SetTitle("");
        hAg->SetXTitle("A"); hAg->SetYTitle("count / 0.1"); hAg->SetTitle("");
        hAgc->SetXTitle("A"); hAgc->SetYTitle("count / 0.1"); hAgc->SetTitle("");
        
        TF1* fitZ = new TF1("fitZ", "gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)", 4, 10);
        Double_t paraZ[15]={150, 5, 0.3, 200, 6, 0.3, 250, 7, 0.3, 350, 8, 0.3, 100, 9, 0.3};
        fitZ->SetParameters(paraZ);
        fitZ->SetLineColor(1);        
        hZ->Fit("fitZ");
        printf("reduced chi-squared = %f \n", fitZ->GetChisquare()/fitZ->GetNDF());        
        
        fitZ->GetParameters(paraZ);
        TF1* k1 = new TF1("k1", "gaus(0)", 4, 10); k1->SetParameters(&paraZ[0]);  k1->SetLineColor(2); k1->Draw("same");
        TF1* k2 = new TF1("k2", "gaus(0)", 4, 10); k2->SetParameters(&paraZ[3]);  k2->SetLineColor(3); k2->Draw("same");
        TF1* k3 = new TF1("k3", "gaus(0)", 4, 10); k3->SetParameters(&paraZ[6]);  k3->SetLineColor(4); k3->Draw("same");
        TF1* k4 = new TF1("k4", "gaus(0)", 4, 10); k4->SetParameters(&paraZ[9]);  k4->SetLineColor(6); k4->Draw("same");
        TF1* k5 = new TF1("k5", "gaus(0)", 4, 10); k5->SetParameters(&paraZ[12]); k5->SetLineColor(2); k5->Draw("same");
        
        /*
        TF1* fit = new TF1("fit", "gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)", 20, 26);
        
         Int_t n20 = hA->FindBin(20); Double_t b20 = hA->GetBinContent(n20);
         Int_t n21 = hA->FindBin(21); Double_t b21 = hA->GetBinContent(n21);
         Int_t n22 = hA->FindBin(22); Double_t b22 = hA->GetBinContent(n22);
         Int_t n23 = hA->FindBin(23); Double_t b23 = hA->GetBinContent(n23);
         Int_t n24 = hA->FindBin(24); Double_t b24 = hA->GetBinContent(n24);
        
         Double_t para[15]={ b20, 20, 0.2,
                       b21, 21, 0.2, 
                       b22, 22, 0.2, 
                       b23, 23, 0.2, 
                       b24, 24, 0.2};
   
         Double_t MaxSigma = 0.5; 

        fit->SetParameters(para);
        fit->SetLineColor(1);
        fit->FixParameter(1,20);
        fit->FixParameter(4,21);
        fit->FixParameter(7,22);
        fit->FixParameter(10,23);
        fit->FixParameter(13,24);
        
         fit->SetParLimits(0 , 0, 2*b20);
         fit->SetParLimits(3 , 0, 2*b21);
         fit->SetParLimits(6 , 0, 2*b22);
         fit->SetParLimits(9 , 0, 2*b23);
         fit->SetParLimits(12, 0, 2*b24);
         
         fit->SetParLimits(2 , 0.1, MaxSigma);
         fit->SetParLimits(5 , 0.1, MaxSigma);
         fit->SetParLimits(8 , 0.1, MaxSigma);
         fit->SetParLimits(11, 0.1, MaxSigma);
         fit->SetParLimits(14, 0.1, MaxSigma);
        
        hA->Fit("fit");
        printf("reduced chi-squared = %f \n", fit->GetChisquare()/fit->GetNDF());        
        
        fit->GetParameters(para);
        TF1* g1 = new TF1("g1", "gaus(0)", 20, 26); g1->SetParameters(&para[0]); g1->SetLineColor(2); g1->Draw("same");
        TF1* g2 = new TF1("g2", "gaus(0)", 20, 26); g2->SetParameters(&para[3]); g2->SetLineColor(3); g2->Draw("same");
        TF1* g3 = new TF1("g3", "gaus(0)", 20, 26); g3->SetParameters(&para[6]); g3->SetLineColor(4); g3->Draw("same");
        TF1* g4 = new TF1("g4", "gaus(0)", 20, 26); g4->SetParameters(&para[9]); g4->SetLineColor(6); g4->Draw("same");
        TF1* g5 = new TF1("g5", "gaus(0)", 20, 26); g5->SetParameters(&para[12]); g5->SetLineColor(2); g5->Draw("same");
        
        
        //tree->Draw("nyokiM:pidAOQ*8>>hAgM(80,16, 24, 5, 0, 5)", gate + "60>Ex && Ex>-40", "colz");
        
        
/*++++++++++++++++++++++++++++++++++++++++++++++ Momentum*/

        tree->Draw("kMomt>>p24(  20, 0, 400)", gate  + "cut24o && 5>Ex && Ex>-10") ;   
        //tree->Draw("kMomt+10>>p23(  20, 0, 400)", gate  + "cut23o && 20>Ex && Ex>-10") ;
        tree->Draw("kMomt>>p22(  20, 0, 400)", gate  + "cut22o && 20>Ex && Ex>7") ;
        tree->Draw("kMomt>>p21(  20, 0, 400)", gate  + "cut21o && 40>Ex && Ex>10") ;
        tree->Draw("kMomt>>p24c( 20, 0, 400)", gatec + "cut24o && 5>Ex && Ex>-10") ;   
        //tree->Draw("kMomt+10>>p23c( 20, 0, 400)", gatec + "cut23o && 20>Ex && Ex>-10") ;
        tree->Draw("kMomt>>p22c( 20, 0, 400)", gatec + "cut22o && 20>Ex && Ex>7") ;
        tree->Draw("kMomt>>p21c( 20, 0, 400)", gatec + "cut21o && 40>Ex && Ex>10") ;
        
        TH1F* q23 = new TH1F("q23", "", 20, 0, 400);
        q23->SetLineColor(1);
        q23->SetXTitle("k [MeV/c]"); q23->SetYTitle("count / 20 MeV"); q23->SetTitle("");//"Ex = 5 MeV");

        q23->Fill(10,1);
        q23->Fill(70,1);
        q23->Fill(90,6);
        q23->Fill(110,4);
        q23->Fill(130,11);
        q23->Fill(150,9);
        q23->Fill(170,5);
        q23->Fill(210,-1);
        q23->Fill(250,3);
        q23->Fill(330,1);
        q23->Fill(350,1);

        p24c->Scale(BGscale); //TH1F* q24 = new TH1F(*p24 - *p24c); q24->SetLineColor(1); q24->SetName("q24"); q24->SetTitle("25F(p,2p)24Ogs");
        p22c->Scale(BGscale); //TH1F* q22 = new TH1F(*p22 - *p22c); q22->SetLineColor(1); q22->SetName("q22"); q22->SetTitle("25F(p,2p)24O*->22O*+2n, 6.93");
        p21c->Scale(BGscale); //TH1F* q21 = new TH1F(*p21 - *p21c); q21->SetLineColor(1); q21->SetName("q22"); q21->SetTitle("25F(p,2p)24O*->21O*+3n, 13.8");

         q23->Sumw2(1);

         Int_t nbin = p24->GetNbinsX();
         Double_t xmin = p24->GetBinLowEdge(1);
         Double_t xmax = p24->GetBinLowEdge(nbin+1);
         TH1F* q24 = new TH1F("q24", "", nbin,  xmin, xmax); q24->Sumw2(1); q24->Add(p24, p24c,1,-1);
         q24->SetLineColor(1);

         Int_t nbin = p22->GetNbinsX();
         Double_t xmin = p22->GetBinLowEdge(1);
         Double_t xmax = p22->GetBinLowEdge(nbin+1);
         TH1F* q22 = new TH1F("q22", "", nbin,  xmin, xmax); q22->Sumw2(1); q22->Add(p22, p22c,1,-1);
         q22->SetLineColor(1);

         Int_t nbin = p21->GetNbinsX();
         Double_t xmin = p21->GetBinLowEdge(1);
         Double_t xmax = p21->GetBinLowEdge(nbin+1);
         TH1F* q21 = new TH1F("q21", "", nbin,  xmin, xmax); q21->Sumw2(1); q21->Add(p21, p21c,1,-1);
         q21->SetLineColor(1);
         

        q24->SetXTitle("k [MeV/c]"); q24->SetYTitle("count / 20 MeV/c"); q24->SetTitle("");//"Ex = 0 MeV");
        q23->SetXTitle("k [MeV/c]"); q23->SetYTitle("count / 20 MeV/c"); q23->SetTitle("");//"Ex = 0 MeV");
        q22->SetXTitle("k [MeV/c]"); q22->SetYTitle("count / 20 MeV/c"); q22->SetTitle("");//"Ex = 13 MeV");
        q21->SetXTitle("k [MeV/c]"); q21->SetYTitle("count / 20 MeV/c"); q21->SetTitle("");//"Ex = 20 MeV");

        Ex00->Draw("k>>hk0a(20, 0, 400)", "xsec1d5", ""); hk0a->SetLineColor(2); 
        Ex00->Draw("k>>hk0b(20, 0, 400)", "xsec1p1", ""); hk0b->SetLineColor(3); 
        Ex00->Draw("k>>hk0c(20, 0, 400)", "xsec1p3", ""); hk0c->SetLineColor(4); 
        Ex00->Draw("k>>hk0d(20, 0, 400)", "xsec2s1", ""); hk0d->SetLineColor(6);
                                                
        Ex05->Draw("k>>hk1a(20, 0, 400)", "xsec1d5", ""); hk1a->SetLineColor(2); 
        Ex05->Draw("k>>hk1b(20, 0, 400)", "xsec1p1", ""); hk1b->SetLineColor(3); 
        Ex05->Draw("k>>hk1c(20, 0, 400)", "xsec1p3", ""); hk1c->SetLineColor(4); 
        Ex05->Draw("k>>hk1d(20, 0, 400)", "xsec2s1", ""); hk1d->SetLineColor(6); 
                                                
        Ex13->Draw("k>>hk2a(20, 0, 400)", "xsec1d5", ""); hk2a->SetLineColor(2); 
        Ex13->Draw("k>>hk2b(20, 0, 400)", "xsec1p1", ""); hk2b->SetLineColor(3); 
        Ex13->Draw("k>>hk2c(20, 0, 400)", "xsec1p3", ""); hk2c->SetLineColor(4); 
        Ex13->Draw("k>>hk2d(20, 0, 400)", "xsec2s1", ""); hk2d->SetLineColor(6); 
                                                
        Ex20->Draw("k>>hk3a(20, 0, 400)", "xsec1d5", ""); hk3a->SetLineColor(2); 
        Ex20->Draw("k>>hk3b(20, 0, 400)", "xsec1p1", ""); hk3b->SetLineColor(3); 
        Ex20->Draw("k>>hk3c(20, 0, 400)", "xsec1p3", ""); hk3c->SetLineColor(4); 
        Ex20->Draw("k>>hk3d(20, 0, 400)", "xsec2s1", ""); hk3d->SetLineColor(6); 
        
        
        Double_t temp = hk0a->GetMaximum()*1.2; 
        hk0a->Scale(q24->GetMaximum()/temp);
        hk0b->Scale(q24->GetMaximum()/temp);
        hk0c->Scale(q24->GetMaximum()/temp);
        hk0d->Scale(q24->GetMaximum()/temp);
        Double_t temp = hk1a->GetMaximum()*1.2; 
        hk1a->Scale(q23->GetMaximum()/temp);
        hk1b->Scale(q23->GetMaximum()/temp);
        hk1c->Scale(q23->GetMaximum()/temp);
        hk1d->Scale(q23->GetMaximum()/temp);
        Double_t temp = hk2b->GetMaximum()*1.2; 
        hk2a->Scale(q22->GetMaximum()/temp);  
        hk2b->Scale(q22->GetMaximum()/temp);  
        hk2c->Scale(q22->GetMaximum()/temp);
        hk2d->Scale(q22->GetMaximum()/temp);
        Double_t temp = hk3c->GetMaximum()*1.2; 
        hk3a->Scale(q21->GetMaximum()/temp);  
        hk3b->Scale(q21->GetMaximum()/temp);  
        hk3c->Scale(q21->GetMaximum()/temp);
        hk3d->Scale(q21->GetMaximum()/temp);
        
        q24->SetMaximum(hk0a->GetMaximum()*1.1);
        q23->SetMaximum(hk1a->GetMaximum()*1.1);
        q22->SetMaximum(hk2a->GetMaximum()*1.1);
        q21->SetMaximum(hk3a->GetMaximum()*1.1);
        
        /**/ //for small plot 
        cPostAna->cd(1)->SetTopMargin(0.01);
        cPostAna->cd(2)->SetTopMargin(0.01);
        cPostAna->cd(3)->SetTopMargin(0.01);
        cPostAna->cd(4)->SetTopMargin(0.01);
        cPostAna->cd(1)->SetRightMargin(0.05);
        cPostAna->cd(2)->SetRightMargin(0.05);
        cPostAna->cd(3)->SetRightMargin(0.05);
        cPostAna->cd(4)->SetRightMargin(0.05);
        cPostAna->cd(1)->SetLeftMargin(0.2);
        cPostAna->cd(2)->SetLeftMargin(0.2);
        cPostAna->cd(3)->SetLeftMargin(0.2);
        cPostAna->cd(4)->SetLeftMargin(0.2);
        cPostAna->cd(1)->SetBottomMargin(0.2);
        cPostAna->cd(2)->SetBottomMargin(0.2);
        cPostAna->cd(3)->SetBottomMargin(0.2);
        cPostAna->cd(4)->SetBottomMargin(0.2);
        
        cPostAna->cd(1)->SetGridx(0);
        cPostAna->cd(2)->SetGridx(0);
        cPostAna->cd(3)->SetGridx(0);
        cPostAna->cd(4)->SetGridx(0);
        cPostAna->cd(1)->SetGridy(0);
        cPostAna->cd(2)->SetGridy(0);
        cPostAna->cd(3)->SetGridy(0);
        cPostAna->cd(4)->SetGridy(0);
        
        q24->GetXaxis()->SetNdivisions(-505);
        q23->GetXaxis()->SetNdivisions(-505);
        q22->GetXaxis()->SetNdivisions(-505);
        q21->GetXaxis()->SetNdivisions(-505);
        
        q24->GetXaxis()->SetLabelSize(9e-2);
        q23->GetXaxis()->SetLabelSize(9e-2);
        q22->GetXaxis()->SetLabelSize(9e-2);
        q21->GetXaxis()->SetLabelSize(9e-2);
        q24->GetYaxis()->SetLabelSize(9e-2);
        q23->GetYaxis()->SetLabelSize(9e-2);
        q22->GetYaxis()->SetLabelSize(9e-2);
        q21->GetYaxis()->SetLabelSize(9e-2);
        q24->GetXaxis()->SetTitleSize(9e-2);
        q23->GetXaxis()->SetTitleSize(9e-2);
        q22->GetXaxis()->SetTitleSize(9e-2);
        q21->GetXaxis()->SetTitleSize(9e-2);
        q24->GetYaxis()->SetTitleSize(10e-2);
        q23->GetYaxis()->SetTitleSize(10e-2);
        q22->GetYaxis()->SetTitleSize(10e-2);
        q21->GetYaxis()->SetTitleSize(10e-2);
        q24->GetYaxis()->SetTitleOffset(0.8);
        q23->GetYaxis()->SetTitleOffset(0.8);
        q22->GetYaxis()->SetTitleOffset(0.8);
        q21->GetYaxis()->SetTitleOffset(0.8);
        
        //q24->GetYaxis()->SetLabelOffset(1.7);
        //q23->GetYaxis()->SetLabelOffset(1.7);
        /**/
        //q24->Draw();hk0a->Draw("l same");hk0b->Draw("l same");hk0c->Draw("l same");hk0d->Draw("l same");
        
        gROOT->ProcessLine(".L ryan/Replot.C");
        cPostAna->cd(1); Replot(hk0a, hk0b, hk0c, hk0d, q24,0, "(^{25}F,^{24}O)");
        cPostAna->cd(2); Replot(hk1a, hk1b, hk1c, hk1d, q23,0, "(^{25}F,^{23}O)");
        //cPostAna->cd(3); Replot(hk2a, hk2b, hk2c, hk2d, q22,0, "(^{25}F,^{22}O)");
        //cPostAna->cd(4); Replot(hk3a, hk3b, hk3c, hk3d, q21,0, "(^{25}F,^{21}O)");
        
        
        
        //cPostAna->cd(2);
        //gROOT->ProcessLine(".L ryan/Replot_fit.C");
        //Replot_fit(hk0a, hk0c, q24,0);
        //Replot_fit(hk1a, hk1c, q23,0);
        //Replot_fit(hk2a, hk2c, q22,0);
        //Replot_fit(hk3a, hk3c, q21,0);
        
        
        
        /**/
        
/*++++++++++++++++++++++++++++++++++++++++++++++ Asymmetry*/
/*
        TCutG* cutAsy = gate21o;
        TString plotTitle = "(25F,24O)"; 
        TCut energy = "abs(Ex-22)<15";
                
        cutAsy->SetName("cutAsy");

        tree->Draw("theta1>>h2aL(5,20,70)", gate + "cutAsy" + energy + "runNum<=43", "colz");
        tree->Draw("theta2>>h2aR(5,20,70)", gate + "cutAsy" + energy + "runNum<=43", "colz");
        
        tree->Draw("theta1>>h2aLg(5,20,70)", gatec + "cutAsy" + energy + "runNum<=43", "colz");
        tree->Draw("theta2>>h2aRg(5,20,70)", gatec + "cutAsy" + energy + "runNum<=43", "colz");
        
        TH1F* h2aLs = new TH1F(*h2aL - *h2aLg); h2aLs->SetName("h2aLs"); h2aLs->SetLineColor(4);
        TH1F* h2aRs = new TH1F(*h2aR - *h2aRg); h2aRs->SetName("h2aRs"); h2aRs->SetLineColor(2);
        
        h2aLs->SetXTitle("theta [deg]"); h2aLs->SetYTitle("count / 10 deg"); h2aLs->SetTitle(plotTitle + "Spin up");
        h2aRs->SetXTitle("theta [deg]"); h2aRs->SetYTitle("count / 10 deg"); h2aRs->SetTitle(plotTitle + "Spin up");
        
        cPostAna->cd(1);
        h2aRs->Draw("");
        h2aLs->Draw("same");
        
        tree->Draw("theta1>>h2bL(5,20,70)", gate + "cutAsy" + energy + "runNum>43", "colz");
        tree->Draw("theta2>>h2bR(5,20,70)", gate + "cutAsy" + energy + "runNum>43", "colz");
        
        tree->Draw("theta1>>h2bLg(5,20,70)", gatec + "cutAsy" + energy + "runNum>43", "colz");
        tree->Draw("theta2>>h2bRg(5,20,70)", gatec + "cutAsy" + energy + "runNum>43", "colz");
        
        TH1F* h2bLs = new TH1F(*h2bL - *h2bLg); h2bLs->SetName("h2bLs"); h2bLs->SetLineColor(4);
        TH1F* h2bRs = new TH1F(*h2bR - *h2bRg); h2bRs->SetName("h2bRs"); h2bRs->SetLineColor(2);
        
        h2bLs->SetXTitle("theta [deg]"); h2bLs->SetYTitle("count / 10 deg"); h2bLs->SetTitle(plotTitle + "Spin down");
        h2bRs->SetXTitle("theta [deg]"); h2bRs->SetYTitle("count / 10 deg"); h2bRs->SetTitle(plotTitle + "Spin down");
        
        Ex20->Draw("theta1>>g1(5,20,70)", "xsec1p3*(1+asym1p3)","");
        Ex20->Draw("theta2>>g2(5,20,70)", "xsec1p3*(1+asym1p3)","");
        
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
                
                printf("%2d, %2d, %2d, %2d, %2d, %2d, %2d, %2d \n", 
                        h2aL->GetBinContent(l),
                        h2aLg->GetBinContent(l),
                        h2aR->GetBinContent(l),
                        h2aRg->GetBinContent(l),
                        h2bL->GetBinContent(l),
                        h2bLg->GetBinContent(l),
                        h2bR->GetBinContent(l),
                        h2bRg->GetBinContent(l));
                
        /*        
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
        */
        }
        
                
/****/
}
