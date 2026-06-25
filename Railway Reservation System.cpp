#include <iostream>
#include <string>
using namespace std;

const int MAX_PASSENGERS = 100;
const int MAX_TRAINS = 10;

struct Train {
    string name;
    string route;
    int seats;
};

struct Passenger {
    string name;
    string CNIC;
    string contactNumber;
    int trainIndex; // index in trains array
    int seatNumber;
};

// Train Data
Train train[MAX_TRAINS];
int numOfTrain = 3;

// Passenger Data
Passenger passenger[MAX_PASSENGERS];
int numOfPassenger = 0;

// Function Prototypes
void createTrain();
void readTrain();
void updateTrain();
void deleteTrain();
void createPassenger();
void readPassenger();
void updatePassenger();
void deletePassenger();
void mainMenu();

int main() {
    // Initialize with some trains
    train[0] = {"Green Line", "Chaklala-Lahore", 90};
    train[1] = {"Red line", "Lahore-Karachi", 90};
    train[2] = {"Yellow line", "Rawalpindi-Faisalabad", 95};
    mainMenu();
    return 0;
}

// ------------------- TRAIN CRUD -------------------

void createTrain() {
    if (numOfTrain >= MAX_TRAINS) {
        cout << "Train limit reached.\n";
        return;
    }
    cin.ignore();
    cout << "Enter train name: ";
    getline(cin, train[numOfTrain].name);
    cout << "Enter route: ";
    getline(cin, train[numOfTrain].route);
    cout << "Enter number of seats: ";
    cin >> train[numOfTrain].seats;
    numOfTrain++;
    cout << "Train added successfully!\n";
}

void readTrain() {
    if (numOfTrain == 0) {
        cout << "No trains available.\n";
        return;
    }
    cout << "\nAvailable Trains:\n";
    cout << "No.\tTrain Name\t\tRoute\t\t\tSeats Available\n";
    for (int i = 0; i < numOfTrain; i++) {
        cout << (i + 1) << "\t" << train[i].name << "\t\t" << train[i].route << "\t\t" << train[i].seats << endl;
    }
}

void updateTrain() {
    readTrain();
    cout << "Enter train number to update: ";
    int index;
    cin >> index;
    if (index < 1 || index > numOfTrain) {
        cout << "Invalid train selection.\n";
        return;
    }
    index--;
    cin.ignore();
    cout << "Enter new train name (current: " << train[index].name << "): ";
    getline(cin, train[index].name);
    cout << "Enter new route (current: " << train[index].route << "): ";
    getline(cin, train[index].route);
    cout << "Enter new number of seats (current: " << train[index].seats << "): ";
    cin >> train[index].seats;
    cout << "Train updated successfully!\n";
}

void deleteTrain() {
    readTrain();
    cout << "Enter train number to delete: ";
    int index;
    cin >> index;
    if (index < 1 || index > numOfTrain) {
        cout << "Invalid train selection.\n";
        return;
    }
    index--;
    // Shift trains left
    for (int i = index; i < numOfTrain - 1; i++) {
        train[i] = train[i + 1];
    }
    numOfTrain--;
    cout << "Train deleted successfully!\n";
}

// ------------------- PASSENGER CRUD -------------------

void createPassenger() {
    if (numOfPassenger >= MAX_PASSENGERS) {
        cout << "Booking limit reached.\n";
        return;
    }
    readTrain();
    cout << "Enter train number to book: ";
    int trainChoice;
    cin >> trainChoice;
    if (trainChoice < 1 || trainChoice > numOfTrain) {
        cout << "Invalid train selection.\n";
        return;
    }
    int trainindex = trainChoice - 1;
    if (train[trainindex].seats <= 0) {
        cout << "No seats available on this train.\n";
        return;
    }
    cin.ignore();
    cout << "Enter passenger name: ";
    getline(cin, passenger[numOfPassenger].name);
    cout << "Enter passenger CNIC: ";
    getline(cin, passenger[numOfPassenger].CNIC);
    cout << "Enter passenger contact number: ";
    getline(cin, passenger[numOfPassenger].contactNumber);
    passenger[numOfPassenger].trainIndex = trainindex;
    passenger[numOfPassenger].seatNumber = train[trainindex].seats;
    train[trainindex].seats--;
    cout << "Booking confirmed! Seat number: " << passenger[numOfPassenger].seatNumber
         << " on " << train[trainindex].name << " (" << train[trainindex].route << ")\n";
    numOfPassenger++;
}

void readPassenger() {
    if (numOfPassenger == 0) {
        cout << "No passengers booked yet.\n";
        return;
    }
    cout << "\nPassenger List:\n";
    cout << "No.\tName\t\tCNIC\t\tTrain\t\tSeat\n";
    for (int i = 0; i < numOfPassenger; i++) {
        cout << (i + 1) << "\t" << passenger[i].name << "\t" << passenger[i].CNIC << "\t"<< passenger[i].contactNumber << "\t"
             << train[passenger[i].trainIndex].name << "\t" << passenger[i].seatNumber << endl;
    }
}

void updatePassenger() {
    readPassenger();
    cout << "Enter passenger number to update: ";
    int index;
    cin >> index;
    if (index < 1 || index > numOfPassenger) {
        cout << "Invalid passenger selection.\n";
        return;
    }
    index--;
    cin.ignore();
    cout << "Enter new name (current: " << passenger[index].name << "): ";
    getline(cin, passenger[index].name);
    cout << "Enter new CNIC (current: " << passenger[index].CNIC << "): ";
    getline(cin, passenger[index].CNIC);
    cout << "Enter new contact number (current: " << passenger[index].contactNumber << "): ";
    getline(cin, passenger[index].CNIC);
    cout << "Change train? (y/n): ";
    char ch;
    cin >> ch;
    if (ch == 'y' || ch == 'Y') {
        readTrain();
        cout << "Enter new train number: ";
        int newTrain;
        cin >> newTrain;
        if (newTrain < 1 || newTrain > numOfTrain) {
            cout << "Invalid train selection.\n";
            return;
        }
        int newTrainIndex = newTrain - 1;
        if (train[newTrainIndex].seats <= 0) {
            cout << "No seats available on this train.\n";
            return;
        }
        // Free up seat on old train
        train[passenger[index].trainIndex].seats++;
        // Assign seat on new train
        passenger[index].trainIndex = newTrainIndex;
        passenger[index].seatNumber = train[newTrainIndex].seats;
        train[newTrainIndex].seats--;
        cout << "Train changed successfully. New seat: " << passenger[index].seatNumber << "\n";
    }
    cout << "Passenger updated successfully!\n";
}

void deletePassenger() {
    readPassenger();
    cout << "Enter passenger number to delete: ";
    int index;
    cin >> index;
    if (index < 1 || index > numOfPassenger) {
        cout << "Invalid passenger selection.\n";
        return;
    }
    index--;
    train[passenger[index].trainIndex].seats++;
    cout << "Booking for " << passenger[index].name << " (Seat " << passenger[index].seatNumber
         << " on " << train[passenger[index].trainIndex].name << ") cancelled.\n";
    for (int i = index; i < numOfPassenger - 1; i++) {
        passenger[i] = passenger[i + 1];
    }
    numOfPassenger--;
}

// ------------------- MAIN MENU -------------------
void mainMenu() {
    int choice;
    do {
        cout << "\n--- Railway Reservation System (Full CRUD) ---\n";
        cout << "1. Add Train (Create)\n";
        cout << "2. Display Trains (Read)\n";
        cout << "3. Update Train (Update)\n";
        cout << "4. Delete Train (Delete)\n";
        cout << "5. Book Ticket (Create Passenger)\n";
        cout << "6. Display Passengers (Read)\n";
        cout << "7. Update Passenger (Update)\n";
        cout << "8. Cancel Ticket (Delete Passenger)\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: createTrain(); break;
            case 2: readTrain(); break;
            case 3: updateTrain(); break;
            case 4: deleteTrain(); break;
            case 5: createPassenger(); break;
            case 6: readPassenger(); break;
            case 7: updatePassenger(); break;
            case 8: deletePassenger(); break;
            case 9: cout << "Exiting system. Goodbye!\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 9);
}