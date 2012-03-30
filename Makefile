UNAME := $(shell uname)

COMPILERFLAGS = -Wall

ifeq ($(UNAME), Linux)
INCLUDE = -I/usr/include/
LIBDIR  = -L/usr/X11R6/lib 
LIBRARIES = -lX11 -lXi -lXmu -lglut -lGL -lGLU -lm 
endif

ifeq ($(UNAME), Darwin)
FRAMEWORK = -framework GLUT
FRAMEWORK += -framework OpenGL
LIBDIR = -L"/System/Library/Frameworks/OpenGL.framework/Libraries"
LIBRARIES = -lGL -lGLU
endif

CC = gcc
CFLAGS = $(COMPILERFLAGS) $(INCLUDE)

all: diamond
diamond:main.o
	$(CC) $(FRAMEWORK) $(CFLAGS) -o $@ $(LIBDIR) $< $(LIBRARIES)  
clean:
	rm -f diamond main.o

