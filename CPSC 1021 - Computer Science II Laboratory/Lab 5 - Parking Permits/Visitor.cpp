#include "Visitor.h"

Visitor::Visitor() {};

string Visitor::getName () {
	return name;
}

void Visitor::setName (string n) {
	name = n;
}

string Visitor::getAddress() {
	return address;
}

void Visitor::setAddress (string a) {
	address = a;
}

string Visitor::getOccupation () {
	return occupation;
}

void Visitor::setOccupation (string o) {
	occupation = o;
}

string Visitor::getEmail () {
	return email;
}

void Visitor::setEmail (string e) {
	email = e;
}

string Visitor::getReason () {
	return reason;
}

bool Visitor::setReason (string r) {
	if ((r != "touring") || (r != "sports") || (r != "other")) {
		return false;
	}
	reason = r;
	return true;
}