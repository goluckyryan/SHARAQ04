/*******************************************************************
Complete analysis of Proton-Proton Elastics Scattering
	1) Optics
		a) FH9 resolution
		b) S0img -> Hit ratio
	2) Scattering
		a) opening angle
		b) beamZ
		c) Sp
		d) counting
		e) polarization
		f) mean d.s.c.
**********************************************************************/
void Ana_PPES() {
   
//#####################    input                ##############################   
   const char* optifile="ppOptics_0729.root";
   const char* scatfile="ppAll_0724_multiOffset.root";
   Bool_t allentry  = 1;
   Int_t firstEntry = 0;
   Int_t nEntries=10000000;
   
//############################################################################
   TBenchmark clock;
   clock.Reset();
   clock.Start("timer");
   Bool_t shown = 0;


   TFile *f = new TFile(rootfile,"read");
   printf(">> %s <<< is loaded. ----> %s\n",rootfile, savefilename);
   TTree *tree = (TTree*)f->Get("tree");
   Int_t totnumEntry = tree->GetEntries();
   

   return ;
}
