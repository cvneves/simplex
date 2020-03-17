src = $(wildcard src/*.cc)
obj = $(src:.c=o.o)

CXXFLAGS = -std=c++14 -I include/ -g

simplex: $(obj)
	$(CXX) -o $@ $^ $(CXXFLAGS)
	
