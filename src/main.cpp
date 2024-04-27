#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(400, 200), "Enter Passkey");

    // Define the passkey
    std::string passkey = "ilovemyjosey"; // Replace "your_passkey" with your desired passkey

    // Create font
    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font file" << std::endl;
        return 1;
    }

    // Create text for instructions
    sf::Text instructions;
    instructions.setFont(font);
    instructions.setString("Enter Passkey:");
    instructions.setCharacterSize(24);
    instructions.setFillColor(sf::Color::Black);
    instructions.setPosition(20.f, 20.f);

    // Create text for passkey input
    sf::Text passkeyText;
    passkeyText.setFont(font);
    passkeyText.setCharacterSize(24);
    passkeyText.setFillColor(sf::Color::Black);
    passkeyText.setPosition(20.f, 70.f);
    std::string enteredPasskey;

    // Main loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window if requested
            if (event.type == sf::Event::Closed)
                window.close();

            // Process text input
            if (event.type == sf::Event::TextEntered)
            {
                if (event.text.unicode < 128)
                {
                    char c = static_cast<char>(event.text.unicode);
                    if (c == '\b' && !enteredPasskey.empty())
                    {
                        enteredPasskey.pop_back();
                    }
                    else if (c != '\b')
                    {
                        enteredPasskey += c;
                    }
                    passkeyText.setString(enteredPasskey);
                }
            }
        }

        // Check if entered passkey is correct
        if (enteredPasskey == passkey)
        {
            // Close the main window
            window.close();

            // Create a new window for success message
            sf::RenderWindow successWindow(sf::VideoMode(400, 200), "Success");

            // Create success text
            sf::Text successText;
            successText.setFont(font);
            successText.setString("Passkey Correct! Welcome!");
            successText.setCharacterSize(24);
            successText.setFillColor(sf::Color::Black);
            successText.setPosition(20.f, 20.f);

            // Success window loop
            while (successWindow.isOpen())
            {
                sf::Event successEvent;
                while (successWindow.pollEvent(successEvent))
                {
                    if (successEvent.type == sf::Event::Closed)
                        successWindow.close();
                }

                // Clear and draw
                successWindow.clear(sf::Color::White);
                successWindow.draw(successText);
                successWindow.display();
            }
        }

        // Clear and draw
        window.clear(sf::Color::White);
        window.draw(instructions);
        window.draw(passkeyText);
        window.display();
    }

    return 0;
}
