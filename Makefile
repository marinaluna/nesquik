BINARY := build/ajax
SRCS := $(shell find . -iname "*.cpp")
OBJS := $(addprefix build/,$(SRCS:.cpp=.o))

NEEDED_LIBS := 
NEEDED_FRAMEWORKS := SDL2

CXX := clang++ -flto
LD := $(CXX) $(addprefix libs/,$(NEEDED_LIBS)) $(addprefix -framework ,$(NEEDED_FRAMEWORKS))
override CXXFLAGS += -std=c++17 -F/usr/local/Frameworks
override LDFLAGS += $(CXXFLAGS)

all:$(BINARY)

$(BINARY):$(OBJS) $(addprefix libs/,$(NEEDED_LIBS))
	$(LD) $(LDFLAGS) -o $@ $^

build/%.o:%.cpp
	$(CXX) -O2 -c $(CXXFLAGS) $< -o $@

run:$(BINARY)
	@$(BINARY) ~/Desktop/NES/rom.nes

clean:
	rm -rf build
	mkdir build
	mkdir build/src
	mkdir build/src/core
	mkdir build/src/core/memory
	mkdir build/src/core/memory/mappers
	mkdir build/src/common
	mkdir build/src/debug