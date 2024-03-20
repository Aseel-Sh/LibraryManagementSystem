library_management_system: main.o patroncollection.o bookcollection.o loancollection.o patron.o book.o loan.o
	g++ main.o patroncollection.o bookcollection.o loancollection.o patron.o book.o loan.o -o library_management_system

main.o: main.cpp patroncollection.h bookcollection.h loancollection.h patron.h book.h loan.h
	g++ -c main.cpp

patroncollection.o: patroncollection.cpp patroncollection.h patron.h
	g++ -c patroncollection.cpp

bookcollection.o: bookcollection.cpp bookcollection.h book.h
	g++ -c bookcollection.cpp

loancollection.o: loancollection.cpp loancollection.h loan.h book.h patron.h
	g++ -c loancollection.cpp

patron.o: patron.cpp patron.h
	g++ -c patron.cpp

book.o: book.cpp book.h
	g++ -c book.cpp

loan.o: loan.cpp loan.h
	g++ -c loan.cpp

clean:
	rm -f *.o library_management_system
