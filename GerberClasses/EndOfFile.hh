#ifndef _END_OF_FILE_H
#define _END_OF_FILE_H

#include "Command.hh"

#include <iostream>
#include <string>

class EndOfFile : public Command {
public:
	EndOfFile();
	~EndOfFile();

private:
	virtual bool do_check_semantic_validity(std::string& error_msg);
	virtual std::ostream& do_print(std::ostream& os) const;
};

#endif // _END_OF_FILE_H