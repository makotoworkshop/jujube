#include "SongInfo.hpp"

#include <cmath>

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "../../Toolkit/EasingFunctions.hpp"
#include "../../Toolkit/SFMLHelpers.hpp"

#include "Panels/Panel.hpp"

namespace MusicSelect {

    BigCover::BigCover(ScreenResources& t_resources) :
        HoldsResources(t_resources)
    {
        m_cover_fallback.setFillColor(sf::Color::Transparent);
        m_cover_fallback.setOutlineThickness(1.f);
        m_cover_fallback.setOutlineColor(sf::Color::White); // White  Makoto : changemenent couleur contour cover
    }

    void BigCover::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        m_cover_fallback.setSize({get_size(), get_size()});
        target.draw(m_cover_fallback, states);
        auto selected_panel = resources.selected_panel;
        if (not selected_panel.has_value()) {
            return;
        }
        auto selected_chart = selected_panel->obj.get_selected_difficulty();
        if (not selected_chart.has_value()) {
            return;
        }
        auto cover_path = selected_chart->song.full_cover_path();
        if (not cover_path.has_value()) {
            return;
        }
        auto cover_texture = shared.covers.async_get(*cover_path);
        if (not cover_texture.has_value()) {
            return;
        }
        sf::Sprite cover{*(cover_texture->texture)};
        auto bounds = cover.getGlobalBounds();
        cover.setScale(get_size()/bounds.width, get_size()/bounds.height);
        auto alpha = static_cast<std::uint8_t>(
            m_seconds_to_alpha.clampedTransform(
                selected_panel->first_click.getElapsedTime().asSeconds()
            )
        );
        cover.setColor(sf::Color(255, 255, 255, alpha));
        target.draw(cover, states);
    }

    SongInfo::SongInfo(ScreenResources& t_resources) :
        HoldsResources(t_resources),
        m_big_cover(resources)
    {}

    void SongInfo::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        states.transform *= getTransform();
        m_big_cover.setOrigin(m_big_cover.get_size()*0.5f, 0.f);  // *0.5f, 0.f  
 //       m_big_cover.setPosition(get_big_cover_x(), get_big_cover_y());
        m_big_cover.setPosition(get_big_cover_x()+(180), get_big_cover_y()+(30));  // Makoto : position du BigCover Album
        target.draw(m_big_cover, states);
        draw_song_title(target, states);
        draw_big_level(target, states);
        draw_chart_list(target, states);
        draw_density_graph(target, states);
    }

    void SongInfo::draw_song_title(sf::RenderTarget& target, sf::RenderStates states) const {
        auto selected_panel = resources.selected_panel;
        if (not selected_panel.has_value()) {
            return;
        }
        auto selected_chart = selected_panel->obj.get_selected_difficulty();
        if (not selected_chart.has_value()) {
            return;
        }
        auto song_title = selected_chart->song.title;
        if (not song_title.empty()) {
            sf::Text song_title_label{
                sf::String::fromUtf8(song_title.begin(), song_title.end()),
                shared.fallback_font.medium,
                static_cast<unsigned int>(
                    0.026315789f*get_screen_width()
                )
            };
            auto song_title_bounds = song_title_label.getLocalBounds();
            if (song_title_bounds.width > m_big_cover.get_size()) {
                song_title_label.setScale(m_big_cover.get_size() / song_title_bounds.width, 1.0f);
            }
            song_title_label.setFillColor(sf::Color::White);
            song_title_label.setPosition(
                get_big_cover_x() - m_big_cover.get_size()/0.9f,     // 2.f  Makoto : position du grand titre
                get_big_cover_y() + m_big_cover.get_size() + (-0.12f)*get_screen_width()   // 0.01f*
            );
            target.draw(song_title_label, states);
        }
        auto song_artist = selected_chart->song.artist;
        if (not song_artist.empty()) {
            sf::Text song_artist_label{
                sf::String::fromUtf8(song_artist.begin(), song_artist.end()),
                shared.fallback_font.medium,
                static_cast<unsigned int>(
                    0.02f*get_screen_width()
                )
            };
            song_artist_label.setStyle(sf::Text::Italic);
            auto song_artist_bounds = song_artist_label.getLocalBounds();
            if (song_artist_bounds.width > m_big_cover.get_size()) {
                song_artist_label.setScale(m_big_cover.get_size() / song_artist_bounds.width, 1.0f);
            }
            song_artist_label.setFillColor(sf::Color::White);
            song_artist_label.setPosition(
                get_big_cover_x() - m_big_cover.get_size()/0.9f,     // 2.f  Makoto : position du grand artiste
                get_big_cover_y() + m_big_cover.get_size() + (-0.09f)*get_screen_width()   //  0.04f*
            );
            target.draw(song_artist_label, states);
        }
    }

    void SongInfo::draw_big_level(sf::RenderTarget& target, sf::RenderStates states) const {
        auto selected_panel = resources.selected_panel;
        if (not selected_panel.has_value()) {
            return;
        }
        auto selected_chart = selected_panel->obj.get_selected_difficulty();
        if (not selected_chart.has_value()) {
            return;
        }
        sf::Text level_label{
            "LEVEL",
            shared.fallback_font.light,
            static_cast<unsigned int>(12.f/768.f*get_screen_width())
        };
        Toolkit::set_origin_normalized(level_label, 0.5f, 0.f);
 //       level_label.setPosition(get_big_level_x(), get_big_level_y());
        level_label.setPosition(get_big_level_x()+(-510.f/1360.f*get_screen_height()), get_big_level_y()+(115.f/768.f*get_screen_width()));      // Makoto : position du petit texte LEVEL
        level_label.setFillColor(sf::Color::White);
        target.draw(level_label, states);
        
        sf::Text level_number_label{
            std::to_string(selected_chart->song.chart_levels.at(selected_chart->difficulty)),
            shared.fallback_font.black,
            static_cast<unsigned int>(130.f/768.f*get_screen_width())
        };
        Toolkit::set_origin_normalized(level_number_label, 0.5f, 0.f);          // Makoto : position texte Level number
 //       level_number_label.setPosition(get_big_level_x(), get_big_level_y()+(30.f/768.f*get_screen_width()));
        level_number_label.setPosition(get_big_level_x()+(-420.f/1360.f*get_screen_height()), get_big_level_y()+(65.f/768.f*get_screen_width()));
        level_number_label.setFillColor(sf::Color::White);
        target.draw(level_number_label, states);

        std::string full_difficulty = selected_chart->difficulty;
        if (selected_chart->difficulty == "BSC") {
            full_difficulty = "BASIC";
        } else if (selected_chart->difficulty == "ADV") {
            full_difficulty = "ADVANCED";
        } else if (selected_chart->difficulty == "EXT") {
            full_difficulty = "EXTREME";
        }

        sf::Text chart_label{
            sf::String::fromUtf8(full_difficulty.begin(), full_difficulty.end()),
            shared.fallback_font.medium,
            static_cast<unsigned int>(20.f/768.f*get_screen_width())
        };
        Toolkit::set_origin_normalized_no_position(chart_label, 0.5f, 0.f);     // Makoto : position texte level basic/adv/Exp
 //       chart_label.setPosition(get_big_level_x(), get_big_level_y()+(145.f/768.f*get_screen_width()));
        chart_label.setPosition(get_big_level_x()+(-560.f/1360.f*get_screen_height()), get_big_level_y()+(140.f/768.f*get_screen_width()));
        chart_label.setFillColor(shared.get_chart_color(selected_chart->difficulty));
        target.draw(chart_label, states);
    }

    void MusicSelect::SongInfo::draw_chart_list(sf::RenderTarget& target, sf::RenderStates states) const {
        auto selected_panel = resources.selected_panel;
        if (not selected_panel.has_value()) {
            return;
        }
        auto selected_chart = selected_panel->obj.get_selected_difficulty();
        if (not selected_chart.has_value()) {
            return;
        }
        auto dif_badge_radius = 8.f/768.f*get_screen_width();
        auto dif_badge_x = 30.f/768.f*get_screen_width();
        auto dif_badge_y = 40.f/768.f*get_screen_width();
        auto dif_badge_step = 3.f*dif_badge_radius;
        std::size_t dif_index = 0;
        for (auto &&[difficulty, level] : selected_chart->song.chart_levels) {
            sf::CircleShape dif_badge{dif_badge_radius};
            Toolkit::set_origin_normalized(dif_badge, 0.5f, 0.5f);
            dif_badge.setFillColor(shared.get_chart_color(difficulty));
            dif_badge.setPosition(dif_badge_x+dif_index*dif_badge_step, dif_badge_y);
            target.draw(dif_badge, states);
            if (difficulty == selected_chart->difficulty) {
                sf::CircleShape select_triangle(dif_badge_radius, 3);
                Toolkit::set_origin_normalized(select_triangle, 0.5f, 0.5f);
                select_triangle.rotate(180.f);
                select_triangle.setFillColor(sf::Color::White);
                if (selected_panel->is_first_click) {
                    select_triangle.setPosition(
                        dif_badge_x+dif_index*dif_badge_step,
                        dif_badge_y-dif_badge_step
                    );
                } else {
                    auto previous_index = (dif_index + selected_chart->song.chart_levels.size() - 1) % selected_chart->song.chart_levels.size();
                    auto animation_factor = m_seconds_to_badge_anim.clampedTransform(selected_panel->last_click.getElapsedTime().asSeconds());
                    animation_factor = Toolkit::EaseExponential(-7.f).transform(animation_factor);
                    select_triangle.setPosition(
                        dif_badge_x+(animation_factor*dif_index+(1-animation_factor)*previous_index)*dif_badge_step,
                        dif_badge_y-dif_badge_step
                    );
                }
                target.draw(select_triangle);
            }
            dif_index++;
        }
    }

    void SongInfo::draw_density_graph(sf::RenderTarget& target, sf::RenderStates states) const {
        sf::RectangleShape line{{get_screen_width()*1.1f,2.f/768.f*get_screen_width()}};
        Toolkit::set_origin_normalized(line, 0.5f, 0.5f);
        line.setFillColor(sf::Color::White);
        line.setPosition(get_screen_width()*0.5f,425.f/768.f*get_screen_width());
        target.draw(line, states);
        auto selected_panel = resources.selected_panel;
        if (not selected_panel.has_value()) {
            return;
        }
        auto selected_difficulty = selected_panel->obj.get_selected_difficulty();
        if (not selected_difficulty.has_value()) {
            return;
        }
        shared.density_graphs.load(*selected_difficulty);
        auto densities = shared.density_graphs.get(*selected_difficulty);
        if (not densities.has_value()) {
            return;
        }
        Toolkit::set_origin_normalized(*densities, 0.5f, 1.f);
        densities->setScale(get_screen_width()/768.f, get_screen_width()/768.f);
        densities->setPosition(get_screen_width()*0.5f,423.f/768.f*get_screen_width());
        target.draw(*densities, states);
    }
}
