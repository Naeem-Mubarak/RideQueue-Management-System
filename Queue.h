#pragma once
#include<iostream>
#include<fstream>
#include<utility>
#include<tuple>
using namespace std;

class queue{
  public:
  int ID;
  string name;
  string pick_location;
  string drop_location;
  string Status;
  queue* next=nullptr;
  queue(int ID,string name,string pick_location,string drop_location,string Status){
    this->ID=ID;
    this->name=name;
    this->pick_location=pick_location;
    this->drop_location=drop_location;
    this->Status=Status;
  }
};
class servingQueue{
  public:
  queue* head=nullptr;
  queue* tail=nullptr;
  int count=0;
  void add(int ID,string name,string pick_location,string drop_location,string Status){
    queue* n=new queue(ID,name,pick_location,drop_location,Status);
    if(head==nullptr){
      head=tail=n;
    }else{
      tail->next=n;
      tail=n;
    }
    count++;
  }
  void delfront(){
    if(head==nullptr){
      cout<<"Empty list"<<endl;
      return;
    }else if(head==tail){
      delete head;
      head=tail=nullptr;
      count=0;
      return;
    }else{
      queue* temp=head;
      head=head->next;
      delete temp;
      count--;
    }
  }
  tuple<int,string,string,string,string> returncustom(){
    if(head==nullptr){
      cout<<"Empty list"<<endl;
      return {-1,"","","",""};
    }else{
      queue* temp=head;
      auto info=make_tuple(temp->ID,temp->name,temp->pick_location,temp->drop_location,temp->Status);
      head=temp->next;
      delete temp;
      count--;
      return info;
    }
  }
  pair<int,string> search(int ID){
    queue* temp=head;
    while(temp!=nullptr){
      if(temp->ID==ID){
        auto s=make_pair(1,temp->name);
        return s;
      }
      temp=temp->next;
    }
    return {-1,""};
  }
  void deltail(){
    if(head==nullptr){
      cout<<"No queue"<<endl;
      return;
    }
    queue* temp=head;
    while(temp->next!=tail){
      temp=temp->next;
    }
    delete tail;
    temp->next=nullptr;
    tail=temp;
    count--;
  }
  void delqueue(int ID){
    if(head==nullptr){
      cout<<"No queue"<<endl;
      return;
    }
    if(head->ID == ID){
        delfront();
        return;
    }
    queue* temp=head;
    while(temp->next!=nullptr && temp->next->ID!=ID){
      temp=temp->next;
    }
    if(temp->next==nullptr){
      cout<<"Not Exist"<<endl;
      return;
    }else if(temp->next==tail){
      deltail();
      return;
    }else{
      queue* del=temp->next;
      temp->next=del->next;
      delete del;
      count--;
    }
  }
  // Need to read this
  void loadServingFromFile(const string &filename) {
    ifstream in(filename);
    if (!in) {
        cout << "Serving file not found!" << endl;
        return;
    }
    string line;
    int id;
    string name, pick, drop, vehicle;
    while (getline(in, line)) {
        if (line.empty()) continue;
        if (line.find("ID:") != string::npos)
            id = stoi(line.substr(line.find(":") + 1));
        else if (line.find("Name:") != string::npos)
            name = line.substr(line.find(":") + 1);
        else if (line.find("Pick up Location:") != string::npos)
            pick = line.substr(line.find(":") + 1);
        else if (line.find("Drop Location:") != string::npos)
            drop = line.substr(line.find(":") + 1);
        else if (line.find("Vehicle Type:") != string::npos) {
            vehicle = line.substr(line.find(":") + 1);
            // Trim spaces
            auto trim = [](string &s) {
                s.erase(0, s.find_first_not_of(" \t"));
                s.erase(s.find_last_not_of(" \t") + 1);
            };
            trim(name); trim(pick); trim(drop); trim(vehicle);
            // Add to queue after reading all fields
            add(id, name, pick, drop, vehicle);
            // Reset variables for next entry
            id = 0; name = pick = drop = vehicle = "";
        }
    }
    in.close();
}
void saveServingToFile(const string &filename) {
    ofstream out(filename);
    queue* temp = head;
    while(temp != nullptr) {
        out << "ID: " << temp->ID << endl;
        out << "Name: " << temp->name << endl;
        out << "Pick up Location: " << temp->pick_location << endl;
        out << "Drop Location: " << temp->drop_location << endl;
        out << "Vehicle Type: " << temp->Status << endl;
        out << endl;
        temp = temp->next;
    }
    out.close();
}
void saveToFile(const string &filename) {
    ofstream out(filename); // overwrite file so head entries are removed
    if (!out) {
        cout << "Unable to open " << filename << " for writing\n";
        return;
    }
    queue* temp = head;
    while (temp) {
        out << "ID: " << temp->ID << endl;
        out << "Name: " << temp->name << endl;
        out << "Pick up Location: " << temp->pick_location << endl;
        out << "Drop Location: " << temp->drop_location << endl;
        out << "Vehicle Type: " << temp->Status << endl;
        // optional separator
        out << "-----" << endl;
        temp = temp->next;
    }
    out.close();
}
// Need to read this
  void disp(){
    queue* temp=head;
    while(temp!=nullptr){
      cout<<"ID: "<<temp->ID<<"\t"<<"Name: "<<temp->name<<"\t"<<"Pick_up Loaction: "<<temp->pick_location<<"\t"<<"Drop Location: "<<temp->drop_location<<"\t"<<
      "Status: "<<temp->Status<<endl;
      temp=temp->next;
    }
  }
};
