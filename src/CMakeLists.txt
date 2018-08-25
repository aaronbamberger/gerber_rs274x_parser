add_subdirectory(ApertureMacros)
add_subdirectory(Apertures)
add_subdirectory(Attributes)
add_subdirectory(Commands)
add_subdirectory(Util)

find_package(BISON REQUIRED)
bison_target(GerberParser
			 gerber_rs274x.y
			 ${CMAKE_CURRENT_BINARY_DIR}/gerber_parser.yy.cc
			 DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/gerber_parser.yy.hh
			 )

find_package(FLEX REQUIRED)
flex_target(GerberScanner
			gerber_rs274x.l
			${CMAKE_CURRENT_BINARY_DIR}/gerber_scanner.yy.cc
			DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/gerber_scanner.yy.hh
			)

add_flex_bison_dependency(GerberScanner GerberParser)

add_library(ScannerParserLib
			${BISON_GerberParser_OUTPUT_SOURCE}
			${FLEX_GerberScanner_OUTPUTS}
		   )

target_link_libraries(ScannerParserLib
					  ApertureMacrosLib
					  AperturesLib
					  CommandsLib
					 )

set(OTHER_SRCS
 	CommandList.cc
	CoordinateData.cc
	gerber_rs274x_scanner.cc
	GraphicsState.cc
	SemanticIssue.cc
	SemanticIssueList.cc
   )

add_library(OtherLib ${OTHER_SRCS})

target_link_libraries(OtherLib ScannerParserLib)

add_executable(ScannerTester scanner_tester.cc)

target_link_libraries(ScannerTester
					  ApertureMacrosLib
					  AperturesLib
					  AttributesLib
					  CommandsLib
					  ScannerParserLib
					  OtherLib
					  UtilLib
					 )

# Pretty much all of the other code uses headers that are generated as a result
# of generating the lexer and parser.  Therefore, make the ScannerParser library
# a dependency of all of the other code, to make sure these headers get generated
# before they're needed
add_dependencies(ApertureMacrosLib ScannerParserLib)
add_dependencies(AperturesLib ScannerParserLib)
add_dependencies(CommandsLib ScannerParserLib)
add_dependencies(OtherLib ScannerParserLib)
add_dependencies(UtilLib ScannerParserLib)
add_dependencies(AttributesLib ScannerParserLib)
