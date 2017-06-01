#include "Dvd.h"
#include <string>
#include <vector>
using namespace std;

//Constructor, initialize all values as blank
Dvd::Dvd()
{
	title = " ";
	length = 0;
	year = 0;
	actors.push_back(" ");
	characters.push_back(" ");
}

//Mutator functions
void Dvd::setTitle(string t)
{
	title = t;
}

void Dvd::setLength(int l)
{
	length = l;
}

void Dvd::setYear(int y)
{
	year = y;
}

void Dvd::setActors(vector<string> a)
{
	actors = a;
}

void Dvd::setCharacters(vector<string> c)
{
	characters = c;
}

//Accessor functions
string Dvd::getTitle() const
{
	return title;
}

int Dvd::getLength() const
{
	return length;
}

int Dvd::getYear() const
{
	return year;
}

vector<string> Dvd::getActors() const
{
	return actors;
}

vector<string> Dvd::getCharacters() const
{
	return characters;
}


//Deconstructor
Dvd::~Dvd()
{
}