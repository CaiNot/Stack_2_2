#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

class STACK {
    int *const elems;    //申请内存用于存放栈的元素
    const int max;    //栈能存放的最大元素个数
    int pos;            //栈实际已有元素个数，栈空时pos=0;
public:
    STACK(int m) : elems(new int[m]), max(m) {        //初始化栈：最多存m个元素
        this->pos = 0;
    }

    STACK(const STACK &s) : elems(new int[s.size()]), max(s.size()) {            //用栈s拷贝初始化栈
        this->pos = (int) s;
        for (int i = 0; i < this->max; i++) {
            this->elems[i] = s[i];
        }
    }

    virtual int size() const {            //返回栈的最大元素个数max
        return this->max;
    }

    virtual operator int() const {            //返回栈的实际元素个数pos
        return this->pos;
    }

    virtual int operator[](int x) const {    //取下标x处的栈元素，第1个元素x=0
        return this->elems[x];
    }

    virtual STACK &operator<<(int e) {    //将e入栈,并返回栈
        this->elems[this->pos] = e;
        this->pos++;
        return *this;
    }

    virtual STACK &operator>>(int &e) {    //出栈到e,并返回栈
        this->pos--;
        e = this->elems[this->pos];
        return *this;
    }

    virtual STACK &operator=(const STACK &s) { //赋s给栈,并返回被赋值的栈
        int i = 0;
        int len = (int) s;
        delete this->elems;

        *(int **) &this->elems = new int[s.size()];
        *(int *) &this->max = s.size();


        for (i = 0; i < len; i++) {
            if (this->pos < s.size()) {
                this->elems[i] = s.elems[i];
                this->pos++;
            }
        }
        return *this;
    }

    virtual void print() const {        //打印栈
        for (int i = 0; i < this->pos; i++) {
            cout << this->elems[i] << "  ";
        }
    }

    virtual ~STACK() {                    //销毁栈
        delete[] elems;
    }
};

bool isNum(char c) {
    return c >= '0' && c <= '9';
}

ofstream saveMessage("U201614751.txt");

int main(int argc, char *argv[]) {

//    int const a = 1;
//    int *b = (int *) &a;
//    *b = 2;
//    cout << a << " " << *b << endl;
//    saveMessage.close();
//    return 0;
    if (!saveMessage.is_open())
        return 1;

    if (argc > 1) {
        int i = 1;
        int e = 0;

        int model = 0;

        int j = 0;
        int popNum = 0;
        STACK *p = 0;
        STACK *c = 0;


        bool isEnd = false;
        for (; i < argc; i++) {
            if (isEnd) {
                delete p;
                return 0;
            }

            if (strcmp(argv[i], "-S") == 0) {
                int m = atoi(argv[i + 1]);
                i++;
                p = new STACK(m);
                cout << "S  " << m << "  ";
                saveMessage << "S  " << m << "  ";

            } else {

                if (strcmp(argv[i], "-I") == 0) {
                    model = 1;
                } else if (strcmp(argv[i], "-O") == 0) {
                    model = 2;
                } else if (strcmp(argv[i], "-C") == 0) {
                    model = 3;
                    i--;
                } else if (strcmp(argv[i], "-A") == 0) {
                    model = 4;
                } else if (strcmp(argv[i], "-N") == 0) {
                    model = 5;
                    i--;
                } else if (strcmp(argv[i], "-G") == 0) {
                    model = 6;
                } else {
                    i--;
                }
                i++;
                switch (model) {
                    case 1:
                        cout << "I  ";
                        saveMessage << "I  ";

                        for (; i < argc; i++) {
                            if (isNum(argv[i][0])) {
                                if ((int) *p < p->size()) {
                                    e = atoi(argv[i]);
                                    *p << e;
                                } else {
                                    cout << "E";
                                    saveMessage << "E";

                                    isEnd = true;
                                    break;
                                }
                            } else {
                                i--;
                                break;
                            }
                        }
                        if (!isEnd)
                            p->print();
                        break;
                    case 2:
                        popNum = atoi(argv[i]);

                        cout << "O  ";
                        saveMessage << "O  ";

                        for (j = 0; j < popNum; j++) {
                            if ((int) *p < 1) {
                                cout << "E";
                                saveMessage << "E";

                                isEnd = true;
                                break;
                            }
                            *p >> e;
                        }
                        if (!isEnd) {
                            p->print();
                        }
                        break;
                    case 3:
                        c = new STACK(*p);
                        delete p;
                        p = c;

                        cout << "C  ";
                        saveMessage << "C  ";
                        p->print();
                        break;
                    case 4:
                        c = new STACK(atoi(argv[i]));
//                        c = new STACK(p->size());
                        *c = *p;
                        delete p;
                        p = c;
                        cout << "A  ";
                        saveMessage << "A  ";
                        p->print();
                        break;
                    case 5:
                        cout << "N  " << (int) *p << "  ";
                        saveMessage << "N  " << (int) *p << "  ";
                        break;
                    case 6:
                        e = atoi(argv[i]);
                        cout << "G  ";
                        saveMessage << "G  ";
                        if (e < (int) *p && e >= 0) {
                            cout << (*p)[e] << "  ";
                            saveMessage << (*p)[e] << "  ";
                        } else {
                            cout << "E";
                            saveMessage << "E";
                            isEnd = true;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }
    saveMessage.close();
    return 0;
}