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
    MenuItem() {
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


    void displayDetails() {
        get();   // reuse your existing function
    }

    void updatePrice(float newPrice) {
        price = newPrice;
        cout<<"Price updated successfully\n";
    }

    void toggleAvailability() {
        isAvailable = !isAvailable;
        cout<<"Availability changed\n";
    }

    void applyDiscount(float percent) {
        price = price - (price * percent / 100);
        cout<<"Discount applied. New price: "<<price<<endl;
    }

    friend class Restaurant;
    friend class Cart;
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

class Cart {
private:
    MenuItem items[100];
    int quantity[100];   // to store quantity of each item
    int count;

public:
    Cart() {
        count = 0;
    }

    void addItem(MenuItem m) {
        // check if item already exists
        for(int i=0;i<count;i++) {
            if(items[i].Itemid == m.Itemid) {
                quantity[i]++;
                cout<<"Item quantity increased\n";
                return;
            }
        }

        items[count] = m;
        quantity[count] = 1;
        count++;
        cout<<"Item added to cart\n";
    }

    void removeItem(int id) {
        for(int i=0;i<count;i++) {
            if(items[i].Itemid == id) {
                for(int j=i;j<count-1;j++) {
                    items[j] = items[j+1];
                    quantity[j] = quantity[j+1];
                }
                count--;
                cout<<"Item removed from cart\n";
                return;
            }
        }
        cout<<"Item not found in cart\n";
    }

    void updateQuantity(int id, int q) {
        for(int i=0;i<count;i++) {
            if(items[i].Itemid == id) {
                quantity[i] = q;
                cout<<"Quantity updated\n";
                return;
            }
        }
        cout<<"Item not found in cart\n";
    }

    float calculateTotal() {
        float total = 0;
        for(int i=0;i<count;i++) {
            total += items[i].price * quantity[i];
        }
        return total;
    }

    void clearCart() {
        count = 0;
        cout<<"Cart cleared\n";
    }

    void displayCart() {
        cout<<"Cart Items:\n";
        for(int i=0;i<count;i++) {
            items[i].get();
            cout<<"Quantity: "<<quantity[i]<<endl;
        }
        cout<<"Total Price: "<<calculateTotal()<<endl;
    }
};

class Order {
private:
    int orderId;
    string status;
    Cart cart;
    string deliveryPerson;
    int deliveryTime;   // in minutes

public:
    Order(int id, Cart c) {
        orderId = id;
        cart = c;
        status = "Created";
        deliveryPerson = "Not Assigned";
        deliveryTime = 0;
        cout<<"Order object created\n";
    }

    void placeOrder() {
        status = "Placed";
        cout<<"Order placed successfully\n";
    }

    void updateStatus(string s) {
        status = s;
        cout<<"Order status updated to: "<<status<<endl;
    }

    void cancelOrder() {
        status = "Cancelled";
        cout<<"Order cancelled\n";
    }

    void assignDeliveryPerson(string name) {
        deliveryPerson = name;
        cout<<"Delivery person assigned: "<<deliveryPerson<<endl;
    }

    void calculateDeliveryTime() {
        deliveryTime = 30;   // fixed for now
        cout<<"Estimated delivery time: "<<deliveryTime<<" minutes\n";
    }

    void displayOrderDetails() {
        cout<<"Order ID: "<<orderId<<endl;
        cout<<"Status: "<<status<<endl;
        cout<<"Delivery Person: "<<deliveryPerson<<endl;
        cout<<"Delivery Time: "<<deliveryTime<<" minutes"<<endl;
        cart.displayCart();
    }
};
