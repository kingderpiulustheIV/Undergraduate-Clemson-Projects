#include "Patient.h"


Patient::Patient(){
  days = 0;
  rate = 0.0;
  medication = 0.0;
  services = 0.0; 
  patientType = 'I';
}
Patient::Patient(char t,int d, double r, double s, double m) {
  patientType = t;
  services = s;
  medication = m;  
  rate = r;
  days = d;
  } 
Patient::Patient(char t, double s, double m) {
  patientType = t;
  services = s;
  medication = m;  
  } 
char Patient::getPatientType(){
return patientType;
}
void Patient::setPatientType(char t){
  if(Patient::validateInput(t) == true)
    patientType = t;
    
  }
int Patient::getDays(){
return days;
}
void Patient::setDays(int d){
  if (Patient::validateInput(d) == true)
    days = d;
  
}
double Patient::getRate()const{
return rate;
}
void Patient::setRate(double r){
  if (Patient::validateInput(r) == true)
    rate = r;

}

double Patient::getServices()const{
return services;
}
void Patient::setServices(double s){
  if (Patient::validateInput(s) == true)
    services = s;
}

double Patient::getMedication()const{
return medication;
}
void Patient::setMedication(double m){
  if (Patient::validateInput(m) == true)
    medication = m;
}


bool Patient::validateInput(char input){
  if(input != 'I' && input != 'O'){
    patientType = 'I';
    return false;
  }
  return true;
}
bool Patient::validateInput(int input){
  if(input <= 0){
    days= 0;
    return false;  
  }
  return true;
}
bool Patient::validateInput(double input){
  if(input <= 0.0){
    rate= 0.0;
    return false;  
  }
  return true;
}

double Patient::calcTotalCharges() {
    return (days * rate) + services + medication;
}