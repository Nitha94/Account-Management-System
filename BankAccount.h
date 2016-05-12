//
//  BankAccount.h
//  Created by Nivetha Mahalakshmi Balasamy on 5/4/16.
//  Copyright © 2016 Nivetha Mahalakshmi Balasamy. All rights reserved.
//


#ifndef BankAccount_h
#define BankAccount_h
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

class BankAccount{
public:
    double viewaccountbalance();
    void updatecashbalance(double);
    void updatecashbalancewithdraw(double);
    void depositcash(double);
    void withdrawcash(double);
    void printbankaccounthistory();
};

class TimeImp {
public:
    TimeImp(int hr, int min) {
        hr_ = hr;
        min_ = min;
    }
    virtual void tell() {
        cout << "Current Time is "<< hr_ << min_ << endl;
    }
protected:
    int hr_, min_;
};

class CivilianTimeImp: public TimeImp {
public:
    CivilianTimeImp(int hr, int min, int pm): TimeImp(hr, min) {
        if (pm)
            strcpy(whichM_, " PM");
        else
            strcpy(whichM_, " AM");
    }
    
    /* virtual */
    void tell() {
        cout << "Current Time is " << hr_ << ":" << min_ << whichM_ << endl;
    }
protected:
    char whichM_[4];
};

class Time {
public:
    Time(){}
    Time(int hr, int min) {
        imp_ = new TimeImp(hr, min);
    }
    virtual void tell() {
        imp_->tell();
    }
protected:
    TimeImp *imp_;
};

class CivilianTime: public Time {
public:
    CivilianTime(int hr, int min, int pm) {
        imp_ = new CivilianTimeImp(hr, min, pm);
    }
};

class SortImpl1 {
public:  virtual void sort() = 0;
};

class SortBubble1 : public SortImpl1 {
public:
    void sort() {
        ifstream file;
        file.open("Bank_Acc_Tran_History_1.txt",std::ifstream::binary);
        string event;
       
        if(file.is_open())
        {
          while(!file.eof())
          {
                getline(file,event);
                cout<<event<<endl;
                
            }
            file.close();
        }

        
        
    }
};

class SortShell1: public SortImpl1 {
        public:
            void sort() {
                std::vector<std::string> lines_in_reverse;
                std::ifstream in("Bank_Acc_Tran_History_1.txt");
                
                if (in.is_open())
                {
                    //std::vector<std::string> lines_in_reverse;
                    std::string line;
                    while (std::getline(in, line))
                    {
                        // Store the lines in reverse order.
                        lines_in_reverse.insert(lines_in_reverse.begin(), line);
                    }
                }
                for(int i=0;i<lines_in_reverse.size();i++)
                {
                    cout<<lines_in_reverse[i]<<endl;
                }
                
        }
            
        };



class Stat1 {
public:
    Stat1() { m_impl1 = new SortBubble1; }
    void upGrade1() { delete m_impl1; m_impl1 = new SortShell1;}
    void downGrade1() { delete m_impl1; m_impl1 = new SortBubble1;}
    void readVector()
    {
    m_impl1->sort();
        //m_min = v[0]; m_max = v[n-1]; m_median = v[n/2]; }
     }
private:
    //int m_min, m_max, m_median;
    SortImpl1* m_impl1;
};







#endif /* BankAccount_h */
