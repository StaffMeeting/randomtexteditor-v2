CXX := g++
CXXFLAGS = -std=c++17 -w -O3 -march=native
TARGET = edit
MAIN = src/main.cpp
SRCS = src/main.cpp src/idk.h src/color.h src/inputer.h src/keymap.h
$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(MAIN) -o $(TARGET)
clean:
	rm $(TARGET)
