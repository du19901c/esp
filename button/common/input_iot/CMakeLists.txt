set(app_src input_iot.c)
set(pri_req)
set(IDF_PATH "C:/esp/esp-idf")
idf_component_register(SRCS ${app_src}
                    INCLUDE_DIRS "."
                    REQUIRES ${pri_req})