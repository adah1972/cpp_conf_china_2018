UNAME = $(shell uname)

ifeq ($(UNAME),Darwin)
CXX = g++-8  # gcc is really clang on macOS; using Homebrew GCC
else
CXX = g++
endif

CMCSTL2 = ../../cmcstl2
RANGEV3 = ../../range-v3
NVWA = ../../nvwa
EXT_DEPS = $(CMCSTL2)/include $(RANGEV3)/include $(NVWA)
INCLUDE  = $(patsubst %,-I%,$(EXT_DEPS))
CXXFLAGS = -W -Wall $(INCLUDE) -std=c++17 -fconcepts -DHAVE_NVWA

TARGET := $(patsubst %.cpp,%,$(wildcard test*.cpp))

.PHONY: all clean

all: $(TARGET)

clean:
	$(RM) $(TARGET)
