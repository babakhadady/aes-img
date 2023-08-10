CXX := g++ -std=c++11 
CXXFLAGS := -g -Wall 
RM := rm -f
TESTS := main-test.o sbox-test.o  
OBJS := ../src/aes.o ../src/sbox.o


tests: $(TESTS)  
	${CXX} ${CXXFLAGS} -I../src/ ${OBJS}  -o $@ $^


clean:
	$(RM) *. tests 
