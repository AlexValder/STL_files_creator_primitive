#include "Cube.h"

Cube::Cube(Vec origin, double length) : center(origin), len(length), name("Cube") { ; }

TriangleSoup Cube::generate()
{
	TriangleSoup vec;
	double L = len / 2;
	//���
	vec.push_back(triangle(
		Vec(center.x - L, center.y + L, center.z - L),
		Vec(center.x + L, center.y + L, center.z - L),
		Vec(center.x + L, center.y - L, center.z - L)
	));
	vec.push_back(triangle(
		Vec(center.x + L, center.y - L, center.z - L),
		Vec(center.x - L, center.y - L, center.z - L),
		Vec(center.x - L, center.y + L, center.z - L)
	));
	//�������
	vec.push_back(triangle(
		Vec(center.x + L, center.y + L, center.z + L),
		Vec(center.x - L, center.y + L, center.z + L),
		Vec(center.x + L, center.y - L, center.z + L)
	));
	vec.push_back(triangle(
		Vec(center.x - L, center.y - L, center.z + L),
		Vec(center.x + L, center.y - L, center.z + L),
		Vec(center.x - L, center.y + L, center.z + L)
	));
	//�����1
	vec.push_back(triangle(
		Vec(center.x - L, center.y - L, center.z - L),
		Vec(center.x - L, center.y - L, center.z + L),
		Vec(center.x - L, center.y + L, center.z - L)
	));
	vec.push_back(triangle(
		Vec(center.x - L, center.y + L, center.z + L),
		Vec(center.x - L, center.y + L, center.z - L),
		Vec(center.x - L, center.y - L, center.z + L)
	));
	//�����2
	vec.push_back(triangle(
		Vec(center.x + L, center.y - L, center.z + L),
		Vec(center.x + L, center.y - L, center.z - L),
		Vec(center.x + L, center.y + L, center.z - L)
	));
	vec.push_back(triangle(
		Vec(center.x + L, center.y + L, center.z - L),
		Vec(center.x + L, center.y + L, center.z + L),
		Vec(center.x + L, center.y - L, center.z + L)
	));
	//�����3
	vec.push_back(triangle(
		Vec(center.x + L, center.y - L, center.z + L),
		Vec(center.x - L, center.y - L, center.z - L),
		Vec(center.x + L, center.y - L, center.z - L)
	));
	vec.push_back(triangle(
		Vec(center.x - L, center.y - L, center.z - L),
		Vec(center.x + L, center.y - L, center.z + L),
		Vec(center.x - L, center.y - L, center.z + L)
	));
	//�����4
	vec.push_back(triangle(
		Vec(center.x - L, center.y + L, center.z - L),
		Vec(center.x + L, center.y + L, center.z + L),
		Vec(center.x + L, center.y + L, center.z - L)
	));
	vec.push_back(triangle(
		Vec(center.x + L, center.y + L, center.z + L),
		Vec(center.x - L, center.y + L, center.z - L),
		Vec(center.x - L, center.y + L, center.z + L)
	));

	return vec;
}

const std::string& Cube::getName() const
{
	return name;
}