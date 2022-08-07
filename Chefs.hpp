#include<string>
#include<fstream>
#ifndef CHEFS_HPP
#define CHEFS_HPP
using namespace std;
class chefs {
   public :
   int  itemId;
   char itemName[25];
   int quantity;
   public:
      void opener(fstream &ifile,char *fileName,ios_base::openmode mode);
       void read() ;
       void pack() ;
       void unpack() ;
       void display() ;
       int search(int id) ;
       void removeRecord() ;
       void modify(int id,int q);
       void accessing();
       int hash(int id);
       float frac(float x);
       void insert( int extra);
       void insertDummy();
};
#endif