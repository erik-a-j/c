

#define FLAGGA1  0
#define FLAGGA2  (1 << 0)
#define FLAGGA3  (1 << 1)
#define FLAGGA4  (1 << 2)
#define FLAGGA10 (1 << 23)

int main(void)
{
    //&|^~
    int a = 0;
    a = a | FLAGGA3;
    a = a & ~FLAGGA3;
    if (a & FLAGGA3)
    {
        return 0;
    }
}
