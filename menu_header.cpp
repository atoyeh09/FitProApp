#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <Windows.h>
#include "Header.h"
#include "menu_header.h"
using namespace std;
void login_menu()
{
    cout << "\n|----------------------------------------------------|";
    cout << "\n|        _______   _____    ____  ____   ___         |";
    cout << "\n|          |      *  |      |___| |___| |   |        |";
    cout << "\n|          |____  |  |      |     |\\    |   |        |";
    cout << "\n|          |      |  |      |     | \\   |___|        |";
    cout << "\n|                                                    |";
    cout << "\n|              (GYM MANAGEMENT SYSTEM)               |";
    cout << "\n|----------------------------------------------------|";
    cout << "\n|                                                    |";
    cout << "\n|                   1. SignUp User                   |";
    cout << "\n|                   2. Login User                    |";
    cout << "\n|                   3. Exit                          |";
    cout << "\n|                                                    |";
    cout << "\n|----------------------------------------------------|";
    cout << endl;
}
void user_menu()
{
    cout << "\n|----------------------------------------------------|";
    cout << "\n|        _______   _____    ____  ____   ___         |";
    cout << "\n|          |      *  |      |___| |___| |   |        |";
    cout << "\n|          |____  |  |      |     |\\    |   |        |";
    cout << "\n|          |      |  |      |     | \\   |___|        |";
    cout << "\n|                                                    |";
    cout << "\n|              (GYM MANAGEMENT SYSTEM)               |";
    cout << "\n|----------------------------------------------------|";
    cout << "\n|                                                    |";
    cout << "\n|                1. Manage Members                   |";
    cout << "\n|                2. Manage Trainers                  |";
    cout << "\n|                3. Manage Staff                     |";
    cout << "\n|                4. Manage Equipments                |";
    cout << "\n|                5. Manage WorkoutPackages           |";
    cout << "\n|                6. Manage Attendance                |";
    cout << "\n|                7. View Analytics                   |";
    cout << "\n|                8. Logout                           |";
    cout << "\n|                                                    |";
    cout << "\n|----------------------------------------------------|";
    cout << endl;
}
void common_menu()
{
    cout << "\n|----------------------------------------------------|";
    cout << "\n|        _______   _____    ____  ____   ___         |";
    cout << "\n|          |      *  |      |___| |___| |   |        |";
    cout << "\n|          |____  |  |      |     |\\    |   |        |";
    cout << "\n|          |      |  |      |     | \\   |___|        |";
    cout << "\n|                                                    |";
    cout << "\n|              (GYM MANAGEMENT SYSTEM)               |";
    cout << "\n|----------------------------------------------------|";
    cout << "\n|                                                    |";
    cout << "\n|                  1. Add Data                       |";
    cout << "\n|                  2. View Data                      |";
    cout << "\n|                  3. Search Data                    |";
    cout << "\n|                  4. Update Data                    |";
    cout << "\n|                  5. Remove Data                    |";
    cout << "\n|                  6. Back                           |";
    cout << "\n|                                                    |";
    cout << "\n|----------------------------------------------------|";
    cout << endl;
}

void attendance_menu()
{
    cout << "\n|----------------------------------------------------|";
    cout << "\n|        _______   _____    ____  ____   ___         |";
    cout << "\n|          |      *  |      |___| |___| |   |        |";
    cout << "\n|          |____  |  |      |     |\\    |   |        |";
    cout << "\n|          |      |  |      |     | \\   |___|        |";
    cout << "\n|                                                    |";
    cout << "\n|              (GYM MANAGEMENT SYSTEM)               |";
    cout << "\n|----------------------------------------------------|";
    cout << "\n|                                                    |";
    cout << "\n|                  1. Member                         |";
    cout << "\n|                  2. Staff                          |";
    cout << "\n|                  3. Trainer                        |";
    cout << "\n|                  4. Back                           |";
    cout << "\n|                                                    |";
    cout << "\n|----------------------------------------------------|";
    cout << endl;
}

void analytics()
{
    cout << "\n|----------------------------------------------------|";
    cout << "\n|        _______   _____    ____  ____   ___         |";
    cout << "\n|          |      *  |      |___| |___| |   |        |";
    cout << "\n|          |____  |  |      |     |\\    |   |        |";
    cout << "\n|          |      |  |      |     | \\   |___|        |";
    cout << "\n|                                                    |";
    cout << "\n|              (GYM MANAGEMENT SYSTEM)               |";
    cout << "\n|----------------------------------------------------|";
    cout << "\n|                     ANALYTICS                      |";
    cout << "\n|----------------------------------------------------|";
    cout << "\n          Total Registered Members      : " << DataCalculate("Members.txt");
    cout << "\n          Total Registered Staff        : " << DataCalculate("Staffs.txt");
    cout << "\n          Total Registered Trainers     : " << DataCalculate("Trainers.txt");
    cout << "\n          Total Registered Equipments   : " << DataCalculate("Equipments.txt");
    cout << "\n          Total No of Offering Packages : " << DataCalculate("Packages.txt");
    cout << "\n|----------------------------------------------------|";
    cout << endl;
}

void screen()
{
    Login Login;
    int choice;
    do {
        login_menu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            system("CLS");
            Login.registerUser();
            break;
        case 2:
            system("CLS");
            if (Login.login() == true)
            {
                cout << "\nLogin Successfully......";
                this_thread::sleep_for(chrono::seconds(5));
                step1();
            }
            else
            {
                cout << "\nInvalid Username or Password!";
                choice = 4;
                this_thread::sleep_for(chrono::seconds(2));
            }
            break;
        case 3:
            system("CLS");
            cout << "Hope you have a Good Experience with FIT PRO!" << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
            this_thread::sleep_for(chrono::seconds());
            system("CLS");
            break;
        }
    } while (choice != 3);
}

void step1()
{
    int choice;
    do {
        user_menu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            system("CLS");
            step_member();
            break;
        case 2:
            system("CLS");
            step_trainer();
            break;
        case 3:
            system("CLS");
            step_staff();
            break;
        case 4:
            system("CLS");
            step_equipment();
            break;
        case 5:
            system("CLS");
            step_package();
            break;
        case 6:
            system("CLS");
            step_attendance();
            break;
        case 7:
            system("CLS");
            analytics();
            break;
        default:
            cout << "Invalid choice!" << endl;
            this_thread::sleep_for(chrono::seconds());
            system("CLS");
            break;
        }
    } while (choice != 8);
    system("CLS");
    screen();
}

void step_member()
{
    int choice;
    Member obj;
    do {
        int query;
        common_menu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            system("CLS");
            cin >> obj;
            obj.addUser();
            break;
        case 2:
            system("CLS");
            obj.viewUser();
            break;
        case 3:
            system("CLS");
            cout << "Enter the ID number which you want to Search = ";
            cin >> query;
            obj.searchMember(query);
            break;
        case 4:
            system("CLS");
            cout << "Enter the ID number which you want to Update = ";
            cin >> query;
            obj.removeMember(query);
            break;
        case 5:
            system("CLS");
            cout << "Enter the ID number which you want to Remove = ";
            cin >> query;
            obj.removeMember(query);
            break;
        default:
            cout << "Invalid choice!" << endl;
            this_thread::sleep_for(chrono::seconds());
            system("CLS");
            break;
        }
    } while (choice != 6);
    system("CLS");
    user_menu();
}

void step_trainer()
{
    int query;
    int choice;
    Trainer obj;
    do {
        common_menu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            system("CLS");
            cin >> obj;
            obj.addUser();
            break;
        case 2:
            system("CLS");
            obj.viewUser();
            break;
        case 3:
            system("CLS");
            cout << "Enter the ID number which you want to Search = ";
            cin >> query;
            obj.searchTrainer(query);
            break;
        case 4:
            system("CLS");
            cout << "Enter the ID number which you want to Update = ";
            cin >> query;
            obj.removeTrainer(query);
            break;
        case 5:
            system("CLS");
            cout << "Enter the ID number which you want to Remove = ";
            cin >> query;
            obj.removeTrainer(query);
            break;
        default:
            cout << "Invalid choice!" << endl;
            this_thread::sleep_for(chrono::seconds());
            system("CLS");
            break;
        }
    } while (choice != 6);
    system("CLS");
    user_menu();
}

void step_staff()
{
    int query;
    int choice;
    Staff obj;
    do {
        common_menu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            system("CLS");
            cin >> obj;
            obj.addUser();
            break;
        case 2:
            system("CLS");
            obj.viewUser();
            break;
        case 3:
            system("CLS");
            cout << "Enter the ID number which you want to Search = ";
            cin >> query;
            obj.searchStaff(query);
            break;
        case 4:
            system("CLS");
            cout << "Enter the ID number which you want to Update = ";
            cin >> query;
            obj.removeStaff(query);
            break;
        case 5:
            system("CLS");
            cout << "Enter the ID number which you want to Remove = ";
            cin >> query;
            obj.removeStaff(query);
            break;
        default:
            cout << "Invalid choice!" << endl;
            this_thread::sleep_for(chrono::seconds());
            system("CLS");
            break;
        }
    } while (choice != 6);
    system("CLS");
    user_menu();
}

void step_equipment()
{
    int query;
    int choice;
    Equipment obj;
    do {
        common_menu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            system("CLS");
            cin >> obj;
            obj.addEquipment();
            break;
        case 2:
            system("CLS");
            obj.viewEquipment();
            break;
        case 3:
            system("CLS");
            cout << "Enter the ID number which you want to Search = ";
            cin >> query;
            obj.searchEquipment(query);
            break;
        case 4:
            system("CLS");
            cout << "Enter the ID number which you want to Update = ";
            cin >> query;
            obj.removeEquipment(query);
            break;
        case 5:
            system("CLS");
            cout << "Enter the ID number which you want to Remove = ";
            cin >> query;
            obj.removeEquipment(query);
            break;
        default:
            cout << "Invalid choice!" << endl;
            this_thread::sleep_for(chrono::seconds());
            system("CLS");
            break;
        }
    } while (choice != 6);
    system("CLS");
    user_menu();
}

void step_package()
{
    int query;
    int choice;
    WorkoutPackage obj;
    do {
        common_menu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            system("CLS");
            cin >> obj;
            obj.addPackage();
            break;
        case 2:
            system("CLS");
            obj.viewPackage();
            break;
        case 3:
            system("CLS");
            cout << "Enter the ID number which you want to Search = ";
            cin >> query;
            obj.searchPackage(query);
            break;
        case 4:
            system("CLS");
            cout << "Enter the ID number which you want to Update = ";
            cin >> query;
            obj.removePackage(query);
            break;
        case 5:
            system("CLS");
            cout << "Enter the ID number which you want to Remove = ";
            cin >> query;
            obj.removePackage(query);
            break;
        default:
            cout << "Invalid choice!" << endl;
            this_thread::sleep_for(chrono::seconds());
            system("CLS");
            break;
        }
    } while (choice != 6);
    system("CLS");
    user_menu();
}


void step_attendance()
{
    int choice;
    Attendance obj;
    do {
        common_menu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            system("CLS");
            add_att();
            break;
        case 2:
            system("CLS");
            view_att();
            break;
        case 3:
            system("CLS");
            search_att();
            break;
        case 4:
            system("CLS");
            update_att();
            break;
        case 5:
            system("CLS");
            remove_att();
            break;
        default:
            cout << "Invalid choice!" << endl;
            this_thread::sleep_for(chrono::seconds());
            system("CLS");
            break;
        }
    } while (choice != 6);
    system("CLS");
    user_menu();
}

void add_att()
{
    int choice;
    Attendance obj;
    do {
        attendance_menu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            system("CLS");
            cin >> obj;
            obj.addAttendance("MemberAttendance.txt", "Members.txt");
            break;
        case 2:
            system("CLS");
            cin >> obj;
            obj.addAttendance("StaffAttendance.txt", "Staffs.txt");
            break;
        case 3:
            system("CLS");
            cin >> obj;
            obj.addAttendance("TrainerAttendance.txt", "Trainers.txt");
        default:
            cout << "Invalid choice!" << endl;
            this_thread::sleep_for(chrono::seconds());
            system("CLS");
            break;
        }
    } while (choice != 4);
    system("CLS");
    step_attendance();
}

void view_att()
{
    int choice;
    Attendance obj;
    do {
        attendance_menu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            system("CLS");
            obj.viewAttendance("MemberAttendance.txt");
            break;
        case 2:
            system("CLS");
            obj.viewAttendance("StaffAttendance.txt");
            break;
        case 3:
            system("CLS");
            cin >> obj;
            obj.viewAttendance("TrainerAttendance.txt");
        default:
            cout << "Invalid choice!" << endl;
            this_thread::sleep_for(chrono::seconds());
            system("CLS");
            break;
        }
    } while (choice != 4);
    system("CLS");
    step_attendance();
}

void search_att()
{
    int query;
    int choice;
    Attendance obj;
    do {
        attendance_menu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            system("CLS");
            cout << "Enter the ID number which you want to Search = ";
            cin >> query;
            if (obj.searchAttendance(query, "MemberAttendance.txt") == -1)
            {
                cout << "\nNo Result Found!\n";
            }
            break;
        case 2:
            system("CLS");
            cout << "Enter the ID number which you want to Search = ";
            cin >> query;
            if (obj.searchAttendance(query, "StaffAttendance.txt") == -1)
            {
                cout << "\nNo Result Found!\n";
            }
            break;
        case 3:
            system("CLS");
            cout << "Enter the ID number which you want to Search = ";
            cin >> query;
            if (obj.searchAttendance(query, "TrainerAttendance.txt") == -1)
            {
                cout << "\nNo Result Found!\n";
            }
        default:
            cout << "Invalid choice!" << endl;
            this_thread::sleep_for(chrono::seconds());
            system("CLS");
            break;
        }
    } while (choice != 4);
    system("CLS");
    step_attendance();
}

void update_att()
{
    int query;
    int choice;
    Attendance obj;
    do {
        attendance_menu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            system("CLS");
            cout << "Enter the ID number which you want to Update = ";
            cin >> query;
            obj.updateAttendance(query, "MemberAttendance.txt", "Members.txt");
            break;
        case 2:
            system("CLS");
            cout << "Enter the ID number which you want to Update = ";
            cin >> query;
            obj.updateAttendance(query, "StaffAttendance.txt", "Staffs.txt");
            break;
        case 3:
            system("CLS");
            cout << "Enter the ID number which you want to Update = ";
            cin >> query;
            obj.updateAttendance(query, "TrainerAttendance.txt", "Trainers.txt");
        default:
            cout << "Invalid choice!" << endl;
            this_thread::sleep_for(chrono::seconds());
            system("CLS");
            break;
        }
    } while (choice != 4);
    system("CLS");
    step_attendance();
}

void remove_att()
{
    int query;
    int choice;
    Attendance obj;
    do {
        attendance_menu();
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
        case 1:
            system("CLS");
            cout << "Enter the ID number which you want to Remove = ";
            cin >> query;
            obj.removeAttendance(query, "MemberAttendance.txt");
            break;
        case 2:
            system("CLS");
            cout << "Enter the ID number which you want to Remove = ";
            cin >> query;
            obj.removeAttendance(query, "StaffAttendance.txt");
            break;
        case 3:
            system("CLS");
            cout << "Enter the ID number which you want to Remove = ";
            cin >> query;
            obj.removeAttendance(query, "TrainerAttendance.txt");
        default:
            cout << "Invalid choice!" << endl;
            this_thread::sleep_for(chrono::seconds());
            system("CLS");
            break;
        }
    } while (choice != 4);
    system("CLS");
    step_attendance();
}
