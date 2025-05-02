#include <iostream>
#include <string>
#include <unistd.h>
#include <termios.h>
void clear() {
    std::cerr<<"\033c";
}
void move(size_t y, size_t x) {
    std::cerr<<"\033["<<(y+1)<<";"<<(x+1)<<"H";
}
template <typename T>
void printscr(size_t y, size_t x, T output) {
    std::cerr<<"\033["<<(y+1)<<";"<<(x+1)<<"H";
    std::cerr<<output;
    std::cerr<<'\n';
}
template <typename T>
void highlight(size_t y, size_t x, T output) {
    std::cerr<<"\033["<<(y+1)<<";"<<(x+1)<<"H";
	std::cerr<<"\033[0;30;107m"<<output<<"\033[0m";
	std::cerr<<'\n';
}
template <typename T>
void printrgb(size_t y, size_t x, T output, int r, int g, int b) {
    std::cerr<<"\033["<<(y+1)<<";"<<(x+1)<<"H";
	std::cerr<<"\033[38;2;"<<r<<";"<<g<<";"<<b<<"m"<<output<<"\033[0m";
	std::cerr<<'\n';
}
template <typename T>
void printrgb(size_t y, size_t x, T output,int r, int g, int b, int br, int bg, int bb) {
    move(y,x);
    std::cerr<<"\033[48;2;"<<br<<";"<<bg<<";"<<bb<<"m"<<"\033[38;2;"<<r<<";"<<g<<";"<<b<<"m"<<output<<"\033[0m";
    std::cerr<<'\n';
}
