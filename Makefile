OBJEKTE  = openglwidget.o openglbutton.o mausobjekt.o textur.o system.o texturensammlung.o textures.o station.o zone.o district.o deck.o room.o wall.o door.o rect.o
CPP      = g++-4.7
CPPFLAGS = -std=c++11 -g

main: main.cpp $(OBJEKTE)
	$(CPP) $(CPPFLAGS) -o main main.cpp $(OBJEKTE) -lGL -lGLU -lSDL -lSDL_image

dis: dis.cpp station.o
	$(CPP) $(CPPFLAGS) -o dis dis.cpp station.o zone.o district.o deck.o room.o wall.o door.o rect.o

system.o: system.hh system.cpp glhilf.h
	$(CPP) $(CPPFLAGS) -c system.cpp

openglwidget.o: openglwidget.cpp openglwidget.hh glhilf.h textur.o zeit.h station.o mausobjekt.o openglwidget_material.h openglwidget_events.h openglbutton.o
	$(CPP) $(CPPFLAGS) -c openglwidget.cpp

openglbutton.o: openglbutton.cpp openglbutton.hh
	$(CPP) -c openglbutton.cpp

textur.o: textur.cpp textur.hh
	$(CPP) $(CPPFLAGS) -c textur.cpp

texturensammlung.o: texturensammlung.cpp texturensammlung.hh textur.o
	$(CPP) $(CPPFLAGS) -c texturensammlung.cpp

textures.o: textures.cpp textures.hh
	$(CPP) $(CPPFLAGS) -c textures.cpp

mausobjekt.o: mausobjekt.cpp mausobjekt.hh
	$(CPP) $(CPPFLAGS) -c mausobjekt.cpp

station.o: station.cpp station.hh zone.o
	$(CPP) $(CPPFLAGS) -c station.cpp

zone.o: zone.cpp zone.hh district.o
	$(CPP) $(CPPFLAGS) -c zone.cpp

district.o: district.cpp district.hh deck.o mausobjekt.o
	$(CPP) $(CPPFLAGS) -c district.cpp

deck.o: deck.cpp deck.hh
	$(CPP) $(CPPFLAGS) -c deck.cpp

room.o: room.cpp room.hh wall.o door.o rect.o
	$(CPP) $(CPPFLAGS) -c room.cpp

wall.o: wall.cpp wall.hh door.o rect.o
	$(CPP) $(CPPFLAGS) -c wall.cpp

door.o: door.cpp door.hh rect.o
	$(CPP) $(CPPFLAGS) -c door.cpp

rect.o: rect.cpp rect.hh
	$(CPP) $(CPPFLAGS) -c rect.cpp

clear:
	rm *.o & rm *.gch & rm main
