#include "IObject.h"

template<typename T> T* BeanFactory::getBean(const std::string& id) {
    return dynamic_cast<T*>(getBean(id));
}
