progobjs=\
test.o
libobjs=\
cmp.o \
haar.o \
sig.o

objects=$(progobjs) $(libobjs)

MAGIC_FLAGS=`Magick++-config --cxxflags --cppflags --ldflags --libs`
CFLAGS=-fwrapv -pthread -fno-strict-aliasing -O2 -fopenmp -fpic
testlib: lib test.o
	c++ -o $@ $(CFLAGS) test.o -L. -lseek

lib: $(libobjs)
	gcc -shared -o libseek.so $(libobjs) $(MAGIC_FLAGS)

test: $(objects)
	c++ -o $@ $(CFLAGS) $(objects) $(MAGIC_FLAGS)
#%.o: %.cpp %.h
%.o: %.cpp %.h
	c++ -o $@ -c $< $(CFLAGS) $(MAGIC_FLAGS)
clean:
	rm -f $(objects) test testlib libseek.so
