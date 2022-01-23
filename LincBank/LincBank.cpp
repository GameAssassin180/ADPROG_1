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
	vector <Account*> accounts;	// Stores Accounts, either current or savings.
	vector <string> parameters;	// Stores the users input but split by spaces. 
	string userCommand;			// Stores the users input as one variable.
	bool currentBit = (false);	// Used to see if a current account has been opened.
	bool isaBit = (false);		// Used to see if an ISA account has been opened.
	// you may also want to store a collection of opened accounts here

	cout << "  ~~~ Welcome to LincBank! ~~~" << endl;
	cout << "~~~ Type options for commands ~~~" << endl;

	while (userCommand != "exit")	// While the user command isnt exit.
	{
		parameters.clear(); // clear ready for next command
		cout << endl << ">>> ";

		getline(cin, userCommand);
		if (userCommand.empty() || userCommand.find_first_not_of(' ') == string::npos)	// If the user just presses enter or the command is a space.
		{
			continue;
		}

		// Copies the user command string to a list of characters.
		char* cstr = new char[userCommand.length() + 1];
		strcpy(cstr, userCommand.c_str());

		// Seperates the string into seperate words.
		char* token;
		token = strtok(cstr, " ");
		
		// While the string isnt empty push the word back to the parameters vector.
		while (token != NULL)
		{
			parameters.push_back(token);
			token = strtok(NULL, " ");
		}

		// Define all commands as per the brief
		string command = parameters[0];	// The first word entered by th user.

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
			if (parameters.size() < 3)	// If the parameters list is under 3 
			{
				cout << ">>> Not enough data" << endl;
				continue;
			}
			else if (parameters.size() > 3)	// If the parameters list is over 3.
			{
				cout << ">>> Too much data" << endl;
				continue;
			}
			else if (parameters.size() == 3 and is_Number(parameters[2]) ==  false)	// If the user enters any words.
			{
				cout << ">>> Please enter as numbers." << endl;
			}
			else if (parameters[1] == "1" and currentBit == false)	// If the user enters 1 and the current bit is false.
			{
				// Opens a new Current account.
				Account* c = new Current(stod(parameters[2]));	// Creates a new account.
				accounts.push_back(c);							// Pushes the Current account back to the accounts vector
				currentBit = true;								// Sets the current bit to true.
				cout << ">>> Current Account Opened!!!" << endl;	// Lets the user know its opened.
			}
			else if (parameters[1] == "1" and currentBit == true)	// If the user enters 1 and the current bit is true.
			{
				cout << ">>> Current account already opened cannot open another!" << endl;
			}
			else if (parameters[1] == "2")	// If the user enters 2
			{
				Account* s = new Savings(stod(parameters[2]), false);	// Creates a new account.
				accounts.push_back(s);									// Pushes the Savings account back to the accounts vector.
				cout << ">>> Savings Account Opened!!!" << endl;		// Lets the user know that its opened.
			}
			else if (parameters[1] == "3" and isaBit == false and stod(parameters[2]) >= 1000)	// If the user enters 3 the isa bit is set to false and the value opened with is over 1000.
			{
				Account* isa = new Savings(stod(parameters[2]), true);	// Creates a new account.
				accounts.push_back(isa);								// Pushed the Savings account back to the accounts vector.
				isaBit = true;											// Sets the ISA bit to true.
				cout << ">>> ISA Account Opened!!!" << endl;			// Lets the user know that its opened. 
			}
			else if (parameters[1] == "3" and isaBit == false and stod(parameters[2]) < 1000)	// If the user enters 3 the isa bit is set to false and the value opened with is under 1000.
			{
				cout << ">>> Account cannot be opened unless 1000 GBP is deposited" << endl;
			}
			else if (parameters[1] == "3" and isaBit == true)	// If the user enters 3 and the isa bit is set to true.
			{
				cout << ">>> ISA account alread opened cannot open another!" << endl;
			}
			else	// If anything else is entered.
			{
				cout << ">>> Invalid entry: (1) = Current, (2) = Savings, (3) = ISA. " << endl;
			}
			// allow a user to open an account
			// e.g., Account* a = new Savings(...);
		}
		else if (command.compare("view") == 0)
		{
			if (parameters.size() > 2)	// If the parameters list is over 2.
			{
				cout << ">>> Too much data!" << endl;
				continue;
			}
			else if (parameters.size() == 2 and is_Number(parameters[1]) == false)	// If the user enters any words. 
			{
				cout << ">>> Please enter account as a number" << endl;
				continue;
			}
			else if (userCommand == "view" and accounts.empty())	// If the user enters view and the accounts vector is empty.
			{
				cout << ">>> No accounts open!" << endl;
			}
			else if (userCommand == "view" and accounts.size() > 0)	// If the user enters view and accounts are in the accounts vector.
			{
				for (int i = 0; i < accounts.size(); i++)	// For every account in the accounts vector.
				{
					cout << "\n>>> Account number " << i + 1 << endl;
					accounts[i]->to_String();	// Runs the to_String function of the account.
				}
			}
			else if (stoi(parameters[1]) > accounts.size() or stoi(parameters[1]) == 0)	// If the user enters view followed by a number and that index is bigger then the accounts entered.
			{
				cout << ">>> Account does not currently exist, there are " << accounts.size() << " accounts open" << endl;
			}
			else if (stoi(parameters[1]) > 0 and accounts.size() > 0)	// If the user enters a specific account.
			{
				accounts[stoi(parameters[1]) - 1]->to_String();	
			}
			// display an account according to an index (starting from 1)
			// alternatively, display all accounts if no index is provided
		}
		else if (command.compare("withdraw") == 0)
		{
			if (parameters.size() < 3)	// If the parameters list is under 3.
			{
				cout << ">>> Not enough data" << endl;
				continue;
			}
			else if (parameters.size() > 3)	// If the parameters list is over 3.
			{
				cout << ">>> Too much data" << endl;
				continue;
			}
			else if ((is_Number(parameters[1]) == false) or (is_Number(parameters[2]) == false))	// If either parameter one ot parameter two contain numbers. 
			{
				cout << ">>> Please enter numbers for account and values." << endl;
				continue;
			}
			else if (stoi(parameters[1]) > accounts.size() or stoi(parameters[1]) == 0)	//	If the user enters an account that doesnt exist or number 0. 
			{
				cout << ">>> Account does not currently exist, there are " << accounts.size() << " accounts open" << endl;
			}
			else if (stoi(parameters[1]) > 0)	// If the account entered is greater then 0.
			{
				accounts[stoi(parameters[1]) - 1]->withdraw(stod(parameters[2]));	// Runs the withdraw method in the account specified.
			}
			// allow user to withdraw funds from an account
		}
		else if (command.compare("deposit") == 0)
		{
			if (parameters.size() < 3)	// If the parameters list is under 3.
			{
				cout << ">>> Not enough data" << endl;
				continue;
			}
			else if (parameters.size() > 3)	// If the parameters list is over 3.
			{
				cout << ">>> Too much data" << endl;
				continue;
			}
			else if ((is_Number(parameters[1]) == false) or (is_Number(parameters[2]) == false))	// If the user enters any thing that isnt a number.
			{
				cout << ">>> Please enter numbers for account and values." << endl;
				continue;
			}
			else if (stoi(parameters[1]) > accounts.size() or stoi(parameters[1]) == 0)	// If the user enters an account that doesnt exist.
			{
				cout << ">>> Account does not currently exist, there are " << accounts.size() << " accounts open" << endl;
			}
			else if (stoi(parameters[1]) > 0)	// If the user enters an account that exists.
			{
				accounts[stoi(parameters[1]) - 1]->deposit(stod(parameters[2]));	// Runs the deposit commenad for the account specified.
			}
			// allow user to deposit funds into an account
		}
		else if (command.compare("transfer") == 0)
		{
			if (parameters.size() < 4)	// If the users enters less then 4 things.
			{
				cout << ">>> Not enough data" << endl;
				continue;
			}
			else if (parameters.size() > 4)	// If the user enters more then 4 things.
			{
				cout << ">>> Too much data" << endl;
				continue;
			}
			else if ((is_Number(parameters[1]) == false) or (is_Number(parameters[2]) == false) or (is_Number(parameters[3]) == false))	// If any of the last 3 parameters are not numbers.
			{
				cout << ">>> Please enter numbers for account and values." << endl;
				continue;
			}
			else if (stoi(parameters[1]) > accounts.size() or stoi(parameters[1]) == 0 or stoi(parameters[2]) > accounts.size() or stoi(parameters[2]) == 0)	// If the user enters any accounts that dont exist.
			{
				cout << ">>> Account does not currently exist, there are " << accounts.size() << " accounts open" << endl;
			}
			else if (accounts[stoi(parameters[1]) - 1]->account_Type == 1)	// If the first account entered is a current account.
			{
				if ((accounts[stoi(parameters[1]) - 1]->get_Overdraft() + accounts[stoi(parameters[1]) - 1]->get_Balance()) < stoi(parameters[3]))	// If the Current account doesnt have sufficient funds.
				{
					cout << ">>> Transfer cannot be made due to insufficient funds in the account!" << endl;
				}
				else if ((accounts[stoi(parameters[1]) - 1]->get_Overdraft() + accounts[stoi(parameters[1]) - 1]->get_Balance()) >= stoi(parameters[3]))	// If the current account does have sufficient funds.
				{
					accounts[stoi(parameters[1]) - 1]->withdraw(stod(parameters[3]));	// Withdraws from the first account.
					accounts[stoi(parameters[2]) - 1]->deposit(stod(parameters[3]));	// Deposits into the second account.
				}
			}
			else if (accounts[stoi(parameters[1]) - 1]->account_Type == 2)	// If the fist account entered is a savings account.
			{
				if (accounts[stoi(parameters[1]) - 1]->get_Balance() < stoi(parameters[3]))	// If the account doesnt have suffiecient funds.
				{
					cout << ">>> Transfer cannot be made due to insufficient funds in the account!" << endl;
				}
				else if (accounts[stoi(parameters[1]) - 1]->get_Balance() >= stoi(parameters[3]))	// If the account does have sufficient funds.
				{
					accounts[stoi(parameters[1]) - 1]->withdraw(stod(parameters[3]));	// Withdraws from the first account.
					accounts[stoi(parameters[2]) - 1]->deposit(stod(parameters[3]));	// Deposits in the second account.
				}
			}
			// allow user to transfer funds between accounts
			// i.e., a withdrawal followed by a deposit!
		}
		else if (command.compare("project") == 0)
		{
			if (parameters.size() < 3)	// If the parameters list is under 3.
			{
				cout << ">>> Not enough data" << endl;
				continue;
			}
			else if (parameters.size() > 3)	// If the parameters list is over 3.
			{
				cout << ">>> Too much data" << endl;
				continue;
			}
			else if ((is_Number(parameters[1]) == false) or (is_Number(parameters[2]) == false))	// If the user enters anything but numbers.
			{
				cout << ">>> Please enter numbers for account and values." << endl;
				continue;
			}
			else if ((stoi(parameters[1]) > accounts.size()) or (stoi(parameters[1]) == 0))	// If the user enters an account that doesnt exist.
			{
				cout << ">>> Account does not currently exist, there are " << accounts.size() << " accounts open" << endl;
			}
			else if (accounts[stoi(parameters[1]) - 1]->account_Type == 2)	// If the account type is a savings account.
			{
				double temp = accounts[stoi(parameters[1]) - 1]->compute_Intrest(stoi(parameters[2]));	// Runs the compute intrest method for the account and gives it to the temp variable.
				cout << ">>> After " << stoi(parameters[2]) << " years, Your balance will be: " << char(156) << fixed << setprecision(2) << temp << endl;	// Prints out the predicted balance after t years.
			}
			else if (accounts[stoi(parameters[1]) - 1]->account_Type == 1)	// If the acount type is a Current account. 
			{
				cout << ">>> Account type does not gain interest!" << endl;
			}
			// compute compound interest t years into the future
		}
		else if (command.compare("exit") == 0)
		{
			continue;
		}
		else
		{
			cout << ">>> Command not avalible.\n>>> Type options for for commands" << endl;
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