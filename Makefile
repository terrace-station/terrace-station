OBJEKTE  = openglwidget.o openglbutton.o openglmenu.o mausobjekt.o system.o textures.o station.o zone.o district.o deck.o room.o door.o rect.o tile.o modell.o fonttextures.o models.o lights.o lamp.o
CPP      = g++-4.7
CPPFLAGS = -std=c++11 -O2 -g

main: main.cpp $(OBJEKTE)
	$(CPP) $(CPPFLAGS) -o main main.cpp $(OBJEKTE) -lGL -lGLU -lSDL -lSDL_image -lSDL_ttf

dis: dis.cpp station.o
	$(CPP) $(CPPFLAGS) -o dis dis.cpp station.o zone.o district.o deck.o room.o door.o rect.o tile.o

system.o: system.hh system.cpp glhilf.h
	$(CPP) $(CPPFLAGS) -c system.cpp

openglwidget.o: openglwidget.cpp openglwidget.hh glhilf.h zeit.h station.o mausobjekt.o openglwidget_material.h openglwidget_events.h openglwidget_zeichne.h openglbutton.o openglmenu.o modell.o fonttextures.o textures.o tile.o callback_funktionen.h models.o lights.o lamp.o
	$(CPP) $(CPPFLAGS) -c openglwidget.cpp

openglbutton.o: openglbutton.cpp openglbutton.hh
	$(CPP) $(CPPFLAGS) -c openglbutton.cpp

lamp.o: lamp.cpp lamp.hh
	$(CPP) $(CPPFLAGS) -c lamp.cpp

openglmenu.o: openglmenu.cpp openglmenu.hh openglbutton.o
	$(CPP) $(CPPFLAGS) -c openglmenu.cpp

lights.o: lights.cpp lights.hh
	$(CPP) $(CPPFLAGS) -c lights.cpp

modell.o: modell.cpp modell.hh
	$(CPP) $(CPPFLAGS) -c modell.cpp

models.o: models.cpp models.hh modell.o
	$(CPP) $(CPPFLAGS) -c models.cpp

textures.o: textures.cpp textures.hh
	$(CPP) $(CPPFLAGS) -c textures.cpp

fonttextures.o: fonttextures.cpp fonttextures.hh
	$(CPP) $(CPPFLAGS) -c fonttextures.cpp

mausobjekt.o: mausobjekt.cpp mausobjekt.hh
	$(CPP) $(CPPFLAGS) -c mausobjekt.cpp

station.o: station.cpp station.hh zone.o
	$(CPP) $(CPPFLAGS) -c station.cpp

zone.o: zone.cpp zone.hh district.o
	$(CPP) $(CPPFLAGS) -c zone.cpp

district.o: district.cpp district.hh deck.o mausobjekt.o
	$(CPP) $(CPPFLAGS) -c district.cpp

deck.o: deck.cpp deck.hh room.o
	$(CPP) $(CPPFLAGS) -c deck.cpp

room.o: room.cpp room.hh door.o rect.o lamp.o
	$(CPP) $(CPPFLAGS) -c room.cpp

door.o: door.cpp door.hh rect.o
	$(CPP) $(CPPFLAGS) -c door.cpp

rect.o: rect.cpp rect.hh
	$(CPP) $(CPPFLAGS) -c rect.cpp

tile.o: tile.cpp tile.hh
	$(CPP) $(CPPFLAGS) -c tile.cpp

clear:
	rm *.o -f
	rm *.gch -f
	rm main -f
