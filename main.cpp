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
        Userid = -1;   // FIX: Use -1 as "empty" sentinel instead of 0, since 0 is a valid ID
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
    }

    bool authenticate(string em, string pass) {
        if (Userid == -1) return false;   // FIX: Skip empty slots
        return (email == em && password == pass);
    }

    // FIX: Added setter so login via authenticate() can mark islogin = true
    void setLogin(bool val) { islogin = val; }

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

    int getId() { return Userid; }
    bool getIsLogin() { return islogin; }
};

// ─────────────────────────────────────────────────────────
// MenuItem
// ─────────────────────────────────────────────────────────
class MenuItem {
    private:
    int Itemid;
    string name;
    float price;
    string catagory;
    bool isAvailable;

    public:
    MenuItem() {
        Itemid = -1;   // FIX: -1 = empty slot
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
    }

    void get() const {
        if(Itemid == -1) return;
        cout << "  Item ID   : " << Itemid << endl;
        cout << "  Name      : " << name << endl;
        cout << "  Category  : " << catagory << endl;
        cout << "  Price     : Rs." << price << endl;
        cout << "  Available : " << (isAvailable ? "Yes" : "No") << endl;
        cout << "  ----------\n";
    }

    void displayDetails() { get(); }

    void updatePrice(float newPrice) {
        price = newPrice;
        cout << "Price updated successfully\n";
    }

    void toggleAvailability() {
        isAvailable = !isAvailable;
        cout << "Availability changed to " << (isAvailable ? "Available" : "Unavailable") << "\n";
    }

    void applyDiscount(float percent) {
        price = price - (price * percent / 100);
        cout << "Discount applied. New price: Rs." << price << endl;
    }

    int getId()    const { return Itemid; }
    float getPrice() const { return price; }
    bool getAvailable() const { return isAvailable; }
    string getName() const { return name; }
    string getCategory() const { return catagory; }

    friend class Restaurant;
    friend class Cart;
};

// ─────────────────────────────────────────────────────────
// Restaurant
// ─────────────────────────────────────────────────────────
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
        Restaurantid = -1;   // FIX: -1 = empty slot
        name = "";
        address = "";
        rating = 0;
        menuCount = 0;
        isOpen = false;
    }

    Restaurant(int id, string nm, string add, float ra, bool y) {
        Restaurantid = id;
        name = nm;
        address = add;
        rating = ra;
        menuCount = 0;
        isOpen = y;
    }

    int getId()      const { return Restaurantid; }
    string getName() const { return name; }
    bool getIsOpen() const { return isOpen; }
    float getRating() const { return rating; }
    string getAddress() const { return address; }

    void addMenuItem(MenuItem m) {
        // FIX: Search whole array (not just menuCount slots) for duplicate
        for(int i = 0; i < 100; i++) {
            if(menu[i].Itemid == m.Itemid && menu[i].Itemid != -1) {
                cout << "Item with ID " << m.Itemid << " already exists.\n";
                return;
            }
        }
        if(menuCount >= 100) { cout << "Menu is full\n"; return; }
        // FIX: Store items compactly (no sparse gaps)
        menu[menuCount] = m;
        menuCount++;
        cout << "Menu item added successfully.\n";
    }

    void displayMenu() const {
        if(menuCount == 0) { cout << "  (No menu items yet)\n"; return; }
        for(int i = 0; i < menuCount; i++) {
            menu[i].get();
        }
    }

    // FIX: Search within menuCount, not sparse 100-slot loop
    MenuItem* getMenuItemById(int id) {
        for(int i = 0; i < menuCount; i++) {
            if(menu[i].Itemid == id) return &menu[i];
        }
        return nullptr;
    }

    void removeMenuItem(int id) {
        for(int i = 0; i < menuCount; i++) {
            if(menu[i].Itemid == id) {
                for(int j = i; j < menuCount - 1; j++)
                    menu[j] = menu[j+1];
                menuCount--;
                cout << "Menu item removed\n";
                return;
            }
        }
        cout << "Item not found\n";
    }

    void updateMenuItem(int id, float newPrice) {
        for(int i = 0; i < menuCount; i++) {
            if(menu[i].Itemid == id) { menu[i].updatePrice(newPrice); return; }
        }
        cout << "Item not found\n";
    }

    void searchMenuItem(int id) const {
        for(int i = 0; i < menuCount; i++) {
            if(menu[i].Itemid == id) { cout << "Item found:\n"; menu[i].get(); return; }
        }
        cout << "Item not found\n";
    }

    void toggleOpen() {
        isOpen = !isOpen;
        cout << "Restaurant is now " << (isOpen ? "Open" : "Closed") << endl;
    }

    float getAverageRating() const { return rating; }
    int getMenuCount() const { return menuCount; }

    // FIX: Save/load helpers for persistence
    void saveToFile(ofstream& file) const {
        if(Restaurantid == -1) return;
        file << Restaurantid << "|" << name << "|" << address << "|"
             << rating << "|" << isOpen << "|" << menuCount << "\n";
        for(int i = 0; i < menuCount; i++) {
            file << "ITEM|" << menu[i].Itemid << "|" << menu[i].name << "|"
                 << menu[i].catagory << "|" << menu[i].price << "|"
                 << menu[i].isAvailable << "\n";
        }
    }

    friend class Owner;
    friend void saveRestaurants(const Restaurant[], int);
    friend void loadRestaurants(Restaurant[], int&);
};

// ─────────────────────────────────────────────────────────
// Cart
// ─────────────────────────────────────────────────────────
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
        if(!m.getAvailable()) { cout << "Sorry, this item is currently unavailable.\n"; return; }
        for(int i = 0; i < count; i++) {
            if(items[i].Itemid == m.Itemid) {
                quantity[i]++;
                cout << "Quantity increased. Now: " << quantity[i] << "\n";
                return;
            }
        }
        if(count >= 100) { cout << "Cart is full\n"; return; }
        items[count] = m;
        quantity[count] = 1;
        count++;
        cout << "\"" << m.getName() << "\" added to cart.\n";
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
                if(q <= 0) { removeItem(id); return; }
                quantity[i] = q;
                cout << "Quantity updated to " << q << "\n";
                return;
            }
        }
        cout << "Item not found in cart\n";
    }

    float calculateTotal() const {
        float total = 0;
        for(int i = 0; i < count; i++)
            total += items[i].price * quantity[i];
        return total;
    }

    void clearCart() {
        count = 0;
        cout << "Cart cleared\n";
    }

    void displayCart() const {
        if(count == 0) { cout << "Cart is empty\n"; return; }
        cout << "\n--- Cart Items ---\n";
        for(int i = 0; i < count; i++) {
            cout << items[i].getName() << " x" << quantity[i]
                 << "  =  Rs." << items[i].price * quantity[i] << "\n";
        }
        cout << "Total: Rs." << calculateTotal() << "\n";
        cout << "------------------\n";
    }

    int getCount() const { return count; }
    float getTotal() const { return calculateTotal(); }
};

// ─────────────────────────────────────────────────────────
// Order
// ─────────────────────────────────────────────────────────
class Order {
    private:
    int orderId;
    string status;
    Cart cart;
    string deliveryPerson;
    int deliveryTime;
    string paymentMethod;

    public:
    Order() {
        orderId = 0;
        status = "None";
        deliveryPerson = "Not Assigned";
        deliveryTime = 0;
        paymentMethod = "Not selected";
    }

    Order(int id, Cart c, string payment) {
        orderId = id;
        cart = c;
        status = "Created";
        deliveryPerson = "Not Assigned";
        deliveryTime = 0;
        paymentMethod = payment;
    }

    void placeOrder() {
        status = "Placed";
        cout << "Order placed successfully!\n";
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

    void displayOrderDetails() const {
        cout << "\n=== Order #" << orderId << " ===\n";
        cout << "Status         : " << status << "\n";
        cout << "Payment Method : " << paymentMethod << "\n";
        cout << "Delivery Person: " << deliveryPerson << "\n";
        cout << "Delivery Time  : " << deliveryTime << " minutes\n";
        cart.displayCart();
    }

    int getId() const { return orderId; }
    string getStatus() const { return status; }
};

// ─────────────────────────────────────────────────────────
// Payment classes
// ─────────────────────────────────────────────────────────
class Payment {
    public:
    virtual void processPayment(float amount) = 0;
    virtual ~Payment() {}

    void validatePayment() { cout << "Payment validated\n"; }
    void generateReceipt(float amount) {
        cout << "Receipt generated for amount: Rs." << amount << "\n";
    }
};

class CreditCard : public Payment {
    public:
    void processPayment(float amount) {
        cout << "Processing credit card payment of Rs." << amount << "\n";
        validateCard();
        validatePayment();
        generateReceipt(amount);
    }
    void validateCard() { cout << "Card details verified.\n"; }
};

class UPI : public Payment {
    public:
    void processPayment(float amount) {
        cout << "Processing UPI payment of Rs." << amount << "\n";
        validateUPI();
        validatePayment();
        generateReceipt(amount);
    }
    void validateUPI() { cout << "UPI ID verified.\n"; }
};

class COD : public Payment {
    public:
    void processPayment(float amount) {
        cout << "Cash on delivery selected. Amount to pay: Rs." << amount << "\n";
        confirmCOD();
        generateReceipt(amount);
    }
    void confirmCOD() { cout << "You will pay at the time of delivery.\n"; }
};

// ─────────────────────────────────────────────────────────
// Customer
// ─────────────────────────────────────────────────────────
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
    }

    // FIX: Show all restaurants that have been added, not just 'n' of them
    void browseRestaurants(Restaurant restaurants[], int total) {
        bool any = false;
        cout << "\n========== Available Restaurants ==========\n";
        for(int i = 0; i < total; i++) {
            if(restaurants[i].getId() != -1) {
                any = true;
                cout << "\nRestaurant ID : " << restaurants[i].getId() << "\n";
                cout << "Name          : " << restaurants[i].getName() << "\n";
                cout << "Address       : " << restaurants[i].getAddress() << "\n";
                cout << "Rating        : " << restaurants[i].getAverageRating() << "/5\n";
                cout << "Status        : " << (restaurants[i].getIsOpen() ? "Open" : "Closed") << "\n";
                cout << "--- Menu ---\n";
                restaurants[i].displayMenu();
            }
        }
        if(!any) cout << "No restaurants available yet.\n";
        cout << "===========================================\n";
    }

    void addToCart(MenuItem item) { cart.addItem(item); }
    void displayCart()            { cart.displayCart(); }

    // FIX: Accept paymentMethod parameter and pass to Order
    void placeOrder(string paymentMethod) {
        if(cart.getCount() == 0) {
            cout << "Cart is empty. Add items before placing order.\n";
            return;
        }

        // Process payment
        float total = cart.getTotal();
        Payment* pay = nullptr;
        if(paymentMethod == "1") {
            pay = new CreditCard();
            paymentMethod = "Credit Card";
        } else if(paymentMethod == "2") {
            pay = new UPI();
            paymentMethod = "UPI";
        } else {
            pay = new COD();
            paymentMethod = "Cash on Delivery";
        }
        pay->processPayment(total);
        delete pay;

        Order newOrder(orderCount + 1, cart, paymentMethod);
        newOrder.placeOrder();
        newOrder.calculateDeliveryTime();
        orderHistory[orderCount++] = newOrder;
        cart.clearCart();
    }

    void viewOrderHistory() {
        if(orderCount == 0) { cout << "No orders placed yet.\n"; return; }
        cout << "\n=== Order History (" << orderCount << " orders) ===\n";
        for(int i = 0; i < orderCount; i++)
            orderHistory[i].displayOrderDetails();
    }

    void removeFromCart(int id) { cart.removeItem(id); }

    void updateCartQuantity(int id, int q) { cart.updateQuantity(id, q); }

    string getAddress() const { return address; }

    friend void saveCustomers(const Customer[], int);
    friend void loadCustomers(Customer[], int&);
};

// ─────────────────────────────────────────────────────────
// Owner
// ─────────────────────────────────────────────────────────
class Owner : public User {
    private:
    int ownedRestaurantIds[100];
    int resCount;

    public:
    Owner() : User() { resCount = 0; }

    Owner(int id, string nm, string em, string pass, string ph)
        : User(id, nm, em, pass, ph) {
        resCount = 0;
    }

    void addOwnedRestaurantId(int rid) {
        ownedRestaurantIds[resCount++] = rid;
    }

    void viewAllOrders() {
        cout << "Order viewing by owner: feature coming in next version.\n";
    }

    friend void saveOwners(const Owner[], int);
    friend void loadOwners(Owner[], int&);
};

// ─────────────────────────────────────────────────────────
// DeliveryPerson
// ─────────────────────────────────────────────────────────
class DeliveryPerson : public User {
    private:
    bool isAvailable;
    string currentArea;
    int deliveriesCount;

    public:
    DeliveryPerson() : User() {
        isAvailable = true; currentArea = ""; deliveriesCount = 0;
    }

    DeliveryPerson(int id, string nm, string em, string pass, string ph)
        : User(id, nm, em, pass, ph) {
        isAvailable = true; currentArea = ""; deliveriesCount = 0;
    }

    void acceptOrder(int orderId) {
        isAvailable = false;
        cout << "Order " << orderId << " accepted\n";
    }

    void completeDelivery() {
        isAvailable = true;
        deliveriesCount++;
        cout << "Delivery completed! Total deliveries: " << deliveriesCount << "\n";
    }

    void updateLocation(string area) {
        currentArea = area;
        cout << "Location updated to: " << currentArea << "\n";
    }

    void viewAssignedOrders() {
        cout << "No orders currently assigned.\n";
    }

    friend void saveDeliveryPersons(const DeliveryPerson[], int);
    friend void loadDeliveryPersons(DeliveryPerson[], int&);
};

// ─────────────────────────────────────────────────────────
// Global arrays — on heap to avoid stack overflow
// ─────────────────────────────────────────────────────────
const int MAX = 100;
Restaurant    restaurants[MAX];
Customer      customers[MAX];
Owner         owners[MAX];
DeliveryPerson deliveryPersons[MAX];
int restCount = 0, custCount = 0, ownCount = 0, dpCount = 0;

// ─────────────────────────────────────────────────────────
// Persistence helpers
// ─────────────────────────────────────────────────────────
void saveRestaurants(const Restaurant arr[], int n) {
    ofstream file("restaurants.txt");
    if(!file) return;
    for(int i = 0; i < n; i++) arr[i].saveToFile(file);
    file.close();
}

void loadRestaurants(Restaurant arr[], int& n) {
    ifstream file("restaurants.txt");
    if(!file) return;
    n = 0;
    string line;
    while(getline(file, line)) {
        if(line.empty()) continue;
        if(line.substr(0,5) == "ITEM|") {
            // Attach to last restaurant
            if(n == 0) continue;
            stringstream ss(line.substr(5));
            string s1,s2,s3,s4,s5;
            getline(ss,s1,'|'); getline(ss,s2,'|'); getline(ss,s3,'|');
            getline(ss,s4,'|'); getline(ss,s5,'|');
            MenuItem m;
            m.enterItemDetails(stoi(s1), s2, s3, stof(s4), stoi(s5));
            arr[n-1].addMenuItem(m);
        } else {
            stringstream ss(line);
            string s1,s2,s3,s4,s5,s6;
            getline(ss,s1,'|'); getline(ss,s2,'|'); getline(ss,s3,'|');
            getline(ss,s4,'|'); getline(ss,s5,'|'); getline(ss,s6,'|');
            arr[n] = Restaurant(stoi(s1), s2, s3, stof(s4), stoi(s5));
            n++;
        }
    }
    file.close();
}

void saveCustomers(const Customer arr[], int n) {
    ofstream file("customers.txt");
    if(!file) return;
    for(int i = 0; i < n; i++) {
        if(arr[i].Userid == -1) continue;
        file << arr[i].Userid << "|" << arr[i].name << "|" << arr[i].email
             << "|" << arr[i].password << "|" << arr[i].phone
             << "|" << arr[i].address << "\n";
    }
    file.close();
}

void loadCustomers(Customer arr[], int& n) {
    ifstream file("customers.txt");
    if(!file) return;
    n = 0;
    string line;
    while(getline(file, line)) {
        if(line.empty()) continue;
        stringstream ss(line);
        string s1,s2,s3,s4,s5,s6;
        getline(ss,s1,'|'); getline(ss,s2,'|'); getline(ss,s3,'|');
        getline(ss,s4,'|'); getline(ss,s5,'|'); getline(ss,s6);
        arr[n++] = Customer(stoi(s1), s2, s3, s4, s5, s6);
    }
    file.close();
}

void saveOwners(const Owner arr[], int n) {
    ofstream file("owners.txt");
    if(!file) return;
    for(int i = 0; i < n; i++) {
        if(arr[i].Userid == -1) continue;
        file << arr[i].Userid << "|" << arr[i].name << "|" << arr[i].email
             << "|" << arr[i].password << "|" << arr[i].phone << "\n";
    }
    file.close();
}

void loadOwners(Owner arr[], int& n) {
    ifstream file("owners.txt");
    if(!file) return;
    n = 0;
    string line;
    while(getline(file, line)) {
        if(line.empty()) continue;
        stringstream ss(line);
        string s1,s2,s3,s4,s5;
        getline(ss,s1,'|'); getline(ss,s2,'|'); getline(ss,s3,'|');
        getline(ss,s4,'|'); getline(ss,s5);
        arr[n++] = Owner(stoi(s1), s2, s3, s4, s5);
    }
    file.close();
}

void saveDeliveryPersons(const DeliveryPerson arr[], int n) {
    ofstream file("delivery_persons.txt");
    if(!file) return;
    for(int i = 0; i < n; i++) {
        if(arr[i].Userid == -1) continue;
        file << arr[i].Userid << "|" << arr[i].name << "|" << arr[i].email
             << "|" << arr[i].password << "|" << arr[i].phone << "\n";
    }
    file.close();
}

void loadDeliveryPersons(DeliveryPerson arr[], int& n) {
    ifstream file("delivery_persons.txt");
    if(!file) return;
    n = 0;
    string line;
    while(getline(file, line)) {
        if(line.empty()) continue;
        stringstream ss(line);
        string s1,s2,s3,s4,s5;
        getline(ss,s1,'|'); getline(ss,s2,'|'); getline(ss,s3,'|');
        getline(ss,s4,'|'); getline(ss,s5);
        arr[n++] = DeliveryPerson(stoi(s1), s2, s3, s4, s5);
    }
    file.close();
}

// ─────────────────────────────────────────────────────────
// Helper: find restaurant in global array by ID
// ─────────────────────────────────────────────────────────
Restaurant* findRestaurantById(int id) {
    for(int i = 0; i < restCount; i++)
        if(restaurants[i].getId() == id) return &restaurants[i];
    return nullptr;
}

// ─────────────────────────────────────────────────────────
// main
// ─────────────────────────────────────────────────────────
int main() {
    loadCustomers(customers, custCount);
    loadOwners(owners, ownCount);
    loadDeliveryPersons(deliveryPersons, dpCount);
    loadRestaurants(restaurants, restCount);  // FIX: load restaurants too

    int choice;

    while(true) {
        cout << "\n========== FoodFast ==========\n";
        cout << "1. Login as Customer\n";
        cout << "2. Login as Owner\n";
        cout << "3. Login as Delivery Person\n";
        cout << "4. Register\n";
        cout << "5. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        // ── CUSTOMER LOGIN ─────────────────────────────────
        if(choice == 1) {
            string email, pass;
            cout << "Email: "; cin >> email;
            cout << "Password: "; cin >> pass;

            Customer* loggedIn = nullptr;
            for(int i = 0; i < custCount; i++) {
                if(customers[i].authenticate(email, pass)) {
                    loggedIn = &customers[i];
                    break;
                }
            }

            if(!loggedIn) { cout << "Invalid credentials!\n"; continue; }

            // FIX: Mark as logged in
            loggedIn->setLogin(true);
            cout << "Welcome, " << loggedIn->getId() << "!\n";

            // FIX: Track which restaurant the customer is browsing by ID (not name)
            int selectedRestaurantId = -1;

            while(true) {
                cout << "\n=== Customer Menu ===\n";
                cout << "1. Browse Restaurants\n";
                cout << "2. View Cart\n";
                cout << "3. Add Item to Cart\n";
                cout << "4. Remove Item from Cart\n";
                cout << "5. Update Item Quantity\n";
                cout << "6. Place Order\n";
                cout << "7. View Order History\n";
                cout << "8. Update Profile\n";
                cout << "9. Logout\n";
                cout << "Enter Choice: ";
                int c; cin >> c;

                if(c == 9) { loggedIn->logout(); break; }

                switch(c) {
                    case 1: {
                        // FIX: Show all restaurants, then ask user to pick by ID
                        loggedIn->browseRestaurants(restaurants, restCount);
                        if(restCount > 0) {
                            cout << "Enter Restaurant ID to select (or -1 to skip): ";
                            cin >> selectedRestaurantId;
                            Restaurant* r = findRestaurantById(selectedRestaurantId);
                            if(!r || r->getId() == -1) {
                                cout << "Restaurant not found.\n";
                                selectedRestaurantId = -1;
                            } else {
                                cout << "Selected: " << r->getName() << "\n";
                            }
                        }
                        break;
                    }
                    case 2:
                        loggedIn->displayCart();
                        break;

                    case 3: {
                        if(selectedRestaurantId == -1) {
                            cout << "Please browse and select a restaurant first (option 1).\n";
                            break;
                        }
                        Restaurant* r = findRestaurantById(selectedRestaurantId);
                        if(!r) { cout << "Restaurant not found.\n"; break; }
                        cout << "Menu of " << r->getName() << ":\n";
                        r->displayMenu();
                        int itemId;
                        cout << "Enter Item ID to add to cart: ";
                        cin >> itemId;
                        MenuItem* item = r->getMenuItemById(itemId);
                        if(item) loggedIn->addToCart(*item);
                        else cout << "Item not found.\n";
                        break;
                    }
                    case 4: {
                        loggedIn->displayCart();
                        int id; cout << "Enter Item ID to remove: "; cin >> id;
                        loggedIn->removeFromCart(id);
                        break;
                    }
                    case 5: {
                        loggedIn->displayCart();
                        int id, q;
                        cout << "Enter Item ID: "; cin >> id;
                        cout << "Enter new quantity (0 to remove): "; cin >> q;
                        loggedIn->updateCartQuantity(id, q);
                        break;
                    }
                    case 6: {
                        loggedIn->displayCart();
                        if(loggedIn->getId() == -1) break; // safety
                        cout << "\nSelect Payment Method:\n";
                        cout << "1. Credit Card\n2. UPI\n3. Cash on Delivery\n";
                        cout << "Enter Choice: ";
                        string pm; cin >> pm;
                        loggedIn->placeOrder(pm);
                        break;
                    }
                    case 7:
                        loggedIn->viewOrderHistory();
                        break;
                    case 8:
                        loggedIn->updateProfile();
                        saveCustomers(customers, custCount); // persist changes
                        break;
                    default:
                        cout << "Invalid option\n";
                }
            }
        }

        // ── OWNER LOGIN ────────────────────────────────────
        else if(choice == 2) {
            string email, pass;
            cout << "Email: "; cin >> email;
            cout << "Password: "; cin >> pass;

            Owner* loggedIn = nullptr;
            for(int i = 0; i < ownCount; i++) {
                if(owners[i].authenticate(email, pass)) {
                    loggedIn = &owners[i];
                    break;
                }
            }

            if(!loggedIn) { cout << "Invalid credentials!\n"; continue; }

            loggedIn->setLogin(true);
            cout << "Welcome, Owner!\n";

            while(true) {
                cout << "\n=== Owner Menu ===\n";
                cout << "1. Add Restaurant\n";
                cout << "2. Add Menu Item to Restaurant\n";
                cout << "3. Remove Menu Item\n";
                cout << "4. Update Menu Item Price\n";
                cout << "5. Toggle Restaurant Open/Closed\n";
                cout << "6. View All Restaurants\n";
                cout << "7. Logout\n";
                cout << "Enter Choice: ";
                int c; cin >> c;

                if(c == 7) { loggedIn->logout(); break; }

                switch(c) {
                    case 1: {
                        int id; string rname, address; float rating; bool isOpen;
                        cout << "Enter Restaurant ID: "; cin >> id;
                        if(findRestaurantById(id)) { cout << "Restaurant ID already exists.\n"; break; }
                        cout << "Enter Name: "; cin.ignore(); getline(cin, rname);
                        cout << "Enter Address: "; getline(cin, address);
                        cout << "Enter Rating (0-5): "; cin >> rating;
                        cout << "Is Open? (1=Yes, 0=No): "; cin >> isOpen;
                        if(restCount >= MAX) { cout << "Max restaurants reached.\n"; break; }
                        restaurants[restCount++] = Restaurant(id, rname, address, rating, isOpen);
                        loggedIn->addOwnedRestaurantId(id);
                        cout << "Restaurant added!\n";
                        saveRestaurants(restaurants, restCount);
                        break;
                    }
                    case 2: {
                        int resId, itemId; string iname, cat; float price; bool avail;
                        cout << "Enter Restaurant ID: "; cin >> resId;
                        Restaurant* r = findRestaurantById(resId);
                        if(!r) { cout << "Restaurant not found.\n"; break; }
                        cout << "Enter Item ID: "; cin >> itemId;
                        cout << "Enter Item Name: "; cin.ignore(); getline(cin, iname);
                        cout << "Enter Category: "; getline(cin, cat);
                        cout << "Enter Price: "; cin >> price;
                        cout << "Available? (1=Yes, 0=No): "; cin >> avail;
                        MenuItem newItem;
                        newItem.enterItemDetails(itemId, iname, cat, price, avail);
                        r->addMenuItem(newItem);  // FIX: Only add once, to global array
                        saveRestaurants(restaurants, restCount);
                        break;
                    }
                    case 3: {
                        int resId, itemId;
                        cout << "Enter Restaurant ID: "; cin >> resId;
                        Restaurant* r = findRestaurantById(resId);
                        if(!r) { cout << "Restaurant not found.\n"; break; }
                        r->displayMenu();
                        cout << "Enter Item ID to remove: "; cin >> itemId;
                        r->removeMenuItem(itemId);
                        saveRestaurants(restaurants, restCount);
                        break;
                    }
                    case 4: {
                        int resId, itemId; float newPrice;
                        cout << "Enter Restaurant ID: "; cin >> resId;
                        Restaurant* r = findRestaurantById(resId);
                        if(!r) { cout << "Restaurant not found.\n"; break; }
                        r->displayMenu();
                        cout << "Enter Item ID: "; cin >> itemId;
                        cout << "Enter new price: "; cin >> newPrice;
                        r->updateMenuItem(itemId, newPrice);
                        saveRestaurants(restaurants, restCount);
                        break;
                    }
                    case 5: {
                        int resId;
                        cout << "Enter Restaurant ID: "; cin >> resId;
                        Restaurant* r = findRestaurantById(resId);
                        if(!r) { cout << "Restaurant not found.\n"; break; }
                        r->toggleOpen();
                        saveRestaurants(restaurants, restCount);
                        break;
                    }
                    case 6: {
                        if(restCount == 0) { cout << "No restaurants yet.\n"; break; }
                        for(int i = 0; i < restCount; i++) {
                            cout << "\nID: " << restaurants[i].getId()
                                 << " | Name: " << restaurants[i].getName()
                                 << " | " << (restaurants[i].getIsOpen() ? "Open" : "Closed") << "\n";
                            restaurants[i].displayMenu();
                        }
                        break;
                    }
                    default: cout << "Invalid option\n";
                }
            }
        }

        // ── DELIVERY PERSON LOGIN ──────────────────────────
        else if(choice == 3) {
            string email, pass;
            cout << "Email: "; cin >> email;
            cout << "Password: "; cin >> pass;

            DeliveryPerson* loggedIn = nullptr;
            for(int i = 0; i < dpCount; i++) {
                if(deliveryPersons[i].authenticate(email, pass)) {
                    loggedIn = &deliveryPersons[i];
                    break;
                }
            }

            if(!loggedIn) { cout << "Invalid credentials!\n"; continue; }

            loggedIn->setLogin(true);
            cout << "Welcome, Delivery Partner!\n";

            while(true) {
                cout << "\n=== Delivery Person Menu ===\n";
                cout << "1. View Assigned Orders\n";
                cout << "2. Update Location\n";
                cout << "3. Complete Delivery\n";
                cout << "4. Logout\n";
                cout << "Enter Choice: ";
                int c; cin >> c;

                if(c == 4) { loggedIn->logout(); break; }

                switch(c) {
                    case 1: loggedIn->viewAssignedOrders(); break;
                    case 2: {
                        string area;
                        cout << "Enter your current area: ";
                        cin.ignore(); getline(cin, area);
                        loggedIn->updateLocation(area);
                        break;
                    }
                    case 3: loggedIn->completeDelivery(); break;
                    default: cout << "Invalid option\n";
                }
            }
        }

        // ── REGISTER ───────────────────────────────────────
        else if(choice == 4) {
            cout << "Register as:\n1. Customer\n2. Owner\n3. Delivery Person\n";
            cout << "Enter Choice: ";
            int type; cin >> type;

            if(type == 1) {
                if(custCount >= MAX) { cout << "Max customers reached.\n"; continue; }
                int id; string nm, em, pass, ph, addr;
                cout << "Enter ID: "; cin >> id;
                // FIX: Check for duplicate ID
                for(int i=0;i<custCount;i++) if(customers[i].getId()==id){cout<<"ID taken.\n";goto done;}
                cout << "Enter Name: "; cin.ignore(); getline(cin, nm);
                cout << "Enter Email: "; cin >> em;
                cout << "Enter Password: "; cin >> pass;
                cout << "Enter Phone: "; cin >> ph;
                cout << "Enter Address: "; cin.ignore(); getline(cin, addr);
                customers[custCount++] = Customer(id, nm, em, pass, ph, addr);
                cout << "Customer registered!\n";
                saveCustomers(customers, custCount);
            }
            else if(type == 2) {
                if(ownCount >= MAX) { cout << "Max owners reached.\n"; continue; }
                int id; string nm, em, pass, ph;
                cout << "Enter ID: "; cin >> id;
                for(int i=0;i<ownCount;i++) if(owners[i].getId()==id){cout<<"ID taken.\n";goto done;}
                cout << "Enter Name: "; cin.ignore(); getline(cin, nm);
                cout << "Enter Email: "; cin >> em;
                cout << "Enter Password: "; cin >> pass;
                cout << "Enter Phone: "; cin >> ph;
                owners[ownCount++] = Owner(id, nm, em, pass, ph);
                cout << "Owner registered!\n";
                saveOwners(owners, ownCount);
            }
            else if(type == 3) {
                if(dpCount >= MAX) { cout << "Max delivery persons reached.\n"; continue; }
                int id; string nm, em, pass, ph;
                cout << "Enter ID: "; cin >> id;
                for(int i=0;i<dpCount;i++) if(deliveryPersons[i].getId()==id){cout<<"ID taken.\n";goto done;}
                cout << "Enter Name: "; cin.ignore(); getline(cin, nm);
                cout << "Enter Email: "; cin >> em;
                cout << "Enter Password: "; cin >> pass;
                cout << "Enter Phone: "; cin >> ph;
                deliveryPersons[dpCount++] = DeliveryPerson(id, nm, em, pass, ph);
                cout << "Delivery Person registered!\n";
                saveDeliveryPersons(deliveryPersons, dpCount);
            }
            else cout << "Invalid type.\n";
            done:;
        }

        // ── EXIT ───────────────────────────────────────────
        else if(choice == 5) {
            cout << "Saving data...\n";
            saveCustomers(customers, custCount);
            saveOwners(owners, ownCount);
            saveDeliveryPersons(deliveryPersons, dpCount);
            saveRestaurants(restaurants, restCount);
            cout << "Thank you for using FoodFast!\n";
            return 0;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}
