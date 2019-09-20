#pragma once
#include <string>
#include "set.h"
class Visitor
{
    public:
        virtual void visit(Set<std::string> &s_set) = 0;
        virtual void visit(Set<int> &i_set) = 0;
        virtual void visit(Set<double> &d_set) = 0;
        virtual void visit(Set<char> &c_set) = 0;
        virtual ~Visitor() = default;
};

class GetType : public Visitor {
    public:
      std::string value;

    public:
      void visit(Set<std::string> &s_set) override {
        value = "Set<std::string>";
      }
      void visit(Set<int> &i_set) override {
        value = "Set<int>";
      }
      void visit(Set<double> &d_set) override {
        value = "Set<double>";
      }
      void visit(Set<char> &c_set) override {
        value = "Set<char>";
      }
};

class GetType : public Visitor {
    public:
      std::string value;

    public:
      void visit(Set<std::string> &s_set) override {
        value = "Set<std::string>";
      }
      void visit(Set<int> &i_set) override {
        value = "Set<int>";
      }
      void visit(Set<double> &d_set) override {
        value = "Set<double>";
      }
      void visit(Set<char> &c_set) override {
        value = "Set<char>";
      }
};
