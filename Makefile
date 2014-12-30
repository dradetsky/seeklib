objects=$(addsuffix .o, $(wildcard *.cpp))
all: $(objects)
%.cpp.o: %.cpp %.h
	gcc -c $< -o $@
clean:
	rm -f $(objects)
