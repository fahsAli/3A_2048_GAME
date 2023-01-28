#ifndef GAME_HEADER
#define GAME_HEADER

#include <iostream>
#include <vector>
#include <time.h>




namespace game
{
    enum class key {
        up,
        down,
        left,
        right,
        quit,
        undefined
    };

    class Game {

        public:
            Game();
            int score();
            int move_num();

            void move(key k);
            void display();
            void play();

            bool can_move();


        private:
            int _score;
            int _move_num;
            int _grille_size;
            std::vector <int> _grille;
            void rand_generator();
            bool full_grille();

    };

}



#endif