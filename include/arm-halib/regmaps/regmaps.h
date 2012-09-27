#pragma once

//#include <boost/type_traits/is_base_of.hpp>
#include "base/localRegMap.h"

namespace arm_halib
{
namespace regmaps
{
namespace base
{
namespace helpers
{
	/**\brief Unificatates distributed and non-distributed RegMaps
	 * \tparam distributed tells if RegMap is distributed or not
	 * \tparam RegMap the RegMap itself
	 *
	 * This class select different instantiation schemes dependant on the type
	 * of RegMap
	 **/
	template<bool distributed, typename RegMap>
	struct RegMapUnificationHelper;

	/**\brief Specialisation for local RegMap
	 * \tparam RegMap the local RegMap
	 *
	 * This class overlays the memory with the local RegMap.
	 **/
	template<typename RegMap>
	struct RegMapUnificationHelper<false, RegMap>
	{
		/**\brief create an instance of the RegMap
		 * \return an instance of the RegMap
		 **/
		RegMap& create() __attribute__((always_inline))
		{
			return *((RegMap*)0);
			//return *new(0) RegMap();	massive overhead
		}
	};

	/**\brief Specialisation for distributed RegMaps
	 * \tparam RegMap the distributed RegMap
	 *
	 * This class creates an Instance of the distributed RegMap and returns it
	 * via the create call.
	 **/
	template<typename RegMap>
	struct RegMapUnificationHelper<true, RegMap>
	{
		/**\brief the instance of the RegMap**/
		RegMap instance;

		/**\brief Return an instance of the RegMap
		 * \return an instance of the RegMap
		 **/
		RegMap& create() __attribute__((always_inline))
		{
			return instance;
		}
	};
}

/**\brief Creates RegMap instances dependand on the type of RegMap
	 * \tparam RegMap the RegMap itself
	 *
	 * This class automatically selects different instantiation schemes
	 * dependant on the type of the RegMap, afterwards the RegMap is created,
	 * by a call to create().
	 **/
template<typename T>
/*struct RegMapUnification : public helpers::RegMapUnificationHelper<
						   			! boost::is_base_of<
										regmaps::base::LocalRegMap, T
									>::type::value, T
								  >
{};
*/
struct RegMapUnification : public helpers::RegMapUnificationHelper<false,T>{};
}
}
}


//Create RegMap for local usage
#define UseRegMap(rm, RegMap) RegMap &rm=*(RegMap*)0

//Sync complete RegMap
#define SyncRegMap(rm) asm("":::"memory")

//Sync one Register of the complete RegMap
#define SyncRegister(rm, Register) rm.sync((Register*)0)
