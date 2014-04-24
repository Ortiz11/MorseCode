//Nicholas Ortiz

#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

//create nodes in the stack
typedef struct node_{
	string data;
	struct node_ *next;
}node;
//create the stack
typedef struct stack_{
	unsigned int size;
	node* stack;
}stack;
//base class
class message{
protected:
	string msg;
public:
	message();
	message(string input);
	~message();
	virtual void printMSG();

};
//derived class
class morseCodeMessage : public message{
public:
	string morseMSG[10];
	int words;
	morseCodeMessage();
	virtual void printMSG();
	void translate(string msg);
};
//stack class
class messageStack{
protected:
	stack* start;
public:
	messageStack(string code[],int size);
	~messageStack();
	void push(string code);
	void pop();
	void printStack();


};
//default constructor
message::message(){
	cout << "Enter an input message.\n";
	getline(cin, msg);

}
//string input constructor
message::message(string input){
	msg = input;
}
//destructor
message::~message(){
	msg = "";
}
//constructor for derived class
morseCodeMessage::morseCodeMessage(){
	words = 0;
	translate(msg);
}
//constructor for stack
messageStack::messageStack(string morseMSG[],int size){
	start = new stack;
	start->size = 0;
	start->stack = NULL;
	int i = 0;
	//push the words to the stack
	for (i = 0; i <= size; i++){
		push(morseMSG[i]);
	}
}
messageStack::~messageStack(){
	delete start;

}
//translate the string into code
void morseCodeMessage::translate(string msg){
	string letters = "abcdefghijklmnopqrstuvwxyz";
	string morseCode[] = { ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....",
		"..", ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...",
		"-", "..-", "...-", ".--", "-..-", "-.--", "--.." };
	int index = 0, length = 0, i = 0;
	char letter;
	//find the length
	length = msg.length();
	for (i = 0; i < length; i++){
		//check for uppercase
		if (isupper(msg[i])){
			msg[i] = tolower(msg[i]);
		}
		//find the letter at an index and use it
		letter = msg[i];
		index = letters.find(letter);
		if (index != -1){
			morseMSG[words] += morseCode[index] + " ";
		}
		else{
			words++;
		}
	}
}
//push a word onto the stack
void messageStack::push(string code){
	node* new_node = NULL;
	node* tmp = NULL;
	//create a new node
	new_node = new node;
	new_node->data = code;
	new_node->next = NULL;
	//place the node in the top of the stack
	if (start->stack == NULL){
		start->stack = new_node;
		start->size += 1;
	}
	else{
		tmp = start->stack;
		new_node->next = tmp;
		start->stack = new_node;
		start->size += 1;
	}

}
//pop the word of the stack and remove memory
void messageStack::pop(){
	node* del = NULL;

	if (start->stack == NULL){

		return;
	}
	del = start->stack;
	start->stack = del->next;
	delete del;
	start->size -= 1;
}
//print the code from the top of the stack
void messageStack::printStack(){
	node_* tmp = NULL;

	cout << "\n" << "Words on the stack: " << start->size << "\n";
	tmp = start->stack;
	cout << "print from the stack: ";
	while (tmp != NULL){
		cout << tmp->data << "  ";
		pop();
		tmp = tmp->next;
	}
	
}
//base class print
void message::printMSG(){
	cout << msg;
}
//print msg from the derived class
void morseCodeMessage::printMSG(){
	int i = 0;
	cout << "Message in Text: " << msg << "\n";
	cout << "Message in Code: ";
		for (i = 0; i <= words; i++){
		cout << morseMSG[i] << "  ";
	}
}

int main(void){
	message *baseMessage;
	morseCodeMessage morseCode;
	//set the base class = to the derived class
	baseMessage = &morseCode;
	//will use the dervied class print function
	baseMessage->printMSG();
	//print the stack top first
	messageStack stack(morseCode.morseMSG,morseCode.words);
	stack.printStack();
	
	return 0;
}