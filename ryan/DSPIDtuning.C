#include <TBenchmark.h>
#include <TFile.h>
#include <TMath.h>
#include <math.h>
#include <TTree.h>
#include <TList.h>
#include <TClonesArray.h>
#include <TH1.h>

void DSPIDtuning(Double_t k1 = 0, Double_t k2 = 0, Double_t d1 = 0, Double_t d2 = 0, Double_t d3 = 0, Double_t d4 = 0, 
   Bool_t gateVertexZ = 1,
   Bool_t gateEx = 1,
   Bool_t gateRadius = 1,) {
   
//############################################################################   
   const char* savefilename="RppAll_0613.root";
   const char* rootfile="X3_25F_ppcoin_r14_0720_noCorr.root";
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=10000000;

   
//############################################################################
   gStyle->SetOptStat(0);
   TCanvas * c1 = new TCanvas("c1", "c1", 0, 0, 800, 800);
   c1->Divide(2,2);
   
   TString hTitle = ", ";
   if( gateVertexZ ) hTitle += "Vertex(Z), ";
   if( gateEx      ) hTitle += "Ex, ";
   if( gateRadius  ) hTitle += "r<7";

   TH1F *hA = new TH1F("hA", "A" + hTitle, 50, 20, 25); hA->SetXTitle("A"); hA->SetYTitle("count / 0.1");
   TH1F *hZ = new TH1F("hZ", "Z" + hTitle, 60,  4, 10); hZ->SetXTitle("Z"); hZ->SetYTitle("count / 0.1");
   
   TH2F * hPID = new TH2F("hPID", "PID"+ hTitle,    25, 20/8., 25/8., 30, 4, 10);
   hPID->SetXTitle("A/Q");
   hPID->SetYTitle("Z");
   
   TH2F * hAEx = new TH2F("hAEx", "A - Ex" + hTitle, 20, 20,    25   , 20, -40, 60);
   hAEx->SetXTitle("A");
   hAEx->SetYTitle("Ex");

//############################################################################



   
//############################################################################
   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded. \n",rootfile);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   
   
   Double_t s0x;
   Double_t s0dx;
   Double_t s1x;
   Double_t tof;
   Double_t pidZ;
   Double_t vertexZ;
   Double_t s0y;
   Double_t Ex;
   
   TBranch* b_s0x;
   TBranch* b_s0dx;
   TBranch* b_s1x;
   TBranch* b_tof;
   TBranch* b_pidZ;
   TBranch* b_vertexZ;
   TBranch* b_s0y;
   TBranch* b_Ex;
   
   tree->SetBranchStatus("*",0);
   tree->SetBranchStatus("s0x",1);
   tree->SetBranchStatus("s0y",1);
   tree->SetBranchStatus("s0dx",1);
   tree->SetBranchStatus("s1x",1); 
   tree->SetBranchStatus("tofS0DS1",1);
   tree->SetBranchStatus("pidZ",1);
   tree->SetBranchStatus("vertexZ",1);
   tree->SetBranchStatus("Ex",1);

   tree->SetBranchAddress("s0x" ,&s0x,  &b_s0x);
   tree->SetBranchAddress("s0y" ,&s0y,  &b_s0y);
   tree->SetBranchAddress("s0dx",&s0dx, &b_s0dx);
   tree->SetBranchAddress("s1x" ,&s1x,  &b_s1x);
   tree->SetBranchAddress("tofS0DS1",&tof, &b_tof);
   tree->SetBranchAddress("pidZ",&pidZ, &b_pidZ);
   tree->SetBranchAddress("vertexZ",&vertexZ, &b_vertexZ);
   tree->SetBranchAddress("Ex",&Ex, &b_Ex);


//############################################################################   
   Int_t endEntry = firstEntry + nEntries;
   if (allentry) {
      firstEntry = 0;
      endEntry = totnumEntry;
      nEntries = endEntry - firstEntry;
   }
   printf("====== totnumEntry:%d, 1stEntry:%d, nEntries:%d[%5.1f%%]\n",totnumEntry,firstEntry,nEntries,nEntries*100./totnumEntry);
   
   gROOT->ProcessLine(".!date");
   
/*++++++++++++++++++++++++++++++++++++++++++++++ tunning downstream PID parameters*/

   Double_t p1 = 0.129648        ;
   Double_t p2 = -0.004874       ;
//   Double_t a1 = 1.78074       ;
//   Double_t a2 = -0.00221778     ;
//   Double_t a3 = 1.0097e-6       ;
   Double_t a4 = 0.0229501       ;

   Double_t a1 = 0.5629       ;
   Double_t a2 = 1098.2371     ;   
   Double_t a3 = 1.0097       ;   
   
   //an improvement
   //p2 = 0;
   //a1 = 0.6629;
   //a2 = 1058.2371;
//##############################################################################

      
   for(Int_t eventID = firstEntry; eventID < endEntry; eventID ++){
      tree->GetEntry(eventID);
      
      // initialization
      Double_t s1xc = TMath::QuietNaN();
      Double_t tofc = TMath::QuietNaN();
      Double_t AOQ  = TMath::QuietNaN();
      
      b_s0x ->GetEntry(eventID,0);
      b_s0y ->GetEntry(eventID,0);
      b_s0dx->GetEntry(eventID,0);
      b_s1x ->GetEntry(eventID,0);
      b_tof ->GetEntry(eventID,0);
      b_pidZ->GetEntry(eventID,0);
      b_vertexZ->GetEntry(eventID,0);
      b_Ex->GetEntry(eventID,0);
      
      //printf(" pidZ:%6.2f, s0x:%6.2f, s0dx:%6.2f, s1x:%6.2f, tof:%6.2f, ", pidZ, s0x, s0dx, s1x, tof);
      
      if( gateEx && (Ex<-40 || Ex>60) ) continue;
      if( gateRadius && (sqrt(s0x*s0x + s0y*s0y) > 7.0)) continue;
      if( gateVertexZ && (vertexZ < -20 || vertexZ > 40)) continue;
      
      hZ->Fill(pidZ);

      
      s1xc = (s1x + (p1+k1) * s0dx)/(1 + (p2 + k2) * s0dx);
      tofc = tof;
      //AOQ = (a1 + d1) + (a2 + d2 )* s1xc + (a3 +d3) * s1xc * s1xc + (a4 +d4) * tofc;
      AOQ = (a1 + d1) + (a3 +d3)* 1e-6 *(s1xc - (a2 + d2))* (s1xc - (a2 + d2)) + (a4 +d4) * tofc;

      //AOQ = -0.469828*AOQ*AOQ +3.71596*AOQ -3.92076;

      hPID->Fill(AOQ, pidZ);
      
      if( 8.4<pidZ || pidZ <7.3 ) continue; 
      //printf("AOQ:%6.3f \n", AOQ);    
      hA->Fill(AOQ*8);
      hAEx->Fill(AOQ*8, Ex);
      
   }
   //clock.Stop("timer");
   c1->cd(1);
   hZ->Draw();
   
   Int_t n5 = hZ->FindBin(5); Double_t b5 = hZ->GetBinContent(n5);
   Int_t n6 = hZ->FindBin(6); Double_t b6 = hZ->GetBinContent(n6);
   Int_t n7 = hZ->FindBin(7); Double_t b7 = hZ->GetBinContent(n7);
   Int_t n8 = hZ->FindBin(8); Double_t b8 = hZ->GetBinContent(n8);
   Int_t n9 = hZ->FindBin(9); Double_t b9 = hZ->GetBinContent(n9);
   
   printf(" %f, %f, %f, %f, %f\n", b5, b6, b7, b8, b9);
   
   TF1* fitZ = new TF1("fitZ", "gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)", 4, 10);
   Double_t paraZ[15]={ b5, 5, 0.2,
                        b6, 6, 0.2, 
                        b7, 7, 0.2, 
                        b8, 8, 0.2, 
                        b9, 9, 0.2};
   
   Double_t MaxSigmaZ = 0.5; 
   
   fitZ->SetParameters(paraZ);
   fitZ->SetLineColor(1);
   fitZ->FixParameter(1 ,5);
   fitZ->FixParameter(4 ,6);
   fitZ->FixParameter(7 ,7);
   fitZ->FixParameter(10,8);
   fitZ->FixParameter(13,9);
   
   hZ->Fit("fitZ", "Q");
   printf("reduced chi-squared = %f \n", fitZ->GetChisquare()/fitZ->GetNDF());        
   
   fitZ->GetParameters(paraZ);
   TF1* gz1 = new TF1("gz1", "gaus(0)", 4, 10); gz1->SetParameters(&paraZ[0]);  gz1->SetLineColor(2); gz1->Draw("same");
   TF1* gz2 = new TF1("gz2", "gaus(0)", 4, 10); gz2->SetParameters(&paraZ[3]);  gz2->SetLineColor(3); gz2->Draw("same");
   TF1* gz3 = new TF1("gz3", "gaus(0)", 4, 10); gz3->SetParameters(&paraZ[6]);  gz3->SetLineColor(4); gz3->Draw("same");
   TF1* gz4 = new TF1("gz4", "gaus(0)", 4, 10); gz4->SetParameters(&paraZ[9]);  gz4->SetLineColor(6); gz4->Draw("same");
   TF1* gz5 = new TF1("gz5", "gaus(0)", 4, 10); gz5->SetParameters(&paraZ[12]); gz5->SetLineColor(7); gz5->Draw("same");
   
   printf("%7f, %7f, %7f, %7f, %7f \n",  paraZ[2], paraZ[5], paraZ[8], paraZ[11], paraZ[14]);
   
   //==================== fit histogram
   c1->cd(2);
   hA->Draw();
   
   Int_t n20 = hA->FindBin(20); Double_t b20 = hA->GetBinContent(n20);
   Int_t n21 = hA->FindBin(21); Double_t b21 = hA->GetBinContent(n21);
   Int_t n22 = hA->FindBin(22); Double_t b22 = hA->GetBinContent(n22);
   Int_t n23 = hA->FindBin(23); Double_t b23 = hA->GetBinContent(n23);
   Int_t n24 = hA->FindBin(24); Double_t b24 = hA->GetBinContent(n24);
   
   printf(" %f, %f, %f, %f, %f\n", b20, b21, b22, b23, b24);
   
   TF1* fit = new TF1("fit", "gaus(0)+gaus(3)+gaus(6)+gaus(9)+gaus(12)", 20, 26);
   Double_t para[15]={ b20, 20, 0.2,
                       b21, 21, 0.2, 
                       b22, 22, 0.2, 
                       b23, 23, 0.2, 
                       b24, 24, 0.2};
   
   Double_t MaxSigma = 0.5; 
   
   fit->SetParameters(para);
   fit->SetLineColor(1);

   fit->FixParameter(1 ,20);
   fit->FixParameter(4 ,21);
   fit->FixParameter(7 ,22);
   fit->FixParameter(10,23);
   fit->FixParameter(13,24);

   //fit->SetParLimits(1 , 19.5, 20.5);
   //fit->SetParLimits(4 , 20.5, 21.5);
   //fit->SetParLimits(7 , 21.5, 22.5);
   //fit->SetParLimits(10, 22.5, 23.5);
   //fit->SetParLimits(13, 23.5, 24.5);
   
   fit->SetParLimits(0 , 0, 2*b20);
   fit->SetParLimits(3 , 0, 2*b21);
   fit->SetParLimits(6 , 0, 2*b22);
   fit->SetParLimits(9 , 0, 2*b23);
   fit->SetParLimits(12, 0, 2*b24);
   
   fit->SetParLimits(2 , 0.1, MaxSigma);
   fit->SetParLimits(5 , 0.1, MaxSigma);
   fit->SetParLimits(8 , 0.1, MaxSigma);
   fit->SetParLimits(11, 0.1, MaxSigma);
   fit->SetParLimits(14, 0.1, MaxSigma);
   
   hA->Fit("fit", "Q");
   printf("reduced chi-squared = %f \n", fit->GetChisquare()/fit->GetNDF());        
   
   c1->cd(2);
   fit->GetParameters(para);
   TF1* g1 = new TF1("g1", "gaus(0)", 20, 26); g1->SetParameters(&para[0]);  g1->SetLineColor(2); g1->Draw("same");
   TF1* g2 = new TF1("g2", "gaus(0)", 20, 26); g2->SetParameters(&para[3]);  g2->SetLineColor(3); g2->Draw("same");
   TF1* g3 = new TF1("g3", "gaus(0)", 20, 26); g3->SetParameters(&para[6]);  g3->SetLineColor(4); g3->Draw("same");
   TF1* g4 = new TF1("g4", "gaus(0)", 20, 26); g4->SetParameters(&para[9]);  g4->SetLineColor(6); g4->Draw("same");
   TF1* g5 = new TF1("g5", "gaus(0)", 20, 26); g5->SetParameters(&para[12]); g5->SetLineColor(7); g5->Draw("same");

   c1->cd(3);
   hPID->Draw("colz");
   
   c1->cd(4);
   hAEx->Draw("colz");
   
   printf("p1:%7f, p2:%7f, a1:%7f, a2:%7f, a3:%15f, a4:%7f\n", p1 + k1, p2 + k2, a1 + d1, a2 + d2, a3 + d3, a4 + d4);
   printf("k1:%7f, k2:%7f, d1:%7f, d2:%7f, d3:%15f, d4:%7f\n", k1, k2, d1, d2, d3, d4);
   printf("(%7f,%7f), (%7f,%7f), (%7f,%7f) \n",  para[6], para[8], para[9], para[11], para[12], para[14]);



   return ;
}
