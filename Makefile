CXX := g++
CXXFLAGS = -std=c++17 -O3 -march=native
TARGET = editor
MAIN = src/main.cpp
SRCS = src/main.cpp src/idk.h src/color.h src/inputer.h src/keymap.h
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(MAIN) -o $(TARGET)
clean:
	rm $(TARGET)
