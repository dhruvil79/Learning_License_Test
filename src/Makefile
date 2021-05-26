# you can put include files in this directory
IDIR =../include
CC=gcc
CFLAGS=-I$(IDIR)

# directory where object files will be created
ODIR=obj
# you can put library files in this directory
LDIR =../lib
# looks for library libm.so or libm.a
LIBS=-lm

# create string with ../include/<header filename> in our case ../include/myheader.h
_DEPS = myheader.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# create string with obj/<object filename> in our case obj/hellomake.o and obj/hellofunc.o  (obj folder will be created under current i.e. source directory)
_OBJ = Answer_key.o Question_Bank.o project_parent.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
project_parent.out: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
	
.PHONY: clean

# removes object files and temporary files created with ~ at the end of file name in current i.e. source and include directory
clean: 
	rm -f $(ODIR)/*.o   *~ core $(INCDIR)/*~
	rm -f ./*.out
