#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<fstream>
#include<stdlib.h>
#include<ctime>

#include "Bill.hpp"
#include "OrderDetails.hpp"
#define fileName "bill.txt"
using namespace std;
fstream billFile;


void Bill:: opener(fstream &ifile,char *filename,ios_base::openmode mode){
    ifile.open(filename,mode);
    if(!ifile){
        cout<<"File not found\n";
        return;
    }
}
void Bill :: read(int id){
    opener(billFile,fileName,ios::app);
    if(!billFile){
        cout<<"\nExit through bill read\n";
        exit(0);
    }
    int m;
    orderDetails od;
    orderId=id;
    totalQuantity=od.calculateTotalQuantity(id);
    float tempAmount=od.calculateTotalAmount(id);
    time_t now = time(0);
    tm *ltm=localtime(&now);
    strcpy(billingTime,to_string(ltm->tm_hour).c_str());
    strcat(billingTime,":");
    strcat(billingTime,to_string(ltm->tm_min).c_str());
    strcat(billingTime,":");
    strcat(billingTime,to_string(ltm->tm_sec).c_str());

    strcpy(billingDate,to_string(ltm->tm_year+1900).c_str());
    strcat(billingDate,"-");
    strcat(billingDate,to_string(ltm->tm_mon+1).c_str());
    strcat(billingDate,"-");
    strcat(billingDate,to_string(ltm->tm_mday).c_str());
    totalAmount=tempAmount;
    cout<<"Enter the payment Method\n";
    cout<<"1. Cash \t"<<"2. Card\t"<<"3.UPI\nEnter method: ";
    cin >> m;
    switch (m)
    {
    case 1:
        strcpy(method,"Cash") ;
        break;
    case 2:
        strcpy(method,"Card") ;
        break;
    case 3:
        strcpy(method,"UPI") ;
        break;
    default:
        break;
    }
    pack();
    billFile.close();
}
void Bill::pack(){
    billFile<<orderId<<"|"<<totalQuantity<<"|"<<totalAmount<<"|"<<method<<"|"<<billingDate<<"|"<<billingTime<<"|#\n";
}
void Bill::displayAll(){
    opener(billFile,fileName,ios::in);
    if(!billFile){
        cout<<"exit through bill display";
        exit(0);
    }
    char buffer[100];
    cout<<setiosflags(ios::left);
    cout<<setw(10)<<"Order Id"<<setw(15)<<"Total Quantity"<<setw(15)<<"Total Amount"<<setw(25)<<"Method"<<setw(15)<<"Date"<<setw(15)<<"Time"<<endl;
    while(1){
        unpack();
        if(billFile.eof())
            break;
        else{
            cout<<setw(10)<<orderId<<setw(15)<<totalQuantity<<setw(15)<<totalAmount<<setw(25)<<method<<setw(15)<<billingDate<<setw(15)<<billingTime<<endl;
        }
        // i--;
    }
    billFile.close();
}
void Bill::displayToday(){
    opener(billFile,fileName,ios::in);
    if(!billFile){
        cout<<"exit through bill display";
        exit(0);
    }
    char todayDate[15];
    time_t now=time(0);
    tm *ltm=localtime(&now);
    strcpy(todayDate,to_string(ltm->tm_year+1900).c_str());
    strcat(todayDate,"-");
    strcat(todayDate,to_string(ltm->tm_mon+1).c_str());
    strcat(todayDate,"-");
    strcat(todayDate,to_string(ltm->tm_mday).c_str());

    cout<<setiosflags(ios::right);
    cout<<setw(40)<<"Date : ";
    cout<<todayDate<<endl;
    cout<<setiosflags(ios::left);
    cout<<setw(10)<<"OrderId"<<setw(15)<<"TotalQuantity"<<setw(15)<<"Total Amount"<<setw(15)<<"Method"<<setw(15)<<"Time"<<endl;
    while(1){
        unpack();
        if(billFile.eof())
            break;
        else if(strcmp(todayDate,billingDate)==0){
            cout<<setw(10)<<orderId<<setw(15)<<totalQuantity<<setw(15)<<totalAmount<<setw(25)<<method<<setw(15)<<billingTime<<endl;
        }
        // i--;
    }
    billFile.close();
}
void Bill::unpack(){
    char buffer[100],idBuf[10],quantityBuf[10],amountBuf[10];
    billFile.getline(idBuf,10,'|');
    billFile.getline(quantityBuf,15, '|' );
    billFile.getline(amountBuf,15,'|');
    billFile.getline(method,25,'|');
    billFile.getline(billingDate,15,'|');
    billFile.getline(billingTime,15,'|');
    orderId=atoi(idBuf);
    totalAmount=atof(amountBuf);
    totalQuantity=atoi(quantityBuf);
    billFile.getline(buffer,100,'#\n');
}
char * Bill::getMethod(int id){
    opener(billFile,fileName,ios::in);
    if(!billFile){
        cout<<"Exit through bill getmethod";
        exit(0);
    }
    while(!billFile.eof()){
        unpack();
        if(orderId==id){
            billFile.close();
            return method;
        }
    }
}
void Bill::accessing(){
  int n;
  while (1)
  {
    cout<<"\n1-Today's Orders\t2-All Orders\t3-Main\nEnter choice:";
    cin>>n;
    switch (n)
    {
        case 1:
            displayToday();
            break;
        case 2:
            displayAll();
            break;
        case 3:
            return;
            break;
        default:
            return;
    }
    billFile.close();
  }
}