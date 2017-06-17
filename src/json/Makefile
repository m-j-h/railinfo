
CXXOPTS = -std=c++14

SOURCES = \
jsonmain.cpp \
jsonparser.cpp

TESTSOURCES = \
jsonparser.cpp \
jsonparsertests.cpp

INCLUDE = -I/home/mark/3rdparty/rapidjson/include

all: $(SOURCES)
	$(CXX) $(CXXOPTS) $(INCLUDE) -o json_test $(SOURCES)

test: $(TESTSOURCES)
	$(CXX) $(CXXOPTS) $(INCLUDE) -o json_parser_tests $(TESTSOURCES) 

clean:
	rm -f json_test
	rm -f json_parser_tests
