#include <iostream>
#include <vector>  
#include <string>  
#include <stdio.h>  
#include <stdlib.h> 
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <unordered_map>
#include <fstream>

#include "Server.h"


int computer_hand();
std::unordered_map <int, std::string> hands;
std::string get_result(int cp, int user);

void write_text_to_log_file(std::string text );


std::string Server::handle_userinput(int userinput)
{

   hands[1] = "Rock";
   hands[2] = "Paper";
   hands[3] = "Scissors";

   char* str = new char[100];
   srand(time(NULL));

   int cp_hand = computer_hand();
   printf("Computer hand \"%s\"\n", hands[cp_hand].c_str());


   std::string result = get_result(cp_hand, userinput);
   sprintf(str, "CP hand: %s, Your hand was %s, You %s", 
      hands[cp_hand].c_str(), hands[userinput].c_str(), result.c_str());
   
   write_text_to_log_file(str);
   
   return result;
}


// 1 for Rock, 2 for Paper, 3 for Scissors
int computer_hand()
{
   int hand = rand() % 3 + 1;
   return hand;
}


std::string get_result(int cp, int user){
   if(user == cp){
      return "draw";
   }
   else if(user == 1){
      if(cp == 2){
         return "lost";
      }
      else{
         return "won";
      }
   }
   else if(user == 2){
      if(cp == 3){
         return "lost";
      }
      else{
         return "won";
      }
   }
   else{
      if(cp == 1){
         return "lost";
      }
      else{
         return "won";
      }
   }
}

void Server::socket_closed_msg(){
   write_text_to_log_file("user disconnected");
}

void write_text_to_log_file(std::string text)
{
    std::ofstream log_file(
        "log_file.txt", std::ios_base::out | std::ios_base::app );
    log_file << text << std::endl;
}