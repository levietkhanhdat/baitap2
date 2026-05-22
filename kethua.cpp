#include<iostream>
#include<list>
#include<string>
#include<map>
using namespace std; 

class Employee;
class Programmer;
class ProjectLeader;
class SoftwareHouse;


// ===============CLASS EMPLOYEE===============

class Employee {
private:
    string payrollNumber;
    double monthlySalary;
    string name;

public:
    Employee(string payrollNumber, double monthlySalary, string name);
    
    void setPayrollNumber(string payrollNumber);
    string getPayrollNumber();
    
    void setMonthlySalary(double monthlySalary);
    double getMonthlySalary();
    
    void setName(string name);
    string getName();
    
    virtual void display();
};


//======== CLASS PROGRAMMER===============

class Programmer : public Employee {
private:
    string language;
    ProjectLeader* leader;

public:
    Programmer(string payrollNumber, double monthlySalary, string name, string language);
    
    void setLanguage(string language);
    string getLanguage();

    virtual void display() override;

    void attachleader(ProjectLeader* leader);
    void detachleader();
};


// ==========CLASS SOFTWARE HOUSE==============

class SoftwareHouse {
private:
    string name;
    map <string, Employee*> staffs; 
public:
    SoftwareHouse(string name);
    
    void setName(string name);
    string getName();
    
    map <string,Employee*> getstaffs();
    void addstaff(Employee* st);
    void removestaff(Employee*  st);

    void display();
    void display_employees();
   
};

//========= CLASS PROJECTLEADER===============
class ProjectLeader : public Programmer{
    private:
    map  <string , Programmer*> programmers;
    public:
    ProjectLeader(string payrollNumber, double monthlySalary, string name, string language);
    map <string , Programmer*>  getprogrammers ();
    void attachProgrammers (Programmer* pr);
    void detachProgrammers(Programmer* pr);
    void display_programmers();
     void display() override;
};


//============ ĐỊNH NGHĨA HÀM CHO EMPLOYEE=================

Employee::Employee(string payrollNumber, double monthlySalary, string name) {
    this->setPayrollNumber(payrollNumber);
    this->setMonthlySalary(monthlySalary);
    this->setName(name);
}

void Employee::setPayrollNumber(string payrollNumber) {
    this->payrollNumber = payrollNumber;
}

string Employee::getPayrollNumber() {
    return this->payrollNumber;
}

void Employee::setMonthlySalary(double monthlySalary) {
    this->monthlySalary = monthlySalary;
}

double Employee::getMonthlySalary() {
    return this->monthlySalary;
}

void Employee::setName(string name) {
    this->name = name;
}

string Employee::getName() {
    return this->name;
}

void Employee::display() {
    cout << "Payroll Number : " << this->getPayrollNumber() << endl;
    cout << "Monthly Salary : " << this->getMonthlySalary() << endl;
    cout << "Name           : " << this->getName() << endl;
}


// ==========ĐỊNH NGHĨA HÀM CHO PROGRAMMER=============

Programmer::Programmer(string payrollNumber, double monthlySalary, string name, string language) 
    : Employee(payrollNumber, monthlySalary, name) {
    this->setLanguage(language);
    this->leader=nullptr;
}

void Programmer::setLanguage(string language) {
    this->language = language;
}

string Programmer::getLanguage() {
    return this->language;
}

void Programmer::display() {
    Employee::display(); 
    cout << "Language: " << this->getLanguage() << endl;
}

 void Programmer::attachleader(ProjectLeader* leader){
      this->leader=leader;
      leader->attachProgrammers(this);
 }


void Programmer::detachleader(){
      if(this->leader!=nullptr){
        this->leader->detachProgrammers(this);
        this->leader=nullptr;
      }
}


// ========PROJECTLEADER==========
 ProjectLeader::ProjectLeader(string payrollNumber, double monthlySalary, string name, string language)
       :Programmer(payrollNumber,monthlySalary,name,language){
        return;
       }

map <string,Programmer*> ProjectLeader:: getprogrammers (){
    return this->programmers ;
}

 void ProjectLeader::attachProgrammers (Programmer* pr){
    string id = pr->getPayrollNumber();
      if (this->programmers.find(id)!=this->programmers.end()){
        cout <<"Programmer :"<<pr->getName()<<" (ID :)"<<id<<endl;
      }
      this->programmers[id]=pr;
      cout <<"them thanh vien cho nhom "<<this->getName()<<"thanh cong"<<endl;
 }

 void ProjectLeader::detachProgrammers (Programmer* pr){
    string id = pr -> getPayrollNumber();
    if (this->programmers.find(id) != this->programmers.end()){
        programmers.erase(id);
    }
      return;
 }

 void ProjectLeader :: display_programmers(){
   cout << "Team members:\n";
        if(this->programmers.empty()){
            cout << "Empty team\n";
            return;
        }
        for(auto [id, p] : this->programmers){
            cout<< p->getName() << "(Id: " << id <<") \n";
        }
 }
 void ProjectLeader::display(){
    cout << "[Project Leader]\n";
    Programmer::display();
    this->display_programmers();
 }

//========CLASS SOFTWARE HOUSE========
SoftwareHouse::SoftwareHouse(string name) {
    this->setName(name);
}

void SoftwareHouse::setName(string name) {
    this->name = name;
}

string SoftwareHouse::getName() {
    return this->name;
}

map <string,Employee*> SoftwareHouse::getstaffs(){
    return this->staffs;
}

void SoftwareHouse::addstaff (Employee* st){
    string id = st->getPayrollNumber();
    if (this->staffs.find(id)!=this->staffs.end()){
        cout <<"Programmer :"<<st->getName()<<" (ID :)"<<id<<endl;
      }
      this->staffs[id]=st;
      cout <<"them thanh vien cho sofeware "<<this->getName()<<"thanh cong"<<endl;
}

void SoftwareHouse::removestaff (Employee* st){
    string id = st->getPayrollNumber();
    if (this->staffs.find(id)!=this->staffs.end()){
        staffs.erase(id);
      }
    return;
   
}

void SoftwareHouse::display_employees(){
    if (this->staffs.empty()){
        cout << "Không có nhân viên nào"<<endl;
        return;
    }
    int count=0;
    for (auto [i,p] : this->staffs){
        cout<<"nhân viên thứ "<< count+1<<endl;
        ++count;
        p->display();
    }
}


void SoftwareHouse::display (){
    cout<<"Name :"<<this->getName()<<endl;
    this->display_employees();
}




int main() {
 Programmer a("001", 1000, "John", "C++");
    Programmer b("002", 2000, "Jane", "Java");
    ProjectLeader c("004", 4000, "Jack", "Python");

    c.attachProgrammers(&a);
    c.attachProgrammers(&b);

    SoftwareHouse d("Facebook");
    d.addstaff(&a);
    d.addstaff(&b);
    d.addstaff(&c);
    d.display();

    return 0;
}