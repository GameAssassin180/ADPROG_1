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

	cout << "  ~~~ Welcome to LincBank! ~~~" << endl;
	cout << "~~~ Type options for commands ~~~" << endl;

	while (userCommand != "exit")
	{
		parameters.clear(); // clear ready for next command
		cout << endl << ">>> ";

		getline(cin, userCommand);
		if (userCommand.empty() || userCommand.find_first_not_of(' ') == string::npos)
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
			cout << ">>> These are the options avalible to you: " << endl;
			cout << ">>> Type open followed by the account type and opening amount to open an account, \n>>> Example: open 1 500" << endl;
			cout << ">>> (1) = Current, (2) = Savings, (3) = ISA." << endl;
			cout << ">>> !Warning! Only one ISA and Current account can be opened, ISA accounts must be opened with atleast 1000 GBP" << endl;
			cout << ">>> Type view to see all accounts and recent transactions or, \n>>> view followed by the account number to see the specific account, Example: view 1" << endl;
			cout << ">>> Type withdraw followed by the account number and amount to withdraw from that account, \n>>> Example: withdraw 1 25" << endl;
			cout << ">>> Type deposit followed by the account number and amount to deposit to that account, \n>>> Example: deposit 1 25" << endl;
			cout << ">>> Type transfer followed by the account number you want to take from,\n>>> the account you want to give too,\n>>> and the amount to be moved, \n>>> Example: transfer 1 2 25" << endl;
			cout << ">>> Type project followed by account number and year to get intrest projections,\n>>> Example: project 1 3" << endl;
			cout << ">>> Type options to see this list again." << endl;
			cout << ">>> Type exit to leave program" << endl;
				
			// display the various commands to the user
		}
		else if (command.compare("open") == 0)
		{
			if (parameters.size() < 3)
			{
				cout << ">>> Not enough data" << endl;
				continue;
			}
			else if (parameters.size() > 3)
			{
				cout << ">>> Too much data" << endl;
				continue;
			}
			else if (parameters[1] == "1" and currentBit == false)
			{
				Current* c = new Current(stod(parameters[2]));
				accounts.push_back(c);
				currentBit = true;
				cout << ">>> Success!!!" << endl;
			}
			else if (parameters[1] == "1" and currentBit == true)
			{
				cout << ">>> Current account alread opened cannot open another!" << endl;
			}
			else if (parameters[1] == "2")
			{
				Savings* s = new Savings(stod(parameters[2]), false);
				accounts.push_back(s);
				cout << ">>> Success!!!" << endl;
			}
			else if (parameters[1] == "3" and isaBit == false and stod(parameters[2]) >= 1000)
			{
				Savings* isa = new Savings(stod(parameters[2]), true);
				accounts.push_back(isa);
				isaBit = true;
				cout << ">>> Success!!!" << endl;
			}
			else if (parameters[1] == "3" and isaBit == false and stod(parameters[2]) < 1000)
			{
				cout << ">>> Account cannot be opened unless 1000 GBP is deposited" << endl;
			}
			else if (parameters[1] == "3" and isaBit == true)
			{
				cout << ">>> ISA account alread opened cannot open another!" << endl;
			}
			else
			{
				cout << ">>> Invalid entry: (1) = Current, (2) = Savings, (3) = ISA. " << endl;
			}
			// allow a user to open an account
			// e.g., Account* a = new Savings(...);
		}
		else if (command.compare("view") == 0)
		{
			if (parameters.size() > 2)
			{
				cout << ">>> Too much data!" << endl;
				continue;
			}
			else if (parameters.size() == 2 and is_Number(parameters[1]) == false)
			{
				cout << ">>> Please enter account as a number" << endl;
				continue;
			}
			else if (userCommand == "view" and accounts.size() <= 0)
			{
				cout << ">>> No accounts open!" << endl;
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
				cout << ">>> Account does not currently exsist, there are " << accounts.size() << " accounts open" << endl;
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
			if (parameters.size() < 3)
			{
				cout << ">>> Not enough data" << endl;
				continue;
			}
			else if (parameters.size() > 3)
			{
				cout << ">>> Too much data" << endl;
				continue;
			}
			else if ((is_Number(parameters[1]) == false) or (is_Number(parameters[2]) == false))
			{
				cout << ">>> Please enter numbers for account and values." << endl;
				continue;
			}
			else if (userCommand == "withdraw")
			{
				cout << ">>> Invalid entry: please follow with account number and amount" << endl;
			}
			else if (stoi(parameters[1]) > accounts.size() or stoi(parameters[1]) == 0)
			{
				cout << ">>> Account does not currently exsist, there are " << accounts.size() << " accounts open" << endl;
			}
			else if (stoi(parameters[1]) > 0)
			{
				accounts[stoi(parameters[1]) - 1]->withdraw(stoi(parameters[2]));
			}
			// allow user to withdraw funds from an account
		}
		else if (command.compare("deposit") == 0)
		{
			if (parameters.size() < 3)
			{
				cout << ">>> Not enough data" << endl;
				continue;
			}
			else if (parameters.size() > 3)
			{
				cout << ">>> Too much data" << endl;
				continue;
			}
			else if ((is_Number(parameters[1]) == false) or (is_Number(parameters[2]) == false))
			{
				cout << ">>> Please enter numbers for account and values." << endl;
				continue;
			}
			else if (userCommand == "deposit")
			{
				cout << ">>> Invalid entry: please follow with account number and amount" << endl;
			}
			else if (stoi(parameters[1]) > accounts.size() or stoi(parameters[1]) == 0)
			{
				cout << ">>> Account does not currently exsist, there are " << accounts.size() << " accounts open" << endl;
			}
			else if (stoi(parameters[1]) > 0)
			{
				accounts[stoi(parameters[1]) - 1]->deposit(stoi(parameters[2]));
			}
			// allow user to deposit funds into an account
		}
		else if (command.compare("transfer") == 0)
		{
			if (parameters.size() < 4)
			{
				cout << ">>> Not enough data" << endl;
				continue;
			}
			else if (parameters.size() > 4)
			{
				cout << ">>> Too much data" << endl;
				continue;
			}
			else if ((is_Number(parameters[1]) == false) or (is_Number(parameters[2]) == false) or (is_Number(parameters[3]) == false))
			{
				cout << ">>> Please enter numbers for account and values." << endl;
				continue;
			}
			else if (stoi(parameters[1]) > accounts.size() or stoi(parameters[1]) == 0 or stoi(parameters[2]) > accounts.size() or stoi(parameters[2]) == 0)
			{
				cout << ">>> Account does not currently exsist, there are " << accounts.size() << " accounts open" << endl;
			}
			else if (accounts[stoi(parameters[1]) - 1]->account_Type == 1)
			{
				if ((accounts[stoi(parameters[1]) - 1]->get_Overdraft() + accounts[stoi(parameters[1]) - 1]->get_Balance()) < stoi(parameters[3]))
				{
					cout << ">>> Transfer cannot be made dude to insufficient funds in the account!" << endl;
				}
				else if ((accounts[stoi(parameters[1]) - 1]->get_Overdraft() + accounts[stoi(parameters[1]) - 1]->get_Balance()) >= stoi(parameters[3]))
				{
					accounts[stoi(parameters[1]) - 1]->withdraw(stoi(parameters[3]));
					accounts[stoi(parameters[2]) - 1]->deposit(stoi(parameters[3]));
				}
			}
			else if (accounts[stoi(parameters[1]) - 1]->account_Type == 2)
			{
				if (accounts[stoi(parameters[1]) - 1]->get_Balance() < stoi(parameters[3]))
				{
					cout << ">>> Transfer cannot be made dude to insufficient funds in the account!" << endl;
				}
				else if (accounts[stoi(parameters[1]) - 1]->get_Balance() >= stoi(parameters[3]))
				{
					accounts[stoi(parameters[1]) - 1]->withdraw(stoi(parameters[3]));
					accounts[stoi(parameters[2]) - 1]->deposit(stoi(parameters[3]));
				}
			}
			// allow user to transfer funds between accounts
			// i.e., a withdrawal followed by a deposit!
		}
		else if (command.compare("project") == 0)
		{
			if (parameters.size() < 3)
			{
				cout << ">>> Not enough data" << endl;
				continue;
			}
			else if (parameters.size() > 3)
			{
				cout << ">>> Too much data" << endl;
				continue;
			}
			else if ((is_Number(parameters[1]) == false) or (is_Number(parameters[2]) == false))
			{
				cout << ">>> Please enter numbers for account and values." << endl;
				continue;
			}
			else if ((stoi(parameters[1]) > accounts.size()) or (stoi(parameters[1]) == 0))
			{
				cout << ">>> Account does not currently exsist, there are " << accounts.size() << " accounts open" << endl;
			}
			else if (accounts[stoi(parameters[1]) - 1]->account_Type == 2)
			{
				double temp = accounts[stoi(parameters[1]) - 1]->compute_Intrest(stoi(parameters[2]));
				cout << ">>> After " << stoi(parameters[2]) << " years, Your balance will be: " << char(156) << fixed << setprecision(2) << temp << endl;
			}
			else if (accounts[stoi(parameters[1]) - 1]->account_Type == 1)
			{
				cout << ">>> Account type does not gain intrest!" << endl;
			}
			// compute compound interest t years into the future
		}
		else
		{
			cout << "Command not avalible.\nType options for for commands" << endl;
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