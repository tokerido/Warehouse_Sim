all: clean compile link

link:
	g++ -o bin/BaseAction.o bin/Customer.o bin/Order.o bin/Volunteer.o bin/WareHouse.o bin/Parse.o bin/main.o

compile:
	g++ -g -Wall -Weffc++ -c -o bin/BaseAction.o src/Action.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Customer.o src/Customer.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Order.o src/Order.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Volunteer.o src/Volunteer.cpp
	g++ -g -Wall -Weffc++ -c -o bin/WareHouse.o src/WareHouse.cpp
	g++ -g -Wall -Weffc++ -c -o bin/Parse.o src/Parse.cpp
	g++ -g -Wall -Weffc++ -c -o bin/main.o src/main.cpp
clean:
	rm -f bin/*