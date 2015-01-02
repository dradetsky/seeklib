objects=$(addsuffix .o, $(wildcard *.cpp))
MAGIC_FLAGS=`Magick++-config --cxxflags --cppflags --ldflags --libs`
CFLAGS=-fwrapv -pthread -fno-strict-aliasing -O2 -fopenmp
test: $(objects)
	c++ -o $@ $(CFLAGS) $(objects) $(MAGIC_FLAGS)
#%.o: %.cpp %.h
%.cpp.o: %.cpp %.h
	c++ -o $@ -c $< $(CFLAGS) $(MAGIC_FLAGS)
clean:
	rm -f $(objects) test
