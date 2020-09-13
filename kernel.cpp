int lineNumber = 0;

void printf(char* str)
{
    static unsigned short* VideoMemory = (unsigned short*)0xb8000;

    for(int i = 0; str[i] != '\0'; ++i)
        VideoMemory[i+lineNumber*80] = (VideoMemory[i+lineNumber*80] & 0xFF00) | str[i];
    lineNumber += 1;
}

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

extern "C" void kernelMain(const void* multiboot_structure, unsigned int /*multiboot_magic*/)
{
    printf("Booted into OS");
    printf("Created 2020");
    printf("> ");
    while(1);
}
