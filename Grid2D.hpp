// Two dimensional grid class

#include <vector>
#include <cassert>
#include <iostream>
#include <limits>

template<class T>
class Grid2D
{
    public:
        // This is the default constructor. Call it without any 
        // arguments and it will return a 0x0 matrix (initialized
        // with 0)
        // Example 
        //      Grid2D<double> g;
        Grid2D() 
            : rows(0)
            , cols(0)
            , data(std::vector<T>(0))
            , blockSize(0)
            {}
        
        // This is the normal constructor. Gets you a rowsxcols matrix
        // with optinal default value value
        // Example
        //      Grid2D<double> square(3, 3, 5.0);
        Grid2D(const size_t rows, const size_t cols, T value=0, const size_t blockSize = 0)
            : rows(rows)
            , cols(cols)
            , data(std::vector<T>(rows*cols, value))
            , blockSize(0)
            {}
            
        const size_t getRows() const { return rows; }
        const size_t getCols() const { return cols; }
        
        const size_t getBlockSize() const { return blockSize; }
        void setBlockSize(const size_t size) {
            // assert rows and cols beeing multiple of the block size
            assert(rows % size == 0);
            assert(cols % size == 0);
            assert(size > 1 && size <= std::min(rows, cols));
            
            blockSize = size;
        }
        
        void getBlock(const size_t I, const size_t J, Grid2D<T>& block) {
            // assert a useful block size
            assert(blockSize > 1);
            assert(blockSize <= std::min(rows, cols));
            assert(rows % blockSize == 0 && cols % blockSize == 0);
            
            // assert i/j within bounds
            assert(I < rows/blockSize && J < cols/blockSize);
            
            // assert block beeing of size blockSize x blockSize
            assert(block.getCols() == blockSize && block.getRows() == blockSize);
            
            size_t k = 0;
            for(size_t i = 0; i < blockSize; ++i) {
                for(size_t j = 0; j < blockSize; ++j) {
                    block.data[k++] = data[(I*blockSize+i)*cols + J*blockSize+j];
                }
            }
            assert(k == blockSize * blockSize);
        }
        
        void setBlock(const size_t I, const size_t J, const Grid2D<T>& block) {
            // assert a useful blockSize factor
            assert(blockSize > 1);
            assert(blockSize <= std::min(rows, cols));
            assert(rows % blockSize == 0 && cols % blockSize == 0);
            
            // assert i/j within bounds
            assert(I < rows/blockSize && J < cols/blockSize);
            
            // assert block beeing of size blockSize x blockSize
            assert(block.getCols() == blockSize && block.getRows() == blockSize);
            
            size_t k = 0;
            for(size_t i = 0; i < blockSize; ++i) {
                for(size_t j = 0; j < blockSize; ++j) {
                    data[(I*blockSize+i)*cols + J*blockSize+j] = block.data[k++];
                }
            }
        }
        
        // This is the copy constructor. 
        // Example
        //      Grid2D<int> g(3, 3, 0);
        //      Grid2D<int> copy(g);
        Grid2D(const Grid2D<T>& g)
            : rows(g.rows)
            , cols(g.cols)
            , data(g.data)
            , blockSize(g.blockSize)
            {}
        
        // This is the assignment operator
        // Example
        //      Grid2D<double> g(3, 4, 5.0);
        //      Grid2D<int>    g2;
        //      g2 = g;
        Grid2D& operator=(Grid2D<T> g) {
            using std::swap;
            swap(*this, g);
            return *this;
        }
        
        // This is for writing to location (i,j)
        T& operator()(const size_t i, const size_t j) {
            assert(i < rows);
            assert(j < cols);
            return data[i*cols + j];
        }
        
        // This is for reading from location (i,j)
        const T& operator()(const size_t i, const size_t j) const {
            assert(i < rows);
            assert(j < cols);
            return data[i*cols + j];
        }
        
        template<class U>
        friend void swap(Grid2D<U>& left, Grid2D<U>& right);
        
    private:
        size_t rows;
        size_t cols;
        std::vector<T> data;
        size_t blockSize;
};

template<class T>
std::ostream& operator<<(std::ostream& out, const Grid2D<T>& g)
{
    if(g.getBlockSize() > 1) {
        out << "Block size: " << g.getBlockSize() << "\n";
    }
    
    for(size_t i = 0; i < g.getRows(); ++i) {
        if(g.getBlockSize() > 1 && i > 0 && i % g.getBlockSize() == 0) {
            for(size_t k = 0; k < g.getCols() + g.getCols() / g.getBlockSize() - 1; ++k) {
                out << "-\t";
            }
            out << "\n";
        }
            
        for(size_t j = 0; j < g.getCols(); ++j) {
            if(g.getBlockSize() > 1 && j > 0 && j % g.getBlockSize() == 0) {
                out << "|\t";
            }
            out << ((g(i, j) == std::numeric_limits<T>::max()) ? 12345 : g(i,j)) << "\t";
        }
        out << "\n";
    }
    return out;
}

template<class T>
void swap(Grid2D<T>& left, Grid2D<T>& right) {
    std::swap(left.rows, right.rows);
    std::swap(left.cols, right.cols);
    std::swap(left.data, right.data);
    std::swap(left.blockSize, right.blockSize);
}
