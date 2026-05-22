#include<iostream>
#include<string>
using namespace std;
class Person{
    private:
    string name;
    string DateOfBirth;
    public:
    //CONSTRUCTOR
    Person(string name , string DateOfBirth);
    //SETTER
    void set_name(string name);
    void set_DateOfBirth(string DateOfBirth);
    //GETTER
    string get_name();
    string get_DateOfBirth();
    //DISPLAY
    void display();
    //Get age
    int get_age();
};

Person::Person(string name, string DateOfBirth){
    this->set_name(name);
    this->set_DateOfBirth(DateOfBirth);
}
string Person::get_name(){
    return this->name;
}
string Person::get_DateOfBirth(){
    return this->DateOfBirth;
}
void Person::set_name(string name){
    this->name=name;
}
void Person::set_DateOfBirth(string DateOfBirth){
    this->DateOfBirth=DateOfBirth;
}
int Person::get_age(){
    string a=this->get_DateOfBirth().substr(this->get_DateOfBirth().length()-4);
    return 2026-stoi(a);
}
void Person::display(){
    cout<<"ten la :"<<this->get_name()<<endl;
    cout<<"ngay sinh:"<<this->get_DateOfBirth()<<endl;
    cout<<"tuoi= "<<this->get_age()<<endl;
}


class Library {
private:
    string name;
public:
    // default constructor
    Library(){
        this->set_name("none");
    }
    // Constructor
    Library(string name){
        this->set_name(name);
    }
    // Access Methods
    void set_name(string name){
        this->name=name;
    }
    string get_name(){
        return this->name;
    }
    // Display
    void display(){
        cout<<"ten thu vien:"<<this->get_name()<<endl;
    }
};

int main(){
    Person a("an","20/1/2006");
    a.set_name("tu");
    a.display();
}