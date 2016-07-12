/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "../interface/RooDCBShape.h" 
#include "RooAbsReal.h" 
#include "RooAbsCategory.h" 
#include "RooMath.h" 
#include <math.h> 
#include "TMath.h" 

ClassImp(RooDCBShape); 

Double_t RooDCBShape::ApproxErf(Double_t arg) const
{
  static const double erflim = 5.0;
  if( arg > erflim )
    return 1.0;
  if( arg < -erflim )
    return -1.0;

  return RooMath::erf(arg);
}

RooDCBShape::RooDCBShape(const char *name, const char *title, 
                       RooAbsReal& _m,
                       RooAbsReal& _m0,
                       RooAbsReal& _sigma,
                       RooAbsReal& _alphaL,
                       RooAbsReal& _alphaR,
                       RooAbsReal& _nL,
                       RooAbsReal& _nR) :
  RooAbsPdf(name,title), 
  m("m","m",this,_m),
  m0("m0","m0",this,_m0),
  sigma("sigma","sigma",this,_sigma),
  alphaL("alphaL","alphaL",this,_alphaL),
  alphaR("alphaR","alphaR",this,_alphaR),
  nL("nL","nL",this,_nL),
  nR("nR","nR",this,_nR)
{ 
} 


RooDCBShape::RooDCBShape(const RooDCBShape& other, const char* name) :  
  RooAbsPdf(other,name), 
  m("m",this,other.m),
  m0("m0",this,other.m0),
  sigma("sigma",this,other.sigma),
  alphaL("alphaL",this,other.alphaL),
  alphaR("alphaR",this,other.alphaR),
  nL("nL",this,other.nL),
  nR("nR",this,other.nR)
{ 
} 



Double_t RooDCBShape::evaluate() const 
{ 
  Double_t t = (m-m0)/sigma;

  Double_t absAlphaL = fabs((Double_t)alphaL);
  Double_t absAlphaR = fabs((Double_t)alphaR);

  if (t >= -absAlphaL && t <= absAlphaR) {
    return exp(-0.5*t*t);
  }
  else if (t < -absAlphaL) {
    Double_t a = TMath::Power(nL/absAlphaL,nL)*exp(-0.5*absAlphaL*absAlphaL);
    Double_t b = nL/absAlphaL - absAlphaL;
    return a/TMath::Power(b - t, nL);
  }
  else {
    Double_t a = TMath::Power(nR/absAlphaR,nR)*exp(-0.5*absAlphaR*absAlphaR);
    Double_t b = nR/absAlphaR - absAlphaR;
    return a/TMath::Power(b + t, nR);
  }
} 



Int_t RooDCBShape::getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const  
{ 
  // LIST HERE OVER WHICH VARIABLES ANALYTICAL INTEGRATION IS SUPPORTED, 
  // ASSIGN A NUMERIC CODE FOR EACH SUPPORTED (SET OF) PARAMETERS 
  // THE EXAMPLE BELOW ASSIGNS CODE 1 TO INTEGRATION OVER VARIABLE X
  // YOU CAN ALSO IMPLEMENT MORE THAN ONE ANALYTICAL INTEGRAL BY REPEATING THE matchArgs 
  // EXPRESSION MULTIPLE TIMES

  if (matchArgs(allVars,analVars,m)) return 1 ; 
  return 0 ; 
} 



Double_t RooDCBShape::analyticalIntegral(Int_t code, const char* rangeName) const  
{ 
  // RETURN ANALYTICAL INTEGRAL DEFINED BY RETURN CODE ASSIGNED BY getAnalyticalIntegral
  // THE MEMBER FUNCTION x.min(rangeName) AND x.max(rangeName) WILL RETURN THE INTEGRATION
  // BOUNDARIES FOR EACH OBSERVABLE x

  static const double sqrtPiOver2 = 1.2533141373;
  static const double sqrt2 = 1.4142135624;

  assert(code==1) ; 
  double result = 0.0;
  bool useLogL = false;
  bool useLogR = false;

  if (fabs(nL-1.0) < 1.e-05)
    useLogL = true;
  if (fabs(nR-1.0) < 1.e-05)
    useLogR = true;

  double sig = fabs((Double_t)sigma);
  double absAlphaL = fabs((Double_t)alphaL);
  double absAlphaR = fabs((Double_t)alphaR);

  double tmin = (m.min(rangeName)-m0)/sig;
  double tmax = (m.max(rangeName)-m0)/sig;

  if (tmin >= -absAlphaL && tmax <= absAlphaR) {
    result += sig * sqrtPiOver2 * (ApproxErf(tmax/sqrt2) - ApproxErf(tmin/sqrt2));
  }
  else if (tmax <= -absAlphaL) {
    Double_t a = TMath::Power(nL/absAlphaL,nL)*exp(-0.5*absAlphaL*absAlphaL);
    Double_t b = nL/absAlphaL - absAlphaL;

    if (useLogL) result += a*sig * (log(b-tmin) - log(b-tmax));
    else result += a*sig/(1.-nL) * (1./TMath::Power(b-tmin, nL-1.) - 1./TMath::Power(b-tmax, nL-1.));
  }
  else if (tmin >= -absAlphaR) {
    Double_t a = TMath::Power(nR/absAlphaR,nR)*exp(-0.5*absAlphaR*absAlphaR);
    Double_t b = nR/absAlphaR - absAlphaR;

    if (useLogR) result += a*sig * (log(b+tmax) - log(b+tmin));
    else result += a*sig/(1.-nR) * (1./TMath::Power(b+tmax, nR-1.) - 1./TMath::Power(b+tmin, nR-1.));
  }
  else if (tmin < -absAlphaL && tmax <= -absAlphaR) {
    Double_t a = TMath::Power(nL/absAlphaL,nL)*exp(-0.5*absAlphaL*absAlphaL);
    Double_t b = nL/absAlphaL - absAlphaL;

    if (useLogL) result += a*sig * (log(b-tmin) - log(nL/absAlphaL));
    else result += a*sig/(1.-nL) * (1./TMath::Power(b-tmin, nL-1.) - 1./TMath::Power(nL/absAlphaL, nL-1.));
    result += sig * sqrtPiOver2 * (ApproxErf(tmax/sqrt2) - ApproxErf(-absAlphaL/sqrt2));
  }
  else if (tmin >= -absAlphaL && tmax > -absAlphaR) {
    Double_t a = TMath::Power(nR/absAlphaR,nR)*exp(-0.5*absAlphaR*absAlphaR);
    Double_t b = nR/absAlphaR - absAlphaR;

    if (useLogR) result += a*sig * (log(b+tmax) - log(nR/absAlphaR));
    else result += a*sig/(1.-nR) * (1./TMath::Power(b+tmax, nR-1.) - 1./TMath::Power(nR/absAlphaR, nR-1.));
    result += sig * sqrtPiOver2 * (ApproxErf(-tmin/sqrt2) - ApproxErf(-absAlphaR/sqrt2));
  }
  else {
    Double_t aL = TMath::Power(nL/absAlphaL,nL)*exp(-0.5*absAlphaL*absAlphaL);
    Double_t bL = nL/absAlphaL - absAlphaL;
    Double_t aR = TMath::Power(nR/absAlphaR,nR)*exp(-0.5*absAlphaR*absAlphaR);
    Double_t bR = nR/absAlphaR - absAlphaR;

    if (useLogL) result += aL*sig * (log(bL-tmin) - log(nL/absAlphaL));
    else result += aL*sig/(1.-nL) * (1./TMath::Power(bL-tmin, nL-1.) - 1./TMath::Power(nL/absAlphaL, nL-1.));
    if (useLogR) result += aR*sig * (log(bR+tmax) - log(nR/absAlphaR));
    else result += aR*sig/(1.-nR) * (1./TMath::Power(bR+tmax, nR-1.) - 1./TMath::Power(nR/absAlphaR, nR-1.));
    result += sig * sqrtPiOver2 * (ApproxErf(absAlphaR/sqrt2) - ApproxErf(-absAlphaL/sqrt2));
  }

  return result; 
} 

