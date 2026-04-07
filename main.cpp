#include<iostream>
#include<string>
using namespace std;

class MenuItem;
class Restaurant;
class Cart;
class Order;
class Customer;
class DeliveryPerson;
class Owner;

class User {
    private:
    bool islogin;
    int Userid;
    string name,email,password;
    string phone;
    public:
    User() : islogin(false), Userid(0), name(""), email(""), password(""), phone("") {}
    User(int id,string nm,string em,string pass,string ph)
        : islogin(false), Userid(id), name(nm), email(em), password(pass), phone(ph) {
        cout<<"User obj created" << endl;
    }
    void get() {
        if(islogin) {
            cout<<"User ID: "<<Userid<<endl;
            cout<<"Name: "<<name<<endl;
            cout<<"Email: "<<email<<endl;
            cout<<"Phone: "<<phone<<endl;
        }
        else {
            cout<<"User is not logged in";
        }
    }
    bool login() {
        int check;
        string pass;
        cout<<"Enter the User id and password"<<"Id: ";
        cin>>check;
        cout<<"Password: ";
        cin>>pass;
        if(check==Userid && pass==password) {
            cout<<"Login successful";
            islogin=true;
            return true;
        }
        else {
            cout<<"Invalid credentials. Please try again.";
            return false;
        }
    }
    void logout() {
        cout<<"Logout successful";
        islogin=false;
    }
    bool authenticate(string em, string pass) {
        if(email == em && password == pass) {
            islogin = true;
            return true;
        }
        return false;
    }
    void updateProfile() {
        if(!islogin) {
            cout<<"Please login to update your profile";
        }
        else {
            cout<<"Current profile information:";
            get();
            cout<<"Enter new name, email, password and phone number in this order:";
            cin>>name>>email>>password>>phone;
            cout<<"Profile updated successfully";
        }
    }
};

class MenuItem {
    private:
    int Itemid;
    string name;
    float price;
    string category;
    bool isAvailable;

    public:
    MenuItem() {
        Itemid=0;
        name="";
        price=0;
        category="";
        isAvailable=false;
    }

    void enterItemDetails(int item,string in,string cat,float p,bool a) {
        Itemid=item;
        name=in;
        category=cat;
        price=p;
        isAvailable=a;
        cout<<"MenuItem obj created" << endl;
    }

    void get() {
        cout<<"Itemid: "<<Itemid<<endl;
        cout<<"Name: "<<name<<endl;
        cout<<"Category: "<<category<<endl;
        cout<<"Price: "<<price<<endl;
        cout<<"Available: "<<isAvailable<<endl;
    }

    void updatePrice(float newPrice) {
        price = newPrice;
        cout<<"Price updated successfully";
    }

    void toggleAvailability() {
        isAvailable = !isAvailable;
        cout<<"Availability changed";
    }

    void applyDiscount(float percent) {
        price = price - (price * percent / 100);
        cout<<"Discount applied. New price: "<<price<<endl;
    }

    friend class Restaurant;
    friend class Cart;
};

class Restaurant {
    protected:
    int Restaurantid;
    string name,address;
    float rating;
    MenuItem menu[100];
    int menuCount;
    bool isOpen;

    public:
    Restaurant() : Restaurantid(0), name(""), address(""), rating(0.0), menuCount(0), isOpen(false) {}

    int getId() const { return Restaurantid; }
    string getName() const { return name; }

    Restaurant(int id,string nm,string add,float ra,int n,bool y)
        : Restaurantid(id), name(nm), address(add), rating(ra), menuCount(n), isOpen(y) {
        cout<<"Restaurant obj created" << endl;
    }

    void addMenuItem(MenuItem m) {
        for(int i=0; i<100; i++) {
            if(menu[i].Itemid == m.Itemid) {
                cout<<"Item with this id already exists. Please enter a unique item id.";
                return;
            }
            if(menu[i].Itemid == 0) {
                menu[i] = m;
                menuCount++;
                cout<<"Menu item added successfully."<<endl;
                return;
            }
        }
        cout<<"Menu is full.";
    }

    void displayMenu() {
        cout<<"Menu for Restaurant: "<<name<<endl;
        for(int i=0;i<menuCount;i++) {
            menu[i].get();
        }
    }

    void removeMenuItem(int id) {
        for(int i=0;i<menuCount;i++) {
            if(menu[i].Itemid == id) {
                for(int j=i;j<menuCount-1;j++) {
                    menu[j] = menu[j+1];
                }
                menuCount--;
                cout<<"Menu item removed";
                return;
            }
        }
        cout<<"Item not found";
    }

    void updateMenuItem(int id, float newPrice) {
        for(int i=0;i<menuCount;i++) {
            if(menu[i].Itemid == id) {
                menu[i].updatePrice(newPrice);
                return;
            }
        }
        cout<<"Item not found";
    }

    void searchMenuItem(int id) {
        for(int i=0;i<menuCount;i++) {
            if(menu[i].Itemid == id) {
                cout<<"Item found:";
                menu[i].get();
                return;
            }
        }
        cout<<"Item not found";
    }

    MenuItem* getMenuItemById(int id) {
        for(int i=0;i<menuCount;i++) {
            if(menu[i].Itemid == id) {
                return &menu[i];
            }
        }
        return nullptr;
    }

    void toggleOpen() {
        isOpen = !isOpen;
        cout<<"Restaurant is now "<<(isOpen ? "Open" : "Closed")<<endl;
    }

    float getAverageRating() {
        return rating;
    }

    string getName() const {
        return name;
    }

    friend class Customer;
    friend class Owner;
};

class Cart {
private:
    MenuItem items[100];
    int quantity[100];
    int count;

public:
    Cart() {
        count = 0;
    }

    void addItem(MenuItem m) {
        for(int i=0;i<count;i++) {
            if(items[i].Itemid == m.Itemid) {
                quantity[i]++;
                cout<<"Item quantity increased";
                return;
            }
        }
        items[count] = m;
        quantity[count] = 1;
        count++;
        cout<<"Item added to cart";
    }

    void removeItem(int id) {
        for(int i=0;i<count;i++) {
            if(items[i].Itemid == id) {
                for(int j=i;j<count-1;j++) {
                    items[j] = items[j+1];
                    quantity[j] = quantity[j+1];
                }
                count--;
                cout<<"Item removed from cart";
                return;
            }
        }
        cout<<"Item not found in cart";
    }

    void updateQuantity(int id, int q) {
        for(int i=0;i<count;i++) {
            if(items[i].Itemid == id) {
                quantity[i] = q;
                cout<<"Quantity updated";
                return;
            }
        }
        cout<<"Item not found in cart";
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
        cout<<"Cart cleared";
    }

    void displayCart() {
        cout<<"Cart Items:" << endl;
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
    int deliveryTime;

public:
    Order() : orderId(0), status("Created"), deliveryPerson("Not Assigned"), deliveryTime(0) {}

    Order(int id, const Cart &c) : orderId(id), cart(c), status("Created"), deliveryPerson("Not Assigned"), deliveryTime(0) {
        cout<<"Order object created" << endl;
    }

    int getOrderId() const {
        return orderId;
    }

    void get(int id, Cart c) {
        orderId = id;
        cart = c;
        status = "Created";
        deliveryPerson = "Not Assigned";
        deliveryTime = 0;
        cout<<"Order object created" << endl;
    }

    void placeOrder() {
        status = "Placed";
        cout<<"Order placed successfully";
    }

    void updateStatus(string s) {
        status = s;
        cout<<"Order status updated to: "<<status<<endl;
    }

    void cancelOrder() {
        status = "Cancelled";
        cout<<"Order cancelled";
    }

    void assignDeliveryPerson(string name) {
        deliveryPerson = name;
        cout<<"Delivery person assigned: "<<deliveryPerson<<endl;
    }

    void calculateDeliveryTime() {
        deliveryTime = 30;
        cout<<"Estimated delivery time: "<<deliveryTime<<" minutes";
    }

    void displayOrderDetails() {
        cout<<"Order ID: "<<orderId<<endl;
        cout<<"Status: "<<status<<endl;
        cout<<"Delivery Person: "<<deliveryPerson<<endl;
        cout<<"Delivery Time: "<<deliveryTime<<" minutes"<<endl;
        cart.displayCart();
    }
};

class Customer: public User {
    protected:
    string address;
    Cart cart;
    Order orderHistory[100];
    int orderCount;

    public:
    Customer() : User(), address(""), orderCount(0) {}
    Customer(int id, string nm, string em, string pass, string ph, string addr)
        : User(id, nm, em, pass, ph), address(addr), orderCount(0) {
        cout<<"Customer obj created" << endl;
    }

    void browseRestaurants(Restaurant restaurants[], int count) {
        cout<<"Browsing restaurants...";
        for(int i=0; i<count; i++) {
            cout<<"Restaurant ID: "<<restaurants[i].Restaurantid<<endl;
            cout<<"Name: "<<restaurants[i].name<<endl;
            cout<<"Address: "<<restaurants[i].address<<endl;
            cout<<"Rating: "<<restaurants[i].rating<<endl;
            cout<<"------------------------- " << endl;
        }
    }

    void addToCart(MenuItem item) {
        cart.addItem(item);
    }

    void placeOrder() {
        if(cart.calculateTotal() == 0) {
            cout<<"Cart is empty. Please add items to cart before placing an order.";
            return;
        }

        int nextId = orderCount + 1;
        Order newOrder(nextId, cart);
        newOrder.placeOrder();
        if(orderCount < 100) {
            orderHistory[orderCount++] = newOrder;
        }
        cart.clearCart();
    }

    void viewOrderHistory() {
        cout<<"Order History:";
        for(int i=0; i<orderCount; i++) {
            orderHistory[i].displayOrderDetails();
            cout<<"------------------------- " << endl;
        }
    }

    void displayCart() {
        cart.displayCart();
    }
};

class DeliveryPerson: public User {
    protected:
    bool isAvailable;
    Order assignedOrders[100];
    int assignedCount;

    public:
    DeliveryPerson() : User(), isAvailable(true), assignedCount(0) {}
    DeliveryPerson(int id, string nm, string em, string pass, string ph)
        : User(id, nm, em, pass, ph), isAvailable(true), assignedCount(0) {
        cout<<"Delivery Person obj created" << endl;
    }

    void acceptOrder(const Order &o) {
        if(assignedCount < 100) {
            assignedOrders[assignedCount++] = o;
            isAvailable = false;
        }
    }

    void updateOrderStatus(int orderId, string status) {
        for(int i=0; i<assignedCount; i++) {
            if(assignedOrders[i].getOrderId() == orderId) {
                assignedOrders[i].updateStatus(status);
                return;
            }
        }
        cout<<"Order not found";
    }

    void markDelivered(const Order &o) {
        for(int i=0; i<assignedCount; i++) {
            if(assignedOrders[i].getOrderId() == o.getOrderId()) {
                assignedOrders[i].updateStatus("Delivered");
                isAvailable = true;
                return;
            }
        }
        cout<<"Order not found";
    }
};

class Owner: public User {
    protected:
    Restaurant ownedRestaurant[100];
    int ownedRestaurantCount;
    string address;

    public:
    Owner() : User(), ownedRestaurantCount(0), address("") {}
    void addMenuItemToRestaurant(int resId, MenuItem m) {
        for(int i=0; i<ownedRestaurantCount; i++) {
            if(ownedRestaurant[i].getId() == resId) {
                ownedRestaurant[i].addMenuItem(m);
                break;
            }
        }
    }

    Owner(int id, string nm, string em, string pass, string ph, string addr)
        : User(id, nm, em, pass, ph), ownedRestaurantCount(0), address(addr) {
            cout<<"Owner obj created" << endl;
        }

    void addRestaurant(const Restaurant &r) {
        if(ownedRestaurantCount < 100) {
            ownedRestaurant[ownedRestaurantCount++] = r;
        }
    }

    void addMenuItem(Restaurant *r, MenuItem m) {
        if(r) {
            r->addMenuItem(m);
            cout<<"Menu item added to restaurant";
        }
    }

    void viewAllOrders() {
        cout<<"Viewing all orders for owned restaurants...";
        for(int i=0; i<ownedRestaurantCount; i++) {
            cout<<"Orders for Restaurant: "<<ownedRestaurant[i].name<<endl;
            cout<<"-------------------------";
        }
    }
};

int main() {
    Restaurant restaurants[100];
    Customer customers[100];
    Owner owners[100];
    DeliveryPerson deliveryPersons[100];
    
    int choice;
    
    while(true) {
        cout << "\n=== FoodFast ===\n";
        cout << "1. Login as Customer\n";
        cout << "2. Login as Owner\n";
        cout << "3. Login as Delivery Person\n";
        cout << "4. Register\n";
        cout << "5. Exit\n";
        cin >> choice;
        
        switch(choice) {
            case 1: {
                { // Customer login & menu
                    int memo;
                    string email, pass;
                cout << "Email: "; cin >> email;
                cout << "Password: "; cin >> pass;
                
                // Find customer
                Customer* loggedIn = nullptr;
                for(int i=0; i<100; i++) {
                    if(customers[i].authenticate(email, pass)) {
                        memo=i;
                        loggedIn = &customers[i];
                        break;
                    }
                }
                
                if(loggedIn) {
                    cout<<"Welcome!!\n";
                    //menu 
                    cout << "\n=== Customer Menu ===\n";
                    cout << "1. Browse Restaurants\n";
                    cout << "2. View Cart\n";
                    cout << "3. Place Order\n";
                    cout << "4. Order History\n";
                    cout << "5. Logout\n";
                    int c;cin>>c;
                    string res_name;
                    switch (c) {
                        case 1: {
                        int n;
                        cout<<"Enter how many Restaurant you want to browse:\n";
                        cin>>n;
                        customers[memo].browseRestaurants(restaurants,n);
                        cout<<"Select a Restaurant and write its name: \n";
                        cin>>res_name;
                        break;
                        }
                        case 2: {
                        customers[memo].displayCart();
                        break;
                        }
                        case 3: {
                            for(int i=0;i<100;i++) {
                                if(res_name==restaurants[i].getName()) {
                                    int item_id;
                                    cout<<"Enter the item id you want to add to cart: \n";
                                    cin>>item_id;
                                    MenuItem* item = restaurants[i].getMenuItemById(item_id);
                                    if(item != nullptr) {
                                        customers[memo].addToCart(*item);
                                    } else {
                                        cout<<"Item not found\n";
                                    }
                                    break;
                            }
                        }
                        break;
                        }
                        case 4: {
                        customers[memo].viewOrderHistory();
                        break;
                        }
                        case 5: {
                        cout<<"Logging out...\n";
                        loggedIn->logout();
                        break;
                        }
                    }
                } 
                else {
                    cout << "Invalid credentials!\n";
                }
                } // end inner block
                break;
            }
            
            case 2: {
                {
                    int memo;
                    string email, pass;
                    cout << "Email: "; cin >> email;
                cout << "Password: "; cin >> pass;
                
                // Find owner
                Owner* loggedIn = nullptr;
                for(int i=0; i<100; i++) {
                    if(owners[i].authenticate(email, pass)) {
                        memo=i;
                        loggedIn = &owners[i];
                        break;
                    }
                }
                if(loggedIn) {
                    cout<<"Welcome!!\n";
                    cout << "\n=== Owner Menu ===\n";
                    cout << "1. Add Restaurant\n";
                    cout << "2. Add Menu Item\n";
                    cout << "3. View Orders\n";
                    cout << "4. Logout\n";
                    int c;
                    cin>>c;
                    switch(c) {
                        case 1: {
                        int id; string name, address; float rating; int menuCount; bool isOpen;
                        cout << "Enter Restaurant ID: "; cin >> id;
                        cout << "Enter Name: "; cin.ignore(); getline(cin, name);
                        cout << "Enter Address: "; getline(cin, address);
                        cout << "Enter Rating: "; cin >> rating;
                        cout << "Enter Menu Count: "; cin >> menuCount;
                        cout << "Is the restaurant open? (1 for Yes, 0 for No): "; cin >> isOpen;
                        Restaurant newRestaurant(id, name, address, rating, menuCount, isOpen);
                        loggedIn->addRestaurant(newRestaurant);
                        break;
                        }
                        case 2: {
                        int resId, itemId; string itemName, category; float price; bool available;
                        cout << "Enter Restaurant ID to add menu item: "; cin >> resId;
                        cout << "Enter Item ID: "; cin >> itemId;
                        cout << "Enter Item Name: "; cin.ignore(); getline(cin, itemName);
                        cout << "Enter Category: "; getline(cin, category);
                        cout << "Enter Price: "; cin >> price;
                        cout << "Is the item available? (1 for Yes, 0 for No): "; cin >> available;
                        MenuItem newItem;
                        newItem.enterItemDetails(itemId, itemName, category, price, available);
                        // Find the restaurant to add the menu item
                        loggedIn->addMenuItemToRestaurant(resId, newItem);

                        break;
                        
                        case 3:{
                        loggedIn->viewAllOrders();
                        break;
                        }
                        case 4:{
                        cout<<"Logging out...\n";
                        loggedIn->logout();
                        break;
                        }
                        default:
                        break;
                    }
                }
                }
                else {
                    cout<<"Invalid Credentials!\n";
                }
                } // end inner block
                break;
            }
            
            case 3: {
                // Delivery person menu
                break;
            }
            
            case 4: {
                {
                cout<<"Enter the user type (1 for Customer, 2 for Owner, 3 for Delivery Person): \n";
                int type;cin>>type;
                if(type==1) {
                    Customer newCustomer;
                    int id; string name, email, pass, phone, addr;
                    cout << "Enter ID: "; cin >> id;
                    cout << "Enter Name: "; cin.ignore(); getline(cin, name);
                    cout << "Enter Email: "; cin >> email;
                    cout << "Enter Password: "; cin >> pass;
                    cout << "Enter Phone: "; cin >> phone;
                    cout << "Enter Address: "; cin.ignore(); getline(cin, addr);
                    newCustomer = Customer(id, name, email, pass, phone, addr);
                    customers[id] = newCustomer;
                    cout<<"Customer registered successfully!\n";
                } 
                else if(type==2) {
                    Owner newOwner;
                    int id; string name, email, pass, phone, addr;
                    cout << "Enter ID: "; cin >> id;
                    cout << "Enter Name: "; cin.ignore(); getline(cin, name);
                    cout << "Enter Email: "; cin >> email;
                    cout << "Enter Password: "; cin >> pass;
                    cout << "Enter Phone: "; cin >> phone;
                    cout << "Enter Address: "; cin.ignore(); getline(cin, addr);
                    newOwner = Owner(id, name, email, pass, phone, addr);
                    owners[id] = newOwner;
                    cout<<"Owner registered successfully!\n";
                } else if(type==3) {
                    DeliveryPerson newDeliveryPerson;
                    int id; string name, email, pass, phone, addr;
                    cout << "Enter ID: "; cin >> id;
                    cout << "Enter Name: "; cin.ignore(); getline(cin, name);
                    cout << "Enter Email: "; cin >> email;
                    cout << "Enter Password: "; cin >> pass;
                    cout << "Enter Phone: "; cin >> phone;
                    newDeliveryPerson = DeliveryPerson(id, name, email, pass, phone);
                    deliveryPersons[id] = newDeliveryPerson;
                    cout<<"Delivery Person registered successfully!\n";
                } else {
                    cout<<"Invalid user type! please try again!\n";
                }
                } // end inner block
                break;
            }
            
            case 5:
            cout<<"Exiting... Thank you for using FoodFast!\n";
                return 0;
        }
    }
    return 0;
}
