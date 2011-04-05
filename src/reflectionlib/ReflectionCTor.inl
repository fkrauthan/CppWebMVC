template<typename T> T* ReflectionCTor::createInstance(const std::vector<boost::any>& params) {
    return reinterpret_cast<T*>(createInstance(params));
}
