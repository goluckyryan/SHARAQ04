{
   gROOT->Reset();
   gROOT->ProcessLine(".!date");
   gStyle->SetOptStat(0);

   //-------------- THREEDEE
   TFile *f00 = new TFile ("THREEDEE/23F_Sp13.3_Tc010_ang003_phi002_DiracYesPerey.root", "read"); TTree *Ex00 = (TTree*)f00->Get("tree");
   TFile *f10 = new TFile ("THREEDEE/23F_Sp23.3_Tc010_ang003_phi002_DiracYesPerey.root", "read"); TTree *Ex10 = (TTree*)f10->Get("tree");
   TFile *f20 = new TFile ("THREEDEE/23F_Sp33.3_Tc010_ang003_phi002_DiracYesPerey.root", "read"); TTree *Ex20 = (TTree*)f20->Get("tree");

/**///======================================================== Browser or Canvas
   Int_t Div[2] = {1,1};  //x,y
   Int_t size[2] = {300,300}; //x,y
   TCanvas * cPostAna = new TCanvas("cPostAna", "cPostAna", 50, 0 , size[0]*Div[0], size[1]*Div[1]);
   cPostAna->Divide(Div[0],Div[1]);
   cPostAna->cd(1);
   
   double labelSize = 7e-2;

//*///======================================================== analysis
/*++++++++++++++++++++++++++++++++++++++++++++++ Sp*/
/*
   TH1F* m22 = new TH1F("m22", "", 40, -20, 60); m22->SetLineColor(2); m22->SetXTitle("Ex [MeV]"); m22->SetYTitle("count / 2 MeV");
   TH1F* m21 = new TH1F("m21", "", 40, -20, 60); m21->SetLineColor(kGreen-2); m21->SetXTitle("Ex [MeV]"); m21->SetYTitle("count / 2 MeV");
   TH1F* m20 = new TH1F("m20", "", 40, -20, 60); m20->SetLineColor(4); m20->SetXTitle("Ex [MeV]"); m20->SetYTitle("count / 2 MeV");

   m22->Fill(-39,  0); m21->Fill(-39, -2); m20->Fill(-39,  2);
   m22->Fill(-37,  1); m21->Fill(-37, -1); m20->Fill(-37,  1);
   m22->Fill(-35,  0); m21->Fill(-35, -2); m20->Fill(-35,  0);
   m22->Fill(-33,  0); m21->Fill(-33, -3); m20->Fill(-33, -1);
   m22->Fill(-31,  0); m21->Fill(-31,  2); m20->Fill(-31, -3);
   m22->Fill(-29,  1); m21->Fill(-29,  1); m20->Fill(-29,  0);
   m22->Fill(-27,  0); m21->Fill(-27,  2); m20->Fill(-27,  1);
   m22->Fill(-25,  0); m21->Fill(-25, -1); m20->Fill(-25,  0);
   m22->Fill(-23,  0); m21->Fill(-23,  2); m20->Fill(-23,  2);
   m22->Fill(-21,  0); m21->Fill(-21,  1); m20->Fill(-21,  4);
   m22->Fill(-19,  1); m21->Fill(-19,  0); m20->Fill(-19,  3);
   m22->Fill(-17,  0); m21->Fill(-17, -1); m20->Fill(-17,  0);
   m22->Fill(-15, -3); m21->Fill(-15,  0); m20->Fill(-15,  4);
   m22->Fill(-13, -2); m21->Fill(-13,  3); m20->Fill(-13, -1);
   m22->Fill(-11, -1); m21->Fill(-11,  0); m20->Fill(-11, -2);
   m22->Fill( -9,  4); m21->Fill( -9,  8); m20->Fill( -9,  1);
   m22->Fill( -7,  9); m21->Fill( -7,  6); m20->Fill( -7,  4);
   m22->Fill( -5, 10); m21->Fill( -5,  3); m20->Fill( -5,  2);
   m22->Fill( -3, 11); m21->Fill( -3, 14); m20->Fill( -3,  4);
   m22->Fill( -1, 13); m21->Fill( -1, 16); m20->Fill( -1,  7);
   m22->Fill(  1, 13); m21->Fill(  1, 25); m20->Fill(  1, 11);
   m22->Fill(  3, 11); m21->Fill(  3, 26); m20->Fill(  3, 14);
   m22->Fill(  5,  9); m21->Fill(  5, 38); m20->Fill(  5, 15);
   m22->Fill(  7,  9); m21->Fill(  7, 52); m20->Fill(  7, 18);
   m22->Fill(  9,  7); m21->Fill(  9, 34); m20->Fill(  9, 20);
   m22->Fill( 11,  3); m21->Fill( 11, 38); m20->Fill( 11, 25);
   m22->Fill( 13,  7); m21->Fill( 13, 39); m20->Fill( 13, 29);
   m22->Fill( 15,  5); m21->Fill( 15, 29); m20->Fill( 15, 43);
   m22->Fill( 17,  0); m21->Fill( 17, 23); m20->Fill( 17, 43);
   m22->Fill( 19,  4); m21->Fill( 19, 20); m20->Fill( 19, 43);
   m22->Fill( 21, -1); m21->Fill( 21, 10); m20->Fill( 21, 39);
   m22->Fill( 23,  1); m21->Fill( 23,  7); m20->Fill( 23, 35);
   m22->Fill( 25,  0); m21->Fill( 25,  7); m20->Fill( 25, 26);
   m22->Fill( 27,  0); m21->Fill( 27,  6); m20->Fill( 27, 25);
   m22->Fill( 29, -1); m21->Fill( 29,  3); m20->Fill( 29, 20);
   m22->Fill( 31,  0); m21->Fill( 31,  4); m20->Fill( 31, 13);
   m22->Fill( 33,  2); m21->Fill( 33,  4); m20->Fill( 33, 11);
   m22->Fill( 35, -1); m21->Fill( 35,  2); m20->Fill( 35, 10);
   m22->Fill( 37,  0); m21->Fill( 37,  6); m20->Fill( 37,  4);
   m22->Fill( 39, -2); m21->Fill( 39,  6); m20->Fill( 39, 12);
   m22->Fill( 41,  2); m21->Fill( 41,  9); m20->Fill( 41,  8);
   m22->Fill( 43, -1); m21->Fill( 43,  0); m20->Fill( 43,  7);
   m22->Fill( 45,  2); m21->Fill( 45,  5); m20->Fill( 45,  3);
   m22->Fill( 47,  0); m21->Fill( 47,  2); m20->Fill( 47, 12);
   m22->Fill( 49,  1); m21->Fill( 49,  1); m20->Fill( 49,  4);
   m22->Fill( 51,  3); m21->Fill( 51,  4); m20->Fill( 51,  9);
   m22->Fill( 53,  0); m21->Fill( 53,  5); m20->Fill( 53,  4);
   m22->Fill( 55,  0); m21->Fill( 55,  2); m20->Fill( 55,  4);
   m22->Fill( 57, -1); m21->Fill( 57,  1); m20->Fill( 57,  5);
   m22->Fill( 59,  0); m21->Fill( 59,  2); m20->Fill( 59,  0);
   
   m22->SetMaximum(58); m22->SetLineWidth(2); m22->SetFillStyle(3001); m22->SetFillColor(2);
   m21->SetMaximum(58); m21->SetLineWidth(2); m21->SetFillStyle(3004); m21->SetFillColor(kGreen-2);
   m20->SetMaximum(58); m20->SetLineWidth(2); m20->SetFillStyle(3005); m20->SetFillColor(4);

   
   //for small plot
   cPostAna->cd(1)->SetGridx(0);
   cPostAna->cd(1)->SetGridy(0);

   cPostAna->cd(1)->SetTopMargin(0.05);
   cPostAna->cd(1)->SetRightMargin(0.05);
   cPostAna->cd(1)->SetLeftMargin(0.15);
   cPostAna->cd(1)->SetBottomMargin(0.15);

   m22->GetXaxis()->SetNdivisions(-504);
   m21->GetXaxis()->SetNdivisions(-504);
   m20->GetXaxis()->SetNdivisions(-504);
   m22->GetXaxis()->SetLabelSize(labelSize);
   m21->GetXaxis()->SetLabelSize(labelSize);
   m20->GetXaxis()->SetLabelSize(labelSize);
   m22->GetYaxis()->SetLabelSize(labelSize);
   m21->GetYaxis()->SetLabelSize(labelSize);
   m20->GetYaxis()->SetLabelSize(labelSize);
   m22->GetXaxis()->SetTitleSize(labelSize);
   m21->GetXaxis()->SetTitleSize(labelSize);
   m20->GetXaxis()->SetTitleSize(labelSize);
   m22->GetYaxis()->SetTitleSize(labelSize);
   m21->GetYaxis()->SetTitleSize(labelSize);
   m20->GetYaxis()->SetTitleSize(labelSize);

//   
//   TF1* fit22o = new TF1("fit22o", "gaus(0)", -40, 60);
//   Double_t para22[3]={10, 0, 8};
//   fit22o->SetParameters(para22);
//   //fit22o->FixParameter(1, 0);
//   fit22o->SetLineColor(2);
//   fit22o->SetLineStyle(1);
//   fit22o->SetLineWidth(2);
//   m22->Fit("fit22o", "R");
//   printf("reduced chi-squared = %f \n", fit22o->GetChisquare()/fit22o->GetNDF());
//   
//   TF1* fit21o = new TF1("fit21o", "gaus(0)", -40, 60);
//   Double_t para21[3]={40, 10, 8};
//   fit21o->SetParameters(para21);
//   //fit21o->SetParLimits(4, 30, 40);
//   fit21o->SetLineColor(3);
//   fit21o->SetLineStyle(1);
//   m21->Fit("fit21o", "R");
//   printf("reduced chi-squared = %f \n", fit21o->GetChisquare()/fit21o->GetNDF());
//   
//   TF1* fit20o = new TF1("fit20o", "gaus(0)", -40, 34);
//   Double_t para20[6]={40, 18, 9};
//   fit20o->SetParameters(para20);
//   //fit20o->SetParLimits(4, 30, 40);
//   fit20o->SetLineColor(4);
//   fit20o->SetLineStyle(1);
//   m20->Fit("fit20o", "R");

   m20->Draw();m21->Draw("same");m22->Draw("same");

   TLatex text;
   text.SetNDC();
   text.SetTextSize(0.08);
   text.SetTextColor(2); text.DrawLatex( 0.67, 0.80, "(^{23}F,^{22}O)");
   text.SetTextColor(kGreen-2); text.DrawLatex( 0.67, 0.70, "(^{23}F,^{21}O)");
   text.SetTextColor(4); text.DrawLatex( 0.67, 0.60, "(^{23}F,^{20}O)");


/**///===================================================   

   cPostAna->cd(1);
   
   TH1F* o24 = new TH1F("o24", "", 20, -20, 60); o24->SetLineColor(2); o24->SetXTitle("Ex [MeV]"); o24->SetYTitle("count / 4 MeV");
   TH1F* o23 = new TH1F("o23", "", 20, -20, 60); o23->SetLineColor(kGreen-2); o23->SetXTitle("Ex [MeV]"); o23->SetYTitle("count / 4 MeV");
   TH1F* o22 = new TH1F("o22", "", 20, -20, 60); o22->SetLineColor(4); o22->SetXTitle("Ex [MeV]"); o22->SetYTitle("count / 4 MeV");
   TH1F* o21 = new TH1F("o21", "", 20, -20, 60); o21->SetLineColor(6); o21->SetXTitle("Ex [MeV]"); o21->SetYTitle("count / 4 MeV");

   o24->Fill(-38,  0);o23->Fill(-38,  0);o22->Fill(-38,  0);o21->Fill(-38,  2);
   o24->Fill(-34,  0);o23->Fill(-34,  2);o22->Fill(-34, -3);o21->Fill(-34, -5);
   o24->Fill(-30, -1);o23->Fill(-30,  1);o22->Fill(-30,  1);o21->Fill(-30,  0);
   o24->Fill(-26,  2);o23->Fill(-26,  0);o22->Fill(-26, -2);o21->Fill(-26,  1);
   o24->Fill(-22,  1);o23->Fill(-22, -2);o22->Fill(-22,  1);o21->Fill(-22,  1);
   o24->Fill(-18, -2);o23->Fill(-18, -4);o22->Fill(-18, -1);o21->Fill(-18,  0);
   o24->Fill(-14,  2);o23->Fill(-14,  0);o22->Fill(-14,  0);o21->Fill(-14,  1);
   o24->Fill(-10,  2);o23->Fill(-10,  1);o22->Fill(-10,  2);o21->Fill(-10,  1);
   o24->Fill( -6,  5);o23->Fill( -6,  2);o22->Fill( -6,  4);o21->Fill( -6,  3);
   o24->Fill( -2, 10);o23->Fill( -2,  4);o22->Fill( -2,  6);o21->Fill( -2,  0);
   o24->Fill(  2, 10);o23->Fill(  2,  8);o22->Fill(  2, 10);o21->Fill(  2,  0);
   o24->Fill(  6,  3);o23->Fill(  6, 14);o22->Fill(  6, 18);o21->Fill(  6, -1);
   o24->Fill( 10,  2);o23->Fill( 10, 11);o22->Fill( 10, 27);o21->Fill( 10,  3);
   o24->Fill( 14,  0);o23->Fill( 14,  9);o22->Fill( 14, 44);o21->Fill( 14, 17);
   o24->Fill( 18, -1);o23->Fill( 18,  6);o22->Fill( 18, 31);o21->Fill( 18,  0);
   o24->Fill( 22,  0);o23->Fill( 22, -1);o22->Fill( 22, 11);o21->Fill( 22,  8);
   o24->Fill( 26,  1);o23->Fill( 26, -2);o22->Fill( 26,  6);o21->Fill( 26, 11);
   o24->Fill( 30,  2);o23->Fill( 30,  1);o22->Fill( 30,  3);o21->Fill( 30,  3);
   o24->Fill( 34,  1);o23->Fill( 34,  1);o22->Fill( 34,  6);o21->Fill( 34,  5);
   o24->Fill( 38,  0);o23->Fill( 38,  1);o22->Fill( 38,  0);o21->Fill( 38,  0);
   o24->Fill( 42, -2);o23->Fill( 42,  1);o22->Fill( 42,  6);o21->Fill( 42,  0);
   o24->Fill( 46,  6);o23->Fill( 46,  3);o22->Fill( 46,  5);o21->Fill( 46,  0);
   o24->Fill( 50,  1);o23->Fill( 50,  0);o22->Fill( 50,  2);o21->Fill( 50, -5);
   o24->Fill( 54,  0);o23->Fill( 54,  0);o22->Fill( 54,  2);o21->Fill( 54,  2);
   o24->Fill( 58, -2);o23->Fill( 58,  1);o22->Fill( 58,  3);o21->Fill( 58,  2);

   o24->SetMaximum(47); o24->SetLineWidth(2); o24->SetFillStyle(3644); o24->SetFillColor(2);
   o23->SetMaximum(47); o23->SetLineWidth(2); o23->SetFillStyle(3004); o23->SetFillColor(kGreen-2);
   o22->SetMaximum(47); o22->SetLineWidth(2); o22->SetFillStyle(3005); o22->SetFillColor(4);
   o21->SetMaximum(47); o21->SetLineWidth(2); o21->SetFillStyle(3005); o21->SetFillColor(6);
   
   cPostAna->cd(2)->SetGridx(0);
   cPostAna->cd(2)->SetGridy(0);
   cPostAna->cd(2)->SetTopMargin(0.05);
   cPostAna->cd(2)->SetRightMargin(0.05);
   cPostAna->cd(2)->SetLeftMargin(0.15);
   cPostAna->cd(2)->SetBottomMargin(0.15);
   
   o24->GetXaxis()->SetNdivisions(-504);
   o23->GetXaxis()->SetNdivisions(-504);
   o22->GetXaxis()->SetNdivisions(-504);
   o21->GetXaxis()->SetNdivisions(-504);
   o24->GetXaxis()->SetLabelSize(labelSize);
   o23->GetXaxis()->SetLabelSize(labelSize);
   o22->GetXaxis()->SetLabelSize(labelSize);
   o21->GetXaxis()->SetLabelSize(labelSize);
   o24->GetYaxis()->SetLabelSize(labelSize);
   o23->GetYaxis()->SetLabelSize(labelSize);
   o22->GetYaxis()->SetLabelSize(labelSize);
   o21->GetYaxis()->SetLabelSize(labelSize);
   o24->GetXaxis()->SetTitleSize(labelSize);
   o23->GetXaxis()->SetTitleSize(labelSize);
   o22->GetXaxis()->SetTitleSize(labelSize);
   o21->GetXaxis()->SetTitleSize(labelSize);
   o24->GetYaxis()->SetTitleSize(labelSize);
   o23->GetYaxis()->SetTitleSize(labelSize);
   o22->GetYaxis()->SetTitleSize(labelSize);
   o21->GetYaxis()->SetTitleSize(labelSize);
   
   
   // Int_t lineWidth = 0.5;
   // TF1* fit24o = new TF1("fit24o", "gaus(0)", -40, 60);
   // Double_t para24[3]={8, 0, 4};
   // fit24o->SetParameters(para24);
   // //fit24o->FixParameter(1, 0);
   // fit24o->SetLineColor(2);
   // fit24o->SetLineStyle(1);
   // fit24o->SetLineWidth(lineWidth);
   // o24->Fit("fit24o", "R");
   // 
   // TF1* fit23o = new TF1("fit23o", "gaus(0)", -40, 60);
   // Double_t para23[6]={12, 6, 6};
   // fit23o->SetParameters(para23);
   // //fit23o->SetParLimits(4, 30, 40);
   // fit23o->SetLineColor(kGreen-2);
   // //fit23o->SetLineStyle(7);
   // fit23o->SetLineStyle(1);
   // fit23o->SetLineWidth(lineWidth);
   // o23->Fit("fit23o", "R");
   // 
   // TF1* fit22o = new TF1("fit22o", "gaus(0)", -40, 60);
   // Double_t para22[6]={40, 13, 8};
   // fit22o->SetParameters(para22);
   // //fit22o->SetParLimits(4, 30, 40);
   // fit22o->SetLineColor(4);
   // //fit22o->SetLineStyle(2);
   // fit22o->SetLineStyle(1);
   // fit22o->SetLineWidth(lineWidth);
   // o22->Fit("fit22o", "R");
   // 
   // TF1* fit21o = new TF1("fit21o", "gaus(0)", -40, 60);
   // Double_t para21[6]={15, 22, 8};
   // fit21o->SetParameters(para21);
   // //fit21o->SetParLimits(4, 30, 40);
   // fit21o->SetLineColor(6);
   // //fit21o->SetLineStyle(4);
   // fit21o->SetLineStyle(1);
   // fit21o->SetLineWidth(lineWidth);
   // o21->Fit("fit21o", "R");

   o21->Draw();
   o22->Draw("");o23->Draw("same");o24->Draw("same");
   //o21->Draw("");o22->Draw("same");o23->Draw("same");o24->Draw("same");

   TLatex text;
   text.SetNDC();
   text.SetTextSize(0.08);
   text.SetTextColor(2); text.DrawLatex( 0.67, 0.80, "(^{25}F,^{24}O)");
   text.SetTextColor(kGreen-2); text.DrawLatex( 0.67, 0.70, "(^{25}F,^{23}O)");
   text.SetTextColor(4); text.DrawLatex( 0.67, 0.60, "(^{25}F,^{22}O)");
   //text.SetTextColor(6); text.DrawLatex( 0.67, 0.50, "(^{25}F,^{21}O)");

}
