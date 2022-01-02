#ifndef BGTEXT_H
#define BGTEXT_H

// On inclut l'en-tête de IDrawable et de ITransitionable
#include "MinGL/include/mingl/graphics/idrawable.h"
#include "MinGL/include/mingl/transition/itransitionable.h"

// Ici, les autres en-têtes utiles
#include "MinGL/include/mingl/gui/text.h"
#include "MinGL/include/mingl/shape/rectangle.h"

// La classe hérite de IDrawable et ITransitionable
class BgText: public nsGraphics::IDrawable, public nsTransition::ITransitionable
{

public:
    // On créé une enumeration pour les différents identifiants des propriétés transitionables
    enum TransitionIds {
        TRANSITION_TEXT_COLOR, /**< Transition pour la couleur du texte */
        TRANSITION_BACKGROUND_COLOR, /**< Transition pour la couleur de fond */
    };

    // Le constructeur de la classe, prenant les paramètres lors de l'instanciation
    BgText(const nsGraphics::Vec2D& position, const std::string& content, const nsGraphics::RGBAcolor& textColor, const nsGraphics::RGBAcolor& backgroundColor);

    // Ne pas oublier le destructeur virtuel
    virtual ~BgText() = default;

    // On surcharge la fonction draw() qui est appelée lors de l'affichage de notre objet
    virtual void draw(MinGL& window) const override;

    // On surcharge la fonction getValues() qui est appelée quand le gestionnaire de transition a besoin de connaitre la valeur d'une propriété
    virtual void getValues(const int &id, std::vector<float> &values) override;

    // On surcharge la fonction setValues() qui est appelée quand le gestionnaire de transition veut régler la valeur d'une propriété
    virtual void setValues(const int &id, const std::vector<float> &values) override;

private:
    // On met les variables membres ici
    nsGui::Text m_text;
    nsShape::Rectangle m_background;

};

#endif // BGTEXT_H
