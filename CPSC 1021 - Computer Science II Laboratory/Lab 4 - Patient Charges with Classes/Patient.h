#ifndef PATIENT_H
#define PATIENT_H
class Patient{
private:
  double services;
  int days;
  double rate;
  double medication;
  char patientType;
  bool validateInput(char input);
  bool validateInput(int input);
  bool validateInput(double input);
   


public:
  Patient();
  Patient(char t,int d, double r, double s, double m);
  Patient(char t, double s, double m);

  double calcTotalCharges();

  char getPatientType();
  void setPatientType(char t);
  int getDays();
  void setDays(int d);
  double getRate()const;
  void setRate(double r);
  double getServices()const;
  void setServices(double s);
  double getMedication()const;
  void setMedication(double m);
};

#endif
