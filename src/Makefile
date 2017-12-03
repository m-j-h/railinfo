
CXXOPTS = -std=c++14

SOURCES = \
main.cpp \
stompclient.cpp \
stomphandler.cpp \
config.cpp \
message.cpp \
logger.cpp

TESTSOURCES = \
messagetests.cpp \
logger.cpp

LIBS = -lboost_system -pthread -linflater
INFLATER_LIB_DIR = $(shell pwd)/inflater/lib
LIB_DIRS = -L/usr/lib/x86_64-linux-gnu -L$(INFLATER_LIB_DIR)
RPATH = -Wl,-rpath,$(INFLATER_LIB_DIR)

all: $(SOURCES)
	$(CXX) $(CXXOPTS) -o railinfo $(SOURCES) $(LIBS) $(LIB_DIRS) $(RPATH)

test: $(TESTSOURCES)
	$(CXX) $(CXXOPTS) $(INCLUDE) -o message_tests $(TESTSOURCES) message.cpp
	./message_tests

clean:
	rm -f railinfo message_tests

