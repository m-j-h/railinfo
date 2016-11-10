
CXXOPTS = -std=c++14

SOURCES = \
main.cpp \
stompclient.cpp \
stomphandler.cpp \
jsonparser.cpp \
config.cpp

JSON_SOURCES = \
jsonmain.cpp \
jsonparser.cpp

JSON_INCLUDE = -I/home/mark/3rdparty/rapidjson/include

LIBS = -lboost_system -pthread -L/usr/lib/x86_64-linux-gnu 

all: $(SOURCES)
	$(CXX) $(CXXOPTS) $(JSON_INCLUDE) -o railinfo $(SOURCES) $(LIBS)

json: $(JSON_SOURCES)
	$(CXX) $(CXXOPTS) $(JSON_INCLUDE) -o json $(JSON_SOURCES)
