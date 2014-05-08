#include "RelCalculator.h"
//____________ Initial parameter
Double_t TKA = 260;
Double_t BGratio = 0.7;
const Int_t nOrder = 2; // order of polynomial
Int_t npfits;
TString titleh1 = "spin UP ";
TString titleh2 = "spin Down ";   
TString titleBG;
Double_t Xrange[2] = {76, 96};
Int_t   nbin = (Xrange[1]-Xrange[0])*4;
Double_t countRange[2] = {85.8, 88.0};

//____________ Loading File
TFile *f0 = new TFile ("ppelasticUp.root");
TTree *recoilUp = (TTree*)f0->Get("recoil");
TFile *f1 = new TFile ("ppelasticDown.root");
TTree *recoilDown = (TTree*)f1->Get("recoil");

//____________ create Canvas and histogram
TCanvas * cPlot = new TCanvas ("cPlot","cPlot", 1400,50,800,800);
//TCanvas * cAux = new TCanvas ("cAux","cAux", 1350,70,400,400);
TH1F * h1 = new TH1F("h1",titleh1, nbin, Xrange[0], Xrange[1]);
TH1F * h2 = new TH1F("h2",titleh2, nbin, Xrange[0], Xrange[1]);
TH1F * h1a = new TH1F("h1a",titleh1,  nbin, Xrange[0], Xrange[1]);
TH1F * h2a = new TH1F("h2a",titleh2, nbin, Xrange[0], Xrange[1]);

//========================================================================
void Fit_ppSumTheta3(Int_t angle1 = 0, Int_t angle2 = 180, Int_t LR = 1, Int_t OPCM = 1){
   gStyle->SetOptFit(1111);
   printf("=========================================\n");
   
   //______________Set the thetaCM and the corresponding thetaLab
   if (OPCM ==1 ){
      Int_t    cmThetaGate[2] = {angle1, angle2};
      Double_t thetaGate[2] ={CMtoLabTheta(TKA,cmThetaGate[0]), CMtoLabTheta(TKA,cmThetaGate[1])};
      printf(" using CM Frame Theta (%4.1f,%4.1f) = Lab(%5.2f, %5.2f)\n",cmThetaGate[0],cmThetaGate[1], thetaGate[0], thetaGate[1]);
   }else{
      Int_t    cmThetaGate[2] = {angle1, angle2};
      Double_t thetaGate[2] = {cmThetaGate[0], cmThetaGate[1]};
      printf(" using Lab Frame Theta (%4.1f,%4.1f)\n",thetaGate[0], thetaGate[1]);
   }
   
   //_____________ Gating for the histogram
   TCut beamZGate1 = "wbeamZ >-20";
   TCut beamZGate2 = "wbeamZ < 40";
   TString cut;
   if ( LR == 1){
      cut = "theta1";
   }else{
      cut = "theta2";
   }
   TString cut1 = cut + "*TMath::RadToDeg() > ";
   TString cut2 = cut + "*TMath::RadToDeg() < ";
   cut1 += thetaGate[0];
   cut2 += thetaGate[1];
   TCut angleCut1 ;
   TCut angleCut2 ;
   angleCut1 += cut1;
   angleCut2 += cut2;
   
   beamZGate1.Print();
   beamZGate2.Print();
   angleCut1.Print();
   angleCut2.Print();
   
   //_____________ Set the histogram title
   TString side;
   if (LR ==1){
      side.Form("L(%2d-%2d)[%s&&%s] ",cmThetaGate[0],cmThetaGate[1],beamZGate1.GetTitle(), beamZGate2.GetTitle());
   }else{
      side.Form("R(%2d-%2d)[%s&&%s] ",cmThetaGate[0],cmThetaGate[1],beamZGate1.GetTitle(), beamZGate2.GetTitle());
   }
   if (OPCM ==1){
      side += "cm";
   }else{
      side += "lab";
   }
   titleBG.Form(" BG Sub(%4.1f-%4.1f)",countRange[0],countRange[1]);
   h1->SetTitle(titleh1+side);
   h2->SetTitle(titleh2+side);
   h1a->SetTitle(titleh1+titleBG);
   h2a->SetTitle(titleh2+titleBG);
   
   //_____________ Fill the hitogram from Data
   cPlot->Clear("All");
   cPlot->Divide(2,2);
   //cAux->Clear("All");
   h1->SetMinimum(0);
   h2->SetMinimum(0);
   //cAux->cd(1);
   cPlot->cd(1);
   recoilUp->Draw("(theta1+theta2)*TMath::RadToDeg()>>h1", beamZGate1 && beamZGate2 && angleCut1 && angleCut2);
   //cAux->cd(2);
   cPlot->cd(3);
   recoilDown->Draw("(theta1+theta2)*TMath::RadToDeg()>>h2", beamZGate1 && beamZGate2 && angleCut1 && angleCut2, "same");
   
   //______________ Primary Fit
   Double_t preA0, preA1, preA2;
   if ( 0 ) {
      TF1 *preFitFunc = new TF1("prefit", "pol2(0)+gaus(3)", Xrange[0], Xrange[1]);
      Double_t prePara[6] = {-1000, 100, -0.1, 100, 86.5, 1};
      preFitFunc->SetLineWidth(1);
      preFitFunc->SetLineColor(3);
      preFitFunc->SetParameters(prePara);
      preFitFunc->SetParLimits(0,-10000,0);
      preFitFunc->SetParLimits(1,0,500);
      preFitFunc->SetParLimits(2,-3,0);
      preFitFunc->SetParLimits(3,10,10000);
      preFitFunc->SetParLimits(4,85,88);
      preFitFunc->SetParLimits(5, 0,2);
      //TFitResultPtr preFit = h1->Fit("pol2", "N S");
      TFitResultPtr preFit = h1->Fit(preFitFunc, "S");
      preA0 = preFit->Parameter(0);
      preA1 = preFit->Parameter(1);
      preA2 = preFit->Parameter(2);
      preFitFunc->SetParameters(prePara);
      //TFitResultPtr preFit = h2->Fit("pol2", "N S");
      TFitResultPtr preFit = h2->Fit(preFitFunc, "S");
      preA0 += preFit->Parameter(0);
      preA1 += preFit->Parameter(1);
      preA2 += preFit->Parameter(2);
      preA0 = preA0/2;
      preA1 = preA1/2;
      preA2 = preA2/2;   
   }else{
      preA0 = -3000;
      preA1 =  80;
      preA2 = -0.3;
   }
   //cAux->cd();
   h1->Draw();
   h2->Draw("same");
   printf("--------------------------------------------\n");
   printf(" preA: %10.2f, %10.2f, %10.5f \n", preA0,preA1, preA2);
   
   //________________ Making Fitting Function
   const Int_t nParaSumTheta = 3;
   const Int_t nPara = nParaSumTheta + 1 + 1 + nOrder ; 
   Int_t Npx = nbin*3; // number of point of Fitting Function
      
   Double_t iniPara1[nPara] ={ 3500, 0.3, 260, 0., -10000, 260, -1.5};
   TF1 *fit1 = new TF1("fit", fitFunction, Xrange[0], Xrange[1], nPara); 
   fit1->SetNpx(Npx);
   fit1->SetParameters(iniPara1);
   
   Double_t iniPara2[nPara] ={ 3500, 0.3, 260, 0., -10000, 260, -1.5};
   TF1 *fit2 = new TF1("fit", fitFunction, Xrange[0], Xrange[1], nPara); 
   fit2->SetNpx(Npx);
   fit2->SetParameters(iniPara2);

   //____________ Using Minuit for fitting
   const Double_t nfitPara = 11;
   TVirtualFitter::SetDefaultFitter("Minuit");
   TVirtualFitter * minuit = TVirtualFitter::Fitter(0,nfitPara);
   minuit->SetParameter( 0, " M1     ",    2000,    0.1   ,   10,5000);
   minuit->SetParameter( 1, " sigma1 ",    0.35,    0.02  ,  0.2,   1);
   minuit->SetParameter( 2, " TKA    ",     TKA,    0.01  ,  250, 270);
   minuit->SetParameter( 3, " shift1 ",      0.,    0.01  , -0.5, 0.5);
   minuit->SetParameter( 4, "  a0    ",   preA0,    0.1   ,    0,   0);
   minuit->SetParameter( 5, "  a1    ",   preA1,    0.01  ,    0,   0);
   minuit->SetParameter( 6, "  a2    ",   preA2,    0.001 ,    0,   0);
   minuit->SetParameter( 7, " M2     ",    2000,    0.1   ,   10,5000);
   minuit->SetParameter( 8, " sigma2 ",     0.3,    0.02  ,  0.2,  1.);
   minuit->SetParameter( 9, " shift2 ",     0.0,    0.01  , -0.5, 0.5);
   minuit->SetParameter(10, "  BG2   ", BGratio,    0.001  ,  0.2,  1.);
   
   minuit->SetFCN(SSR);
   minuit->FixParameter(2);
   minuit->FixParameter(3);
   minuit->FixParameter(9);
   //minuit->FixParameter(10);
   
   double arglist[100];
   arglist[0] = 0;
   // set print level
   minuit->ExecuteCommand("SET PRINT",arglist,2);

   // minimize
   arglist[0] = 5000; // number of function calls
   arglist[1] = 0.01; // tolerance
   minuit->ExecuteCommand("MIGRAD",arglist,2);
    
   //get result
   double minPara[nfitPara];
   double parErrors[nfitPara];
   for (int i = 0; i < nfitPara; ++i) {  
     minPara[i] = minuit->GetParameter(i);
     parErrors[i] = minuit->GetParError(i);
   }
   double chi2, edm, errdef; 
   int nvpar, nparx;
   minuit->GetStats(chi2,edm,errdef,nvpar,nparx);
   printf(" chi2:%10.3f , NDF:%d \n",chi2, npfits-nvpar);
   
   //____________ Set the fit function parameters
   Double_t minPara1[nPara] = {minPara[0],minPara[1],minPara[2],minPara[3],minPara[4],minPara[5],minPara[6]};
   Double_t parErrors1[nPara] = {parErrors[0],parErrors[1],parErrors[2],parErrors[3],parErrors[4],parErrors[5],parErrors[6]};
   fit1->SetParameters(minPara1);
   fit1->SetParErrors(parErrors1);
   fit1->SetChisquare(chi2);
   fit1->SetNDF(npfits-nvpar);
   
   Double_t minPara2[nPara] = {minPara[7],minPara[8],minPara[2],minPara[9],
                                 minPara[10]*minPara[4],
                                 minPara[10]*minPara[5],
                                 minPara[10]*minPara[6]};
   Double_t parErrors2[nPara] = {parErrors[7],parErrors[8],parErrors[2],parErrors[9],
                                  minPara[4]*parErrors[10]+minPara[10]*parErrors[4],
                                  minPara[5]*parErrors[10]+minPara[10]*parErrors[5],
                                  minPara[6]*parErrors[10]+minPara[10]*parErrors[6]};
   fit2->SetParameters(minPara2);
   fit2->SetParErrors(parErrors2);
   fit2->SetChisquare(chi2);
   fit2->SetNDF(npfits-nvpar);
   
   //__________________ add to the histogram so that the histogram will show the fit result.
   h1->GetListOfFunctions()->Add(fit1);
   h2->GetListOfFunctions()->Add(fit2);
   
   //________________ Draw the Fit
   cPlot->cd(1);
   h1->Draw();
   TF1 *gfit1 = new TF1("gfit1", GausConSumTheta,Xrange[0], Xrange[1], nParaSumTheta);
   gfit1->SetNpx(Npx);
   gfit1->SetLineColor(4);
   gfit1->SetParameters(minPara);
   gfit1->Draw("same");
   TF1 *gPoly1 = new TF1("gPloy1", Poly,Xrange[0], Xrange[1], nOrder+1);
   gPoly1->SetNpx(Npx);
   gPoly1->SetLineColor(1);
   gPoly1->SetParameters(&minPara[nParaSumTheta+1]);
   gPoly1->Draw("same");
   
   SubBG(h1, h1a, gPoly1, 2);
   gfit1->Draw("same");
   
   cPlot->cd(3);
   h2->Draw();
   TString BGratioStr;
   BGratioStr.Form("%s%4.3f(%4.3f)","BG Ratio=",minPara[10],parErrors[10]);
   TLatex *BGratioText = new TLatex();
   BGratioText->SetNDC();
   BGratioText->SetTextSize(0.04);
   BGratioText->DrawLatex(0.11, 0.2, BGratioStr);
   TF1 *gfit2 = new TF1("gfit1", GausConSumTheta,Xrange[0], Xrange[1], nParaSumTheta);
   gfit2->SetNpx(Npx);
   gfit2->SetLineColor(4);
   gfit2->SetParameters(minPara2);
   gfit2->Draw("same");
   TF1 *gPoly2 = new TF1("gPloy2", Poly,Xrange[0], Xrange[1], nOrder+1);
   gPoly2->SetNpx(Npx);
   gPoly2->SetLineColor(1);
   gPoly2->SetParameters(&minPara2[nParaSumTheta+1]);
   gPoly2->Draw("same");
   
   SubBG(h2, h2a,  gPoly2, 4);
   gfit2->Draw("same");
   
   //Set TPaveStats
   //TPaveStats *stat = h1->GetListOfFunctions()->FindObject("stats");
   //stat->SetY2(120);
   //stat = h2->GetListOfFunctions()->FindObject("stats");
   //stat->SetY2(120);
}

void SubBG(TH1F* hist, TH1F* hout, TF1* BGfunc, Int_t padID){
   Double_t x;
   Int_t nBin = hist->GetNbinsX();
   Double_t countS = 0, countBG = 0, countTot = 0;

   for ( Int_t i = 1; i<=nBin; i++){
      x = hist->GetBinCenter(i);
      if (hist->GetBinContent(i) == 0) continue;
      //printf(" BGfunc(%5.2f) = %10.2f | hist = %6d \n", x, BGfunc->Eval(x), hist->GetBinContent(i) );
      hout->Fill(x,hist->GetBinContent(i) - BGfunc->Eval(x));
      if ( x > countRange[0] && x < countRange[1] ) {
         countBG  += BGfunc->Eval(x);
         countTot += hist->GetBinContent(i);
      }
      hout->SetBinError(i, TMath::Sqrt(hist->GetBinContent(i) + BGfunc->Eval(x)));
   }
   countS  = countTot - countBG;
   
   //TODO integral error for BG
   
   cPlot->cd(padID);
   hout->Draw("E1");
   printf("Count(%4.1f, %4.1f): %5d [%6.1f] |%d, %d \n",countRange[0], countRange[1], countS, TMath::Sqrt(countTot+countBG), countTot, countBG);

   TLine *line1 = new TLine(countRange[0], hout->GetMinimum(), countRange[0], hout->GetMaximum());
   TLine *line2 = new TLine(countRange[1], hout->GetMinimum(), countRange[1], hout->GetMaximum());
   line1->SetLineColor(3);
   line2->SetLineColor(3);
   line1->SetLineWidth(2);
   line2->SetLineWidth(2);
   line1->Draw("same");
   line2->Draw("same");   
   
   TString countResult;
   countResult.Form("%d[%d]",TMath::Nint(countS),TMath::Nint(TMath::Sqrt(countTot+countBG)));
   TLatex *resultText = new TLatex();
   resultText->SetNDC();
   resultText->DrawLatex(0.2, 0.8, countResult);
}
//===============================================================================
void SSR(Int_t & /*nPar*/, Double_t * /*grad*/ , Double_t &fval, Double_t *p, Int_t /*iflag */ ){
 
   TH1F* hist1 = h1;
   TH1F* hist2 = h2;
   
   Double_t ssr = 0;
   Double_t temp;
   npfits = 0;
   Double_t x[1];
   
   Int_t nBin1 = hist1->GetNbinsX();
   Double_t para1[7] = {p[0], p[1], p[2], p[3], p[4], p[5], p[6]};
   for ( Int_t i = 1; i<=nBin1; i++){
      x[0] = hist1->GetBinCenter(i);
      if (hist1->GetBinContent(i) == 0) continue;
      temp = (hist1->GetBinContent(i) - fitFunction(x, para1))/hist1->GetBinError(i);
      ssr += temp*temp;
      npfits ++;
   }
   
   Int_t nBin2 = hist2->GetNbinsX();
   Double_t para2[7] = {p[7], p[8], p[2], p[9], p[10]*p[4], p[10]*p[5], p[10]*p[6]};
   for ( Int_t i = 1; i<=nBin2; i++){
      x[0] = hist2->GetBinCenter(i);
      if (hist2->GetBinContent(i) == 0) continue;
      temp = (hist2->GetBinContent(i) - fitFunction(x, para2))/hist2->GetBinError(i);
      ssr += temp*temp;
      npfits ++;
   }
   
   fval = ssr;  
}
//===============================================================================
Double_t fitFunction(const Double_t *x, const Double_t *para){
  //const Int_t nParaPloy = nOrder +1;
  //para[3] = shift of x;
  //para[4] and so on is Poly
  
  Double_t arg[1];
  arg[0] = x[0] +para[3];
  return GausConSumTheta(arg,para) + Poly(x,&para[4]);
  
}
//===============================================================================
Double_t Poly(const Double_t *x, const Double_t *para){
   // in the form of 1+ a1 X + a2 X^2 + ..... 
   
   Double_t val = 0;
   
   for ( Int_t i = 0; i <= nOrder; i++){
      val += para[i]*TMath::Power(x[0],i);
   }
  
   return val;
}
//===============================================================================
Double_t Gauss(const Double_t *x, const Double_t *para){
   // magnitude, mean, sigma
   return para[0]*TMath::Gaus(x[0], para[1],para[2],0);
}
//===============================================================================
Double_t GausConSumTheta(Double_t *x, Double_t *para){
  //para[0] = Gaussian magnitude
  //para[1] = Gaussian sigma
  //Para[2] = KE
  Double_t np = 200.0;  // number of Convolution step
  Double_t sc = 5.0;    // convolution extends to +-sc Gaussuan sigma
  
  Double_t xx;

  const Double_t xlow  = x[0] - sc*para[1];
  const Double_t xhigh = x[0] + sc*para[1];
  const Double_t step = (xhigh-xlow)/np;

  Double_t sum = 0;
  for(Int_t i = 0; i <np; i++){
    xx = xlow + i*step;
    sum += SumTheta(&xx,&para[2])* TMath::Gaus(xx,x[0],para[1],0)*step;    
    
  }

  return para[0]*sum ;
}
//===============================================================================
Double_t SumTheta(Double_t*x , Double_t *para){
  //para[0] = KE
  const Double_t mp = 938.272;
  Double_t a  = para[0]/mp/2;
  Double_t temp0 = 4*(1+a)/a/a;
  Double_t arg   = x[0]*TMath::DegToRad(); // input x[0] is deg, arg is rad , arg = theta1+theta2
  Double_t temp1 = TMath::Power(TMath::Sin(arg),2);
  Double_t temp2 = TMath::Power(TMath::Tan(arg),2);
  
  Double_t limit1 = TMath::ATan(TMath::Sqrt(temp0)/TMath::Sin(36*TMath::DegToRad()));
  //Double_t limit2 = TMath::ATan(TMath::Sqrt(temp0)/TMath::Sin(140*TMath::DegToRad()));
  //printf("para[1], para[2]: %5.2f, %5.2f \n", para[1], para[2]);
  //printf("limit1, limit2: %10.3f, %10.3f \n", limit1*TMath::RadToDeg(),limit2*TMath::RadToDeg());
  //printf(" KE:%10.4f, a:%10.4f, Theta_min:%10.4f deg\n",para[0], a, TMath::ATan(TMath::Sqrt(temp0))*TMath::RadToDeg() );
  //printf(" x[0]:%10.4f\n", x[0]);

  if ( temp2 > temp0 && arg<=limit1 && arg>=0){
    if ( temp2 <= temp0 +1) {
      return 1/temp1;
    }
      return 1/temp1/TMath::Sqrt(temp2-temp0);
  }else{
    return 0;
  }
  
}
