# Restaurant-Management-System

A File Structure project to manage an entire restaurant system.
This project signifies the need for efficient management of Order, Item, Bill and Chefs records in a file.

In this system, we have a fixed number of fields, each with a maximum length, that combine to make a data record and fixed length record. 
Fixing the number of fields in a record does not imply that the size of fields in the record is fixed. The records are used as containers to hold a mix of fixed and variable-length fields within a record. Fields in a record are identified by
using ‘|’ as a delimiter.
Implementation of indexing in this project is done using hashing technique. 
Hashing is an effective technique to calculate the direct location of a data record on the disk without using index structure. 
In this technique, data is stored at the data blocks whose address is generated by using the hash function. 
It is an ideal method when one wants to retrieve a particular record based on the search key.
In our project, we have implemented static hashing and hash values are generated on the search key using multiplication method and the case of collision, which is the case of bucket overflow, has been resolved by chaining which is also known as closed hashing.