# Okami AYCE Booking Management System

## 1\. Description

This program is written in C to simulate as restaurant booking management system.  
Shout out to Okami Japanese Restaurant Pennant Hills.

\

## 2\. Main Features

* Add booking
* Search booking by:

  * ID
  * Customer name
  * Table number
  * Time
  * Date
  * Number of customers (pax)
* Update booking
* Delete booking by ID
* Display all bookings
* Sort bookings by:

  * ID
  * Time
  * Number of customers
* Save data to file
* Load data from file
* Data cleaning:

  * Remove invalid bookings
  * Remove duplicate IDs
  * Remove time conflicts

\

## 3\. Data Structure

Each booking includes:

* ID: char, exactly 5 characters
* Table number: int (1 – 100)
* Day: int
* Month: int
* Year: int (26 – 99)
* Hour: int (9 – 21)
* Minute: int (0 – 59)
* Number of customers: int (1 – 6)
* Customer name: char, maximum 50 characters

\

## 4\. Program Structure

|File|Purpose|
|-|-|
|main.c|Controls program flow, menu, and input|
|booking.h|Struct definitions and function prototypes|
|booking.c|Implementation of booking operations|

\

## 5\. Data File Format

Data is stored in plain text. Each line represents one booking with the format:

ID table year month day hour minute pax name

Example:
00001 5 26 3 17 18 30 4 Nguyen Van A

\

## 6\. Rules

* Booking time must be between 09:00 and 21:00
* Maximum 6 customers per table
* A table cannot be booked if:

  * It is on the same date, and
  * The time difference is less than 180 minutes
* Date must be valid (including leap year handling)
* Booking ID is automatically generated and incremented

\

## 7\. Notes

* Compile the program using:

  * gcc main.c booking.c -Wall -Wextra -o main
  * Then run the executable to start the program.
* The program automatically loads "default.txt" at startup.
* When searching by name, approximate matching (substring) is supported.  
Users should enter at least 2 characters to avoid excessive results.
* Data can be cleaned using the “Clean booking” function.
* Sample data files:

  * default.txt: Default dataset loaded automatically
  * input.txt: Standard dataset
  * full.txt: All tables fully booked on the same day
  * dirty.txt: Contains invalid data (duplicate ID, time conflicts, exceeding pax, etc.)
* When entering a filename for saving/exporting, include the full filename with the .txt extension.
