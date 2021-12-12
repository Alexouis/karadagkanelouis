<<<<<<< HEAD
=======
/*
 * File             testDrawable.cpp
 * Directory        examples
 * Created Date     Wednesday, December 8th 2021, 4:46:42 pm
 * Author           Nouhou KANE
 * Email            nouhou.kane@ensea.fr
 * 
 * Copyright (c) 2021  ENSEA(FR)
 * __________________________________________________________________________
 */

>>>>>>> 346e1a6a110a2139ec22ec5abc14c75ce35a3475
#include <SFML/Graphics.hpp>

class MyDrawable : public sf::Drawable
{
    public :
        MyDrawable()
        {
                // This example shows the most common use of sf::Texture:
                // drawing a sprite
                // Load a texture from a file

<<<<<<< HEAD
                m_texture.loadFromFile("res/Valla/128x128.png");
                // Assign it to a sprite
                m_sprite.setTexture(m_texture);
=======
                
        }

        void init(){
            if (!m_texture.loadFromFile("/home/mkas/ENSEA/karadagkanelouis/res/Valla/1200x630wm.png")){
                // Assign it to a sprite
            }
            m_sprite.setTexture(m_texture);
>>>>>>> 346e1a6a110a2139ec22ec5abc14c75ce35a3475
        }

    private :
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            // You can draw other high-level objects
<<<<<<< HEAD
=======
            
>>>>>>> 346e1a6a110a2139ec22ec5abc14c75ce35a3475
            target.draw(m_sprite, states);
            // ... or use the low-level API
            states.texture = &m_texture;
            target.draw(m_vertices, states);
        }
        sf::Sprite m_sprite;
        sf::Texture m_texture;
        sf::VertexArray m_vertices;
};

int main()
{
    MyDrawable dr;
<<<<<<< HEAD
=======
    dr.init();
>>>>>>> 346e1a6a110a2139ec22ec5abc14c75ce35a3475

    sf::RenderWindow renderWindow(sf::VideoMode(2000u, 600u), "TMX Loader");
	renderWindow.setVerticalSyncEnabled(true);

    while(renderWindow.isOpen())
	{
<<<<<<< HEAD
=======
        sf::Event event;
		while(renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				renderWindow.close();
        }

>>>>>>> 346e1a6a110a2139ec22ec5abc14c75ce35a3475
		renderWindow.clear();
        renderWindow.draw(dr);
        renderWindow.display();
    }
}