
template <typename T> ReflectionClass* Reflection::getClass() {
	return getClass(typeid(T).name());
}