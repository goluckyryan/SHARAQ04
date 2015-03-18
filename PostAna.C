{
        gROOT->Reset();
        gROOT->ProcessLine(".!date");
        gStyle->SetOptStat(0);

//========================================================

        char * rootfile = "P_23F_ppcoin_0314.root";
        
        TFile *f0 = new TFile (rootfile, "read"); 
        if( f0==0){
                printf("cannot load file: %s \n", rootfile);
                return;
        }
                
        TTree *tree = (TTree*)f0->Get("tree");
        printf("=====> /// %15s //// is loaded. Total #Entry: %10d \n", rootfile,  tree->GetEntries());
/**/
//======================================================== Browser or Canvas
        Int_t Div[2] = {3,1};  //x,y
        Int_t size[2] = {500,500}; //x,y
        TCanvas * cPostAna = new TCanvas("cPostAna", "cPostAna", 2000, 0, 0 , size[0]*Div[0], size[1]*Div[1]);
        cPostAna->Divide(Div[0],Div[1]);
        

//======================================================== Cut 

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

//======================================================== analysis

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
