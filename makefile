# paths
INCLUDE_PATH = ./include
SRC_PATH = ./src
OBJS_PATH = ./bin
INPUT = ./input

#Define the compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -I$(INCLUDE_PATH) -pg

#Define the dependencies
PDEP = root.c 			#Primary dependencies
SDEP = inner_node.c 	#Secondary dependencies

#Create the .o file with the needed functions
POBJS = $(patsubst %.c,$(OBJS_PATH)/%.o,$(PDEP))	#For primary program
SOBJS = $(patsubst %.c,$(OBJS_PATH)/%.o,$(SDEP))	#For Secondary program

#UNLEASH THE FUll POWER OF VALGRIND!!!
FULLVAL = --leak-check=full -v

# The executable programms
PEXEC = myprime		#Primary program
SEXEC = inner_node 	#Secondary program

#Compile all three main executables
build : $(PEXEC) $(SEXEC)

#Compile Primary Executable
$(PEXEC): $(POBJS) $(INNER_NODE)
	$(CC) $(POBJS) -o $(PEXEC) $(CFLAGS)

#Create all object independently
$(OBJS_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) -c $^ -o $@ $(CFLAGS)

#Compile Secondary Executable
$(SEXEC): $(SOBJS)
	$(CC) $(SOBJS) -o $(SEXEC) $(CFLAGS)

#Run the programm
run: $(PEXEC) $(SEXEC)
	./$(PEXEC)

#Determine full valgrind
fvalgrind: $(PEXEC)
	valgrind $(FULLVAL) ./$(PEXEC)

#Determine simple valgrind
svalgrind: $(PEXEC)
	valgrind ./$(PEXEC) 

#Profiling for executed code, then show analysis on shell
profiling:
	{ \
	gprof $(PEXEC) gmon.out > analysis.txt;\
	cat analysis.txt;\
	rm -f gmon.out;\
	}

#Clean workspace, delete all executables and gmon files
clean:
	{ \
	rm -f $(SOBJS) $(POBJS) $(PEXEC) $(SEXEC);\
	rm -f gmon.out;  \
	}
