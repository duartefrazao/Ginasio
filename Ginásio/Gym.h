#ifndef GYM_H_
#define GYM_H_

#include <string>
#include <vector>
#include <iostream>
#include "Client.h"
#include "Finance.h"
#include "Schedule.h"
#include "Program.h"
#include "PersonalTrainer.h"

class Client;
class Staff;
class PersonalTrainer;

class Gym {
	
	std::string name;
	std::vector<Program*> programs;
	std::vector<Client *> clients;
	std::vector<Staff *> staff;
	std::vector<PersonalTrainer *> profs;
	Schedule gymSchedule;
	int maxNumClients;
	int maxCapacity;
	Finance gymFinance;


public:
	/**
	Gym Constructor
	@param name Name of the gym
	@param programs Vector of pointers to program subscriptions
	@param clients Vector of pointers to clients of the gym
	@param staff Vector of pointers to gym's staff
	@param profs Vector of pointers to gym's profs
	@param profs Vector of pointers to gym's profs

	@param schedule Schedule of the gym
	@param maxNumClients Max number of clients subscribed to the gym
	@param maxCapacity Max number of people inside the gym
	@param gymFinance Finances of the gym
	@return
	*/
	Gym(std::string name, std::vector<Program *> &programs,
		std::vector<Client *> &clients, std::vector<Staff *> &staff,
		std::vector<PersonalTrainer *> &profs, Schedule &gymSchedule,
		int maxNumClients, int maxCapacity, Finance &gymFinance);


	Gym(std::string name, std::vector<Program *> &programs, Schedule &gymSchedule,
		int maxNumClients, int maxCapacity, Finance &gymFinance);

	/**
	Gym destructor

	@return
	*/
	~Gym();


	/**
	Get name of the gym

	@return Returns the name of the gym
	*/
	std::string getName() const;

	/**
	Returns the vector of client pointers of the gym

	@return Returns vector of pointers to clients of the gym
	*/
	std::vector<Client *> getClients() const;

	/**
	Returns the vector of staff pointers of the gym

	@return Returns vector of pointers to staff of the gym
	*/
	std::vector<Staff *> getStaff() const;

	/**
	Returns the vector of Personal Trainers pointers of the gym

	@return Returns vector of pointers to personal trainers of the gym
	*/
	std::vector<PersonalTrainer *> getPT() const;

	std::vector<Program *> getPrograms() const;

	/**
	Returns the gym schedule

	@return Returns the gym schedule
	*/
	Schedule getGymSchedule() const;


	/**
	Returns the max number of clients of the gym

	@return Returns the max number of clients of the gym
	*/
	int getMaxNumClients() const;


	/**
	Returns the number of program subscriptions the gym offers

	@return Returns the number of program subscriptions the gym offers
	*/
	int getNumberPrograms() const;

	/**
	Returns the max capacity of the gym

	@return Returns the max capacity of the gym
	*/
	int getMaxCapacity() const;

	/**
	Returns the finance of the gym

	@return Returns the finance of the gym
	*/
	Finance getGymFinance() const;

	/**
	Sets the vector of clients of the gym

	@param The vector of client pointers of the gym
	*/
	void setClients(std::vector<Client *>);

	/**
	Sets the vector of staff of the gym

	@param The vector of staff pointers of the gym
	*/
	void setStaff(std::vector<Staff *>);

	void setName(std::string newName);

	/**
	Sets the gym schedule

	@param The gym schedule
	*/
	void setGymSchedule(Schedule);

	/**
	Sets the max number of clients of the gym

	@param The max number of clients of the gym
	*/
	void setMaxNumClients(int);

	/**
	Sets the max capacity of the gym

	@param The max capacity of the gym
	*/
	void setMaxCapacity(int);

	/**
	Sets the gym finance

	@param The gym finance
	*/
	void setGymFinance(Finance);


	/**
	Adds a client to the vector

	@param Client pointer
	*/
	void addClient(Client * client);

	/**
	Adds a staff to the vector

	@param Staff pointer
	*/
	void addStaff(Staff * staff);

	/**
	Adds a program to the vector

	@param Program pointer
	*/
	void addProgram(Program* program);

	/**
	Prints the programs the gym has to offer, as well as the conditions
	*/
	void displayPrograms() const;

	/**
	Returns the gym's program subscription that has the id code

	@param	code Program subscription id code
	@return Returns the gym's program subscription that has the id code
	*/
	Program* codeToProgram(int code);

	/**
	Finds gym's staff with a certain Id
	@param
	- staffId is the staff's Id
	- staff_found is a pointer to the found staff
	@return Returns true if staff was found, false otherwise
	*/
	bool findStaff(int staffId, Staff** staff_found);

	/**
	Finds gym's client with a certain Id
	@param
	- clientId is the client's Id
	- client_found is a pointer to the found client
	@return Returns true if client was found, false otherwise
	*/
	bool findClient(int clientId, Client** client_found);

	/**
	Performs the login process for a certain staff
	*/
	void login();

	/**
	Changes gym's capacity
	*/
	void changeCapacity();

	/**
	Changes gym's max number of clients
	*/
	void changeMaxNumClients();

	/**
	Adds a client to the gym
	*/
	void addClient();

	/**
	Prints the programs the gym has to offer, as well as the conditions

	@param
	@return
	*/
	void displayProgramOptions();

	/**
	Removes a client
	*/
	void removeClient();

	/**
	Adds a staff to the gym
	*/
	void addStaff();

	/**
	Removes a staff from the gym
	*/
	void removeStaff();

	/**
	Adds a personal trainer to the gym
	*/
	void addPersonalTrainer();

	/**
	Removes a personal trainer from the gym
	*/
	void removePersonalTrainer();

	/**
	Adds a program to the gym
	*/
	void addProgram();

	/**
	Removes a program from the gym
	*/
	void removeProgram();

	/**
	Prints the gym's clients ids

	@param
	@return
	*/
	void displayClientsIds();

	/**
	Prints the gym's staff ids

	@param
	@return
	*/
	void displayStaffIds() const;

	/**
	Prints the gym's personal trainer's ids

	@param
	@return
	*/
	void displayProfsIds() const;

	/**
	Overload of operator << for class Gym
	@return ostream
	*/
	friend std::ostream & operator<<(std::ostream & out, const Gym &gym);

	/**
	Finds gym's program with a certain Id
	@param 
	programId - id of program to be searched 
	program_found - pointer to return the program found
	@return true if found, false otherwise
	*/
	bool findProgram(int programId, Program** program_found);

	/**
	Finds gym's personal trainer with a certain Id
	@param
	profId - id of personal trainer to be searched
	prof_found - pointer to return the personal trainer found
	@return true if found, false otherwise
	*/
	bool findProf(int profId, Staff** prof_found);

	/**
	Deposits amount to gym's account
	*/
	void depositAmount();

	/**
	Makes payments from the gym's account
	*/
	void makePayments();
};

#endif /* GYM_H_ */