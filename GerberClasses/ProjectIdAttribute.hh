#ifndef _PROJECT_ID_ATTRIBUTE_H
#define _PROJECT_ID_ATTRIBUTE_H

#include "StandardAttribute.hh"

#include <string>

class ProjectIdAttribute : public StandardAttribute {
public:
	ProjectIdAttribute(std::string name,
					   std::string proj_name,
					   std::string guid,
					   std::string revision);
	virtual ~ProjectIdAttribute();

private:
	std::string m_proj_name;
	std::string m_guid;
	std::string m_revision;
};

#endif // _PROJECT_ID_ATTRIBUTE_H
