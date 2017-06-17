
CXXOPTS = -std=c++14

SOURCES = \
main.cpp \
stompclient.cpp \
stomphandler.cpp \
config.cpp

LIBS = -lboost_system -pthread -L/usr/lib/x86_64-linux-gnu 

all: $(SOURCES)
	make -C json all 
	$(CXX) $(CXXOPTS) $(JSON_INCLUDE) -o railinfo $(SOURCES) $(LIBS)

clean:
	make -C json clean
	rm -f railinfo

