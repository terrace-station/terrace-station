OBJEKTE  = openglwidget.o openglwindow.o mausobjekt.o textur.o targetinfomenu.o system.o texturensammlung.o deck.o district.o station.o
CPP      = g++
CPPFLAGS = -g

main: main.cpp $(OBJEKTE)
	$(CPP) $(CPPFLAGS) -o main main.cpp $(OBJEKTE) -lGL -lGLU -lfltk_gl -lfltk

system.o: system.hh system.cpp glhilf.h
	$(CPP) $(CPPFLAGS) -c system.cpp

openglwindow.o: openglwindow.cpp openglwindow.hh openglwidget.o
	g++ -c openglwindow.cpp $(CPPFLAGS)

openglwidget.o: openglwidget.cpp openglwidget.hh glhilf.h textur.o zeit.h
	g++ -c openglwidget.cpp $(CPPFLAGS)

textur.o: textur.cpp textur.hh
	g++ -c textur.cpp $(CPPFLAGS)

texturensammlung.o: texturensammlung.cpp texturensammlung.hh textur.o
	g++ -c texturensammlung.cpp $(CPPFLAGS)

mausobjekt.o: mausobjekt.cpp mausobjekt.hh
	g++ -c mausobjekt.cpp $(CPPFLAGS)

targetinfomenu.o: targetinfomenu.cpp targetinfomenu.hh mausobjekt.o
	g++ -c targetinfomenu.cpp $(CPPFLAGS)

station.o: station.cpp station.hh district.o
	g++ -c station.cpp $(CPPFLAGS)

district.o: district.cpp district.hh deck.o
	g++ -c district.cpp $(CPPFLAGS)

deck.o: deck.cpp deck.hh
	g++ -c deck.cpp $(CPPFLAGS)

clear:
	rm *.o & rm *.gch & rm main
