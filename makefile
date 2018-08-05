INC_DIR = include
SRC = src
TARGET = mindMap
PSHELL = ui

all: $(TARGET) $(PSHELL)

$(TARGET): main.o root.o composite.o node.o component.o nodeModifier.o nodeIdCounter.o mindMapModel.o fileManager.o factory.o command.o editCommand.o changeParentCommand.o deleteCommand.o commandManager.o nodeOperator.o mapFactory.o componentFactory.o insertAParentCommand.o insertAChildCommand.o insertASiblingCommand.o
ifeq (${OS}, Windows_NT)  
	g++ -o $(TARGET) main.o root.o composite.o node.o component.o nodeModifier.o nodeIdCounter.o mindMapModel.o fileManager.o factory.o command.o editCommand.o changeParentCommand.o deleteCommand.o commandManager.o nodeOperator.o mapFactory.o componentFactory.o insertAParentCommand.o insertAChildCommand.o insertASiblingCommand.o -lgtest
else
	g++ -o $(TARGET) main.o root.o composite.o node.o component.o nodeModifier.o nodeIdCounter.o mindMapModel.o fileManager.o factory.o command.o editCommand.o changeParentCommand.o deleteCommand.o commandManager.o nodeOperator.o mapFactory.o componentFactory.o insertAParentCommand.o insertAChildCommand.o insertASiblingCommand.o -lgtest -lpthread
endif

$(PSHELL): textUi.o root.o composite.o node.o component.o nodeModifier.o nodeIdCounter.o mindMapModel.o fileManager.o factory.o command.o editCommand.o changeParentCommand.o deleteCommand.o commandManager.o nodeOperator.o mapFactory.o componentFactory.o insertAParentCommand.o insertAChildCommand.o insertASiblingCommand.o
ifeq (${OS}, Windows_NT) 
	g++ -o $(PSHELL) textUi.o root.o composite.o node.o component.o nodeModifier.o nodeIdCounter.o mindMapModel.o fileManager.o factory.o command.o editCommand.o changeParentCommand.o deleteCommand.o commandManager.o nodeOperator.o mapFactory.o componentFactory.o insertAParentCommand.o insertAChildCommand.o insertASiblingCommand.o -lgtest
else
	g++ -o $(PSHELL) textUi.o root.o composite.o node.o component.o nodeModifier.o nodeIdCounter.o mindMapModel.o fileManager.o factory.o command.o editCommand.o changeParentCommand.o deleteCommand.o commandManager.o nodeOperator.o mapFactory.o componentFactory.o insertAParentCommand.o insertAChildCommand.o insertASiblingCommand.o -lpthread
endif

main.o: main.cpp 
	g++ -std=gnu++0x -c main.cpp

textUi.o: textUi.cpp
	g++ -std=gnu++0x -c textUi.cpp

root.o: $(INC_DIR)/root.h $(SRC)/root.cpp
	g++ -std=gnu++0x -c $(SRC)/root.cpp

node.o: $(INC_DIR)/node.h $(SRC)/node.cpp
	g++ -std=gnu++0x -c $(SRC)/node.cpp

component.o: $(INC_DIR)/component.h $(SRC)/component.cpp
	g++ -std=gnu++0x -c $(SRC)/component.cpp

composite.o: $(INC_DIR)/composite.h $(SRC)/composite.cpp
	g++ -std=gnu++0x -c $(SRC)/composite.cpp

nodeModifier.o: $(INC_DIR)/nodeModifier.h $(SRC)/nodeModifier.cpp
	g++ -std=gnu++0x -c $(SRC)/nodeModifier.cpp

nodeIdCounter.o: $(INC_DIR)/nodeIdCounter.h $(SRC)/nodeIdCounter.cpp
	g++ -std=gnu++0x -c $(SRC)/nodeIdCounter.cpp

mindMapModel.o: $(INC_DIR)/mindMapModel.h $(SRC)/mindMapModel.cpp
	g++ -std=gnu++0x -c $(SRC)/mindMapModel.cpp

fileManager.o: $(INC_DIR)/fileManager.h $(SRC)/fileManager.cpp
	g++ -std=gnu++0x -c $(SRC)/fileManager.cpp

factory.o: $(INC_DIR)/factory.h $(SRC)/factory.cpp
	g++ -std=gnu++0x -c $(SRC)/factory.cpp

command.o: $(INC_DIR)/command.h $(SRC)/command.cpp
	g++ -std=gnu++0x -c $(SRC)/command.cpp

editCommand.o: $(INC_DIR)/editCommand.h $(SRC)/editCommand.cpp
	g++ -std=gnu++0x -c $(SRC)/editCommand.cpp

changeParentCommand.o: $(INC_DIR)/changeParentCommand.h $(SRC)/changeParentCommand.cpp
	g++ -std=gnu++0x -c $(SRC)/changeParentCommand.cpp

deleteCommand.o: $(INC_DIR)/deleteCommand.h $(SRC)/deleteCommand.cpp
	g++ -std=gnu++0x -c $(SRC)/deleteCommand.cpp

commandManager.o: $(INC_DIR)/commandManager.h $(SRC)/commandManager.cpp
	g++ -std=gnu++0x -c $(SRC)/commandManager.cpp

nodeOperator.o: $(INC_DIR)/nodeOperator.h $(SRC)/nodeOperator.cpp
	g++ -std=gnu++0x -c $(SRC)/nodeOperator.cpp

mapFactory.o: $(INC_DIR)/mapFactory.h $(SRC)/mapFactory.cpp
	g++ -std=gnu++0x -c $(SRC)/mapFactory.cpp

componentFactory.o: $(INC_DIR)/componentFactory.h $(SRC)/componentFactory.cpp
	g++ -std=gnu++0x -c $(SRC)/componentFactory.cpp

insertAParentCommand.o: $(INC_DIR)/insertAParentCommand.h $(SRC)/insertAParentCommand.cpp
	g++ -std=gnu++0x -c $(SRC)/insertAParentCommand.cpp

insertAChildCommand.o: $(INC_DIR)/insertAChildCommand.h $(SRC)/insertAChildCommand.cpp
	g++ -std=gnu++0x -c $(SRC)/insertAChildCommand.cpp

insertASiblingCommand.o: $(INC_DIR)/insertASiblingCommand.h $(SRC)/insertASiblingCommand.cpp
	g++ -std=gnu++0x -c $(SRC)/insertASiblingCommand.cpp



clean:	
ifeq (${OS}, Windows_NT) 
	del *.o *.exe
else
	rm -f *.o $(TARGET)
endif