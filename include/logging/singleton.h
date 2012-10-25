#pragma once

#include <stdint.h>
#include <stddef.h>

void* operator new(size_t, void* ptr)
{
    return ptr;
}

/**\brief A general implementation of the singleton concept
 * \tparam T the type to declare singleton
 *
 * This template class allows one to declare another class singleton. This
 * class cannot be constructed afterwards, but must be referenced by a call to
 * getInstance(). The concept allows to create single objects of classes, that
 * exist exactly once.
 **/
template<typename T>
class singleton : public T
{
	private:
		/**\brief no constructor**/
		singleton(){};
		/**\brief no copy constructor**/
		singleton(const singleton&);
	public:

		/**\brief Return an instance of this singleton class
		 * \return an instance of the class T
		 *
		 * This function will construct the object of the class T the first
		 * time it is called. Afterwards it will always return this single
		 * instance.
		 **/
		static singleton& instance()
		{
            static uint8_t instance[sizeof(T)];
            static bool constructed=false;
            if(!constructed)
            {
                new(instance) T();
                constructed=true;
            }
			return *reinterpret_cast<singleton*>(instance);
		}
};
