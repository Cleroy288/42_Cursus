#include "easyfind.hpp"

int main() {
    try {
        // Initialisation compatible avec C++98
        int arr[] = {1, 2, 3, 4, 5};
        std::vector<int> vec(arr, arr + sizeof(arr) / sizeof(arr[0]));

        int index = easyfind(vec, 3);
        std::cout << "Element found at index: " << index << std::endl;
        
        // Test avec un élément non trouvé
        index = easyfind(vec, 6);
        std::cout << "Element found at index: " << index << std::endl;
    } catch (const NotFoundException& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
