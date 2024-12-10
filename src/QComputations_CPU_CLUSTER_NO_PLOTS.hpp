//#define _USE_MATH_DEFINES
#ifndef ENABLE_MPI
#define ENABLE_MPI
#endif

#ifndef ENABLE_CLUSTER
#define ENABLE_CLUSTER
#endif

#pragma once
#include <mpi.h>

#include "QComputations/blocked_matrix.hpp"
#include "QComputations/blocked_vector.hpp"
#include "QComputations/config.hpp"
#include "QComputations/dynamic.hpp"
#include "QComputations/functions.hpp"
#include "QComputations/graph.hpp"
#include "QComputations/hamiltonian.hpp"
#include "QComputations/hamiltonian_blocked.hpp"
#include "QComputations/matrix.hpp"
#include "QComputations/mpi_functions.hpp"
#include "QComputations/plot.hpp"
#include "QComputations/state.hpp"
#include "QComputations/test.hpp"
