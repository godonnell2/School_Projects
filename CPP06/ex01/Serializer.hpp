#ifndef SERIALIZER_H
# define SERIALIZER_H

# include <iostream>
# include <stdint.h>

typedef struct Data {
    std::string name;
    int         num;
} Data;

class Serializer {

    private:
        Serializer();
        ~Serializer();
        Serializer(const Serializer &copy);
        Serializer &operator=(const Serializer &other);

    public:
        static uintptr_t serialize(Data* ptr);
        static Data* deserialize(uintptr_t raw);
};

#endif