all: scanner_tester

clean:
	rm *.o *.yy.*

scanner_tester: scanner_tester.o gerber_scanner.yy.o gerber_parser.yy.o gerber_rs274x_scanner.o
	g++ -g -o scanner_tester scanner_tester.o gerber_scanner.yy.o gerber_parser.yy.o gerber_rs274x_scanner.o
	
scanner_tester.o: scanner_tester.c gerber_scanner.yy.hh gerber_parser.yy.h gerber_rs274x_scanner.hh
	g++ -g -c scanner_tester.c

gerber_scanner.yy.o: gerber_scanner.yy.cc gerber_scanner.yy.hh gerber_parser.yy.h
	g++ -g -c gerber_scanner.yy.cc

gerber_parser.yy.o: gerber_parser.yy.c gerber_parser.yy.h gerber_scanner.yy.hh gerber_parser_defs.h
	g++ -g -c gerber_parser.yy.c

gerber_rs274x_scanner.o: gerber_rs274x_scanner.cc gerber_rs274x_scanner.hh
	g++ -g -c gerber_rs274x_scanner.cc
	
gerber_scanner.yy.cc: gerber_rs274x.l
	flex gerber_rs274x.l
	
gerber_scanner.yy.hh: gerber_rs274x.l
	flex gerber_rs274x.l

gerber_parser.yy.c: gerber_rs274x.y
	bison gerber_rs274x.y

gerber_parser.yy.h: gerber_rs274x.y
	bison gerber_rs274x.y
