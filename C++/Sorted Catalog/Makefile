CC = g++
exe_file = catalog
$(exe_file): catalog.o run_wizard.o
	$(CC) catalog.o run_wizard.o -o $(exe_file)
catalog.o: catalog.cpp
	$(CC) -c catalog.cpp
run_wizard.o: run_wizard.cpp
	$(CC) -c run_wizard.cpp
clean:
	rm -f *.out *.o $(exe_file)
