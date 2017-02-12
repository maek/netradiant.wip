# CMakefile

.SUFFIXES:
.NOTPARALLEL:

SHELL = /bin/sh
BUILDDIR = $(CURDIR)/build
CONFIGURATION = Release


.PHONY: default
default: radiant


.PHONY: radiant
radiant: | $(BUILDDIR)
	@test -f $(BUILDDIR)/Makefile ||\
	(cd $(BUILDDIR) && cmake -DCMAKE_BUILD_TYPE=$(CONFIGURATION)\
	                         -DDOWNLOAD_GAMEPACKS=OFF\
	                         ..)
	@cd $(BUILDDIR) && cmake --build . -- -j$(shell nproc)
	@install -dv $(BUILDDIR)/games
	@./install-gamepacks.sh $(BUILDDIR)
	@echo "[ [32mOK[0m ]"


.PHONY: radiant.exe
radiant.exe: | $(BUILDDIR)
	@test -f "$(BUILDDIR)/Makefile" ||\
	(cd $(BUILDDIR) && cmake -DCMAKE_BUILD_TYPE=Release\
	                         -DDOWNLOAD_GAMEPACKS=OFF\
	                         -DCMAKE_TOOLCHAIN_FILE=../cmake/Toolchain-mingw-w64.cmake\
	                         ..)
	@cd "$(BUILDDIR)" && cmake --build . -- -j$(shell nproc)
	@install -dv $(BUILDDIR)/games
	@./install-gamepacks.sh $(BUILDDIR)
	@echo "[ [32mOK[0m ]"


$(BUILDDIR):
	@install -dv $(BUILDDIR)


.PHONY: install
install:
	@cd $(BUILDDIR) && cmake --build . --target install


.PHONY: dist
dist:
	@cd $(BUILDDIR) && cmake --build . --target package


.PHONY: clean
clean:
	@$(RM) -r $(BUILDDIR)
