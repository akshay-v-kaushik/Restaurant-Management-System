#include<string>
#ifndef BILL_HPP
#define BILL_HPP
using namespace std;
// fstream ifile;
class Bill{

    public :
      int   orderId;
      int   totalQuantity;
      float totalAmount;
      char method[25];
      char billingTime[15];
      char billingDate[15];
     public:
       void opener(fstream &ifile,char *filename,ios_base::openmode mode);
       void read(int id) ;
       void pack() ;
       void unpack() ;
       void displayAll() ;
       void displayToday();
       void search() ;
      //  void removeRecord() ;
       void modify() ;
       void accessing();
       char * getMethod(int id);
};
#endif