#include <iostream>
#include <sstream>
#include <vector>
#include <ctime>
#include "Header.h";
using namespace std;

//Transaction class methods.
//Accessors Methods.
//Setting.
void Transaction::set_Desc(string d)
{
	desc = d;
}
void Transaction::set_Time_Stamp()
{
	time_Stamp = time(0);
}
void Transaction::set_Value(float v)
{
	value = v;
}
//Getting.
string Transaction::get_Desc()
{
	return desc;
}
char* Transaction::get_Time_Stamp()
{
	char* time = ctime(&time_Stamp);
	return time;
}
float Transaction::get_Value()
{
	return value;
}
//Constructor for transactions class.
Transaction::Transaction(string d, float v)
{
	set_Desc(d);
	set_Time_Stamp();
	set_Value(v);
}
//Code for to_String method.
void Transaction::to_String()
{
	cout << get_Desc() << ": " << char(156) << get_Value() << " at " << get_Time_Stamp() << endl;
}


//Account vlass methods.
//Accessor methods.
//Setting.
void Account::set_Balance(float b)
{
	balance = b;
}

void Account::set_History(Transaction t)
{
	history.push_back(t);
}
//Getting.
float Account::get_Balance()
{
	return balance;
}


//Current class methods.
//Accessor methods.
//Setting.
void Current::set_Overdraft(float o)
{
	overdraft = o;
}
//Getting.
float Current::get_Overdraft()
{
	return overdraft;
}
//Code for to_String method.
void Current::to_String()
{
	cout << "Current Account" << endl;
}
//Constructor for Current class.
Current::Current(float v)
{
	Transaction t ("Initial Deposit", v);
	set_Overdraft(500);
	set_History(t);
	set_Balance(v);
}
void Current::deposit(float v)
{
	Transaction t("Deposit", v);
	set_History(t);
	float temp = get_Balance();
	set_Balance(temp + v);
}

void Current::withdraw(float v)
{
	Transaction t("Withdrawl", v);
	set_History(t);
	float temp = get_Balance();
	set_Balance(temp - v);
}