CC = g++
CFLAGS = -g -std=c++11
INCFLAGS = -I./include/
LDFLAGS = 

RM = /bin/rm -f
BUILDDIR = build
APPNAME = alas

all: createBuild alas
createBuild:
	mkdir -p $(BUILDDIR)
alas: main.o Parser.o Code.o Line.o Translator.o include/types.h
	$(CC) $(CFLAGS) -o $(APPNAME) $(BUILDDIR)/main.o $(BUILDDIR)/Parser.o $(BUILDDIR)/Code.o $(BUILDDIR)/Line.o $(BUILDDIR)/Translator.o $(INCFLAGS) $(LDFLAGS) 
main.o: main.cpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/main.o -c main.cpp
Parser.o: src/Parser.cpp include/Parser.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/Parser.o -c src/Parser.cpp

Code.o: src/Code.cpp include/Code.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/Code.o -c src/Code.cpp

Line.o: src/Line.cpp include/Line.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/Line.o -c src/Line.cpp

Translator.o: src/Translator.cpp include/Translator.hpp
	$(CC) $(CFLAGS) $(INCFLAGS) -o $(BUILDDIR)/Translator.o -c src/Translator.cpp


clean: 
clean: 
	$(RM) $(BUILDDIR)/*.o $(APPNAME)
	rmdir $(BUILDDIR)


 
