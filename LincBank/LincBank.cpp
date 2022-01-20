/* ------------------------------------------------------
CMP2801M: Advanced Programming
Driver program for "LincBank" Assessment Item 1
Semester A 2021

Written by James Brown (jamesbrown@lincoln.ac.uk)

During marking, we will use the exact same notation
as provided in the brief, so make sure you follow that guideline.

You should avoid removing parts of this driver program, but
add to it the necessary code to produce your implementation.

Good luck!
------------------------------------------------------ */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <sstream>
#include <vector>
#include "Implementation.h";
using namespace std;

int main()
{
	vector <Account*> accounts;
	vector <string> parameters;
	string userCommand;
	bool currentBit = (false);
	bool isaBit = (false);
	// you may also want to store a collection of opened accounts here

	cout << "~~~ Welcome to LincBank! ~~~" << endl;
	cout << "~~~ Type options for commands ~~~" << endl;

	while (userCommand != "exit")
	{
		parameters.clear(); // clear ready for next command
		cout << endl << ">>> ";

		getline(cin, userCommand);
		if (userCommand.empty())
		{
			continue;
		}
		char* cstr = new char[userCommand.length() + 1];
		strcpy(cstr, userCommand.c_str());

		char* token;
		token = strtok(cstr, " ");

		while (token != NULL)
		{
			parameters.push_back(token);
			token = strtok(NULL, " ");
		}

		// Define all commands as per the brief
		string command = parameters[0];


		if (command.compare("options") == 0)
		{
			cout << "These are the options avalible to you: " << endl;
			cout << "Type open followed by the account type and opening amount, example: open 1 500" << endl;
			cout << "(1) = Current, (2) = Savings, (3) = ISA." << endl;
			cout << "!Warning! Only one ISA and Current account can be opened, ISA accounts must be opened with atleast 1000 GBP" << endl;
			cout << "Type view to see all accounts and recent transactions or, \nview followed by the account number to see the specific account" << endl;
			cout << "Type options to see this list again." << endl;
			cout << "Type exit to leave program" << endl;
				
			// display the various commands to the user
		}
		else if (command.compare("open") == 0)
		{
			if (parameters[1] == "1" and currentBit == false)
			{
				Current* c = new Current(stod(parameters[2]));
				accounts.push_back(c);
				currentBit = true;
			}
			else if (parameters[1] == "1" and currentBit == true)
			{
				cout << "Current account alread opened cannot open another!" << endl;
			}
			else if (parameters[1] == "2")
			{
				Savings* s = new Savings(stod(parameters[2]), false);
				accounts.push_back(s);
			}
			else if (parameters[1] == "3" and isaBit == false and stod(parameters[2]) >= 1000)
			{
				Savings* isa = new Savings(stod(parameters[2]), true);
				accounts.push_back(isa);
				isaBit = true;
			}
			else if (parameters[1] == "3" and isaBit == false and stod(parameters[2]) < 1000)
			{
				cout << "Account cannot be opened unless 1000 GBP is deposited" << endl;
			}
			else if (parameters[1] == "3" and isaBit == true)
			{
				cout << "ISA account alread opened cannot open another!" << endl;
			}
			else
			{
				cout << "Invalid entry: (1) = Current, (2) = Savings, (3) = ISA. " << endl;
			}
			// allow a user to open an account
			// e.g., Account* a = new Savings(...);
		}
		else if (command.compare("view") == 0)
		{
			if (userCommand == "view" and accounts.size() <= 0)
			{
				cout << "No accounts open!" << endl;
			}
			else if (userCommand == "view" and accounts.size() > 0)
			{
				for (int i = 0; i < accounts.size(); i++)
				{
					accounts[i]->to_String();
				}
			}
			else if (stoi(parameters[1]) > accounts.size() or stoi(parameters[1]) == 0)
			{
				cout << "Account does not exsist currently there are " << accounts.size() << " accounts open" << endl;
			}
			else if (stoi(parameters[1]) > 0 and accounts.size() > 0)
			{
				accounts[stoi(parameters[1]) - 1]->to_String();
			}
			// display an account according to an index (starting from 1)
			// alternatively, display all accounts if no index is provided
		}
		else if (command.compare("withdraw") == 0)
		{
			if (userCommand == "withdraw")
			{
				cout << "Invalid entry: please follow with account number and amount" << endl;
			}
			else if (stoi(parameters[1]) > accounts.size() or stoi(parameters[1]) == 0)
			{
				cout << "Account does not exsist currently there are " << accounts.size() << " accounts open" << endl;
			}
			else if (stoi(parameters[1]) > 0)
			{
				accounts[stoi(parameters[1]) - 1]->withdraw(stoi(parameters[2]));
			}
			// allow user to withdraw funds from an account
		}
		else if (command.compare("deposit") == 0)
		{
			if (userCommand == "deposit")
			{
				cout << "Invalid entry: please follow with account number and amount" << endl;
			}
			else if (stoi(parameters[1]) > accounts.size() or stoi(parameters[1]) == 0)
			{
				cout << "Account does not exsist currently there are " << accounts.size() << " accounts open" << endl;
			}
			else if (stoi(parameters[1]) > 0)
			{
				accounts[stoi(parameters[1]) - 1]->deposit(stoi(parameters[2]));
			}
			// allow user to deposit funds into an account
		}
		else if (command.compare("transfer") == 0)
		{
			if (accounts[stoi(parameters[1]) - 1]->account_Type == 1)
			{
				//cout << accounts[stoi(parameters[1]) - 1] << endl;
			}
			else if (accounts[stoi(parameters[1]) - 1]->account_Type == 2)
			{
				
			}
			else if (accounts[stoi(parameters[1]) - 1]->account_Type == 3)
			{
				
			}
			// allow user to transfer funds between accounts
			// i.e., a withdrawal followed by a deposit!
		}
		else if (command.compare("project") == 0)
		{
			// compute compound interest t years into the future
		}
		//else if (command.compare("search"))
		//{
		//	allow users to search their account history for a transaction
		//  (this is a stretch task)
		//}

	}

	cout << "Press any key to quit...";
	getchar();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file