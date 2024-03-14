#include "Resources.hpp"
#include <iostream>

Resources* Resources::m_instance;

Resources& Resources::getResources()
{
    if(m_instance == nullptr)
        m_instance = new Resources();
    
    return *m_instance;
}

void fatalp(const std::string& msg)
{
    std::cerr << "ERROR: " << msg << std::endl;
    exit(EXIT_FAILURE);
}

Resources::Resources()
{
    if(!font.loadFromFile("res/Roboto-Thin.ttf"))
        fatalp("\"res/Roboto-Thin.ttf\" failed to load, aborting!");
}