#pragma once

#include <string.h>
#include <list>
#include <vector>
#include <dlfcn.h>
#include <stdio.h>
#include <stdint.h>

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
        int64_t Run(std::list<int64_t>* arguments){
            void *so_library = dlopen(Library, RTLD_LAZY);
            if (!so_library) 
                throw(dlerror());
            int64_t (*hello)(int64_t,int64_t,int64_t,int64_t,int64_t,int64_t) = (int64_t(*)(int64_t,int64_t,int64_t,int64_t,int64_t,int64_t))dlsym(so_library,Function);
            if (!hello) {
                dlclose(so_library);
                throw(dlerror());
            }
            int64_t args[6];
            int index = 0;
            for(std::list<int64_t>::iterator it = arguments->begin(); it != arguments->end(); ++it){
                if(index <= 5){
                    args[index] = (*it);
                }else{
                    //asm("push");
                }
                index++;
            }

            int64_t returned_value = hello(args[0],args[1],args[2],args[3],args[4],args[5]);
            for(std::list<int64_t>::iterator it = arguments->begin(); it != arguments->end(); ++it){
                if(index <= 5){
                }else{
                    //asm("pop");
                }
                index++;
            }
            dlclose(so_library);
            return returned_value;
        }
};

std::list<Dependency*>* Global_Dependencies;