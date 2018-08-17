CXX=g++
CFLAGS=-Wall

main: main.o StandardCursor.o RichText.o CustomText.o
	$(CXX) main.o StandardCursor.o RichText.o CustomText.o -o main -lsfml-graphics -lsfml-window -lsfml-system -lX11

main.o:
	$(CXX) -Wno-psabi -c main.cpp

StandardCursor.o:
	$(CXX) -Wno-psabi -c Utilities/StandardCursor.cpp

RichText.o:
	$(CXX) -Wno-psabi -c Utilities/RichText.cpp

CustomText.o:
	$(CXX) -Wno-psabi -c Utilities/CustomText.cpp

clean: clean-RichText clean-main clean-CustomText
	rm -f main StandardCursor.o

clean-RichText:
	rm -f RichText.o

clean-main:
	rm -f main.o

clean-CustomText:
	rm -f CustomText.o
