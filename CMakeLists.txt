#Created by VisualGDB. Right-click on the component in Solution Explorer to edit properties using convenient GUI.

idf_component_register(
	SRCS esp_lvgl.cpp displays/display_st7735.cpp displays/display_t6963.cpp base.cpp
	INCLUDE_DIRS . displays widgets
	REQUIRES lvgl ESP_Base ESP_Drivers)
