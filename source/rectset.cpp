#include "geoelement.h"

rectSet::rectSet()
{
    head = {{0, 0, 0, 0}, 0, NULL, &tail};
    tail = {{0, 0, 0, 0}, 0, &head, NULL};
    it = &head;
}

// 在it后面插入节点，插入后it指向新节点
void rectSet::insert(RECT rct, int HP)
{
    rectNode* tmp = new rectNode;
    *tmp = {rct, HP, it, it -> next};
    it -> next -> pre = tmp;
    it -> next = tmp;
    it = tmp;
}

// 移除it节点，移除后it指向后面节点
void rectSet::remove()
{
    it -> pre -> next = it -> next;
    it -> next -> pre = it -> pre;
    delete it;
}

// 返回it指针
rectNode* rectSet::present() {return it;}

// 移动到下一个节点，如果是tail返回false
bool rectSet::next()
{
    it = it -> next;
    return it != &tail;
}

// 移动到上一个节点，如果是head返回false
bool rectSet::pre()
{
    it = it -> pre;
    return it != &head;
}

// head后面一个
void rectSet::first() {it = &head;}

// tail前面一个
void rectSet::last() {it = &tail;}

