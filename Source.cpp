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

ifstream File;

string itemtotal;

struct small

{

    string small[250]; //This will be the itemid - Alphanumeric

};

struct med

{

    string medium[100]; //This will be the itemid - Alphanumeric

};

struct large

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



struct warehouse  //Contains the slots for each size of item.

{

    small sloc[20];

    med medloc[60];

    large lloc[20];

};

void setuplist(list *p)  //Intakes the catalogue and stores it locally in the program.

{

    string temp;

    //getline(File,temp);

    while (!File.eof())

    {

        getline(File,temp);

        if(temp.size()<10)

        {

            if(temp.size()==4)

            {

                itemtotal=temp.substr(1,3); //Amount of items in catalogue.

            }

            else if(temp.size()==3)

            {

                itemtotal=temp.substr(1,2);

            }

            else

                itemtotal=temp.substr(1,1);

        }

        else

        {

            p->itemid=temp.substr(0,10);

            p->itemname=temp.substr(10,30);

            p->itemsize=temp.substr(40,1);

            p->itemprice=temp.substr(41,8);

            p->itemdescription=temp.substr(49,500);

            p->next=new list;

            p=p->next;

        }

            

    }

}

void vendor(warehouse num[])

{

    

}

int main()

{

    File.open("input.txt"); 

    warehouse num[3];  //Three warehouse locations

    string input,temp;

    list *head;  //Catalogue of items

    head= new list;

    /*setuplist(head);

    cout<<head->itemid<<endl<<head->itemname<<endl<<head->itemsize<<endl<<head->itemprice<<endl<<head->itemdescription<<endl;

    cout<<head->next->itemid<<endl<<head->next->itemname<<endl<<head->next->itemsize<<endl<<head->next->itemprice<<endl<<head->next->itemdescription<<endl<<itemtotal;*/

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

    return 0;

}

