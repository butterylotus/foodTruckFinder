#include "foodTruckFinder.hpp"
#include <ctype.h>
#include <cpr/cpr.h>
#include <iomanip>
#include <ctime>
#include <stdlib.h> // defines putenv in POSIX


FoodTruckFinder::FoodTruckFinder(int pageLimit, const std::vector<std::string>& additionalSelectedFields):
        pageLimit_(pageLimit)
{
    //Get current time in San Francisco, CA
    std::time_t t = std::time(nullptr);
    putenv(const_cast<char *>("TZ=PST8PDT"));//set the correct time zone
    curTime_ = std::localtime(&t);

    //Fill in selectedFields
    std::string select1 = "applicant";
    std::string select2 = "location";
    selectedFields_ = select1 + ',' + select2;
    for(const auto & sf: additionalSelectedFields){
        selectedFields_ += ',';
        selectedFields_ += sf;
    }

    //Note: query_ is currently empty. buildQuery function needs to be called to build SOQL queries
}

std::string FoodTruckFinder::getTimeIn24HourFormat(){
    std::string apos = "'";
    std::string formattedTime;
    auto hour = std::to_string(curTime_->tm_hour) ;
    hour = std::string(2 - hour.length(), '0') + hour;//add leading 0's to hour
    auto min = std::to_string(curTime_->tm_min);
    min = std::string(2 - min.length(), '0') + min;//add leading 0's to min
    formattedTime = apos + hour + ":" + min +apos;

    //For testing purpose
    //formattedTime = apos +"03:10"+apos;
    return formattedTime;//e.g. '14:42'
}

int FoodTruckFinder::getDayOfWeek(){
    return curTime_->tm_wday;//days since Sunday
}

std::string FoodTruckFinder::buildQuery(const int& page){
    std::string time = getTimeIn24HourFormat();
    int dayOfWeek = getDayOfWeek();
    offset_ = page * pageLimit_;
    query_ = url_;
    //select clause
    query_ += "?$select="+selectedFields_;
    //limit
    query_ += "&$limit="+std::to_string(pageLimit_);
    //pagination offset
    query_ += "&$offset="+std::to_string(offset_);
    //order clause: ascending order of applicant
    query_ += "&$order=applicant%20ASC";//NOTE: Need to replace space with %20 to make it work in cpr::Get
    //where clause e.g. where='14:42' between start24 and end24 and dayorder=1

    query_ += "&$where="+time+"%20between%20start24%20and%20end24%20";
    query_ += "and%20dayorder="+std::to_string(dayOfWeek);

    return query_;
}

FoodTruckFinderApp::FoodTruckFinderApp(int pageLimit, const std::vector<std::string>& additionalSelectedFields )
{
    ftf_ = std::make_unique<FoodTruckFinder>(pageLimit, additionalSelectedFields);
}

cpr::Response FoodTruckFinderApp::query_api(int page){//query which page
    return cpr::Get(cpr::Url{ftf_->buildQuery(page)});
}

void FoodTruckFinderApp::printResults(const std::string& queryResults, int page){
    std::cout<<queryResults<<std::endl;
    std::cout<<"----Page "<<page<<"----"<<std::endl;
    std::cout<<std::endl;
}

void FoodTruckFinderApp::toLowercaseInput(std::string & userInput){
    for(auto &c: userInput){//allow mixed cases e.g Prev or P
        c = tolower(c);
    }
}

void FoodTruckFinderApp::run(){
    int page = 0;
    cpr::Response response = query_api(page);

    while(true){
        if(response.status_code==200){//OK
            std::string userInput;

            if(response.text.size()<=3){//empty result: "[]\n"
                if(page==0){//no results
                    std::cout<<"There is no food truck available at this time. Please check back later."<<std::endl;
                    break;
                }
                else {//no more results
                    std::cout<<"You've reached the end. Please choose where to go (prev/exit or p/e) : "<<std::endl;
                    std::cin>>userInput;
                    toLowercaseInput(userInput);

                    while(userInput!="prev" && userInput!="p" && userInput!="exit" && userInput!="e"){
                        std::cout<<"Invalid input!"<<std::endl;
                        std::cout<<"You've reached the end. Please choose where to go (prev/exit or p/e) :"<<std::endl;
                        std::cin>>userInput;
                        toLowercaseInput(userInput);
                    }
                    if(userInput=="prev"||userInput=="p"){//in this case, page is not 0
                        response = query_api(--page);
                        continue;
                    }else {//if(userInput=="exit"||userInput=="e")
                        break;
                    }
                }
            }

            printResults(response.text, page+1);

            std::cout<<"Please choose where to go (prev/next/exit or p/n/e) :"<<std::endl;
            std::cin>>userInput;
            toLowercaseInput(userInput);

            while(userInput!="prev" && userInput!="p" && userInput!="exit" && userInput!="e" && userInput!="next"&& userInput!="n"){
                std::cout<<"Invalid input!"<<std::endl;
                std::cout<<"Please choose where to go (prev/next/exit or p/n/e) :"<<std::endl;
                std::cin>>userInput;
                toLowercaseInput(userInput);
            }
            if(userInput=="prev"||userInput=="p"){
                if(page==0){
                    std::cout<<"You've already reached the first page. There is no previous page."<<std::endl;
                    std::cout<<"Please choose where to go (next/exit or n/e) :"<<std::endl;
                    std::cin>>userInput;
                    toLowercaseInput(userInput);

                    while(userInput!="exit" && userInput!="e" && userInput!="next"&& userInput!="n"){
                        std::cout<<"Invalid input!"<<std::endl;
                        std::cout<<"Please choose where to go (next/exit or n/e) :"<<std::endl;
                        std::cin>>userInput;
                        toLowercaseInput(userInput);
                    }
                }else
                    response = query_api(--page);
            }

            if(userInput=="next"||userInput=="n"){
                response = query_api(++page);
            }

            if(userInput=="exit"||userInput=="e"){
                break;
            }
        }
    }
    std::cout<<"Thank you for using the food truck finder! Have a good day!"<<std::endl;
}

