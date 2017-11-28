
LIBNAME = inflater
TESTPROGNAME = $(LIBNAME)_tests
LOCAL_LIB_PATH = $(shell pwd)
CXXOPTS = -std=c++14

SOURCES = \
inflater.cpp

TESTSOURCES = \
inflatertests.cpp

#LIBS = -lboost_system -pthread -L/usr/lib/x86_64-linux-gnu 

all: $(SOURCES)
	$(CXX) $(CXXOPTS) -fPIC -shared -o lib$(LIBNAME).so $(SOURCES)

test: $(TESTSOURCES)
	$(CXX) $(CXXOPTS) $(INCLUDE) -o $(TESTPROGNAME) $(TESTSOURCES) -L$(LOCAL_LIB_PATH) -l$(LIBNAME)
	export LD_LIBRARY_PATH=$(LOCAL_LIB_PATH),$(LD_LIBRARY_PATH) && ./$(TESTPROGNAME)

clean:
	rm -f lib$(LIBNAME).so $(TESTPROGNAME)

