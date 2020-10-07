#include "STLTriangle.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

//Vec

Vec::Vec() : x(0), y(0), z(0) { ; }

Vec::Vec(double _x, double _y, double _z) : x(_x), y(_y), z(_z) { ; }

bool Vec::operator==(const Vec B) const
{
	return (x == B.x) && (y == B.y) && (z == B.z);
}

bool Vec::operator!=(const Vec B) const
{
	return !(*this == B);
}

//triangle

triangle::triangle() : A(), B(), C(), normal() { ; }

triangle::triangle(Vec a, Vec b, Vec c) : A(a), B(b), C(c)
{
	this->generateNormal();
}

triangle::triangle(Vec a, Vec b, Vec c, Vec norm) : A(a), B(b), C(c), normal(norm) { ; }

void triangle::generateNormal()
{
	normal.x = A.y * B.z - A.z * B.y;
	normal.y = A.z * B.x - A.x * B.z;
	normal.z = A.x * B.y - A.y * B.x;

	double length = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
	normal.x /= length;
	normal.y /= length;
	normal.z /= length;
}

triangle triangle::flip() const
{
	return triangle(B, A, C);
}

//STLParser

TriangleSoup STLParser::read(const std::string& filename)
{
	std::ifstream file(filename);
	int count = 0;
	bool named = false;

	if (!file.is_open())
	{
		file.close();
        throw std::runtime_error("File not found");
	}

	std::string cur_word;
	TriangleSoup res;
	std::vector<double> vec;

	file >> cur_word;

	if (cur_word != "solid")
	{
		res.clear();
		vec.clear();
		cur_word.clear();
		file.close();
		std::cout << count << std::endl;
        throw std::runtime_error("File is corrupt: \"solid <name>\" was expected");
	}

	file >> cur_word;
	if (cur_word != "facet")
		named = true;

	while (!file.eof())
	{
		++count;
		if (named)
			file >> cur_word;
		named = true;

		if (cur_word == "endsolid")
			break;

		if (cur_word != "facet")
		{
			res.clear();
			vec.clear();
			cur_word.clear();
			file.close();
			std::cout << count << std::endl;
            throw std::runtime_error("File is corrupt: \"facet\" was expected");
		}
		file >> cur_word;
		if (cur_word != "normal")
		{
			res.clear();
			vec.clear();
			cur_word.clear();
			file.close();
			std::cout << count << std::endl;
            throw std::runtime_error("File is corrupt: \"normal\" was expected");
		}
		for (int i = 0; i < 3; ++i)
		{
			file >> cur_word;
			if (cur_word.size() < 1 || (cur_word[0] != '-' && !isdigit(cur_word[0])))
			{
				res.clear();
				vec.clear();
				cur_word.clear();
				file.close();
				std::cout << count << std::endl;
                throw std::runtime_error("File is corrupt: Normal value was expected");
			}
			vec.push_back(atof(cur_word.c_str()));
		}
		file >> cur_word;
		if (cur_word != "outer")
		{
			res.clear();
			vec.clear();
			cur_word.clear();
			file.close();
			std::cout << count << std::endl;
            throw std::runtime_error("File is corrupt: \"outer loop\" was expected");
		}
		else
		{
			file >> cur_word;
			if (cur_word != "loop")
			{
				res.clear();
				vec.clear();
				cur_word.clear();
				file.close();
				std::cout << count << std::endl;
                throw std::runtime_error("File is corrupt: \"outer loop\" was expected");
			}
		}
		for (int i = 0; i < 3; ++i)
		{
			file >> cur_word;
			if (cur_word != "vertex")
			{
				res.clear();
				vec.clear();
				cur_word.clear();
				file.close();
				std::cout << count << std::endl;
                throw std::runtime_error("File is corrupt: \"vertex\" was expected");
			}
			for (int i = 0; i < 3; ++i)
			{
				file >> cur_word;
				if (cur_word.size() < 1 || cur_word[0] != '-' && !isdigit(cur_word[0]))
				{
					res.clear();
					vec.clear();
					cur_word.clear();
					file.close();
					std::cout << count << std::endl;
                    throw std::runtime_error("File is corrupt: Vertex value was expected");
				}
				vec.push_back(atof(cur_word.c_str()));
			}
		}
		file >> cur_word;
		if (cur_word != "endloop")
		{
			res.clear();
			vec.clear();
			cur_word.clear();
			file.close();
			std::cout << count << std::endl;
            throw std::runtime_error("File is corrupt: \"endloop\" was expected");
		}
		file >> cur_word;
		if (cur_word != "endfacet")
		{
			res.clear();
			vec.clear();
			cur_word.clear();
			file.close();
			std::cout << count << std::endl;
            throw std::runtime_error("File is corrupt: \"endfacet\" was expected");
		}
		res.push_back(triangle(
			Vec(vec[3], vec[4], vec[5]),
			Vec(vec[6], vec[7], vec[8]),
			Vec(vec[9], vec[10], vec[11]),
			Vec(vec[0], vec[1], vec[2])
		));
		vec.clear();
	}
	
	vec.clear();
	cur_word.clear();
	file.close();
	return res;
}

void STLParser::write(const TriangleSoup& vec, const std::string& filename)
{
	unsigned int amount = vec.size();
	Vec a, b, c;
	std::ofstream file;
	
	if (filename.substr(filename.find_last_of(".") + 1) == "stl")
		file.open(filename);
	else
		file.open(filename + ".stl");

	if (file.is_open())
	{
		file << "solid" << std::endl;
		for (unsigned int i = 0; i < amount; ++i)
		{
			file << "facet normal " << vec[i].normal.x << ' ' << vec[i].normal.y << ' ' << vec[i].normal.z << "\n\touter loop\n" <<
				"\t\tvertex " << vec[i].A.x << ' ' << vec[i].A.y << ' ' << vec[i].A.z << '\n' <<
				"\t\tvertex " << vec[i].B.x << ' ' << vec[i].B.y << ' ' << vec[i].B.z << '\n' <<
				"\t\tvertex " << vec[i].C.x << ' ' << vec[i].C.y << ' ' << vec[i].C.z << '\n' <<
				"\tendloop\nendfacet\n" << std::endl;
		}
		file << "endsolid\n";
	}
	else
		std::cout << "Couldn't open " << filename << "." << std::endl;
	file.close();
}
