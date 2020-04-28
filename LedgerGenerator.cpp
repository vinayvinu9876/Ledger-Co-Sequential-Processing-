#include<bits/stdc++.h>
#include <stdexcept> 
#include "FileManager.cpp"
#include "MasterRecordManager.cpp"
#include "TransactionManager.cpp"
#include "utilityFunctions.cpp"
#pragma once

using namespace std;


class LedgerGenerator{
    string months[12] = {"Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
    MasterRecordManager mrm;
    TransactionManager tm;
public:
    bool generateLedger();
private:
    string   getAggregatedLine(list<list<string>> transactions);
    string getLedgerFileName();
    string getLedgerHeader();
    list<list<string>> getAllMatchingTXN(string account_no,list<string> transaction_records);
    int getMonth();
};



bool LedgerGenerator::generateLedger(){
    try{
        FileManager ledger(getLedgerFileName());
        ledger.addLineToFile(getLedgerHeader());

        cout<<"Added Ledger Headers"<<endl;
        list<string> master_records = mrm.getAllAccountDetails();
        cout<<"Got Master Records id = "<<master_records.front()<<endl;
        list<string> transaction_records = tm.getAllTxnDetails();
        cout<<"Got Transaction Records "<<transaction_records.front()<<endl;

        for(auto master : master_records ){
            cout<<"Got master value "<<master<<endl;
            list<string> master_values = splitString(master,'|');
            cout<<"Got list"<<endl;
            string account_no = getAtIndex(master_values,0); //account no is first column
            cout<<"Got account no "<<account_no<<endl;
            list<list<string>> matching_transactions = getAllMatchingTXN(account_no,transaction_records);
            cout<<"Got matching transactions Get At Index "<<getAtIndex(master_values,1)<<endl;
            string ledger_line = account_no + "|" + getAtIndex(master_values,1) + "|" + getAggregatedLine(matching_transactions);
            cout<<"Got  ledger Line"<<endl;
            ledger.addLineToFile(ledger_line);
            cout<<"Done"<<endl;
        }

        return true;

    }   
    catch(const char* message){
        cout<<message<<endl;
        return false;
    }
}

list<list<string>> LedgerGenerator::getAllMatchingTXN(string account_no,list<string> transaction_records){
    list<list<string>> matching_records;

    for(auto transaction : transaction_records){
        list<string> transaction_values = splitString(transaction,'|');
        //account no is stored in second column (indexing from 0,1)
        if(getAtIndex(transaction_values,1)==account_no)
            matching_records.push_back(transaction_values);
    }

    return matching_records;
}
string  LedgerGenerator::getAggregatedLine(list<list<string>> transactions){
    string aggregate_line = "";
    list<string> month_calc;
    // <month,balance>
    map<int,int> month_holder;
    for(int i=1;i<=12;i++){
        month_holder.insert(pair<int,int>(i,0));
    }

    cout<<"Inserted Month Holder"<<endl;
    for(auto transaction : transactions){
        cout<<"Transaction id = "<<transaction.front()<<endl;
        //date is in 4(4-1 index)rd column and debit/credit in 6(6-1 index)th colummn (index starts at 0)
        string date = getAtIndex(transaction,3);
        cout<<"Date = "<<date<<endl;
        list<string> split_date =  splitString(date,'/');
        int month = stoi(getAtIndex(split_date,1));
        cout<<"Got month"<<month<<endl;
        int amount = stoi(getAtIndex(transaction,5));
        cout<<"Got amount "<<amount<<endl;
        month_holder[month] = month_holder[month] + amount;
        cout<<"Month_holder[month] = "<<month_holder[month]<<endl;
    }

    cout<<"Out of loop"<<endl;
    for(int i=1;i<=12;i++){
        cout<<"Getting i="<<i<<endl;
        aggregate_line = aggregate_line + to_string(month_holder[i]);
        cout<<"aggregate line = "<<aggregate_line<<endl;
        if(i<12) //donot add |
            aggregate_line = aggregate_line + "|";
    }
    cout<<"Aggregate line "<<aggregate_line;
    return aggregate_line;
}

string LedgerGenerator::getLedgerFileName(){
    return "Ledger-" + getCurrentDateAndTime() + ".txt";
}

string LedgerGenerator::getLedgerHeader(){
    string headers = "Account_No | Account_Name |";
    for(int i=0;i<12;i++){
        headers = headers + months[i];
        if(i<11) //donot add to last one
             headers = headers + "|";
    }
    return headers;
}