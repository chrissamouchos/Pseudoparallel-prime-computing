# paths
INCLUDE_PATH = ./include
SRC_PATH = ./src
OBJS_PATH = ./bin

#Shared .o file
SHAREDOBJS = Utils.o

#Define the compiler
CC = gcc

# Compile options. Το -I<dir> λέει στον compiler να αναζητήσει εκεί include files
CFLAGS = -I$(INCLUDE_PATH) -pg

#Define the dependencies
PDEP =	root.c \
		Utils.c		#Primary dependencies
SDEP = inner_node.c \
		Records.c 	#Secondary dependencies
DEP = leaf.c 		#Third-party dependencies

#Create the .o file with the needed functions
POBJS = $(patsubst %.c,$(OBJS_PATH)/%.o,$(PDEP))							#For primary program
SOBJS = $(patsubst %.c,$(OBJS_PATH)/%.o,$(SDEP) $(OBJS_PATH)/$(SHAREDOBJS))	#For Secondary program
TOBJS = $(patsubst %.c,$(OBJS_PATH)/%.o,$(DEP))	#For Secondary program

#UNLEASH THE FUll POWER OF VALGRIND!!!
FULLVAL = --leak-check=full -v

# The executable programms
PEXEC = myprime		#Primary program
SEXEC = inner_node 	#Secondary program
TEXEC = leaf		#Third-party program

#Compile all three main executables
build : $(PEXEC) $(SEXEC) $(TEXEC)

#Compile Primary Executable
$(PEXEC): $(POBJS) $(SEXEC)
	$(CC) $(POBJS) -o $(PEXEC) $(CFLAGS)

#Create all objects independently
$(OBJS_PATH)/%.o: $(SRC_PATH)/%.c
	$(CC) -c $^ -o $@ $(CFLAGS)

#Compile Secondary Executable
$(SEXEC): $(SOBJS) $(TEXEC)
	$(CC) $(SOBJS) -o $(SEXEC) $(CFLAGS)

#Compile Third-party executable
$(TEXEC): $(TOBJS)
	$(CC) $(TOBJS) -o $(TEXEC) $(CFLAGS)

#Run the program
run: $(PEXEC) $(SEXEC) $(TEXEC)
	./$(PEXEC) -l 0 -u 12 -w 3

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
	rm -f $(SOBJS) $(POBJS) $(TOBJS) $(PEXEC) $(SEXEC) $(TEXEC);\
	rm -f gmon.out;  \
	}