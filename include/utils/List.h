#ifndef _UTILS_MYLIST_H
#define _UTILS_MYLIST_H

#include <stdint.h>

namespace utils {
    template<typename T>
    class List {
    private:
        struct _NodeBase {
            _NodeBase *prev;
            _NodeBase *next;
        };

        struct _Node : _NodeBase {
            T val;
        };

        template<typename U>
        class _Iterator {
        public:
            _Iterator(List<U> &list) : mList(list) {
                mPosition = &list.mHead;
            }

            _Iterator &operator=(const _Iterator &it) {
                if (&mList == &it.mList) {
                    mPosition = it.mPosition;
                }
                return *this;
            }

            ~_Iterator() {}

            _Iterator &operator++(int) { // post-increment
                mPosition = mPosition->next;
                return *this;
            }

            _Iterator &operator--(int) { // post-decrement
                mPosition = mPosition->prev;
                return *this;
            }

            bool isNull() { return mPosition == &mList.mHead; }

            U *getVal() {
                if (!isNull()) {
                    return &(static_cast<_Node *>(mPosition)->val);
                }
                return nullptr;
            }

        private:
            _Iterator(List<U> &list, _NodeBase *node) : mList(list) {
                mPosition = node;
            }

            _NodeBase *mPosition;
            List<U> &mList;

            friend class List;
        };

        _NodeBase mHead;
        uint32_t mSize;
    public:
        typedef _Iterator<T> Iterator;

        List() {
            mHead.prev = &mHead;
            mHead.next = &mHead;
            mSize = 0;
        }

        ~List() {}

        bool isEmpty() {
            return mHead.next == &mHead;
        }

        uint32_t size() {
            return mSize;
        }

        Iterator begin() {
            return Iterator(*this, mHead.next);
        }

        Iterator end() {
            return Iterator(*this, mHead.prev);
        }

        void pushBack(const T &val) {
            Iterator it = this->end();
            insertAfter(it, val);
        }

        void pushFront(const T &val) {
            Iterator it = this->begin();
            insertBefore(it, val);
        }

        void insertBefore(Iterator &it, const T &val) {
            _NodeBase *pNode = it.mPosition;
            _Node *pNewNode = new _Node();
            pNewNode->next = pNode;
            pNewNode->prev = pNode->prev;
            pNewNode->val = val;
            pNode->prev->next = pNewNode;
            pNode->prev = pNewNode;
        }

        void insertAfter(Iterator &it, const T &val) {
            _NodeBase *pNode = it.mPosition;
            _Node *pNewNode = new _Node();
            pNewNode->next = pNode->next;
            pNewNode->prev = pNode;
            pNewNode->val = val;
            pNode->next = pNewNode;
            pNewNode->next->prev = pNewNode;
        }
    };
}

#endif // _UTILS_MYLIST_H