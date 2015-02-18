	float* Mask = new float[5];
	float* Sigma5 = new float[25];
	float* Sigma11 = new float[55];
	
	float* rect1 = new float [128];
	float* rect5 = new float [128];
	float* rect11 = new float [128];
	
	float* Ix1 = new float [128];
	float* Ix2 = new float [128];
			
	Gauss(1.0, 5, Sigma1);
	Gauss(5.0, 25, Sigma5);	
	Gauss(11.0, 55, Sigma11);
	
	int sig1_Half = 3;
	int sig5_Half = 13;
	int sig11_Half = 28;
	
	int sig1_Max = 5;
	int sig5_Max = 25;
	int sig11_Max = 55;
	
	float temp = 0;
	int x;
	int y;

	char PFile[20] = "lenna.pgm";
	char OFile[20] = "output1.pgm";
	float **mask1;

	int ***lennaMat;
	int **lennaMat2;
	int M = 0;
	int N = 0;
	int Q = 0;
	int A = 0;
	int B = 0;
	int C = 0;
	


	/*	

	for(int i = 0; i < 128; i++)
		{
		cout.precision(5);
		cout << rect[i] << " ";
		}
		cout << endl << endl;
	///#1///
	// 1a-sigma 1

for(int i = 0; i < 5; i++)
		{
		cout.precision(9);
		cout << Sigma1[i] << " ";
		}
		cout << endl << endl;
for(int i = 0; i < 128; i++)
		{
		cout.precision(9);
		cout << rect1[i] << " ";
		}
		cout << endl << endl;

	temp = 0;	
	// 1a-sigma 5
	for (int i = 0; i < 128; i++)
		{
		x = 0;
		y = sig5_Max;
		
		if(sig5_Half >= i)
			{
			x = sig5_Half - i - 1;  
			}
		if(i > 128 - sig5_Half)
			{
			y = sig5_Max - (i + 1);
			}
			
		for(int q = x; q < y; q++)
			{
			temp = temp + ((Sigma5[q]) * (rect[i - sig5_Half + q + 1]));
			}
		
		rect5[i] = temp;
		}
		for(int i = 0; i < 25; i++)
		{
		cout.precision(9);
		cout << Sigma5[i] << " ";
		}
		cout << endl << endl;
for(int i = 0; i < 128; i++)
		{
		cout.precision(9);
		cout << rect5[i] << " ";
		}
		cout << endl << endl;

	temp = 0;
	// 1a-sigma 11
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
		
		rect11[i] = temp;
		}

	for(int i = 0; i < 55; i++)
		{
		cout.precision(9);
		cout << Sigma11[i] << " ";
		}
	cout << endl << endl;
for(int i = 0; i < 128; i++)
		{
		cout.precision(9);
		cout << rect11[i] << " ";
		}
		cout << endl << endl;
	
	temp = 0;
	//1b-(Ix * Gx)*Gx
	for (int i = 0; i < 128; i++)
		{
		x = 0;
		y = sig5_Max;
		
		if(sig5_Half >= i)
			{
			x = sig5_Half - i - 1;  
			}
		if(i > 128 - sig5_Half)
			{
			y = sig5_Max - (i + 1);
			}
			
		for(int q = x; q < y; q++)
			{
			temp = temp + ((Sigma5[q]) * (rect5[i - sig5_Half + q + 1]));
			}
		
		Ix1[i] = temp;
		}
	for(int i = 0; i < 128; i++)
		{
		cout.precision(9);
		cout << Ix1[i] << " ";
		}
		cout << endl << endl;


	temp = 0;
	//1b - Ix * (Gx * Gx)
	Gauss(5.0, 25, Sigma5);

	for (int i = 0; i < 128; i++)
		{
		x = 0;
		y = sig5_Max;
		
		if(sig5_Half >= i)
			{
			x = sig5_Half - i - 1;  
			}
		if(i > 128 - sig5_Half)
			{
			y = sig5_Max - (i + 1);
			}
			
		for(int q = x; q < y; q++)
			{
			temp = temp + ((Sigma5[q]) * (rect5[i - sig5_Half + q + 1]));
			}
		
		Ix2[i] = temp;
		}

	for(int i = 0; i < 128; i++)
		{
		cout.precision(9);
		cout << Ix2[i] << " ";
		}
		cout << endl << endl;*/


		//1c
	
	/*for(int i = 0; i < 5; i++)
		{
		cout.precision(9);
		cout << Sigma1[i] << " ";
		}
		cout << endl << endl;
	for(int i = 0; i < 25; i++)
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
	cout << endl << endl;
	for(int i = 0; i < 128; i++)
		{
		cout.precision(5);
		cout << rect[i] << " ";
		}*/