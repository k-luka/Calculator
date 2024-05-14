//
// Created by Kirill Luka on 5/5/24.
//
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

struct UI {
    // Load font
    sf::Font loadFont() {
        sf::Font font;
        if (!font.loadFromFile("../files/Queen of Camelot.otf"))
        {
            std::cout << "Failed to load font." << std::endl;
        }
        else
            return font;
    }
    struct Button {
        sf::CircleShape button;
        sf::Sprite sprite;
        sf::Text text;
        std::string value;
        // Default Constructor
        Button() {
            button.setRadius(46);
            button.setOutlineColor(sf::Color::Black);
            button.setOutlineThickness(3);
            button.setFillColor(sf::Color(128, 128, 128));

        }
        // Setters
        void SetColorOrange() {
            button.setFillColor(sf::Color(255, 165, 0));
        }


    };
    // Members
    std::vector<std::vector<Button>> buttons;
    std::vector<Button> numButtons; // numbers 1-9
    std::vector<Button> miscButtons; // 0 and .
    std::vector<Button> operButtons; // operations
    std::vector<Button> cntrlButtons; // (AC, +/-, %)
    std::vector<Button> ansButton; // ANS button
    std::vector<Button> nextButton; // Saves previous result and displays above
    sf::Font font;
    sf::Texture textureNum;
    sf::Texture textureOpr;
    sf::Texture textureCntrl;
    sf::Texture textureANS;
    sf::Texture nextButtonText;

    UI() {
        // Load font
        font = loadFont();
        // Load textures
        textureNum.loadFromFile("../files/Calculator_UI_numButtons.jpeg");
        textureOpr.loadFromFile("../files/Calculator_UI_oprButtons.jpeg");
        textureCntrl.loadFromFile("../files/Calculator_UI_cntrlButtons.jpeg");
        textureANS.loadFromFile("../files/Calculator_UI_ANS_Button.jpeg");
        nextButtonText.loadFromFile("../files/Calculator_UI_NextButton.jpeg");

        // num buttons (1-9)
        for (int i = 7; i > 4; i--) {
            for (int j = 0; j < 3; j++) {
                Button temp;
                temp.sprite.setOrigin(-10,0);
                temp.sprite.setPosition(j * 100, (i-2 + 0.5) * 100);
                temp.sprite.setScale(1/4.5, 1/4.5);
                temp.sprite.setTexture(textureNum);
                temp.text.setFont(font);
                temp.text.setCharacterSize(24);
                temp.text.setFillColor(sf::Color::White);
                temp.text.setOrigin(-47, -34);
                temp.text.setPosition((j) * 100, (i-2 + 0.5) * 100);
                numButtons.push_back(temp);
            }
        }


        for (int i = 0; i < numButtons.size(); i++) {
            numButtons[i].value = std::to_string(i+1);
            numButtons[i].text.setString(std::to_string(i+1));
            std::string num = numButtons[i].text.getString();
        }
        buttons.push_back(numButtons);

        // misc buttons (0 and .)
        Button temp; // 0
        temp.sprite.setOrigin(-10,0);
        temp.sprite.setPosition(100, 650);
        temp.sprite.setScale(1/4.5, 1/4.5);
        temp.sprite.setTexture(textureNum);
        temp.text.setFont(font);
        temp.text.setCharacterSize(24);
        temp.text.setFillColor(sf::Color::White);
        temp.text.setOrigin(-47, -34);
        temp.text.setPosition(100, 650);
        temp.value = "0";
        temp.text.setString("0");
        miscButtons.push_back(temp);

        Button temp2; // .
        temp2.sprite.setOrigin(-10,0);
        temp2.sprite.setPosition(200, 650);
        temp2.sprite.setScale(1/4.5, 1/4.5);
        temp2.sprite.setTexture(textureNum);
        temp2.text.setFont(font);
        temp2.text.setCharacterSize(24);
        temp2.text.setFillColor(sf::Color::White);
        temp2.text.setOrigin(-50, -27);
        temp2.text.setPosition(200, 650);
        temp2.value = ".";
        temp2.text.setString(".");
        miscButtons.push_back(temp2);
        buttons.push_back(miscButtons);

        // operation buttons (/, x, -, +, =)
        std::vector<std::string> ops = {"/", "x", "-", "+", "="};
        for (int i = 0; i < 5; i++) {
            Button temp;
            temp.sprite.setOrigin(-10,0);
            temp.sprite.setPosition(340, (i + 2.5) * 100);
            temp.sprite.setScale(1/4.5, 1/4.5);
            temp.sprite.setTexture(textureOpr);
            temp.text.setFont(font);
            temp.text.setCharacterSize(24);
            temp.text.setFillColor(sf::Color::White);
            temp.text.setOrigin(-47, -34);
            temp.text.setPosition(340, (i + 2.5) * 100);
            temp.value = ops[i];
            temp.text.setString(ops[i]);
            operButtons.push_back(temp);
        }
        buttons.push_back(operButtons);

        // Control buttons (AC, +/-, %)
        std::vector<std::string> cntrl = {"AC", "+/-", "  %"};
        for (int i = 0; i < 1; i++) {
            Button temp;
            temp.sprite.setOrigin(-10,0);
            temp.sprite.setPosition(i * 100, 250);
            temp.sprite.setScale(1/4.5, 1/4.5);
            temp.sprite.setTexture(textureCntrl);
            temp.text.setFont(font);
            temp.text.setCharacterSize(24);
            temp.text.setFillColor(sf::Color::White);
            temp.text.setOrigin(-37, -34);
            temp.text.setPosition(i * 100, 250);
            temp.value = cntrl[i];
            temp.text.setString(cntrl[i]);
            cntrlButtons.push_back(temp);
        }
        buttons.push_back(cntrlButtons);

        std::string ansStr = "ANS";
        Button ANS;
        ANS.sprite.setOrigin(-10,0);
        ANS.sprite.setPosition(0, 650);
        ANS.sprite.setScale(1/4.5, 1/4.5);
        ANS.sprite.setTexture(textureANS);
        ANS.text.setFont(font);
        ANS.text.setCharacterSize(24);
        ANS.text.setFillColor(sf::Color::White);
        ANS.text.setOrigin(-31, -34);
        ANS.text.setPosition(0, 650);
        ANS.value = ansStr;
        ANS.text.setString(ansStr);
        ansButton.push_back(ANS);
        buttons.push_back(ansButton);

        std::string nextStr = "NEXT";
        Button next;
        next.sprite.setPosition(117, 255);
        next.sprite.setScale(0.3, 0.3);
        next.sprite.setTexture(nextButtonText);
        next.text.setFont(font);
        next.text.setCharacterSize(24);
        next.text.setFillColor(sf::Color::White);
        next.text.setOrigin(-31, -34);
        next.text.setPosition(150, 253);
        next.value = nextStr;
        next.text.setString(nextStr);
        nextButton.push_back(next);
        buttons.push_back(nextButton);
    }
};

