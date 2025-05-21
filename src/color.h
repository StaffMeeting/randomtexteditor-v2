#include <iostream>
#include <cstdio>
void move(size_t y,size_t x){
    fprintf(stderr,"\033[%zu;%zuH",y+1,x+1);
}
void clear(){
    fprintf(stderr,"\033c");
}
template <typename T>
void highlight(size_t y,size_t x,T output){
    move(y,x); std::cerr<<"\033[0;30;107m"<<output<<"\033[0m";
}
template <typename T>
void printrgb(size_t y,size_t x,T output,int r,int g,int b){
    move(y,x); std::cerr<<"\033[38;2;"<<r<<";"<<g<<";"<<b<<"m"<<output<<"\033[0m";
}
template <typename T>
void printrgb(size_t y,size_t x,T output,int r,int g,int b,int br,int bg,int bb) {
    move(y,x); std::cerr<<"\033[48;2;"<<br<<";"<<bg<<";"<<bb<<"m"<<"\033[38;2;"<<r<<";"<<g<<";"<<b<<"m"<<output<<"\033[0m";
}
