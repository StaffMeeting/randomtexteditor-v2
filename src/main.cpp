#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "idk.h"
#include "keymap.h"
int main(int argc, char* argv[]) {
	restore_terminal();
	std::string name, buffer;
	if (argc <= 1) {
		std::cout << "Enter filename: ";
		std::getline(std::cin, name);
	} else {
		name = argv[1];
	}

	std::fstream file(name);
	if (!file) {
		std::ofstream create(name);
		create.close();
		file.open(name);
	}

	std::vector<std::string> content;
	while (std::getline(file, buffer)) {
		content.push_back(buffer);
	}
	if (content.empty()) content.emplace_back(" ");

	init_getch(-1);
	clear();

	for (size_t i = 0; i < content.size(); ++i) {
		std::cerr<<"\033["<<(i+1)<<";1H"<<std::setw(4)<<(i+1)<<"|"<<content[i];
	}
	int line = 0, col = 0, ch;
	printrgb(line,col+5,content[line][col],0,0,0,255,255,255);

	while((ch = getch()) != EXIT) {
		clear();
		init_getch(-1);
		switch(ch) {
		case UP: {
			if (line > 0) {
				if (col > content[line-1].size()) col = content[line-1].size()-1;
				line--;
			}
			break;
		}
		case LEFT: {
			if (col > 0) {
				col--;
			}
			break;
		}
		case RIGHT: {
			if (col < content[line].size()-1) {
				col++;
			}
			break;
		}
		case DOWN: {
			if (line < content.size()-1) {
				if (col > content[line+1].size()) col = content[line+1].size()-1;
				line++;
			}
			break;
		}
		case ENTER: {
			std::string currline = content[line];
			std::string newline = currline.substr(col);
			content[line] = currline.substr(0, col);
			content.insert(content.begin()+line+1, newline);
			line++;
			col = 0;
			break;
		}
		case BACKSPACE: {
			if (col > 0) {
				content[line].erase(col-1, 1);
				col--;
			} else if (line > 0) {
				col = content[line-1].length();
				content[line-1] += content[line];
				content.erase(content.begin() + line);
				line--;
			}
			break;
		}
		case CONTROL: {
			std::string cmd;
			restore_terminal();
			while ((ch = getch()) != CONTROL) {
				cmd = "";
				getline(std::cin, cmd);
				system(cmd.c_str());
			}
			init_getch(-1);
			break;
		}
		default: {
			if(isprint(ch)) {
				content[line].insert(col,1,ch);
				col++;
			}
			break;
		}
		}
		std::ofstream out(name);
		for(const auto& l : content) out<<l<<'\n';
		for (size_t i = 0; i < content.size(); ++i) {
			std::cerr<<"\033["<<(i+1)<<";1H"<<std::setw(4)<<(i+1)<<"|"<<content[i];
		}
		printrgb(line,col+5,content[line][col],0,0,0,255,255,255);
	}
	restore_terminal();
	return 0;
}
