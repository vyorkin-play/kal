PROJECT := kal
VERSION := 0.1.0

STANDARD := -std=c++14
WARNINGS := -Wall -Wextra -pedantic
DEFINES = -DNAME="\"$(PROJECT)\"" -DVERSION="\"$(VERSION)\""

BIN_DIR := bin
SRC_DIR := src

TARGET := $(BIN_DIR)/kal

SRC_EXT := cpp
SOURCES := $(wildcard **/*.$(SRC_EXT))
INCLUDES := -I include
LLVMFLAGS = `llvm-config --cxxflags --ldflags --system-libs --libs all`

CXX := llvm-g++
CXXFLAGS := $(STANDARD) $(WARNINGS) $(DEFINES) $(INCLUDES) $(LLVMFLAGS)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	$(RM) -rf $(BIN_DIR)/*

.PHONY: clean
