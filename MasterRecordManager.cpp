#include<bits/stdc++.h> 
#include "FileManager.cpp"
#include "utilityFunctions.cpp"
#pragma once

using namespace std;

class MasterRecordManager{
    string filename = "masterrecord.txt";
public:
    bool addAccount(map<string,string> details);
    bool removeAccount(string account_no);
    bool checkAccountExists(string account_no);
    list<string> getAllAccountDetails();
private:
    string getNewAccountNo();
};

bool MasterRecordManager::addAccount(map<string,string> details){
    string new_account_no = getNewAccountNo();
    string details_line = "";
    try{
        if(new_account_no=="-1") throw runtime_error("ERROR Generating Account No.");
        FileManager fm(filename);
        details_line = details_line + new_account_no + "|" + details["name"] + "|" + details["phone"] + "|" + details["email"]; 
        return fm.addLineToFile(details_line); 
    }
    catch(const char* message){
        cout<<message<<endl;
        return false;
    }
}

string MasterRecordManager::getNewAccountNo(){
    try{
        FileManager fm(filename);
        list<string> result = fm.getFileContent();
        if(result.size()==0) return "1" ;
        
        string last_record = result.back();

        string last_account_no = splitString(last_record,'|').front(); //get only key
        string new_account_no = to_string(stoi(last_account_no)+1);
        return new_account_no;
    }
    catch(const char* message){
        cout<<message<<endl;
        return "-1";
    }
}

bool MasterRecordManager::removeAccount(string account_no){
    try{
        FileManager fm(filename);
        list<string> content = fm.getFileContent();
        for(auto line : content){
            string key = splitString(line,'|').front();
            if(key==account_no)
                return fm.removeLine(line);
        }
        throw runtime_error("No Records Found");
    }
    catch(const char* message){
        cout<<message<<endl;
        return false;
    }
}

bool MasterRecordManager::checkAccountExists(string account_no){
    try{
        FileManager fm(filename);
        list<string> content = fm.getFileContent();
        if(content.size()==0) throw runtime_error("NO records found");
        for(auto line : content){
            string key = splitString(line,'|').front();
            if(key==account_no)
                return true;
        }
        return false;
    }
    catch(const char* message){
        cout<<message<<endl;
        return false;
    }
}

list<string> MasterRecordManager::getAllAccountDetails(){
    FileManager fm(filename);
    return fm.getFileContent();
}
