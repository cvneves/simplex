src = $(wildcard src/*.cc)
obj = $(src:.c=o.o)

CXXFLAGS = -std=c++11 -I include/

simplex: $(obj)
	$(CXX) -o $@ $^ $(CXXFLAGS)
	