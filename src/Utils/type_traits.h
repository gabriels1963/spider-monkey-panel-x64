#pragma once

namespace smp
{
	template <class... Ts>
	inline constexpr bool always_false_v = false;
}
