CC = gcc
CFLAGS = -g -Wall

# typing 'make' will invoke the first target entry in the file
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#

default: lmp


# To create the executable file iamroot we need the object files
# lmp.o, binaryTree.o and xx.o:
#

lmp: lmp.o binaryTree.o
	$(CC) $(CFLAGS) -o lmp lmp.o binaryTree.o

lmp.o: lmp.c lmp.h binaryTree.h
	$(CC) $(CFLAGS) -c lmp.c

binaryTree.o: binaryTree.c binaryTree.h
	$(CC) $(CFLAGS) -c binaryTree.c


# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#

clean:
	$(RM) lmp *.o *~