#include "MaxiLikelihood_Func_Norm.C";
#include "MaxiLikelihood_Func.C";
#include "MaxiLikelihood.C";

void Replot(TH1F* h1a, TH1F* h1b, TH1F* h1c, TH1F* h1d, TH1F* h2, Bool_t plothk) {
   
   // replot the momementum with a fitted function.
   
   const int nBin = h1a->GetNbinsX();
   if( nBin != h1b->GetNbinsX()) return;
   
   printf("# of bin: %d\n", nBin);
   
   double xbin = new double[nBin];
   double ybin = new double[nBin];
   
   Double_t maxY = 0;
   Int_t maxBin = 0;
   Double_t maxX = 0;
   
   Double_t gMaxY= 0;
   
//========================================== fit for 1d5/2
   maxY   = h1a->GetMaximum();
   maxBin = h1a->GetMaximumBin();
   maxX   = h1a->GetBinCenter(maxBin);
   if( gMaxY < maxY ) gMaxY = maxY;
   //printf("maxX:%5.1f, maxY:%5.1f \n", maxX, maxY);
   TF1 * f1a = new TF1("f1a", "[0]*exp(-[2]/[1]*(x-[1]))*pow(x,[2])/pow([1],[2])", 0, 400);
   Double_t paraa[3] = {maxY, maxX, 4};
   f1a->SetParameters(paraa);
   f1a->SetParLimits(0,maxY-1,maxY+1); // max
   f1a->SetParLimits(1,maxX-50,maxX+50); // peak
   //f1a->SetParLimits(1,120,150); // peak
   f1a->SetParLimits(2,1,20); // width
   f1a->SetLineColor(2);
   h1a->Fit("f1a","R");
   printf("reduced chi-squared = %f \n", f1a->GetChisquare()/f1a->GetNDF());  
   
//========================================== fit for 1p1/2
   maxY   = h1b->GetMaximum();
   maxBin = h1b->GetMaximumBin();
   maxX   = h1b->GetBinCenter(maxBin);
   if( gMaxY < maxY ) gMaxY = maxY;
   TF1 * f1b = new TF1("f1b", "[0]*exp(-[2]/[1]*(x-[1]))*pow(x,[2])/pow([1],[2])", 0, 400);
   Double_t parab[3] = {maxY, maxX, 4};
   f1b->SetParameters(parab);
   f1b->SetParLimits(0,maxY-1,maxY+1);
   f1b->SetParLimits(1,maxX-50,maxX+50);
   //f1b->SetParLimits(1,70,maxX+50);
   f1b->SetParLimits(2,1,20);
   f1b->SetLineColor(3);
   h1b->Fit("f1b","R");
   printf("reduced chi-squared = %f \n", f1b->GetChisquare()/f1b->GetNDF());  
   

//========================================== fit for 1p3/2
   maxY   = h1c->GetMaximum();
   maxBin = h1c->GetMaximumBin();
   maxX   = h1c->GetBinCenter(maxBin);
   if( gMaxY < maxY ) gMaxY = maxY;
   TF1 * f1c = new TF1("f1c", "[0]*exp(-[2]/[1]*(x-[1]))*pow(x,[2])/pow([1],[2])", 0, 400);
   Double_t parac[3] = {maxY, maxX, 4};
   f1c->SetParameters(parac);
   f1c->SetParLimits(0,maxY*0.8,maxY*1.1);
   f1c->SetParLimits(1,maxX-50,maxX+50);
   f1c->SetParLimits(2,1,20);
   f1c->SetLineColor(4);
   h1c->Fit("f1c","R");
   printf("reduced chi-squared = %f \n", f1c->GetChisquare()/f1c->GetNDF());    

//========================================== fit for 2s1/2
   maxY   = h1d->GetMaximum();
   maxBin = h1d->GetMaximumBin();
   //maxY   = h1d->GetBinContent(maxBin+1);
   maxX   = h1d->GetBinCenter(maxBin);
   //maxX   = h1d->GetBinCenter(maxBin+1);
   if( gMaxY < maxY ) gMaxY = maxY;
   TF1 * f1d = new TF1("f1d", "[0]*exp(-[2]/[1]*(x-[1]))*pow(x,[2])/pow([1],[2]) + [3]*exp(-pow(x-[4],2)/2/pow([5],2))", 0, 400);
   Double_t parad[6] = {maxY, maxX, 4, 10, 200, 50};
   f1d->SetParameters(parad);
   f1d->SetParLimits(0,maxY-1,maxY+1);
   f1d->SetParLimits(1,maxX-50,maxX+50);
   f1d->SetParLimits(2,1,20);
   f1d->SetParLimits(3,0,10);
   f1d->SetParLimits(4,120,220);
   f1d->SetParLimits(5,10,70);
   f1d->SetLineColor(6);
   h1d->Fit("f1d","R");
   printf("reduced chi-squared = %f \n", f1d->GetChisquare()/f1d->GetNDF());    

//==========================================

   
   h2->SetMaximum(gMaxY+1);
   h2->SetFillColor(1);
   h2->SetFillStyle(3004);

   h2->Draw("E");
   h2->Draw("same");
   if( plothk) h1a->Draw("same");
   f1a->Draw("same");
   if( plothk) h1b->Draw("same");
   f1b->Draw("same");
   if( plothk) h1c->Draw("same");
   f1c->Draw("same");
   if( plothk) h1d->Draw("same");
   f1d->Draw("same");
   
   TLatex text;
   text.SetNDC();
   text.SetTextColor(2); text.DrawLatex( 0.7, 0.80, "1d_{5/2}");
   text.SetTextColor(3); text.DrawLatex( 0.7, 0.75, "1p_{1/2}");
   text.SetTextColor(4); text.DrawLatex( 0.7, 0.70, "1p_{3/2}");
   text.SetTextColor(6); text.DrawLatex( 0.7, 0.65, "2s_{1/2}");
   
   
   MaxiLikelihood_Func_Norm(h2, f1a, h1a);
   MaxiLikelihood_Func_Norm(h2, f1b, h1b);
   MaxiLikelihood_Func_Norm(h2, f1c, h1c);
   MaxiLikelihood_Func_Norm(h2, f1d, h1d);

   //printf("\n");
   //
   //MaxiLikelihood_Func(h2, f1a);
   //MaxiLikelihood_Func(h2, f1b);
   //MaxiLikelihood_Func(h2, f1c);
   //MaxiLikelihood_Func(h2, f1d);
   //
   //printf("\n");
   //
   //MaxiLikelihood_Func(h1a, f1a);
   //MaxiLikelihood_Func(h1a, f1b);
   //MaxiLikelihood_Func(h1a, f1c);
   //MaxiLikelihood_Func(h1a, f1d);

//   MaxiLikelihood(h2, h1a);
//   MaxiLikelihood(h2, h1b);
//   MaxiLikelihood(h2, h1c);
//   MaxiLikelihood(h2, h1d);
//   
//   MaxiLikelihood(h1a, h1a);
//   MaxiLikelihood(h1a, h1b);
//   MaxiLikelihood(h1a, h1c);
//   MaxiLikelihood(h1a, h1d);

   
   
   return ;
}
