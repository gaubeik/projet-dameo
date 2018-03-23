dameo: plateau.o cpp/main.cpp
		g++ plateau.o cpp/main.cpp -o dameo

#jeux.o: plateau.o cpp/jeux.cpp header/jeux.h
#		g++ -c cpp/jeux.cpp plateau.o -o jeux.o

plateau.o: header/plateau.h cpp/plateau.cpp pion.o
		g++ -c cpp/plateau.cpp pion.o -o plateau.o

pion.o: header/pion.h cpp/pion.cpp 
		g++ -c cpp/pion.cpp -o pion.o
