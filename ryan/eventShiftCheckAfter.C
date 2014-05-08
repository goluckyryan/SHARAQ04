#include <unistd.h>

void eventShiftCheckAfter() {   
   
   const char* rootfile="ppcoin10XX_es.root";
   Bool_t alldata   = 1;
   Int_t div = 100;
   Int_t firstEntry=  00000;
   Int_t endEntry  = 100;
   
   Double_t SMGate[2] = {-125, -100};
   Double_t F3Gate[2] = {-1465, -1458};
   
   Int_t SMThershold = 80;
   Int_t F3Thershold = 10;

//################################################################
   Double_t dataF3[50], dataSM[50];
   Int_t    ev, nCom, nCom2;
   TFile *f = new TFile(rootfile,"read");
   TTree *es_corr = (TTree*)f->Get("es_corr");   
   Int_t tnEntry = es_corr->GetEntries();
   es_corr->SetBranchAddress("eventID",&ev);
   es_corr->SetBranchAddress("nCom",&nCom);
   es_corr->SetBranchAddress("tDiffF3",dataF3);
   es_corr->SetBranchAddress("nHitFH9V1190",&nCom2);
   es_corr->SetBranchAddress("tDiffSM",dataSM);
   
   if (alldata) {
      firstEntry =0; 
      endEntry = tnEntry;
   }
   
   es_corr->GetEntry(0);
   Int_t firstEventID = ev; 
   printf(" first event :%10d Num event:%10d \n",firstEventID,tnEntry);
   
//###################################################################
   Int_t countF3 = 0, countSM = 0;
   Double_t ymax;
   Bool_t flag = 1;

   TH2F* h2D_F3 = new TH2F("h2D_F3","h2D_F3",(endEntry-firstEntry)/div,firstEntry/div,endEntry/div, 20, 0, 100);
   TH1F* h1D_F3 = new TH1F("h1D_F3","h1D_F3",100,0,100);
   
   TH2F* h2D_SM = new TH2F("h2D_SM","h2D_SM",(endEntry-firstEntry)/div,firstEntry/div,endEntry/div, 20, 0, 100);
   TH1F* h1D_SM = new TH1F("h1D_SM","h1D_SM",100,0,100);

   TCanvas* c3 = new TCanvas("c3", "check", 1000, 250, 800, 600);
   c3->Divide(2,2);
   
//#################################################################   
   for ( Int_t i = firstEntry; i < endEntry ; i++){
      es_corr->GetEntry(i);
      for (Int_t j = 0; j < nCom; j++){
         if(dataF3[j]> F3Gate[0] && dataF3[j] <F3Gate[1] ){
            countF3 = countF3 + 1;
         }
      }      
      for (Int_t j = 0; j < nCom2; j++){
         if(dataSM[j]> SMGate[0] && dataSM[j] < SMGate[1]){
            countSM = countSM + 1;
         }
      }
      
      if( i%div == 0 && i != firstEntry){
         h2D_F3->Fill(i/div,countF3);
         h1D_F3->Fill(countF3);
         h2D_SM->Fill(i/div,countSM);
         h1D_SM->Fill(countSM);
         if ((countF3 <=F3Thershold || countSM <= SMThershold) && flag) {
            printf("============ countF3:%3d,countSM:%3d@%10d\n",countF3,countSM,i-div);
            flag = 0;
         }
         countF3  = 0;
         countSM = 0;
      }
      if( i%5000 ==0) printf("entry# %10d, ev:%10d \n",i, ev);
   }
      
   c3->cd(1);
   h2D_SM->Draw("colz");
   c3->cd(2);
   h1D_SM->Draw();
   c3->cd(3);
   h2D_F3->Draw("colz");
   c3->cd(4);
   h1D_F3->Draw();
   
   return ;
}
