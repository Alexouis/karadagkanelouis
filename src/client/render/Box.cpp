#include "Box.h"
#include "GameWindow.h"
#include "iostream"

namespace render {
    Box::Box()
    {
        this->m_position = sf::Vector2i(100, 200);
    };

    Box::~Box ()
    {

    };

    void Box::update(sf::Event& event, sf::Vector2i m_mousePosition, GameWindow* gameWindow)
    {
        
    };

    void Box::draw (sf::RenderTarget& target, sf::RenderStates states) const{
        std::cout << "Draw Box" << std::endl;
    };

    // Setters and Getters
    const sf::Vector2i& Box::getM_position() const{};

    void Box::setM_position(const sf::Vector2i& pos){};

    const sf::Vector2f& Box::getDimensions() const{};

    void setDimensions(const sf::Vector2f& dimensions){};

    const TextOrTexture& Box::getContent() const{};

    void Box::setContent(const TextOrTexture& content){};

    const sf::Sprite& Box::getSprite() const{};

    void Box::setSprite(const sf::Sprite& sprite){};


    void Box::setText(std::string s){
        this->m_text.setString(s);
    };
    
    void Box::setM_text(const sf::Text& m_text){
        this->m_text = m_text;
    };

    const sf::Text& Box::getM_text() const{
    };

}