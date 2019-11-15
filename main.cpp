#include <iostream>
#include <ctime>
#include <vector>
#include <fstream>
#include "STLTriangle.h"

#include "Cube.h"
#include "Sphere.h"
using namespace std;

int main()
{
	TriangleSoup triangleSoup;
	STLParser parser;
	srand(time(0));
	string answer;
	bool k(1);

	cout << "1. Read STL file.\n2. Write STL file.\n3. Generate Cube.\n4. Generate Sphere. (TODO)\n0. Exit\n" << endl;

	while (k)
	{
		cout << "Enter number: "; cin >> answer;

		if (answer == "1")
		{
			cout << "Name of file? "; cin >> answer;
			triangleSoup.clear();
			try { triangleSoup = parser.read(answer); }
			catch (exception & ex) { cout << ex.what() << endl; }
		}
		else if (answer == "2")
		{
			if (triangleSoup.size() < 1)
				cout << "Nothing to write" << endl;
			cout << "Name of file? "; cin >> answer;
			parser.write(triangleSoup, answer);
			triangleSoup.clear();
		}
		else if (answer == "3")
		{
			double L, x, y, z;
			cout << "Length? "; cin >> L;
			cout << "Origin? "; cin >> x >> y >> z;
			Cube cub(Vec(x, y, z), L);
			triangleSoup.clear();
			triangleSoup = cub.generate();
		}
		else if (answer == "4")
		{
			double radius, x, y, z;
			unsigned int slices, rings;
			cout << "Radius? "; cin >> radius;
			cout << "Origin? "; cin >> x >> y >> z;
			cout << "Slices? "; cin >> slices;
			cout << "Rings? "; cin >> rings;
			Sphere sph(Vec(x, y, z), radius, slices, rings);
			triangleSoup.clear();
			triangleSoup = sph.generate();
		}
		else if (answer == "0")
			k = false;
		else
			cout << "Unknown commmand.\n";
	}

	triangleSoup.~vector();
	return 0;

}