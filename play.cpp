#include "gomoku_winning_chance_simulation.h"
using namespace std;

int main()
{
        srand(time(NULL));
        int x = 0, o = 0, d = 0;
        for (int i = 0; i < 100; i++)
        {
            AIPlayer playerX(PLAYER_X, 1 , 1 );
            AIPlayer playerO(PLAYER_O, 1.5 , 2.5 );
            gameManager z(playerX, playerO, 10, 10); 
            int res = z.playMatch();
            if(res == 0) d++;
            else if(res == PLAYER_X) x++;
            else if(res == PLAYER_O) o++;
        }
        cout << "--- KET QUA ---" << endl;
        cout << "X win: " << x << endl;
        cout << "O win: " << o << endl;
        cout << "Hoa: " << d << endl;
}