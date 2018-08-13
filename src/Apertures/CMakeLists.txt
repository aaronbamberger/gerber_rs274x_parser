set(APERTURE_SRCS
	Aperture.cc
	InstantiatedApertureMacro.cc
	StandardAperture.cc
	StandardApertureCircle.cc
	StandardApertureObround.cc
	StandardAperturePolygon.cc
	StandardApertureRectangle.cc
	)

add_library(AperturesLib ${APERTURE_SRCS})
