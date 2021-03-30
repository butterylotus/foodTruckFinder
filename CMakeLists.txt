cmake_minimum_required(VERSION 3.17)
project(SFOpenFoodTrucks)

set(CMAKE_CXX_STANDARD 14)

include(FetchContent)
FetchContent_Declare(cpr GIT_REPOSITORY https://github.com/whoshuu/cpr.git GIT_TAG c8d33915dbd88ad6c92b258869b03aba06587ff9) # the commit hash for 1.5.0
FetchContent_MakeAvailable(cpr)

add_executable(SFOpenFoodTrucks main.cpp foodTruckFinder.cpp)
target_link_libraries(SFOpenFoodTrucks PRIVATE cpr::cpr)





