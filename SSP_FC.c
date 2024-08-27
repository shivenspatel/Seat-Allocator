#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define B_ROWS 30
#define B_COLS 6
#define TOT_PASS 180

typedef struct Passenger {
    char firstName[50];
    char lastName[50];
    int passengerID;
    int over65; //5 for yes, 0 for no
    int rewardsTier; //1-5, bronze to diamond
    int milStatus; //0 for none, 3 for veterans, 5 for active duty
    int cabinClass; //1 - Basic Economy, 3 - Economy, 5 - Economy Plus
    double priority;
} Passenger;

Passenger* createUser(char firstName[50], char lastName[50], int over65, int rewardsTier, int milStatus, int cabinClass, int passengerID) {
    Passenger* new = (Passenger*) malloc(sizeof(Passenger));

    strcpy(new->firstName, firstName);
    strcpy(new->lastName, lastName);
    new->over65 = over65;
    new->rewardsTier = rewardsTier;
    new->milStatus = milStatus;
    new->cabinClass = cabinClass;
    new->priority = 0.0;
    new->passengerID = passengerID;

    return(new);
}

void calculatePriority(Passenger *subject) {
    double priority = 0.0;

    priority += (subject->milStatus * 0.20); //military status is 20% of the formula
    priority += (subject->rewardsTier * 0.25); //rewards tier is 25% of the formula
    priority += (subject->cabinClass * 0.40); //cabin class is 40% of the formula
    priority += (subject->over65 * 0.15); //senior citizen status is 15% of the formula

    subject->priority = priority;
}

void importUsers(Passenger **map, int totalPassengers) {
    int counter = 0;
    Passenger *flatMap[totalPassengers];

    FILE *cabin;

    cabin = fopen("passengers.txt", "r");
    char new[121];

    while(fgets(new, 120, cabin) != NULL) {
        char fN[50];
        char lN[50];
        char *c_o65;
        char *c_rT;
        char *c_mS;
        char *c_cT;

        int o65;
        int rT;
        int mS;
        int cT;

        char *token;

        token = strtok(new, ", ");
        strcpy(fN, token);
        token = strtok(NULL, ", ");
        strcpy(lN, token);
        token = strtok(NULL, ", ");
        c_o65 = token;
        o65 = atoi(c_o65);
        token = strtok(NULL, ", ");
        c_rT = token;
        rT = atoi(c_rT);
        token = strtok(NULL, ", ");
        c_mS = token;
        mS = atoi(c_mS);
        token = strtok(NULL, "\n");
        c_cT = token;
        cT = atoi(c_cT);
	
        Passenger *new = createUser(fN, lN, o65, rT, mS, cT, (counter + 1));
        calculatePriority(new);

		flatMap[counter] = new;

        counter++;
	}

    //Insertion Sort:
    for (int i = 1; i < totalPassengers; i++) {
        Passenger *p = flatMap[i];
        int j = i - 1;

        while (j >= 0 && flatMap[j]->priority < p->priority) {
            flatMap[j + 1] = flatMap[j];
            j = j - 1;
        }
        flatMap[j + 1] = p;
    }

    for (int i = 0; i < totalPassengers; i++) {
        map[i] = flatMap[i];
    }

    fclose(cabin);
}

void createChart(Passenger **map, int size, int rows, int rowSize) {
    int counter = 0;

    FILE *seatingChart;
    seatingChart = fopen("seating_chart.txt", "w");

    if ((rows * rowSize) != size) {
        return;
    }

    for(int i = 0; i < rows; i++) {
        fprintf(seatingChart, "Row %d:\n", (i + 1));
        char seats[26] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        for(int j = 0; j < rowSize; j++) {
            fprintf(seatingChart, "    Seat %d%c: %s, %s (ID: %d)\n", (i+1), seats[j], map[counter]->lastName, map[counter]->firstName, map[counter]->passengerID);
            counter++;
        }
    }
}

int main() {
    int option;
    int size;
    int rows;
    int rowSize;

    printf("Please enter the aircraft model (1 for 7M8, 2 for A321neo): ");
    scanf("%d", &option);

    if (option == 1) {
        size = 180;
        rows = 30;
        rowSize = 6;
        printf("Chosen aircraft is the Boeing 737 MAX 8.\n");
    }
    else if (option == 2) {
        size = 180;
        rows = 30;
        rowSize = 6;
        printf("Chosen aircraft is the Airbus A321neo.\n");
    }
    else {
        return 0;
    }
    
    Passenger *cabin[size];

    importUsers(cabin, size);

    createChart(cabin, size, rows, rowSize);
    return 0;
}