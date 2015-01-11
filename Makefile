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
LIB_TARGET=/usr/local/lib

all: test testlib

install: CFLAGS=$(PROD_FLAGS) -Dcimg_display=0
install: lib
	cp libseek.so $(LIB_TARGET)
	ln -s $(LIB_TARGET)/libseek.so /usr/lib/libseek.so  # fuck autoconf

uninstall:
	rm -f $(LIB_TARGET)/libseek.so
	rm -f /usr/lib/libseek.so  # fuck autoconf

testlib: lib test.o
	clang++ -o $@ $(CFLAGS) test.o -L. -lseek

lib: $(libobjs)
	clang++ -shared -o libseek.so $(libobjs)

test: $(objects)
	clang++ -o $@ $(CFLAGS) $(objects)
%.o: %.cpp %.h
	clang++ -o $@ -c $< $(CFLAGS)
clean:
	rm -f $(objects) test testlib libseek.so
