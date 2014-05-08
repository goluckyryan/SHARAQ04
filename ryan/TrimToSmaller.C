#include <TBenchmark.h>
#include <TFile.h>
#include <TMath.h>
#include <math.h>
#include <TTree.h>
#include <TList.h>
#include <TClonesArray.h>

void TrimToSmaller() {
   
//############################################################################   
   const char* savefile="25F_newcopyS.root";
   //const char* rootfile="Data/phys14_1_43.root";
   //const char* rootfile="ppDown.root";
   const char* rootfile="25F_newcopy.root";

//############################################################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;

   TFile *f = new TFile(rootfile,"read");
   TTree *tree = (TTree*)f->Get("tree");
   printf("======== Copy a root file with selected Branches ==========\n");
   printf(" >>>> %s is loaded >>>>> save as: %s \n", rootfile, savefile);   

   Int_t totnumEntry = tree->GetEntries();
   printf("====== totnumEntry:%d \n",totnumEntry);
      
   const Int_t nBranch = tree->GetNbranches(); 
   TObjArray * listBranch = tree->GetListOfBranches();
   TString *BranchName = new TString[nBranch];
   
   tree->SetBranchStatus("*",0);
   for( Int_t i = 0; i < nBranch ; i++){
      BranchName[i] = listBranch->At(i)->GetName();
      printf("Branch:%3d  | %14s , Loaded.\n", i, BranchName[i].Data());
      tree->SetBranchStatus(BranchName[i],1);
   }

   //Create a new file + a clone of old tree in new file
   TFile *newfile = new TFile(savefile,"recreate");
   TTree *newtree = tree->CloneTree(0);

//############################################################################

   art::TEventHeader *hoge_run;
   art::sh04::TP2PKinematicsData *hoge_p2p;
   tree->SetBranchAddress("eventheader",&hoge_run);
   tree->SetBranchAddress("p2p",&hoge_p2p);
   
   printf("====== start Triming .... \n");
   for (Int_t eventID=0; eventID<totnumEntry; eventID++) {
      tree->GetEntry(eventID);
      
      Int_t runNum = hoge_run->GetRunNumber();

      if (!TMath::Finite(hoge_p2p->GetSp())) continue;
     
      newtree->Fill();

//------------Clock      
      clock.Stop("timer");
      Double_t time = clock.GetRealTime("timer");
      clock.Start("timer");
      
      if ( !shown ) {
         if (fmod(time, 10) < 1 ){
            printf( "%10d[%2d%%](#%2d) |%3d min %5.2f sec | expect:%5.1fmin\n", 
            eventID, 
            TMath::Nint((eventID+1)*100./totnumEntry),
            runNum,
            TMath::Floor(time/60), time - TMath::Floor(time/60)*60,
            totnumEntry*time/(eventID+1)/60.);
            shown = 1;
         }
      }else{
         if (fmod(time, 10) > 9 ){
            shown = 0;
         }
      }

   }
   
   newtree->Print();
   newtree->AutoSave();
   delete f;
   delete newfile;

//############################################################################   

   clock.Stop("timer");
   printf("============ finished|%10.3f sec --> %s\n",clock.GetRealTime("timer"),savefilename);
   return ;
}
