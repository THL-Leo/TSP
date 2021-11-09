EXEC = graph stack path tsp
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:%.c=%.o)

CC = clang
CFLAGS = -Wall -Wextra -Werror -Wpedantic
LDFLAGS = -lm
PROGRAM = tsp
FILES = graph.o path.o stack.o tsp.o

all: $(PROGRAM)

$(PROGRAM): $(FILES)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(FILES) $(LDFLAGS)

clean: 
	rm -f $(PROGRAM) $(FILES)

format: 
	clang-format -i -style=file *.[ch]

scan-build: clean
	scan-build make     
