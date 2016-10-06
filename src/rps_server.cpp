#include <iostream>
#include <vector>  
#include <string>  
#include <stdio.h>  
#include <stdlib.h> 
#include <time.h>
#include <sys/types.h>
#include <unistd.h>

#include <cgicc/CgiDefs.h> 
#include <cgicc/Cgicc.h> 
#include <cgicc/HTTPHTMLHeader.h> 
#include <cgicc/HTMLClasses.h> 
#include <unordered_map>
#include <fstream>

using namespace cgicc;

std::unordered_map <std::string, int> hands;
int user_pid;

int get_pid();
int computer_hand();
std::string get_result(int cp, std::string user);
std::string get_hand_in_string(int hand);
void write_text_to_log_file(std::string text );


int main ()
{
   srand(time(NULL));

   hands["rock"] = 1;
   hands["paper"] = 2;
   hands["scissors"] = 3;
   user_pid = get_pid();
   int cp_hand = computer_hand();

   Cgicc formData;
  
   std::cout << "Content-type:text/html\r\n\r\n" << std::endl;
   std::cout << "<html>\n"<< std::endl;
   std::cout << "<head>\n"<< std::endl;
   std::cout << "<title>Result</title>\n" << std::endl;
   std::cout << "</head>\n"<< std::endl;
   std::cout << "<body>\n"<< std::endl;
   
   std::string cp_hand_str =  get_hand_in_string(cp_hand);

   std::cout << "CP hand is: " << cp_hand_str << std::endl;
   std::cout << "<br/>\n"<< std::endl;
   std::cout << "<br/>\n"<< std::endl;
   write_text_to_log_file("cp's hand: " + cp_hand_str);


   form_iterator fi = formData.getElement("hand");  
   if( !fi->isEmpty() && fi != (*formData).end()) {  
      std::cout << "You have selected: " << **fi << std::endl;
      write_text_to_log_file("user's hand: " + **fi);
   }

   std::cout << "<br/>\n"<< std::endl;
   std::string result = get_result(cp_hand, **fi);
   std::cout << "<h2> You have " << result << std::endl;
   std::cout << "</body>\n"<< std::endl;
   std::cout << "</html>\n"<< std::endl;


   write_text_to_log_file("result: User " + result);
   
   write_text_to_log_file("disconnect");
   return 0;
}

int get_pid()
{
   int id = getpid();
   return id;
}

// 1 for Rock, 2 for Paper, 3 for Scissors
int computer_hand()
{
   int hand = rand() % 3 + 1;
   return hand;
}

std::string get_hand_in_string(int hand){
   if(hand == 1) return "rock";
   else if(hand == 2) return "paper";
   else{
      return "scissors";
   }
}


std::string get_result(int cp, std::string user){
   if(hands[user] == cp){
      return "draw";
   }
   else if(hands[user] == 1){
      if(cp == 2){
         return "lost";
      }
      else{
         return "won";
      }
   }
   else if(hands[user] == 2){
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

void write_text_to_log_file(std::string text)
{
   text = "user: " + std::to_string(user_pid) + " " + text;
    std::ofstream log_file(
        "../log/log_file.txt", std::ios_base::out | std::ios_base::app );
    log_file << text << std::endl;
}