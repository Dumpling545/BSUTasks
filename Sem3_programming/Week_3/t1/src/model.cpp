#include "model.h"

Model::Model(){}

OutputInfo Model::refresh(InputInfo inputInfo){
    OutputInfo output;
    Set<Element*> set = {inputInfo.elems[0], inputInfo.elems[1]};
    SetIterator<Element*> it = set.iterator();
    int index = 0;
    OutputElementInfo element;
    do{
        //value
        ToString to_str_visitor;
        it.current()->accept(to_str_visitor);
        element.view = to_str_visitor.value;
        //type
        GetType g_type_visitor;
        it.current()->accept(g_type_visitor);
        element.type = g_type_visitor.value;
        //first element
        FirstElement fe_visitor;
        it.current()->accept(fe_visitor);
        element.firstElement = dbl_to_str(fe_visitor.value);
        //last element
        LastElement le_visitor;
        it.current()->accept(le_visitor);
        element.lastElement = dbl_to_str(le_visitor.value);
        //sum
        SumOfElements sum_visitor;
        it.current()->accept(sum_visitor);
        element.sum = dbl_to_str(sum_visitor.value);

        output.elementInfo[index++] = element;

        it.next();
    } while(it.hasNext());
    return output;
}
std::string Model::dbl_to_str(double d){
    std::stringstream ss;
    ss << d;
    return ss.str();
}
