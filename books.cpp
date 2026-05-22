#include<iostream>
#include<string>
#include<math.h>
#include<list>
using namespace std;
class Book;
class Library;
class BorrowerRecord;

// KHỞI TẠO CLASS BOOK
class Book {
    private:
    string Number;
    string Author;
    string Title;
    BorrowerRecord *Borrower;
    public:
    // constructor
    Book();
    Book(string Number , string Author , string Title);
    // set
    void set_Number(string number);
    void set_Author(string Author);
    void set_Title(string Title);
    //get
    string get_Number();
    string get_Author();
    string get_Title();
    //display()
    void display();
    // BOOK <-> BORROWER
    BorrowerRecord* get_Borrower();
    void attachBorrower (BorrowerRecord* borrower);
    void dettachBorrower ();
};


// KHỞI TẠO CLASS LIBRARY
class Library {
    private:
    string Name;
    list <Book*> stock;
    list <BorrowerRecord*> Borrowers;
    public:
    // constructor
    Library();
    Library(string Name);
    // set
    void set_Name(string Name);
    // get
     string get_Name();
     // display()
     void display();
     // librrary->book
     list <Book*> get_stock();
     void addOneBook (Book* Book);
     void display_books();
     // library<->borrower
     list <BorrowerRecord*> get_Borrowers();
     void RegisterOneborrower(BorrowerRecord* borrower);

     void displayBookAvailableForLoan();
     void displayBookOnLoan();
     void lendOneBook (string catalougeNumber, string borrowerName);
     void returnOneBook(string catalougeNumber);
};



// KHỞI TẠO CLASS BORROWERS
 class BorrowerRecord{
    private:
    string Name;
    list <Book*> stock;
    public:
    BorrowerRecord();
    BorrowerRecord(string Name);
    // set
    void set_Name(string Name);
    // get
    string get_Name();
    // display()
    void display();
    // borrower<->book
     list <Book*> get_stock();
     void attachBook (Book* Book);
     void dettachBook (Book* Book);
 };



 // CÁC HÀM CLASS BOOK
 Book::Book(){
    this->set_Number("000");
    this->set_Author("none");
    this->set_Title("none");
    this->Borrower=nullptr;
 };

 Book::Book(string Name , string Author , string Title){
    this->set_Number(Name);
    this->set_Author(Author);
    this->set_Title(Title);
    this->Borrower=nullptr;
 }

void Book::set_Number(string Number){
    this->Number=Number;
};

void Book::set_Author(string Author){
    this->Author=Author;
};

void Book::set_Title(string Title){
    this->Title=Title;
};

string Book::get_Number(){
    return this->Number;
};

string Book::get_Author(){
    return this->Author;
};

string Book::get_Title(){
    return this->Title;
};

void Book::display(){
        cout<<"number="<<this->get_Number()<<endl;
        cout<<"authorr:"<<this->get_Author()<<endl;
        cout<<"title:"<<this->get_Title()<<endl;
}


// CAC HAM TRONG LIBRARY
Library::Library(){
    this->set_Name("none");
};

Library::Library(string Name){
    this->set_Name(Name);
};

void Library::set_Name(string Name){
    this->Name=Name;
};

string Library::get_Name(){
    return this->Name;
};


// CAC HAM TRONG BORROWER
BorrowerRecord::BorrowerRecord(){
    this->set_Name("none");
};

BorrowerRecord::BorrowerRecord(string Name){
    this->set_Name(Name);
};

void BorrowerRecord::set_Name(string Name){
    this->Name=Name;
};

string BorrowerRecord::get_Name(){
    return this->Name;
};

void BorrowerRecord::display(){
    cout<<"name borrower:"<<this->get_Name()<<endl;
};
// ACCESS METHOD

// BOOK <-> BORROWER
BorrowerRecord* Book::get_Borrower(){
    return this->Borrower;
};

void Book::attachBorrower (BorrowerRecord* borrower){
    this->Borrower=borrower;
    borrower->attachBook(this);
}

void Book::dettachBorrower (){
    if (this->get_Borrower()!=nullptr){
        this->get_Borrower()->dettachBook(this);
        this->Borrower=nullptr;
    }
}

// borrower<->book
list <Book*> BorrowerRecord:: get_stock(){
    return this->stock;
};

void  BorrowerRecord::attachBook(Book* Book){
    this->stock.push_back(Book);
    
}

void BorrowerRecord::dettachBook (Book* Book){
    this->stock.remove(Book);
}


// library->book
list <Book*> Library::get_stock(){
    return this->stock;
};

void Library::addOneBook (Book* Book){
    this->stock.push_back(Book);
};

void Library::display_books(){
    for (auto i : this->stock){
        i->display();
    }
};

void Library::displayBookAvailableForLoan(){
    for ( auto i : this->stock){
        if (i->get_Borrower()==nullptr){
            i->display();
        }
    }
}
void Library::displayBookOnLoan(){
    for ( auto i : this->stock){
        if (i->get_Borrower()!=nullptr){
            i->display();
        }
    }

}
// library<->borrower
list <BorrowerRecord*> Library::get_Borrowers(){
    return this->Borrowers;
}
 void Library::RegisterOneborrower(BorrowerRecord* borrower){
    this->Borrowers.push_back(borrower);
 }

void Library::lendOneBook (string catalougeNumber, string borrowerName){
    Book* bk=nullptr;
    BorrowerRecord* br=nullptr;

    for (auto i : this->stock){
        if (i->get_Number()==catalougeNumber) bk=i;
    }
    if (bk==nullptr){
        cout<<"khong tim thay sach "<<endl;
        return;
    }

    for (auto i : this->Borrowers){
        if (i->get_Name()==borrowerName) br=i;
    }
    if (br==nullptr){
        cout<<"khong tim ten nguoi dang ky"<<endl;
        return;
    }

    if (bk->get_Borrower()!=nullptr){
        cout<<"sach da co nguoi muon"<<endl;
        return;
    }
    else{
        bk->attachBorrower(br);
    }
}

void Library :: returnOneBook(string catalougeNumber){
    Book* bk=nullptr;
    BorrowerRecord* br=nullptr;

    for (auto i : this->stock){
        if (i->get_Number()==catalougeNumber) bk=i;
    }
    if (bk==nullptr){
        cout<<"khong tim thay sach "<<endl;
        return;
    }
    if (bk->get_Borrower()==nullptr){
        cout<<"borrower not found"<<endl;
        return;
    }
    bk->dettachBorrower();
}
int main() {
    // 1. Khởi tạo Thư viện
    Library myLibrary("Thu Vien Thanh Pho");
    cout << "=== CHAO MUNG DEN VAY " << myLibrary.get_Name() << " ===" << endl;

    // 2. Mua sách về thư viện (Dùng toán tử 'new' để tạo con trỏ)
    Book* b1 = new Book("001", "Nam Cao", "Chi Pheo");
    Book* b2 = new Book("002", "Vu Trong Phung", "So Do");
    Book* b3 = new Book("003", "Ngo Tat To", "Tat Den");
    
    myLibrary.addOneBook(b1);
    myLibrary.addOneBook(b2);
    myLibrary.addOneBook(b3);

    // 3. Đăng ký thẻ thành viên
    BorrowerRecord* p1 = new BorrowerRecord("Nguyen Van A");
    BorrowerRecord* p2 = new BorrowerRecord("Tran Thi B");
    
    myLibrary.RegisterOneborrower(p1);
    myLibrary.RegisterOneborrower(p2);

    // ==========================================
    // KỊCH BẢN TEST NGHIỆP VỤ
    // ==========================================

    cout << "\n[1] TRANG THAI BAN DAU:" << endl;
    myLibrary.displayBookAvailableForLoan();

    cout << "\n[2] NGUYEN VAN A DEN MUON SACH '001':" << endl;
    myLibrary.lendOneBook("001", "Nguyen Van A");
    
    cout << "\n[3] KIEM TRA LAI THU VIEN SAU KHI MUON:" << endl;
    myLibrary.displayBookAvailableForLoan();
    myLibrary.displayBookOnLoan();

    cout << "\n[4] NGUYEN VAN A DEN TRA SACH '001':" << endl;
    myLibrary.returnOneBook("001");
    
    cout << "\n[5] KIEM TRA LAI THU VIEN SAU KHI TRA:" << endl;
    myLibrary.displayBookAvailableForLoan();

    return 0;
}