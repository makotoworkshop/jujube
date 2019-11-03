#include "Note.hpp"

namespace Data {
    
    Note::Note(
        unsigned int t_position,
        sf::Time t_timing,
        sf::Time t_length,
        unsigned int t_tail_position
    ) : 
        position(t_position),
        timing(t_timing),
        length(t_length),
        tail_position(t_tail_position)
    {
        if (t_position > 15) {  
            throw std::out_of_range(
                "Tried creating a note with invalid position : "
                +std::to_string(t_position)
            );
        }

        if (t_length.asMicroseconds() < 0) {
            throw std::out_of_range(
                "Tried creating a long note with negative length : "
                +std::to_string(t_length.asSeconds())+"s"
            );
        }
        if (t_length.asMicroseconds() > 0) {
            if (t_tail_position > 5) {
                throw std::out_of_range(
                    "Tried creating a long note with invalid tail position : "
                    +std::to_string(t_tail_position)
                );
            }
        }
    }

    bool Note::operator==(const Note &rhs) const {
        return timing == rhs.timing && position == rhs.position;
    }

    bool Note::operator!=(const Note &rhs) const {
        return !(rhs == *this);
    }

    bool Note::operator<(const Note &rhs) const {
        if (timing < rhs.timing) {
            return true;
        }
        if (rhs.timing < timing) {
            return false;
        }
        return position < rhs.position;
    }

    bool Note::operator>(const Note &rhs) const {
        return rhs < *this;
    }

    bool Note::operator<=(const Note &rhs) const {
        return !(rhs < *this);
    }

    bool Note::operator>=(const Note &rhs) const {
        return !(*this < rhs);
    }
    unsigned int Note::getPosition() const {
        return position;    
    }

    const sf::Time& Note::getTiming() const {
        return timing;    
    }

    const sf::Time& Note::getLength() const {
        return length;    
    }

    unsigned int Note::getTailPosition() const {
        return tail_position;    
    }
}
