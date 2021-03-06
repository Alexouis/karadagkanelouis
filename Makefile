# ------------------------------------------------------------------------------
#   _______   __     ________         ______     __          ______    ______  
#  /       \ /  |   /        |       /      \  _/  |        /      \  /      \ 
#  $$$$$$$  |$$ |   $$$$$$$$/       /$$$$$$  |/ $$ |       /$$$$$$  |/$$$$$$  |
#  $$ |__$$ |$$ |      $$ |         $$____$$ |$$$$ | ______$$____$$ |$$____$$ |
#  $$    $$/ $$ |      $$ |          /    $$/   $$ |/      |/    $$/  /    $$/ 
#  $$$$$$$/  $$ |      $$ |         /$$$$$$/    $$ |$$$$$$//$$$$$$/  /$$$$$$/  
#  $$ |      $$ |_____ $$ |         $$ |_____  _$$ |_      $$ |_____ $$ |_____ 
#  $$ |      $$       |$$ |         $$       |/ $$   |     $$       |$$       |
#  $$/       $$$$$$$$/ $$/          $$$$$$$$/ $$$$$$/      $$$$$$$$/ $$$$$$$$/ 
#                                                                              
# ------------------------------------------------------------------------------    

# make sure filename does not contains space !
HEADERS:=$(shell find src -type f -name '*.h')

# clean everything, reconfig everything, recompile everything
all: clean extern configure build 

# ------------------------------------------------------------------------------
# clean
# ------------------------------------------------------------------------------

# clean compiled files and generated header
clean:
	@echo [DEBUG] Root Makefile : clean
	@rm -rf bin build
	@rm -f $(shell grep -ls '// Generated by dia2code' main.h ${HEADERS})

# ------------------------------------------------------------------------------
# distclean :
# ------------------------------------------------------------------------------

# removes everything that is generated, including external dependencies
# make -s : Silent operation
# Change to directory dir before reading the makefiles or doing anything else
distclean: clean
	@echo [DEBUG] Root Makefile : distclean
	@$(MAKE) -s -C extern clean

# -----------------------------------------------------------------------------
# external
# ------------------------------------------------------------------------------

# configure and compile external dependency
extern: #bin/dia2code bin/tgui
	#@echo [DEBUG] Root Makefile : extern

#bin/dia2code:
#	@$(MAKE) -s -C extern dia2code

#bin/tgui:
#	@$(MAKE) -s -C extern tgui

# -----------------------------------------------------------------------------
# configure
# ------------------------------------------------------------------------------

# configure the project
configure:
	@echo [DEBUG] Root Makefile : configure
	@mkdir -p build
	@cd build && cmake ..

# -----------------------------------------------------------------------------
# build 
# -----------------------------------------------------------------------------

# compile all exe (client, server, ...)
build:
	@echo [DEBUG] Root Makefile : build
	@cd build && cmake --build .
	
bin/client:
	@$(MAKE) -s -C build client

bin/server:
	@$(MAKE) -s -C build server

# -----------------------------------------------------------------------------
# test
# -----------------------------------------------------------------------------

test:
	cd build/test && ctest -VV --timeout 300 --report_level=detailed --output-on-failure

# -----------------------------------------------------------------------------
# docker 
# -----------------------------------------------------------------------------

testdocker:
	docker build -t plt-initial -f docker/plt-initial .
	./docker/validate.sh plt-test
	./docker/run_docker_bash.sh plt-test

# -----------------------------------------------------------------------------
# pdf from dia
# -----------------------------------------------------------------------------

diapdf: rapport/state.pdf rapport/render.pdf rapport/engine.pdf rapport/ai.pdf rapport/module.pdf

rapport/state.pdf: src/state.dia
	dia -e rapport/state.ps $<
	ps2pdf rapport/state.ps $@
	rm -f rapport/state.ps

rapport/render.pdf: src/render.dia
	dia -e rapport/render.ps $<
	ps2pdf rapport/render.ps $@
	rm -f rapport/render.ps

rapport/engine.pdf: src/engine.dia
	dia -e rapport/engine.ps $<
	ps2pdf rapport/engine.ps $@
	rm -f rapport/engine.ps

rapport/ai.pdf: src/ai.dia
	dia -e rapport/ai.ps $<
	ps2pdf rapport/ai.ps $@
	rm -f rapport/ai.ps

rapport/module.pdf: src/module.dia
	dia -e rapport/module.ps $<
	ps2pdf rapport/module.ps $@
	rm -f rapport/module.ps

# -----------------------------------------------------------------------------
# others
# -----------------------------------------------------------------------------

list:
	@$(MAKE) -pRrq -f $(lastword $(MAKEFILE_LIST)) : 2>/dev/null | awk -v RS= -F: '/^# File/,/^# Finished Make data base/ {if ($$1 !~ "^[#.]") {print $$1}}' | sort | egrep -v -e '^[^[:alnum:]]' -e '^$@$$'

.PHONY: configure build clean extern test testdocker list



# install all requirements
install-requirements :
	./scripts/requirements.sh
.PHONY : install-requirements


push_git:
	git status
	git add -A
	git commit -m "$m"
	git push origin "$b" 
.PHONY : push_git


code-coverage:
	./scripts/code-coverage.sh
.PHONY : code-coverage


install_submodules :
	@echo 'submodules intallation'
	@git submodule init
	@git submodule update 
.PHONY : install_submodules


install_extern_deps_rsa :
	@echo 'submodules intallation'
	@rm -rf extern/tmx-loader
	@git clone git@github.com:nskley/tmx-loader.git extern/tmx-loader
.PHONY : install_extern_deps_rsa


install_extern_deps_https :
	@echo 'submodules intallation'
	@rm -rf extern/tmx-loader
	@git clone https://github.com/nskley/tmx-loader.git extern/tmx-loader
.PHONY : install_extern_deps_https