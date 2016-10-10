#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <netinet/in.h>
#include <resolv.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "FileHandler.h"


void prompt(int hsock);
void handle_result(std::string result);
void session_statistic();

int main(int argv, char** argc){
    struct sockaddr_in my_addr;
    char* host_name="127.0.0.1";
    int host_port= 1101;
    int hsock;
    int * p_int;
    int err;

    // database.create_table();
    hsock = socket(AF_INET, SOCK_STREAM, 0);
    if(hsock == -1){
        printf("Error initializing socket %d\n",errno);
        goto FINISH;
    }
    
    p_int = (int*)malloc(sizeof(int));
    *p_int = 1;
        
    if( (setsockopt(hsock, SOL_SOCKET, SO_REUSEADDR, (char*)p_int, sizeof(int)) == -1 )||
        (setsockopt(hsock, SOL_SOCKET, SO_KEEPALIVE, (char*)p_int, sizeof(int)) == -1 ) ){
        printf("Error setting options %d\n",errno);
        free(p_int);
        goto FINISH;
    }
    free(p_int);

    my_addr.sin_family = AF_INET ;
    my_addr.sin_port = htons(host_port);
    
    memset(&(my_addr.sin_zero), 0, 8);
    my_addr.sin_addr.s_addr = inet_addr(host_name);

    if( connect( hsock, (struct sockaddr*)&my_addr, sizeof(my_addr)) == -1 ){
        if((err = errno) != EINPROGRESS){
            fprintf(stderr, "Error connecting socket %d\n", errno);
            goto FINISH;
        }
    }

    prompt(hsock);
    
    close(hsock);

    FINISH:
    ;
}


void prompt(int hsock){
    char buffer[1024];
    int buffer_len;
    int bytecount;

    buffer_len = 1024;
    int user_hand;

    memset(buffer, '\0', buffer_len);

    printf("Enter 1 for Rock, 2 for Paper, 3 for Scissors and 4 for session result (press enter)\n");
    fgets(buffer, 1024, stdin);

    user_hand = atoi(buffer);
    if(user_hand < 1 || user_hand > 4){
        printf("Please enter 1, 2, or 3\n");
        close(hsock);
        goto FINISH;
    }

    if(user_hand == 4){
        session_statistic();
    }
    else{
        buffer[strlen(buffer)-1]='\0';

        if( (bytecount=send(hsock, buffer, strlen(buffer),0))== -1){
            fprintf(stderr, "Error sending data %d\n", errno);
            goto FINISH;
        }

        if((bytecount = recv(hsock, buffer, buffer_len, 0))== -1){
            fprintf(stderr, "Error receiving data %d\n", errno);
            goto FINISH;
        }
        printf("Result: \"%s\"\n", buffer);

        handle_result(buffer);
    }

    FINISH:
    ;
}

void handle_result(std::string result){
    FileHandler fhandler;

    int data[4]; 
    memset(data, 0, sizeof(data));
    fhandler.read_file(data);

    if(result == "won"){
        data[0] = data[0] + 1;
    }
    else if(result == "lost"){
        data[1] = data[1] + 1;
    }
    else if(result == "draw"){
        data[2] = data[2] + 1;
    }
    data[3] = data[3]+ 1; // game counter

    std::string data_string;
    data_string = std::to_string(data[0]);
    for(int i = 1; i < 4; i++){
        data_string = data_string + ",";
        data_string = data_string + std::to_string(data[i]);
    }
    fhandler.write_to_file(data_string);
}

void session_statistic(){
    FileHandler fhandler;
    int data[4]; 
    memset(data, 0, sizeof(data));
    fhandler.read_file(data);
    printf("You have played: %d times, won: %d, lost: %d, draw %d\n", data[3], data[0], data[1], data[2]);
}


