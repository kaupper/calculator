SOURCES=$(wildcard *.cpp)
CPPFLAGS=-static-libstdc++ -g --std=c++14
OUTPUT=out

all:
	g++ $(CPPFLAGS) $(LDFLAGS) $(SOURCES) -o $(OUTPUT)

debug: adddebug all

adddebug:
	$(eval CPPFLAGS=$(CPPFLAGS) -DDEBUG)

.PHONY: all debug adddebug
