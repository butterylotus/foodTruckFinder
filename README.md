# San Francisco Open Food Trucks
A C++ command line program that prints out a list (10 at a time) of food trucks that are open at the current date and current time, when the program is being run.

This program uses The San Francisco Data API that can be found [here](https://dev.socrata.com/foundry/data.sfgov.org/bbb8-hzi6).


## Instructions to build the binary SFFoodTruck
On Linux:

This is a CMake project. It depends on the [C++ Requests](https://github.com/whoshuu/cpr) library to send SOQL queries and get results from the SOCRATA API. [Here](https://www.jetbrains.com/help/clion/quick-cmake-tutorial.html#lib-targets) are the directions to build a CMake project. The most convenient way is to use an IDE such as CLion to build the CMakeLists.txt. 
- Git clone this repository
- Install CLion
- Open CLion and select File->Open, type the path of foodTruckFinder folder, and click OK.
- You will see a cmake-build-debug folder getting created in the foodTruckFinder directory. 
- Click the Build button in CLion![image](https://user-images.githubusercontent.com/81490599/113206102-0a653f80-923d-11eb-9027-5959ed943d56.png)
- You will see a binary file called SFFoodTruck getting created in the cmake-build-debug folder along with all the build cpr(C++ Rquests library) objects.


## Execute the program
- Click the Run button in CLion![image](https://user-images.githubusercontent.com/81490599/113208219-88c2e100-923f-11eb-920d-3c2be9032833.png) to run the program.
You can enter "prev" or "p" to page up, "next" or "n" to page down, and "exit" or "e" to exit the program.
![image](https://user-images.githubusercontent.com/81490599/113224661-e8c68100-9259-11eb-86a0-6980004f4b03.png)
![image](https://user-images.githubusercontent.com/81490599/113224936-7f933d80-925a-11eb-80e2-cd6be112dbea.png)
![image](https://user-images.githubusercontent.com/81490599/113224857-54a8e980-925a-11eb-9d40-569fe6bf0440.png)
