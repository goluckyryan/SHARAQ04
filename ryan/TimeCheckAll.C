void TimeCheckAll(){

   TFile *fa = new TFile ("TimeCheck14.root");
   TTree *phys14 = (TTree*)fa->Get("recoil");
   Int_t totEvNuma = phys14->GetEntries();
   
   TFile *fb = new TFile ("TimeCheckproton.root");
   TTree *proton = (TTree*)fb->Get("recoil");
   Int_t totEvNumb = proton->GetEntries();
   
   TFile *fc = new TFile ("TimeCheck22_clean_0.root");
   TTree *phys22 = (TTree*)fc->Get("recoil");
   Int_t totEvNumc = phys22->GetEntries();
   
   TFile *fd = new TFile ("TimeCheck23_clean_0.root");
   TTree *phys23 = (TTree*)fd->Get("recoil");
   Int_t totEvNumd = phys23->GetEntries();
   
   
   printf("===========================\n");
   printf("Phys14:%10d, Proton:%10d, Phys22:%10d, Phys23:%10d\n", totEvNuma, totEvNumb, totEvNumc, totEvNumd);
   
   TCanvas * cTimeCheck = new TCanvas("cTimeCheck", "Time Check", 100, 50, 800,800);
   cTimeCheck->Divide(2,2);
   
   TH1F* hV1190a = new TH1F("V1190a", "tFH1V1190 - tF3V1190", 200, -1470, -1420);
   TH1F* hV1190b = new TH1F("V1190b", "tFH1V1190 - tF3V1190", 200, -1470, -1420);
   TH1F* hV1190c = new TH1F("V1190c", "tFH1V1190 - tF3V1190", 200, -1470, -1420);
   TH1F* hV1190d = new TH1F("V1190d", "tFH1V1190 - tF3V1190", 200, -1470, -1420);
   hV1190a->SetLineColor(4);
   hV1190b->SetLineColor(2);
   hV1190c->SetLineColor(8);
   hV1190d->SetLineColor(1);
   
   TH1F* hV775a = new TH1F("V775a", "tFH1V775 - tF3V775", 200, -330, -290);
   TH1F* hV775b = new TH1F("V775b", "tFH1V775 - tF3V775", 200, -330, -290);
   TH1F* hV775c = new TH1F("V775c", "tFH1V775 - tF3V775", 200, -330, -290);
   TH1F* hV775d = new TH1F("V775d", "tFH1V775 - tF3V775", 200, -330, -290);
   hV775a->SetLineColor(4);
   hV775b->SetLineColor(2);
   hV775c->SetLineColor(8);
   hV775d->SetLineColor(1);
   
   TH1F* h1a = new TH1F("t1a", "t1 - tFH1V775", 200, 0, 30);
   TH1F* h1b = new TH1F("t1b", "t1 - tFH1V775", 200, 0, 30);
   TH1F* h1c = new TH1F("t1c", "t1 - tFH1V775", 200, 0, 30);
   TH1F* h1d = new TH1F("t1d", "t1 - tFH1V775", 200, 0, 30);
   h1a->SetLineColor(4);
   h1b->SetLineColor(2);
   h1c->SetLineColor(8);
   h1d->SetLineColor(1);
   
   TH1F* h2a = new TH1F("t2a", "t2 - tFH1V775", 200, 0, 30);
   TH1F* h2b = new TH1F("t2b", "t2 - tFH1V775", 200, 0, 30);
   TH1F* h2c = new TH1F("t2c", "t2 - tFH1V775", 200, 0, 30);
   TH1F* h2d = new TH1F("t2d", "t2 - tFH1V775", 200, 0, 30);
   h2a->SetLineColor(4);
   h2b->SetLineColor(2);
   h2c->SetLineColor(8);
   h2d->SetLineColor(1);
   
   TLatex text;
   text.SetNDC();
   
   TCut cut = "runNum < 44";

   cTimeCheck->cd(1);   
   phys14->Draw("tdiffV1190>>V1190a");
   proton->Draw("tdiffV1190>>V1190b","","same");
   phys22->Draw("tdiffV1190>>V1190c","","same");
   phys23->Draw("tdiffV1190>>V1190d","","same");
   hV1190a->Scale(2.5/totEvNuma);
   hV1190b->Scale(1./totEvNumb);
   hV1190c->Scale(0.5/totEvNumc);
   hV1190d->Scale(0.5/totEvNumd);
   text.SetTextColor(4);
   text.DrawText(0.2, 0.3, "Phys14");
   text.SetTextColor(2);
   text.DrawText(0.2, 0.25, "Proton");
   text.SetTextColor(8);
   text.DrawText(0.2, 0.2, "Phys22");
   text.SetTextColor(1);
   text.DrawText(0.2, 0.15, "Phys23");

   cTimeCheck->cd(2);
   phys14->Draw("tdiffV775>>V775a");
   proton->Draw("tdiffV775>>V775b","","same");
   phys22->Draw("tdiffV775>>V775c","","same");
   phys23->Draw("tdiffV775>>V775d","","same");
   hV775a->Scale(3./totEvNuma);
   hV775b->Scale(1./totEvNumb);
   hV775c->Scale(0.7/totEvNumc);
   hV775d->Scale(0.5/totEvNumd);

   cTimeCheck->cd(3);
   phys14->Draw("tdiff1>>t1a");
   proton->Draw("tdiff1>>t1b","","same");
   phys22->Draw("tdiff1>>t1c","","same");
   phys23->Draw("tdiff1>>t1d","","same");
   h1a->Scale(2./totEvNuma);
   h1b->Scale(1./totEvNumb);
   h1c->Scale(2./totEvNumc);
   h1d->Scale(2./totEvNumd);

   cTimeCheck->cd(4);
   phys14->Draw("tdiff2>>t2a");
   proton->Draw("tdiff2>>t2b","","same");
   phys22->Draw("tdiff2>>t2c","","same");
   phys23->Draw("tdiff2>>t2d","","same");
   h2a->Scale(3.1/totEvNuma);
   h2b->Scale(1./totEvNumb);
   h2c->Scale(2./totEvNumc);
   h2d->Scale(2./totEvNumd);
   
   printf("===============================\n");
   printf("         Phys14       Proton      Phys22      Phys23\n");
   printf("V1190 |%10.2f|%10.2f|%10.2f|%10.2f\n", 
                   hV1190a->GetBinCenter(hV1190a->GetMaximumBin()), 
                   hV1190b->GetBinCenter(hV1190b->GetMaximumBin()),
                   hV1190c->GetBinCenter(hV1190c->GetMaximumBin()),
                   hV1190d->GetBinCenter(hV1190d->GetMaximumBin()));
   printf("V775  |%10.2f|%10.2f|%10.2f|%10.2f\n", 
                   hV775a->GetBinCenter(hV775a->GetMaximumBin()), 
                   hV775b->GetBinCenter(hV775b->GetMaximumBin()),
                   hV775c->GetBinCenter(hV775c->GetMaximumBin()),
                   hV775d->GetBinCenter(hV775d->GetMaximumBin()));
   printf("t1    |%10.2f|%10.2f|%10.2f|%10.2f\n", 
                   h1a->GetBinCenter(h1a->GetMaximumBin()), 
                   h1b->GetBinCenter(h1b->GetMaximumBin()),
                   h1c->GetBinCenter(h1c->GetMaximumBin()),
                   h1d->GetBinCenter(h1d->GetMaximumBin()));
   printf("t2    |%10.2f|%10.2f|%10.2f|%10.2f\n", 
                   h2a->GetBinCenter(h2a->GetMaximumBin()), 
                   h2b->GetBinCenter(h2b->GetMaximumBin()),
                   h2c->GetBinCenter(h2c->GetMaximumBin()),
                   h2d->GetBinCenter(h2d->GetMaximumBin()));
   
   return;
}
