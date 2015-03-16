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
        gROOT->ProcessLine("listg tree");
        printf("=====> /// %15s //// is loaded. Total #Entry: %10d \n", rootfile,  tree->GetEntries());
/**/
//======================================================== Browser or Canvas
        TBrowser B("Bscript",rootfile, 900,600); 	
        
        
        //tree->Process("Selector_Nyoki.C");
        //tree->Process("Selector_PostAna.C");
        //tree->Process("Selector_MWDC_S0D_charge.C");
        //tree->Process("Selector_Aux.C");
        //tree->Process("Selector_DTDL.C");

/*        
        Int_t Div[2] = {5,3};  //x,y
        Int_t size[2] = {300,300}; //x,y
        TCanvas * cScript = new TCanvas("cScript", "cScript", 0,0 , size[0]*Div[0], size[1]*Div[1]);
        cScript->Divide(Div[0],Div[1]);
   
//======================================================== load histogram
//	TFile *f1 = new TFile ("hist_23F_0112_new_smwdc_S1_config.root", "read");

//================ update.
//	TFile *f0 = new TFile ("23F_1224_nyoki_optics.root","update"); 
//	f0->Close();
/**/
//======================================================== analysis
/************** PID.Downstream    *********************/
/*
        TH2F* h1 = new TH2F("h1", "h1: Beam Profile | Beam trigger", 100, -10, 10, 100, -10, 10);
        h1->SetXTitle("s0.x [mm]");
        h1->SetYTitle("s0.y [mm]");


/************** Crystal Position 2*********************/
/*
        char * rootfile = "23F_ppcoin_0314.root";
        
        TFile *f1 = new TFile (rootfile, "read"); 
        TTree *tree2 = (TTree*)f1->Get("tree");


        TH2F* h1 = new TH2F("h1", "h1: Beam Profile | Beam trigger", 100, -10, 10, 100, -10, 10);
        h1->SetXTitle("s0.x [mm]");
        h1->SetYTitle("s0.y [mm]");
        TH2F* h2 = new TH2F("h2", "h2: Beam Profile | 23F + ppcoin", 100, -10, 10, 100, -10, 10);
        h2->SetXTitle("s0.x [mm]");
        h2->SetYTitle("s0.y [mm]");
        

        cScript->cd(1);
        tree->Draw("S0img.fTrack.fY:S0img.fTrack.fX>>h1", "", "colz");

        cScript->cd(2);
        tree2->Draw("S0img.fTrack.fY:S0img.fTrack.fX>>h2", "", "colz", 1000000);

        cScript->cd(3);
        TH2F* h3 = new TH2F("h3", "h2 / h1", 100, -10, 10, 100, -10, 10);
        h3->SetXTitle("s0.x [mm]");
        h3->SetYTitle("s0.y [mm]");
        h3->Add(h2);
        h3->Divide(h1);
        h3->Draw("colz");



/************** Sp ***********************************/
/*
        cScript->cd(1);
        tree->Draw("p2p.fSp>>h1")


/************** Crystal Position *********************/
/*
        TH2F* h1 = new TH2F("h1", "h1: Beam Profile | 23F + ppcoin", 100, -10, 10, 100, -10, 10);
        h1->SetXTitle("s0.x [mm]");
        h1->SetYTitle("s0.y [mm]");
        TH2F* h2 = new TH2F("h2", "h2: Beam Profile | 23F + ppcoin + pid.DS.Z>5", 100, -10, 10, 100, -10, 10);
        h2->SetXTitle("s0.x [mm]");
        h2->SetYTitle("s0.y [mm]");
        

        cScript->cd(1);
        tree->Draw("S0img.fTrack.fY:S0img.fTrack.fX>>h1", "", "colz");

        cScript->cd(2);
        tree->Draw("S0img.fTrack.fY:S0img.fTrack.fX>>h2", "pid_ds.fZ>5", "colz");

        cScript->cd(3);
        TH2F* h3 = new TH2F("h3", "h2 / h1", 100, -10, 10, 100, -10, 10);
        h3->SetXTitle("s0.x [mm]");
        h3->SetYTitle("s0.y [mm]");
        h3->Add(h2);
        h3->Divide(h1);
        h3->Draw("colz");


/************** vertex.Z   *********************/
/*
        Int_t nEvent = tree->GetEntries();

        TH1F* h1 = new TH1F("h1", "h1", 150, -100, 200);
        h1->SetTitle("pid.Z > 5 + |TOF(S0D-Hodo)|<2");
        h1->SetXTitle("vertex.Z [mm]");
        h1->SetYTitle("count / 1.5 mm");

        TH1F* h2 = new TH1F("h2", "h2", 150, -100, 200);
        h2->SetTitle("pid.Z < 5 + |TOF(S0D-Hodo)|<2");
        h2->SetXTitle("vertex.Z [mm]");
        h2->SetYTitle("count / 1.5 mm");


        cScript->cd(1);
        tree->Draw("vertex.fZ>>h1", "pid_ds.fZ>5 && TMath::Abs(smwdc_S1.fTrack.fX-50)<180 && TMath::Abs(tof_D1.fTiming-36)<2", "", nEvent);

        cScript->cd(2);
        tree->Draw("vertex.fZ>>h2", "pid_ds.fZ<5 && TMath::Abs(smwdc_S1.fTrack.fX-50)<180 && TMath::Abs(tof_D1.fTiming-36)<2", "", nEvent);

        cScript->cd(3);
        TH1F* h3 = new TH1F(*h1-*h2);
        h3->Draw();

/************************************************/
//tree->Draw("smwdc_S1_x1.fTiming>>h1(300, -100, 200)", "smwdc_S1_x1.fCharge>350 && smwdc_S1_x1.fID!= 29", "");
//tree->Draw("smwdc_S1_x1.fTiming>>h2(300, -100, 200)", "smwdc_S1_x1.fCharge>350 && smwdc_S1_x1.fID!= 29 && @smwdc_S1_x1.fSize==1", "same");

//        tree->Draw("smwdc_S1.fTrack.fA:smwdc_S1.GetResidual(0):smwdc_S1.GetResidual(1):smwdc_S1.GetResidual(2):smwdc_S1.GetResidual(3):smwdc_S1.GetResidual(4):smwdc_S1.GetResidual(5):smwdc_S1.GetWireIDAdopted(0):smwdc_S1.GetWireIDAdopted(1):smwdc_S1.GetWireIDAdopted(2):smwdc_S1.GetWireIDAdopted(3):smwdc_S1.GetWireIDAdopted(4):smwdc_S1.GetWireIDAdopted(5)", "smwdc_S1.IsGood() && smwdc_S1.fNPlaneValid==6", "para", 100000);

//tree->Draw("smwdc_S1.fTrack.fA:smwdc_S1.GetDriftLengthAdopted(0):smwdc_S1.GetDriftLengthAdopted(1):smwdc_S1.GetDriftLengthAdopted(2):smwdc_S1.GetDriftLengthAdopted(3):smwdc_S1.GetDriftLengthAdopted(4):smwdc_S1.GetDriftLengthAdopted(5):smwdc_S1.GetWireIDAdopted(0)-smwdc_S1.GetWireIDAdopted(1):smwdc_S1.GetWireIDAdopted(2)-smwdc_S1.GetWireIDAdopted(3):smwdc_S1.GetWireIDAdopted(4)-smwdc_S1.GetWireIDAdopted(5)", "smwdc_S1.IsGood() && smwdc_S1.fNPlaneValid==6", "para", 100000);

//        tree->Draw("smwdc_S1.fTrack.fX:smwdc_S1.fTrack.fA:smwdc_S1.GetDriftLengthAdopted(0):smwdc_S1.GetDriftLengthAdopted(1):smwdc_S1.GetWireIDAdopted(0)-smwdc_S1.GetWireIDAdopted(1)", "smwdc_S1.IsGood() && smwdc_S1.fNPlaneValid==6", "para", 100000);


//        tree->Draw("smwdc_S1.fTrack.fX:smwdc_S1.fTrack.fA:smwdc_S1.fTrack.fB:(smwdc_S1.fTrack.X(-40)-(smwdc_S1.GetWireIDAdopted(0)-28.375)*20)/TMath::Abs(smwdc_S1.fTrack.X(-40)-(smwdc_S1.GetWireIDAdopted(0)-28.375)*20)*smwdc_S1.GetDriftLengthAdopted(0):smwdc_S1.GetWireIDAdopted(0)-smwdc_S1.GetWireIDAdopted(1):(smwdc_S1.fTrack.X(-24)-(smwdc_S1.GetWireIDAdopted(1)-28.625)*20)/TMath::Abs(smwdc_S1.fTrack.X(-24)-(smwdc_S1.GetWireIDAdopted(1)-28.625)*20)*smwdc_S1.GetDriftLengthAdopted(1)",  "smwdc_S1.IsGood() && smwdc_S1.fNPlaneValid==6", "para", 100000);

//        tree->Draw("smwdc_S1.fTrack.fX:smwdc_S1.fTrack.fA:smwdc_S1.fTrack.fB:smwdc_S1.GetWireIDAdopted(2):smwdc_S1.GetWireIDAdopted(3):smwdc_S1.fTrack.fX*0.8-0.6*smwdc_S1.fTrack.fY:(smwdc_S1.fTrack.X(-8)*0.8-0.6*smwdc_S1.fTrack.Y(-8)-(smwdc_S1.GetWireIDAdopted(2)-22.375)*20)/TMath::Abs(smwdc_S1.fTrack.X(-8)*0.8-0.6*smwdc_S1.fTrack.Y(-8)-(smwdc_S1.GetWireIDAdopted(2)-22.375)*20)*smwdc_S1.GetDriftLengthAdopted(2):smwdc_S1.GetWireIDAdopted(2)-smwdc_S1.GetWireIDAdopted(3):(smwdc_S1.fTrack.X(8)*0.8-0.6*smwdc_S1.fTrack.Y(8)-(smwdc_S1.GetWireIDAdopted(3)-22.625)*20)/TMath::Abs(smwdc_S1.fTrack.X(8)*0.8-0.6*smwdc_S1.fTrack.Y(8)-(smwdc_S1.GetWireIDAdopted(3)-22.625)*20)*smwdc_S1.GetDriftLengthAdopted(3)",  "smwdc_S1.IsGood() && smwdc_S1.fNPlaneValid==6", "para", 100000);

//        tree->Draw("smwdc_S1.fTrack.fX:smwdc_S1.fTrack.fA:smwdc_S1.fTrack.fB:smwdc_S1.GetWireIDAdopted(2):smwdc_S1.fTrack.fX*0.8-0.6*smwdc_S1.fTrack.fY:smwdc_S1.GetLRAdopted(2)*smwdc_S1.GetDriftLengthAdopted(2):smwdc_S1.GetWireIDAdopted(2)-smwdc_S1.GetWireIDAdopted(3):smwdc_S1.GetLRAdopted(3)*smwdc_S1.GetDriftLengthAdopted(3):smwdc_S1.fTrack.X(-30):smwdc_S1.GetWireIDAdopted(0):smwdc_S1.GetLRAdopted(0)*smwdc_S1.GetDriftLengthAdopted(0):smwdc_S1.GetWireIDAdopted(0)-smwdc_S1.GetWireIDAdopted(1):smwdc_S1.GetLRAdopted(1)*smwdc_S1.GetDriftLengthAdopted(1):smwdc_S1.fTrack.X(-40):smwdc_S1.fTrack.X(-24)",  "smwdc_S1.IsGood() && smwdc_S1.fNPlaneValid==6", "para", 100000);

//tree->Draw("smwdc_S1.fTrack.fX:smwdc_S1.fTrack.fA:@smwdc_S1_x1.fSize:@smwdc_S1_x2.fSize:@smwdc_S1_u1.fSize:@smwdc_S1_v2.fSize:@smwdc_S1_v1.fSize:@smwdc_S1_v2.fSize",  "smwdc_S1.IsGood() && smwdc_S1.fNPlaneValid==6", "para", 100000);

/********** single Hit MWDC-S1 tracking result **********************************/
/*
        TCanvas * haha = new TCanvas("haha", "haha", 100, 100, 800, 800);
        haha->Divide(2,2);
        
        TH2F* h1 = new TH2F("h1", "All plane Multiplicty == 1", 300, -200, 600, 300, -150, 150);
        h1->SetXTitle("X");
        h1->SetYTitle("Y");
        TH2F* h2 = new TH2F("h2", "All plane Multiplicty == 1", 300, -200, 600, 300,   -1,   1);
        h2->SetXTitle("X");
        h2->SetYTitle("A");
        TH2F* h3 = new TH2F("h3", "All plane Multiplicty == 1", 300, -150, 150, 300,   -1,   1);
        h3->SetXTitle("Y");
        h3->SetYTitle("B");
        TH2F* h4 = new TH2F("h4", "All plane Multiplicty == 1", 300,   -1,   1, 300,   -1,   1);
        h4->SetXTitle("A");
        h4->SetYTitle("B");
        
        haha->cd(1);
        tree->Draw("smwdc_S1.fTrack.fY:smwdc_S1.fTrack.fX>>h1", "@smwdc_S1_x1.fSize == 1 && @smwdc_S1_x2.fSize ==1 && @smwdc_S1_u1.fSize == 1 && @smwdc_S1_v2.fSize == 1 && @smwdc_S1_v1.fSize==1 && @smwdc_S1_v2.fSize==1 && smwdc_S1.IsGood() && smwdc_S1.fNPlaneValid==6", "colz");
        
        haha->cd(2);
        tree->Draw("smwdc_S1.fTrack.fA:smwdc_S1.fTrack.fX>>h2", "@smwdc_S1_x1.fSize == 1 && @smwdc_S1_x2.fSize ==1 && @smwdc_S1_u1.fSize == 1 && @smwdc_S1_v2.fSize == 1 && @smwdc_S1_v1.fSize==1 && @smwdc_S1_v2.fSize==1 && smwdc_S1.IsGood() && smwdc_S1.fNPlaneValid==6", "colz");
        
        haha->cd(3);
        tree->Draw("smwdc_S1.fTrack.fB:smwdc_S1.fTrack.fY>>h3", "@smwdc_S1_x1.fSize == 1 && @smwdc_S1_x2.fSize ==1 && @smwdc_S1_u1.fSize == 1 && @smwdc_S1_v2.fSize == 1 && @smwdc_S1_v1.fSize==1 && @smwdc_S1_v2.fSize==1 && smwdc_S1.IsGood() && smwdc_S1.fNPlaneValid==6", "colz");
        
        haha->cd(4);
        tree->Draw("smwdc_S1.fTrack.fB:smwdc_S1.fTrack.fA>>h4", "@smwdc_S1_x1.fSize == 1 && @smwdc_S1_x2.fSize ==1 && @smwdc_S1_u1.fSize == 1 && @smwdc_S1_v2.fSize == 1 && @smwdc_S1_v1.fSize==1 && @smwdc_S1_v2.fSize==1 && smwdc_S1.IsGood() && smwdc_S1.fNPlaneValid==6", "colz");
        
/**************************************************/

//        tree->Draw("smwdc_S1.fTrack.fA:smwdc_S1.GetWireIDAdopted(0)-smwdc_S1.GetWireIDAdopted(1):smwdc_S1.GetWireIDAdopted(2)-smwdc_S1.GetWireIDAdopted(3):smwdc_S1.GetWireIDAdopted(4)-smwdc_S1.GetWireIDAdopted(5)", "smwdc_S1.IsGood() && smwdc_S1.fNPlaneValid==6", "para", 100000);

//        tree->Draw("smwdc_S1.fTrack.fA:smwdc_S1.GetWireIDAdopted(0)-smwdc_S1.GetWireIDAdopted(1)>>h1(10,-5,6, 200, -3, 3)", "smwdc_S1.IsGood() && smwdc_S1.fNPlaneValid==6", "colz", 100000);


/*
        TCanvas haha("haha", "haha", 800,800);
        haha.Divide(2,2);
        Int_t nEvent = 1000000;
        
        TString gate = "";//"gate.Test(0)";
        
        //haha.cd(1); 
        //tree->Draw( "smwdc_S1.GetSigma(1)*1000>>h1(200,0,10)", gate, ""    , nEvent); h1->SetLineColor(2);
        //tree2->Draw("smwdc_S1.GetSigma(1)*1000>>h2(200,0,10)", gate, "same", nEvent);
        
//        tree->Draw("smwdc_S1_x1.fCharge>>h1(200,0,1500)", gate, "", 10000);
//        tree2->Draw("smwdc_S1_x1.fCharge>>h2(200,0,1500)", gate, "same", 10000);
        
        
        haha.cd(1); tree->Draw("smwdc_S1.fTrack.fY:smwdc_S1.fTrack.fX>>h1(400,-500, 500, 200,  -150,  150)", gate, "colz");
        haha.cd(2); tree->Draw("smwdc_S1.fTrack.fA:smwdc_S1.fTrack.fX>>h2(400,-500, 500, 200,    -0.5,    0.5)", gate, "colz");
        haha.cd(3); tree->Draw("smwdc_S1.fTrack.fB:smwdc_S1.fTrack.fY>>h3(200,-150, 150, 200,    -0.25,   0.25)", gate, "colz");
        haha.cd(4); tree->Draw("smwdc_S1.fTrack.fB:smwdc_S1.fTrack.fA>>h4(200,  -0.5,   0.5, 200,    -0.25,    0.25)", gate, "colz");
*/

/*****************************************************************/
/*
        cScript->cd(1);

        TLatex text;
        text.SetNDC();
        text.SetTextColor(1);
        text.SetTextColor(0.04); 

        Double_t m23F = 21423.1; 
        Double_t m22O = 20498.1;
        Double_t FL = 6903;

        Double_t offset = 0;
        Double_t mass = m23F;
        Double_t A = 23;
        TString title = "23F";
        TString cut = "gate.Test(0) && gate.Test(12) && TMath::Abs(S0img.fTrack.fA)<0.005 && TMath::Abs(S0img.fTrack.fB)<0.005 && nyoki.fID==7";
        //TString cut = "gate.Test(0) && gate.Test(12) && nyoki.fID==7";


        TString plotUp;
        plotUp.Form("%f/%f*(1/TMath::Sqrt(1-TMath::Power(74075/299.792458/(tof_US.fTiming+1463+382.18),2))-1)>>h2(200,220,310)", mass, A);


        TString plotDnTime;
        plotDnTime.Form("tof_D1.fTiming+%f>>h3(200,30, 40)", offset);

        TString plotDn;
        plotDn.Form("%f/%f*(1/TMath::Sqrt(1-TMath::Power(%f/299.792458/(tof_D1.fTiming+%f),2))-1)>>h4(200,220,310)", mass, A, FL, offset);

        TString plotS0D;
        plotS0D.Form("%f/%f*(1/TMath::Sqrt(1-TMath::Power(1457/299.792458/(tofS0D.fTiming+124.67+7.54),2))-1)>>h8(200,220,310)", mass, A);

        TString energyLoss;
        energyLoss.Form("%f/%f*((1/TMath::Sqrt(1-TMath::Power(74075/299.792458/(tof_US.fTiming+1463+382.18),2))-1)-(1/TMath::Sqrt(1-TMath::Power(%f/299.792458/(tof_D1.fTiming+%f),2))-1))>>h6(200,-50,50)", mass, A, FL, offset);

        TString Ecoin;
        Ecoin.Form("%f/%f*((1/TMath::Sqrt(1-TMath::Power(74075/299.792458/(tof_US.fTiming+1463+382.18),2))-1)):%f/%f*((1/TMath::Sqrt(1-TMath::Power(6296/299.792458/(tof_D1.fTiming+%f),2))-1))>>h9(200, 260, 300, 200, 286, 292)", mass, A, mass, A, offset);


        cScript->cd(1);
        tree->Draw("(tof_US.fTiming+1463+382.18)>>h1(200,370, 410)", cut, "colz");
        h1->SetTitle("tof(F3-FH9) | L = 74075 mm | tgt + "+ title);
        h1->SetXTitle("tof(F3-FH9) [ns]");

        cScript->cd(2);
        tree->Draw(plotUp, cut, "colz");
        h2->SetTitle("Kinetic Energy per nucleon | tgt + "+ title);
        h2->SetXTitle("TKE [A MeV]");

        cScript->cd(4);
        tree->Draw(plotDnTime, cut + "&& nyoki.fID==7", "colz");
        TString hTitle;
        hTitle.Form("tof(S0DPL-Hodo-7) | L = %4.0f mm | tgt + %s", FL, title.Data());
        h3->SetTitle(hTitle);
        h3->SetLineColor(2);
        h3->SetXTitle("tof(S0DPL-Hodo) [ns]");

        cScript->cd(5);
        tree->Draw(plotDn, cut + "&& nyoki.fID==7", "colz");
        h4->SetTitle("Kinetic Energy per nucleon | tgt + "+ title);
        h4->SetXTitle("TKE [A MeV]");
        h4->SetLineColor(2);

        cScript->cd(3);
        tree->Draw(energyLoss, cut, "colz");
        h6->SetTitle("Energy Loss");
        h6->SetXTitle("Energy Loss [A MeV]");

/*        cScript->cd(7);
        tree->Draw("(tofS0D.fTiming+124.67+7.54)>>h7(200,5, 10)", cut, "colz");
        h7->SetTitle("tof(tgt-S0DPL) | L = 1457 mm | tgt + "+ title);
        h7->SetXTitle("tof(F3-FH9) [ns]");

        cScript->cd(8);
        tree->Draw(plotS0D, cut, "colz");
        h8->SetTitle("Kinetic Energy per nucleon | tgt + "+ title);
        h8->SetXTitle("TKE [A MeV]");
        h8->SetLineColor(7);

        cScript->cd(6);
        h2->Draw();
        h4->Draw("same");
//        h8->Draw("same");
        
/*        cScript->cd(9);
        tree->Draw(Ecoin, "", "colz");
*/
/***************************************************************************/
/*
 //with Post-tree

        TCut vertexZcut = "abs(vertexZ-10)<60";
        TCut carboncut = "abs(vertexZ-10)<60";
        TCut s1xcut = "";//"s1x>0";
        //TCut s1xcut = "s1x>0 && s1x < 200";
        TCut pidZcut = "pidZ>1 && pidZ<4";
        TCut tofS1cut = "abs(tofS1-36.0)<2";
        TCut s0cut = "";//"gateNum==1";
        TCut Aux = "";//"TMath::Abs(theta1+theta2-82)<2";//"abs(Ex-10)<10";
        Double_t bgScale = 0.1;
        
        Double_t binWidth = 1;
        Int_t binRange[2] = {-40,80};
        
        Bool_t Fiton = 0;
        
        TLatex text;
        text.SetNDC();
        
        cScript->cd(1);
        tree->Draw("s1x:Ex>>h1(70,-40,100, 100, -200, 300)", s1xcut + s0cut + pidZcut + vertexZcut + tofS1cut + Aux, "colz");
        h1->SetTitle("s1x vs Ex");
        h1->SetXTitle("Ex [MeV]");
        h1->SetYTitle("s1x [mm]");
        text->DrawLatex(0.6, 0.8, s1xcut);
        
        cScript->cd(2);
        tree->Draw("tofS1:Ex>>h2(70,-40,100, 100, 32, 40)", s1xcut + s0cut + pidZcut + vertexZcut + tofS1cut + Aux, "colz");
        h2->SetTitle("tofS1 vs Ex");
        h2->SetXTitle("Ex [MeV]");
        h2->SetYTitle("tofS1 [mm]");
        text->DrawLatex(0.3, 0.8, tofS1cut);
        
        cScript->cd(3);
        tree->Draw("pidAOQ:Ex>>h3(70,-40,100, 100, 1.8, 3.2)", s1xcut + s0cut + pidZcut + vertexZcut + tofS1cut + Aux, "colz");
        h3->SetTitle("A/Q vs Ex");
        h3->SetXTitle("Ex [MeV]");
        h3->SetYTitle("A/Q");
        
        cScript->cd(4);
        tree->Draw("pidZ:Ex>>h4(70,-40,100,100,1, 11)", s1xcut + s0cut + pidZcut + vertexZcut + tofS1cut + Aux, "colz");
        h4->SetTitle("Z vs Ex");
        h4->SetXTitle("Ex [MeV]");
        h4->SetYTitle("Z ");
        text->DrawLatex(0.6, 0.95, pidZcut);
        
        cScript->cd(5);
        tree->Draw("pidZ:pidAOQ>>h5(100,1.8,3.2,100,1, 11)", s1xcut + s0cut + pidZcut + vertexZcut + tofS1cut + Aux, "colz");
        h5->SetTitle("Z vs A/Q");
        h5->SetXTitle("A/Q");
        h5->SetYTitle("Z ");
        
        cScript->cd(6);
        tree->Draw("vertexZ:Ex>>h6(70,-40,100,100,-100, 250)", s1xcut + s0cut + pidZcut + vertexZcut + tofS1cut + Aux, "colz");
        h6->SetTitle("vertex.Z vs Ex");
        h6->SetXTitle("Ex [MeV]");
        h6->SetYTitle("vertex.Z [mm]");
        text->DrawLatex(0.3, 0.8, vertexZcut);
        
        cScript->cd(7);
        tree->Draw("s1x:pidAOQ>>h7(100,1.8,3.2,100,-200,300)", s1xcut + s0cut + pidZcut + vertexZcut + tofS1cut + Aux, "colz");
        h7->SetTitle("s1x vs A/Q");
        h7->SetXTitle("A/Q ");
        h7->SetYTitle("s1x [mm]");
        
        cScript->cd(8);
        TString plot1; plot1.Form("Ex>>hEx(%3.0f,%d,%d)", (binRange[1]-binRange[0])/binWidth, binRange[0], binRange[1]);
        TString plot2; plot2.Form("Ex>>hExbg(%3.0f,%d,%d)", (binRange[1]-binRange[0])/binWidth, binRange[0], binRange[1]);
        
        //tree->Draw("s1x:vertexZ>>h7(100,-100,250,100,-200,300)", "", "colz");
        tree->Draw(plot1, s1xcut + s0cut + pidZcut + vertexZcut + tofS1cut, "colz");
        hEx->SetMinimum(0);
        hEx->SetTitle("Ex | gated");
        hEx->SetXTitle("Ex [MeV]");
        TString hExYTitle; hExYTitle.Form("count / %1.1f MeV", binWidth);
        hEx->SetYTitle(hExYTitle);
        hEx->Draw();
        tree->Draw(plot2, s1xcut + s0cut + !pidZcut + carboncut + tofS1cut, "same");
        hExbg->Scale(bgScale);
        hExbg->SetLineColor(2);
        hExbg->Draw("same");
        text->SetTextColor(2);
        text->DrawLatex(0.6,0.8,"carbon");
        
        cScript->cd(9);
        TH1F* hExsub = new TH1F(*hEx);
        hExsub->Sumw2();
        hExsub->Add(hExbg,-1);
        hExsub->Draw();
        
        if( Fiton){
                TF1 * fit = new TF1("fit", "gaus(0)+gaus(3)+gaus(6)+gaus(9)", -15, 40);
                Double_t par[12] = {50, 0, 5, 40, 10, 5, 20, 30, 5};
                fit->SetParameters(50, 0, 5, 40, 10, 5, 20, 30, 5);
                fit->FixParameter(1,0);                
                hExsub->Fit("fit","R");
        }
        
        cScript->cd(10);
        tree->Draw("kMomt>>h10(50,0,400)", s1xcut + s0cut + pidZcut + vertexZcut + tofS1cut + Aux, "colz");
        h10->SetTitle("Momt [MeV/c]");
        h10->SetXTitle("Momt [MeV/c]");
        tree->Draw("kMomt>>h10a(50,0,400)", s1xcut + s0cut + !pidZcut + carboncut + tofS1cut + Aux, "same");
        h10a->SetLineColor(2);
        h10a->SetXTitle("Momt [MeV/c]");
        h10a->Scale(bgScale);
        h10a->Draw("same");
        
        cScript->cd(11);
        TH1F* h10b = new TH1F(*h10);
        h10b->Sumw2();
        h10b->Add(h10a,-1);
        h10b->Draw();
        
        cScript->cd(12);
        tree->Draw("phi2-phi1>>h11(50,-50,50)", s1xcut + s0cut + pidZcut + vertexZcut + tofS1cut + Aux, "colz");
        h11->SetTitle("Off-Plane Angle");
        h11->SetXTitle("Off-Plane Angle [deg]");
        tree->Draw("phi2-phi1>>h11a(50,-50,50)", s1xcut + s0cut + !pidZcut + carboncut + tofS1cut + Aux, "same");
        h11a->SetLineColor(2);
        h11a->Scale(bgScale);
        h11a->Draw("same");
        
        cScript->cd(13);
        TH1F* h11b = new TH1F(*h11);
        h11b->Sumw2();
        h11b->Add(h11a,-1);
        h11b->Draw();
        
        cScript->cd(14);
        tree->Draw("theta1+theta2>>h14(90, 60, 90)", s1xcut + s0cut + pidZcut + vertexZcut + tofS1cut + Aux, "colz");
        h14->SetTitle("Open Theta");
        h14->SetXTitle("theta1+theta2 [deg]");
        tree->Draw("theta1+theta2>>h14a(90, 60, 90)", s1xcut + s0cut + !pidZcut + carboncut + tofS1cut + Aux, "same");
        h14a->SetLineColor(2);
        h14a->Scale(bgScale);
        h14a->Draw("same");
        
        cScript->cd(15);
        TH1F* h14b = new TH1F(*h14);
        h14b->Sumw2();
        h14b->Add(h14a,-1);
        h14b->Draw();
        
/********************************************************************/
//tree->Draw("s1x:pidAOQ>>h8(100,1.4,3.2,100,-200,300)", "abs(tofS1-34.5)<1 && abs(vertexZ-15)<20 && pidZ>5", "colz");
//tree->Draw("pidZ:pidAOQ>>h8(100,1.4,3.2,100,1, 11)", "abs(tofS1-34.5)<1 && abs(vertexZ-15)<20 && pidZ>5", "colz");
/*
//	TString cut = "gate.Test(9) & abs(vertex-10)<60 & abs(tof_D1.fTiming-35)<2 & abs((p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()-80)<15 & abs(p2p.fSp-20)<30"

TString cut = "gate.Test(9) && abs(vertex.fZ-10)<60 && abs(tof_D1.fTiming-35)<1 ";
TString cutbg = "gate.Test(11) && !gate.Test(9) && abs(vertex.fZ-10)<60 && abs(tof_D1.fTiming-35)<2";
TString cutbg2 = "!gate.Test(9) && abs(vertex.fZ-10)<60 && abs(tof_D1.fTiming-35)<1";

TCut tgt = "gate.Test(9)";
TCut vertexZ = "abs(vertex.fZ-10)<60";

/*
TString openAng = "";//"&& TMath::Abs((p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()-80)<15";

cScript->cd(1);
tree->Draw("p2p.fEx>>hSp1(50,-20,80)",cut + openAng + "&& smwdc_S1.fTrack.fX<0 && pid_ds.fZ>5", "");
hSp1->SetTitle("tgt + |vertex.Z-10|<60 + |tof-35|<1 + 0<s1x<100 + Z>5");
hSp1->SetXTitle("Ex2(22O) [MeV]");
hSp1->SetMinimum(0);
hSp1->Draw();
tree->Draw("p2p.fEx>>hSp1bg(50,-20,80)",cutbg2 + openAng + "&& smwdc_S1.fTrack.fX<0 && pid_ds.fZ>5", "same");
hSp1bg->SetLineColor(2);
hSp1bg->Scale(1.0);
hSp1bg->Draw("same");

cScript->cd(2);
TH1F* sp1sub = new TH1F(*hSp1);
sp1sub->Sumw2();
sp1sub->Add(hSp1bg, -1);
sp1sub->Draw();

printf("Sp1...done\n");

cScript->cd(3);
tree->Draw("p2p.fEx>>hSp2(50,-20,80)",cut + openAng + "&& smwdc_S1.fTrack.fX<100 && smwdc_S1.fTrack.fX>0 && pid_ds.fZ>5", "");
hSp2->SetTitle("tgt + |vertex.Z-10|<60 + |tof-35|<1 + 0<s1x<100 + Z<5");
hSp2->SetXTitle("Ex2(22O*) [MeV]");
hSp2->SetMinimum(0);
hSp2->Draw();
tree->Draw("p2p.fEx>>hSp2bg(50,-20,80)",cutbg2 + openAng + "&& smwdc_S1.fTrack.fX<100 && smwdc_S1.fTrack.fX>0  && pid_ds.fZ>5", "same");
hSp2bg->SetLineColor(2);
hSp2bg->Scale(1.0);
hSp2bg->Draw("same");

cScript->cd(4);
TH1F* sp2sub = new TH1F(*hSp2);
sp2sub->Sumw2();
sp2sub->Add(hSp2bg, -1);
sp2sub->Draw();


/*
cScript->cd(1);
tree->Draw("smwdc_S1.fTrack.fX:pid_ds.fAOQ>>hs1xAoQ(100,2,3, 100, -200, 500)", cut, "colz");

cScript->cd(2);
tree->Draw("smwdc_S1.fTrack.fX:pid_ds.fZ>>hs1xZ(100,1,10, 100, -200, 500)", cut, "colz");

cScript->cd(3);
tree->Draw("smwdc_S1.fTrack.fX:p2p.fEx>>hs1xEx(80,-40,120, 100, -200, 500)", cut, "colz");

cScript->cd(1);
//tree->Draw("pid_ds.fZ:pid_ds.fAOQ>>hPID(100,2,3,100,1,10)", cut , "colz");
tree->Draw("p2p.fEx>>hSp1(80,-40,120)",cut + "&& smwdc_S1.fTrack.fX<0", "colz");
tree->Draw("p2p.fEx>>hSp1bg(80,-40,120)",cutbg + "&& smwdc_S1.fTrack.fX<0", "colz");

cScript->cd(2);
//tree->Draw("pid_ds.fZ:pid_ds.fAOQ>>hPIDa(100,2,3,100,1,10)", cut + "&& smwdc_S1.fTrack.fX<0", "colz");



/*
tree->Draw("smwdc_S1[0].fTrack.fX>>h01(200,-200,400)", cut + " & nyoki.fID==1", "");
tree->Draw("smwdc_S1[0].fTrack.fX>>h02(200,-200,400)", cut + " & nyoki.fID==2", "");
tree->Draw("smwdc_S1[0].fTrack.fX>>h03(200,-200,400)", cut + " & nyoki.fID==3", "");
tree->Draw("smwdc_S1[0].fTrack.fX>>h04(200,-200,400)", cut + " & nyoki.fID==4", "");


tree->Draw("smwdc_S1[0].fTrack.fX>>h05(200,-200,400)", cut + " & nyoki.fID==5", "", 2000000);printf(" h05 done .\n"); 	
tree->Draw("smwdc_S1[0].fTrack.fX>>h06(200,-200,400)", cut + " & nyoki.fID==6", "", 2000000);printf(" h06 done .\n");
tree->Draw("smwdc_S1[0].fTrack.fX>>h07(200,-200,400)", cut + " & nyoki.fID==7", "", 2000000);printf(" h07 done .\n");
tree->Draw("smwdc_S1[0].fTrack.fX>>h08(200,-200,400)", cut + " & nyoki.fID==8", "", 2000000);printf(" h08 done .\n");
tree->Draw("smwdc_S1[0].fTrack.fX>>h09(200,-200,400)", cut + " & nyoki.fID==9", "", 2000000);printf(" h09 done .\n");
//tree->Draw("smwdc_S1[0].fTrack.fX>>h10(200,-200,400)", cut + " & nyoki.fID==10", "");

h07->SetLineColor(4);h07->Draw();
h08->SetLineColor(2);h08->Draw("same");
h09->SetLineColor(4);h09->Draw("same");
//h10->SetLineColor(2);h10->Draw("same");
h06->SetLineColor(2);h06->Draw("same");
h05->SetLineColor(4);h05->Draw("same");
/*h04->SetLineColor(2);h04->Draw("same");
h03->SetLineColor(4);h03->Draw("same");
h02->SetLineColor(2);h02->Draw("same");
h01->SetLineColor(4);h01->Draw("same");

cScript->cd(3);
tree->Draw("pid_ds.fZ:pid_ds.fAOQ>>hPIDb(100,2,3,100,1,10)", cut + "&& 100>smwdc_S1.fTrack.fX && smwdc_S1.fTrack.fX>0", "colz");
//tree->Draw("nyoki.fCharge:plaV775[4].fCharge>>p07(100,700, 2200, 100, 700, 2200)", cut + "& nyoki.fID==7", "colz", 2000000);
//printf(" p07 done .\n");

/*cScript->cd(1);
tree->Draw("nyoki.fCharge:plaV775[4].fCharge>>p08(100,700, 2200, 100, 700, 2200)", cut + "& nyoki.fID==8", "colz",3000000);
p08->SetTitle("Nyoki-8 Q | S0DPL");
printf(" p08 done .\n");

/*
//----------------- S0img
TString cut = "1";//"(coinReg.fQuality & 7) == 2"; //"gate.Test(1) & gate.Test(12)";
//Int_t eventRange[2] = {250000, 1102000}; // optics 3019
//Int_t eventRange[2] = {1841093, 8999275}; // ppcoin 1007, ppcoin
Int_t eventRange[2] = {tree->GetEntries(), 0 };
//Int_t eventRange[2] = {5000000, 256859}; // 
//Int_t eventRange[2] = {200000, 10840368}; // ppcoin 1008, 1009, beam

cScript->cd(1);
tree->Draw("plaV1190_FH9.fCharge:tof_US.fTiming>>hpid(500, -1500, -1400, 500, 4900, 6200)",cut, "colz", eventRange[0], eventRange[1]);
hpid->SetTitle("PID upstream");

cScript->cd(2);
tree->Draw("S0img.fTrack.fY:S0img.fTrack.fX>>hs0xy(200, -30, 30, 200, -30, 30)", cut, "colz", eventRange[0], eventRange[1]);
hs0xy->SetTitle("S0img XY [mm, mm]");

cScript->cd(3);
tree->Draw("S0img.fTrack.fA*1000:S0img.fTrack.fX>>hs0xa(200, -30, 30, 200, -30, 30)", cut, "colz", eventRange[0], eventRange[1]);
hs0xa->SetTitle("S0img XA [mm, mrad]");

cScript->cd(4);
tree->Draw("S0img.fTrack.fB*1000:S0img.fTrack.fX>>hs0xb(200, -30, 30, 200, -50, 50)", cut, "colz", eventRange[0], eventRange[1]);
hs0xb->SetTitle("S0img XB [mm, mrad]");

cScript->cd(5);
tree->Draw("S0img.fTrack.fB*1000:S0img.fTrack.fY>>hs0yb(200, -30, 30, 200, -50, 50)", cut, "colz", eventRange[0], eventRange[1]);
hs0yb->SetTitle("S0img YB, [mm, mrad]");

cScript->cd(6);
tree->Draw("S0img.fTrack.fB*1000:S0img.fTrack.fA*1000>>hs0ab(200, -30, 30, 200, -50, 50)", cut, "colz", eventRange[0], eventRange[1]);
hs0ab->SetTitle("S0img AB [mrad, mrad]");


/**/ //----------------- Optics element
/*
//	TString cut = "gate.Test(1) & gate.Test(12) & abs(smwdc_S1.fTrack.fB)<0.3 && abs(ppac.fX/75)<0.2 && abs(S0img.fTrack.fB)<10";
TString cut = "gate.Test(1) & gate.Test(12) & abs(smwdc_S1.fTrack.fB)<0.3";

//Int_t eventRange[2] = {250000, 1102000}; // optics 3019
//Int_t eventRange[2] = {200000, 10840368}; // ppcoin 1008, 1009
//Int_t eventRange[2] = {256858, 0}; // ppcoin 1008, 1009
Int_t eventRange[2] = {7000000, 256859}; // 
//Int_t eventRange[2] = {tree->GetEntries(), 0}; // 


cScript->cd(1);
tree->Draw("S0img.fTrack.fX:smwdc_S1.fTrack.fX>>hs1xs0x(50,-20,20,50,-8,8)", cut + " & abs(S0img.fTrack.fA*1000)<3", "colz", eventRange[0], eventRange[1]);
hs1xs0x->SetTitle("(s1x|s0x) [mm/mm] | ");

cScript->cd(2);
tree->Draw("S0img.fTrack.fA*1000:smwdc_S1.fTrack.fX>>hs1xs0a(50,-20,20,50,-30,30)", cut + " & abs(S0img.fTrack.fX)<2", "colz", eventRange[0], eventRange[1]);
hs1xs0a->SetTitle("(s1x|s0a) [mm/mrad]");

cScript->cd(3);
tree->Draw("ppac.fX/75:smwdc_S1.fTrack.fX>>hs1xs0d(50,-20,20,50,-1,1)", cut + " & abs(S0img.fTrack.fA*1000)<3" + " & abs(S0img.fTrack.fX)<2" , "colz", eventRange[0], eventRange[1]);
hs1xs0d->SetTitle("(s1x|d) [mm/1%]");

cScript->cd(4);
tree->Draw("S0img.fTrack.fX:smwdc_S1.fTrack.fA*1000>>hs1as0x(50,-350,-100,50,-8,8)", cut + " & abs(S0img.fTrack.fA*1000)<3", "colz", eventRange[0], eventRange[1]);
hs1as0x->SetTitle("(s1a|s0x) [mrad/mm]");

cScript->cd(5);
tree->Draw("S0img.fTrack.fA*1000:smwdc_S1.fTrack.fA*1000>>hs1as0a(50,-350,-100,50,-30,30)", cut + " & abs(S0img.fTrack.fX)<2", "colz", eventRange[0], eventRange[1]);
hs1as0a->SetTitle("(s1a|s0a) [mrad/mrad]");

cScript->cd(6);
tree->Draw("ppac.fX/75:smwdc_S1.fTrack.fA*1000>>hs1as0d(50,-350,-100,50,-1,1)", cut + " & abs(S0img.fTrack.fA*1000)<3" + " & abs(S0img.fTrack.fX)<2" , "colz", eventRange[0], eventRange[1]);
hs1as0d->SetTitle("(s1a|d) [mrad/1%]");

/*
cScript->cd(5);
tree->Draw("S0img.fTrack.fY:smwdc_S1.fTrack.fY>>hs1ys0y(100,-200,200,100,-8,8)", cut , "colz", eventRange[0], eventRange[1]);
hs1ys0y->SetTitle("(s1y|s0y) [mm/mm]");

cScript->cd(6);
tree->Draw("S0img.fTrack.fB*1000:smwdc_S1.fTrack.fY>>hs1ys0b(100,-200,200,100,-30,30)", cut , "colz", eventRange[0], eventRange[1]);
hs1ys0b->SetTitle("(s1y|s0b) [mm/mrad]");
/*
cScript->cd(7);
tree->Draw("S0img.fTrack.fY:smwdc_S1.fTrack.fB>>hs1bs0y(100,-1.5,1.5,100,-8,8)", cut , "colz", eventRange[0], eventRange[1]);
hs1bs0y->SetTitle("(s1b|s0y) [rad/mm]");

cScript->cd(8);
tree->Draw("S0img.fTrack.fB*1000:smwdc_S1.fTrack.fB>>hs1bs0b(100,-1.5,1.5,100,-30,30)", cut , "colz", eventRange[0], eventRange[1]);
hs1bs0b->SetTitle("(s1b|s0b) [rad/mrad]");

/**************************************************/
/*
        cScript->cd(1);
        tree->Draw("smwdc_S1.GetSigma(0)>>hsX(100,0,1)", "" , "");
        hsX->SetTitle("Sigma(X) [mm]");
        
        cScript->cd(2);
        tree->Draw("smwdc_S1.GetSigma(1)*1000>>hsA(100,0,20)", "" , "");
        hsA->SetTitle("Sigma(A) [mrad]");
        
        cScript->cd(3);
        tree->Draw("smwdc_S1.GetSigma(2)>>hsY(100,0,1)", "" , "");
        hsY->SetTitle("Sigma(X) [mm]");
        
        cScript->cd(4);
        tree->Draw("smwdc_S1.GetSigma(3)*1000>>hsB(100,0,20)", "" , "");
        hsB->SetTitle("Sigma(X) [mrad]");

/*******************************************************/


/*
TString cut = "abs(smwdc_S1.fTrack.fB)<0.3 &";

cScript->cd(1);
tree->Draw("smwdc_S1.fTrack.fX>>h23F(100,-80,20)", cut + "gate.Test(0) & abs(pid_ds.fZ-9)<0.5", "");
//h23F->SetTitle("s1x for difference isotopes");
//h23F->SetLineColor(1);
h23F->SetTitle("23F Brho=6.571 ");

cScript->cd(2);
tree->Draw("smwdc_S1.fTrack.fX>>h22O(100,-80,20)", cut + "gate.Test(1) & abs(pid_ds.fZ-8)<0.5", "");
h22O->SetTitle("22O Brho=6.569 ");
//h22O->SetLineColor(2);

cScript->cd(3);
tree->Draw("smwdc_S1.fTrack.fX>>h20N(100,-80,20)", cut + "gate.Test(2) & abs(pid_ds.fZ-7)<0.5", "");
h20N->SetTitle("20N Brho=6.582 ");
//h20N->SetLineColor(3);

cScript->cd(4);
tree->Draw("smwdc_S1.fTrack.fX>>h16C(100,-80,20)", cut + "gate.Test(4) & abs(pid_ds.fZ-6)<0.5", "");
h16C->SetTitle("16C Brho=6.617 ");
//h16C->SetLineColor(4);

cScript->cd(5);
tree->Draw("smwdc_S1.fTrack.fX>>h13B(100,-80,20)", cut + "gate.Test(5) & abs(pid_ds.fZ-5)<0.5", "");
h13B->SetTitle("13B Brho=6.640 ");
//h13B->SetLineColor(5);

cScript->cd(6);
tree->Draw("smwdc_S1.fTrack.fX>>h10Be(100,-80,20)", cut + "gate.Test(6) & abs(pid_ds.fZ-4)<0.5", "");
h10Be->SetTitle("10Be Brho=6.662 ");
//h10Be->SetLineColor(6);

cScript->cd(7);
tree->Draw("smwdc_S1.fTrack.fX>>h7Li(100,-80,20)", cut + "gate.Test(8) & abs(pid_ds.fZ-3)<0.5", "");
h7Li->SetTitle("7Li Brho=6.684 ");
//h7Li->SetLineColor(7);

cScript->cd(8);
tree->Draw("smwdc_S1.fTrack.fX>>h8Li(100,-80,20)", cut + "gate.Test(7) & abs(pid_ds.fZ-3)<0.5", "");
h8Li->SetTitle("8Li Brho=6.674 ");
//h8Li->SetLineColor(8);

/*
Double_t newO[2] = {0,0}; //{x,z} mm
Double_t ang = -74.3; //deg, left hand rotation about y axis

Double_t t = TMath::Tan(ang*TMath::DegToRad());
Double_t s = TMath::Sin(ang*TMath::DegToRad());
Double_t c = TMath::Cos(ang*TMath::DegToRad());

TString plot;
//plot.Form("(smwdc_S1.fTrack.fA+%.4f)/(1-smwdc_S1.fTrack.fA*%.4f):smwdc_S1.fTrack.fA>>h1(100,-3,3,100,-5,5)", t, t);
//plot.Form("smwdc_S1.fTrack.fY:(smwdc_S1.fTrack.fX-%.3f+smwdc_S1.fTrack.fA*%.3f)/(%.3f-smwdc_S1.fTrack.fA*%.3f)>>h1(400,-500,500,100,-200,200)", newO[0], newO[1],c,s);
plot.Form("smwdc_S1.fTrack.fX:(smwdc_S1.fTrack.fX-%.3f+smwdc_S1.fTrack.fA*%.3f)/(%.3f-smwdc_S1.fTrack.fA*%.3f)>>h1(400,-500,500,400,-500,500)", newO[0], newO[1],c,s);

tree->Draw(plot, "", "colz");
/**/

/*


for( Int_t i = 1; i <= 6; i++){
cScript->cd(i);
TString gate, plot;
Int_t wireNum = 44;
if( i == 1 || i == 2) wireNum = 56;
gate.Form("abs(smwdc_S1.fTrack.fX-150)<50 & abs(smwdc_S1.fTrack.fY)<25 & gate.Test(12)");
if( i == 1){
plot.Form("smwdc_S1_x1.fID>>h%0d(%d,1,%d)", i, wireNum, wireNum+1);
}else if( i ==2){
plot.Form("smwdc_S1_x2.fID>>h%0d(%d,1,%d)", i, wireNum, wireNum+1);
}else if( i ==3){
plot.Form("smwdc_S1_u1.fID>>h%0d(%d,1,%d)", i, wireNum, wireNum+1);
}else if( i ==4){
plot.Form("smwdc_S1_u2.fID>>h%0d(%d,1,%d)", i, wireNum, wireNum+1);
}else if( i ==5){
plot.Form("smwdc_S1_v1.fID>>h%0d(%d,1,%d)", i, wireNum, wireNum+1);
}else if( i ==6){
plot.Form("smwdc_S1_v2.fID>>h%0d(%d,1,%d)", i, wireNum, wireNum+1);
}

//gate.Form("smwdc_S1.GetWireIDAdopted(0)==%d", i);
//plot.Form("smwdc_S1.GetDriftLengthOriginal(0)>>h%0d(200,-1,11)",i);
tree->Draw(plot, gate);
}/**/

/*******************************************************************/
/*
cScript->cd(1);   tree->Draw("smwdc_S1_x1.fTiming>>h1(300, -100,  400)", "smwdc_S1_x1.fCharge > 350", "colz");
cScript->cd(2);   tree->Draw("smwdc_S1_x2.fTiming>>h2(300, -100,  400)", "smwdc_S1_x2.fCharge > 350", "colz");
cScript->cd(3);   tree->Draw("smwdc_S1_u1.fTiming>>h3(300, -100,  400)", "smwdc_S1_u1.fCharge > 350", "colz");
cScript->cd(4);   tree->Draw("smwdc_S1_u2.fTiming>>h4(300, -100,  400)", "smwdc_S1_u2.fCharge > 350", "colz");
cScript->cd(5);   tree->Draw("smwdc_S1_v1.fTiming>>h5(300, -100,  400)", "smwdc_S1_v1.fCharge > 350", "colz");
cScript->cd(6);   tree->Draw("smwdc_S1_v2.fTiming>>h6(300, -100,  400)", "smwdc_S1_v2.fCharge > 350", "colz");
/**/
/*  
cScript->cd(1);   tree->Draw("smwdc_S1_x1.fTiming:smwdc_S1_x1.fID>>h1(56, 1, 57, 500, -100,  400)", "", "colz");
cScript->cd(2);   tree->Draw("smwdc_S1_x2.fTiming:smwdc_S1_x2.fID>>h2(56, 1, 57, 500, -100,  400)", "", "colz");
cScript->cd(3);   tree->Draw("smwdc_S1_u1.fTiming:smwdc_S1_u1.fID>>h3(44, 1, 45, 500, -100,  400)", "", "colz");
cScript->cd(4);   tree->Draw("smwdc_S1_u2.fTiming:smwdc_S1_u2.fID>>h4(44, 1, 45, 500, -100,  400)", "", "colz");
cScript->cd(5);   tree->Draw("smwdc_S1_v1.fTiming:smwdc_S1_v1.fID>>h5(44, 1, 45, 500, -100,  400)", "", "colz");
cScript->cd(6);   tree->Draw("smwdc_S1_v2.fTiming:smwdc_S1_v2.fID>>h6(44, 1, 45, 500, -100,  400)", "", "colz");
/**/
/*
cScript->cd(1);   tree->Draw("smwdc_S1_x1.fDriftLength>>h1(300, -1,  11)", "smwdc_S1_x1.fCharge > 650", "colz");
cScript->cd(2);   tree->Draw("smwdc_S1_x2.fDriftLength>>h2(300, -1,  11)", "smwdc_S1_x2.fCharge > 650", "colz");
cScript->cd(3);   tree->Draw("smwdc_S1_u1.fDriftLength>>h3(300, -1,  11)", "smwdc_S1_u1.fCharge > 650", "colz");
cScript->cd(4);   tree->Draw("smwdc_S1_u2.fDriftLength>>h4(300, -1,  11)", "smwdc_S1_u2.fCharge > 650", "colz");
cScript->cd(5);   tree->Draw("smwdc_S1_v1.fDriftLength>>h5(300, -1,  11)", "smwdc_S1_v1.fCharge > 650", "colz");
cScript->cd(6);   tree->Draw("smwdc_S1_v2.fDriftLength>>h6(300, -1,  11)", "smwdc_S1_v2.fCharge > 650", "colz");
/**/

/*   
TCut incA = "TMath::Abs(S0img[0].fTrack.fA*1000)<1";
TCut incB = "TMath::Abs(S0img[0].fTrack.fB*1000)<1";
//TCut incX = "TMath::Abs(S0img[0].fTrack.fX*1000)<1";
//TCut incY = "TMath::Abs(S0img[0].fTrack.fY*1000)<1";

/* 
TCut pid23F = "TMath::Abs(tof_DS[0].fTiming-321.2)<3 && TMath::Abs(plaV775[0].fCharge-875)<75";
TCut pid22O = "TMath::Abs(tof_DS[0].fTiming-304)<3 && TMath::Abs(plaV775[0].fCharge-800)<100";
TCut pid20N = "TMath::Abs(tof_DS[0].fTiming-295)<3 && TMath::Abs(plaV775[0].fCharge-766)<100";
TCut pid16C = "TMath::Abs(tof_DS[0].fTiming-313)<3 && TMath::Abs(plaV775[0].fCharge-695)<50";	
TCut pid13B = "TMath::Abs(tof_DS[0].fTiming-319)<1 && TMath::Abs(plaV775[0].fCharge-634)<50";
TCut pid10Be = "TMath::Abs(tof_DS[0].fTiming-329)<3 && TMath::Abs(plaV775[0].fCharge-575)<50";
TCut pid8Li = "TMath::Abs(tof_DS[0].fTiming-314)<3 && TMath::Abs(plaV775[0].fCharge-530)<50";
TCut pid7Li = "TMath::Abs(tof_DS[0].fTiming-344)<3 && TMath::Abs(plaV775[0].fCharge-527)<50";
/**/



/*
TCut vertexZ = "TMath::Abs(beamZ.fAverage-10)<60";
TCut tofD1 = "TMath::Abs(tof_D1.fTiming-35)<10";	
TCut ang = "TMath::Abs((p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()-80)<10";

TCut tgt = "gate.Test(9)";
TCut holder = "gate.Test(10) && !gate.Test(9)";


TCut nyoki = "TMath::Abs(nyoki.fID-8)<=1 && nyoki.fCharge>500";

TCut carbon = "TMath::Abs(beamZ.fAverage-10)<120";
TCut Sp = "TMath::Abs(p2p.fSp)<60";

//tree->Draw("(p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()>>g1(100,80,90)","","");
//tree2->Draw("(p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()>>g2(100,80,90)","","same");
TH2F* h1 = new TH2F("h1", "Ex2 vs s1x | common", 100, -150, 300, 40, -20, 60);
TH2F* h2 = new TH2F("h2", "Ex2 vs s1x | common tgt", 100, -150, 300, 40, -20, 60);
TH2F* h3 = new TH2F("h3", "Ex2 vs s1x | common holder", 100, -150, 300, 40, -20, 60);	
TH2F* h4 = new TH2F("h4", "Ex2 vs s1x | common tgt |Sp-20|<20", 100, -150, 300, 40, -20, 60);	


cScript->cd(1);	tree->Draw("p2p.fEx:smwdc_S1.fTrack.fX>>h1", vertexZ + tofD1 + ang, "colz");
printf("------------- 1\n");
cScript->cd(2);	tree->Draw("p2p.fEx:smwdc_S1.fTrack.fX>>h2", vertexZ + tofD1 + ang + tgt, "colz");
printf("------------- 2\n");
cScript->cd(3);	tree->Draw("p2p.fEx:smwdc_S1.fTrack.fX>>h3", vertexZ + tofD1 + ang + holder, "colz");
printf("------------- 3\n");
cScript->cd(4);	//tree->Draw("p2p.fEx:smwdc_S1.fTrack.fX>>h4", vertexZ + tofD1 + ang + tgt + "abs(p2p.fSp-20)<20", "colz");
//printf("------------- 4\n");



/**/
/*
TString cut = "abs((p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()-86)<3 & abs(beamZ.fAverage-10)<60 & abs(p2p.fSp)<10";
cScript->cd(1);	
//	tree->Draw("p2p.fRecoilL.E()-938.272:p2p.fRecoilL.Theta()*TMath::RadToDeg()>>h1(100,20,70,100,0,200)", cut , "colz");
//	TF1 * f1 = new TF1("f1", "258.5/(1+(1.137753231)*TMath::Power(TMath::Tan(x*TMath::DegToRad()),2))", 20, 70);
//	f1->Draw("same");

tree->Draw("tofL.fTiming:p2p.fRecoilL.Theta()*TMath::RadToDeg()>>h1(100,20,70,100,5,20)", cut , "colz");
h1->SetTitle("Tpla-L ToF vs Theta | |openAng-86|<3 + |beamZ-10|<60 + |Sp|<10");
TF1 * f1 = new TF1("f1", "1400/299.792458/TMath::Cos((x-60)*TMath::DegToRad())*(938.272+(258.5/(1+(1.137753231)*TMath::Power(TMath::Tan(x*TMath::DegToRad()),2))))/TMath::Sqrt(2*938.272*(258.5/(1+(1.137753231)*TMath::Power(TMath::Tan(x*TMath::DegToRad()),2))) + TMath::Power((258.5/(1+(1.137753231)*TMath::Power(TMath::Tan(x*TMath::DegToRad()),2))),2))", 20, 70);
f1->Draw("same");


cScript->cd(2);
//	tree->Draw("p2p.fRecoilR.E()-938.272:p2p.fRecoilR.Theta()*TMath::RadToDeg()>>h2(100,20,70,100,0,200)", cut , "colz");
tree->Draw("tofR.fTiming:p2p.fRecoilR.Theta()*TMath::RadToDeg()>>h2(100,20,70,100,5,20)", cut , "colz");
h2->SetTitle("Tpla-R ToF vs Theta");
f1->Draw("same");

//================================================ Temp analysis   

/*
for( Int_t i = 0; i <11; i++){
printf("============== Sp BG - %d \n", i);
TString plotStr;
plotStr.Form("nyoki.fCharge:p2p.fSp>>hSpBG%d(200, -150, 200, 200,-500,4500)", i);
TString nyokiIDGate;
nyokiIDGate.Form("nyoki.fID==%d",i);
TCut nyokiID = nyokiIDGate;
tree->Draw(plotStr, nyokiID + basic2 + poltgt + tofD1, "colz");
}

tree->Draw("nyoki.fCharge:p2p.fSp>>hSpBG(200, -150, 200, 200,-500,4500)", basic2 + poltgt + tofD1, "colz");

for( Int_t i = 0; i <11; i++){
printf("============== nyoki BG - %d \n", i);
TString plotStr;
plotStr.Form("nyoki.fCharge:tof_D1.fTiming>>hnQBG%d(200, -25, 0, 200,-500,4500)", i);
TString nyokiIDGate;
nyokiIDGate.Form("nyoki.fID==%d",i);
TCut nyokiID = nyokiIDGate;
tree->Draw(plotStr, nyokiID + basic2 + poltgt, "colz");
}

tree->Draw("nyoki.fCharge:tof_D1.fTiming>>hnQBG(200, -25, 0, 200,-500,4500)", basic2 + poltgt, "colz");

Int_t Div[2] = {6,2}; 
Int_t size = 300;
TCanvas * cScript = new TCanvas("cScript", "cScript", 0,0 , size*Div[0], size*Div[1]);
cScript->Divide(Div[0],Div[1]);

for( Int_t i = 0; i <11; i++){
printf("============== nyoki - %d \n", i);
cScript->cd(i/2 +1 + 6*(1-TMath::Power(-1,i))/2);
TString plotStr;
plotStr.Form("nyoki.fCharge:tof_D1.fTiming>>hnQ%d(200, -25, 0, 200,-500,4500)", i);
TString nyokiIDGate;
nyokiIDGate.Form("nyoki.fID==%d",i);
TCut nyokiID = nyokiIDGate;
tree->Draw(plotStr, nyokiID + basic + poltgt, "colz");
}

cScript->cd(12);
tree->Draw("nyoki.fCharge:tof_D1.fTiming>>hnQ(200, -25, 0, 200,-500,4500)", basic + poltgt, "colz");

TCanvas * cScript2 = new TCanvas("cScript2", "cScript2", 2000,0 , size*Div[0], size*Div[1]);
cScript2->Divide(Div[0],Div[1]);

for( Int_t i = 0; i <11; i++){
printf("============== Sp - %d \n", i);
cScript2->cd(i/2 +1 + 6*(1-TMath::Power(-1,i))/2);
TString plotStr;
plotStr.Form("nyoki.fCharge:p2p.fSp>>hSp%d(200, -150, 200, 200,-500,4500)", i);
TString nyokiIDGate;
nyokiIDGate.Form("nyoki.fID==%d",i);
TCut nyokiID = nyokiIDGate;
tree->Draw(plotStr, nyokiID + basic + poltgt + tofD1, "colz");
}



/*   
cScript->cd(1);
tree->Draw("p2p.fRecoilL.Theta()*TMath::RadToDeg():p2p.fRecoilR.Theta()*TMath::RadToDeg()>>g1(100, 20,70, 100, 20, 70)","","colz");

cScript->cd(2);
tree2->Draw("p2p.fRecoilL.Theta()*TMath::RadToDeg():p2p.fRecoilR.Theta()*TMath::RadToDeg()>>g2(100, 20,70, 100, 20, 70)","","colz");

/*
cScript->cd(1);
//tree->Draw("p2p.fEx>>g1(60,-20,100)", basic + tofD1+ nyoki + poltgt +ang );
//tree->Draw("p2p.fEx>>g2(60,-20,100)", !basic + !tofD1+ nyoki + poltgt +ang , "same");

//tree->Draw("(p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()>>g1(60,60,90)", basic + tofD1+ nyoki + poltgt + Sp);
//tree->Draw("(p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()>>g2(60,60,90)", !basic + !tofD1+ nyoki + poltgt + Sp , "same");

//Sp = "TMath::Abs(p2p.fEx-(-2))<2";

tree->Draw("p2p.fResidual.P()>>g1(40,0,300)", basic + tofD1+ nyoki + poltgt + "TMath::Abs(p2p.fEx)<5");
tree->Draw("p2p.fResidual.P()>>g2(40,0,300)", !basic + !tofD1+ nyoki + poltgt + "TMath::Abs(p2p.fEx)<5" , "same");

g2->Scale(0.21);
g2->SetLineColor(2);
g2->Draw("same");

cScript->cd(2);
TH1F * g3 = new TH1F(*g1 - *g2);
g3->Draw();

cScript->cd(3);
tree->Draw("p2p.fResidual.P()>>h1(100,0,300)", basic + tofD1+ nyoki + poltgt + "TMath::Abs(p2p.fEx-16)<10");
tree->Draw("p2p.fResidual.P()>>h2(100,0,300)", !basic + !tofD1+ nyoki + poltgt + "TMath::Abs(p2p.fEx-16)<10" , "same");

h2->Scale(0.21);
h2->SetLineColor(2);
h2->Draw("same");

cScript->cd(4);
TH1F * h3 = new TH1F(*h1 - *h2);
h3->Scale(1/h3->Integral(0,100));
h3->Draw();

cScript->cd(5);
tree->Draw("p2p.fResidual.P()>>k1(40,0,300)", basic + tofD1+ nyoki + poltgt + "TMath::Abs(p2p.fEx-40)<10");
tree->Draw("p2p.fResidual.P()>>k2(40,0,300)", !basic + !tofD1+ nyoki + poltgt + "TMath::Abs(p2p.fEx-40)<10" , "same");

k2->Scale(0.21);
k2->SetLineColor(2);
k2->Draw("same");

cScript->cd(6);
TH1F * k3 = new TH1F(*k1 - *k2);
k3->Scale(1/k3->Integral(0,100));
k3->Draw();


cScript->cd(7);
tree->Draw("p2p.fResidual.P()>>q1(40, 0,300)", basic + tofD1+ nyoki + poltgt + "TMath::Abs(p2p.fEx-60)<10");
tree->Draw("p2p.fResidual.P()>>q2(40, 0,300)", !basic + !tofD1+ nyoki + poltgt + "TMath::Abs(p2p.fEx-60)<10" , "same");

q2->Scale(0.21);
q2->SetLineColor(2);
q2->Draw("same");

cScript->cd(8);
TH1F * q3 = new TH1F(*q1 - *q2);
q3->Scale(1/q3->Integral(0,100));
q3->Draw();
/*
Double_t para[18] = {20,0,4, 50,10,4, 120,15,4, 80,25,4, 30,40,5, 20,60,4}  ;
TF1 * total = new TF1("total", "gaus(0) + gaus(3) + gaus(6) + gaus(9) + gaus(12) + gaus(15)", -10, 100);
total->SetParameters(para);

g3->Fit("total","R");

total->GetParameters(para);

Double_t fitRange[2] = {-10,100};
TF1 * k1 = new TF1("k1", "gaus", fitRange[0], fitRange[1]);
TF1 * k2 = new TF1("k2", "gaus", fitRange[0], fitRange[1]);
TF1 * k3 = new TF1("k3", "gaus", fitRange[0], fitRange[1]);
TF1 * k4 = new TF1("k4", "gaus", fitRange[0], fitRange[1]);
TF1 * k5 = new TF1("k5", "gaus", fitRange[0], fitRange[1]);
TF1 * k6 = new TF1("k6", "gaus", fitRange[0], fitRange[1]);


k1->SetParameters(&para[0]);
k1->SetLineColor(2);k1->SetLineWidth(1);k1->SetLineStyle(1);k1->Draw("same");
k2->SetParameters(&para[3]);
k2->SetLineColor(4);k2->SetLineWidth(1);k2->SetLineStyle(1);k2->Draw("same");
k3->SetParameters(&para[6]);	
k3->SetLineColor(6);k3->SetLineWidth(1);k3->SetLineStyle(1);k3->Draw("same");
k4->SetParameters(&para[9]);
k4->SetLineColor(7);k4->SetLineWidth(1);k4->SetLineStyle(1);k4->Draw("same");
k5->SetParameters(&para[12]);
k5->SetLineColor(8);k4->SetLineWidth(1);k4->SetLineStyle(1);k5->Draw("same");
k6->SetParameters(&para[15]);
k6->SetLineColor(9);k4->SetLineWidth(1);k4->SetLineStyle(1);k6->Draw("same");

printf("reduced chi-square: %3.1f/%d = %3.1f\n", total->GetChisquare(), total->GetNDF(), total->GetChisquare()/total->GetNDF());



/*	
TCut nyokiS = "((nyoki.fID==7 && TMath::Abs(nyoki.fCharge-2650)<650) || (nyoki.fID==8 && TMath::Abs(nyoki.fCharge-2500)<500))";  

TCut nyokiA = "((nyoki.fID==7 || nyoki.fID==8) && TMath::Abs(nyoki.fCharge-2650)<650)";
TCut nyoki7 = "(nyoki.fID==7 && TMath::Abs(nyoki.fCharge-2650)<650)";
TCut nyoki8 = "(nyoki.fID==8 && TMath::Abs(nyoki.fCharge-2500)<500)";

TH1F* h1 = new TH1F("h1", "nyoki 7 ~ 8", 60, -20, 100);
h1->SetMinimum(0);
TH1F* h2 = new TH1F("h2", "nyoki 7", 50, 0, 1);
TH1F* h3 = new TH1F("h3", "nyoki 8", 50, 0, 1);
h2->SetMinimum(0);
h3->SetLineColor(2);

cScript->cd(1);
//tree->Draw("p2p_c.fSp>>h1", "gate.Test(4) & TMath::Abs(vertex.fZ-170)<60" && nyokiS);

tree->Draw("p2p.fResidual.Theta()*TMath::RadToDeg()>>h2", "gate.Test(4) & TMath::Abs(vertex.fZ-170)<60" && nyoki7);
h2->Scale(1./h2->Integral(1,50));
//cScript->cd(2);

tree->Draw("p2p.fResidual.Theta()*TMath::RadToDeg()>>h3", "gate.Test(4) & TMath::Abs(vertex.fZ-170)<60" && nyoki8, "same");
h3->Scale(1./h3->Integral(1,50));

/*
cScript->cd(3);
TH1F * twoPthree = new TH1F(*h2);
twoPthree->Add(h3,1);
twoPthree->SetTitle("nyoki 7 + nyoki 8");
twoPthree->SetMinimum(0);
twoPthree->Draw();

cScript->cd(4);
TH1F* overlap = new TH1F(*twoPthree);
overlap->SetTitle("nyoki 7 + nyoki 8 - (nyoki 7 & nyoki 8)");
overlap->Sumw2();
overlap->Add(h1, -1);
overlap->Draw();

/*   
TCut common = "gate.Test(4) && nyoki.fCharge>2000 && TMath::Abs(vertex.fZ)<60";
TCut carbon = "gate.Test(4) && nyoki.fCharge>2000 && TMath::Abs(vertex.fZ-160)<60";

TH1F * hSp = new TH1F("hSp", "Sp", 160, -40, 120);
hSp->SetMinimum(0);
TH1F* hMomt1 = new TH1F("hMomt1", "Momt", 100, 0, 300);

cScript->cd(1);
tree->Draw("p2p.fSp>>hSp", common);
tree->Draw("p2p_c.fSp>>hSpc(160,-40,120)", carbon, "same");

cScript->cd(2);
tree->Draw("TMath::Power(TMath::Power(0.84746*(p2p.fResidual.E())-1.310797*(p2p.fResidual.Pz()),2)+TMath::Power(p2p.fResidual.Px(),2)+TMath::Power(p2p.fResidual.Py(),2),0.5)>>hMomt1", common);
tree->Draw("TMath::Power(TMath::Power(0.84746*(p2p.fResidual.E())-1.310797*(p2p.fResidual.Pz()),2)+TMath::Power(p2p.fResidual.Px(),2)+TMath::Power(p2p.fResidual.Py(),2),0.5)>>hMomtc(100,0,300)", carbon, "same");

cScript->cd(3);
tree->Draw("TMath::Power(TMath::Power(0.84746*(p2p.fResidual.E())-1.310797*(p2p.fResidual.Pz()),2)+TMath::Power(p2p.fResidual.Px(),2)+TMath::Power(p2p.fResidual.Py(),2),0.5):p2p.fSp>>h1(80,-40,120,60,0,300)", common, "colz");

cScript->cd(4);
tree->Draw("TMath::Power(TMath::Power(0.84746*(p2p_c.fResidual.E())-1.310797*(p2p_c.fResidual.Pz()),2)+TMath::Power(p2p_c.fResidual.Px(),2)+TMath::Power(p2p_c.fResidual.Py(),2),0.5):p2p_c.fSp>>h2(80,-40,120,60,0,300)", carbon, "colz");

/*  cScript->cd(1);
tree->Draw("nyoki.fCharge:p2p.fSp>>hSpn(160, -40, 120, 40, 500, 4500)", common, "colz");

cScript->cd(5);
tree->Draw("nyoki.fCharge:(p2p.fRecoilL.Theta()+p2p.fRecoilR.Theta())*TMath::RadToDeg()>>hOpen(60, 60, 90, 40, 500, 4500)", common, "colz");

cScript->cd(2);
*/
/*   cScript->cd(1);
tree->Draw("plaV775_R_raw.fTiming>>h1(2000,0,2000)",     "plaV775_R_raw.fID==1");
cScript->cd(2);
tree->Draw("plaV775_R_raw.fTiming>>h1a(200, 200,300)",   "plaV775_R_raw.fID==1");
cScript->cd(3);
tree->Draw("plaV775_R_raw.fTiming>>h1b(200, 1750,1850)", "plaV775_R_raw.fID==1");
*/

/*
TCut common = "gate.Test(0) && gate.Test(6) && TMath::Abs(vertex.fZ)<100";

cScript->cd(1);
gROOT->ProcessLine(".!date"); printf(" nyoki 6 \n");
tree->Draw("p2p.fSp>>h6(40,-40,120)", common && "nyoki.fID==6 && nyoki.fCharge>1500", "colz");

cScript->cd(6);
gROOT->ProcessLine(".!date"); printf(" nyoki 6 2D\n");
tree->Draw("nyoki.fCharge:p2p.fSp>>h6n(40,-40,120,50,0, 4500)", common && "nyoki.fID==6", "colz");

cScript->cd(2);
gROOT->ProcessLine(".!date"); printf(" nyoki 7 \n");
tree->Draw("p2p.fSp>>h7(80,-40,120)", common && "nyoki.fID==7 && nyoki.fCharge>2000", "colz");

cScript->cd(7);
gROOT->ProcessLine(".!date"); printf(" nyoki 7 2D \n");
tree->Draw("nyoki.fCharge:p2p.fSp>>h7n(40,-40,120,40,500, 4500)", common && "nyoki.fID==7", "colz");

cScript->cd(3);
gROOT->ProcessLine(".!date"); printf(" nyoki 8 \n");
tree->Draw("p2p.fSp>>h8(80,-40,120)", common && "nyoki.fID==8 && nyoki.fCharge>2000", "colz");

cScript->cd(8);
gROOT->ProcessLine(".!date"); printf(" nyoki 8 2D \n");
tree->Draw("nyoki.fCharge:p2p.fSp>>h8n(40,-40,120,45,500, 4500)", common && "nyoki.fID==8", "colz");

cScript->cd(4);
gROOT->ProcessLine(".!date"); printf(" nyoki 9 \n");
tree->Draw("p2p.fSp>>h9(40,-40,120)", common && "nyoki.fID==9 && nyoki.fCharge>2000", "colz");

cScript->cd(9);
gROOT->ProcessLine(".!date"); printf(" nyoki 9 2D \n");
tree->Draw("nyoki.fCharge:p2p.fSp>>h9n(40,-40,120,45,500, 4500)", common && "nyoki.fID==9", "colz");

cScript->cd(5);
gROOT->ProcessLine(".!date"); printf(" nyoki all \n");
tree->Draw("p2p.fSp>>hall(80,-40,120)", common && "nyoki.fCharge>2000", "colz");

cScript->cd(10);
gROOT->ProcessLine(".!date"); printf(" nyoki all 2D \n");
tree->Draw("nyoki.fCharge:p2p.fSp>>halln(40,-40,120,45,500, 4500)", common, "colz");

/*cScript->cd(4);
//gROOT->ProcessLine(".!date"); printf(" nyoki all 2D \n");
//tree->Draw("nyoki.fCharge:p2p.fSp>>hn(40,-40,120,40,500, 4500)", common , "colz");

*/

}   

//############################################# Template

/*   TLatex text;
text.SetNDC();
text.SetTextColor(1);
text.DrawText(0.2, 0.3, "no Corr");
text.SetTextColor(2);
text.DrawText(0.2, 0.25, "Mag Corr");
text.SetTextColor(4);
text.DrawText(0.2, 0.2, "Mag + BeamZ=15 Corr");*/


/* ----------- get leave data

Double_t data;
tree->SetBranchAddress("branch", &data);
tree->GetEntry(eventID);
printf("%f \n", data);

*/
