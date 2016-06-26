CXX = g++
OPTIONS = -std=c++11 -O2 -DNDEBUG -D_GLIBCXX_DEBUG -Wall -Wextra -Werror -Wno-uninitialized -Wno-sign-compare -Wshadow

program.exe: Cita.o Biblio.o program.o Text.o
	$(CXX) -o $@ $^

program.o: program.cc
		$(CXX) -c $^ $(OPTIONS)

Cita.o: Cita.cc
	$(CXX) -c $^ $(OPTIONS)

Biblio.o: Biblio.cc
	$(CXX) -c $^ $(OPTIONS)

Text.o: Text.cc
	$(CXX) -c $^ $(OPTIONS)

practica.tar:
	tar -cvf practica.tar **.cc **.hh Makefile 

clean:
	rm *.o
	rm *.tar
	rm *.exe
