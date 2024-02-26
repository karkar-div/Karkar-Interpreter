#include <stack>
#include <list>
#include <vector>
#include <string>
#include <cstring>


#define COPACTY 100

int Max(int x,int y){
	if(x > y)return x;
	if(y > x)return y;
	else     return x;
}

class VarType{
	public:
		int Size;
		virtual void debug(int tabs){}
};

class IntType : public VarType{
	public:
		IntType():VarType(){
			Size = 8;
		}
		void debug(int tabs) override {
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("Size:%d\n",Size);
		}
};

class Symbol {
	public:
		char* Name; // Name of the variable
		VarType* Type; 
		int DefaultDereferencing;
		Symbol(char* name,VarType* type){
			Name = name;
			Type = type;
			DefaultDereferencing = 1;
		}
		Symbol(){}
		void debug(){
			printf("Symbol:\"%s\".",Name);
		}
};

class Definition{
	public:
		char* Identifier;
		int AssignedValue;
		Definition(char* identifier,int value){
			AssignedValue = value;
			Identifier = identifier;
		}
};

class DependencySymbol{
	public:
		int FunctionIndex;
		char* Identifier;
		DependencySymbol(int index,char* indetifier){
			FunctionIndex = index;
			Identifier = indetifier;
		}
};

class SymbolTableStack{
	public:
		int Top;
		int MaxSize;
		std::vector<std::list<Symbol*>*> Tables;
		std::list<Definition*>* Definitions;
		std::list<DependencySymbol*>* DependencySymbols;
		SymbolTableStack(){
			Top = -1;
			MaxSize = 0;
			Tables = std::vector<std::list<Symbol*>*>(COPACTY);
			Definitions = new std::list<Definition*>;
			DependencySymbols = new std::list<DependencySymbol*>();
		}
		void Push(std::list<Symbol*>* table){
			Top++;
			Tables[Top] = table;
		}
		void Pop(void){
			MaxSize = Max(MaxSize,CerentSize());
			delete Tables[Top];
			Top--;
		}
		int Find(const char* indentifier){
			int address = 8;
			for (int i = 0; i < Top+1; i++) 
				for (std::list<Symbol*>::iterator it = Tables[i]->begin(); it != Tables[i]->end(); ++it){
					if(!strcmp((*it)->Name,indentifier)) return address;
					else address += (*it)->Type->Size;
				}
			return -1;
		}
		void ResetSize(){
			MaxSize = 0;
		}
		int FindDefinition(const char* indentifier){
			for (std::list<Definition*>::iterator it = Definitions->begin(); it != Definitions->end(); ++it){
				if(!strcmp((*it)->Identifier,indentifier))
					return (*it)->AssignedValue;
			}
			return -1;
		}
		int FindExternedFunction(const char* indentifier){
			for (std::list<DependencySymbol*>::iterator it = DependencySymbols->begin(); it != DependencySymbols->end(); ++it){
				if(!strcmp((*it)->Identifier,indentifier)){
					return (*it)->FunctionIndex;
								
				}
				printf("Failer %s:\n",(*it)->Identifier);	
			}

			return -1;
		}
	private:
		int CerentSize(){
			int size = 0;
			for (int i = 0; i < Top+1; i++) 
				for (std::list<Symbol*>::iterator it = Tables[i]->begin(); it != Tables[i]->end(); ++it) 
					size += (*it)->Type->Size;
			return size;
		}
};

SymbolTableStack* Symbol_Tables;