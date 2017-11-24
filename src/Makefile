
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

LIBS = -lboost_system -pthread -L/usr/lib/x86_64-linux-gnu 

all: $(SOURCES)
	$(CXX) $(CXXOPTS) $(JSON_INCLUDE) -o railinfo $(SOURCES) $(LIBS)

test: $(TESTSOURCES)
	$(CXX) $(CXXOPTS) $(INCLUDE) -o message_tests $(TESTSOURCES) message.cpp
	./message_tests

clean:
	make -C json clean
	rm -f railinfo message_tests

