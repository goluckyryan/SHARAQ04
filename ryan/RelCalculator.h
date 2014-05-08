#ifndef RelCalculator
#define RelCalculator

#include <TMath.h>
#include "constant.h"

Double_t LengthBytofBrho(Double_t tof, Double_t Brho, Double_t mass, Int_t Z){
   Double_t alpha = Z* Brho * cVaccum/mass ;
   Double_t beta  = alpha/TMath::Sqrt(1+alpha*alpha);
   return tof*beta*cVaccum;
}

Double_t betaByBrho(Double_t Brho, Double_t mass, Int_t Z){
   Double_t alpha = Z* Brho * cVaccum/mass ;
   return alpha/TMath::Sqrt(1+alpha*alpha);
}

Double_t tofByBrho(Double_t Length, Double_t Brho, Double_t mass,Int_t Z){
   Double_t alpha = Z* Brho * cVaccum/mass ;
   Double_t beta  = alpha/TMath::Sqrt(1+alpha*alpha);
   return Length/beta/cVaccum;
}

Double_t TKAByTof(Double_t Length, Double_t tof, Double_t mass, Int_t A){
   Double_t beta = Length/tof/cVaccum;
   Double_t gamma = 1/TMath::Sqrt(1-beta*beta);
   return (gamma-1)*mass/A;
}

Double_t TKAByBrho(Double_t Brho, Double_t mass, Int_t A, Int_t Z){
   Double_t alpha = Z* Brho * cVaccum/mass ;
   Double_t beta  = alpha/TMath::Sqrt(1+alpha*alpha);
   Double_t gamma = 1/TMath::Sqrt(1-beta*beta);
   return (gamma-1)*mass/A;
}

Double_t BrhoByTKA(Double_t TKA, Double_t mass, Int_t Z){
   Double_t beta = TMath::Sqrt(2*mass*TKA+TKA*TKA)/(mass+TKA);
   Double_t gamma = 1/TMath::Sqrt(1-beta*beta);
   return gamma*beta*mass/Z/cVaccum;
}

Double_t tofByTKA(Double_t Length, Double_t TKA, Double_t mass, Int_t A){
   Double_t gamma = 1 + TKA*A/mass;
   Double_t beta  = TMath::Sqrt(1- 1/gamma/gamma);
   return = Length/beta/cVaccum;
}

Double_t CMtoLabTheta(Double_t TKA, Double_t cmTheta){
   Double_t a = TKA/2/mp;
   return TMath::ATan(TMath::Tan(cmTheta*TMath::DegToRad()/2)/TMath::Sqrt(1+a))*TMath::RadToDeg();
}

Double_t LabtoCMTheta(Double_t TKA, Double_t LabTheta){
   Double_t a = TKA/2/mp;
   return 2*TMath::ATan(TMath::Tan(LabTheta*TMath::DegToRad())*TMath::Sqrt(1+a))*TMath::RadToDeg();
}

#endif
