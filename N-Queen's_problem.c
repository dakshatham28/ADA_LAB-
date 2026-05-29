#include <stdio.h>

int board[20][20]; // A simple 2D grid (supports up to a 20x20 board)
int n;             // Size of the board entered by the user
int count = 0;     // Total solution tracker

// 1. Clear display function
void printSolution() {
    count++;
    printf("Solution %d:\n", count);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (board[i][j] == 1) printf(" Q ");
            else                  printf(" . ");
        }
        printf("\n");
    }
    printf("\n");
}

// 2. Simple loop check: Is it safe to drop a queen here?
int isSafe(int row, int col) {
    int i, j;

    // Check row to the left
    for (i = 0; i < col; i++) {
        if (board[row][i] == 1) return 0; // Under attack!
    }

    // Check upper diagonal to the left
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) return 0; // Under attack!
    }

    // Check lower diagonal to the left
    for (i = row, j = col; i < n && j >= 0; i++, j--) {
        if (board[i][j] == 1) return 0; // Under attack!
    }

    return 1; // Completely safe!
}

// 3. The Backtracking core
void solve(int col) {
    // If we reach past the last column, we successfully placed all queens!
    if (col == n) {
        printSolution();
        return;
    }

    // Try placing a queen in every row of this column
    for (int i = 0; i < n; i++) {
        if (isSafe(i, col)) {
            
            board[i][col] = 1;  // PLACE: Place the queen
            
            solve(col + 1);     // EXPLORE: Move to the next column
            
            board[i][col] = 0;  // BACKTRACK: Take it back if it didn't work out
        }
    }
}

int main() {
    printf("Enter board size (N): ");
    scanf("%d", &n);

    // Start the process at column 0
    solve(0);

    if (count == 0) {
        printf("No solutions exist for a board size of %d.\n", n);
    } else {
        printf("Total solutions found: %d\n", count);
    }

    return 0;
}
