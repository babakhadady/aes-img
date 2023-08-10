CXX := g++ -std=c++11 
CXXFLAGS := -g -Wall 
RM := rm -f
OBJ := aes.o main.o sbox.o ./util/gf-util.o 



aes: $(OBJ)
	${CXX} ${CXXFLAGS} -I./util -o $@ $^

clean:
	$(RM) *.o aes 
