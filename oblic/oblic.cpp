#include <iostream>
#include <vector>
#include <string>
#include <fstream> 
using namespace std;

struct product {
    int id{};
    string name;
    string supplier;
    int num{};
    string cost;
};

struct buyer {
    string name;
    string surname;
    vector<product> product;
};

string exitToMenu(int indif) {
    string key;
    if (indif == 0) {
        cout << "\nTry again - enter 1. Exit - enter any characher." << endl;
        cin >> key;

        if (key != "1") {
            exit(0);
        }
    }
    else if (indif == 1){
        cout << "\nBack to menu - enter 1. Try again - enter 2. Exit - enter any characher." << endl;
        cin >> key;

        if (key != "1" && key != "2") {
            exit(0);
        }
    }

    return key;
}

string createMenu() {
    string key;
    const int OPTIONS = 8;
    
    const char* menu_options[OPTIONS] = { "Add new good", "Delete the good", "Search the good", "Edit info about the good", "Get all goods", "Create the report", "Save products to file", "Exit" };

    system("cls");
    cout << "Menu: " << endl;
    for (int i = 0; i < OPTIONS; i++) {
        cout << i + 1 << "." << menu_options[i] << endl;
    }

    cout << "\nEnter the option number you want to work with: ";
    cin >> key;

    return key;
}

bool isNumber(string str)
{
    for (char c : str) {
        if (isdigit(c) == 0) return false;
    }
    return true;
}

bool isDouble(string str)
{
    for (char c : str) {
        if (isdigit(c) == 0 && c != '.') return false;
    }
    return true;
}

void addProduct(vector<product>& P) {
    product NEW;
    int id;
    string key, name, supplier, str_num, cost;
    bool flag = false;
    
    do {
        system("cls");

        cout << "Enter the product name: ";
        cin >> name;

        cout << "Enter the supplier of the product: ";
        cin >> supplier;

        cout << "Enter number of product: ";
        cin >> str_num;

        cout << "Enter the product cost: ";
        cin >> cost;

        if (isNumber(str_num) && isDouble(cost)) {
            
            id = P.size() + 1;

            for (int i = 0; i != P.size(); i++) {
                if (P[i].name == name && P[i].supplier == supplier && P[i].cost == cost) {
                    flag = true;
                    P[i].num += stoi(str_num);
                }
            }       

            if(!flag) {
                NEW.id = id;
                NEW.cost = cost;
                NEW.num = stoi(str_num);
                NEW.name = name;
                NEW.supplier = supplier;
                P.push_back(NEW);
                cout << "\nThe good was added";
            } 
        } else {
            cout << "\nError: Invalid data. Try again";
        }

        key = exitToMenu(1);
    } while (key != "1");

    return;
}

void deleteProduct(vector<product>& P) {
    string name, supplier, key;
    bool flag = false;
    int index;

    do {
        system("cls");

        cout << "\nEnter the name of the product you want to delete: ";
        cin >> name;
        cout << "\nEnter the supplier of the product: ";
        cin >> supplier;

        for (int i = 0; i != P.size(); i++) {
            if (P[i].name == name && P[i].supplier == supplier) {
                flag = true;
                index = i;
            }
        }
       
        if (flag) {
            P.erase(remove_if(P.begin(), P.end(), [&](product const& p) { return p.name == P[index].name && p.supplier == P[index].supplier; }), P.end());
            cout << "The product is deleted!";
            }
        else {
            cout << "The product does not exist" << endl;
        }
        key = exitToMenu(1);
    } while (key != "1");

    return;
}

void searchProduct(vector<product>& P) {
    string name, supplier, key;
    bool flag = false;

    do {
         system("cls");

        cout << "\nEnter the name of the product you want to get: ";
        cin >> name;
        cout << "\nEnter the supplier of the product: ";
        cin >> supplier;

        for (int i = 0; i != P.size(); i++) {
            if (P[i].name == name && P[i].supplier == supplier) {
                flag = true;
                cout << "Your product:" << endl;
                cout << "ID: " << P[i].id;
                cout << "\nName: " << P[i].name;
                cout << "\nCost: " << P[i].cost;
                cout << "\nSupplier: " << P[i].supplier;
                cout << "\nNumber of product: " << P[i].num;
            }
        }

        if (!flag) {
            cout << "The product does not exist" << endl;
        }

        key = exitToMenu(1);
    } while (key != "1");
   
    return;
}

void editProduct(vector<product>& P) {
    int num;
    string cost, str_num, name, supplier, key;
    bool flag = false;

    do {
        system("cls");

        cout << "\nEnter the product name you want to get: ";
        cin >> name;
        cout << "\nEnter the supplier of the product: ";
        cin >> supplier;

            for (int i = 0; i != P.size(); i++) {
                if (P[i].name == name && P[i].supplier == supplier) {
                    flag = true;
                    cout << "Please enter new info about the good. If you do not want to edit some criteria, enter -1" << endl;
                    cout << "Name: ";
                    cin >> name;
                    cout << "Cost: ";
                    cin >> cost;
                    cout << "Supplier: ";
                    cin >> supplier;
                    cout << "Number of product: ";
                    cin >> str_num;

                    if (isNumber(str_num) && isDouble(cost)) {
                        if (name != "-1") {
                            P[i].name = name;
                        }
                        if (supplier != "-1") {
                            P[i].supplier = supplier;
                        }
                        if (str_num != "-1") {
                            P[i].num = stoi(str_num);
                        }
                        if (cost != "-1") {
                            P[i].cost = cost;
                        }
                        cout << "\nData is changed";
                    } else {
                    cout << "\nError: Invalid data. Try again";
                    }
                }   
            }

        if (!flag) {
            cout << "The product does not exist" << endl;
        }

        key = exitToMenu(1);
    } while (key != "1");
    
    return;
}

void getAllProducts(vector<product>& P) {
    string key;
    do {
        system("cls");
        if (P.size()) {
            cout << "List of products:";
            for (int i = 0; i != P.size(); i++) {
                cout << "\n\nProduct " << P[i].id << endl;
                cout << "Name: " << P[i].name;
                cout << "\nSupplier: " << P[i].supplier;
                cout << "\nCost: " << P[i].cost;
                cout << "\nNumber of product: " << P[i].num;
            }
        }
        else {
            cout << "Products do not exist";
        } 
        key = exitToMenu(1);
    } while (key != "1");
    return;
}

void createReport(vector<product>& P, vector<buyer>& B) {
    string key, _key;
    product temp;
    bool flag = true;

    const int OPTIONS = 3;
    const char* report_menu[OPTIONS] = { "Cost of all goods", "List of scarcity goods", "The most expensive product" };
   
    do {
        system("cls");

        if (!P.size()) {
            cout << "You have not any product";
            exitToMenu(0);
            return;
        }
        cout << "List of reports: " << endl;
        for (int i = 0; i < OPTIONS; i++) {
            cout << i + 1 << ". " << report_menu[i] << endl;
        }
    
        cout << "Enter the report number you want to get: ";
        cin >> key;

        double totalCost = 0;
        vector<product> minNum;
        string maximum = "0";
        vector<product> maxCost;
        
        if (key == "1") {
            if (!P.size()) {
                totalCost = 0;
                break;
            }

            for (int i = 0; i != P.size(); i++) {
                    double productCost = stod(P[i].cost);
                    totalCost = totalCost + (productCost * P[i].num);                
            }
        }
        else if (key == "2") {
            for (int i = 0; i != P.size(); i++) {
                if (P[i].num < 10) {
                    minNum.push_back(P[i]);
                }
            }
        }
        else if (key == "3") {
            for (int i = 0; i != P.size(); i++) {
                
                if (P[i].cost > maximum) {
                    maximum = P[i].cost;
                }
            }
            for (int i = 0; i != P.size(); i++) {
                if (P[i].cost == maximum) {
                    maxCost.push_back(P[i]);
                }
            }
        }
        else {
            flag = false;
            cout << "\nError: Invalid data. Try again";
        }

        if (flag) {
            cout << "The report #" << key << ":" << endl;
            if (key == "1") cout << "Total cost: " << totalCost;
            if (key == "2") {
                if (minNum.size()) {
                    cout << "List of scarcity goods:";
                    for (int i = 0; i != minNum.size(); i++) {
                        cout << "\n\nName: " << minNum[i].name << "\nCost : " << minNum[i].cost << "\nNumber of products : " << minNum[i].num;
                    }
                }
                else {
                    cout << "There are no shortages of goods";
                }
                
            }
            if (key == "3") {
                cout << "The most expensive product:";
                for (int i = 0; i != maxCost.size(); i++) {
                    cout << "\nName: " << maxCost[i].name << "\nCost : " << maxCost[i].cost << "\nNumber of products : " << maxCost[i].num;
                }
            }
        }
        _key = exitToMenu(1);
    } while (_key != "1");

    return;
}

bool saveInfo(vector<product>& P) {
    string key;
    bool result = false;
    if (P.size()) {
        ofstream products;
        products.open("Products.txt");

        if (!products.is_open()) {
            cout << "Error: can`t open file";
        }
        else {
            result = true;
            for (int i = 0; i != P.size(); i++) {
                products << P[i].id << endl;
                products << P[i].name << endl;
                products << P[i].supplier << endl;
                products << P[i].cost << endl;
                products << P[i].num << endl;
            }
        }
        products.close();
    }
    return result;
}

void saveProducts(vector<product>& P) {
    string key;
    do {
        system("cls");
        if (saveInfo(P)) {
            cout << "Products was saved";
        }
        else {
            cout << "You have not any product";
        }
        key = exitToMenu(1);
    } while (key != "1");
    return;
}

void saveSale(vector<buyer>& B) {
    ofstream buy;
    buy.open("Buyers.txt");

    if (!buy.is_open()) {
        cout << "Error: can`t open file";
    }
    else {
        for (int i = 0; i != B.size(); i++) {
            buy << B[i].name << "\n" << B[i].surname << endl;
            for (int j = 0; j != B[i].product.size(); j++) {
                buy << B[i].product[j].id << endl;
                buy << B[i].product[j].cost << endl;
                buy << B[i].product[j].name << endl;
                buy << B[i].product[j].supplier << endl;
                buy << B[i].product[j].num << endl;
            }
            buy << endl;
        }
    buy.close();
    }
    return;
}

void saveBuyer(vector<buyer>& B, buyer buy) {
    bool useradd = false;
    
    if (B.size()) {
        for (int i = 0; i != B.size(); i++) {
            if (B[i].name == buy.name && B[i].surname == buy.surname) {
                for (int j = 0; j != buy.product.size(); j++) {   
                    B[i].product.push_back(buy.product[j]);
                }
                useradd = true;
            }
        }
        if (!useradd) {
            B.push_back(buy);
        }
    }
    else {
        B.push_back(buy);
    }
}

void buyProduct(vector<product>& P, buyer buy, vector<buyer>& B) {
    string name, supplier, str_num, key;
    product buyedProduct;
    bool flag = false;
    int index, num;
    do {
        system("cls");
        cout << "Enter the product name you want to get: ";
        cin >> name;
        cout << "\nEnter the supplier of the product: ";
        cin >> supplier;
        
        for (int i = 0; i != P.size(); i++) {
            if (P[i].name == name && P[i].supplier == supplier && P[i].num != 0) {
                flag = true;
                index = i;
            }
        }
        if (flag) {
            cout << "Enter how much you want to buy: ";
            cin >> str_num;
            if (isNumber(str_num)) {
                num = stoi(str_num);

                if (num > 0) {
                    if (P[index].num >= num) {
                        cout << "The order is formed";
                        buyedProduct = P[index];
                        buyedProduct.num = num;
                        
                        P[index].num -= num;
                        buy.product.push_back(buyedProduct);
                       
                        saveBuyer(B, buy);
                        saveSale(B);
                        saveInfo(P);
                    }
                    else {
                        cout << "The quantily entered exceeds availability";
                    }
                }
                else {
                    "Error: Invalid data";
                }
            }
            else {
                "Error: Invalid data";
                key = exitToMenu(1);
            }
        }
        else {
            cout << "The product does not exist";
        }
        key = exitToMenu(1);
    } while (key != "1");
    return;
}

void buyerApp(vector<product>& P, vector<buyer>& B) {
    buyer NEW;
    string key, _key;

    system("cls");
    cout << "Enter your name: ";
    cin >> NEW.name;
    cout << "Enter your surname: ";
    cin >> NEW.surname;

    do {
        system("cls");
        cout << "Hello " << NEW.name << "! What do you want?" << endl;
        cout << "1. Search the good; \n2. Buy the good; \n3. Exit." << endl;
        cout << "Enter number of option: ";
        cin >> key;
        
        if (key == "1") {
            searchProduct(P);
        }
        else if (key == "2") {
            buyProduct(P, NEW, B);
        }
        else if (key == "3") {
            exit(0);
        }
        else {
            _key = exitToMenu(0);
        }
        
    } while (_key != "1");
    
    return;
}

void ownerApp(vector<product>& P, vector<buyer>& B) {
    string key, _key, password_enter, password_true;
    ifstream password_read;
    password_read.open("Password.txt");

    system("cls");
  
    if (password_read >> password_true) {
        cout << "Enter password: ";
        cin >> password_enter;  

        if (password_enter == password_true) {
            do {
                key = createMenu();
                if (key == "1") {
                    addProduct(P);
                }
                else if (key == "2") {
                    deleteProduct(P);
                }
                else if (key == "3") {
                    searchProduct(P);
                }
                else if (key == "4") {
                    editProduct(P);
                }
                else if (key == "5") {
                    getAllProducts(P);
                }
                else if (key == "6") {
                    createReport(P, B);
                }
                else if (key == "7") {
                    saveProducts(P);
                }
                else if (key == "8") {
                    exit(0);
                }
                else {
                    cout << "This comand is not exsist! ";
                    _key = exitToMenu(1);
                }

            } while (_key != "0");
        }
        else {
            cout << "Error: invalid password";
            exitToMenu(1);
        }
    }
    else {
        ofstream password_write;
        password_write.open("Password.txt");
        if (password_write.is_open()) {
            string password;
            
            cout << "Create password: ";
            cin >> password;
            password_write << password;
        }
        password_write.close();
    }
    password_read.close();
    return;
}

void enterToProgram(vector<product>& P, vector<buyer>& B) {
    string person;

    cout << "Hello. This is Mari-Store! Who are you? \nEnter 1 - you are owner. Enter 2 - you are buyer: ";
    cin >> person;

    if (person == "1") {
        ownerApp(P, B);
    }
    else if (person == "2") {
        if (!P.size()) {
            string key;
            do {
                system("cls");
                cout << "Sorry the shop does not work";
                key = exitToMenu(1);
            } while (key != "1");    
        }
        else {
            buyerApp(P, B);
        } 
    }
    else {
        cout << "Error: Invalid data. Try again";
        exitToMenu(1);
    }
    return;
}

void readInfoBuyers(vector<buyer>& B) {
    int id, num;
    string cost, name, supplier, s;

    ifstream brout;
    brout.open("Buyers.txt");
    if (brout.is_open()) {
        while (!brout.eof()) {
            buyer NEW;
            product buyed;
            brout >> NEW.name;
            brout >> NEW.surname;
            while (getline(brout, s)) {
                while (!s.empty()) {
                    brout >> buyed.id;
                    brout >> buyed.cost;
                    brout >> buyed.name;
                    brout >> buyed.supplier;
                    brout >> buyed.num;
                    NEW.product.push_back(buyed);
                }
                break;
            }
            B.push_back(NEW);
        }
    }
    brout.close();
    return;
}

void readInfoProduct(vector<product>& P) {
    ifstream prout;
    prout.open("Products.txt");
    if (prout.is_open()) {
        while(!prout.eof()) {
            product NEW;
            prout >> NEW.id;
            prout >> NEW.name;
            prout >> NEW.supplier;
            prout >> NEW.cost;
            prout >> NEW.num;
            if (NEW.num != 0) {
                P.push_back(NEW);
            }
         }
    }
    prout.close();
    return;
}

int main()
{
    vector<product> P;
    readInfoProduct(P);
    vector<buyer> B;
    readInfoBuyers(B);
    do {
        system("cls");
        enterToProgram(P, B);
    } while (true);
    
    return 0;
}
