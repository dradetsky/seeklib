objects=$(addsuffix .o, $(wildcard *.cpp))
# CFLAGS=`Magick++-config --cxxflags --cppflags`
CFLAGS=
# objects=sig.o haar.o
# all: $(objects)

test: $(objects)
	c++ -o $@ $(CFLAGS) $(objects) `Magick++-config --cxxflags --cppflags --ldflags --libs`
#%.o: %.cpp %.h
%.cpp.o: %.cpp %.h
	c++ -o $@ -c $< $(CFLAGS)  `Magick++-config --cxxflags --cppflags --ldflags --libs`
clean:
	rm -f $(objects)
