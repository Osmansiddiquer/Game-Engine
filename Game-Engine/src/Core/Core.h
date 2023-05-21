#pragma once
//automating dll exporting and importing
#ifdef ENGINE_PLATFORM_WINDOWS //specific to windows
	#ifdef ENGINE_BUILD_DLL  //set different macros for import and exporsst
		#define ENGINE_API __declspec(dllexport)
		#define ENGINE_API_DECLARE
	#else
		#define ENGINE_API __declspec(dllimport)
		#define ENGINE_API_DECLARE __declspec(dllexport)
#define
	#endif
#else
	#error Engine only supports windows at the moment
#endif

//Assertions

#ifdef ENGINE_DEBUG
#define ASSERT(expr, description) \
if (expr) { } \
else \
{ \
	ENGINE_CORE_ERROR("Asssertion: {0} failed ---- File: {1} | Line: {2}", description, \
	__FILE__, __LINE__); \
	__debugbreak(); \
}
#else
#define ASSERT(expr, description) //evaluates to nothing
#endif

/**
 * \brief Used to easily benchmark a given procedure and print the result out
 * using the given name
 */
template <typename Function, typename... Args>
double Benchmark(Function && func, Args&&... args) {
	// Start the timer
	auto startTime = std::chrono::high_resolution_clock::now();

	// Execute the function with the provided arguments
	std::invoke(std::forward<Function>(func), std::forward<Args>(args)...);

	// Stop the timer and calculate the elapsed time in milliseconds
	auto endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> elapsedTime = endTime - startTime;

	return elapsedTime.count();
}