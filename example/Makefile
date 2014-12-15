program_NAME := read_config_test
program_CXX_SRCS := $(wildcard src/*.cpp)
program_CXX_OBJS := ${program_CXX_SRCS:.cpp=.o}
program_OBJS := $(program_CXX_OBJS)
program_INCLUDE_DIRS := /home/mjaniak/Soft/scfgp/include
program_LIBRARY_DIRS := /home/mjaniak/Soft/scfgp/lib
program_LIBRARY_DIRS += /home/mjaniak/Soft/bazinga/lib
program_INCLUDE_DIRS += /home/mjaniak/Soft/bazinga/include
program_LIBRARIES := m scfgp bazinga

CXX := g++


CPPFLAGS += 


# shared libraries
# LDFLAGS += -Wl,-rpath $(program_LIBRARY_DIRS)
CPPFLAGS += $(foreach includedir,$(program_INCLUDE_DIRS),-I$(includedir)) 
LDFLAGS += $(foreach librarydir,$(program_LIBRARY_DIRS),-L$(librarydir))
LDFLAGS += $(foreach library,$(program_LIBRARIES),-l$(library))

.PHONY: all clean

all: $(program_NAME)

$(program_NAME): $(program_OBJS)
	$(CXX) $(program_OBJS) -o $(program_NAME) $(LDFLAGS) $(CPPFLAGS)

clean:
	@- $(RM) $(program_NAME)
	@- $(RM) $(program_OBJS)
