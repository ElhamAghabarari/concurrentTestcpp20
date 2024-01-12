// cpp20_test.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <thread>
#include <array>
#include<format>
#include <semaphore>

int main()
{
    std::array<int, 30000> list_num{0};
    std::binary_semaphore sph_w{1};
    std::binary_semaphore sph_r{0};

    auto fillArray{
        [&](int index) {
            sph_w.acquire();

            for (int i = index;i < index + 10000;i++) {
                list_num.at(i) = i+1;
            }

            if (index == 20000) {
                sph_r.release();
            }
            else {
                sph_w.release();
            }
        }
    };

    auto readArray{
        [&](int index) {

            sph_r.acquire();

            for (int i = 0;i < 30000;i++) {
                std::cout << std::format("index{}={}\n",i, list_num[i]);
            }
        }
    };

    //std::cout << "Hello World!\n";
    std::jthread(fillArray, 0);
    std::jthread(fillArray, 10000);
    std::jthread(fillArray, 20000);
    std::jthread(readArray,0);
    

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
