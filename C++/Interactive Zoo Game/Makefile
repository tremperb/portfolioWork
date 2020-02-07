CC = g++
exe_file = zooTycoon
$(exe_file): driver.o zoo.o animal.o monkey.o meerkat.o Otter.o
	$(CC) driver.o zoo.o animal.o monkey.o meerkat.o Otter.o -o $(exe_file)
driver.o: driver.cpp
	$(CC) -c driver.cpp
zoo.o: zoo.cpp
	$(CC) -c zoo.cpp
animal.o: animal.cpp
	$(CC) -c animal.cpp
monkey.o: monkey.cpp
	$(CC) -c monkey.cpp
meerkat.o: meerkat.cpp
	$(CC) -c meerkat.cpp
Otter.o: Otter.cpp
	$(CC) -c Otter.cpp
clean:
	rm -f *.out *.o $(exe_file)
