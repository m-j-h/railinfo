
CXXOPTS = -std=c++14

TESTSOURCES = \
jsonparser.cpp \
jsonparsertests.cpp

INCLUDE = -I/home/mark/3rdparty/rapidjson/include

all: test

test: $(TESTSOURCES)
	$(CXX) $(CXXOPTS) $(INCLUDE) -o json_parser_tests $(TESTSOURCES)
	./json_parser_tests

clean:
	rm -f json_parser_tests
