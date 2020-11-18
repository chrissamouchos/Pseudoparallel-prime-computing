# Pseudoparallel-prime-computing
Compute prime numbers in space between [n,m], where n,m positive integers and n < m.

### Functions to be used
- exec****(): The exec family of functions replaces the current running process with a new process. It can be used to run a C program by using another C program. It comes under the header file unistd.h.
- mkfifo(): In computing, a named pipe (also known as a FIFO) is one of the methods for intern-process communication. It is an extension to the traditional pipe concept on Unix. A traditional pipe is “unnamed” and lasts only as long as the process. A named pipe, however, can last as long as the system is up, beyond the life of the process. It can be deleted if no longer used. Usually a named pipe appears as a file and generally processes attach to it for inter-process communication. A FIFO file is a special kind of file on the local storage which allows two or more processes to communicate with each other by reading/writing to/from this file. A FIFO special file is entered into the filesystem by calling mkfifo() in C. Once we have created a FIFO special file in this way, any process can open it for reading or writing, in the same way as an ordinary file. However, it has to be open at both ends simultaneously before you can proceed to do any input or output operations on it.
- pipe():Conceptually, a pipe is a connection between two processes, such that the standard output from one process becomes the standard input of the other process. In UNIX Operating System, Pipes are useful for communication between related processes(inter-process communication). Pipe is one-way communication only i.e we can use a pipe such that One process write to the pipe, and the other process reads from the pipe. It opens a pipe, which is an area of main memory that is treated as a “virtual file”. The pipe can be used by the creating process, as well as all its child processes, for reading and writing. One process can write to this “virtual file” or pipe and another related process can read from it.
If a process tries to read before something is written to the pipe, the process is suspended until something is written. The pipe system call finds the first two available positions in the process’s open file table and allocates them for the read and write ends of the pipe.
- open(): Used to Open the file for reading, writing or both.
- close(): Close an opened file.
- read(): Read an opened file.
- write(): Write to file.
- poll(): The poll() function provides applications with a mechanism for multiplexing input/output over a set of file descriptors. For each member of the array pointed to by fds, poll() shall examine the given file descriptor for the event(s) specified in events. The number of pollfd structures in the fds array is specified by nfds. The poll() function shall identify those file descriptors on which an application can read or write data, or on which certain events have occurred.
- wait(): A call to wait() blocks the calling process until one of its child processes exits or a signal is received. After child process terminates, parent continues its execution after wait system call instruction.
- kill(): The kill() function shall send a signal to a process or a group of processes specified by pid. The signal to be sent is specified by sig and is either one from the list given in <signal.h> or 0. If sig is 0 (the null signal), error checking is performed but no signal is actually sent. The null signal can be used to check the validity of pid.
- exit(): The C library function void exit(int status) terminates the calling process immediately. Any open file descriptors belonging to the process are closed and any children of the process are inherited by process 1, init, and the process parent is sent a SIGCHLD signal.

!
να δω τι κανει η select και η poll.
εχω floating point exception, δηλαδη έχω unexpected NaN or devision by zero, λογικα μεσα στην split n exec ή στην main του myprime. Να το τσεκαρω, επιπλεον έχω memory leak.

χρησιμοποιω miller rabin για witness a = 2. ομως αν ο αριθμος ειναι ισχυρα ψευδοπρωτος τοτε πρεπει να ελεγξω για μαρτυρα 2,3. Αναλυτικα απο το σαιτ της βικιπαιδεια ισχύει ότι:
- if n < 2,047, it is enough to test a = 2;
- if n < 1,373,653, it is enough to test a = 2 and 3;
- if n < 9,080,191, it is enough to test a = 31 and 73;
- if n < 25,326,001, it is enough to test a = 2, 3, and 5;
Επιπλέον ο μεγαλύτερος int που μπορει να αποθηκευτει ειναι ο 2,147,483,647. Επομένως πρεπει να φτιάξω το προγραμμα κατάλληλα για να μην βρισκω ισχυρα ψευδοπρωτους(strong pseudoprime)/