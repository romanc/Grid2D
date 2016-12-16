#include <algorithm>    // std::min
#include "Grid2D.hpp"

int main() {
    
    utils::Grid2D<double, utils::row_major> g(5, 8);

    utils::Grid2D<int, utils::row_major> zero(3,3,0);

    for(size_t i = 0; i < std::min(g.getRows(), g.getCols()); ++i) {
        g(i,i) = i;
    }

    std::cout << g << std::endl;

    std::cout << "3x3 Nullmatrix\n" << zero << std::endl;

    utils::Grid2D<int, utils::row_major> copy(zero);
    std::cout << "Copy of 3x3 Nullmatrix\n" << copy << std::endl;

    utils::Grid2D<double, utils::row_major> g2(3,4);
    std::cout << "g2\n" << g2 << std::endl;

    using std::swap;
    swap(g, g2);

    std::cout << "swapping first (g) and g2\n" << g << "\n" << g2 << std::endl;

    g2 = g;
    std::cout << "assignment of g to g2\n" << g << "\n" << g2 << std::endl;
    
    utils::Grid2D<float, utils::row_major> blocktest(8,8, 0);
    blocktest.setBlockSize(4);
    size_t counter = 0;
    for(size_t i = 0; i < 8; ++i) {
        for(size_t j = 0; j < 8; ++j) {
            blocktest(i,j) = counter++;
        }
    }
    
    std::cout << "Blocktest matrix\n" << blocktest << std::endl;
    utils::Grid2D<float, utils::row_major> block(4, 4);
    
    for(size_t i = 0; i < 8/4; ++i) {
        for(size_t j = 0; j < 8/4; ++j) {
            blocktest.getBlock(i, j, block);
            std::cout << "Block I/J = " << i << "/" << j << "\n";
            std::cout << block << std::endl;
            
            if(i == 0) {
                for(size_t ii = 0; ii < 4; ++ii) {
                    for(size_t jj = 0; jj < 4; ++jj) {
                        block(ii,jj) *= 2;
                    }
                }
                blocktest.setBlock(i, j, block);
            }
        }
    }
    
    std::cout << "Blocktest matrix\n" << blocktest << std::endl;

    return 0;
}
