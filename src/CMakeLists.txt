set (utils_DIR          ${SOURCE_DIR}/utils)
set (xml4nlp_DIR        ${SOURCE_DIR}/xml4nlp/)
set (segmentor_DIR      ${SOURCE_DIR}/segmentor)
set (postagger_DIR      ${SOURCE_DIR}/postagger)
set (parser_DIR         ${SOURCE_DIR}/parser)
set (parser_n_DIR       ${SOURCE_DIR}/parser_n)
set (splitsnt_DIR       ${SOURCE_DIR}/splitsnt)
set (ner_DIR            ${SOURCE_DIR}/ner/)
set (srl_DIR            ${SOURCE_DIR}/srl/)
set (ltp_DIR            ${SOURCE_DIR}/ltp/)
set (server_DIR         ${SOURCE_DIR}/server/)

add_subdirectory ("segmentor")

# mongoose server is not supported in windows
if (UNIX)
endif()


