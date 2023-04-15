#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<climits>
#include<stdio.h>
using namespace std;

void Menufunc();
void createAcc();
void checkBalance();
void deposit();
void withdrawfunc();
void transferFunds();
void loan();
void deleteAcc();
int exit();

int MenuChoice = 0;
long checkIBAN, IBAN, cash_dep, crnt_balance, withdraw;
string name, read, checkpassword, password;

fstream Account; // new file for an account
void createAcc()
{
	cout << endl << "Thanks for choosing ATMW Bank. To create your account kindly follow the procedure." << endl;

	//name
	cout << "Enter your name: ";
	cin.ignore();
	getline(cin, name);

	//IBAN
	srand(time(0));
	cout << "Account's IBAN number : ";
	IBAN = rand();
	cout << IBAN;
	cout << endl;

	Account.open(to_string(IBAN) + ".txt", ios::out);

	//password
	cout << "Enter your password : ";
	getline(cin, password);

	//depositing money
	cout << "Kindly Deposit Money to create your account (Deposit atleast 1000) : ";
	cin >> cash_dep;

	// first diposit validation according to bank policy
	while (cin.fail() || cash_dep < 1000)
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Kindly enter A value more than 1000 as it's a bank policy: ";
		cin >> cash_dep;
	}

	//text file entries
	Account << name << endl;
	Account << IBAN << endl;
	Account << password << endl;
	Account << cash_dep << endl; // here crnt_balance = cash_dep 

	Account.close();

	//program shows the manu again
	cout << endl;
	cout << "Press 1 for menu else any number to exit : ";
	cin >> MenuChoice;
	system("CLS");

	if (MenuChoice == 1)
	{
		cout << endl;
		Menufunc();
	}
	else
		exit();
}

void checkBalance()
{
	cout << "Please enter your IBAN address: ";
	cin >> checkIBAN;
	//checkIBAN validation
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "You can only enter numeric digits in IBAN address. ";
		cin >> checkIBAN;
	}

	cin.ignore();

	// pasword check for specified IBAN
	Account.open(to_string(checkIBAN) + ".txt", ios::in);
	if (Account.is_open())
	{
		for (int i = 1; getline(Account, read); i++)
		{
			if (i == 3) // i is the line no. being red to check password in file
			{
				while (true)
				{
					cout << "please enter password: ";
					getline(cin, checkpassword);
					if (checkpassword == read)
						break;
				}

			}
		}
		Account.close();

		// displaying current balance for specified IBAN
		Account.open(to_string(checkIBAN) + ".txt", ios::in);
		for (int i = 1; getline(Account, read); i++)
		{
			if (i == 1) // i is the line no. being red
				cout << "\nName : " << read << endl;

			if (i == 4)
				cout << "Balance : " << read << endl;
		}

		Account.close();

		cout << endl;
		cout << "Press 1 for menu else any number to exit : ";
		cin >> MenuChoice;
		if (MenuChoice == 1)
		{
			cout << endl;
			Menufunc();
		}
		else
			exit();
	}
	else
	{
		cout << "The account doesnt exist" << endl;
		cout << "Press 1 to create new account" << endl;
		cout << "press 2 for menu" << endl;
		cout << "Press 3 to exit the program" << endl;
		cout << endl << "Your choice : ";
		cin >> MenuChoice;
		if (MenuChoice == 1)
			createAcc();
		else if (MenuChoice == 2)
			Menufunc();
		else if (MenuChoice == 3)
			exit();
	}


}

void deposit()
{
	int cdeposit; //use to temporary store amount in read value from file
	cout << "Please enter your IBAN address: ";
	cin >> checkIBAN;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "You can only enter numeric digits in IBAN address. ";
		cin >> checkIBAN;
	}

	cin.ignore();

	// pasword check for specified IBAN
	Account.open(to_string(checkIBAN) + ".txt", ios::in);
	if (Account.is_open())
	{
		for (int i = 1; getline(Account, read); i++)
		{
			if (i == 1)
				name = read;
			if (i == 2)
				IBAN = atoi(read.c_str());
			if (i == 3) // i is the line no. being read
			{
				while (true)
				{
					cout << "please enter password: ";
					getline(cin, checkpassword);
					if (checkpassword == read)
					{
						password = read;
						break;
					}

				}
			}
			if (i == 4)
			{
				cdeposit = atoi(read.c_str());
			}
		}


		Account.close();


		// cash deposit + current balance for specified IBAN
		cout << "Please enter the amount you want to deposit: ";
		cin >> cash_dep;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Abay andha hai kia, bataya bhi hai cash enter kr or konsa cash abc hota? yar hud krtay ho panday g sahi value dalo integer main : ";
			cin >> cash_dep;
		}
		cash_dep = cash_dep + cdeposit;
		Account.open(to_string(checkIBAN) + ".txt", ios::out);

		Account << name << endl;
		Account << IBAN << endl;
		Account << password << endl;
		Account << cash_dep << endl;

		cout << "Your new balance is : " << cash_dep;
		cout << endl;
		cout << "Press 1 for menu else any number to exit : ";
		cin >> MenuChoice;
		system("CLS");
		if (MenuChoice == 1)
		{
			cout << endl;
			Menufunc();
		}
		else
			exit();
	}


	else
	{
		system("CLS");
		cout << "The account doesnt exist" << endl;
		cout << "Press 1 to create new account" << endl;
		cout << "press 2 for menu" << endl;
		cout << "Press 3 to exit the program" << endl;
		cout << endl << "Your choice : ";
		cin >> MenuChoice;
		system("CLS");

		if (MenuChoice == 1)
			createAcc();
		else if (MenuChoice == 2)
			Menufunc();
		else if (MenuChoice == 3)
			exit();
	}
}

void withdrawfunc()
{
	int cwithdraw; //store the value of cash temporarily in int after reading from file
	cout << "Please enter your IBAN address: ";
	cin >> checkIBAN;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "You can only enter numeric digits in IBAN address. ";
		cin >> checkIBAN;
	}

	cin.ignore();

	// pasword check for specified IBAN
	Account.open(to_string(checkIBAN) + ".txt", ios::in);
	if (Account.is_open())
	{
		for (int i = 1; getline(Account, read); i++)
		{
			if (i == 1)
				name = read;
			if (i == 2)
				IBAN = atoi(read.c_str());
			if (i == 3) // i is the line no. being red
			{
				while (true)
				{
					cout << "please enter password: ";
					getline(cin, checkpassword);
					if (checkpassword == read)
					{
						password = read;
						break;
					}

				}
			}
			if (i == 4)
			{
				cwithdraw = atoi(read.c_str());
			}
		}


		Account.close();


		// cash deposit + current balance for specified IBAN
		cout << "Please enter the amount you want to Withdraw: ";
		cin >> withdraw;
		while (cin.fail() || (cwithdraw - withdraw) < 0)
		{
			if (cwithdraw - withdraw < 0)
			{
				cout << "Your amount exceeds total balance. \n" << endl;
				cout << "Press 1 to Enter amount again" << endl;
				cout << "press 2 for menu" << endl;
				cout << "Press 3 to exit the program" << endl;
				cout << endl << "Your choice : ";
				cin >> MenuChoice;
				if (MenuChoice == 1)
				{
					cout << "Enter amount to withdraw : ";
					cin >> withdraw;
				}

				else if (MenuChoice == 2)
					Menufunc();
				else if (MenuChoice == 3)
					exit();
			}
			else
			{
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				cout << "Value can not be in string. Kindly enter integer value : ";
				cin >> withdraw;
			}

		}
		withdraw = cwithdraw - withdraw;
		Account.open(to_string(checkIBAN) + ".txt", ios::out);

		Account << name << endl;
		Account << IBAN << endl;
		Account << password << endl;
		Account << withdraw << endl;

		cout << "Your new balance is : " << withdraw;
		cout << endl;
		cout << "Press 1 for menu else any number to exit : ";
		cin >> MenuChoice;
		system("CLS");

		if (MenuChoice == 1)
		{
			cout << endl;
			Menufunc();
		}
		else
			exit();
	}


	else
	{
		system("CLS");

		cout << "The account doesnt exist" << endl;
		cout << "Press 1 to create new account" << endl;
		cout << "press 2 for menu" << endl;
		cout << "Press 3 to exit the program" << endl;
		cout << endl << "Your choice : ";
		cin >> MenuChoice;
		system("CLS");

		if (MenuChoice == 1)
			createAcc();
		else if (MenuChoice == 2)
			Menufunc();
		else if (MenuChoice == 3)
			exit();
	}
}

void transferFunds()
{
	int money = 0;

	cout << "Please enter IBAN address of sender : ";
	cin >> checkIBAN;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "You can only enter numeric digits in IBAN address : ";
		cin >> checkIBAN;
	}

	cin.ignore();

	Account.open(to_string(checkIBAN) + ".txt", ios::in);
	if (Account.is_open())
	{
		for (int i = 1; getline(Account, read); i++)
		{
			if (i == 1)
				name = read;
			if (i == 2)
				IBAN = atoi(read.c_str());
			if (i == 3) // i is the line no. being red
			{
				while (true)
				{
					cout << "please enter password: ";
					getline(cin, checkpassword);
					if (checkpassword == read)
					{
						password = read;
						break;
					}

				}
			}
			if (i == 4)
			{
				crnt_balance = atoi(read.c_str());
			}
		}

		Account.close();
	}

	else
	{
		cout << "The account doesnt exist" << endl;
		cout << "Press 1 to create new account" << endl;
		cout << "press 2 for menu" << endl;
		cout << "Press 3 to exit the program" << endl;
		cout << endl << "Your choice : ";
		cin >> MenuChoice;
		system("CLS");
		if (MenuChoice == 1)
			createAcc();
		else if (MenuChoice == 2)
			Menufunc();
		else if (MenuChoice == 3)
			exit();
	}



	cout << "Enter the amount you want to transfer : ";
	cin >> money;

	Account.open(to_string(checkIBAN) + ".txt", ios::out);

	while (cin.fail() || (crnt_balance - money) < 0)
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "You have entered either a string or you amount exceeds current balance " << endl;
		cout << "Kindly enter you amount again : ";
		cin >> money;
	}
	crnt_balance = crnt_balance - money;
	Account << name << endl;
	Account << IBAN << endl;
	Account << password << endl;
	Account << crnt_balance << endl;

	Account.close();

	cout << "Please enter the IBAN address of  reciever's account : ";
	cin >> checkIBAN;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "You can only enter numeric digits in IBAN address : ";
		cin >> checkIBAN;
	}

	cin.ignore();

	Account.open(to_string(checkIBAN) + ".txt", ios::in);
	if (Account.is_open())
	{
		for (int i = 1; getline(Account, read); i++)
		{
			if (i == 1)
				name = read;
			if (i == 2)
				IBAN = atoi(read.c_str());
			if (i == 3) // i is the line no. being red
			{
				while (true)
				{
					cout << "please enter password: ";
					getline(cin, checkpassword);
					if (checkpassword == read)
					{
						password = read;
						break;
					}

				}
			}
			if (i == 4)
			{
				crnt_balance = atoi(read.c_str());
			}
		}

		Account.close();
	}
	else
	{
		cout << "The account doesnt exist" << endl;
		cout << "Press 1 to create new account" << endl;
		cout << "press 2 for menu" << endl;
		cout << "Press 3 to exit the program" << endl;
		cout << endl << "Your choice : ";
		cin >> MenuChoice;
		system("CLS");
		if (MenuChoice == 1)
			createAcc();
		else if (MenuChoice == 2)
			Menufunc();
		else if (MenuChoice == 3)
			exit();
	}


	Account.open(to_string(checkIBAN) + ".txt", ios::out);
	crnt_balance = crnt_balance + money;
	Account << name << endl;
	Account << IBAN << endl;
	Account << password << endl;
	Account << crnt_balance << endl;

	Account.close();

}

void  loan()
{
	cout << "Please enter your IBAN address: ";
	cin >> checkIBAN;
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "You can only enter numeric digits in IBAN address. ";
		cin >> checkIBAN;
	}

	cin.ignore();

	// pasword check for specified IBAN
	Account.open(to_string(checkIBAN) + ".txt", ios::in);
	if (Account.is_open())
	{
		for (int i = 1; getline(Account, read); i++)
		{
			if (i == 1)
				name = read;
			if (i == 2)
				IBAN = atoi(read.c_str());
			if (i == 3) // i is the line no. being read
			{
				while (true)
				{
					cout << "please enter password: ";
					getline(cin, checkpassword);
					if (checkpassword == read)
					{
						password = read;
						break;
					}
				}
			}
			if (i == 4)
			{
				crnt_balance = atoi(read.c_str());
			}
		}


		Account.close();


		// cash deposit + current balance for specified IBAN
		cout << "How much loan you wanna take : ";
		cin >> cash_dep;
		while (cin.fail())
		{
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Abay andha hai kia, bataya bhi hai cash enter kr or konsa cash abc hota? yar hud krtay ho panday g sahi value dalo integer main : ";
			cin >> cash_dep;
		}
		cash_dep = cash_dep + crnt_balance;
		Account.open(to_string(checkIBAN) + ".txt", ios::out);

		Account << name << endl;
		Account << IBAN << endl;
		Account << password << endl;
		Account << cash_dep << endl;

		cout << "Your new balance is : " << cash_dep;
		cout << endl;
		cout << "Press 1 for menu else any number to exit : ";
		cin >> MenuChoice;
		system("CLS");
		if (MenuChoice == 1)
		{
			cout << endl;
			Menufunc();
		}
		else
			exit();
	}


	else
	{
		system("CLS");
		cout << "The account doesnt exist" << endl;
		cout << "Press 1 to create new account" << endl;
		cout << "press 2 for menu" << endl;
		cout << "Press 3 to exit the program" << endl;
		cout << endl << "Your choice : ";
		cin >> MenuChoice;
		system("CLS");

		if (MenuChoice == 1)
			createAcc();
		else if (MenuChoice == 2)
			Menufunc();
		else if (MenuChoice == 3)
			exit();
	}
}

void deleteAcc()
{
	string filename;

	cout << "Please enter your IBAN address: ";
	cin >> checkIBAN;
	//checkIBAN validation
	while (cin.fail())
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "You can only enter numeric digits in IBAN address. ";
		cin >> checkIBAN;
	}
	cin.ignore();

	Account.open(to_string(checkIBAN) + ".txt", ios::in);
	if (Account.is_open())
	{
		for (int i = 1; getline(Account, read); i++)
		{
			if (i == 3) // i is the line no. being red to check password in file
			{
				while (true)
				{
					cout << "please enter password: ";
					getline(cin, checkpassword);
					if (checkpassword == read)
						break;
				}
			}
		}
		Account.close();

		string strr = to_string(checkIBAN) + ".txt";
		if (remove(strr.c_str()) != 0)
			cout << "Error deleting file.";
		else
			puts("File successfully deleted");  //The puts() function in C/C++ is used to write a line or string to the output( stdout ) stream

	}
	else
	{
		system("CLS");
		cout << "The account doesnt exist" << endl;

		cout << "press 1 for menu" << endl;
		cout << "Press 2 to exit the program" << endl;
		cout << endl << "Your choice : ";
		cin >> MenuChoice;
		system("CLS");

		if (MenuChoice == 1)
			Menufunc();
		else if (MenuChoice == 2)
			exit();
	}
}


int exit()
{
	cout << endl << setfill('-') << setw(50) << "-" << "\n Allah Hafiz AND Thanks for Coming To ATMW Banks" << endl << setw(52) << "-\n\n";
	return 0;
}
void Menufunc()
{
	cout << endl << setfill('-') << setw(9) << "-" << " MENU " << setw(9) << "-" << endl << endl;
	cout << " Press 1 to create account." << endl;
	cout << " Press 2 to Check balance." << endl;
	cout << " Press 3 to deposit money." << endl;
	cout << " Press 4 to withdraw money." << endl;
	cout << " Press 5 to transfer funds." << endl;
	cout << " Press 6 to apply for loan." << endl;
	cout << " Press 7 to delete an account." << endl;
	cout << " Press 8 to EXIT." << endl;

	// manu selection
	cout << "\nKindly Input Your Desired Option : ";
	cin >> MenuChoice;
	while (cin.fail() || (MenuChoice != 1 && MenuChoice != 2 && MenuChoice != 3 && MenuChoice != 4 && MenuChoice != 5 && MenuChoice != 6 && MenuChoice != 7 && MenuChoice != 8))
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Kindly enter integer value from 1-8" << endl;
		cin >> MenuChoice;

	}
	system("CLS");

	if (MenuChoice == 1)
		createAcc();
	else if (MenuChoice == 2)
		checkBalance();
	else if (MenuChoice == 3)
		deposit();
	else if (MenuChoice == 4)
		withdrawfunc();
	else if (MenuChoice == 5)
		transferFunds();

	else if (MenuChoice == 6)
		loan();
	else if (MenuChoice == 7)
		deleteAcc();
	else if (MenuChoice == 8)
	{
		cout << endl;
		exit();
	}

}


int main()
{
	Menufunc();
}