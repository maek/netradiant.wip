# Local Makefile

.SUFFIXES:
.NOTPARALLEL:

SHELL = /bin/sh


.PHONY: default
default: radiant


.PHONY: radiant
radiant:
	@install -dv build
	@cd build && cmake -DCMAKE_BUILD_TYPE=Debug\
	                   -DDOWNLOAD_GAMEPACKS=OFF\
	                   ..
	@cd build && cmake --build . -- -j$(shell nproc)
	@install -dv build/games
	@./install-gamepacks.sh build
	@echo "[ [32mOK[0m ]"


.PHONY: radiant.exe
radiant.exe:
	@install -dv build
	@cd build && cmake -DCMAKE_BUILD_TYPE=Debug\
	                   -DDOWNLOAD_GAMEPACKS=OFF\
	                   -DCMAKE_TOOLCHAIN_FILE=../cmake/cross-toolchain-mingw64.cmake\
	                   ..
	@cd build && cmake --build . -- -j$(shell nproc)
	@echo "[ [32mOK[0m ]"


.PHONY: q3map2
q3map2:
	@install -dv build
	@cd build && cmake -DCMAKE_BUILD_TYPE=Debug\
	                   ..
	@cd build && cmake --build . --target q3map2 -- -j$(shell nproc)
	@echo "[ [32mOK[0m ]"


.PHONY: q3map2.exe
q3map2.exe:
	@install -dv build
	@cd build && cmake -DCMAKE_BUILD_TYPE=Debug\
	                   -DCMAKE_TOOLCHAIN_FILE=../cmake/cross-toolchain-mingw64.cmake\
	                   ..
	@cd build && cmake --build . --target q3map2 -- -j$(shell nproc)
	@echo "[ [32mOK[0m ]"


.PHONY: clean
clean:
	@$(RM) -rv build
