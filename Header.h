#pragma once

#include <iostream>
#include <string>
#include <fstream>
using namespace std;
struct LoginAttributes {
	string username;
	string password;
};

class Login {
private:
	LoginAttributes* users;
	int numUsers;
	int maxUsers;
	void readUsersFromFile();

public:
	Login();
	~Login();
	void registerUser();
	bool login();
};

class User {
protected:
	string name;
	string email;
	string phone;
	string gender;
	string dateOfBirth;
public:
	User() {}
	User(string name_, string email_, string phone_, string gender_, string dob) : name(name_), email(email_), phone(phone_), gender(gender_), dateOfBirth(dob) {}
	void set();
	void get();
	virtual void addUser() = 0;
	virtual void viewUser() = 0;
};

class Trainer :public User {
	int trainerID;
	string specialization;
	string shift;
	double salary;
public:
	void addUser();
	friend istream& operator >>(istream& in, Trainer& obj);
	void viewUser();
	int searchTrainer(int query);
	void updateTrainer(int query);
	void removeTrainer(int query);
};

class WorkoutPackage {
	int packageID;
	string title;
	string description;
	double price;
	string duration;
public:
	void addPackage();
	friend istream& operator >>(istream& in, WorkoutPackage& obj);
	void viewPackage();
	int searchPackage(int query);
	void updatePackage(int query);
	void removePackage(int query);
};

class Member :public User {
	int membershipID;
	string startDate;
	string endDate;
	bool membershipStatus;
	double amount;
	string paymentMethod;
public:
	void addUser();
	friend istream& operator >>(istream& in, Member& obj);
	void viewUser();
	int searchMember(int query);
	void updateMember(int query);
	void removeMember(int query);

};

class Staff :public User {
	int staffID;
	string hireDate;
	string jobtitle;
	double salary;
public:
	void addUser();
	friend istream& operator >>(istream& in, Staff& obj);
	void viewUser();
	int searchStaff(int query);
	void updateStaff(int query);
	void removeStaff(int query);
};

class Equipment {
	int equipmentID;
	string name;
	string type;
	int quantity;
	string purchaseDate;
	double purchasePrice;
public:
	void addEquipment();
	friend istream& operator >>(istream& in, Equipment& obj);
	void viewEquipment();
	int searchEquipment(int query);
	void updateEquipment(int query);
	void removeEquipment(int query);
};

class Attendance {
	int attendanceID;
	string date;
	string timeIn;
	string timeOut;
public:
	void addAttendance(string filename, string helpingfile);
	friend istream& operator >>(istream& in, Attendance& obj);
	void viewAttendance(string fileName);
	int searchAttendance(int query, string fileName);
	void updateAttendance(int query, string fileName, string helpingfile);
	void removeAttendance(int query, string fileName);

};

int DataCalculate(string fileName);
int IDAssigner();