#Created by VisualGDB. Right-click on the component in Solution Explorer to edit properties using convenient GUI.

idf_component_register(
	SRCS
		base.cpp
		esp_lvgl.cpp
	INCLUDE_DIRS
		.
		interfaces
		widgets
	REQUIRES lvgl ESP_Base ESP_Drivers)
