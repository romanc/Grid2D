#include <algorithm>    // std::min
#include "Grid2D.hpp"

int main() {
    Grid2D<double> g(5, 8);

    Grid2D<int> zero(3,3,0);

    for(size_t i = 0; i < std::min(g.getRows(), g.getCols()); ++i) {
        g(i,i) = i;
    }

    std::cout << g << std::endl;

    std::cout << "3x3 Nullmatrix\n" << zero << std::endl;

    Grid2D<int> copy(zero);
    std::cout << "Copy of 3x3 Nullmatrix\n" << copy << std::endl;

    Grid2D<double> g2(3,4);
    std::cout << "g2\n" << g2 << std::endl;

    using std::swap;
    swap(g, g2);

    std::cout << "swapping first (g) and g2\n" << g << "\n" << g2 << std::endl;

    g2 = g;
    std::cout << "assignment of g to g2\n" << g << "\n" << g2 << std::endl;
    
    Grid2D<float> blocktest(8,8, 0);
    blocktest.setBlockingFactor(4);
    size_t counter = 0;
    for(size_t i = 0; i < 8; ++i) {
        for(size_t j = 0; j < 8; ++j) {
            blocktest(i,j) = counter++;
        }
    }
    
    std::cout << "Blocktest matrix\n" << blocktest << std::endl;
    
    for(size_t i = 0; i < 8/4; ++i) {
        for(size_t j = 0; j < 8/4; ++j) {
            Grid2D<float> block(4, 4);
            blocktest.getBlock(i, j, block);
            std::cout << "Block I/J = " << i << "/" << j << "\n";
            std::cout << block << std::endl;
        }
    }

    return 0;
}
