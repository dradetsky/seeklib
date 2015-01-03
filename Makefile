progobjs=\
test.o
libobjs=\
cmp.o \
haar.o \
sig.o

objects=$(progobjs) $(libobjs)
DEV_FLAGS=-fwrapv -pthread -fpic -g
PROD_FLAGS=-fwrapv -pthread -fpic -O2
CFLAGS=$(PROF_FLAGS) $(DEV_FLAGS)
MAGIC_FLAGS=`Magick++-config --cxxflags --cppflags --ldflags --libs`
# -ffast-math ?
#CFLAGS=-fwrapv -pthread -fno-strict-aliasing -O2 -fopenmp -fpic -Wattributes -rdynamic -Wl,-E
#CFLAGS=-fwrapv -pthread -fno-strict-aliasing -O2 -fopenmp -fpic

all: test testlib

testlib: lib test.o
	c++ -o $@ $(CFLAGS) test.o -L. -lseek

lib: $(libobjs)
	g++ -shared -o libseek.so $(libobjs) $(MAGIC_FLAGS)

test: $(objects)
	c++ -o $@ $(CFLAGS) $(objects) $(MAGIC_FLAGS)
#%.o: %.cpp %.h
%.o: %.cpp %.h
	c++ -o $@ -c $< $(CFLAGS) $(MAGIC_FLAGS)
clean:
	rm -f $(objects) test testlib libseek.so
