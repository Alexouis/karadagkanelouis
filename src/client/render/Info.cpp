#include "Info.h"
#include "GameWindow.h"

namespace render{

    Info::Info(){};

    Info::Info(std::string s, sf::Font& font, unsigned int sizeFont, sf::Vector2i position,GameWindow* gameWindow)
    {
        this->m_position = position;
        this->m_font = font;
        this->m_text.setString(s);
        this->m_text.setFont(m_font);
        this->m_text.setCharacterSize(sizeFont);
        this->m_text.setScale(m_text.getScale()*(gameWindow->zoom));
        this->m_text.setOrigin(0,0);
        this->m_text.setColor(sf::Color(255,255,255));
        this->m_text.setPosition(gameWindow->window.mapPixelToCoords(m_position));
    };
    
    //  Pour écrire l’info sur la scène.
    void Info::draw (sf::RenderTarget& target, sf::RenderStates  states) const{
        target.draw(m_text, states);
    };

    //  Pour réactualiser l’info (le texte) affichée.
    void Info::update(sf::Event& event, sf::Vector2i m_mousePosition, GameWindow* gameWindow)
    {
        if(gameWindow->isZoomed)
        {
            this->m_text.setScale(m_text.getScale()*(gameWindow->zoom));
        }
        this->m_text.setPosition(gameWindow->window.mapPixelToCoords(m_position));
    };

    //-----------------------------Setters and Getters-----------------------------
    
    const sf::Font& Info::getM_font() const{
        return m_font;
    };

    void Info::setM_font(const sf::Font& m_font){
        this->m_font = m_font;
    };

    Info::~Info(){};
}