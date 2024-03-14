#pragma once
#include <SFML/Graphics.hpp>

class Resources
{
public:
    static Resources& getResources();
    
    sf::Font font;
    
private:
    Resources();
    Resources(const Resources&) = delete;
    void operator=(const Resources&) = delete;
    
    static Resources* m_instance;
};