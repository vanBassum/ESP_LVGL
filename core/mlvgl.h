#pragma once
#include "esp_system.h"
#include "kernel.h"
#include "esp_log.h"
#include "lvgl.h"
#include <functional>
#include <type_traits>

#define LVGL_HANDLER_TICK_MS	5	//The timing is not critical but it should be about 5 milliseconds to keep the system responsive.
#define LVGL_TIMER_TICK_MS		1

namespace ESP_LVGL
{
	class DebugMutex
	{
		const char* description;
		Mutex mutex;
		Mutex dMut;
	public:
		
		bool Take(const char* descr, TickType_t timeout = portMAX_DELAY)
		{
			dMut.Take();
			if (mutex.IsTaken())
				ESP_LOGE("DebugMutex", "Taken %s", description);			
			description = descr;
			dMut.Give();
			return mutex.Take(timeout);
		}

		bool Give()
		{
			return mutex.Give();
		}
		
		
	};
	
	
class LVGL
	{
		const char* TAG = "LVGL";
		static Mutex singletonMutex;
		static LVGL* instance;

		int coreId = -1;
		Task task;
		Timer timer;	
		DebugMutex mutex;
		
		/**
         * @brief Private constructor for the LVGL class.
         * 
         * This constructor initializes the LVGL library, creates a task, and starts a timer
         * to handle LVGL operations.
         */
		LVGL();

		/**
		 * @brief LVGL task's main function.
		 * 
		 * This function runs in a separate task and handles LVGL operations continuously.
		 * It updates the coreId with the current core ID on which the LVGL task is running.
		 * 
		 * @param task Pointer to the task instance (unused).
		 * @param args Pointer to additional arguments (unused).
		 */
		void Work(Task* task, void* args);

		/**
		 * @brief Execute an LVGL function safely on the LVGL task's core.
		 * 
		 * This function is used internally by the ExecuteSafely() method to execute LVGL commands safely.
		 * It checks whether the current core ID matches the LVGL task's core ID before executing
		 * the provided function.
		 * 
		 * @param function The function containing LVGL commands to execute.
		 */
		void Execute(std::function<void()> function, const char* d);
		
	public:
		/**
         * @brief Get the singleton instance of the LVGL class.
         * 
         * @return LVGL& The reference to the LVGL singleton instance.
         */
		static LVGL& GetOrCreateInstance();

		/**
		 * @brief Execute an LVGL function safely on the LVGL task's core.
		 * 
		 * This function ensures that the LVGL commands are executed on the same core
		 * where LVGL tasks are running. It is used to safely execute LVGL-related commands.
		 * 
		 * @param function The function containing LVGL commands to execute.
		 */
		static void ExecuteSafely(std::function<void()> function, const char* d);

		// The copy constructor and assignment operator are deleted to prevent cloning and assignment.
		LVGL(LVGL &other) = delete;
		void operator=(const LVGL &) = delete;
	};
}
