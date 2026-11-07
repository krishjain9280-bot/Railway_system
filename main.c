
#include <stdio.h>
#include <string.h>

#define N 5
#define MAX 100

struct Train {
    int trainNo, 
    totalSeats, 
    availableSeats;
    char name[30], 
    source[30], 
    destination[30];
};

struct Ticket {
    int ticketId, 
    trainNo, 
    age, 
    seats, 
    active;
    char passengerName[30];
};

struct Train trains[N] = {
    {101,100,100,"Rajdhani","Delhi","Jaipur"},
    {102,80,80,"Shatabdi","Jaipur","Delhi"},
    {103,120,120,"Duronto","Mumbai","Delhi"},
    {104,90,90,"Express","Jaipur","Mumbai"},
    {105,70,70,"GaribRath","Delhi","Mumbai"}
};

struct Ticket tickets[MAX];
int ticketCount = 0, 
nextId = 1;

int findTrain(int no) {
    for (int i = 0; i < N; i++)
        if (trains[i].trainNo == no)
            return i;
    return -1;
}

// MODULE 1: TRAIN DETAILS

void trainDetails() {
    for (int i = 0; i < N; i++) {
        printf("\n%d %s | %s to %s", trains[i].trainNo,
        trains[i].name, trains[i].source, trains[i].destination);
        printf("\nTotal: %d Available: %d\n",
        trains[i].totalSeats, trains[i].availableSeats);
    }
}

void searchTrain() {
    int no, i;
    printf("Enter Train Number: ");
    scanf("%d", &no);

    i = findTrain(no);
    if (i == -1)
        printf("Train Not Found!\n");
    else
        printf("%s %s to %s\nAvailable Seats: %d\n",
        trains[i].name, trains[i].source,
        trains[i].destination, trains[i].availableSeats);
}

// MODULE 2: TICKET BOOKING

void bookTicket() {
    int no, i, age, seats;

    if (ticketCount == MAX) {
        printf("Booking Limit Reached!\n");
        return;
    }

    printf("Enter Train Number: ");
    scanf("%d", &no);
    i = findTrain(no);

    if (i == -1) {
        printf("Train Not Found!\n");
        return;
    }

    printf("Passenger Name: ");
    scanf("%29s", tickets[ticketCount].passengerName);

    printf("Enter Age and Seats: ");
    scanf("%d%d", &age, &seats);

    if (age <= 0 || seats <= 0) {
        printf("Invalid Details!\n");
        return;
    }

    if (seats > trains[i].availableSeats) {
        printf("Seats Not Available!\n");
        return;
    }

    tickets[ticketCount].ticketId = nextId;
    tickets[ticketCount].trainNo = no;
    tickets[ticketCount].age = age;
    tickets[ticketCount].seats = seats;
    tickets[ticketCount].active = 1;

    trains[i].availableSeats -= seats;

    printf("Ticket Booked! ID: %d\n", nextId);
    nextId++;
    ticketCount++;
}

// MODULE 3: SEARCH AND CANCELLATION

void searchTicket() {
    int id, found = 0;
    printf("Enter Ticket ID: ");
    scanf("%d", &id);

    for (int i = 0; i < ticketCount; i++) {
        if (tickets[i].ticketId == id && tickets[i].active == 1) {
            printf("\nID: %d\nName: %s\nTrain: %d\nAge: %d\nSeats: %d\n",
            tickets[i].ticketId, tickets[i].passengerName,
            tickets[i].trainNo, tickets[i].age, tickets[i].seats);
            found = 1;
            break;
        }
    }

    if (found == 0)
        printf("Ticket Not Found!\n");
}

void cancelTicket() {
    int id, i, j;
    printf("Enter Ticket ID: ");
    scanf("%d", &id);

    for (i = 0; i < ticketCount; i++) {
        if (tickets[i].ticketId == id && tickets[i].active == 1) {
            j = findTrain(tickets[i].trainNo);
            trains[j].availableSeats += tickets[i].seats;
            tickets[i].active = 0;
            printf("Ticket Cancelled!\n");
            return;
        }
    }

    printf("Ticket Not Found!\n");
}

// MODULE 4: SORTING AND REPORT

void sortTrains() {
    struct Train temp;

    for (int i = 0; i < N-1; i++) {
        for (int j = 0; j < N-i-1; j++) {
            if (trains[j].trainNo > trains[j+1].trainNo) {
                temp = trains[j];
                trains[j] = trains[j+1];
                trains[j+1] = temp;
            }
        }
    }

    printf("Trains Sorted!\n");
    trainDetails();
}

void bookingReport() {
    int count = 0;

    for (int i = 0; i < ticketCount; i++) {
        if (tickets[i].active == 1) {
            printf("\nID: %d Name: %s Train: %d Seats: %d\n",
            tickets[i].ticketId, tickets[i].passengerName,
            tickets[i].trainNo, tickets[i].seats);
            count++;
        }
    }

    printf("Total Active Bookings: %d\n", count);
}

// MAIN FUNCTION

int main() {
    int choice;

    do {
        printf("\n--- RAILWAY RESERVATION SYSTEM ---");
        printf("\n1. Train Details\n2. Search Train");
        printf("\n3. Book Ticket\n4. Search Ticket");
        printf("\n5. Cancel Ticket\n6. Sort Trains");
        printf("\n7. Booking Report\n8. Exit");
        printf("\nEnter Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: trainDetails(); break;
            case 2: searchTrain(); break;
            case 3: bookTicket(); break;
            case 4: searchTicket(); break;
            case 5: cancelTicket(); break;
            case 6: sortTrains(); break;
            case 7: bookingReport(); break;
            case 8: printf("Thank You!\n"); break;
            default: printf("Invalid Choice!\n");
        }
    } while (choice != 8);

    return 0;
}
