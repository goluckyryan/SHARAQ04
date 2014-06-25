//void OpenAng_beamZgate(){
{   gROOT->Reset();
   gStyle->SetOptStat(0);
   
   const char * rootfile = "test.root";
   Double_t AngRange[2] = {70, 100};
   Int_t   nbin = (AngRange[1]-AngRange[0])*2;
   Bool_t S0imgExist = 0;
   Bool_t ResExist = 0;
   
   if ( S0imgExist ){
   	Double_t center[2]={0., 1.9}; //{0., 3.35}
   	Double_t radiusA = 11., radiusB = 15.;
   }
   Int_t widthZ = 50;
   Int_t startZ = -15;
   
   Bool_t hAngAutoMax = 0; 
   Int_t hAngMax = 5000;
   
   Double_t S0DtRange[2] = {-134, -126};
   Double_t S0DqRange[2] = {1000, 3500};

//########################################################################   
   TFile *f0 = new TFile (rootfile, "read");
   TTree *recoil = (TTree*)f0->Get("recoil");
   
   Int_t xDiv = 4, yDiv = 3;
   Double_t PadSize=300;
   TCanvas * cOpenAng = new TCanvas ("cOpenAng","cOpenAng", 0,0,PadSize*xDiv,PadSize*yDiv);
   cOpenAng->Divide(xDiv,yDiv);
   
   if ( S0imgExist ){
   	TString hS0imgTitle;
   	hS0imgTitle.Form("S0img (%4.2f,%4.2f|%5.2f, %5.2f)", center[0], center[1], radiusA, radiusB);
   	TH2F * hS0img = new TH2F ("S0img", hS0imgTitle, 100,-20, 20, 100,  -20, 20);
   }
   TH2F * hPIDDS = new TH2F ("PIDDS", "PID ds Res(0)", 100, S0DtRange[0], S0DtRange[1], 100, S0DqRange[0], S0DqRange[1]);
   
   const Int_t nhist = xDiv*yDiv;
   TH1F **hist = new TH1F[nhist];
   TH1F **histBeamZ = new TH1F[nhist];
   TString histName, histBeamZName;
   Int_t   VarGateRange[2];
   TString VarGateTitle;
   TCut    VarGate;
   TString drawTitle;
   THStack hs("hs", "stack");
   
//====================================  
	TCut crystalA, crystalB; 
   if ( S0imgExist ){
   	TString crystalTitle;
   	crystalTitle.Form("TMath::Power(s0x-%4.2f,2) + TMath::Power(s0y-%4.2f,2) >= %6.2f", center[0], center[1], radiusA*radiusA);
   	crystalA = crystalTitle;
   	crystalTitle.Form("TMath::Power(s0x-%4.2f,2) + TMath::Power(s0y-%4.2f,2) <= %6.2f", center[0], center[1], radiusB*radiusB);
   	crystalB = crystalTitle;
   }else{
   	crystalA = "";
   	crystalB = "";
	}
	
   TCut Etot = "E1+E2 >= 100";
   
   TCutG * ResO23F = new TCutG("ResO23F",6);
   ResO23F->SetVarX("tofS0D");
   ResO23F->SetVarY("QS0D");
   ResO23F->SetPoint(0,-129.1,1872.3);
   ResO23F->SetPoint(1,-126.1,2072.9);
   ResO23F->SetPoint(2,-125.7,1957.0);
   ResO23F->SetPoint(3,-127.7,1676.2);
   ResO23F->SetPoint(4,-128.2,1448.8);
   ResO23F->SetPoint(5,-129.1,1444.4);
   ResO23F->SetPoint(6,-129.1,1872.3);
   
   TCutG *ResO25F = new TCutG("ResO25F",4);
   ResO25F->SetVarX("tofS0D");
   ResO25F->SetVarY("QS0D");
   ResO25F->SetPoint(0,-132.72,2310.2);
   ResO25F->SetPoint(1,-132.38,2178.5);
   ResO25F->SetPoint(2,-126.38,3000.0);
   ResO25F->SetPoint(3,-126.73,3230.0);
   ResO25F->SetPoint(4,-132.72,2310.2);
   
   TCutG *ResN14O = new TCutG("ResN14O",5);
   ResN14O->SetVarX("tofS0D");
   ResN14O->SetVarY("QS0D");
   ResN14O->SetPoint(0,-69.2,1821.6);
   ResN14O->SetPoint(1,-69.0,1648.8);
   ResN14O->SetPoint(2,-66.4,1956.2);
   ResN14O->SetPoint(3,-62.9,2389.4);
   ResN14O->SetPoint(4,-64.3,2465.7);
   ResN14O->SetPoint(5,-69.2,1821.6);
   
   TCutG *ResC14O = new TCutG("ResC14O",6);
   ResC14O->SetVarX("tofS0D");
   ResC14O->SetVarY("QS0D");
   ResC14O->SetPoint(0,-69.0,1648.8);
   ResC14O->SetPoint(1,-68.8,1423.0);
   ResC14O->SetPoint(2,-66.4,1635.3);
   ResC14O->SetPoint(3,-61.8,2257.3);
   ResC14O->SetPoint(4,-62.9,2389.4);
   ResC14O->SetPoint(5,-66.4,1956.2);
   ResC14O->SetPoint(6,-69.0,1648.8);
   
   
   TCut ExtGate;
   if ( ResExist ){
	   ExtGate = crystalA + crystalB + Etot + "ResO25F";
   }else{
   	ExtGate = crystalA + crystalB + Etot;
	}
   ExtGate.Print();
   
   for (Int_t i = 0; i <xDiv*yDiv -3; i++){
      VarGateRange[0] = startZ + widthZ*(i-2);
      VarGateRange[1] = startZ + widthZ*(i+1-2) ;
      VarGateTitle.Form("wbeamZ > %5d && wbeamZ < %5d", VarGateRange[0], VarGateRange[1]);
      
      VarGate.Clear();
      VarGate += VarGateTitle;
      VarGate.Print();
      histName.Form("hist[%d]",i);
      hist[i] = new TH1F(histName, VarGateTitle, nbin, AngRange[0],AngRange[1]);
      if (hAngAutoMax)hist[i]->SetMaximum(hAngMax);
      hist[i]->SetXTitle("OpenAng [degree]");
      TString hAngYTitle;
      hAngYTitle.Form("count / %3.1f degree",(AngRange[1]-AngRange[0])/nbin);
      hist[i]->SetYTitle(hAngYTitle);
      hist[i]->GetYaxis()->SetTitleOffset(1.5);
      hist[i]->SetMinimum(0);
      hist[i]->SetFillColor(i+1);
      
      histBeamZName.Form("histBeamZ[%d]",i);
      histBeamZ[i] = new TH1F(histBeamZName, "beamZ", 200, startZ + widthZ*(-2), startZ + widthZ*(xDiv*yDiv-5));
      histBeamZ[i]->SetFillColor(i+1);
      
      cOpenAng->cd(i+1);
      
      drawTitle.Form("wbeamZ>>histBeamZ[%d]",i);
      recoil->Draw(drawTitle, VarGate && ExtGate);
      hs.Add(histBeamZ[i]);
      
      drawTitle.Form("(theta1+theta2)*TMath::RadToDeg()>>hist[%d]",i);
      recoil->Draw(drawTitle, VarGate && ExtGate);
      //hs.Add(hist[i]);
   }
   
   TString Text;
	TLatex text;
   
   cOpenAng->cd(xDiv*yDiv-2);
   hs.Draw();
   cOpenAng->cd(xDiv*yDiv-1);
   if ( S0imgExist ){
		Int_t countS0img = recoil->Draw("s0y:s0x>>S0img", ExtGate, "colz");
		text.SetNDC();
		text.SetTextColor(1);
		Text.Form("count:%d",countS0img);
		text.DrawText(0.15, 0.8, Text); 
		TLine line;
		Int_t nPt = 20;
		for ( Int_t i = 0; i < nPt; i++){
		   line.DrawLine(center[0] + radiusA*TMath::Cos(2*TMath::Pi()*i/nPt),
		                 center[1] + radiusA*TMath::Sin(2*TMath::Pi()*i/nPt),
		                 center[0] + radiusA*TMath::Cos(2*TMath::Pi()*(i+1)/nPt),
		                 center[1] + radiusA*TMath::Sin(2*TMath::Pi()*(i+1)/nPt));
		}
   	for ( Int_t i = 0; i < nPt; i++){
      	line.DrawLine(center[0] + radiusB*TMath::Cos(2*TMath::Pi()*i/nPt),
      	              center[1] + radiusB*TMath::Sin(2*TMath::Pi()*i/nPt),
      	              center[0] + radiusB*TMath::Cos(2*TMath::Pi()*(i+1)/nPt),
      	              center[1] + radiusB*TMath::Sin(2*TMath::Pi()*(i+1)/nPt));
   	}
   }
   cOpenAng->cd(xDiv*yDiv);
   if ( ResExist ){
   	recoil->Draw("QS0D:tofS0D>>PIDDS", ExtGate, "colz");
   	ResO25F->Draw("same");
   }
   cOpenAng->cd(1);
   text.DrawText(0.15, 0.8, rootfile); 
   text.DrawText(0.15, 0.75, "PID gated");
   text.DrawText(0.15, 0.7, "ppcoin");
   text.DrawText(0.15, 0.65, "MWDCTracked");
   text.DrawText(0.15, 0.6, Etot.GetTitle());   
   
   return;
   
}
