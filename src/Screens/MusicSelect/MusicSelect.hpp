#pragma once

#include <map>

#include <SFML/Window.hpp>

#include "../../Data/SongList.hpp"
#include "../../Data/Chart.hpp"
#include "../../Data/KeyMapping.hpp"
#include "../../Toolkit/AffineTransform.hpp"
#include "Ribbon.hpp"
#include "Resources.hpp"
#include "ButtonHighlight.hpp"

namespace MusicSelect {

    // The music select screen is created only once
    // it loads a cache of available songs in the song_list attribute
    class Screen {
    public:
        Screen(const Data::SongList& t_song_list);
        void select_chart(sf::RenderWindow& window);

    private:
        // Data
        const Data::SongList& song_list;
        unsigned int panel_size = 150;

        // Resources
        Resources resources;

        // State
        Ribbon ribbon;
        std::optional<std::reference_wrapper<SongPanel>> selected_panel;
        ButtonHighlight button_highlight;
    
        KeyMapping key_mapping;
        // converts a key press into a button press
        void handle_key_press(const sf::Event::KeyEvent& key_event);
        // converts a mouse click into a button press
        void handle_mouse_click(const sf::Event::MouseButtonEvent& mouse_button_event);
        // chooses what happens for each button
        void press_button(const Button& button);
    };
}
