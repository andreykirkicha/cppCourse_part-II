#include <vector>
#include <list>
#include <iterator>
#include <iostream>

// ====================================================================================================================

template<typename Type>
class VectorList
{
private:
    using Vect = std::vector<Type>;
    using List = std::list<Vect>;

public:
    using value_type = Type const;
    using VectIterator = typename Vect::const_iterator;
    using ListIterator = typename List::const_iterator;
// 
    VectorList()                    = default;
    VectorList(VectorList const &)  = default;
    VectorList(VectorList &&)       = default;
// 
    VectorList & operator=(VectorList &&)       = default;
    VectorList & operator=(VectorList const &)  = default;
// 
    // Method which fills VectorList (ALREADY MADE)
    // Warranted that there's no empty arrays in the list
    template<typename Iterator>
    void append(Iterator begin, Iterator end)
    {
        if (begin != end)
            data_.push_back(Vect(begin, end));
    }
// 
    bool empty() const { return size() == 0; } 
// 
    size_t size() const 
    {
        size_t res = 0;

        for (auto list_ : data_) { for (auto vector_ : list_) ++res; }

        return res;
    }
// 
    struct const_iterator : std::iterator<std::bidirectional_iterator_tag, value_type>
    {
        const_iterator()                    = default;
        const_iterator(const_iterator &)    = default;
        const_iterator(VectIterator vect_iter, ListIterator list_iter, List * data_ptr)
            : vect_iter_(vect_iter), list_iter_(list_iter), data_ptr_(data_ptr) {}
        
        ~const_iterator() = default;

        const_iterator operator++(int value)
        {
            if (vect_iter_ + value != list_iter_->end()) { std::advance(vect_iter_, value); }
            else
            {
                size_t dist = std::distance(vect_iter_, list_iter_->end());
                list_iter_++;
                vect_iter_ = list_iter_->begin();

                int rest = value - dist;
                vect_iter_ += rest;
            }
        }

    private:
        VectIterator vect_iter_;
        ListIterator list_iter_;
        List * data_ptr_;
    };
// 
    // определите методы begin / end
    // const_iterator begin() const { return ... ; }
    // const_iterator end()   const { return ... ; }
// 
    // определите const_reverse_iterator
    // ... const_reverse_iterator ...
// 
    // определите методы rbegin / rend
    // const_reverse_iterator rbegin() const { return ... ;   }
    // const_reverse_iterator rend()   const { return ... ; }

private:
    List data_;
};

// ====================================================================================================================

int main()
{
    VectorList<int> vector_list;
    
    std::vector<int> vec1 = {1, 0, 0};
    std::vector<int> vec2 = {0, 1, 0};
    std::vector<int> vec3 = {0, 0, 1};

    vector_list.append(vec1.begin(), vec1.end());
    vector_list.append(vec2.begin(), vec2.end());
    vector_list.append(vec3.begin(), vec3.end());

    std::cout << "Size is " << vector_list.size() << std::endl;

    return 0;
}