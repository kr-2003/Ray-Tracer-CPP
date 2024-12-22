# Define target binary
linkTarget = programfile

# Define compiler and standard
CXX = clang++
CXXFLAGS = -std=c++17 -O3 -flto -Ofast

# Include paths
INCLUDE_PATHS = \
    -I/opt/homebrew/Cellar/sdl2/2.30.10/include

# Library paths and libraries
LIB_PATHS = -L/opt/homebrew/Cellar/sdl2/2.30.10/lib
LIBS = -lSDL2

# Source files
SRC = main.cpp CApp.cpp $(wildcard RayTrace/*.cpp)

# Object directory
OBJDIR = .objs

# Object files (preserving directory structure under OBJDIR)
OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRC))

# Rule to build the target
$(linkTarget): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) $(LIB_PATHS) $(LIBS) -o $@

# Rule to compile .cpp files to .o files
$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< $(INCLUDE_PATHS) -o $@

# Clean rule
.PHONY: clean
clean:
	rm -f $(OBJS) $(linkTarget)
	find $(OBJDIR) -type d -empty -delete 2>/dev/null || true
