#include <iostream>
#include <fstream>
#include <map>

int maxValue(std::map<std::pair<int, int>, int>& map, int values[], int sizes[], int capacity, int i) {
    if (i == 0) {
        return 0;
    }

    auto key = std::make_pair(i, capacity);
    auto it = map.find(key);
    if(it != map.end())
    {
        return it->second;
    }

    int maxValueIfThisIndexIsNotIncluded = maxValue(map, values, sizes, capacity, i - 1);

    if (sizes[i - 1] > capacity) {
        return maxValueIfThisIndexIsNotIncluded;
    }

    int maxValueIfThisIndexIsIncluded = values[i - 1] + maxValue(map, values, sizes, capacity - sizes[i - 1], i - 1);

    int maxVal = std::max(maxValueIfThisIndexIsNotIncluded, maxValueIfThisIndexIsIncluded);
    auto ret = map.insert(std::make_pair(key, maxVal));

    return maxVal;
}

struct Data {
    int capacity;
    int n;
    int *values;
    int *sizes;
};

Data *readData() {
    std::ifstream input("input3.txt");

    int n;
    int capacity;

    input >> capacity >> n;

    int *values = new int[n];
    int *sizes = new int[n];


    for (int i = 0; i < n; i++) {
        input >> values[i] >> sizes[i];
    }

    Data *data = new Data;
    data->n = n;
    data->capacity = capacity;
    data->values = values;
    data->sizes = sizes;

    return data;
}

int main() {
    Data *data = readData();

    std::map<std::pair<int, int>, int> map;
    std::cout << maxValue(map, data->values, data->sizes, data->capacity, data->n) << std::endl;

    return 0;
}
