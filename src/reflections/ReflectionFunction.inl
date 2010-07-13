template<typename T> T ReflectionFunction::invoke(void* instance, const std::vector<boost::any>& params) {
    return boost::any_cast<T>(mInvoke(instance, params));
}