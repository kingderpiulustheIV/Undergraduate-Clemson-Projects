#include <iostream>
#include <string>
#include <cstring>
#include "Semi.h"
#include "TA.h"
#include "Motorcycle.h"
#include "Lev.h"
#include "Ev.h"
#include "Invoice.h"

using namespace std;

void getVehicle(string& vehicleType, Lev& Lev, Ev& ev, Motorcycle& motor, Semi& Semi);

int main() {
    string permitType;
    string vehicleType;
    bool validation = false;
    string permitLength = "";

    //Variables for TA
    string address;
    string name;
    string email;
    long int gradID;

    //Variables for teacher
    long int teacherID;
    string department;
    string major;

    //Variables for student

    //Variables for visitor
    string occupation;
    string reason;

    //Permit Types
    TA assistant;
    Teacher professor;
    Student undergrad;
    Visitor guest;

    //Vehicles
	Lev Lev;
    Ev ev;
	Motorcycle motor;
	Semi Semi;


    int year;
    do {
        std::cout << "Enter Permit Type(TA, Teacher, Student, Visitor): ";
        std::cin >> permitType;
        if(permitType == "TA"){
            validation = true;
            getVehicle(vehicleType, Lev, ev, motor, Semi);
            cout << "Enter name: ";
            cin.ignore();
            getline (cin, name);
            assistant.setName(name);

            cout << "Enter address: ";
            getline (cin, address);
            assistant.setAddress(address);

            cout << "Enter Grad ID: ";
            cin >> gradID;
            assistant.setGradID(gradID);

            cout << "Enter Major: ";
            cin.ignore();
            getline (cin, major);
            assistant.setMajor(major);

            cout << "Enter Email: ";
            cin >> email;
            assistant.setEmail(email);


        }

        if(permitType == "Teacher"){
            validation = true;
            getVehicle(vehicleType, Lev, ev, motor, Semi);
            cout << "Enter name: ";
            cin.ignore();
            getline (cin, name);
            professor.setName(name);

            cout << "Enter address: ";
            getline (cin, address);
            professor.setAddress(address);

            cout << "Enter Teacher ID: ";
            cin >> teacherID;
            professor.setTeacherID(teacherID);

            cout << "Enter department: ";
            cin.ignore();
            getline (cin, department);
            professor.setDepartment(department);

            cout << "Enter Email: ";
            cin >> email;
            professor.setEmail(email);
        }

        if(permitType == "Student"){
            validation = true;
            getVehicle(vehicleType, Lev, ev, motor, Semi);
            cout << "Enter name: ";
            cin.ignore();
            getline (cin, name);
            undergrad.setName(name);

            cout << "Enter address: ";
            getline (cin, address);
            undergrad.setAddress(address);

            cout << "Enter Graduation year: ";
            cin >> year;
            undergrad.setYear(year);

            cout << "Enter Major: ";
            cin.ignore();
            getline (cin, major);
            undergrad.setMajor(major);

            cout << "Enter Email: ";
            cin >> email;
            undergrad.setEmail(email);
        }

        if(permitType == "Visitor"){
            validation = true;
            getVehicle(vehicleType, Lev, ev, motor, Semi);
            cout << "Enter name: ";
            cin.ignore();
            getline (cin, name);
            guest.setName(name);

            cout << "Enter address: ";
            getline (cin, address);
            guest.setAddress(address);

            cout << "Enter occupation: ";
            getline (cin, occupation);
            guest.setOccupation(occupation);

            cout << "Enter Reason: ";
            getline (cin, reason);
            guest.setReason(reason);

            cout << "Enter Email: ";
            cin >> email;
            guest.setEmail(email);
        }
    }  while(validation == false);


    do {
        cout << "Enter length of permit (week, semester, annual): ";
        cin >> permitLength;

    } while (permitLength != "week" && permitLength != "semester" && permitLength != "annual");



    Invoice i(permitType, vehicleType, permitLength);

    i.calcTotalPrice();
    i.invoiceFunct(professor, assistant, undergrad, guest, motor, Lev, ev, Semi);


}

void getVehicle(string& vehicleType, Lev& Lev, Ev& ev, Motorcycle& motor, Semi& Semi) {
	string vehicleMake = "";
	string vehicleModel = "";
	int vehicleYear = 0;
	string semiComLiscense = "";
	int vehicleBattery = 0;
	char vehicleSize = ' ';
	string vehicleColor = "";
	string hybridOrElectric = "";
	int weight = 0;
	string comLiscense = "";
	int vehicleYearPuchased = 0;
	int mpg = 0;

	do {
		std::cout << "Enter Vechicle Type (Lev, Ev, Motorcycle, Semi): ";
		std::cin >> vehicleType;
	} while (vehicleType != "Lev" && vehicleType != "Ev" && vehicleType != "Motorcycle" && vehicleType != "Semi");

	if (vehicleType == "Lev") {


		while (vehicleMake != "Honda" && vehicleMake != "Toyota" && vehicleMake != "Ford" &&
            vehicleMake != "Nissan" && vehicleMake != "GM") {

            std::cout << "Enter valid make of Lev (Honda, Toyota, Ford, Nissan, GM): ";
			std::cin >> vehicleMake;
		}

        Lev.setMake(vehicleMake);

        while (vehicleModel != "Prius" && vehicleModel != "Focus" && vehicleModel != "Civic" &&
            vehicleModel != "Volt") {
			std::cout << "Enter valid model of Lev: (Prius, Focus, Civic, Volt): ";
			std::cin >> vehicleModel;
		}

        Lev.setModel(vehicleModel);


        while (vehicleYear < 1980 || vehicleYear > 2023) {
			std::cout << "Enter valid year of Lev (1978, 2023): ";
			std::cin >> vehicleYear;
		}

        Lev.setYear(vehicleYear);

        while (vehicleColor != "Green" && vehicleColor != "Blue" && vehicleColor != "Black" &&
            vehicleColor != "White") {
			std::cout << "Enter valid color of Lev: (Green, Blue, Black, White): ";
			std::cin >> vehicleColor;
		}

        Lev.setCarColor(vehicleColor);

		while (hybridOrElectric != "Hybrid") {
			std::cout << "Lev Hybred or Electric (Hybrid): ";
			std::cin >> hybridOrElectric;
			Lev.setHybridOrElectric(hybridOrElectric);
		}

        Lev.setHybridOrElectric(hybridOrElectric);


	}

    if (vehicleType == "Ev") {




        while (vehicleSize != 's' && vehicleSize != 'm' && vehicleSize != 'l') {
    		std::cout << "Enter a valid battery of EV Vehicle(s, m, l): ";
    		std::cin >> vehicleSize;
    	}

        ev.setSize(vehicleSize);

        while (vehicleBattery != 999 && vehicleBattery != 550 && vehicleBattery != 100) {
    		std::cout << "Enter valid battery of EV Vehicle(999, 550, 100): ";
    		std::cin >> vehicleBattery;
    	}

        ev.setBattery(vehicleBattery);


        while (vehicleYear < 1980 || vehicleYear > 2023) {
			std::cout << "Enter valid year of Ev (1978, 2023): ";
			std::cin >> vehicleYear;
		}

        ev.setYear(vehicleYear);


        while (vehicleMake != "Tesla" && vehicleMake != "Lucid") {
    		std::cout << "Enter valid make of EV Vehicle (Tesla, Lucid): ";
    		std::cin >> vehicleMake;
    	}

        ev.setMake(vehicleMake);

        while (vehicleModel != "S" && vehicleModel != "3" && vehicleModel != "X" &&
            vehicleModel != "Y" && vehicleModel != "S3XY") {
    		std::cout << "Enter valid make of EV Vehicle (S, 3, X, Y, S3XY): ";
    		std::cin >> vehicleModel;
    	}

        ev.setModel(vehicleModel);
    }

    if (vehicleType == "Motorcycle") {
            while (vehicleMake != "Honda" && vehicleMake != "Ducati" && vehicleMake != "Triumph" &&
                vehicleMake != "Thruxton" && vehicleMake != "Tigersportt") {
				std::cout << "Enter valid make of Motorcycle"
                    " (Honda, Ducati, Triumph, Thruxton, Tigersportt): ";
				std::cin >> vehicleMake;
			}

			motor.setMake(vehicleMake);
			while (vehicleModel != "CB750" && vehicleModel != "CB125F" && vehicleModel != "V4" &&
                vehicleModel != "916") {
				std::cout << "Enter valid model of Motorcycle: (CB750, CB125F, V4, 916): ";
				std::cin >> vehicleModel;
			}

			motor.setModel(vehicleModel);

			while (vehicleYear < 1980 || vehicleYear > 2023) {
				std::cout << "Enter valid year of Motorcycle (1978, 2023): ";
				std::cin >> vehicleYear;
			}

			motor.setYear(vehicleYear);

			while (vehicleYearPuchased < 1980 || vehicleYearPuchased > 2022) {
				std::cout << "Enter a valid year of Motorcycle purchase:  (1980, 2022): ";
				std::cin >> vehicleYearPuchased;
			}

			motor.setYearPurchased(vehicleYearPuchased);
			while (mpg < 10) {
				std::cout << "Enter a valid mpg: ";
				std::cin >> mpg;
			}
			motor.setMPG(mpg);
    }
			if (vehicleType == "Semi") {

				while (vehicleMake != "Volvo" && vehicleMake != "Mack" &&
                    vehicleMake != "Kenworth") {
					std::cout << "Enter valid make of Semi (Volvo, Mack, Kenworth): ";
					std::cin >> vehicleMake;
				}

                Semi.setMake(vehicleMake);

                while (vehicleModel != "T200" && vehicleModel != "F901" &&
                    vehicleModel != "ZB3TA") {
					std::cout << "Enter valid model of Semi: (T200, F901, ZB3TA)";
					std::cin >> vehicleModel;
				}

                Semi.setModel(vehicleModel);


                while (vehicleYear < 1978 || vehicleYear > 2023) {
					std::cout << "Enter valid year of Semi (1978, 2023): ";
					std::cin >> vehicleYear;
				}

                Semi.setYear(vehicleYear);


                while (weight <= 0) {
					std::cout << "Enter valid weight of Semi: ";
					std::cin >> weight;
				}

                Semi.setWeight(weight);

                std::cout << "Enter a valid Commercal liscense of Semi Driver: ";
				std::cin >> comLiscense;

                Semi.setComLiscense(comLiscense);
			}
		}
