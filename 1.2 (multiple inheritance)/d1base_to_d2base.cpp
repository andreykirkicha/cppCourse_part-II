struct Base { }; 

struct D1 : Base { };
struct D2 : Base { }; 
struct D3 : D1, D2 { };

// ============================================================================================

// "base" points to instance of "Base" corresponding to "D1"

// Function "D1BaseToD2Base" returns pointer to instance
// of "Base" corresponding to "D2"
Base const *D1BaseToD2Base(Base const *base)
{
    return (D2 *)((D3 *)((D1 *)base));
}