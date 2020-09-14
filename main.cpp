#include <iostream>
#include <list>
#include <map>
#include <string>
#include <vector>
#include <unordered_map>


using namespace std;


template<typename T>
struct page {
    int time, frequency;
    T data;

    page(T input_data) {
        data = input_data;
        time = 0;
        frequency = 1;
    }

    void increase_time() {
        this->time++;
    };
};

template<typename T>
T find_min_frequency(unordered_map<T, page<T>> cache) {
    int min = cache.begin()->second.frequency, time = cache.begin()->second.time;
    T answer = cache.begin()->first;
    for (auto it = cache.begin(); it != cache.end(); ++it) {
        if (it->second.frequency < min) {
            answer = it->first;
            min = cache.find(answer)->second.frequency;
            time = cache.find(answer)->second.time;
        }
        if (it->second.frequency == min && it->second.time > time) {
            answer = it->first;
            min = cache.find(answer)->second.frequency;
            time = cache.find(answer)->second.time;
        }
    }
    return answer;
}


int main() {
    //string type;
    //cin >> type;
    int n, m;
    cout << "Number of items in queue and cache" << endl;
    cin >> n >> m;
    int input_data;
    vector<page<int>> queue;
    unordered_map<int, page<int>> cache;
    for (int i = 0; i < n; ++i) {
        cin >> input_data;
        page<int> input_page(input_data);
        queue.push_back(input_page);
        if (i < m) {
            if (cache.find(input_data) == cache.end()) {
                cache.emplace(input_data, queue[i]);
                for (auto it = cache.begin()++; it != cache.end(); ++it) {
                    it->second.increase_time();
                }
            } else {
                for (auto it = cache.begin()++; it != cache.end(); ++it) {
                    it->second.increase_time();
                    if (it->second.data == input_data) {
                        it->second.frequency++;
                        it->second.time = 0;
                    }
                }
            }
        }
        if (i >= m) {
            if (cache.find(input_data) == cache.end()) {
                cache.erase(find_min_frequency(cache));
                cache.insert(cache.find(find_min_frequency(cache)), make_pair(input_data, queue[i]));
                for (auto it = cache.begin()++; it != cache.end(); ++it) {
                    it->second.increase_time();
                }
            } else {
                for (auto it = cache.begin()++; it != cache.end(); ++it) {
                    it->second.increase_time();
                    if (it->second.data == input_data) {
                        it->second.frequency++;
                        it->second.time = 0;
                    }
                }
            }
        }
    }

    for (auto it = cache.begin(); it != cache.end(); it++) {
        cout << it->first << " ";
    }
    return 0;
}