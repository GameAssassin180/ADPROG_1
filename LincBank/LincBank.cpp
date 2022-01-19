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
			cout << "Type options to see this list again." << endl;
				
			// display the various commands to the user
		}
		else if (command.compare("open") == 0)
		{
			if (parameters[1] == "1")
			{
				Current c(stod(parameters[2]));
				c.to_String();
			}
			// allow a user to open an account
			// e.g., Account* a = new Savings(...);
		}
		else if (command.compare("view") == 0)
		{
			// display an account according to an index (starting from 1)
			// alternatively, display all accounts if no index is provided
		}
		else if (command.compare("withdraw") == 0)
		{
			// allow user to withdraw funds from an account
		}
		else if (command.compare("deposit") == 0)
		{
			// allow user to deposit funds into an account
		}
		else if (command.compare("transfer") == 0)
		{
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