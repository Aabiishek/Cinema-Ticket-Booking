#include <stdio.h>
#include <stdlib.h>

// Structure for Seat
typedef struct Seat {
	int seatNumber;
	int status; // 0 for available, 1 for booked
	struct Seat *left;
	struct Seat *right;
} Seat;

// Function to create a new seat node
Seat* createSeat(int seatNumber) {
	Seat* newSeat = (Seat*)malloc(sizeof(Seat));
	newSeat->seatNumber = seatNumber;
	newSeat->status = 0; // Seat is initially available
	newSeat->left = NULL;
	newSeat->right = NULL;
	return newSeat;
}

// Insert a new seat into the binary tree
Seat* insertSeat(Seat* root, int seatNumber) {
	if (root == NULL) {
		return createSeat(seatNumber);
	}
	if (seatNumber < root->seatNumber) {
		root->left = insertSeat(root->left, seatNumber);
	} else if (seatNumber > root->seatNumber) {
		root->right = insertSeat(root->right, seatNumber);
	}
	return root;
}

// Find a seat by seat number in the binary tree
Seat* findSeat(Seat* root, int seatNumber) {
	if (root == NULL || root->seatNumber == seatNumber) {
		return root;
	}
	if (seatNumber < root->seatNumber) {
		return findSeat(root->left, seatNumber);
	}
	return findSeat(root->right, seatNumber);
}

// Book a seat if it is available
void bookSeat(Seat* root, int seatNumber) {
	Seat* seat = findSeat(root, seatNumber);
	if (seat != NULL) {
		if (seat->status == 0) {
			seat->status = 1;
			printf("Seat %d successfully booked.\n", seatNumber);
		} else {
			printf("Seat %d is already booked.\n", seatNumber);
		}
	} else {
		printf("Seat %d not found.\n", seatNumber);
	}
}

// Cancel a booking if the seat is booked
void cancelBooking(Seat* root, int seatNumber) {
	Seat* seat = findSeat(root, seatNumber);
	if (seat != NULL) {
		if (seat->status == 1) {
			seat->status = 0;
			printf("Booking for seat %d successfully canceled.\n", seatNumber);
		} else {
			printf("Seat %d is not booked.\n", seatNumber);
		}
	} else {
		printf("Seat %d not found.\n", seatNumber);
	}
}

// Display all seats and their booking status (In-order traversal)
void displaySeats(Seat* root) {
	if (root != NULL) {
		displaySeats(root->left);
		printf("Seat %d - %s\n", root->seatNumber, root->status == 0 ? "Available" : "Booked");
		displaySeats(root->right);
	}
}

// Main function
int main() {
	Seat* seatRoot = NULL;
	int choice, seatNumber;

	// Initialize seats 1-10
	for (int i = 1; i <= 30; i++) {
		seatRoot = insertSeat(seatRoot, i);
	}

	printf("\t\t\t=============================================\n");
	printf("\t\t\t|                                            |\n");
	printf("\t\t\t|        WELCOME TO THE CINEMA BOOKING       |\n");
	printf("\t\t\t|                  SYSTEM                    |\n");
	printf("\t\t\t|                                            |\n");
	printf("\t\t\t=============================================\n\n");

	while (1) {
		printf("\n\tCinema Ticket Booking System\n");
		printf("\t1. Book Seat\n");
		printf("\t2. Cancel Booking\n");
		printf("\t3. View Seats\n");
		printf("\t4. Exit\n");
		printf("\tEnter your choice: ");
		scanf("%d", &choice);

		switch (choice) {
		case 1:
			printf("Enter seat number to book: ");
			scanf("%d", &seatNumber);
			bookSeat(seatRoot, seatNumber);
			break;

		case 2:
			printf("Enter seat number to cancel booking: ");
			scanf("%d", &seatNumber);
			cancelBooking(seatRoot, seatNumber);
			break;

		case 3:
			printf("Seat Availability:\n");
			displaySeats(seatRoot);
			break;

		case 4:
			printf("\t\t\t =============================================\n");
			printf("\t\t\t|                                              |\n");
			printf("\t\t\t|  ^_^ ^_^    THANK YOU FOR BOOKING    ^_^ ^_^ |\n");
			printf("\t\t\t|                                              |\n");
			printf("\t\t\t =============================================\n\n");

			exit(0);

		default:
			printf("Invalid choice. Please try again.\n");
		}
	}
	return 0;
}
