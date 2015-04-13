//
//  main.cpp
//  375 - Big project
//
//  Created by Christopher Murdoch on 4/8/15.
//  Copyright (c) 2015 Christopher Murdoch. All rights reserved.
//
#include <iostream>
#include <string>
#include <fstream>
using namespace std;
ifstream File, Vendor, Customer; //Three file initializations.
string itemtotal; //Total number of items in Catalogue string form.
int total = 0; //Total number of items in catalogue, converted to int.
struct sm
{
	string small[250]; //This will be the itemid - Alphanumeric
};
struct med
{
	string medium[100]; //This will be the itemid - Alphanumeric
};
struct lar
{
	string large[10]; //This will be the itemid - Alphanumeric
};
struct list //Information about each item.
{
	string itemid;
	string itemname;
	string itemsize;
	string itemprice;
	string itemdescription;
	list *next; //Will be a linked list.
};
list *head;  //Catalogue of items
struct warehouse  //Contains the slots for each size of item.
{
	sm sloc[20];
	med medloc[60];
	lar lloc[20];
};
bool check(string item, list *p, int num)
{
	for (int i = 0; i<total; i++)  //Compares item id to every node.
	{
		if (p->itemid == item)
		{
			return true; //If found, return true.
		}
		p = p->next;
	}
	return false; //Otherwise, return false.
}
void setuplist(list *p)  //Intakes the catalogue and stores it locally in the program.
{
	string temp;
	//getline(File,temp); //For the first line, 'List last created on: '
	while (!File.eof())
	{
		getline(File, temp);
		if (temp.size()<10) //For last line of catalogue - T#items
		{
			if (temp.size() == 4)
			{
				itemtotal = temp.substr(1, 3); //Amount of items in catalogue.
			}
			else if (temp.size() == 3)
			{
				itemtotal = temp.substr(1, 2);
			}
			else
				itemtotal = temp.substr(1, 1);
		}
		else  //For every other line in the catalogue, sets up a node for each in a linked list.
		{
			p->itemid = temp.substr(0, 10);
			p->itemname = temp.substr(10, 30);
			p->itemsize = temp.substr(40, 1);
			p->itemprice = temp.substr(41, 8);
			p->itemdescription = temp.substr(49, 500);
			p->next = new list;
			p = p->next;
		}
	}
	total = atoi(itemtotal.c_str()); //Converts the total number from string to int.
}
void vendor(warehouse num[3])  //For when the Vendor file is ingested.
{
	string input, today, fileid, item, number, count, shipped, comp, sentnum, numven, lineitems, itemsize;
	getline(Vendor, input);  //First line with File ID and date receieved.
	fileid = input.substr(1, 4);
	today = input.substr(6, 8); cout << "File #" << fileid << "  Shipment recieved on: " << today.substr(0, 2) << "-" << today.substr(2, 2) << "-" << today.substr(4, 4) << endl << endl;
	while (!Vendor.eof())  //Ticks once for every vendor.
	{
		getline(Vendor, input);  //Gets vendor info and amount of items.
		if (input.size()>7)  //If not last line of file, continue.
		{
			comp = input.substr(0, 50); shipped = input.substr(50, 10); sentnum = input.substr(60, 1);
			cout << "Shipment from: " << comp << endl << "Sent on: " << shipped << endl << "Number of items: " << sentnum << endl;
			int i = atoi(sentnum.c_str());  //Gets number of items from vendor in int form.
			for (int j = i; j>0; j--)
			{
				getline(Vendor, input);
				item = input.substr(0, 10); number = input.substr(11, 1);
				if (input.size() == 14){ count = input.substr(13, 1); }
				else if (input.size() == 15){ count = input.substr(13, 2); }
				else if (input.size() == 16){ count = input.substr(13, 3); }
				else if (input.size() == 17){ count = input.substr(13, 4); }
				int n = (atoi(number.c_str()) - 1);
				if (check(item, head, total) != true)
				{
					cout << "Item " << item << " is not in the catalogue, will not store item." << endl;
				}
				else
				{
					list *temp; temp = head;
					for (int i = 0; i<total; i++)
					{
						if (temp->itemid == item)
						{
							itemsize = temp->itemsize; //Grabs Item Size from catalogue.
							break;
						}
						temp = temp->next;
					}
					if (itemsize == "S")  //If item size is large
					{

					}
					else if (itemsize == "M") //If item size is medium.
					{
						for (int i = 0; i<60; i++)
						{
							if (num[n].medloc[i].medium[0] == "" || num[n].medloc[i].medium[0] == item)
							{
								if (num[n].medloc[i].medium[0] == item)
								{
									for (int j = 0; j<100; j++)
									{
										//Not finished.
									}
								}
							}
						}
					}
					else if (itemsize == "L") //If item size is large.
					{

					}
				}
			}
		}
		else
		{
			lineitems = input.substr(3, 1); numven = input.substr(1, 1);
			cout << "Total number of vendors: " << numven << endl << "Total number of line items: " << lineitems << endl;
		}
	}
}
void customer(warehouse num[3])
{
	string input, type, last, first, business, straddr, city, state, post, country, orderdate, ordercount, custid, orderid, payment, discount, fileid, shipdate, item, number, count, customers, lineitems;
	getline(Customer, input);
}
int main()
{
	File.open("catalogue.txt"), Vendor.open("vendor.txt"), Customer.open("Customer.txt");  //Opening the files.
	warehouse num[3];  //Three warehouse locations
	string input, temp;
	head = new list;
	setuplist(head);

	//vendor(num);
	/*cout<<"What would you like to do?"<<endl<<"1. Intake initial stock."<<endl<<"2.Take vendor items in."<<endl;
	cout<<"3.Receive customer order and ship."<<endl<<"4. Next Day."<<endl<<"5. Save and quit."<<endl;
	cin>>input;
	while(true)
	{
	if(input=="1" || "1.")
	{

	}
	else if(input=="2" || "2.")
	{

	}
	else if(input=="3" || "3.")
	{

	}
	else if(input=="4" || "4.")
	{

	}
	else if(input=="5" || "5.")
	{

	}
	else
	{
	cout<<"Not a valid entry. Retype choice.";
	}
	}*/
	system("pause"); //Coding in Xcode on mac, I don't need this.
	return 0;
}