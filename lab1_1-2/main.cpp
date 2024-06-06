#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int CAP = 65536;

auto ZERO = [](){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 0;
};

struct Data{
    ushort key;
    string value;
};

void countingSort(vector<Data>& input){
    vector<int> count(CAP,0);
    vector<int> pos(CAP,0);
    vector<Data> res(input.size());
    for (size_t i = 0; i < input.size(); i++)
    {
        count[input[i].key]+=1;
    }
    for (size_t i = 1; i < pos.size(); i++)
    {
        pos[i] = pos[i-1]+count[i-1];
    }
    for (size_t i = 0; i < input.size(); i++)
    {
        res[pos[input[i].key]++] = std::move(input[i]);
    }
    input = std::move(res);
}



int main(){
    vector<Data> input;
    input.reserve(1000000);
    ushort key1;
    string value1;
    while(cin>>key1>>value1){
        input.push_back({key1,value1});
    }
    countingSort(input);
    for(const auto& [key,value]:input){
        cout << key << "\t" << value << "\n";
    }
    return 0;
}