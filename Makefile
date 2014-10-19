Sources=main.cpp classes.cpp Object.cpp Ray.cpp Pixel.cpp Sphere.cpp Rectangle.cpp Cube.cpp Camera.cpp Light.cpp Wall.cpp
Executable=CornellBox

CFlags=-c -std=c++11 -g -Iinc
LDFlags=
ObjectDir=CornellBox/obj/
SourceDir=CornellBox/src/
BinDir=CornellBox/bin/

CC=g++
RM=rm

#!!!!!DO NOT EDIT ANYTHING UNDER THIS LINE!!!!!
Objects=$(Sources:.cpp=.o)
CSources=$(addprefix $(SourceDir),$(Sources))
CObjects=$(addprefix $(ObjectDir),$(Objects))
CExecutable=$(addprefix $(BinDir),$(Executable))

default: all

all: $(CSources) $(CExecutable)

run: $(CExecutable) 
	./$(addprefix $(BinDir),$(Executable))

sense: room clean all run

room:
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""

$(CExecutable): $(CObjects)
	$(CC) $(LDFlags) $(CObjects) -o $@

$(ObjectDir)%.o: $(SourceDir)%.cpp
	$(CC) $(CFlags) $< -o $@

clean:
	$(RM) $(CObjects)