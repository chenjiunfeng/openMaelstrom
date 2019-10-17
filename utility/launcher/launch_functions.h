#pragma once
#include <utility/launcher.h>
#include <utility/identifier.h>
#ifndef _WIN32
#define FORWARD(args) args...
#else
#define FORWARD(args) std::forward<Ts>(args)...
#endif
template <launch_config cfg,
	template <launch_config, hash_length, cell_ordering, cell_structuring, typename...>
class T,
typename... Vs, typename... Ts>
void launch_i(int32_t threads, Ts... args) {
	static auto structure = parameters::cell_structure{};
	//	static auto ordering = parameters::cell_order{};
	static auto width = parameters::hash_size{};
#ifdef LINEAR_CELL_ALGORITHM
	if (structure == cell_structuring::complete)
		T<cfg, hash_length::bit_32, cell_ordering::linear_order, cell_structuring::complete,
		Vs...>::launch(threads, FORWARD(args));
#endif
#ifdef MLM64_CELL_ALGORITHM
	if (structure == cell_structuring::MLM && width == hash_length::bit_64)
		T<cfg, hash_length::bit_64, cell_ordering::z_order, cell_structuring::MLM, Vs...>::launch(
			threads, FORWARD(args));
#endif
#ifdef HASHED64_CELL_ALGORITHM
	if (structure == cell_structuring::hashed && width == hash_length::bit_64)
		T<cfg, hash_length::bit_64, cell_ordering::z_order, cell_structuring::hashed, Vs...>::launch(
			threads, FORWARD(args));
#endif
#ifdef HASHED32_CELL_ALGORITHM
	if (structure == cell_structuring::hashed && width == hash_length::bit_32)
		T<cfg, hash_length::bit_32, cell_ordering::z_order, cell_structuring::hashed, Vs...>::launch(
			threads, args... );
#endif
#ifdef COMPACT_MLM_CELL_ALGORITHM
	if (structure == cell_structuring::compactMLM)
		T<cfg, hash_length::bit_64, cell_ordering::z_order, cell_structuring::compactMLM, Vs...>::launch(
			threads, args...);
#endif
}

template <launch_config cfg, template <launch_config, neighbor_list, typename...> class T,
	typename... Vs, typename... Ts>
	void launch_i(int32_t threads, Ts... args) {
	static auto neighborhood = parameters::neighborhood_kind{};
#ifdef BASIC_NEIGHBORLIST_COMPILED
	if (neighborhood == neighbor_list::basic)
		T<cfg, neighbor_list::constrained, Vs...>::launch(threads, FORWARD(args));
#endif
#ifdef CONSTRAINED_NEIGHBORLIST_COMPILED
	if (neighborhood == neighbor_list::constrained)
		T<cfg, neighbor_list::constrained, Vs...>::launch(threads, FORWARD(args));
#endif
#ifdef CELLBASED_NEIGHBORLIST_COMPILED
	if (neighborhood == neighbor_list::cell_based)
		T<cfg, neighbor_list::cell_based, Vs...>::launch(threads, FORWARD(args));
#endif
#ifdef COMPACTCELL_NEIGHBORLIST_COMPILED
	if (neighborhood == neighbor_list::compactCell)
		T<cfg, neighbor_list::compactCell, Vs...>::launch(threads, FORWARD(args));
#endif
#ifdef COMPACTMLM_NEIGHBORLIST_COMPILED
	if (neighborhood == neighbor_list::compactMLM)
		T<cfg, neighbor_list::compactMLM, Vs...>::launch(threads, FORWARD(args));
#endif
#ifdef MASKED_NEIGHBORLIST_COMPILED
	if (neighborhood == neighbor_list::masked)
		T<cfg, neighbor_list::masked, Vs...>::launch(threads, FORWARD(args));
#endif
}

template <launch_config cfg, template <launch_config, typename...> class T, typename... Vs,
	typename... Ts>
	void launch_i(int32_t threads, Ts... args) {
	T<cfg, Vs...>::launch(threads, FORWARD(args));
}

template <template <launch_config, hash_length, cell_ordering, cell_structuring, typename...>
typename T,
typename... Vs, typename... Ts>
void launch(int32_t threads, Ts... args) {
	launch_i<launch_config::_used_for_template_specializations, T, Vs...>(threads,
		FORWARD(args));
}
template <template <launch_config, neighbor_list, typename...> class T, typename... Vs,
	typename... Ts>
	void launch(int32_t threads, Ts... args) {
	launch_i<launch_config::_used_for_template_specializations, T, Vs...>(threads,
		FORWARD(args));
}
template <template <launch_config, typename...> class T, typename... Vs, typename... Ts>
void launch(int32_t threads, Ts&&... args) {
	launch_i<launch_config::_used_for_template_specializations, T, Vs...>(threads,
		FORWARD(args));
}

template <template <launch_config, hash_length, cell_ordering, cell_structuring, typename...>
class T,
typename... Vs, typename... Ts>
void launchDevice(int32_t threads, Ts&&... args) {
	launch_i<launch_config::device, T, Vs...>(threads, FORWARD(args));
}
template <template <launch_config, neighbor_list, typename...> class T, typename... Vs,
	typename... Ts>
	void launchDevice(int32_t threads,Ts &&... args) {
	launch_i<launch_config::device, T, Vs...>(threads, FORWARD(args));
}
template <template <launch_config, typename...> class T, typename... Vs, typename... Ts>
void launchDevice(int32_t threads, Ts&&... args) {
	launch_i<launch_config::device, T, Vs...>(threads, FORWARD(args));
}

template <template <launch_config, hash_length, cell_ordering, cell_structuring, typename...>
class T,
typename... Vs, typename... Ts>
void launchHost(int32_t threads, Ts&&... args) {
	launch_i<launch_config::host, T, Vs...>(threads, FORWARD(args));
}
template <template <launch_config, neighbor_list, typename...> class T, typename... Vs,
	typename... Ts>
	void launchHost(int32_t threads, Ts&&... args) {
	launch_i<launch_config::host, T, Vs...>(threads, FORWARD(args));
}
template <template <launch_config, typename...> class T, typename... Vs, typename... Ts>
void launchHost(int32_t threads, Ts&&... args) {
	launch_i<launch_config::host, T, Vs...>(threads, FORWARD(args));
}
template <launch_config cfg,
	template <launch_config, hash_length, cell_ordering, cell_structuring, typename...>
class T,
	typename... Vs, typename... Ts>
	void launch_i(int2 threads, Ts... args) {
	static auto structure = parameters::cell_structure{};
	//	static auto ordering = parameters::cell_order{};
	static auto width = parameters::hash_size{};
#ifdef LINEAR_CELL_ALGORITHM
	if (structure == cell_structuring::complete)
		T<cfg, hash_length::bit_32, cell_ordering::linear_order, cell_structuring::complete,
		Vs...>::launch(threads, FORWARD(args));
#endif
#ifdef MLM64_CELL_ALGORITHM
	if (structure == cell_structuring::MLM && width == hash_length::bit_64)
		T<cfg, hash_length::bit_64, cell_ordering::z_order, cell_structuring::MLM, Vs...>::launch(
			threads, FORWARD(args));
#endif
#ifdef HASHED64_CELL_ALGORITHM
	if (structure == cell_structuring::hashed && width == hash_length::bit_64)
		T<cfg, hash_length::bit_64, cell_ordering::z_order, cell_structuring::hashed, Vs...>::launch(
			threads, FORWARD(args));
#endif
#ifdef HASHED32_CELL_ALGORITHM
	if (structure == cell_structuring::hashed && width == hash_length::bit_32)
		T<cfg, hash_length::bit_32, cell_ordering::z_order, cell_structuring::hashed, Vs...>::launch(
			threads, args...);
#endif
#ifdef COMPACT_MLM_CELL_ALGORITHM
	if (structure == cell_structuring::compactMLM)
		T<cfg, hash_length::bit_64, cell_ordering::z_order, cell_structuring::compactMLM, Vs...>::launch(
			threads, args...);
#endif
}

template <launch_config cfg, template <launch_config, neighbor_list, typename...> class T,
	typename... Vs, typename... Ts>
	void launch_i(int2 threads, Ts... args) {
	static auto neighborhood = parameters::neighborhood_kind{};
#ifdef BASIC_NEIGHBORLIST_COMPILED
	if (neighborhood == neighbor_list::basic)
		T<cfg, neighbor_list::constrained, Vs...>::launch(threads, FORWARD(args));
#endif
#ifdef CONSTRAINED_NEIGHBORLIST_COMPILED
	if (neighborhood == neighbor_list::constrained)
		T<cfg, neighbor_list::constrained, Vs...>::launch(threads, FORWARD(args));
#endif
#ifdef CELLBASED_NEIGHBORLIST_COMPILED
	if (neighborhood == neighbor_list::cell_based)
		T<cfg, neighbor_list::cell_based, Vs...>::launch(threads, FORWARD(args));
#endif
#ifdef COMPACTCELL_NEIGHBORLIST_COMPILED
	if (neighborhood == neighbor_list::compactCell)
		T<cfg, neighbor_list::compactCell, Vs...>::launch(threads, FORWARD(args));
#endif
#ifdef COMPACTMLM_NEIGHBORLIST_COMPILED
	if (neighborhood == neighbor_list::compactMLM)
		T<cfg, neighbor_list::compactMLM, Vs...>::launch(threads, FORWARD(args));
#endif
#ifdef MASKED_NEIGHBORLIST_COMPILED
	if (neighborhood == neighbor_list::masked)
		T<cfg, neighbor_list::masked, Vs...>::launch(threads, FORWARD(args));
#endif
}

template <launch_config cfg, template <launch_config, typename...> class T, typename... Vs,
	typename... Ts>
	void launch_i(int2 threads, Ts... args) {
	T<cfg, Vs...>::launch(threads, FORWARD(args));
}

template <template <launch_config, hash_length, cell_ordering, cell_structuring, typename...>
typename T,
typename... Vs, typename... Ts>
void launch(int2 threads, Ts... args) {
	launch_i<launch_config::_used_for_template_specializations, T, Vs...>(threads,
		FORWARD(args));
}
template <template <launch_config, neighbor_list, typename...> class T, typename... Vs,
	typename... Ts>
	void launch(int2 threads, Ts... args) {
	launch_i<launch_config::_used_for_template_specializations, T, Vs...>(threads,
		FORWARD(args));
}
template <template <launch_config, typename...> class T, typename... Vs, typename... Ts>
void launch(int2 threads, Ts&&... args) {
	launch_i<launch_config::_used_for_template_specializations, T, Vs...>(threads,
		FORWARD(args));
}

template <template <launch_config, hash_length, cell_ordering, cell_structuring, typename...>
class T,
	typename... Vs, typename... Ts>
	void launchDevice(int2 threads, Ts&&... args) {
	launch_i<launch_config::device, T, Vs...>(threads, FORWARD(args));
}
template <template <launch_config, neighbor_list, typename...> class T, typename... Vs,
	typename... Ts>
	void launchDevice(int2 threads, Ts &&... args) {
	launch_i<launch_config::device, T, Vs...>(threads, FORWARD(args));
}
template <template <launch_config, typename...> class T, typename... Vs, typename... Ts>
void launchDevice(int2 threads, Ts&&... args) {
	launch_i<launch_config::device, T, Vs...>(threads, FORWARD(args));
}

template <template <launch_config, hash_length, cell_ordering, cell_structuring, typename...>
class T,
	typename... Vs, typename... Ts>
	void launchHost(int2 threads, Ts&&... args) {
	launch_i<launch_config::host, T, Vs...>(threads, FORWARD(args));
}
template <template <launch_config, neighbor_list, typename...> class T, typename... Vs,
	typename... Ts>
	void launchHost(int2 threads, Ts&&... args) {
	launch_i<launch_config::host, T, Vs...>(threads, FORWARD(args));
}
template <template <launch_config, typename...> class T, typename... Vs, typename... Ts>
void launchHost(int2 threads, Ts&&... args) {
	launch_i<launch_config::host, T, Vs...>(threads, FORWARD(args));
}
