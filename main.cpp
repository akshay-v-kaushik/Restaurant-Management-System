#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Item.hpp"
#include "OrderDetails.hpp"
#include "Chefs.hpp"
#include "Bill.hpp"

#define MAX_BUFFER 75
using namespace std;

fstream myFile;
int main()
{
  int choice;
  while(1){
    cout<<"\n1.Customer Service\n2.Order History\n3.Modification Of Menu\n4.Service In Progress\n5.Exit\nEnter choice: ";
    cin>>choice;
    item itemobj;
    chefs chefobj;
    Bill b;
    switch(choice)//first switch(main switch)
    {
    case 1:{
           itemobj.accessing();
          
    }  break;
    case 2:{
            b.accessing();
            }  break;
    case 3 : {
                itemobj.operationsOnItem();
    }
            break;
    case 4: {
            chefobj.accessing();
    }          break;
    default:  return 0;
    }
    myFile.close();
  } 
  return 0;
}

