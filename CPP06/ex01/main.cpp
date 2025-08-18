#include "Serializer.hpp"

int main() {
    Data data;
    data.name = "string";
    data.num = 42;

    std::cout << "Original Data!" << std::endl;
    std::cout << "Name: " << data.name << std::endl;
    std::cout << "Num: " << data.num << std::endl;
    std::cout << std::endl;

    uintptr_t raw = Serializer::serialize(&data);

    std::cout << "Serialized Data!" << std::endl;
    std::cout << "Raw uintptr_t: " << raw << std::endl;
    std::cout << std::endl;

    Data* deserializedData = Serializer::deserialize(raw);

    std::cout << "Deserialized Data!" << std::endl;
    std::cout << "Name: " << deserializedData->name << std::endl;
    std::cout << "Num: " << deserializedData->num << std::endl;

    return 0;
}
