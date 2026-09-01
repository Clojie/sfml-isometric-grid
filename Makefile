CXX      = g++
CXXFLAGS = -std=c++17 -O2 -arch arm64 \
           -I/opt/homebrew/opt/sfml@2/include
LDFLAGS  = -L/opt/homebrew/opt/sfml@2/lib \
           -lsfml-graphics -lsfml-window -lsfml-system

TARGET = isometric_grid
SRC    = main.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) $(LDFLAGS) -o $(TARGET)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET)

