void deleteSegBranch(){
   
   const char* rootfile="25F_new.root";
   const char* savefile="25F_newcopy.root";
   
//==================================================      
   TFile *oldfile = new TFile(rootfile,"read");
   TTree *tree = (TTree*)oldfile->Get("tree");
   printf("======== Copy a root file with selected Branches ==========\n");
   printf(" >>>> %s is loaded >>>>> save as: %s \n", rootfile, savefile);

//------ Get Branch name and onoff
   const Int_t nBranch = tree->GetNbranches(); 
   TObjArray * listBranch = tree->GetListOfBranches();
   TString *BranchName = new TString[nBranch];
   Int_t  * BranchSwitch = new Int_t[nBranch];
   for ( Int_t i = 0; i< nBranch ; i++){
      BranchName[i] = listBranch->At(i)->GetName();
      printf("Branch:%3d  | %14s , Load(y,n) ? ", i, BranchName[i].Data());
      TString onoff;
      onoff.ReadLine(cin);
      if ( onoff == "y" ) {
         BranchSwitch[i] = 1;
      }else{
         BranchSwitch[i] = 0;
      }
   }
   
   tree->SetBranchStatus("*",0);
   for( Int_t i = 0; i < nBranch ; i++){
      tree->SetBranchStatus(BranchName[i],BranchSwitch[i]);
   }
   
   TFile *newfile = new TFile(savefile, "recreate");
   printf(" >>>> copying ..... \n");
   TTree *newtree = tree->CloneTree();
   
   newtree->Print();
   newfile->Write();
   newfile->Close();
   oldfile->Close();
   
   //delete tree;
   //delete newtree;
   //delete oldfile;
   //delete newfile;
   
   return ;
}
