cmake_minimum_required(VERSION 3.24)
project(projectX)

set(CMAKE_CXX_STANDARD 20)

add_link_options(-framework CoreFoundation)

include_directories(/Users/rahimahmedov/.local/include)


add_executable(projectX src/raft/server.cpp src/raft/proto/service.grpc.pb.h src/raft/proto/service.grpc.pb.cc src/raft/proto/service.pb.cc src/raft/proto/service.pb.h src/raft/states.h)
target_link_directories(projectX PUBLIC /Users/rahimahmedov/.local/lib)
target_link_libraries(projectX
        protobuf
        grpc++_reflection
        grpc++_unsecure
        grpc_unsecure
        gpr
        absl_raw_hash_set
        absl_hashtablez_sampler
        absl_hash
        absl_city
        absl_low_level_hash
        absl_random_distributions
        absl_random_seed_sequences
        absl_random_internal_pool_urbg
        absl_random_internal_randen
        absl_random_internal_randen_hwaes
        absl_random_internal_randen_hwaes_impl
        absl_random_internal_randen_slow
        absl_random_internal_platform
        absl_random_internal_seed_material
        absl_random_seed_gen_exception
        absl_statusor
        absl_status
        absl_cord
        absl_cordz_info
        absl_cord_internal
        absl_cordz_functions
        absl_exponential_biased
        absl_cordz_handle
        absl_bad_optional_access
        absl_strerror
        absl_str_format_internal
        absl_synchronization
        absl_graphcycles_internal
        absl_stacktrace
        absl_symbolize
        absl_debugging_internal
        absl_demangle_internal
        absl_malloc_internal
        absl_time
        absl_civil_time
        absl_strings
        absl_strings_internal
        absl_base
        absl_spinlock_wait
        absl_int128
        absl_throw_delegate
        absl_time_zone
        absl_bad_variant_access
        absl_raw_logging_internal
        absl_log_severity
        upb
        z
        cares
        address_sorting
        resolv
        )


add_executable(projectX_client src/raft/proto/service.grpc.pb.h src/raft/proto/service.grpc.pb.cc src/raft/proto/service.pb.cc src/raft/proto/service.pb.h src/raft/client.cpp)
target_link_directories(projectX_client PUBLIC /Users/rahimahmedov/.local/lib)
target_link_libraries(projectX_client
        protobuf
        grpc++_reflection
        grpc++_unsecure
        grpc_unsecure
        gpr
        absl_raw_hash_set
        absl_hashtablez_sampler
        absl_hash
        absl_city
        absl_low_level_hash
        absl_random_distributions
        absl_random_seed_sequences
        absl_random_internal_pool_urbg
        absl_random_internal_randen
        absl_random_internal_randen_hwaes
        absl_random_internal_randen_hwaes_impl
        absl_random_internal_randen_slow
        absl_random_internal_platform
        absl_random_internal_seed_material
        absl_random_seed_gen_exception
        absl_statusor
        absl_status
        absl_cord
        absl_cordz_info
        absl_cord_internal
        absl_cordz_functions
        absl_exponential_biased
        absl_cordz_handle
        absl_bad_optional_access
        absl_strerror
        absl_str_format_internal
        absl_synchronization
        absl_graphcycles_internal
        absl_stacktrace
        absl_symbolize
        absl_debugging_internal
        absl_demangle_internal
        absl_malloc_internal
        absl_time
        absl_civil_time
        absl_strings
        absl_strings_internal
        absl_base
        absl_spinlock_wait
        absl_int128
        absl_throw_delegate
        absl_time_zone
        absl_bad_variant_access
        absl_raw_logging_internal
        absl_log_severity
        upb
        z
        cares
        address_sorting
        resolv
        )

add_executable(thread_check src/raft/thread_check.cpp)

add_executable(rbtree src/lsmtree/rbtree.h src/tests/rbtree_test.cpp src/tests/rbtree_test.h)

add_executable(bloom src/lsmtree/bloom.h src/tests/bloom_test.cpp)

add_executable(btree src/lsmtree/btree.h src/tests/btree_test.cpp src/tests/btree_test.h)