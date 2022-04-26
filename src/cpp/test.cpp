#include <iostream>
#include "class.h"

int main(){
    CD *diagram = new CD;
    Entity *ent1 = new Entity;
    Entity *ent2 = new Entity;
    diagram->addEntity(ent1);
    diagram->addEntity(ent2);
    Erconnect *con1 = new Erconnect(ent1, ent2);
    diagram->addConnection(con1);
    Attribute *attr1 = new Attribute;
    Attribute *attr2 = new Attribute;
    attr1->updateName("var");
    attr2->updateName("test");
    ent1->addAttribute(attr1);
    ent1->addAttribute(attr2);
    Method *meth1 = new Method;
    Method *meth2 = new Method;
    meth1->updateName("var");
    meth2->updateName("test");
    ent1->addMethod(meth1);
    ent1->addMethod(meth2);
    ent1->RemoveMethod(meth1);
    ent1->RemoveMethod(meth2);
    ent1->RemoveAttribute(attr1);
    ent1->RemoveAttribute(attr2);
    diagram->RemoveEntity(ent1);
    delete diagram;
    delete con1;
}