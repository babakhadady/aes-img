CXX := g++ -std=c++11 
CXXFLAGS := -g -Wall 
RM := rm -f
OBJ := aes.o main.o sbox.o 


aes: $(OBJ)
	${CXX} ${CXXFLAGS} -o $@ $^

clean:
	$(RM) *.o aes 
