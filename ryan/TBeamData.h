
#ifndef TBEAMDATA_H
#define TBEAMDATA_H

#include "constant.h"
#include "TLorentzVector.h" //(px, py, pz, E)

class TBeamData{
public:
   Double_t fBrho, fActualBrho; // fBrho is principle, rho is actual by PPAC
   Double_t fMass;
   Int_t fZ, fA, fN;
   Double_t fTofGate[2];
   Double_t fQGate[2];
   TString  fName;
   Double_t fSp;
   
   Double_t fToffsetV1190, fToffsetV775;
   Double_t fToffset1, fToffset2;
   
   Double_t fBeta, fGamma;
   Double_t fTKA, fMomentum, fTheta, fPhi;
   TLorentzVector f4Vector;
   
   Bool_t fppacOn;
   
   TBeamData();
   TBeamData(TString str);
   ~TBeamData();
   void UseProjectile(TString str);
   void SetKinetic(Double_t ActBrho, Double_t s0a, Double_t s0b);
   void Print();
protected:
   void DefaultGate();
   
};

//Contructor
TBeamData::TBeamData(){
   UseProjectile("proton");
   
   fActualBrho = fBrho;
   SetKinetic(fBrho, 0, 0);
}

TBeamData::TBeamData(TString str){
   DefaultGate();
   UseProjectile(str);
   
   fActualBrho = fBrho;
   SetKinetic(fBrho, 0, 0);
   
}

TBeamData::~TBeamData(){
}

void TBeamData::DefaultGate(){
   fTofGate[0]  = -9000;
   fTofGate[1]  = 9000;
   fQGate[0]    = 0;
   fQGate[1]    = 9000;
}

void TBeamData::UseProjectile(TString str){
   fName = str;
   DefaultGate();
   fToffsetV1190 = -1444.08;
   fToffsetV775  = -242.9;
   fToffset1 = 0;
   fToffset2 = 0;
   fppacOn   = 0;
   fSp       = 0;
   if (str == "proton"){
      fBrho = 2.4781;
      fMass = mp; fZ    = 1; fA    = 1; 
      fTofGate[0]  = -1450.; fTofGate[1]  = -1430.;
      fQGate[0]    =  5000.;  fQGate[1]   =  6000.;
      fToffsetV1190 = -1444.1;
      fToffsetV775  = -306.88;
      fToffset1 = 56.7;//12.82
      fToffset2 = 57.9;//11.62
   }else if ( str == "14O"){
      fBrho = 4.2; // 4.217 in datasheet. 
      fMass = mO14; fZ    = 8; fA    = 14; 
      fTofGate[0]  = -1446.; fTofGate[1]  = -1436.;
      fQGate[0]    =  5646.;  fQGate[1]   =  5930.;
      fToffsetV1190 = -1440.3;
      fToffsetV775  = -302.16;
      fToffset1 = 55.7;//14.62;
      fToffset2 = 57.1;//13.27;
      fppacOn  = 1;
      fSp  = 4.627;
      
   }else if ( str == "22O"){
      fBrho = 6.7288;
      fMass = mO22; fZ    = 8; fA    = 22; 
      fTofGate[0]  = -1448.; fTofGate[1]  = -1444.;
      fQGate[0]    =  5665.;  fQGate[1]   =  5905.;
      fToffsetV1190 = -1445.7;
      fToffsetV775  = -307.32;
      fToffset1 = 56.6;//13.12
      fToffset2 = 57.7;//12.07
      fSp  = 23.26;
      
   }else if ( str == "24O"){
      fBrho = 7.1315;
      fMass = mO24; fZ    = 8; fA    = 24; 
      fTofGate[0]  = -1442.; fTofGate[1]  = -1433.;
      fQGate[0]    =  5657.;  fQGate[1]   =  5915.;
      fToffset1 = 56.6;//13.12
      fToffset2 = 57.7;//12.07
      fppacOn  = 1;
      fSp = 27.1;
      
   }else if ( str == "23F"){
      fBrho = 6.7288;
      fMass = mF23; fZ    = 9; fA    = 23; 
      fTofGate[0]  = -1465.; fTofGate[1]  = -1461.;
      fQGate[0]    =  5767.;  fQGate[1]   =  6060.;
      fToffsetV1190 = -1462.88;
      fToffsetV775  = -324.58;
      fToffset1 = 56.6;
      fToffset2 = 57.7;
      fSp = 13.26;
      
   }else if ( str == "25F"){
      fBrho = 7.1315;
      fMass = mF25; fZ    = 9; fA    = 25;
      fTofGate[0]  = -1461.; fTofGate[1]  = -1453.;
      fQGate[0]    =  5750.;  fQGate[1]   =  6013.; 
      fToffsetV1190 = -1456.7;
      fToffsetV775  = -318.35;
      fToffset1 = 56.6-1.5;
      fToffset2 = 57.7-1.5;
      fppacOn  = 1;
      fSp = 14.43;
      
   }
   
   fN  = fA - fZ;  
   
}

void TBeamData::SetKinetic(Double_t ActBrho, Double_t s0a, Double_t s0b){
   if (TMath::IsNaN(ActBrho) == 1) return;
   if (TMath::IsNaN(s0a) == 1) return;
   if (TMath::IsNaN(s0b) == 1) return;
   fActualBrho = ActBrho;
   
   Double_t alpha = cVaccum * fZ * fActualBrho / fMass;// alpha = fGamma*fBeta
   
   fBeta  = alpha/sqrt(1+alpha*alpha);
   fGamma = 1/sqrt(1-fBeta*fBeta);
   fTKA   = (fGamma-1)*fMass/fA;
   fMomentum = fGamma*fBeta*fMass;
   
   if ( s0a || s0b) {
      fTheta = 0;
      fPhi   = 0;
   }else{
      fTheta = atan(sqrt(s0a*s0a+s0b*s0b));
      fPhi   = atan2(s0b, s0a);
   }
   
   f4Vector.SetVectM(fMomentum,fMass);
   f4Vector.SetTheta(fTheta);
   f4Vector.SetPhi(fPhi);

}

void TBeamData::Print(){
   printf("----%4s ------fBrho:%8.4f\n", fName.Data(),fBrho);
   printf("fMass:%7.2fMeV, fA:%2d, fZ:%2d, fN:%2d\n",fMass, fA, fZ, fN);
   printf("fTofGate:(%8.2f,%8.2f)\n", fTofGate[0],fTofGate[1]);
   printf("  fQGate:(%8.2f,%8.2f)\n", fQGate[0],fQGate[1]);
   printf(" time offset for V1190 :%10.4f ns\n", fToffsetV1190);
   printf(" time offset for V775  :%10.4f ns\n", fToffsetV775);
   printf(" time offset for Tpla1 :%10.4f ns\n", fToffset1);
   printf(" time offset for Tpla2 :%10.4f ns\n", fToffset2);
   printf("---------------------\n");   
}

#endif
