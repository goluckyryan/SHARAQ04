{
        gROOT->Reset();
        gROOT->ProcessLine(".!date");
        gStyle->SetOptStat(0);

//========================================================

        char * rootfile = "P_23F_ppcoin_0608.root";
        //char * rootfile = "P_23F_ppcoin_0602_oldD1.root";
        //char * rootfile = "P_23F_ppcoin_0528_Tplaoffset_2.root";
        
        TFile *f0 = new TFile (rootfile, "read"); 
        if( f0==0){
                printf("cannot load file: %s \n", rootfile);
                return;
        }
                
        //TTree *tree = (TTree*)f0->Get("tree");
        printf("=====> /// %15s //// is loaded. Total #Entry: %10d \n", rootfile,  tree->GetEntries());
/**///======================================================== Browser or Canvas
/*        Int_t Div[2] = {3,1};  //x,y
        Int_t size[2] = {500,500}; //x,y
        TCanvas * cPostAna = new TCanvas("cPostAna", "cPostAna", 2000, 0, 0 , size[0]*Div[0], size[1]*Div[1]);
        cPostAna->Divide(Div[0],Div[1]);
        

/**///======================================================== Cut 
        TCut gateCry = "s0x*s0x+TMath::Power(s0y-1.8,2)<49";
        TCut gateCryc = "s0x*s0x+TMath::Power(s0y-1.8,2)>49 && s0x*s0x+TMath::Power(s0y-1.8,2)<196";
        TCut gateTofS1 = "32<tofS1 && tofS1<35";
        TCut gateS0D = "TMath::Finite(s0dx)";
        TCut gateVertexZ = "TMath::Abs(vertexZ-10)<30";
        TCut gateVertexZc = "TMath::Abs(vertexZ-160)<30";
        //TCut gateOpenAng = "90>theta1+theta2 && theta1+theta2>60";
        //TCut gateOpenAng = "theta1>30 || theta2>30";
        TCut gateOpenAng = "";
        TCut gateZ = "8.6>pidZ && pidZ>7.4";
        TCut gateNID = "";//"nyokiID > 3 && nyokiID <11";
        
        TCut gate0 = gateCry + gateTofS1 + gateVertexZ  + gateOpenAng + gateNID + gateS0D;
        TCut gatec = gateCry + gateTofS1 + gateVertexZc + gateOpenAng + gateNID + gateS0D + gateZ; 
        TCut gate =  gateCry + gateTofS1 + gateVertexZ  + gateOpenAng + gateNID + gateS0D + gateZ;
        
        TString gate0Str = "r_Crystal<7 X 32<tofS1<35 X |vertexZ-10|<30 X Finite(S0D)";
        TString gatecStr  = "r_Crystal<7 X 32<tofS1<35 X |vertexZ-160|<30 X Finite(S0D) X 8.6>pidZ>7.4";
        TString gateStr = "r_Crystal<7 X 32<tofS1<35 X |vertexZ-10|<30 X Finite(S0D) X 8.6>pidZ>7.4";
        
        //TCut cut22o = "TMath::Abs(pidAOQ*8-22)<0.5";
        //TCut cut21o = "TMath::Abs(pidAOQ*8-21)<0.5";
        //TCut cut20o = "TMath::Abs(pidAOQ*8-20)<0.5";
        //TCut cut19o = "TMath::Abs(pidAOQ*8-19)<0.5";
        //TCut cut18o = "TMath::Abs(pidAOQ*8-18)<0.5";
        
        Double_t BGscale = 1.;
        
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

/*
        Int_t pidZvalue = 8;
        
        TCut vertexZcut = "abs(vertexZ-10)<30";
        TCut carboncut = "abs(vertexZ-160)<30";
        TCut s1xcut = "";//"s1x<0";
        //TCut s1xcut = "s1x>0 && s1x < 150";
        TString pidZcutstr; pidZcutstr.Form("TMath::Abs(pidZ-%d)<0.5", pidZvalue);
        TCut pidZcut = "";//pidZcutstr;
        TCut pidZcut2 = "pidZ<5";
        TCut tofS1cut = "abs(tofS1-36.0)<1";
        TCut s0cut = "";//"gateNum==1";
        //TCut Aux = "TMath::Abs(Ex -15)< 35 && TMath::Abs(theta1+theta2-80)<10";//"theta1 < 50 && theta2 < 50";//"pidAOQ*7>17.5";//"TMath::Abs(s1b)<0.3";//"TMath::Abs(theta1+theta2-82)<2";//"abs(Ex-10)<10";
        TCut Aux = "";//"Ex>-10 && TMath::Abs(theta1+theta2-80)<10";
        //TCut Aux = "";//Ex>50";
        Double_t bgScale = 1.0;
        
        Double_t binWidth = 1.5;
        Int_t binRange[2] = {-20,70};
        
        
        TCutG * cutg = new TCutG("cutg", 6);
        cutg->SetVarX("pidAOQ");
        cutg->SetVarY("pidZ");
        cutg->SetPoint(0, 2.40, 8.73);
        cutg->SetPoint(1, 2.40, 6.73);
        cutg->SetPoint(2, 2.50, 6.22);
        cutg->SetPoint(3, 2.53, 7.05);
        cutg->SetPoint(4, 2.53, 8.44);
        cutg->SetPoint(5, 2.47, 8.85);
        cutg->SetPoint(6, 2.40, 8.73);
        
        TCutG * cutg2 = new TCutG("cutg2", 7);
        cutg2->SetVarX("pidAOQ");
        cutg2->SetVarY("pidZ");
        cutg2->SetPoint(0, 2.54, 7.83);
        cutg2->SetPoint(1, 2.52, 6.90);
        cutg2->SetPoint(2, 2.51, 6.05);
        cutg2->SetPoint(3, 2.58, 5.61);
        cutg2->SetPoint(4, 2.69, 6.78);
        cutg2->SetPoint(5, 2.75, 7.80);
        cutg2->SetPoint(6, 2.61, 8.22);
        cutg2->SetPoint(7, 2.54, 7.83);
        
        //TCut signalcut = s1xcut + s0cut + pidZcut + vertexZcut + tofS1cut + Aux;
        TCut signalcut = s1xcut + s0cut + vertexZcut + tofS1cut + Aux + "cutg2";
        //TCut bgcut = s1xcut + s0cut + pidZcut2 + vertexZcut + tofS1cut + Aux;
        //TCut bgcut = s1xcut + s0cut + pidZcut + carboncut + tofS1cut + Aux;
        TCut bgcut = s1xcut + s0cut + carboncut + tofS1cut + Aux + "cutg2";

//*///======================================================== analysis

        tree->Draw("Ex>>oAll( 150, -200, 100)", gate )  ; oAll->SetTitle(gateStr);
        tree->Draw("Ex>>oAllc(150, -200, 100)", gatec ) ; oAllc->SetTitle(gatecStr); oAllc->SetLineColor(2);
        tree->Draw("Ex>>o22(  20, -20, 40)", gate  + "cut22o") ; //o22->SetTitle(gateStr + " X 22O");
        tree->Draw("Ex>>o21(  20, -20, 40)", gate  + "cut21o") ; //o21->SetTitle(gateStr + " X 21O");
        tree->Draw("Ex>>o20(  20, -20, 40)", gate  + "cut20o") ; //o20->SetTitle(gateStr + " X 20O");
        tree->Draw("Ex>>o19(  20, -20, 40)", gate  + "cut19o") ; //o19->SetTitle(gateStr + " X 19O");
        tree->Draw("Ex>>o18(  20, -20, 40)", gate  + "cut18o") ; //o18->SetTitle(gateStr + " X 18O");
        tree->Draw("Ex>>o22c( 20, -20, 40)", gatec + "cut22o") ; //o22c->SetTitle(gateStr + " X 22O");
        tree->Draw("Ex>>o21c( 20, -20, 40)", gatec + "cut21o") ; //o21c->SetTitle(gateStr + " X 21O");
        tree->Draw("Ex>>o20c( 20, -20, 40)", gatec + "cut20o") ; //o20c->SetTitle(gateStr + " X 20O");
        tree->Draw("Ex>>o19c( 20, -20, 40)", gatec + "cut19o") ; //o19c->SetTitle(gateStr + " X 19O");
        tree->Draw("Ex>>o18c( 20, -20, 40)", gatec + "cut18o") ; //o18c->SetTitle(gateStr + " X 18O");
        
        oAllc->Scale(BGscale); TH1F* mAll = new TH1F(*oAll - *oAllc); mAll->SetTitle("23F(p,2p)22O*");
        
        o22c->Scale(BGscale); TH1F* m22 = new TH1F(*o22 - *o22c); m22->SetLineColor(2); m22->SetTitle("23F(p,2p)22Ogs");
        o21c->Scale(BGscale); TH1F* m21 = new TH1F(*o21 - *o21c); m21->SetLineColor(3); m21->SetTitle("23F(p,2p)22O*->21O*+n, 6.86");
        o20c->Scale(BGscale); TH1F* m20 = new TH1F(*o20 - *o20c); m20->SetLineColor(4); m20->SetTitle("23F(p,2p)22O*->20O*+2n, 10.65");
        o19c->Scale(BGscale); TH1F* m19 = new TH1F(*o19 - *o19c); m19->SetLineColor(6); m19->SetTitle("23F(p,2p)22O*->19O*+3n, 18.28");
        o18c->Scale(BGscale); TH1F* m18 = new TH1F(*o18 - *o18c); m18->SetLineColor(9); m18->SetTitle("23F(p,2p)22O*->18O*+4n, 22.22");
        
        THStack *mS = new THStack("mS", "Stack of Ex for 22O - 18O");
        mS->Add(m22);
        mS->Add(m21);
        mS->Add(m20);
        mS->Add(m19);
        mS->Add(m18);
        
        
        tree->Draw("thetaR>>p22(  50, 0, 180)", gate  + "cut22o") ; //o22->SetTitle(gateStr + " X 22O");
        tree->Draw("thetaR>>p21(  50, 0, 180)", gate  + "cut21o") ; //o21->SetTitle(gateStr + " X 21O");
        tree->Draw("thetaR>>p20(  50, 0, 180)", gate  + "cut20o") ; //o20->SetTitle(gateStr + " X 20O");
        
        tree->Draw("thetaR>>p22c( 50, 0, 180)", gatec + "cut22o") ; //o22c->SetTitle(gateStr + " X 22O");
        tree->Draw("thetaR>>p21c( 50, 0, 180)", gatec + "cut21o") ; //o21c->SetTitle(gateStr + " X 21O");
        tree->Draw("thetaR>>p20c( 50, 0, 180)", gatec + "cut20o") ; //o20c->SetTitle(gateStr + " X 20O");
        
        p22c->Scale(BGscale); TH1F* q22 = new TH1F(*p22 - *p22c); q22->SetLineColor(2); q22->SetTitle("23F(p,2p)22Ogs");
        p21c->Scale(BGscale); TH1F* q21 = new TH1F(*p21 - *p21c); q21->SetLineColor(3); q21->SetTitle("23F(p,2p)22O*->21O*+n, 6.86");
        p20c->Scale(BGscale); TH1F* q20 = new TH1F(*p20 - *p20c); q20->SetLineColor(4); q20->SetTitle("23F(p,2p)22O*->20O*+2n, 10.65");
        
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
        
        
        tree->Draw("pidZ:pidAOQ>>hPID(100,2,3, 100, 4, 10)", gate0, "colz"); hPID->SetTitle(gate0Str);
        tree->Draw("pidAOQ*8>>hA(80,16, 24)", gate, "colz"); hA->SetTitle(gateStr);
        tree->Draw("pidAOQ*8>>hAg(80,16, 24)", gate + "60>Ex && Ex>-40", "colz"); hAg->SetTitle(gateStr + " X 60>Ex>-40");
        tree->Draw("pidAOQ*8>>hAgc(80,16, 24)", gatec + "60>Ex && Ex>-40", "colz"); hAgc->SetTitle(gatecStr + " X 60>Ex>-40");
        
        hAgc->Scale(BGscale); TH1F* hAgs = new TH1F(*hAg - *hAgc); hAgs->SetTitle("");
        
        //TF1* fit = new TF1("fit", "gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)+gaus(15)", 16, 24);
        //Double_t para[18]={40, 17, 0.5, 80, 18, 0.5, 100, 19, 0.4, 210, 20, 0.3, 170, 21, 0.3, 40, 22, 0.3};
        //with gateCry
        //Double_t para[18]={10, 17, 0.5, 20, 18, 0.5, 40, 19, 0.4, 90, 20, 0.3, 80, 21, 0.3, 20, 22, 0.3};

        TF1* fit = new TF1("fit", "gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)", 16, 24);
        //Double_t para[18]={40, 17, 0.5, 80, 18, 0.5, 100, 19, 0.4, 210, 20, 0.3, 170, 21, 0.3, 40, 22, 0.3};
        //with gateCry
        Double_t para[15]={20, 18, 0.5, 40, 19, 0.4, 90, 20, 0.3, 80, 21, 0.3, 20, 22, 0.3};

        fit->SetParameters(para);
        fit->SetLineColor(1);
        hAgs->Fit("fit");
        printf("reduced chi-squared = %f \n", fit->GetChisquare()/fit->GetNDF());        
        
        fit->GetParameters(para);
        TF1* g1 = new TF1("g1", "gaus(0)", 16, 24); g1->SetParameters(&para[0]); g1->SetLineColor(9); g1->Draw("same");
        TF1* g2 = new TF1("g2", "gaus(0)", 16, 24); g2->SetParameters(&para[3]); g2->SetLineColor(6); g2->Draw("same");
        TF1* g3 = new TF1("g3", "gaus(0)", 16, 24); g3->SetParameters(&para[6]); g3->SetLineColor(4); g3->Draw("same");
        TF1* g4 = new TF1("g4", "gaus(0)", 16, 24); g4->SetParameters(&para[9]); g4->SetLineColor(3); g4->Draw("same");
        TF1* g5 = new TF1("g5", "gaus(0)", 16, 24); g5->SetParameters(&para[12]); g5->SetLineColor(2); g5->Draw("same");
        //TF1* g6 = new TF1("g6", "gaus(0)", 16, 24); g6->SetParameters(&para[15]); g6->SetLineColor(2); g6->Draw("same");
        
        
        //tree->Draw("nyokiM:pidAOQ*8>>hAgM(80,16, 24, 5, 0, 5)", gate + "60>Ex && Ex>-40", "colz");
        




/*
        Bool_t Fiton = 1;
        
        TLatex text;
        text.SetNDC();
        
        cPostAna->cd(1);
        TString plot1; plot1.Form("Ex>>hEx(%3.0f,%d,%d)", (binRange[1]-binRange[0])/binWidth, binRange[0], binRange[1]);
        TString plot2; plot2.Form("Ex>>hExbg(%3.0f,%d,%d)", (binRange[1]-binRange[0])/binWidth, binRange[0], binRange[1]);
        
        //tree->Draw("s1x:vertexZ>>h7(100,-100,250,100,-200,300)", "", "colz");
        tree->Draw(plot1, signalcut, "colz");
        hEx->SetMinimum(0);
        TString hExTitle = "Ex | 23F + ppcoin ";
        if( pidZcut != "") {hExTitle += " + |pid.Z-"; hExTitle += pidZvalue; hExTitle += "|<0.5";}
        if( vertexZcut != "") hExTitle += " + |vertex.Z-10|<30 ";
        if( tofS1cut != "") hExTitle += " + |TOF(S0D-Hodo)-36|<1";
        if( s1xcut != "") {hExTitle += " + "; hExTitle += s1xcut;}
        hEx->SetTitle(hExTitle);
        hEx->SetXTitle("Ex [MeV]");
        TString hExYTitle; hExYTitle.Form("count / %1.1f MeV", binWidth);
        hEx->SetYTitle(hExYTitle);
        hEx->Draw();
        tree->Draw(plot2, bgcut, "same");
        hExbg->Scale(bgScale);
        hExbg->SetLineColor(2);
        hExbg->Draw("same");
        text->SetTextColor(2);
        text->DrawLatex(0.6,0.8,"carbon");
        
        cPostAna->cd(2);
        TH1F* hExsub = new TH1F(*hEx);
        hExsub->Sumw2();
        hExsub->Add(hExbg,-1);
        hExsub->Draw();
        
        if( Fiton){
                TF1 * fit = new TF1("fit", "gaus(0)+gaus(3)+gaus(6)+gaus(9)", -15, 60);
                Double_t par[12] = {50, 0, 5, 30, 10, 5, 20, 20, 5, 10, 30, 5};
                fit->SetParameters(par);
                //fit->FixParameter(1,0);                
                hExsub->Fit("fit","R");
        }
        
        cPostAna->cd(3);
        //TString plot3; plot3.Form("pidAOQ*%d:Ex>>h3(45,-20, 70, 50, %d, %d)", pidZvalue, pidZvalue*2, pidZvalue*3 );
        //tree->Draw(plot3, signalcut, "colz");
        //TString h3Title; h3Title.Form("A(Z=%d) vs Ex", pidZvalue);
        //h3->SetTitle(h3Title);
        //h3->SetXTitle("Ex [MeV]");
        //h3->SetYTitle("A");
        
        tree->Draw("pidAOQ:Ex>>h3(45,-20, 70, 50, 2, 3)", signalcut, "colz");
        h3->SetTitle("");
        h3->SetXTitle("Ex [MeV]");
        h3->SetYTitle("A/Q");
        
        //cPostAna->cd(4);
        //tree->Draw("pidZ:pidAOQ>>h1(50, 2, 3, 50, 1, 10)", "cutg", "colz");
        //h1->SetTitle(" 23F + ppcoin + crytsal");
        //h1->SetXTitle("A/Q");
        //h1->SetYTitle("Z");


/**************************************************************************/
/*
        cPostAna->cd(1);
        tree->Draw("pidZ:pidAOQ>>h1(50, 2, 3, 50, 1, 10)", signalcut, "colz");
        h1->SetTitle(" 23F + ppcoin + crytsal + Ex>0 + |OpenAng-80|<10");
        h1->SetXTitle("A/Q");
        h1->SetYTitle("Z");
        
        cPostAna->cd(2);
        tree->Draw("pidZ:pidAOQ>>h2(50, 2, 3, 50, 1, 10)", bgcut, "colz");
        h2->SetTitle(" 23F + ppcoin +  carbon + Ex>0 + |OpenAng-80|<10");
        Int_t max = h1->GetMaximum();
        h2->SetMaximum(max);
        h2->SetXTitle("A/Q");
        h2->SetYTitle("Z");
        
        cPostAna->cd(3);
        TH2F * h3 = new TH2F(*h1);
        h3->Add(h2,-1.2);
        h3->SetTitle("subtraction: h1- 1.2*h2");
        h3->Draw("colz");
        
        //cPostAna->cd(4);
        //tree->Draw("theta1+theta2>>h4(100,60,100)", signalcut+ "pidZ<5");
        //h4->SetTitle("Open Angle");
        

/**************************************************************************/
/*
        cPostAna->cd(1);
        tree->Draw("pidZ:pidAOQ>>h1(50, 2, 3, 50, 1, 10)", s0cut + vertexZcut + tofS1cut + Aux, "colz");
        h1->SetTitle(" 23F + ppcoin + crytsal + |vertex.Z-10|<30 + |TOF(S0D-Hodo)-36|<1");
        h1->SetXTitle("A/Q");
        h1->SetYTitle("Z");
        
        cPostAna->cd(2);
        tree->Draw("pidAOQ:Ex>>h2(60, -20, 70, 40, 2, 3)", s0cut + vertexZcut + tofS1cut + Aux, "colz");
        h2->SetTitle(" 23F + ppcoin + crytsal + |vertex.Z-10|<30 + |TOF(S0D-Hodo)-36|<1");
        h2->SetXTitle("Ex [MeV]");
        h2->SetYTitle("A/Q");
        
        cPostAna->cd(3);
        tree->Draw("pidAOQ*5:Ex>>h4(60, -20, 70, 40, 10, 15)", s0cut + vertexZcut + tofS1cut + Aux + "TMath::Abs(pidZ-5)<0.5", "colz");
        h4->SetTitle("|pid.Z-5|<0.5");
        h4->SetXTitle("Ex [MeV]");
        h4->SetYTitle("A");
        
        cPostAna->cd(4);
        tree->Draw("pidAOQ*6:Ex>>h5(60, -20, 70, 40, 12, 18)", s0cut + vertexZcut + tofS1cut + Aux + "TMath::Abs(pidZ-6)<0.5", "colz");
        h5->SetTitle("|pid.Z-6|<0.5");
        h5->SetXTitle("Ex [MeV]");
        h5->SetYTitle("A");
        
        cPostAna->cd(5);
        tree->Draw("pidAOQ*7:Ex>>h6(60, -20, 70, 40, 14, 21)", s0cut + vertexZcut + tofS1cut + Aux + "TMath::Abs(pidZ-7)<0.5", "colz");
        h6->SetTitle("|pid.Z-7|<0.5");
        h6->SetXTitle("Ex [MeV]");
        h6->SetYTitle("A");
        
        cPostAna->cd(6);
        tree->Draw("pidAOQ*8:Ex>>h7(60, -20, 70, 40, 16, 24)", s0cut + vertexZcut + tofS1cut + Aux + "TMath::Abs(pidZ-8)<0.5", "colz");
        h7->SetTitle("|pid.Z-8|<0.5");
        h7->SetXTitle("Ex [MeV]");
        h7->SetYTitle("A");
        
        cPostAna->cd(7);
        tree->Draw("pidAOQ*9:Ex>>h8(60, -20, 70, 40, 18, 27)", s0cut + vertexZcut + tofS1cut + Aux + "TMath::Abs(pidZ-9)<0.5", "colz");
        h8->SetTitle("|pid.Z-9|<0.5");
        h8->SetXTitle("Ex [MeV]");
        h8->SetYTitle("A");
/**************************************************************************/
/*       
        Bool_t Fiton = 0;
        
        TLatex text;
        text.SetNDC();
        
        cPostAna->cd(1);
        tree->Draw("s1x:Ex>>h1(45,-20, 70, 80, -150, 200)", signalcut, "colz");
        h1->SetTitle("s1x vs Ex");
        h1->SetXTitle("Ex [MeV]");
        h1->SetYTitle("s1x [mm]");
        text->DrawLatex(0.6, 0.8, s1xcut);
        
        cPostAna->cd(2);
        tree->Draw("tofS1:Ex>>h2(45,-20, 70, 100, 32, 40)", signalcut, "colz");
        h2->SetTitle("tofS1 vs Ex");
        h2->SetXTitle("Ex [MeV]");
        h2->SetYTitle("tofS1 [mm]");
        text->DrawLatex(0.3, 0.8, tofS1cut);
        
        cPostAna->cd(3);
        tree->Draw("pidAOQ:Ex>>h3(45,-20, 70, 50, 2, 3.0)", signalcut, "colz");
        h3->SetTitle("A/Q vs Ex");
        h3->SetXTitle("Ex [MeV]");
        h3->SetYTitle("A/Q");
        
        cPostAna->cd(4);
        tree->Draw("pidZ:Ex>>h4(45,-20, 70, 50,1, 11)", signalcut, "colz");
        h4->SetTitle("Z vs Ex");
        h4->SetXTitle("Ex [MeV]");
        h4->SetYTitle("Z ");
        text->DrawLatex(0.2, 0.8, pidZcut);
        
        cPostAna->cd(5);
        tree->Draw("pidZ:pidAOQ>>h5(50,2,3,50,1, 11)", signalcut, "colz");
        h5->SetTitle("Z vs A/Q");
        h5->SetXTitle("A/Q");
        h5->SetYTitle("Z ");
        
        cPostAna->cd(6);
        tree->Draw("vertexZ:Ex>>h6(45,-20, 70,100,-100, 250)", signalcut, "colz");
        h6->SetTitle("vertex.Z vs Ex");
        h6->SetXTitle("Ex [MeV]");
        h6->SetYTitle("vertex.Z [mm]");
        text->DrawLatex(0.3, 0.8, vertexZcut);
        
        cPostAna->cd(7);
        tree->Draw("s1x:pidAOQ>>h7(50,2,3,80,-150,200)", signalcut, "colz");
        h7->SetTitle("s1x vs A/Q");
        h7->SetXTitle("A/Q ");
        h7->SetYTitle("s1x [mm]");
        
        cPostAna->cd(8);
        TString plot1; plot1.Form("Ex>>hEx(%3.0f,%d,%d)", (binRange[1]-binRange[0])/binWidth, binRange[0], binRange[1]);
        TString plot2; plot2.Form("Ex>>hExbg(%3.0f,%d,%d)", (binRange[1]-binRange[0])/binWidth, binRange[0], binRange[1]);
        
        //tree->Draw("s1x:vertexZ>>h7(100,-100,250,100,-200,300)", "", "colz");
        tree->Draw(plot1, signalcut, "colz");
        hEx->SetMinimum(0);
        hEx->SetTitle("Ex | gated");
        hEx->SetXTitle("Ex [MeV]");
        TString hExYTitle; hExYTitle.Form("count / %1.1f MeV", binWidth);
        hEx->SetYTitle(hExYTitle);
        hEx->Draw();
        tree->Draw(plot2, bgcut, "same");
        hExbg->Scale(bgScale);
        hExbg->SetLineColor(2);
        hExbg->Draw("same");
        text->SetTextColor(2);
        text->DrawLatex(0.6,0.8,"carbon");
        
        cPostAna->cd(9);
        TH1F* hExsub = new TH1F(*hEx);
        hExsub->Sumw2();
        hExsub->Add(hExbg,-1);
        hExsub->Draw();
        
        if( Fiton){
                TF1 * fit = new TF1("fit", "gaus(0)+gaus(3)+gaus(6)+gaus(9)", -15, 40);
                Double_t par[12] = {25, 0, 5, 20, 5, 5, 20, 13, 5, 10, 30, 5};
                fit->SetParameters(par);
                fit->FixParameter(1,0);                
                hExsub->Fit("fit","R");
        }
        
        cPostAna->cd(10);
        tree->Draw("kMomt>>h10(50,0,400)", signalcut, "colz");
        h10->SetTitle("Momt [MeV/c]");
        h10->SetXTitle("Momt [MeV/c]");
        tree->Draw("kMomt>>h10a(50,0,400)", bgcut, "same");
        h10a->SetLineColor(2);
        h10a->SetXTitle("Momt [MeV/c]");
        h10a->Scale(bgScale);
        h10a->Draw("same");
        
        cPostAna->cd(11);
        TH1F* h10b = new TH1F(*h10);
        h10b->Sumw2();
        h10b->Add(h10a,-1);
        h10b->Draw();
        
        cPostAna->cd(12);
        tree->Draw("phi2-phi1>>h11(50,-50,50)", signalcut, "colz");
        h11->SetTitle("Off-Plane Angle");
        h11->SetXTitle("Off-Plane Angle [deg]");
        tree->Draw("phi2-phi1>>h11a(50,-50,50)", bgcut, "same");
        h11a->SetLineColor(2);
        h11a->Scale(bgScale);
        h11a->Draw("same");
        
        cPostAna->cd(13);
        TH1F* h11b = new TH1F(*h11);
        h11b->Sumw2();
        h11b->Add(h11a,-1);
        h11b->Draw();
        
        cPostAna->cd(14);
        tree->Draw("theta1+theta2>>h14(90, 60, 90)", signalcut, "colz");
        h14->SetTitle("Open Theta");
        h14->SetXTitle("theta1+theta2 [deg]");
        tree->Draw("theta1+theta2>>h14a(90, 60, 90)", bgcut, "same");
        h14a->SetLineColor(2);
        h14a->Scale(bgScale);
        h14a->Draw("same");
        
        cPostAna->cd(15);
        TH1F* h14b = new TH1F(*h14);
        h14b->Sumw2();
        h14b->Add(h14a,-1);
        h14b->Draw();
        
/********************************************************************/
}
