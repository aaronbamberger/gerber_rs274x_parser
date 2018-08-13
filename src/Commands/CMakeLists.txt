set(COMMAND_SRCS
	ApertureDefinition.cc
	ApertureDefinitionCustom.cc
	ApertureDefinitionModifier.cc
	ApertureDefinitionStandard.cc
	ApertureMacro.cc
	Command.cc
	Comment.cc
	DCommand.cc
	EndOfFile.cc
	FormatSpecifier.cc
	GCommand.cc
	LevelPolarity.cc
	SelectApertureCommand.cc
	StepAndRepeat.cc
	UnitSpecifier.cc
	)

add_library(CommandsLib ${COMMAND_SRCS})

target_link_libraries(CommandsLib ApertureMacrosLib AperturesLib)
