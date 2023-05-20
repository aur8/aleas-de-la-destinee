#ifndef ALEAS_DE_LA_DESTINEE_PLAYER_H
#define ALEAS_DE_LA_DESTINEE_PLAYER_H
#include <string>

class Player {

private:

    std::string m_name = "Player";

    int m_str = 0;
    int m_dex = 0;
    int m_con = 0;

    unsigned int m_ability_points_left = 15;

public:
    Player()=default;
    Player(int str, int dex, int con) : m_str(str), m_dex(dex), m_con(con) {};

    void generate_name();
    void generate_stats();

private:

    void display_abilities() const;
    void add_value_to_ability(int &ability, const std::string& ability_name);
};


#endif //ALEAS_DE_LA_DESTINEE_PLAYER_H
