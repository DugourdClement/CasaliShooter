/**
 *
 * @file    cexception.h
 *
 * @authors M. Laporte, D. Mathieu
 *
 * @date    23/03/2010
 *
 * @version V1.0
 *
 * @brief   Declaration de la classe CException
 *
 * @version V1.1
 *
 * @author Alexandre Sollier
 *
 * @brief Ajout de la documentation
 *
 **/

#ifndef CEXCEPTION_H
#define CEXCEPTION_H

#include <string>
#include <iostream>
#include <exception>

#include "../tools/ieditable.h"
#include "errcode.h"

/**
 * @namespace nsException
 * @brief Espace de nom pour la gestion d'exceptions
 */
namespace nsException
{

/**
 * @class CException
 * @brief Classe pour créer des exceptions facilement
 */
class CException : public std::exception, public nsUtil::IEditable
{

public :
    /**
     * @brief Constructeur pour la classe CException
     * @param[in] Libelle : Libellé de l'exception
     * @param[in] CodErr : Code erreur de l'exception
     * @fn CException(const std::string& Libelle = std::string(), const unsigned CodErr = KNoExc);
     */
    CException(const std::string& Libelle = std::string(), const unsigned CodErr = KNoExc);

    /**
     * @brief Destructeur virtuel pour la classe CException
     * @fn virtual ~CException() override = default;
     */
    virtual ~CException() override = default;

    /**
     * @brief Récupère le libellé de l'exception
     * @fn const std::string& GetLibelle() const;
     */
    const std::string& GetLibelle() const;

    /**
     * @brief Récupère le code erreur de l'exception
     * @fn unsigned GetCodErr() const;
     */
    unsigned GetCodErr() const;

    /**
     * @brief Retourne une chaine de caractère C décrivant l'exception
     * @fn virtual const char* what() const noexcept override;
     */
    virtual const char* what() const noexcept override;

protected :
    virtual std::ostream& _Edit(std::ostream& os = std::cerr) const override;

    /**
     * @brief m_Libelle : Libellé de l'exception
     */
    std::string m_Libelle;

    /**
     * @brief m_CodErr : Code erreur de l'exception
     */
    unsigned m_CodErr;

}; // class CException
    
} // namespace nsException

#include "cexception.hpp"

#endif // CEXCEPTION_H

