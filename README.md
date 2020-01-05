# Flight-Simulator

# Programing Project - 1st Mile Stone
# Flight Simulator 2020

[Link to project's repository](https://github.com/ofekbr/Flight-Simulator)

An Interpreter coded in C++ for FlightGear's Flight Simulator

# Project description?
In this program, we created an interpreter for running the flight gear simulator. Upon receiving a text files with commands, we will want to interpret it. We created a set of commands that are being executed by the interpreter with the given parameters. The interpreter is both client and server for the simulator - it receives data from the simulator and updates its own information, and also sends data to the simulator and updates it's state.

# HOW DOES IT WORK ?
We simulate communication between server and client as both parts are programmed by us.
We send commands to the server while running another thread that reads the information from the server.
At first we intrerprate the text from the simulator to commands and act accordingly to its demands.
This communication between both sides yields wonderful flight results so the clients is satisfied.

# WORKSPACE
Our project designed on a Linux operating system in C++ language.

# HOW CAN I USE IT ?
In order to use our program you need to work on a linux operating System in your computer and download the
Flight Simulator gui.
Link to download Flightgear-
https://www.flightgear.org/download/main-program/
Then, in the FlightGear in the additional settings section write the following lines:
--telnet=socket,in,10,127.0.0.1,5402,tcp
--generic=socket,out,10,127.0.0.1,5400,tcp,generic_small
In addition, create a .txt file with a set of commands for the interpreter. Also create a xml file of the data the simulator will send and put it in the protocol folder of the simulator.
Compile the code with the following line :g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread. And run it with : ./a.out file_name.
After you run our code you may push the button "fly" in the simulator and wait for the communication between
the client and server.


# TEAM
NAME: Shani Berdah
ID: 20569426

NAME: Ofek Barkai
ID:316079532
