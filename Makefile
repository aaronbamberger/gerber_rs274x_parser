all: scanner_tester

clean:
	rm *.o

scanner_tester: scanner_tester.o gerber_scanner.yy.o
	gcc -g -o scanner_tester scanner_tester.o gerber_scanner.yy.o
	
scanner_tester.o: scanner_tester.c
	gcc -g -c scanner_tester.c -o scanner_tester.o

gerber_scanner.yy.o: gerber_scanner.yy.c gerber_scanner.yy.h
	gcc -g -c gerber_scanner.yy.c -o gerber_scanner.yy.o
	
gerber_scanner.yy.c: gerber_rs274x.l
	flex gerber_rs274x.l
	
gerber_scanner.yy.h: gerber_rs274x.l
	flex gerber_rs274x.l
