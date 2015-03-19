void test(TString rootfile, TString branch_name){

//############################################################################
  TFile *f = new TFile(rootfile,"read");
  printf(">> %s <<< is loaded.\n",rootfile.Data());
  TTree *tree = (TTree*)f->Get("tree");
  Int_t totEntries = tree->GetEntries();
  printf("totEntries:%d, \n", totEntries);

//############################################################################   
  tree->SetBranchStatus("*",0);
  tree->SetBranchStatus(branch_name,1);

  //TClonesArray    *plaV775 = 0;
  //TBranch        *b_plaV775;   //!
  //tree->SetBranchAddress("plaV775", &plaV775, &b_plaV775);

  //art::TTimingChargeData * event = new art::TTimingChargeData();
  //TBranch * branch = tree->GetBranch(branch_name);
  //branch->SetAddress(&event);
  
  TClonesArray  *hoge = 0;
  tree->SetBranchAddress(branch_name,&hoge);
  
  
//############################################################################  
  for( Int_t eventID = 0; eventID < totEntries; eventID ++){
    tree->GetEntry(eventID,0);

    //b_plaV775->GetEntry(eventID);
    
    
    hoge->Clear();
    
    //event->Clear();
    //________________________________ Get S0D charge
    //Int_t nHit = hoge_v775->GetEntriesFast();
    //for( Int_t p = 0; p < nHit; p++){
    //  Int_t ID = ((art::TTimingChargeData*)hoge_v775->At(p))->GetID();
    //}

  }

//############################################################################

}
