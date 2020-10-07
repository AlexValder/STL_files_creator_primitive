#pragma once
#include <vector>
#include <string>

struct Vec
{
	double x, y, z;
	Vec();
	Vec(double x, double y, double z);
	bool operator==(const Vec B) const;
	bool operator!=(const Vec B) const;
};

struct triangle
{
	Vec A, B, C;
	Vec normal;
	triangle();
	triangle(Vec a, Vec b, Vec c);
	triangle(Vec a, Vec b, Vec c, Vec norm);
	void generateNormal();
	triangle flip() const;
};

using TriangleSoup = std::vector<triangle>;

class STLParser
{
public:
	TriangleSoup read(const std::string& filename);
	void write(const TriangleSoup& triangleSoup, const std::string& filename);
private:
	//?
};