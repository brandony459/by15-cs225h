CPP=clang++
CPPFLAGS=-fopenmp -std=c++17
LD=clang++
LDFLAGS=-fopenmp -std=c++17 -lomp


openmp : /workspaces/cs225git/cs225h/openmp/openmp.cpp
	$(CPP) $(LDFLAGS) /workspaces/cs225git/cs225h/openmp/openmp.cpp -o ompexample2

la_test: la_test.o la.o
	$(LD) $(LDFLAGS) la_test.o la.o -o la_test

la.o : /workspaces/cs225git/cs225h/openmp/la.cpp /workspaces/cs225git/cs225h/openmp/la.h
	$(CPP) $(CPPFLAGS) -c /workspaces/cs225git/cs225h/openmp/la.cpp -o la.o

la_test.o : /workspaces/cs225git/cs225h/openmp/la_test.cpp /workspaces/cs225git/cs225h/openmp/la.h
	$(CPP) $(CPPFLAGS) -c /workspaces/cs225git/cs225h/openmp/la_test.cpp -o la_test.o

clean : 
	rm -rf *.o ompexample pi la_test a.out