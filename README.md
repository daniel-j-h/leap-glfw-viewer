leap-glfw-viewer
================

Integrating the Leap Motion input handling into a basic GLFW 3 application.
This is more or less my experimental playground and / or a template for more advanced applications.


Requirements
------------

* Leap SDK (tested with Leap-0.8.0-x64 on GNU/Linux Gentoo)
* GCC (tested with 4.7.3) or Clang (tested with 3.3)
* GLFW 3 (installation instruction below)


Dependencies
-------------

Build and install the latest GLFW 3 release:

    git clone https://github.com/glfw/glfw.git
    cd glfw
    git checkout 3.0.1
    mkdir build
    cd build
    cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_SHARED_LIBS=ON -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_INSTALL=ON
    make -j 4
    sudo make install
    sudo ldconfig

Note: Should be done by the build system (e.g. CMake)


Building
--------

Check the Makefile; you probably have to customize some settings.

    make

Start the leapd daemon and use your fingers as input.

    leapd
    ./leap-glfw-viewer

Note: Close with ESC keypress

