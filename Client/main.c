/*
 ██████╗██╗     ██╗███████╗███╗   ██╗████████╗    ██████╗ ██╗   ██╗    ██████╗ ███████╗███╗   ███╗██╗   ██╗
██╔════╝██║     ██║██╔════╝████╗  ██║╚══██╔══╝    ██╔══██╗╚██╗ ██╔╝    ██╔══██╗██╔════╝████╗ ████║╚██╗ ██╔╝
██║     ██║     ██║█████╗  ██╔██╗ ██║   ██║       ██████╔╝ ╚████╔╝     ██████╔╝█████╗  ██╔████╔██║ ╚████╔╝
██║     ██║     ██║██╔══╝  ██║╚██╗██║   ██║       ██╔══██╗  ╚██╔╝      ██╔══██╗██╔══╝  ██║╚██╔╝██║  ╚██╔╝
╚██████╗███████╗██║███████╗██║ ╚████║   ██║       ██████╔╝   ██║       ██║  ██║███████╗██║ ╚═╝ ██║   ██║
 ╚═════╝╚══════╝╚═╝╚══════╝╚═╝  ╚═══╝   ╚═╝       ╚═════╝    ╚═╝       ╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝   ╚═╝

*/

#include "func.h"

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

#define DT "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define BOARD_SIZE 3
#define IP "127.0.0.1"

char board[BOARD_SIZE][BOARD_SIZE] = { {'-', '-', '-'},
                                       {'-', '-', '-'},
                                       {'-', '-', '-'} };

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    beggining();
    WSADATA ws;
    WSAStartup(MAKEWORD(2, 2), &ws);
    SOCKET client_socket = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN sa;//struct with settings of our socket
    sa.sin_family = AF_INET;
    sa.sin_port = htons(8080);
    sa.sin_addr.S_un.S_addr = inet_addr(IP);
    if (connect(client_socket, &sa, sizeof(sa)) != 0) {
        printf(RED"Failed connection!\n"DT);
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }
    short int row, column;
    char isWorking = 0;
    printf(GREEN"You connected successfully!\n"DT);
    while (!isWorking) {
        printf("your friend's move\n");
        recv(client_socket, &row, sizeof(row), 0);
        recv(client_socket, &column, sizeof(column), 0);
        board[row][column] = 'O';
        check(client_socket, board);
        printBoard(board);
        printf("entry row: ");
        scanf("%hd", &row);
        printf("entry column: ");
        scanf("%hd", &column);
        board[row][column] = 'X';
        check(client_socket, board);
        printBoard(board);
        send(client_socket, &row, sizeof(row), 0);
        send(client_socket, &column, sizeof(column), 0);
    }

    return 0;
}
