#include "geoelement.h"

// 构造函数，链表初始化
polygonSet::polygonSet()
{
    head.pre = NULL;
    head.next = &tail;
    tail.pre = &head;
    tail.next = NULL;
    it = &head;
}

// 析构函数，释放所有节点
polygonSet::~polygonSet() {release();}

// 在it后面插入节点，插入后it指向新节点
void polygonSet::insert(struct polygonNode p)
{
    struct polygonNode* tmp = new struct polygonNode;
    *tmp = p;
    it -> next -> pre = tmp;
    tmp -> next = it -> next;
    it -> next = tmp;
    tmp -> pre = it;
    it = tmp;
}

// 移除it节点，移除后it指向后面节点
void polygonSet::remove()
{
    struct polygonNode* tmp = it -> next;
    it -> pre -> next = it -> next;
    it -> next -> pre = it -> pre;
    delete it;
    it = tmp;
}

// 释放所有节点
void polygonSet::release()
{
    it = head.next;
    while (it != &tail) remove();
}

// 返回it指针
polygonNode* polygonSet::present() {return it;}

// 移动到下一个节点，如果是tail返回false
bool polygonSet::next()
{
    it = it -> next;
    return (it -> next != NULL) && (it != NULL);
}

// 移动到上一个节点，如果是head返回false
bool polygonSet::pre()
{
    it = it -> pre;
    return (it -> pre != NULL) && (it != NULL);
}

// 移动到head
void polygonSet::first() {it = &head;}

// 移动到tail
void polygonSet::last() {it = &tail;}

