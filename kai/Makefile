CPPFLAGS = -std=c++0x -fopenmp -lfltk_gl -lfftw3 -O2 -g
OBJEKTE = station.o district.o deck.o room.o wall.o door.o rect.o

dis: dis.cpp station.o
	g++ -o dis dis.cpp $(OBJEKTE)

clean:
	rm *.o dis

station.o: station.cpp station.hh district.o
	g++ -c station.cpp $(CPPFLAGS)

district.o: district.cpp district.hh deck.o
	g++ -c district.cpp $(CPPFLAGS)

deck.o: deck.cpp deck.hh room.o
	g++ -c deck.cpp $(CPPFLAGS)

room.o: room.cpp room.hh wall.o door.o rect.o
	g++ -c room.cpp $(CPPFLAGS)

wall.o: wall.cpp wall.hh door.o rect.o
	g++ -c wall.cpp $(CPPFLAGS)

door.o: door.cpp door.hh rect.o
	g++ -c door.cpp $(CPPFLAGS)

rect.o: rect.cpp rect.hh
	g++ -c rect.cpp $(CPPFLAGS)
