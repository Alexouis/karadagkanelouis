#include "Button.h"

namespace render {
    Button::Button()
    {

    };

    Button::Button (std::string s, sf::Font& font, sf::Vector2f position,  enum buttonStyle style)
    {
        //set position
    pos = position;

    //set initial state
    m_btnState = NORMAL;

    //set button style
    m_style = style;

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

    //set up text
    m_text.setString(s);
    m_text.setFont(font);
    m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
    m_text.setColor(m_textNormal);

    //set some defauts
    m_borderRadius = 5.f;
    m_borderThickness = 0.f;
    m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.5f);

    m_button.setPointCount(4);
    m_button.setPoint(0, sf::Vector2f(0, 0));
    m_button.setPoint(1, sf::Vector2f(150, 0));
    m_button.setPoint(2, sf::Vector2f(150, 30));
    m_button.setPoint(3, sf::Vector2f(0, 30));
    m_button.setOrigin(m_button.getGlobalBounds().width/2, m_button.getGlobalBounds().height/2);
    m_button.setPosition(pos);

    sf::Vector2f textPosition = sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_button.getGlobalBounds().height/4);

    m_text.setPosition(textPosition);

    m_shadow.setFont(font);
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

        case gui::style::save:
        {
            target.draw(m_button, states);
            target.draw(m_shadow, states);
            target.draw(m_text, states);
        }
        break;

        case gui::style::cancel:
        {
            target.draw(m_button, states);
            target.draw(m_shadow, states);
            target.draw(m_text, states);
        }
        break;

        case gui::style::clean:
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
    
    // Setters and Getters
    const enum buttonState& Button::getM_btnState() const{

    };
    
    void Button::setM_btnState(const enum buttonState& m_btnState){

    };
    
    const sf::Text& Button::getM_text() const{

    };
    
    void Button::setM_text(const sf::Text& m_text){

    };
    
    const sf::Color& Button::getM_bgNormal() const{

    };
    
    void Button::setM_bgNormal(const sf::Color& m_bgNormal){

    };
    
    const sf::Color& Button::getM_bgHover() const{

    };
    
    void Button::setM_bgHover(const sf::Color& m_bgHover){

    };
    
    const sf::Color& Button::getM_bgClicked() const{

    };
    
    void Button::setM_bgClicked(const sf::Color& m_bgClicked){

    };
    
    const sf::Color& Button::getM_textNormal() const{

    };
    
    void Button::setM_textNormal(const sf::Color& m_textNormal){

    };
    
    const sf::Color& Button::getM_textHover() const{

    };
    
    void Button::setM_textHover(const sf::Color& m_textHover){

    };
    
    const sf::Color& Button::getM_textClicked() const{

    };
    
    void Button::setM_textClicked(const sf::Color& m_textClicked){

    };
    
    const sf::Color& Button::getM_border() const{

    };
    
    void Button::setM_border(const sf::Color& m_border){

    };
    
    float Button::getM_borderThickness() const{

    };
    
    void Button::setM_borderThickness(float m_borderThickness){

    };
    
    float Button::getM_borderRadius() const{

    };
    
    void Button::setM_borderRadius(float m_borderRadius){

    };
    
    const sf::Vector2f& Button::getM_size() const{

    };
    
    void Button::setM_size(const sf::Vector2f& m_size){
        
    };
    
    const  enum buttonStyle& Button::getM_style() const{

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

    };
    
    void Button::setM_button(const sf::ConvexShape& m_button){

    };
    
    unsigned int Button::getM_fontSize() const{

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

    };
    
    void Button::setM_font(const sf::Font& m_font)
    {
        m_text.setFont(m_font);
        m_shadow.setFont(m_font);
    };

    const sf::Text& Button::getM_shadow() const{

    };
    
    void Button::setM_shadow(const sf::Text& m_shadow){

    };
    

};