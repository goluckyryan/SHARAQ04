{
        gROOT->Reset();
        gROOT->ProcessLine(".!date");
        gStyle->SetOptStat(0);

//========================================================
        //char * rootfile = "O_23F_timeoffset.root";
        char * rootfile = "O_23F_timeoffset_58.9_59.7.root";
        //char * rootfile = "O_25F_timeoffset_58.4_59.7.root";
        //char * rootfile = "O_pp_0605.root";
        //char * rootfile = "O_pp_0605_fine.root";
        //char * rootfile = "O_test.root";
        
        TFile *f0 = new TFile (rootfile, "read"); 
                
        TTree *tree = (TTree*)f0->Get("tree");
        gROOT->ProcessLine("listg tree");
        printf("=====> /// %15s //// is loaded. Total #Entry: %10d \n", rootfile,  tree->GetEntries());
/**/
//======================================================== Browser or Canvas
//        TBrowser B("Bscript",rootfile, 900,600); 	
        
        
        //tree->Process("Selector_Nyoki.C");
        //tree->Process("Selector_PostAna.C");
        //tree->Process("Selector_MWDC_S0D_charge.C");
        //tree->Process("Selector_Aux.C");

        
        Int_t Div[2] = {2,1};  //x,y
        Int_t size[2] = {500,500}; //x,y
        TCanvas * cScript = new TCanvas("cScript", "cScript", 2000,10 , size[0]*Div[0], size[1]*Div[1]);
        cScript->Divide(Div[0],Div[1]);
        
        
        TH2F* h2 = new TH2F("h2", rootfile, 11, -1.1, 1.1, 11, -1.1, 1.1);
   
        TCanvas * cScript2 = new TCanvas("cScript2", "cScript", 0,0 , 1500, 1500);
        cScript2->Divide(11,11);
        
//======================================================== load histogram
//	TFile *f1 = new TFile ("hist_23F_0112_new_smwdc_S1_config.root", "read");

//================ update.
//	TFile *f0 = new TFile ("23F_1224_nyoki_optics.root","update"); 
//	f0->Close();
/**/
//======================================================== analysis

TCut cut24o = "TMath::Abs(pidAOQ*8-24)<0.5";
TCut cut23o = "TMath::Abs(pidAOQ*8-23)<0.5";
TCut cut22o = "TMath::Abs(pidAOQ*8-22)<0.5";
TCut cut21o = "TMath::Abs(pidAOQ*8-21)<0.5";
TCut cut20o = "TMath::Abs(pidAOQ*8-20)<0.5";
TCut cut19o = "TMath::Abs(pidAOQ*8-19)<0.5";
TCut cut18o = "TMath::Abs(pidAOQ*8-18)<0.5";

TCut gateVertexZ = "TMath::Abs(vertexZ-10)<30";
TCut gateVertexZc = "TMath::Abs(vertexZ-160)<30";

TCut gate20  = cut20o + gateVertexZ;
TCut gate20c = cut20o + gateVertexZc;

TCut gate21  = cut21o + gateVertexZ;
TCut gate21c = cut21o + gateVertexZc;

TCut gate22  = cut22o + gateVertexZ;
TCut gate22c = cut22o + gateVertexZc;

TCut gate23  = cut23o + gateVertexZ;
TCut gate23c = cut23o + gateVertexZc;

TCut gate24  = cut24o + gateVertexZ;
TCut gate24c = cut24o + gateVertexZc;

Int_t mBin1=0, mPeak1=0;
Int_t mBin2=0, mPeak2=0;
Int_t mBin3=0, mPeak3=0;

cScript->cd(1);
tree->Draw("pidAOQ*8>>hA( 80,16,24)", gateVertexZ);
tree->Draw("pidAOQ*8>>hAg(80,16,24)", gateVertexZc, "same");

TString plotStr;
TString pmi, pmj;

TString getBinStr, getPeakStr, subStr;

TH1F * htemp = new TH1F();

cScript->cd(1);

Int_t maxPeak = 0;

Int_t nBin = 50;
Int_t range[2] = {-40,60};

Double_t binsize = (range[1] - range[0])*1./nBin;
TString hYTitle;
hYTitle.Form("count / %4.1f MeV", binsize);

for( Int_t i = -5; i <= 5; i++){
        for( Int_t j = -5; j <= 5; j++){
                Int_t  ni = TMath::Abs(i);
                Int_t  nj = TMath::Abs(j);
                
                if( i < 0 ) {
                        pmi = "m";
                }else if( i == 0){
                        pmi = "0";
                        ni = 0;
                }else{
                        pmi = "p";
                }
                
                if( j < 0 ) {
                        pmj = "m";
                }else if( j == 0){
                        pmj = "0";
                        nj = 0;
                }else{
                        pmj = "p";
                }
                
                //---------------
                plotStr.Form("Ex%1s%d[%d]>>h%1s%d%1s%d(%d, %d, %d)", pmi.Data(), ni , j+5, pmi.Data(), ni, pmj.Data(), nj, nBin, range[0], range[1]);
                printf("%30s    ", plotStr.Data());
                tree->Draw(plotStr, gate22);
                
                plotStr.Clear();
                plotStr.Form("Ex%1s%d[%d]>>h%1s%d%1s%dc(%d, %d, %d)", pmi.Data(), ni , j+5, pmi.Data(), ni, pmj.Data(), nj, nBin, range[0], range[1]);
                tree->Draw(plotStr, gate22c);
                
                subStr.Form("TH1F* p%1s%d%1s%d = new TH1F(*h%1s%d%1s%d - *h%1s%d%1s%dc); htemp = p%1s%d%1s%d;", pmi.Data(), ni, pmj.Data(), nj, pmi.Data(), ni, pmj.Data(), nj, pmi.Data(), ni, pmj.Data(), nj, pmi.Data(), ni, pmj.Data(), nj);
                gROOT->ProcessLine(subStr.Data());
                
                htemp->SetXTitle("Ex [MeV]");
                htemp->SetYTitle(hYTitle);
                mBin1 = htemp->GetMaximumBin();
                mPeak1 = htemp->GetBinContent(mBin1);
                if( mPeak1 > maxPeak) maxPeak = mPeak1;
                htemp = 0;

                //-------------
                plotStr.Form("Ex%1s%d[%d]>>g%1s%d%1s%d(%d, %d, %d)", pmi.Data(), ni , j+5, pmi.Data(), ni, pmj.Data(), nj, nBin, range[0], range[1]);
                printf("%30s    ", plotStr.Data());
                tree->Draw(plotStr, gate21);
                
                plotStr.Clear();
                plotStr.Form("Ex%1s%d[%d]>>g%1s%d%1s%dc(%d, %d, %d)", pmi.Data(), ni , j+5, pmi.Data(), ni, pmj.Data(), nj, nBin, range[0], range[1]);
                tree->Draw(plotStr, gate21c);
                
                subStr.Form("TH1F* q%1s%d%1s%d = new TH1F(*g%1s%d%1s%d - *g%1s%d%1s%dc); htemp = q%1s%d%1s%d;", pmi.Data(), ni, pmj.Data(), nj, pmi.Data(), ni, pmj.Data(), nj, pmi.Data(), ni, pmj.Data(), nj, pmi.Data(), ni, pmj.Data(), nj);
                gROOT->ProcessLine(subStr.Data());
                
                htemp->SetXTitle("Ex [MeV]");
                htemp->SetYTitle(hYTitle);
                mBin2 = htemp->GetMaximumBin();
                mPeak2 = htemp->GetBinContent(mBin2);
                if( mPeak2 > maxPeak) maxPeak = mPeak2;
                htemp = 0;
                
                //-------------
                plotStr.Form("Ex%1s%d[%d]>>k%1s%d%1s%d(%d, %d, %d)", pmi.Data(), ni , j+5, pmi.Data(), ni, pmj.Data(), nj, nBin, range[0], range[1]);
                printf("%30s    ", plotStr.Data());
                tree->Draw(plotStr, gate20);
                
                plotStr.Form("Ex%1s%d[%d]>>k%1s%d%1s%dc(%d, %d, %d)", pmi.Data(), ni , j+5, pmi.Data(), ni, pmj.Data(), nj, nBin, range[0], range[1]);
                tree->Draw(plotStr, gate20c);
                
                subStr.Form("TH1F* r%1s%d%1s%d = new TH1F(*k%1s%d%1s%d - *k%1s%d%1s%dc); htemp = r%1s%d%1s%d;", pmi.Data(), ni, pmj.Data(), nj, pmi.Data(), ni, pmj.Data(), nj, pmi.Data(), ni, pmj.Data(), nj, pmi.Data(), ni, pmj.Data(), nj);
                gROOT->ProcessLine(subStr.Data());
                
                htemp->SetXTitle("Ex [MeV]");
                htemp->SetYTitle(hYTitle);
                mBin3 = htemp->GetMaximumBin();
                mPeak3 = htemp->GetBinContent(mBin3);
                if( mPeak3 > maxPeak) maxPeak = mPeak3;
                htemp = 0;
                
                //-----------------------
                Int_t mPeak = mPeak1+ mPeak2+mPeak3;
        
                h2->Fill(2*i/10.,2*j/10. , mPeak); 
                printf("%2d, %2d : Peak:%3d \n", i, j,  mPeak);
        }
}

for( Int_t i = -5; i <= 5; i++){
        for( Int_t j = -5; j <= 5; j++){
                Int_t  ni = TMath::Abs(i);
                Int_t  nj = TMath::Abs(j);
                
                if( i < 0 ) {
                        pmi = "m";
                }else if( i == 0){
                        pmi = "0";
                        ni = 0;
                }else{
                        pmi = "p";
                }
                
                if( j < 0 ) {
                        pmj = "m";
                }else if( j == 0){
                        pmj = "0";
                        nj = 0;
                }else{
                        pmj = "p";
                }
                
                cScript2->cd(11*(10-(j+5))+ (i+5)+1);
                
                plotStr.Form("p%1s%d%1s%d->SetMaximum(%d); p%1s%d%1s%d->SetLineColor(2); p%1s%d%1s%d->Draw()", pmi.Data(), ni, pmj.Data(), nj, maxPeak+2, pmi.Data(), ni, pmj.Data(), nj, pmi.Data(), ni, pmj.Data(), nj);
                gROOT->ProcessLine(plotStr.Data());
                
                plotStr.Form("q%1s%d%1s%d->SetMaximum(%d); q%1s%d%1s%d->SetLineColor(8); htemp = q%1s%d%1s%d;", pmi.Data(), ni, pmj.Data(), nj, maxPeak+2, pmi.Data(), ni, pmj.Data(), nj, pmi.Data(), ni, pmj.Data(), nj);
                gROOT->ProcessLine(plotStr.Data());
                htemp->Draw("same");
                
                plotStr.Form("r%1s%d%1s%d->SetMaximum(%d); r%1s%d%1s%d->SetLineColor(4); htemp = r%1s%d%1s%d;", pmi.Data(), ni, pmj.Data(), nj, maxPeak+2, pmi.Data(), ni, pmj.Data(), nj, pmi.Data(), ni, pmj.Data(), nj);
                gROOT->ProcessLine(plotStr.Data());
                htemp->Draw("same");
                
                //if(i == 0 && j ==0){
                //        TLatex text;
                //        text.SetTextSizePixels(5000);
                //        text.SetNDC();
                //        text.SetTextColor(1);
                //        text.DrawText(0.2, 0.8, "0,0");
                //}
        }
}

cScript->cd(1);
h2->Draw("colz");

cScript->cd(2);
/**/

}




/*
TCut cut = "TMath::Finite(dcs0d.fX) && gate.Test(11) && TMath::Abs(vertex.fZ-10)<30 && TMath::Abs(tof_s1.fTiming-33.5)<1.5 && TMath::Abs(nyoki_zt.fCharge-8)<0.6";

        TCutG * o20 = new TCutG("o20", 6);
        o20->SetVarX("pid_s1.fAOQ");
        o20->SetVarY("nyoki_zt.fCharge");
        o20->SetPoint(0, 2.42, 8.27);
        o20->SetPoint(1, 2.42, 7.65);
        o20->SetPoint(2, 2.50, 7.20);
        o20->SetPoint(3, 2.56, 7.53);
        o20->SetPoint(4, 2.56, 8.24);
        o20->SetPoint(5, 2.49, 8.71);
        o20->SetPoint(6, 2.42, 8.27);
        
        
        tree->Draw("p2p_m500_m500.fSp2-13.26>>hm5m5(100,-40,60)", cut + o20);
        tree->Draw("p2p_m500_m400.fSp2-13.26>>hm5m4(100,-40,60)", cut + o20);
        tree->Draw("p2p_m500_m300.fSp2-13.26>>hm5m3(100,-40,60)", cut + o20);
        tree->Draw("p2p_m500_m200.fSp2-13.26>>hm5m2(100,-40,60)", cut + o20);
        tree->Draw("p2p_m500_m100.fSp2-13.26>>hm5m1(100,-40,60)", cut + o20);
        tree->Draw("p2p_m500_0000.fSp2-13.26>>hm500(100,-40,60)", cut + o20);
        tree->Draw("p2p_m500_p100.fSp2-13.26>>hm5p1(100,-40,60)", cut + o20);
        tree->Draw("p2p_m500_p200.fSp2-13.26>>hm5p2(100,-40,60)", cut + o20);
        tree->Draw("p2p_m500_p300.fSp2-13.26>>hm5p3(100,-40,60)", cut + o20);
        tree->Draw("p2p_m500_p400.fSp2-13.26>>hm5p4(100,-40,60)", cut + o20);
        tree->Draw("p2p_m500_p500.fSp2-13.26>>hm5p5(100,-40,60)", cut + o20);
                                                    
        tree->Draw("p2p_m400_m500.fSp2-13.26>>hm4m5(100,-40,60)", cut + o20);
        tree->Draw("p2p_m400_m400.fSp2-13.26>>hm4m4(100,-40,60)", cut + o20);
        tree->Draw("p2p_m400_m300.fSp2-13.26>>hm4m3(100,-40,60)", cut + o20);
        tree->Draw("p2p_m400_m200.fSp2-13.26>>hm4m2(100,-40,60)", cut + o20);
        tree->Draw("p2p_m400_m100.fSp2-13.26>>hm4m1(100,-40,60)", cut + o20);
        tree->Draw("p2p_m400_0000.fSp2-13.26>>hm400(100,-40,60)", cut + o20);
        tree->Draw("p2p_m400_p100.fSp2-13.26>>hm4p1(100,-40,60)", cut + o20);
        tree->Draw("p2p_m400_p200.fSp2-13.26>>hm4p2(100,-40,60)", cut + o20);
        tree->Draw("p2p_m400_p300.fSp2-13.26>>hm4p3(100,-40,60)", cut + o20);
        tree->Draw("p2p_m400_p400.fSp2-13.26>>hm4p4(100,-40,60)", cut + o20);
        tree->Draw("p2p_m400_p500.fSp2-13.26>>hm4p5(100,-40,60)", cut + o20);
                                                    
        tree->Draw("p2p_m300_m500.fSp2-13.26>>hm3m5(100,-40,60)", cut + o20);
        tree->Draw("p2p_m300_m400.fSp2-13.26>>hm3m4(100,-40,60)", cut + o20);
        tree->Draw("p2p_m300_m300.fSp2-13.26>>hm3m3(100,-40,60)", cut + o20);
        tree->Draw("p2p_m300_m200.fSp2-13.26>>hm3m2(100,-40,60)", cut + o20);
        tree->Draw("p2p_m300_m100.fSp2-13.26>>hm3m1(100,-40,60)", cut + o20);
        tree->Draw("p2p_m300_0000.fSp2-13.26>>hm300(100,-40,60)", cut + o20);
        tree->Draw("p2p_m300_p100.fSp2-13.26>>hm3p1(100,-40,60)", cut + o20);
        tree->Draw("p2p_m300_p200.fSp2-13.26>>hm3p2(100,-40,60)", cut + o20);
        tree->Draw("p2p_m300_p300.fSp2-13.26>>hm3p3(100,-40,60)", cut + o20);
        tree->Draw("p2p_m300_p400.fSp2-13.26>>hm3p4(100,-40,60)", cut + o20);
        tree->Draw("p2p_m300_p500.fSp2-13.26>>hm3p5(100,-40,60)", cut + o20);

        tree->Draw("p2p_m200_m500.fSp2-13.26>>hm2m5(100,-40,60)", cut + o20);
        tree->Draw("p2p_m200_m400.fSp2-13.26>>hm2m4(100,-40,60)", cut + o20);
        tree->Draw("p2p_m200_m300.fSp2-13.26>>hm2m3(100,-40,60)", cut + o20);
        tree->Draw("p2p_m200_m200.fSp2-13.26>>hm2m2(100,-40,60)", cut + o20);
        tree->Draw("p2p_m200_m100.fSp2-13.26>>hm2m1(100,-40,60)", cut + o20);
        tree->Draw("p2p_m200_0000.fSp2-13.26>>hm200(100,-40,60)", cut + o20);
        tree->Draw("p2p_m200_p100.fSp2-13.26>>hm2p1(100,-40,60)", cut + o20);
        tree->Draw("p2p_m200_p200.fSp2-13.26>>hm2p2(100,-40,60)", cut + o20);
        tree->Draw("p2p_m200_p300.fSp2-13.26>>hm2p3(100,-40,60)", cut + o20);
        tree->Draw("p2p_m200_p400.fSp2-13.26>>hm2p4(100,-40,60)", cut + o20);
        tree->Draw("p2p_m200_p500.fSp2-13.26>>hm2p5(100,-40,60)", cut + o20);
        
        tree->Draw("p2p_m100_m500.fSp2-13.26>>hm1m5(100,-40,60)", cut + o20);
        tree->Draw("p2p_m100_m400.fSp2-13.26>>hm1m4(100,-40,60)", cut + o20);
        tree->Draw("p2p_m100_m300.fSp2-13.26>>hm1m3(100,-40,60)", cut + o20);
        tree->Draw("p2p_m100_m200.fSp2-13.26>>hm1m2(100,-40,60)", cut + o20);
        tree->Draw("p2p_m100_m100.fSp2-13.26>>hm1m1(100,-40,60)", cut + o20);
        tree->Draw("p2p_m100_0000.fSp2-13.26>>hm100(100,-40,60)", cut + o20);
        tree->Draw("p2p_m100_p100.fSp2-13.26>>hm1p1(100,-40,60)", cut + o20);
        tree->Draw("p2p_m100_p200.fSp2-13.26>>hm1p2(100,-40,60)", cut + o20);
        tree->Draw("p2p_m100_p300.fSp2-13.26>>hm1p3(100,-40,60)", cut + o20);
        tree->Draw("p2p_m100_p400.fSp2-13.26>>hm1p4(100,-40,60)", cut + o20);
        tree->Draw("p2p_m100_p500.fSp2-13.26>>hm1p5(100,-40,60)", cut + o20);
        
        tree->Draw("p2p_0000_m500.fSp2-13.26>>h00m5(100,-40,60)", cut + o20);
        tree->Draw("p2p_0000_m400.fSp2-13.26>>h00m4(100,-40,60)", cut + o20);
        tree->Draw("p2p_0000_m300.fSp2-13.26>>h00m3(100,-40,60)", cut + o20);
        tree->Draw("p2p_0000_m200.fSp2-13.26>>h00m2(100,-40,60)", cut + o20);
        tree->Draw("p2p_0000_m100.fSp2-13.26>>h00m1(100,-40,60)", cut + o20);
        tree->Draw("p2p.fSp2-13.26>>h0000(100,-40,60)", cut + o20);
        tree->Draw("p2p_0000_p100.fSp2-13.26>>h00p1(100,-40,60)", cut + o20);
        tree->Draw("p2p_0000_p200.fSp2-13.26>>h00p2(100,-40,60)", cut + o20);
        tree->Draw("p2p_0000_p300.fSp2-13.26>>h00p3(100,-40,60)", cut + o20);
        tree->Draw("p2p_0000_p400.fSp2-13.26>>h00p4(100,-40,60)", cut + o20);
        tree->Draw("p2p_0000_p500.fSp2-13.26>>h00p5(100,-40,60)", cut + o20);
        
        tree->Draw("p2p_p100_m500.fSp2-13.26>>hp1m5(100,-40,60)", cut + o20);
        tree->Draw("p2p_p100_m400.fSp2-13.26>>hp1m4(100,-40,60)", cut + o20);
        tree->Draw("p2p_p100_m300.fSp2-13.26>>hp1m3(100,-40,60)", cut + o20);
        tree->Draw("p2p_p100_m200.fSp2-13.26>>hp1m2(100,-40,60)", cut + o20);
        tree->Draw("p2p_p100_m100.fSp2-13.26>>hp1m1(100,-40,60)", cut + o20);
        tree->Draw("p2p_p100_0000.fSp2-13.26>>hp100(100,-40,60)", cut + o20);
        tree->Draw("p2p_p100_p100.fSp2-13.26>>hp1p1(100,-40,60)", cut + o20);
        tree->Draw("p2p_p100_p200.fSp2-13.26>>hp1p2(100,-40,60)", cut + o20);
        tree->Draw("p2p_p100_p300.fSp2-13.26>>hp1p3(100,-40,60)", cut + o20);
        tree->Draw("p2p_p100_p400.fSp2-13.26>>hp1p4(100,-40,60)", cut + o20);
        tree->Draw("p2p_p100_p500.fSp2-13.26>>hp1p5(100,-40,60)", cut + o20);
        
        tree->Draw("p2p_p200_m500.fSp2-13.26>>hp2m5(100,-40,60)", cut + o20);
        tree->Draw("p2p_p200_m400.fSp2-13.26>>hp2m4(100,-40,60)", cut + o20);
        tree->Draw("p2p_p200_m300.fSp2-13.26>>hp2m3(100,-40,60)", cut + o20);
        tree->Draw("p2p_p200_m200.fSp2-13.26>>hp2m2(100,-40,60)", cut + o20);
        tree->Draw("p2p_p200_m100.fSp2-13.26>>hp2m1(100,-40,60)", cut + o20);
        tree->Draw("p2p_p200_0000.fSp2-13.26>>hp200(100,-40,60)", cut + o20);
        tree->Draw("p2p_p200_p100.fSp2-13.26>>hp2p1(100,-40,60)", cut + o20);
        tree->Draw("p2p_p200_p200.fSp2-13.26>>hp2p2(100,-40,60)", cut + o20);
        tree->Draw("p2p_p200_p300.fSp2-13.26>>hp2p3(100,-40,60)", cut + o20);
        tree->Draw("p2p_p200_p400.fSp2-13.26>>hp2p4(100,-40,60)", cut + o20);
        tree->Draw("p2p_p200_p500.fSp2-13.26>>hp2p5(100,-40,60)", cut + o20);
        
        tree->Draw("p2p_p300_m500.fSp2-13.26>>hp3m5(100,-40,60)", cut + o20);
        tree->Draw("p2p_p300_m400.fSp2-13.26>>hp3m4(100,-40,60)", cut + o20);
        tree->Draw("p2p_p300_m300.fSp2-13.26>>hp3m3(100,-40,60)", cut + o20);
        tree->Draw("p2p_p300_m200.fSp2-13.26>>hp3m2(100,-40,60)", cut + o20);
        tree->Draw("p2p_p300_m100.fSp2-13.26>>hp3m1(100,-40,60)", cut + o20);
        tree->Draw("p2p_p300_0000.fSp2-13.26>>hp300(100,-40,60)", cut + o20);
        tree->Draw("p2p_p300_p100.fSp2-13.26>>hp3p1(100,-40,60)", cut + o20);
        tree->Draw("p2p_p300_p200.fSp2-13.26>>hp3p2(100,-40,60)", cut + o20);
        tree->Draw("p2p_p300_p300.fSp2-13.26>>hp3p3(100,-40,60)", cut + o20);
        tree->Draw("p2p_p300_p400.fSp2-13.26>>hp3p4(100,-40,60)", cut + o20);
        tree->Draw("p2p_p300_p500.fSp2-13.26>>hp3p5(100,-40,60)", cut + o20);
        
        tree->Draw("p2p_p400_m500.fSp2-13.26>>hp4m5(100,-40,60)", cut + o20);
        tree->Draw("p2p_p400_m400.fSp2-13.26>>hp4m4(100,-40,60)", cut + o20);
        tree->Draw("p2p_p400_m300.fSp2-13.26>>hp4m3(100,-40,60)", cut + o20);
        tree->Draw("p2p_p400_m200.fSp2-13.26>>hp4m2(100,-40,60)", cut + o20);
        tree->Draw("p2p_p400_m100.fSp2-13.26>>hp4m1(100,-40,60)", cut + o20);
        tree->Draw("p2p_p400_0000.fSp2-13.26>>hp400(100,-40,60)", cut + o20);
        tree->Draw("p2p_p400_p100.fSp2-13.26>>hp4p1(100,-40,60)", cut + o20);
        tree->Draw("p2p_p400_p200.fSp2-13.26>>hp4p2(100,-40,60)", cut + o20);
        tree->Draw("p2p_p400_p300.fSp2-13.26>>hp4p3(100,-40,60)", cut + o20);
        tree->Draw("p2p_p400_p400.fSp2-13.26>>hp4p4(100,-40,60)", cut + o20);
        tree->Draw("p2p_p400_p500.fSp2-13.26>>hp4p5(100,-40,60)", cut + o20);
        
        tree->Draw("p2p_p500_m500.fSp2-13.26>>hp5m5(100,-40,60)", cut + o20);
        tree->Draw("p2p_p500_m400.fSp2-13.26>>hp5m4(100,-40,60)", cut + o20);
        tree->Draw("p2p_p500_m300.fSp2-13.26>>hp5m3(100,-40,60)", cut + o20);
        tree->Draw("p2p_p500_m200.fSp2-13.26>>hp5m2(100,-40,60)", cut + o20);
        tree->Draw("p2p_p500_m100.fSp2-13.26>>hp5m1(100,-40,60)", cut + o20);
        tree->Draw("p2p_p500_0000.fSp2-13.26>>hp500(100,-40,60)", cut + o20);
        tree->Draw("p2p_p500_p100.fSp2-13.26>>hp5p1(100,-40,60)", cut + o20);
        tree->Draw("p2p_p500_p200.fSp2-13.26>>hp5p2(100,-40,60)", cut + o20);
        tree->Draw("p2p_p500_p300.fSp2-13.26>>hp5p3(100,-40,60)", cut + o20);
        tree->Draw("p2p_p500_p400.fSp2-13.26>>hp5p4(100,-40,60)", cut + o20);
        tree->Draw("p2p_p500_p500.fSp2-13.26>>hp5p5(100,-40,60)", cut + o20);
        
/************** nyoki Q correction table *********************/
/*
        Int_t nyokiID = 6;
        TString gate  = "pidusGate == 1";
        Int_t nBin = 140;
        Int_t Range[2] = {-320, -180};
        
        TString filename; filename.Form("nyoki%0d.dat",nyokiID);
        
        File * fout;
        fout = fopen(filename, "w");
        
        
        TString h1Title; h1Title.Form("qS1[%d]:tS1[%d] | ", nyokiID, nyokiID);
        h1Title += gate;
        TH2F * h1 = new TH2F("h1", h1Title, nBin, Range[0], Range[1], 100, 1000, 4500);
        TH1F * g1 = new TH1F("g1",  "g1"  , nBin, Range[0], Range[1]);
        g1->SetLineColor(2);
        
        TString plot; plot.Form("qS1[%d]:tS1[%d]>>h1", nyokiID, nyokiID);
        
        cScript->cd(1);
        tree->Draw(plot, gate, "colz");
        
        Double_t charge_temp = 1400;
        for(Int_t bin = 1; bin <= nBin; bin ++){
                Double_t time = h1->GetBinCenter(bin);
                h1->ProjectionY("htemp", bin, bin);
                Int_t maxQbin = htemp->GetMaximumBin();
                Double_t charge = htemp->GetBinCenter(maxQbin);
                if( time < -220 && charge < charge_temp ) continue;
                //if( time > -220 && TMath::Abs(charge-charge_temp)>300 ) continue;
                g1->Fill(time, charge);
                charge_temp = charge;
                
                fprintf(fout, "%8.3f\t%8.3f\n", time, charge);
        }
        fclose(fout);
        g1->Draw("E same");
        
        
        
        
        
        

/************** Tpla Timing on coinReg *********************/
/*
        Int_t coinRegBit = 2;
        
        TString gate;
        gate.Form("coinReg & %d", coinRegBit);
        TString gateTitle;
        if( coinRegBit == 0 )  gateTitle = "F3 trigger";
        if( coinRegBit == 2 )  gateTitle = "FH9 trigger";
        if( coinRegBit == 4 )  gateTitle = "ppcoin trigger";
        if( coinRegBit == 8 )  gateTitle = "NDcoin trigger";
        if( coinRegBit == 16 ) gateTitle = "p-single trigger";
        if( coinRegBit == 32 ) gateTitle = "ND-single trigger";
        if( coinRegBit == 64 ) gateTitle = "ND-cosmic trigger";
        TString hTitle;
        
        
        cScript->cd(1);
        tree->Draw("tTplaLB:tTplaLF>>hLBLF(400, -250, -100, 400, -250, -100)", gate, "colz");
        hTitle = "Tpla-L : F vs B | " + gateTitle; 
        hLBLF->SetXTitle("TplaLF");
        hLBLF->SetYTitle("TplaLB");
        hLBLF->SetTitle(hTitle);

        cScript->cd(2);
        tree->Draw("tTplaRB:tTplaRF>>hRBRF(400, -250, -100, 400, -250, -100)", gate, "colz");
        hTitle = "Tpla-R : F vs B | " + gateTitle; 
        hRBRF->SetXTitle("TplaRF");
        hRBRF->SetYTitle("TplaRB");
        hRBRF->SetTitle(hTitle);
        
        cScript->cd(3);
        tree->Draw("tTplaRB:tTplaLF>>hRBLF(400, -250, -100, 400, -250, -100)", gate, "colz");
        hTitle = "tTplaRB:tTplaLF | " + gateTitle; 
        hRBLF->SetXTitle("TplaLF");
        hRBLF->SetYTitle("TplaRB");
        hRBLF->SetTitle(hTitle);
        
        cScript->cd(4);
        tree->Draw("tTplaRB:tTplaLB>>hRBLB(400, -250, -100, 400, -250, -100)", gate, "colz");
        hTitle = "B : L vs R | " + gateTitle; 
        hRBLB->SetXTitle("TplaLB");
        hRBLB->SetYTitle("TplaRB");
        hRBLB->SetTitle(hTitle);
        
        cScript->cd(5);
        tree->Draw("tTplaRF:tTplaLF>>hRFLF(400, -250, -100, 400, -250, -100)", gate, "colz");
        hTitle = "F : L vs R | " + gateTitle; 
        hRFLF->SetXTitle("TplaLF");
        hRFLF->SetYTitle("TplaRF");
        hRFLF->SetTitle(hTitle);
        
        cScript->cd(6);
        tree->Draw("tTplaRF:tTplaLB>>hRFLB(400, -250, -100, 400, -250, -100)", gate, "colz");
        hTitle = "tTplaRF:tTplaLB | " + gateTitle; 
        hRFLB->SetXTitle("TplaLB");
        hRFLB->SetYTitle("TplaRF");
        hRFLB->SetTitle(hTitle);
        


/************** Nyoki Q  ppcoin *********************/
/*
        cScript->cd(1);
        tree->Draw("qS1[4]*1.02-320:tofS1[4]>>h04b(300, 30, 40, 300, 100, 4500)", "gate==1 && coinReg[1] && TMath::Abs(nyokiT[4]+240)<30 && pidusGate==0", "colz");
        
        cScript->cd(2);
        tree->Draw("qS1[5]*1.00-25:tofS1[5]>>h05b(300, 30, 40, 300, 100, 4500)", "gate==1 && coinReg[1] && TMath::Abs(nyokiT[5]+240)<30 && pidusGate==0", "colz");

        cScript->cd(3);
        tree->Draw("qS1[6]*1.07-140:tofS1[6]>>h06b(300, 30, 40, 300, 100, 4500)", "gate==1 && coinReg[1] && TMath::Abs(nyokiT[6]+240)<30 && pidusGate==0", "colz");
        
        cScript->cd(4);
        tree->Draw("qS1[7]:tofS1[7]>>h07b(300, 30, 40, 300, 100, 4500)", "gate==1 && coinReg[1] && TMath::Abs(nyokiT[7]+240)<30 && pidusGate==0", "colz");
        
        cScript->cd(5);
        tree->Draw("qS1[8]*1.00-291:tofS1[8]>>h08b(300, 30, 40, 300, 100, 4500)", "gate==1 && coinReg[1] && TMath::Abs(nyokiT[8]+240)<30 && pidusGate==0", "colz");
        
        cScript->cd(6);
        tree->Draw("qS1[9]*0.78+64:tofS1[9]>>h09b(300, 30, 40, 300, 100, 4500)", "gate==1 && coinReg[1] && TMath::Abs(nyokiT[9]+240)<30 && pidusGate==0", "colz");
        
        cScript->cd(7);
        tree->Draw("qS1[10]*0.60-162:tofS1[10]>>h10b(300, 30, 40, 300, 100, 4500)", "gate==1 && coinReg[1] && TMath::Abs(nyokiT[10]+240)<30 && pidusGate==0", "colz");
        
        /*
        
        cScript->cd(8);
        tree->Draw("qS1[4]*1.02-371:nyokiT[4]>>h04(300, -270, -210, 300, 100, 4500)", "gate==1 && coinReg[1]", "colz");
        
        cScript->cd(9);
        tree->Draw("qS1[5]*1.00- 25:nyokiT[5]>>h05(300, -270, -210, 300, 100, 4500)", "gate==1 && coinReg[1]", "colz");

        cScript->cd(10);
        tree->Draw("qS1[6]*1.07-140:nyokiT[6]>>h06(300, -270, -210, 300, 100, 4500)", "gate==1 && coinReg[1]", "colz");
        
        cScript->cd(11);
        tree->Draw("qS1[7]*1.00 + 0:nyokiT[7]>>h07(300, -270, -210, 300, 100, 4500)", "gate==1 && coinReg[1]", "colz");
        
        cScript->cd(12);
        tree->Draw("qS1[8]*1.00-291:nyokiT[8]>>h08(300, -270, -210, 300, 100, 4500)", "gate==1 && coinReg[1]", "colz");
        
        cScript->cd(13);
        tree->Draw("qS1[9]*0.79+9:nyokiT[9]>>h09(300, -270, -210, 300, 100, 4500)", "gate==1 && coinReg[1]", "colz");
        
        cScript->cd(14);
        tree->Draw("qS1[10]*0.61-220:nyokiT[10]>>h10(300, -270, -210, 300, 100, 4500)", "gate==1 && coinReg[1]", "colz");
        
/************** S0D Q vs Nyoki Q  *********************/
/*
        cScript->cd(1);
        tree->Draw("qS0D:nyokiQ[8]>>h1a(200,200, 4500, 200, 200, 2500)", "gate==1 && runNum==23 && nyokiT[8]>-270 && nyokiT[8]<210 && pidusGate==0", "colz");
        h1a->SetTitle("run=23 && 23F && Crystal < 5 mm && nyokiTimeGate");
        h1a->SetXTitle("nyoki8.Charge");
        h1a->SetYTitle("S0D.Charge");

        cScript->cd(2);
        tree->Draw("qS0D:nyokiQ[8]>>h2a(200,200, 4500, 200, 200, 2500)", "gate==1 && runNum!=23 && nyokiT[8]>-270 && nyokiT[8]<210 && pidusGate==0", "colz");
        h2a->SetTitle("run=24 && 23F && Crystal < 5 mm && nyokiTimeGate");
        h2a->SetXTitle("nyoki8.Charge");
        h2a->SetYTitle("S0D.Charge");
        
        cScript->cd(4);
        tree->Draw("qS0D:nyokiQ[8]>>h1b(200,200, 4500, 200, 200, 2500)", "gate==1 && runNum==23 && nyokiT[8]>-270 && nyokiT[8]<210 && pidusGate==1", "colz");
        h1b->SetTitle("run=23 && 22O && Crystal < 5 mm && nyokiTimeGate");
        h1b->SetXTitle("nyoki8.Charge");
        h1b->SetYTitle("S0D.Charge");
        
        cScript->cd(5);
        tree->Draw("qS0D:nyokiQ[8]>>h2b(200,200, 4500, 200, 200, 2500)", "gate==1 && runNum!=23 && nyokiT[8]>-270 && nyokiT[8]<210 && pidusGate==1", "colz");
        h2b->SetTitle("run=24 && 22O && Crystal < 5 mm && nyokiTimeGate");
        h2b->SetXTitle("nyoki8.Charge");
        h2b->SetYTitle("S0D.Charge");
        
        cScript->cd(3);
        tree->Draw("qS0D:nyokiQ[8]>>hall(200,200, 4500, 200, 200, 2500)", "gate==1 && runNum>=23 && nyokiT[8]>-270 && nyokiT[8]<210", "colz");
        hall->SetTitle("run=23,24 && Crystal < 5 mm && nyokiTimeGate");
        hall->SetXTitle("nyoki8.Charge");
        hall->SetYTitle("S0D.Charge");
/************** S0D Q   *********************/
/*
        cScript->cd(1);
        tree->Draw("qS0D:tofS0D>>h1(500,-25,-15, 500,200, 2500)", "gate==1 && runNum==23", "colz");
        h1->SetXTitle("TOF(FH9-S0D)");
        h1->SetYTitle("S0D.Charge");
        h1->SetTitle("Crystal < 5 mm && run=23");
        
        cScript->cd(5);
        tree->Draw("qS0D:tofS0D>>h2(500,-25,-15, 500,200, 2500)", "gate==1 && runNum!=23", "colz");
        h2->SetXTitle("TOF(FH9-S0D)");
        h2->SetYTitle("S0D.Charge");
        h2->SetTitle("Crystal < 5 mm && run=24");
        
        cScript->cd(2);
        tree->Draw("qS0D:tofS0D>>h3(500,-25,-15, 500,200, 2500)", "gate==1 && runNum==23 && pidusGate==0", "colz");
        h3->SetXTitle("TOF(FH9-S0D)");
        h3->SetYTitle("S0D.Charge");
        h3->SetTitle("23F && Crystal < 5 mm && run=23");
        
        cScript->cd(6);
        tree->Draw("qS0D:tofS0D>>h4(500,-25,-15, 500,200, 2500)", "gate==1 && runNum!=23 && pidusGate==0", "colz");
        h4->SetXTitle("TOF(FH9-S0D)");
        h4->SetYTitle("S0D.Charge");
        h4->SetTitle("23F && Crystal < 5 mm && run=24");
        
        cScript->cd(3);
        tree->Draw("qS0D:tofS0D>>h5(500,-25,-15, 500,200, 2500)", "gate==1 && runNum==23 && pidusGate==1", "colz");
        h5->SetXTitle("TOF(FH9-S0D)");
        h5->SetYTitle("S0D.Charge");
        h5->SetTitle("22O && Crystal < 5 mm && run=23");
        
        cScript->cd(7);
        tree->Draw("qS0D:tofS0D>>h6(500,-25,-15, 500,200, 2500)", "gate==1 && runNum!=23 && pidusGate==1", "colz");
        h6->SetXTitle("TOF(FH9-S0D)");
        h6->SetYTitle("S0D.Charge");
        h6->SetTitle("22O && Crystal < 5 mm && run=24");
        
        cScript->cd(4);
        h3->ProjectionY()->Draw();
        h5->ProjectionY()->Draw("same");
        
        cScript->cd(8);
        h4->ProjectionY()->Draw();
        h6->ProjectionY()->Draw("same");
        
        
/************** Nyoki Q   *********************/
/*
        cScript->cd(1);
        tree->Draw("nyokiQ[7]:nyokiT[7]>>h1(200, -270, -210, 200, 30, 4000)","pidusGate==0 && gate==1 && runNum!=23", "colz");
        h1->SetXTitle("nyoki.Timing");
        h1->SetYTitle("nyoki.Charge");
        h1->SetTitle("nyoki.ID==7 && 23F && Crystal < 5 mm && run=24");
        cScript->cd(2);
        tree->Draw("nyokiQ[7]:tofS1[7]>>h2(200, 30, 40, 200, 30, 4000)",  "pidusGate==0 && gate==1 && runNum!=23 && nyokiT[7]>-270 && nyokiT[7]<-210", "colz");
        h2->SetXTitle("TOF(S0D-Nyoki-7)");
        h2->SetYTitle("nyoki.Charge");
        h2->SetTitle("nyoki.ID==7 && 23F && Crystal < 5 mm && run=24");
        cScript->cd(3);
        tree->Draw("nyokiT[7]:tofS0D>>h3(200, -50,  10, 200, -270, -210)","pidusGate==0 && gate==1 && runNum!=23", "colz");
        h3->SetXTitle("TOF(FH9-S0D)");
        h3->SetYTitle("nyoki.Timing");
        h3->SetTitle("nyoki.ID==7 && 23F && Crystal < 5 mm && run=24");
        
        
        cScript->cd(4);
        tree->Draw("nyokiQ[7]:nyokiT[7]>>h4(200, -270, -210, 200, 30, 4000)","pidusGate==1 && gate==1 && runNum!=23", "colz");
        h4->SetXTitle("nyoki.Timing");
        h4->SetYTitle("nyoki.Charge");
        h4->SetTitle("nyoki.ID==7 && 22O && Crystal < 5 mm && run=24");
        cScript->cd(5);
        tree->Draw("nyokiQ[7]:tofS1[7]>>h5(200, 30, 40, 200, 30, 4000)",     "pidusGate==1 && gate==1 && runNum!=23 && nyokiT[7]>-270 && nyokiT[7]<-210", "colz");
        h5->SetXTitle("TOF(S0D-Nyoki-7)");
        h5->SetYTitle("nyoki.Charge");
        h5->SetTitle("nyoki.ID==7 && 22O && Crystal < 5 mm && run=24");
        cScript->cd(6);
        tree->Draw("nyokiT[7]:tofS0D>>h6(200, -50, 10, 200, -270, -210)",    "pidusGate==1 && gate==1 && runNum!=23", "colz");
        h6->SetXTitle("TOF(FH9-S0D)");
        h6->SetYTitle("nyoki.Timing");
        h6->SetTitle("nyoki.ID==7 && 23F && Crystal < 5 mm && run=24");
        
/************** Nyoki TOF(S0D-Hodo)    *********************/
/*
        tree->Draw("tof_D1.fTiming>>h1(150,33,37)", "tof_D1.fID==7 && gate.Test(0) && gate.Test(12)", ""    ); h1->SetLineColor(2); h1->Draw();
        tree->Draw("tof_D1.fTiming>>h2(150,33,37)", "tof_D1.fID==7 && gate.Test(1) && gate.Test(12)", "same"); h2->SetLineColor(2); h2->Draw("same");
        tree->Draw("tof_D1.fTiming>>h3(150,33,37)", "tof_D1.fID==8 && gate.Test(0) && gate.Test(12)", "same");
        tree->Draw("tof_D1.fTiming>>h4(150,33,37)", "tof_D1.fID==8 && gate.Test(1) && gate.Test(12)", "same");

/************** Nyoki Q  23F  *********************/
/*
        cScript->cd(1);
        tree->Draw("tof_D1.fCharge>>h1(150, 2000, 4500)", "tof_D1.fID==7 && gate.Test(0) && gate.Test(12) && nyoki.fTiming >-270 && nyoki.fTiming<-210 & Sum$(nyoki.fID==7 || nyoki.fID==8)==2", ""    ); 
        h1->SetLineColor(2); h1->Draw();
        tree->Draw("tof_D1.fCharge>>h2(150, 2000, 4500)", "tof_D1.fID==7 && gate.Test(1) && gate.Test(12) && nyoki.fTiming >-270 && nyoki.fTiming<-210 & Sum$(nyoki.fID==7 || nyoki.fID==8)==2", "same"); 
        h2->SetLineColor(6); h2->Draw("same");
        tree->Draw("tof_D1.fCharge*1.1914-1302.5>>h3(150, 2000, 4500)", "tof_D1.fID==8 && gate.Test(0) && gate.Test(12) && nyoki.fTiming >-270 && nyoki.fTiming<-210 & Sum$(nyoki.fID==7 || nyoki.fID==8)==2", "same"); 
        h3->SetLineColor(4); h3->Draw("same");
        tree->Draw("tof_D1.fCharge*1.1914-1302.5>>h4(150, 2000, 4500)", "tof_D1.fID==8 && gate.Test(1) && gate.Test(12) && nyoki.fTiming >-270 && nyoki.fTiming<-210 & Sum$(nyoki.fID==7 || nyoki.fID==8)==2", "same"); 
        h4->SetLineColor(7); h4->Draw("same");
        tree->Draw("tof_D1.fCharge>>h5(150, 2000, 4500)", "tof_D1.fID==7 && gate.Test(3) && gate.Test(12) && nyoki.fTiming >-270 && nyoki.fTiming<-210 & Sum$(nyoki.fID==7 || nyoki.fID==8)==2", "same"); 
        //h5->SetLineColor(3); h5->Scale(40); h5->Draw("same");
        //tree->Draw("tof_D1.fCharge*1.1914-1302.5>>h6(150, 2000, 4500)", "tof_D1.fID==8 && gate.Test(3) && gate.Test(12) && nyoki.fTiming >-270 && nyoki.fTiming<-210 & Sum$(nyoki.fID==7 || nyoki.fID==8)==2", "same"); 
        //h6->SetLineColor(9); h6->Scale(40);  h6->Draw("same");

/************** Nyoki Q  23F  *********************/
/*
        TCut cut = "gate.Test(12) && nyoki.fTiming>-270 && nyoki.fTiming<-210 ";
        
        cScript->cd(1);        tree->Draw("tof_D1.fCharge:tof_D1.fTiming>>h5(100, 30, 40, 100, 0, 4000)", cut + "tof_D1.fID==5", "colz");
        cScript->cd(2);        tree->Draw("tof_D1.fCharge:tof_D1.fTiming>>h6(100, 30, 40, 100, 0, 4000)", cut + "tof_D1.fID==6", "colz");
        cScript->cd(3);        tree->Draw("tof_D1.fCharge:tof_D1.fTiming>>h7(100, 30, 40, 100, 0, 4000)", cut + "tof_D1.fID==7", "colz");
        cScript->cd(4);        tree->Draw("tof_D1.fCharge:tof_D1.fTiming>>h8(100, 30, 40, 100, 0, 4000)", cut + "tof_D1.fID==8", "colz");
        cScript->cd(5);        tree->Draw("tof_D1.fCharge:tof_D1.fTiming>>h9(100, 30, 40, 100, 0, 4000)", cut + "tof_D1.fID==9", "colz");
        
        
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

//tree->Scan("smwdc_S1.fTrack.fX:smwdc_S1.IsGood():smwdc_S1.fNPlaneValid", "smwdc_S1.GetWireIDAdopted(0)-smwdc_S1.GetWireIDAdopted(1) == 1");

//-------------- Check input
//tree->Scan("smwdc_S1_x1.fID:smwdc_S1_x1.fCharge:smwdc_S1_x1.fDriftLength:smwdc_S1_x2.fID:smwdc_S1_x2.fCharge:smwdc_S1_x2.fDriftLength:smwdc_S1_u1.fID:smwdc_S1_u1.fCharge:smwdc_S1_u1.fDriftLength:smwdc_S1_u2.fID:smwdc_S1_u2.fCharge:smwdc_S1_u2.fDriftLength:smwdc_S1_v1.fID:smwdc_S1_v1.fCharge:smwdc_S1_v1.fDriftLength:smwdc_S1_v2.fID:smwdc_S1_v2.fCharge:smwdc_S1_v2.fDriftLength:smwdc_S1.fWireIDAdopted:smwdc_S1.fLRAdopted:smwdc_S1.fNPlaneValid:smwdc_S1.fTrack.fX:smwdc_S1.fTrack.fA:smwdc_S1.fTrack.fY:smwdc_S1.fTrack.fB:smwdc_S1.IsGood()", "", "", 100000, 80);

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
        
        TString gate = "gate.Test(0)";//"gate.Test(0)";
        
        //haha.cd(1); 
        //tree->Draw( "smwdc_S1.GetSigma(1)*1000>>h1(200,0,10)", gate, ""    , nEvent); h1->SetLineColor(2);
        //tree2->Draw("smwdc_S1.GetSigma(1)*1000>>h2(200,0,10)", gate, "same", nEvent);
        
//        tree->Draw("smwdc_S1_x1.fCharge>>h1(200,0,1500)", gate, "", 10000);
//        tree2->Draw("smwdc_S1_x1.fCharge>>h2(200,0,1500)", gate, "same", 10000);
        
        
        haha.cd(1); tree->Draw("smwdc_S1.fTrack.fY:smwdc_S1.fTrack.fX>>h1(400,-500, 500, 200,  -150,  150)", gate, "colz");
        haha.cd(2); tree->Draw("smwdc_S1.fTrack.fA:smwdc_S1.fTrack.fX>>h2(400,-500, 500, 200,    -0.5,    0.5)", gate, "colz");
        haha.cd(3); tree->Draw("smwdc_S1.fTrack.fB:smwdc_S1.fTrack.fY>>h3(200,-150, 150, 200,    -0.25,   0.25)", gate, "colz");
        haha.cd(4); tree->Draw("smwdc_S1.fTrack.fB:smwdc_S1.fTrack.fA>>h4(200,  -0.5,   0.5, 200,    -0.25,    0.25)", gate, "colz");
/**/

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
