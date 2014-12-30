objects=$(addsuffix .o, $(wildcard *.cpp))
# CFLAGS=`Magick++-config --cxxflags --cppflags`
CFLAGS=-fwrapv -pthread -fno-strict-aliasing -O2 -fopenmp
test: $(objects)
	c++ -o $@ $(CFLAGS) $(objects) `Magick++-config --cxxflags --cppflags --ldflags --libs`
#%.o: %.cpp %.h
%.cpp.o: %.cpp %.h
	c++ -o $@ -c $< $(CFLAGS)  `Magick++-config --cxxflags --cppflags --ldflags --libs`
clean:
	rm -f $(objects)
