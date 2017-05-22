/*
 *
 */
#ifndef _UTILS_LIST_H
#define _UTILS_LIST_H

#include <cstddef>

namespace utils {
    class ListNode {
    public:
        ListNode() { mPrev = mNext = this; }

        void insertBefore(ListNode &node) { insert(&node, this->mPrev, this); }

        void insertAfter(ListNode &node) { insert(&node, this, this->mNext); }

        void pushBack(ListNode &head) { insertBefore(head); }

        void pushFront(ListNode &head) { insertAfter(head); }

        ListNode *prev() { return mPrev; }

        ListNode *next() { return mNext; }

        ~ListNode() { remove(); }

        void remove() {
            mPrev->mNext = mNext;
            mNext->mPrev = mPrev;
            mPrev = this;
            mNext = this;
        }

    private:
        static void insert(ListNode *node, ListNode *prev, ListNode *next) {
            next->mPrev = node;
            node->mNext = next;
            node->mPrev = prev;
            prev->mNext = node;
        }

        ListNode *mPrev;
        ListNode *mNext;
    };
}

#define ForeachListNode(node, head) \
    for (node = (head)->next(); node != (head); node = node->next())

#define ForeachListNodeSafe(node, nextNode, head) \
    for (node = (head)->next(), nextNode = node->next(); node != (head); \
         node = nextNode, nextNode = node->next())

#define GetContainerOfListNode(node, container_type, node_member) \
    reinterpret_cast<container_type *>(reinterpret_cast<char *>(node) - offsetof(container_type, node_member))

#endif //_UTILS_LIST_H
