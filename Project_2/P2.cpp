/////////////////////////////////////////////////////////////////////
// Nicholas Smith
// Project 1
// CS 565
/////////////////////////////////////////////////////////////////////

#include "Files.h"
#include <cmath>


using namespace std;

int main()
{

char in[20];
char out[20] = "image.pgm";

int **ImageIn, **ImageTrans, **ImageCrop;

float **data, **A, **B, **X;

float *X_ptr, *B_ptr;

int M, N, Q;

int LESX, LESY;
int RESX, RESY;
int MSX, MSY;
int NX, NY;

int LEDX, LEDY;
int REDX, REDY;
int MDX, MDY;

cout << "Enter File Name: ";
cin >> in;

cout << endl << "Enter Left Eye Start X: ";
cin >> LESX;
cout << "Enter Left Eye Start y: ";
cin >> LESY;
cout  << "Enter Right Eye Start X: ";
cin >> RESX;
cout  << "Enter Right Eye Start y: ";
cin >> RESY;
cout << "Enter Mouth Start x: ";
cin >> MSX;
cout  << "Enter Mouth Start y: ";
cin >> MSY;


cout << endl << "Enter Left Eye Destination X: ";
cin >> LEDX;
cout << "Enter Left Eye Destination y: ";
cin >> LEDY;
cout  << "Enter Right Eye Destination X: ";
cin >> REDX;
cout  << "Enter Right Eye Destination y: ";
cin >> REDY;
cout << "Enter Mouth Destination x: ";
cin >> MDX;
cout  << "Enter Mouth Destination y: ";
cin >> MDY;
cout << "Enter Nose X: ";
cin >> NX;
cout  << "Enter Nose y: ";
cin >> NY;

ReadImage(in, &ImageIn, M, N, Q);

////////////////////////////////////////////////////////////////////////////////////////
//Transformation
////////////////////////////////////////////////////////////////////////////////////////

//Initalizing Transformation matrix
data = new float* [4];
for (int i = 0; i < 4; i++)
{
	(data)[i] = new float[4];
	for(int q = 0;q < 4; q++)
	{
		if(i > 0 && q > 0)
		{
			data[i][q] = 0.f;
		}
	}
}
data[3][3] = 1.f;


//Initalizing matrix A in Ax + b
A = new float* [4];
for (int i = 0; i < 4; i++)
{
	(A)[i] = new float[4];
	for(int q = 0;q < 4; q++)
	{
		if(i > 0 && q > 0)
		{
			A[i][q] = 0.f;
		}
	}
}

//Filling Matrix A
A[1][1] = LEDX;
A[1][2] = LEDY;
A[1][3] = 1.f;

A[2][1] = REDX;
A[2][2] = REDY;
A[2][3] = 1.f;

A[3][1] = MDX;
A[3][2] = MDY;
A[3][3] = 1.f;


//Initalizing matrix B
B = new float* [4];
for (int i = 0; i < 4; i++)
{
	(B)[i] = new float[4];
	for(int q = 0;q < 2; q++)
	{
		if(i > 0 && q > 0)
		{
			B[i][q] = 0.f;
		}
	}
}

// Generate b from x-coords
B[1][1] = LESX;
B[2][1] = RESX;
B[3][1] = MSX;

//Solve Matrix
B_ptr = new float[4];
B_ptr[0] = 0.f;
for(int q = 0; q < 4; q++)
{
	B_ptr[q] = B[q][1];
}

X_ptr = new float[4];


solve_system(3, 3, A, X_ptr, B_ptr);
delete []B_ptr;

//Initializing X
X = new float* [4];
for (int i = 0; i < 4; i++)
{
	(X)[i] = new float[4];
	for(int q = 0;q < 2; q++)
	{
		if(i > 0 && q > 0)
		{
			X[i][q] = 0.f;
		}
	}
}

for(int q = 0; q < 4; q++)
{
	X[q][1] = X_ptr[q];
} 
delete []X_ptr;

//Filling Transformation
data[1][1] = X[1][1];
data[1][2] = X[2][1];
data[1][3] = X[3][1];


// Generate b from Y-coords
B[1][1] = LESY;
B[2][1] = RESY;
B[3][1] = MSY;

//Solve Matrix
B_ptr = new float[4];
B_ptr[0] = 0.f;
for(int q = 0; q < 4; q++)
{
	B_ptr[q] = B[q][1];
}

X_ptr = new float[4];


solve_system(3, 3, A, X_ptr, B_ptr);
delete []B_ptr;

//Initializing X
X = new float* [4];
for (int i = 0; i < 4; i++)
{
	(X)[i] = new float[4];
	for(int q = 0;q < 2; q++)
	{
		if(i > 0 && q > 0)
		{
			X[i][q] = 0.f;
		}
	}
}

for(int q = 0; q < 4; q++)
{
	X[q][1] = X_ptr[q];
} 
delete []X_ptr;

//Filling Transformation
data[2][1] = X[1][1];
data[2][2] = X[2][1];
data[2][3] = X[3][1];

//Print
for (int i = 1; i < 4; i++)
{
	for (int q = 1; q < 4; q++)
	{
		cout << data[i][q] << "    ";
	}
	cout << endl;
}
cout << endl;

////////////////////////////////////////////////////////////////////////////////////////////
//Image
////////////////////////////////////////////////////////////////////////////////////////////
int X_scr, Y_scr;

//Initializing ImageTrans
ImageTrans = new int* [92];
for (int i = 0; i < 92; i++)
{
	(ImageTrans)[i] = new int[112];
}


//Transforming image using the reverse
for(int i = 0; i < 112; i++)
{
	for(int j = 0; j < 92; j++)
	{
		X_scr = j * data[1][1] + i * data[1][2] + data[1][3];
		Y_scr = j * data[2][1] + i * data[2][2] + data[2][3];

		if(X_scr >= 0 && X_scr < 92 && Y_scr >=0 && Y_scr < 112)
		{
			ImageTrans[j][i] = ImageIn[Y_scr][X_scr];

		}
		else
		{
			ImageTrans[j][i] = 0;

		}
	}
}


//Initializing Crop image
ImageCrop = new int* [56];
for (int i = 0; i < 56; i++)
{
	(ImageCrop)[i] = new int[46];
}

// Cropping the image
for(int i = 0; i < 56; i++)
{
	for(int j = 0; j < 46; j++)
	{
		ImageCrop[i][j] = ImageTrans[j + 0][i + 0];
	}
}


WriteImage(out, ImageCrop, M, N, Q);

	return 0;
}