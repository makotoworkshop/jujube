#include <iostream>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <cereal/archives/json.hpp>
#include <whereami/whereami++.hpp>

#include "Data/Song.hpp"
#include "Data/Preferences.hpp"
#include "Resources/Marker.hpp"
// #include "Data/Chart.hpp"
// #include "Data/Score.hpp"

#include "Screens/MusicSelect/MusicSelect.hpp"
// #include "Screens/Gameplay.hpp"
// #include "Screens/Result.hpp"

int main(int, char const **) {

    const std::string jujube_path = whereami::executable_dir();
    Data::Preferences preferences{jujube_path};
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window{
        sf::VideoMode(
            preferences.screen.width,
            preferences.screen.height
        ),
        "jujube",
        preferences.screen.fullscreen ? sf::Style::Fullscreen : sf::Style::Default,
        settings
    };
    Data::SongList song_list{jujube_path};
    MusicSelect::SharedResources music_select_resources{preferences};
    if (music_select_resources.markers.find(preferences.options.marker) == music_select_resources.markers.end()) {
        preferences.options.marker = music_select_resources.markers.begin()->first;
    }
    MusicSelect::Screen music_select{song_list, music_select_resources};    
    music_select.select_chart(window);
    /*
    while (true) {
        
        Chart& selected_chart = music_select.select_chart(window);

        Screen::Gameplay gameplay(selected_chart);
        Score score = gameplay.play_chart(window);
        
        Screen::Result result_screen(score);
        result_screen.display(window);
    
    }
    */
    
    return 0;

}
