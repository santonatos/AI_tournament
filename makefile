#Author:Spiros Antonatos 

src = $(wildcard *.cpp)
obj = $(src:%.cpp=%.o)
cc = g++
header = headers/%.hpp
CFLAGS = -std=c++11 -Iheaders/

PROGRAM = agentSmurf

all: $(obj)
	$(cc) $(CFLAGS) $(obj) -o $(PROGRAM) 	
	rm -f *.o

%.o: %.cpp $(header)
	$(cc) -c $(CFLAGS)  $< -o $@


clean:
	rm -f $(PROGRAM)
	rm -f *.o 



