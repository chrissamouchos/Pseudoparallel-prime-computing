# Pseudoparallel-prime-computing
Compute effectively prime numbers in space between [n,m], where n,m positive integers and n < m.

### Data structures and general application design
In this program a tree of processes is being created with height equal to 3. The root of the tree functions as the master process or coordinator, who is responsible for collecting data from the other nodes-processes. The inner nodes assemble the data collected from the leafs of the tree and sort them in an increasing order. The leafs perform fast and cost-effective computations for **single** prime numbers and for each execution the leaf restarts its procedure with respect to the previous number found. Although a degree of multi-programming is achieved, the whole structure does not simulate an authentic parallel system, because it is designed for computer architectures with one processing core.
For the organisation of the data due to asychronous computations between the processes a sorted simple linked list is being used.
The communication of the processes is being achieved via a set of named pipes for reading and writing respectively.
Additionally, a signal handler is being used for recording when a leaf-process terminated normally or unexpectetdly.

### Prime computation
According to Miller Rabin algorithm (implemented and used in leaf process) a witness number is needed. Arbitary i chose a = 2. However if the number is strongly pseudo-random, then another witness should be chosen. With more detail, for the algorithm to work properly there are 4 options:
- if n < 2,047, it is enough to test a = 2;
- if n < 1,373,653, it is enough to test a = 2 and 3;
- if n < 9,080,191, it is enough to test a = 31 and 73;
- if n < 25,326,001, it is enough to test a = 2, 3, and 5;

### Note
A further optimazition would be the implementation of a small program, that checks if "current" number if strongly pseudo-random.