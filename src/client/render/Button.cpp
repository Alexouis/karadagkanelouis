#include "Button.h"
#include "GameWindow.h"
#include "iostream"

namespace render {
    Button::Button()
    {

    };

    Button::Button (std::string s, sf::Font& font,sf::Vector2f size, sf::Vector2i position, enum buttonStyle style, char m_type, GameWindow* gameWindow)
    {
  
    dimensions = size; 

        //set position
    m_position = position;

    //set initial state
    m_btnState = NORMAL;

    //set button style
    m_style = style;
    m_font = font;

    this->m_type = m_type;

    switch(m_style)
    {
        case NONE:
        {
            m_textNormal = sf::Color(255,255,255);
            m_textHover = sf::Color(255,255,255);
            m_textClicked = sf::Color(255,255,255);
            m_bgNormal = sf::Color(255,255,255,100);
            m_bgHover = sf::Color(200,200,200,100);
            m_bgClicked = sf::Color(150,150,150);
            m_border = sf::Color(255,255,255,100);
        }
        break;

        case SAVE:
        {
            m_textNormal = sf::Color(255,255,255);
            m_textHover = sf::Color(255,255,255);
            m_textClicked = sf::Color(255,255,255);
            m_bgNormal = sf::Color(0,255,0,100);
            m_bgHover = sf::Color(0,200,0,100);
            m_bgClicked = sf::Color(0,150,0);
            m_border = sf::Color(0,0,0,100);
        }
        break;

        case CANCEL:
        {
            m_textNormal = sf::Color(255,255,255);
            m_textHover = sf::Color(255,255,255);
            m_textClicked = sf::Color(255,255,255);
            m_bgNormal = sf::Color(255,0,0,100);
            m_bgHover = sf::Color(200,0,0,100);
            m_bgClicked = sf::Color(150,0,0);
            m_border = sf::Color(255,255,255,100);
        }
        break;

        case CLEAN:
        {
            m_textNormal = sf::Color(255,255,255);
            m_textHover = sf::Color(255,255,255);
            m_textClicked = sf::Color(255,255,255);
            m_bgNormal = sf::Color(0,255,255,100);
            m_bgHover = sf::Color(0,200,200,100);
            m_bgClicked = sf::Color(0,150,150);
            m_border = sf::Color(255,255,255,100);
        }
        break;

        default:
            m_textNormal = sf::Color(255,255,255);
            m_textHover = sf::Color(255,255,255);
            m_textClicked = sf::Color(255,255,255);
            m_bgNormal = sf::Color(255,255,255,100);
            m_bgHover = sf::Color(200,200,200,100);
            m_bgClicked = sf::Color(150,150,150);
            m_border = sf::Color(255,255,255,100);
            break;
    }

    //set up text
    m_text.setString(s);
    m_text.setFont(m_font);
    m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
    m_text.setColor(m_textNormal);

    //set some defauts
    m_borderRadius = 5.f;
    m_borderThickness = 0.f;
    m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.5f);

    m_button.setPointCount(4);
    m_button.setPoint(0, sf::Vector2f(0, 0));
    m_button.setPoint(1, sf::Vector2f(dimensions.x, 0));
    m_button.setPoint(2, sf::Vector2f(dimensions.x, dimensions.y));
    m_button.setPoint(3, sf::Vector2f(0, dimensions.y));
    m_button.setOrigin(m_button.getGlobalBounds().width/2, m_button.getGlobalBounds().height/2);
    m_button.setPosition(gameWindow->window.mapPixelToCoords(m_position));

    sf::Vector2f textPosition = sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_button.getGlobalBounds().height/4);

    m_text.setPosition(textPosition);

    m_shadow.setFont(m_font);
    m_shadow = m_text;
    m_shadow.setOrigin(m_shadow.getGlobalBounds().width/2, m_shadow.getGlobalBounds().height/2);
    m_shadow.setPosition(m_text.getPosition().x + 3.f, m_text.getPosition().y + 3.f);

    };
    
    Button::~Button (){

    };
    
    void Button::draw (sf::RenderTarget& target, sf::RenderStates states) const{
        
        switch(m_style)
    {
        case NONE:
        {
            target.draw(m_button, states);
            target.draw(m_shadow, states);
            target.draw(m_text, states);
        }
        break;

        case SAVE:
        {
            target.draw(m_button, states);
            target.draw(m_shadow, states);
            target.draw(m_text, states);
        }
        break;

        case CANCEL:
        {
            target.draw(m_button, states);
            target.draw(m_shadow, states);
            target.draw(m_text, states);
        }
        break;

        case CLEAN:
        {
            target.draw(m_button, states);
            target.draw(m_shadow, states);
            target.draw(m_text, states);
        }
        break;

        default:
            break;
    }
    };

    void Button::update(sf::Event& e, sf::Vector2i  m_mousePosition, GameWindow* gameWindow)
    {
            //perform updates for settings from user
    switch(m_style)
    {
        case NONE:
        {
            m_button.setOrigin(m_button.getGlobalBounds().width/2, m_button.getGlobalBounds().height/2);
            if(gameWindow->isZoomed)
            {
                m_button.setScale(m_button.getScale()*(gameWindow->zoom));
                m_button.setPosition(gameWindow->window.mapPixelToCoords(m_position));
            }
            m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
            sf::Vector2f textPosition = sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_button.getGlobalBounds().height/4);
            m_text.setPosition(textPosition);
            m_text.setColor(m_textNormal);
            m_shadow.setOrigin(m_shadow.getGlobalBounds().width/2, m_shadow.getGlobalBounds().height/2);
            m_shadow.setPosition(m_text.getPosition().x + 3.f, m_text.getPosition().y + 3.f);
            m_shadow.setColor(sf::Color(0,0,0));
        }
        break;

        case SAVE:
        {
            if(gameWindow->isZoomed){
                m_button.setScale(m_button.getScale()*(gameWindow->zoom));
                m_button.setPosition(gameWindow->window.mapPixelToCoords(m_position));
            }

            m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
            sf::Vector2f textPosition = sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_button.getGlobalBounds().height/4);
            m_text.setPosition(textPosition);
            m_text.setColor(m_textNormal);
            m_shadow.setOrigin(m_shadow.getGlobalBounds().width/2, m_shadow.getGlobalBounds().height/2);
            m_shadow.setPosition(m_text.getPosition().x + 3.f, m_text.getPosition().y + 3.f);
            m_shadow.setColor(sf::Color(0,0,0));
        }
        break;

        case CANCEL:
        {
            m_button.setOrigin(m_button.getGlobalBounds().width/2, m_button.getGlobalBounds().height/2);
            if(gameWindow->isZoomed)
            {
                m_button.setScale(m_button.getScale()*(gameWindow->zoom));
                m_button.setPosition(gameWindow->window.mapPixelToCoords(m_position));

            }

            m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
            sf::Vector2f textPosition = sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_button.getGlobalBounds().height/4);
            m_text.setPosition(textPosition);
            m_text.setColor(m_textNormal);
            m_shadow.setOrigin(m_shadow.getGlobalBounds().width/2, m_shadow.getGlobalBounds().height/2);
            m_shadow.setPosition(m_text.getPosition().x + 3.f, m_text.getPosition().y + 3.f);
            m_shadow.setColor(sf::Color(0,0,0));
        }
        break;

        case CLEAN:
        {
            m_button.setOrigin(m_button.getGlobalBounds().width/2, m_button.getGlobalBounds().height/2);
            if(gameWindow->isZoomed)
            {
                m_button.setScale(m_button.getScale()*(gameWindow->zoom));
                m_button.setPosition(gameWindow->window.mapPixelToCoords(m_position));
            }
            m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
            sf::Vector2f textPosition = sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_button.getGlobalBounds().height/4);
            m_text.setPosition(textPosition);
            m_text.setColor(m_textNormal);
            m_shadow.setOrigin(m_shadow.getGlobalBounds().width/2, m_shadow.getGlobalBounds().height/2);
            m_shadow.setPosition(m_text.getPosition().x + 3.f, m_text.getPosition().y + 3.f);
            m_shadow.setColor(sf::Color(0,0,0));
        }
        break;

        default:
            m_button.setOrigin(m_button.getGlobalBounds().width/2, m_button.getGlobalBounds().height/2);
            if(gameWindow->isZoomed)
            {
                m_button.setScale(m_button.getScale()*(gameWindow->zoom));
                m_button.setPosition(gameWindow->window.mapPixelToCoords((sf::Vector2i)pos));
            }
            m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
            sf::Vector2f textPosition = sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_button.getGlobalBounds().height/4);
            m_text.setPosition(textPosition);
            m_text.setColor(m_textNormal);
            m_shadow.setOrigin(m_shadow.getGlobalBounds().width/2, m_shadow.getGlobalBounds().height/2);
            m_shadow.setPosition(m_text.getPosition().x + 3.f, m_text.getPosition().y + 3.f);
            m_shadow.setColor(sf::Color(0,0,0));
            break;
    }
    
    

    //perform updates for user mouse interactions
    sf::Vector2i mousePosition = m_mousePosition;

    bool mouseInButton =    mousePosition.x >= m_button.getPosition().x - m_button.getGlobalBounds().width/2
                            && mousePosition.x <= m_button.getPosition().x + m_button.getGlobalBounds().width/2
                            && mousePosition.y >= m_button.getPosition().y - m_button.getGlobalBounds().height/2
                            && mousePosition.y <= m_button.getPosition().y + m_button.getGlobalBounds().height/2;

    if(e.type == sf::Event::MouseMoved)
    {
        if(mouseInButton && m_btnState != CLICKED)
        {
            m_btnState = HOVERED;
        }

        else if (m_btnState != CLICKED)
        {
            m_btnState = NORMAL;
        }
    }

    if (e.type == sf::Event::MouseButtonPressed)
    {
        switch(e.mouseButton.button)
        {
        case sf::Mouse::Left:
        {
            if(mouseInButton)
            {
                m_btnState = CLICKED;
                gameWindow->selected = m_type;
            }

            else
            {
                m_btnState = NORMAL;
            }
        }
        break;
        }
    }

    if (e.type == sf::Event::MouseButtonReleased)
    {
        switch(e.mouseButton.button)
        {
        case sf::Mouse::Left:
        {
            if(mouseInButton)
            {
                if(m_type >=5)
                {
                    m_btnState = HOVERED;
                }
                else if(m_type < 5 && m_btnState==CLICKED)
                {
                    m_btnState = CLICKED;    
                }
                 
            }

            else if(m_btnState != CLICKED)
            {
                m_btnState = NORMAL;
            }
        }
        }
    }

    switch(m_btnState)
    {
    case NORMAL:
    {
        m_button.setFillColor(m_bgNormal);
        m_text.setColor(m_textNormal);
    }
    break;

    case HOVERED:
    {
        m_button.setFillColor(m_bgHover);
        m_text.setColor(m_textHover);
    }
    break;

    case CLICKED:
    {
        m_button.setFillColor(m_bgClicked);
        m_text.setColor(m_textClicked);
    }
    break;
    }
    }
    
    // Setters and Getters
    const enum buttonState& Button::getM_btnState() const{
        return m_btnState;
    };
    
    void Button::setM_btnState(const enum buttonState& m_btnState){
        this->m_btnState = m_btnState;
    };
    
    const sf::Text& Button::getM_text() const{
        return m_text;
    };
    
    void Button::setM_text(const sf::Text& m_text){
        this->m_text = m_text;
    };
    
    const sf::Color& Button::getM_bgNormal() const{
        return m_bgNormal;
    };
    
    void Button::setM_bgNormal(const sf::Color& m_bgNormal){
        this->m_bgNormal = m_bgNormal;
    };
    
    const sf::Color& Button::getM_bgHover() const{
        return(m_bgHover);
    };
    
    void Button::setM_bgHover(const sf::Color& m_bgHover){
        this->m_bgHover = m_bgHover;
    };
    
    const sf::Color& Button::getM_bgClicked() const{
        return m_bgClicked;
    };
    
    void Button::setM_bgClicked(const sf::Color& m_bgClicked){
        this->m_bgClicked = m_bgClicked;
    };
    
    const sf::Color& Button::getM_textNormal() const{
        return m_textNormal;
    };
    
    void Button::setM_textNormal(const sf::Color& m_textNormal){
        this->m_textNormal = m_textNormal;
    };
    
    const sf::Color& Button::getM_textHover() const{
        return m_textHover;
    };
    
    void Button::setM_textHover(const sf::Color& m_textHover){
        this->m_textHover = m_textHover;
    };
    
    const sf::Color& Button::getM_textClicked() const{
        return m_textClicked;
    };
    
    void Button::setM_textClicked(const sf::Color& m_textClicked){
        this->m_textClicked = m_textClicked;
    };
    
    const sf::Color& Button::getM_border() const{
        return m_border;
    };
    
    void Button::setM_border(const sf::Color& m_border){
        this->m_border = m_border; 
    };
    
    float Button::getM_borderThickness() const{
        return m_borderThickness;
    };
    
    void Button::setM_borderThickness(float m_borderThickness){
        this->m_borderThickness = m_borderThickness;
    };
    
    float Button::getM_borderRadius() const{
        return m_borderRadius;
    };
    
    void Button::setM_borderRadius(float m_borderRadius){
        this->m_borderRadius = m_borderRadius;
    };
    
    const sf::Vector2f& Button::getM_size() const{
        return m_size;
    };
    
    void Button::setM_size(const sf::Vector2f& m_size){
        this->m_size = m_size;
    };
    
    const  enum buttonStyle& Button::getM_style() const{
        return m_style;
    };
    
    void Button::setM_style(const enum buttonStyle& m_style){
        //set button style
    this->m_style = m_style;

    switch(m_style)
    {
        case NONE:
        {
            m_textNormal = sf::Color(255,255,255);
            m_textHover = sf::Color(255,255,255);
            m_textClicked = sf::Color(255,255,255);
            m_bgNormal = sf::Color(255,255,255,100);
            m_bgHover = sf::Color(200,200,200,100);
            m_bgClicked = sf::Color(150,150,150);
            m_border = sf::Color(255,255,255,100);
        }
        break;

        case SAVE:
        {
            m_textNormal = sf::Color(255,255,255);
            m_textHover = sf::Color(255,255,255);
            m_textClicked = sf::Color(255,255,255);
            m_bgNormal = sf::Color(0,255,0,100);
            m_bgHover = sf::Color(0,200,0,100);
            m_bgClicked = sf::Color(0,150,0);
            m_border = sf::Color(0,0,0,100);
        }
        break;

        case CANCEL:
        {
            m_textNormal = sf::Color(255,255,255);
            m_textHover = sf::Color(255,255,255);
            m_textClicked = sf::Color(255,255,255);
            m_bgNormal = sf::Color(255,0,0,100);
            m_bgHover = sf::Color(200,0,0,100);
            m_bgClicked = sf::Color(150,0,0);
            m_border = sf::Color(255,255,255,100);
        }
        break;

        case CLEAN:
        {
            m_textNormal = sf::Color(255,255,255);
            m_textHover = sf::Color(255,255,255);
            m_textClicked = sf::Color(255,255,255);
            m_bgNormal = sf::Color(0,255,255,100);
            m_bgHover = sf::Color(0,200,200,100);
            m_bgClicked = sf::Color(0,150,150);
            m_border = sf::Color(255,255,255,100);
        }
        break;

        default:
            break;
    }
    };
    
    const sf::ConvexShape& Button::getM_button() const{
        return m_button;
    };
    
    void Button::setM_button(const sf::ConvexShape& m_button){
        this->m_button = m_button;
    };
    
    unsigned int Button::getM_fontSize() const{
        return m_fontSize;
    };
    
    void Button::setM_fontSize(unsigned int m_fontSize){
        m_fontSize = m_fontSize;
        m_text.setCharacterSize(m_fontSize);
        m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
        m_shadow.setCharacterSize(m_fontSize);
        m_shadow.setOrigin(m_shadow.getGlobalBounds().width/2, m_shadow.getGlobalBounds().height/2);
        m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, (m_text.getGlobalBounds().height + m_text.getGlobalBounds().height) * 1.5f);
        m_button.setPointCount(4);
        m_button.setPoint(0, sf::Vector2f(0, 0));
        m_button.setPoint(1, sf::Vector2f(150, 0));
        m_button.setPoint(2, sf::Vector2f(150, 30));
        m_button.setPoint(3, sf::Vector2f(0, 30));
        m_button.setOrigin(m_button.getGlobalBounds().width/2, m_button.getGlobalBounds().height/2);
        m_button.setPosition(pos);
    };
    
    const sf::Font& Button::getM_font() const{
        return m_font;
    };
    
    void Button::setM_font(const sf::Font& m_font)
    {
        m_text.setFont(m_font);
        m_shadow.setFont(m_font);
    };

    const sf::Text& Button::getM_shadow() const{
        return m_shadow;
    };
    
    void Button::setM_shadow(const sf::Text& m_shadow){
        this->m_shadow = m_shadow;
    };
    

};