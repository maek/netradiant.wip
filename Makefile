# Local Makefile

.SUFFIXES:
.NOTPARALLEL:

SHELL = /bin/sh


.PHONY: default
default: netradiant


.PHONY: netradiant
netradiant:
	@install -dv build
	@cd build && cmake ..
	@cd build && cmake --build . -- -j4


.PHONY: clean
clean:
	@$(RM) -rv build
