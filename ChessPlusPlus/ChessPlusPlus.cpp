/*
     _    _      _                            _____       _____ _
    | |  | |    | |                          |_   _|     /  __ \ |                    _     _
    | |  | | ___| | ___ ___  _ __ ___   ___    | | ___   | /  \/ |__   ___  ___ ___ _| |_ _| |_
    | |/\| |/ _ \ |/ __/ _ \| '_ ` _ \ / _ \   | |/ _ \  | |   | '_ \ / _ \/ __/ __|_   _|_   _|
    \  /\  /  __/ | (_| (_) | | | | | |  __/   | | (_) | | \__/\ | | |  __/\__ \__ \ |_|   |_|
     \/  \/ \___|_|\___\___/|_| |_| |_|\___|   \_/\___/   \____/_| |_|\___||___/___/
*/

#include <iostream>
#include <string>

class Console {
public:
    static void ForegroundColor(int Red, int Green, int Blue) { 
        std::cout << "\x1b[38;2;" << Red << ";" << Green << ";" << Blue << "m"; 
    }
    static void BackgroundColor(int Red, int Green, int Blue) { 
        std::cout << "\x1b[48;2;" << Red << ";" << Green << ";" << Blue << "m"; 
    }
    static void ResetColor() { std::cout << "\x1b[0m"; }

    static void Write(const std::string& str = "") { std::cout << str; }
    static void WriteLine(const std::string& str = "") { std::cout << str << std::endl; }
    static void Write(char chr) { std::cout << chr; }
    static void WriteLine(char chr) { std::cout << chr << std::endl; }

    static void Clear() { std::cout << "\033[2J\033[H"; }

    static void MoveCursor(int x, int y) { std::cout << "\033[" << x << ";" << y << "H"; }
    static void ResetCursor() { std::cout << "\033[9;1H"; }

    static std::string ReadLine() { 
        std::string str;
        std::getline(std::cin, str);
        return str;
    }
};



enum GameState : uint8_t {
    NoWinner,
    WhiteWins,
    BlackWins
};

// (First bit reserved for color 1b)[Type 3b]'[Val 4b] : 0b0000'0000
enum Piece : uint8_t {
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

char toChar(const Piece& piece) {
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
    Piece Data[8][8] = {
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
                (x + y) % 2 == 0 ? Console::BackgroundColor(241, 217, 192) : Console::BackgroundColor(169, 122, 101);
                Data[y][x] >> 7 != 1 ? Console::ForegroundColor(255, 255, 255) : Console::ForegroundColor(45, 45, 45);

                Console::Write(" " + std::string(1, toChar(Data[y][x])) + " ");

                Console::ResetColor();
            }
            Console::WriteLine();
        }
    }
};

int main() {
    Board board = Board();

    // Welcome message.
    Console::WriteLine(" _    _      _                            _____       _____ _                               ");
    Console::WriteLine("| |  | |    | |                          |_   _|     /  __ \\ |                    _     _   ");
    Console::WriteLine("| |  | | ___| | ___ ___  _ __ ___   ___    | | ___   | /  \\/ |__   ___  ___ ___ _| |_ _| |_ ");
    Console::WriteLine("| |/\\| |/ _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\   | |/ _ \\  | |   | '_ \\ / _ \\/ __/ __|_   _|_   _|");
    Console::WriteLine("\\  /\\  /  __/ | (_| (_) | | | | | |  __/   | | (_) | | \\__/\\ | | |  __/\\__ \\__ \\ |_|   |_|  ");
    Console::WriteLine(" \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|   \\_/\\___/   \\____/_| |_|\\___||___/___/            \n\n");

    Console::Write("Press [ENTER] to start!");
    Console::ReadLine();

    do {
        Console::Clear();
        board.DrawBoard();

        // Print out Algebraic Chess Notation guide.
        Console::MoveCursor(1, 28);
        Console::Write("Algebraic Chess Notation:");
        Console::MoveCursor(2, 28);
        Console::Write("\tidk gl bro.");
        Console::ResetCursor();

        Console::Write("\nYour move:");
        Console::ReadLine();
    } while (false);

    Console::Write("\n\nPress [ENTER] to close the program.");
    Console::ReadLine();
    return 0;
}