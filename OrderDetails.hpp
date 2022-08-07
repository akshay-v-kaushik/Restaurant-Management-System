#include <string>
#ifndef ORDERDETAILS_H
#define ITEM_H
#define ORDERDETAILS_H
using namespace std;
class orderDetails {
public:
  int orderId;
  int itemId;
  int quantity;
  float amount;
  int flag;//this is for reference of whether there is multiple food item or not, generates id if it is first else not

public:
  orderDetails();
  orderDetails(int f);
  void opener(fstream &ifile,char *filename,ios_base::openmode mode);
  void read();
  void pack(int flag) ;
  void unpack() ;
  void display() ;
  int search(int id);
  void removeRecord() ;
  void particularOrderAccessing(int id,int f);
  void modify(int id,int item, int num) ;
  void accessing();
  int generateOrderId();
  int validate(int itemId,int quantity);
  float calculateAmount(int itemId);
  float calculateTotalAmount(int id);
  int calculateTotalQuantity(int id);
  void deleteOrder(int id);
  int validateOrderId(int id);
};
#endif