CC = gcc
CXX = g++
CXXFLAGS = -std=c++11
BISON = bison
BISONFLAGS = --warnings=none
FLEX = flex
MAKE = make

all: scanner_tester

clean:
	rm -rf *.o *.yy.*
	$(MAKE) -C GerberClasses/ clean

scanner_tester: scanner_tester.o gerber_scanner.yy.o gerber_parser.yy.o gerber_rs274x_scanner.o gerber_classes
	$(CXX) $(CXXFLAGS) -g -o scanner_tester scanner_tester.o gerber_scanner.yy.o gerber_parser.yy.o gerber_rs274x_scanner.o
	
scanner_tester.o: scanner_tester.c gerber_scanner.yy.hh gerber_parser.yy.hh gerber_rs274x_scanner.hh
	$(CXX) $(CXXFLAGS) -g -c scanner_tester.c

gerber_scanner.yy.o: gerber_scanner.yy.cc gerber_scanner.yy.hh gerber_parser.yy.hh
	$(CXX) $(CXXFLAGS) -g -c gerber_scanner.yy.cc

gerber_parser.yy.o: gerber_parser.yy.cc gerber_parser.yy.hh gerber_scanner.yy.hh gerber_parser_defs.h
	$(CXX) $(CXXFLAGS) -g -c gerber_parser.yy.cc

gerber_rs274x_scanner.o: gerber_rs274x_scanner.cc gerber_rs274x_scanner.hh
	$(CXX) $(CXXFLAGS) -g -c gerber_rs274x_scanner.cc
	
gerber_scanner.yy.cc: gerber_rs274x.l
	$(FLEX) gerber_rs274x.l
	
gerber_scanner.yy.hh: gerber_rs274x.l
	$(FLEX) gerber_rs274x.l

gerber_parser.yy.cc: gerber_rs274x.y
	$(BISON) $(BISONFLAGS) gerber_rs274x.y

gerber_parser.yy.hh: gerber_rs274x.y
	$(BISON) $(BISONFLAGS) gerber_rs274x.y

gerber_classes:
	$(MAKE) -C GerberClasses/