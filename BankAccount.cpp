//
//  BankAccount.cpp
//  Created by Nivetha Mahalakshmi Balasamy on 5/4/16.
//  Copyright © 2016 Nivetha Mahalakshmi Balasamy. All rights reserved.
//

//#include <stdio.h>

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include "BankAccount.h"
using namespace std;

double BankAccount::viewaccountbalance(){
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

void BankAccount::updatecashbalance(double cashvalue){
    ifstream file;
    string price;
    double balance;
    file.open("Cash_Balance_Account.txt");
    if(file.is_open()){
        while(getline(file,price)){
            stringstream ss(price);
            if(ss>>balance){
                double bal= balance+cashvalue;
                cout<<"Balance is:"<<bal<<endl;
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

void BankAccount::updatecashbalancewithdraw(double cashvalue){
    ifstream file;
    string price;
    double balance;
    file.open("Cash_Balance_Account.txt");
    if(file.is_open()){
        while(getline(file,price)){
            stringstream ss(price);
            //double balance;
            if(ss>>balance){
                double bal= balance-cashvalue;
                cout<<"Balance is:"<<bal<<endl;
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


void BankAccount::depositcash(double deposit){
    time_t seconds;
    seconds = time(NULL);
    //cout<<"The number of seconds since January 1, 1970 is:" <<seconds<<"\n";
    tm * timeinfo;
    timeinfo = localtime(&seconds);
    //int blah=timeinfo->tm_hour;
    int hour=timeinfo->tm_hour;
    int min=timeinfo->tm_min;
    int sec=timeinfo->tm_sec;
    
    updatecashbalance(deposit);
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
                    myfile<<"DEPOSIT"<<setw(10)<<(deposit)<<setw(10)<<balance<<setw(10)<<hour<<":"<<min<<":"<<sec<<endl;
                }
                
                // file.out(bal);
            }// endif
            
            
        }//endwhile
        
    }//fileopen end
    
}

void BankAccount::withdrawcash(double withdraw){
    
    time_t seconds;
    seconds = time(NULL);
    //cout<<"The number of seconds since January 1, 1970 is:" <<seconds<<"\n";
    tm * timeinfo;
    timeinfo = localtime(&seconds);
    //int blah=timeinfo->tm_hour;
    int hour=timeinfo->tm_hour;
    int min=timeinfo->tm_min;
    int sec=timeinfo->tm_sec;
    updatecashbalancewithdraw(withdraw);
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
                    myfile<<"WITHDRAW"<<setw(10)<<(withdraw)<<setw(10)<<balance<<setw(10)<<hour<<":"<<min<<":"<<sec<<endl;
                }
                
                // file.out(bal);
            }// endif
            
            
        }//endwhile
        
    }//fileopen end
}

void BankAccount::printbankaccounthistory(){
    ifstream file;
    file.open("Bank_Acc_Tran_History_1.txt",std::ifstream::binary);
    string event;
    if(file.is_open()){
        while(!file.eof()){
            getline(file,event);
            cout<<event<<endl;
            
        }
        file.close();
        
        
    }
    
}




