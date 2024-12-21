# Define target binary
linkTarget = programfile

# Define compiler and standard
CXX = clang++
CXXFLAGS = -std=c++17 -O3 -flto -Ofast

# Include paths
INCLUDE_PATHS = \
    -I/opt/homebrew/Cellar/sdl2/2.30.10/include \

# Library paths and libraries
LIB_PATHS = -L/opt/homebrew/Cellar/sdl2/2.30.10/lib
LIBS = -lSDL2

# Source files
SRC = main.cpp CApp.cpp $(wildcard RayTrace/*.cpp)

# Object directory
OBJDIR = .objs

# Object files (derived from sources)
OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(patsubst %.c,$(OBJDIR)/%.o,$(SRC)))

# Rule to build the target
$(linkTarget): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(INCLUDE_PATHS) $(LIB_PATHS) $(LIBS) -o $(linkTarget)

# Rule to compile .cpp and .c files to .o files
$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) -c $< $(INCLUDE_PATHS) -o $@

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CXX) -std=c99 -c $< $(INCLUDE_PATHS) -o $@

# Clean rule
.PHONY: clean
clean:
	rm -f $(OBJS) $(linkTarget)
	rmdir $(OBJDIR) 2>/dev/null || true