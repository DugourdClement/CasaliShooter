/**
 *
 * @file    event.hpp
 * @author  Alexandre Sollier
 * @date    Décembre 2019
 * @version 1.0
 * @brief   Différents types utile pour le gestionnaire d'événements
 *
 **/

#ifndef EVENT_HPP
#define EVENT_HPP

/**
 * @namespace nsEvent
 * @brief Espace de nom pour la gestion d'événements
 */
namespace nsEvent {

/**
 * @brief EventType_t : Liste de tout les types d'événements
 */
enum EventType_t {
    MouseClick, /**< L'utilisateur a cliqué sur un des boutons de la souris */
    MouseMove /**< Le curseur s'est déplacé */,
    MouseDrag, /**< Le curseur s'est déplacé pendant qu'un des boutons de la souris était pressé */
};

/**
 * @struct MouseClickData_t
 * @brief Possède des données pour un événement MouseClick
 */
struct MouseClickData_t {
    int button; /**< ID numérique du bouton */
    int state; /**< Nouvel état du bouton */
    int x; /**< Coordonnée X du curseur, relative au coin supérieur-gauche de la fenêtre */
    int y; /**< Coordonnée Y du curseur, relative au coin supérieur-gauche de la fenêtre */
};

/**
 * @struct MouseMoveData_t
 * @brief Possède des données pour un événement MouseMove/MouseDrag
 */
struct MouseMoveData_t {
    int x; /**< Coordonnée X du curseur, relative au coin supérieur-gauche de la fenêtre */
    int y; /**< Coordonnée Y du curseur, relative au coin supérieur-gauche de la fenêtre */
};

/**
 * @union EventData_t
 * @brief Union contenant les données d'un événement
 */
union EventData_t {
    MouseClickData_t clickData; /**< Données pour un événement MouseClick */
    MouseMoveData_t moveData; /**< Données pour un événment MouseMove/MouseDrag */
};

/**
 * @struct Event_t
 * @brief Possède des données pour un événement
 */
struct Event_t {
    EventType_t eventType; /**< Type de l'événement */
    EventData_t eventData; /**< Données de l'événement */
};

} // namespace nsEvent

#endif // EVENT_HPP
