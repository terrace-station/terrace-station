OBJEKTE  = openglwidget.o mausobjekt.o textur.o system.o texturensammlung.o textures.o station.o district.o deck.o room.o wall.o door.o rect.o
CPP      = g++
CPPFLAGS = -g

main: main.cpp $(OBJEKTE)
	$(CPP) $(CPPFLAGS) -o main main.cpp $(OBJEKTE) -lGL -lGLU -lSDL -lSDL_image

dis: dis.cpp station.o
	$(CPP) $(CPPFLAGS) -o dis dis.cpp station.o district.o deck.o room.o wall.o door.o rect.o

system.o: system.hh system.cpp glhilf.h
	$(CPP) $(CPPFLAGS) -c system.cpp

openglwindow.o: openglwindow.cpp openglwindow.hh openglwidget.o
	$(CPP) -c openglwindow.cpp $(CPPFLAGS)

openglwidget.o: openglwidget.cpp openglwidget.hh glhilf.h textur.o zeit.h
	$(CPP) -c openglwidget.cpp $(CPPFLAGS)

textur.o: textur.cpp textur.hh
	$(CPP) -c textur.cpp $(CPPFLAGS)

texturensammlung.o: texturensammlung.cpp texturensammlung.hh textur.o
	$(CPP) -c texturensammlung.cpp $(CPPFLAGS)

textures.o: textures.cpp textures.hh
	$(CPP) -c textures.cpp $(CPPFLAGS) 

mausobjekt.o: mausobjekt.cpp mausobjekt.hh
	$(CPP) -c mausobjekt.cpp $(CPPFLAGS)

station.o: station.cpp station.hh district.o
	$(CPP) -c station.cpp $(CPPFLAGS)

district.o: district.cpp district.hh deck.o
	$(CPP) -c district.cpp $(CPPFLAGS)

deck.o: deck.cpp deck.hh
	$(CPP) -c deck.cpp $(CPPFLAGS)

room.o: room.cpp room.hh wall.o door.o rect.o
	$(CPP) -c room.cpp $(CPPFLAGS)

wall.o: wall.cpp wall.hh door.o rect.o
	$(CPP) -c wall.cpp $(CPPFLAGS)

door.o: door.cpp door.hh rect.o
	$(CPP) -c door.cpp $(CPPFLAGS)

rect.o: rect.cpp rect.hh
	$(CPP) -c rect.cpp $(CPPFLAGS)

clear:
	rm *.o & rm *.gch & rm main
