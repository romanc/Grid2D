// Two dimensional grid class

#include <vector>
#include <cassert>
#include <iostream>

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
            , blocking(0)
            {}
        
        // This is the normal constructor. Gets you a rowsxcols matrix
        // with optinal default value value
        // Example
        //      Grid2D<double> square(3, 3, 5.0);
        Grid2D(const size_t rows, const size_t cols, T value=0, const size_t blocking = 0)
            : rows(rows)
            , cols(cols)
            , data(std::vector<T>(rows*cols, value))
            , blocking(0)
            {}
            
        const size_t getRows() const { return rows; }
        const size_t getCols() const { return cols; }
        
        const size_t getBlockingFactor() const { return blocking; }
        void setBlockingFactor(const size_t factor) {
            // assert rows and cols beeing multiple of the blocking factor
            assert(rows % factor == 0);
            assert(cols % factor == 0);
            assert(factor > 1 && factor <= std::min(rows, cols));
            
            blocking = factor;
        }
        
        void getBlock(const size_t I, const size_t J, Grid2D<T>& block) {
            // assert a useful blocking factor
            assert(blocking > 1);
            assert(blocking <= std::min(rows, cols));
            assert(rows % blocking == 0 && cols % blocking == 0);
            
            // assert i/j within bounds
            assert(I < rows/blocking && J < cols/blocking);
            
            // assert block beeing of size blocking x blocking
            assert(block.getCols() == blocking && block.getRows() == blocking);
            
            size_t k = 0;
            for(size_t i = 0; i < blocking; ++i) {
                for(size_t j = 0; j < blocking; ++j) {
                    block.data[k++] = data[(I*blocking+i)*cols + J*blocking+j];
                }
            }
            assert(k == blocking * blocking);
        }
        
        void setBlock(const size_t I, const size_t J, const Grid2D<T>& block) {
            // assert a useful blocking factor
            assert(blocking > 1);
            assert(blocking <= std::min(rows, cols));
            assert(rows % blocking == 0 && cols % blocking == 0);
            
            // assert i/j within bounds
            assert(I < rows/blocking && J < cols/blocking);
            
            // assert block beeing of size blocking x blocking
            assert(block.getCols() == blocking && block.getRows() == blocking);
            
            size_t k = 0;
            for(size_t i = 0; i < blocking; ++i) {
                for(size_t j = 0; j < blocking; ++j) {
                    data[(I*blocking+i)*cols + J*blocking+j] = block.data[k++];
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
            , blocking(g.blocking)
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
        size_t blocking;
};

template<class T>
std::ostream& operator<<(std::ostream& out, const Grid2D<T>& g)
{
    if(g.getBlockingFactor() > 1) {
        out << "Blocking factor: " << g.getBlockingFactor() << "\n";
    }
    
    for(size_t i = 0; i < g.getRows(); ++i) {
        if(g.getBlockingFactor() > 1 && i > 0 && i % g.getBlockingFactor() == 0) {
            for(size_t k = 0; k < g.getCols() + g.getCols() / g.getBlockingFactor() - 1; ++k) {
                out << "-\t";
            }
            out << "\n";
        }
            
        for(size_t j = 0; j < g.getCols(); ++j) {
            if(g.getBlockingFactor() > 1 && j > 0 && j % g.getBlockingFactor() == 0) {
                out << "|\t";
            }
            out << g(i, j) << "\t";
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
    std::swap(left.blocking, right.blocking);
}
