/*
 * Player Management System
 *
 * This program allows users to manage a list of cricket players, including functionalities 
 * for adding, displaying, searching, updating, sorting, and removing player records. 
 * Each player is represented by a structure containing the following attributes:
 * - Jersey Number (int)
 * - Player Name (string)
 * - Runs scored (int)
 * - Wickets taken (int)
 * - Matches played (int)
 *
 * Key Features:
 * 1. Dynamically adds players and expands the array using malloc and realloc.
 * 2. Displays all players in a formatted table.
 * 3. Searches for players by jersey number or name.
 * 4. Updates player statistics based on jersey number.
 * 5. Removes players from the list using jersey number.
 * 6. Sorts players by runs or wickets in ascending order.
 *
 * The program continues to run until the user chooses to exit, ensuring a continuous 
 * management experience. Memory is dynamically allocated to handle any number of players.
 *
 * Author: [Your Name]
 * Date: [Current Date]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int jNumber;
    char pName[100];
    int runs;
    int wickets;
    int matchPlayed;
} Player;

// Function to add players and return the updated pointer
Player* addPlayer(Player *players, int *count, int *size) {
    int playersToAdd;

    if (*size == 0) {
        *size = 1;
        players = (Player *)malloc(sizeof(Player));
    } else {
        printf("How many players do you want to add? ");
        scanf("%d", &playersToAdd);
        *size += playersToAdd;
        players = (Player *)realloc(players, (*size) * sizeof(Player));
    }

    for (int i = *count; i < *size; i++) {
        printf("\nAdding player %d:\n", i + 1);
        printf("Enter Jersey Number: ");
        scanf("%d", &players[i].jNumber);
        printf("Enter Player Name: ");
        scanf(" %[^\n]%*c", players[i].pName);
        printf("Enter Runs: ");
        scanf("%d", &players[i].runs);
        printf("Enter Wickets: ");
        scanf("%d", &players[i].wickets);
        printf("Enter Matches Played: ");
        scanf("%d", &players[i].matchPlayed);

        (*count)++;
        printf("Player added successfully!\n");
    }

    return players; // Return the updated pointer
}

void displayPlayers(Player *players, int count) {
    if (count == 0) {
        printf("No players have been added yet.\n");
        return;
    }

    printf("\n--- List of Players ---\n");
    printf("+-----------------+-----------------------+-------+---------+----------------+\n");
    printf("| Jersey Number    | Player Name           | Runs  | Wickets | Matches Played  |\n");
    printf("+-----------------+-----------------------+-------+---------+----------------+\n");

    for (int i = 0; i < count; i++) {
        printf("| %-15d | %-21s | %-5d | %-7d | %-14d |\n",
               players[i].jNumber,
               players[i].pName,
               players[i].runs,
               players[i].wickets,
               players[i].matchPlayed);
    }

    printf("+-----------------+-----------------------+-------+---------+----------------+\n");
}

void sortPlayers(Player *players, int count) {
    if (count == 0) {
        printf("No players to sort.\n");
        return;
    }

    int choice;
    printf("Sort by:\n");
    printf("1. Runs (Minimum to Maximum)\n");
    printf("2. Wickets (Minimum to Maximum)\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int shouldSwap = 0;
            if (choice == 1 && players[j].runs > players[j + 1].runs) {
                shouldSwap = 1;
            } else if (choice == 2 && players[j].wickets > players[j + 1].wickets) {
                shouldSwap = 1;
            }

            if (shouldSwap) {
                Player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }

    printf("\n--- Sorted Players ---\n");
    displayPlayers(players, count);
}

void removePlayer(Player *players, int *count) {
    if (*count == 0) {
        printf("No players to remove.\n");
        return;
    }

    int jNumber;
    printf("Enter Jersey Number of player to remove: ");
    scanf("%d", &jNumber);

    for (int i = 0; i < *count; i++) {
        if (players[i].jNumber == jNumber) {
            players[i] = players[*count - 1];
            (*count)--;
            printf("Player with jersey number %d removed successfully!\n", jNumber);
            return;
        }
    }

    printf("Player with jersey number %d not found.\n");
}

void searchPlayer(Player *players, int count) {
    if (count == 0) {
        printf("No players have been added yet.\n");
        return;
    }

    int choice;
    printf("Search by:\n");
    printf("1. Jersey Number\n");
    printf("2. Name\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        int jNumber;
        printf("Enter Jersey Number of player to search: ");
        scanf("%d", &jNumber);

        for (int i = 0; i < count; i++) {
            if (players[i].jNumber == jNumber) {
                printf("\n--- Player Found ---\n");
                printf("+-----------------+-----------------------+-------+---------+----------------+\n");
                printf("| Jersey Number    | Player Name           | Runs  | Wickets | Matches Played  |\n");
                printf("+-----------------+-----------------------+-------+---------+----------------+\n");
                printf("| %-15d | %-21s | %-5d | %-7d | %-14d |\n",
                       players[i].jNumber,
                       players[i].pName,
                       players[i].runs,
                       players[i].wickets,
                       players[i].matchPlayed);
                printf("+-----------------+-----------------------+-------+---------+----------------+\n");
                return;
            }
        }
        printf("Player with jersey number %d not found.\n", jNumber);
    } else if (choice == 2) {
        char name[100];
        printf("Enter Player Name to search: ");
        scanf(" %[^\n]%*c", name);

        for (int i = 0; i < count; i++) {
            if (strcmp(players[i].pName, name) == 0) {
                printf("\n--- Player Found ---\n");
                printf("+-----------------+-----------------------+-------+---------+----------------+\n");
                printf("| Jersey Number    | Player Name           | Runs  | Wickets | Matches Played  |\n");
                printf("+-----------------+-----------------------+-------+---------+----------------+\n");
                printf("| %-15d | %-21s | %-5d | %-7d | %-14d |\n",
                       players[i].jNumber,
                       players[i].pName,
                       players[i].runs,
                       players[i].wickets,
                       players[i].matchPlayed);
                printf("+-----------------+-----------------------+-------+---------+----------------+\n");
                return;
            }
        }
        printf("Player with name %s not found.\n", name);
    } else {
        printf("Invalid choice! Please try again.\n");
    }
}

void updatePlayer(Player *players, int count) {
    if (count == 0) {
        printf("No players have been added yet.\n");
        return;
    }

    int jNumber;
    printf("Enter Jersey Number of player to update: ");
    scanf("%d", &jNumber);

    for (int i = 0; i < count; i++) {
        if (players[i].jNumber == jNumber) {
            printf("\nPlayer found:\n");
            printf("+-----------------+-----------------------+-------+---------+----------------+\n");
            printf("| Jersey Number    | Player Name           | Runs  | Wickets | Matches Played  |\n");
            printf("+-----------------+-----------------------+-------+---------+----------------+\n");
            printf("| %-15d | %-21s | %-5d | %-7d | %-14d |\n",
                   players[i].jNumber,
                   players[i].pName,
                   players[i].runs,
                   players[i].wickets,
                   players[i].matchPlayed);
            printf("+-----------------+-----------------------+-------+---------+----------------+\n");

            // Update player details
            printf("\nEnter new Runs: ");
            scanf("%d", &players[i].runs);
            printf("Enter new Wickets: ");
            scanf("%d", &players[i].wickets);
            printf("Enter new Matches Played: ");
            scanf("%d", &players[i].matchPlayed);

            printf("Player updated successfully!\n");
            return;
        }
    }

    printf("Player with jersey number %d not found.\n", jNumber);
}

int main() {
    Player *players = NULL;
    int count = 0, size = 0, choice;

    while (1) {
        printf("\nPlayer Management System\n");
        printf("1. Add Player\n");
        printf("2. Display Players\n");
        printf("3. Search Player\n");
        printf("4. Update Player\n");
        printf("5. Remove Player\n");
        printf("6. Sort Players\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                players = addPlayer(players, &count, &size);
                break;
            case 2:
                displayPlayers(players, count);
                break;
            case 3:
                searchPlayer(players, count);
                break;
            case 4:
                updatePlayer(players, count);
                break;
            case 5:
                removePlayer(players, &count);
                break;
            case 6:
                sortPlayers(players, count);
                break;
            case 7:
                free(players);
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
