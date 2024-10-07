

#ifndef UNIVERSAL_GARBAGE_H
#ifndef UNIVERSAL_GARBAGE_H
#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define UniversalGarbage_create_empty_struct(name,element_type) \
(element_type*)malloc(sizeof(element_type));    \
*name = (element_type){0};


#define UniversalGarbage_cast(value) ((void**)&value)


#define UniversalGarbage_add(garbage,deallocator_callback,value) \
    rawUniversalGarbage_add(garbage,(void(*)(void*))deallocator_callback,UniversalGarbage_cast(value))

#define UniversalGarbage_add_simple(garbage,value) \
     UniversalGarbage_add(garbage,free,value)


#define UniversalGarbage_add_return(garbage,deallocator_callback,value) \
        UniversalGarbage_add(garbage->return_values,deallocator_callback,value)


#define UniversalGarbage_add_simple_return(garbage,value) \
    UniversalGarbage_add_simple(garbage->return_values,value)



#define  UniversalGarbage_remove(garbage,value) \
    rawUniversalGarbage_remove(garbage,UniversalGarbage_cast(value));


#define  UniversalGarbage_disconnect(garbage,value) \
    rawUniversalGarbage_disconnect(garbage,UniversalGarbage_cast(value));




#define UniversalGarbage_reallocate(garbage,value) \
    rawUniversalGarbage_reallocate(garbage,UniversalGarbage_cast(value))


#define UniversalGarbage_resset(garbage,value) \
    rawUniversalGarbage_resset(garbage,UniversalGarbage_cast(value))



#ifndef PRIVATE_UNIVERSGAL_GARBAGE_ELEMENT_TYPE
#define PRIVATE_UNIVERSGAL_GARBAGE_ELEMENT_TYPE
typedef struct privateUniversalGarbageElement{
    void **pointer;
    void (*deallocator_callback)(void *element);
    void *pointed_value;
}privateUniversalGarbageElement;
#endif



#ifndef  PRIVATE_UNIVERSAL_GARBAGE_TYPE
#define PRIVATE_UNIVERSAL_GARBAGE_TYPE


typedef  struct UniversalGarbage{

    struct UniversalGarbage *return_values;
    privateUniversalGarbageElement **elements;
    int  elements_size;
    bool is_the_root;

}UniversalGarbage;
#endif














void private_UniversalGarbageSimpleElement_free_pointed_value(privateUniversalGarbageElement *self);


void private_UniversalGarbageSimpleElement_free(privateUniversalGarbageElement *self);

privateUniversalGarbageElement * private_newUniversalGarbageSimpleElement(void (*dealocator_callback)(void *element), void **pointer);







UniversalGarbage * newUniversalGarbage();

UniversalGarbage * private_new_MainUniversalGarbage();



bool  rawUniversalGarbage_resset(UniversalGarbage *self, void **pointer);

bool  rawUniversalGarbage_remove(UniversalGarbage *self, void **pointer);

bool  rawUniversalGarbage_disconnect(UniversalGarbage *self, void **pointer);

bool rawUniversalGarbage_reallocate(UniversalGarbage *self, void **pointer);

bool  rawUniversalGarbage_add(UniversalGarbage *self,  void (*dealocator_callback)(void *element), void **pointer);

void private_UniversalGarbage_free_all_sub_elements(UniversalGarbage *self);

void UniversalGarbage_free_including_return(UniversalGarbage *self);

void UniversalGarbage_free(UniversalGarbage *self);





#ifdef __cplusplus
}
#endif

#define UNIVERSAL_GARBAGE_H
#endif










privateUniversalGarbageElement * private_newUniversalGarbageSimpleElement(void (*dealocator_callback)(void *element), void **pointer){

    privateUniversalGarbageElement * self = UniversalGarbage_create_empty_struct(
        self,
        privateUniversalGarbageElement
    );
    self->pointer = pointer;
    self->deallocator_callback = dealocator_callback;
    self->pointed_value = *pointer;
    return  self;
}
void private_UniversalGarbageSimpleElement_free_pointed_value(privateUniversalGarbageElement *self){
    if(self->pointed_value){
        self->deallocator_callback(self->pointed_value);
        self->pointed_value = NULL;
    }
}

void private_UniversalGarbageSimpleElement_free(privateUniversalGarbageElement *self){
    private_UniversalGarbageSimpleElement_free_pointed_value(self);
    free(self);
}






UniversalGarbage * private_new_MainUniversalGarbage(){
    UniversalGarbage *self = UniversalGarbage_create_empty_struct(self,UniversalGarbage)
    self->elements = (privateUniversalGarbageElement**)malloc(0);
    self->is_the_root = false;
    return self;
}

UniversalGarbage * newUniversalGarbage(){
    UniversalGarbage *self = UniversalGarbage_create_empty_struct(self,UniversalGarbage)
    self->is_the_root = true;
    self->elements = (privateUniversalGarbageElement**)malloc(0);
    self->return_values =private_new_MainUniversalGarbage();

    return self;
}




bool  rawUniversalGarbage_reallocate(UniversalGarbage *self, void **pointer){

    if(self->is_the_root){

        if(rawUniversalGarbage_reallocate(self->return_values,pointer)){
            return true;
        }
    }


    for(int i = 0; i < self->elements_size; i++){

        privateUniversalGarbageElement *current = self->elements[i];
        bool reallocate = current->pointer == pointer;

        if(reallocate){
            current->pointed_value = *pointer;
            return true;
        }
    }
    return false;
}

bool rawUniversalGarbage_resset(UniversalGarbage *self, void **pointer){

    if(self->is_the_root){
        if(rawUniversalGarbage_resset(self->return_values,pointer)){
            return true;
        }
    }


    for(int i = 0; i < self->elements_size; i++){
        privateUniversalGarbageElement *current = self->elements[i];
        bool resset = current->pointer == pointer;
        if(resset){
            private_UniversalGarbageSimpleElement_free_pointed_value(current);
            current->pointed_value = *pointer;
            return true;
        }
    }
    return  false;

}
bool  rawUniversalGarbage_remove(UniversalGarbage *self, void **pointer){
    if(self->is_the_root){
        if(rawUniversalGarbage_remove(self->return_values,pointer)){
            *pointer = NULL;
            return true;
        }
    }

    for(int i = 0; i < self->elements_size; i++){
        privateUniversalGarbageElement *current = self->elements[i];
        if(current->pointer == pointer){
            private_UniversalGarbageSimpleElement_free(current);
            self->elements_size-=1;
            bool its_not_the_last = i < self->elements_size;
            if(its_not_the_last){
                self->elements[i] = self->elements[self->elements_size];

            }
            *pointer = NULL;
            return  true;
        }
    }
    return  false;
}
bool  rawUniversalGarbage_disconnect(UniversalGarbage *self, void **pointer){
    if(self->is_the_root){
        if(rawUniversalGarbage_disconnect(self->return_values,pointer)){
            return true;
        }
    }

    for(int i = 0; i < self->elements_size; i++){
        privateUniversalGarbageElement *current = self->elements[i];
        if(current->pointer == pointer){
            free(current);
            self->elements_size-=1;
            bool its_not_the_last = i < self->elements_size;
            if(its_not_the_last){
                privateUniversalGarbageElement *last_element =  self->elements[self->elements_size];
                self->elements[i] = last_element;
            }
            return true;
        }
    }
    return  false;



}
bool  rawUniversalGarbage_add(UniversalGarbage *self,  void (*dealocator_callback)(void *element), void **pointer){

    if(!pointer){
        return false;
    }

    if(*pointer){
        for(int i = 0; i < self->elements_size; i++){
            privateUniversalGarbageElement *current = self->elements[i];
            if(current->pointed_value == *pointer){
                return false;
            }
        }
    }


    self->elements = (privateUniversalGarbageElement**)realloc(
            self->elements,
            (self->elements_size + 1) * sizeof(privateUniversalGarbageElement*)
    );



    self->elements[self->elements_size] = private_newUniversalGarbageSimpleElement(dealocator_callback, pointer);
    self->elements_size+=1;
    return  true;
}



void  private_UniversalGarbage_free_all_sub_elements(UniversalGarbage *self){
    for(int i = 0; i < self->elements_size; i++){
        private_UniversalGarbageSimpleElement_free(self->elements[i]);
    }
    free(self->elements);
}

void UniversalGarbage_free_including_return(UniversalGarbage *self){
    private_UniversalGarbage_free_all_sub_elements(self);
    if(self->is_the_root){
        UniversalGarbage_free(self->return_values);
    }
    free(self);
}

void UniversalGarbage_free(UniversalGarbage *self){
    private_UniversalGarbage_free_all_sub_elements(self);

    if(self->is_the_root){

        UniversalGarbage *return_garbage = self->return_values;
        for(int i = 0; i < return_garbage->elements_size; i++){
            free(return_garbage->elements[i]);
        }

        free(return_garbage->elements);
        free(return_garbage);
    }


    free(self);
}






#define UNIVERSAL_GARBAGE_H
#endif
