/****************************
all units are: mm, ns, MeV
****************************/

#ifndef constant
#define constant

#include <TMath.h>

const Double_t cVaccum=299.792458; //speed of light [mm/ns]
const Double_t mp = 938.272;
const Double_t mn = 939.565;
const Double_t me = 0.5109989;
const Double_t mO14 = 13048.92336 - 8*me;
const Double_t mO22 = 20502.15215 - 8*me;
const Double_t mO24 = 22374.92640 - 8*me;
const Double_t mF23 = 21427.69175 - 9*me;
const Double_t mF25 = 23298.62270 - 9*me;

const Double_t deg2rad=0.01745329251;
const Double_t rad2deg=57.2957795131;

const Double_t L_F3FH9 = 74075.; 
const Double_t DbeamZ = 13.;
const Double_t L_FH9TGT = 12020.-1155. + DbeamZ;
const Double_t L_TGTCARBON = 150.;

const Double_t LENGTH_RATIO_FH9_TGT = L_FH9TGT/L_F3FH9;
const Double_t LENGTH_RATIO_FH9_cTGT = (L_FH9TGT + L_TGTCARBON)/L_F3FH9;

const Double_t z0 = 1012.37;
const Double_t        z0L =   0. ,         z0R =   0.;
const Double_t mwdcAngleL =  60. ,  mwdcAngleR = -60.;
const Double_t        x0L =   0. ,         x0R =   0.;
const Double_t        y0L =   0. ,         y0R =   0.;

const Double_t z0Tpla = 1400.;

const Double_t kInvalidD=TMath::QuietNaN();

#endif
