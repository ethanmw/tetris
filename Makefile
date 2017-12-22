CMP = g++ -std=c++11
FLAGX = -lX11
FLAGINC = -I/opt/X11/include
FLAGLIB = -L/opt/X11/lib
CLASS1 = Game
CLASS2= Tetrimino
MAIN = tetris
EXEC = $(MAIN)

$(EXEC): $(CLASS1).o $(CLASS2).o $(MAIN).o gfxnew.o
	$(CMP) $(FLAGX) $(FLAGINC) $(FLAGLIB) $(MAIN).o $(CLASS1).o $(CLASS2).o gfxnew.o -o $(EXEC)

$(CLASS1).o: $(CLASS1).cpp $(CLASS1).h $(CLASS2).h
	$(CMP) -c $(CLASS1).cpp -o $(CLASS1).o

$(CLASS2).o: $(CLASS2).cpp $(CLASS2).h
	$(CMP) -c $(CLASS2).cpp -o $(CLASS2).o

$(MAIN).o: $(MAIN).cpp $(CLASS1).h
	$(CMP) -c $(MAIN).cpp -o $(MAIN).o

gfxnew.o: gfxnew.c gfxnew.h
	$(CMP) -c gfxnew.c -o gfxnew.o

clean:
	rm $(EXEC) $(MAIN).o $(CLASS1).o $(CLASS2).o gfxnew.o
