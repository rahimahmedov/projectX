//
// Created by Rahim Ahmedov on 12.02.23.
//
#include <thread>
#include <iostream>
#include <random>

void print(int mintime, int maxtime)
{

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<> dist(mintime, maxtime);
    int sleep_time = dist(gen);
    std::cout <<sleep_time << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
    std::cout << "Thread id: " << std::this_thread::get_id() << std::endl;
}

int main()
{
    auto t1 = std::thread{ []()->void{print(1000, 10000);}};
    t1.join();
    std::cout << "Thread id: " << std::this_thread::get_id() << std::endl;
    return 0;
}