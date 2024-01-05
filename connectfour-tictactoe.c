#include <stdio.h>
#define MAX_ROWS 6
#define MAX_COLS 7
void printBoard(int n, int m, char board[MAX_ROWS][MAX_COLS]) {
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            printf("+---");
        }
        printf("+\n");

        for (j = 0; j < n; j++) {
            printf("| %c ", board[i][j]);
        }
        printf("|\n");
    }

    for (j = 0; j < n; j++) {
        printf("+---");
    }
    printf("+\n");

    for (j = 0; j < n; j++) {
        printf("  %d ", j);
    }
    printf("\n\n");
}

int isValidMove(int n, int m, char board[MAX_ROWS][MAX_COLS], int column) {
    return (column >= 0 && column < n && board[0][column] == ' ');
}
void placeMove(int n, int m, char board[MAX_ROWS][MAX_COLS], int column, char player) {
    int i;
    for (i = m - 1; i >= 0; --i) {
        if (board[i][column] == ' ') {
            board[i][column] = player;
            break;
        }
    }
}
int checkWin(int n, int m, char board[MAX_ROWS][MAX_COLS], char player) {
    int i, j;
    for (i = 0; i < m; i++) {
        for (j = 0; j <= n - 4; j++) {
            if (board[i][j] == player &&
                board[i][j + 1] == player &&
                board[i][j + 2] == player &&
                board[i][j + 3] == player)
                return 1; 
        }
    }

    for (i = 0; i <= m - 4; i++) {
        for (j = 0; j < n; j++) {
            if (board[i][j] == player &&
                board[i + 1][j] == player &&
                board[i + 2][j] == player &&
                board[i + 3][j] == player)
                return 1; 
        }
    }
    for (i = 0; i <= m - 4; i++) {
        for (j = 0; j <= n - 4; j++) {
            if (board[i][j] == player &&
                board[i + 1][j + 1] == player &&
                board[i + 2][j + 2] == player &&
                board[i + 3][j + 3] == player)
                return 1;
        }
    }

    for (i = 0; i <= m - 4; i++) {
        for (j = n - 1; j >= 3; j--) {
            if (board[i][j] == player &&
                board[i + 1][j - 1] == player &&
                board[i + 2][j - 2] == player &&
                board[i + 3][j - 3] == player)
                return 1; 
        }
    }

    return 0; 
}

int isBoardFull(int n, int m, char board[MAX_ROWS][MAX_COLS]) {
    int i, j;
    for (i = 0; i < m; ++i) {
        for (j = 0; j < n; ++j) {
            if (board[i][j] == ' ') {
                return 0; 
            }
        }
    }
    return 1; 
}

void playConnectFour() {
    char board[MAX_ROWS][MAX_COLS];
    int i,j;
    for ( i = 0; i < MAX_ROWS; i++) {
        for ( j = 0; j < MAX_COLS; j++) {
            board[i][j] = ' ';
        }
    }
    int currentPlayer = 1; 

    do {
        printBoard(MAX_COLS, MAX_ROWS, board);

        int column;
        do {
            printf("Player %d, enter a column (1-7): ", currentPlayer);
            scanf("%d", &column);
            column--; 
            if (isValidMove(MAX_COLS, MAX_ROWS, board, column)) {
                placeMove(MAX_COLS, MAX_ROWS, board, column, (currentPlayer == 1) ? 'X' : 'O');

                if (checkWin(MAX_COLS, MAX_ROWS, board, (currentPlayer == 1) ? 'X' : 'O')) {
                    printBoard(MAX_COLS, MAX_ROWS, board);
                    printf("Player %d wins!\n", currentPlayer);
                    return;
                }

                if (isBoardFull(MAX_COLS, MAX_ROWS, board)) {
                    printBoard(MAX_COLS, MAX_ROWS, board);
                    printf("The game is a tie!\n");
                    return;
                }

                currentPlayer = (currentPlayer == 1) ? 2 : 1;
                break;
            } else {
                printf("Invalid move. Please choose a valid column.\n");
            }
        } while (1);

    } while (1);
}

void playTicTacToe() {
    char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int row, col;
    char current_player = 'X';

    while (1) {
        printBoard(3, 3, board);
        printf("Player %c, enter your move (row and column, e.g., 1 2): ", current_player);
        scanf("%d %d", &row, &col);
        if (row < 0 || row >= 3 || col < 0 || col >= 3 || board[row][col] != ' ') {
            printf("Invalid move. Try again.\n");
            continue;
        }
        board[row][col] = current_player;
        if (checkWin(3, 3, board, current_player)) {
            printBoard(3, 3, board);
            printf("Player %c wins!\n", current_player);
            return;
        }
        if (isBoardFull(3, 3, board)) {
            printBoard(3, 3, board);
            printf("The game is a tie!\n");
            return;
        }
        current_player = (current_player == 'X') ? 'O' : 'X';
    }
}

int main() {
    char choice;

    do {
        printf("Choose a game to play:\n");
        printf("1. Connect Four\n");
        printf("2. Tic-Tac-Toe\n");
        printf("Enter your choice (1 or 2): ");
        int gameChoice;
        scanf("%d", &gameChoice);

        if (gameChoice == 1) {
            playConnectFour();
        } else if (gameChoice == 2) {
            playTicTacToe();
        } else {
            printf("Invalid choice. Please enter 1 or 2.\n");
        }

        printf("Do you want to play again? (y/n): ");
        scanf(" %c", &choice);
    } while (choice == 'y');

    return 0;
}

