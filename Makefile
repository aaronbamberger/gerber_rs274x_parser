all: scanner_tester

clean:
	rm *.o *.yy.*

scanner_tester: scanner_tester.o gerber_scanner.yy.o gerber_parser.yy.o
	gcc -g -o scanner_tester scanner_tester.o gerber_scanner.yy.o gerber_parser.yy.o
	
scanner_tester.o: scanner_tester.c gerber_scanner.yy.h gerber_parser.yy.h
	gcc -g -c scanner_tester.c -o scanner_tester.o

gerber_scanner.yy.o: gerber_scanner.yy.c gerber_scanner.yy.h gerber_parser.yy.h gerber_scanner_defs.h
	gcc -g -c gerber_scanner.yy.c -o gerber_scanner.yy.o

gerber_parser.yy.o: gerber_parser.yy.c gerber_parser.yy.h gerber_scanner.yy.h gerber_parser_defs.h
	gcc -g -c gerber_parser.yy.c -o gerber_parser.yy.o
	
gerber_scanner.yy.c: gerber_rs274x.l
	flex gerber_rs274x.l
	
gerber_scanner.yy.h: gerber_rs274x.l
	flex gerber_rs274x.l

gerber_parser.yy.c: gerber_rs274x.y
	bison gerber_rs274x.y

gerber_parser.yy.h: gerber_rs274x.y
	bison gerber_rs274x.y
