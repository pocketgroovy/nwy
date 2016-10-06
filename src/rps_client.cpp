#include <iostream>

int main()
{
  	std::cout << "Content-type:text/html\r\n\r\n" << std::endl;
    std::cout << "<html>\n" << std::endl;
   	std::cout << "<head>\n" << std::endl;
   	std::cout << "<title>Rock Paper Scissors - nWay</title>\n" << std::endl;
   	std::cout << "</head>\n" << std::endl;
    std::cout << "<body>\n" << std::endl;
    std::cout << "<h2> Select Rock, Paper or Scissors</h2>" << std::endl;
    std::cout << "<form action='/cgi-bin/rps_server.cgi' method='POST' target='_blank'>" << std::endl;
    std::cout << "<input type='radio' name='hand' value='rock' checked='checked' /> Rock"<< std::endl;
    std::cout << "<input type='radio' name='hand' value='paper' /> Paper"<< std::endl;
    std::cout << "<input type='radio' name='hand' value='scissors' /> Scissors"<< std::endl;
    std::cout << "<br/>\n" << std::endl;
    std::cout << "<input type='submit' value='Go!'/>"<< std::endl;
    std::cout << "</form" << std::endl;
    
    std::cout << "<br/>\n" << std::endl;

    std::cout << "</body>\n" << std::endl;
    std::cout << "</html>\n" << std::endl;

	return 0;
}
