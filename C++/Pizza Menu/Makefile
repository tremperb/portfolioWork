CC = g++
exe_file = pizza_portal
$(exe_file): driver.o driver_functions.o menu.o pizza.o restaurant.o
	$(CC) driver.o driver_functions.o menu.o pizza.o restaurant.o -o $(exe_file)
driver.o: driver.cpp
	$(CC) -c driver.cpp
driver_functions.o: driver_functions.cpp
	$(CC) -c driver_functions.cpp
menu.o: menu.cpp
	$(CC) -c menu.cpp
pizza.o: pizza.cpp
	$(CC) -c pizza.cpp
restaurant.o: restaurant.cpp
	$(CC) -c restaurant.cpp
clean:
	rm -f *.out *.o $(exe_file)
