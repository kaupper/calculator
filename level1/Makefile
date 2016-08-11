SOURCES=$(wildcard *.cpp)
CPPFLAGS=-static-libstdc++ --std=c++14
OUTPUT=out

all:
	g++ $(CPPFLAGS) $(LDFLAGS) $(SOURCES) -o $(OUTPUT)

debug: adddebug all

adddebug:
	$(eval CPPFLAGS=$(CPPFLAGS) -DDEBUG -g)

.PHONY: all debug adddebug
