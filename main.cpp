#include <vector>
#include <algorithm>
#include <cstdlib> // for std::rand()
#include <ctime>
#include <iostream>
#include <functional>
#include <map>

#include "timer.h"
//#define DEBUG

std::vector<unsigned> generate_vector(int how_many, unsigned max)
{
    std::vector<unsigned> numbers(how_many);

    std::srand(std::time(NULL));

    std::generate(numbers.begin(), numbers.end(), 
        [&how_many, &max] { 

            return std::rand() % max + 1; 

        });

    return numbers;
}


int binary_search(const std::vector<unsigned>& nrs, unsigned lookup_val, int begin, int end)
{
    while(begin <= end)
    {
        int mid = (begin + end) / 2;

#ifdef DEBUG
        std::cout << "nrs[mid]: " << nrs[mid] << "\t";
        std::cout << "Begin: " << begin << " Mid: " << mid << " End: " <<  end << std::endl;
#endif

        if(lookup_val < nrs[mid])
            end = mid - 1;

        else if(lookup_val > nrs[mid])
            begin = mid + 1;
        else // either we found lookup, 
             // or we found position where
             // it should be
            return mid;
    }
}

void insertion_sort(std::vector<unsigned>& nrs)
{
    for(int j = 0; j < nrs.size(); ++j)
    {
        unsigned key = nrs[j];
        int i = j-1;

        while(i >= 0 && nrs[i] > key)
        {
            nrs[i+1] = nrs[i];
            --i;
        }

        nrs[i+1] = key;
    }
}

void binary_search_insertion_sort(std::vector<unsigned>& nrs)
{
    for(int j = 0; j < nrs.size(); ++j)
    {
        unsigned key = nrs[j];

        int ins_pos = binary_search(nrs, key, 0, j);
#ifdef DEBUG
        std::cout << "Position to insert key " << key << " : " << ins_pos << std::endl;
#endif

        int i = j;

        while(i >= ins_pos)
        {
            nrs[i] = nrs[i-1];
            --i;
        }

        nrs[ins_pos] = key;
    }
}

void std_q_sort(std::vector<unsigned>& nrs)
{
    std::sort(nrs.begin(), nrs.end());
}


bool is_sorted(const std::vector<unsigned>& nrs)
{
    for(int i = 0; i < nrs.size()-1; ++i)
        if(nrs[i] > nrs[i+1])
            return false;

    return true;
}

template <typename type>
void print_vector(const std::vector<type>& vec)
{
    for(const type& i : vec)
        std::cout << i << " ";

    std::cout << std::endl << std::endl;

}


using string_function_map_t = std::map<std::string, std::function< void(std::vector<unsigned>&) >>;

void sorting_test(string_function_map_t sorting_fn_map, 
                    int vector_size, unsigned max_value)
{
    // this is terrible, I should get a function object of 'generate' bound to some args
    auto original_vec = generate_vector(vector_size, max_value);

    std::cout << "Sorting vector with " << vector_size << " elements" << std::endl;

    for(auto& pair: sorting_fn_map)
    {
        auto test_vec = original_vec;
        auto function = pair.second;

        std::cout << "Sorting by " << pair.first << std::endl;

        Timer timer; timer.start();
        function(test_vec);

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(timer.getNanosecondsElapsed());
        std::cout << pair.first << " took " << duration.count() << 
                " milliseconds" << std::endl << std::endl;
    }

}



int main()
{
    const unsigned how_many = 50000;
    const unsigned max = 100000;

    string_function_map_t algo_map;

    algo_map["insertion_sort"] = insertion_sort;
    algo_map["binary_search_insertion_sort"] = binary_search_insertion_sort;
    algo_map["std::sort"] = std_q_sort;

    sorting_test(algo_map, how_many, max);

    return 0;
}
