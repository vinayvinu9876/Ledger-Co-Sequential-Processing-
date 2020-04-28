#include<bits/stdc++.h>
#include "FileManager.cpp"
#include "MasterRecordManager.cpp"
#include "TransactionManager.cpp"
#include "LedgerGenerator.cpp"

using namespace std;


MasterRecordManager master_record_manager;
TransactionManager transaction_manager;
LedgerGenerator generator;



void handleCreateAccount(){
    map<string,string> details;
    string temp;
    cout<<endl<<"Please Enter Name : "<<endl;
    cin>>temp;
    details.insert(pair<string,string>("name",temp));
    cout<<endl<<"Please Enter Phone : "<<endl;
    cin>>temp;
    details.insert(pair<string,string>("phone",temp));
    cout<<endl<<"Please Enter Email : "<<endl;
    cin>>temp;
    details.insert(pair<string,string>("email",temp));
    bool result = master_record_manager.addAccount(details);
    if(result){
        cout<<endl<<"Account Created Succesfully"<<endl;
        return;
    }
    cout<<endl<<"Account Creation Failed"<<endl;
    
}

void handleAddTransaction(){
    map<string,string> details;
    string temp;
    cout<<endl<<"Please Enter Account Number : "<<endl;
    cin>>temp;
    details.insert(pair<string,string>("account_no",temp));
    cout<<endl<<"Please Enter Check Number : "<<endl;
    cin>>temp;
    details.insert(pair<string,string>("check_number",temp));
    cout<<endl<<"Please Enter date : "<<endl;
    cin>>temp;
    details.insert(pair<string,string>("date",temp));
    cout<<endl<<"Please Enter Description : "<<endl;
    cin>>temp;
    details.insert(pair<string,string>("description",temp));
    cout<<endl<<"Please Enter Debit/Credit(-/+) : "<<endl;
    cin>>temp;
    details.insert(pair<string,string>("debit_credit",temp));
    cout<<"Inserting record"<<endl;
    bool result = transaction_manager.addTransaction(details);
    cout<<"Inserted Record result = "<<result<<endl;
    if(result){
        cout<<endl<<"Transaction Successful"<<endl;
        return;
    }
    cout<<endl<<"Transaction Failed"<<endl;
    
}

void handleDeleteAccount(){
    string account_no;
    cout<<endl<<"Please Enter Account No. to be Deleted :"<<endl;
    cin>>account_no;
    bool result = master_record_manager.removeAccount(account_no);
    if(result){
        cout<<endl<<"Account Deleted Succesfully"<<endl;
        return;
    }
    cout<<endl<<"Account Delete Failed"<<endl;
}

void handleDeleteTransaction(){
    string txn_id;
    cout<<endl<<"Please Enter Transaction Id to be Deleted :"<<endl;
    cin>>txn_id;
    bool result = transaction_manager.removeTransaction(txn_id);
    if(result){
        cout<<endl<<"Transaction Deleted Succesfully"<<endl;
        return;
    }
    cout<<endl<<"Transaction Delete Failed"<<endl;
}

void handleListAccount(){
    list<string> account_list = master_record_manager.getAllAccountDetails();
    cout<<endl<<"Account No | Name | Phone | Email"<<endl;
    for(auto x : account_list)
        cout<<x<<endl;
}

void handleListTransaction(){
    list<string> txn_list = transaction_manager.getAllTxnDetails();
    cout<<endl<<"TXN ID | ACCOUNT_NO | CHECK_NUMBER |  DATE | DESCRIPTION | DEBIT/CREDIT"<<endl;
    for(auto x : txn_list)
        cout<<x<<endl;
}

void handleGenerateLedger(){
    if(generator.generateLedger()){
        cout<<endl<<"Ledger Genereated Succesfully"<<endl;
        return;
    }
    cout<<endl<<"Ledger Generation Unsuccesfull"<<endl;
}

int getSelectedOption(){
    cout<<endl<<"============================="<<endl;
    cout<<"\tMENU"<<endl;
    cout<<"============================="<<endl;
    cout<<"1.Create Account \t 2.Add Transaction"<<endl;
    cout<<"3.Remove Account \t 4.Remove Transaction"<<endl;
    cout<<"5.List Accounts \t 6.List Transaction"<<endl;
    cout<<"7.Generate Ledger \t 8.Exit"<<endl;
    int ch;
    cin>>ch;
    return ch;
}

int main(void){
    int ch;
    do{
        ch = getSelectedOption();
        switch(ch){
            case 1 : handleCreateAccount();break;
            case 2 : handleAddTransaction();break;
            case 3 : handleDeleteAccount();break;
            case 4 : handleDeleteTransaction();break;
            case 5 : handleListAccount();break;
            case 6 : handleListTransaction();break;
            case 7 : handleGenerateLedger();break;
            default : exit(0);break;
        }
    }
    while(ch<8);
    
}