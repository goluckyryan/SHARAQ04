{
        gROOT->Reset();
        gROOT->ProcessLine(".!date");
        gStyle->SetOptStat(0);

//========================================================

        char * rootfile = "P_24O_ppcoin_r14_0720.root";
        
        TFile *f0 = new TFile (rootfile, "read"); TTree *tree = (TTree*)f0->Get("tree");
        printf("=====> /// %15s //// is loaded. Total #Entry: %10d \n", rootfile,  tree->GetEntries());
        
/**///======================================================== Browser or Canvas
        Int_t Div[2] = {1,1};  //x,y
        Int_t size[2] = {500,500}; //x,y
        TCanvas * cPostAna = new TCanvas("cPostAna", "cPostAna", 2000, 0 , size[0]*Div[0], size[1]*Div[1]);
        cPostAna->Divide(Div[0],Div[1]);
        cPostAna->cd(1);

/**///======================================================== Cut 
        TCut gateCry = "s0x*s0x+TMath::Power(s0y-1.8,2)<49";
        TCut gateCryc = "s0x*s0x+TMath::Power(s0y-1.8,2)>49 && s0x*s0x+TMath::Power(s0y-1.8,2)<196";
        TCut gateTofS1 = "35<tofS0DS1 && tofS0DS1<42";
        TCut gateS0D = "TMath::Finite(s0dx)";
        TCut gateVertexZ = "TMath::Abs(vertexZ-10)<30";
        TCut gateVertexZc = "TMath::Abs(vertexZ-165)<50";
        //TCut gateOpenAng = "90>theta1+theta2 && theta1+theta2>60";
        //TCut gateOpenAng = "theta1>30 || theta2>30";
        TCut gateOpenAng = "";
        TCut gateZ = "8>pidZ && pidZ>6.6";
        TCut gateNID = "";// "nyokiID>5";//"nyokiID > 3 && nyokiID <11";
        
        TCut gate0 = gateCry + gateTofS1 + gateVertexZ  + gateOpenAng + gateNID + gateS0D;
        TCut gatec = gateCry + gateTofS1 + gateVertexZc + gateOpenAng + gateNID + gateS0D + gateZ; 
        TCut gate =  gateCry + gateTofS1 + gateVertexZ  + gateOpenAng + gateNID + gateS0D + gateZ;
        
        TString gate0Str = "r_Crystal<7 X 32<tofS1<35 X |vertexZ-10|<30 X Finite(S0D)";
        TString gatecStr  = "r_Crystal<7 X 32<tofS1<35 X |vertexZ-160|<30 X Finite(S0D) X 8.6>pidZ>7.4";
        TString gateStr = "r_Crystal<7 X 32<tofS1<35 X |vertexZ-10|<30 X Finite(S0D) X 8.6>pidZ>7.4";
        
        TCut cut22o = "TMath::Abs(pidAOQ*8-22)<0.5";
        TCut cut23o = "TMath::Abs(pidAOQ*8-23)<0.5";
        TCut cut24o = "TMath::Abs(pidAOQ*8-24)<0.5";

        Double_t BGscale = 1.;
        
        //TCutG * gate22o = new TCutG("cut22o", 6);
        //gate22o->SetVarX("pidAOQ");
        //gate22o->SetVarY("pidZ");
        //gate22o->SetPoint(0, 2.68, 8.44);
        //gate22o->SetPoint(1, 2.68, 7.48);
        //gate22o->SetPoint(2, 2.73, 7.20);
        //gate22o->SetPoint(3, 2.80, 7.59);
        //gate22o->SetPoint(4, 2.80, 8.46);
        //gate22o->SetPoint(5, 2.73, 9.01);
        //gate22o->SetPoint(6, 2.68, 8.44);
        //
        //TCutG * gate23o = new TCutG("cut23o", 6);
        //gate23o->SetVarX("pidAOQ");
        //gate23o->SetVarY("pidZ");
        //gate23o->SetPoint(0, 2.80, 8.46);
        //gate23o->SetPoint(1, 2.80, 7.59);
        //gate23o->SetPoint(2, 2.87, 7.41);
        //gate23o->SetPoint(3, 2.94, 7.63);
        //gate23o->SetPoint(4, 2.94, 8.40);
        //gate23o->SetPoint(5, 2.87, 8.69);
        //gate23o->SetPoint(6, 2.80, 8.46);
        //
        //TCutG * gate24o = new TCutG("cut24o", 6);
        //gate24o->SetVarX("pidAOQ");
        //gate24o->SetVarY("pidZ");
        //gate24o->SetPoint(0, 2.94, 8.27);
        //gate24o->SetPoint(1, 2.94, 7.65);
        //gate24o->SetPoint(2, 3.00, 7.50);
        //gate24o->SetPoint(3, 3.07, 7.68);
        //gate24o->SetPoint(4, 3.07, 8.46);
        //gate24o->SetPoint(5, 3.00, 8.65);
        //gate24o->SetPoint(6, 2.94, 8.27);

//*///======================================================== analysis

        tree->Draw("Ex>>oAll( 150, -200, 100)", gate )  ; oAll->SetTitle(gateStr);
        tree->Draw("Ex>>oAllc(150, -200, 100)", gatec ) ; oAllc->SetTitle(gatecStr); oAllc->SetLineColor(2);
        tree->Draw("Ex>>o24(  25, -40, 60)", gate  + cut24o) ; //o24->SetTitle(gateStr + " X 24O");
        tree->Draw("Ex>>o23(  25, -40, 60)", gate  + cut23o) ; //o23->SetTitle(gateStr + " X 23O");
        tree->Draw("Ex>>o22(  25, -40, 60)", gate  + cut22o) ; //o22->SetTitle(gateStr + " X 22O");
        tree->Draw("Ex>>o24c( 25, -40, 60)", gatec + cut24o) ; //o24c->SetTitle(gateStr + " X 24O");
        tree->Draw("Ex>>o23c( 25, -40, 60)", gatec + cut23o) ; //o23c->SetTitle(gateStr + " X 23O");
        tree->Draw("Ex>>o22c( 25, -40, 60)", gatec + cut22o) ; //o22c->SetTitle(gateStr + " X 22O");
        
        oAllc->Scale(BGscale); TH1F* mAll = new TH1F(*oAll - *oAllc); mAll->SetName("mAll"); mAll->SetTitle("23F(p,2p)22O*");
        
        o24c->Scale(BGscale); TH1F* m24 = new TH1F(*o24 - *o24c); m24->SetName("m24"); m24->SetLineColor(2); m24->SetTitle("25F(p,2p)24Ogs");
        o23c->Scale(BGscale); TH1F* m23 = new TH1F(*o23 - *o23c); m23->SetName("m23"); m23->SetLineColor(3); m23->SetTitle("25F(p,2p)24O*->23O*+n, 4.18");
        o22c->Scale(BGscale); TH1F* m22 = new TH1F(*o22 - *o22c); m22->SetName("m22"); m22->SetLineColor(4); m22->SetTitle("25F(p,2p)24O*->22O*+2n, 6.93");

        m23->SetXTitle("Ex [MeV]"); m23->SetYTitle("count / 4 MeV");
        
        
        THStack *mS = new THStack("mS", "Stack of Ex for 22O - 18O");
        mS->Add(m24);
        mS->Add(m23);
        mS->Add(m22);

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
        
        tree->Draw("pidZ:pidAOQ>>hPID(100,2.2,3.2, 100, 4, 10)", gate0, "colz"); hPID->SetTitle(gate0Str);
        tree->Draw("pidAOQ*8>>hA(60,20, 26)", gate, "colz"); hA->SetTitle(gateStr);
        tree->Draw("pidAOQ*8>>hAg(60,20, 26)", gate   /*+ "60>Ex && Ex>-40"*/, "colz"); hAg->SetTitle(gateStr + " X 60>Ex>-40");
        tree->Draw("pidAOQ*8>>hAgc(60,20, 26)", gatec /*+ "60>Ex && Ex>-40"*/, "colz"); hAgc->SetTitle(gatecStr + " X 60>Ex>-40");
        
        hAgc->Scale(BGscale); TH1F* hAgs = new TH1F(*hAg - *hAgc); hAgs->SetTitle("");
        
        //TF1* fit = new TF1("fit", "gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)+gaus(15)", 16, 24);
        //Double_t para[18]={40, 17, 0.5, 80, 18, 0.5, 100, 19, 0.4, 210, 20, 0.3, 170, 21, 0.3, 40, 22, 0.3};
        //with gateCry
        //Double_t para[18]={10, 17, 0.5, 20, 18, 0.5, 40, 19, 0.4, 90, 20, 0.3, 80, 21, 0.3, 20, 22, 0.3};

        TF1* fit = new TF1("fit", "gaus(0)+gaus(3)+gaus(6)+gaus(9)", 20, 26);
        //Double_t para[18]={40, 17, 0.5, 80, 18, 0.5, 100, 19, 0.4, 210, 20, 0.3, 170, 21, 0.3, 40, 22, 0.3};
        //with gateCry
        Double_t para[15]={20, 24, 0.3, 45, 23, 0.4, 30, 22, 0.3, 20, 21, 0.3};

        fit->SetParameters(para);
        fit->SetLineColor(1);
        hAgs->Fit("fit");
        printf("reduced chi-squared = %f \n", fit->GetChisquare()/fit->GetNDF());        
        
        fit->GetParameters(para);
        TF1* g1 = new TF1("g1", "gaus(0)", 20, 26); g1->SetParameters(&para[0]); g1->SetLineColor(2); g1->Draw("same");
        TF1* g2 = new TF1("g2", "gaus(0)", 20, 26); g2->SetParameters(&para[3]); g2->SetLineColor(3); g2->Draw("same");
        TF1* g3 = new TF1("g3", "gaus(0)", 20, 26); g3->SetParameters(&para[6]); g3->SetLineColor(4); g3->Draw("same");
        TF1* g4 = new TF1("g4", "gaus(0)", 20, 26); g4->SetParameters(&para[9]); g4->SetLineColor(6); g4->Draw("same");
        TF1* g5 = new TF1("g5", "gaus(0)", 20, 26); g5->SetParameters(&para[12]); g5->SetLineColor(2); g5->Draw("same");
        
        
        //tree->Draw("nyokiM:pidAOQ*8>>hAgM(80,16, 24, 5, 0, 5)", gate + "60>Ex && Ex>-40", "colz");
        
        
/*++++++++++++++++++++++++++++++++++++++++++++++ Momentum*/
        
        tree->Draw("kMomt>>p24(  40, 0, 400)", gate  + cut24o +"TMath::Abs(Ex+5)<5") ;   
        tree->Draw("kMomt>>p23(  40, 0, 400)", gate  + cut23o +"TMath::Abs(Ex-10)<5") ;
        tree->Draw("kMomt>>p22(  20, 0, 400)", gate  + cut22o +"TMath::Abs(Ex-15)<15") ;
        tree->Draw("kMomt>>p24c( 40, 0, 400)", gatec + cut24o +"TMath::Abs(Ex+5)<5") ;   
        tree->Draw("kMomt>>p23c( 40, 0, 400)", gatec + cut23o +"TMath::Abs(Ex-10)<5") ;
        tree->Draw("kMomt>>p22c( 20, 0, 400)", gatec + cut22o +"TMath::Abs(Ex-15)<15") ;

        p24c->Scale(BGscale); TH1F* q24 = new TH1F(*p24 - *p24c); q24->SetLineColor(1); q24->SetName("q24"); q24->SetTitle("25F(p,2p)24Ogs");
        p23c->Scale(BGscale); TH1F* q23 = new TH1F(*p23 - *p23c); q23->SetLineColor(1); q23->SetName("q23"); q23->SetTitle("25F(p,2p)24O*->23O*+n, 4.18");
        p22c->Scale(BGscale); TH1F* q22 = new TH1F(*p22 - *p22c); q22->SetLineColor(1); q22->SetName("q22"); q22->SetTitle("25F(p,2p)24O*->22O*+2n, 6.93");

        q24->SetXTitle("k [MeV/c]"); q24->SetYTitle("count / 10 MeV"); q24->SetTitle("Ex = 0 MeV");
        q23->SetXTitle("k [MeV/c]"); q23->SetYTitle("count / 10 MeV"); q23->SetTitle("Ex = 10 MeV");
        q22->SetXTitle("k [MeV/c]"); q22->SetYTitle("count / 10 MeV"); q22->SetTitle("Ex = 15 MeV");

        Ex00->Draw("k>>hk0a(10, 0, 400)", "xsec1d5", "E"); hk0a->SetLineColor(2); 
        Ex00->Draw("k>>hk0b(10, 0, 400)", "xsec1p1", "E"); hk0b->SetLineColor(3); 
        Ex00->Draw("k>>hk0c(10, 0, 400)", "xsec1p3", "E"); hk0c->SetLineColor(4); 
        Ex10->Draw("k>>hk1a(10, 0, 400)", "xsec1d5", "E"); hk1a->SetLineColor(2); 
        Ex10->Draw("k>>hk1b(10, 0, 400)", "xsec1p1", "E"); hk1b->SetLineColor(3); 
        Ex10->Draw("k>>hk1c(10, 0, 400)", "xsec1p3", "E"); hk1c->SetLineColor(4); 
        Ex15->Draw("k>>hk2a(10, 0, 400)", "xsec1d5", "E"); hk2a->SetLineColor(2); 
        Ex15->Draw("k>>hk2b(10, 0, 400)", "xsec1p1", "E"); hk2b->SetLineColor(3); 
        Ex15->Draw("k>>hk2c(10, 0, 400)", "xsec1p3", "E"); hk2c->SetLineColor(4); 
        
        
        Double_t temp = hk0a->GetMaximum(); 
        hk0a->Scale(q24->GetMaximum()/temp);
        hk0b->Scale(q24->GetMaximum()/temp);
        hk0c->Scale(q24->GetMaximum()/temp);
        Double_t temp = hk1b->GetMaximum(); 
        hk1a->Scale(q23->GetMaximum()/temp);
        hk1b->Scale(q23->GetMaximum()/temp);
        hk1c->Scale(q23->GetMaximum()/temp);
        Double_t temp = hk2c->GetMaximum(); 
        hk2a->Scale(q22->GetMaximum()/temp);  
        hk2b->Scale(q22->GetMaximum()/temp);  
        hk2c->Scale(q22->GetMaximum()/temp);
        
        q24->Draw();hk0a->Draw("same");hk0b->Draw("same");hk0c->Draw("same");
        
        

}
