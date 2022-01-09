/**
 *
 * @file    cexception.hpp
 *
 * @authors M. Laporte, D. Mathieu
 *
 * @date    23/03/2010
 *
 * @version V1.0
 *
 * @brief   classe CException
 *
 * @version V1.1
 *
 * @author Alexandre Sollier
 *
 * @brief Documentation complétée
 *
 **/

#ifndef CEXCEPTION_HPP
#define CEXCEPTION_HPP

#include <string>

#include "cexception.h"

inline nsException::CException::CException(const std::string& Libelle /* = std::string () */, const unsigned CodErr  /* = KNoExc */)
    : m_Libelle (Libelle)
    , m_CodErr (CodErr)
{} // CException()

inline const std::string& nsException::CException::GetLibelle() const
{
    return m_Libelle;
} // GetLibelle()

inline unsigned nsException::CException::GetCodErr() const
{
    return m_CodErr;
} // GetCoderr()

inline const char* nsException::CException::what() const noexcept
{
    return m_Libelle.c_str();
} // what()

#endif // CEXCEPTION_HPP

