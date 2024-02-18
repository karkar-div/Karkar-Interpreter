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
			Size = 1;
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

class ConstGlobalSymbol{
	public:
		Symbol* TheSymbol;
		int AssignedValue;
		ConstGlobalSymbol(Symbol* _symbol,int value){
			AssignedValue = value;
			TheSymbol = _symbol;
		}
};

class SymbolTableStack{
	public:
		int Top;
		int MaxSize;
		std::vector<std::list<Symbol*>*> Tables;
		std::list<ConstGlobalSymbol*>* ConstGlobalSymbols;
		SymbolTableStack(){
			Top = -1;
			MaxSize = 0;
			Tables = std::vector<std::list<Symbol*>*>(COPACTY);
			ConstGlobalSymbols = new std::list<ConstGlobalSymbol*>;
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
		int Find(char* indentifier){
			bool is_found = false;
			int address = 0;
			for (int i = 0; i < Top+1; i++) {
				for (std::list<Symbol*>::iterator it = Tables[i]->begin(); it != Tables[i]->end(); ++it){
					if(!strcmp((*it)->Name,indentifier)){
						is_found = true;
						goto end_search;
					}else
						address += (*it)->Type->Size;
				}
			}        
			end_search:
			if(is_found){
				address++;
				return address;
			} else {
				printf("undefine");
				return -100000;
			}
		}
		void ResetSize(){
			MaxSize = 0;
		}
		int FindGlobaly(const char* indentifier){
			int address = 0;
			for (std::list<ConstGlobalSymbol*>::iterator it = ConstGlobalSymbols->begin(); it != ConstGlobalSymbols->end(); ++it){
				if(!strcmp((*it)->TheSymbol->Name,indentifier)){
					goto end_search;
				}
				address += (*it)->TheSymbol->Type->Size;
			}
			end_search:
			return address;
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