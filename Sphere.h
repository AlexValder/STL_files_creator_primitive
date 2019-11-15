#pragma once
#include "Command.h"
#include "STLTriangle.h"

class Sphere : public Command
{
private:
	Vec center;
	double radius;
	unsigned int slices, rings;
	const std::string name;
public:
	Sphere(Vec center, double radius, unsigned int slices, unsigned int rings);
	TriangleSoup generate() const;
	const std::string& getName() const override;
//	int execute(const std::map<std::string, std::string>& args) override;
};