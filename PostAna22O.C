{
        gROOT->Reset();
        gROOT->ProcessLine(".!date");
        gStyle->SetOptStat(0);

        //========================================================

        char * rootfile = "X_22O_ppcoin_r14_0814.root";

        TFile *f0 = new TFile (rootfile, "read"); 
        TTree *tree = (TTree*)f0->Get("tree");
        
        //-------------- THREEDEE
        //TFile *f00 = new TFile ("THREEDEE/23F_Sp13.3_Tc030_ang010_phi00.root", "read"); TTree *Ex00 = (TTree*)f00->Get("tree");
        //TFile *f10 = new TFile ("THREEDEE/23F_Sp23.3_Tc030_ang010_phi00.root", "read"); TTree *Ex10 = (TTree*)f10->Get("tree");
        //TFile *f20 = new TFile ("THREEDEE/23F_Sp33.3_Tc030_ang010_phi00.root", "read"); TTree *Ex20 = (TTree*)f20->Get("tree");
        
        printf("=====> /// %15s //// is loaded. Total #Entry: %10d \n", rootfile,  tree->GetEntries());
        /**///======================================================== Browser or Canvas
        /*        Int_t Div[2] = {3,1};  //x,y
        Int_t size[2] = {500,500}; //x,y
        TCanvas * cPostAna = new TCanvas("cPostAna", "cPostAna", 2000, 0, 0 , size[0]*Div[0], size[1]*Div[1]);
        cPostAna->Divide(Div[0],Div[1]);


        /**///======================================================== Cut 
        TCut gateCry = "s0x*s0x+TMath::Power(s0y-1.8,2)<49";
        TCut gateCryc = "s0x*s0x+TMath::Power(s0y-1.8,2)>49 && s0x*s0x+TMath::Power(s0y-1.8,2)<196";
        TCut gateTofS1 = "33<tofS0DS1 && tofS0DS1<37";
        TCut gateS0D = "TMath::Finite(s0dx)";
        TCut gateVertexZ = "TMath::Abs(vertexZ-10)<30";
        TCut gateVertexZc = "TMath::Abs(vertexZ-160)<30";
        //TCut gateOpenAng = "90>theta1+theta2 && theta1+theta2>60";
        //TCut gateOpenAng = "theta1>30 || theta2>30";
        TCut gateOpenAng = "";
        TCut gateZ = "7.5>pidZ && pidZ>6.2";
        TCut gateNID = "";//"nyokiID > 3 && nyokiID <11";

        TCut gate0 = gateCry + gateTofS1 + gateVertexZ  + gateOpenAng + gateNID + gateS0D;
        TCut gate0c = gateCry + gateTofS1 + gateVertexZc  + gateOpenAng + gateNID + gateS0D;
        TCut gatec = gateCry + gateTofS1 + gateVertexZc + gateOpenAng + gateNID + gateS0D + gateZ; 
        TCut gate =  gateCry + gateTofS1 + gateVertexZ  + gateOpenAng + gateNID + gateS0D + gateZ;

        TString gate0Str = "r_Crystal<7 X 32<tofS0DS1<35 X |vertexZ-10|<30 X Finite(S0D)";
        TString gatecStr  = "r_Crystal<7 X 32<tofS0DS1<35 X |vertexZ-160|<30 X Finite(S0D) X 8.6>pidZ>7.4";
        TString gateStr = "r_Crystal<7 X 32<tofS0DS1<35 X |vertexZ-10|<30 X Finite(S0D) X 8.6>pidZ>7.4";

        TCut cut21n = "TMath::Abs(pidAOQ*7-21)<0.5";
        TCut cut20n = "TMath::Abs(pidAOQ*7-20)<0.5";
        TCut cut19n = "TMath::Abs(pidAOQ*7-19)<0.5";
        TCut cut18n = "TMath::Abs(pidAOQ*7-18)<0.5";

        Double_t BGscale = 1.;
/*
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

        tree->Draw("Ex>>nAll( 150, -200, 100)", gate )  ; nAll->SetTitle(gateStr);
        tree->Draw("Ex>>nAllc(150, -200, 100)", gatec ) ; nAllc->SetTitle(gatecStr); nAllc->SetLineColor(2);
        tree->Draw("Ex>>n21(  50, -40, 60)", gate  + cut21n) ;
        tree->Draw("Ex>>n20(  50, -40, 60)", gate  + cut20n) ;
        tree->Draw("Ex>>n19(  50, -40, 60)", gate  + cut19n) ;
        tree->Draw("Ex>>n18(  50, -40, 60)", gate  + cut18n) ;
        tree->Draw("Ex>>n21c( 50, -40, 60)", gatec + cut21n) ;
        tree->Draw("Ex>>n20c( 50, -40, 60)", gatec + cut20n) ;
        tree->Draw("Ex>>n19c( 50, -40, 60)", gatec + cut19n) ;
        tree->Draw("Ex>>n18c( 50, -40, 60)", gatec + cut18n) ;

        nAllc->Scale(BGscale); TH1F* mAll = new TH1F(*nAll - *nAllc); mAll->SetTitle("22O(p,2p)21N*");
        
        n21c->Scale(BGscale); TH1F* m21 = new TH1F(*n21 - *n21c); m21->SetLineColor(2); m21->SetName("m21"); m21->SetTitle("22O(p,2p)21N*->20N*+n, 4.49");
        n20c->Scale(BGscale); TH1F* m20 = new TH1F(*n20 - *n20c); m20->SetLineColor(3); m20->SetName("m20"); m20->SetTitle("22O(p,2p)21N*->19N*+2n,  6.74");
        n19c->Scale(BGscale); TH1F* m19 = new TH1F(*n19 - *n19c); m19->SetLineColor(4); m19->SetName("m19"); m19->SetTitle("22O(p,2p)21N*->18N*+3n, 12.07");
        n18c->Scale(BGscale); TH1F* m18 = new TH1F(*n18 - *n18c); m18->SetLineColor(6); m18->SetName("m18"); m18->SetTitle("22O(p,2p)21N*->17N*+4n, 14.91");
        
        m21->SetXTitle("Ex [MeV]"); m21->SetYTitle("count / 2 MeV");

        THStack *mS = new THStack("mS", "Stack of Ex for 21N - 18N");
        mS->Add(m21);
        mS->Add(m20);
        mS->Add(m19);
        mS->Add(m18);

        /*
        TF1* fit22o = new TF1("fit22o", "gaus(0)", -20, 60);
        Double_t para22[3]={30, 0, 8};
        fit22o->SetParameters(para22);
        fit22o->FixParameter(1, 0);
        fit22o->SetLineColor(1);
        m22->Fit("fit22o", "R");
        printf("reduced chi-squared = %f \n", fit22o->GetChisquare()/fit22o->GetNDF());

        TF1* fit21o = new TF1("fit21o", "gaus(0)+gaus(3)", -20, 60);
        Double_t para21[6]={30, 8, 8, 10, 35, 10};
        fit21o->SetParameters(para21);
        //fit21o->SetParLimits(4, 30, 40);
        fit21o->SetLineColor(1);
        m21->Fit("fit21o", "R");
        printf("reduced chi-squared = %f \n", fit21o->GetChisquare()/fit21o->GetNDF());

        TF1* fit20o = new TF1("fit20o", "gaus(0)+gaus(3)", -20, 60);
        Double_t para20[6]={30, 14, 8, 10, 35, 10};
        fit20o->SetParameters(para20);
        //fit20o->SetParLimits(4, 30, 40);
        fit20o->SetLineColor(1);
        m20->Fit("fit20o", "R");
        printf("reduced chi-squared = %f \n", fit21o->GetChisquare()/fit21o->GetNDF());
        /**/

/*++++++++++++++++++++++++++++++++++++++++++++++ PID*/

        tree->Draw("pidZ:pidAOQ>>hPID(100,2.3,3.3, 100, 4, 9)", gate0, "colz"); hPID->SetTitle(gate0Str);
        tree->Draw("pidAOQ*7>>hA(80,16, 24)", gate, "colz"); hA->SetTitle(gateStr);
        tree->Draw("pidAOQ*7>>hAg(80,16, 24)", gate + "60>Ex && Ex>-40", "colz"); hAg->SetTitle(gateStr + " X 60>Ex>-40");
        tree->Draw("pidAOQ*7>>hAgc(80,16, 24)", gatec + "60>Ex && Ex>-40", "colz"); hAgc->SetTitle(gatecStr + " X 60>Ex>-40");

        hAgc->Scale(BGscale); TH1F* hAgs = new TH1F(*hAg - *hAgc); hAgs->SetTitle("");

        //TF1* fit = new TF1("fit", "gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)+gaus(15)", 16, 24);
        //Double_t para[18]={40, 17, 0.5, 80, 18, 0.5, 100, 19, 0.4, 210, 20, 0.3, 170, 21, 0.3, 40, 22, 0.3};
        //with gateCry
        //Double_t para[18]={10, 17, 0.5, 20, 18, 0.5, 40, 19, 0.4, 90, 20, 0.3, 80, 21, 0.3, 20, 22, 0.3};

        TF1* fit = new TF1("fit", "gaus(0)+gaus(3)+gaus(6)+gaus(9)", 16, 24);
        //Double_t para[18]={40, 17, 0.5, 80, 18, 0.5, 100, 19, 0.4, 210, 20, 0.3, 170, 21, 0.3, 40, 22, 0.3};
        //with gateCry
        Double_t para[15]={20, 18, 0.5, 40, 19, 0.4, 90, 20, 0.3, 80, 21, 0.3, 20};

        fit->SetParameters(para);
        fit->SetLineColor(1);
        hAgs->Fit("fit");
        printf("reduced chi-squared = %f \n", fit->GetChisquare()/fit->GetNDF());        

        fit->GetParameters(para);
        TF1* g1 = new TF1("g1", "gaus(0)", 16, 24); g1->SetParameters(&para[0]); g1->SetLineColor(6); g1->Draw("same");
        TF1* g2 = new TF1("g2", "gaus(0)", 16, 24); g2->SetParameters(&para[3]); g2->SetLineColor(4); g2->Draw("same");
        TF1* g3 = new TF1("g3", "gaus(0)", 16, 24); g3->SetParameters(&para[6]); g3->SetLineColor(3); g3->Draw("same");
        TF1* g4 = new TF1("g4", "gaus(0)", 16, 24); g4->SetParameters(&para[9]); g4->SetLineColor(2); g4->Draw("same");
        //TF1* g5 = new TF1("g5", "gaus(0)", 16, 24); g5->SetParameters(&para[12]); g5->SetLineColor(2); g5->Draw("same");
        //TF1* g6 = new TF1("g6", "gaus(0)", 16, 24); g6->SetParameters(&para[15]); g6->SetLineColor(2); g6->Draw("same");


        //tree->Draw("nyokiM:pidAOQ*8>>hAgM(80,16, 24, 5, 0, 5)", gate + "60>Ex && Ex>-40", "colz");
        //tree->Draw("pidZ>>hZ(60,4,10)", gate0 + "60>Ex && Ex>-40", "colz");   hZ->SetTitle(gateStr + " X 60>Ex>-40");
        //tree->Draw("pidZ>>hZc(60,4,10)", gate0c + "60>Ex && Ex>-40", "colz"); hZc->SetTitle(gatecStr + " X 60>Ex>-40"); hZc->SetLineColor(2);
        //
        //hZc->Scale(BGscale); TH1F* hZs = new TH1F(*hZ - *hZc); hZs->SetTitle("");
        
        
        /*****************    Z */ /*
        hPID->ProjectionY("hZ");
        
        //TF1* fitZ = new TF1("fitZ", "gaus(0)+gaus(3)+gaus(6)+gaus(9)", 4, 10);
        //Double_t paraZ[15]={30, 5, 0.3, 100, 6, 0.2, 110, 7, 0.3, 270, 8, 0.3};

        TF1* fitZ = new TF1("fitZ", "gaus(0)+gaus(3)+gaus(6)", 4, 7.5);
        Double_t paraZ[15]={30, 5, 0.3, 100, 6, 0.2, 110, 7, 0.3};

        fitZ->SetParameters(paraZ);
        fitZ->SetLineColor(1);
        //fitZ->FixParameter(11,8);
        hZ->Fit("fitZ", "R");
        printf("reduced chi-squared = %f \n", fitZ->GetChisquare()/fitZ->GetNDF());        

        fitZ->GetParameters(paraZ);
        TF1* j1 = new TF1("j1", "gaus(0)", 4, 7.5); j1->SetParameters(&paraZ[0]);  j1->SetLineColor(4); j1->Draw("same");
        TF1* j2 = new TF1("j2", "gaus(0)", 4, 7.5); j2->SetParameters(&paraZ[3]);  j2->SetLineColor(3); j2->Draw("same");
        TF1* j3 = new TF1("j3", "gaus(0)", 4, 7.5); j3->SetParameters(&paraZ[6]);  j3->SetLineColor(2); j3->Draw("same");
        //TF1* j4 = new TF1("j4", "gaus(0)", 4, 10); j4->SetParameters(&paraZ[9]);  j4->SetLineColor(2); j4->Draw("same");

        
        //hZc->Draw("same");


/*++++++++++++++++++++++++++++++++++++++++++++++ Momentum*/

        //tree->Draw("(0.002*kE + kp)/sqrt(1-0.002*0.002)>>p22(  9, -300, 300)", gate  + cut22o +"TMath::Abs(Ex)<20") ; //o22->SetTitle(gateStr + " X 22O");
        //tree->Draw("(0.002*kE + kp)/sqrt(1-0.002*0.002)>>p21(  18, -300, 300)", gate  + cut21o +"TMath::Abs(Ex-8)<20") ; //o21->SetTitle(gateStr + " X 21O");
        //tree->Draw("(0.002*kE + kp)/sqrt(1-0.002*0.002)>>p20(  18, -300, 300)", gate  + cut20o +"TMath::Abs(Ex-15)<20") ; //o20->SetTitle(gateStr + " X 20O");
        //tree->Draw("(0.002*kE + kp)/sqrt(1-0.002*0.002)>>p22c( 9, -300, 300)", gatec + cut22o +"TMath::Abs(Ex)<20") ; //o22c->SetTitle(gateStr + " X 22O");
        //tree->Draw("(0.002*kE + kp)/sqrt(1-0.002*0.002)>>p21c( 18, -300, 300)", gatec + cut21o +"TMath::Abs(Ex-8)<20") ; //o21c->SetTitle(gateStr + " X 21O");
        //tree->Draw("(0.002*kE + kp)/sqrt(1-0.002*0.002)>>p20c( 18, -300, 300)", gatec + cut20o +"TMath::Abs(Ex-15)<20") ; //o20c->SetTitle(gateStr + " X 20O");
/*
        tree->Draw("kMomt>>p22(  40, 0, 400)", gate  + cut22o +"TMath::Abs(Ex)<20") ; //o22->SetTitle(gateStr + " X 22O");
        tree->Draw("kMomt>>p21(  40, 0, 400)", gate  + cut21o +"TMath::Abs(Ex-10)<10") ; //o21->SetTitle(gateStr + " X 21O");
        tree->Draw("kMomt>>p20(  40, 0, 400)", gate  + cut20o +"TMath::Abs(Ex-20)<20") ; //o20->SetTitle(gateStr + " X 20O");
        tree->Draw("kMomt>>p22c( 40, 0, 400)", gatec + cut22o +"TMath::Abs(Ex)<20") ; //o22c->SetTitle(gateStr + " X 22O");
        tree->Draw("kMomt>>p21c( 40, 0, 400)", gatec + cut21o +"TMath::Abs(Ex-10)<10") ; //o21c->SetTitle(gateStr + " X 21O");
        tree->Draw("kMomt>>p20c( 40, 0, 400)", gatec + cut20o +"TMath::Abs(Ex-20)<20") ; //o20c->SetTitle(gateStr + " X 20O");

        p22c->Scale(BGscale); TH1F* q22 = new TH1F(*p22 - *p22c); q22->SetLineColor(1); q22->SetName("q22"); q22->SetTitle("23F(p,2p)22Ogs");
        p21c->Scale(BGscale); TH1F* q21 = new TH1F(*p21 - *p21c); q21->SetLineColor(1); q21->SetName("q21"); q21->SetTitle("23F(p,2p)22O*->21O*+n, 6.86");
        p20c->Scale(BGscale); TH1F* q20 = new TH1F(*p20 - *p20c); q20->SetLineColor(1); q20->SetName("q20"); q20->SetTitle("23F(p,2p)22O*->20O*+2n, 10.65");

        q22->SetXTitle("k [MeV/c]"); q22->SetYTitle("count / 10 MeV"); q22->SetTitle("Ex = 0 MeV");
        q21->SetXTitle("k [MeV/c]"); q21->SetYTitle("count / 10 MeV"); q21->SetTitle("Ex = 10 MeV");
        q20->SetXTitle("k [MeV/c]"); q20->SetYTitle("count / 10 MeV"); q20->SetTitle("Ex = 20 MeV");
        
        Ex00->Draw("k>>hk0a(20, 0, 400)", "xsec1d5", "E"); hk0a->SetLineColor(2); 
        Ex00->Draw("k>>hk0b(20, 0, 400)", "xsec1p1", "E"); hk0b->SetLineColor(3); 
        Ex00->Draw("k>>hk0c(20, 0, 400)", "xsec1p3", "E"); hk0c->SetLineColor(4); 
        Ex00->Draw("k>>hk0d(20, 0, 400)", "xsec2s1", "E"); hk0d->SetLineColor(6);
        Ex10->Draw("k>>hk1a(20, 0, 400)", "xsec1d5", "E"); hk1a->SetLineColor(2); 
        Ex10->Draw("k>>hk1b(20, 0, 400)", "xsec1p1", "E"); hk1b->SetLineColor(3); 
        Ex10->Draw("k>>hk1c(20, 0, 400)", "xsec1p3", "E"); hk1c->SetLineColor(4); 
        Ex10->Draw("k>>hk1d(20, 0, 400)", "xsec2s1", "E"); hk1d->SetLineColor(6); 
        Ex20->Draw("k>>hk2a(20, 0, 400)", "xsec1d5", "E"); hk2a->SetLineColor(2); 
        Ex20->Draw("k>>hk2b(20, 0, 400)", "xsec1p1", "E"); hk2b->SetLineColor(3); 
        Ex20->Draw("k>>hk2c(20, 0, 400)", "xsec1p3", "E"); hk2c->SetLineColor(4); 
        Ex20->Draw("k>>hk2d(20, 0, 400)", "xsec2s1", "E"); hk2d->SetLineColor(6); 
        
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
        
        */
        /*/--------------------------------------------calculate mixing
        Double_t ca = 0, cb = 0, aa = 0, ab = 0, bb = 0;
        
        for ( Int_t i = 1 ; i <=40 ; i++){
                Double_t k = q21->GetBinCenter(i);
                Int_t bin = hk1a->FindBin(k);
                ca += hk1a->GetBinContent(bin)*q21->GetBinContent(i);
                cb += hk1b->GetBinContent(bin)*q21->GetBinContent(i);
                aa += hk1a->GetBinContent(bin)*hk1a->GetBinContent(i);
                ab += hk1a->GetBinContent(bin)*hk1b->GetBinContent(i);
                bb += hk1b->GetBinContent(bin)*hk1b->GetBinContent(i);
        }
        
        Double_t a1 = (ca*bb-cb*ab)/(aa*bb-ab*ab);
        Double_t a2 = (-ca*ab+cb*aa)/(aa*bb-ab*ab);
        printf(" the mixing is 1d3/2 %f, 1p1/2 %f\n", a1, a2 );
        Double_t chisq = 0;
        
        for ( Int_t i = 1 ; i <=20 ; i++){
                Double_t k = q21->GetBinCenter(i);
                Int_t bin = hk1a->FindBin(k);
                Double_t temp0 = q21->GetBinContent(i);
                Double_t temp1 = hk1a->GetBinContent(bin);
                Double_t temp2 = hk1b->GetBinContent(bin);
                Double_t gg = temp0- a1 * temp1+ a2 * temp2;
                
                printf("%2d , %5.1f, %5.1f, %5.1f, chi = %8.2f \n", i, temp0, temp1, temp2, gg);
                chisq += TMath::Power(gg,2);
                
        }
        printf(" the mixing is 1d3/2 %f, 1p1/2 %f, chisq = %f, reduced-chisq = %f\n", a1, a2, chisq, chisq/(10-2));
        
        TH1F* hk1af = new TH1F(*hk1a); hk1af->Scale(a1);
        TH1F* hk1bf = new TH1F(*hk1b); hk1bf->Scale(a2);
        
        THStack *hk1fS = new THStack("hk1S", "");
        hk1fS->Add(hk1af);
        hk1fS->Add(hk1bf);
        
        q21->Draw(""); hk1af->Draw("same");hk1bf->Draw("same"); hk1fS->Draw("same");
        
/***********/
}
