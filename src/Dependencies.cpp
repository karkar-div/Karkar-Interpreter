#pragma once

#include <string.h>
#include <list>
#include <vector>
#include <dlfcn.h>
#include <stdio.h>
#include <stdint.h>

class Dependency{
    private:
        void *so_library;
        int64_t (*loaded_function)(int64_t,int64_t,int64_t,int64_t,int64_t,int64_t);
        void safe_strcopy(char* desk,const char* source,int buffersize){
            if((strlen(desk)+1)<=(size_t)buffersize)
                strcpy(desk,source);
            else
                throw ("the name is too long");
        }
    public:
        char Function[20];
        char Library[20];
        Dependency(const char* library,const char* function,bool init = true){
            safe_strcopy(Library,library,sizeof(Library));
            safe_strcopy(Function,function,sizeof(Function));
            if(init) initalize();
        }
        void initalize(){
            so_library = dlopen(Library, RTLD_LAZY);
            if (!so_library) 
                throw(dlerror());
            loaded_function = (int64_t(*)(int64_t,int64_t,int64_t,int64_t,int64_t,int64_t))dlsym(so_library,Function);
            if (!loaded_function) {
                dlclose(so_library);
                throw(dlerror());
            }
        }
        inline int64_t Run(int64_t* args,int args_num){
            return loaded_function(args[0],args[1],args[2],args[3],args[4],args[5]);
        }
        Dependency* Clone() const {
            return new Dependency(Library,Function);
        }
        void info(){
            printf("Library: %s\n",Library);
            printf("Function: %s\n",Function);
        }
        ~Dependency(){
            dlclose(so_library);
        }
};

std::list<Dependency*>* Global_Dependencies;