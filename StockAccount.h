//
//  StockAccount.h
//  Created by Nivetha Mahalakshmi Balasamy on 5/4/16.
//  Copyright © 2016 Nivetha Mahalakshmi Balasamy. All rights reserved.
//

#ifndef StockAccount_h
#define StockAccount_h

#include "Account.h"

using namespace std;

class StockAccount{
private:
    double cashbalance;
    
public:
    double getcashbalance();
    void displaypriceforstock(string);
    
    
};

class Node{
    friend class LinkedList;
    
private:
    
    string item_name;
    int item_no;
    Node *next;
    Node *prev;
    
public:
    Node(string &,int);
    Node* getnext();
    
};

class LinkedList:public Account{
    
private:
    Node* start;
    Node* end;
    int list_size;
    
public:
    LinkedList();
    bool isEmpty();
    void printlist();
    Node* createnode(string name, int no);
    void addtostart(string item, int num);
    void addtolist(string item,int num);
    void buyshares(string ticker,int shares, double amount);
    bool checkIfItemExists(string symbol, int num, double stockValue);
    void updatecashbalance(int num, double stockprice);
    void displayportfolio(string ticker,int shares,double price);
    void displayport();
    void addstocktofile();
    double getpriceforticker(string ticker);
    double getcashbalance();
    //Transaction History
    void savetransactionhistory(string event,string ticker,int shares,double price,double total);
    void viewtransactionhistory();
    void bankacctranshistory(string,int,double);
    //Sell Shares
    void sellshares(string ticker,int sellshares,double price);
    void bankacctranshistorysell(string,int,double);
    void updatecashbalancesell(int,double);
    void deleteatstart();
    void deleteitemnumber(int);
    void swap(int*,int*);
    Node* lastNode(Node*);
    Node* partition(Node*,Node*);
    void _quicksort(Node*,Node*);
    void quicksort();
    //Adding Portfolio history
    void addtoportfoliohistory();
    void display();
    void swap1(string*,string*);
    double getprice(string);
    
};











#endif /* StockAccount_h */
