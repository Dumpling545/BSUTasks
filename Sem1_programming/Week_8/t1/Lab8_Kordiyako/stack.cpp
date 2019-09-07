#include "complexNumber.h"
#include "stack.h"
template class ComplexNumber;
void Stack<ComplexNumber>::push(ComplexNumber item){
    StackItem<ComplexNumber> newItem(item, firstItem);
    firstItem = newItem;
}
ComplexNumber* Stack<ComplexNumber>::first(){
    return firstItem.value;
}
ComplexNumber* Stack<ComplexNumber>::pop(){
}
Stack<ComplexNumber>::Stack(){
    firstItem = nullptr;
}
