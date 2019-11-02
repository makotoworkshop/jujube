#include <SFML/Graphics.hpp>

#include "Data/Chart.hpp"
#include "Data/Score.hpp"

#include "Screens/MusicSelect/MusicSelect.hpp"
#include "Screens/Gameplay.hpp"
#include "Screens/Result.hpp"

int main(int argc, char const *argv[]) {
    
    sf::RenderWindow window(sf::VideoMode(800,600), "jujube");
    window.setVerticalSyncEnabled(true);
    
    MusicSelect::Screen music_select;
    
    while (true) {
        
        Chart& selected_chart = music_select.select_chart(window);

        Screen::Gameplay gameplay(selected_chart);
        Score score = gameplay.play_chart(window);
        
        Screen::Result result_screen(score);
        result_screen.display(window);
    
    }
    
    return 0;

}
