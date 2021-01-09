# Makefiles
# matt russell
# comp15 2020 summer

# defines the compiler we're using
CXX=clang++
CXXFLAGS=-O2 -std=c++11

default: gerp
	
gerp: gerp.o IndexedDirectory.o
	$(CXX) $(CXXFLAGS) -o gerp gerp.o IndexedDirectory.o

gerp.o: gerp.cpp IndexedDirectory.h
	$(CXX) $(CXXFLAGS) -c gerp.cpp

IndexedDirectory.o: IndexedDirectory.cpp IndexedDirectory.h
	$(CXX) $(CXXFLAGS) -c IndexedDirectory.cpp

# clean destroys all the .o files
clean:
	-@rm -rf *.o 2>/dev/null
