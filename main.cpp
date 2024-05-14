#include "UserInterface.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <sstream>


std::string Calculate(std::string inputStr) {
    std::vector<float> numbers;
    std::vector<char> operators;
    std::string numberStr = "";

    // Parse the input string into numbers and operators, considering unary minus for negative numbers
    for (int c = 0; c < inputStr.size(); c++) {
        if (isdigit(inputStr[c]) || inputStr[c] == '.' || (inputStr[c] == '-' && (c == 0 || !isdigit(inputStr[c-1])))) {
            numberStr += inputStr[c];
        } else if (inputStr[c] == '+' || inputStr[c] == '-' || inputStr[c] == '/' || inputStr[c] == 'x') {
            if (!numberStr.empty()) {
                numbers.push_back(std::stof(numberStr));
                numberStr = "";
            }
            operators.push_back(inputStr[c]);
        }
    }
    if (!numberStr.empty()) {
        numbers.push_back(std::stof(numberStr));
    }

    // First pass: Evaluate multiplication and division
    std::vector<float> newNumbers;
    std::vector<char> newOperators;
    float result = numbers[0];

    for (int i = 0; i < operators.size(); ++i) {
        if (operators[i] == 'x' || operators[i] == '/') {
            result = (operators[i] == 'x') ? result * numbers[i+1] : result / numbers[i+1];
        } else {
            newNumbers.push_back(result);
            newOperators.push_back(operators[i]);
            result = numbers[i+1];
        }
    }
    newNumbers.push_back(result); // Push the last accumulated result

    // Second pass: Evaluate addition and subtraction
    result = newNumbers[0];
    for (int i = 0; i < newOperators.size(); ++i) {
        if (newOperators[i] == '+') {
            result += newNumbers[i+1];
        } else if (newOperators[i] == '-') {
            result -= newNumbers[i+1];
        }
    }

    // Format the output to remove insignificant trailing zeros
    std::ostringstream out;
    out << std::fixed << std::setprecision(6) << result;
    std::string resultStr = out.str();
    resultStr.erase(resultStr.find_last_not_of('0') + 1, std::string::npos);
    resultStr.erase(resultStr.find_last_not_of('.') + 1, std::string::npos);

    return resultStr;
}



int main()
{
    sf::RenderWindow window(sf::VideoMode(450, 750), "Calculator");

    UI ui; // Instance of UI (buttons)
    // Make sprites for decorations
    sf::Texture windowUItext;
    windowUItext.loadFromFile("../files/Futuristic_UI_InputWindow_texture.jpeg");
    sf::Texture decorUItext;
    decorUItext.loadFromFile("../files/Calculator_UI_decor_texture.jpeg");
    sf::Sprite windowUISprite;
    windowUISprite.setTexture(windowUItext);
    windowUISprite.setScale(0.5, 0.5);
    sf::Sprite decorUISprite;
    decorUISprite.setTexture(decorUItext);
    decorUISprite.setScale(0.5, 0.5);
    decorUISprite.setRotation(270);
    decorUISprite.setPosition(298, 745);

    // input strings
    sf::Text inputText;
    sf::Font font;
    if (!font.loadFromFile("../files/Queen of Camelot.otf"))
    {
        std::cout << "Failed to load font." << std::endl;
    }
    inputText.setString("");
    inputText.setFont(font);
    inputText.setCharacterSize(26);
    inputText.setFillColor(sf::Color::White);
    sf::Text oldInput;
    oldInput.setString("");
    oldInput.setFont(font);
    oldInput.setCharacterSize(24);
    oldInput.setFillColor(sf::Color(150, 150, 150));

    // Event loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event)) {
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            // Take user input
            if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mouse;
                mouse = sf::Mouse::getPosition(window);

                // Check button
                if (event.mouseButton.button == sf::Mouse::Left) {
                    for (int i = 0; i < ui.buttons.size(); i++) {
                        for (int j = 0; j < ui.buttons[i].size(); j++) {
                            if (ui.buttons[i][j].sprite.getGlobalBounds().contains(mouse.x, mouse.y)) {
                                if (ui.buttons[i][j].value == "AC") {
                                    inputText.setString("");
                                    oldInput.setString("");
                                }
                                else if (ui.buttons[i][j].value == "NEXT") {
                                    oldInput.setString(inputText.getString());
                                    inputText.setString("");
                                }
                                else if (ui.buttons[i][j].value == "ANS") {
                                    inputText.setString(inputText.getString() + oldInput.getString());
                                }
                                else if (ui.buttons[i][j].value == "=") {
                                    inputText.setString(Calculate(inputText.getString()));
                                }
                                else {
                                    inputText.setString(inputText.getString() + ui.buttons[i][j].value);
                                }
                            }
                        }

                    }
                }
            }
        }

        // Draw/Display
        window.clear(sf::Color(21, 23, 36));
        window.draw(windowUISprite);

        for (int i = 0; i < ui.buttons.size(); i++) {
            for (int j = 0; j < ui.buttons[i].size(); j++) {
                window.draw(ui.buttons[i][j].sprite);
                window.draw(ui.buttons[i][j].text);
            }

        }
        window.draw(decorUISprite);
        // Set right side as origin for text
        sf::FloatRect textRect = inputText.getLocalBounds();
        inputText.setOrigin(textRect.width, 0);  // Shift origin to the right end of the text
        inputText.setPosition(370, 150);
        window.draw(inputText);
        sf::FloatRect textRect2 = oldInput.getGlobalBounds();
        oldInput.setOrigin(textRect2.width, 0);
        oldInput.setPosition(370, 90);
        window.draw(oldInput);
        window.display();
    }

    return 0;
}