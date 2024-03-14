#include "input.hpp"

Input::Input(const sf::Window& window, int holdThreshold, const std::vector<Key>& keysToPoll)
    : m_window{window}, m_keysToPoll{keysToPoll}
{
    setHoldThreshold(holdThreshold);
    
    m_keyInfo.resize(static_cast<int>(TotalKeyCount));
}

bool Input::isDown(Key a) const
{
    return getKeyInfo(a).isDown;
}

bool Input::isPressed(Key a) const
{
    return getKeyInfo(a).isPressed;
}

bool Input::wasReleased(Key a) const
{
    return getKeyInfo(a).wasReleased;
}

bool Input::isHeld(Key a) const
{
    return getKeyInfo(a).heldTime == m_holdThreshold;
}

int Input::getHoldThreshold() const
{
    return m_holdThreshold;
}

sf::Vector2i Input::mousePosition() const
{
    return m_mousePos;
}

void Input::setKeysToPoll(const std::vector<Key>& a)
{
    m_keysToPoll = a;
}

void Input::setHoldThreshold(int a)
{
    m_holdThreshold = (a < MIN_HOLD_THRESHOLD ? MIN_HOLD_THRESHOLD : a);
}

void Input::poll()
{
    for(Key key : m_keysToPoll)
    {
        /* Skip over invalid values */
        if(key < 0 || key == KeyboardKeyCount || key >= TotalKeyCount)
            continue;
        
        int index = static_cast<int>(key);
        bool wasDown = getKeyInfo(key).isDown;
        
        /* Is key down or up (actively being pressed or not)? */
        if(key < KeyboardKeyCount)
        {
            getKeyInfo(key).isDown = sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key));
        }
        else
        {
            /* Input::Key has the mouse buttons at the end of the enum.
               Therefore, convert the Input::Key value to sf::Mouse::Button. */
            sf::Mouse::Button converted = static_cast<sf::Mouse::Button>(index - static_cast<int>(KeyboardKeyCount) - 1);
            getKeyInfo(key).isDown = sf::Mouse::isButtonPressed(static_cast<sf::Mouse::Button>(converted));
        }
        
        getKeyInfo(key).isPressed = !wasDown && getKeyInfo(key).isDown;
        
        /* Check if the key was released */
        bool isPressed = getKeyInfo(key).isPressed;
        bool wasReleased = wasDown && !getKeyInfo(key).isDown;
        getKeyInfo(key).wasReleased = wasReleased;
        
        /* Handle key holding */
        if(wasReleased)
        {
            getKeyInfo(key).heldTime = 0;
        }
        else if(isPressed)
        {
            getKeyInfo(key).heldTime++;
            
            /* Cap out at the threshold */
            if(getKeyInfo(key).heldTime > m_holdThreshold)
                getKeyInfo(key).heldTime = m_holdThreshold;
        }
    }
    
    m_mousePos = sf::Mouse::getPosition(m_window);
}

const Input::KeyInfo& Input::getKeyInfo(Key a) const
{
    return m_keyInfo[static_cast<int>(a)];
}

Input::KeyInfo& Input::getKeyInfo(Key a)
{
    return m_keyInfo[static_cast<int>(a)];
}