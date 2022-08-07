#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <cstring>
#include<limits>
#include "Chefs.hpp"
#include "OrderDetails.hpp"
#include "Item.hpp"
using namespace std;
int count = 0 ; 
item itemobj;
chefs chefobj;
fstream orderFile;
#define fileName "order.txt"
void orderDetails :: opener(fstream &ifile,char *filename,ios_base::openmode mode){
    ifile.open(filename,mode);
    if(!ifile){
        cout<<"File not found\n";
        return;
    }
}
orderDetails::orderDetails(){}
orderDetails::orderDetails(int f):flag(f){}

int  orderDetails ::  generateOrderId(){
    srand(time(0));
    int id = rand() % 900;
    if(validateOrderId(id) == 0)
        return generateOrderId();
    else
        return id;
}
int orderDetails :: validateOrderId(int id ){
    opener(orderFile,fileName,ios::app);
    if(!orderFile){
        cout<<"Exit through read in order\n";
        exit(0);
    }
    while(!orderFile.eof()){
            unpack();
            if(orderFile){
                if(id == orderId){
                    orderFile.close();
                    return 0;
                }
            }
        }
        orderFile.close();
        return 1;

}
void orderDetails :: read(){
    opener(orderFile,fileName,ios::app);
    if(!orderFile){
        cout<<"Exit through read in order\n";
        exit(0);
    }
   do
    {
        cout << "Enter item id: ";
        cin >> itemId;
        if(cin.good())
            break;
        cin.clear();
        string str;
        cin>>str;
        if(str=="quit")
        break;
        // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout<<"\n Enter valid input for id(whole number)\n";
    } while(1);
    
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    do
    {
       cout<<"Enter the quantity";
        cin>>quantity;  
        if(cin.good())
            break;
        cin.clear();
        string str;
        cin>>str;
        if(str=="quit")
        break;
        // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        cout<<"\n Enter valid input for quantity(whole number)\n";
    } while (1);
    //  cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(!itemobj.search(itemId)){
        cout<<"Item Id does not exists!\n";
        orderFile.close();
        return;
    }
    int availQuantity = validate(itemId,quantity);
    if(availQuantity != 0 )
    {
        cout<<"The available quantity is only "<< availQuantity <<endl;
        cout<<"Sorry cant make the order !!! \n";
        orderFile.close();
        return;
    }
    amount=calculateAmount(itemId);
    pack(0);
    count++;
    itemobj.modify(itemId,quantity * (-1) );
    orderFile.close();
}
int orderDetails :: validate(int itemId , int quantity){

    if(itemobj.getQuantity(itemId) < quantity ){
        cout<< itemobj.getQuantity(itemId);
        return quantity;
    }
    else
        return 0;   
}
void orderDetails :: pack(int flag){
    char buffer[75];
    char temp[10];
    itoa(orderId,buffer,10);
    cout<<temp;
    strcat(buffer,"|");
    strcat(buffer,itoa(itemId,temp,10));
    strcat(buffer,"|");
    strcat(buffer,itoa(quantity,temp,10));
    strcat(buffer,"|");
    strcat(buffer,itoa(amount,temp,10));
    strcat(buffer,"#");
    orderFile.fill('*');
    if(flag == 0)
        orderFile<<setiosflags(ios::left)<<setw(sizeof(orderDetails) +4)<<buffer<<endl;
    else
        orderFile<<setiosflags(ios::left)<<setw(sizeof(orderDetails)+ 4)<<buffer;
}
float  orderDetails :: calculateAmount(int itemId){
    // cout<<"getprice return:"<<itemobj.getPrice(itemId);
  return  itemobj.getPrice(itemId) * quantity;
}
void orderDetails::unpack(){
    char buffer[50],oidBuf[10],iidBuf[10],quantitybuf[10],amountBuf[10];
    orderFile.getline(oidBuf,10,'|');
    orderFile.getline(iidBuf,10,'|');
    orderFile.getline(quantitybuf,10,'|');
    orderFile.getline(amountBuf,10,'#');
    orderFile.getline(buffer,50,'\n');
    orderId=atoi(oidBuf);
    itemId=atoi(iidBuf);
    quantity=atoi(quantitybuf);
    amount=atof(amountBuf);
}
void orderDetails::particularOrderAccessing(int currOrderId,int f){
    opener(orderFile,fileName,ios::in);
    if(!orderFile){
        cout<<"Exit through particular order accessing in order details\n";
        exit(0);
    }
    // int currOrderId=orderId;
    cout<<setiosflags(ios::left);
    cout<<setw(10)<<"Item Id"<<setw(25)<<"Item Name"<<setw(10)<<"Quantity"<<setw(25)<<"PricePerUnit"<<setw(10)<<"Amount"<<endl;
    while(1){
        unpack();
        // cout<<"currOrderId: "<<currOrderId<<"OrderId: "<<orderId<<endl;
        if(orderFile.eof())
            break;
        
        else if(currOrderId==orderId){
            if(quantity>0){
                if(f){
                chefobj.itemId = itemId;
                chefobj.quantity = quantity;
                strcpy(chefobj.itemName , itemobj.getItemName(itemId));
                chefobj.insert(quantity);
                }
                cout<<setw(10)<<itemId<<setw(25)<<itemobj.getItemName(itemId)<<setw(10)<<quantity<<setw(25)<<itemobj.pricePerUnit<<setw(10)<<amount<<endl;
            }
        }
    }
    orderFile.close();
}
float orderDetails :: calculateTotalAmount(int id){
        opener(orderFile,fileName,ios::in);
        if(!orderFile)
        {
            cout<<"Exit through calculateAmount in orders";
            exit(0);
        }
        float total = 0.0;
        int flag = 0;
        while(!orderFile.eof()){
            unpack();
            if(orderFile){
                if(id == orderId && quantity>0){
                    total = total + amount; 
                    flag = 1;
                }
                else if(flag == 1)
                    break;
            }
        }
        orderFile.close();
        return total;
}
int orderDetails :: calculateTotalQuantity(int id){
        opener(orderFile,fileName,ios::in);
        int total = 0;
        int flag = 0;
        while(!orderFile.eof()){
            unpack();
            if(orderFile){
                if(id == orderId){
                    total = total + quantity; 
                    flag = 1;
                }
                else if(flag == 1)
                    break;
            }
        }
        orderFile.close();
        return total;
}
void orderDetails :: modify(int id , int item , int num){
    int pos ;
    opener(orderFile,fileName,ios::in|ios::binary|ios::out);
    if(!orderFile){
        cout<<"Exit through modify in order details\n";
        exit(0);
    }
    while(!orderFile.eof()){
        pos = orderFile.tellg();
        unpack();
            if(id == orderId && item == itemId){
                orderFile.seekp(pos);
                itemobj.modify(item,quantity-num);
                quantity = num;
                amount=calculateAmount(item);
                pack(1);
                orderFile.close();
                return;
            }
    }
    cout<<"Have not ordered this!\n";
    orderFile.close();
}
void orderDetails::deleteOrder(int id){
    cout<<"Size"<<sizeof(orderDetails);
    int f = 0;
     opener(orderFile,fileName,ios::in|ios::binary|ios::out);
    if(!orderFile){
        cout<<"Exit through delete order in order details\n";
        exit(0);
    }
    int items[10];
    int i = 0 ;
    while(!orderFile.eof()){
        unpack();
        if(id == orderId){
            items[i] = itemId;
            i++;
        }
    }
    f = i;
    orderFile.close();
    for(i = 0 ; i < f;i++){
        modify(id,items[i],0);
    }

    
}