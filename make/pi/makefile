
SOURCE = thinspace/src
SOURCE_GLHELPER = $(SOURCE)/glhelper
SOURCE_GL = $(SOURCE)/gl
SOURCE_GLSHAPE = $(SOURCE)/glshape
SOURCE_COMPONENT = $(SOURCE)/component
SOURCE_UTIL = $(SOURCE)/util
SOURCE_APPHELPER = $(SOURCE)/apphelper
SOURCE_CONTEXT = $(SOURCE)/context
SOURCE_APP = $(SOURCE)/app

OBJ_GLHELPER = $(wildcard $(SOURCE_GLHELPER)/**/*.cc)
OBJ_GLSHAPE = $(wildcard $(SOURCE_GLSHAPE)/**/*.cc)
OBJ_GL = $(wildcard $(SOURCE_GL)/**/*.cc)
OBJ_COMPONENT = $(wildcard $(SOURCE_COMPONENT)/**/*.cc)
OBJ_UTIL = $(wildcard $(SOURCE_UTIL)/**/*.cc)
OBJ_APPHELPER = $(wildcard $(SOURCE_APPHELPER)/**/*.cc)
OBJ_CONTEXT = $(wildcard $(SOURCE_CONTEXT)/**/*.cc)
OBJ_APP = app.cc
OBJ_MAIN = main_pi.cc
OBJ_PROJECT = $(wildcard src/**/*.cc)

FLAG_INCLUDE = -I$(SOURCE_GL) -I$(SOURCE_COMPONENT) -I$(SOURCE_UTIL) -I$(SOURCE_APP) -I$(SOURCE_APPHELPER) -I$(SOURCE_GLHELPER) -I$(SOURCE_GLSHAPE) -I$(SOURCE_CONTEXT) -I.
FLAG_DEBUG = -g
FLAG_PI = -ldrm -lgbm -lEGL -lGL -I/usr/include/libdrm
FLAG_IMAGE = -lfreeimage
FLAG_VAR = -DINCLUDE_GL_PI_4 -DDEFINE_GLSL_VERSION='"300 es"'

OBJ = $(OBJ_MAIN) $(OBJ_APP) $(OBJ_APPHELPER) $(OBJ_GL) $(OBJ_GLHELPER) $(OBJ_GLSHAPE) $(OBJ_UTIL) $(OBJ_COMPONENT) $(OBJ_CONTEXT) $(OBJ_PROJECT)
FLAG = $(FLAG_VAR) $(FLAG_INCLUDE) $(FLAG_PI) $(FLAG_IMAGE) 

O = bin/app

CC = g++
C++ = -std=c++11

main: $(OBJ)
	$(CC) $(C++) $(FLAG) $(OBJ) -o $(O)