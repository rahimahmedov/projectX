//
// Created by Rahim Ahmedov on 17.09.23.
//

#include "btree_test.h"
#include <random>
#include <ctime>

int main()  {

    std::mt19937 random_gen(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<int>  distribution(1, 1000);

    auto bts = new BTreeString<5>();

    for(int i=1; i < 950; i++) {
        auto k = distribution(random_gen);
        auto v = std::to_string(k);
        //std::cout << "inserting " << k << ":" << v << "...\n";
        bts->insert(k, v);
        //bts->print();
        //std::cout << "------------------------\n";
    }

    bts->print();

    delete bts;

//    auto k = 14; //distribution(random_gen);
//    auto v = std::to_string(k);
//    std::cout << "inserting " << k << ":" << v << "...\n";
//    bts->insert(k, v);
//    bts->print();
//    std::cout << "------------------------\n";

//    int k = 17; std::string v = "17";
//    bts->insert(k, v);
//    bts->print();
//    std::cout << "------------------------\n";

    return 0;
}