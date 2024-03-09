#include <stack>
#include <list>
#include <vector>
#include <string>
#include <cstring>
#include <memory>


#define COPACTY 100

int Max(int x,int y){
	if(x > y)return x;
	if(y > x)return y;
	else     return x;
}

class VarType{
	public:
		int Size;
		virtual void info(int tabs){}
		virtual VarType* Clone() const {
			VarType* temp = (VarType*)malloc(sizeof(VarType));
			memcpy(temp,this,sizeof(VarType));
			return temp;
		}
};

class IntType : public VarType{
	public:
		IntType():VarType(){
			Size = 8;
		}
		void info(int tabs) override {
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("Size:%d\n",Size);
		}
		VarType* Clone() const {
			return new IntType();
		}
};

class CharType : public VarType{
	public:
		CharType():VarType(){
			Size = 1;
		}
		void info(int tabs) override {
			for(int x = 0;x < tabs;x++)printf("    ");
			printf("Size:%d\n",Size);
		}
};

class Symbol {
	public:
		char* Name; // Name of the variable
		VarType* Type; 
		int DefaultDereferencing;
		Symbol(const char* name,const VarType* type){
			Name = strdup(name);
			Type = type->Clone();
			DefaultDereferencing = 1;
		}
		Symbol(){}
		void info(){
			printf("Symbol:\"%s\".",Name);
		}
		Symbol* Clone(){
			return new Symbol(Name,Type);
		}
		~Symbol(){
			delete Type;
			free(Name);
		}
};

class Definition{
	public:
		char* Identifier;
		int AssignedValue;
		Definition(const char* identifier,int value){
			AssignedValue = value;
			Identifier = strdup(identifier);
		}
		~Definition(){
			free(Identifier);
		}
};

class DependencySymbol{
	public:
		int FunctionIndex;
		char* Identifier;
		DependencySymbol(int index,const char* indetifier){
			FunctionIndex = index;
			Identifier = strdup(indetifier);
		}
		~DependencySymbol(){
			free(Identifier);
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
		void Push(const std::list<Symbol*>* table){
			Top++;
			std::list<Symbol*>* temp = new std::list<Symbol*>;
			for (std::list<Symbol*>::const_iterator it = table->begin(); it != table->end(); ++it) 
				temp->push_back((*it)->Clone());
			Tables[Top] = temp;
		}
		void PushNewTable(){
			Top++;
			Tables[Top] = new std::list<Symbol*>();
		}
		void Pop(void){
			MaxSize = Max(MaxSize,CerentSize());
			for (std::list<Symbol*>::iterator it = Tables[Top]->begin(); it != Tables[Top]->end(); ++it) 
				delete (*it);
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
			for (std::list<DependencySymbol*>::iterator it = DependencySymbols->begin(); it != DependencySymbols->end(); ++it)
				if(!strcmp((*it)->Identifier,indentifier))
					return (*it)->FunctionIndex;
			return -1;
		}
		~SymbolTableStack(){
			// Definitions
			for (std::list<Definition*>::iterator it = Definitions->begin(); it != Definitions->end(); ++it)
				delete (*it);			
			delete Definitions;
			// DependencySymbols
			for (std::list<DependencySymbol*>::iterator it = DependencySymbols->begin(); it != DependencySymbols->end(); ++it)
				delete (*it);
			delete DependencySymbols;
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