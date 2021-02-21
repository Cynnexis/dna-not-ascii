#!/usr/bin/make
ifneq (,$(wildcard ./.env))
	include .env
	export $(shell sed 's/=.*//' .env)
endif
SHELL := /bin/bash
SOURCE = $(wildcard src/*.cpp) $(wildcard src/*.hpp)
LIBS = $(wildcard lib/cpp_progress_bar/*.hpp) $(wildcard lib/cpp_progress_bar/*.cpp) $(wildcard lib/cpp-stopwatch/*.cpp) $(wildcard lib/cpp-stopwatch/*.h)
DEPS = $(SOURCE) $(LIBS) 
CMAKE_BUILD_TYPE=Release
.PHONY: clean compile run debug
.ONESHELL:

all: compile

help:
	@echo "DNA's Not ASCII Makefile"
	@echo ''
	@echo "  help                    - Display this text and exit."
	@echo "  compile                 - Compile the program by calling cmake."
	@echo "                            CMAKE_BUILD_TYPE: Specify the build type. Defaults to 'Release'."
	@echo "  clean                   - Remove build/ and docs/."
	@echo "  docs                    - Generate the Doxygen documentation."
	@echo "  run                     - Launch DNA's Not ASCII program."
	@echo "                            CMAKE_BUILD_TYPE: Specify the build type. Defaults to 'Release'."
	@echo "  debug                   - Compile the project as debug, and run GDB. You might need to clean the project before."
	@echo ''

clean:
	rm -rf build
	rm -rf docs
	rm -rf logs

build/Makefile:
	mkdir -p build
	cd build
	cmake -DCMAKE_BUILD_TYPE=$(CMAKE_BUILD_TYPE) ..
	cd ..

build/dna-not-ascii: build/Makefile $(DEPS)
	cd build
	rm -f dna-not-ascii
	make
	cd ..

compile: build/dna-not-ascii

run: build/dna-not-ascii
	@build/dna-not-ascii

debug:
	$(MAKE) compile CMAKE_BUILD_TYPE=Debug && \
	gdb build/dna-not-ascii

docs: $(SOURCE) doxy.conf
	doxygen doxy.conf
