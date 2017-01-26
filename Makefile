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
	                   -DDOWNLOAD_GAMEPACKS=ON\
	                   -DRADIANT_ABOUTMSG="Lorem Ipsum..."\
	                   ..
	@cd build && cmake --build . -- -j4
	@echo "[ [32mOK[0m ]"


.PHONY: clean
clean:
	@$(RM) -rv build
