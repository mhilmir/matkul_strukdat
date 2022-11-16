CXX?=g++
LSFML+= -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio
SOURCES=src/main.cpp

src/%.o : src/%.cpp  # ini proses compile (bikin .cpp jadi .o)
	$(CXX) -c -o $@ $^

main : $(SOURCES:.cpp=.o)  # ini proses linking (bikin .o jadi file executable)
	$(CXX) -o $@ $^ $(LSFML)
	rm src/*.o

clean :
	rm main