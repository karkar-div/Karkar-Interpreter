
#include <list>
#include <vector>

#define CAPACITY 1000

#include "Statements.cpp"

class ScopeStack{
	public:
		int Top = -1;
		std::vector<Statement*> Elements;
		ScopeStack(){
			Elements = std::vector<Statement*>(CAPACITY);
		}
		void Push(Statement* statement,int index){
			int collapse_num = Top-index + 1;
			for(int i = 0; i < collapse_num;i++)
				collapse();
			if(index == Top+1)
				Elements[index] = statement;
			else 
				throw ("Incorrect indentation");
			Top = index;
		}
		void flat(int index){
			int collapse_num = Top-index + 1;
			for(int i = 0; i < collapse_num;i++)
				collapse();
		}
		void collapse() {
			Statement* child = Elements[Top];
			Top--;
			((CompoundStatement*)Elements[Top])->Statements->push_back(child);
		}
};

ScopeStack* Scopes;