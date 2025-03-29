CC = g++
CFLAGS = -Wall -std=c++17 -g -fPIC
SRC =  $(wildcard src/**/**/*.cpp) $(wildcard src/**/*.cpp) $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = libboshi.so

ifeq ($(BACKEND_WINDOW_SDL2), 1)
CFLAGS += -DBOSHIBACKEND_WND_SDL2
LDFLAGS += -lSDL2
endif
ifeq ($(BACKEND_RENDER_GL), 1)
CFLAGS += -DBOSHIBACKEND_RND_GL
LDFLAGS += -lGL -lGLEW
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) -shared -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

install: $(TARGET)
	mkdir -p $(DESTDIR)/usr/lib $(DESTDIR)/usr/include/boshi $(DESTDIR)/usr/local/include/boshi
	cp $(TARGET) $(DESTDIR)/usr/lib/

	rsync -av --include='*/' --include='*.hpp' --exclude='*' src/ $(DESTDIR)/usr/include/boshi/
	rsync -av --include='*/' --include='*.hpp' --exclude='*' src/ $(DESTDIR)/usr/local/include/boshi/

clean:
	rm -f $(OBJ) $(TARGET)

