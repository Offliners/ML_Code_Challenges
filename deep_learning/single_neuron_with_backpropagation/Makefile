CPP_DIR = Cpp
C_DIR = C

LDLAGS  = -lm

CPP_OUTPUT = SN_cpp
C_OUTPUT = SN_c

all:                                                                                                                                                                                                        
	g++ ./$(CPP_DIR)/main.cpp -o $(CPP_OUTPUT)
	gcc ./$(C_DIR)/main.c -o $(C_OUTPUT) $(LDLAGS)

clean:
	@rm $(CPP_OUTPUT)
	@rm $(C_OUTPUT)