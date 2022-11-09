set(COSMOS_WEB_CORE_BINDING_HEADERS

)

set(COSMOS_WEB_CORE_BINDING_SOURCE
    cosmos_web_core_bindings.cpp
)

# Create bindings library
add_library(cosmos_web_core_bindings ${COSMOS_WEB_CORE_BINDING_SOURCE} ${COSMOS_WEB_CORE_BINDING_HEADERS})
target_link_libraries(cosmos_web_core_bindings
    # Link to our library
    CosmosSupport
    CosmosMath

    # Emscripten compiler options
    "-o ${PROJECT_SOURCE_DIR}/build/CosmosWebCore.js"
    "--bind"
    "-s WASM=1"
    "-s MODULARIZE=1"
    "-s EXPORT_NAME=COSMOSJS"
    "-s DISABLE_EXCEPTION_CATCHING=0"
    "-s ALLOW_MEMORY_GROWTH=1"
)
