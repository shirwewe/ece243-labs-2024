int main()
{
    volatile int *LEDR_ptr = 0xFF200000;
    volatile int *SW_ptr = 0xFF200040;
    int value;

    while (1){
        value = *SW_ptr;
        *LEDR_ptr = value;
    }
}

