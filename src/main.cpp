// Copyright (c) 2025 Yevhenii Kryvyi
// SPDX-License-Identifier: MIT

#include <sstream>

#include "Resources.hpp"
#include "RtMidi.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Graphics/Text.hpp"

int main()
{
    std::unique_ptr<RtMidiIn> midi;
    try
    {
        midi = std::make_unique<RtMidiIn>();
    }
    catch (...)
    {
        return 1;
    }

    std::stringstream labelText;
    const auto midiports = midi->getPortCount();
    labelText << midiports << ":\n";

    for (uint32_t i = 0; i < midiports; ++i)
    {
        labelText << midi->getPortName(i) << "\n";
    }

    muno::Resources res;

    sf::Font labelFont(res.font());
    sf::Text label(labelFont, labelText.str());

    auto window = sf::RenderWindow(sf::VideoMode({1280u, 720u}), "midi-sfml-test");
    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.draw(label);
        window.display();
    }
}