template<class Type>
struct Array
{
    explicit Array(size_t size = 0);
    Array(Array const & a);
    Array & operator=(Array const & a);
    ~Array();

    size_t size() const;
    Type & operator [] (size_t i);
    Type const & operator [] (size_t i) const;

    // move constructor
    Array(Array && a) : size_(a.size_), data_(a.data_)
    {
        a.data_ = nullptr;
        a.size_ = 0;
    }

    // move assignment operator
    Array & operator = (Array && a)
    {
        if (this != &a)
        {
            this->~Array();
            data_ = a.data_;
            size_ = a.size_;

            a.data_ = nullptr;
            a.size_ = 0;
        }

        return *this;
    }

private:    
    size_t size_;
    Type * data_;    
};