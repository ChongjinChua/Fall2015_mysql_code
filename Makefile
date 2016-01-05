all:
	g++ -Wall -Wshadow -g -o mysql mysql.cpp mysqlmain.cpp -L/usr/include/mysql -lmysqlclient -I/usr/include/mysql

valgrind: 
	valgrind --log-file=memcheck.log --track-origins=yes --leak-check=full ./mysql

