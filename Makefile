TESTS	= test-upo

SRCDIR	= ./source
SRC 	=	$(SRCDIR)/sqlfactory.cpp	\
		$(SRCDIR)/sqlfactory_mysql.cpp	\
		$(SRCDIR)/utils.cpp

OBJS	= $(SRC:.cpp=.o)

NAME	= libupo.a

INCLUDE	= -I./include
INCLUDE	+= -I../mysql-connector/include

CFLAGS	= -W -Wall
CFLAGS	+= -Wlong-long -Wunused-parameter
CFLAGS 	+= $(INCLUDE)
# MySQL wrapper
CFLAGS	+= -DUPO_MYSQL -DSQL_ENGINE=MySQL

CC	= g++
AR	= ar

$(NAME): $(OBJS)
	$(AR) -rvcs $@ $(OBJS)

all:	$(NAME)

.cpp.o:
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(OBJS) *~
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re:	fclean all

test:	$(TESTS)
$(TESTS):
	make -C test
