SRCDIR	= ./source
TESTDIR	= ./test
SRC 	=	$(SRCDIR)/sqlfactory.cpp	\
		$(SRCDIR)/utils.cpp		\
		$(TESTDIR)/main.cpp

OBJS	= $(SRC:.cpp=.o)

NAME	= upo

INCLUDE	= -I./include
INCLUDE	+= -I../mysql-connector/include

LFLAGS	= -L/export/expts/MySQLConnectorC++/lib/ -lmysqlcppconn-static
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

bclean:
	rm -rf *backup*

fclean: clean bclean
	rm -rf $(NAME)

re:	fclean all

backup:
	tar cvf backup_upo`date "+%Y%m%d%H%M%S"`.tar *.c *.h Makefile
