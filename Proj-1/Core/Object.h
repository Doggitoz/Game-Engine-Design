#include <string>

class Object {
    public:
        Object* parent;
        std::string name;
        std::vector<Object*> children;
};