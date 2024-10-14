typedef const struct
{
    char code[4];
    void* variable;
    unsigned char clear_mask;
    unsigned char set_mask;
}OPTION;