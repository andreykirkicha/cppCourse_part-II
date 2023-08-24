#include <vector>
#include <list>
#include <iterator>
#include <iostream>

// ====================================================================================================================

template<typename Type>
class VectorList
{
private:
    using Vect = typename std::vector<Type>;
    using List = typename std::list<Vect>;

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
    struct const_iterator : std::iterator<typename std::bidirectional_iterator_tag, value_type>
    {
        const_iterator()                        = default;
        const_iterator(const_iterator const &)  = default;
        const_iterator(ListIterator list_iter, VectIterator vect_iter, List const * data_ptr)
            :   list_iter_(list_iter),
                vect_iter_(vect_iter),
                data_ptr_(data_ptr)
        {}
        
        ~const_iterator() = default;

        // ============================================================================================================

        const_iterator operator++(int)
        {
            auto old = const_iterator(list_iter_, vect_iter_, data_ptr_);
            
            if (std::next(vect_iter_) != list_iter_->cend()) { ++vect_iter_; }
            else if (std::next(list_iter_) != data_ptr_->cend())
            {
                ++list_iter_;
                vect_iter_ = list_iter_->cbegin();
            }
            
            return old;
        }

        const_iterator & operator++()
        {
            if (std::next(vect_iter_) != list_iter_->cend()) { ++vect_iter_; }
            else if (std::next(list_iter_) != data_ptr_->cend())
            {
                ++list_iter_;
                vect_iter_ = list_iter_->cbegin();
            }

            return *this;
        }

        const_iterator operator--(int)
        {
            auto old = const_iterator(list_iter_, vect_iter_, data_ptr_);
            
            if (vect_iter_ != list_iter_->cbegin()) { --vect_iter_; }
            else if (list_iter_ != data_ptr_->cbegin())
            {
                --list_iter_;
                vect_iter_ = std::prev(list_iter_->cend());
            }
            
            return old;
        }

        const_iterator & operator--()
        {
            if (vect_iter_ != list_iter_->cbegin()) { --vect_iter_; }
            else if (list_iter_ != data_ptr_->cbegin())
            {
                --list_iter_;
                vect_iter_ = std::prev(list_iter_->cend());
            }

            return *this;
        }

        // ============================================================================================================

        bool operator==(const_iterator const & it) const
        {
            return this->data_ptr_ == it.data_ptr_;
        }

        bool operator!=(const_iterator const & it) const
        {
            return this->data_ptr_ != it.data_ptr_;
        }

        // ============================================================================================================

        typename VectIterator::reference operator*()   const { return *vect_iter_; }
        typename VectIterator::pointer operator->()    const { return  vect_iter_; }

    private:
        ListIterator list_iter_;
        VectIterator vect_iter_;
        List const * data_ptr_;
    };
// 
    const_iterator begin() const
    { 
        if (this->empty()) return const_iterator();
        return const_iterator(data_.cbegin(), data_.cbegin()->cbegin(), &data_);
    }
    const_iterator end() const
    { 
        if (this->empty()) return const_iterator();
        return const_iterator(std::prev(data_.cend()), std::prev(data_.cend())->cend(), &data_);
    }
// 
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
// 
    const_reverse_iterator rbegin() const  { return const_reverse_iterator(this->end());   }
    const_reverse_iterator rend()   const  { return const_reverse_iterator(this->begin()); }

private:
    List data_;
};

// ====================================================================================================================

int main()
{
    VectorList<int> vector_list;
    
    std::vector<int> vec1 = {0, 1, 2};
    std::vector<int> vec2 = {3, 4, 5};
    std::vector<int> vec3 = {6, 7, 8};

    vector_list.append(vec1.begin(), vec1.end());
    vector_list.append(vec2.begin(), vec2.end());
    vector_list.append(vec3.begin(), vec3.end());

    std::cout   << "Size:\t" << vector_list.size() << std::endl;
    std::cout   << std::endl;

    auto begin  = vector_list.begin();
    auto end    = vector_list.end();

    std::cout   << "Begin:\t\t" << *begin               << std::endl;
    std::cout   << "Pre-end:\t" << *(std::prev(end))    << std::endl;
    std::cout   << std::endl;

    std::cout   << "Pre-increment:\t"
                << *begin
                << " ==> "
                << *(++begin)
                << std::endl;

    std::cout   << "Post-increment:\t"
                << *(begin++)
                << " ==> "
                << *begin
                << std::endl;
    std::cout   << std::endl;

    bool not_equal = (begin != end);

    std::cout   << "operator != :\t"
                << not_equal
                << std::endl;

    auto extra_iterator = end;
    bool equal = (extra_iterator == end);

    std::cout   << "operator == :\t"
                << equal
                << std::endl;
    std::cout   << std::endl;

    auto rbegin = vector_list.rbegin();
    auto rend    = vector_list.rend();

    std::cout   << "Rbegin:\t\t" << *rbegin             << std::endl;
    std::cout   << "Pre-rend:\t" << *(std::prev(rend))  << std::endl;
    std::cout   << std::endl;

    return 0;
}