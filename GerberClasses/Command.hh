#ifndef _COMMAND_H
#define _COMMAND_H

#include <string>
#include <iostream>

class Command {
public:
	Command();
	virtual ~Command();

	bool check_semantic_validity(std::string& error_msg);
	friend std::ostream& operator<<(std::ostream& os, const Command& cmd);

protected:
	virtual bool do_check_semantic_validity(std::string& error_msg) = 0;

private:
	virtual std::ostream& do_print(std::ostream& os) const = 0;
};

std::ostream& operator<<(std::ostream& os, const Command& cmd)
{
	return cmd.do_print(os);
}

#endif // _COMMAND_H