/*
 * File             button_test.cpp
 * Directory        client
 * Created Date     Tuesday, December 7th 2021, 3:59:32 pm
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2021  ENSEA(FR)
 * __________________________________________________________________________
 */

#include <iostream>

#include <SFML/Graphics.hpp>


namespace gui
{
    namespace style
    {
        enum
        {
            none = 0,
            save = 1,
            cancel = 2,
            clean = 3,
        };
    };

    namespace state
    {
        enum
        {
            normal = 0,
            hovered = 1,
            clicked = 2
        };
    };

    class button : public sf::Drawable
    {
        public:
            button();
            button(std::string s, sf::Font& font, sf::Vector2f position, sf::Uint32 style);

            ~button();

            void setColorTextNormal(sf::Color text){m_textNormal = text;};
            void setColorTextHover(sf::Color text){m_textHover = text;};
            void setColorTextClicked(sf::Color text){m_textClicked = text;};
            void setColorNormal(sf::Color bgNormal){m_bgNormal = bgNormal;};
            void setColorHover(sf::Color bgHover){m_bgHover = bgHover;};
            void setColorClicked(sf::Color bgClicked){m_bgClicked = bgClicked;};
            void setBorderColor(sf::Color border){m_border = border;};
            void setBorderThickness(float t){m_borderThickness = t;};
            void setBorderRadius(float r){m_borderRadius = r;};
            void setPosition(sf::Vector2f position){m_position = position;};
            void setSize(unsigned int size);
            void setText(std::string s)
            {
                m_text.setString(s);
                m_shadow = m_text;
            };
            void setStyle(sf::Uint32 style);
            void setFont(sf::Font& font);

            sf::Vector2f getPosition(){return m_position;};
            sf::Vector2f getDimensions(){return sf::Vector2f(m_button.getGlobalBounds().width, m_button.getGlobalBounds().height);};
            sf::Uint32 getState(){return m_btnstate;};

            void update(sf::Event& e, sf::RenderWindow& window);

        private:

           virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;

        private:

            sf::Color m_bgNormal;
            sf::Color m_bgHover;
            sf::Color m_bgClicked;
            sf::Color m_textNormal;
            sf::Color m_textHover;
            sf::Color m_textClicked;
            sf::Color m_border;

            float m_borderThickness;
            float m_borderRadius;
            sf::Vector2f m_size;
            sf::Vector2f m_position;
            sf::Uint32 m_style;
            sf::Uint32 m_btnstate;

            sf::ConvexShape m_button;
            sf::Font m_font;
            unsigned int m_fontSize;
            sf::Text m_text;
            sf::Text m_shadow;
    };
};

gui::button::button()
{

}

gui::button::button(std::string s, sf::Font& font, sf::Vector2f position, sf::Uint32 style)
{
    //set position
    m_position = position;

    //set initial state
    m_btnstate = gui::state::normal;

    //set button style
    m_style = style;

    switch(m_style)
    {
        case gui::style::none:
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

        case gui::style::save:
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

        case gui::style::cancel:
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

        case gui::style::clean:
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
    m_button.setPosition(m_position);

    sf::Vector2f textPosition = sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_button.getGlobalBounds().height/4);

    m_text.setPosition(textPosition);

    m_shadow.setFont(font);
    m_shadow = m_text;
    m_shadow.setOrigin(m_shadow.getGlobalBounds().width/2, m_shadow.getGlobalBounds().height/2);
    m_shadow.setPosition(m_text.getPosition().x + 3.f, m_text.getPosition().y + 3.f);
}

gui::button::~button()
{

}

void gui::button::setSize(unsigned int size)
{
    m_fontSize = size;
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
    m_button.setPosition(m_position);
}

void gui::button::setStyle(sf::Uint32 style)
{
    //set button style
    m_style = style;

    switch(m_style)
    {
        case gui::style::none:
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

        case gui::style::save:
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

        case gui::style::cancel:
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

        case gui::style::clean:
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
}

void gui::button::setFont(sf::Font& font)
{
    m_text.setFont(font);
    m_shadow.setFont(font);
}

void gui::button::update(sf::Event& e, sf::RenderWindow& window)
{
    //perform updates for settings from user
    switch(m_style)
    {
        case gui::style::none:
        {
            m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.75f);
            m_button.setPointCount(4);
            m_button.setPoint(0, sf::Vector2f(0, 0));
            m_button.setPoint(1, sf::Vector2f(150, 0));
            m_button.setPoint(2, sf::Vector2f(150, 30));
            m_button.setPoint(3, sf::Vector2f(0, 30));
            m_button.setOrigin(m_button.getGlobalBounds().width/2, m_button.getGlobalBounds().height/2);
            m_button.setPosition(m_position);
            m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
            sf::Vector2f textPosition = sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_button.getGlobalBounds().height/4);
            m_text.setPosition(textPosition);
            m_text.setColor(m_textNormal);
            m_shadow.setOrigin(m_shadow.getGlobalBounds().width/2, m_shadow.getGlobalBounds().height/2);
            m_shadow.setPosition(m_text.getPosition().x + 3.f, m_text.getPosition().y + 3.f);
            m_shadow.setColor(sf::Color(0,0,0));
        }
        break;

        case gui::style::save:
        {
            m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.75f);
            m_button.setPointCount(4);
            m_button.setPoint(0, sf::Vector2f(0, 0));
            m_button.setPoint(1, sf::Vector2f(150, 0));
            m_button.setPoint(2, sf::Vector2f(150, 30));
            m_button.setPoint(3, sf::Vector2f(0, 30));
            m_button.setOrigin(m_button.getGlobalBounds().width/2, m_button.getGlobalBounds().height/2);
            m_button.setPosition(m_position);
            m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
            sf::Vector2f textPosition = sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_button.getGlobalBounds().height/4);
            m_text.setPosition(textPosition);
            m_text.setColor(m_textNormal);
            m_shadow.setOrigin(m_shadow.getGlobalBounds().width/2, m_shadow.getGlobalBounds().height/2);
            m_shadow.setPosition(m_text.getPosition().x + 3.f, m_text.getPosition().y + 3.f);
            m_shadow.setColor(sf::Color(0,0,0));
        }
        break;

        case gui::style::cancel:
        {
           m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.75f);
            m_button.setPointCount(4);
            m_button.setPoint(0, sf::Vector2f(0, 0));
            m_button.setPoint(1, sf::Vector2f(150, 0));
            m_button.setPoint(2, sf::Vector2f(150, 30));
            m_button.setPoint(3, sf::Vector2f(0, 30));
            m_button.setOrigin(m_button.getGlobalBounds().width/2, m_button.getGlobalBounds().height/2);
            m_button.setPosition(m_position);
            m_text.setOrigin(m_text.getGlobalBounds().width/2, m_text.getGlobalBounds().height/2);
            sf::Vector2f textPosition = sf::Vector2f(m_button.getPosition().x, m_button.getPosition().y - m_button.getGlobalBounds().height/4);
            m_text.setPosition(textPosition);
            m_text.setColor(m_textNormal);
            m_shadow.setOrigin(m_shadow.getGlobalBounds().width/2, m_shadow.getGlobalBounds().height/2);
            m_shadow.setPosition(m_text.getPosition().x + 3.f, m_text.getPosition().y + 3.f);
            m_shadow.setColor(sf::Color(0,0,0));
        }
        break;

        case gui::style::clean:
        {
            m_size = sf::Vector2f(m_text.getGlobalBounds().width * 1.5f, m_text.getGlobalBounds().height * 1.75f);
            m_button.setPointCount(4);
            m_button.setPoint(0, sf::Vector2f(0, 0));
            m_button.setPoint(1, sf::Vector2f(150, 0));
            m_button.setPoint(2, sf::Vector2f(150, 30));
            m_button.setPoint(3, sf::Vector2f(0, 30));
            m_button.setOrigin(m_button.getGlobalBounds().width/2, m_button.getGlobalBounds().height/2);
            m_button.setPosition(m_position);
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
            break;
    }

    //perform updates for user mouse interactions
    sf::Vector2i m_mousePosition = sf::Mouse::getPosition(window);

    bool mouseInButton =    m_mousePosition.x >= m_button.getPosition().x - m_button.getGlobalBounds().width/2
                            && m_mousePosition.x <= m_button.getPosition().x + m_button.getGlobalBounds().width/2
                            && m_mousePosition.y >= m_button.getPosition().y - m_button.getGlobalBounds().height/2
                            && m_mousePosition.y <= m_button.getPosition().y + m_button.getGlobalBounds().height/2;

    if(e.type == sf::Event::MouseMoved)
    {
        if(mouseInButton)
        {
            m_btnstate = gui::state::hovered;
        }

        else
        {
            m_btnstate = gui::state::normal;
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
                m_btnstate = gui::state::clicked;
            }

            else
            {
                m_btnstate = gui::state::normal;
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
                m_btnstate = gui::state::hovered;
            }

            else
            {
                m_btnstate = gui::state::normal;
            }
        }
        }
    }

    switch(m_btnstate)
    {
    case gui::state::normal:
    {
        m_button.setFillColor(m_bgNormal);
        m_text.setColor(m_textNormal);
    }
    break;

    case gui::state::hovered:
    {
        m_button.setFillColor(m_bgHover);
        m_text.setColor(m_textHover);
    }
    break;

    case gui::state::clicked:
    {
        m_button.setFillColor(m_bgClicked);
        m_text.setColor(m_textClicked);
    }
    break;
    }
}

void gui::button::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    switch(m_style)
    {
        case gui::style::none:
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
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(800,600,32), "Starfield Example", sf::Style::Default);

    sf::Font myfont;
    if(!myfont.loadFromFile("./extern/tmx-loader/fonts/Ubuntu-M.ttf"))
    {
        std::cerr<<"Could not find contb.ttf font."<<std::endl;
    }

    gui::button yeah("Yeah!", myfont, sf::Vector2f(100.f,100.f), gui::style::save);
    gui::button nope("Nope", myfont, sf::Vector2f(100.f, 200.f), gui::style::cancel);
    gui::button nice("Nice...", myfont, sf::Vector2f(300.f, 100.f), gui::style::clean);
    gui::button custom("Sweet", myfont, sf::Vector2f(300.f, 200.f), gui::style::none);
    custom.setBorderThickness(2.f);
    custom.setBorderRadius(20.f);
    custom.setBorderColor(sf::Color(255,255,255,255));
    custom.setColorNormal(sf::Color(200,0,200,255));
    custom.setColorHover(sf::Color(255,0,255,100));
    custom.setColorClicked(sf::Color(150,0,150,255));
    custom.setColorTextNormal(sf::Color(255,255,255,255));
    custom.setColorTextHover(sf::Color(255,255,0,255));
    custom.setColorTextClicked(sf::Color(255,0,0,255));

    sf::Event e;
    bool running = true;
    while(running)
    {
        while(window.pollEvent(e))
        {
            if(e.type == sf::Event::Closed)
            {
                window.close();
                return 0;
            }
        }
            yeah.update(e,window);
            nope.update(e,window);
            nice.update(e,window);
            custom.update(e,window);

            window.clear();
            window.draw(yeah);
            window.draw(nope);
            window.draw(nice);
            window.draw(custom);
            window.display();
    }
    return 0;
}
