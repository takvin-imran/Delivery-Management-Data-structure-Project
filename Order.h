#pragma once
#include<iostream>
#include<string>
#include "DeliveryType.h"
using namespace std;

class Order
{
public:
	int orderID;
	string merchantName;
	string pickAddress;
	string merchantContact;
	string deliveryDate;
	DeliveryType delType;
	string customerName;
	string customerContact;
	string deliveryLocation;
	double cod;
	string orderStatus;
	double dc;
	Order();

};

