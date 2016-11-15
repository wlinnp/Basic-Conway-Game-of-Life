//Wai Phyo
//CS256-EX7
//completed on 02/17/2016

#include "Conway.h"
#include <stdlib.h> 
#include <iostream>
#include <fstream>
#include <sstream>
void Destroy2D(bool** booIn, int inRow)
{
	for(int a=0;a<inRow;++a)
	{
		delete[] booIn[a];//remove each row
		booIn[a]=nullptr;//point to null
	}
	delete[] booIn;//remove the big one
}

bool** copyNew2D(bool** oldBool,bool** newBool, int newRows, int newCols)
{
	oldBool = new bool* [newRows];//create new array
	for(int a=0;a<newRows;++a)//for rows
	{
		oldBool[a]=new bool [newCols];//create new column arrays
		for(int b=0;b<newCols;++b)//for columns
		{
			oldBool[a][b]=newBool[a][b];//copy cells
		}
	}
	return oldBool;//return new array
}
bool deadOrAlive(int alive, int dead, bool current)
{
	bool returnVal;//declare bool var for return
	if(current) // existing cell is alive
	{
		//conditions to change alive or dead
		(alive <2 || alive >3) ? returnVal = false : returnVal = true;
	}
	else // existing cell is dead
	{
		//conditions to change alive or dead
		(alive == 3 ) ? returnVal = true : returnVal = false;
	}
	return returnVal;//return new status
}
bool** playMe(bool** inBool, int noRows, int noCols)
{
	bool** temp = new bool* [noRows];//create temp array
	for(int a=0;a<noRows;++a)//for rows
	{
		temp[a]=new bool[noCols];//create temp array for clumns
		for(int b=0;b<noCols;++b)//for columns
		{
			int alive=0;//start with 0
			int dead=0;//start with 0
			if(a == 0 && b == 0) //top left cornor
			{ // 3 neighbors
				(inBool[a+1][b+1]) ? ++alive : ++dead;
				(inBool[a+1][b]) ? ++alive : ++dead;
				(inBool[a][b+1]) ? ++alive : ++dead;
			}
			else if (a == 0 && b == (noCols - 1)) // top right cornor
			{ // 3 neighbors
				(inBool[a+1][b-1]) ? ++alive : ++dead;
				(inBool[a+1][b]) ? ++alive : ++dead;
				(inBool[a][b-1]) ? ++alive : ++dead;
			}
			else if (a == (noRows - 1) && b == 0) //bottom left cornor
			{ // 3 neighbors
				(inBool[a-1][b+1]) ? ++alive : ++dead;
				(inBool[a-1][b]) ? ++alive : ++dead;
				(inBool[a][b+1]) ? ++alive : ++dead;
			}
			else if (a == (noRows - 1) && b == (noCols - 1)) // bottom right cornor
			{ // 3 neighbors
				(inBool[a-1][b-1]) ? ++alive : ++dead;
				(inBool[a-1][b]) ? ++alive : ++dead;
				(inBool[a][b-1]) ? ++alive : ++dead;
			}
			else if (a == 0) // top row
			{ // 5 neighbors
				(inBool[a+1][b+1]) ? ++alive : ++dead;
				(inBool[a+1][b-1]) ? ++alive : ++dead;
				(inBool[a+1][b]) ? ++alive : ++dead;
				(inBool[a][b+1]) ? ++alive : ++dead;
				(inBool[a][b-1]) ? ++alive : ++dead;
			}
			else if (b == 0) // left column
			{  // 5 neighbors
				(inBool[a][b+1]) ? ++alive : ++dead;
				(inBool[a+1][b+1]) ? ++alive : ++dead;
				(inBool[a-1][b+1]) ? ++alive : ++dead;
				(inBool[a+1][b]) ? ++alive : ++dead;
				(inBool[a-1][b]) ? ++alive : ++dead;
			}
			else if (b == (noCols - 1)) // right column
			{ // 5 neighbors
				(inBool[a][b-1]) ? ++alive : ++dead;
				(inBool[a+1][b-1]) ? ++alive : ++dead;
				(inBool[a-1][b-1]) ? ++alive : ++dead;
				(inBool[a+1][b]) ? ++alive : ++dead;
				(inBool[a-1][b]) ? ++alive : ++dead;
			}
			else if (a == (noRows - 1)) // bottom row
			{ // 5 neighbors
				(inBool[a-1][b+1]) ? ++alive : ++dead;
				(inBool[a-1][b-1]) ? ++alive : ++dead;
				(inBool[a-1][b]) ? ++alive : ++dead;
				(inBool[a][b+1]) ? ++alive : ++dead;
				(inBool[a][b-1]) ? ++alive : ++dead;
			}
			else // in the middle
			{ // 8 neighbors
				(inBool[a-1][b+1]) ? ++alive : ++dead;
				(inBool[a-1][b-1]) ? ++alive : ++dead;
				(inBool[a-1][b]) ? ++alive : ++dead;
				(inBool[a+1][b+1]) ? ++alive : ++dead;
				(inBool[a+1][b-1]) ? ++alive : ++dead;
				(inBool[a+1][b]) ? ++alive : ++dead;
				(inBool[a][b+1]) ? ++alive : ++dead;
				(inBool[a][b-1]) ? ++alive : ++dead;
			}
			temp[a][b] = deadOrAlive(alive, dead, inBool[a][b]);//get new cell values
		}
	}
	Destroy2D(inBool, noRows);//remove old one. (with old values)
	return temp;//return new one or temp one
}
Conway::Conway():rows(1),cols(1),grid(new bool*[1])//empty constructor
{
	grid[0]=new bool[1];//create array with 1 cell
}
Conway::Conway(const std::string& in)//constructor with file
{
	std::ifstream fin(in);//get file
	if(fin)//file exist
	{
		fin >> rows;//get rows
		fin >> cols;//get columns
		grid = new bool* [rows];//create new array
		for(int a=0;a<rows;++a)//for rows
		{
			grid[a]=new bool [cols];//create column arrays
			for(int b=0;b<cols;++b)//for columns
			{
				fin>>grid[a][b];//store values in cells
			}
		}
	}
}
Conway::Conway(const Conway& other):rows(other.rows),cols(other.cols)//copy constructor
{
	grid = copyNew2D(grid, other.grid, other.rows, other.cols);//just sent to function to create new 2d array filled with everything
}
Conway::~Conway()//destructor
{
	Destroy2D(grid, rows);//ask to destroy existing 2d array
	rows=cols=0;//update values
}
Conway& Conway::operator=(const Conway& right)//"=" overload
{
	if(this == &right)//check for assigning same object
	{
		std::cout<<"assigning itself, don't do that.."<<std::endl;
		return *this;
	}
	Destroy2D(grid, rows);	//destroy existing 2d array
	grid = copyNew2D(grid, right.grid, right.rows, right.cols);//fill with new 2d array
	rows=right.rows;//update values
	cols=right.cols;	
	return *this;//return me
}
bool Conway::alive(int row, int col) const
{
	return grid[row][col];//return whether it is alive or dead
}
void Conway::flip(int row, int col)
{
	if(row>-1 && col>-1 && row<rows && col<cols)//check for valid cell
	{
		grid[row][col]=!grid[row][col];//convert value
	}
}
std::string Conway::str() const//to string
{
	std::stringstream sout;//declare stingstream
	for(int a=0;a<rows;++a)//for rows
	{
		for(int b=0;b<cols;++b)//for columns
		{
			sout<<((grid[a][b]) ? "X" :".")<<"\t";//print X or .
		}
		sout<<"\n";//next line for new row
	}
	return sout.str();
}
std::string Conway::step()//play ONE time
{
	std::stringstream sout;//declare stringstream
	sout<<"Before Playing\n"<<str()<<"\n\n";//print string
	grid = playMe(grid, rows, cols);//play and store result
	sout<<"After Playing\n"<<str()<<"\n\n";//print string
	return sout.str();
}
std::string Conway::play(int n)//play number of times from argument
{
	std::stringstream sout;//declare stringstream
	sout<<"Before Playing\n"<<str()<<"\n\n";//print string
	for(int a=0;a<n;++a)//play for number of times
	{
		grid = playMe(grid, rows, cols);//play
		sout<<"After Playing "<<(a+1)<<" times\n"<<str()<<"\n\n";//print end result
	}
	return sout.str();
}
///////////////////////////////////////////////////////////////
//////////////////	MAIN FUNC	///////////////////////
///////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
	if(argc < 3)//check for 2 arguments
	{
		std::cout<<"Not enough parameter. quitting"<<std::endl;
		return 0;
	}
	std::string fromFile(argv[1]);//store file name from argument
	const Conway c(fromFile);//create object with filename
	//while(1)//test for memory leak
	{	
		Conway c1;//empty object
		c1 = c;//test "=" overload
		Conway c2(c);//test copy constructor
		std::string playTimes(argv[2]);//store times to play
		std::cout<<c1.step();// test step function for for object with "="overload
		std::cout<<c2.play(atoi(playTimes.c_str()));//test play function for bject with copy constructor
	}
	return 0;
}
