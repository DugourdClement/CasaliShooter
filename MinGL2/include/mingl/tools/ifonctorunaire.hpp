#ifndef IFONCTORBINAIRE_HPP
#define IFONCTORBINAIRE_HPP

namespace nsUtil
{

/**
 * @class IFonctorUnaire
 * @brief Interface pour un fonctor unaire
 */
template<typename T1, typename TRes>
class IFonctorUnaire
{

public:
    /**
     * @brief Destructeur pour la classe IFonctorUnaire
     * @fn virtual ~IFonctorUnaire() = default;
     */
    virtual ~IFonctorUnaire() = default;

    /**
     * @brief Surcharge de l'opérateur d'appel
     * @param[in] in : Premier paramètre
     * @fn virtual TRes operator()(const T1& in) const = 0;
     */
    virtual TRes operator()(const T1& in) const = 0;

}; // class IFonctorUnaire

} // namespace nsUtil

#endif // IFONCTORBINAIRE_HPP
