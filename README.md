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
You can enter "prev" or "p" to page up, "next" or "n" to page down, "exit" or "e" to exit the program.
![image](https://user-images.githubusercontent.com/81490599/113224661-e8c68100-9259-11eb-86a0-6980004f4b03.png)
![image](https://user-images.githubusercontent.com/81490599/113224936-7f933d80-925a-11eb-80e2-cd6be112dbea.png)
![image](https://user-images.githubusercontent.com/81490599/113224857-54a8e980-925a-11eb-9d40-569fe6bf0440.png)

- If you reached the end, you can only enter "prev" or "p" to page up, "exit" or "e" to exit the program.
![image](https://user-images.githubusercontent.com/81490599/113229695-7bb8e880-9265-11eb-87be-fe7136ac618e.png)

- If you check during non business hours, you will see a note:
![image](https://user-images.githubusercontent.com/81490599/113229883-d5211780-9265-11eb-8b12-89a9adb8696f.png)


## How to convert it to a fully featured web application using the data provided by the Socrata API capable of serving millions of concurrent users?
This command line proof-of-concept program did not use an application token, so it is subject to a throttling limit. We need to obtain an application token to be able to serve more people. Also I noticed that the response time is relatively long (in seconds) from the Socrata API. This is too slow for multiple queries in a paginated API. We need to use caching to take care of request spikes. We can achieve that by setting cache control headers provided by the Socrata API. When a large amount of simultaneous requests come to our webservice, we will check if the request query is already in cache. If yes, then we just retrieve the results from the cache without sending the request to the Socrata API. If not, then we make the request to the Socrata API and cache the results.

Currently with a developer application token, there is no throttling, but to serve millions of users it is better to have our own database. The dataset in this use case is structured, so we can choose to use MySQL database. We could have multiple webservers and each user could be directed to one of them through a load balancer. Each web server could pass a batch of user requests to one of the read APIs through a load balancer. Each read API will look up its cache(we can use a LRU in memory cache such as Redis) first to determine whether to query the database and we could have multiple Redis replicas (use a cluster mode disabled Redis cluster) to speed up lookup. We could use a write API to periodically poll the Socrata API for an update to the dataset in our database. 

And to have a fully featured web application, we need some static contents for the web pages and they can be stored in a CDN.
