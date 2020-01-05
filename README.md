# Flight-Simulator

# Programing Project - 1st Mile Stone
# Flight Simulator 2020

[Link to project's repository](https://github.com/ofekbr/Flight-Simulator)

An Interpenter coded in C++ for FlightGear's Flight Simulator

# WHAT IS IT ABOUT ?

Our project connects to a flight simulator and sends it commands that make an airplain fly.

# HOW DOES IT WORK ?

We simulate communication between server and client as both parties are programmed by us.
We send commands to the server while running another thread that reads the information from the server.
At first we intrerprate the text from the simulatir to commands and act accordingly to its demands.
This communication between both sides yields wonderful flight results so the clients is satisfied.

# HOW CAN I USE IT ?

In order to use our program you need to work on a linux operating System in your computer and download the
Flight Simulator gui.Compile the code with the following line :g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread. And run it with : ./a.out file_name.
After you run our code you may push the button "fly" in the simulator and wait for the communication between
the client and server.

# WORKSPACE

Our project designed on a Linux operating system in C++ language.

# TEAM

NAME: Shani Berdah
ID: 20569426

NAME: Ofek Barkai
ID:316079532
