# varibales
BINARIES := bin
EXECS := $(wildcard $(BINARIES)/*)

# Execute all binaries in the inside bin directory
all : $(EXECS)
	$(EXECS:%=./%)
.PHONY : all


# build the project
build : 
	@if [ -d "build" ]; then       \
		cd build;                  \
		if [ -f "Makefile" ]; then \
			make -j;               \
		else                       \
			cmake ..;              \
			make -j;               \
		fi                         \
	else                           \
		mkdir build;               \
		cd build;                  \
		cmake ..;                  \
		make -j;                   \
	fi
.PHONY : build


# remove compiled files and generated headers
clean :
	
.PHONY : clean