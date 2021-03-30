#include <iostream>
#include <ctype.h>
#include <cpr/cpr.h>
#include <iomanip>
#include <ctime>
#include <stdlib.h> // defines putenv in POSIX

class FoodTruckFinder{
private:
    std::tm* curTime_;
    std::string selectedFields_;
    int pageLimit_;
    int offset_ = 0;
    std::string url_ = "http://data.sfgov.org/resource/bbb8-hzi6.json";
    std::string query_;

    std::string getTimeIn24HourFormat();
    int getDayOfWeek();
public:
    FoodTruckFinder(int pageLimit = 10, const std::vector<std::string>& additionalSelectedFields = {});
    std::string buildQuery(const int& page);
};

class FoodTruckFinderApp{
public:
    FoodTruckFinderApp(){};
    void run();

private:
    FoodTruckFinder ftf_;

    cpr::Response query_api(int page);
    void printResults(const std::string& queryResults, int page);
    void toLowercaseInput(std::string & userInput);
};
