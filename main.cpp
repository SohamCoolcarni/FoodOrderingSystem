#include<iostream>
using namespace std;

class User {
    private:
    bool islogin;
    int Userid;
    string name,email,password;
    string phone;
    public:
    User(int id,string nm,string em,string pass,string ph) {
        Userid=id;
        name=nm;
        email=em;
        password=pass;
        phone=ph;
        cout<<"User obj created\n";
    }
    void get() {
        if(islogin) {
            cout<<"User ID: "<<Userid<<endl;
            cout<<"Name: "<<name<<endl;
            cout<<"Email: "<<email<<endl;
            cout<<"Phone: "<<phone<<endl;
        }
        else {
            cout<<"User is not logged in\n";
        }
    }
    void login() {
        int check;
        string pass;
        cout<<"Enter the User id and password\n"<<"Id: ";
        cin>>check;
        cout<<"Password: ";
        cin>>pass;
        if(check==Userid && pass==password) {
            cout<<"Login successful\n";
            islogin=true;
        }
        else {
            cout<<"Invalid credentials. Please try again.\n";
        }
    }
    void logout() {
        cout<<"Logout successful\n";
        islogin=false;
    }
    void updateProfile() {
        if(!islogin) {
            cout<<"Please login to update your profile\n";
        }
        else {
            cout<<"Current profile information:\n";
            get();
            cout<<"Enter new name, email, password and phone number in this order:\n";
            cin>>name>>email>>password>>phone;
            cout<<"Profile updated successfully\n";
        }
    }
};

class Customer: public User {
    private:
    string address;
    string cart[100]; // Assuming a maximum of 100 items in the cart
    string orderHistory[100]; // Assuming a maximum of 100 past orders
    public:
    Customer(int id,string nm,string em,string pass,string ph,string add):User(id,nm,em,pass,ph) {
        address=add;
        cout<<"Customer obj created\n";
    }
};


class MenuItem {
    private:
    int Itemid;
    string name;
    float price;
    string catagory;
    bool isAvailable;
    public:
    MenuItem() {//initializing as default constructor as restaurant needs to create menu items without details and then update them later
        Itemid=0;
        name="";
        price=0;
        catagory="";
        isAvailable=false;
    }
    void enterItemDetails(int item,string in,string cat,float p,bool a) {
        Itemid=item;
        name=in;
        catagory=cat;
        price=p;
        isAvailable=a;
        cout<<"MenuItem obj created\n";
    }
    void get() {
        cout<<"Itemid: "<<Itemid<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Catagory: "<<catagory<<endl;
        cout<<"Price: "<<price<<endl;
        cout<<"Available: "<<isAvailable<<endl;
    }
    friend class Restaurant; // Allow Restaurant class to access private members of MenuItem
};



class Restaurant {
    private:
    int Restaurantid;
    string name,address;
    float rating;
    MenuItem menu[100]; // Assuming a maximum of 100 menu items
    int menuCount;
    bool isOpen;
    public:
    Restaurant(int id,string nm,string add,float ra,int n,bool y) {
        Restaurantid=id;
        name=nm;
        address=add;
        rating=ra;
        menuCount=n;
        isOpen=y;
        cout<<"Restaurant obj created\n";
    }
    void addMenuItem(MenuItem m) {
        for(int i=0;i<menuCount;i++) {
            if(menu[i].Itemid==m.Itemid) {
                cout<<"Item with this id already exists. Please enter a unique item id.\n";
                return;
            }
            else if(menu[i].Itemid==0) { // Assuming 0 indicates an empty slot in the menu array
                menu[i]=m;cout<<"Menu item added successfully."<<endl;
                break;
            }
        }
        
    }
    void displayMenu() {
        cout<<"Menu for Restaurant: "<<name<<"\n";
        for(int i=0;i<menuCount;i++) {
            menu[i].get();
        }
    }
};