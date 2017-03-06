#This is Makefile Build 2016-10-24

CC = g++
RM = rm
INCLUDE = -I/usr/local/include/activemq-cpp-3.9.3 -I/usr/local/apr/include/apr-1
CFLAGS = -Wall -ggdb  $(INCLUDE) #-D_DEBUG 
JSONCPP = /usr/local/lib/libjsoncpp.a
LIBFILE = -lpthread $(JSONCPP) -lactivemq-cpp
PROJECT = TerminalServer
VERSIONDATE = `date '+%y%m%d'`
SRCCPP = listbuf.cpp log.cpp main.cpp  process.cpp myjson.cpp netconfig.cpp ryanConfig.cpp systeminfo.cpp global.cpp activemq.cpp
OBJS = $(SRCCPP:.cpp=.o)

all:$(PROJECT)

.cpp.o:
	@echo   "           "
	@echo   "c++    ...."
	$(CC) -c $(CFLAGS) $^

$(PROJECT):$(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFILE) -o $(PROJECT)_$(VERSIONDATE)

.PHONY:clean
clean:
	$(RM) -rf $(OBJS) $(PROJECT)_$(VERSIONDATE) core
