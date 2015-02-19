/*//////////////////////////////////////////////////////////////////
Project 1
Problem 2
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
	// Read in
	int** myImageL;
	int** myImageSF;

	//Smoothing
	int** LImage;
	int** SFImage;

	//Output
	int** Image_lennaX;
	int** Image_lennaXX;
	int** Image_lennaY;
	int** Image_lennaYY;
	int** Image_lennaM;
	int** Image_lennaD;

	int** Image_sfX;
	int** Image_sfXX;
	int** Image_sfY;
	int** Image_sfYY;
	int** Image_sfM;
	int** Image_sfD;

	int M, N, Q;
	int A, B, C;
	float S;

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
	float SobelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
	float SobelY[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

	//Read in images
	ReadImage(LFile, &myImageL, M, N, Q);
	ReadImage(SFFile, &myImageSF, A, B, C);

//Initializing
Image_lennaX = new int* [N];
Image_lennaXX = new int* [N];
Image_lennaY = new int* [N];
Image_lennaYY = new int* [N];
Image_lennaM = new int* [N];
Image_lennaD = new int* [N];

Image_sfX = new int* [N];
Image_sfXX = new int* [N];
Image_sfY = new int* [N];
Image_sfYY = new int* [N];
Image_sfM = new int* [N];
Image_sfD = new int* [N];

LImage = new int* [N];
SFImage = new int* [N];
for(int i=0; i<N; i++)
{
	(Image_lennaX)[i] = new int[M];
	(Image_lennaXX)[i] = new int[M];
	(Image_lennaY)[i] = new int[M];
	(Image_lennaYY)[i] = new int[M];
	(Image_lennaM)[i] = new int[M];
	(Image_lennaD)[i] = new int[M];

	(Image_sfX)[i] = new int[M];
	(Image_sfXX)[i] = new int[M];
	(Image_sfY)[i] = new int[M];
	(Image_sfYY)[i] = new int[M];
	(Image_sfM)[i] = new int[M];
	(Image_sfD)[i] = new int[M];

	(LImage)[i] = new int[M];
	(SFImage)[i] = new int[M];
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
//Smoothing of lenna
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
		LImage[r][t] = S;
	}
}

//Smoothing SF
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
		S = 0.0;
		for(int z = 0; z < 3; z++)
		{
			for(int h = 0; h < 3; h++)
			{
				if( (r - z + 3 / 2) < 0 || (r - z + 3 / 2) >= N || 
					(t - h + 3 / 2) < 0 || (t - h + 3 / 2) >= M )
				{
					S += 0.0;
				}
				else
				{
					S += SobelX[z][h] * LImage[r - z + 3 / 2][t - h + 3 / 2];
				}
			}
		}
		Image_lennaX[r][t] = S;
	}
}
WriteImage(XLout, Image_lennaX, M,  N,  Q);

//Sobel X mask sf
cout << "---Applying Sx Mask to sf---" <<endl;
for(int t = 0; t < N; t++)
{
	for(int r = 0; r < M; r++)
	{
		S = 0.0;
		for(int z = 0; z < 3; z++)
		{
			for(int h = 0; h < 3; h++)
			{
				if( (r - z + 3 / 2) < 0 || (r - z + 3 / 2) >= N || 
					(t - h + 3 / 2) < 0 || (t - h + 3 / 2) >= M )
				{
					S += 0.0;
				}
				else
				{
					S += SobelX[z][h] * SFImage[r - z + 3 / 2][t - h + 3 / 2];
				}
			}
		}
		Image_sfX[r][t] = S;
	}
}
WriteImage(XSFout, Image_sfX, M,  N,  Q);


///////////////////////////////////////////////////////////////////////
//Number 2 Part B
///////////////////////////////////////////////////////////////////////
//Soble Y mask Lenna
cout << "---Applying Sy Mask to lenna---" <<endl;

for(int t = 0; t < N; t++)
{
	for(int r = 0; r < M; r++)
	{
		S = 0.0;
		for(int z = 0; z < 3; z++)
		{
			for(int h = 0; h < 3; h++)
			{
				if( (r - z + 3 / 2) < 0 || (r - z + 3 / 2) >= N || 
					(t - h + 3 / 2) < 0 || (t - h + 3 / 2) >= M )
				{
					S += 0.0;
				}
				else
				{
					S += SobelY[z][h] * LImage[r - z + 3 / 2][t - h + 3 / 2];
				}
			}
		}
		Image_lennaY[r][t] = S;
	}
}
WriteImage(YLout, Image_lennaY, M,  N,  Q);

//Sobel Y mask sf
cout << "---Applying Sy Mask to sf---" <<endl;
for(int t = 0; t < N; t++)
{
	for(int r = 0; r < M; r++)
	{
		S = 0.0;
		for(int z = 0; z < 3; z++)
		{
			for(int h = 0; h < 3; h++)
			{
				if( (r - z + 3 / 2) < 0 || (r - z + 3 / 2) >= N || 
					(t - h + 3 / 2) < 0 || (t - h + 3 / 2) >= M )
				{
					S += 0.0;
				}
				else
				{
					S += SobelY[z][h] * SFImage[r - z + 3 / 2][t - h + 3 / 2];
				}
			}
		}
		Image_sfY[r][t] = S;
	}
}
WriteImage(YSFout, Image_sfY, M,  N,  Q);


///////////////////////////////////////////////////////////////////////
//Number 2 Part C
///////////////////////////////////////////////////////////////////////
cout << "---Acquiring mag of lenna---" <<endl;


//Squaring X lenna
for(int r = 0; r < N; r++)
{
	for(int c = 0; c < M; c++)
	{
		Image_lennaXX[r][c] += (Image_lennaX[r][c] * Image_lennaX[r][c]);
	}
}

// Squaring Y lenna
for(int r = 0; r < N; r++)
{
	for(int c = 0; c < M; c++)
	{
		Image_lennaYY[r][c] += (Image_lennaY[r][c] * Image_lennaY[r][c]); 
	}
}

//Adding both into M leena
for(int r = 0; r < N; r++)
{
	for(int c = 0; c < M; c++)
	{
		Image_lennaM[r][c] = (sqrt(Image_lennaXX[r][c] + Image_lennaYY[r][c]));
	}
}
WriteImage(MLout, Image_lennaM, M,  N,  Q);


cout << "---Acquiring mag of sf---" <<endl;


//Squaring X sf
for(int r = 0; r < N; r++)
{
	for(int c = 0; c < M; c++)
	{
		Image_sfXX[r][c] += (Image_sfX[r][c] * Image_sfX[r][c]);
	}
}

// Squaring Y lenna
for(int r = 0; r < N; r++)
{
	for(int c = 0; c < M; c++)
	{
		Image_sfYY[r][c] += (Image_sfY[r][c] * Image_sfY[r][c]); 
	}
}

//Adding both into M sf
for(int r = 0; r < N; r++)
{
	for(int c = 0; c < M; c++)
	{
		Image_sfM[r][c] = (sqrt(Image_sfXX[r][c] + Image_sfYY[r][c]));
	}
}
WriteImage(MSFout, Image_sfM, M,  N,  Q);

///////////////////////////////////////////////////////////////////////
//Number 2 Part D
///////////////////////////////////////////////////////////////////////
cout << "---Acquiring gradient direction  of lenna---" <<endl;

//Tangent
for(int r = 0; r < N; r++)
{
	for(int c = 0; c < M; c++)
	{
		Image_lennaD[r][c] = atan2(Image_lennaY[r][c], Image_lennaX[r][c]);
	}
}
WriteImage(DLout, Image_lennaD, M,  N,  Q);


cout << "---Acquiring gradient direction  of SF---" <<endl;

//Tangent
for(int r = 0; r < N; r++)
{
	for(int c = 0; c < M; c++)
	{
		Image_sfD[r][c] = atan2(Image_sfY[r][c], Image_sfX[r][c]);
	}
}
WriteImage(DSFout, Image_sfD, M,  N,  Q);
///////////////////////////////////////////////////////////////////////
//Number 2 Part E
///////////////////////////////////////////////////////////////////////
cout << "---Acquiring threshold of lenna---" <<endl;

int thresh;

cout << "Enter threshold value for lenna: ";
cin >> thresh;

for(int r = 0; r < N; r++)
{
	for(int c = 0; c < M; c++)
	{
		if(Image_lennaM[r][c] < thresh)
		{
			Image_lennaM[r][c] = 0;
		}
	}
}

WriteImage(TLout, Image_lennaM, M,  N,  Q);

cout << "---Acquiring threshold of SF---" <<endl;

cout << "Enter threshold value for sf: ";
cin >> thresh;

for(int r = 0; r < N; r++)
{
	for(int c = 0; c < M; c++)
	{
		if(Image_sfM[r][c] < thresh)
		{
			Image_sfM[r][c] = 0;
		}
	}
}

WriteImage(TSFout, Image_sfM, M,  N,  Q);



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