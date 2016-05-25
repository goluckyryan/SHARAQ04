void Replot_fit(TH1F* h1a, TH1F* h1c, TH1F* h2, Bool_t plothk) {
   
   // replot the momementum with a fitted function.
   
   const int nBin = h1a->GetNbinsX();
   if( nBin != h1c->GetNbinsX()) return;
   
   printf("# of bin: %d\n", nBin);
   
   double xbin = new double[nBin];
   double ybin = new double[nBin];
   double Ymax = h2->GetMaximum();
   
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
   f1a->GetParameters(paraa);
   printf("reduced chi-squared = %f \n", f1a->GetChisquare()/f1a->GetNDF());  
   

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
   f1c->GetParameters(parac);
   printf("reduced chi-squared = %f \n", f1c->GetChisquare()/f1c->GetNDF());    

//========================================== fit for p + d

   TF1 * f1ab = new TF1("f1ab", "[6]*[0]*exp(-[2]/[1]*(x-[1]))*pow(x,[2])/pow([1],[2]) + [7]*[3]*exp(-[5]/[4]*(x-[4]))*pow(x,[5])/pow([4],[5])", 0, 400);
   Double_t paraab[8] = {paraa[0], paraa[1], paraa[2], parac[0], parac[1], parac[2], 0.5, 0.5};
   f1ab->SetParameters(paraab);
   //f1ab->SetParLimits(0, 0, paraa[0]*1.1);
   //f1ab->FixParameter(1, paraa[1]);
   //f1ab->FixParameter(2, paraa[2]);
   //f1ab->SetParLimits(3, 0, parac[0]*1.1);
   //f1ab->FixParameter(4, parac[1]);
   //f1ab->FixParameter(5, parac[2]);
   
   f1ab->FixParameter(0, paraa[0]);
   f1ab->FixParameter(1, paraa[1]);
   f1ab->FixParameter(2, paraa[2]);
   f1ab->FixParameter(3, parac[0]);
   f1ab->FixParameter(4, parac[1]);
   f1ab->FixParameter(5, parac[2]);
   f1ab->SetParLimits(6, 0, 2);
   f1ab->SetParLimits(7, 0, 2);
   
   //f1ab->GetParameters(paraab);
   
   f1ab->SetLineColor(3);
   h2->Fit("f1ab","R");
   printf("reduced chi-squared = %f \n", f1ab->GetChisquare()/f1ab->GetNDF());    
   
   Double_t sa = f1ab->GetParameter(6);
   Double_t sc = f1ab->GetParameter(7);
   Double_t ea = f1ab->GetParError(6);
   Double_t ec = f1ab->GetParError(7);
   
   f1a->SetParameter(0, sa*paraa[0]);
   f1c->SetParameter(0, sc*parac[0]);

   // Normalized 
   
   Double_t sum = sa + sc;
   Double_t sum_e = sqrt(ea*ea+ec*ec);
   
   Double_t x = sa / sum; Double_t ex = x* sqrt( sum_e*sum_e/sum/sum + ea*ea/sa/sa);
   Double_t y = sc / sum; Double_t ey = y* sqrt( sum_e*sum_e/sum/sum + ec*ec/sc/sc);
   

//==========================================
   
   //h2->SetMaximum(gMaxY+1);
   h2->SetFillColor(1);
   h2->SetFillStyle(3004);

   h2->Draw("E");
   h2->Draw("same");
   if( plothk) h1a->Draw("same");
   f1a->Draw("same");
   if( plothk) h1c->Draw("same");
   f1c->Draw("same");
   
   TString str;
   TLatex text;
   text.SetNDC();
   text.SetTextColor(2); str.Form("1d_{5/2}: %4.2f(%4.2f)", x, ex); text.DrawLatex( 0.55, 0.80, str);
   text.SetTextColor(4); str.Form("1p_{3/2}: %4.2f(%4.2f)", y, ey); text.DrawLatex( 0.55, 0.70, str);
   text.SetTextColor(1); str.Form("#chi^{2}: %4.2f", f1ab->GetChisquare()/f1ab->GetNDF()); text.DrawLatex( 0.55, 0.60, str);
   
   return ;
}
