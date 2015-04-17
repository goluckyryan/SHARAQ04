void nyokiQCaliPar(){
        gROOT->Reset();
        gROOT->ProcessLine(".!date");
        gStyle->SetOptStat(0);

//========================================================

        char * rootfile = "P_test_all.root";
        
        TFile *f0 = new TFile (rootfile, "read"); 
        if( f0==0){
        printf("cannot load file: %s \n", rootfile);
        return;
        }
                
        TTree *tree = (TTree*)f0->Get("tree");
        printf("=====> /// %15s //// is loaded. Total #Entry: %10d \n", rootfile,  tree->GetEntries());
/**/
//======================================================== Browser or Canvas
        
        Int_t Div[2] = {1,1};  //x,y
        Int_t size[2] = {500,500}; //x,y
        TCanvas * cScript = new TCanvas("cScript", "cScript", 2000,0 , size[0]*Div[0], size[1]*Div[1]);
        cScript->Divide(Div[0],Div[1]);
   
//======================================================== analysis
/************** nyoki Q correction table *********************/

        Int_t nyokiID = 8;
        TString gate  = "";
        TString gate  = "pidusGate == 1";
        //TString gate  = "pidusGate == 1 && TMath::Abs(qS0D-1700)<200";
        Int_t nBin = 80;
        Int_t Range[2] = {-280, -200};
        Int_t QRange[2] = {1000, 4500};
        Int_t halfwidth = 100;
        Double_t charge_init = 2000; // 9 = 1400, 8 = 1500, 7= 1150, 6 = 1400, 5 = 1350
        
        TString filename; filename.Form("nyoki%02d.dat",nyokiID);
        
        //File * fout;
        //fout = fopen(filename, "w");
        
        std::ofstream fout (filename, std::ofstream::out);
        
        TString h1Title; h1Title.Form("qS1[%d]:tS1[%d] | ", nyokiID, nyokiID);
        h1Title += gate;
        TH2F * h1 = new TH2F("h1", h1Title, nBin, Range[0], Range[1], 100, QRange[0], QRange[1]);
        TH1F * g1 = new TH1F("g1",  "g1"  , nBin, Range[0], Range[1]);
        g1->SetLineColor(2);
        
        TString plot; plot.Form("qS1[%d]:tS1[%d]>>h1", nyokiID, nyokiID);
        
        cScript->cd(1);
        tree->Draw(plot, gate, "colz");
        

        for(Int_t bin = 1; bin <= nBin; bin ++){
                Double_t time = h1->GetBinCenter(bin);
                h1->ProjectionY("htemp", bin, bin);
                htemp->SetAxisRange(TMath::Max(charge_init-halfwidth, (Double_t)QRange[0]), TMath::Min(charge_init+halfwidth, (Double_t)QRange[1]));
                Int_t maxQbin = htemp->GetMaximumBin();
                Double_t charge = htemp->GetBinCenter(maxQbin);
                if( time < -220 && charge < charge_init ) continue;
                //if( time > -220 && TMath::Abs(charge-charge_init)>300 ) continue;
                g1->Fill(time, charge);
                charge_init = charge;
                
                //fprintf(fout, "%8.3f\t%8.3f\n", time, charge);
                fout << time << "\t" << charge << "\t#"<< bin <<"\n";
        }
        //fclose(fout);
        fout.close();
        g1->Draw("E same");
        
        printf("parameter file saved --> %s \n", filename.Data());
        
}
