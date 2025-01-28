CFLAGS = -O3
LDFLAGS =
appname = test

all: $(appname)
clean:
    rm -f $(appname) *.o
.PHONY: all clean

sdl_cflags := $(shell pkg-config --cflags sdl2 SDL2_mixer)
sdl_libs := $(shell pkg-config --libs sdl2 SDL2_mixer)
override CFLAGS += $(sdl_cflags)
override LIBS += $(sdl_libs)

$(appname): test.o
    $(CC) $(LDFLAGS) -o $@ $^ $(LIBS)
