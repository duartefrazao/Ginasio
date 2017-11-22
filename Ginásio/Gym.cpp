#include "stdafx.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iomanip>
#include "Gym.h"
#include "Client.h"
#include "termcolor.hpp"

#ifdef WIN32
#include <conio.h>
#else
int _getch(void);
#endif

using namespace std;

void inputClientIdObj(int &optionClient, Gym &gym, Client** client_found);
void inputStaffIdObj(int &optionStaff, Gym &gym, Staff** staff_found);
void inputPtIdObj(int &optionPt, Gym &gym, Staff** staff_found);
void inputProgramIdObj(int &optionProgram, Gym &gym, Program** program_found);

//Functions
int filterInput(int inf, int sup,std::string msg = "Selection: ");

// Gym Constructor
Gym::Gym(string name, vector<Program *> &programs, vector<Client *> &clients,
		vector<Staff *> &staff, vector<PersonalTrainer *> &profs,
		Schedule &gymSchedule, int maxNumClients, int maxCapacity,
		Finance &gymFinance) :
		name(name), programs(programs), clients(clients), staff(staff), profs(
				profs), gymSchedule(gymSchedule), maxNumClients(maxNumClients), maxCapacity(
				maxCapacity), gymFinance(gymFinance) {
}

// Gym Constructor
Gym::Gym(string name, vector<Program *> &programs, Schedule &gymSchedule,
		int maxNumClients, int maxCapacity, Finance &gymFinance) :
		name(name), programs(programs), gymSchedule(gymSchedule), maxNumClients(
				maxNumClients), maxCapacity(maxCapacity), gymFinance(
				gymFinance) {
}

// Gym Destructor
Gym::~Gym() {

}

#pragma region Gets 

//Get name of the gym
string Gym::getName() const { return name; }

//Returns the vector of client pointers of the gym
vector<Client *> Gym::getClients() const {return clients;}

//Returns the vector of program subscriptions pointers of the gym
vector<Program *> Gym::getPrograms() const {return programs;}

//Returns the number of program subscriptions the gym offers
int Gym::getNumberPrograms() const{return programs.size();}

//Returns the vector of pointers to staff of the gym
vector<Staff *> Gym::getStaff() const {return staff;}

//Returns the vector of pointers to Personal Trainer of the gym
vector<PersonalTrainer *> Gym::getPT() const {return profs;}

//Returns the gym schedule
Schedule Gym::getGymSchedule() const {return gymSchedule;}

//Returns the max number of clients the gym can sign
int Gym::getMaxNumClients() const {return maxNumClients;}

//Returns the max capacity of the gym
int Gym::getMaxCapacity() const {return maxCapacity;}

//Returns the finance of the gym
Finance Gym::getGymFinance() const {return gymFinance;}

#pragma endregion




#pragma region Sets


//Sets the vector of clients of the gym
void Gym::setClients(vector<Client *> clients) {
	this->clients = clients;
}


//Sets the vector of staff of the gym
void Gym::setStaff(vector<Staff *> staff) {
	this->staff = staff;
}


//Sets the gym schedule
void Gym::setName(string newName)
{
	name = newName;
}

void Gym::setGymSchedule(Schedule gymSchedule) {
	this->gymSchedule = gymSchedule;
}

//Sets the max number of clients of the gym
void Gym::setMaxNumClients(int maxNumClients) {
	this->maxNumClients = maxNumClients;
}

//Sets the max capacity of the gym
void Gym::setMaxCapacity(int maxCapacity) {
	this->maxCapacity = maxCapacity;
}


//Sets the gym finance
void Gym::setGymFinance(Finance gymFinance) {
	this->gymFinance = gymFinance;
}

#pragma endregion


#pragma region Add

void Gym::addClient(Client * client) {clients.push_back(client);}

void Gym::addStaff(Staff * staff) {this->staff.push_back(staff);}

void Gym::addProgram(Program* program) {programs.push_back(program);}

# pragma endregion



#pragma region Login authentication

//Performs the login process for a certain staff's id
void Gym::login() {
	cout << "    Welcome to " << name << " !      \n"
		<< "--- AUTHENTICATION PORTAL ---\n";


	Staff* staff_found = NULL;
	bool staffFound = 0;
	do
	{
		int staffId;
		cout << "Login ID: ";
		cin >> staffId;
		cin.ignore();

		if (findStaff(staffId, &staff_found))
		{
			staffFound = 1;
			bool access = 0;
			char ch;
			do
			{
				string pass;
				cout << "Password: ";
				ch = _getch();
				while (ch != 13)
				{
					if (ch == 8)
					{
						if (pass.size() != 0)
						{
							pass.pop_back();
							cout << "\b \b";
						}
					}
					else
					{
						pass.push_back(ch);
						cout << "*";
					}
					ch = _getch();
				}

				if (staff_found->auth(pass))
				{
					cout << "\n\nACCESS GRANTED!\n" << "WELCOME STAFF NUMBER " << staff_found->getId() << "!\n\n";
					access = 1;
				}
				else {
					cout << "\n\nACESS DENIED!\n";
					cout << "Try again: press 0 or Exit: press 1\n" << "--> ";
					int incorrect_option;
					cin >> incorrect_option;
					while (incorrect_option != 0 && incorrect_option != 1) {
						cout << "Enter a correct command ...\n";
						cin >> incorrect_option;
					}
					if (incorrect_option) exit(0);
					cin.ignore();
				}

			} while (!access);
		}
		else
		{
			cout << endl << "STAFF NOT FOUND!" << endl;
			cout << "Try again: press 0 or Exit: press 1\n" << "--> ";
			int incorrect_option2;
			cin >> incorrect_option2;
			while (incorrect_option2 != 0 && incorrect_option2 != 1) {
				cout << "Enter a correct command ...\n";
				cin >> incorrect_option2;
			}
			if (incorrect_option2) exit(0);
			cin.ignore();
		}

	} while (!staffFound);
}


#pragma endregion

#pragma region Search algorithms
bool Gym::findStaff(int staffId, Staff **staff_found) {

	for (const auto staff_pointer : staff)
	{
		if (staff_pointer->getId() == staffId)
		{
			*staff_found = staff_pointer;
			return true;
		}
	}

	staff_found = NULL;
	return false;
}


//Finds gym's professor with a certain Id
bool Gym::findProf(int profId, Staff** prof_found) {
	for (const auto prof_pointer : profs)
	{
		if (prof_pointer->getId() == profId)
		{
			*prof_found = prof_pointer;
			return true;
		}
	}

	prof_found = NULL;
	return false;
}


//Finds gym's client with a certain Id
bool Gym::findClient(int clientId, Client** client_found) {
	for (const auto client_pointer : clients)
	{
		if (client_pointer->getId() == clientId)
		{
			*client_found = client_pointer;
			return true;
		}
	}

	client_found = NULL;
	return false;
}

//Finds gym's program with a certain Id
bool Gym::findProgram(int programId, Program** program_found) {
	for (const auto program_pointer : programs)
	{
		if (program_pointer->getCode() == programId)
		{
			*program_found = program_pointer;
			return true;
		}
	}

	program_found = NULL;
	return false;
}
#pragma endregion


//Shows gym's clients id's
void Gym::displayClientsIds()
{
	for (size_t i = 0; i < clients.size(); i++)
	{
		cout << std::setw(10) << std::left << clients.at(i)->getName() << " ID: " << clients.at(i)->getId() << endl;
	}
}

//Prints the staff the gym has contracted
void Gym::displayStaffIds() const
{
	for (size_t i = 0; i < staff.size(); i++)
	{
		cout << staff.at(i)->getName() << " ID: " << staff.at(i)->getId() << endl;
	}
}

//Prints the profs the gym has contracted
void Gym::displayProfsIds() const
{
	for (size_t i = 0; i < profs.size(); i++)
	{
		cout << profs.at(i)->getName() << " ID: " << profs.at(i)->getId() << endl;
	}
}

//Prints the programs the gym has to offer, as well as the conditions
void Gym::displayPrograms() const
{
	cout << name << " has the following programs to offer:\n\n";
	for (unsigned int i = 0; i < programs.size(); i++)
	{
		cout << *programs.at(i);
	}
}


//Returns the gym's program subscription that has the id code
Program* Gym::codeToProgram(int code)
{
	for (unsigned int i = 0; i < programs.size(); i++)
		if (code == programs.at(i)->getCode())
			return programs.at(i);

	return NULL;

}

//Prints the programs the gym has to offer, as well as the conditions
void Gym::displayProgramOptions()
{
	cout << "---Available program subscriptions---" << endl<<endl;
	for (unsigned int i = 0; i < programs.size(); i++)
		cout << *(this->getPrograms().at(i));
}

/* Changes gym's capacity */
void Gym::changeCapacity() 
{
	int newMaxCapacity;
	cout << "What is the new gym's capacity? ";
	cin >> newMaxCapacity;
	while (cin.fail() || newMaxCapacity < 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << sign::error << "Insert a valid value! ";
		cin >> newMaxCapacity;
	}
	setMaxCapacity(newMaxCapacity);
	cout << sign::success << "Maximum capacity changed successfully!\n";
}

/* Changes gym's max number of clients */
void Gym::changeMaxNumClients() 
{
	int newMaxNumClients;
	cout << "What is the new gym's maximum number of clients? ";
	cin >> newMaxNumClients;
	while (cin.fail() || newMaxNumClients < 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << sign::error << "Insert a valid value! ";
		cin >> newMaxNumClients;
	}
	setMaxNumClients(newMaxNumClients);
	cout << sign::success << "Maximum number of clients changed successfully!\n";
}

//Adds a client to the gym
void Gym::addClient()
{
	//To-do alterar mecanismo de assgn de pt
	string name;
	int age, program;
	cout << "Adicionar novo cliente" << endl << endl;

	//Name
	cout << "Nome: ";
	cin >> name;

	//Program subscription
	displayProgramOptions();
	cout << "Programa:";
	program= filterInput(1, programs.size());

	//age
	cout << "Idade: ";
	cin >> age;

	//To-do arranjar maneira de em vez de usar staff ser um professor, porque pode dar errado
	PersonalTrainer *professor = profs.at(rand() % profs.size());

	Client * newClient = new Client (name, codeToProgram(program), age, professor);

	clients.push_back(newClient);
	cout << sign::success <<"Cliente adicionado com sucesso" << endl << endl << endl;
	cout << "Informacao do novo cliente:" << endl;
	cout << *newClient;
}


/**
Removes a client
*/
void Gym::removeClient()
{
	int optionClient;
	Client *clientToEdit;
	inputClientIdObj(optionClient, *this, &clientToEdit);

	//algo que mostre ids + fun��o que check ids

	vector<Client *>::iterator it_client;
	for (it_client = clients.begin(); it_client != clients.end(); it_client++) {
		if ((*it_client)->getId() == optionClient) {
			clients.erase(it_client);
			cout << sign::success << "Client with id " << optionClient << " erased successfully!\n";
			return;
		}
	}
	cout << "Client with id " << optionClient << " does not exist!\n";
}

/**
Adds a staff to the gym
*/
void Gym::addStaff() 
{
	int age; double wage;
	string name, pass;

	cout << "Insert new staff's name: ";
	cin.ignore(1000, '\n');
	getline(cin, name);
	do {
		cout << "Insert new staff's age: ";
		cin >> age;
		cin.ignore();
	} while (age < 0);
	do {
		cout << "Insert new staff's wage: ";
		cin >> wage;
		cin.ignore();
	} while (wage < 0);
	cout << "Insert new staff's password: ";
	cin.ignore(1000, '\n');
	getline(cin, pass);

	staff.push_back(new Staff(name, age, wage, pass));
	cout << sign::success <<"Staff added successfully!\n";
}

/**
Removes a staff from the gym
*/
void Gym::removeStaff() 
{
	int optionStaff;
	Staff *staffToEdit;
	inputStaffIdObj(optionStaff, *this, &staffToEdit);
	
	vector<Staff *>::iterator it_staff;
	for (it_staff = staff.begin(); it_staff != staff.end(); it_staff++) {
		if ((*it_staff)->getId() == optionStaff) {
			staff.erase(it_staff);
			cout << "Staff with id " << optionStaff << " erased sucessfully!\n";
			return;
		}
	}
	cout << "Staff with id " << optionStaff << " does not exist!\n";
}

/**
Adds a personal trainer to the gym
*/
void Gym::addPersonalTrainer()
{
	int age; double wage;
	string name, pass, specializedArea;

	cout << "Insert new personal trainer's name: ";
	cin.ignore(1000, '\n');
	getline(cin, name);
	do {
		cout << "Insert new personal trainer's age: ";
		cin >> age;
		cin.ignore();
	} while (age < 0);
	cin.ignore(1000, '\n');
	cout << "Insert new pt's specialized area: ";
	getline(cin, specializedArea);
	do {
		cout << "Insert new personal trainer's wage: ";
		cin >> wage;
		cin.ignore();
	} while (wage < 0);
	cout << "Insert new pt's password: ";
	cin.ignore(1000, '\n');
	getline(cin, pass);
	
	PersonalTrainer* pt = new PersonalTrainer(name, age, wage, pass, specializedArea);
	staff.push_back(pt);
	profs.push_back(pt);
	cout << sign::success <<"Personal trainer added successfully!\n";
}

/**
Removes a personal trainer from the gym
*/
void Gym::removePersonalTrainer()
{
	int optionProf;
	Staff *profToEdit;
	inputPtIdObj(optionProf, *this, &profToEdit);
	
	vector<PersonalTrainer *>::iterator it_prof;
	for (it_prof = profs.begin(); it_prof != profs.end(); it_prof++) {
		if ((*it_prof)->getId() == optionProf) {
			profs.erase(it_prof);
			break;
		}
	}
	vector<Staff *>::iterator it_staff;
	for (it_staff = staff.begin(); it_staff != staff.end(); it_staff++) {
		if ((*it_staff)->getId() == optionProf) {
			staff.erase(it_staff);
			cout << sign::success << "Personal trainer with id " << optionProf << " erased sucessfully!\n";
			return;
		}
	}
	cout << "Personal trainer with id " << optionProf << " does not exist!\n";
}

/**
Adds a program to the gym
*/
void Gym::addProgram()
{
	int programCode, gymDays;
	float cost;
	Program *programFound = NULL;

	cout << "Insert new program's code: ";
	cin >> programCode;
	while (cin.fail() || findProgram(programCode, &programFound)) {
		if (cin.fail()) {
			cout << sign::error << "Insert a valid value! ";
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else cout << sign::error << "Insert a non-existent program! ";
		cin >> programCode;
	}
	
	cout << "Insert program number of gym days: ";
	cin >> gymDays;
	while (cin.fail() || gymDays < 0 || gymDays > 365) {
		cout << sign::error << "Insert a valid value! ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> gymDays;
	}
	
	cout << "Insert program's monthly cost: ";
	cin >> cost;
	while (cin.fail() || cost < 0) {
		cout << sign::error << "Insert a valid value! ";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> cost;
	}

	programs.push_back(new Program(programCode, gymDays, cost));
	cout << sign::success << "New program added successfully!\n";
}

/**
Removes a program from the gym
*/
void Gym::removeProgram()
{
	int optionProgram;
	Program *programToErase;
	inputProgramIdObj(optionProgram, *this, &programToErase);

	vector<Program *>::iterator it_prog;
	for (it_prog = programs.begin(); it_prog != programs.end(); it_prog++) {
		if ((*it_prog)->getCode() == optionProgram) {
			programs.erase(it_prog);
			cout << sign::success << "Program with code " << optionProgram << " erased sucessfully!\n";
			return;
		}
	}
	cout << sign::error << "Program with code " << optionProgram << " does not exist!\n";
}

/**
Deposits amount
*/
void Gym::depositAmount()
{
	cout << "What is the amount to deposit to gym's account ? ";
	double amount;
	cin >> amount;
	while (cin.fail() || amount < 0) {
		cout << "Please insert a valid amount!\n";
		cin.clear();
		cin.ignore(1000, '\n');
		cin >> amount;
	}
	Transaction newTransaction("DEPOSIT", amount);
	newTransaction.setDescription("BANK TRANSFER");

	gymFinance.addTransaction(newTransaction);
	cout << sign::success<<"Transaction performed successfully!\n\n";
}

/**
Makes payments for every staff who hasn't been paid yet
*/
void Gym::makePayments()
{
	cout << "------------ Paid workers ------------ \n";
	if (staff.size() == 0) {
		cout << "No workers to be paid!\n\n";
	}
	else {
		bool someonePaid = false, allPaid = true;
		for (auto worker : staff) {
			if (!worker->getWasPaid()) {
				Transaction payment("WITHDRAWAL", worker->getWage());
				payment.setDescription("MONTHLY PAYMENT");
				if (gymFinance.addTransaction(payment)) {
					someonePaid = true;
					worker->changeWasPaid();
					cout << "ID: " << worker->getId() << " | Name: " << worker->getName() << endl;
				}
				else allPaid = false;
			}
		}
		if (allPaid && !someonePaid) cout << "Every worker is already paid!\n";
		else if (!someonePaid) cout << "Insufficient balance to pay any salary!\n";
	}
	cout << endl;
}

//To-do falta dar overload de operator << no schedule para substituir printSchedule
std::ostream &operator<<(ostream &out, const Gym &gym)
{	out << string(gym.name.length()+2,'-')<<endl;
	out << "|" <<gym.name << "|" << endl;
	out << string(gym.name.length()+2,'-')<<endl<<endl;
	gym.displayPrograms();
	out << gym.clients.size() << " Clients" << endl<< endl;
	out << gym.staff.size() << " Staff Members" << endl<< endl;
	out << gym.profs.size() << " Professors" << endl<< endl;
	out << gym.gymSchedule << endl<<endl;
	out << "Maximum number of clients: " << gym.maxNumClients << endl<< endl;
	out << "Maximum gym capacity: " << gym.maxCapacity << endl<< endl<< endl;
	return out;
}
