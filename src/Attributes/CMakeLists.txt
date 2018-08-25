set(ATTRIBUTES_SRCS
	Attribute.cc
	StandardAttribute.cc
	PartAttribute.cc
	FileFunctionAttribute.cc
	FilePolarityAttribute.cc
	SameCoordinatesAttribute.cc
	CreationDateAttribute.cc
	GenerationSoftwareAttribute.cc
   )


add_library(AttributesLib ${ATTRIBUTES_SRCS})

target_link_libraries(AttributesLib UtilLib)
