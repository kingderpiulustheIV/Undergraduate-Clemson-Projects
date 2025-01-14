#ifndef INVOICE_H_
#define INVOICE_H_
#include "Motorcycle.h"
#include "Lev.h"
#include "Ev.h"
#include "Semi.h"
#include "Teacher.h"
#include "TA.h"
#include "Student.h"
#include "Visitor.h"

using namespace std;

class Invoice
{//Beginning of "Invoice" class
private:
  //Private member variable declaration
  int personType {1};
  int vehicleType {1};
  int permitType {1};
  const double discount {0.1};
  const double serviceCharge {0.05};
  double price;

  //Private member function delcaration
  bool validatePermitType(int);
public:
  Invoice();
  Invoice(string, string, string);

  //Public member function declarations
  void setPersonType(string);
  void setVehicleType(string);
  void setPermitType(string);
  int getPermitType();
  int getPersonType();
  int getVehicleType();
  void calcTotalPrice();
  void invoiceFunct(Teacher, TA, Student, Visitor, Motorcycle, Lev, Ev, Semi);         

};//End of "Invoice" class

#endif
