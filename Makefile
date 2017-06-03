BIN_DIR := bin
SRC_DIR := src

TARGET := $(BIN_DIR)/kal

SRC_EXT := cpp
SOURCES := $(shell find $(SRC_DIR) -type f -name *.$(SRC_EXT))
INC := -I llvm/include -I llvm/build/include -I include

CXX := llvm-g++
CXXFLAGS := -g $(INC)
LLVMFLAGS = `llvm-config --cxxflags --ldflags --system-libs --libs all`

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(LLVMFLAGS) $^ -o $@

clean:
	$(RM) -rf $(BIN_DIR)/*

.PHONY: clean
