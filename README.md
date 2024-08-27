README

Shiven S. Patel
Purdue University

Repository Includes:
- Source Code File (SSP_FC.c)
- Sample Input File (passengers.txt)
- Sample Exported Seating Chart (seating_chart.txt)
- Final Report
- README.md

Additional materials related to the project, including a narrated video demo and slides are available upon request.

This project contains four functions outside of the standard main() function. 

The first function is createUser(), which takes in a host of values pertaining to a passenger and creates a new dynamically allocated instance of the Passenger data type. It then assigns all of the relevant variables to the newly created Passenger. This function is called by the importUsers() function.

The caclulatePriority() function takes in a Passenger data type and calculates a priority score, which is then set on the corresponding structure variable. This function is called by the importUsers() function.

The importUsers() function reads the passengers.txt file line-by-line and creates a new Passenger struct for each using the createUser() function and calculates the priority using the calculatePriority() function. It then assigns each passenger to an array. Once all of the passengers have been imported, it performs an insertion sort and sorts all of the passengers by their priority score.

The fclose() function exports the sorted array into a nice easy-to-read txt file.