/*
 * Copyright 2021 Aaron Bamberger
 * Licensed under BSD 2-clause license
 * See LICENSE file at root of source tree,
 * or https://opensource.org/licenses/BSD-2-Clause
 */

#ifndef _APERTURE_MACRO_VARIABLE_ENVIRONMENT_H
#define _APERTURE_MACRO_VARIABLE_ENVIRONMENT_H

#include <unordered_map>

class ApertureMacroVariableEnvironment {
public:
    ApertureMacroVariableEnvironment();
    virtual ~ApertureMacroVariableEnvironment();

    void set_variable(int var_num, double value);
    double get_variable(int var_num);

private:
    std::unordered_map<int, double> m_variable_env;
};

#endif // _APERTURE_MACRO_VARIABLE_ENVIRONMENT_H
