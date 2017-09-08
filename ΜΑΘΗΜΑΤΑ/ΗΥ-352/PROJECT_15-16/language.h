#pragma once
#include <string>
#include <iostream>
#include <regex>
#include <vector>
#include <stdarg.h> 
#include <string>
using namespace std;
#define PROGRAM_BEGIN int main(){ (false  
#define PROGRAM_END  );}

#define GROUP &GROUPz
#define TIMES &customstring
#define  MATCH ,false); match( 
#define WITH  , 
#define REGEX(v) ,false);\
string v =#v;\
findItem(#v) == true ? false
#define START sample=&caller2("")
#define END &caller2("");\
r.text=sample.text;\
reg.push_back(r);\
sample.text="";\
(false
#define TEXT(a) &caller2(#a) 
#define CHAR(a)  &caller2(#a)
#define OPTIONAL &caller2("?")
#define DOT &caller2(".")
string  temp;
class customstring {
private:
public:
	string text;
	string identifier;
	~customstring() {}
	customstring() {
		text = "";
	}
	customstring(string test)
		:text(test)
	{}
	customstring(int num)
	{
		this->text = "{" + to_string(num) + "}";

	}
	customstring(int num, int num2)
	{
		/* add it to the vector*/

		this->text = "{" + to_string(num ) + "," + to_string(num2) + "}";
	}
	bool operator==(const customstring lhs)
	{
		return this->text == lhs.text;
	}
	customstring operator|(customstring lhs)
	{
		customstring l1(this->text + "|" + lhs.text);
		return l1;
	}
	customstring  operator&(customstring lhs)
	{
		customstring l1(this->text + lhs.text);
		return   l1;
	}
	customstring operator&()
	{
		return *this;
	}
	customstring  operator()(customstring b)
	{
		customstring D;
		D.text = this->text + "(" + b.text + ")";
		return D;
	}
	customstring operator[](customstring a)
	{
		customstring D;
		D.text = this->text + "[" + a.text + "]";
		return &D;
	}
	customstring operator*(customstring a)
	{
		customstring l1(this->text + "*" + a.text);
		return l1;
	}
	customstring  operator+(customstring a)
	{
		customstring l1(this->text + "+" + a.text);
		return l1;
	}
	customstring operator()()
	{
		return *this;
	}
	customstring  operator-(customstring a)
	{
		customstring l1(this->text + "-" + a.text);
		return l1;
	}
	friend ostream &operator<<(ostream &output,
		const customstring &D)
	{
		output << "Output : " << D.text;
		return output;
	}
}   GROUPz;
class Regex {
public:
	string text;
	string identifier;
	Regex() {
	}
	Regex(string id, string text)
		: text(text),
		identifier(id)
	{}
	Regex operator+(const Regex& b)
	{
		Regex Regex;
		Regex.text = this->text + b.text;
		return Regex;
	}
	string Volume() { return text; }
};
Regex t;
std::vector<Regex> reg;
customstring sample; Regex r;
bool findItem(string item) {
	//	cout << "Checking if " + item + " exists in your vector" << endl;
	r.identifier = item;
	for (int i = 0; i < reg.size(); i++) {
		if (reg.at(i).identifier == item) {
			//cout << "Operator found, skipping definition"<<endl;
			return true;
		}
	}
	return false;
}
void match(string e1, string str2) {
	int k;
	Regex temp ;
	for (k = 0; k < reg.size(); k++) {
		if (reg.at(k).identifier == e1) {
			temp = reg.at(k);
			break;
		}
	}
	cout << "regular expression " + e1 + " ";
	
	string found = temp.text;
	regex e(found);
	bool match = regex_match(str2, e);
	if (match == true) {
		cout << "matches " << '"' << str2 << '"' << endl;
	}
	else {
		cout << "does not match " << '"' << str2 << '"' << endl;
	}
}
customstring caller2(string t) {
	customstring l1(t);
	return l1;
}

void match(string e1, string str2, bool nouse) {
	match(e1, str2);
}