Socket
	run server -- ./server
	run client -- ./client

	selection 1 for rock, 2 for paper, 3 for scissors and 4 for statistic
	the statistic is saved as "game_data.txt" on client side
	server side will keep track the result to log_file.txt

* developed on Centos 7 
_____________________________________________________________________________________________________

CGI
Rock Paper Scissors implementation in C++

* A web browser as a client

* Log file should be created under inside log directory with a name log_file.txt 

* Source files are inside src directory

--To test--

1. place all the folders under the apache directory

2. access it by typing your-domain-name/cgi-bin/rps_client.cgi

3. make a selection and hit "Go!"

4. You will see Computer's selection, Your selection and the result if you won, lost or draw.

* the log file will keep track the users' process IDs and their selections, Computer selections and the results, as well as disconnection.
