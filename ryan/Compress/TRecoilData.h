
#ifndef TRECOILDATA_H
#define TRECOILDATA_H

#include "../constant.h"
#include "../RelCalculator.h"
#include "TLorentzVector.h" //(px, py, pz, E)

class TRecoilData{
public:
   Double_t fMass;
   Int_t fZ, fA, fN;

   Double_t fFlightLength;
   Double_t fTof;
   Double_t fBeta, fGamma;
   Double_t fTKA, fMomentum;
   Double_t fTheta, fPhi;
   //Double_t fTheta_AB, fPhi_AB;
   TLorentzVector f4Vector;
   Double_t fBeamZ, fBeamX;
   Bool_t  fOK;
   
   Double_t feBeamZ, feBeamX;

   TRecoilData();
   ~TRecoilData();
   void SetKinetic(Int_t id, Double_t &tof, Double_t &x, Double_t &y, Double_t &a, Double_t &b,
                             Double_t s0x, Double_t s0y,
                             Double_t &etof, Double_t &ex, Double_t &ey, Double_t &ea, Double_t &eb);
   void CalPPelastic(Int_t id, Double_t Einc,Double_t theta, Double_t phi);
   void CMFrame(Double_t Einc);
   void Print();

};

//Contructor
TRecoilData::TRecoilData(){
   fMass = mp;
   fZ    = 1;
   fA    = 1;
   fN    = 0;
   
   fFlightLength = kInvalidD;
   fBeta = kInvalidD;
   fTof  = kInvalidD;
   fGamma = kInvalidD;
   fTKA = kInvalidD;
   fMomentum = kInvalidD;
   fTheta = kInvalidD;
   fPhi = kInvalidD;
   fBeamZ = kInvalidD;
   feBeamZ = kInvalidD;
   fBeamX = kInvalidD;
   feBeamX = kInvalidD;
   fOK  = 0;
   
   f4Vector.SetXYZM(0,0,0, mp);
}


TRecoilData::~TRecoilData(){
}

void TRecoilData::SetKinetic(Int_t id, Double_t &tof, Double_t &x, Double_t &y, Double_t &a, Double_t &b,
                                       Double_t s0x, Double_t s0y,
                                       Double_t &etof, Double_t &ex, Double_t &ey, Double_t &ea, Double_t &eb){
   if ( TMath::IsNaN(x) == kInvalidD || TMath::IsNaN(y) == kInvalidD) return;
   if ( tof < z0Tpla / cVaccum ) return;

   Double_t PlaneAngle;
   
   fOK = 1;

   Double_t Xpos, Ypos, Zpos;   // lab frame coordiante
   Double_t Zmwdc, Xmwdc, Ymwdc; // lab frame coordiante
   if (id ==1) { // SMWDC-L
      PlaneAngle = mwdcAngleL;
      Zmwdc = z0+ z0L;//-DbeamZ*cos(PlaneAngle*deg2rad);
      Xmwdc = x + x0L;//+DbeamZ*sin(PlaneAngle*deg2rad);
      Ymwdc = y + y0L;
   }else if(id = 2){
      PlaneAngle = mwdcAngleR;
      Zmwdc = z0+ z0R;//-DbeamZ*cos(PlaneAngle*deg2rad);
      Xmwdc = x + x0R;//-DbeamZ*sin(PlaneAngle*deg2rad);
      Ymwdc = y + y0R;
   }else{
      PlaneAngle = 0;
      return;
   }
   
   PlaneAngle = PlaneAngle*deg2rad;
   const Double_t cos = TMath::Cos(PlaneAngle);
   const Double_t sin = TMath::Sin(PlaneAngle);
   
   fBeamZ = (a *Zmwdc - Xmwdc)/(a * cos + sin);
   feBeamZ = TMath::Sqrt(TMath::Power((Xmwdc*cos + Zmwdc*sin)/(a * cos + sin)*ea,2) + ex*ex)/(a * cos + sin);
   feBeamZ = TMath::Abs(feBeamZ);

   fBeamX = (a *Zmwdc - Xmwdc)/(a * sin - cos);
   feBeamX = TMath::Sqrt(TMath::Power((Xmwdc*sin - Zmwdc*cos)/(a * sin - cos)*ea,2) + ex*ex)/(a * sin - cos);
   feBeamX = TMath::Abs(feBeamX);   

   if( TMath::IsNaN(s0x) ) s0x = 0;
   if( TMath::IsNaN(s0y) ) s0y = 0;
   
   if ( TMath::Abs(x) <10000 && TMath::Abs(y)<200){
      Xpos = sin*Zmwdc + cos*Xmwdc - s0x;
      Ypos = Ymwdc - s0y;
      Zpos = cos*Zmwdc - sin*Xmwdc - DbeamZ;
   }else{
      Xpos = kInvalidD;
      Ypos = kInvalidD;
      Zpos = kInvalidD;
      fOK = 0;
   }

   fFlightLength = TMath::Sqrt(Xpos*Xpos+Ypos*Ypos+Zpos*Zpos);
   fFlightLength = fFlightLength*z0Tpla/Zmwdc;

   if ( tof <= 0) {
      fBeta = kInvalidD;
      fOK = 0;
   }else{
      fBeta  = fFlightLength/cVaccum/tof;
   }

   fGamma = 1/sqrt(1-fBeta*fBeta);
   fTKA   = (fGamma-1)*fMass/fA;
   fMomentum = fGamma*fBeta*fMass;

   //fTheta = TMath::ATan2(TMath::Sqrt(Xpos*Xpos+Ypos*Ypos), Zpos);
   // range -90 ~ 270
   //fPhi   = TMath::ATan2(Ypos,Xpos);
   
   fTheta = acos((cos - sin*a)/sqrt(a*a+b*b+1));
   fPhi   = atan2(b,(sin + cos*a));
   if (fPhi < -TMath::PiOver2()){
      fPhi = fPhi + TMath::Pi()*2;
   }else if (fPhi > 3*TMath::PiOver2()){
      fPhi = fPhi - TMath::Pi()*2;
   }

   //printf(" fBeta:%5.3f fMomentum:%10.2f, fMass:%10.2f, Angle:(%10.2f,%10.2f)\n",fBeta,fMomentum, fMass, fTheta, fPhi);

   f4Vector.SetVectM(fMomentum,fMass); // (x,y,z,E) = ( momentum, 0, 0, Sqrt(momentum^2+mass^2);
   f4Vector.SetTheta(fTheta);
   f4Vector.SetPhi(fPhi);
   
   //f4Vector.Print();

}

void TRecoilData::CalPPelastic(Int_t id, Double_t Einc, Double_t theta, Double_t phi){
   if (TMath::IsNaN(Einc) == kInvalidD) continue;
   fTheta = theta*deg2rad;
   fPhi   = phi*deg2rad;

   Double_t PlaneAngle;//rad
   if (id == 1) {
      PlaneAngle = mwdcAngleL*deg2rad; 
   }else if ( id ==2 ){
      PlaneAngle = mwdcAngleR*deg2rad;
   }else{
      PlaneAngle = 0;
   }
   
   Double_t dirCosPlane[3] = {TMath::Sin(PlaneAngle),
                              0,
                              TMath::Cos(PlaneAngle)};

   Double_t dirCos[3] = {TMath::Cos(fPhi)*TMath::Sin(fTheta),
                         TMath::Sin(fPhi)*TMath::Sin(fTheta),
                                         TMath::Cos(fTheta)};

//   printf("dirCosPlane:(%10.3f,%10.3f,%10.3f)\n",dirCosPlane[0],dirCosPlane[1],dirCosPlane[2]);
//   printf("     dirCos:(%10.3f,%10.3f,%10.3f)\n",dirCos[0],dirCos[1],dirCos[2]);
   
   fFlightLength = 0;
   for (Int_t i = 0; i< 3; i++){
      fFlightLength += dirCosPlane[i]*dirCos[i]; // give the cos(IncAngle);
   }
//   printf(" cos:%10.3f",fFlightLength); 
   fFlightLength = z0Tpla/fFlightLength;
//   printf(" , FL:%10.3f\n", fFlightLength);
   
   const Double_t TanSq = TMath::Power(TMath::Tan(fTheta),2);
   fTKA = Einc/(1+ TanSq *(2*fMass+Einc)/(2*fMass));
   fMomentum = TMath::Sqrt(2*fMass*fTKA*fA + fTKA*fTKA*fA*fA );
   
   fBeta  = fMomentum/(fTKA*fA+fMass);
   fGamma = 1/TMath::Sqrt(1-fBeta*fBeta);
   fTof   = fFlightLength/fBeta/cVaccum;
   
//   printf(" TKA:%10.3f, Beta:%10.3f, tof:%10.3f\n",fTKA,fBeta,fTof);   
   //printf(" --- %f, %f, %f, %f, %f \n", fTheta, TanSq, Einc, fTKA, fMomentum);
   f4Vector.SetVectM(fMomentum,fMass); // (x,y,z,E) = ( momentum, 0, 0, Sqrt(momentum^2+mass^2);
   f4Vector.SetTheta(fTheta);
   f4Vector.SetPhi(fPhi);
   
}

void  TRecoilData::CMFrame(Double_t Einc){

   Double_t beta  = TMath::Sqrt(2*mp*Einc+Einc*Einc)/(Einc+2*mp);
   
   //printf(" boost: %7.5f\n", beta);
   
   f4Vector.Boost(0,0,-beta);
   
   fBeta  = f4Vector.Beta();
   fGamma = f4Vector.Gamma();
   fMomentum = f4Vector.Mag();
   fTKA   = f4Vector.E()-f4Vector.M(); // A = 1;
   fTheta = f4Vector.Theta();
   fPhi   = f4Vector.Phi();
   if (fPhi < -TMath::PiOver2()){
      fPhi = fPhi + TMath::Pi()*2;
   }else if (fPhi > 3*TMath::PiOver2()){
      fPhi = fPhi - TMath::Pi()*2;
   }
   
}

void TRecoilData::Print(){
   printf(" tof:%10.2f, fl:%10.2f, fBeta;%5.3f, fTKA:%10.2f\n",fTof, fFlightLength, fBeta, fTKA);
   f4Vector.Print();
}

#endif
