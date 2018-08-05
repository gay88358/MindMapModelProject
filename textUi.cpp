#include <iostream>
#include "./include/mindMapModel.h"

using std::endl;
using std::cout;
using std::cin;

void renderMenu() {
    cout << "Please enter your choice:" << endl;
    cout << "1. Create a new mind map" << endl;
    cout << "2. Insert a new node" << endl;
    cout << "3. Edit a node" << endl;
    cout << "4. Display mind map" << endl;
    cout << "5. Save mind map" << endl;
    cout << "6. Load a mind map" << endl;
    cout << "7. Redo" << endl;
    cout << "8. Undo" << endl;
    cout << "9. Exit" << endl;
    cout << ">";
}

void renderMindMap(MindMapModel *mindMap) {
    string mindMapGraph;
    try {
        mindMapGraph = mindMap->showMap();
        cout << "The mind map Computer is displayed as follows: " << endl;
        cout << mindMapGraph << endl;
    } catch(std::string error) {
        cout << error << endl;
    }   
}

void renderGuideText(string text) {
    cout << text << endl;
    cout << ">";
}

int enterChoice() {
    int choice;
    cin >> choice;
    cin.clear();
    cin.ignore();
    return choice;
}

void renderInsertGuideText() {
    cout << "a. Insert a parent node " << endl;
    cout << "b. Insert a child node " << endl;
    cout << "c. Insert a sibling node" << endl;
    cout << ">";
}

string enterNodeName() {
    renderGuideText("Enter the node name: ");
    string name;
    cin >> name;
    return name;
}

string enterNodeType() {
    renderInsertGuideText();
    string insertType;
    cin >> insertType;        
    return insertType;
}

int enterId() {
    renderGuideText("Enter the node ID: ");
    int id = enterChoice();
    return id;
}

bool isValidInsertTypeForRoot(string &insertType, int id) {
    return !((id == 0 && insertType == "a") || (id == 0 && insertType == "c"));
}

void handleSaveMindMapEvent(MindMapModel *mindMap) {
    mindMap->saveMindMap();
}

void handleRenderMindMapEvent(MindMapModel *mindMap) {
    renderMindMap(mindMap);
}

void handleCreateMindMapEvent(MindMapModel *mindMap) {
    renderGuideText("Please enter the topic: ");
    string topic;
    cin >> topic;
    mindMap->createMindMap(topic);
    renderMindMap(mindMap);
}

void handleRedoEvent(MindMapModel *minMap) {
     try {
        minMap->redo();
    } catch(std::string error) {
        renderGuideText(error);
    }
}

void handleUndoEvent(MindMapModel *minMap) {
    try {
        minMap->undo();
    } catch(std::string error) {
        renderGuideText(error);
    }
}

void handleLoadMindMapEvent(MindMapModel *minMap) {
    string path;
    renderGuideText("enter the path: ");
    cin >> path;
    minMap->loadMindMap(path);
}

void renderEditChoice() {
    cout << "a. Edit description of a node" << endl;
    cout << "b. Change the parent of a node" << endl;
    cout << "c. Delete a node" << endl;
}

int enterNodeId(MindMapModel *minMap) {
    int targetId;

    while(true) {
        targetId = enterChoice();
        cout << "fuck" << endl;
        if (minMap->findNodeById(targetId) == nullptr) {
            renderGuideText("The node is not exist!");
            continue;
        }

        break;
    }
    return targetId;
}

void editNodeDescription(MindMapModel *minMap, int targetId) {
    string description;
    cin >> description;
    minMap->editNodeDescriptionCommand(targetId, description); 
}


string enterInsertType(int id) {
    string insertType;
    while(1) {
        insertType = enterNodeType();
        map<string, string> errorHints = { {"a", "Root can’t insert parent node"}, {"c", "Root can’t insert sibling node "} };
        if (!isValidInsertTypeForRoot(insertType, id)) {
            cout << errorHints[insertType] << endl;
            continue;
        }
        
        if (insertType != "a" && insertType != "b" && insertType != "c") {
            cout << "Please enter right char" << endl;
            continue;
        }
        // input is valid
        break;
    }
    return insertType;
}

void insertNodeIntoMindMap(MindMapModel *mindMap) {
    renderGuideText("Enter node id!");
    int id = enterNodeId(mindMap);
    string insertType = enterInsertType(id);
    string name = enterNodeName();
    mindMap->insertNode(id, name, insertType);
}

void handleInsertNodeEvent(MindMapModel *mindMap) {
    renderMindMap(mindMap);
    insertNodeIntoMindMap(mindMap);
}

void deleteNode(MindMapModel *minMap, int targetId) {
    minMap->deleteNodeCommand(targetId);
}

void changeNodeParent(MindMapModel *minMap, int targetId) {
    renderGuideText("Enter the parent ID:");
    int parentId = enterNodeId(minMap); 
    minMap->changeNodeParentCommand(targetId, parentId);
}

string enterEditNodeChoice() {
    string choice;
    while(true) {
        renderEditChoice();
        cin >> choice;
        if (choice != "a" && choice != "b" && choice != "c") {
            cout << "The command is not found!" << endl;
            continue;
        }
        break;
    }
    return choice;
}


void handleEditTargetById(MindMapModel *minMap, int targetId) {
    string editChoice = enterEditNodeChoice();

    if (editChoice == "a") {
        editNodeDescription(minMap, targetId); 
    } else if (editChoice == "b") {
        changeNodeParent(minMap, targetId); 
    } else if (editChoice == "c") {
        deleteNode(minMap, targetId);
    }
} 

void handleEditNodeEvent(MindMapModel *minMap) {
    renderGuideText("Enter the edit node ID:");
    int targetId = enterNodeId(minMap);
    handleEditTargetById(minMap, targetId);
}

void handleRequireEvent(MindMapModel *mindMap, int choice) {
    if (choice == 1) {
        handleCreateMindMapEvent(mindMap);
    } else if (choice == 2) {
        handleInsertNodeEvent(mindMap);
        handleRenderMindMapEvent(mindMap);
    } else if (choice == 3) {
        handleEditNodeEvent(mindMap);
        handleRenderMindMapEvent(mindMap);
    } else if (choice == 4) {
        handleRenderMindMapEvent(mindMap);
    } else if (choice == 5) {
        handleSaveMindMapEvent(mindMap);
    } else if (choice == 6) {
        handleLoadMindMapEvent(mindMap);
        handleRenderMindMapEvent(mindMap);
    } else if (choice == 7) {
        handleRedoEvent(mindMap);
        handleRenderMindMapEvent(mindMap);
    } else if (choice == 8) {
        handleUndoEvent(mindMap);
        handleRenderMindMapEvent(mindMap);
    }
    else {
        cout << "Please enter right number\n" << endl;
    }
}

int main( int argc , char **argv )
{
    MindMapModel *mindMap = new MindMapModel();
    while(1) {
        renderMenu();
        int choice = enterChoice();
        if (choice == 9) break;
        handleRequireEvent(mindMap, choice);
    }
    return 0;
}

