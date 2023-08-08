// "Type" is a complex polymorphic class that uses multiple inheritance

// Returns 'true' if "p" and "q" both point to the same object
template<class Type>
bool isSameObject(Type const *p, Type const *q)
{
    // For some object dynamic_cast<void *> returns addres of
    // its first byte
    void const *p_void = dynamic_cast<void const *>(p);
    void const *q_void = dynamic_cast<void const *>(q);

    return (p_void == q_void);
}