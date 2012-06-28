SRCDIR	= .
SRC 	=	$(SRCDIR)/main.cpp

OBJS	= $(SRC:.cpp=.o)

NAME	= test-upo

INCLUDE	= -I.
INCLUDE	+= -I../include
INCLUDE	+= -I../../mysql-connector/include

LFLAGS	= -L/export/expts/MySQLConnectorC++/lib/ -lmysqlcppconn-static
#LFLAGS	= -L/usr/local/lib/ -lmysqlcppconn-static
LFLAGS	+= -L/usr/lib/i386-linux-gnu/ -lmysqlclient
LFLAGS	+= -L.. -lupo

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
