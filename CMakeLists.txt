#Created by VisualGDB. Right-click on the component in Solution Explorer to edit properties using convenient GUI.

idf_component_register(
	SRCS esp_lvgl.cpp displaymonochrome.cpp
	INCLUDE_DIRS "."
	REQUIRES lvgl ESP_Base ESP_Drivers)
