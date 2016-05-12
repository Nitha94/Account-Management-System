//  main.cpp
//  Created by Nivetha Mahalakshmi Balasamy on 5/4/16.
//  Copyright © 2016 Nivetha Mahalakshmi Balasamy. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <time.h>
#include <iomanip>
#include "Account.h"
#include "StockAccount.h"
#include "BankAccount.h"
using namespace std;

int main(int argc, const char * argv[]) {
    
    int choice,menu=0;
    string ticker;
    int shares;
    double amount,viewaccbalance,deposit,withdraw;
    
    time_t seconds;
    tm * timeinfo;
    int hour,min,sec;
    ifstream file;
    string price;
    double balance;
    Time *timeone;
    int setvar;
    
    BankAccount ba;
    LinkedList ll;
    Stat1 obj;
    
FirstMenu:
    while(1){
        cout << endl << "Welcome to the Account Management System. Please select an account to access:" << endl
        << "1. Stock Portfolio Account" << endl
        << "2. Bank Account" << endl
        << "3. Exit" << endl
        << "Option:";
        cin >> menu;
        switch(menu){
            case 1:
            {
                while(1){
                std::cout<<"\nMENU\n";
                std::cout<<"1.  Display price for stock\n";
                std::cout<<"2.  Display current portfolio\n";
                std::cout<<"3.  Buy Shares\n";
                std::cout<<"4.  Sell Shares\n";
                std::cout<<"5.  *View Portfolio History in Graph\n"; // MATLAB
                std::cout<<"6.  View Transaction History\n";
                std::cout<<"7.  Return to previous Menu\n";
                std::cout<<"Please Enter your choice:";
                
                //std::cout<<"Please enter your option";
                cin>>choice;
                
                switch(choice){
                    case 1:
                        double value;
                        cout<<"Enter Ticker Symbol\n";
                        cin>>ticker;
                        value=ll.getprice(ticker);
                        cout<<value;
                        break;
                        
                    case 2:
                        ll.quicksort();
                        ll.display();
                        //ll.printlist();
                        break;
                    case 3:
                        cout<<"Enter Company-Symbol\n";
                        cin>>ticker;
                        cout<<"Enter number of shares\n";
                        cin>>shares;
                        cout<<"Enter amount\n";
                        cin>>amount;
                        ll.buyshares(ticker, shares, amount);
                        break;
                        
                    case 4:
                        cout<<"Enter Company-Symbol\n";
                        cin>>ticker;
                        cout<<"Enter number of shares\n";
                        cin>>shares;
                        cout<<"Enter amount\n";
                        cin>>amount;
                        ll.sellshares(ticker, shares, amount);
                        break;
                        
                    case 5:
                        //MATLAB INTEGRATION FOR GRAPH
                        
//                        Engine *ep;
//                        ep=engOpen(NULL);
//                        if(ep==NULL){
//                            cout<<"Error: Not Found"<<endl;
//                            exit(1);
//                        }
//                        //double x[5]={11.1,12.1,13.1,14.1,15.1};
//                        //double y[1]={55.97};
//	                       mxArray* m_X;
//                        mxArray* m_Y;
//                        //mxArray *m_Y;
//                        m_X = mxCreateDoubleMatrix(1,5,mxREAL);
//                        m_Y = mxCreateDoubleMatrix(1,5,mxREAL);
//                        memcpy((void*) mxGetPr(m_X),(void*)x, sizeof(double)*5);
//                        memcpy((void*) mxGetPr(m_Y),(void*)y, sizeof(double)*5);
//                        //engPutVariable(ep,"x",m_X);
//                        engPutVariable(ep,"x",m_X);
//                        engPutVariable(ep,"y",m_Y);
//                        
//                        //PLOT:
//                        engEvalString(ep,"plot(x,y);");
                        
                        
                        case 6:
                        ll.viewtransactionhistory();
                        break;
                        
                    case 7:
                        ll.addtoportfoliohistory();
                        goto FirstMenu;
                        
                }
                }
                
                case 2:
                {
                    while(1){
                    std::cout<<"\nMENU\n";
                    std::cout<<"1.  View Account Balance\n";
                    std::cout<<"2.  Deposit Funds\n";
                    std::cout<<"3.  Withdraw Funds\n";
                    std::cout<<"4.  Show Bank Transaction\n";
                    std::cout<<"5.  Enter amount to deposit in Account and view current Time\n";
                    std::cout<<"6.  Enter amount to Withdraw from Account and view current Time\n";
                    std::cout<<"7.  View in order of most recent Transactions\n";
                    std::cout<<"8.  View in order of earliest Transactions\n";
                    std::cout<<"9.  Return to previous menu\n";
                    std::cout<<"Please Enter your choice\n ";
                    cin>>choice;
                    switch(choice){
                            
                        case 1:
                            viewaccbalance=ba.viewaccountbalance();
                            cout<<"Account Balance is: $"<<viewaccbalance<<endl;
                            break;
                            
                            
                        case 2:
                            cout<<"Enter amount to deposit in Account\n";
                            cin>>deposit;
                            ba.depositcash(deposit);
                            break;
                            
                            
                        case 3:
                            cout<<"Enter amount to Withdraw\n";
                            cin>>withdraw;
                            ba.withdrawcash(withdraw);
                            break;
                            
                        case 4:
                            ba.printbankaccounthistory();
                            break;
                            
                        case 5:
                            cout<<"Enter amount to deposit in Account and view current Time\n";
                            cin>>deposit;
                            //time_t seconds;
                            seconds = time(NULL);
                            //cout<<"The number of seconds since January 1, 1970 is:" <<seconds<<"\n";
                            //tm * timeinfo;
                            timeinfo = localtime(&seconds);
                            //int blah=timeinfo->tm_hour;
                            hour=timeinfo->tm_hour;
                            min=timeinfo->tm_min;
                            sec=timeinfo->tm_sec;
                            
                            ba.updatecashbalance(deposit);
                            //                        ifstream file;
                            //                        string price;
                            //                        double balance;
                            if(hour>12 && hour<23)
                                setvar=1;
                            else
                                setvar=0;
                            timeone=new CivilianTime(hour,min,setvar);
                            timeone->tell();
                            file.open("Cash_Balance_Account.txt");
                            if(file.is_open()){
                                while(getline(file,price)){
                                    stringstream ss(price);
                                    if(ss>>balance){
                                        ofstream myfile;
                                        myfile.open("Bank_Acc_Tran_History_1.txt",ios::app);
                                        if(myfile.is_open()){
                                            myfile<<"DEPOSIT(NEW)"<<setw(10)<<(deposit)<<setw(10)<<balance<<setw(10)<<hour<<":"<<min<<endl;
                                            //myfile<<"DEPOSIT"<<" "<<(deposit)<<" "<<balance<<" "<<endl;
                                        }
                                        
                                        // file.out(bal);
                                    }// endif
                                    
                                    
                                }//endwhile
                                
                            }//fileopen end
                            break;
                            
                        case 6:
                            cout<<"Enter amount to Withdraw from Account and view current Time\n";
                            cin>>withdraw;
                            //time_t seconds;
                            seconds = time(NULL);
                            //cout<<"The number of seconds since January 1, 1970 is:" <<seconds<<"\n";
                            //tm * timeinfo;
                            timeinfo = localtime(&seconds);
                            //int blah=timeinfo->tm_hour;
                            hour=timeinfo->tm_hour;
                            min=timeinfo->tm_min;
                            sec=timeinfo->tm_sec;
                            ba.updatecashbalancewithdraw(withdraw);
                            //                        ifstream file;
                            //                        string price;
                            //                        double balance;
                            if(hour>12 && hour<23)
                                setvar=1;
                            else
                                setvar=0;
                            timeone=new CivilianTime(hour,min,setvar);
                            timeone->tell();
                            file.open("Cash_Balance_Account.txt");
                            if(file.is_open()){
                                while(getline(file,price)){
                                    stringstream ss(price);
                                    if(ss>>balance){
                                        ofstream myfile;
                                        myfile.open("Bank_Acc_Tran_History_1.txt",ios::app);
                                        if(myfile.is_open()){
                                            myfile<<"WITHDRAW(NEW)"<<setw(10)<<(withdraw)<<setw(10)<<balance<<setw(10)<<hour<<":"<<min<<endl;
                                        }
                                        
                                        // file.out(bal);
                                    }// endif
                                    
                                    
                                }//endwhile
                                
                            }//fileopen end
                            break;
                            
                        case 7:
                            obj.upGrade1();
                            obj.readVector();
                            break;
                            
                        case 8:
                            obj.downGrade1();
                            obj.readVector();
                            break;
                            
                        case 9:
                            goto FirstMenu;
                            
                    }
                    
                }
                
                case 3:
                    exit(0);
                }
            }
    }
return 0;
}
}
