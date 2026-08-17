#pragma once
#include<iostream>
#include<fstream>
#include<tuple>
using namespace std;

class node{
  public:
  int license;
  string name;
  int unique;
  node* next=nullptr;
  node(int license,string name,int unique){
    this->license=license;
    this->name=name;
    this->unique=unique;
  }
};
class Drivers{
  public:
  node* head=nullptr;
  node* tail=nullptr;
  int count=0;
  void add(int license,string name,int unique){
    node* n=new node(license,name,unique);
    if(head==nullptr){
      head=tail=n;
    }else{
      tail->next=n;
      tail=n;
    }
    count++;
  }
 tuple<int,string,int> delnode(int license){
    if(head==nullptr){
      cout<<"Empty list"<<endl;
      return {-1,"",-1};
    }else if(head->license==license){
      node* temp=head;
      auto info=make_tuple(head->license,head->name,head->unique);
      head=temp->next;
      delete temp;
      count--;
      return info;
    }else{
      node* temp=head;
      while(temp!=nullptr && temp->next->license!=license){
        temp=temp->next;
      }
      node* del=temp->next;
      auto info=make_tuple(del->license,del->name,del->unique);
      temp->next=del->next;
      delete del;
      count--;
      return info;
    }
  }
  // Need to Read this code
 void loadDriversFromFile(const string &filename){
    ifstream in(filename);
    if (!in){
        // no file yet; that's okay
        return;
    }
    string line;
    while (getline(in, line)){
        if (line.empty() || line.find("License:") == string::npos) continue;

        size_t pos1 = line.find("License:");
        size_t pos2 = line.find("Name:");
        // accept either "Password:" or "Unique id:" (robust)
        size_t pos3 = line.find("Password:");
        if (pos3 == string::npos) pos3 = line.find("Unique id:");

        // safely parse license
        int license = 0;
        string name;
        int unique = 0;

        if (pos1 != string::npos && pos2 != string::npos) {
            string slicense = line.substr(pos1 + 8, pos2 - (pos1 + 8));
            slicense.erase(0, slicense.find_first_not_of(" \t"));
            slicense.erase(slicense.find_last_not_of(" \t") + 1);
            try { license = stoi(slicense); } catch(...) { license = 0; }
        }

        if (pos2 != string::npos) {
            if (pos3 != string::npos) {
                name = line.substr(pos2 + 5, pos3 - (pos2 + 5));
            } else {
                name = line.substr(pos2 + 5);
            }
            name.erase(0, name.find_first_not_of(" \t"));
            name.erase(name.find_last_not_of(" \t") + 1);
        }

        if (pos3 != string::npos) {
            string sUnique = line.substr(pos3 + (string("Password:").size()));
            sUnique.erase(0, sUnique.find_first_not_of(" \t"));
            sUnique.erase(sUnique.find_last_not_of(" \t") + 1);
            try { unique = stoi(sUnique); } catch(...) { unique = 0; }
        }

        add(license, name, unique);
    }
    in.close();
}
void saveDriversToFile(const string &filename) {
    ofstream out(filename);
    node* temp = head;
    while(temp != nullptr) {
        out << "License: " << temp->license
            << " Name: " << temp->name
            << " Password: " << temp->unique << endl;
        temp = temp->next;
    }
    out.close();
}
// Need to Read this code
tuple<int,string,int> getDriverInfo(int license){
    node* temp=head;
    while(temp){
        if(temp->license==license){
            return make_tuple(temp->license,temp->name,temp->unique);
        }
        temp=temp->next;
    }
    return make_tuple(-1,string(""),-1);
}
int search(int i){
    if(i<0){
      cout<<"Invalid Id"<<endl;
      return -1;
    }else{
      node* temp=head;
      while(temp!=nullptr){
        if(temp->license==i){
          return i;
        }else{
           temp=temp->next;
        }
      }
      return -1;
    }
  }
  int unique(int d){
    if(d<0){
      cout<<"Invalid id"<<endl;
      return -1;
    }else{
      node* temp=head;
      while(temp!=nullptr){
        if(temp->unique==d){
          return d;
        }else{
          temp=temp->next;
        }
      }
      return -1;
    }
  }
  void disp(){
    node* temp=head;
    while(temp!=nullptr){
      cout<<"Licesnse No: "<<temp->license<<"\t"<<" Driver Name: "<<temp->name<<endl;
      temp=temp->next;
    }
  }
};
