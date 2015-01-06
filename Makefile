progobjs=\
test.o
libobjs=\
cmp.o \
haar.o \
sig.o

objects=$(progobjs) $(libobjs)
DEV_FLAGS=-fwrapv -pthread -fpic -g
PROD_FLAGS=-fwrapv -pthread -fpic -O2 -ffast-math
CFLAGS=$(PROF_FLAGS) $(DEV_FLAGS) -Dcimg_display=0

all: test testlib

install: CFLAGS=$(PROD_FLAGS) -Dcimg_display=0
install: lib
	cp libseek.so /usr/local/lib/

uninstall:
	rm -f /usr/local/lib/libseek.so

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
