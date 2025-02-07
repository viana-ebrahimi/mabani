#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>

using namespace std;

struct Item;
struct User;
struct myAnbarData;

struct User
{
    string username;
    string password;
    string type;
    double wallet = 0.0;
    Item *userItemsList = nullptr;
};

struct Item
{
    string name;
    double price;
    int kiloo;
};

struct myAnbarData
{
    const int numberOfPeople = 5;
    User people[5];
    Item *anbarItemsList = nullptr;
    int itemsCount = 0;
};

void showUserMenu(const string &inputN, User people[], int size, myAnbarData &data);
void showAdminMenu(const string &inputN, User people[], int size, myAnbarData &data);
void createUsers(User people[]);
void initializeItems(myAnbarData &data);
void login(User people[], int size, myAnbarData &data);
void addItem(const string &item, double price, myAnbarData &data);
void deleteItems(myAnbarData &data);
void removeItem(const string &item, myAnbarData &data);
void renameItem(const string &oldName, const string &newName, myAnbarData &data);
void changePrice(myAnbarData &data, double newPrice, const string &name);
void credit(double price, const string &name, User people[], int size);
void showItem(myAnbarData &data);
void buyItem(const string &itemName, myAnbarData &data, User people[], int userCount, const string &username);
void showBalance(const string &inputN, User people[], int size);
void help(const string &name);
void saveDataToFile(const myAnbarData &data);
void readDataFromFile(myAnbarData &data);



void saveDataToFile(const myAnbarData &data)
{
    ofstream out("data.txt");
    if (!out)
    {
        cerr << "Error opening file for writing." << endl;
        return;
    }
    out << data.itemsCount << "\n";
    for (int i = 0; i < data.itemsCount; i++)
    {
        out << data.anbarItemsList[i].name << "\n";
        out << data.anbarItemsList[i].price << "\n";
        out << data.anbarItemsList[i].kiloo << "\n";
    }
    out.close();
    cout << "Data saved to file successfully." << endl;
}

void readDataFromFile(myAnbarData &data)
{
    ifstream in("data.txt");
    if (!in)
    {
        cerr << " file nor found." << endl;
        return;
    }
    int count;
    in >> count;
    in.ignore();
    if (data.anbarItemsList)
    {
        delete[] data.anbarItemsList;
    }
    data.anbarItemsList = new Item[count];
    data.itemsCount = count;
    for (int i = 0; i < count; i++)
    {
        getline(in, data.anbarItemsList[i].name);
        in >> data.anbarItemsList[i].price;
        in.ignore();
        in >> data.anbarItemsList[i].kiloo;
        in.ignore();
    }
    in.close();
    cout << "Data loaded from file successfully." << endl;
}

void initializeItems(myAnbarData &data)
{
    try
    {
        data.itemsCount = 10;
        data.anbarItemsList = new Item[data.itemsCount];

        data.anbarItemsList[0] = {"apple", 50000, 5};
        data.anbarItemsList[1] = {"lemon", 60000, 5};
        data.anbarItemsList[2] = {"banana", 100000, 5};
        data.anbarItemsList[3] = {"orange", 80000, 6};
        data.anbarItemsList[4] = {"kiwi", 90000, 6};
        data.anbarItemsList[5] = {"Cucumber", 400000, 10};
        data.anbarItemsList[6] = {"Pomegranate", 50000, 4};
        data.anbarItemsList[7] = {"Onion", 500000, 7};
        data.anbarItemsList[8] = {"Potatoes", 60000, 8};
        data.anbarItemsList[9] = {"Persimmon", 80000, 8};
    }
    catch (exception &e)
    {
        throw runtime_error("error in initializeItems: " + string(e.what()));
    }
}

void deleteItems(myAnbarData &data)
{
    try
    {
        delete[] data.anbarItemsList;
        data.anbarItemsList = nullptr;
        data.itemsCount = 0;
    }
    catch (exception &e)
    {
        throw runtime_error("error in deleteItems: " + string(e.what()));
    }
}

void addItem(const string &item, double price, myAnbarData &data)
{
    try
    {
        if (item.empty())
        {
            throw invalid_argument("Item name cannot be empty.");
        }

        int kiloo = 0;
        cout << "How much " << item << "? ";
        cin >> kiloo;

        // Search for an existing item
        bool itemFound = false;
        for (int i = 0; i < data.itemsCount; i++)
        {
            if (data.anbarItemsList[i].name == item)
            {
                data.anbarItemsList[i].kiloo += kiloo;
                itemFound = true;
                cout << "Item " << item << " already exists. Kilo updated to " << data.anbarItemsList[i].kiloo << endl;
                break;
            }
        }

        // If not found, add a new item
        if (!itemFound)
        {
            Item *newItemsList = new Item[data.itemsCount + 1];
            for (int i = 0; i < data.itemsCount; i++)
            {
                newItemsList[i] = data.anbarItemsList[i];
            }
            newItemsList[data.itemsCount] = {item, price, kiloo};
            delete[] data.anbarItemsList;
            data.anbarItemsList = newItemsList;
            data.itemsCount++;
            cout << "Item " << item << " added successfully" << endl;
        }

        // Save data to file after adding an item
        saveDataToFile(data);
    }
    catch (const exception &e)
    {
        cout << "error in addItem: " << e.what() << endl;
    }
}

void removeItem(const string &item, myAnbarData &data)
{
    try
    {
        if (item.empty())
            throw invalid_argument("item name cannot be empty");

        int index = -1;
        for (int i = 0; i < data.itemsCount; i++)
        {
            if (data.anbarItemsList[i].name == item)
            {
                index = i;
                break;
            }
        }
        if (index == -1)
            throw invalid_argument("Item " + item + " not found.");

        Item removed = data.anbarItemsList[index];
        Item *newItemsList = new Item[data.itemsCount - 1];

        for (int i = 0, j = 0; i < data.itemsCount; i++)
        {
            if (i != index)
                newItemsList[j++] = data.anbarItemsList[i];
        }
        delete[] data.anbarItemsList;
        data.anbarItemsList = newItemsList;
        data.itemsCount--;
        cout << "Item " << item << " removed successfully." << endl;

        int choice;
        cout << "Press 1 if you want to return the product, or any other number to continue: ";
        if (choice == 1)
        {
            addItem(removed.name, removed.price, data);
            cout << "Product " << removed.name << " restored successfully!" << endl;
        }

        // save data to file after removing an item
        saveDataToFile(data);
    }
    catch (exception &e)
    {
        cout << "error in removeItem: " << e.what() << endl;
    }
}

void renameItem(const string &oldName, const string &newName, myAnbarData &data)
{
    try
    {
        if (oldName.empty() || newName.empty())
            throw invalid_argument("Old name and new name cannot be empty.");

        bool found = false;
        for (int i = 0; i < data.itemsCount; i++)
        {
            if (data.anbarItemsList[i].name == oldName)
            {
                data.anbarItemsList[i].name = newName;
                found = true;
                break;
            }
        }
        if (!found)
            throw invalid_argument("Item " + oldName + " not found.");
        cout << "Rename completed successfully." << endl;

        // Save data to file after renaming an item
        saveDataToFile(data);
    }
    catch (exception &e)
    {
        cout << "error in renameItem: " << e.what() << endl;
    }
}

void changePrice(myAnbarData &data, double newPrice, const string &name)
{
    try
    {
        if (name.empty())
            throw invalid_argument("Item name cannot be empty");

        bool found = false;
        for (int i = 0; i < data.itemsCount; i++)
        {
            if (data.anbarItemsList[i].name == name)
            {
                data.anbarItemsList[i].price = newPrice;
                found = true;
                cout << "Price of " << name << " updated to " << newPrice << endl;
                break;
            }
        }
        if (!found)
            throw invalid_argument("Item " + name + " not found.");

        // Save data to file after changing the price of an item
        saveDataToFile(data);
    }
    catch (exception &e)
    {
        cout << "error in changePrice: " << e.what() << endl;
    }
}

void credit(double price, const string &name, User people[], int size)
{
    try
    {
        if (name.empty())
            throw invalid_argument("User name cannot be empty.");
        bool found = false;
        for (int i = 0; i < size; i++)
        {
            if (people[i].username == name)
            {
                people[i].wallet += price;
                found = true;
                cout << "Wallet of " << name << " increased by " << price << endl;
                break;
            }
        }
        if (!found)
            throw invalid_argument("User " + name + " not found.");
    }
    catch (exception &e)
    {
        cout << "Error in credit: " << e.what() << endl;
    }
}

void showItem(myAnbarData &data)
{
    try
    {
        for (int i = 0; i < data.itemsCount; i++)
        {
            cout << "Name: " << data.anbarItemsList[i].name
                 << ", Price: " << data.anbarItemsList[i].price
                 << ", Kilo: " << data.anbarItemsList[i].kiloo << endl;
        }
        cout << "Enter the item name to search for: ";
        string name;
        cin >> name;
        if (name.empty())
            throw invalid_argument("name cannot be empty.");
        for (int i = 0; i < data.itemsCount; i++)
        {
            if (data.anbarItemsList[i].name == name)
            {
                cout << "Found: " << data.anbarItemsList[i].name
                     << ", Price: " << data.anbarItemsList[i].price << endl;
                return;
            }
        }
        cout << "Item not found." << endl;
    }
    catch (exception &e)
    {
        cout << "error in showItem: " << e.what() << endl;
    }
}

void buyItem(const string &itemName, myAnbarData &data, User people[], int userCount, const string &username)
{
    try
    {
        if (itemName.empty())
            throw invalid_argument("Item name cannot be empty.");

        double price = 0.0;
        int itemIndex = -1;
        for (int i = 0; i < data.itemsCount; i++)
        {
            if (data.anbarItemsList[i].name == itemName)
            {
                price = data.anbarItemsList[i].price;
                itemIndex = i;
                break;
            }
        }
        if (itemIndex == -1)
            throw invalid_argument("Item " + itemName + " not found.");

        bool userFound = false;
        for (int i = 0; i < userCount; i++)
        {
            if (people[i].username == username)
            {
                userFound = true;
                if (people[i].wallet < price)
                    throw invalid_argument("Not enough money.");
                people[i].wallet -= price;
                data.anbarItemsList[itemIndex].kiloo--;
                cout << "Bought " << itemName << " successfully." << endl;
                break;
            }
        }
        if (!userFound)
            throw invalid_argument("User " + username + " not found.");

        // Save data to file after buying an item
        saveDataToFile(data);
    }
    catch (exception &e)
    {
        cout << "error in buyItem: " << e.what() << endl;
    }
}

void showBalance(const string &inputN, User people[], int size)
{
    try
    {
        if (inputN.empty())
            throw invalid_argument("Username cannot be empty.");
        bool found = false;
        for (int i = 0; i < size; i++)
        {
            if (inputN == people[i].username)
            {
                found = true;
                cout << inputN << ", your current balance is: " << people[i].wallet << endl;
                break;
            }
        }
        if (!found)
            throw invalid_argument("User " + inputN + " not found.");
    }
    catch (exception &e)
    {
        cout << "Error in showBalance: " << e.what() << endl;
    }
}

void help(const string &name)
{
    try
    {
        if (name == "show item")
            cout << "Displays available items and allows searching for an item." << endl;
        else if (name == "buy item")
            cout << "Allows you to buy an item." << endl;
        else if (name == "balance")
            cout << "Shows your current wallet balance." << endl;
        else if (name == "help")
            cout << "Provides help for available commands." << endl;
        else
            throw invalid_argument("Help topic not found.");
    }
    catch (exception &e)
    {
        cout << "Error in help: " << e.what() << endl;
    }
}

void showAdminMenu(const string &inputN, User people[], int size, myAnbarData &data)
{
    try
    {
        cout << "\nAdmin Commands:\n"
             << "  add <item> <price>\n"
             << "  remove <item>\n"
             << "  rename <oldName> <newName>\n"
             << "  price <item> <newPrice>\n"
             << "  credit <amount> <user>\n"
             << "$ ";
        string command;
        cin >> command;
        if (command.empty())
            throw invalid_argument("Command cannot be empty.");

        if (command == "add")
        {
            string item;
            double price;
            cin >> item >> price;
            if (item.empty())
                throw invalid_argument("Item name cannot be empty.");
            addItem(item, price, data);
        }
        else if (command == "remove")
        {
            string item;
            cin >> item;
            if (item.empty())
                throw invalid_argument("Item name cannot be empty.");
            removeItem(item, data);
        }
        else if (command == "rename")
        {
            string oldName, newName;
            cin >> oldName >> newName;
            if (oldName.empty() || newName.empty())
                throw invalid_argument("Both old name and new name must be provided.");
            renameItem(oldName, newName, data);
        }
        else if (command == "price")
        {
            string name;
            double newPrice;
            cin >> name >> newPrice;
            if (name.empty())
                throw invalid_argument("Item name cannot be empty.");
            changePrice(data, newPrice, name);
        }
        else if (command == "credit")
        {
            double amount;
            string user;
            cin >> amount >> user;
            if (user.empty())
                throw invalid_argument("User name cannot be empty.");
            credit(amount, user, people, size);
        }
        else
        {
            throw invalid_argument("Command not found.");
        }
    }
    catch (exception &e)
    {
        cout << "Error in admin menu: " << e.what() << endl;
    }
}

void showUserMenu(const string &inputN, User people[], int size, myAnbarData &data)
{
    try
    {
        cout << "\nUser Commands:\n"
             << "  show item\n"
             << "  buy item <name>\n"
             << "  balance\n"
             << "  help <command>\n"
             << "# ";
        string command;
        cin >> command;
        if (command.empty())
            throw invalid_argument("Command cannot be empty.");

        if (command == "show")
        {
            string nextPart;
            cin >> nextPart;
            if (nextPart.empty())
                throw invalid_argument("Incomplete command for 'show'.");
            if (nextPart == "item")
                showItem(data);
            else
                throw invalid_argument("Sub-command for show not recognized.");
        }
        else if (command == "buy")
        {
            string nextPart, itemName;
            cin >> nextPart >> itemName;
            if (nextPart.empty() || itemName.empty())
                throw invalid_argument("Incomplete command for 'buy'.");
            if (nextPart == "item")
                buyItem(itemName, data, people, size, inputN);
            else
                throw invalid_argument("Sub-command for buy not recognized.");
        }
        else if (command == "balance")
        {
            showBalance(inputN, people, size);
        }
        else if (command == "help")
        {
            string topic;
            cin >> topic;
            if (topic.empty())
                throw invalid_argument("Help topic cannot be empty.");
            help(topic);
        }
        else
        {
            throw invalid_argument("Command not found.");
        }
    }
    catch (exception &e)
    {
        cout << "Error in user menu: " << e.what() << endl;
    }
}

void createUsers(User people[])
{
    try
    {
        people[0] = {"ali", "1234", "admin", 1000.0};
        people[1] = {"nava", "4321", "admin", 1000.0};
        people[2] = {"user1", "7777", "user", 500.0};
        people[3] = {"user2", "4444", "user", 500.0};
        people[4] = {"user3", "5555", "user", 500.0};
    }
    catch (exception &e)
    {
        throw runtime_error("Error in createUsers: " + string(e.what()));
    }
}

void login(User people[], int size, myAnbarData &data)
{
    try
    {
        string inputN, inputP;
        cout << "Enter username: ";
        cin >> inputN;
        if (inputN.empty())
            throw invalid_argument("Username cannot be empty.");
        cout << "Enter password: ";
        cin >> inputP;
        if (inputP.empty())
            throw invalid_argument("Password cannot be empty.");

        bool loggedIn = false;
        for (int i = 0; i < size; i++)
        {
            if (people[i].username == inputN && people[i].password == inputP)
            {
                loggedIn = true;
                cout << "Welcome, " << people[i].username << " (" << people[i].type << ")!" << endl;
                if (people[i].type == "admin")
                    showAdminMenu(inputN, people, size, data);
                else
                    showUserMenu(inputN, people, size, data);
                break;
            }
        }
        if (!loggedIn)
            throw invalid_argument("Login failed: Invalid username or password.");
    }
    catch (exception &e)
    {
        cout << "Error in login: " << e.what() << endl;
    }
}

void startProgram()
{
    try
    {
        myAnbarData anbar;
        createUsers(anbar.people);
        cout << "press 1 to load other to start new";	
        int choice;
        cin >> choice;
        if (choice == 1)
        {
        	readDataFromFile(anbar);
        }
        else
        {
         	initializeItems(anbar);
        }
        login(anbar.people, anbar.numberOfPeople, anbar);
    }
    catch (exception &e)
    {
        cout << "Error in startProgram: " << e.what() << endl;
    }
}

int main()
{
    try
    {
        startProgram();
    }
    catch (exception &e)
    {
        cout << "Unhandled exception: " << e.what() << endl;
    }
    return 0;
}
