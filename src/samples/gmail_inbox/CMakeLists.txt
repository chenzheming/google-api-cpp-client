project (Gmail_Inbox)

include_directories(${GFLAGS_INCLUDES})
INCLUDE_DIRECTORIES(${GOOGLEAPIS_SERVICE_REPOSITORY_DIR}/gmail)

add_executable(gmail_inbox main.cc
                           inbox.cc
                           command.cc
                           storage.cc
                           encription.cc
                           new_http_transport_layer_config.cc
                           authorization.cc
                           http_status.cc)

target_link_libraries(gmail_inbox google_gmail_api)
target_link_libraries(gmail_inbox googleapis_jsoncpp)
target_link_libraries(gmail_inbox googleapis_curl_http)
target_link_libraries(gmail_inbox googleapis_http)
target_link_libraries(gmail_inbox googleapis_oauth2)
target_link_libraries(gmail_inbox googleapis_utils)
if (HAVE_OPENSSL)
target_link_libraries(gmail_inbox googleapis_openssl_codec)
endif()
target_link_libraries(gmail_inbox ${GFLAGS_LIBRARY})
target_link_libraries(gmail_inbox pthread)


add_executable(test_storage test_storage.cc
                            storage.cc)

add_executable(test_encription test_encription.cc
                               encription.cc)
