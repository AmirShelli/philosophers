# philosophers

## Table of Contents
+ [About](#about)
+ [Getting Started](#getting_started)
+ [Usage](#usage)

## About

In this project I use multithreading and mutex to solve the classic Dinning Philosophers problem.

Dining philosophers problem is a problem created by Edsger Wybe Dijkstra in 1965 to explain the deadlock state of an operating system, which is traditionally commonly introduced in lectures on operating systems.

+ _check the subject in `` ./SUB `` for more information about the project_
## Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

This project works only on Linux/MacOS platforms only.

### Installing
To compile the program, you'll have to use your terminal and use the Makefile rules below:

 + ``make`` Generates _philosophers_ and an object file for each .c
 + ``make clean``  Deletes all object files
 + ``make fclean``  Deletes the object files and the _philosophers_
 + ``make re``  makes ``fclean`` and ``make`` again 
