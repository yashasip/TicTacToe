/* --------------------------------------------- TIC TAC TOE ------------------------------------------------------ */
/* Choose your marker
   Enter your move based on below box numbers
     1 | 2 | 3
    --- --- ---
     4 | 5 | 6
    --- --- ---
     7 | 8 | 9
*/

#include <iostream>
#include <stdlib.h> /* rand(), srand()  */
#include <time.h>

const int BOX_COUNT = 9;
const int SIDE_SIZE = 3;

class TicTacToe
{

public:
    enum symbols
    {
        BLANK,
        CROSS,
        CIRCLE
    };

    symbols input_map[SIDE_SIZE][SIDE_SIZE];
    symbols player_marker, computer_marker;
    int marker_choice, empty_box_count = BOX_COUNT;

    void initialize()
    {
        setup_game();

        std::cout << "\nPlay as:\n1.Cross\n2.Circle\nYour Marker Choice: ";
        std::cin >> marker_choice;

        set_markers(marker_choice);
        game_loop();
    }

    void game_loop()
    {
        int player_move;
        bool game_over;

        do
        {
            game_interface();
            // check if all boxes are filled
            if (empty_box_count <= 0)
            {
                std::cout << "Game Draw\n";
                return;
            }

            std::cout << "Your Move: ";
            std::cin >> player_move;
            if (player_move > 0 && player_move <= 9)
                set_input_map(player_move - 1);
            else
                printf("Invalid Move, Move should be in range of 0-9\n");

            game_over = result();
        } while (!game_over);
    }

    void game_interface()
    {
        std::cout << "\n";
        for (int i = 0; i < 5; i++)
        {
            if (i % 2 == 0)
                std::cout << get_row(i / 2);
            else
                std::cout << "--- --- ---\n";
        }
        std::cout << "\n";
    }

    // sets player_move and computer_move in input_map
    void set_input_map(int player_move)
    {
        int computer_move, count = 0;

        // check if box is empty
        if (input_map[player_move / 3][player_move % 3] == BLANK)
            input_map[player_move / 3][player_move % 3] = player_marker;
        else
        {
            std::cout << "\nAlready Marked, Choose different Move!\n";
            return;
        }
        empty_box_count--;

        // random play by computer
        srand(time(NULL));
        do
        {
            computer_move = rand() % 9;
            if (input_map[computer_move / 3][computer_move % 3] == BLANK)
            {
                input_map[computer_move / 3][computer_move % 3] = computer_marker;
                empty_box_count--;
                break;
            }
        } while (empty_box_count > 0);
    }

    // sets up each row as a string for displaying, returns the row as a string
    std::string get_row(int row)
    {
        std::string row_string = "   |   |  \n";

        row_string[1] = get_symbol(input_map[row][0]);
        row_string[5] = get_symbol(input_map[row][1]);
        row_string[9] = get_symbol(input_map[row][2]);

        return row_string;
    }

    symbols game_logic()
    {
        int count = 0, i = 0;
        symbols marker;

        marker = input_map[i][i];

        // check columns
        for (i = 0; i < SIDE_SIZE; i++)
        {
            marker = input_map[i][0];
            if (marker == BLANK)
                continue;
            else if (input_map[i][2] == marker && input_map[i][1] == marker)
            {
                return marker;
            }
        }

        // check rows
        for (i = 0; i < SIDE_SIZE; i++)
        {
            marker = input_map[0][i];
            if (marker == BLANK)
                continue;
            else if (input_map[2][i] == marker && input_map[1][i] == marker)
            {
                return marker;
            }
        }

        // check diagonals
        marker = input_map[0][0];
        if (marker != BLANK && input_map[2][2] == marker && input_map[1][1] == marker)
        {
            return marker;
        }

        marker = input_map[0][2];
        if (marker != BLANK && input_map[2][0] == marker && input_map[1][1] == marker)
        {
            return marker;
        }
        return BLANK;
    }

    bool result()
    {
        symbols marker = game_logic();
        if (marker != BLANK)
        {
            game_interface();
            std::cout << get_symbol(marker) << " wins.\n";
            return true;
        }
        return false;
    }

    void game_menu()
    {
        std::cout << "\n - - - TIC TAC TOE - - -\n\n";
        std::cout << "1.Play\n";
        std::cout << "2.Exit\a\n";
    }

    // convert enumerated symbol to character
    char get_symbol(symbols marker)
    {
        switch (marker)
        {
        case CROSS:
            return 'X';
        case CIRCLE:
            return 'O';
        default:
            return ' ';
        }
    }

    // set player and computer markers
    void set_markers(int marker_choice)
    {
        switch (marker_choice)
        {
        case 1:
            player_marker = CROSS;
            computer_marker = CIRCLE;
            break;
        case 2:
            player_marker = CIRCLE;
            computer_marker = CROSS;
            break;
        }
    }

    // initializes and resets game value
    void setup_game()
    {
        for (int i = 0; i < BOX_COUNT; i++)
        {
            input_map[i / 3][i % 3] = BLANK;
        }
        empty_box_count = BOX_COUNT;
    }
};

int main()
{
    TicTacToe game;
    int choice;

    do
    {
        game.game_menu();
        std::cout << "Your Choice: ";
        std::cin >> choice;
        if (choice == 1)
        {
            game.initialize();
        }
    } while (choice != 2);

    return 0;
}