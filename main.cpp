#include "include/player.h"
#include "include/story.h"

int main() {
    Player player1;
    story_begin();
    player1.generate_name();
    player1.generate_stats();
}