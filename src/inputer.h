#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <termios.h>
#include <csignal>
#include <cstdio>
#include "keymap.h"
namespace {
    struct TermManager {
        termios original{};
        bool initialized = false;

        void init(int vtim) noexcept {
            if (initialized) return;
            
            tcgetattr(STDIN_FILENO, &original);
            
            termios config = original;
            config.c_lflag &= ~(ICANON | ECHO);
            config.c_cc[VTIME] = vtim;
            config.c_cc[VMIN] = 0;
            
            tcsetattr(STDIN_FILENO, TCSANOW, &config);
            
            initialized = true;
            
            std::signal(SIGINT, [](int) { term_restore(); exit(0); });
            std::signal(SIGTERM, [](int) { term_restore(); exit(0); });
            std::atexit(term_restore);
        }

        static void term_restore() noexcept {
            if (instance().initialized) {
                tcsetattr(STDIN_FILENO, TCSADRAIN, &instance().original);
                instance().initialized = false;
            }
        }

        static TermManager& instance() noexcept {
            static TermManager tm;
            return tm;
        }
    };
}

void init_getch(int vtim = 0) noexcept {
    TermManager::instance().init(vtim);
    fprintf(stderr,"\033[?25l");
}
void restore_terminal() noexcept {
    TermManager::instance().term_restore();
    fprintf(stderr,"\033[?25h");
}
int get_arrow_key() {
    char seq[3];
    if (read(STDIN_FILENO, &seq[0], 1) == 1 && seq[0] == '[') {
        if (read(STDIN_FILENO, &seq[1], 1) == 1) {
            switch (seq[1]) {
                case 'A': return UP;
                case 'B': return DOWN;
                case 'C': return RIGHT;
                case 'D': return LEFT;
            }
        }
    }
    return 0;
}
char getch() noexcept {
    char c = 0;
    if (read(STDIN_FILENO, &c, 1) == 1) {
        if (c == 27) return get_arrow_key();
        return c;
    }
    return 0;
}

bool read_byte(char& c) noexcept {
    return read(STDIN_FILENO, &c, 1) == 1;
}

