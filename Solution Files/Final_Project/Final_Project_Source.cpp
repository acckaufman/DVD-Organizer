#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include "Dvd.h"
using namespace std;

void displayMenu();
void getSelection(int&);
void displayList(vector<Dvd>);
void addItem(vector<Dvd>&);
void removeItem(vector<Dvd>&);
void updateItem(vector<Dvd>&);

int main()
{
	int selection;
	vector<Dvd> list;

	cout << "DVD Organizer" << endl;
	do
	{
		//Display the menu
		displayMenu();

		//Get the user's menu choice
		getSelection(selection);

		switch (selection)
		{
			case 1:
				//Display DVD List
				if (list.empty())
				{
					cout << endl << "There are currently no DVD's to display." << endl << endl;
					system("pause");
				}

				else
				{
					displayList(list);
				}
				break;

			case 2:
				//Add an item to the list
				addItem(list);
				break;

			case 3:
				//Remove an item from the list
				if (list.empty())
				{
					cout << endl << "There are currently no DVD's available." << endl << endl;
					system("pause");
				}
				else
					removeItem(list);
				break;

			case 4:
				//Update DVD
				if (list.empty())
				{
					cout << endl << "There are currently no DVD's available." << endl << endl;
					system("pause");
				}
				else
					updateItem(list);
				break;

			case 5:
				cout << endl << "Thank you for using the program!  Now exiting." << endl << endl;
				break;
		}
	} while (selection != 5);

	system("pause");

	return 0;
}

void displayMenu()
{
	cout << endl << "Main Menu:" << endl;
	cout << "1. Display DVD List " << endl;
	cout << "2. Add DVD" << endl;
	cout << "3. Remove DVD" << endl;
	cout << "4. Update DVD" << endl;
	cout << "5. Quit Program" << endl << endl;
}

void getSelection(int &choice)
{
	cout << "Please make a selection: ";
	cin >> choice;
	cin.ignore();

	//Input validation to make sure the user entered a valid choice
	while (choice < 1 || choice > 5)
	{
		cout << "Error! You must make a valid selection from the menu.  Please try again." << endl;
		cout << "Please make a selection: ";
		cin >> choice;
	}
}

void displayList(vector<Dvd> list)
{
	cout << endl;
	for (int count = 0; count < list.size(); count++)
	{
		cout << "DVD #" << (count + 1) << endl;
		cout << "Title: " << list[count].getTitle() << endl;		//Display title
		cout << "Length: " << list[count].getLength() << endl;		//Display length
		cout << "Year: " << list[count].getYear() << endl;			//Display year

		//Display actors alongside the name of their character
		cout << setw(8) << left << "Actors: ";
		vector<string> temp;										//Declare a temporary vector to hold the actor names
		temp = list[count].getActors();								//Get the list of actors using the Dvd member function and store it in temp
		vector<string> temp2;										//Declare a temporary vector to hold the character names
		temp2 = list[count].getCharacters();						//Get the list of character names using the Dvd member function and store it in temp2
		
		cout << setw(20) << left << temp[0] << setw(8) << left << " as " << setw(20) << left << temp2[0] << endl;	//First line display (unique)
		for (int index = 1; index < temp.size(); index++)			//Display each actor name next to the character they play
		{
			cout << setw(8) << " " << setw(20) << left << temp[index] << setw(8) << left << " as " << setw(20) << left << temp2[index] << endl;
		}

		cout << endl;
	}

	system("pause");
}

void addItem(vector<Dvd> &list)
{
	string t;			//Title
	int l;				//Length
	int y;				//Year
	vector<string> a;	//Actors
	vector<string> c;	//Characters
	Dvd tempDVD;		//Temporary storage for all of the elements of the DVD input by the user, so we can add it to the list once complete
	char again;			//Inner do-while loop (for adding actors and characters)
	char againMain;		//Outer do-while loop (for adding another DVD)

	do {				//As long as the user wants to keep adding DVD's
		
		cout << endl << "Add DVD" << endl;

		cout << "Title: ";
		getline(cin, t);
		tempDVD.setTitle(t);			//Assign the title entered by the user to the temporary DVD holder

		cout << "Length (in mins): ";
		cin >> l;
		tempDVD.setLength(l);			//Assign the length entered by the user to the temporary DVD holder

		cout << "Year released: ";
		cin >> y;
		tempDVD.setYear(y);				//Assign the year entered by the user to the temporary DVD holder

		cout << "Would you like to add actors and characters at this time? (y/n): ";
		cin >> again;
		cin.ignore();

		//If the user does not want to add actors and characters, store at least an empty value in those arrays.
		if (again != 'y' && again != 'Y')
		{
			a.push_back(" ");
			c.push_back(" ");
		}

		//Allow the user to enter actors and characters as long as they keep saying yes
		while (again == 'y' || again == 'Y')
		{
			string tempString;			//Temporary string holder for actor name
			cout << "Actor name: ";
			getline(cin, tempString);
			a.push_back(tempString);	//Add another element to the a vector for actors, and store the string in it

			string tempString2;			//Temporary string holder for character name
			cout << "Corresponding character: ";
			getline(cin, tempString2);
			c.push_back(tempString2);	//Add another element to the c vector for characters, and store the string in it

			cout << "Would you like to add another actor and character? (y/n): ";
			cin >> again;
			cin.ignore();
		}

		tempDVD.setActors(a);			//Assign the a vector containing actor names to the tempDVD element
		tempDVD.setCharacters(c);		//Assign the c vector containing actor names to the tempDVD element

		list.push_back(tempDVD);		//Create a new element in the main list of DVD's which was passed to the function,
										//and add the temporary DVD element we created to that vector

		cout << "Would you like to add another DVD? (y/n): ";
		cin >> againMain;
		cin.ignore();

	} while (againMain == 'y' || againMain == 'Y');
}

void removeItem(vector<Dvd> &list)
{
	char again;				//To ask the user if they want to remove another item
	int selection;			//To ask the user which DVD they would like to remove

		do {
			if (!list.empty())	//Check to make sure there are DVD's in the list
			{
				displayList(list);

				cout << "Which DVD # would you like to remove? ";
				cin >> selection;

				//We will take all the elements between the one after the user's selection and the end of the vector, and shift them to the left one.
				//The element that the user selected will be overwritten by the information from the element immediately after it, and so forth.

				//Identify some temporary variables to help with this process.  This process could be simplified by using the return member functions
				//in the arguments for the functions that assign the variables to the previous element.
				string tempTitle;
				int tempLength;
				int tempYear;
				vector<string> tempActors;
				vector<string> tempCharacters;

				for (int count = (selection - 1); count < (list.size() - 1); count++)
				{
					tempTitle = list[count + 1].getTitle();
					list[count].setTitle(tempTitle);

					tempLength = list[count + 1].getLength();
					list[count].setLength(tempLength);

					tempYear = list[count + 1].getYear();
					list[count].setYear(tempYear);

					tempActors = list[count + 1].getActors();
					list[count].setActors(tempActors);

					tempCharacters = list[count + 1].getCharacters();
					list[count].setCharacters(tempCharacters);
				}

				//Delete the last element in the vector, which now should be a duplicate of the second-to-last element.
				list.pop_back();

				cout << "Would you like to remove another item? (y/n): ";
				cin >> again;
			}
			else
			{
				//If there are no items left in the list
				cout << endl << "There are no DVD's available. " << endl << endl;
				again = 'n';
				system("pause");
			}


		} while ((again == 'y' || again == 'Y'));
}

void updateItem(vector<Dvd> &list)
{
	char again;						//To ask the user if they want to update another DVD
	char againActors;				//To ask the user if they want to add more actors and characters
	vector<string> a;				//To hold the list of actors that the user inputs
	vector<string> c;				//To hold the list of characters that the user inputs

	do {
		int DvdSelection;			//To ask the user which DVD they want to update
		int attributeSelection;		//To ask the user which attribute they would like to modify
		string tempString;			//To hold a string input by the user
		string tempString2;			//To hold a string input by the user
		int temp;					//To hold an integer input by the user

		displayList(list);			//Display the list of DVD's for the user

		cout << "Which DVD # would you like to modify? ";
		cin >> DvdSelection;

		cout << "Which attribute would you like to modify? " << endl;
		cout << "1. Title" << endl;
		cout << "2. Length" << endl;
		cout << "3. Year" << endl;
		cout << "4. Actors and characters" << endl;

		cout << "Attribute #: ";
		cin >> attributeSelection;
		cin.ignore();

		switch (attributeSelection)
		{
		case 1: 
			cout << "Enter title: ";
			getline(cin, tempString);
			list[(DvdSelection - 1)].setTitle(tempString);	//Assign the user's input to the title of the DVD they selected

			cout << "The title has been successfully changed." << endl;
			break;

		case 2:
			cout << "Enter length (in mins): ";
			cin >> temp;
			list[(DvdSelection - 1)].setLength(temp);	//Assign the user's input to the length of the DVD they selected

			cout << "The length has successfully been changed." << endl;
			break;

		case 3:
			cout << "Enter year: ";
			cin >> temp;
			list[(DvdSelection - 1)].setYear(temp);	//Assign the user's input to the year of the DVD they selected

			cout << "The year has successfully been changed." << endl;
			break;

		case 4:
			do{
				cout << "Actor name: ";
				getline(cin, tempString);
				a.push_back(tempString);	//Add another element to the a vector for actors, and store the string in it

				cout << "Corresponding character: ";
				getline(cin, tempString2);
				c.push_back(tempString2);	//Add another element to the c vector for characters, and store the string in it

				cout << "Would you like to add another actor and character? (y/n): ";
				cin >> againActors;
			} while (againActors == 'y' || againActors == 'Y');

			list[(DvdSelection - 1)].setActors(a);			//Assign the a vector containing actor names to the tempDVD element
			list[(DvdSelection - 1)].setCharacters(c);		//Assign the c vector containing actor names to the tempDVD element
			break;

		default:
			cout << "There has been an error." << endl << endl;
			break;
		}

		cout << "Would you like to update another DVD? (y/n): ";
		cin >> again;

	} while (again == 'y' || again == 'Y');

}