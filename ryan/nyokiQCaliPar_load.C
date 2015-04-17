#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <cstring>

using namespace std;

void nyokiQCaliPar_load(){
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
        
        Int_t Div[2] = {2,2};  //x,y
        Int_t size[2] = {450,450}; //x,y
        TCanvas * cNyokiQCorr = new TCanvas("cNyokiQCorr", "cNyokiQCorr", 2000,0 , size[0]*Div[0], size[1]*Div[1]);
        cNyokiQCorr->Divide(Div[0],Div[1]);
   
//======================================================== analysis

        Int_t nyokiID = 0;
        Int_t nBin = 200;
        Int_t nQBin = 200;
        Int_t QRange[2] = {100, 4500};
        Int_t Range[2] = {-280, -210};
        Double_t newQRange[2] = {0.0, 1.6};
        
        Double_t pedestal = 240;
        
        if( nyokiID ==  0 ) pedestal = 150;
        if( nyokiID ==  1 ) pedestal = 200;
        if( nyokiID ==  2 ) pedestal = 300;
        if( nyokiID ==  3 ) pedestal = 240;
        if( nyokiID ==  4 ) pedestal = 220;
        if( nyokiID ==  5 ) pedestal = 40;
        if( nyokiID ==  6 ) pedestal = 110;
        if( nyokiID ==  7 ) pedestal = 40;
        if( nyokiID ==  8 ) pedestal = 320;
        if( nyokiID ==  9 ) pedestal = 70;
        if( nyokiID == 10 ) pedestal = 70;

        TString filename; filename.Form("prm/nyoki/correction/nyoki%02d.dat",nyokiID);        
        ifstream fin;
        fin.open(filename);
                
        printf("parameter file loaded --> %s \n", filename.Data());
        
        TString h1Title; h1Title.Form("qS1[%d]:tS1[%d] pedestal:%4.0f", nyokiID, nyokiID, pedestal);
        TH2F * h1 = new TH2F("h1", h1Title, nBin, Range[0], Range[1], nQBin, QRange[0], QRange[1]);
        TH2F * k1 = new TH2F("k1", h1Title, nBin, Range[0], Range[1], nQBin, newQRange[0], newQRange[1]);
        TH1F * g1 = new TH1F("g1", h1Title, nBin, Range[0], Range[1]);
        g1->SetLineColor(2);
        
        
        Double_t* charge, *time;
        
        //___________________________ Load paramter
        Int_t lineNum = 0;
        string line;
        Int_t numberPoint = 0;
        Int_t lineNumEff = 0;
        
        do{
                lineNum ++;
                getline(fin, line); // read fin and store in line
                
                if( line.length() < 1) continue;                
                //printf("%3d, %3d  %s ", lineNum, line.length(),line.c_str());

                if( lineNum == 1) {
                        numberPoint = atoi(line.c_str());
                        printf("\n ------- number of points claim = %d \n", numberPoint);
                        charge = new Double_t[numberPoint];
                        time = new Double_t[numberPoint];
                        continue;
                }
                
                lineNumEff ++;
                time[lineNum-2] = atof(line.substr(0,6).c_str());
                charge[lineNum-2] = atof(line.substr(7,12).c_str());
                                
                //printf("(%3d, %6.1f ,%6.1f)\n", lineNum-2, time[lineNum-2], charge[lineNum-2]);
                
                g1->Fill( time[lineNum-2], charge[lineNum-2]);
                

        }while(! fin.eof());
        fin.close();
        printf("..... done loading parameters, number of data loaded: %d\n", lineNumEff);
        
        //___________________________ Load the nyokiQ and apply correction
        printf("..... start loading and correcting nyokiQ, pedestal: %6.1f\n", pedestal);

        Double_t hoge_Q[14], hoge_T[14];
        tree->SetBranchStatus("*",0);
        tree->SetBranchStatus("qS1",1);
        tree->SetBranchStatus("tS1",1);
        
        tree->SetBranchAddress("qS1", &hoge_Q);
        tree->SetBranchAddress("tS1", &hoge_T);
        
        Double_t minQ = 1000;
        
        for(Int_t eventID = 0; eventID < tree->GetEntries(); eventID ++){
                tree->GetEntry(eventID, 0);
                
                Double_t oldQ = hoge_Q[nyokiID];
                Double_t oldT = hoge_T[nyokiID];
                
                if( TMath::IsNaN(oldT) ) continue;
                if( oldT < Range[0] || oldT>Range[1]) continue;
                
                if( oldQ < minQ ) minQ = oldQ;
                
                h1->Fill(oldT, oldQ);
                
                //__________ Find correction parameter
                Int_t index = 0;
                Double_t cQ1, cQ2, cT1, cT2;
                do{
                        cQ1 = charge[index];
                        cQ2 = charge[index+1];
                        cT1 = time[index];
                        cT2 = time[index+1];
                        
                        if( oldT == time[index] ) {
                                cT2 = cT1+1;
                                cQ2 = cQ1;
                        }
                        
                        index ++;
                }while(oldT >= time[index]);
                Double_t corrpar = cQ1 + (cQ2-cQ1)/(cT2-cT1)*(oldT-cT1);
                
                //printf("oldT:%6.1f, (%6.1f, %6.1f),(%6.1f, %6.1f)\n", oldT, cT1, cQ1, cT2, cQ2);
                
                Double_t newQ = (oldQ - pedestal )/corrpar;
                
                k1->Fill(oldT, newQ);
                
        }
        printf("..... done loading and correcting nyokiQ, minQ : %6.2f\n", minQ);

        //___________________________ Draw nyokiQ and parameter
        cNyokiQCorr->cd(1);
        h1->Draw("colz");
        g1->Draw("E same");
        //cNyokiQCorr_1->SetLogz(1);
        

        cNyokiQCorr->cd(3);
        k1->Draw("colz");
        cNyokiQCorr_3->SetLogz(1);
        
        cNyokiQCorr->cd(4);
        k1->ProjectionY()->Draw("");
        
        cNyokiQCorr->cd(1);
        


}
