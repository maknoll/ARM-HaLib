#pragma once

#include <stdint.h>
#include <stddef.h>

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

    static T content;

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
      return static_cast<singleton&>(content);
		}
};

template<typename T>
T singleton<T>::content;
