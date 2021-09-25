# varibales
BINARIES := bin
EXECS := $(wildcard $(BINARIES)/*)

# Execute all binaries in the inside bin directory
all : $(EXECS)
	$(EXECS:%=./%)
.PHONY : all


# build the project
build : 
	./scripts/make_helper.sh build
.PHONY : build


# remove compiled files and generated headers
clean :
	./scripts/make_helper.sh clean
.PHONY : clean