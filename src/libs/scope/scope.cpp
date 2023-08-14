#include "scope.hpp"

Scope::Scope() : parent(nullptr){}

Scope::Scope(Scope* parent) {
 //   assert(parent != nullptr);
}

void Scope::Decrement_Reference(Value* value){

    if(value != nullptr) value->Decrement_Reference_counting();
}

void Scope::Increment_Reference(Value* value){

    if(value != nullptr) value->Increment_Reference_counting();
}

void Scope::define(const std::string& name, Value* value) {
    
    auto it = values.find(name);
   
    if (it != values.end()) {
        Decrement_Reference(it->second);
        it->second = value;
        Increment_Reference(it->second);
    } else {
        values.emplace(name, value);
        Increment_Reference(value);
    }
}

Value * Scope::get(std::string name) {

    auto it = values.find(name);
   
    if (it != values.end()) return it->second;

    throw std::runtime_error("Undeclared variable '" + name + "'");
}
