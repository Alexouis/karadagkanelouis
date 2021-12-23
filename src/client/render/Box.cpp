#include "Box.h"

namespace render {
    Box::Box()
    {
        this->pos = sf::Vector2f(100.f, 200.f);
    };

    Box::~Box ()
    {

    };

    void Box::update ()
    {
        
    };

    void Box::draw (sf::RenderTarget& target, sf::RenderStates states) const{};

    // Setters and Getters
    const sf::Vector2f& Box::getPos() const{};

    void Box::setPos(const sf::Vector2f& pos){};

    const sf::Vector2f& Box::getDimensions() const{};

    void setDimensions(const sf::Vector2f& dimensions){};

    const TextOrTexture& Box::getContent() const{};

    void Box::setContent(const TextOrTexture& content){};

    const sf::Sprite& Box::getSprite() const{};

    void Box::setSprite(const sf::Sprite& sprite){};

}