/*
 * 双向链表模板类。
 * 整个双向链表有两种结点：带值的结点和不带值的结点。
 * 不带值的结点整个链表中有且只有一个，用于表示链表的头部。此外，其他结点都是带值的结点。
 * 该链表可使用迭代器进行顺序访问。
 * 该链表是STL list的裁剪版本，只实现了其部分接口。
 */
#ifndef _UTILS_DYNAMICLIST_H
#define _UTILS_DYNAMICLIST_H

#include <cstdint>
#include "utils/List.h"

namespace utils {
    template<typename T>
    class DynamicList {
    private:
        struct _Node {
            ListNode node;
            T val;
        };
        ListNode mHead;

        template<typename U>
        class _Iterator {
        public:
            _Iterator(DynamicList<U> &list) : mList(&list), mPosition(&list.mHead) {}

            ~_Iterator() {}

            _Iterator &operator=(const _Iterator &it) {
                if (mList == it.mList) {
                    mPosition = it.mPosition;
                }
                return *this;
            }

            _Iterator &operator++(int) { // post-increment
                mPosition = mPosition->next();
                return *this;
            }

            _Iterator &operator--(int) { // post-decrement
                mPosition = mPosition->prev();
                return *this;
            }

            bool isNull() { return mPosition == &mList->mHead; }

            U *getVal() {
                if (!isNull()) {
                    return &(GetContainerOfListNode(mPosition, _Node, node)->val);
                }
                return nullptr;
            }

            bool operator==(const _Iterator &it) {
                return (&mList == &it.mList) && (mPosition == it.mPosition);
            }

            bool operator!=(const _Iterator &it) {
                return (&mList != &it.mList) || (mPosition != it.mPosition);
            }

        private:
            DynamicList<U> *mList;
            ListNode *mPosition;

            _Iterator(DynamicList<U> *list, ListNode *node) : mList(list), mPosition(node) {}

            friend class DynamicList;
        };

    public:
        typedef _Iterator<T> Iterator;

        DynamicList() : mHead() {}

        ~DynamicList() { clear(); }

        bool isEmpty() { return mHead.next() == &mHead; }

        uint32_t size() {
            uint32_t n = 0;
            ListNode *node;
            ForeachListNode(node, &mHead)n++;
            return n;
        }

        Iterator begin() { return Iterator(this, mHead.next()); }

        Iterator end() { return Iterator(this, mHead.prev()); }

        void pushBack(const T &val) {
            Iterator it = this->end();
            insertAfter(it, val);
        }

        void pushFront(const T &val) {
            Iterator it = this->begin();
            insertBefore(it, val);
        }

        void insertBefore(Iterator &it, const T &val) {
            _Node *newNode = new _Node();
            newNode->val = val;
            it.mPosition->insertBefore(newNode->node);
        }

        void insertAfter(Iterator &it, const T &val) {
            _Node *newNode = new _Node();
            newNode->val = val;
            it.mPosition->insertAfter(newNode->node);
        }

        void clear() {
            ListNode *node, *nextNode;
            ForeachListNodeSafe(node, nextNode, &mHead) {
                delete GetContainerOfListNode(node, _Node, node);
            }
        }

        void remove(Iterator &it, bool moveNext = true) {
            if (!it.isNull()) {
                ListNode *node = it.mPosition;
                if (moveNext) {
                    it.mPosition = node->next();
                } else {
                    it.mPosition = node->prev();
                }
                delete GetContainerOfListNode(node, _Node, node);
            }
        }

//        bool popBack(T &val) {
//            if (isEmpty())
//                return false;
//            Iterator it = this->end();
//            val = *(it.getVal());
//            remove(it);
//            return true;
//        }
//
//        bool popFront(T &val) {
//            if (isEmpty())
//                return false;
//            Iterator it = this->begin();
//            val = *(it.getVal());
//            remove(it);
//            return true;
//        }
    };
}

#endif // _UTILS_DYNAMICLIST_H