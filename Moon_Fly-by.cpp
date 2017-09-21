// name: wenhao ge
// partner: Logan Liles.
// project: a moon fly-by

#include<iostream>
#include<fstream>
#include<string>
#include<cmath>

using namespace std;

// function prototype

void write_star(double ra, double dec, int *pix, int ncols, int nrows, int maxval, double mag);
void write_moon(int ncols, int nrows, int *pix, double radius);
string get_name();

int main()
{

	fstream ifs;

	string fname;

	// call the function called get_name() to get the name of the file that need to be read

	fname = get_name();

	// open the file

	ifs.open(fname);
	const int SIZE = 1200;


	int num[SIZE] = { 0 };

	double ra[SIZE] = { 0.0000 };
	double dec[SIZE] = { 0.0000 };

	double mag[SIZE] = { 0.0000 };

	// create three arrays and store the RA, DEC AND mag to three arrays
	int i = 0;
	do {

		ifs >> num[i] >> ra[i] >> dec[i] >> mag[i];
		// cout << ra[i] << " " << dec[i] << " " << mag[i] << endl;

		i++;

	} while (i <= 1097);
	ifs.close();

	cout << "RA & DEC& MAG have been sucessfully read into three arrays." << endl;
	double ra_degr[1098] = { 0 };

	for (int i = 0; i < 1098; i++)
		ra_degr[i] = ra[i] * 15;

	float FOV_hori = 24.0000;
	float FOV_vertical = 16.0000;

	// I will fix the camera at RA 0

	// create a .pgm file and write pix values to it

	ofstream ofs;
	//ofs.open("universe.pgm");
	string type = "P2";
	int ncols = 600, nrows = 400;
	int maxval = 255;

	// I created a dynamically allocated array here

	int *pix = NULL;
	//pix = new int[ncols*nrows];


	int count = 0;
	int index = 0;

	// the following is to find out if the stars are in FOV, once they are in FOV, call the function called write_star
	// I declare an int pointer called test and use it to point all the stars and all the positions within the area of the moon

	int *test;
	test = new int[240000];
	for (int a = 0; a <240000; a++)
	{
		test[a] = 0;
	}
	pix = test;

	/*for (int j = 0; j < 1098; j++)
	{
		if (ra_degr[j] > 180)
		{
			ra_degr[j] = ra_degr[j] - 360;
		}

		if ((ra_degr[j] <= (FOV_hori / 2)) && abs(dec[j]) <= (FOV_vertical / 2))
		{
			write_star(ra_degr[j], dec[j], pix, ncols, nrows, maxval, mag[j]);
		}

	}*/

	/*
	for (int i = 0; i < 400; i++)
	{
	for (int j = 0; j < 600; j++)
	{
	ofs << test[i*ncols + j] << " ";
	}
	ofs << endl;
	}
	ofs.close();
	*/

	// the following is to draw the moon


	// write_moon(ncols, nrows, pix);

	// draw the moon to the pgm file

	/*for (int r = 0; r < 400; r++)
	{
	for (int c = 0; c < 600; c++)
	{
	ofs << test[r*ncols + c]<< " ";
	}
	ofs << endl;
	}*/


	// The original distance from earth to moon is dstart, the final distance between them is dend
	// nframes means the number of pictures camera will take during its trip to the moon

	double nframes = 1000;
	double dstart = 384400;
	double dend = 15000;
	double dsteps = (dstart - dend) / nframes;
	double dist = 0;
	double radius = 10;

	const int totalPGMs = 1000;
	int img_num = 0;
	string img_name[1000] = { "" };

	// The following code is to find out if the stars are in FOV, once they are in FOV, write_star function will be called
	// once it draws all the stars, it will call write_moon function. In this nested loop, 250 pgm files will be created and
	// their moons are different. 

	for (int i = 0; i < 1000; i++)
	{
		dist = dstart - dsteps*i;
		radius = radius + 0.28;

		for (int j = 0; j < 1098; j++)
		{
			if (ra_degr[j] > 180)
			{
				ra_degr[j] = ra_degr[j] - 360;
			}

			if ((ra_degr[j] <= (FOV_hori / 2)) && abs(dec[j]) <= (FOV_vertical / 2))
			{
				write_star(ra_degr[j], dec[j], pix, ncols, nrows, maxval, mag[j]);
			}
		}

		write_moon(ncols, nrows, pix, radius);
		img_num = 10000 + i;
		img_name[i] = "image_" + to_string(img_num) + ".pgm";
		ofs.open(img_name[i]);
		ofs << type << " " << ncols << " " << nrows << " " << maxval << endl;

		// Now the pointer test holds many different values and it is going to draw the stars and 
		// moon into pgm files

		for (int r = 0; r < 400; r++)
		{
			for (int c = 0; c < 600; c++)
			{
				ofs << test[r*ncols + c] << " ";
			}
			ofs << endl;
		}

		for (int a = 0; a <240000; a++)
		{
			test[a] = 0;
		}

		cout << img_name[i] << endl;
		ofs.close();


	}
	//cout << radius;

	/*
	for (int a = 0; a < 1000; a++)
	{
	// ofs.open(img_name[a]);

	for (int r = 0; r < 400; r++)
	{
	for (int c = 0; c < 600; c++)
	{
	ofs << test[r*ncols + c] << " ";
	}
	ofs << endl;
	}
	// test[240000] = { 0 };


	}
	*/
	*pix = NULL;

	system("pause");
	return 0;
}

// the folowing is the write_star function.
// it determine the center coordinates of different stars
// and determine the radius of different stars
// then write 255 to the pointer called pix, once the distance from stars' centers to a specific location is less than the stars'radius

void write_star(double ra, double dec, int *pix, int ncols, int nrows, int maxval, double mag)
{

	double center_x = round(ncols / 2 - ra * ncols / 24);
	double center_y = round(nrows / 2 - dec * nrows / 16);

	double radius = 12 - mag;

	for (int r = 0; r < nrows; r++)
	{
		for (int c = 0; c < ncols; c++)
		{
			double dist = sqrt((r - center_y)*(r - center_y) + (c - center_x)*(c - center_x));

			if (dist <= radius)
				pix[r*ncols + c] = 255;
		}
	}


}


// the following is the write_moon function
// It first determine the center coodrinate of the whole pgm file
// the center of the moon will be in that location
// the pointer pix, its radius and ncols and nrows are its paramters
// once the distance from a specific location to the center position of the moon
// is less than or equal to the radius of the moon, which means that specific location
// is in the moon, 255 will be put into the pointer pix

void write_moon(int ncols, int nrows, int *pix, double radius)
{
	int center_x = ncols / 2;
	int center_y = nrows / 2;
	double dist_moon = 0;
	for (int r = 0; r < 400; r++)
	{
		for (int c = 0; c < 600; c++)
		{
			dist_moon = sqrt((c - center_x)*(c - center_x) + (r - center_y)*(r - center_y));

			if (dist_moon <= radius)
			{
				pix[r*ncols + c] = 255;
			}

		}
	}
}

// at the begining of the code, I will call this function to get
// the name of the file that is needed to be read. 
// then return the filename

string get_name()
{
	string fname;
	cout << "Please enter the name of the file: " << endl;
	cin >> fname;

	return fname;
}