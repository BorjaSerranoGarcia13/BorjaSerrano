
#ifndef __BS_IMGUI__
#define __BS_IMGUI__ 1

#include "imgui-SFML.h"
#include "imgui.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <stdint.h>

/**
/* Class ImGui
/* manage the program to work with ImGui
*/
class BsImgui {
public:

    /**
   * @brief constructor of class
   */
    BsImgui();

    /**
    * @brief destructor of class
    */
    virtual ~BsImgui();

    BsImgui(const BsImgui& o) = delete;

    /**
    * @brief init a imgui window
    */
    void init(sf::RenderWindow& window);
    /**
    * @brief manage events imgui
    */
    void event(sf::Event event);
    /**
    * @brief updates imgui
    */
    void update(sf::RenderWindow& window, sf::Clock clock);
    /**
    * @brief ends imgui
    */
    void end(sf::RenderWindow& window);


    // ATTRIBUTES
    uint8_t enabled_;
};


#endif // __BS_IMGUI__
