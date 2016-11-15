//Wai Phyo
//CS256-EX7
//completed on 02/17/2016

#ifndef CONWAY_H
#define CONWAY_H

#include <string>

class Conway
{
private:
	int rows;
	int cols;
	bool** grid;
public:
	Conway();
	Conway(const std::string& in);
	Conway(const Conway& other);
	~Conway();
	Conway& operator=(const Conway& right);
	bool alive(int row, int col) const;
	void flip(int row, int col);
	std::string str() const;
	std::string step();
	std::string play(int n);
};

#endif
