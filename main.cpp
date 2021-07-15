#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Memory{
public:
    //string name;
    int start;      //起点
    int len;     //长度
    Memory(){
        start = 0;
        len = 1;
    }
    Memory(int _start, int _len){
        start = _start;
        len = _len;
    }
};

bool cmp(Memory a, Memory b){
    return a.len > b.len;
}

vector<Memory> memory;
vector<Memory> history;

void allocate(int _size){    //分配
    bool isSuccess = false;
    for(int i = 0; i < memory.size(); i++){
        if(memory[i].len == _size){     //如果大小一致
            int _begin = memory[i].start;   //这个数据块起点
            swap(memory[i], memory[memory.size()-1]);   //用于删除这个数据块
            memory.pop_back();
            history.push_back(Memory(_begin, _size));          //保存这个已经被分配的数据块
            cout << "分配成功！" << endl;
            isSuccess = true;
            break;
        }
        else if(memory[i].len > _size) {    //如果空闲块略大
            int _begin = memory[i].start;   //起点
            int _start = memory[i].start + _size;   //剩余数据块的起点
            int _len = memory[i].len - _size;
            swap(memory[i], memory[memory.size()-1]);
            memory.pop_back();
            memory.push_back(Memory(_start, _len));     //将剩余数据块插入
            history.push_back(Memory(_begin, _size));   //保存
            cout << "分配成功！" << endl;
            isSuccess = true;
            break;;
        }
    }
    sort(memory.begin(), memory.end(), cmp);
    sort(history.begin(), history.end(), cmp);

    if(!isSuccess){
        cout << "分配失败" << endl;
    }

}

void recycle(int _num){     //回收
    if(_num < 0 || _num >= history.size()){
        cout << "回收失败" << endl;
        return;
    }

    int _start = history[_num].start;
    int _len = history[_num].len;

    //从history中删除数据块
    swap(history[_num], history[history.size()]);
    history.pop_back();
    sort(history.begin(), history.end(), cmp);

    //向前合并
    for(int i = 0; i < memory.size(); i++){
        if((memory[i].start + memory[i].len) == _start){
            _start = memory[i].start;
            _len += memory[i].len;
            //删除这个块
            swap(memory[i], memory[memory.size()]);
            memory.pop_back();
            sort(memory.begin(), memory.end(), cmp);
            break;
        }
    }
    //向后合并
    for(int i = 0; i < memory.size(); i++){
        if(memory[i].start == (_start+_len)){
            _len += memory[i].len;
            //删除这个块
            swap(memory[i], memory[memory.size()]);
            memory.pop_back();
            sort(memory.begin(), memory.end(), cmp);
            break;
        }
    }
    //插入
    memory.push_back(Memory(_start, _len));
    sort(memory.begin(), memory.end(), cmp);
    cout << "回收成功！" << endl;
}

void show(){        //展示
    cout << "------剩余空闲块--------" << endl;
    for(int i = 0; i < memory.size(); i++){
        cout << "块" << i << " start：" << memory[i].start << " len：" << memory[i].len << endl;
    }
    cout << "------已分配数据块------" << endl;
    for(int i = 0; i < history.size(); i++){
        cout << "块" << i << " start：" << history[i].start << " len：" << history[i].len << endl;
    }
    cout << "----------------------" << endl;
}
int main() {
    char a;
    int index = 1;

    memory.push_back(Memory(0, 128*1024));
    while (true){
        cout << "-------主存管理-------" << endl;
        cout << "输入q退出，输入a分配，输入r回收，输入s展示空余空间" << endl;
        cout << index++ << ": ";
        cin >> a;
        switch (a) {
            case 'q':
                goto L1;
            case 'a':
                cout << "分配，请输入长度:";
                int size;
                cin >> size;
                allocate(size);
                break;
            case 'r':
                cout << "回收，请输入块号:";
                int num;
                cin >> num;
                recycle(num);
                break;
            case 's':
                cout << "展示" << endl;
                show();
                break;
            default:
                break;
        }
    }
L1:
    cout << "退出成功" << endl;
    return 0;
}
