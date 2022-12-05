exercise01:	exercise01.cpp country.o city.o world-util.o
	g++ -std=c++23 -o exercise01 exercise01.cpp city.o country.o world-util.o

country.o: ../world/country.cpp 	
	g++ -std=c++23 -c ../world/country.cpp

city.o: ../world/city.cpp 	
	g++ -std=c++23 -c ../world/city.cpp

world-util.o: ../world/world-util.cpp 	
	g++ -std=c++23 -c ../world/world-util.cpp

clean: 
	rm -f *.o exercise01
