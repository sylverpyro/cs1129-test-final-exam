//------------------------------------
// Name		:Michael Benson
//-----------------------------------

#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <cctype>
#include <fstream>
#include <cmath>

using namespace std;

// Class Definition

class Student
{
    public:
	Student();

	// Mutators
        void inputFirstName(string fname);
	void inputLastName(string lname);
	void inputNumGrade(double numGrade);
	void calcLetGrade();

        // Accesors
        string returnFirstName();
        string returnLastName();
        double returnNumGrade();
        char returnLetGrade();

        // Viewing
        void displayFirstName();
        void displayLastName();
        void displayNumGrade();
        void displayLetGrade();

    private:
	string fname;
	string lname;
	double ngrade;
	char lgrade;
};

int parseIntField(ifstream& inStream);
double parseDoubleField(ifstream& inStream);
void skipWhite(ifstream& inStream);
int power(int x, int y);
int stringlen(string inString);
void loadData(ifstream& inStream, Student* studentPoint, 
	int numStudents);
void writeData(ofstream& outStream, Student* studentPoint, 
	int numStudents);


int main()
{
    ifstream inStream;
    ofstream outStream;

    inStream.open("input.txt");
    int numStudents = parseIntField(inStream);
    inStream.close();
    Student *studentPoint;
    studentPoint = new Student[numStudents];

    //Load data into memory
    loadData(inStream, studentPoint, numStudents);

    //Write data to file
    writeData(outStream, studentPoint, numStudents);

}

//-------------------------------------------------------------------
//      loadData(ifstream&, Employee*, int)
//
// Preconditions        :Takes an ifstream, a pointer to the Employee
//                       array, and an int for the number of entries
//
// Postconditions       :Loads the contents of "Employees.txt" into
//                       memory
//-------------------------------------------------------------------

void loadData(ifstream& inStream, Student* studentPoint, 
	int numStudents)
{
//      Employee *tempEmpPointer = empPointer;
        Student *tempStudentPointer = studentPoint;
        int skip = 0;

        inStream.open("input.txt");
        while ( skip < 2)
        {
                char temp;
                inStream.get(temp);
                if (temp == '\n')
                        skip++;
        }

        for ( int i = 0; i < numStudents; i++)
        {
       	 	string tempLast;
		string tempLastName;
		string tempFirst;
		string tempFirstName;
		tempFirst = inStream.get();
		while ( !isspace(tempFirst[0]) )
		{
			tempFirstName = tempFirstName + tempFirst;
			tempFirst = inStream.get();
		}
			
                tempStudentPointer->inputFirstName(tempFirstName);
                skipWhite(inStream);
		
//		tempName[0] = '\0';
		
		tempLast = inStream.get();
		while ( !isspace(tempLast[0]) )
		{
			tempLastName = tempLastName + tempLast;
			tempLast = inStream.get();
		}

                tempStudentPointer->
                        inputLastName(tempLastName);
                skipWhite(inStream);

//		tempName[0] = '\0';

                tempStudentPointer->
			inputNumGrade(parseDoubleField(inStream));

                tempStudentPointer->calcLetGrade();
                skipWhite(inStream);

                tempStudentPointer++;
        }
        inStream.close();
}

//-------------------------------------------------------------------
//      writeData(ofstream&, Employee*, int)
//
// Preconditions        :Takes an ofstream, a pointer to the Employee
//                       class array, and a int for number of
//                       employees
//
// Postconditions       :Writes out to a file "testOutput.txt" the
//                       contents of the Employee class array
//-------------------------------------------------------------------

void writeData(ofstream& outStream, Student* studentPoint, 
	int numStudents)
{
        outStream.open("output.txt");
        outStream.setf(ios::fixed);
        outStream.setf(ios::showpoint);
        outStream.setf(ios::left);
        outStream.precision(2);

        outStream << numStudents << endl;
        outStream.width(18);
        outStream << "First_Name";
        outStream.width(18);
        outStream << "Last_Name";
        outStream.width(18);
        outStream << "Numeric_Grade";
        outStream.width(18);
        outStream << "Letter_Grade" << endl;

        for (int i = 0; i < numStudents; i++)
        {
                outStream.width(18);
                outStream << studentPoint->returnFirstName();
                outStream.width(18);
                outStream << studentPoint->returnLastName();
                outStream.width(18);
                outStream << studentPoint->returnNumGrade();
                outStream.width(18);
                outStream << studentPoint->returnLetGrade();
                outStream << endl;
                studentPoint++;
        }

        outStream.close();
}


//-------------------------------------------------------------------
//      parseIntField(ifstream&)
//
// Preconditions        :Takes an ifstream object that is open and
//                       the stream pointer at the BEGINNING of the
//                       field to be parsed to an int
//
// Postconditions       :Returns an int based on the data found in
//                       the field the pointer began at
//-------------------------------------------------------------------

int parseIntField(ifstream& inStream)
{
        string intList;
        string temp;
        int length;
        int result = 0;

        while ( ! isspace(inStream.peek()) )
        {
                temp = inStream.get();
                intList = intList + temp;
        }

        length = stringlen(intList);

        for (int i = 0; i < length; i++)
        {
                int pow = power(10,length-(i+1));
                int intVers = intList[i]-48;
                result += pow*intVers;
        }

        return result;
}

//-------------------------------------------------------------------
//      parseDoubleField(ifstream&)
//
// Preconditions        :Needs an inStream object already opened and
//                       the current stream pointer at the BEGINNING
//                       of the field to be parsed to an double
//
// Postconditions       :Returns a double based on the data read in
//                       from the file
//-------------------------------------------------------------------

double parseDoubleField(ifstream& inStream)
{
        string intList;
        string decList;
        string temp;
        int length;
        double result = 0.00;

        while ( inStream.peek() != '.' )
        {
                temp = inStream.get();
                intList = intList + temp;
        }

        inStream.get();

        while ( ! isspace( inStream.peek()) )
        {
                temp = inStream.get();
                decList = decList + temp;
        }

        length = stringlen(intList);

        for (int i = 0; i < length; i++)
        {
                double pow = power(10,length-(i+1));
                double intVers = intList[i]-48;
                result += pow*intVers;
        }

        length = stringlen(decList);

        for (int i = 0; i < length; i++)
        {
                double intVers = decList[i]-48;
                double power = pow(10.0, -(i+1));
                result += (decList[i]-48) * power;
        }

        return result;
}


//-------------------------------------------------------------------
//      skipWhite(ifstream&)
//
// Preconditions        :Needs an ifstream that is open
//
// Postconditions       :Skips over the next block of white space in
//                       the file
//-------------------------------------------------------------------

void skipWhite(ifstream& inStream)
{
        while( isspace(inStream.peek()) )
        {
                inStream.get();
        }
}

//-------------------------------------------------------------------
//      power(int, int)
//
// Preconditions        :Takes 2 integers
//
// Postconditions       :Returns an int of value x raised to the y
//                       NOTE: DOES NOT HANDLE -y VALUES
//-------------------------------------------------------------------

int power(int x, int y)
{
        int answer = 1;

        if (y != 0)
                answer = x;

        for (int i = 1; i < y; i++)
        {
                answer *= x;
        }

        return answer;
}

//-------------------------------------------------------------------
//      stringlen(string)
//
// Preconditions        :Takes a string data type
//
// Postconditions       :Returns an int that is the length of the
//                       passed string NOT-INCLUDING the \0
//-------------------------------------------------------------------

int stringlen(string inString)
{
        int i = 0;
        char check = inString[0];

        while ( check != '\0' )
        {
                i++;
                check = inString[i];
        }

        return i;
}

// Default constructor
Student::Student():fname("No Input"), lname("No Input"), ngrade(0.0),
	 lgrade('E')
{/*Intentionally Empty*/}


void Student::inputFirstName(string inname) { fname = inname; }
void Student::inputLastName(string inname) { lname = inname; }
void Student::inputNumGrade(double ingrade) { ngrade = ingrade; }
void Student::calcLetGrade()
{
    if (ngrade < 60.0)
	lgrade = 'F';
    if (ngrade >= 60.0)
	lgrade = 'D';
    if (ngrade >= 70.0)
	lgrade = 'C';
    if (ngrade >= 80.0)
	lgrade = 'B';
    if (ngrade >= 90.0)
	lgrade = 'A';
}

string Student::returnFirstName() { return(fname); }
string Student::returnLastName() { return(lname); }
double Student::returnNumGrade() { return(ngrade); }
char Student::returnLetGrade() { return(lgrade); }

void Student::displayFirstName() { cout << fname; }
void Student::displayLastName() { cout << lname; }
void Student::displayNumGrade() { cout << ngrade; }
void Student::displayLetGrade() { cout << lgrade; }
