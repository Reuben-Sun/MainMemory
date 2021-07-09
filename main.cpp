#include <iostream>
#include <string>
using namespace std;

int main() {
    char a;
    int index = 1;
    while (true){
        cout << "-------主存管理-------" << endl;
        cout << "输入q退出，输入s存，输入d删" << endl;
        cout << index++ << ": ";
        cin >> a;
        switch (a) {
            case 'q':
                goto L1;
            case 's':
                cout << "存" << endl;
                break;
            case 'd':
                cout << "删" << endl;
                break;;
            default:
                break;
        }
    }
L1:
    cout << "退出成功" << endl;
    return 0;
}
