{
        gROOT->Reset();
        gROOT->ProcessLine(".!date");
        gStyle->SetOptStat(0);
        const double deg2rad = 3.141592654/180;

        //========================================================
        //TFile *f00 = new TFile ("THREEDEE/23F_Sp13.3_Tc030_ang010_phi004.root", "read"); TTree *Ex00 = (TTree*)f00->Get("tree");
        TFile *f00 = new TFile ("THREEDEE/23F_Sp13.3_Tc002_ang002.root", "read"); TTree *Ex00 = (TTree*)f00->Get("tree");
        //TFile *f10 = new TFile ("THREEDEE/23F_Sp23.3_Tc030_ang010_phi00.root", "read"); TTree *Ex10 = (TTree*)f10->Get("tree");
        //TFile *f20 = new TFile ("THREEDEE/23F_Sp33.3_Tc030_ang010_phi00.root", "read"); TTree *Ex20 = (TTree*)f20->Get("tree");
        
        /*
        Ex00->Draw("theta1>>h1(5,20,70)","xsec1d5","");
        Ex00->Draw("theta2>>h2(5,20,70)","xsec1d5","");

        Double_t YL[5], YR[5];
        Double_t asym[5];
        
        
        for( Int_t i = 1; i <=5; i++){
                YL[i] = h1->GetBinContent(i);
                YR[i] = h2->GetBinContent(i);
                asym[i] = (YL[i]-YR[i])/(YL[i]+YR[i]);
                printf("%d, %10.2f, %10.2f, %6.3f\n", i, YL[i],YR[i],asym[i]);
        }
        */
        
        TCanvas * cAy = new TCanvas("cAy", "cAy", 2000, 0, 3*500, 1*500);
        cAy->Divide(3,1);
        
        TH2F * h1 = new TH2F("h1", "1d5/2", 20, 20,70, 50, -180,180); h1->SetXTitle("theta1 [deg]"); h1->SetYTitle("theta_k [deg]");
        TH2F * h2 = new TH2F("h2", "1p1/2", 20, 20,70, 50, -180,180); h2->SetXTitle("theta1 [deg]"); h2->SetYTitle("theta_k [deg]");
        TH2F * h3 = new TH2F("h3", "1p3/2", 20, 20,70, 50, -180,180); h3->SetXTitle("theta1 [deg]"); h3->SetYTitle("theta_k [deg]");
        
        
        Double_t theta1, theta2;
        Double_t xsec1p1,asym1p1;
        Double_t xsec1p3,asym1p3;
        Double_t xsec1d5,asym1d5;
        Double_t offplane;
        Double_t theta_k,phi_k;
        
        Ex00->SetBranchAddress("theta1", &theta1);
        Ex00->SetBranchAddress("theta2", &theta2);
        Ex00->SetBranchAddress("xsec1p1", &xsec1p1);
        Ex00->SetBranchAddress("xsec1p3", &xsec1p3);
        Ex00->SetBranchAddress("xsec1d5", &xsec1d5);
        Ex00->SetBranchAddress("asym1p1", &asym1p1);
        Ex00->SetBranchAddress("asym1p3", &asym1p3);
        Ex00->SetBranchAddress("asym1d5", &asym1d5);
        //Ex00->SetBranchAddress("offPlane", &offplane);
        Ex00->SetBranchAddress("theta_k", &theta_k);
        //Ex00->SetBranchAddress("phi_k", &phi_k);
        
        Int_t totalentry = Ex00->GetEntries();
        
        for( Int_t i = 0; i < totalentry; i++){
                Ex00->GetEntry(i);
                
                //if( abs(offplane) > 4) continue;
                
                Double_t theta_k_a = theta_k;
                //if( -90 <phi_k && phi_k <90) theta_k_a = theta_k;
                //if( -90 > phi_k || phi_k >90) theta_k_a = -1.*theta_k;
                 
                
                h1->Fill(theta1, theta_k_a, xsec1d5*(1+asym1d5));
                h2->Fill(theta1, theta_k_a, xsec1p1*(1+asym1p1));
                h3->Fill(theta1, theta_k_a, xsec1p3*(1+asym1p3));
                
                
        }
        
        cAy->cd(1);
        h1->Draw("colz");
        cAy->cd(2);
        h2->Draw("colz");
        cAy->cd(3);
        h3->Draw("colz");
        
}
