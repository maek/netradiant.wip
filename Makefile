# CMakefile

.SUFFIXES:
.NOTPARALLEL:

SHELL = /bin/sh
BUILDDIR = $(CURDIR)/build


.PHONY: default
default: radiant


.PHONY: radiant
radiant: | $(BUILDDIR)
	@test -f "$(BUILDDIR)/Makefile" ||\
	(cd "$(BUILDDIR)" && cmake -DCMAKE_BUILD_TYPE=Debug\
	                           -DDOWNLOAD_GAMEPACKS=OFF\
	                           ..)
	@cd "$(BUILDDIR)" && cmake --build . -- -j$(shell nproc)
	@install -dv "$(BUILDDIR)/games"
	@./install-gamepacks.sh "$(BUILDDIR)"
	@echo "[ [32mOK[0m ]"


.PHONY: radiant.exe
radiant.exe: | $(BUILDDIR)
	@test -f "$(BUILDDIR)/Makefile" ||\
	(cd "$(BUILDDIR)" && cmake -DCMAKE_BUILD_TYPE=Debug\
	                           -DDOWNLOAD_GAMEPACKS=OFF\
	                           -DCMAKE_TOOLCHAIN_FILE=../cmake/Toolchain-mingw-w64.cmake\
	                           ..)
	@cd "$(BUILDDIR)" && cmake --build . -- -j$(shell nproc)
	@install -dv "$(BUILDDIR)/games"
	@./install-gamepacks.sh "$(BUILDDIR)"
	@echo "[ [32mOK[0m ]"


.PHONY: q3map2
q3map2: | $(BUILDDIR)
	@test -f "$(BUILDDIR)/Makefile" ||\
	(cd "$(BUILDDIR)" && cmake -DCMAKE_BUILD_TYPE=Debug\
	                           ..)
	@cd "$(BUILDDIR)" && cmake --build . --target q3map2 -- -j$(shell nproc)
	@echo "[ [32mOK[0m ]"


.PHONY: q3map2.exe
q3map2.exe: | $(BUILDDIR)
	@test -f "$(BUILDDIR)/Makefile" ||\
	(cd "$(BUILDDIR)" && cmake -DCMAKE_BUILD_TYPE=Debug\
	                           -DCMAKE_TOOLCHAIN_FILE=../cmake/Toolchain-mingw-w64.cmake\
	                           ..)
	@cd "$(BUILDDIR)" && cmake --build . --target q3map2 -- -j$(shell nproc)
	@echo "[ [32mOK[0m ]"


$(BUILDDIR):
	@install -dv "$(BUILDDIR)"


.PHONY: clean
clean:
	@$(RM) -r "$(BUILDDIR)"
