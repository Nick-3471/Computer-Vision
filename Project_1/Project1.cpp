#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <vector>
#define pi 3.141592653589793
using namespace std;


void ReadImage(char name[], int ***fimage, int& M, int& N, int& Q);
void WriteImage(char fname[], int **fimage, int M, int N, int Q);
void Gauss (float s, int Hsize, float * H);




int main()
	{
	ifstream fin;
	ofstream fout;
	float* rect = new float [128];
	float* Sigma1 = new float[5];
	float* Sigma5 = new float[25];
	float* Sigma11 = new float[55];
	
	Gauss(1.0, 5, Sigma1);
	Gauss(5.0, 25, Sigma5);	
	Gauss(11.0, 55, Sigma11);
	
	int sig1_Half = 3;
	int sig5_Half = 13;
	int sig11_Half = 28;
	
	int sig1_Max = 5;
	int sig5_Max = 25;
	int sig11_Max = 55;
	
	float temp;
	int x;
	int y;
	
	fin.open("Rect_128.txt");
	for(int i = 0; i < 128; i++)
		{
		fin >> rect[i];
		}
	fin.close();
	
	
	for (int i = 0; i < 128; i++)
		{
		x = 0;
		y = sig11_Max;
		
		if(sig11_Half >= i)
			{
			x = sig11_Half - i - 1;  
			}
		if(i > 128 - sig11_Half)
			{
			y = sig11_Max - (i + 1);
			}
			
		for(int q = x; q < y; q++)
			{
			temp = temp + ((Sigma11[q]) * (rect[i - sig11_Half + q + 1]));
			}
		
		rect[i] = temp;
	
		}
	
	/*for(int i = 0; i < 5; i++)
		{
		cout.precision(9);
		cout << Sigma1[i] << " ";
		}
		cout << endl << endl;
	/*for(int i = 0; i < 25; i++)
		{
		cout.precision(9);
		cout << Sigma5[i] << " ";
		}
		cout << endl << endl;
	for(int i = 0; i < 55; i++)
		{
		cout.precision(9);
		cout << Sigma11[i] << " ";
		}
	cout << endl << endl;*/
	for(int i = 0; i < 128; i++)
		{
		cout.precision(5);
		cout << rect[i] << " ";
		}
	//ReadImage(lenna.pmg, 
	

	return 0;
	}



void Gauss (float s, int Hsize, float * H)

{
  /* Create a one-dimensional Gaussian mask
 "H" of scale "s" (sigma) on "Hsize" pixels.

   The values of the mask are scaled so that the
 sum of mask values = 1.0 
*/

	int     i;
  
	float  cst,tssq,x,sum;
 
  
	
	cst=1./(s*sqrt(2.0*pi));
  
	tssq=1./(2*s*s);
 
  
	for (i=0; i<Hsize; i++) 
	{
    
		x=(float)(i-Hsize/2);
    
		H[i]=(cst*exp(-(x*x*tssq)));
  
	}
 
  	
	sum=0.0;
  
	for (i=0;i<Hsize;i++)
    
		sum += H[i];
  
	for(i=0;i<Hsize;i++)
    
	H[i] /= sum;

}




void ReadImage(char fname[], int ***fimage, int& M, int& N, int& Q)
{
 int i, j;
 unsigned char *image;
 char header [100], *ptr;
 ifstream ifp;

 ifp.open(fname, ios::in); 

 if (!ifp) {
   cout << "Can't read image: " << fname << endl;
   exit(1);
 }

 // read header

 ifp.getline(header,100,'\n');
 if ( (header[0]!=80) ||    /* 'P' */
      (header[1]!=53) ) {   /* '5' */
      cout << "Image " << fname << " is not PGM" << endl;
      exit(1);
 }

 ifp.getline(header,100,'\n');
 while(header[0]=='#')
   ifp.getline(header,100,'\n');

 M=strtol(header,&ptr,0);
 N=atoi(ptr);

 ifp.getline(header,100,'\n');

 Q=strtol(header,&ptr,0);

 image = (unsigned char *) new unsigned char [M*N];

 *fimage = new int* [N];
 for(i=0; i<N; i++)
   (*fimage)[i] = new int[M];

 ifp.read( reinterpret_cast<char *>(image), (M*N)*sizeof(unsigned char));

 if (ifp.fail()) {
   cout << "Image " << fname << " has wrong size" << endl;
   exit(1);
 }

 ifp.close();

 //
 // Convert the unsigned characters to integers
 //

 for(i=0; i<N; i++)
   for(j=0; j<M; j++)
     (*fimage)[i][j]=(int)image[i*M+j];
}



void WriteImage(char fname[], int **fimage, int M, int N, int Q)
{
 int i, j;
 unsigned char *image;
 ofstream ofp;

 image = (unsigned char *) new unsigned char [M*N];

 // convert the integer values to unsigned char

 for(i=0; i<N; i++)
   for(j=0; j<M; j++)
     image[i*M+j]=(unsigned char)fimage[i][j];

 ofp.open(fname, ios::out);

 if (!ofp) {
   cout << "Can't open file: " << fname << endl;
   exit(1);
 }

 ofp << "P5" << endl;
 ofp << M << " " << N << endl;
 ofp << Q << endl;

 ofp.write( reinterpret_cast<char *>(image), (M*N)*sizeof(unsigned char));

 if (ofp.fail()) {
   cout << "Can't write image " << fname << endl;
   exit(0);
 }

 ofp.close();

}








