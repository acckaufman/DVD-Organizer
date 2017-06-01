#pragma once
#include <vector>
#include <string>
using namespace std;

class Dvd
{
private:
	string title;
	int length;
	int year;
	vector<string> actors;
	vector<string> characters;
public:
	//Constructor
	Dvd();

	//Mutator functions
	void setTitle(string);
	void setLength(int);
	void setYear(int);
	void setActors(vector<string>);
	void setCharacters(vector<string>);

	//Accessor functions
	string getTitle() const;
	int getLength() const;
	int getYear() const;
	vector<string> getActors() const;
	vector<string> getCharacters() const;

	//Destructor
	~Dvd();
};

