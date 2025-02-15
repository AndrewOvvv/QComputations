cmake_minimum_required(VERSION 3.12)
project(MyProject)

# Set Intel OneAPI installation path
set(LIB_ROOT "/usr/lib/x86_64-linux-gnu/lib")

# Set Intel MKL variables
set(MKL_INCLUDE_DIRS "$ENV{ONEAPI_ROOT}/mkl/latest/include")
set(MKL_LIBRARIES "$ENV{ONEAPI_ROOT}/mkl/latest/lib/intel64")

# Set BLACS and ScaLAPACK variables
set(SCALAPACK_INCLUDE_DIRS "$ENV{ONEAPI_ROOT}/mkl/latest/include")
set(SCALAPACK_LIBRARIES "$ENV{ONEAPI_ROOT}/mkl/latest/lib/intel64/libmkl_scalapack_lp64.so")
set(BLACS_LIBRARIES "$ENV{ONEAPI_ROOT}/mkl/latest/lib/intel64/libmkl_blacs_intelmpi_lp64.so")

# Set Intel Python variables
set(INTEL_PYTHON_INCLUDE_DIRS "$ENV{ONEAPI_ROOT}/intelpython/latest/include/python3" "$ENV{ONEAPI_ROOT}/intelpython/python3.9/lib/python3.9/site-packages/numpy/core/include")
set(INTEL_PYTHON_LIBRARIES "$ENV{ONEAPI_ROOT}/intelpython/latest/lib")

# Set Intel MPI variables
set(MPI_INCLUDE_DIRS "$ENV{ONEAPI_ROOT}/mpi/latest/include")
set(MPI_LIBRARIES "$ENV{ONEAPI_ROOT}/mpi/latest/lib/release/libmpi.so")

# Add source files to be compiled
file(GLOB SOURCE_FILES "../src/QComputations/*.cpp")

# Function to create custom build targets for the given options
function(create_build_target TARGET_NAME PYTHON_FLAG)
    # Create target
    add_library(${TARGET_NAME} SHARED ${SOURCE_FILES})

    # Set flags
    target_compile_options(${TARGET_NAME} PRIVATE -qopenmp -qmkl=parallel -DENABLE_MPI -DENABLE_CLUSTER)

    # Link libraries
    #target_link_libraries(${TARGET_NAME} /lib/x86_64-linux-gnu/libdl.so.2)
    #target_link_libraries(${TARGET_NAME} /lib/x86_64-linux-gnu/libm.so.6)
    #target_link_libraries(${TARGET_NAME} ${MKL_LIBRARIES}/libmkl_scalapack_lp64.so)
    #target_link_libraries(${TARGET_NAME} ${MKL_LIBRARIES}/libmkl_blacs_intelmpi_lp64.so)
    #target_link_libraries(${TARGET_NAME} ${MKL_LIBRARIES}/libmkl_intel_lp64.so)
    #target_link_libraries(${TARGET_NAME} ${MKL_LIBRARIES}/libmkl_intel_thread.so)
    #target_link_libraries(${TARGET_NAME} ${MKL_LIBRARIES}/libmkl_sequential.so)
    #target_link_libraries(${TARGET_NAME} ${MKL_LIBRARIES}/libmkl_core.so)
    #target_link_libraries(${TARGET_NAME} ${INTEL_PYTHON_LIBRARIES}/libiomp5.so)
    #target_link_libraries(${TARGET_NAME} ${MKL_LIBRARIES}/libmkl_core.so)
    #target_link_libraries(${TARGET_NAME} ${SCALAPACK_LIBRARIES})
    #target_link_libraries(${TARGET_NAME} ${BLACS_LIBRARIES})

    if (PYTHON_FLAG)
        target_link_libraries(${TARGET_NAME} ${INTEL_PYTHON_LIBRARIES}/libpython3.so)
        target_compile_options(${TARGET_NAME} PRIVATE -DENABLE_MATPLOTLIB)
        target_include_directories(${TARGET_NAME} PRIVATE ${INTEL_PYTHON_INCLUDE_DIRS})
        #target_link_libraries(${TARGET_NAME} ${INTEL_PYTHON_LIBRARIES})
    endif()

    #target_include_directories(${TARGET_NAME} PRIVATE ${MKL_INCLUDE_DIRS})
    #target_include_directories(${TARGET_NAME} PRIVATE ${SCALAPACK_INCLUDE_DIRS})
    #target_include_directories(${TARGET_NAME} PRIVATE ${MPI_INCLUDE_DIRS})
    #target_link_libraries(${TARGET_NAME} ${MPI_LIBRARIES})
    target_link_options(${TARGET_NAME} PRIVATE -qmkl=parallel -lmkl_blacs_intelmpi_lp64 -lmkl_scalapack_lp64)
endfunction()

# Create build targets
create_build_target(QComputations_CPU_CLUSTER ON)
create_build_target(QComputations_CPU_CLUSTER_NO_PLOTS OFF)
