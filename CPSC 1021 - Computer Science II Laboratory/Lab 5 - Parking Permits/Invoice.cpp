#include "Invoice.h"

using namespace std;

Invoice::Invoice () {
	personType = 0;
	vehicleType = 2;
	permitType = 5;
}

Invoice::Invoice (string ps, string v, string pm) {
	if (ps == "Teacher") {personType = 0;} 
	if (ps == "TA") {personType = 5;}
	if (ps == "Student") {personType = 10;}
	if (ps == "Visitor") {personType = 15;}
	
	if (v == "Lev") {vehicleType = 2;}
	if (v == "Ev") {vehicleType = 3;}
	if (v == "Motorcycle") {vehicleType = 4;}
	if (v == "Semi") {vehicleType = 5;}
	
	if (pm == "week") {permitType = 5;}
	if (pm == "semester") {permitType = 25;}
	if (pm == "annual") {permitType = 35;}	
}

void Invoice::setPersonType(string ps) {
	if (ps == "Teacher") {personType = 0;} 
	if (ps == "TA") {personType = 5;}
	if (ps == "Student") {personType = 10;}
	if (ps == "Visitor") {personType = 15;}
}

void Invoice::setVehicleType(string v) {
	if (v == "Lev") {vehicleType = 2;}
	if (v == "Ev") {vehicleType = 3;}
	if (v == "Motorcycle") {vehicleType = 4;}
	if (v == "Semi") {vehicleType = 5;}
}

void Invoice::setPermitType(string pm) {
	if (pm == "week") {permitType = 5;}
	if (pm == "semester") {permitType = 25;}
	if (pm == "annual") {permitType = 35;}
}

int Invoice::getPersonType() {
	return personType;
}

int Invoice::getVehicleType() {
	return vehicleType;
}

int Invoice::getPermitType() {
	return permitType;
}

void Invoice::calcTotalPrice() {
	price = (vehicleType * permitType) + personType;
    cout << "The price of the permit is: $" << price << endl;
}

void Invoice::invoiceFunct (Teacher tc, TA t, Student st, Visitor vs, Motorcycle mt, Lev l, Ev e, Semi s) {
	if (personType == 0) {
		cout << "User Type: Teacher" << endl
		<< "Name: " << tc.getName() << endl
		<< "Address: " << tc.getAddress() << endl
		<< "Email: " << tc.getEmail() << endl
		<< "ID: " << tc.getTeacherID() << endl
		<< "Dept: " << tc.getDepartment() << endl;
	}
	
	if (personType == 5) {
		cout << "User Type: TA" << endl
		<< "Name: " << t.getName() << endl
		<< "Address: " << t.getAddress() << endl
		<< "Email: " << t.getEmail() << endl
		<< "Major: " << t.getMajor() << endl
		<< "ID: " << t.getGradID() << endl;
	}
	
	if (personType == 10) {
		cout << "User Type: Student" << endl	
		<< "Name: " << st.getName() << endl
		<< "Address: " << st.getAddress() << endl
		<< "Email: " << st.getEmail() << endl
		<< "Year: " << st.getYear() << endl
		<< "Major: " << st.getMajor() << endl;
	}

	if (personType == 15) {
		cout << "User Type: Visitor" << endl
		<< "Name: " << vs.getName() << endl
		<< "Address: " << vs.getAddress() << endl
		<< "Email: " << vs.getEmail() << endl
		<< "Occupation: " << vs.getEmail() << endl
		<< "Reason: " << vs.getEmail() << endl;
	}			
	
	if (vehicleType == 2) {
		cout << "Vehicle Type: Low-Emission Vehicle" << endl
		<< "Make: " << l.getMake() << endl
		<< "Model: " << l.getModel() << endl
		<< "Year: " << l.getYear() << endl
		<< "Color: " << l.getCarColor() << endl
		<< "Type: " << l.getHybridOrElectric() << endl;
	}
	
	if (vehicleType == 3) {
		cout << "Vehicle Type: Emission Vehicle" << endl
		<< "Make: " << e.getMake() << endl
		<< "Model: " << e.getModel() << endl
		<< "Year: " << e.getYear() << endl
		<< "Battery: " << e.getBattery() << endl
		<< "Size: " << e.getSize() << endl;
	}
	
	if (vehicleType == 4) {
		cout << "Vehicle Type: Motorcycle" << endl
		<< "Make: " << mt.getMake() << endl
		<< "Model: " << mt.getModel() << endl
		<< "Year: " << mt.getYear() << endl
		<< "MPG: " << mt.getMPG() << endl
		<< "Purchased On: " << mt.getYearPurchased() << endl;
	}
	
	if (vehicleType == 5) {
		cout << "Vehicle Type: Semi" << endl
		<< "Make: " << s.getMake() << endl
		<< "Model: " << s.getModel() << endl
		<< "Year: " << s.getYear() << endl
		<< "License: " << s.getComLiscense() << endl
		<< "Weight: " << s.getWeight() << endl;
	}
}