#include <iostream>
#include <fstream>
#include <cstdint>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <iomanip>
#include "idk.h"
#include "keymap.h"
int main(int argc,char** argv){
	restore_terminal();
	std::string name;
	if(argc <= 1){
		std::cout<<"which file\n";
		std::getline(std::cin,name);
	}else name = argv[1];

	std::fstream file(name);
	if(!file){
		std::ofstream create(name);
		create.close();
		file.open(name);
	}
	std::vector<std::string> content;
	std::string* buf = new std::string;
	while(std::getline(file,*buf))content.push_back(*buf);
	delete buf; buf = nullptr;
	if(content.empty())content.emplace_back(" ");
	init_getch(-1); clear();
	for(size_t i = 0; i < content.size(); ++i)
		std::cerr<<"\033["<<(i+1)<<";1H"<<std::setw(4)<<(i+1)<<"|"<<content[i];
	size_t line = 0,col = 0;
	for(int ch=0; ch != EXIT; ch = getch()){
		clear();
		switch(ch){
		case UP:{
			if(line > 0){
				if(col > content[line-1].size()) col = content[line-1].size()-1;
				line--;
		    }
			break;
		}
		case LEFT:{
			if(col > 0)col--;
			break;
		}
		case RIGHT:{
			if(col < content[line].size()-1)col++; 
			break;
		}
		case DOWN:{
			if(line < content.size()-1){
				if(col > content[line+1].size()) col = content[line+1].size()-1;
				line++;
			}
			break;
		}
		case ENTER:{
			std::string currline = content[line];
			std::string newline = currline.substr(col);
			content[line] = currline.substr(0,col);
			content.insert(content.begin()+line+1,newline);
			line++; col = 0; break;
		}
		case BACKSPACE:{
			if(col > 0){
				content[line].erase(col-1,1);col--;
				file.seekp(-1, std::ios_base::cur);
			}else if(line > 0){
				col = content[line-1].length();
				content[line-1] += content[line];
				content.erase(content.begin() + line); line--;
			}
			break;
		}
		case CONTROL:{
			std::string cmd;
			while((ch = fgetc(stdin)) != CONTROL){
				if(ch == '\n'){
					system(cmd.c_str()); cmd.clear();
				}else cmd += ch;
			}
			break;
		}
		default:{
			if(isprint(ch)){content[line].insert(col,1,ch); col++;}
			break;
		}
		}
		std::ofstream out(name);
		for(std::string l : content) out<<l<<'\n';
		for(int i = 0; i < content.size(); ++i){
			std::cerr<<std::setw(4)<<(i+1);
			fprintf(stderr,"|%s\n",content[i].c_str());
		}
		move(line,col+5);
	}
	file.close(); restore_terminal();
	return 0;
}
