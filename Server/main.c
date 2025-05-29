/*
███████╗███████╗██████╗ ██╗   ██╗███████╗██████╗     ██████╗ ██╗   ██╗    ██████╗ ███████╗███╗   ███╗██╗   ██╗
██╔════╝██╔════╝██╔══██╗██║   ██║██╔════╝██╔══██╗    ██╔══██╗╚██╗ ██╔╝    ██╔══██╗██╔════╝████╗ ████║╚██╗ ██╔╝
███████╗█████╗  ██████╔╝██║   ██║█████╗  ██████╔╝    ██████╔╝ ╚████╔╝     ██████╔╝█████╗  ██╔████╔██║ ╚████╔╝
╚════██║██╔══╝  ██╔══██╗╚██╗ ██╔╝██╔══╝  ██╔══██╗    ██╔══██╗  ╚██╔╝      ██╔══██╗██╔══╝  ██║╚██╔╝██║  ╚██╔╝
███████║███████╗██║  ██║ ╚████╔╝ ███████╗██║  ██║    ██████╔╝   ██║       ██║  ██║███████╗██║ ╚═╝ ██║   ██║
╚══════╝╚══════╝╚═╝  ╚═╝  ╚═══╝  ╚══════╝╚═╝  ╚═╝    ╚═════╝    ╚═╝       ╚═╝  ╚═╝╚══════╝╚═╝     ╚═╝   ╚═╝
*/

#include "func.h"

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable:4996)

#define SERVER_MOVE 0 // O
#define CLIENT_MOVE 1 // X
#define BOARD_SIZE 3
#define DT "\x1b[0m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"

char current_user = SERVER_MOVE;
char board[BOARD_SIZE][BOARD_SIZE] = { {'-', '-', '-'},
                                       {'-', '-', '-'},
                                       {'-', '-', '-'} };

int main() {
    beggining();
    WSADATA ws;
    WSAStartup(MAKEWORD(2, 2), &ws);
    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN sa;//struct with settings of our socket
    sa.sin_family = AF_INET;//works only with ipv4
    sa.sin_port = htons(8080);
    sa.sin_addr.S_un.S_addr = INADDR_ANY;
    bind(s, &sa, sizeof(sa));
    listen(s, 1);
    SOCKET client_socket;
    SOCKADDR_IN client_addr;
    int size = sizeof(client_addr);
    client_socket = accept(s, &client_addr, &size);
    if (client_socket  == INVALID_SOCKET) {
        printf(RED"Failed connection!\n"DT);
        closesocket(s);
        WSACleanup();
        return 1;
    }
    short int row, column;
    printf(GREEN"Friend connected\n"DT);
    while (1) {
        printBoard(board);
        if (current_user == SERVER_MOVE) {
            printf("entry row: ");
            scanf("%hd", &row);
            printf("entry column: ");
            scanf("%hd", &column);
            board[row][column] = 'O';
            send(client_socket, &row, sizeof(row), 0);
            send(client_socket, &column, sizeof(column), 0);
            current_user = CLIENT_MOVE;
        }
        else if (current_user == CLIENT_MOVE) {
            printf("your friend's move\n");
            recv(client_socket, &row, sizeof(row), 0);
            recv(client_socket, &column, sizeof(column), 0);
            board[row][column] = 'X';
            current_user = SERVER_MOVE;
        }
        check(s, client_socket, board);
    }
    return 0;
}
