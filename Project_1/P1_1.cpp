/*//////////////////////////////////////////////////////////////////
Project 1
Problem 1
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

void readFile(float* dest)
{
	ifstream fin("Rect_128.txt");

	//fin.open("Rect_128.txt");

	for(int i = 0; i < 128; i++)
	{

		fin >> dest[i];

	}
	fin.close();
}

float* mask(const float* Oigin, int maskSize, const float* mask)
{
	int maskHalf = maskSize / 2;
	float* result = new float[128];

	for (int i = 0; i < 128; ++i)
	{
		result[i] = 0.0;
		for(int q = -maskHalf; q <= maskHalf; ++q)
		{
			if(i + q >= 0 && i + q <= 127)
			{
				result[i] += Oigin[i + q] * mask[q + maskHalf];
			}
		}
	}
	return result;
}


int main()
{
	float rect[128];
	float* Sigma1 = new float [5];
	float* Sigma5 = new float [25];
	float* Sigma11 = new float [55];

	float* rect1;
	float* rect5;
	float* rect11; 



	readFile(rect);
///////////////////////////////////////////////////////////////////////
//Number 1 Part A
///////////////////////////////////////////////////////////////////////
//Sigma 1
Gauss(1.0, 5, Sigma1);
cout << "-------Sigma is of size 1-------" << endl;
rect1 = mask(rect, 5, Sigma1 );
for( int i = 0; i < 128; ++i )
	{
		cout << rect1[i] * 255.0 << ", ";
	}
delete[] rect1;
delete[] Sigma1;

//Sigma 5
Gauss(5.0, 25, Sigma5);
cout << endl << endl << "-------Sigma is of size 5-------" << endl;
rect5 = mask(rect, 25, Sigma5 );
for(int q = 0; q < 128; q++)
{
	cout << rect5[q] * 255.0 << ", ";
}
delete[] rect5;
delete[] Sigma5;

//Sigma 11
Gauss(11.0, 55, Sigma11);
cout << endl << endl << "-------Sigma is of size 11-------" << endl;
rect11 = mask(rect, 55, Sigma11 );
for(int q = 0; q < 128; q++)
{
	cout << rect11[q] * 255.0 << ", ";
}
delete[] rect11;
delete[] Sigma11;



///////////////////////////////////////////////////////////////////////
//Number 1 Part B
///////////////////////////////////////////////////////////////////////
cout << endl << endl << "-------Sigma is of size 5 Twice-------" << endl;
float* Ix1;

Sigma5 = new float[25];
Gauss(5.0, 25, Sigma5);

rect5 = mask(rect, 25, Sigma5);
Ix1 = mask(rect5, 25, Sigma5);
for(int q = 0; q < 128; q++)
{
	cout << Ix1[q] * 255.0 << ", ";
}
delete[] Ix1;
delete[] rect5;


cout << endl << endl << "-------Sigma is of size 5*root(2)-------" << endl;
float* Ix2;

Gauss(5.0, 25, Sigma5);

Ix2 = mask(rect, 25, Sigma5);
for(int q = 0; q < 128; q++)
{
	cout << Ix2[q] * 255.0 << ", ";
}
delete[] Ix2;
delete[] Sigma5;



///////////////////////////////////////////////////////////////////////
//Number 1 Part C
///////////////////////////////////////////////////////////////////////
int** myImage;
int** ImageSig;
int** TempImage;

char ILFile[20] = "lenna.pgm";
char OLFile1[20] = "2D_lenna1.pgm";
char OLFile5[20] = "2D_Lenna5.pgm";
char OLFile11[20] = "2D_Lenna11.pgm";

int M;
int N;
int Q;
float S = 0.0;

//Mask Matrix
float Sig1[5][5];
float Sig5[25][25];
float Sig11[55][55];

//1D Gauss
Sigma1 = new float[5];
Sigma5 = new float[25];
Sigma11 = new float[55];

Gauss(1.0, 5 , Sigma1);
Gauss(5.0, 25, Sigma5);
Gauss(11.0, 55, Sigma11);


//2D Gauss Mask for Sigma 1
for(int n = 0; n < 5; n++)
{
	for(int g = 0; g < 5; g++)
	{
		Sig1[n][g] = Sigma1[n] * Sigma1[g];
	}
}

//2D Gauss Mask for Sigma 5
for(int n = 0; n < 25; n++)
{
	for(int g = 0; g < 25; g++)
	{
		Sig5[n][g] = Sigma5[n] * Sigma5[g];
	}
}

//2D Gauss Mask for Sigma 11
for(int n = 0; n < 55; n++)
{
	for(int g = 0; g < 55; g++)
	{
		Sig11[n][g] = Sigma11[n] * Sigma11[g];
	}
}

cout << endl << endl << "-------2D Gauss on lenna-------" << endl;

ReadImage(ILFile, &myImage, M, N, Q);

ImageSig = new int* [N];
TempImage = new int* [N];															
for(int i=0; i<N; i++)
{
		 (ImageSig)[i] = new int[M];
		 (TempImage)[i] = new int[M];

}


//Smoothing of 2D Sigma 1
for(int t = 0; t < N; t++)
{
	for(int r = 0; r < M; r++)
	{
		S = 0;
		for(int z = 0; z < 5; z++)
		{
			for(int h = 0; h < 5; h++)
			{
				if( (r - z + 5 / 2) < 0 || (r - z + 5 / 2) >= N || 
					(t - h + 5 / 2) < 0 || (t - h + 5 / 2) >= M )
				{
					S += 0;
				}
				else
				{
					S += Sig1[z][h] * myImage[r - z + 5 / 2][t - h + 5 / 2];
				}
			}
		}
		ImageSig[r][t] = S;
	}
}
WriteImage(OLFile1, ImageSig, M,  N,  Q);


//Smoothing of 2D Sigma 5
for(int t = 0; t < N; t++)
{
	for(int r = 0; r < M; r++)
	{
		S = 0;
		for(int z = 0; z < 25; z++)
		{
			for(int h = 0; h < 25; h++)
			{
				if( (r - z + 25 / 2) < 0 || (r - z + 25 / 2) >= N || 
					(t - h + 25 / 2) < 0 || (t - h + 25 / 2) >= M )
				{
					S += 0;
				}
				else
				{
					S += Sig5[z][h] * myImage[r - z + 25 / 2][t - h + 25 / 2];
				}
			}
		}
		ImageSig[r][t] = S;

	}
}
WriteImage(OLFile5, ImageSig, M,  N,  Q);


//Smoothing  of 2d Sigma 11
for(int t = 0; t < N; t++)
{
	for(int r = 0; r < M; r++)
	{
		S = 0;
		for(int z = 0; z < 55; z++)
		{
			for(int h = 0; h < 55; h++)
			{
				if( (r - z + 55 / 2) < 0 || (r - z + 55 / 2) >= N || 
					(t - h + 55 / 2) < 0 || (t - h + 55 / 2) >= M )
				{
					S += 0;
				}
				else
				{
					S += Sig11[z][h] * myImage[r - z + 55 / 2][t - h + 55 / 2];
				}
			}
		}

		ImageSig[r][t] = S;
	}
}
WriteImage(OLFile11, ImageSig, M,  N,  Q);


///////////////////////////////////////////////////////////////////////
//Number 1 Part D
///////////////////////////////////////////////////////////////////////
char File1_1D[20] = "1D_Lenna.pgm";
char File5_1D[20] = "1D_Lenna5.pgm";
char File11_1D[20] = "1D_Lenna11.pgm";

cout << endl << "-------Using 2 1D Gauss on lenna-------" << endl;

//Smoothing of 2D Sigma 1
//Applying mask to rows
for(int t = 0; t < N; t++)
{
	for(int r = 0; r < M; r++)
	{
		S = 0;
		for(int z = 0; z < 5; z++)
		{
			if( (r - z + 5 / 2) < 0 || (r - z + 5 / 2) >= N)
			{
				S += 0;
			}
			else
			{
				S += Sigma1[z] * myImage[r - z + 5 / 2][t];
			}
		}
		TempImage[r][t] = S;
	}
}
//Applying mask to cols
for(int t = 0; t < N; t++)
{
	for(int r = 0; r < M; r++)
	{
		S = 0;
		for(int z = 0; z < 5; z++)
		{
			if( (r - z + 5 / 2) < 0 || (r - z + 5 / 2) >= N)
			{
				S += 0;
			}
			else
			{
				S += Sigma1[z] * TempImage[t][r - z + 5 / 2];
			}
		}
		ImageSig[t][r] = S;
	}
}
WriteImage(File1_1D, ImageSig, M,  N,  Q);


//Smoothing of 2D Sigma 5
//Applying mask to rows
for(int t = 0; t < N; t++)
{
	for(int r = 0; r < M; r++)
	{
		S = 0;
		for(int z = 0; z < 25; z++)
		{
			if( (r - z + 25 / 2) < 0 || (r - z + 25 / 2) >= N)
			{
				S += 0;
			}
			else
			{
				S += Sigma5[z] * myImage[r - z + 25 / 2][t];
			}
		}
		TempImage[r][t] = S;
	}
}
//Applying mask to cols
for(int t = 0; t < N; t++)
{
	for(int r = 0; r < M; r++)
	{
		S = 0;
		for(int z = 0; z < 25; z++)
		{
			if( (r - z + 25 / 2) < 0 || (r - z + 25 / 2) >= N)
			{
				S += 0;
			}
			else
			{
				S += Sigma5[z] * TempImage[t][r - z + 25 / 2];
			}
		}
		ImageSig[t][r] = S;
	}
}
WriteImage(File5_1D, ImageSig, M,  N,  Q);



//Smoothing of 2D Sigma 11
//Applying mask to rows
for(int t = 0; t < N; t++)
{
	for(int r = 0; r < M; r++)
	{
		S = 0;
		for(int z = 0; z < 55; z++)
		{
			if( (r - z + 55 / 2) < 0 || (r - z + 55 / 2) >= N)
			{
				S += 0;
			}
			else
			{
				S += Sigma11[z] * myImage[r - z + 55 / 2][t];
			}
		}
		TempImage[r][t] = S;
	}
}
//Applying mask to cols
for(int t = 0; t < N; t++)
{
	for(int r = 0; r < M; r++)
	{
		S = 0;
		for(int z = 0; z < 55; z++)
		{
			if( (r - z + 55 / 2) < 0 || (r - z + 55 / 2) >= N)
			{
				S += 0;
			}
			else
			{
				S += Sigma11[z] * TempImage[t][r - z + 55 / 2];
			}
		}
		ImageSig[t][r] = S;
	}
}
WriteImage(File11_1D, ImageSig, M,  N,  Q);
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
