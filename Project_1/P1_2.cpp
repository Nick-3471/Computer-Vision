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
	// Read in
	int** myImageL;
	int** myImageSF;

	//Smoothing
	int** LImage;
	int** SFImage;

	//Output
	int** Image_lenna;
	int** Image_sf;

	int M, N, Q;
	int A, B, C;
	int S;

	//Read in name
	char LFile[10] = "lenna.pgm";
	char SFFile[10] = "sf.pgm";

	//Read out name
	char XLout[20] = "lenna_X.pgm";
	char YLout[20] = "lenna_Y.pgm";
	char MLout[20] = "lenna_M.pgm";
	char DLout[20] = "lenna_D.pgm";
	char TLout[20] = "lenna_T.pgm";

	char XSFout[20] = "SF_X.pgm";
	char YSFout[20] = "SF_Y.pgm";
	char MSFout[20] = "SF_M.pgm";
	char DSFout[20] = "SF_D.pgm";
	char TSFout[20] = "SF_T.pgm";

	//Soble Masks X & Y
	int SobelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
	int SobelY[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

	//Read in images
	ReadImage(LFile, &myImageL, M, N, Q);
	ReadImage(SFFile, &myImageSF, A, B, C);

Image_lenna = new int* [N];
Image_sf = new int* [N];
LImage = new int* [N];
SFImage = new int* [N];
for(int i=0; i<N; i++)
{
	(Image_lenna)[i] = new int[M];
	(Image_sf)[i] = new int[M];
	(LImage)[i] = new int[M];
	(SFImage)[i] = new int[M];
}

//Smooth
float* Sigma1 = new float[5];
float Sig1[5][5];

Gauss(1.0, 5 , Sigma1);

for(int n = 0; n < 5; n++)
{
	for(int g = 0; g < 5; g++)
	{
		Sig1[n][g] = Sigma1[n] * Sigma1[g];
	}
}
//Smoothing of lenna
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
					S += Sig1[z][h] * myImageL[r - z + 5 / 2][t - h + 5 / 2];
				}
			}
		}
		LImage[r][t] = S;
	}
}

//Smoothing SF
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
					S += Sig1[z][h] * myImageSF[r - z + 5 / 2][t - h + 5 / 2];
				}
			}
		}
		SFImage[r][t] = S;
	}
}

///////////////////////////////////////////////////////////////////////
//Number 2 Part A
///////////////////////////////////////////////////////////////////////

//Soble X mask Lenna
cout << "---Applying Sx Mask to lenna---" <<endl;

for(int t = 0; t < N; t++)
{
	for(int r = 0; r < M; r++)
	{
		S = 0;
		for(int z = 0; z < 3; z++)
		{
			for(int h = 0; h < 3; h++)
			{
				if( (r - z + 3 / 2) < 0 || (r - z + 3 / 2) >= N || 
					(t - h + 3 / 2) < 0 || (t - h + 3 / 2) >= M )
				{
					S += 0;
				}
				else
				{
					S += SobelX[z][h] * LImage[r - z + 3 / 2][t - h + 3 / 2];
				}
			}
		}
		Image_lenna[r][t] = S;
	}
}
WriteImage(XLout, Image_lenna, M,  N,  Q);

//Sobel Y mask sf
cout << "---Applying Sx Mask to sf---" <<endl;
for(int t = 0; t < N; t++)
{
	for(int r = 0; r < M; r++)
	{
		S = 0;
		for(int z = 0; z < 3; z++)
		{
			for(int h = 0; h < 3; h++)
			{
				if( (r - z + 3 / 2) < 0 || (r - z + 3 / 2) >= N || 
					(t - h + 3 / 2) < 0 || (t - h + 3 / 2) >= M )
				{
					S += 0;
				}
				else
				{
					S += SobelX[z][h] * SFImage[r - z + 3 / 2][t - h + 3 / 2];
				}
			}
		}
		Image_sf[r][t] = S;
	}
}
WriteImage(XSFout, Image_sf, M,  N,  Q);


///////////////////////////////////////////////////////////////////////
//Number 2 Part B
///////////////////////////////////////////////////////////////////////
//Soble X mask Lenna
cout << "---Applying Sx Mask to lenna---" <<endl;

for(int t = 0; t < N; t++)
{
	for(int r = 0; r < M; r++)
	{
		S = 0;
		for(int z = 0; z < 3; z++)
		{
			for(int h = 0; h < 3; h++)
			{
				if( (r - z + 3 / 2) < 0 || (r - z + 3 / 2) >= N || 
					(t - h + 3 / 2) < 0 || (t - h + 3 / 2) >= M )
				{
					S += 0;
				}
				else
				{
					S += SobelY[z][h] * LImage[r - z + 3 / 2][t - h + 3 / 2];
				}
			}
		}
		Image_lenna[r][t] = S;
	}
}
WriteImage(YLout, Image_lenna, M,  N,  Q);

//Sobel Y mask sf
cout << "---Applying Sx Mask to sf---" <<endl;
for(int t = 0; t < N; t++)
{
	for(int r = 0; r < M; r++)
	{
		S = 0;
		for(int z = 0; z < 3; z++)
		{
			for(int h = 0; h < 3; h++)
			{
				if( (r - z + 3 / 2) < 0 || (r - z + 3 / 2) >= N || 
					(t - h + 3 / 2) < 0 || (t - h + 3 / 2) >= M )
				{
					S += 0;
				}
				else
				{
					S += SobelY[z][h] * SFImage[r - z + 3 / 2][t - h + 3 / 2];
				}
			}
		}
		Image_sf[r][t] = S;
	}
}
WriteImage(YSFout, Image_sf, M,  N,  Q);


	return 0;
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