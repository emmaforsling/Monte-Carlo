Sources=main.cpp classes.cpp Object.cpp Ray.cpp Pixel.cpp Sphere.cpp Rectangle.cpp Cube.cpp Camera.cpp Light.cpp Wall.cpp
Executable=CornellBox

CFlags=-c -std=c++11 -g -Iinc -ffloat-store #-fopenmp
#If mac remove the LDFlags, since in this makefile the LDFlags are
#written to make the program runnable on Windows…
LDFlags=-Wl,--large-address-aware #-fopenmp
#--large-address-aware to allow 32-bit windows more than 2 Gb memory
LDFlags= #-fopenmp
ObjectDir=CornellBox/obj/
SourceDir=CornellBox/src/
BinDir=CornellBox/bin/

CC=g++
RM=rm

Objects=$(Sources:.cpp=.o)
CSources=$(addprefix $(SourceDir),$(Sources))
CObjects=$(addprefix $(ObjectDir),$(Objects))
CExecutable=$(addprefix $(BinDir),$(Executable))

default: all

all: $(CSources) $(CExecutable)

run: $(CExecutable) 
	./$(addprefix $(BinDir),$(Executable))

sense: room1 clean all room2 run

sound:
	@say ”Nu du Martin har du allt skitit i det blå skåpet”

room:
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""

room1:
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo "=========== cleaning and compiling ==========="
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""

room2:
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo ""
	@echo "================== running =================="
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