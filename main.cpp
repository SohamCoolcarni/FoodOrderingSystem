#include<iostream>
#include<string>
#include<fstream>
#include<sstream>
using namespace std;

class User {
    protected:
    bool islogin;
    int Userid;
    string name, email, password;
    string phone;

    public:
    User() {
        Userid = 0;
        name = "";
        email = "";
        password = "";
        phone = "";
        islogin = false;
    }

    User(int id, string nm, string em, string pass, string ph) {
        Userid = id;
        name = nm;
        email = em;
        password = pass;
        phone = ph;
        islogin = false;
        cout << "User obj created\n";
    }

    bool authenticate(string em, string pass) {
        return (email == em && password == pass);
    }

    void get() {
        if(islogin) {
            cout << "User ID: " << Userid << endl;
            cout << "Name: " << name << endl;
            cout << "Email: " << email << endl;
            cout << "Phone: " << phone << endl;
        } else {
            cout << "User is not logged in\n";
        }
    }

    void login() {
        int check;
        string pass;
        cout << "Enter the User id and password\n" << "Id: ";
        cin >> check;
        cout << "Password: ";
        cin >> pass;
        if(check == Userid && pass == password) {
            cout << "Login successful\n";
            islogin = true;
        } else {
            cout << "Invalid credentials. Please try again.\n";
        }
    }

    void logout() {
        cout << "Logout successful\n";
        islogin = false;
    }

    void updateProfile() {
        if(!islogin) {
            cout << "Please login to update your profile\n";
        } else {
            cout << "Current profile information:\n";
            get();
            cout << "Enter new name, email, password and phone number in this order:\n";
            cin >> name >> email >> password >> phone;
            cout << "Profile updated successfully\n";
        }
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
        Itemid = 0;
        name = "";
        price = 0;
        catagory = "";
        isAvailable = false;
    }

    void enterItemDetails(int item, string in, string cat, float p, bool a) {
        Itemid = item;
        name = in;
        catagory = cat;
        price = p;
        isAvailable = a;
        cout << "MenuItem obj created\n";
    }

    void get() {
        cout << "Itemid: " << Itemid << endl;
        cout << "Name: " << name << endl;
        cout << "Catagory: " << catagory << endl;
        cout << "Price: " << price << endl;
        cout << "Available: " << isAvailable << endl;
    }

    void displayDetails() {
        get();
    }

    void updatePrice(float newPrice) {
        price = newPrice;
        cout << "Price updated successfully\n";
    }

    void toggleAvailability() {
        isAvailable = !isAvailable;
        cout << "Availability changed\n";
    }

    void applyDiscount(float percent) {
        price = price - (price * percent / 100);
        cout << "Discount applied. New price: " << price << endl;
    }

    int getId() { return Itemid; }
    float getPrice() { return price; }

    friend class Restaurant;
    friend class Cart;
};

class Restaurant {
    private:
    int Restaurantid;
    string name, address;
    float rating;
    MenuItem menu[100];
    int menuCount;
    bool isOpen;

    public:
    Restaurant() {
        Restaurantid = 0;
        name = "";
        address = "";
        rating = 0;
        menuCount = 0;
        isOpen = false;
    }

    Restaurant(int id, string nm, string add, float ra, int n, bool y) {
        Restaurantid = id;
        name = nm;
        address = add;
        rating = ra;
        menuCount = n;
        isOpen = y;
        cout << "Restaurant obj created\n";
    }

    int getId() { return Restaurantid; }
    string getName() { return name; }

    void addMenuItem(MenuItem m) {
        for(int i = 0; i < 100; i++) {
            if(menu[i].Itemid == m.Itemid && menu[i].Itemid != 0) {
                cout << "Item with this id already exists. Please enter a unique item id.\n";
                return;
            }
        }
        for(int i = 0; i < 100; i++) {
            if(menu[i].Itemid == 0) {
                menu[i] = m;
                menuCount++;
                cout << "Menu item added successfully." << endl;
                return;
            }
        }
        cout << "Menu is full\n";
    }

    void displayMenu() {
        cout << "Menu for Restaurant: " << name << "\n";
        for(int i = 0; i < 100; i++) {
            if(menu[i].Itemid != 0) {
                menu[i].get();
            }
        }
    }

    MenuItem* getMenuItemById(int id) {
        for(int i = 0; i < 100; i++) {
            if(menu[i].Itemid == id) {
                return &menu[i];
            }
        }
        return nullptr;
    }

    void removeMenuItem(int id) {
        for(int i = 0; i < menuCount; i++) {
            if(menu[i].Itemid == id) {
                for(int j = i; j < menuCount - 1; j++) {
                    menu[j] = menu[j+1];
                }
                menuCount--;
                cout << "Menu item removed\n";
                return;
            }
        }
        cout << "Item not found\n";
    }

    void updateMenuItem(int id, float newPrice) {
        for(int i = 0; i < menuCount; i++) {
            if(menu[i].Itemid == id) {
                menu[i].updatePrice(newPrice);
                return;
            }
        }
        cout << "Item not found\n";
    }

    void searchMenuItem(int id) {
        for(int i = 0; i < menuCount; i++) {
            if(menu[i].Itemid == id) {
                cout << "Item found:\n";
                menu[i].get();
                return;
            }
        }
        cout << "Item not found\n";
    }

    void toggleOpen() {
        isOpen = !isOpen;
        cout << "Restaurant is now " << (isOpen ? "Open" : "Closed") << endl;
    }

    float getAverageRating() {
        return rating;
    }
};

class Cart {
    private:
    MenuItem items[100];
    int quantity[100];
    int count;

    public:
    Cart() {
        count = 0;
        for(int i = 0; i < 100; i++) quantity[i] = 0;
    }

    void addItem(MenuItem m) {
        for(int i = 0; i < count; i++) {
            if(items[i].Itemid == m.Itemid) {
                quantity[i]++;
                cout << "Item quantity increased\n";
                return;
            }
        }
        items[count] = m;
        quantity[count] = 1;
        count++;
        cout << "Item added to cart\n";
    }

    void removeItem(int id) {
        for(int i = 0; i < count; i++) {
            if(items[i].Itemid == id) {
                for(int j = i; j < count - 1; j++) {
                    items[j] = items[j+1];
                    quantity[j] = quantity[j+1];
                }
                count--;
                cout << "Item removed from cart\n";
                return;
            }
        }
        cout << "Item not found in cart\n";
    }

    void updateQuantity(int id, int q) {
        for(int i = 0; i < count; i++) {
            if(items[i].Itemid == id) {
                quantity[i] = q;
                cout << "Quantity updated\n";
                return;
            }
        }
        cout << "Item not found in cart\n";
    }

    float calculateTotal() {
        float total = 0;
        for(int i = 0; i < count; i++) {
            total += items[i].price * quantity[i];
        }
        return total;
    }

    void clearCart() {
        count = 0;
        cout << "Cart cleared\n";
    }

    void displayCart() {
        if(count == 0) {
            cout << "Cart is empty\n";
            return;
        }
        cout << "Cart Items:\n";
        for(int i = 0; i < count; i++) {
            items[i].get();
            cout << "Quantity: " << quantity[i] << endl;
        }
        cout << "Total Price: " << calculateTotal() << endl;
    }

    int getCount() { return count; }
};

class Order {
    private:
    int orderId;
    string status;
    Cart cart;
    string deliveryPerson;
    int deliveryTime;

    public:
    Order() {
        orderId = 0;
        status = "None";
        deliveryPerson = "Not Assigned";
        deliveryTime = 0;
    }

    Order(int id, Cart c) {
        orderId = id;
        cart = c;
        status = "Created";
        deliveryPerson = "Not Assigned";
        deliveryTime = 0;
        cout << "Order object created\n";
    }

    void placeOrder() {
        status = "Placed";
        cout << "Order placed successfully\n";
    }

    void updateStatus(string s) {
        status = s;
        cout << "Order status updated to: " << status << endl;
    }

    void cancelOrder() {
        status = "Cancelled";
        cout << "Order cancelled\n";
    }

    void assignDeliveryPerson(string name) {
        deliveryPerson = name;
        cout << "Delivery person assigned: " << deliveryPerson << endl;
    }

    void calculateDeliveryTime() {
        deliveryTime = 30;
        cout << "Estimated delivery time: " << deliveryTime << " minutes\n";
    }

    void displayOrderDetails() {
        cout << "Order ID: " << orderId << endl;
        cout << "Status: " << status << endl;
        cout << "Delivery Person: " << deliveryPerson << endl;
        cout << "Delivery Time: " << deliveryTime << " minutes" << endl;
        cart.displayCart();
    }

    int getId() { return orderId; }
    string getStatus() { return status; }
};

class Customer : public User {
    private:
    string address;
    Cart cart;
    Order orderHistory[100];
    int orderCount;

    public:
    Customer() : User() {
        address = "";
        orderCount = 0;
    }

    Customer(int id, string nm, string em, string pass, string ph, string add)
        : User(id, nm, em, pass, ph) {
        address = add;
        orderCount = 0;
        cout << "Customer obj created\n";
    }

    void browseRestaurants(Restaurant restaurants[], int n) {
        cout << "Available Restaurants:\n";
        for(int i = 0; i < n; i++) {
            cout << i+1 << ". " << restaurants[i].getName() << endl;
            restaurants[i].displayMenu();
        }
    }

    void addToCart(MenuItem item) {
        cart.addItem(item);
    }

    void displayCart() {
        cart.displayCart();
    }

    void placeOrder() {
        if(cart.getCount() == 0) {
            cout << "Cart is empty. Add items before placing order.\n";
            return;
        }
        Order newOrder(orderCount + 1, cart);
        newOrder.placeOrder();
        newOrder.calculateDeliveryTime();
        orderHistory[orderCount++] = newOrder;
        cart.clearCart();
    }

    void viewOrderHistory() {
        if(orderCount == 0) {
            cout << "No orders placed yet.\n";
            return;
        }
        cout << "Order History:\n";
        for(int i = 0; i < orderCount; i++) {
            orderHistory[i].displayOrderDetails();
        }
    }

    friend void saveCustomers(const Customer[]);
    friend void loadCustomers(Customer[]);
};

class Owner : public User {
    private:
    Restaurant ownedRestaurants[100];
    int resCount;

    public:
    Owner() : User() {
        resCount = 0;
    }

    Owner(int id, string nm, string em, string pass, string ph, string addr)
        : User(id, nm, em, pass, ph) {
        resCount = 0;
        cout << "Owner obj created\n";
    }

    void addRestaurant(Restaurant r) {
        ownedRestaurants[resCount++] = r;
        cout << "Restaurant added successfully\n";
    }

    void addMenuItemToRestaurant(int resId, MenuItem item) {
        for(int i = 0; i < resCount; i++) {
            if(ownedRestaurants[i].getId() == resId) {
                ownedRestaurants[i].addMenuItem(item);
                return;
            }
        }
        cout << "Restaurant not found\n";
    }

    void viewAllOrders() {
        cout << "Viewing all orders (feature coming soon)\n";
    }

    friend void saveOwners(const Owner[]);
    friend void loadOwners(Owner[]);
};

class DeliveryPerson : public User {
    private:
    bool isAvailable;
    string currentArea;
    int deliveriesCount;

    public:
    DeliveryPerson() : User() {
        isAvailable = true;
        currentArea = "";
        deliveriesCount = 0;
    }

    DeliveryPerson(int id, string nm, string em, string pass, string ph)
        : User(id, nm, em, pass, ph) {
        isAvailable = true;
        currentArea = "";
        deliveriesCount = 0;
        cout << "DeliveryPerson obj created\n";
    }

    void acceptOrder(int orderId) {
        isAvailable = false;
        cout << "Order " << orderId << " accepted\n";
    }

    void completeDelivery() {
        isAvailable = true;
        deliveriesCount++;
        cout << "Delivery completed\n";
    }

    void updateLocation(string area) {
        currentArea = area;
        cout << "Location updated to: " << currentArea << endl;
    }

    void viewAssignedOrders() {
        cout << "Viewing assigned orders (feature coming soon)\n";
    }

    friend void saveDeliveryPersons(const DeliveryPerson[]);
    friend void loadDeliveryPersons(DeliveryPerson[]);
};

// Base class for payment
class Payment {
    public:
    virtual void processPayment(float amount) = 0;

    void validatePayment() {
        cout << "Payment validated\n";
    }

    void generateReceipt(float amount) {
        cout << "Receipt generated for amount: " << amount << endl;
    }
};

// Credit card payment
class CreditCard : public Payment {
    public:
    void processPayment(float amount) {
        cout << "Processing credit card payment of " << amount << endl;
        validateCard();
        validatePayment();
        generateReceipt(amount);
    }

    void validateCard() {
        cout << "Card details checked\n";
    }
};

// UPI payment
class UPI : public Payment {
    public:
    void processPayment(float amount) {
        cout << "Processing UPI payment of " << amount << endl;
        validateUPI();
        validatePayment();
        generateReceipt(amount);
    }

    void validateUPI() {
        cout << "UPI id verified\n";
    }
};

// Cash on delivery
class COD : public Payment {
    public:
    void processPayment(float amount) {
        cout << "Cash on delivery selected, amount: " << amount << endl;
        confirmCOD();
        generateReceipt(amount);
    }

    void confirmCOD() {
        cout << "Order will be paid at delivery\n";
    }
};


// ======================================================================
// FIX: Moved these large arrays to global scope to prevent Stack Overflow
// ======================================================================
Restaurant restaurants[100];
Customer customers[100];
Owner owners[100];
DeliveryPerson deliveryPersons[100];

void saveCustomers(const Customer customers[]) {
    ofstream file("customers.txt");
    if (!file) return;
    for (int i = 0; i < 100; i++) {
        if (customers[i].Userid != 0) {
            file << customers[i].Userid << "," << customers[i].name << "," << customers[i].email << ","
                 << customers[i].password << "," << customers[i].phone << "," << customers[i].address << endl;
        }
    }
    file.close();
}

void loadCustomers(Customer customers[]) {
    ifstream file("customers.txt");
    if (!file) return;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, email, pass, phone, addr;
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, pass, ',');
        getline(ss, phone, ',');
        getline(ss, addr);
        int id = stoi(idStr);
        if(id >= 0 && id < 100) {
            customers[id] = Customer(id, name, email, pass, phone, addr);
        }
    }
    file.close();
}

void saveOwners(const Owner owners[]) {
    ofstream file("owners.txt");
    if (!file) return;
    for (int i = 0; i < 100; i++) {
        if (owners[i].Userid != 0) {
            file << owners[i].Userid << "," << owners[i].name << "," << owners[i].email << ","
                 << owners[i].password << "," << owners[i].phone << endl;
        }
    }
    file.close();
}

void loadOwners(Owner owners[]) {
    ifstream file("owners.txt");
    if (!file) return;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, email, pass, phone;
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, pass, ',');
        getline(ss, phone);
        int id = stoi(idStr);
        if(id >= 0 && id < 100) {
            owners[id] = Owner(id, name, email, pass, phone, "");
        }
    }
    file.close();
}

void saveDeliveryPersons(const DeliveryPerson deliveryPersons[]) {
    ofstream file("delivery_persons.txt");
    if (!file) return;
    for (int i = 0; i < 100; i++) {
        if (deliveryPersons[i].Userid != 0) {
            file << deliveryPersons[i].Userid << "," << deliveryPersons[i].name << "," << deliveryPersons[i].email << ","
                 << deliveryPersons[i].password << "," << deliveryPersons[i].phone << endl;
        }
    }
    file.close();
}

void loadDeliveryPersons(DeliveryPerson deliveryPersons[]) {
    ifstream file("delivery_persons.txt");
    if (!file) return;
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string idStr, name, email, pass, phone;
        getline(ss, idStr, ',');
        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, pass, ',');
        getline(ss, phone);
        int id = stoi(idStr);
        if(id >= 0 && id < 100) {
            deliveryPersons[id] = DeliveryPerson(id, name, email, pass, phone);
        }
    }
    file.close();
}

int main() {
    // Load data from files
    loadCustomers(customers);
    loadOwners(owners);
    loadDeliveryPersons(deliveryPersons);

    int choice;

    while(true) {
        cout << "\n=== FoodFast ===\n";
        cout << "1. Login as Customer\n";
        cout << "2. Login as Owner\n";
        cout << "3. Login as Delivery Person\n";
        cout << "4. Register\n";
        cout << "5. Exit\n";
        cout << "Enter Choice: "; // Added a tiny prompt here to make it easier to read
        cin >> choice;

        switch(choice) {

            case 1: {
                int memo = -1;
                string email, pass;
                cout << "Email: "; cin >> email;
                cout << "Password: "; cin >> pass;

                Customer* loggedIn = nullptr;
                for(int i = 0; i < 100; i++) {
                    if(customers[i].authenticate(email, pass)) {
                        memo = i;
                        loggedIn = &customers[i];
                        break;
                    }
                }

                if(loggedIn) {
                    cout << "Welcome!!\n";
                    string res_name = "";
                    int c;
                    
                    // Small loop added so you don't get kicked out immediately after one action
                    while (true) { 
                        cout << "\n=== Customer Menu ===\n";
                        cout << "1. Browse Restaurants\n";
                        cout << "2. View Cart\n";
                        cout << "3. Add Item to Cart\n";
                        cout << "4. Place Order\n";
                        cout << "5. Order History\n";
                        cout << "6. Logout\n";
                        cout << "Enter Choice: ";
                        cin >> c;

                        if (c == 6) {
                            cout << "Logging out...\n";
                            loggedIn->logout();
                            break;
                        }

                        switch(c) {
                            case 1: {
                                int n;
                                cout << "Enter how many Restaurants you want to browse: ";
                                cin >> n;
                                customers[memo].browseRestaurants(restaurants, n);
                                cout << "Select a Restaurant and write its name: \n";
                                cin >> res_name;
                                break;
                            }
                            case 2: {
                                customers[memo].displayCart();
                                break;
                            }
                            case 3: {
                                if(res_name == "") {
                                    cout << "Please browse restaurants first (option 1)\n";
                                    break;
                                }
                                for(int i = 0; i < 100; i++) {
                                    if(res_name == restaurants[i].getName()) {
                                        int item_id;
                                        cout << "Enter the item id you want to add to cart: ";
                                        cin >> item_id;
                                        MenuItem* item = restaurants[i].getMenuItemById(item_id);
                                        if(item != nullptr) {
                                            customers[memo].addToCart(*item);
                                        } else {
                                            cout << "Item not found\n";
                                        }
                                        break;
                                    }
                                }
                                break;
                            }
                            case 4: {
                                customers[memo].placeOrder();
                                break;
                            }
                            case 5: {
                                customers[memo].viewOrderHistory();
                                break;
                            }
                            default:
                                cout << "Invalid option\n";
                        }
                    }
                } else {
                    cout << "Invalid credentials!\n";
                }
                break;
            }

            case 2: {
                int memo = -1;
                string email, pass;
                cout << "Email: "; cin >> email;
                cout << "Password: "; cin >> pass;

                Owner* loggedIn = nullptr;
                for(int i = 0; i < 100; i++) {
                    if(owners[i].authenticate(email, pass)) {
                        memo = i;
                        loggedIn = &owners[i];
                        break;
                    }
                }

                if(loggedIn) {
                    cout << "Welcome!!\n";
                    
                    while (true) {
                        cout << "\n=== Owner Menu ===\n";
                        cout << "1. Add Restaurant\n";
                        cout << "2. Add Menu Item\n";
                        cout << "3. View Orders\n";
                        cout << "4. Logout\n";
                        int c;
                        cout << "Enter Choice: ";
                        cin >> c;

                        if (c == 4) {
                            cout << "Logging out...\n";
                            loggedIn->logout();
                            break;
                        }

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
                                
                                // Keep the global restaurant array updated so customers can see it
                                for(int i=0; i<100; i++) {
                                    if(restaurants[i].getId() == 0) {
                                        restaurants[i] = newRestaurant;
                                        break;
                                    }
                                }
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
                                loggedIn->addMenuItemToRestaurant(resId, newItem);
                                
                                // Keep the global restaurant array updated so customers can see it
                                for(int i=0; i<100; i++) {
                                    if(restaurants[i].getId() == resId) {
                                        restaurants[i].addMenuItem(newItem);
                                        break;
                                    }
                                }
                                break;
                            }
                            case 3: {
                                loggedIn->viewAllOrders();
                                break;
                            }
                            default:
                                cout << "Invalid option\n";
                        }
                    }
                } else {
                    cout << "Invalid Credentials!\n";
                }
                break;
            }

            case 3: {
                int memo = -1;
                string email, pass;
                cout << "Email: "; cin >> email;
                cout << "Password: "; cin >> pass;

                DeliveryPerson* loggedIn = nullptr;
                for(int i = 0; i < 100; i++) {
                    if(deliveryPersons[i].authenticate(email, pass)) {
                        memo = i;
                        loggedIn = &deliveryPersons[i];
                        break;
                    }
                }

                if(loggedIn) {
                    cout << "Welcome!!\n";
                    
                    while(true) {
                        cout << "\n=== Delivery Person Menu ===\n";
                        cout << "1. View Assigned Orders\n";
                        cout << "2. Update Location\n";
                        cout << "3. Complete Delivery\n";
                        cout << "4. Logout\n";
                        int c;
                        cout << "Enter Choice: ";
                        cin >> c;

                        if(c == 4) {
                            cout << "Logging out...\n";
                            loggedIn->logout();
                            break;
                        }

                        switch(c) {
                            case 1: {
                                loggedIn->viewAssignedOrders();
                                break;
                            }
                            case 2: {
                                string area;
                                cout << "Enter your current area: ";
                                cin.ignore(); getline(cin, area);
                                loggedIn->updateLocation(area);
                                break;
                            }
                            case 3: {
                                loggedIn->completeDelivery();
                                break;
                            }
                            default:
                                cout << "Invalid option\n";
                        }
                    }
                } else {
                    cout << "Invalid Credentials!\n";
                }
                break;
            }

            case 4: {
                cout << "Enter the user type (1 for Customer, 2 for Owner, 3 for Delivery Person): \n";
                int type; cin >> type;

                if(type == 1) {
                    int id; string name, email, pass, phone, addr;
                    cout << "Enter ID (0-99): "; cin >> id; 
                    if(id < 0 || id > 99) { cout << "Invalid ID. Please use 0-99.\n"; break; }
                    cout << "Enter Name: "; cin.ignore(); getline(cin, name);
                    cout << "Enter Email: "; cin >> email;
                    cout << "Enter Password: "; cin >> pass;
                    cout << "Enter Phone: "; cin >> phone;
                    cout << "Enter Address: "; cin.ignore(); getline(cin, addr);
                    customers[id] = Customer(id, name, email, pass, phone, addr);
                    cout << "Customer registered successfully!\n";
                }
                else if(type == 2) {
                    int id; string name, email, pass, phone, addr;
                    cout << "Enter ID (0-99): "; cin >> id;
                    if(id < 0 || id > 99) { cout << "Invalid ID. Please use 0-99.\n"; break; }
                    cout << "Enter Name: "; cin.ignore(); getline(cin, name);
                    cout << "Enter Email: "; cin >> email;
                    cout << "Enter Password: "; cin >> pass;
                    cout << "Enter Phone: "; cin >> phone;
                    cout << "Enter Address: "; cin.ignore(); getline(cin, addr);
                    owners[id] = Owner(id, name, email, pass, phone, addr);
                    cout << "Owner registered successfully!\n";
                }
                else if(type == 3) {
                    int id; string name, email, pass, phone;
                    cout << "Enter ID (0-99): "; cin >> id;
                    if(id < 0 || id > 99) { cout << "Invalid ID. Please use 0-99.\n"; break; }
                    cout << "Enter Name: "; cin.ignore(); getline(cin, name);
                    cout << "Enter Email: "; cin >> email;
                    cout << "Enter Password: "; cin >> pass;
                    cout << "Enter Phone: "; cin >> phone;
                    deliveryPersons[id] = DeliveryPerson(id, name, email, pass, phone);
                    cout << "Delivery Person registered successfully!\n";
                }
                else {
                    cout << "Invalid user type! Please try again!\n";
                }
                break;
            }

            case 5:
                cout << "Exiting... Thank you for using FoodFast!\n";
                // Save data to files
                saveCustomers(customers);
                saveOwners(owners);
                saveDeliveryPersons(deliveryPersons);
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}