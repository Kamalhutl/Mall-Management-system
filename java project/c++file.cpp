#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>
#include <limits>
#include <string>
#include <map>
#include <iomanip>

#ifdef _WIN32
  #include <conio.h>
  #include <windows.h>
#else
  // Provide a simple _getch fallback for non-Windows (press Enter to send a char)
  #include <termios.h>
  #include <unistd.h>
  static int _getch() {
      struct termios oldt, newt;
      int ch;
      tcgetattr(STDIN_FILENO, &oldt);
      newt = oldt;
      newt.c_lflag &= ~(ICANON | ECHO);
      tcsetattr(STDIN_FILENO, TCSANOW, &newt);
      ch = getchar();
      tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
      return ch;
  }
#endif

using namespace std;

#define RESET "\033[0m"
#define CYAN "\033[36m"
#define YELLOW "\033[33m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define RED "\033[31m"
#define BOLD "\033[1m"

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void centerPrint(const string &text)
{
    int padding = 60;
    for (int i = 0; i < padding; ++i) cout << " ";
    cout << text << endl;
}

struct Shop
{
    string name;
    int floor;
    string description;
    string timing;
    vector<string> items;
};

class Mall
{
public:
    bool Welcome()
    {
        string reset = "\033[0m";
        string bright_cyan = "\033[96m";
        string bright_magenta = "\033[95m";
        string bright_yellow = "\033[93m";

        cout << endl;
        cout << bright_yellow << "                                                            HELLO CUSTOMER !!!!!!!!!!!!!!!!" << reset << endl;
        cout << bright_cyan << "                                                 Would you like to drop yourself into a new world of experience?" << reset << endl;
        cout << bright_magenta << "                                                     If YES press Enter........If NO press any other key" << reset << endl;

        char ch = _getch();
        return (ch == 13 || ch == '\n');
    }

    void clear_screen()
    {
        clearScreen();
    }

    void Logo()
    {
        string reset = "\033[0m";
        string bright_green = "\033[92m";
        string bright_yellow = "\033[93m";
        string bright_cyan = "\033[96m";
        string bright_magenta = "\033[95m";
        string bold = "\033[1m";

        cout << bright_green << "                                                                   ======================================" << reset << endl;
        cout << bright_green << "                                                                   |" << reset << "                                      " << bright_green << "|" << reset << endl;
        cout << bright_green << "                                                                   |" << reset << bold << bright_yellow << "        Welcome To The Opera          " << reset << bright_green << "|" << reset << endl;
        cout << bright_green << "                                                                   |" << reset << bright_cyan << "         where people can             " << reset << bright_green << "|" << reset << endl;
        cout << bright_green << "                                                                   |" << reset << bright_magenta << "            shop Dreams               " << reset << bright_green << "|" << reset << endl;
        cout << bright_green << "                                                                   ======================================" << reset << endl;
    }
};

class Parking
{
private:
    string name;
    long long mobile_no;
    string carId;
    long Parking_ID;
    int wheeler;
    double fare;
    string parking_time;

public:
    Parking()
    {
        cout << "                                                            Enter Your Name:" << endl;
        getline(cin >> ws, name);

        cout << "                                                           Enter Your Mobile Number:" << endl;
        while(!(cin >> mobile_no)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid number. Enter again: ";
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "                                                           Enter Your Car Plate ID:" << endl;
        getline(cin, carId);

        cout << "                                                   Enter Whether Your Vehicle Is 2 Wheeler or 4 Wheeler (enter 2 or 4):" << endl;
        while(!(cin >> wheeler) || (wheeler != 2 && wheeler != 4)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter 2 or 4: ";
        }

        Parking_ID = rand();

        time_t now = time(0);
        tm *ltm = localtime(&now);

        char buffer[80];
        strftime(buffer, sizeof(buffer), "%d-%b-%Y %I:%M %p", ltm);
        parking_time = string(buffer);
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear newline
    }

    void Information()
    {
        cout << "\n\n\033[93m                                                          ==================================\033[0m" << endl;
        cout << "\033[1m\033[96m                                                           PARKING CHARGES INFORMATION\033[0m" << endl;
        cout << "\033[93m                                                          ==================================\033[0m" << endl;

        cout << "                                                          Price Of 2 Wheeler Vehicle: \033[93m30 $\033[0m" << endl;
        cout << "                                                          Price Of 4 Wheeler Vehicle: \033[93m50 $\033[0m" << endl;
        cout << "                                                          Maintenance Charges:        \033[93m0.25 $\033[0m" << endl;
        cout << "                                                          Other Charges:              \033[93m0.75 $\033[0m" << endl;
    }

    void Price()
    {
        // Use base prices consistent with Information()
        double base = (wheeler == 2) ? 30.0 : 50.0;
        fare = base + (base * 0.18) + 10.0 + 0.75;
    }

    void display()
    {
        cout << endl;
        cout << "\033[93m                                                           ==============================\033[0m" << endl;
        cout << "\033[1m\033[96m                                                                    BILL RECEIPT\033[0m" << endl;
        cout << "\033[93m                                                           ==============================\033[0m" << endl;

        cout << "                                                           Name:               " << name << endl;
        cout << "                                                           Mobile Number:      " << mobile_no << endl;
        cout << "                                                           Car Plate ID:       " << carId << endl;
        cout << "                                                           Parking ID:         " << Parking_ID << endl;
        cout << "                                                           Vehicle Type:       " << wheeler << " wheeler" << endl;
        cout << "                                                           Parking Time:       " << parking_time << endl;
        cout << "                                                           Service Charges:    10 $" << endl;
        cout << "                                                           Other Charges:      0.75 $" << endl;
        cout << fixed << setprecision(2);
        cout << "                                                           Parking Charges:    " << fare << " $" << endl;
        cout << RESET;
    }
};

class navigation
{
    vector<string> categories;
    vector<vector<Shop>> shops;

    string indent = "                                                            "; // 60 spaces

    const string reset = "\033[0m";
    const string bright_yellow = "\033[93m";
    const string bright_cyan = "\033[96m";
    const string bright_magenta = "\033[95m";
    const string bold = "\033[1m";

public:
    navigation()
    {
        categories = {"Fashion", "Electronics", "Food Court", "Cinema", "Kids Section", "Grocery Store", "Home Decor"};

        shops = {
            {{"Zara", 1, "Trendy fashion apparel", "11AM–10PM"},
             {"H&M", 0, "Affordable styles", "11AM–10PM"},
             {"Nike", 2, "Sportswear & shoes", "11AM–10PM"},
             {"Levis", 0, "Denim in style", "11AM–10PM"},
             {"Adidas", 1, "Latest athletic footwear, apparel, and gear", "11AM–10PM"},
             {"Woodland", 2, "Explore rugged footwear, outdoor gear, and apparel", "11AM–10PM"},
             {"Lee Cooper", 0, "British style. Timeless denim", "11AM–10PM"},
             {"Forever 21", 1, "Trendy fashion for young adults", "11AM–10PM"},
             {"Puma", 2, "Performance apparel for every sport", "11AM–10PM"}},
            {{"Apple Store", 0, "Latest Apple gadgets", "11AM–10PM"},
             {"Samsung", 2, "Bringing the best in electronics to you", "11AM–10PM"},
             {"Sony", 1, "Smartphones and TVs", "10AM–9PM"},
             {"Croma", 2, "Smart choices for Smarter living", "10AM–9PM"},
             {"Reliance", 0, "Reliance — Delivering value, every day", "10AM–9PM"},
             {"One Plus", 2, "Crafted for those who demand more", "10AM–9PM"},
             {"Mi Store", 1, "Affordable innovation", "10AM–9PM"},
             {"HP World", 2, "Laptops, printers, and accessories", "10AM–9PM"}},
            {{"McDonald's", 3, "Fast food chain", "10AM–11PM"},
             {"Starbucks", 3, "Your daily coffee ritual", "10AM–11PM"},
             {"Pizza Hut", 3, "Pizzas and more", "10AM–11PM"},
             {"Dominos", 3, "Pizza made easy", "10AM–11PM"},
             {"Haldiram", 3, "Authentic food with unforgettable flavors", "10AM–11PM"},
             {"Bikanervala", 3, "Savor the legacy", "10AM–11PM"},
             {"Burger King", 3, "Home of the Whopper", "10AM–11PM"},
             {"Subway", 3, "Eat fresh", "10AM–11PM"}},
            {{"PVR Cinemas", 4, "Where movies come to life", "10AM–12PM"},
             {"Cinepolis", 4, "Experience cinema like never before", "10AM–12PM"},
             {"Carnival Cinema", 4, "Big screen, bigger experience", "10AM–12PM"},
             {"INOX", 4, "Entertainment beyond movies", "10AM–12PM"}},
            {{"Game Zone", 4, "The ultimate game playground", "11AM-10PM"},
             {"Hamleys", 4, "Hamleys — A playground of dreams", "11AM-10PM"},
             {"First Cry", 4, "Everything for your little one", "11AM-10PM"},
             {"Toys R Us", 4, "World's greatest toy store", "11AM-10PM"}},
            {{"Big Bazaar", 0, "Everyday essentials, everyday savings", "10AM-10PM"},
             {"Market 99", 1, "Bringing you more for less", "10AM-10PM"},
             {"D-Mart", 0, "Low prices. Great savings", "10AM–10PM"},
             {"Spencer’s", 0, "Fresh food & more", "10AM–10PM"}},
            {{"The Home Decor", 2, "Where your home comes to life", "11AM-10PM"},
             {"PepperFry", 1, "Furnishing your dreams, with love", "11AM-10PM"},
             {"Exclusive Interiors", 2, "Style, comfort, and quality — all in one place", "11AM-10PM"},
             {"Home Centre", 2, "Inspiring homes", "11AM-10PM"},
             {"FabIndia", 1, "Traditional yet modern furniture & decor", "11AM–10PM"}}};
    }

    void showCategories(int selected)
    {
        clearScreen();
        cout << "\n"
             << indent << bold << bright_cyan << "Select a Category:\n\n"
             << reset;
        cout << indent << bright_magenta << "[Press any other key to exit category selection]" << reset << "\n\n";
        for (int i = 0; i < categories.size(); ++i)
        {
            cout << indent;
            if (i == selected)
                cout << bright_yellow << "> " << categories[i] << reset << "\n\n";
            else
                cout << bright_cyan << "  " << categories[i] << reset << "\n\n";
        }
    }

    void showShops(int catIndex, int selected)
    {
        clearScreen();
        cout << "\n"
             << indent << bold << bright_cyan << "Shops in " << categories[catIndex] << ":\n\n"
             << reset;
        cout << indent << bright_magenta << "[Press Esc key to exit shop selection]" << reset << "\n\n";
        for (int i = 0; i < shops[catIndex].size(); ++i)
        {
            cout << indent;
            if (i == selected)
                cout << bright_yellow << "> " << shops[catIndex][i].name << reset << "\n\n";
            else
                cout << bright_cyan << "  " << shops[catIndex][i].name << reset << "\n\n";
        }
    }

    void showShopDetails(int catIndex, int shopIndex)
    {
        clearScreen();
        cout << "\n"
             << indent << bold << bright_cyan << "Details of " << shops[catIndex][shopIndex].name << ":\n\n"
             << reset;
        cout << indent << "Shop: " << shops[catIndex][shopIndex].name << endl;
        cout << indent << "Floor: " << shops[catIndex][shopIndex].floor << endl;
        cout << indent << "Description: " << shops[catIndex][shopIndex].description << endl;
        cout << indent << "Opening Hours: " << shops[catIndex][shopIndex].timing << endl;
    }

    void navigateShops()
    {
        int cat = 0;
        while (true)
        {
            cout << "Press Esc Key to Category Selection:" << endl;
            showCategories(cat);
            int key = _getch();
            if (key == 224) // Special key (arrow keys) on Windows
            {
                key = _getch();
                if (key == 72 && cat > 0)
                    cat--;
                else if (key == 80 && cat < (int)categories.size() - 1)
                    cat++;
            }
            else if (key == 13)
            { // Enter key
                int shopSel = 0;
                while (true)
                {
                    showShops(cat, shopSel);
                    int skey = _getch();
                    if (skey == 224)
                    {
                        skey = _getch();
                        if (skey == 72 && shopSel > 0)
                            shopSel--;
                        else if (skey == 80 && shopSel < (int)shops[cat].size() - 1)
                            shopSel++;
                    }
                    else if (skey == 13)
                    {
                        showShopDetails(cat, shopSel);
                        cout << "\n                                                            Press Enter to go back..." << endl;
                        _getch();
                    }
                    else if (skey == 27)
                    {
                        break;
                    }
                    else
                    {
                        return;
                    }
                }
            }
            else if (key == 27)
            {
                break;
            }
            else
            {
                return;
            }
        }
    }
};

class BillingSystem
{
private:
    map<string, double> cart;
    string customerName, paymentMode, cardNumber, cvv, upiId;
    Mall obj;

public:
    void selectItems(const map<string, double> &items)
    {
        int choice;
        vector<string> keys;
        int i = 1;
        cout << GREEN;
        centerPrint("Select items to add to your cart (0 to finish):");
        cout << RESET;

        for (const auto &item : items)
        {
            cout << "  " << i++ << ". " << item.first << " - $" << item.second << "\n";
            keys.push_back(item.first);
        }

        while (true)
        {
            cout << "\nEnter item number (or 0 to finish): ";
            if (!(cin >> choice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << RED << "Invalid input.\n" << RESET;
                continue;
            }
            if (choice == 0)
                break;
            if (choice > 0 && choice <= (int)keys.size())
            {
                cart[keys[choice - 1]] += items.at(keys[choice - 1]);
                cout << keys[choice - 1] << " added to cart.\n";
            }
            else
            {
                cout << RED << "Invalid selection.\n" << RESET;
            }
        }
    }

    void collectCustomerDetails()
    {
        obj.clear_screen();
        cout << YELLOW << "\n--- Enter Customer Details ---\n" << RESET;
        cout << "Name: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, customerName);
        cout << "Payment Mode (Card/Cash/UPI): ";
        getline(cin, paymentMode);

        if (paymentMode == "Card" || paymentMode == "card" || paymentMode == "CARD")
        {
            cout << "Credit Card Number: ";
            getline(cin, cardNumber);
            cout << "CVV: ";
            getline(cin, cvv);
        }
        else if (paymentMode == "UPI" || paymentMode == "upi" || paymentMode == "UPI")
        {
            cout << "Enter your UPI ID: ";
            getline(cin, upiId);
        }
    }

    void generateBill()
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);

        cout << MAGENTA << "\n========== Final Bill ==========\n" << RESET;
        cout << "Customer Name: " << customerName << endl;
        cout << "Payment Mode: " << paymentMode << endl;

        if (paymentMode == "Card" || paymentMode == "card" || paymentMode == "CARD")
        {
            cout << "Card Number: " << cardNumber << endl;
            cout << "CVV: " << cvv << endl;
        }
        else if (paymentMode == "UPI" || paymentMode == "upi" || paymentMode == "UPI")
        {
            cout << "UPI ID: " << upiId << endl;
        }

        cout << "Date: " << 1900 + ltm->tm_year << "-"
             << setfill('0') << setw(2) << 1 + ltm->tm_mon << "-"
             << setw(2) << ltm->tm_mday << "\n";
        cout << "Time: " << setw(2) << ltm->tm_hour << ":"
             << setw(2) << ltm->tm_min << endl;

        double total = 0;
        cout << "\nItems Purchased:\n";
        for (const auto &item : cart)
        {
            cout << "  - " << item.first << ": $" << fixed << setprecision(2) << item.second << endl;
            total += item.second;
        }

        cout << "\nTotal Amount: $" << fixed << setprecision(2) << total << endl;
        cout << MAGENTA << "===============================\n" << RESET;

        cout << GREEN << "\nPayment Successful! Thank you for shopping with us.\n" << RESET;
    }
};

class Lift
{
    BillingSystem billing;
    Mall obj;

public:
    Lift()
    {
        chooseFloor();
    }

    void chooseFloor()
    {
        obj.clear_screen();
        cout << BOLD << CYAN;
        centerPrint("===============================================");
        centerPrint("Welcome to the Mall's Smart Lift System!");
        centerPrint("===============================================\n");
        cout << RESET;
        int floor;
        cout << YELLOW;
        centerPrint("Choose the floor you'd like to visit:");
        centerPrint("1. Floor 1  (Fashion and Electronics)");
        centerPrint("2. Floor 2  (Food Court and Cinema)");
        centerPrint("3. Floor 3  (Kids Section and Grocery Store)");
        centerPrint("4. Floor 4  (Home Decor and Sports)");
        centerPrint("Enter your floor choice: ");
        cout << RESET;
        if (!(cin >> floor)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "Invalid input. Returning to lift menu.\n" << RESET;
            chooseFloor();
            return;
        }

        switch (floor)
        {
        case 1:
            floor1Sections();
            break;
        case 2:
            floor2Sections();
            break;
        case 3:
            floor3Sections();
            break;
        case 4:
            floor4Sections();
            break;
        default:
            cout << RED << "Invalid floor.\n" << RESET;
            chooseFloor();
        }
    }

    void floor1Sections()
    {
        centerPrint("1. Fashion ");
        centerPrint("2. Electronics");
        centerPrint("3. Enter your Choice");
        int sec;
        cin >> sec;
        if (sec == 1)
            showFashion();
        else if (sec == 2)
            showElectronics();
        else
            cout << RED << "Invalid\n" << RESET;
    }

    void floor2Sections()
    {
        centerPrint("1. Food Court");
        centerPrint("2. Cinema");
        centerPrint("Enter your choice:");
        int sec;
        cin >> sec;
        if (sec == 1)
            showFoodCourt();
        else if (sec == 2)
            showCinema();
        else
            cout << RED << "Invalid\n" << RESET;
    }

    void floor3Sections()
    {
        centerPrint("1. Kids");
        centerPrint("2. Grocery");
        centerPrint("Enter Your Choice:");
        int sec;
        cin >> sec;
        if (sec == 1)
            showKids();
        else if (sec == 2)
            showGrocery();
        else
            cout << RED << "Invalid\n" << RESET;
    }

    void floor4Sections()
    {
        centerPrint("1. Home Decor");
        centerPrint("2. Sports");
        centerPrint("3. Enter Your Choice:");
        int sec;
        cin >> sec;
        if (sec == 1)
            showHomeDecor();
        else if (sec == 2)
            showSports();
        else
            cout << RED << "Invalid\n" << RESET;
    }

    void showFashion()
    {
        obj.clear_screen();
        cout << MAGENTA << "\n           Choose a Fashion Store:\n" << RESET;
        cout << "             1. Zara\n";
        cout << "             2. H&M\n";
        cout << "             3. Levi's\n";
        cout << "             Enter your choice: ";
        int choice;
        cin >> choice;

        map<string, double> items;
        switch (choice)
        {
        case 1:
            items = { {"T-Shirts", 25}, {"Jeans", 40}, {"Jackets", 60}, {"Shoes", 50}, {"Pant", 60} };
            break;
        case 2:
            items = { {"Hoodies", 30}, {"Dresses", 45}, {"Skirts", 35}, {"Belts", 20}, {"Caps", 15} };
            break;
        case 3:
            items = { {"Denim Jackets", 70}, {"Slim Fit Jeans", 55}, {"Shirts", 35}, {"Tees", 25} };
            break;
        default:
            cout << RED << "Invalid store choice.\n" << RESET;
            return showFashion();
        }

        billing.selectItems(items);
        exitPrompt();
    }

    void showElectronics()
    {
        obj.clear_screen();
        int choice;
        cout << BLUE << "\n";
        cout << "                         ====== Electronics Shops ======\n";
        cout << RESET;
        cout << "                         1. Apple Store\n";
        cout << "                         2. Samsung\n";
        cout << "                         3. Sony\n";
        cout << "                         Enter your choice: ";
        cin >> choice;

        map<string, double> items;

        switch (choice)
        {
        case 1:
            items = { {"iPhone 15", 999}, {"MacBook Air", 1299}, {"AirPods", 199}, {"Apple Watch", 399}, {"iPad Pro", 1099}, {"Magic Mouse", 99}, {"iPhone 16 Pro", 1299} };
            break;
        case 2:
            items = { {"Galaxy S24", 899}, {"Smart TV", 499}, {"Galaxy Buds", 149}, {"Galaxy Tab S9", 699}, {"Refrigerator", 899}, {"Microwave Oven", 199} };
            break;
        case 3:
            items = { {"PlayStation 5", 499}, {"Sony Headphones", 120}, {"Sony Bravia TV", 999}, {"Sound Bar", 250}, {"Wireless Speaker", 180} };
            break;
        default:
            cout << RED << "                         Invalid store choice.\n" << RESET;
            return;
        }

        billing.selectItems(items);
        exitPrompt();
    }

    void showFoodCourt()
    {
        obj.clear_screen();
        cout << MAGENTA << "\n==================== FOOD COURT SHOPS ====================\n" << RESET;
        cout << "1. McDonald's\n";
        cout << "2. Starbucks\n";
        cout << "3. Domino's\n";
        cout << "4. KFC\n";
        cout << "Enter your preferred shop number: ";

        int choice;
        cin >> choice;

        map<string, double> items;

        switch (choice)
        {
        case 1:
            items = { {"Big Mac", 5}, {"Fries", 2}, {"Coke", 1.5}, {"McChicken", 4.5}, {"McFlurry", 3.0} };
            break;
        case 2:
            items = { {"Coffee", 4}, {"Muffin", 3}, {"Sandwich", 6}, {"Iced Latte", 4.5}, {"Croissant", 2.5} };
            break;
        case 3:
            items = { {"Margherita Pizza", 8}, {"Garlic Bread", 4}, {"Peppy Paneer", 9}, {"Stuffed Crust", 10}, {"Choco Lava Cake", 3} };
            break;
        case 4:
            items = { {"Zinger Burger", 6}, {"Popcorn Chicken", 4}, {"Chicken Bucket", 12}, {"Pepsi", 1.5}, {"Wings Combo", 7} };
            break;
        default:
            cout << RED << "Invalid shop selection.\n" << RESET;
            return;
        }

        cout << CYAN << "\nYou selected a menu from the shop. Please choose your items:\n" << RESET;
        billing.selectItems(items);
        exitPrompt();
    }

    void showCinema()
    {
        obj.clear_screen();
        cout << MAGENTA << "\n==================== CINEMA HALLS ====================\n" << RESET;
        cout << "1. PVR Cinemas\n";
        cout << "2. INOX\n";
        cout << "3. Cinepolis\n";
        cout << "4. Carnival Cinemas\n";
        cout << "Enter your preferred cinema: ";

        int choice;
        cin >> choice;

        map<string, double> items;

        switch (choice)
        {
        case 1:
            items = { {"Movie Ticket (Standard)", 12}, {"Popcorn", 5}, {"Coke", 3}, {"Nachos", 4}, {"3D Glasses", 2} };
            break;
        case 2:
            items = { {"Movie Ticket (Recliner)", 15}, {"Butter Popcorn", 6}, {"Pepsi", 3}, {"Samosa", 2}, {"Brownie", 3} };
            break;
        case 3:
            items = { {"Premium Ticket", 14}, {"Combo Meal", 8}, {"Lemonade", 2.5}, {"Chocolate Muffin", 2.5}, {"Salted Popcorn", 4} };
            break;
        case 4:
            items = { {"Budget Ticket", 10}, {"Mini Popcorn", 3}, {"Cola", 2}, {"Cheese Nachos", 5}, {"Ice Cream Cup", 2} };
            break;
        default:
            cout << RED << "Invalid cinema selection.\n" << RESET;
            return;
        }

        cout << CYAN << "\nYou selected items from the cinema. Please choose:\n" << RESET;
        billing.selectItems(items);
        exitPrompt();
    }

    void showKids()
    {
        obj.clear_screen();
        cout << MAGENTA << "\n==================== KIDS TOY STORES ====================\n" << RESET;
        cout << "1. Hamleys\n";
        cout << "2. Toys R Us\n";
        cout << "3. Lego Store\n";
        cout << "4. Funskool\n";
        cout << "Enter your preferred kids' store: ";

        int choice;
        cin >> choice;

        map<string, double> items;

        switch (choice)
        {
        case 1:
            items = { {"Plush Teddy Bear", 20}, {"Remote Control Car", 35}, {"Barbie Doll", 25}, {"Magic Drawing Pad", 15} };
            break;
        case 2:
            items = { {"Puzzle Box", 18}, {"Action Figures Set", 30}, {"Baby Rattle", 10}, {"Play Tent", 40} };
            break;
        case 3:
            items = { {"Lego Classic Bricks", 45}, {"Lego Technic Car", 60}, {"Lego Friends Set", 50}, {"Mini Lego City", 25} };
            break;
        case 4:
            items = { {"Board Game - Ludo", 12}, {"Craft Kit", 20}, {"Educational Blocks", 22}, {"Drawing Set", 18} };
            break;
        default:
            cout << RED << "Invalid kids' store selection.\n" << RESET;
            return;
        }

        cout << CYAN << "\nYou selected items from the kids' store. Please choose:\n" << RESET;
        billing.selectItems(items);
        exitPrompt();
    }

    void showGrocery()
    {
        obj.clear_screen();
        cout << BLUE << "\n==================== GROCERY STORES ====================\n" << RESET;
        cout << "1. Big Bazaar\n";
        cout << "2. Spencer's\n";
        cout << "3. Reliance Fresh\n";
        cout << "4. More\n";
        cout << "Enter your preferred grocery store: ";

        int choice;
        cin >> choice;

        map<string, double> items;

        switch (choice)
        {
        case 1:
            items = { {"Fresh Vegetables", 10}, {"Fruits (per kg)", 8}, {"Snacks Pack", 5}, {"Grocery Staples", 20} };
            break;
        case 2:
            items = { {"Beverages", 3}, {"Cereal Boxes", 6}, {"Snacks", 4}, {"Frozen Food", 15} };
            break;
        case 3:
            items = { {"Dairy Products", 4}, {"Cereals", 5}, {"Ice Cream", 7}, {"Breads", 2} };
            break;
        case 4:
            items = { {"Organic Vegetables", 12}, {"Packaged Meals", 10}, {"Canned Goods", 3}, {"Fresh Juices", 6} };
            break;
        default:
            cout << RED << "Invalid grocery store selection.\n" << RESET;
            return;
        }

        cout << CYAN << "\nYou selected items from the grocery store. Please choose:\n" << RESET;
        billing.selectItems(items);
        exitPrompt();
    }

    void showHomeDecor()
    {
        obj.clear_screen();
        cout << MAGENTA << "\n==================== HOME DECOR STORES ====================\n" << RESET;
        cout << "1. Home Centre\n";
        cout << "2. Pepperfry\n";
        cout << "3. IKEA\n";
        cout << "4. Urban Ladder\n";
        cout << "Enter your preferred home decor store: ";

        int choice;
        cin >> choice;

        map<string, double> items;

        switch (choice)
        {
        case 1:
            items = { {"Sofas", 299}, {"Curtains", 50}, {"Dining Tables", 150}, {"Wall Art", 30} };
            break;
        case 2:
            items = { {"Lighting", 60}, {"Dining Tables", 399}, {"Chairs", 120}, {"Wall Mirrors", 80} };
            break;
        case 3:
            items = { {"Storage Units", 120}, {"Carpets", 70}, {"Shelving Units", 90}, {"Curtains", 50} };
            break;
        case 4:
            items = { {"Modular Sofas", 500}, {"Coffee Tables", 150}, {"Wall Shelves", 40}, {"Rugs", 75} };
            break;
        default:
            cout << RED << "Invalid home decor store selection.\n" << RESET;
            return;
        }

        cout << CYAN << "\nYou selected items from the home decor store. Please choose:\n" << RESET;
        billing.selectItems(items);
        exitPrompt();
    }

    void showSports()
    {
        obj.clear_screen();
        cout << BLUE << "\n==================== SPORTS STORES ====================\n" << RESET;
        cout << "1. Nike\n";
        cout << "2. Adidas\n";
        cout << "3. Decathlon\n";
        cout << "4. Reebok\n";
        cout << "Enter your preferred sports store: ";

        int choice;
        cin >> choice;

        map<string, double> items;

        switch (choice)
        {
        case 1:
            items = { {"Sports Shoes", 90}, {"Gym Wear", 60}, {"Basketballs", 30}, {"Sports Bags", 40} };
            break;
        case 2:
            items = { {"Tracksuits", 75}, {"Footballs", 30}, {"Running Shoes", 85}, {"Gym Accessories", 50} };
            break;
        case 3:
            items = { {"Dumbbells", 50}, {"Yoga Mats", 25}, {"Sports Shoes", 70}, {"Rackets", 40} };
            break;
        case 4:
            items = { {"Fitness Gear", 60}, {"Trainers", 100}, {"Sports Watches", 150}, {"Cycling Gear", 120} };
            break;
        default:
            cout << RED << "Invalid sports store selection.\n" << RESET;
            return;
        }

        cout << CYAN << "\nYou selected items from the sports store. Please choose:\n" << RESET;
        billing.selectItems(items);
        exitPrompt();
    }

    void exitPrompt() {
        cout << GREEN << "\nPress ESC to finish shopping and generate bill..." << RESET;
        while (true) {
            int ch = _getch();
            if (ch == 27) break;
        }

        billing.collectCustomerDetails();
        billing.generateBill();
        cout << YELLOW << "\nWould you like to continue shopping or return to the lift system? (1: Continue Shopping, 2: Exit): " << RESET;
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = 2;
        }
        if (choice == 1) {
            chooseFloor();
        } else {
            cout << MAGENTA << "\nThank you for shopping with us. Have a great day!\n" << RESET;
            exit(0);
        }
    }
};

int main()
{
    srand((unsigned int)time(nullptr));

    Mall obj;
    navigation n1;
    obj.clear_screen();
    bool check = obj.Welcome();

    if (check)
    {
        obj.clear_screen();
        obj.Logo();
        cout << "\n\n                                                            Press ENTER to continue........!!!!!!" << endl;
        cin.get();

        obj.clear_screen();
        cout << "\n                                                            Press 1 if you are carrying a vehicle and 2 if not:" << endl;
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << RED << "Invalid input, exiting.\n" << RESET;
            return 0;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1)
        {
            obj.clear_screen();
            Parking park;

            obj.clear_screen();
            cin.get();
            cout << "\n                                                            Press ENTER to continue and check parking charges..............!!!!!!!!!!!!!!" << endl;
            cin.get();
            obj.clear_screen();
            park.Information();
            cout << "\n                                                            Press ENTER to see receipt..." << endl;
            cin.get();
            park.Price();
            obj.clear_screen();
            park.display();
            cout << "\n\n                                                            Press ENTER To Continue..." << endl;
            cin.get();
            obj.clear_screen();
            n1.navigateShops();

            cout << "Press Enter to go to the lift System!!!........" << endl;
            cin.get();
            obj.clear_screen();

            Lift lift;
        }

        else
        {
            obj.clear_screen();
            n1.navigateShops();
            cout << "Press Enter to go to the lift System!!!........" << endl;
            cin.get();
            obj.clear_screen();

            Lift lift;
        }
    }
    else
    {
        obj.clear_screen();
        cout << endl;
        cout << "\033[93m                                                            No Worries!!!!!\033[0m" << endl;
        cout << "\033[96m                                                       Hope we get to serve you later\033[0m" << endl;
    }
    return 0;
}

