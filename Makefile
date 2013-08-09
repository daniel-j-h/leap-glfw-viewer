# pkg-config does not look at /usr/local, so if you installed glfw locally, you have to set this
PKG_CONFIG_PATH=/usr/local/lib/pkgconfig

CXX ?= g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -O2 `pkg-config --cflags glfw3`
LDFLAGS = `pkg-config --libs glfw3` -lLeap
TARGET = leap-glfw-viewer

# adjust leap specific settings
LEAP_SDK ?= ~/leap/Leap_Developer_Kit_0.8.0_5300_Linux/LeapSDK
ARCH ?= x64


all: $(TARGET)


$(TARGET): Main.o Renderer.o
	@$(CXX) $(LDFLAGS) $(CXXFLAGS) -L $(LEAP_SDK)/lib/$(ARCH) Main.o Renderer.o -o $(TARGET)

Main.o: Main.cpp
	@$(CXX) $(CXXFLAGS) -I $(LEAP_SDK)/include -c $<

Renderer.o: Renderer.cpp Renderer.h
	@$(CXX) $(CXXFLAGS) -I $(LEAP_SDK)/include -c $<


clean:
	rm -f *.o $(TARGET)
