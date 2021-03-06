#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
//For tile loading
#include <tmxlite/Map.hpp>
#include "MapLoader.hpp"


//Set constant for sprite speed
#define SPEED 5;


int main()
{

    // Create window that fits the user's screen size, then make it fullscreen.
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window (sf::VideoMode(desktopMode.width, desktopMode.height, desktopMode.bitsPerPixel), "Sprite movement prototype", sf::Style::Fullscreen);

    //Load the map in
      tmx::Map map;
      map.load("devmap.tmx");

      MapLayer layerZero(map, 0);


    //Create a camera controller
    sf::View view;
    //Set view to user's screen size
    view.setSize(desktopMode.width, desktopMode.height);

    //Only handle key presses once per loop
    window.setKeyRepeatEnabled(false);
    
    //Enable VSync
    window.setVerticalSyncEnabled(true);

    //Load the texture for the left sprite.
    sf::Texture leftTexture;
    if(!leftTexture.loadFromFile("sprite_left.png"))
    {
        return EXIT_FAILURE;
    }
// Load the right texture for the sprite
    sf::Texture rightTexture;
    if(!rightTexture.loadFromFile("sprite_right.png"))
    {
        return EXIT_FAILURE;
    }
     //Set the sprite texture (default)
    sf::Sprite sprite(leftTexture);

    //Load background image
    sf::Texture bgImg;
    if(!bgImg.loadFromFile("bg.png")){
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
    sf::Clock globalClock;
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

            sf::Time duration = globalClock.restart();
            layerZero.update(duration);

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

        //Focus camera on sprite
        sf::Vector2f spritePos = sprite.getPosition();
        view.setCenter(spritePos);

    //Update sprite texture to face moving direction
        if(facingRight){
    sprite.setTexture(rightTexture);
        }
        else if(!facingRight)
        {
    sprite.setTexture(leftTexture);
        }

        //Prevent sprite from leaving screen bounds
        //x,y vars are window bounds
/*        if(x<0)
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
*/
        //Prevent camera from leaving tilemap
      sf::FloatRect mapSize = layerZero.getGlobalBounds();
      float mapHeight = mapSize.height;
      float mapWidth = mapSize.width;



    //Move camera view back into bounds if it exits tilemap
/*      if(view.getCenter().x > mapWidth - view.getSize().x)
      {
          view.setCenter(mapWidth - view.getSize().x, mapWidth);
      }
      if (view.getCenter().y > mapWidth - view.getSize().y)
      {
          view.setCenter(mapWidth - view.getSize().y, mapHeight);
      }
      if (view.getCenter().x > 0)
      {
          view.setCenter(0, view.getSize().y);
      }
      if (view.getCenter().y > 0)
      {
          view.setSize(view.getSize().x, 0);
      }
*/

        //Clear previous frame, set background colour to Azure
        window.clear(sf::Color(0,128,255));

        // Draw background image. DO NOT DRAW ANYTHING BEFORE THIS!
        //window.draw(bgSprite);

        //Update camera position
        window.setView(view);

        //Draw tilemap
        window.draw(layerZero);

        //Update character sprite location
        sprite.setPosition(x,y);
        //Draw character sprite
        window.draw(sprite);


        //Debug
/*        std::string debugText;
        debugText = std::to_string(view.getCenter().x) + std::to_string(view.getCenter().y);
        std::cout << debugText;
*/

        //Update frame
        window.display();
    }
    return EXIT_SUCCESS;
}