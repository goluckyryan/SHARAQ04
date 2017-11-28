void Replot_fit(TH1F* h1a, // 1d5/2 histogram
                TH1F* h1c, // 1p histogram
                TH1F* h2,  // fit target
                Int_t nFit, // 0 = fit for 1d5/2, 1 = fit for p, 2 = fit for d + p
                Bool_t fitFlag=1, // fit or using given p1, p2. 1 = fit
                Double_t p1 = 0.5, 
                Double_t p2 = 0.5, 
                Double_t sf = 1.0 // scaling factor
                ) {
   
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

   if (nFit == 2){

      TF1 * f1ab = new TF1("f1ab", "[6]*[0]*exp(-[2]/[1]*(x-[1]))*pow(x,[2])/pow([1],[2]) + [7]*[3]*exp(-[5]/[4]*(x-[4]))*pow(x,[5])/pow([4],[5])", 0, 400);
      Double_t paraab[8] = {paraa[0], paraa[1], paraa[2], parac[0], parac[1], parac[2], p1, p2};
      f1ab->SetParameters(paraab);
      f1ab->FixParameter(0, paraa[0]);
      f1ab->FixParameter(1, paraa[1]);
      f1ab->FixParameter(2, paraa[2]);
      f1ab->FixParameter(3, parac[0]);
      f1ab->FixParameter(4, parac[1]);
      f1ab->FixParameter(5, parac[2]);
      f1ab->SetParLimits(6, 0, 2);
      f1ab->SetParLimits(7, 0, 2);
      f1ab->SetLineColor(1);
      
      if ( fitFlag ) h2->Fit("f1ab","R");
      if ( !fitFlag) {
         f1ab->FixParameter(6, p1);
         f1ab->FixParameter(7, p2);
         h2->Fit("f1ab","R");
      }
      
      printf("reduced chi-squared = %f \n", f1ab->GetChisquare()/f1ab->GetNDF());    
      Double_t sa = f1ab->GetParameter(6);
      Double_t sc = f1ab->GetParameter(7);
      Double_t ea = f1ab->GetParError(6);
      Double_t ec = f1ab->GetParError(7);

      f1a->SetParameter(0, sa*paraa[0]);
      f1c->SetParameter(0, sc*parac[0]);
   
      // Normalized 
      //Double_t sum = sa + sc;
      //Double_t sum_e = sqrt(ea*ea+ec*ec);
      //Double_t x = sa / sum; Double_t ex = x* sqrt( sum_e*sum_e/sum/sum + ea*ea/sa/sa);
      //Double_t y = sc / sum; Double_t ey = y* sqrt( sum_e*sum_e/sum/sum + ec*ec/sc/sc);
      
      // not normalized
      Double_t x = sa; Double_t ex = ea;
      Double_t y = sc; Double_t ey = ec;
   
      //h2->SetMaximum(gMaxY+1);
      h2->SetFillColor(1);
      h2->SetFillStyle(3004);
   
      h2->Draw("E");
      h2->Draw("same");
      f1a->Draw("same");
      f1c->Draw("same");
      
      TString str;
      TLatex text;
      text.SetNDC();
      if( fitFlag) {
         text.SetTextColor(2); str.Form("1d_{5/2}: %4.2f(%4.2f)", x, ex); text.DrawLatex( 0.55, 0.80, str);
         text.SetTextColor(4); str.Form("1p_{3/2}: %4.2f(%4.2f)", y, ey); text.DrawLatex( 0.55, 0.70, str);
      }
      if( !fitFlag) {
         text.SetTextColor(2); str.Form("1d_{5/2}: %4.2f", x); text.DrawLatex( 0.55, 0.80, str);
         text.SetTextColor(4); str.Form("1p_{3/2}: %4.2f", y); text.DrawLatex( 0.55, 0.70, str);
      }
      text.SetTextColor(1); str.Form("#chi^{2}/ndf: %4.2f", f1ab->GetChisquare()/f1ab->GetNDF()/sf); 
      text.DrawLatex( 0.55, 0.60, str);
   
   }
   
   
   if( nFit == 0 || nFit == 1){
      TF1 * f1ab = new TF1("f1ab", "[3]*[0]*exp(-[2]/[1]*(x-[1]))*pow(x,[2])/pow([1],[2])", 0, 400);
      Double_t paraab[8] = {paraa[0], paraa[1], paraa[2], p1};
      f1ab->SetParameters(paraab);
      
      if( nFit == 0){
         f1ab->FixParameter(0, paraa[0]);
         f1ab->FixParameter(1, paraa[1]);
         f1ab->FixParameter(2, paraa[2]);
      }
      
      if( nFit == 1){
         f1ab->FixParameter(0, parac[0]);
         f1ab->FixParameter(1, parac[1]);
         f1ab->FixParameter(2, parac[2]);
      }
      
      f1ab->SetParLimits(3, 0, 2);
      
      f1ab->SetLineColor(3);
      h2->Fit("f1ab","R");
      printf("reduced chi-squared = %f \n", f1ab->GetChisquare()/f1ab->GetNDF());    
      Double_t sa = f1ab->GetParameter(3);
      Double_t ea = f1ab->GetParError(3);
      
      if( nFit == 0) f1a->SetParameter(0, sa*paraa[0]);
      if( nFit == 1) f1c->SetParameter(0, sa*parac[0]);
   
      // Normalized 
      
      Double_t sum = sa;
      Double_t sum_e = ea;
      
      Double_t x = sa / sa ; Double_t ex = ea / sa;
      
      //h2->SetMaximum(gMaxY+1);
      h2->SetFillColor(1);
      h2->SetFillStyle(3004);
   
      h2->Draw("E");
      h2->Draw("same");
      if( nFit == 0) f1a->Draw("same");
      if( nFit == 1) f1c->Draw("same");
      
      TString str;
      TLatex text;
      text.SetNDC();
      if( nFit == 0) {text.SetTextColor(2); str.Form("1d_{5/2}: %4.2f(%4.2f)", x, ex); text.DrawLatex( 0.55, 0.80, str);}
      if( nFit == 1) {text.SetTextColor(4); str.Form("1p_{3/2}: %4.2f(%4.2f)", x, ex); text.DrawLatex( 0.55, 0.70, str);}
      text.SetTextColor(1); str.Form("#chi^{2}/ndf: %4.2f", f1ab->GetChisquare()/f1ab->GetNDF()); text.DrawLatex( 0.55, 0.60, str);

   }
   
   
   if( nFit == -2){
      //delete f1ab;
      TF1 * f1ab = new TF1("f1ab", "[6]*[0]*exp(-[2]/[1]*(x-[1]))*pow(x,[2])/pow([1],[2]) + [7]*[3]*exp(-[5]/[4]*(x-[4]))*pow(x,[5])/pow([4],[5])", 0, 400);
      
      Double_t paraab[8] = {paraa[0], paraa[1], paraa[2], parac[0], parac[1], parac[2], p1, p2};
      
      f1ab->SetParameters(paraab);
      f1ab->FixParameter(0, paraa[0]);
      f1ab->FixParameter(1, paraa[1]);
      f1ab->FixParameter(2, paraa[2]);
      f1ab->FixParameter(3, parac[0]);
      f1ab->FixParameter(4, parac[1]);
      f1ab->FixParameter(5, parac[2]);
      f1ab->SetParLimits(6, 0, 2);
      f1ab->SetParLimits(7, 0, 2);
      f1ab->SetLineColor(3);
      
      Double_t ssr = 0;
      Double_t count = 0;
      for ( Int_t i = 1; i <= nBin; i++){
         Double_t xpos = h2->GetBinCenter(i);
         Double_t val  = h2->GetBinContent(i);
         Double_t diff = val - f1ab->Eval(xpos);
         Double_t err = h2->GetBinError(i);
         
         //if( val < 11){
         //   switch(val){
         //      case 0 : err = 2.44; break;
         //      case 1 : err = 3.36; break;
         //      case 2 : err = 3.91; break;
         //      case 3 : err = 4.42; break;
         //      case 4 : err = 4.60; break;
         //      case 5 : err = 5.0; break;
         //      case 6 : err = 5.47; break;
         //      case 7 : err = 5.53; break;
         //      case 8 : err = 5.99; break;
         //      case 9 : err = 6.30; break;
         //      case 10 : err = 6.5; break;
         //   }
         //}else{
         //   err = sqrt(val);
         //}
         
         if( err > 0 ) {
            ssr += diff*diff/err/err;
            count ++;
         }
         //printf("%f, %f, %f, %f\n", xpos, h2->GetBinContent(i), f1ab->Eval(xpos), diff); 
         
      }
      
      ssr = ssr/(count-2)/sf;
      
      printf("%f \n", ssr);
      
      //h2->Fit("f1ab","R");
      //printf("reduced chi-squared = %f \n", f1ab->GetChisquare()/f1ab->GetNDF());    
      Double_t sa = f1ab->GetParameter(6);
      Double_t sc = f1ab->GetParameter(7);

      f1a->SetParameter(0, sa*paraa[0]);
      f1c->SetParameter(0, sc*parac[0]);
   
      // Normalized 
      
      Double_t sum = sa + sc;
      
      Double_t x = sa / sum;
      Double_t y = sc / sum;
      
         //h2->SetMaximum(gMaxY+1);
      h2->SetFillColor(1);
      h2->SetFillStyle(3004);
   
      h2->Draw("E");
      h2->Draw("same");
      f1a->Draw("same");
      f1c->Draw("same");
      f1ab->Draw("same");
      
      TString str;
      TLatex text;
      text.SetNDC();
      text.SetTextColor(2); str.Form("1d_{5/2}: %4.2f", x); text.DrawLatex( 0.55, 0.80, str);
      text.SetTextColor(4); str.Form("1p_{3/2}: %4.2f", y); text.DrawLatex( 0.55, 0.70, str);
      text.SetTextColor(1); str.Form("#chi^{2}/ndf: %4.2f", ssr); text.DrawLatex( 0.55, 0.60, str);

   }
   //==========================================
   if( nFit == -4){
      //delete f1ab;
      TF1 * f1ab = new TF1("f1ab", "[6]*[0]*exp(-[2]/[1]*(x-[1]))*pow(x,[2])/pow([1],[2]) + [7]*[3]*exp(-[5]/[4]*(x-[4]))*pow(x,[5])/pow([4],[5])", 0, 400);

      Double_t step = 0.01;
      
      TH2F* hchi = new TH2F("chi", "", 1/step, 0, 1, 1/step, 0, 1);
      
      hchi->SetTitle(h2->GetTitle());
      hchi->SetXTitle("a");
      hchi->SetYTitle("b");
      
      for ( p1 = 0; p1 <= 1; p1 += step){
         for ( p2 = 0; p2 <= 1; p2 += step){
            Double_t paraab[8] = {paraa[0], paraa[1], paraa[2], parac[0], parac[1], parac[2], p1, p2};
            
            f1ab->SetParameters(paraab);
            f1ab->FixParameter(0, paraa[0]);
            f1ab->FixParameter(1, paraa[1]);
            f1ab->FixParameter(2, paraa[2]);
            f1ab->FixParameter(3, parac[0]);
            f1ab->FixParameter(4, parac[1]);
            f1ab->FixParameter(5, parac[2]);
            f1ab->SetParLimits(6, 0, 2);
            f1ab->SetParLimits(7, 0, 2);
            f1ab->SetLineColor(3);
            
            Double_t ssr = 0;
            Int_t count = 0;
            for ( Int_t i = 1; i <= nBin; i++){
               Double_t xpos = h2->GetBinCenter(i);
               Double_t val  = h2->GetBinContent(i);
               Double_t diff = val - f1ab->Eval(xpos);
               Double_t err = h2->GetBinError(i);
               
               //if( val < 11){
               //   switch(val){
               //      case 0 : err = 2.44; break;
               //      case 1 : err = 3.36; break;
               //      case 2 : err = 3.91; break;
               //      case 3 : err = 4.42; break;
               //      case 4 : err = 4.60; break;
               //      case 5 : err = 5.0; break;
               //      case 6 : err = 5.47; break;
               //      case 7 : err = 5.53; break;
               //      case 8 : err = 5.99; break;
               //      case 9 : err = 6.30; break;
               //      case 10 : err = 6.5; break;
               //   }
               //}else{
               //   err = sqrt(val);
               //}
               
               if( err > 0 ) {
                  ssr += diff*diff/err/err;
                  count ++;
               }
               //printf("%f, %f, %f, %f\n", xpos, h2->GetBinContent(i), f1ab->Eval(xpos), diff); 
               
            }
            
            //ssr = ssr/(nBin-2)/sf;
            ssr = ssr/(count-2)/sf;
            
            //printf("%f, %f, %f | %f\n", p1, p2, ssr, ssr_min);
            
            
            
            if( ssr < 2) hchi->Fill(p1-step/2,p2-step/2,ssr);
            //hchi->Fill(p1,p2,ssr);
   
         
            //if ( 0.05 > TMath::Abs(ssr-1.)){
            //   printf(" %f, %f, %f \n", p1,p2,ssr);
            //}
         }
      }

      //hchi->SetMinimum(0.5);
      hchi->Draw("colz");
   }   

   
   return ;
}
