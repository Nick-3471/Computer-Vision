/////////////////////////////////////////////////////////////////////
// Nicholas Smith
// Project 1
// CS 485
/////////////////////////////////////////////////////////////////////

#include "Files.h"
#include <cmath>


using namespace std;

int main()
{

int** myImage;
char in[20] = "1.pgm";
char out[20] = "image.pgm";

int** ImageOut;


int M, N, Q;

int LEX, LEY;
int REX, REY;
int NX, NY;
int MX, MY;



cout << endl << "Enter Left Eye X: ";
cin >> LEX;
cout << "Enter Left Eye y: ";
cin >> LEY;
cout  << "Enter Right Eye X: ";
cin >> REX;
cout  << "Enter Right Eye y: ";
cin >> REY;
cout << "Enter Nose X: ";
cin >> NX;
cout  << "Enter Nose y: ";
cin >> NY;
cout << "Enter Mouth x: ";
cin >> MX;
cout  << "Enter Mouth y: ";
cin >> MY;

ReadImage(in, &myImage, M, N, Q);

ImageOut = new int* [40];
for(int i = 0; i < 40; i++)
{
	(ImageOut)[i]= new int[48];
}

for(int q = 0; q < 40; q++)
{
	for(int z = 0; z < 48; z++)
	{
		ImageOut[q][z] = myImage[LEX + q - 6][LEY + z];
	}
}
 WriteImage(out, ImageOut, M, N ,Q);
cout << "Got here" << endl;

	return 0;
}