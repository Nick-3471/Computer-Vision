/* **************************** */
/* First derivative of Gaussian */
/* **************************** */

#define pi 3.141592653589793

void Gauss_deriv1 (float s, int Hsize, float * H)
{
  int     i;
  float  x,cst,tssq;

  cst = 1.0/(s*s*s*sqrt(2.0*pi)) ;
  tssq = -1.0/(2.0*s*s) ;

  for (i=0; i<Hsize; i++) 
  {
    x = (float)(i-Hsize/2);
    H[i] = -x*cst*exp(x*x*tssq);
  }
}