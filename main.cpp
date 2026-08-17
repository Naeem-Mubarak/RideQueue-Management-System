#include<iostream>
#include<fstream>
#include<utility>
#include<tuple>
#include "Vehicle.h"
#include "Queue.h"
#include "Driver.h"
using namespace std;

int main(){
  servingQueue serving,Waiting;
  Vehicle *v;
  Drivers d;
  d.loadDriversFromFile("Driver.txt");
  serving.loadServingFromFile("Serving.txt");
  Waiting.loadServingFromFile("Waiting.txt");
  const int MAX_REGISTERED = 5;
  int option;
do{
   cout<<"1. Admin"<<endl;
   cout<<"2. Customer"<<endl;
   cout<<"3. Exit"<<endl;
   cout<<"Enter Option: ";
   cin>>option;
   if(option==1){
     int choice;
 do {
    cout<<"\n====== Admin Menu ======"<<endl;
    cout<<"1. Cancel a registration by ID"<<endl;
    cout<<"2. Display all registered participants"<<endl;
    cout<<"3. Display waiting list"<<endl;
    cout<<"4. Search by ID"<<endl;
    cout<<"5. Add Driver"<<endl;
    cout<<"6. Check Drivers"<<endl;
    cout<<"7. Search Driver by license"<<endl;
    cout<<"8. Serve first customer"<<endl; 
    cout<<"9. Exit"<<endl;
    cout<<"Enter your choice: ";
    cin>>choice;
    switch(choice){
      case 1: {
        int id;
        cout<<"Enter Registration ID to cancel: ";
        cin>>id;
        serving.delqueue(id);
        Waiting.delqueue(id);
        serving.saveToFile("Serving.txt");
        Waiting.saveToFile("Waiting.txt");
        if(serving.count < MAX_REGISTERED && Waiting.head != nullptr){
          queue* promote = Waiting.head;
          Waiting.delfront();
          serving.add(promote->ID,promote->name,promote->pick_location,promote->drop_location,"Served");
          cout<<"Promoted "<<promote->name<<" from Waiting to Registered!"<<endl;
          serving.saveToFile("Serving.txt");
          Waiting.saveToFile("Waiting.txt");
        }
        break;
      }
      case 2: {
        cout<<"\nRegistered Participants:"<<endl;
        serving.disp();
        break;
      }
      case 3: {
        cout<<"\nWaiting List:"<<endl;
        Waiting.disp();
        break;
      }
      case 4: {
        int ID;
        cout<<"Enter id to search: ";
        cin>>ID;
        pair<int,string> info=serving.search(ID);
        pair<int,string> w=Waiting.search(ID);
        int i=info.first;
        string na=info.second;
        int s=w.first;
        string n=w.second;
        cout<<"\nSearching in Registered list..."<<endl;
        if(i==-1){
          cout<<"Not Found"<<endl;
        }else{
          cout<<"Found!"<<endl;
          cout<<"Name: "<<na<<endl;
        }
        cout<<"\nSearching in Waiting list..."<<endl;
        if(s==-1){
          cout<<"Not Found"<<endl;
        }else{
          cout<<"Found!"<<endl;
          cout<<"Name: "<<n<<endl;
        }
        break;
      }
      case 5:{
        int license;
        string name;
        int pass;
        bool verified = false;
        while(!verified){
          cout<<"Enter License Number: ";
          cin>>license;
          if(d.search(license)==-1){
            cout<<"Enter Name: ";
            cin.ignore();
            getline(cin,name);
            cout<<"Enter Password: ";
            cin>>pass;
            d.add(license,name,pass);
            verified=true;
          }else{
            cout<<"Already present enter a different one"<<endl;
          }
        }
        ofstream out("Driver.txt",ios::app);
        out<<"License: "<<license<<" Name: "<<name<<" Password: "<<pass<<endl;
        break;
      }
      case 6:{
        cout<<"Available Drivers: "<<endl;
        d.disp();
        break;
      }
      case 7:{
        int li;
        cout<<"Enter License: ";
        cin>>li;
        int num=d.search(li);
        if(num==-1){
          cout<<"Not Found"<<endl;
        }else{
          cout<<num<<" Found"<<endl;
        }
        break;
      }
      case 8:{
        cout<<"Available Drivers: "<<endl;
        d.disp();
        int li;
        int password;
        bool ver=false;
        cout<<"Select Driver(liscense): ";
        cin>>li;
        auto info=d.getDriverInfo(li);
        int id=get<0>(info);
        string na=get<1>(info);
        int u=get<2>(info);
        tuple<int,string,string,string,string> cust = serving.returncustom();
        int cust_id = get<0>(cust);
        string cust_name = get<1>(cust);
        string cust_pick = get<2>(cust);
        string cust_drop = get<3>(cust);
        string cust_vehicle = get<4>(cust);
        while(!ver){
          cout<<"Enter Password: ";
          cin>>password;
          if(password==u){
            if(cust_vehicle=="Bike"){
              v=new Bike;
            }else if(cust_vehicle=="Truck"){
              v=new Truck;
            }else{
              v=new Car;
            }
            v->input();
            v->calculateBill();
            ofstream out("Done.txt",ios::app);
              out<<"<-----------Done----------->"<<endl;
              out<<"ID: "<<cust_id<<endl;
              out<<"Name: "<<cust_name<<endl;
              out<<"Pick up Location: "<<cust_pick<<endl;
              out<<"Drop Location: "<<cust_drop<< endl;
              out<<"Status: "<<cust_vehicle<<endl;
              out<<"Liscense: "<<id<<endl;
              out<<"Driver Name: "<<na<<endl;
              out<<"Vehicle Number: "<<v->getNumberPlate()<<endl;
              out<<"Billing: "<<v->bill<<endl;
              out<<"---------"<<endl;
              out.close();
              if (Waiting.head != nullptr) {
                auto nextCust = Waiting.returncustom(); // this removes Waiting head
                int wid = get<0>(nextCust);
                string wname = get<1>(nextCust);
                string wpick = get<2>(nextCust);
                string wdrop = get<3>(nextCust);
                string wvehicle = get<4>(nextCust);

                // append this waiting customer to serving (tail)
                serving.add(wid, wname, wpick, wdrop, wvehicle);
            }
            // rewrite both files so disk matches memory
            serving.saveToFile("Serving.txt");
            Waiting.saveToFile("Waiting.txt");
            d.delnode(id);
            d.saveDriversToFile("Driver.txt");
            ver = true;
            delete v;
          }else{
            cout<<"Incorrect Password"<<endl;
          }
        }
        break;
      }
      case 9:
        cout<<"Exiting program..."<<endl;
        break;
      default:
        cout<<"Invalid choice, try again."<<endl;
    }
  } while(choice != 9);
   }else if(option==2){
    int customeroption;
    do{
       cout<<"1. Register a participant"<<endl;
       cout<<"2. Exiting Program"<<endl;
       cout<<"Enter option: ";
       cin>>customeroption;
       switch(customeroption){
        case 1: {
        int id;
        string name,pick_location,drop_location;
        bool verify=false;
        int c;
        while(!verify){
          cout << "Enter Registration ID: ";
        cin >> id;
          pair<int,string> info=serving.search(id);
        pair<int,string> s=Waiting.search(id);
        int i=info.first;
        int d=s.first;
          if(i==-1 && d==-1){
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter pick_location: ";
        getline(cin, pick_location);
        cout << "Enter drop_location: ";
        getline(cin, drop_location);
        if(serving.count < MAX_REGISTERED){
           do{
    cout << "<------Choose Vehicle------>" << endl
         << "1. Bike" << endl
         << "2. Car" << endl
         << "3. Truck " << endl
         << "Enter c: ";
    cin >> c;
    cin.ignore();
    if (c == 1){
      v = new Bike;
    }else if (c == 2){
      v = new Car;
    }else if (c == 3){
      v = new Truck;
    }else{
      cout << "Wrong Selection you can only select from 1-3" << endl;
    }
  }while(c<1 || c>3);
          ofstream out("Serving.txt",ios::app);
          serving.add(id,name,pick_location,drop_location,"Served");
          out<<"ID: "<<id<<endl;
          out<<"Name: "<<name<<endl;
          out<<"Pick up Location: "<<pick_location<<endl;
          out<<"Drop Location: "<<drop_location << endl;
          out<<"Vehicle Type: "<<(c==1 ? "Bike" : c==2 ? "Car" : "Truck")<<endl;
          cout<<"Participant added to serving list and record saved in Served.txt!"<<endl;
verify=true;
        } else {
          ofstream out("Waiting.txt",ios::app);
          Waiting.add(id,name,pick_location,drop_location,"Waiting");
          out << "ID: " << id << endl;
          out << "Name: " << name << endl;
          out << "Pick up Location: " << pick_location << endl;
          out << "Drop Location: " << drop_location << endl;
          out << "Vehicle Type: "<<(c==1 ? "Bike" : c==2 ? "Car" : "Mini Car")<<endl;
          cout<<"Serving list full. Added to Waiting list!"<<endl;
          verify=true;
        }
          }else{
            cout<<"Enter Again: ";
          }
        }
        break;
      }
      case 2:{
        cout<<"Exiting Program"<<endl;
        break;
      }
      default:{
        cout<<"Inalid Choice"<<endl;
        cout<<"Try Again"<<endl;
      }
       }
    }while(customeroption!=2);
   }else if(option==3){
    cout<<"Exit Successfully"<<endl;
    break;
   }else{
    cout<<"Invalid Option"<<endl;
    break;
   }
}while(option!=3);
  return 0;
}