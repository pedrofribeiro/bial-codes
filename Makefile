# Biomedical Image Analysis Library
# See README file in the root instalation directory for more information.

debug ?= 0
verbose ?= 0
test ?= 0
clang ?= 0
implicit ?= 0
profile ?= 0
#ccache=$(shell ccache --version 2>/dev/null)

LIB=../BIAL/build/linux/release/lib
OBJ=../BIAL/build/linux/release/obj
ifneq ($(debug), 0)
	OBJ=../BIAL/build/linux/debug/obj
	LIB=../BIAL/build/linux/debug/lib
endif

BIAL_LINK_FLAGS= -L$(LIB) -lbial -L../BIAL/bial/SLIC/obj/* -L../BIAL/bial/cpplex/obj/* -L../BIAL/bial/lsh/obj/* -fopenmp -lpthread -lz -lm
ifneq ($(profile), 0)
	BIAL_LINK_FLAGS=-L$(LIB) -lbial -L../BIAL/bial/SLIC/obj/* -L../BIAL/bial/cpplex/obj/* -L../BIAL/bial/lsh/obj/* -lpthread -lz -lm -lprofiler
endif

BIAL_CC_FLAGS=-Wall -Wno-unused-function -Wno-literal-conversion -I../BIAL/bial/inc -I../BIAL/bial/src -I../BIAL/bial/SLIC/inc -I../BIAL/bial/cpplex/inc -I../BIAL/bial/lsh/inc -DREAL_FLOAT -O3
ifneq ($(verbose), 0)
	BIAL_CC_FLAGS=-Wall -Wno-unused-function -Wno-literal-conversion -I../BIAL/bial/inc -I../BIAL/bial/src -I../BIAL/bial/SLIC/inc -I../BIAL/bial/cpplex/inc -I../BIAL/bial/lsh/inc -DREAL_FLOAT -O3 -DBIAL_DEBUG=$(verbose)
endif
ifneq ($(debug), 0)
	BIAL_CC_FLAGS=-g -Wno-unused-function -Wno-literal-conversion -O0 -I../BIAL/bial/inc -I../BIAL/bial/src -I../BIAL/bial/SLIC/inc -I../BIAL/bial/cpplex/inc -I../BIAL/bial/lsh/inc -DREAL_FLOAT -DBIAL_DEBUG=$(debug)
endif
ifneq ($(test), 0)
	BIAL_CC_FLAGS=-g -Wno-unused-function -Wno-literal-conversion -O0 -I../BIAL/bial/inc -I../BIAL/bial/src -I../BIAL/bial/SLIC/inc -I../BIAL/bial/cpplex/inc -I../BIAL/bial/lsh/inc -DREAL_FLOAT
endif

ifeq ($(debug), 1)
	QMAKE_PARAMS=../master.pro -r -spec linux-g++ CONFIG+=debug -o ../Makefile
else
	QMAKE_PARAMS=../master.pro -r -spec linux-g++ CONFIG+=release -o ../Makefile
endif

CXX=g++ -Wl,--no-as-needed --std=c++0x
ifdef ccache
	ifeq ($(clang), 1)
		CXX=ccache clang++ -Wl,--no-as-needed --std=c++0x -Qunused-arguments
	else
		CXX=ccache g++ -Wl,--no-as-needed --std=c++0x
	endif
else
	ifeq ($(clang), 1)
		CXX=clang++ -Wl,--no-as-needed --std=c++0x -Qunused-arguments
	else
		CXX=g++ -Wl,--no-as-needed --std=c++0x
	endif
endif

BIAL_SRC=../BIAL/bial/src/*.cpp
SRC=./src
BIN=./bin

all: libbial PNM

libbial:
	export LD_LIBRARY_PATH=$(LIB)
#	rm -f $(OBJ)/Common.o
#	qmake-qt5 $(QMAKE_PARAMS)
#	$(MAKE) -C ../ --no-print-directory

PNM: PNM-AffineTransformation PNM-Mean PNM-Normalization

PNM-AffineTransformation:
	$(CXX) $(BIAL_CC_FLAGS) -o $(BIN)/$@ $(SRC)/$(@).cpp $(BIAL_LINK_FLAGS)

PNM-Mean:
	$(CXX) $(BIAL_CC_FLAGS) -o $(BIN)/$@ $(SRC)/$(@).cpp $(BIAL_LINK_FLAGS)

PNM-Normalization:
	$(CXX) $(BIAL_CC_FLAGS) -o $(BIN)/$@ $(SRC)/$(@).cpp $(BIAL_LINK_FLAGS)


clean:
	rm -f src/*~ bin/* *~
	rm -rf dat/*
	$(MAKE) clean -C ../ --no-print-directory
