/*
     _    _      _                            _____       _____ _
    | |  | |    | |                          |_   _|     /  __ \ |                    _     _
    | |  | | ___| | ___ ___  _ __ ___   ___    | | ___   | /  \/ |__   ___  ___ ___ _| |_ _| |_
    | |/\| |/ _ \ |/ __/ _ \| '_ ` _ \ / _ \   | |/ _ \  | |   | '_ \ / _ \/ __/ __|_   _|_   _|
    \  /\  /  __/ | (_| (_) | | | | | |  __/   | | (_) | | \__/\ | | |  __/\__ \__ \ |_|   |_|
     \/  \/ \___|_|\___\___/|_| |_| |_|\___|   \_/\___/   \____/_| |_|\___||___/___/
*/

#include <iostream>


static enum GameState : uint8_t {
    NoWinner,
    WhiteWins,
    BlackWins
};

// (First bit reserved for color 1b)[Type 3b]'[Val 4b] : 0b0000'0000
static enum Piece : uint8_t {
	None =      0b0000'0000,

    WPawn =     0b0001'0001,
    WKnight =   0b0010'0011,
    WBishop =   0b0011'0011,
    WRook =     0b0100'0101,
    WQueen =    0b0101'1001,
    WKing =     0b0110'1111,

    BPawn =     0b1001'0001,
    BKnight =   0b1010'0011,
    BBishop =   0b1011'0011,
    BRook =     0b1100'0101,
    BQueen =    0b1101'1001,
    BKing =     0b1110'1111,
};

static char toChar(const Piece& piece) {
    switch (piece >> 4) {
        case 1: case 9: return 'P'; break;
        case 2: case 10: return 'N'; break;
        case 3: case 11: return 'B'; break;
        case 4: case 12: return 'R'; break;
        case 5: case 13: return 'Q'; break;
        case 6: case 14: return 'K'; break;
        default:return ' ';
    }
}

class Board {
private:
    GameState gameState = NoWinner;
    Piece BoardData[8][8] = {
        { BRook,    BKnight,    BBishop,    BQueen,     BKing,      BBishop,    BKnight,    BRook },
        { BPawn,    BPawn,      BPawn,      BPawn,      BPawn,      BPawn,      BPawn,      BPawn }, 
		{ None,     None,       None,       None,       None,       None,       None,       None  },
		{ None,     None,       None,       None,       None,       None,       None,       None  },
		{ None,     None,       None,       None,       None,       None,       None,       None  },
		{ None,     None,       None,       None,       None,       None,       None,       None  },
		{ WPawn,    WPawn,      WPawn,      WPawn,      WPawn,      WPawn,      WPawn,      WPawn },
		{ WRook,    WKnight,    WBishop,    WQueen,     WKing,      WBishop,    WKnight,    WRook }
    };
public:
    void DrawBoard() {
        for (int y = 0; y < 8; y++) {
            for (int x = 0; x < 8; x++) {
                std::cout << ((x + y) % 2 == 0 ? "\x1b[48;2;241;217;192m" : "\x1b[48;2;169;122;101m"); // Background color.
                std::cout << (BoardData[y][x] >> 7 != 1 ? "\x1b[38;2;255;255;255m" : "\x1b[38;2;0;0;0m"); // Foreground color.

                std::cout << " " << toChar(BoardData[y][x]) << " ";

                std::cout << "\x1b[0m"; // Reset Color.
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    Board board = Board();

    // Welcome message.
    std::cout << " _    _      _                            _____       _____ _                               " << std::endl;
    std::cout << "| |  | |    | |                          |_   _|     /  __ \\ |                    _     _   " << std::endl;
    std::cout << "| |  | | ___| | ___ ___  _ __ ___   ___    | | ___   | /  \\/ |__   ___  ___ ___ _| |_ _| |_ " << std::endl;
    std::cout << "| |/\\| |/ _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\   | |/ _ \\  | |   | '_ \\ / _ \\/ __/ __|_   _|_   _|" << std::endl;
    std::cout << "\\  /\\  /  __/ | (_| (_) | | | | | |  __/   | | (_) | | \\__/\\ | | |  __/\\__ \\__ \\ |_|   |_|  " << std::endl;
    std::cout << " \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|   \\_/\\___/   \\____/_| |_|\\___||___/___/            \n\n" << std::endl;

    std::cout << "Press [ENTER] to start!";
    std::cin.get();

    do {
        std::cout << "\033[2J\033[H"; // Clear the console.
        board.DrawBoard();

        // Print out Algebraic Chess Notation guide.
        std::cout << "\033[1;28H"; // Move to right side of chess board.
        std::cout << "Algebraic Chess Notation:";
        std::cout << "\033[2;28H"; // Move to right side of chess board.
        std::cout << "\tidk gl bro.";
        std::cout << "\033[9;1H"; // Reset to bottom of board.

        std::cout << "\nYour move:";
        std::cin.get();
    } while (true);

    std::cout << "\n\nPress [ENTER] to close the program.";
    std::cin.get();
    return 0;
}