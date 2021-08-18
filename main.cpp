#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

//Set constant for sprite speed
#define SPEED 5;

int main()
{

    // Create window that fits the user's screen size, then make it fullscreen.
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window (sf::VideoMode(desktopMode.width, desktopMode.height, desktopMode.bitsPerPixel), "Sprite movement prototype", sf::Style::Fullscreen);

    //Only handle key presses once per loop
    window.setKeyRepeatEnabled(false);
    
    //Enable VSync
    window.setVerticalSyncEnabled(true);

    //Load the texture for the left sprite.
    sf::Texture leftTexture;
    if(!leftTexture.loadFromFile("img/sprite_left.png"))
    {
        return EXIT_FAILURE;
    }
// Load the right texture for the sprite
    sf::Texture rightTexture;
    if(!rightTexture.loadFromFile("img/sprite_right.png"))
    {
        return EXIT_FAILURE;
    }
     //Set the sprite texture (default)
    sf::Sprite sprite(leftTexture);

    //Set default sprite po
//Sesition
    sf::FloatRect spriteSize = sprite.getGlobalBounds(); //Rectangle around the sprite
    sprite.setOrigin(spriteSize.width/2, spriteSize.height/2);

    //Get window bounds
    int x = window.getSize().x/2;
    int y = window.getSize().y/2;

    //Movement data
    bool movingUp = false;
    bool movingDown = false;
    bool movingLeft = false;
    bool movingRight = false;

    //Orientation data
    bool facingRight = false;

    //Start game loop
    while (window.isOpen())
    {

            //Process events
            sf::Event event;
            while (window.pollEvent(event))
            {
                //Close window = exit
                if (event.type == sf::Event::Closed)
                {
                    window.close();
                }
                //Handle keyboard movement
                if (event.type == sf::Event::KeyPressed)
                {
                    switch(event.key.code)
                    {
                        case::sf::Keyboard::W:
                                movingUp = true;
                                break;
                        case::sf::Keyboard::S:
                                movingDown = true;
                                break;
                        case::sf::Keyboard::A:
                            movingLeft = true;
                            facingRight = false;
                            break;
                        case::sf::Keyboard::D:
                            movingRight = true;
                            facingRight = true;
                            break;
                        default:
                            break;
                    }
                }
                if (event.type == sf::Event::KeyReleased)
                {
                    switch(event.key.code)
                    {
                        case::sf::Keyboard::W:
                            movingUp = false;
                            break;
                        case::sf::Keyboard::S:
                            movingDown = false;
                            break;
                        case::sf::Keyboard::A:
                            movingLeft = false;
                            break;
                        case::sf::Keyboard::D:
                            movingRight = false;
                            break;
                        default:
                            break;

                    }
                }
            }
        //Apply movement
        if(movingLeft){
            x-=SPEED;
        }
        else if(movingRight){
            x+=SPEED;
        }
        else if(movingUp){
            y-=SPEED;
        }
        else if(movingDown){
            y+=SPEED;
        }

        if(facingRight){
    //Set the sprite texture
    sprite.setTexture(rightTexture);
        }
        else if(!facingRight)
        {
    //Set the sprite texture
    sprite.setTexture(leftTexture);
        }

        //Prevent sprite from escaping screen bounds
        if(x<0)
        {
            x=0;
        }
        if(x>(int) window.getSize().x)
        {
             x=window.getSize().x;
        }
        if(y < 0)
        {
            y = 0;
        }
        if(y>(int) window.getSize().y)
        {
            y=window.getSize().y;
        }
        //Clear previous frame, set background colour to Azure
        window.clear(sf::Color(0,128,255));

        //Draw sprite
        //sf::Vector2f spritePos = sprite.getPosition();
        //window.draw(sprite);
        sprite.setPosition(x,y);
        window.draw(sprite);
        //Update frame
        window.display();
    }
    return EXIT_SUCCESS;
}