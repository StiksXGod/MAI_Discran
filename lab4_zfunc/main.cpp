#include <iostream>
#include <vector>



std::vector<int> buildZfunction(const std::string& text){
    int l,r;
    int n = text.size();
    std::vector<int> res(n,0);
    l = r = 0;
    for (int i = 1; i < text.size(); i++)
    {
        if (i<=r)
        {
            res[i] = std::min(r-i+1,res[i-l]);
        }
        while(res[i]+i<text.size() and text[i+res[i]]==text[res[i]]){
            res[i]++;
        }
        if (i+res[i]-1>r)
        {
            r = i+res[i]-1;
            l = i;
        }
    }
    return res;
}

std::vector<int> find(std::string& pattern, std::string& text){
    std::string temp = pattern+"%"+text;
    std::vector<int> z = buildZfunction(temp);
    std::vector<int> res;
    int sizeP = pattern.size();
    for (int i = sizeP+1; i < temp.size(); i++)
    {
        if (z[i]==sizeP)
        {
            res.push_back(i-sizeP-1);
        }
        
    }
    return res;
}


int main(){
    std::string text;
    std::string pat;
    std::cin >> text >> pat;
    std::vector<int> res = find(pat,text);
    for (int elem: res)
    {
        std::cout<< elem <<std::endl;
    }
    


    return 0;
}