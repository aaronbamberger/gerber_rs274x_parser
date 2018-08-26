#include "Attributes/ProjectIdAttribute.hh"

ProjectIdAttribute::ProjectIdAttribute(ValueWithLocation<std::string> name,
									   ValueWithLocation<std::string> proj_name,
									   ValueWithLocation<std::string> guid,
									   ValueWithLocation<std::string> revision) :
	StandardAttribute(name), m_proj_name(proj_name), m_guid(guid), m_revision(revision)
{}

ProjectIdAttribute::~ProjectIdAttribute()
{}
