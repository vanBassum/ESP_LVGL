#Created by VisualGDB. Right-click on the component in Solution Explorer to edit properties using convenient GUI.

idf_component_register(
	SRCS esp_lvgl.cpp displays/display_t6963.cpp displays/display_st7735.cpp
	INCLUDE_DIRS "." "displays"
	REQUIRES lvgl ESP_Base ESP_Drivers)
