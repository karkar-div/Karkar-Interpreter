#include <string.h>

#include <dlfcn.h>
#include <stdio.h>

class Dependency{
    private:
        void safe_strcopy(char* desk,const char* source,int buffersize){
            if((strlen(desk)+1)<= buffersize)
                strcpy(desk,source);
            else
                throw ("the name is too long");
        }
    public:
        char Function[20];
        char Library[20];
        Dependency(const char* library,const char* function){
            safe_strcopy(Library,library,sizeof(Library));
            safe_strcopy(Function,function,sizeof(Function));
        }
        void Run(){
            void *so_library = dlopen(Library, RTLD_LAZY);
            if (!so_library) 
                throw(dlerror());
            void (*hello)() = (void(*)())dlsym(so_library,Function);
            if (!hello) {
                dlclose(so_library);
                throw(dlerror());
            }
            hello();
            dlclose(so_library);
        }
};