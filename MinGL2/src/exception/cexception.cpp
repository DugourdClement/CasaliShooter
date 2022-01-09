/**
 *
 * @file    cexception.cpp
 *
 * @authors M. Laporte, D. Mathieu
 *
 * @date    23/03/2010
 *
 * @version V1.0
 *
 * @brief  classe CException
 *
 **/

#include <iostream>

#include "mingl/exception/cexception.h"

std::ostream& nsException::CException::_Edit(std::ostream& os) const
{ 
    return os << "Exception : " << m_Libelle << '\n'
              << "Code      : " << m_CodErr;
} // _Edit()

