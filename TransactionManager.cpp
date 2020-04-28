#include<bits/stdc++.h>
#include <stdexcept> 
#include "FileManager.cpp"
#include "MasterRecordManager.cpp"
#include "utilityFunctions.cpp"
#pragma once

using namespace std;

class TransactionManager{
    string filename = "transactions.txt";
public:
    bool addTransaction(map<string,string> details);
    bool removeTransaction(string transaction_id);
    list<string> getAllTxnDetails();
private:
    string getNewTxnNumber();
};

bool TransactionManager::addTransaction(map<string,string> details){
    string newtxnid = getNewTxnNumber();
    string record_line = "";
    MasterRecordManager mrm;
    try{
        if(newtxnid=="-1") throw runtime_error("ERROR Generating TXN ID");
        if(!validDate(details["date"])) throw runtime_error("Invalid Date");
        cout<<"Account No = "<<details["account_no"]<<endl;
        if(!mrm.checkAccountExists(details["account_no"])) throw runtime_error("Account Doesnt Exist"); 

        FileManager fm(filename);
        record_line = record_line + newtxnid + "|" + details["account_no"] + "|" + details["check_number"] + "|" + details["date"] + "|" + details["description"] + "|" + details["debit_credit"]; 
        return fm.addLineToFile(record_line); 
    }
    catch(const char* message){
        cout<<message<<endl;
        return false;
    }
}

bool TransactionManager::removeTransaction(string txn_id){
    try{
        FileManager fm(filename);
        list<string> content = fm.getFileContent();
        for(auto line : content){
            string key = splitString(line,'|').front();
            if(key==txn_id)
                return fm.removeLine(line);
        }
        throw runtime_error("No Records Found");
    }
    catch(const char* message){
        cout<<message<<endl;
        return false;
    }
}

list<string> TransactionManager::getAllTxnDetails(){
    FileManager fm(filename);
    return fm.getFileContent();
}

string TransactionManager::getNewTxnNumber(){
    try{
        FileManager fm(filename);
        list<string> result = fm.getFileContent();
        if(result.size()==0) return "1";
        string last_record = result.back();

        string last_txn_no = splitString(last_record,'|').front(); //get only key
        string new_txn_no = to_string(stoi(last_txn_no)+1);
        return new_txn_no;
    }
    catch(const char* message){
        cout<<message<<endl;
        return "-1";
    }
}