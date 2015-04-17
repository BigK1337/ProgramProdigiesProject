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
	string small[2]; //Position 0 is ID.  Position 1 is Number of items with that ID in this slot.
};
struct med
{
	string medium[2]; //Position 0 is ID.  Position 1 is Number of items with that ID in this slot.
};
struct lar
{
	string large[2]; //Position 0 is ID.  Position 1 is Number of items with that ID in this slot.
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
	sm sloc[20];//20 small slots
	med medloc[60];//60 medium slots
	lar lloc[20];//20 large slots
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
	bool itemAlreadyInWarehouse;
	getline(Vendor, input);  //First line with File ID and date receieved.
	fileid = input.substr(1, 4);
	today = input.substr(6, 8); cout << "File #" << fileid << "  Shipment recieved on: " << today.substr(0, 4) << "-" << today.substr(4, 2) << "-" << today.substr(6, 2) << endl << endl;
	while (!Vendor.eof())  //Ticks once for every vendor.
	{
		getline(Vendor, input);  //Gets vendor info and amount of items.
		if (input.size()>13)  //If not last line of file, continue.
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
					int numberAlreadyInWarehouse = (atoi(num[n].medloc[i].medium[1].c_str()) - 1);
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
					if (itemsize == "S")  //If item size is small.
					{

					}
					else if (itemsize == "M") //If item size is medium.
					{
						//The below chunk checks to see if the item already exists in the warehouse
						for (int i = 0; i<60; i++)//Look at all 60 medium spots in the warehouse
						{
							if (num[n].medloc[i].medium[0] == item && num[n].medloc[i].medium[0]!="100")//If item is in warehouse and the slot isnt full
							{
								itemAlreadyInWarehouse = true;//Item is in warehouse
								break;
							}
							if(itemAlreadyInWarehouse == true){
							while(n>0 && numberAlreadyInWarehouse < 100)//While there are some to be added from the form and still room in the slot
							{
								n--;//Remove one from number to be added to warehouse
								numberAlreadyInWarehouse++;//Add one to number in warehouse
							}
							if(n == 0)//If we added every item from the vendor form
							{
								//Convert numberAlreadyInWarehouse back into a string to be stored in num[n].medloc[i].medium[1]
							}
							if(numberAlreadyInWarehouse == 100 && n>0)//If we filled the slot and there are still items remaining to be added
							{
								i--;//Redo for loop for same item
							}
							else
							{
								//item perfectly fills slot
							}
							}
							else//item is not already in warehouse
							{
								//Search for an empty slot. If none exist then check another warehouse.Ifa all are full, tell analyst

						//The below chunk runs if the item does not already exist in the warehouse.
						for (int i = 0; i<60; i++)//Look at all 60 medium spots in the warehouse
						{
						if(num[n].medloc[i].medium[0] == "")
						{
							num[n].medloc[i].medium[0] = item;	
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
	string input, type, last, first, business, straddr, city, state, post, country, orderdate, ordercount, custid, orderid, payment, discount, fileid, shipdate, item, number, count, customers, lineitems, itemsize;
	//what is the business variable for???????
	getline(Customer, input);
	fileid = input.substr(1, 4);
	shipdate = input.substr(6, 8); cout << "File #" << fileid << "  Shipping Date: " << shipdate.substr(0, 4) << "-" << shipdate.substr(4, 2) << "-" << shipdate.substr(6, 2) << endl << endl;
	while (!Customer.eof()) 
	{
		getline(Customer, input);//Type,Last,First
		if (input.size()>13)  //If not last line of file, continue.
		{
			//All of Customer's Info
			type = input.substr(0, 1); last = input.substr(1, 30); first = input.substr(30, 30);straddr = input.substr(60, 30);city = input.substr(90, 20);
			state = input.substr(110, 20);post = input.substr(130, 10);country = input.substr(140, 40);orderdate = input.substr(180, 8);ordercount = input.substr(188, 1);
			custid = input.substr(189, 10);orderid = input.substr(199, 10);payment = input.substr(209, 10);discount = input.substr(219, 3);
		
		int i = atoi(ordercount.c_str());  //Gets number of items from vendor in int form.
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
					if (itemsize == "S")  //If item size is small.
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
	}			
}
int main()
{
	File.open("catalogue.txt"), Vendor.open("vendor.txt"), Customer.open("Customer.txt");  //Opening the files.
	warehouse num[3];  //Three warehouse locations
	string input, temp;
	head = new list;
	setuplist(head);
	vendor(num);
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