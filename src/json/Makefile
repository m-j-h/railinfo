
CXXOPTS = -std=c++14

SOURCES = \
jsonmain.cpp \
jsonparser.cpp

INCLUDE = -I/home/mark/3rdparty/rapidjson/include

all: $(SOURCES)
	$(CXX) $(CXXOPTS) $(INCLUDE) -o json_test $(SOURCES)

clean:
	rm -f json_test

