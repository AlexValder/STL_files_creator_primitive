#pragma once
#include "Command.h"
#include "STLTriangle.h"

class Cube : public Command
{
private:
	double len;
	Vec center;
	const std::string name;
public:
	Cube(Vec center, double length);
	const std::string& getName() const override;
//	int execute(const std::map<std::string, std::string>& args) override;
	TriangleSoup generate();
};