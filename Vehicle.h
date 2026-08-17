#pragma once
#include<iostream>
#include<fstream>
using namespace std;

class Vehicle{
protected:
  string numberPlate,goodsType;
  void basicinput(){
    cout<<"<---------Enter Vehicle Informaton--------->"<<endl;
    cout<<"Enter Number: ";
    cin>>numberPlate;
    cout<<endl;
  }
  void computeBill(double fuelRate, double usedAmount, int latePenalty){
        int choice;
        do{
            cout<<"1. Customer Arrived late"<<endl;
            cout<<"2. Customer On time"<<endl;
            cout<<"3. Exit"<<endl;
            cout<<"Enter choice: ";
            cin>>choice;
            switch(choice){
                case 1:{
                    int min;
                    cout<<"Enter min: ";
                    cin>>min;
                    bill=(fuelRate*usedAmount)+(min*latePenalty);
                    break;
                }
                case 2:{
                    bill = (fuelRate * usedAmount);
                    break;
                }
                case 3:
                    cout<<"Exiting Billing Menu\n";
                    break;
                default:
                    cout<<"Invalid Choice Try Again\n";
            }
        } while(choice != 3);
    }
public:
  double bill;
  // Pure virtual Function
  string getNumberPlate(){ 
    return numberPlate; 
  }
  virtual void input()=0;
  virtual void calculateBill()=0;
  // virtual Destructor
  virtual ~Vehicle() {}
};
class Bike:public Vehicle{
public:
  float fuelRate=256;
  int late=3;
  float Oil;
  void input() override{
    Vehicle::basicinput();
    cout << "<----------Enter Bike Data---------->" << endl;
    cout << "Enter Oil Used: ";
    cin >> Oil;
    cin.ignore();
  }
  void calculateBill() override{
     computeBill(fuelRate,Oil,late);
  }
};
class Car : public Vehicle{
public:
  double fuelRate = 470.23;
  float tollTax, fuelUsed;
  int late=10;
  void input() override{
    Vehicle::basicinput();
    tinput();
  }
  void tinput(){
    cout << "<----------Enter Cost---------->" << endl;
    cout << "Toll Tax(GST): ";
    cin >> tollTax;
    cout << "Enter Fuel Used: ";
    cin >> fuelUsed;
    cin.ignore();
  }
 void calculateBill() override{
    computeBill(fuelRate,fuelUsed,late);
    bill+=tollTax;
  }
};
class Truck : public Car{
public:
  Truck(){
    // fuel rate overriding
    fuelRate = 259.13;
  }
  void input() override{
    Vehicle::basicinput();
    Car::tinput();
  }
  void calculateBill() override {
    computeBill(fuelRate, fuelUsed, late);
    bill += tollTax;
}
};
