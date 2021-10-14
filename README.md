# Bus-App
A console application built in C++ which is aimed to find bus route and estimated distance and fare based on the data of 2018.

## Platform
Linux (Ubuntu 18.04)

## Creation date
2019

## Language
C++

## Description
This is a console application based on C++ which allows user to find buses in a given starting point and destination point of Dhaka city. The data collected for this console application was as of 2018. Every input output is taken and showed in console window.

## How to run
Go to the path containing the Bus-App folder, open linux command line. After that run by ./main then the application will be shown in the command line as a console application

#### Initial window
In the initial window there are 3 options: register, login and exit. A new user can register and existing user can login

![image](https://user-images.githubusercontent.com/48018036/137321830-6597b729-e3eb-4691-aafa-a1fc6afcd9bb.png)

#### Main Menu
![image](https://user-images.githubusercontent.com/48018036/137324401-9af05b35-4bbb-4aed-b67d-8b21aaaeee2e.png)

After login , the user will be able to see 7 sections. 
1. **Find Bus** : This section allows user to give the starting and end point of the route and the available busses will be shown with estimated fare and distance.![image](https://user-images.githubusercontent.com/48018036/137324514-66276d4b-7554-4078-8311-8d5ed3bb0025.png)

2. **History** : This section shows the previously searched routes
3. **Bus Data** : All the busses covered in this app with the route ![image](https://user-images.githubusercontent.com/48018036/137324469-bc0ff872-2795-4a3d-b207-6c8256f6071a.png)

4. **All places** : All the places covered in this app 
5. **Settings** : Some additional settings regarding password reset and history
6. **About this app** : Notes about the application
7. **Log out** :Logging out 

## FAQ
1. **How to run?**: Go to the path containing the Bus-App folder, open linux command line. After that run by ./main then the application will be shown in the command line as a console application
2. **How can I run in windows?** : The app can be run in the same way in windows using [WSL (windows subsystem for linux)](https://docs.microsoft.com/en-us/windows/wsl/install) 

## Notes
1. Fare data and distance data provided are purely estimated, may not be totally accurate
2. All data are from 2018 so some bus data may come non existent
