# Local Makefile

.SUFFIXES:
.NOTPARALLEL:

SHELL = /bin/sh


.PHONY: default
default: netradiant


.PHONY: netradiant
netradiant:
	@install -dv build
	@cd build && cmake -DCMAKE_BUILD_TYPE=Debug\
	                   -DDOWNLOAD_GAMEPACKS=OFF\
	                   ..
	@cd build && cmake --build . -- -j4
	@install -dv build/games
	@./install-gamepacks.sh build
	@echo "[ [32mOK[0m ]"


.PHONY: clean
clean:
	@$(RM) -rv build
