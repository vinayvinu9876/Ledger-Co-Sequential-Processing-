#include<bits/stdc++.h> 
#include <iostream>
#include <chrono>
#include <ctime> 
#pragma once

using namespace std;

list<string> splitString(string str,char delimiter){
	
	list<string> values;
	stringstream check1(str);
	string intermediate; 
    // Tokenizing w.r.t. space ' ' 
    while(getline(check1, intermediate, delimiter)) 
    { 
        values.push_back(intermediate); 
    }
	return values;
}

//index starts at 0
string getAtIndex(list<string> values,int index){
    for(int i=0;i<index;i++){
        values.pop_front();
    }
    return values.front();
}

string getCurrentDateAndTime(){
    auto end = std::chrono::system_clock::now();
    time_t end_time = chrono::system_clock::to_time_t(end);
    return ctime(&end_time);
}


bool isDateCorrect(int day,int month,int year){
    if(1000 <= year <= 3000)
       {
         if((month==1 || month==3 || month==5|| month==7|| month==8||month==10||month==12) && day>0 && day<=31)
            return true;
         else 
            if(month==4 || month==6 || month==9|| month==11 && day>0 && day<=30)
                return true;
            else
                if(month==2)
                {
                  if((year%400==0 || (year%100!=0 && year%4==0)) && day>0 && day<=29)
                        return true;
                  else if(day>0 && day<=28)
                        return true;
                  else
                        return false;
               }
         else
               return false;
      }
    else
        return false;
}

bool validDate(string date){
    try{
        list<string> parts = splitString(date,'/');
        int day = stoi(parts.front()); //read day
        parts.pop_front(); //remove day
        int month = stoi(parts.front());
        parts.pop_front();
        int year = stoi(parts.front());
        parts.pop_front();

        return isDateCorrect(day,month,year);
    }
    catch(const char* message){
        cout<<message<<endl;
        return false;
    } 
}
