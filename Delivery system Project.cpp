// Delivery system Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Order.h"
#include <ctime>
#include <fstream>
#include "DeliveryType.h"
#include <algorithm> 
#include<stdlib.h>
#include "Account.h"
#include"DeliveryAssistant.h"

using namespace std;

double delType;
int counter;
int dCounter;

Order order[100];
Account account;
DeliveryAssistant deliveryAssistant[20];


void readDeliveryAssistantInfo() {
    ifstream read;
    read.open("DeliveryAssistantInfo.txt");
    dCounter = 0;
    if (!read.fail()) {
        for (int i = 0; !read.eof(); i++) {
            read >> deliveryAssistant[i].name;
            read >> deliveryAssistant[i].contact;
            read >> deliveryAssistant[i].salary;
            dCounter++;
        }
    }
    read.close();
}


void writeDeliveryAssistantInfo() {
    ofstream write;
    write.open("DeliveryAssistantInfo.txt");

    if (!write.fail()) {
        for (int i = 0; i < dCounter; i++) {
            if (deliveryAssistant[i].salary != 0) {
                write << deliveryAssistant[i].name << endl;
                write << deliveryAssistant[i].contact << endl;
                write << deliveryAssistant[i].salary << endl;
            }
        }
    }
    write.close();
}

void displayDeliveryAssistantInfo() {
    for (int i = 0; i < dCounter; i++) {
        if (deliveryAssistant[i].salary != 0) {
            cout << "Name: " << deliveryAssistant[i].name << endl;
            cout << "Contact: " << deliveryAssistant[i].contact << endl;
            cout << "Phone: " << deliveryAssistant[i].salary << endl;
        }
        
    }
}

void salaryDisburst() {
    double sum=0;
    for (int i = 0; i < dCounter; i++) {
        if (account.getBalance() > deliveryAssistant[i].salary && deliveryAssistant[i].salary!=0) {
            account.disburstSalary(deliveryAssistant[i].salary);
            cout << "Salary of " << deliveryAssistant[i].name << " is disbursted..." << endl;
        }
        else if (account.getBalance() < deliveryAssistant[i].salary && deliveryAssistant[i].salary != 0) {
            cout << (double) account.disburstSalary(deliveryAssistant[i].salary) << "tk is short for " << deliveryAssistant[i].name << " salary disburstment." << endl;
            sum = sum + deliveryAssistant[i].salary;
        }
    }
  
}


int generateOrderID() {
    int id = rand() * 99;
    for (int i = 0; i < counter; i++) {
        if (order[i].orderID == id) {
            id = rand() * 99;
        }
    }
    return id;
}

void bubbleSort() {
    Order temp;
    for (int i = 0; i < counter; i++) {
        for (int j = i + 1; j < counter; j++) {
            if (order[i].orderID > order[j].orderID) {
                temp = order[i];
                order[i] = order[j];
                order[j] = temp;
            }
        }
    }
}

void SyncOrder() {
    counter = 0;
    ifstream readOrder;
    readOrder.open("OrderList.txt");
    
    if (readOrder.fail()) {
        cerr << "File Not Working";
    }
    if (readOrder.peek() != std::ifstream::traits_type::eof())
    {
        for (int i = 0; !readOrder.eof(); i++) {
            readOrder >> order[i].orderID;
            readOrder >> order[i].merchantName;
            readOrder >> order[i].merchantContact;
            readOrder >> order[i].pickAddress;
            readOrder >> order[i].deliveryDate;
            readOrder >> delType;
            readOrder >> order[i].customerName;
            readOrder >> order[i].customerContact;
            readOrder >> order[i].deliveryLocation;
            readOrder >> order[i].cod;
            readOrder >> order[i].orderStatus;
            order[i].dc = delType;
            counter++;
        }

    }
    
    readOrder.close();
}

void StoreOrder() {
    ofstream writeOrder;
    writeOrder.open("OrderList.txt");

    if (writeOrder.fail()) {
        cerr << "File Not Working";
    }
    for (int i = 0; i <=counter; i++) {
        if (order[i].orderID != 0) {
            writeOrder << order[i].orderID << endl;
            writeOrder << order[i].merchantName << endl;
            writeOrder << order[i].merchantContact << endl;
            writeOrder << order[i].pickAddress << endl;
            writeOrder << order[i].deliveryDate << endl;
            writeOrder << order[i].dc << endl;
            writeOrder << order[i].customerName << endl;
            writeOrder << order[i].customerContact << endl;
            writeOrder << order[i].deliveryLocation << endl;
            writeOrder << order[i].cod << endl;
            writeOrder << order[i].orderStatus << endl;
            
        }
    }

    writeOrder.close();
}

void insertOrder() {
    int x;
    int i = counter;
    order[i].orderID = generateOrderID();
    cout << "Enter your name: ";
    getline(cin, order[i].merchantName);
    cout << "Enter your Mobile No.: ";
    getline(cin, order[i].merchantContact);
    cout << "Enter parcel pickup address.: ";
    getline(cin, order[i].pickAddress);
    cout << "Enter Delivery Date (DD/MM/YY): ";
    getline(cin, order[i].deliveryDate);
    cout << "Select Delivery Type\n1. Regular Delivery-80tk\n2. Fast Delivery-150tk\n3. Special Delivery-250tk ";
    cin >> x;
    if (x == 1) {
        order[i].dc=order[i].delType.regularDelivery;
    }
    else if (x == 2) {
        order[i].dc = order[i].delType.fastDelivery;
    }
    else if (x == 3) {
        order[i].dc = order[i].delType.specialDelivery;
    }
    getchar();
    cout << "Enter customer name: ";
    getline(cin, order[i].customerName);
    cout << "Enter your Mobile No.: ";
    getline(cin, order[i].customerContact);
    cout << "Enter parcel delivery address: ";
    getline(cin, order[i].deliveryLocation);
    cout << "Enter Collection amount from customer: ";
    cin >> order[i].cod;
    counter++;
}

void searchOrder(string check) {
    string temp;
    bool test = false;
    transform(check.begin(), check.end(), check.begin(), ::toupper);
    for (int i = 0; i <= counter; i++) {
        temp = order[i].merchantName;
        transform(temp.begin(), temp.end(), temp.begin(), :: toupper);
        if (temp.compare(check)==0) {
            cout << "Mechant name: " << order[i].merchantName << endl;
            cout << "Merchant Contact: " << order[i].merchantContact << endl;
            cout << "Pickup Location: " << order[i].pickAddress << endl;
            cout << "Delivery Date:" << order[i].deliveryDate << endl;
            cout << "Delivery Charge:" << delType << endl;
            cout << "Customer Name: " << order[i].customerName << endl;
            cout << "Customer Contact: " << order[i].customerContact << endl;
            cout << "Delivery Location"<< order[i].deliveryLocation << endl;
            cout << "Cash Collected: " << order[i].cod << endl;
            cout << "Delivery Status: " << order[i].orderStatus << endl << endl;
            test = true;
        }
    }
    if (test == false) {
        cout << "No Match Found";
    }
}

void searchOrderById(int id) {
    bubbleSort();
    cout << "-------------LIST OF ORDERS-------------" << endl;
    int start = 0;
    int end = counter - 1;
    int mid = (start + end) / 2;

    while (start <= end && order[mid].orderID != id) {
        if (order[mid].orderID < id) {
            start = mid + 1;
            mid = (start + end) / 2;
        }
        else if (order[mid].orderID > id) {
            end = mid - 1;
            mid = (start + end) / 2;
        }
    }
    if (order[mid].orderID == id) {
        cout << "OrderID: " << order[mid].orderID << endl;
        cout << "Mechant name: " << order[mid].merchantName << endl;
        cout << "Merchant Contact: " << order[mid].merchantContact << endl;
        cout << "Pickup Location: " << order[mid].pickAddress << endl;
        cout << "Delivery Date:" << order[mid].deliveryDate << endl;
        cout << "Delivery Charge:" << order[mid].dc << endl;
        cout << "Customer Name: " << order[mid].customerName << endl;
        cout << "Customer Contact: " << order[mid].customerContact << endl;
        cout << "Delivery Location" << order[mid].deliveryLocation << endl;
        cout << "Cash Collected: " << order[mid].cod << endl;
        cout << "Delivery Status: " << order[mid].orderStatus << endl << endl;
    }
    else {
        cout << id << ": this order ID not found" << endl;
    }
}

void DisplayOrders() {
    cout << "-------------LIST OF ORDERS-------------" << endl;
    for (int i = 0; i < counter; i++) {

        cout << "OrderID: " << order[i].orderID << endl;
        cout << "Mechant name: " << order[i].merchantName << endl;
        cout << "Merchant Contact: " << order[i].merchantContact << endl;
        cout << "Pickup Location: " << order[i].pickAddress << endl;
        cout << "Delivery Date:" << order[i].deliveryDate << endl;
        cout << "Delivery Charge:" << order[i].dc << endl;
        cout << "Customer Name: " << order[i].customerName << endl;
        cout << "Customer Contact: " << order[i].customerContact << endl;
        cout << "Delivery Location" << order[i].deliveryLocation << endl;
        cout << "Cash Collected: " << order[i].cod << endl;
        cout << "Delivery Status: " << order[i].orderStatus << endl << endl;
    }
}

void OrderStatusUpdate(int id) {
    int x;
    for (int i = 0; i < counter; i++) {
        if (order[i].orderID == id) {
            cout << "---Press 1 to Complete" << endl;
            cout << "---Press 2 to Cancel" << endl;
            cin >> x;
            if (x == 1) {
                order[i].orderStatus = "completed";
            }
            else if (x == 2) {
                order[i].orderStatus = "canceled";
            }
        }
    }
}

void DeductDeliveryCharges() {
    
    
    for (int i = 0; i < counter; i++) {
        if (order[i].orderStatus.compare("pending")==0 && order[i].orderID!=0) {
            cout << "start";
            order[i].cod = order[i].cod - order[i].dc;
            account.setBalance(order[i].dc);
            order[i].orderStatus = "completed";
            cout << "end";
        }
    }
}



int main(){
    readDeliveryAssistantInfo();
    displayDeliveryAssistantInfo();
    salaryDisburst();
    
    return 0;
}