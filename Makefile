progobjs=\
test.o
libobjs=\
cmp.o \
haar.o \
sig.o

objects=$(progobjs) $(libobjs)
DEV_FLAGS=-fwrapv -pthread -fpic -g
PROD_FLAGS=-fwrapv -pthread -fpic -O2
CFLAGS=$(PROF_FLAGS) $(DEV_FLAGS) -Dcimg_display=0
# -ffast-math ?

all: test testlib

testlib: lib test.o
	c++ -o $@ $(CFLAGS) test.o -L. -lseek

lib: $(libobjs)
	g++ -shared -o libseek.so $(libobjs)

test: $(objects)
	c++ -o $@ $(CFLAGS) $(objects)
%.o: %.cpp %.h
	c++ -o $@ -c $< $(CFLAGS)
clean:
	rm -f $(objects) test testlib libseek.so
