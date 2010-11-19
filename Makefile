OBJS = main.o

CC = g++
EXEC = graph
W_FLAGS = -Wall -Wextra -pedantic

FLAGS = -I . $(W_FLAGS)

%.o : %.cpp
	$(CC) $(FLAGS) -I$(BOOST_INC) -c $<

main: $(OBJS)
	@echo "Building $(EXEC)"
	$(CC) $(OBJS) $(FLAGS) -o $(EXEC)

tags:
	ctags -R .
		
clean:
	@echo "Cleaning all!"
	\rm -rf *.o *.out *.~ $(EXEC)

