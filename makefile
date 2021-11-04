IDIR=include
CC=g++
CFLAGS=-I$(IDIR)

ODIR =obj
SRCDIR =src


LIBS=-lsfml-graphics -lsfml-window -lsfml-system

_DEPS = Complex.hpp Mandelbrot.hpp Entry.hpp Tree.hpp Map.hpp
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = Complex.o Mandelbrot.o main.o Entry.o Tree.o Map.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: $(SRCDIR)/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

compile: $(OBJ)
	$(CC) -o $(ODIR)/main.app $^ $(CFLAGS) $(LIBS)

run:
	./$(ODIR)/main.app

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o $(ODIR)/*.app *~ core $(INCDIR)/*~
