#include <algorithm>
#include <functional>
#include <fstream>
#include <iostream>
#include <iterator>
#include <queue>
#include <vector>
#include <ctime>

void selection_sort(std::vector<int>::iterator begin, std::vector<int>::iterator end, std::function<bool(const int&, const int&)> comparator){
    for(; begin != end; ++begin){
        const auto min_it = std::min_element(begin, end, comparator);
        std::iter_swap(min_it, begin);
    }
}

void insertion_sort(std::vector<int>::iterator begin, std::vector<int>::iterator end, std::function<bool(const int&, const int&)> comparator){
    for(auto i = begin + 1; i < end; ++i){
        const auto k = *i;
        auto j = i - 1;
        while(j >= begin && comparator(k, *j)){
            std::iter_swap(j, j+1);
            j--;
        }
        *(j+1) = k;
    }
}

auto Partition(auto begin, auto end, auto comparator){
    auto pivot = std::prev(end, 1);
    auto i = begin;
    for(auto j = begin; j != pivot; ++j){
        if(comparator(*j, *pivot)) std::iter_swap(i++, j);
    }
    std::iter_swap(i, pivot);
    return i;
}

void quicksort(std::vector<int>::iterator begin, std::vector<int>::iterator end, std::function<bool(const int&, const int&)> comparator){
    if(std::distance(begin, end) > 1){
        const auto bound = Partition(begin, end, comparator);
        quicksort(begin, bound, comparator);
        quicksort(bound+1, end, comparator);
    }
}

void merge(auto begin, auto mid, auto end, auto comparator){
    std::vector<int> temp;
    temp.reserve(std::distance(begin, end));
    auto left = begin;
    auto right = mid;
    while(left != mid && right != end){
        if(comparator(*right, *left)){
            temp.emplace_back(*right++);
        }
        else{
            temp.emplace_back(*left++);
        }
    }
    temp.insert(temp.end(), left, mid);
    temp.insert(temp.end(), right, end);
    std::move(temp.begin(), temp.end(), begin);
}

void merge_sort(std::vector<int>::iterator begin, std::vector<int>::iterator end, std::function<bool(const int&, const int&)> comparator){
    const auto size = std::distance(begin, end);
    if(size > 1){
        const auto mid = std::next(begin, size / 2);
        merge_sort(begin, mid, comparator);
        merge_sort(mid, end, comparator);
        merge(begin, mid, end, comparator);
    }
}

void heap_sort(std::vector<int>::iterator begin, std::vector<int>::iterator end, std::function<bool(const int&, const int&)> comparator){
    std::make_heap(begin, end, comparator);  // Heapify in O(n), where n is the number of elements in the given array
    int size = std::distance(begin, end);
    while(size--){
        std::pop_heap(begin, end--, comparator);  // Heap Sort in O(nlogn)
    }
}

int counter = 0;
struct myfunc{
    bool operator()(const int& x, const int& y) const {
        ++counter;
        return x < y;
    }
}func;

void print(const std::vector<int> v){
    for(const int e : v) std::cout << e << " "; 
    std::cout << "\n";
}


int main(){
    srand((unsigned)time(NULL));
    std::clock_t start;
    double duration;
    std::ofstream fout("results.csv");
    fout << "LIST SIZE,SORTING TECHNIQUE,RUNTIME DURATION,COMPARISON COUNT\n";
    
    for(int size = 1000; size <= 50000; size += 1000){
        std::cout << size << std::endl;
        std::vector<int> v(size);
        std::generate(v.begin(), v.end(), std::rand);
        for(auto it = v.begin(); it != v.end(); ++it) *it = (*it) % (size*10);
        
        std::vector<int> v1{v}; counter = 0;
        start = std::clock();
        selection_sort(v1.begin(), v1.end(), func);
        duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
        fout << size << "," << "SELECTION SORT," << duration << "," << counter << "\n";
        //print(v1);
        
        std::vector<int> v2{v}; counter = 0;
        start = std::clock();
        insertion_sort(v2.begin(), v2.end(), func);
        duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
        fout << size << "," << "INSERTION SORT," << duration << "," << counter << "\n";
        //print(v2);
        
        std::vector<int> v3{v}; counter = 0;
        start = std::clock();
        quicksort(v3.begin(), v3.end(), func);
        duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
        fout << size << "," << "QUICKSORT," << duration << "," << counter << "\n";
        //print(v3);
        
        std::vector<int> v4{v}; counter = 0;
        start = std::clock();
        merge_sort(v4.begin(), v4.end(), func);
        duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
        fout << size << "," << "MERGE SORT," << duration << "," << counter << "\n";
        //print(v4);
        
        std::vector<int> v5{v}; counter = 0;
        start = std::clock();
        heap_sort(v5.begin(), v5.end(), func);
        duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
        fout << size << "," << "HEAP SORT," << duration << "," << counter << "\n";
        //print(v5);
        
        std::vector<int> v6{v}; counter = 0;
        start = std::clock();
        std::sort(v6.begin(), v6.end(), func);
        duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
        fout << size << "," << "STL SORT," << duration << "," << counter << "\n";
        //print(v6);
        
        std::vector<int> v7{v}; counter = 0;
        start = std::clock();
        std::stable_sort(v7.begin(), v7.end(), func);
        duration = (std::clock() - start) / (double) CLOCKS_PER_SEC;
        fout << size << "," << "STABLE SORT," << duration << "," << counter << "\n";
        //print(v7);
        
    }
    fout.close();

    return 0;
}
