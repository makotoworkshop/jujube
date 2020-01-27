#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "../../Data/SongList.hpp"
#include "Resources.hpp"

namespace MusicSelect {

    class Screen;

    // A Panel holds anything that can go under a button on the moving part
    // of the music select screen, be it nothing, a category indicator, or a song
    class Panel {
    public:
        // What happens when you click on the panel
        virtual void click(Ribbon& ribbon) = 0;
        // How the panel should be displayed
        virtual void draw(const Resources& resources, sf::RenderTarget& target, sf::FloatRect area) = 0;
        virtual ~Panel() = default;
    };

    class EmptyPanel final : public Panel {
    public:
        void click(Ribbon& ribbon) override {return;};
        void draw(const Resources& resources, sf::RenderTarget& target, sf::FloatRect area) override {return;};
    };

    class ColorPanel final : public Panel {
    public:
        explicit ColorPanel(const sf::Color& t_color) : color(t_color) {};
        void click(Ribbon& ribbon) override {return;};
        void draw(const Resources& resources, sf::RenderTarget& target, sf::FloatRect area) override;
    private:
        const sf::Color color;
    };

    class CategoryPanel final : public Panel {
    public:
        explicit CategoryPanel(const std::string& t_label) : label(t_label) {};
        void click(Ribbon& ribbon) override;
        void draw(const Resources& resources, sf::RenderTarget& target, sf::FloatRect area) override;
    private:
        std::string label;
    };

    class SongPanel final : public Panel {
    public:
        explicit SongPanel(const Data::Song& t_song) : song(t_song) {};
        void click(Ribbon& ribbon) override;
        void draw(const Resources& resources, sf::RenderTarget& target, sf::FloatRect area) override;
    private:
        const Data::Song& song;
    };

    void set_to_global_bounds(sf::RectangleShape& rect, const sf::Text& text);
}