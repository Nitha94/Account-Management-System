//
//  StockAccount.cpp
//  Bank Account Management
//  Created by Nivetha Mahalakshmi Balasamy on 5/02/16.
//  Copyright © 2016 Nivetha Mahalakshmi Balasamy. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <iomanip>
#include <time.h>

#include "StockAccount.h"
using namespace std;

void StockAccount::displaypriceforstock(string search){
    ifstream fileInput;
    //int offset;
    string line;
    srand((unsigned)time(0));
    
    int val= rand()%2+1;
    if(val==1)
        fileInput.open("Results1.txt");
    else
        fileInput.open("Results2.txt");
    if(fileInput.is_open()) {
        while(getline(fileInput,line)) {
            stringstream ss(line);
            double price;
            string a;
            if(ss>>a>>price){
                if(a==search && !fileInput.eof()){
                    std::cout<<a<<"\t"<<price<<endl;
                    break;
                }
                
            }
            
        }//while end
        cout<<"Ticker not Found.....";
        fileInput.close();
    }
    else cout << "Unable to open file.";
    
}

Node::Node(string& i_name,int i_no):item_name(i_name),item_no(i_no){
    this->next = NULL;
    this->prev=NULL;
    
}
// Node constructor

LinkedList::LinkedList(){
    this->start = NULL;
    this->end = NULL;
    list_size=0;
}// LinkedList constructor

bool LinkedList::isEmpty(){
    return start==0;
}//isEmpty condition

Node* LinkedList::createnode(string name, int num){
    Node* newnode = new Node(name,num);
    return newnode;
}// create a new node

void LinkedList::addtostart(string item, int no){
    Node* new_node = createnode(item,no);
    if(isEmpty())
        start=end=new_node;
    else{
        new_node->prev=NULL;
        new_node->next=start;
        start->prev=new_node;
        start=new_node;
    }
}

void LinkedList::addtolist(string item,int num){
    Node* currptr=start;
    while(currptr!=0){
        if(currptr->item_name==item)
        {
            currptr->item_no=currptr->item_no+num;
            
        }// end if
        
        else
            addtostart(item,num);
    }
    
    
}


void LinkedList::printlist(){
    Node* currptr = start;
    if(isEmpty())
        std::cout<<"The Portfolio is empty\n";
    else{
        while(currptr!=0){
            std::cout<<currptr->item_no<<"\t";
            std::cout<<currptr->item_name<<"\n";
            currptr=currptr->next;
        }
    }
}

bool LinkedList::checkIfItemExists(string symbol, int num, double stockValue){
    
    Node *newPtr = start;
    
    while ( newPtr != 0){
        
        if ( newPtr->item_name == symbol){
            
            newPtr->item_no=num+newPtr->item_no;
            
            
            cout << "You have purchased " << num << " shares of " << symbol << " at "<< stockValue << " each for a total of " << (num*stockValue) << endl;
            cout << "Total number of " << symbol << " shares = " << newPtr->item_no<<endl << endl;
            
            updatecashbalance(num,stockValue);
            savetransactionhistory("BUY",symbol, num, stockValue,(num*stockValue));
            bankacctranshistory("WITHDRAW",num,stockValue);
            
            return true;
        }
        newPtr = newPtr -> next;
    }
    return false;
    
}

void LinkedList::updatecashbalance(int num, double stockprice){
    
    ifstream file;
    string price;
    double balance;
    
    file.open("Cash_Balance_Account.txt");
    if(file.is_open()){
        while(getline(file,price)){
            stringstream ss(price);
            //double balance;
            if(ss>>balance){
                double bal= balance-(num*stockprice);
                cout<<"Balance is: $"<<bal<<endl;
                ofstream myfile;
                myfile.open("Cash_Balance_Account.txt");
                if(myfile.is_open()){
                    myfile<<bal;
                }
                
                // file.out(bal);
            }// endif
            
            
        }//endwhile
        
    }//fileopen end
}
// BUY SHARES
void LinkedList::buyshares(string ticker,int shares,double amount){
    double stock_purchase_amount=shares*amount;
    ifstream file;
    string price;
    double balance;
    double actual_stock_bought;
    file.open("Cash_Balance_Account.txt");
    if(file.is_open()){
        while(getline(file,price)){
            stringstream ss(price);
            //double balance;
            if(ss>>balance){
                if(stock_purchase_amount>balance){
                    std::cout<<"Insufficient Balance to buy stocks";
                }
            }// endif
            
            
        }//endwhile
        
    }//fileopen end
    //
    ifstream fileInput;
    //int offset;
    string line;
    srand((unsigned)time(0));
    string a;
    int val= rand()%2+1;
    
    if(val==1)
        fileInput.open("Results1.txt");
    else
        fileInput.open("Results2.txt");
    
    if(fileInput.is_open()) {
        while(getline(fileInput,line)) {
            stringstream ss(line);
            double price;
            if(ss>>a>>price){
            
                if(a==ticker && price>amount){
                    std::cout<<"Stock price for "<<ticker<<" higher than what you are willing to pay. Transaction Failed"<<endl;
                    break;
                }
                
                else if(a==ticker && price<=amount){
                    actual_stock_bought=price*shares;
                    
                    if(checkIfItemExists(ticker,shares,price)==false)
                    {
                        addtostart(ticker,shares);
                        cout << "You have purchased " <<shares<< " shares of " << ticker << " at "<< price << " each for a total of " << (shares*price) << endl << endl;
                        updatecashbalance(shares,price);
                        savetransactionhistory("BUY",ticker, shares, price,(shares*price));
                        bankacctranshistory("WITHDRAW",shares,price);
                    }
                    printlist();
                    addstocktofile();
                    break;
                }
                
                else if(fileInput.eof()){
                    std::cout<<"The Ticker is not present"<<endl;
                    
                }
                
            }
            else{
                
            }
            
        }// end while loop
        
        //cout<<"Transaction Failed. Stock not found"<<endl;
        fileInput.close();
    }
    else cout << "Unable to open file.";
    
}

void LinkedList::displayportfolio(string ticker, int shares, double price)
{
    double totalprice=shares*price;
    ofstream file;
    file.open("display_portfolio_txt.txt");
    if(file.is_open()){
        file<<"TICKER"<<" "<<"SHARES"<<" "<<"PRICE/SHARE"<<" "<<"TOTAL PRICE"<<endl;
        file<<ticker<<" "<<shares<<" "<<price<<" "<<totalprice<<endl;
        
    }
    cout<<ticker<<" "<<shares<<" "<<price<<" "<<totalprice<<endl;
    
    
}

void LinkedList::addstocktofile()
{
    Node* currptr = start;
    if(isEmpty())
        std::cout<<"The Portfolio is empty\n";
    else{
        ofstream myfile;
        myfile.open("stock_portfolio_text.txt");
        while(currptr!=0){
            myfile<<currptr->item_no<<"\t";
            myfile<<currptr->item_name<<"\n";
            currptr=currptr->next;
        }
    }
}

double LinkedList::getpriceforticker(string ticker)
{
    ifstream fileInput;
    srand((unsigned)time(0));
    string a;
    double price;
    string date;
    int val=rand()%2+1;
    if(val==1)
        fileInput.open("Results1.txt");
    else
        fileInput.open("Results2.txt");
    while(fileInput>>a>>price>>date){
        if(a==ticker){
            //cout<<price;
            return price;
            //cout<<price;
        }
        //        else
        //            cout<<"Stock not found"<<endl;
    }
    //cout<<"Stock not found"<<endl;
    return 0;
}

void LinkedList::displayport()
{
    double value = 0.0;
    double totalprice = 0.0;
    double sumprice=0.0;
    double result;
    ifstream file;
    file.open("stock_portfolio_text.txt");
    string ticker;
    int shares;

    if(file.is_open()){
        while(file>>shares>>ticker){
            value=getpriceforticker(ticker);
            totalprice=shares*value;
            sumprice=sumprice+totalprice;
            ofstream portfolio;
            portfolio.open("port_out.txt",ios::app);
            if(portfolio.is_open()){
                cout<<ticker<<" "<<shares<<" "<<value<<" "<<totalprice<<endl;
                portfolio<<ticker<<" "<<shares<<" "<<value<<" "<<totalprice<<endl;
            }
            
        }
        cout<<"Sum Price: $"<<sumprice<<endl;
        result=getcashbalance();
        cout<<"CASH BALANCE:$"<<result<<endl;
        cout<<"TOTAL VALUE: $"<<(result+sumprice)<<endl;
        
        file.close();// closing portfolio here//
       
    }
    
}

double LinkedList::getcashbalance()
{
    double cashbalancevalue;
    ifstream myfile;
    myfile.open("Cash_Balance_Account.txt");
    if(myfile.is_open()){
        while(myfile>>cashbalancevalue){
            return cashbalancevalue;
        }
        
    }
    myfile.close();
    return 0;
    
    
}

void LinkedList::savetransactionhistory(string event,string ticker,int shares,double price,double total){
    time_t seconds;
    seconds = time(NULL);
    //cout<<"The number of seconds since January 1, 1970 is:" <<seconds<<"\n";
    tm * timeinfo;
    timeinfo = localtime(&seconds);
    //cout<<"The current local time and date is:"<<asctime(timeinfo);
    ofstream file;
    file.open("Transaction_History_1.txt",ios::app);
    if(file.is_open()){
        file<<event<<" "<<ticker<<" "<<shares<<" "<<price<<" "<<total<<" "<<asctime(timeinfo)<<endl;
        
    }
    
}

void LinkedList::viewtransactionhistory()
{
    ifstream file;
    file.open("Transaction_History_1.txt",std::ifstream::binary);
    string event,ticker,day,month,time;
    
    if(file.is_open())
    {
        while(!file.eof()){
            getline(file,event);
            cout<<event<<endl;
            
        }
        file.close();
        
        
    }
    
}
// FOR buy shares
void LinkedList::bankacctranshistory(string event,int num,double stockprice){
    
    time_t seconds;
    seconds = time(NULL);
    //cout<<"The number of seconds since January 1, 1970 is:" <<seconds<<"\n";
    tm * timeinfo;
    timeinfo = localtime(&seconds);
    //int blah=timeinfo->tm_hour;
    int hour=timeinfo->tm_hour;
    int min=timeinfo->tm_min;
    int sec=timeinfo->tm_sec;
    //cout<<"The current local time and date is:"<<asctime(timeinfo);
    
    ifstream file;
    string price;
    double balance;
   
    file.open("Cash_Balance_Account.txt");
    if(file.is_open()){
        while(getline(file,price)){
            stringstream ss(price);
            //double balance;
            if(ss>>balance){
                ofstream myfile;
                myfile.open("Bank_Acc_Tran_History_1.txt",ios::app);
                if(myfile.is_open()){
                    myfile<<event<<setw(10)<<(num*stockprice)<<setw(10)<<balance<<setw(10)<<hour<<":"<<min<<":"<<sec<<endl;
                }
                
                // file.out(bal);
            }// endif
            
            
        }//endwhile
        
    }//fileopen end
    
    
}

void LinkedList::sellshares(string ticker,int sellshares,double price){
    double stockpricefromresults;
    double sellprice;
    Node* currptr=start;
    while(currptr!=0){
        if(currptr->item_name==ticker)
        {
            stockpricefromresults=getpriceforticker(ticker);
            if(stockpricefromresults<=price){
                cout<<"Transaction Failed. Actual stock price is lesser"<<endl;
                break;
            }
            else{
                currptr->item_no=currptr->item_no-sellshares;
                if(currptr->item_no==0){
                    //delete node
                    deleteitemnumber(0);
                    sellprice=stockpricefromresults;
                    // add to bank acc info
                    updatecashbalancesell(sellshares, stockpricefromresults);
                    savetransactionhistory("SELL",ticker,sellshares,stockpricefromresults,(sellprice*sellshares));
                    bankacctranshistorysell("DEPOSIT",sellshares, sellprice);
                    //REMOVE STOCK FROM FILE
                    cout << "You have sold " << sellshares<< " shares of " << ticker << " at "<< sellprice << " each for a total of " << (sellshares*sellprice) << endl;
                    break;
                    
                }
                else if(currptr->item_no>0){
                  
                    sellprice=stockpricefromresults;
                    cout<<(sellshares*stockpricefromresults)<<endl;
                    updatecashbalancesell(sellshares, stockpricefromresults);
                    savetransactionhistory("SELL",ticker,sellshares,stockpricefromresults,(sellprice*sellshares));
                    bankacctranshistorysell("DEPOSIT",sellshares,sellprice);
                   
                    cout << "You have sold " << sellshares<< " shares of " << ticker << " at "<< sellprice << " each for a total of " << (sellshares*sellprice) << endl;
                    break;
                }
                
                
            }
            
            
        }
        else{
            currptr=currptr->next;
            if(currptr==0)
                cout<<"Transaction Failed. Stock Not Found...\n";
        }
        
        
    }// end of while
   
}

void LinkedList::bankacctranshistorysell(string event,int sellshares,double sellprice){
    time_t seconds;
    seconds = time(NULL);
    //cout<<"The number of seconds since January 1, 1970 is:" <<seconds<<"\n";
    tm * timeinfo;
    timeinfo = localtime(&seconds);
    //int blah=timeinfo->tm_hour;
    int hour=timeinfo->tm_hour;
    int min=timeinfo->tm_min;
    int sec=timeinfo->tm_sec;
    
    ifstream file;
    string price;
    double balance;
   
    file.open("Cash_Balance_Account.txt");
    if(file.is_open()){
        while(getline(file,price)){
            stringstream ss(price);
            if(ss>>balance){
                ofstream myfile;
                myfile.open("Bank_Acc_Tran_History_1.txt",ios::app);
                if(myfile.is_open()){
                    myfile<<event<<setw(10)<<(sellshares*sellprice)<<setw(10)<<balance<<setw(10)<<hour<<":"<<min<<":"<<sec<<endl;
                }
                
                // file.out(bal);
            }// endif
            
            
        }//endwhile
        
    }//fileopen end
}

void LinkedList::updatecashbalancesell(int num,double stockprice){
    ifstream file;
    string price;
    double balance;

    file.open("Cash_Balance_Account.txt");
    if(file.is_open()){
        while(getline(file,price)){
            stringstream ss(price);
            if(ss>>balance){
                double bal= balance+(num*stockprice);
                cout<<"Balance is:"<<bal<<endl;
                ofstream myfile;
                myfile.open("Cash_Balance_Account.txt");
                if(myfile.is_open()){
                    myfile<<bal;
                }
                
            }// endif
            
            
        }//endwhile
        
    }//fileopen end
    
}

void LinkedList::deleteatstart(){
    if(isEmpty()){
        std::cout<<"The portfolio is empty\n";
    }
    else{
        Node* currptr;
        currptr=start;
        start=start->next;
        delete currptr;
    }
    
}

void LinkedList::deleteitemnumber(int num){
    Node* prev= start;
    Node* nexttoprev=start->next;
    while(nexttoprev!=NULL){
        if(nexttoprev->item_no==num){
            break;
        }
        else{
            prev=nexttoprev;
            nexttoprev=nexttoprev->next;
        }
    }
    if(start==NULL){
        std::cout<<"The item is not found\n";
    }
    else if(start->item_no==num){
        deleteatstart();
    }
    else if(nexttoprev==NULL){
        std::cout<<"The item is not found\n";
    }
    else {
        std::cout<<"Deleting "<<nexttoprev->item_name<<endl;
        prev->next=nexttoprev->next;
        delete nexttoprev;
    }
    
}


void LinkedList::swap ( int* a, int* b )
{   int t = *a;      *a = *b;       *b = t;   }


void LinkedList::swap1 ( string* a, string* b )
{   string t = *a;      *a = *b;       *b = t;   }

// A utility function to find last node of linked list

Node* LinkedList::lastNode(Node* root){
    while (root && root->next)
        root = root->next;
    return root;
    
}



Node* LinkedList::partition(Node* l, Node* h){
    int x  = h->item_no*(getpriceforticker(h->item_name));
    //int x=h->item_no;
    
    // similar to i = l-1 for array implementation
    Node *i = l->prev;
    
    // Similar to "for (int j = l; j <= h- 1; j++)"
    for (Node *j = l; j != h; j = j->next)
    {
        if (j->item_no*(getpriceforticker(j->item_name)) >= x)
            //if(j->item_no >=x)
        {
            // Similar to i++ for array
            i = (i == NULL)? l : i->next;
            
            //swap(&(i->item_no, &(j->item_no));
            swap(&(i->item_no), &(j->item_no));
            swap1(&(i->item_name), &(j->item_name));
            
        }
    }
    i = (i == NULL)? l : i->next; // Similar to i++
    swap(&(i->item_no), &(h->item_no));
    swap1(&(i->item_name), &(h->item_name));
    return i;
    
    
}


void LinkedList::_quicksort(Node* l, Node* h){
    if (h != NULL && l != h && l != h->next)
    {
        Node *p = partition(l, h);
        _quicksort(l, p->prev);
        _quicksort(p->next, h);
    }
}

void LinkedList::quicksort(){
    Node* head=start;
    Node* h=lastNode(head);
    _quicksort(head,h);
    
}
// Adding to portfolio history
void LinkedList::addtoportfoliohistory(){
    time_t seconds;
    seconds = time(NULL);
    //cout<<"The number of seconds since January 1, 1970 is:" <<seconds<<"\n";
    tm * timeinfo;
    timeinfo = localtime(&seconds);
    //cout<<"The current local time and date is:"<<asctime(timeinfo);
    string ticker;
    int shares;
    double price,balance;
    double totalprice=0.0;
    
    ofstream file;
    file.open("portfolio_history_out_1.txt",ios::app);
    if(file.is_open()){
        //file<<"TOTAL VALUE"<< setw(10) <<"TIME INFO"<<endl;
        Node* curptr=start;
        balance=getcashbalance();
        
        while(curptr!=0){
            ticker=curptr->item_name;
            shares=curptr->item_no;
            price=shares*getpriceforticker(ticker);
            totalprice=totalprice+price;
            curptr=curptr->next;
        }
        //file<<"TOTAL VALUE"<<setw(10)<<"TIME INFO"<<endl;
        file<<totalprice+balance<< setw(10) <<asctime(timeinfo);
        
    }
    
}
// To Display the current portfolio value
void LinkedList::display(){
    
    string ticker;
    int shares;
    double price;
    double totalprice;
    double sum=0.0;
    Node* currptr=start;
    cout<<"CASH BALANCE: $"<<Account::getcashbalance()<<endl;
    cout<<"\t\t"<<"TICKER"<<"\t\t"<<"SHARES"<<"\t\t\t"<<"PRICE"<<"\t\t\t"<<"TOTAL PRICE"<<endl<<endl;
    while(currptr!=0)
    {
        ticker=currptr->item_name;
        shares=currptr->item_no;
        price=getpriceforticker(ticker);
        totalprice=shares*price;
        sum=sum+totalprice;
        cout<<"\t\t"<<ticker<<setw(7)<<shares<<"\t\t\t"<<price<<"\t\t\t"<<totalprice<<endl<<endl;
        currptr=currptr->next;
    }
    cout<<"CASH BALANCE: $"<<Account::getcashbalance()<<endl;
    cout<<"TOTAL VALUE: $"<<sum+Account::getcashbalance()<<endl;
    
}

double LinkedList::getprice(string ticker){
    ifstream fileInput;
    string symbol,date;
    double price;
    srand((unsigned)time(0));
    int val= rand()%2+1;
    if(val==1)
        fileInput.open("Results1.txt");
    else
        fileInput.open("Results2.txt");
        while (fileInput >> symbol >> price >> date){
            
            if (symbol == ticker){
                return price;
            }
            
        }
        cout << "Stock not found." << endl;
        return 0;
    
}















