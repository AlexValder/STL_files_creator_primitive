#include "Sphere.h"

constexpr double PI = 2*3.141592653589799323;

Sphere::Sphere(Vec cen, double rad, unsigned int slic, unsigned int rin) : center(cen), radius(rad), slices(slic), rings(rin), name("Sphere") { ; }

const std::string& Sphere::getName() const
{
	return name;
}

TriangleSoup Sphere::generate() const
{
	Vec A, B, C, D;
	TriangleSoup vec;

	if (rings < 2 || slices < 3)
		throw std::exception("Cannot create a sphere");

	for (unsigned long long j = 0; j < rings; ++j)
		for (unsigned long long i = 0; i < slices; ++i)
		{
			A.x = center.x + radius * (cos(PI * i		/ slices)	* sin(PI * j		/ (2ll * rings)));
			B.x = center.x + radius * (cos(PI * (i + 1)	/ slices)	* sin(PI * j		/ (2ll * rings)));
			A.y = center.y + radius * (sin(PI * i		/ slices)	* sin(PI * j		/ (2ll * rings)));
			B.y = center.y + radius * (sin(PI * (i + 1)	/ slices)	* sin(PI * j		/ (2ll * rings)));

			C.x = center.x + radius * (cos(PI * i		/ slices)	* sin(PI * (j + 1)	/ (2ll * rings)));
			D.x = center.x + radius * (cos(PI * (i + 1) / slices)	* sin(PI * (j + 1)	/ (2ll * rings)));
			C.y = center.y + radius * (sin(PI * i		/ slices)	* sin(PI * (j + 1)	/ (2ll * rings)));
			D.y = center.y + radius * (sin(PI * (i + 1) / slices)	* sin(PI * (j + 1)	/ (2ll * rings)));

			A.z = B.z = center.z + radius * cos(PI * j			/ (2ll * rings));
			C.z = D.z = center.z + radius * cos(PI * (j + 1)	/ (2ll * rings));

			if (A != B)
				vec.push_back(triangle(B, A, C));
			if (C != D)
				vec.push_back(triangle(D, B, C));
		}
	return vec;
}