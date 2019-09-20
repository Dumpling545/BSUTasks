#pragma once
#include <iostream>
#include <string>
#include <initializer_list>
#include <sstream>
class Vector;
class Matrix;

class Visitor{
public:
    virtual void visit(Vector &vector) = 0;
    virtual void visit(Matrix &matrix) = 0;
    virtual ~Visitor() = default;
};

class Element{
public:
    virtual void accept(Visitor &v) = 0;
    virtual ~Element() = default;
};

class Matrix : public Element
{
    public:
        int size_1, size_2;
        double ** elements;
        Matrix (int size_1, int size_2, double ** elements){
            this->size_1 = size_1;
            this->size_2 = size_2;
            this->elements = elements;
        }
        void accept(Visitor &v) override{
            v.visit(*this);
        }
};

class Vector : public Element{
    public:
        int size;
        double * elements;
        Vector (){}
        Vector (int size, double * elements){
            this->size = size;
            this->elements = elements;
        }

        void accept(Visitor &v) override{
            v.visit(*this);
        }
};

class GetType : public Visitor{
    public:
        std::string value;
        void visit(Matrix &m) override{
            value = "Matrix";
        }
        void visit(Vector &v) override{
            value = "Vector";
        }
};

class FirstElement : public Visitor{
    public:
        double value;
        void visit(Matrix &m) override{
            value = m.elements[0][0];
        }
        void visit(Vector &v) override{
            value = v.elements[0];
        }
};

class LastElement : public Visitor{
    public:
        double value;
        void visit(Matrix &m) override{
            value = m.elements[m.size_1 - 1][m.size_2 - 1];
        }
        void visit(Vector &v) override{
            value = v.elements[v.size - 1];
        }
};

class SumOfElements : public Visitor{
    public:
        double value = 0.0;
        void visit(Matrix &m) override{
            for(int i = 0; i < m.size_1; i++){
                for(int j = 0; j < m.size_2; j++){
                    value+= m.elements[i][j];
                }
            }
        }
        void visit(Vector &v) override{
            for(int i = 0; i < v.size; i++){
                value+= v.elements[i];
            }
        }
};

class ToString : public Visitor{
    public:
        std::string value;
        std::stringstream ss;
        void visit(Matrix &m) override{
            for(int i = 0; i < m.size_1; i++){
                for(int j = 0; j < m.size_2; j++){
                    ss << m.elements[i][j] << "  ";
                }
                ss << '\n';
            }
            value = ss.str();
        }
        void visit(Vector &v) override{
            for(int i = 0; i < v.size; i++){
                ss << v.elements[i] << "  ";
            }
            value = ss.str();
        }
};
