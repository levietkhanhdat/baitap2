#include<iostream>
#include<string>
using namespace std;
class account{
    private:
    string number;
    int balance;
    public:
    //constructor
    account(string number, int balance);
    //setter
    void set_number(string number);
    void set_balance(int balance);
    //getter
    string get_number();
    int get_balance();
    // credit
    void credit(int amount);
    // debit
    void debit(int amount);
    //display
    void display();
};
account::account(string number, int balance){
    this->set_number(number);
    this->set_balance(balance);
}
void account::set_number(string number){
    this->number=number;
}
void account::set_balance(int balance){
    this->balance=balance;
}
string account::get_number(){
    return this->number;
}
int account::get_balance(){
    return this->balance;
}
void account::credit(int amount){
    this->balance-=amount;
}
void account::debit(int amount){
    this->balance+=amount;
}
void account::display(){
    cout<<"so tai khoan:"<<get_number()<<endl;
    cout<<"so tien:"<<get_balance()<<endl;
}
int main(){
    string a="KD";
    account khanhdat(a,200000);
    khanhdat.credit(10000);
    khanhdat.display();
}