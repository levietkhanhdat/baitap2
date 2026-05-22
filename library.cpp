#include <string>
#include <iostream>
#include<list>
using namespace std;
class Book;
class Library;
class BorrowerRecord;

class Book {
    // attributes: number, author, title
    private:
    string number;
    string author;
    string title;
    BorrowerRecord* borrower; // lưu địa chỉ người mượn sách
    //default constructor
    public:
    Book ();
    // constructors
    Book (string number , string author , string title);
    //setters
    void set_number(string number);
    void set_author(string author);
    void set_title(string title);
    // getters
    string get_number();
    string get_author();
    string get_title();
    // display book
    void display();
    ////Book <-> borrower
    BorrowerRecord* getBorrower();
    void attachBorrower(BorrowerRecord* br);
    void dettachBorrower(BorrowerRecord* br);
};




class Library {
private:
    string name;
    list <Book*> stock;
    list <BorrowerRecord*> borrowers;
public:
    // default constructor
    Library();
    // Constructor
    Library(string name);
    // Access Methods
    void set_name(string name);
    string get_name();
    // setter book
    void addonebook (Book* book);
    // getter
    list <Book*> getstock();
    // display
    void display_book();
    void display_borrower();
    void displayBookAvailableForLoan();
    void displayBookOnLoan();
    // ĐĂNG KÝ MƯỢN SÁCH 
    BorrowerRecord*  RegisterOneBorrower(string name);
    // getter Borrower
    list <BorrowerRecord*> getBorrower();
    ~Library();
    void  lendOneBook (string catalougeNumber, string borrowerName);
};



class BorrowerRecord {
    string name;
    list<Book*> books;
    public:
    // default constructor
    BorrowerRecord();
    // Constructor
    BorrowerRecord(string name);
    // Access Methods
    void set_name(string name);
    string get_name();
    void attachBook(Book* book);
    void display();
    void dettach(Book *book);
};

//default constructor
Book::Book (){
        this->set_number("000");
        this->set_author("none");
        this->set_title("none");
        this->borrower = nullptr;
};
 // constructors
Book::Book(string number , string author , string title){
        this->set_number(number);
        this->set_author(author);
        this->set_title(title);
        this->borrower = nullptr;
}
    //setters
void Book::set_number(string number){
        this->number=number;
}
void Book::set_author(string author){
        this->author=author;
}
void Book::set_title(string title){
        this->title=title;
}


// getter
string Book:: get_number(){
        return this->number;
}
string Book:: get_author(){
        return this->author;
}
string Book:: get_title(){
        return this->title;
}
// Additional Method:
void Book::attachBorrower(BorrowerRecord* br){
    this->borrower=br;
    br->attachBook(this);
}
void Book::dettachBorrower(BorrowerRecord* br){
    if (this->borrower != nullptr) {
        this->borrower->dettach(this);
        this->borrower = nullptr; 
    }
}
// trả về địa chỉ người mượn sách này
BorrowerRecord* Book::getBorrower(){
    return this->borrower;
 }
// display book
void Book::display(){
        cout<<"number="<<this->get_number()<<endl;
        cout<<"authorr:"<<this->get_author()<<endl;
        cout<<"title:"<<this->get_title()<<endl;
         if (this->borrower != nullptr) {
        cout << "Nguoi muon la: "<< this->getBorrower()->get_name() << endl;
    } else {
        cout << "Sach chua duoc muon" << endl;
    }
}




// default constructor
Library::Library(){
        this->set_name("none");
}
    // Constructor
Library::Library(string name){
        this->set_name(name);
}
    // Access Methods
void Library::set_name(string name){
        this->name=name;
}
 string Library:: get_name(){
        return this->name;
 }
    // setter book
void Library::addonebook (Book* book){
        this->stock.push_back(book);
}
    // getter
list <Book*> Library:: getstock(){
        return this->stock;
}
    // display
void Library:: display_book(){
        cout<<"ten thu vien : "<<this->get_name()<<endl;
        for ( auto i : this->stock){
            i->display();
        }
}
void Library::displayBookAvailableForLoan(){
    for (auto i : this->stock){
        if (i->getBorrower()==nullptr) i->display();
    }
}

void Library::displayBookOnLoan(){
    for (auto i: this->stock){
        if (i->getBorrower()!=nullptr) i->display(); 
    }
}

void Library:: display_borrower(){
        cout<<"ten thu vien : "<<this->get_name()<<endl;
        for ( auto i : this->borrowers){
            i->display();
        }
}

BorrowerRecord* Library::RegisterOneBorrower(string name){
     BorrowerRecord* br=new BorrowerRecord(name);
     this->borrowers.push_back(br);
     return br;
}

list <BorrowerRecord*> Library :: getBorrower(){
    return this->borrowers;
}

 void Library::lendOneBook (string catalougeNumber, string borrowerName){
    Book* book=nullptr;
    BorrowerRecord* borrow=nullptr;
     for (auto i : this->stock){
        if (i->get_number()==catalougeNumber){
            book=i;
        }
     }
     if (book==nullptr) {
        cout<<"book not found";
        return;
     }

     for (auto i: this->borrowers){
        if (i->get_name()==borrowerName){
            borrow=i;
        }
     }
     if (borrow==nullptr) {
        cout<<"borrower not found";
        return;
     }

      if (book->getBorrower()!=nullptr) {
        cout<<"book on loan";
        return ;
      }
      else book->attachBorrower(borrow);
    
 }
Library::~Library() {
    // Giải phóng danh mục sách
    for (auto i : this->stock) {
        delete i;
    }
    // Giải phóng danh sách người mượn
    for (auto k : this->borrowers) {
        delete k; 
    }
}

BorrowerRecord::BorrowerRecord(){
        this->set_name("none");
}
    // Constructor
BorrowerRecord::BorrowerRecord(string name){
        this->set_name(name);
}
    // Access Methods
void BorrowerRecord::set_name(string name){
        this->name=name;
}
string BorrowerRecord::get_name(){
        return this->name;
}
void BorrowerRecord::attachBook(Book* book){
    this->books.push_back(book);
}
void BorrowerRecord::display(){
    cout<<"borrower:"<<this->get_name();
}
void BorrowerRecord::dettach(Book* book){
     this->books.remove(book);
}
int main() {

    
    Library hcmus("Thu vien KHTN");
    hcmus.addonebook(new Book("S01", "Aso Haro", "Alice in Borderland"));
    hcmus.addonebook(new Book("S02", "Fujiko", "Doraemon"));
    hcmus.addonebook(new Book("S03", "Nam Cao", "Chi Pheo"));

    hcmus.RegisterOneBorrower("Khanh Dat");
    hcmus.RegisterOneBorrower("Hoang Nam");


    cout << "\n[Test 1] Muon sach hop le (S01 cho Khanh Dat):" << endl;
    hcmus.lendOneBook("S01", "Khanh Dat");
    // Kiểm tra kết quả


    cout << "\n[Test 2] Muon sach sai ID (S99):" << endl;
    hcmus.lendOneBook("S99", "Khanh Dat"); 

    // CASE 3: Người mượn không tồn tại (Sai tên)
    cout << "\n[Test 3] Nguoi muon sai ten (Ai Do):" << endl;
    hcmus.lendOneBook("S02", "Ai Do"); 

    // CASE 4: Sách đã có người khác mượn
    cout << "\n[Test 4] Muon sach dang bi muon (S01 cho Hoang Nam):" << endl;
    hcmus.lendOneBook("S01", "Hoang Nam"); 

    hcmus.displayBookAvailableForLoan();
    hcmus.displayBookOnLoan();

    return 0;

    

}

// delete chỉ áp dụng cho liên kết 2 chiều
