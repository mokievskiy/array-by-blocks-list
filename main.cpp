#include "list.h"
#include <iostream>

using namespace std;

int main() {
    int* arr = new int[5];

    for (int i = 0; i < 5; ++i) {
        cin >> arr[i];
    }

    List<int> l = List<int>(arr, (size_t)5);

    l.push_back(6);
    l.push_back(6);
    l.push_back(6);

    l.pop_back();
    l.push_back(6);
    l.push_back(6);
    l.pop_back();
    l.pop_back();

    return 0;
}
