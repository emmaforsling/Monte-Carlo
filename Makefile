Sources=main.cpp classes.cpp Ray.cpp Pixel.cpp Sphere.cpp Rectangle.cpp Cube.cpp Light.cpp Wall.cpp
Executable=CornellBox

CFlags=-c -Wall -g -Iinc
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

all: $(CSources) $(CExecutable)

run: $(CExecutable) 
	./$(addprefix $(BinDir),$(Executable))

$(CExecutable): $(CObjects)
	$(CC) $(LDFlags) $(CObjects) -o $@

$(ObjectDir)%.o: $(SourceDir)%.cpp
	$(CC) $(CFlags) $< -o $@

clean:
	$(RM) $(CObjects)