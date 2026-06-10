# 단일 파일 빠른 컴파일/실행용 Makefile
# 사용법:
#   make run FILE=src/main.cpp     # 컴파일 후 실행
#   make build FILE=src/main.cpp   # 컴파일만
#   make clean                     # build 디렉토리 정리

CXX      := clang++
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic -g
BUILDDIR := build
FILE     ?= src/main.cpp
BIN      := $(BUILDDIR)/$(notdir $(basename $(FILE)))

.PHONY: run build clean

build:
	@mkdir -p $(BUILDDIR)
	$(CXX) $(CXXFLAGS) $(FILE) -o $(BIN)

run: build
	@./$(BIN)

clean:
	@rm -rf $(BUILDDIR)
