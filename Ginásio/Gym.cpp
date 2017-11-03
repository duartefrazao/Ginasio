#include "stdafx.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Gym.h"
#include "Client.h"


using namespace std;

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

string Gym::getName() const { return name; }

vector<Client *> Gym::getClients() const {return clients;}

vector<Program *> Gym::getPrograms() const {return programs;}

int Gym::getNumberPrograms() const{return programs.size();}

vector<Staff *> Gym::getStaff() const {return staff;}

Schedule Gym::getGymSchedule() const {return gymSchedule;}

int Gym::getMaxNumClients() const {return maxNumClients;}

int Gym::getMaxCapacity() const {return maxCapacity;}

Finance Gym::getGymFinance() const {return gymFinance;}

#pragma endregion



#pragma region Sets


void Gym::setClients(vector<Client *> clients) {
	this->clients = clients;
}

void Gym::setStaff(vector<Staff *> staff) {
	this->staff = staff;
}

void Gym::setName(string newName)
{
	name = newName;
}

void Gym::setGymSchedule(Schedule gymSchedule) {
	this->gymSchedule = gymSchedule;
}

void Gym::setMaxNumClients(int maxNumClients) {
	this->maxNumClients = maxNumClients;
}

void Gym::setMaxCapacity(int maxCapacity) {
	this->maxCapacity = maxCapacity;
}

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

/**
	Performs the login process for a certain staff's id

	@param Staff's Id to be logged on
*/
void Gym::login(int staffId) {
	cout << "    Welcome to Go Gym!      \n"
		<< "--- AUTHENTICATION PORTAL ---\n";

	Staff* staff_found = NULL;
	bool staffFound = 0;
	do
	{
		string staffName;
		cout << "Login: ";
		getline(cin, staffName);

		if (findStaff(staffId, staff_found))
		{
			staffFound = 1;
			bool access = 0;
			do
			{
				string pass;
				cout << "Password: ";
				char ch = getchar(); //Now compatible with other compilers
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
					ch = getchar();
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


bool Gym::findStaff(int staffId, Staff* staff_found) {
	for (auto staff_pointer : staff)
	{
		if (staff_pointer->getId() == staffId)
		{
			staff_found = staff_pointer;
			return true;
		}
	}

	staff_found = NULL;
	return false;
}

#pragma endregion





# pragma region staffMenu
/**
Shows the menu of options for adding or removing staff

@return Returns the chosen option of the staff's menu
*/
int staffMenu() {

	string options[] = { "1. Add Staff", "2. Remove staff" };
	for (size_t i = 0; i < 3; i++) {
		cout << options[i] << endl;
	}

	/* insert function to accept option */
	int option = filterInput(1,options->size());

	return option;
}


void Gym::menuStaff() {

	int option;
	while ((option = staffMenu()) != 0) {
		switch (option) {
		case 1:
		{
			/* add staff */
			int age, wage;
			string name;
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

			staff.push_back(new Staff(age, wage));
			cout << "Staff added sucessfully!\n";
		}
		break;
		case 2:
		{
			/* remove staff by Id*/
			int id;
			cout << "Insert staff's id to remove: ";
			cin >> id;
			cin.ignore();
			vector<Staff *>::iterator it_staff;
			for (it_staff = staff.begin(); it_staff != staff.end(); it_staff++) {
				if ((*it_staff)->getId() == id) {
					staff.erase(it_staff);
					cout << "Staff with id " << id << " erased sucessfully!\n";
				}
			}
			if (it_staff == staff.end()) {
				cout << "Staff with id " << id << " does not exist!\n";
			}
		}
		break;
		default:
			cout << "Unreachable option ...\n";
		}
	}
}

#pragma endregion


void Gym::displayPrograms() const
{
	cout << name << " has the following programs to offer\n\n\n";
	for (unsigned int i = 0; i < programs.size(); i++)
	{
		programs.at(i)->displayProgram();
	}
}

Program* Gym::codeToProgram(int code){
	for (unsigned int i = 0; i < programs.size(); i++)
		if (code == programs.at(i)->getCode())
			return programs.at(i);

	return NULL;

}

void Gym::displayProgramOptions()
{
	cout << "---Programas disponiveis---" << endl;
	for (unsigned int i = 0; i < programs.size(); i++)
	{
		cout << programs.at(i);
	}
}

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
	cout << "Programa:" << endl;
	displayProgramOptions();
	program= filterInput(1, programs.size());

	//age
	cout << "Idade: ";
	cin >> age;

	//To-do arranjar maneira de em vez de usar staff ser um professor, porque pode dar errado
	PersonalTrainer *professor = profs.at(rand() % staff.size());

	Client novoCliente(name, codeToProgram(program), age, this, professor);

	clients.push_back(&novoCliente);
	cout << "Cliente adicionado com sucesso" << endl;
}

/**
Shows the menu of options for adding or removing clients

@return Returns the chosen option of the clients's menu
*/
int clientMenu() {

	string options[] = { "1. Add client", "2. Remove client" };
	for (size_t i = 0; i < 3; i++) {
		cout << options[i] << endl;
	}

	/* insert function to accept option */
	int option = filterInput(1, options->size());

	return option;
}


void Gym::menuClient() {

	int option;
	while ((option = staffMenu()) != 0) {
		switch (option) {
		case 1:
		{
			addClient();
		}
		break;
		case 2:
		{
			removeClient();
		}
		break;
		default:
			cout << "Unreachable option ...\n";
		}
	}
}


void Gym::removeClient()
{

	int id;
	cout << "Insert client's id to remove: ";
	//algo que mostre ids + fun��o que check ids
	cin >> id;
	cin.ignore();
	vector<Client *>::iterator it_client;
	for (it_client = clients.begin(); it_client != clients.end(); it_client++) {
		if ((*it_client)->getId() == id) {
			clients.erase(it_client);
			cout << "Client with id " << id << " erased sucessfully!\n";
		}
	}
	if (it_client == clients.end()) {
		cout << "Client with id " << id << " does not exist!\n";
	}
}
