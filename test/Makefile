SRCDIR	= ./source
SRC 	=	main.cpp	\
		$(SRCDIR)/test.cpp

OBJS	= $(SRC:.cpp=.o)

NAME	= test-upo

INCLUDE	= -I./include
INCLUDE	+= -I../include
INCLUDE	+= -I../../mysql-connector/include

LFLAGS	= -L.. -lupo
LFLAGS	+= -L/export/expts/MySQLConnectorC++/lib/ -lmysqlcppconn-static
#LFLAGS	= -L/usr/local/lib/ -lmysqlcppconn-static
LFLAGS	+= -L/usr/lib/i386-linux-gnu/ -lmysqlclient

CFLAGS	= -W -Wall
CFLAGS	+= -Wlong-long -Wunused-parameter
CFLAGS 	+= $(INCLUDE)
# MySQL wrapper
CFLAGS	+= -DUPO_MYSQL -DSQL_ENGINE=MySQL

CC	= g++

$(NAME): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LFLAGS)

all:	$(NAME)

.cpp.o:
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(OBJS) *~
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re:	fclean all
