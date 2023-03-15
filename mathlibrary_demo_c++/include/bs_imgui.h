
#ifndef __BS_IMGUI__
#define __BS_IMGUI__ 1

#include "imgui-SFML.h"
#include "imgui.h"
#include "imgui_stdlib.h"

#include "bs_database.h"
#include "imgui.h"

#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

#include <stdint.h>


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
    * @brief initialize imgui
    */
    void init(sf::RenderWindow& window);
    /**
    * @brief event imgui for sfml
    */
    void event(sf::Event event);
    /**
    * @brief update imgui
    */
    void update(sf::RenderWindow& window, sf::Clock clock, BsDataBase database);
    /**
    * @brief ends imgui
    */
    void end(sf::RenderWindow& window);

    // ATTRIBUTES
    uint8_t enabled_;
    std::string logged = "Not Logged In";
    std::string logged2 = "";

    bool structure_;
    bool login_;
    bool test_int_;
    bool test_float_;
    bool test_bool_;

    bool use_login_;

    std::string username_;
    std::string password_;
    std::string username_sign_;
    std::string password_sign_;
};


#endif // __BS_IMGUI__
