#include <iostream>
#include <string>
#include <vector>

using namespace std;

#include <stdio.h>	// this is a C header include

int func1(int a, string s);
float func2(int a, int b);

struct Cat
{
	int age = 5;
	string name;
	string color;
	struct Food
	{
		string type;
		int quantity;
	};
};

enum Animals
{
	dog,
	cat,
	horse
};

class Book
{
public: //private:

	string title;
	string author;

public:

	Book()
	{
	}

	~Book()
	{
		cout << "Deconstructing Book" << endl;
	}	

	Book(string title, string author)
	{
		this->title = title;
		this->author = author;
	}

	// virtual void burn() = 0;

	void readbook()
	{
		cout << "Reading " + this->title + " by " + this->author << endl;
	}
};

class SpecialBook : public Book
{
public:
	int rating;

	void burn()
	{
		cout << "Burning " + this->title + " by " + this->author << endl;
	}

	SpecialBook(string title, string author, int rating) 
		: Book(title, author)
	{
		this->rating = rating;
	}

	~SpecialBook()
	{
		cout << "Deconstructing SpecialBook" << endl;
	}	
};

int main()
{
  double pi, radius;
  double area, circumference;
  long double ld;
  bool flag = true;
  string name = "Jane Doe";
  char a = 'A';
  pi = 3.1415926535;

  radius = 42;

  area = pi * (radius * radius);
  circumference = 2 * pi * radius;

  printf("Hello C\n");
  cout << "Hello C++" << endl;
  cout << "Name is " << name << endl;

  int num = 10;
  cout << "Pionter: " << &num << endl;
  int *pNum = &num;
  cout << pNum << endl;
  cout << *pNum << endl;
  cout << name.length() << endl;
  cout << name[0] << endl;
  cout << name.substr(1, 3) << endl;
  cout << name.find("Do") << endl;

  cout << "Enter your name: ";
  cin >> name;
  cout << "Name is " << name << endl;

  int grid[2][3] = { {1, 2, 3}, {4, 5, 6} };
  grid[1][1] = 99;
  cout << grid[1][1] << endl;

  vector<string> names;
  names.push_back("Bob");
  names.push_back("Jim");
  names.push_back("Jane");
  names.insert(names.begin() + 1, "Alice");
  names.erase(names.begin() + 1);
  cout << names.at(0) + " " + names.at(1) + " " << names.size() << endl;

  cout << func1(10, name) << endl;

  if (name.compare("Ikke") == 0)
  {
    cout << "Compare == 0" << endl;
  }
  else
  {
    cout << "Compare != 0" << endl;
  }
  
  try 
  {
	float f = func2(42, 0);
	cout << f << endl;
  }
  catch (const char* msg)
  {
  	cerr << msg << endl;
  }

  Book book1;
  book1.title = "Rendez-vous with Rama";
  book1.author = "Arthur C. Clarke";
  book1.readbook();
  cout << book1.title + " - " + book1.author << endl;

  Book book2("Hyperion", "Dan Simmons");
  book2.readbook();

  SpecialBook book3("Harry Potter", "JK Rollings", 2);
  book3.readbook();
  book3.burn();


  Animals aa = cat;
  Animals bb(dog);

  Cat pussy { 3, "Pussy", "Black" };
  Cat poes = { 4, "Poes", "White" };

  Cat::Food f {"SNacks", 4};

  return 0;
}

int func1(int a, string s)
{
	return a * s.length();
}

float func2(int a, int b)
{
	if (b == 0)
	{
		throw "Division by zero !";
	}

	return (float)a / b;
}

// c++ hello.c -o hello
