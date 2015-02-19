/*//////////////////////////////////////////////////////////////////
Project 1
Problem 3
Nicholas Smith
Collaboration with Brian Goga
//////////////////////////////////////////////////////////////////*/

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
	//Read in
	int** myImageL;


	//scale
	int** LImage256;
	int** LImage128;
	int** LImage64;
	int** LImage32;

	int** LImage128_P;
	int** LImage64_P;
	int** LImage32_P;

	//Write out
	int** Image_lenna;

	int M, N, Q;
	int S;

	char LFile[10] = "lenna.pgm";


	char Lout_256[20] = "lenna_256.pgm";
	char Lout_128[20] = "lenna_128.pgm";
	char Lout_64[20] = "lenna_64.pgm";
	char Lout_32[20] = "lenna_32.pgm";

	ReadImage(LFile, &myImageL, M, N, Q);

	//Initializing
	LImage256 = new int* [N];
	for(int i=0; i<N; i++)
		(LImage256)[i] = new int[M];


	LImage128 = new int* [N/2];
	LImage128_P = new int* [N/2];
	for(int i=0; i<N/2; i++)
	{
		(LImage128)[i] = new int[M/2];
		(LImage128_P)[i] = new int[M/2];
	}

	LImage64 = new int* [N/4];
	LImage64_P = new int* [N/4];
	for(int i=0; i<N/4; i++)
	{
		(LImage64)[i] = new int[M/4];
		(LImage64_P)[i] = new int[M/4];
	}

	LImage32 = new int* [N/8];
	LImage32_P = new int* [N/8];
	for(int i=0; i<N/8; i++)
	{
		(LImage32)[i] = new int[M/4];
		(LImage32_P)[i] = new int[M/4];
	}



//Smooth
float* Sigma1 = new float[25];
float Sig1[5][5];

Gauss(1.0, 5 , Sigma1);

for(int n = 0; n < 5; n++)
{
	for(int g = 0; g < 5; g++)
	{
		Sig1[n][g] = Sigma1[n] * Sigma1[g];
	}
}

//Scale of 1
for(int t = 0; t < N; t++)
{
	for(int r = 0; r < M; r++)
	{
		S = 0.0;
		for(int z = 0; z < 5; z++)
		{
			for(int h = 0; h < 5; h++)
			{
				if( (r - z + 5 / 2) < 0 || (r - z + 5 / 2) >= N || 
					(t - h + 5 / 2) < 0 || (t - h + 5 / 2) >= M )
				{
					S += 0.0;
				}
				else
				{
					S += Sig1[z][h] * myImageL[r - z + 5 / 2][t - h + 5 / 2];
				}
			}
		}
		LImage256[r][t] = S;
	}
}

cout << "----Printing Scale of 1----" << endl;

WriteImage(Lout_256, LImage256, M, N, Q);

//Scale 2
for(int r = 1; r < N; r+=2)
{
	for(int c = 1; c < M; c+=2)
	{
		LImage128_P[r/2][c/2] = LImage256[r][c];
	}
}

for(int t = 0; t < N/2; t++)
{
	for(int r = 0; r < M/2; r++)
	{
		S = 0.0;
		for(int z = 0; z < 5; z++)
		{
			for(int h = 0; h < 5; h++)
			{
				if( (r - z + 5 / 2) < 0 || (r - z + 5 / 2) >= N/2 || 
					(t - h + 5 / 2) < 0 || (t - h + 5 / 2) >= M/2 )
				{
					S += 0.0;
				}
				else
				{
					S += Sig1[z][h] * LImage128_P[r - z + 5 / 2][t - h + 5 / 2];
				}
			}
		}
		LImage128[r][t] = S;
	}
}

cout << "----Printing Scale of 2----" << endl;

WriteImage(Lout_128, LImage128, M/2, N/2, Q);


//Scale 4
for(int r = 1; r < N/2; r+=2)
{
	for(int c = 1; c < M/2; c+=2)
	{
		LImage64_P[r/4][c/4] = LImage128[r][c];
	}
}

for(int t = 0; t < N/4; t++)
{
	for(int r = 0; r < M/4; r++)
	{
		S = 0.0;
		for(int z = 0; z < 5; z++)
		{
			for(int h = 0; h < 5; h++)
			{
				if( (r - z + 5 / 2) < 0 || (r - z + 5 / 2) >= N/4 || 
					(t - h + 5 / 2) < 0 || (t - h + 5 / 2) >= M/4 )
				{
					S += 0.0;
				}
				else
				{
					S += Sig1[z][h] * LImage64_P[r - z + 5 / 2][t - h + 5 / 2];
				}
			}
		}
		LImage64[r][t] = S;
	}
}

cout << "----Printing Scale of 4----" << endl;

WriteImage(Lout_64, LImage64, M/4, N/4, Q);


//Scale 8
for(int r = 1; r < N/4; r+=2)
{
	for(int c = 1; c < M/4; c+=2)
	{
		LImage64_P[r/8][c/8] = LImage128[r][c];
	}
}

for(int t = 0; t < N/8; t++)
{
	for(int r = 0; r < M/8; r++)
	{
		S = 0.0;
		for(int z = 0; z < 5; z++)
		{
			for(int h = 0; h < 5; h++)
			{
				if( (r - z + 5 / 2) < 0 || (r - z + 5 / 2) >= N/8 || 
					(t - h + 5 / 2) < 0 || (t - h + 5 / 2) >= M/8 )
				{
					S += 0.0;
				}
				else
				{
					S += Sig1[z][h] * LImage32_P[r - z + 5 / 2][t - h + 5 / 2];
				}
			}
		}
		LImage32[r][t] = S;
	}
}

cout << "----Printing Scale of 8----" << endl;

WriteImage(Lout_32, LImage32, M/8, N/8, Q);
	return 0;
}

///////////////////////////////////////////////////////////////////////
//Functions
///////////////////////////////////////////////////////////////////////
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