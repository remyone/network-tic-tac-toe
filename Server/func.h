#include <stdio.h>
#include <winsock2.h>
#include <stdlib.h>

#define BOARD_SIZE 3

void printBoard(char board[3][3]) {
    for (register int i = 0; i < BOARD_SIZE; ++i) {
        for (register int j = 0; j < BOARD_SIZE; ++j) {
            printf("%c", board[i][j]);
        }
        putchar('\n');
    }
}

void beggining() {
    printf("███████╗███████╗██████╗ ██╗   ██╗███████╗██████╗     ██████╗ ██╗   ██╗    ██████╗ ███████╗███╗   ███╗██╗   ██╗\n");
    printf("██╔════╝██╔════╝██╔══██╗██║   ██║██╔════╝██╔══██╗    ██╔══██╗╚██╗ ██╔╝    ██╔══██╗██╔════╝████╗ ████║╚██╗ ██╔╝\n");
    printf("███████╗█████╗  ██████╔╝██║   ██║█████╗  ██████╔╝    ██████╔╝ ╚████╔╝     ██████╔╝█████╗  ██╔████╔██║ ╚████╔╝\n");
    printf("╚════██║██╔══╝  ██╔══██╗╚██╗ ██╔╝██╔══╝  ██╔══██╗    ██╔══██╗  ╚██╔╝      ██╔══██╗██╔══╝  ██║╚██╔╝██║  ╚██╔╝\n");
    printf("███████║███████╗██║  ██║ ╚████╔╝ ███████╗██║  ██║    ██████╔╝   ██║       ██║  ██║███████╗██║ ╚═╝ ██║   ██║\n");
    printf("╚══════╝╚══════╝╚═╝  ╚═╝  ╚═══╝  ╚══════╝╚═╝  ╚═╝    ╚═════╝    ╚═╝       ╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝   ╚═╝\n");
}

void check(SOCKET server_socket, SOCKET client_socket, char board[3][3]) {
    //if draw
    static short int numberOfFilledCells = 0;
    for (register int i = 0; i < BOARD_SIZE; ++i) {
        for (register int j = 0; j < BOARD_SIZE; ++j) {
            if (board[i][j] == 'O' || board[i][j] == 'X') {
                ++numberOfFilledCells;
            }
        }
    }
    if (numberOfFilledCells == BOARD_SIZE * 3) {
        printf("Draw!\n");
        exit(0);
        closesocket(client_socket);
        closesocket(server_socket);
        WSACleanup();
    }
    // check if server is a winner
    if (board[0][0] == 'O' && board[0][1] == 'O' && board[0][2] == 'O') {
        printf("You're a winner!\n");
        exit(0);
        closesocket(client_socket);
        closesocket(server_socket);
        WSACleanup();
    }
    else if (board[1][0] == 'O' && board[1][1] == 'O' && board[1][2] == 'O') {
        printf("You're a winner!\n");
        exit(0);
        closesocket(client_socket);
        closesocket(server_socket);
        WSACleanup();
    }
    else if (board[2][0] == 'O' && board[2][1] == 'O' && board[2][2] == 'O') {
        printf("You're a winner!\n");
        exit(0);
        closesocket(client_socket);
        closesocket(server_socket);
        WSACleanup();
    }
    else if (board[0][0] == 'O' && board[1][1] == 'O' && board[2][2] == 'O') {
        printf("You're a winner!\n");
        exit(0);
        closesocket(client_socket);
        closesocket(server_socket);
        WSACleanup();
    }
    else if (board[0][2] == 'O' && board[1][1] == 'O' && board[2][0] == 'O') {
        printf("You're a winner!\n");
        exit(0);
        closesocket(client_socket);
        closesocket(server_socket);
        WSACleanup();
    }
    else if (board[0][0] == 'O' && board[1][0] == 'O' && board[2][0] == 'O') {
        printf("You're a winner!\n");
        exit(0);
        closesocket(client_socket);
        closesocket(server_socket);
        WSACleanup();
    }
    else if (board[0][1] == 'O' && board[1][1] == 'O' && board[2][1] == 'O') {
        printf("You're a winner!\n");
        exit(0);
        closesocket(client_socket);
        closesocket(server_socket);
        WSACleanup();
    }
    else if (board[0][2] == 'O' && board[1][2] == 'O' && board[2][2] == 'O') {
        printf("You're a winner!\n");
        exit(0);
        closesocket(client_socket);
        closesocket(server_socket);
        WSACleanup();
    }// check if client is a winner
    else if (board[0][0] == 'X' && board[0][1] == 'X' && board[0][2] == 'X') {
        printf("Your friend is a winner!\n");
        exit(0);
        closesocket(client_socket);
        closesocket(server_socket);
        WSACleanup();
    }
    else if (board[1][0] == 'X' && board[1][1] == 'X' && board[1][2] == 'X') {
        printf("Your friend is a winner!\n");
        exit(0);
        closesocket(client_socket);
        WSACleanup();
    }
    else if (board[2][0] == 'X' && board[2][1] == 'X' && board[2][2] == 'X') {
        printf("Your friend is a winner!\n");
        exit(0);
        closesocket(client_socket);
        closesocket(server_socket);
        WSACleanup();
    }
    else if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X') {
        printf("Your friend is a winner!\n");
        exit(0);
        closesocket(client_socket);
        closesocket(server_socket);
        WSACleanup();
    }
    else if (board[0][2] == 'X' && board[1][1] == 'X' && board[2][0] == 'X') {
        printf("Your friend is a winner!\n");
        exit(0);
        closesocket(client_socket);
        closesocket(server_socket);
        WSACleanup();
    }
    else if (board[0][0] == 'X' && board[1][0] == 'X' && board[2][0] == 'X') {
        printf("your friend is a winner\n");
        exit(0);
        closesocket(client_socket);
        closesocket(server_socket);
        WSACleanup();
    }
    else if (board[0][1] == 'X' && board[1][1] == 'X' && board[2][1] == 'X') {
        printf("Your friend is a winner!\n");
        exit(0);
        closesocket(client_socket);
        closesocket(server_socket);
        WSACleanup();
    }
    else if (board[0][2] == 'X' && board[1][2] == 'X' && board[2][2] == 'X') {
        printf("Your friend is a winner!\n");
        exit(0);
        closesocket(client_socket);
        closesocket(server_socket);
        WSACleanup();
    }
}