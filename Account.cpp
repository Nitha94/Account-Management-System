//
//  Account.cpp
//  Created by Nivetha Mahalakshmi Balasamy on 5/4/16.
//  Copyright © 2016 Nivetha Mahalakshmi Balasamy. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>

#include "Account.h"
using namespace std;


double Account::getcashbalance(){
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

