IDIR=include
CC=g++ -std=c++20
CFLAGS=-I$(IDIR)
PFLAG=-pthread

ODIR =obj
SRCDIR =src
TESTDIR =test

LIBS=-lsfml-graphics -lsfml-window -lsfml-system

_DEPS = Entry.hpp Tree.hpp Complex.hpp Stack.hpp Mandelbrot.hpp Utilities.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ =  Entry.o Tree.o Complex.o Stack.o Mandelbrot.o Utilities.o main.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

DEBUG_OBJ = $(patsubst %,$(ODIR)/debug_%,$(_OBJ))

$(ODIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(ODIR)/debug_%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -g -o $@ $< $(CFLAGS)

compile: $(OBJ)
	$(CC) -o $(ODIR)/main.app $^ $(PFLAG) $(CFLAGS) $(LIBS)

debug: $(DEBUG_OBJ)
	$(CC) -g -o $(ODIR)/$@_main.app $^ $(PFLAG) $(CFLAGS) $(LIBS)
	gdb $(ODIR)/$@_main.app

run:
	./$(ODIR)/main.app test/log_file.txt

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(ODIR)/*.app *~ core $(INCDIR)/*~

.PHONY: debug_clean

debug_clean:
	rm -f $(ODIR)/debug_*

.PHONY: count

count:
	find . -name '*.[hc]pp' -o -name 'makefile' -o -name 'README.md' -o -name '.gitignore' | xargs wc -l