{

        gROOT->Reset();
        gROOT->ProcessLine(".!date");
        //gStyle->SetOptStat(0);

//=================================================================================
        TFile *f1 = new TFile ("23F_run23_nyokiQ_cali.root"); 
        //TFile *f1 = new TFile ("23F_optics.root"); 

        Int_t nyokiID = 7;

        Double_t Qgain=1, Qoffset=0;
        
        
        const Double_t L_F3FH9 = 74075.; 
        const Double_t DbeamZ = 0.;
        const Double_t L_FH9TGT = 12020.-1155. + DbeamZ;

        /*switch(nyokiID){
        case 0:  Qgain = 0.17; Qoffset = 522; break;
        case 1:  Qgain = 0.48; Qoffset = 319; break;
        case 2:  Qgain = 0.33; Qoffset = 429; break;
        case 3:  Qgain = 0.36; Qoffset = 443; break;
        case 4:  Qgain = 0.34; Qoffset = 441; break;
        case 5:  Qgain = 0.34; Qoffset = 566; break;
        case 6:  Qgain = 0.36; Qoffset = 486; break;
        case 7:  Qgain = 0.38; Qoffset = 581; break;
        case 8:  Qgain = 0.36; Qoffset = 439; break;
        case 9:  Qgain = 0.35; Qoffset = 577; break;
        case 10: Qgain = 0.22; Qoffset = 585; break;
        }*/

        //	printf("Qgain:%4.2f, Qoffset:%6.0f \n", Qgain, Qoffset);

//=================================================================================
        TClonesArray *hoge_FH9, *hoge_V775, *hoge_nyoki, *hoge_tofD1, *hoge_mwdc;
        art::TGateArray * gate;
        art::TCoinRegData *coinReg;
        TTree *tree = (TTree*)f1->Get("tree");
        Int_t totnumEntry = tree->GetEntries();

        printf(" --------------------- total entry = %d \n", totnumEntry);
        tree->SetBranchStatus("*",0);
        tree->SetBranchStatus("gate",1);
        //tree->SetBranchStatus("coinReg",1);
        tree->SetBranchStatus("plaV775",1);
        //tree->SetBranchStatus("plaV1190_FH9",1);
        tree->SetBranchStatus("nyoki",1);
        //tree->SetBranchStatus("tof_D1",1);

        //tree->SetBranchAddress("coinReg",&coinReg); 
        tree->SetBranchAddress("gate",&gate); 
        tree->SetBranchAddress("plaV775",&hoge_V775);
        //tree->SetBranchAddress("plaV1190_FH9",&hoge_FH9); 
        tree->SetBranchAddress("nyoki",&hoge_nyoki); 
        //tree->SetBranchAddress("tof_D1",&hoge_tofD1); 
        //tree->SetBranchAddress("smwdc_S1",&hoge_mwdc); 

//=================================================================================
        Int_t Div[2] ={4,3};
        Int_t size = 300;
        TCanvas * cTiming= new TCanvas("cTiming", "cTiming", 2000, 0,Div[0]*size,Div[1]*size);
        cTiming->Divide(Div[0],Div[1]);
        
        TH1F* hF3time = new TH1F("hF3time", "F3 timing", 300,  0, 200);
        TH1F* hFH9time = new TH1F("hFH9time", "FH9 timing", 300, -210, -190);
        TH2F* hF3_FH9 = new TH2F("hF3_FH9", "", 300, -210, -190, 300, 40, 160);
        TH1F* htofUS = new TH1F("htofUS", "TOF(F3-FH9)", 300, -350, -270);        
        
        TH1F* htgttime = new TH1F("htgttime", "tgt timing", 300, -260, -230);
        TH1F* hS0Dtime = new TH1F("hS0Dtime", "S0D timing", 300, -285, -255);
        TH2F* htgt_S0D = new TH2F("htgt_S0D", "", 300, -285, -255, 300, -260, -230);
        TH1F* htofDS = new TH1F("htofDS", "TOF(tgt-S0D)", 300, -26, -16);
        
        TH1F* hNyoki07timing = new TH1F("hNyoki07timing", "Nyoki Timing - 07", 300, -250, -220);
        TH1F* hNyoki08timing = new TH1F("hNyoki08timing", "Nyoki Timing - 08", 300, -250, -220);
        TH1F* hNyoki06timing = new TH1F("hNyoki06timing", "Nyoki Timing - 06", 300, -250, -220);

        TH2F* hS0D_n7 = new TH2F("hS0D_n7", "", 300, -250, -220, 300, -285, -255);


        Double_t QS0D = TMath::QuietNaN();
        Double_t tFH9 = TMath::QuietNaN();
        Double_t tS0D = TMath::QuietNaN();
        Double_t t_tgt = TMath::QuietNaN();
        Double_t tF3  = TMath::QuietNaN();
        Double_t nyokiQ[14];
        Double_t nyokiT[14];

//=================================================================================
        for( Int_t eventID = 0; eventID< totnumEntry; eventID ++){
                tree->GetEntry(eventID,0); 

                //if( coinReg->Test(0) != 1) continue;
                //if ( gate->Test(6) != 1) continue; 
                //if ( gate->Test(8) == 1) continue; 
                //if ( gate->Test(0) != 1) continue; 
                if ( gate->Test(15) != 1) continue;
                
                //intialization
                QS0D = TMath::QuietNaN();
                tFH9 = TMath::QuietNaN();
                tS0D = TMath::QuietNaN();
                t_tgt = TMath::QuietNaN();
                tF3  = TMath::QuietNaN();
                
                for( Int_t i = 0; i < 14; i++){ 
                        nyokiQ[i] = TMath::QuietNaN();
                        nyokiT[i] = TMath::QuietNaN();
                }
                
                //__________________________________________________ get timing & charge of V775
                Int_t nHit = hoge_V775->GetEntriesFast();
                for(Int_t p = 0; p < nHit; p++){
                        art::TTwoSidedPlasticData* data1 = (art::TTwoSidedPlasticData*)hoge_V775->At(p) ;
                        Int_t ID = data1->GetID() ;
                        if( ID == 4 ) {
                                QS0D    = data1->GetCharge();
                                tS0D    = data1->GetTiming();
                        }else if(ID == 3){
                                tFH9    = data1->GetTiming();
                        }else if(ID == 2){
                                tF3 = data1->GetTiming();
                        }else{
                                continue;
                        }
                }
                if( TMath::IsNaN(tFH9)) continue;
                if( TMath::IsNaN(tF3)) continue;
                if( TMath::IsNaN(tS0D)) continue;
                
                hF3time->Fill(tF3);
                hFH9time->Fill(tFH9);
                
                hF3_FH9->Fill(tFH9, tF3);
                
                htofUS->Fill(tFH9-tF3);
                
                t_tgt = tFH9 + (tFH9-tF3)*L_FH9TGT/L_F3FH9;
                
                htgttime->Fill(t_tgt);
                
                hS0Dtime->Fill(tS0D);
                
                htgt_S0D->Fill(tS0D, t_tgt);
                
                htofDS->Fill( tS0D - t_tgt);

                //__________________________________________________ get timing & charge of Nyoki
                Int_t nHit = hoge_nyoki->GetEntriesFast();
                for(Int_t p = 0; p < nHit; p++){
                        art::TTimingChargeData* data = (art::TTimingChargeData*)hoge_nyoki->At(p) ;
                        Int_t nyokiID = data->GetID();
                        nyokiQ[nyokiID] = data->GetCharge();
                        nyokiT[nyokiID] = data->GetTiming();
                        
                }
                
                hNyoki06timing->Fill(nyokiT[6]);
                hNyoki07timing->Fill(nyokiT[7]);
                hNyoki08timing->Fill(nyokiT[8]);
                
                hS0D_n7->Fill(nyokiT[7], tS0D);
                        
                /*        
                //__________________________________________________ get charge of FH9 v1190
                Int_t nHit = hoge_FH9->GetEntriesFast();
                //if ( nHit >=2) continue;
                for(Int_t p = 0; p < nHit; p++){
                        art::TTwoSidedPlasticData* data1 = (art::TTwoSidedPlasticData*)hoge_FH9->At(p) ;
                        Double_t QFH9 = data1->GetCharge();
                        hFH9S0DQ->Fill( QS0D, QFH9);
                        //printf("nyokiQ:%4.0f, FH9 Q:%4.0f\n", nyokiQ, data1->GetCharge());		
                        hFH9NyokiQ->Fill(QFH9,  nyokiQ);
                        hFH9SlewV775->Fill(tFH9, QFH9);
                        hFH9PID->Fill(tFH9-tF3, QFH9);
                }
                */

        }

//=================================================================================
        cTiming->cd(1);
        hF3time->Draw();

        cTiming->cd(2);
        hFH9time->Draw();

        cTiming->cd(3);
        hF3_FH9->Draw("colz");
        
        cTiming->cd(4);
        htofUS->Draw();
        
        cTiming->cd(5);
        htgttime->Draw();

        cTiming->cd(6);
        hS0Dtime->Draw();

        cTiming->cd(7);
        htgt_S0D->Draw("colz");
        
        cTiming->cd(8);
        htofDS->Draw("");
        
        cTiming->cd(9);
        hNyoki06timing->Draw("");
        
        cTiming->cd(10);
        hNyoki07timing->Draw("");
        
        cTiming->cd(11);
        hNyoki08timing->Draw("");
        
        cTiming->cd(12);
        hS0D_n7->Draw("colz");
}
