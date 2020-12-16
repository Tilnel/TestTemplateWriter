IDIR = ./include
ODIR = ./build
INCLUDES = $(addprefix -I, $(IDIR))
CFLAGS += -O2 -Wall -Werror -ggdb3 $(INCLUDES)
CC = g++
LD = g++
BINARY = $(ODIR)/writer
SRCS = $(shell find src/ -name "*.cpp")
OBJS = $(SRCS:src/%.cpp=$(ODIR)/%.o)

$(ODIR)/%.o : src/%.cpp
	@$(CC) $(CFLAGS) -c -o $@ $<

-include $(OBJS:.o=.d)

.DEFAULT_GOAL = love

.PHONY : love run run-env gdb clean
love : $(BINARY)

$(BINARY) : $(OBJS)
	$(LD) -O2 -rdynamic -o $@ $^

EXEC := $(BINARY) $(ARGS)
run-env : $(BINARY)

run : run-env
	$(EXEC)

gdb : run-env
	gdb -s $(BINARY) --args $(EXEC)

clean : 
	-rm $(ODIR)/*
