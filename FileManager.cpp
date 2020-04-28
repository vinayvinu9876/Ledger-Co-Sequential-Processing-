#include<bits/stdc++.h> 
#pragma once

using namespace std;

class FileManager{
    string filepath;
public:
    FileManager(string filename);
    list<string> getFileContent(); 
    bool addListToFile(list<string> to_add_list);
    bool addLineToFile(string line);
    bool removeLine(string line);
};

FileManager::FileManager(string filename){
    this->filepath = filename;
}

list<string> FileManager::getFileContent(){
    list<string> content;
    string line;
    try{
        ifstream file(filepath,ios::app);
        while(!file.eof()){
            getline(file,line);
            if(!(line.empty()))
                content.push_back(line);
        }
        file.close();
        return content;
    }
    catch(const char* message){
        cout<<"Error : "<<message<<endl;
        return content;
    }
}

bool FileManager::addListToFile(list<string> to_add_list){
    try{
        fstream file(filepath,ios::app);
        if(!file) throw runtime_error("Unable to Open File "+filepath);
        for(auto x : to_add_list){
            file << x << endl;
        }
        file.close();
    }
    catch(const char* message){
        cout<<message<<endl;
        return false;
    }
    return true;
}

bool FileManager::addLineToFile(string line){
    try{
        fstream file(filepath,ios::app);
        if(!file) throw runtime_error("Unable to Open File "+filepath);
        file<<line<<endl;
        file.close();
        return true;
    }
    catch(const char* message){
        cout<<message<<endl;
        return false;
    }
}

bool FileManager::removeLine(string line){
    try{
        ifstream file(filepath,ios::app);
        fstream tempfile("tmp.txt",ios::app);
        if(!file) throw runtime_error("Unable to Open File "+filepath);
        string fileline = "";
        while(!file.eof()){
            getline(file,fileline);
            if(!(fileline.empty()) && (line!=fileline))
                tempfile << fileline <<endl;
        }
        file.close();
        tempfile.close();
        remove(filepath.c_str());
        rename("tmp.txt",filepath.c_str());
        return true;
    }
    catch(const char* message){
        cout<<message<<endl;
        return false;
    }
}
