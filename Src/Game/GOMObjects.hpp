#pragma once

#include "GOMEntry.hpp"
#include <cstdint>
#include <list>

#include <Network/Packet.h>

namespace Game
{
	struct GOMState
	{
		/**
		 * @brief Constructor.
		 */
		GOMState();
		/**
		 * @brief Constructor.
		 * @param id The id of the GOM Entry in the GOM Server.
		 * @param state The state of the GOM Entry in the GOM Server.
		 * @param gomEntry The GOM Entry.
		 */
		GOMState(int32_t id, int32_t state, IGOMEntry* gomEntry);

		int32_t id, state;
		IGOMEntry* gomEntry;
		bool full;

		friend Framework::Network::Packet& operator<<(Framework::Network::Packet& pPacket, const GOMState& state);
	};

	struct GOMStateRaw
	{
		int32_t id, state;
		std::string data;

		friend Framework::Network::Packet& operator>>(Framework::Network::Packet& pPacket, GOMStateRaw& state);
	};

	struct GOMVisitor
	{
		/**
		 * @brief Visits a GOM Server.
		 * @param id The id of the GOM Entry in the GOM Server.
		 * @param state The state of the GOM Entry in the GOM Server.
		 * @param gomEntry The GOM Entry.
		 * @return
		 */
		void operator()(int32_t type, int32_t id, int32_t state, IGOMEntry* gomEntry);
		void operator()(int32_t type, int32_t id);

		template <class Op>
		void apply(Op& op)
		{
			for(auto itor = gomEntries.begin(), end = gomEntries.end(); itor != end; ++itor)
				std::for_each(itor->second.begin(), itor->second.end(), op);
		}

		std::map<int32_t, std::list<GOMState> > gomEntries;
		std::map<int32_t, std::list<uint32_t> > gomDeleted;
	};
}