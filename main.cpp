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

    //Load background image
    sf::Texture bgImg;
    if(!bgImg.loadFromFile("img/bg.png")){
        return EXIT_FAILURE;
    }
    //Create background sprite
    sf::Sprite bgSprite(bgImg);
    //Set default sprite position
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

    //Update sprite texture to face moving direction
        if(facingRight){
    sprite.setTexture(rightTexture);
        }
        else if(!facingRight)
        {
    sprite.setTexture(leftTexture);
        }

        //Prevent sprite from leaving screen bounds
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

        // Draw background image. DO NOT DRAW ANYTHING BEFORE THIS!
        window.draw(bgSprite);

        //Update character sprite location
        sprite.setPosition(x,y);
        //Draw character sprite
        window.draw(sprite);
        //Update frame
        window.display();
    }
    return EXIT_SUCCESS;
}