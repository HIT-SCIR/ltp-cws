include_directories (./
    ${SOURCE_DIR}/segmentor
    ${SOURCE_DIR}/utils
    ${THIRDPARTY_DIR}/tinythreadpp)


link_directories ( ${LIBRARY_OUTPUT_PATH} )

add_executable (cws_cmdline cws_cmdline.cpp)
target_link_libraries (cws_cmdline segmentor_static_lib
    boost_regex_static_lib)

add_executable (multi_cws_cmdline multi_cws_cmdline.cpp
    ${THIRDPARTY_DIR}/tinythreadpp/tinythread.cpp)

add_executable (customized_cws_cmdline customized_cws_cmdline.cpp)
target_link_libraries (customized_cws_cmdline segmentor_static_lib
    boost_regex_static_lib)

add_executable (multi_customized_cws_cmdline multi_customized_cws_cmdline.cpp
    ${THIRDPARTY_DIR}/tinythreadpp/tinythread.cpp)

if (UNIX)
target_link_libraries (multi_cws_cmdline segmentor_static_lib
    boost_regex_static_lib
    pthread)
target_link_libraries (multi_customized_cws_cmdline segmentor_static_lib
    boost_regex_static_lib
    pthread)
else ()
target_link_libraries (multi_cws_cmdline segmentor_static_lib
    boost_regex_static_lib)
target_link_libraries (multi_customized_cws_cmdline segmentor_static_lib
    boost_regex_static_lib)
endif ()

