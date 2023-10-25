#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <iomanip>
#include "Header.h"
using namespace std;

int IDAssigner() {
	const int MIN_ID = 100;
	const int MAX_ID = 999;
	srand(time(0));
	int id;
	bool is_id_used;
	string filename = "IDS.txt";
	ifstream file(filename);
	if (!file) {
		 cerr << "Could not open file: " << filename << '\n';
		return -1;
	}

	do {
		id = rand() % (MAX_ID - MIN_ID + 1) + MIN_ID; // generate random 3 digit integer ID
		is_id_used = false;

		int stored_id;
		while (file >> stored_id) {
			if (stored_id == id) {
				is_id_used = true; // ID is already used
				break;
			}
		}

		file.clear(); // clear error flags
		file.seekg(0,  ios::beg); // rewind file to beginning
	} while (is_id_used); // check if ID is already used

	 ofstream outfile(filename,  ios::app);
	if (!outfile) {
		 cerr << "Could not open file: " << filename << '\n';
		return -1;
	}

	outfile << id << '\n';
	 cout << "Generated and ID " << id << " Assigned " << '\n';

	return id;
}

int DataCalculate(string filename) {
	ifstream file(filename);
	if (!file) {
		 cerr << "Could not open file: " << filename << '\n';
		return -1;
	}

	int count = 0;
	string line;
	while ( getline(file, line)) {
		++count;
	}

	return count;
}

//funtions for Login Class

void Login::readUsersFromFile() {
	ifstream fin("users.txt");
	if (fin) {
		LoginAttributes user;
		while (fin >> user.username >> user.password) {
			if (numUsers == maxUsers) {
				// If the array is full, allocate a larger one
				maxUsers *= 2;
				LoginAttributes* newUsers = new LoginAttributes[maxUsers];
				for (int i = 0; i < numUsers; i++) {
					newUsers[i] = users[i];
				}
				delete[] users;
				users = newUsers;
			}
			users[numUsers++] = user;
		}
	}
}
Login::Login() {
	users = new LoginAttributes[10];
	numUsers = 0;
	maxUsers = 10;
	readUsersFromFile();
}
Login::~Login() {
	delete[] users;
}
void Login:: registerUser() {
	cout << "Enter username: ";
	string username;
	cin >> username;
	cout << "Enter password: ";
	string password;
	cin >> password;
	LoginAttributes user = { username, password };
	if (numUsers == maxUsers) {
		// If the array is full, allocate a larger one
		maxUsers *= 2;
		LoginAttributes* newUsers = new LoginAttributes[maxUsers];
		for (int i = 0; i < numUsers; i++) {
			newUsers[i] = users[i];
		}
		delete[] users;
		users = newUsers;
	}
	users[numUsers++] = user;
	ofstream fout("users.txt", ios::app);
	fout << username << " " << password << endl;
	cout << "User registered successfully!" << endl;
}

bool Login::login() {
	cout << "Enter username: ";
	string username;
	cin >> username;
	cout << "Enter password: ";
	string password;
	cin >> password;
	for (int i = 0; i < numUsers; i++) {
		if (users[i].username == username && users[i].password == password) {
			return true;
		}
	}
	return false;
}

//function definition for User Class

void User::set()
{
	cout << "Enter Name = ";
	cin >> name;
	cout << "Enter Email = ";
	cin >> email;
	cout << "Enter Phone = ";
	cin >> phone;
	cout << "Enter Gender = ";
	cin >> gender;
	cout << "Enter Date Of Birth = ";
	cin >> dateOfBirth;
}
void User::get()
{
	cout << "\nName : " << name;
	cout << "\nEmail : " << email;
	cout << "\nPhone : " << phone;
	cout << "\nGender : " << gender;
	cout << "\nDate Of Birth : " << dateOfBirth;
}

//Functions Definition for Trainer Class

istream& operator >>(istream& in, Trainer& obj)
{
	obj.set();
	int temp_shift;
	obj.trainerID=IDAssigner();
	cout << "Enter Specialization = ";
	cin >> obj.specialization;
	cout << "\n1.Morning Shift";
	cout << "\n2.Afternoon Shift";
	cout << "\n3.Evening Shift";
	cout << "\nEnter Shift = ";
	cin >> temp_shift;
	while (temp_shift == 1 && temp_shift == 2 && temp_shift == 3)
	{
		cout << "\nWrong Input Try Again!";
		cout << "\nEnter Shift = ";
		cin >> temp_shift;
	}
	obj.shift = (temp_shift == 0) ? "Morning" : ((temp_shift == 1) ? "Noon" : "Evening");
	cout << "\nEnter Salary = ";
	cin >> obj.salary;
	return in;
}
void Trainer::addUser()
{
	fstream fout;
	fout.open("Trainers.txt", ios::app);
	if (!fout)
	{
		cout << "\nFile not created!";
	}
	else
	{
		cout << "\nData Entered";
		fout << name << " " << email << " " << phone << " " << gender << " " << dateOfBirth << " ";
		fout << trainerID << " " << specialization << " " << shift << " " << salary << endl;
		fout.close();
	}
}
void Trainer::viewUser()
{
	fstream fin;
	fin.open("Trainers.txt");
	fin.seekg(0);
	string nam;
	string em;
	string ph;
	string gen;
	string dob;
	int tID;
	string spec;
	string shft;
	double sal;
	if (!(fin.is_open()))
	{
		cout << "\nNo such File Exists!";
	}
	else
	{
		int count = 0;
		cout << endl;
		cout << "Name\t\tEmail\t\tPhone\tGender\tDateofBirth\tTrainerID\tSpecialization\tShift\t\tSalary" << endl;
		while (!fin.eof() && count < DataCalculate("Trainers.txt"))
		{
			++count;
			fin >> nam >> em >> ph >> gen >> dob >> tID >> spec >> shft >> sal;
			cout << nam << "\t\t" << em << "\t" << ph << "\t" << gen << "\t" << dob << "\t" << tID << "\t\t" << spec << "\t\t" << shft << "\t\t" << sal << endl;
		}
		fin.close();
	}
}

int Trainer::searchTrainer(int query)
{
	fstream fin;
	fin.open("Trainers.txt");
	fin.seekg(0);
	string nam;
	string em;
	string ph;
	string gen;
	string dob;
	int tID;
	string spec;
	string shft;
	double sal;
	int loc = -1;
	if (!(fin.is_open()))
	{
		cout << "\nNo such File Exists!";
	}
	else
	{
		int count = 0;
		cout << endl;
		cout << "Name\t\tEmail\t\tPhone\tGender\tDateofBirth\tTrainerID\tSpecialization\tShift\t\tSalary" << endl;
		while (!fin.eof() && count < DataCalculate("Trainers.txt"))
		{
			++count;
			fin >> nam >> em >> ph >> gen >> dob >> tID >> spec >> shft >> sal;
			if (tID == query)
			{
				loc = count;
				cout << nam << "\t\t" << em << "\t" << ph << "\t" << gen << "\t" << dob << "\t" << tID << "\t\t" << spec << "\t\t" << shft << "\t\t" << sal << endl;
			}
		}
		fin.close();
	}
	return loc;
}

void Trainer::updateTrainer(int query)
{
	fstream fin, fout;
	int pos = searchTrainer(query);
	cout << "\n----------------------------------------";
	if (pos == -1)
	{
		cout << "\nNo Record Found Against this Query!";
		exit(0);
	}
	fin.open("Trainers.txt");
	fout.open("temp.txt",ios::app);
	fin.seekg(0);
	string nam;
	string em;
	string ph;
	string gen;
	string dob;
	int tID;
	string spec;
	string shft;
	double sal;
	int loc;
	if (!(fin.is_open()))
	{
		cout << "\nNo such File Exists!";
	}
	else
	{
		int count = 0;
		cout << endl;
		while (!fin.eof() && count < DataCalculate("Trainers.txt"))
		{
			++count;
			if (!fout)
			{
				cout << "\nError While Updating Data!";
			}
			else
			{
				fin >> nam >> em >> ph >> gen >> dob >> tID >> spec >> shft >> sal;
				if (count == pos)
				{
					cout << "\nEnter Updated Data!\n";
					cout << "Enter Name = ";
					cin >> nam;
					cout << "Enter Email = ";
					cin >> em;
					cout << "Enter Phone = ";
					cin >> ph;
					cout << "Enter Gender = ";
					cin >> gen;
					cout << "Enter Date Of Birth = ";
					cin >> dob;
					int temp_shift;
					cout << "Enter Specialization = ";
					cin >> spec;
					cout << "\n1.Morning Shift";
					cout << "\n2.Afternoon Shift";
					cout << "\n3.Evening Shift";
					cout << "\nEnter Shift = ";
					cin >> temp_shift;
					while (temp_shift == 1 && temp_shift == 2 && temp_shift == 3)
					{
						cout << "\nWrong Input Try Again!";
						cout << "\nEnter Shift = ";
						cin >> temp_shift;
					}
					shft = (temp_shift == 0) ? "Morning" : ((temp_shift == 1) ? "Noon" : "Evening");
					cout << "\nEnter Salary = ";
					cin >> sal;
					cout << "\nDATA UPDATED!\n";
				}
				fout << nam << " " << em << " " << ph << " " << gen << " " << dob << " ";
				fout << tID << " " << spec << " " << shft << " " << sal << endl;
			}
		}
		fin.close();
		fout.close();
		remove("Trainers.txt");
		rename("temp.txt", "Trainers.txt");
	}

	
	
}

void Trainer::removeTrainer(int query)
{
	fstream fin, fout;
	int pos = searchTrainer(query);
	cout << "\n----------------------------------------";
	if (pos == -1)
	{
		cout << "\nNo Record Found Against this Query!";
		exit(0);
	}
	fin.open("Trainers.txt");
	fout.open("temp.txt", ios::app);
	fin.seekg(0);
	string nam;
	string em;
	string ph;
	string gen;
	string dob;
	int tID;
	string spec;
	string shft;
	double sal;
	int loc;
	if (!(fin.is_open()))
	{
		cout << "\nNo such File Exists!";
	}
	else
	{
		int count = 0;
		cout << endl;
		while (!fin.eof() && count < DataCalculate("Trainers.txt"))
		{
			++count;
			if (!fout)
			{
				cout << "\nError While Removing Data!";
			}
			else
			{
				char choice;
				fin >> nam >> em >> ph >> gen >> dob >> tID >> spec >> shft >> sal;
				if (count == pos)
				{
					cout << "\nAre you sure you want to delete above data\n";
					do {
						cout << "Enter Y/N: ";
						cin >> choice;
						switch (choice) {
						case 'Y':
							cout << "\nDATA REMOVED!";
							break;
						case 'y':
							cout << "\nDATA REMOVED!";
							break;
						case 'N':
							fout << nam << " " << em << " " << ph << " " << gen << " " << dob << " ";
							fout << tID << " " << spec << " " << shft << " " << sal << endl;
							break;
						case 'n':
							fout << nam << " " << em << " " << ph << " " << gen << " " << dob << " ";
							fout << tID << " " << spec << " " << shft << " " << sal << endl;
							break;
						default:
							cout << "Invalid choice!" << endl;
							this_thread::sleep_for(chrono::seconds());
							break;
						}
					} while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');
				}
				else
				{
					fout << nam << " " << em << " " << ph << " " << gen << " " << dob << " ";
					fout << tID << " " << spec << " " << shft << " " << sal << endl;
				}
			}
		}
		fin.close();
		fout.close();
		remove("Trainers.txt");
		rename("temp.txt", "Trainers.txt");
	}
}

//Functions Definition for WorkoutPackage Class

istream& operator >>(istream& in, WorkoutPackage& obj)
{
	obj.packageID=IDAssigner();
	cout << "Enter Title = ";
	cin >> obj.title;
	cout << "Enter Package Description = ";
	cin >> obj.description;
	cout << "Enter Price = ";
	cin >> obj.price;
	cout << "Enter Duration = ";
	cin >> obj.duration;
	return in;
}
void WorkoutPackage::addPackage()
{
	fstream fout;
	fout.open("Packages.txt", ios::app);
	if (!fout)
	{
		cout << "\nFile not created!";
	}
	else
	{
		cout << "\nData Entered";
		fout << packageID << " " << title << " " << description << " " << price << " " << duration << endl;
		fout.close();
	}
}
void WorkoutPackage::viewPackage()
{
	fstream fin;
	fin.open("Packages.txt");
	fin.seekg(0);
	int pID;
	string tit;
	string desc;
	double prc;
	string dur;
	if (!(fin.is_open()))
	{
		cout << "\nNo such File Exists!";
	}
	else
	{
		int count = 0;
		while (!fin.eof() && count < DataCalculate("Packages.txt"))
		{
			++count;
			fin >> pID >> tit >> desc >> prc >> dur;
			cout << "PackageID : " << pID << endl;
			cout << "Title : " << tit << endl;
			cout << "Description : " << desc << endl;
			cout << "Price : " << prc << endl;
			cout << "Duration : " << dur << endl;
			cout << "-----------------------------------------------------------------" << endl;
		}
		fin.close();
	}
}

int WorkoutPackage::searchPackage(int query)
{
	fstream fin;
	fin.open("Packages.txt");
	fin.seekg(0);
	int pID;
	string tit;
	string desc;
	double prc;
	string dur;
	int loc = -1;
	if (!(fin.is_open()))
	{
		cout << "\nNo such File Exists!";
	}
	else
	{
		int count = 0;
		cout << endl;
		while (!fin.eof() && count < DataCalculate("Packages.txt"))
		{
			++count;
			fin >> pID >> tit >> desc >> prc >> dur;
			if (pID == query)
			{
				loc = count;
				cout << "PackageID : " << pID << endl;
				cout << "Title : " << tit << endl;
				cout << "Description : " << desc << endl;
				cout << "Price : " << prc << endl;
				cout << "Duration : " << dur << endl;
				cout << "-----------------------------------------------------------------" << endl;
			}
		}
		fin.close();
	}
	return loc;
}

void WorkoutPackage::updatePackage(int query)
{
	fstream fin, fout;
	int pos = searchPackage(query);
	cout << "\n----------------------------------------";
	if (pos == -1)
	{
		cout << "\nNo Record Found Against this Query!";
		exit(0);
	}
	fin.open("Packages.txt");
	fout.open("temp.txt", ios::app);
	fin.seekg(0);
	int pID;
	string tit;
	string desc;
	double prc;
	string dur;
	int loc;
	if (!(fin.is_open()))
	{
		cout << "\nNo such File Exists!";
	}
	else
	{
		int count = 0;
		cout << endl;
		while (!fin.eof() && count < DataCalculate("Packages.txt"))
		{
			++count;
			if (!fout)
			{
				cout << "\nError While Updating Data!";
			}
			else
			{
				fin >> pID >> tit >> desc >> prc >> dur;
				if (count == pos)
				{
					cout << "\nEnter Updated Data!\n";
					cout << "Enter Title = ";
					cin >> tit;
					cout << "Enter Description = ";
					cin >> desc;
					cout << "Enter Price = ";
					cin >> prc;
					cout << "Enter Duration = ";
					cin >> dur;
					cout << "\nDATA UPDATED!\n";
				}
				fout << pID << " " << tit << " " << desc << " " << prc << " " << dur << endl;
			}
		}
		fin.close();
		fout.close();
		remove("Packages.txt");
		rename("temp.txt", "Packages.txt");
	}



}

void WorkoutPackage::removePackage(int query)
{
	fstream fin, fout;
	int pos = searchPackage(query);
	cout << "\n----------------------------------------";
	if (pos == -1)
	{
		cout << "\nNo Record Found Against this Query!";
		exit(0);
	}
	fin.open("Packages.txt");
	fout.open("temp.txt", ios::app);
	fin.seekg(0);
	int pID;
	string tit;
	string desc;
	double prc;
	string dur;
	int loc;
	if (!(fin.is_open()))
	{
		cout << "\nNo such File Exists!";
	}
	else
	{
		int count = 0;
		cout << endl;
		while (!fin.eof() && count < DataCalculate("Packages.txt"))
		{
			++count;
			if (!fout)
			{
				cout << "\nError While Removing Data!";
			}
			else
			{
				char choice;
				fin >> pID >> tit >> desc >> prc >> dur;
				if (count == pos)
				{
					cout << "\nAre you sure you want to delete above data\n";
					do {
						cout << "Enter Y/N: ";
						cin >> choice;
						switch (choice) {
						case 'Y':
							cout << "\nDATA REMOVED!";
							break;
						case 'y':
							cout << "\nDATA REMOVED!";
							break;
						case 'N':
							fout << pID << " " << tit << " " << desc << " " << prc << " " << dur << endl;
							break;
						case 'n':
							fout << pID << " " << tit << " " << desc << " " << prc << " " << dur << endl;
							break;
						default:
							cout << "Invalid choice!" << endl;
							this_thread::sleep_for(chrono::seconds());
							break;
						}
					} while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');
				}
				else
				{
					fout << pID << " " << tit << " " << desc << " " << prc << " " << dur << endl;
				}
			}
		}
		fin.close();
		fout.close();
		remove("Packages.txt");
		rename("temp.txt", "Packages.txt");
	}
}

//funcion definitions for Member class

istream& operator >>(istream& in, Member& obj)
{
	obj.set();
	obj.membershipID = IDAssigner();
	cout << "Enter Starting Date = ";
	cin >> obj.startDate;
	cout << "Enter Ending Date = ";
	cin >> obj.endDate;
	cout << "Enter MemberShip Status = ";
	cin >> obj.membershipStatus;
	cout << "Enter Amount = ";
	cin >> obj.amount;
	cout << "Enter Payement Method = ";
	cin >> obj.paymentMethod;
	return in;
}
void Member::addUser()
{
	fstream fout;
	fout.open("Members.txt", ios::app);
	if (!fout)
	{
		cout << "\nFile not created!";
	}
	else
	{
		cout << "\nData Entered";
		fout << name << " " << email << " " << phone << " " << gender << " " << dateOfBirth << " ";
		fout << membershipID << " " << startDate << " " << endDate << " " << membershipStatus << " " << amount << " " << paymentMethod << endl;
		fout.close();
	}
}
void Member::viewUser()
{
	fstream fin;
	fin.open("Members.txt");
	fin.seekg(0);
	string nam;
	string em;
	string ph;
	string gen;
	string dob;
	int mID;
	string sDate;
	string eDate;
	bool mStatus;
	int pID;
	int tID;
	double amt;
	string pM;
	if (!(fin.is_open()))
	{
		cout << "\nNo such File Exists!";
	}
	else
	{
		int count = 0;
		cout << endl;
		cout << "Name\t\tEmail\t\tPhone\tGender\tDateofBirth\tMemberID\tStartDate\t\tEndDate\t\tStatus\tAmount\tPayementMethod" << endl;
		while (!fin.eof() && count < DataCalculate("Members.txt"))
		{
			++count;
			fin >> nam >> em >> ph >> gen >> dob >> mID >> sDate >> eDate >> mStatus >> amt >> pM;
			cout << nam << "\t\t" << em << "\t" << ph << "\t" << gen << "\t" << dob << "\t" << mID << "\t\t" << sDate << "\t\t" << eDate << "\t" << mStatus << "\t\t" << amt << "\t" << pM << endl;
		}
		fin.close();
	}
}


int Member::searchMember(int query)
{
	fstream fin;
	fin.open("Members.txt");
	fin.seekg(0);
	string nam;
	string em;
	string ph;
	string gen;
	string dob;
	int mID;
	string sDate;
	string eDate;
	bool mStatus;
	int pID;
	int tID;
	double amt;
	string pM;
	int loc = -1;
	if (!(fin.is_open()))
	{
		cout << "\nNo such File Exists!";
	}
	else
	{
		int count = 0;
		cout << endl;
		cout << "Name\t\tEmail\t\tPhone\tGender\tDateofBirth\tMemberID\tStartDate\t\tEndDate\t\tStatus\tAmount\tPayementMethod" << endl;
		while (!fin.eof() && count < DataCalculate("Members.txt"))
		{
			++count;
			fin >> nam >> em >> ph >> gen >> dob >> mID >> sDate >> eDate >> mStatus >> amt >> pM;
			if (mID == query)
			{
				loc = count;
				cout << nam << "\t\t" << em << "\t" << ph << "\t" << gen << "\t" << dob << "\t" << mID << "\t\t" << sDate << "\t\t" << eDate << "\t" << mStatus << "\t\t" << amt << "\t" << pM << endl;
			}
		}
		fin.close();
	}
	return loc;
}

void Member::updateMember(int query)
{
	fstream fin, fout;
	int pos = searchMember(query);
	cout << "\n----------------------------------------";
	if (pos == -1)
	{
		cout << "\nNo Record Found Against this Query!";
		exit(0);
	}
	fin.open("Members.txt");
	fout.open("temp.txt", ios::app);
	fin.seekg(0);
	string nam;
	string em;
	string ph;
	string gen;
	string dob;
	int mID;
	string sDate;
	string eDate;
	bool mStatus;
	int pID;
	int tID;
	double amt;
	string pM;
	int loc;
	if (!(fin.is_open()))
	{
		cout << "\nNo such File Exists!";
	}
	else
	{
		int count = 0;
		cout << endl;
		while (!fin.eof() && count < DataCalculate("Members.txt"))
		{
			++count;
			if (!fout)
			{
				cout << "\nError While Updating Data!";
			}
			else
			{
				fin >> nam >> em >> ph >> gen >> dob >> mID >> sDate >> eDate >> mStatus >> amt >> pM;
				if (count == pos)
				{
					cout << "\nEnter Updated Data!\n";
					cout << "Enter Name = ";
					cin >> nam;
					cout << "Enter Email = ";
					cin >> em;
					cout << "Enter Phone = ";
					cin >> ph;
					cout << "Enter Gender = ";
					cin >> gen;
					cout << "Enter Date Of Birth = ";
					cin >> dob;
					cout << "Enter Start Date = ";
					cin >> sDate;
					cout << "Enter End Date = ";
					cin >> sDate;
					cout << "Enter Status = ";
					cin >> mStatus;
					cout << "Enter Amount = ";
					cin >> amt;
					cout << "Enter Payement Method = ";
					cin >> pM;
					cout << "\nDATA UPDATED!\n";
				}
				fout << nam << " " << em << " " << ph << " " << gen << " " << dob << " ";
				fout << mID << " " << sDate << " " << eDate << " " << mStatus << " " << amt << " " << pM << endl;
			}
		}
		fin.close();
		fout.close();
		remove("Members.txt");
		rename("temp.txt", "Members.txt");
	}



}

void Member::removeMember(int query)
{
	fstream fin, fout;
	int pos = searchMember(query);
	cout << "\n----------------------------------------";
	if (pos == -1)
	{
		cout << "\nNo Record Found Against this Query!";
		exit(0);
	}
	fin.open("Members.txt");
	fout.open("temp.txt", ios::app);
	fin.seekg(0);
	string nam;
	string em;
	string ph;
	string gen;
	string dob;
	int mID;
	string sDate;
	string eDate;
	bool mStatus;
	int pID;
	int tID;
	double amt;
	string pM;
	int loc;
	if (!(fin.is_open()))
	{
		cout << "\nNo such File Exists!";
	}
	else
	{
		int count = 0;
		cout << endl;
		while (!fin.eof() && count < DataCalculate("Members.txt"))
		{
			++count;
			if (!fout)
			{
				cout << "\nError While Removing Data!";
			}
			else
			{
				char choice;
				fin >> nam >> em >> ph >> gen >> dob >> mID >> sDate >> eDate >> mStatus >> amt >> pM;
				if (count == pos)
				{
					cout << "\nAre you sure you want to delete above data\n";
					do {
						cout << "Enter Y/N: ";
						cin >> choice;
						switch (choice) {
						case 'Y':
							cout << "\nDATA REMOVED!";
							break;
						case 'y':
							cout << "\nDATA REMOVED!";
							break;
						case 'N':
							fout << nam << " " << em << " " << ph << " " << gen << " " << dob << " ";
							fout << mID << " " << sDate << " " << eDate << " " << mStatus << " " << amt << " " << pM << endl;
							break;
						case 'n':
							fout << nam << " " << em << " " << ph << " " << gen << " " << dob << " ";
							fout << mID << " " << sDate << " " << eDate << " " << mStatus << " " << amt << " " << pM << endl; 
							break;
						default:
							cout << "Invalid choice!" << endl;
							this_thread::sleep_for(chrono::seconds());
							break;
						}
					} while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');
				}
				else
				{
					fout << nam << " " << em << " " << ph << " " << gen << " " << dob << " ";
					fout << mID << " " << sDate << " " << eDate << " " << mStatus << " " << amt << " " << pM << endl;
				}
			}
		}
		fin.close();
		fout.close();
		remove("Members.txt");
		rename("temp.txt", "Members.txt");
	}
}

//Functions Definition for Staff Class

istream& operator >>(istream& in, Staff& obj)
{
	obj.set();
	obj.staffID = IDAssigner();
	cout << "Enter Hire Date = ";
	cin >> obj.hireDate;
	cout << "Enter Job Title = ";
	cin >> obj.jobtitle;
	cout << "Enter Salary = ";
	cin >> obj.salary;
	return in;
}
void Staff::addUser()
{
	fstream fout;
	fout.open("Staffs.txt", ios::app);
	if (!fout)
	{
		cout << "\nFile not created!";
	}
	else
	{
		cout << "\nData Entered";
		fout << name << " " << email << " " << phone << " " << gender << " " << dateOfBirth << " ";
		fout << staffID << " " << hireDate << " " << jobtitle << " " << salary << endl;
		fout.close();
	}
}
void Staff::viewUser()
{
	fstream fin;
	fin.open("Staffs.txt");
	fin.seekg(0);
	string nam;
	string em;
	string ph;
	string gen;
	string dob;
	int sID;
	string hDate;
	string jobT;
	double sal;
	if (!(fin.is_open()))
	{
		cout << "\nNo such File Exists!";
	}
	else
	{
		int count = 0;
		cout << endl;
		cout << "Name\t\tEmail\t\tPhone\tGender\tDateofBirth\tStaffID\t\tHireDate\tJobTitle\tSalary"<< endl;
		while (!fin.eof() && count < DataCalculate("Staffs.txt"))
		{
			++count;
			fin >> nam >> em >> ph >> gen >> dob >> sID >> hDate >> jobT >> sal;
			cout << nam << "\t\t" << em << "\t" << ph << "\t" << gen << "\t" << dob << "\t" << sID << "\t\t" << hDate << "\t" << jobT << "\t" << sal << endl;
		}
		fin.close();
	}
}


int Staff::searchStaff(int query)
{
	fstream fin;
	fin.open("Staffs.txt");
	fin.seekg(0);
	string nam;
	string em;
	string ph;
	string gen;
	string dob;
	int sID;
	string hDate;
	string jobT;
	double sal;
	int loc = -1;
	if (!(fin.is_open()))
	{
		cout << "\nNo such File Exists!";
	}
	else
	{
		int count = 0;
		cout << endl;
		cout << "Name\t\tEmail\t\tPhone\tGender\tDateofBirth\tStaffID\t\tHireDate\tJobTitle\tSalary" << endl;
		while (!fin.eof() && count < DataCalculate("Staffs.txt"))
		{
			++count;
			fin >> nam >> em >> ph >> gen >> dob >> sID >> hDate >> jobT >> sal;
			if (sID == query)
			{
				loc = count;
				cout << nam << "\t\t" << em << "\t" << ph << "\t" << gen << "\t" << dob << "\t" << sID << "\t\t" << hDate << "\t" << jobT << "\t" << sal << endl;
			}
		}
		fin.close();
	}
	return loc;
}

void Staff::updateStaff(int query)
{
	fstream fin, fout;
	int pos = searchStaff(query);
	cout << "\n----------------------------------------";
	if (pos == -1)
	{
		cout << "\nNo Record Found Against this Query!";
		exit(0);
	}
	fin.open("Staffs.txt");
	fout.open("temp.txt", ios::app);
	fin.seekg(0);
	string nam;
	string em;
	string ph;
	string gen;
	string dob;
	int sID;
	string hDate;
	string jobT;
	double sal;
	int loc;
	if (!(fin.is_open()))
	{
		cout << "\nNo such File Exists!";
	}
	else
	{
		int count = 0;
		cout << endl;
		while (!fin.eof() && count < DataCalculate("Staffs.txt"))
		{
			++count;
			if (!fout)
			{
				cout << "\nError While Updating Data!";
			}
			else
			{
				fin >> nam >> em >> ph >> gen >> dob >> sID >> hDate >> jobT >> sal;
				if (count == pos)
				{
					cout << "\nEnter Updated Data!\n";
					cout << "Enter Name = ";
					cin >> nam;
					cout << "Enter Email = ";
					cin >> em;
					cout << "Enter Phone = ";
					cin >> ph;
					cout << "Enter Gender = ";
					cin >> gen;
					cout << "Enter Date Of Birth = ";
					cin >> dob;
					cout << "Enter Hiring Date = ";
					cin >> hDate;
					cout << "Enter Job Title = ";
					cin >> jobT;
					cout << "\nEnter Salary = ";
					cin >> sal;
					cout << "\nDATA UPDATED!\n";
				}
				fout << nam << " " << em << " " << ph << " " << gen << " " << dob << " ";
				fout << sID << " " << hDate << " " << jobT << " " << sal << endl;
			}
		}
		fin.close();
		fout.close();
		remove("Staffs.txt");
		rename("temp.txt", "Staffs.txt");
	}



}

void Staff::removeStaff(int query)
{
	fstream fin, fout;
	int pos = searchStaff(query);
	cout << "\n----------------------------------------";
	if (pos == -1)
	{
		cout << "\nNo Record Found Against this Query!";
		exit(0);
	}
	fin.open("Staff.txt");
	fout.open("temp.txt", ios::app);
	fin.seekg(0);
	string nam;
	string em;
	string ph;
	string gen;
	string dob;
	int sID;
	string hDate;
	string jobT;
	double sal;
	int loc;
	if (!(fin.is_open()))
	{
		cout << "\nNo such File Exists!";
	}
	else
	{
		int count = 0;
		cout << endl;
		while (!fin.eof() && count < DataCalculate("Staff.txt"))
		{
			++count;
			if (!fout)
			{
				cout << "\nError While Removing Data!";
			}
			else
			{
				char choice;
				fin >> nam >> em >> ph >> gen >> dob >> sID >> hDate >> jobT >> sal;
				if (count == pos)
				{
					cout << "\nAre you sure you want to delete above data\n";
					do {
						cout << "Enter Y/N: ";
						cin >> choice;
						switch (choice) {
						case 'Y':
							cout << "\nDATA REMOVED!";
							break;
						case 'y':
							cout << "\nDATA REMOVED!";
							break;
						case 'N':
							fout << nam << " " << em << " " << ph << " " << gen << " " << dob << " ";
							fout << sID << " " << hDate << " " << jobT << " " << sal << endl;
							break;
						case 'n':
							fout << nam << " " << em << " " << ph << " " << gen << " " << dob << " ";
							fout << sID << " " << hDate << " " << jobT << " " << sal << endl;
							break;
						default:
							cout << "Invalid choice!" << endl;
							this_thread::sleep_for(chrono::seconds());
							break;
						}
					} while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');
				}
				else
				{
					fout << nam << " " << em << " " << ph << " " << gen << " " << dob << " ";
					fout << sID << " " << hDate << " " << jobT << " " << sal << endl;
				}
			}
		}
		fin.close();
		fout.close();
		remove("Staffs.txt");
		rename("temp.txt", "Staffs.txt");
	}
}

//Functions Definition for Equipment Class

istream& operator >>(istream& in, Equipment& obj)
{
	obj.equipmentID = IDAssigner();
	cout << "Enter Name = ";
	cin >> obj.name;
	cout << "Enter Equipment Type = ";
	cin >> obj.type;
	cout << "Enter Quantity = ";
	cin >> obj.quantity;
	cout << "Enter PurchaseDate = ";
	cin >> obj.purchaseDate;
	cout << "Enter PurchasePrice = ";
	cin >> obj.purchasePrice;
	return in;
}
void Equipment::addEquipment()
{
	fstream fout;
	fout.open("Equipments.txt", ios::app);
	if (!fout)
	{
		cout << "\nFile not created!";
	}
	else
	{
		cout << "\nData Entered";
		fout << equipmentID << " " << name << " " << type << " " << quantity << " " << purchaseDate << " " << purchasePrice << endl;
		fout.close();
	}
}
void Equipment::viewEquipment()
{
	fstream fin;
	fin.open("Equipments.txt");
	fin.seekg(0);
	int eID;
	string nam;
	string typ;
	int qty;
	string purDate;
	double purPrice;
	if (!(fin.is_open()))
	{
		cout << "\nNo such File Exists!";
	}
	else
	{
		int count = 0;
		cout << endl;
		cout << "EquipmentID\tName\t\tType\t\tQuantity\tPurchaseDate\tPrice" << endl;
		while (!fin.eof() && count < DataCalculate("Equipments.txt"))
		{
			++count;
			fin >> eID >> nam >> typ >> qty >> purDate >> purPrice;
			cout << eID << "\t\t" << nam << "\t" << typ << "\t\t" << qty << "\t\t" << purDate << "\t" << purPrice << endl;
		}
		fin.close();
	}
}


int Equipment::searchEquipment(int query)
{
	fstream fin;
	fin.open("Equipments.txt");
	fin.seekg(0);
	int eID;
	string nam;
	string typ;
	int qty;
	string purDate;
	double purPrice;
	int loc = -1;
	if (!(fin.is_open()))
	{
		cout << "\nNo such File Exists!";
	}
	else
	{
		int count = 0;
		cout << endl;
		cout << "EquipmentID\tName\t\tType\t\tQuantity\tPurchaseDate\tPrice" << endl;
		while (!fin.eof() && count < DataCalculate("Trainers.txt"))
		{
			++count;
			fin >> eID >> nam >> typ >> qty >> purDate >> purPrice;
			if (eID == query)
			{
				loc = count;
				cout << eID << "\t\t" << nam << "\t" << typ << "\t\t" << qty << "\t\t" << purDate << "\t" << purPrice << endl;
			}
		}
		fin.close();
	}
	return loc;
}

void Equipment::updateEquipment(int query)
{
	fstream fin, fout;
	int pos = searchEquipment(query);
	cout << "\n----------------------------------------";
	if (pos == -1)
	{
		cout << "\nNo Record Found Against this Query!";
		exit(0);
	}
	fin.open("Equipments.txt");
	fout.open("temp.txt", ios::app);
	fin.seekg(0);
	int eID;
	string nam;
	string typ;
	int qty;
	string purDate;
	double purPrice;
	int loc;
	if (!(fin.is_open()))
	{
		cout << "\nNo such File Exists!";
	}
	else
	{
		int count = 0;
		cout << endl;
		while (!fin.eof() && count < DataCalculate("Equipments.txt"))
		{
			++count;
			if (!fout)
			{
				cout << "\nError While Updating Data!";
			}
			else
			{
				fin >> eID >> nam >> typ >> qty >> purDate >> purPrice;
				if (count == pos)
				{
					cout << "\nEnter Updated Data!\n";
					cout << "Enter Name = ";
					cin >> nam;
					cout << "Enter Type = ";
					cin >> typ;
					cout << "Enter Quantity = ";
					cin >> qty;
					cout << "Enter PurchaseDate = ";
					cin >> purDate;
					cout << "Enter PurchasePrice = ";
					cin >> purPrice;
					cout << "\nDATA UPDATED!\n";
				}
				fout << eID << " " << nam << " " << typ << " " << qty << " " << purDate << " " << purPrice << endl;

			}
		}
		fin.close();
		fout.close();
		remove("Equipments.txt");
		rename("temp.txt", "Equipments.txt");
	}



}

void Equipment::removeEquipment(int query)
{
	fstream fin, fout;
	int pos = searchEquipment(query);
	cout << "\n----------------------------------------";
	if (pos == -1)
	{
		cout << "\nNo Record Found Against this Query!";
		exit(0);
	}
	fin.open("Equipments.txt");
	fout.open("temp.txt", ios::app);
	fin.seekg(0);
	int eID;
	string nam;
	string typ;
	int qty;
	string purDate;
	double purPrice;
	int loc;
	if (!(fin.is_open()))
	{
		cout << "\nNo such File Exists!";
	}
	else
	{
		int count = 0;
		cout << endl;
		while (!fin.eof() && count < DataCalculate("Equipments.txt"))
		{
			++count;
			if (!fout)
			{
				cout << "\nError While Removing Data!";
			}
			else
			{
				char choice;
				fin >> eID >> nam >> typ >> qty >> purDate >> purPrice;
				if (count == pos)
				{
					cout << "\nAre you sure you want to delete above data\n";
					do {
						cout << "Enter Y/N: ";
						cin >> choice;
						switch (choice) {
						case 'Y':
							cout << "\nDATA REMOVED!";
							break;
						case 'y':
							cout << "\nDATA REMOVED!";
							break;
						case 'N':
							fout << eID << " " << nam << " " << typ << " " << qty << " " << purDate << " " << purPrice << endl;
							break;
						case 'n':
							fout << eID << " " << nam << " " << typ << " " << qty << " " << purDate << " " << purPrice << endl;
							break;
						default:
							cout << "Invalid choice!" << endl;
							this_thread::sleep_for(chrono::seconds());
							break;
						}
					} while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');
				}
				else
				{
					fout << eID << " " << nam << " " << typ << " " << qty << " " << purDate << " " << purPrice << endl;
				}
			}
		}
		fin.close();
		fout.close();
		remove("Equipments.txt");
		rename("temp.txt", "Equipments.txt");
	}
}

//functions Definition of Attendance Class

istream& operator >>(istream& in, Attendance& obj)
{
	obj.attendanceID = IDAssigner();
	cout << "Enter Date = ";
	cin >> obj.date;
	cout << "Enter Time In = ";
	cin >> obj.timeIn;
	cout << "Enter Time Out = ";
	cin >> obj.timeOut;
	return in;
}

void Attendance::addAttendance(string filename, string helpingfile)
{
	ifstream fin;
	ofstream fout;
	fout.open(filename, ios::app);
	if (!fout)
	{
		cout << "\nFile not created!";
	}
	else
	{
		fin.open(helpingfile);
		fin.seekg(0);
		if (!(fin.is_open()))
		{
			cout << "\nUnable to excess Members Data!";
		}
		else
		{
			cout << "\nData Accessing....\n";
			fout << attendanceID << " " << date << " " << timeIn << " " << timeOut << " ";
			int count = 0;
			if (helpingfile == "Members.txt")
			{
				string nam;
				string em;
				string ph;
				string gen;
				string dob;
				int mID;
				string sDate;
				string eDate;
				bool mStatus;
				int pID;
				int tID;
				double amt;
				string pM;
				while (!fin.eof() && count < DataCalculate(helpingfile))
				{
					++count;
					fin >> nam >> em >> ph >> gen >> dob >> mID >> sDate >> eDate >> mStatus >> amt >> pM;
					int ID = mID;
					char att = '0';
					while (att != 'P' && att != 'A')
					{
						cout << nam << "(" << ID << ") = ";
						cin >> att;
					}
					fout << nam << "(" << ID << ")" << " " << att << " ";
				}
			}
			else if (helpingfile == "Staffs.txt")
			{
				string nam;
				string em;
				string ph;
				string gen;
				string dob;
				int sID;
				string hDate;
				string jobT;
				double sal;
				while (!fin.eof() && count < DataCalculate(helpingfile))
				{
					++count;
					fin >> nam >> em >> ph >> gen >> dob >> sID >> hDate >> jobT >> sal;
					int ID = sID;
					char att = '0';
					while (att != 'P' && att != 'A')
					{
						cout << nam << "(" << ID << ") = ";
						cin >> att;
					}
					fout << nam << "(" << ID << ")" << " " << att << " ";
				}
			}
			else if (helpingfile == "Trainers.txt")
			{
				string nam;
				string em;
				string ph;
				string gen;
				string dob;
				int tID;
				string spec;
				string shft;
				double sal;
				while (!fin.eof() && count < DataCalculate(helpingfile))
				{
					++count;
					fin >> nam >> em >> ph >> gen >> dob >> tID >> spec >> shft >> sal;
					int ID = tID;
					char att = '0';
					while (att != 'P' && att != 'A')
					{
						cout << nam << "(" << ID << ") = ";
						cin >> att;
					}
					fout << nam << "(" << ID << ")" << " " << att << " ";
				}
			}
			else
			{
				cout << "\nTRYING TO GET INVALID DATA!\n";
			}
			fin.close();
			fout << "." << endl;
		}
		fout.close();
	}
}
void Attendance::viewAttendance(string filename)
{
	fstream fin;
	fin.open(filename);
	fin.seekg(0);
	int attID;
	string dat;
	string timIn;;
	string timOut;
	string att;
	int loc = -1;
	if (!(fin.is_open()))
	{
		cout << "\nNo such File Exists!";
	}
	else
	{
		int count = 0;
		cout << endl;
		cout << "\n----------------------------------------------\n";
		cout << "ID\t" << "Date\t\t" << "TimeIn\t" << "TimeOut\t";
		cout << "\n----------------------------------------------\n";
		while (!fin.eof() && count < DataCalculate(filename))
		{
			++count;
			fin >> attID >> dat >> timIn >> timOut;
			cout << attID << "\t" << dat << "\t" << timIn << "\t" << timOut << endl;
			for (int i = 0; att != "."; i++)
			{
				fin >> att;
				if (att == "P" || att == "A")
				{
					cout << att << endl;
				}
				else
				{
					if (att != ".")
					{
						cout << att << " ";
					}
				}
			}
			if (!fin.eof())
			{
				att = "-";
			}
			cout << "----------------------------------------------\n";

		}
		fin.close();
	}
}

int Attendance::searchAttendance(int query, string fileName)
{
	fstream fin;
	fin.open(fileName);
	fin.seekg(0);
	int attID;
	string dat;
	string timIn;;
	string timOut;
	string att;
	int loc = -1;
	if (!(fin.is_open()))
	{
		cout << "\nNo such File Exists!";
	}
	else
	{
		int count = 0;
		cout << endl;
		cout << "\n----------------------------------------------\n";
		cout << "ID\t" << "Date\t\t" << "TimeIn\t" << "TimeOut\t";
		cout << "\n----------------------------------------------\n";
		while (!fin.eof() && count < DataCalculate(fileName))
		{
			++count;
			fin >> attID >> dat >> timIn >> timOut;
			if (attID == query)
			{
				loc = count;
				cout << attID << "\t" << dat << "\t" << timIn << "\t" << timOut << endl;
				for (int i = 0; att != "."; i++)
				{
					fin >> att;
					if (att == "P" || att == "A")
					{
						cout << att << endl;
					}
					else
					{
						if (att != ".")
						{
							cout << att << " ";
						}
					}
				}
				if (!fin.eof())
				{
					att = "-";
				}
				cout << "----------------------------------------------\n";
			}
			else
			{
				//cout << attID << "\t" << dat << "\t" << timIn << "\t" << timOut << endl;
				for (int i = 0; att != "."; i++)
				{
					fin >> att;
					if (att == "P" || att == "A")
					{
						//cout << att << endl;
					}
					else
					{
						if (att != ".")
						{
							//cout << att << " ";
						}
					}
				}
				if (!fin.eof())
				{
					att = "-";
				}
			}
		}
		fin.close();
	}
	return loc;
}

void Attendance::updateAttendance(int query, string fileName, string helpingfile)
{
	fstream fin, fout, hfin;
	int pos = searchAttendance(query,fileName);
	cout << "\n----------------------------------------";
	if (pos == -1)
	{
		cout << "\nNo Record Found Against this Query!";
		exit(0);
	}
	fin.open(fileName);
	fout.open("temp.txt", ios::app);
	fin.seekg(0);
	int attID;
	string dat;
	string timIn;;
	string timOut;
	string att;
	string line;
	if (!(fin.is_open()))
	{
		cout << "\nNo such File Exists!";
	}
	else
	{
		int count = 0;
		cout << endl;
		while (!fin.eof() && count < DataCalculate(fileName))
		{
			++count;
			if (!fout)
			{
				cout << "\nError While Updating Data!";
			}
			else
			{
				hfin.open(helpingfile);
				hfin.seekg(0);
				
				if (count == pos)
				{
					fin >> attID >> dat >> timIn >> timOut;
					cout << "\nEnter Updated Data!\n";
					cout << "Enter Date = ";
					cin >> dat;
					cout << "Enter TimeIn = ";
					cin >> timIn;
					cout << "Enter TimeOut = ";
					cin >> timOut;
					int typecount = 0;
					if (!(hfin.is_open()))
					{
						cout << "\nUnable to excess Data!";
					}
					else
					{
						cout << "\nData Accessing....\n";
						fout << attID << " " << dat << " " << timIn << " " << timOut << " ";
						if (helpingfile == "Members.txt")
						{
							string nam;
							string em;
							string ph;
							string gen;
							string dob;
							int mID;
							string sDate;
							string eDate;
							bool mStatus;
							int pID;
							int tID;
							double amt;
							string pM;
							while (!hfin.eof() && typecount < DataCalculate(helpingfile))
							{
								++typecount;
								hfin >> nam >> em >> ph >> gen >> dob >> mID >> sDate >> eDate >> mStatus >> amt >> pM;
								int ID = mID;
								char att = '0';
								while (att != 'P' && att != 'A')
								{
									cout << nam << "(" << ID << ") = ";
									cin >> att;
								}
								fout << nam << "(" << ID << ")" << " " << att << " ";
							}
						}
						else if (helpingfile == "Staffs.txt")
						{
							string nam;
							string em;
							string ph;
							string gen;
							string dob;
							int sID;
							string hDate;
							string jobT;
							double sal;
							while (!hfin.eof() && typecount < DataCalculate(helpingfile))
							{
								++typecount;
								hfin >> nam >> em >> ph >> gen >> dob >> sID >> hDate >> jobT >> sal;
								int ID = sID;
								char att = '0';
								while (att != 'P' && att != 'A')
								{
									cout << nam << "(" << ID << ") = ";
									cin >> att;
								}
								fout << nam << "(" << ID << ")" << " " << att << " ";
							}
						}
						else if (helpingfile == "Trainers.txt")
						{
							string nam;
							string em;
							string ph;
							string gen;
							string dob;
							int tID;
							string spec;
							string shft;
							double sal;
							while (!hfin.eof() && typecount < DataCalculate(helpingfile))
							{
								++typecount;
								hfin >> nam >> em >> ph >> gen >> dob >> tID >> spec >> shft >> sal;
								int ID = tID;
								char att = '0';
								while (att != 'P' && att != 'A')
								{
									cout << nam << "(" << ID << ") = ";
									cin >> att;
								}
								fout << nam << "(" << ID << ")" << " " << att << " ";
							}
						}
					}
					hfin.close();
				}
				else
				{
					fin >> attID >> dat >> timIn >> timOut;
					fout << attID << " " << dat << " " << timIn << " " << timOut << " ";
					for (int i = 0; att != "."; i++)
					{
						fin >> att;
						fout << att << " ";
					}
				}
				fout << " ." << endl;
				fout.close();
				
			}
		}
		fin.close();
		fout.close();
		if (fileName == "MemberAttendance.txt")
		{
			remove("MemberAttendance.txt");
			rename("temp.txt", "MemberAttendance.txt");
		}
		else if (fileName == "StaffAttendance.txt")
		{
			remove("StaffAttendance.txt");
			rename("temp.txt", "StaffAttendance.txt");
		}
		else
		{
			remove("TrainerAttendance.txt");
			rename("temp.txt", "TrainerAttendance.txt");
		}
		
	}
}

void Attendance::removeAttendance(int query, string fileName)
{
	fstream fin, fout;
	int pos = searchAttendance(query, fileName);
	cout << "\n----------------------------------------";
	if (pos == -1)
	{
		cout << "\nNo Record Found Against this Query!";
		exit(0);
	}
	fin.open(fileName);
	fout.open("temp.txt", ios::app);
	fin.seekg(0);
	int attID;
	string dat;
	string timIn;;
	string timOut;
	string att;
	string line;
	if (!(fin.is_open()))
	{
		cout << "\nNo such File Exists!";
	}
	else
	{
		int count = 0;
		cout << endl;
		while (!fin.eof() && count < DataCalculate(fileName))
		{
			++count;
			if (!fout)
			{
				cout << "\nError While Updating Data!";
			}
			else
			{
				char choice;
				if (count == pos)
				{
					cout << "\nAre you sure you want to delete above data\n";
					do {
						cout << "Enter Y/N: ";
						cin >> choice;
						switch (choice) {
						case 'Y':
							cout << "\nDATA REMOVED!";
							break;
						case 'y':
							cout << "\nDATA REMOVED!";
							break;
						case 'N':
							fin >> attID >> dat >> timIn >> timOut;
							fout << attID << " " << dat << " " << timIn << " " << timOut << " ";
							for (int i = 0; att != "."; i++)
							{
								fin >> att;
								fout << att << " ";
							}
							break;
						case 'n':
							fin >> attID >> dat >> timIn >> timOut;
							fout << attID << " " << dat << " " << timIn << " " << timOut << " ";
							for (int i = 0; att != "."; i++)
							{
								fin >> att;
								fout << att << " ";
							}
							break;
						default:
							cout << "Invalid choice!" << endl;
							this_thread::sleep_for(chrono::seconds());
							break;
						}
					} while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');
					fout << " ." << endl;
				}
				else
				{
					fin >> attID >> dat >> timIn >> timOut;
					fout << attID << " " << dat << " " << timIn << " " << timOut << " ";
					for (int i = 0; att != "."; i++)
					{
						fin >> att;
						fout << att << " ";
					}
				}
				fout << " ." << endl;
				fout.close();

			}
		}
		fin.close();
		fout.close();
		if (fileName == "MemberAttendance.txt")
		{
			remove("MemberAttendance.txt");
			rename("temp.txt", "MemberAttendance.txt");
		}
		else if (fileName == "StaffAttendance.txt")
		{
			remove("StaffAttendance.txt");
			rename("temp.txt", "StaffAttendance.txt");
		}
		else
		{
			remove("TrainerAttendance.txt");
			rename("temp.txt", "TrainerAttendance.txt");
		}

	}
}