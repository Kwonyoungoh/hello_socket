#include <iostream>


int main(int argc, char *argv[])
{
    int count;

    if(argc!= 3)
    {
        std::cout << "Usage : " << argv[0] << " <num> <num>" << std::endl;
        exit(1);
    }
    
    std::cout << "argc : " << argc << std::endl;
    std::cout << "argv[0] : " << argv[0] << std::endl;
    std::cout << "argv[1] : " << argv[1] << std::endl;
    std::cout << "argc[2] : " << argv[2] << std::endl;

    return 0;
}