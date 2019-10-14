#include "model.h"

Model::Model(){}

void Model::addElement(Element * element){
    elements.push_back(element);
}
OutputInfo Model::refresh(InputInfo inputInfo){
    OutputInfo output;
    if(elements.size() <=  inputInfo.firstIndex ||
       elements.size() <=  inputInfo.secondIndex){
        OutputElementInfo element;
        element.view = "ERROR!";
        output.elementInfo[0] = element;
        output.elementInfo[1] = element;
    } else {
        Set<Element*> set = {elements[inputInfo.firstIndex],
                             elements[inputInfo.secondIndex]};
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
    }
    return output;
}
std::string Model::dbl_to_str(double d){
    std::stringstream ss;
    ss << d;
    return ss.str();
}
