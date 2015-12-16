{
        gROOT->Reset();
        gROOT->ProcessLine(".!date");
        gStyle->SetOptStat(0);

//========================================================
        //char * rootfile = "O_25F_timeoffset_58.9_59.7.root";
        //char * rootfile = "O_25F_timeoffset_58.7_59.5.root";
        //char * rootfile = "O_25F_timeoffset_58.7_59.5_315.38_noppac.root";
        char * rootfile = "O_25F_timeoffset_58.7_59.5_315.23.root";
        
        TFile *f0 = new TFile (rootfile, "read"); TTree *tree = (TTree*)f0->Get("tree");
        gROOT->ProcessLine("listg tree");
        printf("=====> /// %15s //// is loaded. Total #Entry: %10d \n", rootfile,  tree->GetEntries());
        
/**/
//======================================================== Browser or Canvas

        Int_t Div[2] = {2,1};  //x,y
        Int_t size[2] = {500,500}; //x,y
        TCanvas * cScript = new TCanvas("cScript", "cScript", 2000,10 , size[0]*Div[0], size[1]*Div[1]);
        cScript->Divide(Div[0],Div[1]);
        
        TH2F* h2 = new TH2F("h2", rootfile, 11, -1.1, 1.1, 11, -1.1, 1.1);
   
        TCanvas * cScript2 = new TCanvas("cScript2", "cScript", 0,0 , 1500, 1500);
        cScript2->Divide(11,11);
        
//======================================================== analysis

TCut cut24o = "TMath::Abs(pidAOQ*8-24)<0.5";
TCut cut23o = "TMath::Abs(pidAOQ*8-23)<0.5";
TCut cut22o = "TMath::Abs(pidAOQ*8-22)<0.5";
TCut cut21o = "TMath::Abs(pidAOQ*8-21)<0.5";

TCut gateVertexZ = "TMath::Abs(pidZ-8)<0.6 && TMath::Abs(vertexZ-10)<30";
TCut gateVertexZc = "TMath::Abs(pidZ-8)<0.6 && TMath::Abs(vertexZ-165)<50";

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

TString plotStr;
TString pmi, pmj;

TString getBinStr, getPeakStr, subStr;

TH1F * htemp = new TH1F();

cScript->cd(1);

Int_t maxPeak = 0;

Int_t nBin = 40;
Int_t range[2] = {-140,60};

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
                tree->Draw(plotStr, gate24);
                
                plotStr.Clear();
                plotStr.Form("Ex%1s%d[%d]>>h%1s%d%1s%dc(%d, %d, %d)", pmi.Data(), ni , j+5, pmi.Data(), ni, pmj.Data(), nj, nBin, range[0], range[1]);
                tree->Draw(plotStr, gate24c);
                
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
                tree->Draw(plotStr, gate23);
                
                plotStr.Clear();
                plotStr.Form("Ex%1s%d[%d]>>g%1s%d%1s%dc(%d, %d, %d)", pmi.Data(), ni , j+5, pmi.Data(), ni, pmj.Data(), nj, nBin, range[0], range[1]);
                tree->Draw(plotStr, gate23c);
                
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
                tree->Draw(plotStr, gate22);
                
                plotStr.Form("Ex%1s%d[%d]>>k%1s%d%1s%dc(%d, %d, %d)", pmi.Data(), ni , j+5, pmi.Data(), ni, pmj.Data(), nj, nBin, range[0], range[1]);
                tree->Draw(plotStr, gate22c);
                
                subStr.Form("TH1F* r%1s%d%1s%d = new TH1F(*k%1s%d%1s%d - *k%1s%d%1s%dc); htemp = r%1s%d%1s%d;", pmi.Data(), ni, pmj.Data(), nj, pmi.Data(), ni, pmj.Data(), nj, pmi.Data(), ni, pmj.Data(), nj, pmi.Data(), ni, pmj.Data(), nj);
                gROOT->ProcessLine(subStr.Data());
                
                htemp->SetXTitle("Ex [MeV]");
                htemp->SetYTitle(hYTitle);
                mBin3 = htemp->GetMaximumBin();
                mPeak3 = htemp->GetBinContent(mBin3);
                if( mPeak3 > maxPeak) maxPeak = mPeak3;
                htemp = 0;
                
                //-----------------------
                Int_t mPeak = mPeak1 ;//+ mPeak2+mPeak3;
        
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
tree->Draw("pidAOQ*8>>hA( 80,18,26)", gateVertexZ);
tree->Draw("pidAOQ*8>>hAc(80,18,26)", gateVertexZc, "same");

TH1F* hAs = new TH1F(*hA - *hAc);

//hAs->Draw();

tree->Draw("pidZ:pidAOQ>>hPID(60, 2.2, 3.2, 60, 4, 10)", "", "colz");

/**/

}
