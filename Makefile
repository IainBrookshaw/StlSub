#
# Makefile for STL Mesh Subdivision
#
# This code is intended for compilation bythe GCC ONLY. GCC unique pre-proccessor
# flags exist!
#
# NOTE: To run this the test program, you need to export the current 
#       directory to the LD_LIBRARY_PATH environment var. This is done
#       automatically by the make process.
# 
# Author:    Iain Brookshaw
# Date:      05 December 2016
# Version    1.0
# Copyright: GPL
#
################################################################################
VERSION = 1.0


# ------------------------------------------------------------------------------
# Directories and Files
#
TARGET_BASE     = libstlsubdiv.so
TARGET_VERSION  = 1
TARGET_REVISION = 0
TARGET_NO       = 0
TARGET      = $(TARGET_BASE).$(TARGET_VERSION).$(TARGET_REVISION).$(TARGET_NO)

HEADERS    = include
BUILDDIR   = build
SOURCEDIR  = src
TESTDIR    = unit_tests
EXESOURCE = $(SOURCEDIR)/refinestl.cpp
EXETARGET = refinestl

# main program sources and objects
SOURCES     = $(wildcard $(SOURCEDIR)/*.cpp)
OBJECTS     = $(patsubst $(SOURCEDIR)/%.cpp,$(BUILDDIR)/%.o, $(SOURCES))
EXEOBJECTS = $(BUILDDIR)/stlsubdiv.o

# tests sources, objects and targets
TEST_TARGET = ./$(TESTDIR)/all_tests
TEST_SRC    = $(wildcard $(TESTDIR)/*.cpp)
TEST_OBJ    = $(patsubst $(TESTDIR)/%.cpp,$(BUILDDIR)/%.o, $(TEST_SRC) )

.PHONY: 
	install uninstall clean exe $(EXETARGET) all tests
# ------------------------------------------------------------------------------



# ------------------------------------------------------------------------------
# Compiler and CPPFLAGS
#
CXX             = g++
CPPFLAGS       := -fPIC -g -Wall -std=c++11 -I$(HEADERS) 
TEST_CPPFLAGS  := -I/usr/include/gtest -g -Wall -std=c++11 -I$(HEADERS) 
# ------------------------------------------------------------------------------



# ------------------------------------------------------------------------------
# Libraries and Linking
#
LIBS          = -lm
TEST_LIBS     = $(LIBS) -lgtest -lgtest_main -lstlsubdiv -pthread
#
LDFLAGS      := -shared -L/usr/local/lib -L/usr/lib 
TEST_LDFLAGS := -L/usr/local/lib -L/usr/lib 
# ------------------------------------------------------------------------------



# ------------------------------------------------------------------------------
# Make Rules for library
# 
$(TARGET): $(OBJECTS)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) $(OBJECTS) -o $(TARGET)  $(LIBS) 
	# rm -r $(BUILDDIR)

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.cpp
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -c $< -o $@
# ------------------------------------------------------------------------------



# ------------------------------------------------------------------------------
#  Make unit Test Rules
# 
tests: $(TEST_TARGET)
	@echo "[MAKE]: making test target: " $(TEST_TARGET)
	$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJ) $(TARGET)
	@echo "[MAKE]: compiling test ($(TEST_TARGET)) from test-objs ($(TEST_OBJ))"
	$(CXX) -L./ $(TEST_CPPFLAGS) $(TEST_LDFLAGS) $(TEST_OBJ) -o $@  $(TEST_LIBS)

$(BUILDDIR)/%.o: $(TESTDIR)/%.cpp
	@echo "[MAKE]: compiling test objects..."
	$(CXX) $(TEST_CPPFLAGS) $(TEST_LDFLAGS) -c $< -o $@
# ------------------------------------------------------------------------------



# ------------------------------------------------------------------------------
# Other Rules...
#
# --- build stand-alone executable
exe: $(EXETARGET)
#
$(EXETARGET): $(TARGET) $(EXEOBJECTS) 
	$(CXX) $(CPPFLAGS)  $(LDFAGS) $(EXEOBJECTS) -o $(EXETARGET) $(LIBS) -L./ -lstlsubdiv
#
$(EXEOBJECTS): $(EXESOURCE)
	$(CXX) $(CPPFLAGS) $(LDFLAGS)  -c $< -o $@
#
#
all: $(TARGET) install $(EXETARGET) 
#
#
install: $(TARGET)
	@echo "Installing $(TARGET) to system (needs root privileges)..."
	sudo cp $(TARGET) /usr/local/lib
	sudo ln -s /usr/local/lib/$(TARGET) /usr/local/lib/$(TARGET_BASE).$(TARGET_VERSION)
	sudo ln -s /usr/local/lib/$(TARGET_BASE).$(TARGET_VERSION) /usr/local/lib/$(TARGET_BASE)
	sudo ldconfig
#
uninstall: $(TARGET)
	sudo rm /usr/local/lib/$(TARGET)
	sudo rm /usr/local/lib/$(TARGET_BASE).$(TARGET_VERSION)
	sudo rm /usr/local/lib/$(TARGET_BASE)
	sudo ldconfig
#
# --- clean everything
clean:
	-rm -f $(TARGET) $(OBJECTS) $(EXETARGET) $(EXEOBJECTS) $(TEST_OBJ) $(TEST_TARGET)
# ------------------------------------------------------------------------------
