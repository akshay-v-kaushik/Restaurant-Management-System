#include<string>
#ifndef ITEM_HPP
#define ITEM_HPP
using namespace std;
// fstream ifile;
class item {
    public :
       int  itemId;
       char itemName[25];
       char itemCategory[25];
       int  itemStocks;
       float pricePerUnit;
    public:
       void opener(fstream &ifile,char *fileName,ios_base::openmode mode);
       void read() ;
       void pack();
       void unpack();
       void display() ;
       int  search(int id) ;
       void removeRecord() ;
       void modify(int id , int stocks) ;
       void accessing();
       int getQuantity(int id);
       float getPrice(int id);
       char * getItemName(int id);
       void operationsOnItem();
       int hash(int id);
       float frac(float x);
      };
#endif